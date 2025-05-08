#include "NovaLib.h"
#include "EVNEW.h"
#include <regex>


NovaLib& NovaLib::Get()
{
	static NovaLib instance;
	return instance;
}
NovaLib::~NovaLib() { 
	Clear();
}

void NovaLib::Clear()
{
	for (auto& p : GetData()) delete p;
	GetData().clear();
	for (auto& p : GetPlugins()) delete p;
	GetPlugins().clear();
	GetNCB().clear();
}

std::vector<CPlugIn*>& NovaLib::GetData() { return Get().data; }
std::vector<CPlugIn*>& NovaLib::GetPlugins() { return Get().plugins; }
std::set<int> NovaLib::GetNCB() { return Get().usedNCB; }

CPlugIn* NovaLib::ActiveFile()
{
	return Get().active;
}

int NovaLib::Change(std::string filename, CWindow* pWndParent)
{
	auto path = std::filesystem::path(filename);
	for (auto& p : GetPlugins())
		if (std::filesystem::path(p->GetFilename()) == path) {
			Get().active = p;

			return 1;
		}
	for (auto& p : GetData())
		if (std::filesystem::path(p->GetFilename()) == path) {
			Get().active = p;

			return 1;
		}
	CPlugIn* opened = new CPlugIn();
	GetPlugins().push_back(opened);
	return opened->Load(path.string().data(), pWndParent);
}

int NovaLib::Open(std::string filename, CWindow* pWndParent)
{
	NovaLib& instance = Get();
	instance.rootPath = std::filesystem::path(filename).parent_path().parent_path().generic_string();
	AddFolder(instance.rootPath + "/Nova Files", pWndParent, instance.data);
	AddFolder(instance.rootPath + "/Nova Plug-ins", pWndParent, instance.plugins);
	instance.gamePath = instance.rootPath + "";
	return Change(filename, pWndParent);
}

void NovaLib::AddFolder(std::string path, CWindow* pWndParent, std::vector<CPlugIn*>& files) {
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		if (!entry.is_regular_file()) continue;
		if (entry.path().extension() == ".rez") { // ADD .txt files? and .plt files?
			AddRezFile(entry.path().string(), pWndParent, files);
		}
	}
}

void NovaLib::AddRezFile(std::string filename, CWindow* pWndParent, std::vector<CPlugIn*>& files)
{
	CPlugIn* lib = new CPlugIn();
	lib->Load(filename.data(), pWndParent);
	files.insert(files.begin(), lib);
}

NovaResourceRange NovaLib::Each(int type)
{
	return NovaResourceRange(type);
}

std::vector<CNovaResource*> NovaLib::All(int type)
{
	NovaResourceRange v = NovaLib::Each(type);
	std::vector<CNovaResource*> result;
	result.reserve(v.end().idx);
	for (const auto& res : v) result.push_back(res);
	return result;
}

std::vector<CNovaResource*> NovaLib::Filter(int type, ResourceFilter f)
{
	NovaResourceRange v = NovaLib::Each(type);
	std::vector<CNovaResource*> result;
	result.reserve(v.end().idx);
	for (auto& r = v.begin(), e = v.end(); r != e; ++r)
		if(f(*r, r.idx)) result.push_back(*r);
	return result;
}

std::vector<std::string> NovaLib::Names(int type) {
	NovaResourceRange v = NovaLib::Each(type);
	std::vector<std::string> result;
	result.reserve(v.end().idx);
	for (auto& r = v.begin(), e = v.end(); r != e; ++r)
		result.push_back(std::to_string((*r)->GetID()) + ": " + (*r)->GetName() + "-" + r.PluginFilename());
	return result;
}

// Single Access
CNovaResource* NovaLib::FindById(int type, int id) {
	for (auto& r : NovaLib::Each(type))
		if (r->GetID() == id) return r;
	return NULL;
}

CNovaResource* NovaLib::FindByIdx(int type, int i)
{
	NovaResourceRange v = NovaLib::Each(type);
	for (auto& r = v.begin(), e = v.end(); r != e; ++r)
		if (r.idx == i) return *r;
	return NULL;
}

CNovaResource* NovaLib::FindWhere(int type, ResourceFilter f)
{
	NovaResourceRange v = NovaLib::Each(type);
	for (auto& r = v.begin(), e = v.end(); r != e; ++r)
		if (f(*r, r.idx)) return *r;
	return NULL;
}

std::string NovaLib::RezStr(int type, int id, bool addType) {
	CNovaResource* ptr = FindById(type, id);
	if (ptr == NULL) return "None";
	if (!addType) return std::string(ptr->GetName());
	return g_szResourceTypes[type] + std::string(": ") + ptr->GetName();
}

// NCB Helper Methods
void NovaLib::UpdateNCBList() {
	usedNCB.clear();
	for (int i = 0; i < NUM_RESOURCE_TYPES; i++)
		for (auto& r: NovaLib::Each(i)) r->RegisterNCB();
}

void NovaLib::RegisterNCB(const char* expression)
{
	static const std::regex pattern(R"(b(\d{1,4}))");
	const char* begin = expression;
	std::cmatch match;

	while (std::regex_search(begin, match, pattern)) {
		int bit = std::stoi(match[1]);
		if (bit >= 0 && bit <= 9999) Get().usedNCB.insert(bit);
		begin = match.suffix().first;
	}
}

std::string NovaLib::GetAvailableNCB()
{
	std::ostringstream output;
	int start = 0;

	for (int bit : Get().usedNCB) {
		if (bit > start) {
			if (!output.str().empty()) output << ", ";
			output << start;
			if (bit - 1 != start) output << "-" << (bit - 1);
		}
		start = bit + 1;
	}

	if (!output.str().empty()) output << ", ";

	if (start > 9999) return output.str();
	else if (start == 9999) return output.str() + "9999";
	else return output.str() + std::to_string(start) + "-9999";
}