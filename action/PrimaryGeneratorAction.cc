#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    G4int n_particle = 1;
    particleGun = new G4ParticleGun(n_particle);

    G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle(211);
    G4String particleName;
    std::cout<<"particle: "<<particleDefinition<<std::endl;
    particleGun->SetParticleDefinition(particleDefinition);
    particleGun->SetParticleEnergy(150.0*GeV);
    particleGun->SetParticlePosition(G4ThreeVector(0.0, 0.0, 0.0));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    
    G4ThreeVector v(40.00*GeV,60.00*GeV,20.0*GeV);
    particleGun->SetParticleMomentumDirection(v);
    particleGun->GeneratePrimaryVertex(anEvent);
    
}


