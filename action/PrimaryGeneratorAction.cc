#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
}

void PrimaryGeneratorAction::addParticle(G4int pdgid, G4ThreeVector momentum, G4ThreeVector vertex)
{
    G4ParticleGun* particleGun = new G4ParticleGun(1);
    G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle(pdgid);
    particleGun->SetParticleDefinition(particleDefinition);
    particleGun->SetParticleEnergy(momentum.mag());
    particleGun->SetParticlePosition(vertex);
    particleGun->SetParticleMomentumDirection(momentum);
    _particleGuns.push_back(particleGun);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    for (G4int i = 0; i<_particleGuns.size();++i)
    {
        delete _particleGuns[i];
    }
    _particleGuns.clear();
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    for (G4int i = 0; i<_particleGuns.size();++i)
    {
        _particleGuns[i]->GeneratePrimaryVertex(anEvent);
    }
    
}


