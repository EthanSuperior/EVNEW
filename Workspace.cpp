#include "Workspace.h"
#include "EVNEW.h"
#include <regex>

Workspace& Workspace::Get()
{
	static Workspace instance;
	return instance;
}
Workspace::~Workspace() { 
	Clear();
}

void Workspace::Clear()
{
	for (auto& p : GetData()) delete p;
	GetData().clear();
	for (auto& p : GetPlugins()) delete p;
	GetPlugins().clear();
	GetNCB().clear();
}

std::vector<CPlugIn*>& Workspace::GetData() { return Get().data; }
std::vector<CPlugIn*>& Workspace::GetPlugins() { return Get().plugins; }
std::set<int> Workspace::GetNCB() { return Get().usedNCB; }

CPlugIn* Workspace::ActiveFile()
{
	return Get().active;
}

int Workspace::Change(std::string filename, CWindow* pWndParent)
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

int Workspace::Open(std::string filename, CWindow* pWndParent)
{
	Workspace& instance = Get();
	instance.rootPath = std::filesystem::path(filename).parent_path().parent_path().generic_string();
	AddFolder(instance.rootPath + "/Nova Files", pWndParent, instance.data);
	AddFolder(instance.rootPath + "/Nova Plug-ins", pWndParent, instance.plugins);
	instance.gamePath = instance.rootPath + "";
	return Change(filename, pWndParent);
}

void Workspace::AddFolder(std::string path, CWindow* pWndParent, std::vector<CPlugIn*>& files) {
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		if (!entry.is_regular_file()) continue;
		if (entry.path().extension() == ".rez") { // ADD .txt files? and .plt files?
			AddRezFile(entry.path().string(), pWndParent, files);
		}
	}
}

void Workspace::AddRezFile(std::string filename, CWindow* pWndParent, std::vector<CPlugIn*>& files)
{
	CPlugIn* lib = new CPlugIn();
	lib->Load(filename.data(), pWndParent);
	files.insert(files.begin(), lib);
}

NovaResourceRange Workspace::Each(int type)
{
	return NovaResourceRange(type);
}

std::vector<CNovaResource*> Workspace::All(int type)
{
	NovaResourceRange v = Workspace::Each(type);
	std::vector<CNovaResource*> result;
	result.reserve(v.end().idx);
	for (const auto& res : v) result.push_back(res);
	return result;
}

std::vector<CNovaResource*> Workspace::Filter(int type, ResourceFilter f)
{
	NovaResourceRange v = Workspace::Each(type);
	std::vector<CNovaResource*> result;
	result.reserve(v.end().idx);
	for (auto& r = v.begin(), e = v.end(); r != e; ++r)
		if(f(*r, r.idx)) result.push_back(*r);
	return result;
}

std::vector<std::string> Workspace::Names(int type) {
	NovaResourceRange v = Workspace::Each(type);
	std::vector<std::string> result;
	result.reserve(v.end().idx);
	for (auto& r = v.begin(), e = v.end(); r != e; ++r)
		result.push_back(std::to_string((*r)->GetID()) + ": " + (*r)->GetName() + "-" + r.PluginFilename());
	return result;
}

// Single Access
CNovaResource* Workspace::FindById(int type, int id) {
	for (auto& r : Workspace::Each(type))
		if (r->GetID() == id) return r;
	return NULL;
}

CNovaResource* Workspace::FindByIdx(int type, int i)
{
	NovaResourceRange v = Workspace::Each(type);
	for (auto& r = v.begin(), e = v.end(); r != e; ++r)
		if (r.idx == i) return *r;
	return NULL;
}

CNovaResource* Workspace::FindWhere(int type, ResourceFilter f)
{
	NovaResourceRange v = Workspace::Each(type);
	for (auto& r = v.begin(), e = v.end(); r != e; ++r)
		if (f(*r, r.idx)) return *r;
	return NULL;
}

std::string Workspace::RezStr(int type, int id, bool addType) {
	CNovaResource* ptr = FindById(type, id);
	if (ptr == NULL) return "None";
	if (!addType) return std::string(ptr->GetName());
	return g_szResourceTypes[type] + std::string(": ") + ptr->GetName();
}

// NCB Helper Methods
void Workspace::UpdateNCBList() {
	usedNCB.clear();
	for (int i = 0; i < NUM_RESOURCE_TYPES; i++)
		for (auto& r: Workspace::Each(i)) r->RegisterNCB();
}

void Workspace::RegisterNCB(const char* expression)
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

std::string Workspace::GetAvailableNCB()
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