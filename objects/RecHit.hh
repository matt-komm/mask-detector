#ifndef RECHIT_H
#define RECHIT_H

#include "G4ThreeVector.hh"
#include "DetId.hh"

class RecHit
{
    protected:
        G4ThreeVector _pos;
        DetId* _detId;
        G4double _time;
        G4ThreeVector _uncertainty;
        G4int _simHitId;
    public:
        RecHit();
        inline const G4ThreeVector GetPosition() const
        {
            return _pos;
        }
        
        inline const DetId* GetDetId() const
        {
            return _detId;
        }
        
        inline G4double GetTime() const
        {
            return _time;
        }
        
        inline const G4ThreeVector GetUncertainty() const
        {
            return _uncertainty;
        }
        
        inline G4int GetSimHitId() const
        {
            return _simHitId;
        }
        
        inline void SetPosition(G4ThreeVector position) 
        {
            _pos = position;
        }
        
        inline void SetDetId(DetId* detId) 
        {
            _detId = detId;
        }
        
        inline void SetTime(G4double time) 
        {
            _time = time;
        }
        
        inline void SetUncertainty(G4ThreeVector uncertainty)
        {
            _uncertainty = uncertainty;
        }
        
        inline void SetSimHitId(G4int simHitId)
        {
            _simHitId = simHitId;
        }
        
        ~RecHit();
};

#endif

