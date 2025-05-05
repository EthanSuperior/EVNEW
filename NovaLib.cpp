#include "NovaLib.h"
#include "EVNEW.h"

NovaLib* NovaLib::instance = NULL;

NovaLib& NovaLib::Get()
{
	if (instance == NULL) instance = new NovaLib();
	return *instance;
}

CNovaResource* NovaLib::At(int type, int id) {
	if (type < 0 || type >= NUM_RESOURCE_TYPES) return NULL;
	auto it = Get().rez[type].find(id);
	if (it != Get().rez[type].end()) return it->second;
	// If not found, check if the ID is within the current plugin
	return CEditor::GetCurrentEditor()->Find(type, id);
}

char* NovaLib::RezName(int type, int id) {
	CNovaResource* ptr = At(type, id);
	if (ptr == NULL) return "None";
	return ptr->GetName();
}

std::string NovaLib::RezStr(int type, int id, bool addType) {
	CNovaResource* ptr = At(type, id);
	if (ptr == NULL) return "None";
	if (!addType) return std::string(ptr->GetName());
	return g_szResourceTypes[type] + std::string(": ") + ptr->GetName();
}

std::vector<CNovaResource*> NovaLib::GetAllOf(int type)
{
	std::vector<CNovaResource*> values(CEditor::GetCurrentPlugin()->m_vResources[type]);
	for (auto& [id, val] : Get().rez[type])	values.push_back(val);
	return values;
}


NovaLib::~NovaLib(){ Clear(); }

void NovaLib::AddFolder(std::string path, CWindow* pWndParent) {
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		if (entry.is_regular_file() && entry.path().extension() == ".rez")
			AddRezFile(entry.path().lexically_normal().string(), pWndParent);
	}
}

void NovaLib::AddRezFile(std::string filename, CWindow* pWndParent)
{
	CPlugIn lib;
	lib.Load((char*)filename.c_str(), pWndParent);

	for (int i = 0; i < NUM_RESOURCE_TYPES; i++) {
		for (int j = 0; j < lib.m_vResources[i].size(); j++) {
			if (lib.m_vResources[i][j] == NULL) continue;
			rez[i][lib.m_vResources[i][j]->GetID()] = lib.m_vResources[i][j];
			lib.m_vResources[i][j] = NULL;
		}
	}
}

void NovaLib::Clear()
{
	if (instance == NULL) return;
	for (int i = 0; i < NUM_RESOURCE_TYPES; ++i) {
		for (auto& [id, ptr] : rez[i]) delete ptr;
		rez[i].clear();
	}
}

