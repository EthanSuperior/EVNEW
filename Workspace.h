#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <vector>

#include "CPlugIn.h"
#include <set>
#include <functional>
#include "NovaResourceRange.h"

class CEditor;

// std::ofstream ofstream("log.txt", std::ios::app);
// ofstream << iNotifyCode << std::endl;

using ResourceFilter = std::function<bool(CNovaResource*, int)>;
class Workspace
{
public:
    static Workspace& Get();
    // Add New Resource Files
    static int Open(std::string path, CWindow* pWndParent);
    static void AddFolder(std::string path, CWindow* pWndParent, std::vector<CPlugIn*>& files);
    static void AddRezFile(std::string filename, CWindow* pWndParent, std::vector<CPlugIn*>& files);

    // Remove Resource Files
    static void Clear();

    // Accessors
    static std::vector<CPlugIn*>& GetData();
    static std::vector<CPlugIn*>& GetPlugins();
    static std::set<int> GetNCB();

    // Active Resource File
    static CPlugIn* ActiveFile();
    static CPlugIn* Change(std::string filename, CWindow* pWndParent);

    // Bulk Access
    static NovaResourceRange Each(int type);
    static std::vector<CNovaResource*> All(int type);
    static std::vector<CNovaResource*> Filter(int type, ResourceFilter f);
    static std::vector<std::string> Names(int type);

    // Single Access
    static CNovaResource* FindById(int type, int id);
    static CNovaResource* FindByIdx(int type, int idx);
    static CNovaResource* FindWhere(int type, ResourceFilter f);
    static std::string RezStr(int type, int id, bool addType = false);

    // NCB Helper Methods
    static void RegisterNCB(const char* expression);
    static std::string GetAvailableNCB();
    static void UpdateNCBList();
    std::string rootPath = "";
    CPlugIn* active;
private:
    Workspace() = default;
    ~Workspace();
    // Prevent copying and assignment
    Workspace(const Workspace&) = delete;
    Workspace& operator=(const Workspace&) = delete;
    std::set<int> usedNCB = {};
    std::vector<CPlugIn*> data;
    std::vector<CPlugIn*> plugins;
    std::string gamePath;
};
