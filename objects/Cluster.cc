#include "Cluster.hh"

Cluster::Cluster(DetId* detId, G4ThreeVector position):
    _detId(detId),
    _position(position)
{
}

void Cluster::AddSimHit(const SimHit* simHit)
{
    _energyDeposit+=simHit->GetEnergyDeposit();
    _simHits.push_back(simHit);
}

Cluster::~Cluster()
{
}


