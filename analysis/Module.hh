#ifndef __MODULE_H__
#define __MODULE_H__

#include "ObjectStore.hh"

class Module
{
    protected:
    public:
        Module();
        void process(ObjectStore& objStore);
        ~Module();
};

#endif

