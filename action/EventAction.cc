#include "EventAction.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4HCtable.hh"
#include "G4VHitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "SimHit.hh"
#include <iostream>

EventAction::EventAction():
    G4UserEventAction()
{
    //
}

EventAction::~EventAction()
{
}

void EventAction::EndOfEventAction(const G4Event* event)
{
    //G4UserEventAction::fpEventManager->KeepTheCurrentEvent();
    
    G4HCofThisEvent* hitcollections = event->GetHCofThisEvent();
    for (G4int icollection = 0; icollection<hitcollections->GetNumberOfCollections(); ++icollection)
    {
        
        std::cout<<"  ->  hit collection: "<<icollection<<std::endl;
        G4VHitsCollection* hitCollection = hitcollections->GetHC(icollection);
        std::cout<<"  ->    ->  name: "<<hitCollection->GetName()<<std::endl;
        std::cout<<"  ->    ->  sdname: "<<hitCollection->GetSDname()<<std::endl;
        std::cout<<"  ->    ->  hits: "<<hitCollection->GetSize()<<std::endl;
        
        for (unsigned int ihit = 0; ihit<hitCollection->GetSize();++ihit)
        {
            SimHit* hit = dynamic_cast<SimHit*>(hitCollection->GetHit(ihit));
            if (!hit)
            {
                throw "casting simhit collection failed";
            }
            std::cout<<"  ->    ->   ->  ";
            hit->Print();
        }
        
    } 
}


