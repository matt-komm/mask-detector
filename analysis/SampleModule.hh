#ifndef SAMPLEMODULE_H
#define SAMPLEMODULE_H

#include "Module.hh"
#include "SimHit.hh"
#include "RecHit.hh"

#include <vector>

class SampleModule:
    public Module
{
    protected:
    public:
        SampleModule()
        {
        }
        
        virtual void Process(ObjectStore& objStore)
        {
            std::vector<const SimHit*> simhits = objStore.Get<SimHit>("simhits");
  
        }
        
        ~SampleModule()
        {
        }
};

#endif

