#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <vector>

#include "CPlugIn.h"

class CEditor;

// std::ofstream ofstream("log.txt", std::ios::app);
// ofstream << iNotifyCode << std::endl;

class NovaLib
{
public:
	static NovaLib &Get();
	void AddFolder(std::string path, CWindow *pWndParent);
	void AddRezFile(std::string filename, CWindow *pWndParent);
	static CNovaResource *At(int type, int id);
	static char *RezName(int type, int id);
	static std::string RezStr(int type, int id, bool addType = false);
	static std::vector<CNovaResource *> GetAllOf(int type);
	void Clear();
	std::map<int, CNovaResource *> rez[NUM_RESOURCE_TYPES] = {};

private:
	NovaLib() = default;
	~NovaLib();
	static NovaLib *instance;
};
