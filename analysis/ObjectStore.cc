
#include "ObjectStore.hh"

#include <map>
#include <string>
#include <vector>

#include <typeinfo>

Collection::Collection()
{
}

Collection::~Collection()
{
}


ObjectStore::ObjectStore()
{
}


std::vector<std::string> ObjectStore::GetCollectionNames()
{
    std::vector<std::string> names;
    for (std::map<std::string,const Collection*>:: const_iterator it=_store.begin(); it!=_store.end();++it)
    {
        names.push_back(it->first);
    }
    return names;
}

std::string ObjectStore::GetType(std::string name)
{
    if (_store.find(name)==_store.end())
    {
        throw "'"+name+"' not found in ObjectStore";
    }
    return _store[name]->GetType();
}


ObjectStore::~ObjectStore()
{
}



