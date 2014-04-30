#include "RecHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4Allocator<RecHit> RecHitAllocator;

RecHit::RecHit():
     G4VHit(),
    _posrec(0,0,0),
    _detrecId(0),
    _timer(-1),
    _uncertainty(0,0,0),
    _simHitId(-1)
{
}

RecHit::~RecHit()
{
}


RecHit::RecHit(const RecHit& recHit)
{
    _detrecId = recHit._detrecId;
    _posrec = recHit._posrec;
}

void RecHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(_posrec);
    circle.SetScreenSize(6.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,1.,1.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);

  }
}

void RecHit::Print()
{
  std::cout
    << " Position: " << std::setw(4) << G4BestUnit(_posrec,"Length_Reco")
    << "localtime: " << std::setw(4) << G4BestUnit(_timer,"Time_Reco")
    << std::endl;


}
