#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "TROOT.h"
#include "TObject.h"
#include "TChain.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TString.h"
#include "TKey.h"
#include "TF1.h"
#include "TMath.h"

#include <TRandom.h>
#include <Math/Vector4D.h>


int Simulation()
{
    TH1D *PtDist = new TH1D("Pt", "Pt; Pt (GeV); Events", 500, 0, 2.5);
    PtDist->Sumw2();
    
    TH1D *EtaDist = new TH1D("Eta", "Eta; Eta; Events", 500, -1, 1);
    EtaDist->Sumw2();
    
    TH1D *PhiDist = new TH1D("Phi", "Phi; Phi; Events", 500, 0, 6.28);
    PhiDist->Sumw2();
    
    TH1F *InvariantMassesLambda = new TH1F("InvariantMassesLambda", "p - Pi- Inavariant Masses; InvariantMasses; Count", 40, 1.08, 1.16);
    InvariantMassesLambda->Sumw2();
    
    TH2D *LambdaAcceptance = new TH2D("PtVsYLambda", "Pt vs Y for Lambda-0; y_{CM}; Pt (Gev)", 200, -1, 1, 200, 0, 2.5);
    LambdaAcceptance->Sumw2();
    
    
    Double_t Pt;
    Double_t Eta;
    Double_t Phi;
    
    
    const Double_t Energy = 3.0;
    const Double_t Pi = 3.1415926535;
    
    const Double_t ProtonMass = 0.938;
    const Double_t PionMass = 0.13957;
    
    std::vector<double> ProtonPtVec;
    std::vector<double> ProtonEtaVec;
    std::vector<double> ProtonPhiVec;
    std::vector<double> ProtonMassVec;
    std::vector<double> PionMinusPtVec;
    std::vector<double> PionMinusEtaVec;
    std::vector<double> PionMinusPhiVec;
    std::vector<double> PionMinusMassVec;

    TRandom *Rand = new TRandom();
    
    
    for(Long64_t EventNumber = 0; EventNumber < 50000; EventNumber++)
    {
        if(EventNumber % 5000 == 0)
        {
            std::cout << "On Event # " << EventNumber << std::endl;
        }

        for(Long64_t TrackNumber = 0; TrackNumber < 50; TrackNumber++)
        {
            Pt = Rand->Exp(Energy);

            if((Pt < 0.18) || (Pt > 2.0))
            {
                continue;
            }

            Eta = Rand->Uniform(0, 1);

            Phi = Rand->Uniform(0, 2 * Pi);

            PtDist->Fill(Pt);
            EtaDist->Fill(Eta);
            PhiDist->Fill(Phi);

            ProtonPtVec.push_back(Pt);
            ProtonEtaVec.push_back(Eta);
            ProtonPhiVec.push_back(Phi);
            ProtonMassVec.push_back(ProtonMass);

            PionMinusPtVec.push_back(Pt);
            PionMinusEtaVec.push_back(Eta);
            PionMinusPhiVec.push_back(Phi);
            PionMinusMassVec.push_back(PionMass);
        }
    

        Double_t Im;


        for(size_t i = 0; i < ProtonPtVec.size(); i++)
        {
            for(size_t j = 0; j < PionMinusPtVec.size(); j++)
            {
                    ROOT::Math::PtEtaPhiMVector ProtonFourVector(ProtonPtVec[i], ProtonEtaVec[i], ProtonPhiVec[i], ProtonMassVec[i]);
        
                    ROOT::Math::PtEtaPhiMVector PionMinusFourVector(PionMinusPtVec[j], PionMinusEtaVec[j], PionMinusPhiVec[j], PionMinusMassVec[j]);
    
                    Im = (ProtonFourVector + PionMinusFourVector).M();

                    InvariantMassesLambda->Fill(Im);
            }
        }
    
        ProtonPtVec.clear();
        ProtonEtaVec.clear();
        ProtonPhiVec.clear();
        ProtonMassVec.clear();
    
        PionMinusPtVec.clear();
        PionMinusEtaVec.clear();
        PionMinusPhiVec.clear();
        PionMinusMassVec.clear();  
    }
    
    PtDist->SetDirectory(0);
    EtaDist->SetDirectory(0);
    PhiDist->SetDirectory(0);
    InvariantMassesLambda->SetDirectory(0);
    
    std::string SimulationFileString = "/star/u/mcgordon/VnFromEPD/Simulations/SimulationResults.root";
    const char *SimulationFileChar = &SimulationFileString[0];
    
    TFile *SimulationRootFile = TFile::Open(SimulationFileChar, "RECREATE");
    SimulationRootFile->cd();
    
    
    PtDist->Write();
    EtaDist->Write();
    PhiDist->Write();
    InvariantMassesLambda->Write();
    
    
    SimulationRootFile->Close();
    

    delete Rand;
    delete PtDist;
    delete EtaDist;
    delete PhiDist;
    delete InvariantMassesLambda;
    delete LambdaAcceptance;
    
    
    std::cout << "Done!" << std::endl;

    return 0;
}
