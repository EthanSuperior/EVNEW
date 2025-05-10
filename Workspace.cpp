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

CPlugIn* Workspace::Change(std::string filename, CWindow* pWndParent)
{
	auto path = std::filesystem::path(filename);
	for (auto& p : GetPlugins())
		if (std::filesystem::path(p->GetFilename()) == path)
			return (Get().active = p);
	for (auto& p : GetData())
		if (std::filesystem::path(p->GetFilename()) == path)
			return (Get().active = p);
	CPlugIn* opened = new CPlugIn();
	GetPlugins().push_back(opened);
	opened->Load(path.string().data(), pWndParent);
	return opened;
}

int Workspace::Open(std::string filename, CWindow* pWndParent)
{
	Workspace& instance = Get();
	instance.rootPath = std::filesystem::path(filename).parent_path().parent_path().generic_string();
	AddFolder(instance.rootPath + "/Nova Files", pWndParent, instance.data);
	AddFolder(instance.rootPath + "/Nova Plug-ins", pWndParent, instance.plugins);
	instance.gamePath = instance.rootPath + "";


	HMENU hPluginsMenu = CreatePopupMenu();
	for (size_t i = 0; i < Workspace::GetPlugins().size(); ++i) {
		char* displayName = Workspace::GetPlugins()[i]->GetFilenameNoPath();
		AppendMenuA(hPluginsMenu, MF_STRING, 50000 + static_cast<UINT>(i), displayName);
	}
	HWND hwnd = pWndParent->GetHWND();
	HMENU hMainMenu = GetMenu(hwnd);
	InsertMenuA(GetSubMenu(hMainMenu, 2), 3, MF_BYPOSITION | MF_POPUP, (UINT_PTR)hPluginsMenu, "Switch Active");

	DrawMenuBar(hwnd);


	return Change(filename, pWndParent)!=NULL?1:0;
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

NovaResourceRange Workspace::Each(int type) { return NovaResourceRange(type); }

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
	Get().usedNCB.clear();
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
	UpdateNCBList();
	std::ostringstream output;
	int start = 0;
	output << "Available:\n";
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