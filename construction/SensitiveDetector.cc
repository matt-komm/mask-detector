#include "SensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "Randomize.hh"

//Include C++ Library
#include <iostream>

SensitiveDetector::SensitiveDetector(DetId* detId):
    G4VSensitiveDetector(detId->GetDetName()),
    _hitsCollection(NULL),
    _hitsRecCollection(NULL),
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
    _hitsRecCollection = new RecHitCollection(SensitiveDetectorName, collectionName[1]);

    // Add this collection in hce
    G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    G4int hcrcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[1]);
    hce->AddHitsCollection( hcID, _hitsCollection ); 
    hce->AddHitsCollection( hcrcID, _hitsRecoCollection );
}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{  
    G4double energyDeposit = aStep->GetTotalEnergyDeposit();
    if (energyDeposit==0.) 
    {
        return false;
    }
    SimHit* newHit = new SimHit();
    RecHit* newrecHit = new RecHit();
    RandEngine aRandEngine;
    G4double width = 0.015*cm;	
    G4double Smear = RandGauss::shoot(&aRandEngine,stepPoint->GetPosition(),width);

    //Set SimHit parameters
    newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
    newHit->SetEnergyDeposit(energyDeposit);
    newHit->SetTrackEnergy(aStep->GetTrack()->GetKineticEnergy ());
    
    G4StepPoint* stepPoint = aStep->GetPreStepPoint();
    newHit->SetLocalTime(stepPoint->GetLocalTime());
    newHit->SetProperTime(stepPoint->GetProperTime());
    newHit->SetGlobalTime(stepPoint->GetGlobalTime());
    newHit->SetDetId(_detId);
    newHit->SetPos(stepPoint->GetPosition());

    _hitsCollection->insert( newHit );

    //newHit->Print();

    //Set RecHit parameters
    newrecHit->SetTime(stepPont->GetGobalTime());
    newrecHit->SetDetId(_detId);
    newrecHit->SetPosition(stepPoint->GetPosition()+Smear);

    _hitsRecoCollection->insert(newrecHit);

    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
    G4int nofHits = _hitsCollection->entries();
    G4cout << "\n-------->SimHits: " << nofHits << G4endl;
}

