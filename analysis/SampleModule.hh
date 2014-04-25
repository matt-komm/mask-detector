#ifndef SAMPLEMODULE_H
#define SAMPLEMODULE_H

#include "Module.hh"
#include "SimHit.hh"
#include "RecHit.hh"

#include "G4ThreeVector.hh"

#include "TCanvas.h"
#include "TH2F.h"
#include "TStyle.h"

#include <vector>

class SampleModule:
    public Module
{
    protected:
        TH2F* _histEtaPhi;
        TH2F* _histRPhi;
        TH2F* _histEtaZ;
    public:
        SampleModule()
        {
            _histEtaPhi=new TH2F("hist","simhits;#eta;#phi",100,-2.5,2.5,100,-3.1415,3.1415);
            _histRPhi=new TH2F("hist","simhits;x;y",100,-1.5,1.5,100,-1.5,1.5);
            _histEtaZ=new TH2F("hist","simhits;z;r",100,-1.5,1.5,100,0,1.5);
        }
        
        virtual void Process(ObjectStore& objStore)
        {
            std::vector<const SimHit*> simhits = objStore.Get<SimHit>("simhits");
            for (unsigned int ihit =0; ihit<simhits.size();++ihit)
            {
                const SimHit* hit = simhits[ihit];
                const G4ThreeVector pos = hit->GetPosition();
                _histEtaPhi->Fill(pos.eta(),pos.phi());
                _histRPhi->Fill(pos.rho()/m*cos(pos.phi()/rad),pos.rho()/m*sin(pos.phi()/rad));
                _histEtaZ->Fill(pos.z()/m,pos.rho()/m);
            }
        }
        
        virtual ~SampleModule()
        {
            gStyle->SetOptStat(0);
            
            TCanvas cvEtaPhi("cvEtaPhi","",1200,900);
            cvEtaPhi.cd();
            _histEtaPhi->SetMarkerStyle(20);
            _histEtaPhi->SetMarkerSize(0.8);
            _histEtaPhi->Draw();
            cvEtaPhi.Print("simhits_EtaPhi.pdf");
            
            TCanvas cvRPhi("cvRPhi","",1200,900);
            cvRPhi.cd();
            _histRPhi->SetMarkerStyle(20);
            _histRPhi->SetMarkerSize(0.8);
            _histRPhi->Draw();
            cvRPhi.Print("simhits_RPhi.pdf");
            
            TCanvas cvEtaZ("cvEtaZ","",1200,900);
            cvEtaZ.cd();
            _histEtaZ->SetMarkerStyle(20);
            _histEtaZ->SetMarkerSize(0.8);
            _histEtaZ->Draw();
            cvEtaZ.Print("simhits_EtaZ.pdf");
        }
};

#endif

