#ifndef SEEDING_H
#define SEEDING_H

#include "Module.hh"
#include "SimHit.hh"
#include "RecHit.hh"

#include "G4ThreeVector.hh"

#include "TColor.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TStyle.h"
#include "THStack.h"

#include "DetId.hh"

#include <iostream>
#include <vector>

class Seeding:
public Module
{
    protected:
        TH1F* histSameTrack;
        TH1F* histOpTrack;
    public:
        Seeding()
        {
            histSameTrack = new TH1F("histSameTrack",";dxy/mm;",20,0,500);
            histOpTrack = new TH1F("histOpTrack",";dxy/mm;",20,0,500);
        }
        
        double Get2DImpactParameter(G4ThreeVector linePropagator, G4ThreeVector pos)
        {
            double a = linePropagator.rho()/mm*cos(linePropagator.phi()/rad);
            double b = linePropagator.rho()/mm*sin(linePropagator.phi()/rad);
            double x = pos.rho()/mm*cos(pos.phi()/rad);
            double y = pos.rho()/mm*sin(pos.phi()/rad);
            double propagation = -0.5*(x*b+y*a)/(a*b);
            if (propagation>0)
            {
                return 499;
            }
            return 0.5*(a*y-b*x)/(a*b)*sqrt(a*a+b*b);
        }
        
        
        virtual void Process(ObjectStore& objStore)
        {
            std::vector<const SimHit*> simhits = objStore.Get<SimHit>("simhits");
            for (unsigned int ihit1 = 0; ihit1 < simhits.size(); ++ihit1)
            {
                if (simhits[ihit1]->GetDetId()->layer()!=0) continue;
                const SimHit* hit1 = simhits[ihit1];
                for (unsigned int ihit2 = 0; ihit2 < simhits.size(); ++ihit2)
                {
                    if (simhits[ihit2]->GetDetId()->layer()!=1) continue;
                    const SimHit* hit2 = simhits[ihit2];
                    G4ThreeVector linePropagator = hit2->GetPosition()-hit1->GetPosition();
                    double dxy = Get2DImpactParameter(linePropagator,hit1->GetPosition());
                    if (hit1->GetTrackID()==hit2->GetTrackID())
                    {
                        
                        histSameTrack->Fill(dxy);
                    }
                    else
                    {
                        
                        histOpTrack->Fill(dxy);
                    }
                    /*
                    for (unsigned int ihit3 = 0; ihit3 < simhits.size(); ++ihit3)
                    {
                        if (simhits[ihit3]->GetDetId()->layer()!=2) continue;
                        const SimHit* hit3 = simhits[ihit3];
                        std::cout<<ihit1<<","<<ihit2<<","<<ihit3<<std::endl;
                    }*/
                }
            }
        }
        
        virtual ~Seeding()
        {
            histOpTrack->Scale(1.0/histOpTrack->Integral());
            histOpTrack->SetFillColor(kGray);
            histSameTrack->Scale(1.0/histSameTrack->Integral());
            histSameTrack->SetFillColor(kGreen);
            gStyle->SetOptStat(0);
            TCanvas cv("cvseeding","",800,600);
            THStack hStack("hs",";dxy/mm;");
            hStack.Add(histOpTrack);
            hStack.Add(histSameTrack);
            hStack.Draw();
            cv.Print("seeding.pdf");
        }
};

#endif
