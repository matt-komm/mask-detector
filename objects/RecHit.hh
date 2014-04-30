#ifndef RECHIT_H
#define RECHIT_H

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "DetId.hh"

class RecHit: public G4VHit
{
    protected:
        G4ThreeVector _posrec;
        DetId* _detrecId;
        G4double _timer;
        G4ThreeVector _uncertainty;
        G4int _simHitId;
    public:
        RecHit();
        ~RecHit();
        RecHit(const RecHit&);

        const RecHit& operator=(const RecHit& recHit)
        {
	  _detrecId = recHit._detrecId;
	  _posrec = recHit._posrec;
	  _timer = recHit._timer;
	  _uncertainty = recHit._uncertainty;
	  _simHitId = recHit._simHitId;
	  return *this;
        }
       
        G4int operator==(const RecHit& recHit) const
        {
	  return ( this == &recHit ) ? 1: 0;
        }  

        inline void* operator new(size_t);
        inline void  operator delete(void*);

        virtual void Draw();
        virtual void Print();

        inline const G4ThreeVector GetPosition() const
        {
            return _posrec;
        }
        
        inline const DetId* GetDetId() const
        {
            return _detrecId;
        }
        
        inline G4double GetTime() const
        {
            return _timer;
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
            _posrec = position;
        }
        
        inline void SetDetId(DetId* detId) 
        {
            _detrecId = detId;
        }
        
        inline void SetTime(G4double time) 
        {
            _timer = time;
        }
        
        inline void SetUncertainty(G4ThreeVector uncertainty)
        {
            _uncertainty = uncertainty;
        }
        
        inline void SetSimHitId(G4int simHitId)
        {
            _simHitId = simHitId;
        }
        
};

typedef G4THitsCollection<RecHit> RecHitCollection;

extern G4Allocator<RecHit> RecHitAllocator;

inline void* RecHit::operator new(size_t)
{
  void *hitrec;
  hitrec = (void *) RecHitAllocator.MallocSingle();
  return hitrec;
}

inline void RecHit::operator delete(void *hitrec)
{
  RecHitAllocator.FreeSingle((RecHit*) hitrec);
}


#endif

