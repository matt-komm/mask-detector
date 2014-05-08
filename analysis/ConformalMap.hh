#ifndef CONFORMALMAP_H
#define CONFORMALMAP_H

#include "Module.hh"
#include "SimHit.hh"
#include "RecHit.hh"

#include "G4ThreeVector.hh"

#include "TCanvas.h"
#include "TH2F.h"
#include "TStyle.h"

#include <vector>

class ConformalMap:
public Module
{
    protected:
        TH2F* _histUV;
    public:
        ConformalMap()
        {
            _histUV=new TH2F("histuv","simhits;v;u",100,-0.005,0.005,100,-0.005,0.005);
        }
        
        double mapV(double x, double y)
        {
            return x/(x*x+y*y);
        }
        
        double mapU(double x, double y)
        {
            return y/(x*x+y*y);
        }
        
        virtual void Process(ObjectStore& objStore)
        {
            std::vector<const SimHit*> simhits = objStore.Get<SimHit>("simhits");
            for (unsigned int ihit =0; ihit<simhits.size();++ihit)
            {
                const SimHit* hit = simhits[ihit];
                const G4ThreeVector pos = hit->GetPosition();
                _histUV->Fill(mapV(pos.x(),pos.y()),mapU(pos.x(),pos.y()));
            }
        }
        
        virtual ~ConformalMap()
        {
            gStyle->SetOptStat(0);
            
            TCanvas cvUV("cvUV","",1200,900);
            cvUV.cd();
            _histUV->SetMarkerStyle(20);
            _histUV->SetMarkerSize(0.8);
            _histUV->Draw();
            cvUV.Print("simhits_UV.pdf");
            
        }
};

#endif
