#include "SensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include <iostream>


SensitiveDetector::SensitiveDetector(DetId* detId):
    G4VSensitiveDetector(detId->GetDetName()),
    _hitsCollection(NULL),
    _detId(detId)
{
    collectionName.insert(detId->GetHitCollectionName());
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
    G4double energyDeposit = aStep->GetTotalEnergyDeposit();
    if (energyDeposit==0) 
    {
        return false;
    }
    SimHit* newHit = new SimHit();

    newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
    newHit->SetEnergyDeposit(energyDeposit);
    newHit->SetTrackEnergy(aStep->GetTrack()->GetKineticEnergy ());
    
    G4StepPoint* stepPoint = aStep->GetPreStepPoint();
    newHit->SetLocalTime(stepPoint->GetLocalTime());
    newHit->SetProperTime(stepPoint->GetProperTime());
    newHit->SetGlobalTime(stepPoint->GetGlobalTime());
    newHit->SetDetId(_detId);
    newHit->SetPosition(stepPoint->GetPosition());

    _hitsCollection->insert( newHit );

    //newHit->Print();

    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
    G4int nofHits = _hitsCollection->entries();
    G4cout << "\n-------->SimHits: " << nofHits << G4endl;
}

