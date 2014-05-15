#ifndef ENERGYDEPOSIT_H
#define ENERGYDEPOSIT_H

#include "Module.hh"
#include "SimHit.hh"
#include "RecHit.hh"

#include "G4ThreeVector.hh"

#include "TColor.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TStyle.h"

#include "DetId.hh"

#include <iostream>
#include <vector>

class EnergyDeposit:
public Module
{
    protected:
        TH1D* energy;
    public:
        EnergyDeposit()
        {
            double* binning = new double[101];
            for (int i=0;i<101;++i)
            {
                binning[i]=0.1+pow(10.0,8*i/100.0);
            }
            energy = new TH1D("energy",";energy/eV;",100,binning);
        }
        
        virtual void Process(ObjectStore& objStore)
        {
            std::vector<const SimHit*> simhits = objStore.Get<SimHit>("simhits");
            for (unsigned int ihit = 0; ihit < simhits.size(); ++ihit)
            {
                energy->Fill(simhits[ihit]->GetEnergyDeposit()/eV);
            }
        }
        
        virtual ~EnergyDeposit()
        {
            gStyle->SetOptStat(0);
            TCanvas cv("cvseeding","",800,600);
            gPad->SetLogx(1);
            energy->Draw();
            cv.Print("energyDeposit.pdf");
        }
};

#endif
