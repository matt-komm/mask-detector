#include "RunAction.hh"

#include <stdlib.h>
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4Event.hh"
#include "G4HCtable.hh"
#include "G4VHitsCollection.hh"
#include "G4HCofThisEvent.hh"

#include "G4ios.hh"

RunAction::RunAction()
{
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run* run)
{  
}

void RunAction::EndOfRunAction(const G4Run* run)
{
    //only available if event action does not reject each event
    /*
    const std::vector<const G4Event*>* events= run->GetEventVector();
    for (G4int ievent = 0; ievent < events->size(); ++ievent)
    {
        //
        
    }
    */
}









