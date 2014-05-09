#include "EventAction.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4HCtable.hh"
#include "G4VHitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "SimHit.hh"
#include "RecHit.hh"

#include "ObjectStore.hh"

#include <iostream>

EventAction::EventAction():
    G4UserEventAction()
{

}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event *anEvent)
{

}
void EventAction::EndOfEventAction(const G4Event* event)
{
    //G4UserEventAction::fpEventManager->KeepTheCurrentEvent();
    //std::cout<<"end of event"<<std::endl;
    //std::cout<<"----------------"<<std::endl;
    G4HCofThisEvent* hitcollections = event->GetHCofThisEvent();
    //std::cout<<"hit collections: "<<hitcollections->GetNumberOfCollections()<<std::endl;
    
    std::vector<const SimHit*> simhits;
    
    for (G4int icollection = 0; icollection<hitcollections->GetNumberOfCollections(); ++icollection)
    {
        
        //std::cout<<"  ->  hit collection: "<<icollection<<std::endl;
        G4VHitsCollection* hitCollection = hitcollections->GetHC(icollection);
        //std::cout<<"  ->    ->  name: "<<hitCollection->GetName()<<std::endl;
        //std::cout<<"  ->    ->  sdname: "<<hitCollection->GetSDname()<<std::endl;
        //std::cout<<"  ->    ->  hits: "<<hitCollection->GetSize()<<std::endl;
        
        for (unsigned int ihit = 0; ihit<hitCollection->GetSize();++ihit)
        {
            SimHit* hit = dynamic_cast<SimHit*>(hitCollection->GetHit(ihit));
            if (hit)
            {
                simhits.push_back(hit);
                //std::cout<<"  ->    ->   ->  ";
                //hit->Print();
            }
        }
    }
    try
    {
        
        ObjectStore objStore;
        objStore.Put<SimHit>("simhits",simhits);
        _chain.Run(objStore);
    }
    catch (std::string s)
    {
        std::cout<<s<<std::endl;
        
    }
}


