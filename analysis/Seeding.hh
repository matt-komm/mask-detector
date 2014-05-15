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
        TH1F* histSameTrackXY;
        TH1F* histOpTrackXY;
        
        TH1F* histSameTrackZ;
        TH1F* histOpTrackZ;
    public:
        Seeding()
        {
            histSameTrackXY = new TH1F("histSameTrackXY",";dxy/mm;",20,0,500);
            histOpTrackXY = new TH1F("histOpTrackXY",";dxy/mm;",20,0,500);
            
            histSameTrackZ = new TH1F("histSameTrackZ",";dz/mm;",20,0,500);
            histOpTrackZ = new TH1F("histOpTrackZ",";dz/mm;",20,0,500);
        }
        
        double GetImpactParameterXY(G4ThreeVector linePropagator, G4ThreeVector pos)
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
        
        double GetImpactParameterZ(G4ThreeVector linePropagator, G4ThreeVector pos)
        {
            double a = linePropagator.eta();
            double b = linePropagator.z()/mm;
            double x = pos.eta();
            double y = pos.z()/mm;
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
                    double dxy = GetImpactParameterXY(linePropagator,hit1->GetPosition());
                    double dz = GetImpactParameterZ(linePropagator,hit1->GetPosition());
                    if (hit1->GetTrackID()==hit2->GetTrackID())
                    {
                        histSameTrackXY->Fill(dxy);
                        histSameTrackZ->Fill(dz);
                    }
                    else
                    {
                        histOpTrackXY->Fill(dxy);
                        histOpTrackZ->Fill(dz);
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
            histOpTrackXY->Scale(1.0/histOpTrackXY->Integral());
            histOpTrackXY->SetFillColor(kGray);
            histSameTrackXY->Scale(1.0/histSameTrackXY->Integral());
            histSameTrackXY->SetFillColor(kGreen);
            
            histOpTrackZ->Scale(1.0/histOpTrackZ->Integral());
            histOpTrackZ->SetFillColor(kGray);
            histSameTrackZ->Scale(1.0/histSameTrackZ->Integral());
            histSameTrackZ->SetFillColor(kGreen);
            
            gStyle->SetOptStat(0);
            TCanvas cvXY("cvseedingXY","",800,600);
            THStack hStackXY("hsXY",";dxy/mm;");
            hStackXY.Add(histOpTrackXY);
            hStackXY.Add(histSameTrackXY);
            hStackXY.Draw();
            cvXY.Print("seeding_dxy.pdf");
            
            TCanvas cvZ("cvseedingZ","",800,600);
            THStack hStackZ("hsZ",";dz/mm;");
            hStackZ.Add(histOpTrackZ);
            hStackZ.Add(histSameTrackZ);
            hStackZ.Draw();
            cvZ.Print("seeding_dz.pdf");
        }
};

#endif
