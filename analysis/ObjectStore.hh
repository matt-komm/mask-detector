#ifndef __OBJECTSTORE_H__
#define __OBJECTSTORE_H__

#include <map>
#include <string>
#include <vector>

class Collection
{
    public:
        Collection()
        {
        }
        virtual std::string getType() const=0 ;
        //template<class TYPE> virtual TYPE* get(unsigned int index) = 0;
        virtual ~Collection()
        {
        }
};

template<class TYPE>
class CollectionTmpl
{
    protected:
        std::string _type;
        std::vector<TYPE*> _collection;
    public:
        CollectionTmpl(std::string type, std::vector<TYPE*> collection):
            _type(type),
            _collection(collection)
        {
        }
        
        virtual std::string getType() const
        {
            return _type;
        }
        /*
        template<class TYPE> virtual TYPE* get(unsigned int index)
        {
            //ptr=_collection[index];
        }
        */
        virtual ~CollectionTmpl()
        {
        }
};

class ObjectStore
{
    protected:
        std::map<std::string,Collection*> _store;
    public:
        ObjectStore();
        template<class TYPE> void store(std::string name, std::vector<TYPE*> collection)
        {
            CollectionTmpl<TYPE>* container = new CollectionTmpl<TYPE>(name,collection);
            _store[name]=container;
        }
        ~ObjectStore();
};

#endif

