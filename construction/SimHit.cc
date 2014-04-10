
#include "SimHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4Allocator<SimHit> SimHitAllocator;

SimHit::SimHit():
    G4VHit(),
    _trackId(-1)
{
    _detId.id=0;
}


SimHit::~SimHit() 
{
}


SimHit::SimHit(const SimHit& simHit)
{
    _trackId = simHit._trackId;
    _detId = simHit._detId;
    _pos = simHit._pos;
}

const SimHit& SimHit::operator=(const SimHit& simHit)
{
    _trackId = simHit._trackId;
    _detId = simHit._detId;
    _pos = simHit._pos;
    return *this;
}

G4int SimHit::operator==(const SimHit& simHit) const
{
  return ( this == &simHit ) ? 1 : 0;
  
}

void SimHit::Draw()
{
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    std::cout<<"vismanager: "<<pVVisManager<<std::endl;
    if(pVVisManager)
    {
        
        G4Circle circle(_pos);
        circle.SetScreenSize(6.);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour colour(1.,1.,1.);
        G4VisAttributes attribs(colour);
        circle.SetVisAttributes(attribs);
        pVVisManager->Draw(circle);
    }
}

void SimHit::Print()
{
  G4cout
     << "  trackID: " << _trackId << " DetId.id " << _detId.id
     << " Position: " << std::setw(7) << G4BestUnit(_pos,"Length")
     << G4endl;
}

