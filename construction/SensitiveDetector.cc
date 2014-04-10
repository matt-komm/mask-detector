#include "SensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include <iostream>


SensitiveDetector::SensitiveDetector(const G4String& name,const G4String& hitsCollectionName): 
    G4VSensitiveDetector(name),
    _hitsCollection(NULL)
{
    collectionName.insert(hitsCollectionName);
}

SensitiveDetector::~SensitiveDetector() 
{
}

void SensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
    // Create hits collection
    _hitsCollection = new SimHitCollection(SensitiveDetectorName, collectionName[0]); 

    // Add this collection in hce

    G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hce->AddHitsCollection( hcID, _hitsCollection ); 
}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{  
    // check energy deposit
    G4double edep = aStep->GetTotalEnergyDeposit();
    if (edep==0.) 
    {
        return false;
    }
    SimHit* newHit = new SimHit();

    newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
    //newHit->SetDetId(?)
    //aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber());
    newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());

    _hitsCollection->insert( newHit );

    //newHit->Print();

    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
    G4int nofHits = _hitsCollection->entries();
    G4cout << "\n-------->SimHits: " << nofHits << G4endl;
}

