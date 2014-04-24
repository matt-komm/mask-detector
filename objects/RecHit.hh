#ifndef RECHIT_H
#define RECHIT_H

#include "G4ThreeVector.hh"

class RecHit
{
    protected:
        G4ThreeVector _pos;
        DetId* _detId;
        G4double _time;
        G4ThreeVector _uncertainty;
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
        
        inline G4ThreeVector GetUncertainty() const
        {
            return _uncertainty;
        }
        
        
        
        ~RecHit();
};

#endif

