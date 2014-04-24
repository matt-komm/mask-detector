#ifndef ANALYSISCHAIN_H
#define ANALYSISCHAIN_H

#include <vector>

class Module;
class ObjectStore;

class AnalysisChain
{
    protected:
        std::vector<Module*> _modules;
    public:
        AnalysisChain();
        void AddModule(Module* module);
        void Run(ObjectStore& objectStore);
        ~AnalysisChain();
};

#endif

