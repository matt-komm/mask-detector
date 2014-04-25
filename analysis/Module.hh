#ifndef __MODULE_H__
#define __MODULE_H__

#include "ObjectStore.hh"

class Module
{
    protected:
    public:
        Module();
        virtual void Process(ObjectStore& objStore)=0;
        virtual ~Module();
};

#endif

