#pragma once

#include "CNovaResource.h"
#include "NovaLib.h"

class NovaLibResourceRange
{
public:
    NovaLibResourceRange(int type) :rezType(type) {}
    struct Iterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using value_type = CNovaResource*;
        using pointer = value_type*;
        using reference = value_type&;
        Iterator(pointer ptr) : m_ptr(ptr) {}
        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        reference operator[](int index) { return *m_ptr; }
        Iterator& operator++() { m_ptr++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
    private:
        pointer m_ptr;
        int idx;
        bool onData = true;
        int pluginIdx;
    };
    Iterator begin() {
        return Iterator(NovaLib::GetData().front()->m_vResources[rezType].begin()._Ptr);
    }
    Iterator end() {
        return Iterator(NovaLib::GetPlugins().back()->m_vResources[rezType].end()._Ptr);
    }
private:
    int rezType;
};