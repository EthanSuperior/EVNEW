#include "NovaLib.h"
#include "EVNEW.h"
#include <regex>


NovaLib& NovaLib::Get()
{
	static NovaLib instance;
	return instance;
}
NovaLib::~NovaLib() { Clear(); }

CNovaResource* NovaLib::Find(int type, int id) {
	if (type < 0 || type >= NUM_RESOURCE_TYPES) return NULL;
	auto it = Get().rez[type].find(id);
	if (it != Get().rez[type].end()) return it->second;
	// If not found, check if the ID is within the current plugin
	return CEditor::GetCurrentEditor()->Find(type, id);
}

char* NovaLib::RezName(int type, int id) {
	CNovaResource* ptr = Find(type, id);
	if (ptr == NULL) return "None";
	return ptr->GetName();
}

std::string NovaLib::RezStr(int type, int id, bool addType) {
	CNovaResource* ptr = Find(type, id);
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
CNovaResource* NovaLib::AtIdx(int type, int i)
{
	std::vector<CNovaResource*> values(CEditor::GetCurrentPlugin()->m_vResources[type]);
	if (i < values.size()) return values[i];
	for (auto& [id, val] : Get().rez[type])	values.push_back(val);
	try { return values.at(i); }
	catch (...) { return NULL; }
}

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
			lib.m_vResources[i][j]->RegisterNCB();
			lib.m_vResources[i][j] = NULL;
		}
	}
}

void NovaLib::Clear()
{
	for (int i = 0; i < NUM_RESOURCE_TYPES; ++i) {
		for (auto& [id, ptr] : rez[i]) delete ptr;
		rez[i].clear();
	}
	usedNCB.clear();
}

void NovaLib::UpdateNCBList() {
	usedNCB.clear();
	for (int i = 0; i < NUM_RESOURCE_TYPES; i++)
		for each (auto r in rez[i])
			r.second->RegisterNCB();
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