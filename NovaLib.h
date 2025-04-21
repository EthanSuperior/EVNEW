#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <vector>

#include "CPlugIn.h"

//TODO: `"syst"\t(....)\t(".*?")\t(.*)\t"EOR".\n`
//TODO: `{$1, CSystResource($1, $2, R"($3)")},\n`

class NovaLib
{
public:
	static NovaLib& Get();
	void AddFolder(std::string path, CWindow* pWndParent);
	void AddRezFile(std::string filename, CWindow* pWndParent);
	static CNovaResource* At(int type, int id);
	static char* RezName(int type, int id);
	void Clear();
	std::map<int, CNovaResource*> rez[NUM_RESOURCE_TYPES] = {};

private:
	NovaLib() = default;
	~NovaLib();
	static NovaLib* instance;
	std::vector<CPlugIn*> plugins;
};

