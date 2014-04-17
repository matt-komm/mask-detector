#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ThreeVector.hh"

#include <vector>

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);
    
    void addParticle(G4int pdgid, G4ThreeVector momentum, G4ThreeVector vertex=G4ThreeVector(0.0,0.0,0.0));

  private:
    std::vector<G4ParticleGun*> _particleGuns;
};

#endif


