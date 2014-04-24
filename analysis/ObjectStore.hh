#ifndef OBJECTSTORE_H
#define OBJECTSTORE_H

#include <map>
#include <string>
#include <vector>

#include <typeinfo>

#include "demangle.hh"

class Collection
{
    public:
        Collection();
        virtual std::string GetType() const=0;
        virtual ~Collection();
};

template<class TYPE>
class CollectionTmpl:
    public Collection
{
    protected:
        std::string _type;
        std::vector<const TYPE*> _collection;
    public:
        CollectionTmpl(std::string type, std::vector<const TYPE*> collection):
            _type(type),
            _collection(collection)
        {
        }
        
        virtual std::string GetType() const
        {
            return demangle(typeid(TYPE).name());
        }
        
        const std::vector<const TYPE*>& Get() const
        {
            return _collection;
        }
        
        virtual ~CollectionTmpl()
        {
        }
};

class ObjectStore
{
    protected:
        std::map<std::string,const Collection*> _store;
    public:
        ObjectStore();
        
        template<class TYPE> void Put(std::string name, std::vector<const TYPE*> collection)
        {
            if (_store.find(name)!=_store.end())
            {
                throw "'"+name+"' already exists in ObjectStore"; 
            }
            Collection* container = new CollectionTmpl<TYPE>(name,collection);
            _store[name]=container;
        }
        
        std::vector<std::string> GetCollectionNames();
        
        std::string GetType(std::string name);
        
        template<class TYPE> const std::vector<const TYPE*>& Get(std::string name)
        {
            if (_store.find(name)==_store.end())
            {
                throw "'"+name+"' not found in ObjectStore";
            }
            const CollectionTmpl<TYPE>* container = dynamic_cast<const CollectionTmpl<TYPE>*>(_store[name]);
            if (!container)
            {
                throw "'"+name+"' is of type '"+_store[name]->GetType()+"'; NOT of requested type '"+demangle(typeid(TYPE).name())+"'";
            }
            return container->Get();
        }
        
        ~ObjectStore();
};

#endif

