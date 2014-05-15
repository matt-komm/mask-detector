#ifndef CLUSTER_H
#define CLUSTER_H

#include "SimHit.hh"
#include "DetId.hh"
#include "G4ThreeVector.hh"
#include <vector>


class Cluster
{
    protected:
        std::vector<const SimHit*> _simHits;
        DetId* _detId;
        G4ThreeVector _position;
        G4double _energyDeposit;
    public:
        Cluster(DetId* detId, G4ThreeVector position);
        void AddSimHit(const SimHit* simHit);
        inline G4double GetEnergyDeposit()
        {
            return _energyDeposit;
        }
        
        ~Cluster();
};


class ClusterFactory
{
    protected:
        std::vector<const SimHit*> _simHits;
        DetId* _detId;
        G4double _length;
        G4double _width;
    public:
        ClusterFactory(DetId* detId, G4double length, G4double width):
            _detId(detId),
            _length(length),
            _width(width)
        {
        }
        
        void AddSimHits(const SimHit* simHit)
        {
            _simHits.push_back(simHit);
        }
        
        std::vector<const Cluster*> GenerateClustering()
        {
            std::vector<const Cluster*> clusters;
            return clusters;
        }
};

#endif

