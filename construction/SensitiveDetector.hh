
#ifndef SENSITIVEDETECTOR_H
#define SENSITIVEDETECTOR_H

#include "G4VSensitiveDetector.hh"
#include "DetId.hh"

#include "SimHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class SensitiveDetector:
    public G4VSensitiveDetector
{
    private:
        SimHitCollection* _hitsCollection;
        DetId _detId;
    public:
        SensitiveDetector(const G4String& name, const G4String& hitsCollectionName);
        virtual ~SensitiveDetector();
        
        inline void SetDetId(DetId detId)
        {
            _detId=detId;
        }
        
        virtual void   Initialize(G4HCofThisEvent* hitCollection);
        virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
        virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);


};


#endif
