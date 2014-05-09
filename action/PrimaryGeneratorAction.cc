#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction():
    _random(new CLHEP::MTwistEngine(123))
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

void PrimaryGeneratorAction::clear()
{
    for (G4int i = 0; i<_particleGuns.size();++i)
    {
        delete _particleGuns[i];
    }
    _particleGuns.clear();
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    clear();
    G4int ids[8] = {2122,-2122,211,-211,11,-11,13,-13};

    std::cout<<"new event"<<std::endl;
    for (int i = 0; i<10; ++i)
    {
        G4double energy = _random.fire(100.0,800.0);
        std::cout<<i<<","<<energy<<std::endl;
        G4double eta = _random.fire(-2.0,2.0);
        G4double phi = _random.fire(0.0,3.14156*2);
        G4int idindex = G4int(_random.fire(0,7.9));
        G4ThreeVector momentum(0.0,0.0,0.0);
        momentum.setREtaPhi(energy*GeV,eta,phi*rad);
        addParticle(ids[idindex],momentum);
    }
    for (G4int i = 0; i<_particleGuns.size();++i)
    {
        _particleGuns[i]->GeneratePrimaryVertex(anEvent);
    }
    
}


