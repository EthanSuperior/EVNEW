#pragma once
#include "CNovaResource.h"
#include <string>

class Workspace;

class NovaResourceRange
{
public:
    NovaResourceRange(int type) :rezType(type) {}
    class Iterator
    {
    public:
        //using iterator_category = std::bidirectional_iterator_tag;
        using value_type = CNovaResource*;
        using pointer = value_type*;
        using reference = value_type&;
        Iterator(pointer ptr, int type, int idx, bool onPlugins, int i, int pluginIdx)
            : ptr(ptr), rezType(type), idx(idx), onPlugins(onPlugins), i(i), pluginIdx(pluginIdx) {}
        pointer operator->() { return ptr; }
        reference operator*() const { return *ptr; }
        Iterator& operator++();
        Iterator& operator--();
        std::string PluginFilename();
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; };
        int idx;
    private:
        pointer ptr = nullptr;
        bool onPlugins; int pluginIdx; int rezType;
        int i;
    };
    Iterator begin() const;
    Iterator end() const;
    int rezType;
};

