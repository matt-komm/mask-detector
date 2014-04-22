#ifndef SIMHIT_H
#define SIMHIT_H

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "DetId.hh"



class SimHit: 
    public G4VHit
{
    private:
        G4int _trackId;
        G4double _energyDeposit;
        G4double _trackEnergy;
        DetId _detId;
        G4ThreeVector _pos;
        G4double _localTime;
        G4double _properTime;
        G4double _globalTime;

    public:
        SimHit();
        SimHit(const SimHit&);
        virtual ~SimHit();

        const SimHit& operator=(const SimHit&);
        G4int operator==(const SimHit&) const;

        inline void* operator new(size_t);
        inline void  operator delete(void*);

        virtual void Draw();
        virtual void Print();
        
        inline G4int GetTrackID() const
        { 
            return _trackId; 
        }
        
        inline G4double GetEnergyDeposit() const
        {
            return _energyDeposit;
        }
        
        inline G4double GetTrackEnergy() const
        {
            return _trackEnergy;
        }
        
        inline const DetId& GetDetId() const
        { 
            return _detId; 
        }
        
        inline G4double GetLocalTime() const
        { 
            return _localTime; 
        }
        
        inline G4double GetProperTime() const
        { 
            return _properTime; 
        }
        
        inline G4double GetGlobalTime() const
        { 
            return _globalTime; 
        }
        
        inline const G4ThreeVector& GetPosition() const 
        { 
            return _pos; 
        }
        
        inline void SetLocalTime(G4double localTime)
        {
            _localTime=localTime;
        }
        
        inline void SetProperTime(G4double properTime)
        {
            _properTime=properTime;
        }
        
        inline void SetGlobalTime(G4double globalTime)
        {
            _globalTime=globalTime;
        }

        inline void SetTrackID(G4int trackId)
        {
            _trackId = trackId; 
        }
        
        inline void SetEnergyDeposit(G4double energyDeposit)
        {
            _energyDeposit=energyDeposit;
        }
        
        inline void SetTrackEnergy(G4double trackEnergy)
        {
            _trackEnergy=trackEnergy;
        }
        
        inline void SetDetId(DetId detId)
        { 
            _detId = detId; 
        }
        
        inline void SetPos(G4ThreeVector pos)
        { 
            _pos = pos; 
        }
};

typedef G4THitsCollection<SimHit> SimHitCollection;

extern G4Allocator<SimHit> SimHitAllocator;


inline void* SimHit::operator new(size_t)
{
    void *hit;
    hit = (void *) SimHitAllocator.MallocSingle();
    return hit;
}


inline void SimHit::operator delete(void *hit)
{
    SimHitAllocator.FreeSingle((SimHit*) hit);
}


#endif
