#include "AnalysisChain.hh"

#include "ObjectStore.hh"
#include "Module.hh"

#include "SampleModule.hh"
#include "ConformalMap.hh"
#include "Seeding.hh"
#include "EnergyDeposit.hh"

AnalysisChain::AnalysisChain()
{
    this->AddModule(new SampleModule());
    this->AddModule(new ConformalMap());
    this->AddModule(new Seeding());
    this->AddModule(new EnergyDeposit());
}

void AnalysisChain::AddModule(Module* module)
{
    _modules.push_back(module);
}

void AnalysisChain::Run(ObjectStore& objectStore)
{
    for (unsigned int imodule=0; imodule<_modules.size(); ++imodule)
    {
        _modules[imodule]->Process(objectStore);
    }
}

AnalysisChain::~AnalysisChain()
{
    for (unsigned int imodule=0; imodule<_modules.size(); ++imodule)
    {
        delete _modules[imodule];
    }
    _modules.clear();
}


