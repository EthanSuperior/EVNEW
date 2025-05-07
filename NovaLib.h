#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <vector>

#include "CPlugIn.h"
#include <set>

class CEditor;

// std::ofstream ofstream("log.txt", std::ios::app);
// ofstream << iNotifyCode << std::endl;

class NovaLib
{
public:
	static NovaLib &Get();
	void AddFolder(std::string path, CWindow *pWndParent);
	void AddRezFile(std::string filename, CWindow *pWndParent);
	static CNovaResource *Find(int type, int id);
	static char *RezName(int type, int id);
	static std::string RezStr(int type, int id, bool addType = false);
	static std::vector<CNovaResource*> GetAllOf(int type);
	static CNovaResource* AtIdx(int type, int idx);
	static void RegisterNCB(const char* expression);
	static std::string GetAvailableNCB();
	void Clear();
	void UpdateNCBList();
	std::map<int, CNovaResource *> rez[NUM_RESOURCE_TYPES] = {};
private:
	NovaLib() = default;
	~NovaLib();
	// Prevent copying and assignment
	NovaLib(const NovaLib&) = delete;
	NovaLib& operator=(const NovaLib&) = delete;
	std::set<int> usedNCB = {};
};
