//Author: Michael Gordon
//Date: 1-7-25


#include <iostream>
#include <string>
#include <vector>

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

#include "TreeAnalyzer.h"
#include "FlowFunctions.h"
#include "DeuteronsAndTritons.h"
#include "TileVector.h"

#include "StBichsel/Bichsel.h"

#include "StPicoDstMaker/StPicoDstMaker.h"
#include "StPicoEvent/StPicoEvent.h"
#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoTrack.h"
#include "StPicoEvent/StPicoETofHit.h"
#include "StPicoEvent/StPicoBTofPidTraits.h"
#include "StPicoEvent/StPicoETofPidTraits.h"
#include "StPicoEvent/StPicoEpdHit.h"
#include "StEpdUtil/StEpdGeom.h"
#include "StEpdUtil/StEpdEpFinder.h"

#include "KFParticle.h"

#include <Math/Vector4D.h>

ClassImp(TreeAnalyzer)

    
TreeAnalyzer::TreeAnalyzer(StPicoDstMaker *picoMaker, Char_t *JobID, Char_t *Systematic):StMaker()
{
    mPicoDstMaker = picoMaker;
    mPicoDst = 0;
    
    ID = std::string(JobID);
    
    Variation = std::string(Systematic);
}



// Bichsel function
Double_t BichselZ(Double_t *p, Double_t *parameters) 
{
    Double_t POverM = p[0] / parameters[0];

    return TMath::Exp(Bichsel::Instance()->GetMostProbableZ(TMath::Log10(POverM),parameters[1]));
}



void TreeAnalyzer::Clear(Option_t *opt)
{
    StMaker::Clear();
}



Int_t TreeAnalyzer::Finish()
{
    //Outputting the Histograms
    if(RunIteration == 1)
    {EventCheck->SetDirectory(0);
        for(int i = 0; i < 16; i++)
        {
            HistoInnerEPDQxRaw[i]->SetDirectory(0);
            HistoInnerEPDQyRaw[i]->SetDirectory(0);
            HistoOuterEPDQxRaw[i]->SetDirectory(0);
            HistoOuterEPDQyRaw[i]->SetDirectory(0);
            HistoOuterTPCQxRaw[i]->SetDirectory(0);
            HistoOuterTPCQyRaw[i]->SetDirectory(0);
        }
        for(int i = 0; i < 16; i++)
        {
            HistoInnerEPDQxRawByRun[i]->SetDirectory(0);
            HistoInnerEPDQyRawByRun[i]->SetDirectory(0);
            HistoOuterEPDQxRawByRun[i]->SetDirectory(0);
            HistoOuterEPDQyRawByRun[i]->SetDirectory(0);
            HistoOuterTPCQxRawByRun[i]->SetDirectory(0);
            HistoOuterTPCQyRawByRun[i]->SetDirectory(0);
        }
        ZVertexValues->SetDirectory(0);
        RVertexValues->SetDirectory(0);
        DCAValues->SetDirectory(0);
        NHitsValues->SetDirectory(0);
        NHitsdEdxValues->SetDirectory(0);
        NHitsFitOverNHitsPossValues->SetDirectory(0);
        RunCount->SetDirectory(0);
        pVx->SetDirectory(0);
        pVy->SetDirectory(0);
        pVz->SetDirectory(0);
        pPt->SetDirectory(0);
        pEta->SetDirectory(0);
        HitCountOuterEPD->SetDirectory(0);
        Centralities->SetDirectory(0);
        CentralitiesNineToFifteenOuterEPDHitsOnly->SetDirectory(0);
        h2_zd_vs_mom->SetDirectory(0);
        h2_zt_vs_mom->SetDirectory(0);
        MomentumDistributionBischel->SetDirectory(0);
        ZDeuteronDistribution->SetDirectory(0);
        ZTritonDistribution->SetDirectory(0);
        HistoDA->SetDirectory(0);
        HistoDB->SetDirectory(0);
        HistoD0->SetDirectory(0);
        HistoD1->SetDirectory(0);
        HistoD2->SetDirectory(0);
        HistoD3->SetDirectory(0);
        HistoD4->SetDirectory(0);
        HistoD4A->SetDirectory(0);
        HistoD5->SetDirectory(0);
        HistoD6->SetDirectory(0);
        HistoD7->SetDirectory(0);
        HistoD8->SetDirectory(0);
        HistoD9->SetDirectory(0);
        HistoD10->SetDirectory(0);
        HistoD11->SetDirectory(0);
        HistoD12->SetDirectory(0);
        HistoD13->SetDirectory(0);
        HistoD14->SetDirectory(0);
        HistoD15->SetDirectory(0);
        HistoD16->SetDirectory(0);
        HistoD17->SetDirectory(0);
        HistoD18->SetDirectory(0);
        HistoD19->SetDirectory(0);
        HistoD20->SetDirectory(0);
        HistoD21->SetDirectory(0);
        HistoD22->SetDirectory(0);
        HistoD23->SetDirectory(0);
        HistoD24->SetDirectory(0);
        HistoD25->SetDirectory(0);
        HistoD26->SetDirectory(0);
        HistoD27->SetDirectory(0);
        HistoD27A->SetDirectory(0);
        HistoD27B->SetDirectory(0);
        HistoD28->SetDirectory(0);
        HistoD29->SetDirectory(0);
        HistoD30->SetDirectory(0);
        HistoD31->SetDirectory(0);
        HistoD32->SetDirectory(0);
        HistoD32A->SetDirectory(0);
        HistoD32B->SetDirectory(0);
        for(int i = 0; i < 16; i++)
        {
            HistoD33[i]->SetDirectory(0);
            HistoD36[i]->SetDirectory(0);
            HistoD39[i]->SetDirectory(0);
        }
        InvariantMassesLambda->SetDirectory(0);
        InvariantMassesKShort->SetDirectory(0);
        LambdaAcceptance->SetDirectory(0);
        KShortAcceptance->SetDirectory(0);
        ProtonMultiplicity->SetDirectory(0);
        PionPlusMultiplicity->SetDirectory(0);
        PionMinusMultiplicity->SetDirectory(0);
        EToFFlags->SetDirectory(0);
        // ProtonTPCDetected->SetDirectory(0);
        // ProtonTPCDetectedRapidity->SetDirectory(0);        
        // KaonPlusTPCDetected->SetDirectory(0);
        // KaonPlusTPCDetectedRapidity->SetDirectory(0);
        // KaonMinusTPCDetected->SetDirectory(0);
        // KaonMinusTPCDetectedRapidity->SetDirectory(0);
        // PionPlusTPCDetected->SetDirectory(0);
        // PionPlusTPCDetectedRapidity->SetDirectory(0);
        // PionMinusTPCDetected->SetDirectory(0);
        // PionMinusTPCDetectedRapidity->SetDirectory(0);
        // DeuteronTPCDetected->SetDirectory(0);
        // TritonTPCDetected->SetDirectory(0);
        // ProtonToFDetected->SetDirectory(0);
        // ProtonToFDetectedRapidity->SetDirectory(0);
        // ProtonToFDetectedRapidityMSquaredCuts->SetDirectory(0);
        // ProtonEToFDetected->SetDirectory(0);
        // ProtonEToFDetectedRapidity->SetDirectory(0);
        // KaonPlusToFDetected->SetDirectory(0);
        // KaonPlusToFDetectedRapidity->SetDirectory(0);
        // KaonPlusToFDetectedRapidityMSquaredCuts->SetDirectory(0);
        // KaonPlusEToFDetected->SetDirectory(0);
        // KaonPlusEToFDetectedRapidity->SetDirectory(0);
        // KaonMinusToFDetected->SetDirectory(0);
        // KaonMinusToFDetectedRapidity->SetDirectory(0);
        // KaonMinusToFDetectedRapidityMSquaredCuts->SetDirectory(0);
        // KaonMinusEToFDetected->SetDirectory(0);
        // KaonMinusEToFDetectedRapidity->SetDirectory(0);
        // PionPlusToFDetected->SetDirectory(0);
        // PionPlusToFDetectedRapidity->SetDirectory(0);
        // PionPlusToFDetectedRapidityMSquaredCuts->SetDirectory(0);
        // PionPlusEToFDetected->SetDirectory(0);
        // PionPlusEToFDetectedRapidity->SetDirectory(0);
        // PionMinusToFDetected->SetDirectory(0);
        // PionMinusToFDetectedRapidity->SetDirectory(0);
        // PionMinusToFDetectedRapidityMSquaredCuts->SetDirectory(0);
        // PionMinusEToFDetected->SetDirectory(0);
        // PionMinusEToFDetectedRapidity->SetDirectory(0);
        // DeuteronToFDetected->SetDirectory(0);
        // DeuteronEToFDetected->SetDirectory(0);
        // TritonToFDetected->SetDirectory(0);
        // TritonEToFDetected->SetDirectory(0);
        GlobalPt->SetDirectory(0);
        GlobalEta->SetDirectory(0);
        GlobalPhi->SetDirectory(0);
        GlobalPtProton->SetDirectory(0);
        GlobalEtaProton->SetDirectory(0);
        GlobalPtPionPlus->SetDirectory(0);
        GlobalEtaPionPlus->SetDirectory(0);
        GlobalPtPionMinus->SetDirectory(0);
        GlobalEtaPionMinus->SetDirectory(0);
        GlobaldEdxVsP->SetDirectory(0);
        AllTracksToFDetected->SetDirectory(0);
        MSquaredBToF->SetDirectory(0);
        MSquaredEToF->SetDirectory(0);
        KaonPlusPtOutliersEta->SetDirectory(0);
        KaonPlusPtOutliersMSquared->SetDirectory(0);
        PionPlusPtOutliersEta->SetDirectory(0);
        PionPlusPtOutliersMSquared->SetDirectory(0);
     

     
        // std::string ToFEfficiencyFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/ToFEfficiency" + ID +".root";
        // const char *ToFEfficiencyFileChar = &ToFEfficiencyFileString[0];

        // TFile *ToFEfficiencyRootFile = TFile::Open(ToFEfficiencyFileChar, "RECREATE");
        // ToFEfficiencyRootFile->cd();


        // ProtonTPCDetected->Write();
        // ProtonTPCDetectedRapidity->Write();
        // KaonPlusTPCDetected->Write();
        // KaonPlusTPCDetectedRapidity->Write();
        // KaonMinusTPCDetected->Write();
        // KaonMinusTPCDetectedRapidity->Write();
        // PionPlusTPCDetected->Write();
        // PionPlusTPCDetectedRapidity->Write();
        // PionMinusTPCDetected->Write();
        // PionMinusTPCDetectedRapidity->Write();
        // DeuteronTPCDetected->Write();
        // TritonTPCDetected->Write();
        // ProtonToFDetected->Write();
        // ProtonToFDetectedRapidity->Write();
        // ProtonToFDetectedRapidityMSquaredCuts->Write();
        // ProtonEToFDetected->Write();
        // ProtonEToFDetectedRapidity->Write();
        // KaonPlusToFDetected->Write();
        // KaonPlusToFDetectedRapidity->Write();
        // KaonPlusToFDetectedRapidityMSquaredCuts->Write();
        // KaonPlusEToFDetected->Write();
        // KaonPlusEToFDetectedRapidity->Write();
        // KaonMinusToFDetected->Write();
        // KaonMinusToFDetectedRapidity->Write();
        // KaonMinusToFDetectedRapidityMSquaredCuts->Write();
        // KaonMinusEToFDetected->Write();
        // KaonMinusEToFDetectedRapidity->Write();
        // PionPlusToFDetected->Write();
        // PionPlusToFDetectedRapidity->Write();
        // PionPlusToFDetectedRapidityMSquaredCuts->Write();
        // PionPlusEToFDetected->Write();
        // PionPlusEToFDetectedRapidity->Write();
        // PionMinusToFDetected->Write();
        // PionMinusToFDetectedRapidity->Write();
        // PionMinusToFDetectedRapidityMSquaredCuts->Write();
        // PionMinusEToFDetected->Write();
        // PionMinusEToFDetectedRapidity->Write();
        // DeuteronToFDetected->Write();
        // DeuteronEToFDetected->Write();
        // TritonToFDetected->Write();
        // TritonEToFDetected->Write();

        // ToFEfficiencyRootFile->Close();
     

        

        std::string QVectorHistogramFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/QVectorFirstPass" + Variation + ID +".root";
        const char *QVectorHistogramFileChar = &QVectorHistogramFileString[0];

        TFile *QVectorHistogramRootFile = TFile::Open(QVectorHistogramFileChar, "RECREATE");
        QVectorHistogramRootFile->cd();

        for(int i = 0; i < 16; i++)
        {
            HistoInnerEPDQxRaw[i]->Write();
            HistoInnerEPDQyRaw[i]->Write();
            HistoOuterEPDQxRaw[i]->Write();
            HistoOuterEPDQyRaw[i]->Write();
            HistoOuterTPCQxRaw[i]->Write();
            HistoOuterTPCQyRaw[i]->Write();
        }

        for(int i = 0; i < 16; i++)
        {
            HistoInnerEPDQxRawByRun[i]->Write();
            HistoInnerEPDQyRawByRun[i]->Write();
            HistoOuterEPDQxRawByRun[i]->Write();
            HistoOuterEPDQyRawByRun[i]->Write();
            HistoOuterTPCQxRawByRun[i]->Write();
            HistoOuterTPCQyRawByRun[i]->Write();
        }

        QVectorHistogramRootFile->Close();
        
        


        std::string HistogramRootFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramFirstPass" + Variation + ID + ".root";
        const char *HistogramRootFileChar = &HistogramRootFileString[0];

        TFile *HistogramRootFile =TFile::Open(HistogramRootFileChar, "RECREATE");
        HistogramRootFile->cd();
EventCheck->Write();
        ZVertexValues->Write();
        RVertexValues->Write();
        DCAValues->Write();
        NHitsValues->Write();
        NHitsdEdxValues->Write();
        NHitsFitOverNHitsPossValues->Write();
        RunCount->Write();
        pVx->Write();
        pVy->Write();
        pVz->Write();
        pPt->Write();
        pEta->Write();
        HitCountOuterEPD->Write();
        Centralities->Write();
        CentralitiesNineToFifteenOuterEPDHitsOnly->Write();
        h2_zd_vs_mom->Write();
        h2_zt_vs_mom->Write();
        MomentumDistributionBischel->Write();
        ZDeuteronDistribution->Write();
        ZTritonDistribution->Write();
        HistoDA->Write();
        HistoDB->Write();
        HistoD0->Write();
        HistoD1->Write();
        HistoD2->Write();
        HistoD3->Write();
        AllTracksToFDetected->Write();
        HistoD4->Write();
        HistoD4A->Write();
        HistoD5->Write();
        HistoD6->Write();
        HistoD7->Write();
        HistoD8->Write();
        HistoD9->Write();
        HistoD10->Write();
        HistoD11->Write();
        HistoD12->Write();
        HistoD13->Write();
        HistoD14->Write();
        HistoD15->Write();
        HistoD16->Write();
        HistoD17->Write();
        HistoD18->Write();
        HistoD19->Write();
        HistoD20->Write();
        HistoD21->Write();
        HistoD22->Write();
        HistoD23->Write();
        HistoD24->Write();
        HistoD25->Write();
        HistoD26->Write();
        HistoD27->Write();
        HistoD27A->Write();
        HistoD27B->Write();
        HistoD28->Write();
        HistoD29->Write();
        HistoD30->Write();
        HistoD31->Write();
        HistoD32->Write();
        HistoD32A->Write();
        HistoD32B->Write();
        for(int i = 0; i < 16; i++)
        {
            HistoD33[i]->Write();
            HistoD36[i]->Write();
            HistoD39[i]->Write();
        }
        InvariantMassesLambda->Write();
        InvariantMassesKShort->Write();
        LambdaAcceptance->Write();
        KShortAcceptance->Write();
        ProtonMultiplicity->Write();
        PionPlusMultiplicity->Write();
        PionMinusMultiplicity->Write();
        GlobalPt->Write();
        GlobalEta->Write();
        GlobalPhi->Write();
        GlobalPtProton->Write();
        GlobalEtaProton->Write();
        GlobalPtPionPlus->Write();
        GlobalEtaPionPlus->Write();
        GlobalPtPionMinus->Write();
        GlobalEtaPionMinus->Write();
        GlobaldEdxVsP->Write();
        EToFFlags->Write();
        MSquaredBToF->Write();
        MSquaredEToF->Write();
        KaonPlusPtOutliersEta->Write();
        KaonPlusPtOutliersMSquared->Write();
        PionPlusPtOutliersEta->Write();
        PionPlusPtOutliersMSquared->Write();
     
        HistogramRootFile->Close();
    }
    
    
    
    if(RunIteration == 2)
    {
        for(int i = 0; i < 16; i++)
        {
            HistoInnerEPDQxRecentered[i]->SetDirectory(0);
            HistoInnerEPDQyRecentered[i]->SetDirectory(0);
            HistoOuterEPDQxRecentered[i]->SetDirectory(0);
            HistoOuterEPDQyRecentered[i]->SetDirectory(0);
            HistoOuterTPCQxRecentered[i]->SetDirectory(0);
            HistoOuterTPCQyRecentered[i]->SetDirectory(0);
        }
        for(int i = 0; i < 16; i++)
        {
            HistoInnerEPDSineAverages[i]->SetDirectory(0);
            HistoInnerEPDCosineAverages[i]->SetDirectory(0);
            HistoOuterEPDSineAverages[i]->SetDirectory(0);
            HistoOuterEPDCosineAverages[i]->SetDirectory(0);
            HistoOuterTPCSineAverages[i]->SetDirectory(0);
            HistoOuterTPCCosineAverages[i]->SetDirectory(0);
        }
        for(int i = 0; i < 16; i++)
        {
            HistoD34[i]->SetDirectory(0);
            HistoD37[i]->SetDirectory(0);
            HistoD40[i]->SetDirectory(0);
        }
        
        
        
        std::string QVectorHistogramFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/QVectorSecondPass" + Variation + ID +".root";
        const char *QVectorHistogramFileChar = &QVectorHistogramFileString[0];        

        TFile *QVectorHistogramRootFile = TFile::Open(QVectorHistogramFileChar, "RECREATE");
        QVectorHistogramRootFile->cd();

        for(int i = 0; i < 16; i++)
        {
            HistoInnerEPDQxRecentered[i]->Write();
            HistoInnerEPDQyRecentered[i]->Write();
            HistoOuterEPDQxRecentered[i]->Write();
            HistoOuterEPDQyRecentered[i]->Write();
            HistoOuterTPCQxRecentered[i]->Write();
            HistoOuterTPCQyRecentered[i]->Write();
        }
        for(int i = 0; i < 16; i++)
        {
            HistoInnerEPDSineAverages[i]->Write();
            HistoInnerEPDCosineAverages[i]->Write();
            HistoOuterEPDSineAverages[i]->Write();
            HistoOuterEPDCosineAverages[i]->Write();
            HistoOuterTPCSineAverages[i]->Write();
            HistoOuterTPCCosineAverages[i]->Write();
        }

        QVectorHistogramRootFile->Close();

            
            


        std::string HistogramRootFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramSecondPass" + Variation + ID + ".root";
        const char *HistogramRootFileChar = &HistogramRootFileString[0];
        
        TFile *HistogramRootFile = TFile::Open(HistogramRootFileChar, "RECREATE");
        HistogramRootFile->cd();

        for(int i = 0; i < 16; i++)
        {
            HistoD34[i]->Write();
            HistoD37[i]->Write();
            HistoD40[i]->Write();
        }

        HistogramRootFile->Close();
    }
    
    
    
    if(RunIteration == 3)
    {
        for(int i = 0; i < 16; i++)
        {    
            HistoD35[i]->SetDirectory(0);
            HistoD38[i]->SetDirectory(0);
            HistoD41[i]->SetDirectory(0);
        }
        HistoD51->SetDirectory(0);
        HistoD52->SetDirectory(0);
        HistoD53->SetDirectory(0);
                    
            


        std::string HistogramRootFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramThirdPass" + Variation + ID + ".root";
        const char *HistogramRootFileChar = &HistogramRootFileString[0];
        
        TFile *HistogramRootFile = TFile::Open(HistogramRootFileChar, "RECREATE");
        HistogramRootFile->cd();

        for(int i = 0; i < 16; i++)
        {    
            HistoD35[i]->Write();
            HistoD38[i]->Write();
            HistoD41[i]->Write();
        }
        HistoD51->Write();
        HistoD52->Write();
        HistoD53->Write();

        HistogramRootFile->Close();
    }
    
    
    
    if(RunIteration == 4)
    {
        std::string YAxisString = "V_{" + std::to_string(nV) +"}";
        const char* YAxisChar = &YAxisString[0];
        
        
        
        
        
        std::string HistoD89String = "DataVnVsPtForProtonsCentrality0-10";
        const char* HistoD89Char = &HistoD89String[0];
        
        std::string HistoD90String = "DataVnVsPtForProtonsCentrality10-40";
        const char* HistoD90Char = &HistoD90String[0];
        
        std::string HistoD91String = "DataVnVsPtForProtonsCentrality40-60";
        const char* HistoD91Char = &HistoD91String[0];
        
        std::string HistoD92String = "DataVnVsYForProtonsCentrality0-10";
        const char* HistoD92Char = &HistoD92String[0];
        
        std::string HistoD93String = "DataVnVsYForProtonsCentrality10-40";
        const char* HistoD93Char = &HistoD93String[0];
        
        std::string HistoD94String = "DataVnVsYForProtonsCentrality40-60";
        const char* HistoD94Char = &HistoD94String[0];



        std::string HistoD89StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for Protons, 0-10% Centrality";
        const char* HistoD89CharTitle = &HistoD89StringTitle[0];
        
        std::string HistoD90StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for Protons, 10-40% Centrality";
        const char* HistoD90CharTitle = &HistoD90StringTitle[0];
        
        std::string HistoD91StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for Protons, 40-60% Centrality";
        const char* HistoD91CharTitle = &HistoD91StringTitle[0];
        
        std::string HistoD92StringTitle = "V_{" + std::to_string(nV) + "} vs Y for Protons, 0-10% Centrality";
        const char* HistoD92CharTitle = &HistoD92StringTitle[0];
        
        std::string HistoD93StringTitle = "V_{" + std::to_string(nV) + "} vs Y for Protons, 10-40% Centrality";
        const char* HistoD93CharTitle = &HistoD93StringTitle[0];
        
        std::string HistoD94StringTitle = "V_{" + std::to_string(nV) + "} vs Y for Protons, 40-60% Centrality";
        const char* HistoD94CharTitle = &HistoD94StringTitle[0];
        
        
        
        TProfile *HistoD89 = (TProfile*)HistoD79->ProfileY(HistoD89Char, 1, 2);
        HistoD89->SetTitle(HistoD89CharTitle);
        HistoD89->SetXTitle("Pt (GeV)");
        HistoD89->SetYTitle(YAxisChar);
        TProfile *HistoD90 = (TProfile*)HistoD79->ProfileY(HistoD90Char, 3, 8);
        HistoD90->SetTitle(HistoD90CharTitle);
        HistoD90->SetXTitle("Pt (GeV)");
        HistoD90->SetYTitle(YAxisChar);
        TProfile *HistoD91 = (TProfile*)HistoD79->ProfileY(HistoD91Char, 9, 12);
        HistoD91->SetTitle(HistoD91CharTitle);
        HistoD91->SetXTitle("Pt (GeV)");
        HistoD91->SetYTitle(YAxisChar);
        TProfile *HistoD92 = (TProfile*)HistoD80->ProfileY(HistoD92Char, 1, 2);
        HistoD92->SetTitle(HistoD92CharTitle);
        HistoD92->SetXTitle("y_{CM}");
        HistoD92->SetYTitle(YAxisChar);
        TProfile *HistoD93 = (TProfile*)HistoD80->ProfileY(HistoD93Char, 3, 8);
        HistoD93->SetTitle(HistoD93CharTitle);
        HistoD93->SetXTitle("y_{CM}");
        HistoD93->SetYTitle(YAxisChar);
        TProfile *HistoD94 = (TProfile*)HistoD80->ProfileY(HistoD94Char, 9, 12);
        HistoD94->SetTitle(HistoD94CharTitle);
        HistoD94->SetXTitle("y_{CM}");
        HistoD94->SetYTitle(YAxisChar);
        
        
        
        
        
        
        
        
        
        
        std::string HistoD95String = "DataVnVsPtForKaonsPlusCentrality0-10";
        const char* HistoD95Char = &HistoD95String[0];
        
        std::string HistoD96String = "DataVnVsPtForKaonsPlusCentrality10-40";
        const char* HistoD96Char = &HistoD96String[0];
        
        std::string HistoD97String = "DataVnVsPtForKaonsPlusCentrality40-60";
        const char* HistoD97Char = &HistoD97String[0];
        
        std::string HistoD98String = "DataVnVsYForKaonsPlusCentrality0-10";
        const char* HistoD98Char = &HistoD98String[0];
        
        std::string HistoD99String = "DataVnVsYForKaonsPlusCentrality10-40";
        const char* HistoD99Char = &HistoD99String[0];
        
        std::string HistoD100String = "DataVnVsYForKaonsPlusCentrality40-60";
        const char* HistoD100Char = &HistoD100String[0];


        std::string HistoD95StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for K^{+}, 0-10% Centrality";
        const char* HistoD95CharTitle = &HistoD95StringTitle[0];
        
        std::string HistoD96StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for K^{+}, 10-40% Centrality";
        const char* HistoD96CharTitle = &HistoD96StringTitle[0];
        
        std::string HistoD97StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for K^{+}, 40-60% Centrality";
        const char* HistoD97CharTitle = &HistoD97StringTitle[0];
        
        std::string HistoD98StringTitle = "V_{" + std::to_string(nV) + "} vs Y for K^{+}, 0-10% Centrality";
        const char* HistoD98CharTitle = &HistoD98StringTitle[0];
        
        std::string HistoD99StringTitle = "V_{" + std::to_string(nV) + "} vs Y for K^{+}, 10-40% Centrality";
        const char* HistoD99CharTitle = &HistoD99StringTitle[0];
        
        std::string HistoD100StringTitle = "V_{" + std::to_string(nV) + "} vs Y for K^{+}, 40-60% Centrality";
        const char* HistoD100CharTitle = &HistoD100StringTitle[0];


        TProfile *HistoD95 = (TProfile*)HistoD81->ProfileY(HistoD95Char, 1, 2);
        HistoD95->SetTitle(HistoD95CharTitle);
        HistoD95->SetXTitle("Pt (GeV)");
        HistoD95->SetYTitle(YAxisChar);
        TProfile *HistoD96 = (TProfile*)HistoD81->ProfileY(HistoD96Char, 3, 8);
        HistoD96->SetTitle(HistoD96CharTitle);
        HistoD96->SetXTitle("Pt (GeV)");
        HistoD96->SetYTitle(YAxisChar);
        TProfile *HistoD97 = (TProfile*)HistoD81->ProfileY(HistoD97Char, 9, 12);
        HistoD97->SetTitle(HistoD97CharTitle);
        HistoD97->SetXTitle("Pt (GeV)");
        HistoD97->SetYTitle(YAxisChar);
        TProfile *HistoD98 = (TProfile*)HistoD82->ProfileY(HistoD98Char, 1, 2);
        HistoD98->SetTitle(HistoD98CharTitle);
        HistoD98->SetXTitle("y_{CM}");
        HistoD98->SetYTitle(YAxisChar);
        TProfile *HistoD99 = (TProfile*)HistoD82->ProfileY(HistoD99Char, 3, 8);
        HistoD99->SetTitle(HistoD99CharTitle);
        HistoD99->SetXTitle("y_{CM}");
        HistoD99->SetYTitle(YAxisChar);
        TProfile *HistoD100 = (TProfile*)HistoD82->ProfileY(HistoD100Char, 9, 12);
        HistoD100->SetTitle(HistoD100CharTitle);
        HistoD100->SetXTitle("y_{CM}");
        HistoD100->SetYTitle(YAxisChar);
        
        
        
        
        
        
        
        std::string HistoD101String = "DataVnVsPtForKaonsMinusCentrality0-10";
        const char* HistoD101Char = &HistoD101String[0];
        
        std::string HistoD102String = "DataVnVsPtForKaonsMinusCentrality10-40";
        const char* HistoD102Char = &HistoD102String[0];
        
        std::string HistoD103String = "DataVnVsPtForKaonsMinusCentrality40-60";
        const char* HistoD103Char = &HistoD103String[0];
        
        std::string HistoD104String = "DataVnVsYForKaonsMinusCentrality0-10";
        const char* HistoD104Char = &HistoD104String[0];
        
        std::string HistoD105String = "DataVnVsYForKaonsMinusCentrality10-40";
        const char* HistoD105Char = &HistoD105String[0];
        
        std::string HistoD106String = "DataVnVsYForKaonsMinusCentrality40-60";
        const char* HistoD106Char = &HistoD106String[0];

        

        std::string HistoD101StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for K^{-}, 0-10% Centrality";
        const char* HistoD101CharTitle = &HistoD101StringTitle[0];
        
        std::string HistoD102StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for K^{-}, 10-40% Centrality";
        const char* HistoD102CharTitle = &HistoD102StringTitle[0];
        
        std::string HistoD103StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for K^{-}, 40-60% Centrality";
        const char* HistoD103CharTitle = &HistoD103StringTitle[0];
        
        std::string HistoD104StringTitle = "V_{" + std::to_string(nV) + "} vs Y for K^{-}, 0-10% Centrality";
        const char* HistoD104CharTitle = &HistoD104StringTitle[0];
        
        std::string HistoD105StringTitle = "V_{" + std::to_string(nV) + "} vs Y for K^{-}, 10-40% Centrality";
        const char* HistoD105CharTitle = &HistoD105StringTitle[0];
        
        std::string HistoD106StringTitle = "V_{" + std::to_string(nV) + "} vs Y for K^{-}, 40-60% Centrality";
        const char* HistoD106CharTitle = &HistoD106StringTitle[0];
        


        TProfile *HistoD101 = (TProfile*)HistoD83->ProfileY(HistoD101Char, 1, 2);
        HistoD101->SetTitle(HistoD101CharTitle);
        HistoD101->SetXTitle("Pt (GeV)");
        HistoD101->SetYTitle(YAxisChar);
        TProfile *HistoD102 = (TProfile*)HistoD83->ProfileY(HistoD102Char, 3, 8);
        HistoD102->SetTitle(HistoD102CharTitle);
        HistoD102->SetXTitle("Pt (GeV)");
        HistoD102->SetYTitle(YAxisChar);
        TProfile *HistoD103 = (TProfile*)HistoD83->ProfileY(HistoD103Char, 9, 12);
        HistoD103->SetTitle(HistoD103CharTitle);
        HistoD103->SetXTitle("Pt (GeV)");
        HistoD103->SetYTitle(YAxisChar);
        TProfile *HistoD104 = (TProfile*)HistoD84->ProfileY(HistoD104Char, 1, 2);
        HistoD104->SetTitle(HistoD104CharTitle);
        HistoD104->SetXTitle("y_{CM}");
        HistoD104->SetYTitle(YAxisChar);
        TProfile *HistoD105 = (TProfile*)HistoD84->ProfileY(HistoD105Char, 3, 8);
        HistoD105->SetTitle(HistoD105CharTitle);
        HistoD105->SetXTitle("y_{CM}");
        HistoD105->SetYTitle(YAxisChar);
        TProfile *HistoD106 = (TProfile*)HistoD84->ProfileY(HistoD106Char, 9, 12);
        HistoD106->SetTitle(HistoD106CharTitle);
        HistoD106->SetXTitle("y_{CM}");
        HistoD106->SetYTitle(YAxisChar);


        
        
        
        
        
        
        std::string HistoD107String = "DataVnVsPtForPionsPlusCentrality0-10";
        const char* HistoD107Char = &HistoD107String[0];
        
        std::string HistoD108String = "DataVnVsPtForPionsPlusCentrality10-40";
        const char* HistoD108Char = &HistoD108String[0];
        
        std::string HistoD109String = "DataVnVsPtForPionsPlusCentrality40-60";
        const char* HistoD109Char = &HistoD109String[0];
        
        std::string HistoD110String = "DataVnVsYForPionsPlusCentrality0-10";
        const char* HistoD110Char = &HistoD110String[0];
        
        std::string HistoD111String = "DataVnVsYForPionsPlusCentrality10-40";
        const char* HistoD111Char = &HistoD111String[0];
        
        std::string HistoD112String = "DataVnVsYForPionsPlusCentrality40-60";
        const char* HistoD112Char = &HistoD112String[0];


        std::string HistoD107StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for #pi^{+}, 0-10% Centrality";
        const char* HistoD107CharTitle = &HistoD107StringTitle[0];
        
        std::string HistoD108StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for #pi^{+}, 10-40% Centrality";
        const char* HistoD108CharTitle = &HistoD108StringTitle[0];
        
        std::string HistoD109StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for #pi^{+}, 40-60% Centrality";
        const char* HistoD109CharTitle = &HistoD109StringTitle[0];
        
        std::string HistoD110StringTitle = "V_{" + std::to_string(nV) + "} vs Y for #pi^{+}, 0-10% Centrality";
        const char* HistoD110CharTitle = &HistoD110StringTitle[0];
        
        std::string HistoD111StringTitle = "V_{" + std::to_string(nV) + "} vs Y for #pi^{+}, 10-40% Centrality";
        const char* HistoD111CharTitle = &HistoD111StringTitle[0];
        
        std::string HistoD112StringTitle = "V_{" + std::to_string(nV) + "} vs Y for #pi^{+}, 40-60% Centrality";
        const char* HistoD112CharTitle = &HistoD112StringTitle[0];
        

        TProfile *HistoD107 = (TProfile*)HistoD85->ProfileY(HistoD107Char, 1, 2);
        HistoD107->SetTitle(HistoD107CharTitle);
        HistoD107->SetXTitle("Pt (GeV)");
        HistoD107->SetYTitle(YAxisChar);
        TProfile *HistoD108 = (TProfile*)HistoD85->ProfileY(HistoD108Char, 3, 8);
        HistoD108->SetTitle(HistoD108CharTitle);
        HistoD108->SetXTitle("Pt (GeV)");
        HistoD108->SetYTitle(YAxisChar);
        TProfile *HistoD109 = (TProfile*)HistoD85->ProfileY(HistoD109Char, 9, 12);
        HistoD109->SetTitle(HistoD109CharTitle);
        HistoD109->SetXTitle("Pt (GeV)");
        HistoD109->SetYTitle(YAxisChar);
        TProfile *HistoD110 = (TProfile*)HistoD86->ProfileY(HistoD110Char, 1, 2);
        HistoD110->SetTitle(HistoD110CharTitle);
        HistoD110->SetXTitle("y_{CM}");
        HistoD110->SetYTitle(YAxisChar);
        TProfile *HistoD111 = (TProfile*)HistoD86->ProfileY(HistoD111Char, 3, 8);
        HistoD111->SetTitle(HistoD111CharTitle);
        HistoD111->SetXTitle("y_{CM}");
        HistoD111->SetYTitle(YAxisChar);
        TProfile *HistoD112 = (TProfile*)HistoD86->ProfileY(HistoD112Char, 9, 12);
        HistoD112->SetTitle(HistoD112CharTitle);
        HistoD112->SetXTitle("y_{CM}");
        HistoD112->SetYTitle(YAxisChar);
        
        
        
        
        
        
        
        
        std::string HistoD113String = "DataVnVsPtForPionsMinusCentrality0-10";
        const char* HistoD113Char = &HistoD113String[0];
        
        std::string HistoD114String = "DataVnVsPtForPionsMinusCentrality10-40";
        const char* HistoD114Char = &HistoD114String[0];
        
        std::string HistoD115String = "DataVnVsPtForPionsMinusCentrality40-60";
        const char* HistoD115Char = &HistoD115String[0];
        
        std::string HistoD116String = "DataVnVsYForPionsMinusCentrality0-10";
        const char* HistoD116Char = &HistoD116String[0];
        
        std::string HistoD117String = "DataVnVsYForPionsMinusCentrality10-40";
        const char* HistoD117Char = &HistoD117String[0];
        
        std::string HistoD118String = "DataVnVsYForPionsMinusCentrality40-60";
        const char* HistoD118Char = &HistoD118String[0];


        std::string HistoD113StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for #pi^{-}, 0-10% Centrality";
        const char* HistoD113CharTitle = &HistoD113StringTitle[0];
        
        std::string HistoD114StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for #pi^{-}, 10-40% Centrality";
        const char* HistoD114CharTitle = &HistoD114StringTitle[0];
        
        std::string HistoD115StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for #pi^{-}, 40-60% Centrality";
        const char* HistoD115CharTitle = &HistoD115StringTitle[0];
        
        std::string HistoD116StringTitle = "V_{" + std::to_string(nV) + "} vs Y for #pi^{-}, 0-10% Centrality";
        const char* HistoD116CharTitle = &HistoD116StringTitle[0];
        
        std::string HistoD117StringTitle = "V_{" + std::to_string(nV) + "} vs Y for #pi^{-}, 10-40% Centrality";
        const char* HistoD117CharTitle = &HistoD117StringTitle[0];
        
        std::string HistoD118StringTitle = "V_{" + std::to_string(nV) + "} vs Y for #pi^{-}, 40-60% Centrality";
        const char* HistoD118CharTitle = &HistoD118StringTitle[0];
        


        TProfile *HistoD113 = (TProfile*)HistoD87->ProfileY(HistoD113Char, 1, 2);
        HistoD113->SetTitle(HistoD113CharTitle);
        HistoD113->SetXTitle("Pt (GeV)");
        HistoD113->SetYTitle(YAxisChar);
        TProfile *HistoD114 = (TProfile*)HistoD87->ProfileY(HistoD114Char, 3, 8);
        HistoD114->SetTitle(HistoD114CharTitle);
        HistoD114->SetXTitle("Pt (GeV)");
        HistoD114->SetYTitle(YAxisChar);
        TProfile *HistoD115 = (TProfile*)HistoD87->ProfileY(HistoD115Char, 9, 12);
        HistoD115->SetTitle(HistoD115CharTitle);
        HistoD115->SetXTitle("Pt (GeV)");
        HistoD115->SetYTitle(YAxisChar);
        TProfile *HistoD116 = (TProfile*)HistoD88->ProfileY(HistoD116Char, 1, 2);
        HistoD116->SetTitle(HistoD116CharTitle);
        HistoD116->SetXTitle("y_{CM}");
        HistoD116->SetYTitle(YAxisChar);
        TProfile *HistoD117 = (TProfile*)HistoD88->ProfileY(HistoD117Char, 3, 8);
        HistoD117->SetTitle(HistoD117CharTitle);
        HistoD117->SetXTitle("y_{CM}");
        HistoD117->SetYTitle(YAxisChar);
        TProfile *HistoD118 = (TProfile*)HistoD88->ProfileY(HistoD118Char, 9, 12);
        HistoD118->SetTitle(HistoD118CharTitle);
        HistoD118->SetXTitle("y_{CM}");
        HistoD118->SetYTitle(YAxisChar);
        
        
        
        
        
        
        
        
        std::string HistoD119String = "DataVnVsPtForDeuteronsCentrality0-10";
        const char* HistoD119Char = &HistoD119String[0];
        
        std::string HistoD120String = "DataVnVsPtForDeuteronsCentrality10-40";
        const char* HistoD120Char = &HistoD120String[0];
        
        std::string HistoD121String = "DataVnVsPtForDeuteronsCentrality40-60";
        const char* HistoD121Char = &HistoD121String[0];
        
        std::string HistoD122String = "DataVnVsYForDeuteronsCentrality0-10";
        const char* HistoD122Char = &HistoD122String[0];
        
        std::string HistoD123String = "DataVnVsYForDeuteronsCentrality10-40";
        const char* HistoD123Char = &HistoD123String[0];
        
        std::string HistoD124String = "DataVnVsYForDeuteronsCentrality40-60";
        const char* HistoD124Char = &HistoD124String[0];


        std::string HistoD119StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for Deuterons, 0-10% Centrality";
        const char* HistoD119CharTitle = &HistoD119StringTitle[0];
        
        std::string HistoD120StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for Deuterons, 10-40% Centrality";
        const char* HistoD120CharTitle = &HistoD120StringTitle[0];
        
        std::string HistoD121StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for Deuterons, 40-60% Centrality";
        const char* HistoD121CharTitle = &HistoD121StringTitle[0];
        
        std::string HistoD122StringTitle = "V_{" + std::to_string(nV) + "} vs Y for Deuterons, 0-10% Centrality";
        const char* HistoD122CharTitle = &HistoD122StringTitle[0];
        
        std::string HistoD123StringTitle = "V_{" + std::to_string(nV) + "} vs Y for Deuterons, 10-40% Centrality";
        const char* HistoD123CharTitle = &HistoD123StringTitle[0];
        
        std::string HistoD124StringTitle = "V_{" + std::to_string(nV) + "} vs Y for Deuterons, 40-60% Centrality";
        const char* HistoD124CharTitle = &HistoD124StringTitle[0];


        TProfile *HistoD119 = (TProfile*)HistoD88A->ProfileY(HistoD119Char, 1, 2);
        HistoD119->SetTitle(HistoD119CharTitle);
        HistoD119->SetXTitle("Pt (GeV)");
        HistoD119->SetYTitle(YAxisChar);
        TProfile *HistoD120 = (TProfile*)HistoD88A->ProfileY(HistoD120Char, 3, 8);
        HistoD120->SetTitle(HistoD120CharTitle);
        HistoD120->SetXTitle("Pt (GeV)");
        HistoD120->SetYTitle(YAxisChar);
        TProfile *HistoD121 = (TProfile*)HistoD88A->ProfileY(HistoD121Char, 9, 12);
        HistoD121->SetTitle(HistoD121CharTitle);
        HistoD121->SetXTitle("Pt (GeV)");
        HistoD121->SetYTitle(YAxisChar);
        TProfile *HistoD122 = (TProfile*)HistoD88B->ProfileY(HistoD122Char, 1, 2);
        HistoD122->SetTitle(HistoD122CharTitle);
        HistoD122->SetXTitle("y_{CM}");
        HistoD122->SetYTitle(YAxisChar);
        TProfile *HistoD123 = (TProfile*)HistoD88B->ProfileY(HistoD123Char, 3, 8);
        HistoD123->SetTitle(HistoD123CharTitle);
        HistoD123->SetXTitle("y_{CM}");
        HistoD123->SetYTitle(YAxisChar);
        TProfile *HistoD124 = (TProfile*)HistoD88B->ProfileY(HistoD124Char, 9, 12);
        HistoD124->SetTitle(HistoD124CharTitle);
        HistoD124->SetXTitle("y_{CM}");
        HistoD124->SetYTitle(YAxisChar);
        
        
        
        
        
        
        
        
        std::string HistoD125String = "DataVnVsPtForTritonsCentrality0-10";
        const char* HistoD125Char = &HistoD125String[0];
        
        std::string HistoD126String = "DataVnVsPtForTritonsCentrality10-40";
        const char* HistoD126Char = &HistoD126String[0];
        
        std::string HistoD127String = "DataVnVsPtForTritonsCentrality40-60";
        const char* HistoD127Char = &HistoD127String[0];
        
        std::string HistoD128String = "DataVnVsYForTritonsCentrality0-10";
        const char* HistoD128Char = &HistoD128String[0];
        
        std::string HistoD129String = "DataVnVsYForTritonsCentrality10-40";
        const char* HistoD129Char = &HistoD129String[0];
        
        std::string HistoD130String = "DataVnVsYForTritonsCentrality40-60";
        const char* HistoD130Char = &HistoD130String[0];


        std::string HistoD125StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for Tritons, 0-10% Centrality";
        const char* HistoD125CharTitle = &HistoD125StringTitle[0];
        
        std::string HistoD126StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for Tritons, 10-40% Centrality";
        const char* HistoD126CharTitle = &HistoD126StringTitle[0];
        
        std::string HistoD127StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for Tritons, 40-60% Centrality";
        const char* HistoD127CharTitle = &HistoD127StringTitle[0];
        
        std::string HistoD128StringTitle = "V_{" + std::to_string(nV) + "} vs Y for Tritons, 0-10% Centrality";
        const char* HistoD128CharTitle = &HistoD128StringTitle[0];
        
        std::string HistoD129StringTitle = "V_{" + std::to_string(nV) + "} vs Y for Tritons, 10-40% Centrality";
        const char* HistoD129CharTitle = &HistoD129StringTitle[0];
        
        std::string HistoD130StringTitle = "V_{" + std::to_string(nV) + "} vs Y for Tritons, 40-60% Centrality";
        const char* HistoD130CharTitle = &HistoD130StringTitle[0];


        TProfile *HistoD125 = (TProfile*)HistoD88C->ProfileY(HistoD125Char, 1, 2);
        HistoD125->SetTitle(HistoD125CharTitle);
        HistoD125->SetXTitle("Pt (GeV)");
        HistoD125->SetYTitle(YAxisChar);
        TProfile *HistoD126 = (TProfile*)HistoD88C->ProfileY(HistoD126Char, 3, 8);
        HistoD126->SetTitle(HistoD126CharTitle);
        HistoD126->SetXTitle("Pt (GeV)");
        HistoD126->SetYTitle(YAxisChar);
        TProfile *HistoD127 = (TProfile*)HistoD88C->ProfileY(HistoD127Char, 9, 12);
        HistoD127->SetTitle(HistoD127CharTitle);
        HistoD127->SetXTitle("Pt (GeV)");
        HistoD127->SetYTitle(YAxisChar);
        TProfile *HistoD128 = (TProfile*)HistoD88D->ProfileY(HistoD128Char, 1, 2);
        HistoD128->SetTitle(HistoD128CharTitle);
        HistoD128->SetXTitle("y_{CM}");
        HistoD128->SetYTitle(YAxisChar);
        TProfile *HistoD129 = (TProfile*)HistoD88D->ProfileY(HistoD129Char, 3, 8);
        HistoD129->SetTitle(HistoD129CharTitle);
        HistoD129->SetXTitle("y_{CM}");
        HistoD129->SetYTitle(YAxisChar);
        TProfile *HistoD130 = (TProfile*)HistoD88D->ProfileY(HistoD130Char, 9, 12);
        HistoD130->SetTitle(HistoD130CharTitle);
        HistoD130->SetXTitle("y_{CM}");
        HistoD130->SetYTitle(YAxisChar);
        
        
        
        
        std::string VnVsYSymmetricProtonCentrality0_10String = "DataVnVsYSymmetricForProtonsCentrality0-10";
        const char* VnVsYSymmetricProtonCentrality0_10Char = &VnVsYSymmetricProtonCentrality0_10String[0];
        
        std::string VnVsYSymmetricProtonCentrality10_40String = "DataVnVsYSymmetricForProtonsCentrality10-40";
        const char* VnVsYSymmetricProtonCentrality10_40Char = &VnVsYSymmetricProtonCentrality10_40String[0];
        
        std::string VnVsYSymmetricProtonCentrality40_60String = "DataVnVsYSymmetricForProtonsCentrality40-60";
        const char* VnVsYSymmetricProtonCentrality40_60Char = &VnVsYSymmetricProtonCentrality40_60String[0];


        std::string VnVsYSymmetricProtonCentrality0_10StringTitle = "V_{" + std::to_string(nV) + "} vs Y Symmetric for Protons, 0-10% Centrality";
        const char* VnVsYSymmetricProtonCentrality0_10CharTitle = &VnVsYSymmetricProtonCentrality0_10StringTitle[0];
        
        std::string VnVsYSymmetricProtonCentrality10_40StringTitle = "V_{" + std::to_string(nV) + "} vs Y Symmetric for Protons, 10-40% Centrality";
        const char* VnVsYSymmetricProtonCentrality10_40CharTitle = &VnVsYSymmetricProtonCentrality10_40StringTitle[0];
        
        std::string VnVsYSymmetricProtonCentrality40_60StringTitle = "V_{" + std::to_string(nV) + "} vs Y Symmetric for Protons, 40-60% Centrality";
        const char* VnVsYSymmetricProtonCentrality40_60CharTitle = &VnVsYSymmetricProtonCentrality40_60StringTitle[0];


        TProfile *VnVsYSymmetricProtonCentrality0_10 = (TProfile*)VnVsYSymmetricProton->ProfileY(VnVsYSymmetricProtonCentrality0_10Char, 1, 2);
        VnVsYSymmetricProtonCentrality0_10->SetTitle(VnVsYSymmetricProtonCentrality0_10CharTitle);
        VnVsYSymmetricProtonCentrality0_10->SetXTitle("y_{CM}");
        VnVsYSymmetricProtonCentrality0_10->SetYTitle(YAxisChar);
        TProfile *VnVsYSymmetricProtonCentrality10_40 = (TProfile*)VnVsYSymmetricProton->ProfileY(VnVsYSymmetricProtonCentrality10_40Char, 3, 8);
        VnVsYSymmetricProtonCentrality10_40->SetTitle(VnVsYSymmetricProtonCentrality10_40CharTitle);
        VnVsYSymmetricProtonCentrality10_40->SetXTitle("y_{CM}");
        VnVsYSymmetricProtonCentrality10_40->SetYTitle(YAxisChar);
        TProfile *VnVsYSymmetricProtonCentrality40_60 = (TProfile*)VnVsYSymmetricProton->ProfileY(VnVsYSymmetricProtonCentrality40_60Char, 9, 12);
        VnVsYSymmetricProtonCentrality40_60->SetTitle(VnVsYSymmetricProtonCentrality40_60CharTitle);
        VnVsYSymmetricProtonCentrality40_60->SetXTitle("y_{CM}");
        VnVsYSymmetricProtonCentrality40_60->SetYTitle(YAxisChar);





        
        std::string VnVsPtProtonHighRapidityCentrality10_40String = "VnVsPtProtonHighRapidityCentrality10-40";
        const char* VnVsPtProtonHighRapidityCentrality10_40Char = &VnVsPtProtonHighRapidityCentrality10_40String[0];

        std::string VnVsPtDeuteronHighRapidityCentrality10_40String = "VnVsPtDeuteronHighRapidityCentrality10-40";
        const char* VnVsPtDeuteronHighRapidityCentrality10_40Char = &VnVsPtDeuteronHighRapidityCentrality10_40String[0];

        std::string VnVsPtTritonHighRapidityCentrality10_40String = "VnVsPtTritonHighRapidityCentrality10-40";
        const char* VnVsPtTritonHighRapidityCentrality10_40Char = &VnVsPtTritonHighRapidityCentrality10_40String[0];



        std::string VnVsPtProtonHighRapidityCentrality10_40StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for Protons (Y > 0.5), 10-40% Centrality";
        const char* VnVsPtProtonHighRapidityCentrality10_40CharTitle = &VnVsPtProtonHighRapidityCentrality10_40StringTitle[0];

        std::string VnVsPtDeuteronHighRapidityCentrality10_40StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for Deuterons (Y > 0.5), 10-40% Centrality";
        const char* VnVsPtDeuteronHighRapidityCentrality10_40CharTitle = &VnVsPtDeuteronHighRapidityCentrality10_40StringTitle[0];        

        std::string VnVsPtTritonHighRapidityCentrality10_40StringTitle = "V_{" + std::to_string(nV) + "} vs Pt for Tritons (Y > 0.5), 10-40% Centrality";
        const char* VnVsPtTritonHighRapidityCentrality10_40CharTitle = &VnVsPtTritonHighRapidityCentrality10_40StringTitle[0];

        

        TProfile *VnVsPtProtonHighRapidityCentrality10_40 = (TProfile*)VnVsCentPtProtonHighRapidity->ProfileY(VnVsPtProtonHighRapidityCentrality10_40Char, 3, 8);
        VnVsPtProtonHighRapidityCentrality10_40->SetTitle(VnVsPtProtonHighRapidityCentrality10_40CharTitle);
        VnVsPtProtonHighRapidityCentrality10_40->SetXTitle("Pt (GeV)");
        VnVsPtProtonHighRapidityCentrality10_40->SetYTitle(YAxisChar);
        TProfile *VnVsPtDeuteronHighRapidityCentrality10_40 = (TProfile*)VnVsCentPtDeuteronHighRapidity->ProfileY(VnVsPtDeuteronHighRapidityCentrality10_40Char, 3, 8);
        VnVsPtDeuteronHighRapidityCentrality10_40->SetTitle(VnVsPtDeuteronHighRapidityCentrality10_40CharTitle);
        VnVsPtDeuteronHighRapidityCentrality10_40->SetXTitle("Pt (GeV)");
        VnVsPtDeuteronHighRapidityCentrality10_40->SetYTitle(YAxisChar);
        TProfile *VnVsPtTritonHighRapidityCentrality10_40 = (TProfile*)VnVsCentPtTritonHighRapidity->ProfileY(VnVsPtTritonHighRapidityCentrality10_40Char, 3, 8);
        VnVsPtTritonHighRapidityCentrality10_40->SetTitle(VnVsPtTritonHighRapidityCentrality10_40CharTitle);
        VnVsPtTritonHighRapidityCentrality10_40->SetXTitle("Pt (GeV)");
        VnVsPtTritonHighRapidityCentrality10_40->SetYTitle(YAxisChar);
        

        
        EventCheck->SetDirectory(0);
        OverallTrackCheckNoCuts->SetDirectory(0);
        OverallTrackCheckQACuts->SetDirectory(0);
        ProtonTrackCheck->SetDirectory(0);
        MostlyGoodProtonTrackCheck->SetDirectory(0);
        GoodProtonTrackCheck->SetDirectory(0);
        KaonPlusTrackCheck->SetDirectory(0);
        MostlyGoodKaonPlusTrackCheck->SetDirectory(0);
        GoodKaonPlusTrackCheck->SetDirectory(0);
        KaonMinusTrackCheck->SetDirectory(0);
        MostlyGoodKaonMinusTrackCheck->SetDirectory(0);
        GoodKaonMinusTrackCheck->SetDirectory(0);
        PionPlusTrackCheck->SetDirectory(0);
        MostlyGoodPionPlusTrackCheck->SetDirectory(0);
        GoodPionPlusTrackCheck->SetDirectory(0);
        PionMinusTrackCheck->SetDirectory(0);
        MostlyGoodPionMinusTrackCheck->SetDirectory(0);
        GoodPionMinusTrackCheck->SetDirectory(0);
        DeuteronTrackCheck->SetDirectory(0);
        MostlyGoodDeuteronTrackCheck->SetDirectory(0);
        GoodDeuteronTrackCheck->SetDirectory(0);
        TritonTrackCheck->SetDirectory(0);
        MostlyGoodTritonTrackCheck->SetDirectory(0);
        GoodTritonTrackCheck->SetDirectory(0);
        TrackMultiplicity->SetDirectory(0);
        OverallTrackCheckIDedAsAny->SetDirectory(0);
        HistoDC->SetDirectory(0);
        HistoDD->SetDirectory(0);
        HistoDE->SetDirectory(0);
        HistoD44C->SetDirectory(0);
        HistoD47B->SetDirectory(0);
        HistoD47C->SetDirectory(0);
        HistoD50B->SetDirectory(0);
        HistoD50C->SetDirectory(0);
        HistoD50D->SetDirectory(0);
        HistoD50E->SetDirectory(0);
        HistoD54A->SetDirectory(0);
        HistoD54B->SetDirectory(0);
        HistoD54C->SetDirectory(0);
        HistoD54D->SetDirectory(0);
        HistoD54E->SetDirectory(0);
        HistoD54F->SetDirectory(0);
        HistoD54G->SetDirectory(0);
        VnVsCentralityProtonHighRapidity->SetDirectory(0);
        VnVsCentralityDeuteronHighRapidity->SetDirectory(0);
        VnVsCentralityTritonHighRapidity->SetDirectory(0);
        FlowStrength->SetDirectory(0);
        FlowStrengthProton->SetDirectory(0);
        HistoD79->SetDirectory(0);
        HistoD80->SetDirectory(0);
        HistoD81->SetDirectory(0);
        HistoD82->SetDirectory(0);
        HistoD83->SetDirectory(0);
        HistoD84->SetDirectory(0);
        HistoD85->SetDirectory(0);
        HistoD86->SetDirectory(0);
        HistoD87->SetDirectory(0);
        HistoD88->SetDirectory(0);
        HistoD88A->SetDirectory(0);
        HistoD88B->SetDirectory(0);
        HistoD88C->SetDirectory(0);
        HistoD88D->SetDirectory(0);
        VnVsCentPtProtonHighRapidity->SetDirectory(0);
        VnVsCentPtDeuteronHighRapidity->SetDirectory(0);
        VnVsCentPtTritonHighRapidity->SetDirectory(0);
        HistoD89->SetDirectory(0);
        HistoD90->SetDirectory(0);
        HistoD91->SetDirectory(0);
        HistoD92->SetDirectory(0);
        HistoD93->SetDirectory(0);
        HistoD94->SetDirectory(0);
        HistoD95->SetDirectory(0);
        HistoD96->SetDirectory(0);
        HistoD97->SetDirectory(0);
        HistoD98->SetDirectory(0);
        HistoD99->SetDirectory(0);
        HistoD100->SetDirectory(0);
        HistoD101->SetDirectory(0);
        HistoD102->SetDirectory(0);
        HistoD103->SetDirectory(0);
        HistoD104->SetDirectory(0);
        HistoD105->SetDirectory(0);
        HistoD106->SetDirectory(0);
        HistoD107->SetDirectory(0);
        HistoD108->SetDirectory(0);
        HistoD109->SetDirectory(0);
        HistoD110->SetDirectory(0);
        HistoD111->SetDirectory(0);
        HistoD112->SetDirectory(0);
        HistoD113->SetDirectory(0);
        HistoD114->SetDirectory(0);
        HistoD115->SetDirectory(0);
        HistoD116->SetDirectory(0);
        HistoD117->SetDirectory(0);
        HistoD118->SetDirectory(0);
        HistoD119->SetDirectory(0);
        HistoD120->SetDirectory(0);
        HistoD121->SetDirectory(0);
        HistoD122->SetDirectory(0);
        HistoD123->SetDirectory(0);
        HistoD124->SetDirectory(0);
        HistoD125->SetDirectory(0);
        HistoD126->SetDirectory(0);
        HistoD127->SetDirectory(0);
        HistoD128->SetDirectory(0);
        HistoD129->SetDirectory(0);
        HistoD130->SetDirectory(0);
        VnVsPtProton0_00Through0_10->SetDirectory(0);
        VnVsPtProton0_10Through0_20->SetDirectory(0);
        VnVsPtProton0_20Through0_30->SetDirectory(0);
        VnVsPtProton0_30Through0_40->SetDirectory(0);
        VnVsPtDeuteron0_00Through0_10->SetDirectory(0);
        VnVsPtDeuteron0_10Through0_20->SetDirectory(0);
        VnVsPtDeuteron0_20Through0_30->SetDirectory(0);
        VnVsPtDeuteron0_30Through0_40->SetDirectory(0);
        VnVsPtTriton0_00Through0_10->SetDirectory(0);
        VnVsPtTriton0_10Through0_20->SetDirectory(0);
        VnVsPtTriton0_20Through0_30->SetDirectory(0);
        VnVsPtTriton0_30Through0_40->SetDirectory(0);
        VnOverAVsPtOverAProton0_00Through0_10->SetDirectory(0);
        VnOverAVsPtOverAProton0_10Through0_20->SetDirectory(0);
        VnOverAVsPtOverAProton0_20Through0_30->SetDirectory(0);
        VnOverAVsPtOverAProton0_30Through0_40->SetDirectory(0);
        VnOverAVsPtOverADeuteron0_00Through0_10->SetDirectory(0);
        VnOverAVsPtOverADeuteron0_10Through0_20->SetDirectory(0);
        VnOverAVsPtOverADeuteron0_20Through0_30->SetDirectory(0);
        VnOverAVsPtOverADeuteron0_30Through0_40->SetDirectory(0);
        VnOverAVsPtOverATriton0_00Through0_10->SetDirectory(0);
        VnOverAVsPtOverATriton0_10Through0_20->SetDirectory(0);
        VnOverAVsPtOverATriton0_20Through0_30->SetDirectory(0);
        VnOverAVsPtOverATriton0_30Through0_40->SetDirectory(0);
        VnVsYSymmetricProton->SetDirectory(0);
        VnVsYSymmetricProtonCentrality0_10->SetDirectory(0);
        VnVsYSymmetricProtonCentrality10_40->SetDirectory(0);
        VnVsYSymmetricProtonCentrality40_60->SetDirectory(0);
        VnVsPtProtonHighRapidityCentrality10_40->SetDirectory(0);
        VnVsPtDeuteronHighRapidityCentrality10_40->SetDirectory(0);
        VnVsPtTritonHighRapidityCentrality10_40->SetDirectory(0);

        
        std::string HistogramRootFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramFourthPass" + Variation + ID + ".root";
        const char *HistogramRootFileChar = &HistogramRootFileString[0];
        
        TFile *HistogramRootFile = TFile::Open(HistogramRootFileChar, "RECREATE");
        HistogramRootFile->cd();
        

        EventCheck->Write();
        OverallTrackCheckNoCuts->Write();
        OverallTrackCheckQACuts->Write();
        ProtonTrackCheck->Write();
        MostlyGoodProtonTrackCheck->Write();
        GoodProtonTrackCheck->Write();
        KaonPlusTrackCheck->Write();
        MostlyGoodKaonPlusTrackCheck->Write();
        GoodKaonPlusTrackCheck->Write();
        KaonMinusTrackCheck->Write();
        MostlyGoodKaonMinusTrackCheck->Write();
        GoodKaonMinusTrackCheck->Write();
        PionPlusTrackCheck->Write();
        MostlyGoodPionPlusTrackCheck->Write();
        GoodPionPlusTrackCheck->Write();
        PionMinusTrackCheck->Write();
        MostlyGoodPionMinusTrackCheck->Write();
        GoodPionMinusTrackCheck->Write();
        DeuteronTrackCheck->Write();
        MostlyGoodDeuteronTrackCheck->Write();
        GoodDeuteronTrackCheck->Write();
        TritonTrackCheck->Write();
        MostlyGoodTritonTrackCheck->Write();
        GoodTritonTrackCheck->Write();
        TrackMultiplicity->Write();
        OverallTrackCheckIDedAsAny->Write();
        HistoDC->Write();
        HistoDD->Write();
        HistoDE->Write();
        HistoD44C->Write();
        HistoD47B->Write();
        HistoD47C->Write();
        HistoD50B->Write();
        HistoD50C->Write();
        HistoD50D->Write();
        HistoD50E->Write();
        HistoD54A->Write();
        HistoD54B->Write();
        HistoD54C->Write();
        HistoD54D->Write();
        HistoD54E->Write();
        HistoD54F->Write();
        HistoD54G->Write();
        VnVsCentralityProtonHighRapidity->Write();
        VnVsCentralityDeuteronHighRapidity->Write();
        VnVsCentralityTritonHighRapidity->Write();
        FlowStrength->Write();
        FlowStrengthProton->Write();
        HistoD79->Write();
        HistoD80->Write();
        HistoD81->Write();
        HistoD82->Write();
        HistoD83->Write();
        HistoD84->Write();
        HistoD85->Write();
        HistoD86->Write();
        HistoD87->Write();
        HistoD88->Write();
        HistoD88A->Write();
        HistoD88B->Write();
        HistoD88C->Write();
        HistoD88D->Write();
        VnVsCentPtProtonHighRapidity->Write();
        VnVsCentPtDeuteronHighRapidity->Write();
        VnVsCentPtTritonHighRapidity->Write();
        HistoD89->Write();
        HistoD90->Write();
        HistoD91->Write();
        HistoD92->Write();
        HistoD93->Write();
        HistoD94->Write();
        HistoD95->Write();
        HistoD96->Write();
        HistoD97->Write();
        HistoD98->Write();
        HistoD99->Write();
        HistoD100->Write();
        HistoD101->Write();
        HistoD102->Write();
        HistoD103->Write();
        HistoD104->Write();
        HistoD105->Write();
        HistoD106->Write();
        HistoD107->Write();
        HistoD108->Write();
        HistoD109->Write();
        HistoD110->Write();
        HistoD111->Write();
        HistoD112->Write();
        HistoD113->Write();
        HistoD114->Write();
        HistoD115->Write();
        HistoD116->Write();
        HistoD117->Write();
        HistoD118->Write();
        HistoD119->Write();
        HistoD120->Write();
        HistoD121->Write();
        HistoD122->Write();
        HistoD123->Write();
        HistoD124->Write();
        HistoD125->Write();
        HistoD126->Write();
        HistoD127->Write();
        HistoD128->Write();
        HistoD129->Write();
        HistoD130->Write();
        VnVsPtProton0_00Through0_10->Write();
        VnVsPtProton0_10Through0_20->Write();
        VnVsPtProton0_20Through0_30->Write();
        VnVsPtProton0_30Through0_40->Write();
        VnVsPtDeuteron0_00Through0_10->Write();
        VnVsPtDeuteron0_10Through0_20->Write();
        VnVsPtDeuteron0_20Through0_30->Write();
        VnVsPtDeuteron0_30Through0_40->Write();
        VnVsPtTriton0_00Through0_10->Write();
        VnVsPtTriton0_10Through0_20->Write();
        VnVsPtTriton0_20Through0_30->Write();
        VnVsPtTriton0_30Through0_40->Write();
        VnOverAVsPtOverAProton0_00Through0_10->Write();
        VnOverAVsPtOverAProton0_10Through0_20->Write();
        VnOverAVsPtOverAProton0_20Through0_30->Write();
        VnOverAVsPtOverAProton0_30Through0_40->Write();
        VnOverAVsPtOverADeuteron0_00Through0_10->Write();
        VnOverAVsPtOverADeuteron0_10Through0_20->Write();
        VnOverAVsPtOverADeuteron0_20Through0_30->Write();
        VnOverAVsPtOverADeuteron0_30Through0_40->Write();
        VnOverAVsPtOverATriton0_00Through0_10->Write();
        VnOverAVsPtOverATriton0_10Through0_20->Write();
        VnOverAVsPtOverATriton0_20Through0_30->Write();
        VnOverAVsPtOverATriton0_30Through0_40->Write();
        VnVsYSymmetricProton->Write();
        VnVsYSymmetricProtonCentrality0_10->Write();
        VnVsYSymmetricProtonCentrality10_40->Write();
        VnVsYSymmetricProtonCentrality40_60->Write();
        VnVsPtProtonHighRapidityCentrality10_40->Write();
        VnVsPtDeuteronHighRapidityCentrality10_40->Write();
        VnVsPtTritonHighRapidityCentrality10_40->Write();        
 
            

        HistogramRootFile->Close();
        
        ResolutionFile->Close();
        
        TPCEfficiencyFile->Close();
        ToFEfficiencyFile->Close();
        TPCEfficiencyFileDandT->Close();
        
        delete HistoD89;
        delete HistoD90;
        delete HistoD91;
        delete HistoD92;
        delete HistoD93;
        delete HistoD94;
        delete HistoD95;
        delete HistoD96;
        delete HistoD97;
        delete HistoD98;
        delete HistoD99;
        delete HistoD100;
        delete HistoD101;
        delete HistoD102;
        delete HistoD103;
        delete HistoD104;
        delete HistoD105;
        delete HistoD106;
        delete HistoD107;
        delete HistoD108;
        delete HistoD109;
        delete HistoD110;
        delete HistoD111;
        delete HistoD112;
        delete HistoD113;
        delete HistoD114;
        delete HistoD115;
        delete HistoD116;
        delete HistoD117;
        delete HistoD118;
        delete HistoD119;
        delete HistoD120;
        delete HistoD121;
        delete HistoD122;
        delete HistoD123;
        delete HistoD124;
        delete HistoD125;
        delete HistoD126;
        delete HistoD127;
        delete HistoD128;
        delete HistoD129;
        delete HistoD130;
        delete VnVsYSymmetricProton;
        delete VnVsYSymmetricProtonCentrality0_10;
        delete VnVsYSymmetricProtonCentrality10_40;
        delete VnVsYSymmetricProtonCentrality40_60;
        delete VnVsPtProtonHighRapidityCentrality10_40;
        delete VnVsPtDeuteronHighRapidityCentrality10_40;
        delete VnVsPtTritonHighRapidityCentrality10_40;  
    }

    
   
    if(RunIteration == 1)
    {delete EventCheck;
        delete h2_zd_vs_mom;
        delete h2_zt_vs_mom;
        delete MomentumDistributionBischel;
        delete ZDeuteronDistribution;
        delete ZTritonDistribution;
        for(int i = 0; i < 16; i++)
        {
            delete HistoInnerEPDQxRaw[i];
            delete HistoInnerEPDQyRaw[i];
            delete HistoOuterEPDQxRaw[i];
            delete HistoOuterEPDQyRaw[i];
            delete HistoOuterTPCQxRaw[i];
            delete HistoOuterTPCQyRaw[i];
        }
        for(int i = 0; i < 16; i++)
        {    
            delete HistoInnerEPDQxRawByRun[i];
            delete HistoInnerEPDQyRawByRun[i];
            delete HistoOuterEPDQxRawByRun[i];
            delete HistoOuterEPDQyRawByRun[i];
            delete HistoOuterTPCQxRawByRun[i];
            delete HistoOuterTPCQyRawByRun[i];
        }
        delete RunCount;
        delete ZVertexValues;
        delete RVertexValues;
        delete DCAValues;
        delete NHitsValues;
        delete NHitsdEdxValues;
        delete NHitsFitOverNHitsPossValues;
        delete pVx;
        delete pVy;
        delete pVz;
        delete pPt;
        delete pEta;
        delete HitCountOuterEPD;
        delete Centralities;
        delete CentralitiesNineToFifteenOuterEPDHitsOnly;
        delete HistoDA;
        delete HistoDB;
        delete HistoD0;
        delete HistoD1;
        delete HistoD2;
        delete HistoD3;
        delete HistoD4;
        delete HistoD4A;
        delete HistoD5;
        delete HistoD6;
        delete HistoD7;
        delete HistoD8;
        delete HistoD9;
        delete HistoD10;
        delete HistoD11;
        delete HistoD12;
        delete HistoD13;
        delete HistoD14;
        delete HistoD15;
        delete HistoD16;
        delete HistoD17;
        delete HistoD18;
        delete HistoD19;
        delete HistoD20;
        delete HistoD21;
        delete HistoD22;
        delete HistoD23;
        delete HistoD24;
        delete HistoD25;
        delete HistoD26;
        delete HistoD27;
        delete HistoD27A;
        delete HistoD27B;
        delete HistoD28;
        delete HistoD29;
        delete HistoD30;
        delete HistoD31;
        delete HistoD32;
        delete HistoD32A;
        delete HistoD32B;
        for(int i = 0; i < 16; i++)
        { 
            delete HistoD33[i];
            delete HistoD36[i];
            delete HistoD39[i];
        }
        delete InvariantMassesLambda;
        delete InvariantMassesKShort;
        delete LambdaAcceptance;
        delete KShortAcceptance;
        delete ProtonMultiplicity;
        delete PionPlusMultiplicity;
        delete PionMinusMultiplicity;
        delete EToFFlags;
        delete ProtonTPCDetected;
        delete ProtonTPCDetectedRapidity;
        delete KaonPlusTPCDetected;
        delete KaonPlusTPCDetectedRapidity;
        delete KaonMinusTPCDetected;
        delete KaonMinusTPCDetectedRapidity;
        delete PionPlusTPCDetected;
        delete PionPlusTPCDetectedRapidity;
        delete PionMinusTPCDetected;
        delete PionMinusTPCDetectedRapidity;
        delete DeuteronTPCDetected;
        delete TritonTPCDetected;
        delete ProtonToFDetected;
        delete ProtonToFDetectedRapidity;
        delete ProtonToFDetectedRapidityMSquaredCuts;
        delete ProtonEToFDetected;
        delete ProtonEToFDetectedRapidity;
        delete KaonPlusToFDetected;
        delete KaonPlusToFDetectedRapidity;
        delete KaonPlusToFDetectedRapidityMSquaredCuts;
        delete KaonPlusEToFDetected;
        delete KaonPlusEToFDetectedRapidity;
        delete KaonMinusToFDetected;
        delete KaonMinusToFDetectedRapidity;
        delete KaonMinusToFDetectedRapidityMSquaredCuts;
        delete KaonMinusEToFDetected;
        delete KaonMinusEToFDetectedRapidity;
        delete PionPlusToFDetected;
        delete PionPlusToFDetectedRapidity;
        delete PionPlusToFDetectedRapidityMSquaredCuts;
        delete PionPlusEToFDetected;
        delete PionPlusEToFDetectedRapidity;
        delete PionMinusToFDetected;
        delete PionMinusToFDetectedRapidity;
        delete PionMinusToFDetectedRapidityMSquaredCuts;
        delete PionMinusEToFDetected;
        delete PionMinusEToFDetectedRapidity;
        delete DeuteronToFDetected;
        delete DeuteronEToFDetected;
        delete TritonToFDetected;
        delete TritonEToFDetected;
        delete AllTracksToFDetected;
        delete GlobalPt;
        delete GlobalEta;
        delete GlobalPhi;
        delete GlobalPtProton;
        delete GlobalEtaProton;
        delete GlobalPtPionPlus;
        delete GlobalEtaPionPlus;
        delete GlobalPtPionMinus;
        delete GlobalEtaPionMinus;
        delete GlobaldEdxVsP;
        delete MSquaredBToF;
        delete MSquaredEToF;
        delete KaonPlusPtOutliersEta;
        delete KaonPlusPtOutliersMSquared;
        delete PionPlusPtOutliersEta;
        delete PionPlusPtOutliersMSquared;
    }
   
    
    
    if(RunIteration == 2)
    {
        for(int i = 0; i < 16; i++)
        {
            delete HistoInnerEPDQxRecentered[i];
            delete HistoInnerEPDQyRecentered[i];
            delete HistoOuterEPDQxRecentered[i];
            delete HistoOuterEPDQyRecentered[i];
            delete HistoOuterTPCQxRecentered[i];
            delete HistoOuterTPCQyRecentered[i];
        }
        for(int i = 0; i < 16; i++)
        {
            delete HistoInnerEPDSineAverages[i];
            delete HistoInnerEPDCosineAverages[i];
            delete HistoOuterEPDSineAverages[i];
            delete HistoOuterEPDCosineAverages[i];
            delete HistoOuterTPCSineAverages[i];
            delete HistoOuterTPCCosineAverages[i];
        }
        for(int i = 0; i < 16; i++)
        {
            delete HistoD34[i];
            delete HistoD37[i];
            delete HistoD40[i];
        }
    }
  
    
    if(RunIteration == 3)
    {
        for(int i = 0; i < 16; i++)
        {    
            delete HistoD35[i];
            delete HistoD38[i];
            delete HistoD41[i];
        }
        delete HistoD51;
        delete HistoD52;
        delete HistoD53;
    }
    
    
    if(RunIteration == 4)
    {
        delete EventCheck;
        delete OverallTrackCheckNoCuts;
        delete OverallTrackCheckQACuts;
        delete ProtonTrackCheck;
        delete MostlyGoodProtonTrackCheck;
        delete GoodProtonTrackCheck;
        delete KaonPlusTrackCheck;
        delete MostlyGoodKaonPlusTrackCheck;
        delete GoodKaonPlusTrackCheck;
        delete KaonMinusTrackCheck;
        delete MostlyGoodKaonMinusTrackCheck;
        delete GoodKaonMinusTrackCheck;
        delete PionPlusTrackCheck;
        delete MostlyGoodPionPlusTrackCheck;
        delete GoodPionPlusTrackCheck;
        delete PionMinusTrackCheck;
        delete MostlyGoodPionMinusTrackCheck;
        delete GoodPionMinusTrackCheck;
        delete DeuteronTrackCheck;
        delete MostlyGoodDeuteronTrackCheck;
        delete GoodDeuteronTrackCheck;
        delete TritonTrackCheck;
        delete MostlyGoodTritonTrackCheck;
        delete GoodTritonTrackCheck;
        delete TrackMultiplicity;
        delete OverallTrackCheckIDedAsAny;
        delete HistoDC;
        delete HistoDD;
        delete HistoDE;
        delete HistoD44C;
        delete HistoD47B;
        delete HistoD47C;
        delete HistoD50B;
        delete HistoD50C;
        delete HistoD50D;
        delete HistoD50E;
        delete HistoD54A;
        delete HistoD54B;
        delete HistoD54C;
        delete HistoD54D;
        delete HistoD54E;
        delete HistoD54F;
        delete HistoD54G;
        delete VnVsCentralityProtonHighRapidity;
        delete VnVsCentralityDeuteronHighRapidity;
        delete VnVsCentralityTritonHighRapidity;
        delete FlowStrength;
        delete FlowStrengthProton;
        delete HistoD79;
        delete HistoD80;
        delete HistoD81;
        delete HistoD82;
        delete HistoD83;
        delete HistoD84;
        delete HistoD85;
        delete HistoD86;
        delete HistoD87;
        delete HistoD88;
        delete HistoD88A;
        delete HistoD88B;
        delete HistoD88C;
        delete HistoD88D;
        delete VnVsCentPtProtonHighRapidity;
        delete VnVsCentPtDeuteronHighRapidity;
        delete VnVsCentPtTritonHighRapidity;
        delete VnOverAVsPtOverAProton0_00Through0_10;
        delete VnOverAVsPtOverAProton0_10Through0_20;
        delete VnOverAVsPtOverAProton0_20Through0_30;
        delete VnOverAVsPtOverAProton0_30Through0_40;
        delete VnOverAVsPtOverADeuteron0_00Through0_10;
        delete VnOverAVsPtOverADeuteron0_10Through0_20;
        delete VnOverAVsPtOverADeuteron0_20Through0_30;
        delete VnOverAVsPtOverADeuteron0_30Through0_40;
        delete VnOverAVsPtOverATriton0_00Through0_10;
        delete VnOverAVsPtOverATriton0_10Through0_20;
        delete VnOverAVsPtOverATriton0_20Through0_30;
        delete VnOverAVsPtOverATriton0_30Through0_40;
    }
    
    return kStOK;
}



Int_t TreeAnalyzer::Init()
{
    std::vector<int> RunIDs {0, 79020,79021,79022,78002,78003,78004,78005,78006,78007,78008,78009,78010,78011,78012,78013,77002,77003,77004,77005,77006,77007,77008,77012,77013,77014,76001,76002,76003,76004,76005,76006,76007,76008,76009,76011,76012,75001,75002,75003,75004,75005,75006,75007,75008,75010,75011,75013,75031,75032,74002,74003,74004,74005,74006,74007,74010,74011,74012,74013,74014,74018,74019,74046,74047,74048,74049,74050,74054,74055,74056,74057,74058,74059,74060,74061,74062,73001,73002,73003,73004,73005,73006,73009,73010,73011,73012,73013,73014,73015,73016,73017,73018,73019,73020,73023,73024,73025,73026,73027,73028,73029,73030,73031,73032,73033,73034,73035,72001,72002,72003,72004,72005,72006,72007,72008,72009,72010,72022,72024,72025,71021,71022,71023,71024,71025,71026,71027,71028,71029,71030,71031,71032,71033,70001,70002,70003,70004,70005,70006,70007,70008,70009,70014,70015,70016,70017,70018,70019,70020,70021,70022,69001,69002,69003,69004,69005,69006,69007,69008,69009,69010,69011,69018,69022,69023,68003,68004,68005,68006,68007,68008,68009,68010,68015,67001,67002,67003,67004,67005,67006,67007,67008,67009,67010,67011,67012,67016,67017,67021,67022,67023,67024,67025,67027,67028,67029,66001,66002,66003,66004,66005,66006,66009,66010,66013,66014,66015,66016,66017,66018,66019,66020,66023,66024,66026,66028,66029,66030,66031,66034,66035,66036,66037,66038,66039,65001,65002,65003,65004,65005,65006,65007,65008,65009,65010,65012,65013,65014,65015,65016,65017,65018,65019,65021,65024,65025,65026,65027,65028,65029,65031,65032,65033,65034,65035,64001,64002,64003,64004,64005,64006,64007,64008,64009,64010,64011,64012,64013,64014,64015,64016,64017,64018,64019,64022,64024,64025,64026,64027,64028,64029,64030,64031,64032,64033,63002,63003,63004,63005,63006,63007,63008,63009,63010,63011,63012,63013,63014,63015,63016,63017,63018,63019,63020,63026,63027,63028,63029,63030,63031,63032,63034,63035,63036,62001,62003,62006,62007,62008,62009,62015,62018,62019,62021,62022,62023,61001,61002,61003,61004,61005,61006,61009,61010,61012,61013,61014,61015,61016,61018,61019,61020,61023,61024,61025,61026,61027,61028,61029,61030,61031,61032,61033,60001,60002,60003,60004,60005,60006,60007,60008,60009,60010,60011,60012,60013,60014,60015,60016,60017,60018,60019,60020,60021,60022,60024,60025,60026,60027,60028,60029,60030,60031,60032,60046,60047,60048,60049,60050,60051,60052,60053,59001,59003,59008,59009,59010,59011,59012,59013,59015,59051,59052,59053,58032,58033,58036,25001,25002,25003,25004,25005,25006,25007,25008,25009,25010,25011,24002,24003,24004,24005,24006,24007,24008,24011,24012,24013,24014,24018,24027,24028,24031,23001,23002,23003,23004,23005,23006,23007,23008,23009,23010,23011,23012,23013,23014,23015,23016,23017,23018,23020,23021,23025,23026,23027,23028,23030,23031,23032,23034,23035,23037,23038,23040,23041,22001,22002,22003,22004,22005,22006,22007,22008,22009,22010,22011,22014,22016,22017,22018,22019,22020,22021,22024,22025,22026,22027,22028,22029,22031,22032,22034,22035,21033,21036,21037,21038,21039,21040,21041,21044,21045,21046,21048,21049,21050,21052,21053};


    
    
    const char* CentralityXLabels[16] = {"0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60", "60-65", "65-70", "70-75", "75-80"};
        
    std::string FirstPassString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramFirstPass" + Variation + ".root";
    char *FirstPassChar = &FirstPassString[0];
    
    std::string SecondPassString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramSecondPass" + Variation + ".root";
    char *SecondPassChar = &SecondPassString[0];
    
    std::string ThirdPassString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramThirdPass" + Variation + ".root";
    char *ThirdPassChar = &ThirdPassString[0];

    if(UsingModifiedBesselResolution)
    {
        if(nV == 1)
        {
            if(ifstream(ThirdPassChar).good())
            {
                RunIteration = 4;
            }
    
            else if(ifstream(SecondPassChar).good())
            {
                RunIteration = 3;
            }
    
            else if(ifstream(FirstPassChar).good())
            {
                RunIteration = 2;
            }
    
            else
            {
                RunIteration = 1;
            }
        }
        
        else
        {
            RunIteration = 4;
        }

        QVectorDirectoryNumber = 1;
    }

    else
    {
        if(ifstream(ThirdPassChar).good())
        {
            RunIteration = 4;
        }

        else if(ifstream(SecondPassChar).good())
        {
            RunIteration = 3;
        }

        else if(ifstream(FirstPassChar).good())
        {
            RunIteration = 2;
        }

        else
        {
            RunIteration = 1;
        }

        QVectorDirectoryNumber = nV;
    }
    
    
    // RunIteration = 1;
    

    
    
    if(RunIteration == 2)
    {
        std::string QVectorHistogramFirstString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(QVectorDirectoryNumber) + "Histograms/QVectorFirstPass" + Variation + ".root";
        char *QVectorHistogramFirstChar = &QVectorHistogramFirstString[0];

        QVectorHistogramFileFirst = TFile::Open(QVectorHistogramFirstChar, "READ");
    }

    if(RunIteration == 3)
    {
        std::string QVectorHistogramFirstString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(QVectorDirectoryNumber) + "Histograms/QVectorFirstPass" + Variation + ".root";
        char *QVectorHistogramFirstChar = &QVectorHistogramFirstString[0];

        QVectorHistogramFileFirst = TFile::Open(QVectorHistogramFirstChar, "READ");

        std::string QVectorHistogramSecondString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(QVectorDirectoryNumber) + "Histograms/QVectorSecondPass" + Variation + ".root";
        char *QVectorHistogramSecondChar = &QVectorHistogramSecondString[0];

        QVectorHistogramFileSecond = TFile::Open(QVectorHistogramSecondChar, "READ");
    }

    if(RunIteration == 4)
    {
        std::string QVectorHistogramFirstString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(QVectorDirectoryNumber) + "Histograms/QVectorFirstPass" + Variation + ".root";
        char *QVectorHistogramFirstChar = &QVectorHistogramFirstString[0];

        QVectorHistogramFileFirst = TFile::Open(QVectorHistogramFirstChar, "READ");

        std::string QVectorHistogramSecondString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(QVectorDirectoryNumber) + "Histograms/QVectorSecondPass" + Variation + ".root";
        char *QVectorHistogramSecondChar = &QVectorHistogramSecondString[0];

        QVectorHistogramFileSecond = TFile::Open(QVectorHistogramSecondChar, "READ");

        std::string ResolutionFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/R_" + std::to_string(nV) + std::to_string(nPsi) + "_" + Variation + ".root";
        const char* ResolutionFileChar = &ResolutionFileString[0];

        ResolutionFile = TFile::Open(ResolutionFileChar, "READ");

        TPCEfficiencyFile = TFile::Open("/star/u/mcgordon/VnFromEPD/Efficiencies/TPCEfficiency.root","READ");
        ToFEfficiencyFile = TFile::Open("/star/u/mcgordon/VnFromEPD/Efficiencies/ToFEfficiency.root","READ");
        TPCEfficiencyFileDandT = TFile::Open("/star/u/mcgordon/VnFromEPD/Efficiencies/TPCEfficiencyDandT.root","READ");
    }





    if(RunIteration >= 2)
    {
        for(int i = 0; i < 16; i++)
        {
            InnerEPDQxMeanHisto[i] = (TProfile*)QVectorHistogramFileFirst->Get(Form("InnerEPDQxRawByRun%d", i));
            InnerEPDQyMeanHisto[i] = (TProfile*)QVectorHistogramFileFirst->Get(Form("InnerEPDQyRawByRun%d", i));
            OuterEPDQxMeanHisto[i] = (TProfile*)QVectorHistogramFileFirst->Get(Form("OuterEPDQxRawByRun%d", i));
            OuterEPDQyMeanHisto[i] = (TProfile*)QVectorHistogramFileFirst->Get(Form("OuterEPDQyRawByRun%d", i));
            OuterTPCQxMeanHisto[i] = (TProfile*)QVectorHistogramFileFirst->Get(Form("OuterTPCQxRawByRun%d", i));
            OuterTPCQyMeanHisto[i] = (TProfile*)QVectorHistogramFileFirst->Get(Form("OuterTPCQyRawByRun%d", i));
        }

        // InnerEPDQxMean = InnerEPDQxMeanHisto->GetMean();
        // InnerEPDQyMean = InnerEPDQyMeanHisto->GetMean();
        // OuterEPDQxMean = OuterEPDQxMeanHisto->GetMean();
        // OuterEPDQyMean = OuterEPDQyMeanHisto->GetMean();
        // OuterTPCQxMean = OuterTPCQxMeanHisto->GetMean();
        // OuterTPCQyMean = OuterTPCQyMeanHisto->GetMean();
    }

    if(RunIteration >= 3)
    {
        for(int i = 0; i < 16; i++)
        {
                InnerEPDSineAverageProfile[i] = (TProfile2D*)QVectorHistogramFileSecond->Get(Form("InnerEPDSineAverages%d", i));
                InnerEPDCosineAverageProfile[i] = (TProfile2D*)QVectorHistogramFileSecond->Get(Form("InnerEPDCosineAverages%d", i));
                OuterEPDSineAverageProfile[i] = (TProfile2D*)QVectorHistogramFileSecond->Get(Form("OuterEPDSineAverages%d", i));
                OuterEPDCosineAverageProfile[i] = (TProfile2D*)QVectorHistogramFileSecond->Get(Form("OuterEPDCosineAverages%d", i));
                OuterTPCSineAverageProfile[i] = (TProfile2D*)QVectorHistogramFileSecond->Get(Form("OuterTPCSineAverages%d", i));
                OuterTPCCosineAverageProfile[i] = (TProfile2D*)QVectorHistogramFileSecond->Get(Form("OuterTPCCosineAverages%d", i));
        }
    }
    
   
  
    
    //Histograms
    
    //First Pass Histograms


    if(RunIteration == 1)
    {
        for(int i = 0; i < 16; i++)
        {
            HistoInnerEPDQxRawByRun[i] = new TProfile(Form("InnerEPDQxRawByRun%d", i), Form("Qx Raw for Inner EPD, Centrality Class %d; Event Index; Q_{x}", i), RunIDs.size() - 1, 1, RunIDs.size());
            HistoInnerEPDQyRawByRun[i] = new TProfile(Form("InnerEPDQyRawByRun%d", i), Form("Qy Raw for Inner EPD, Centrality Class %d; Event Index; Q_{y}", i), RunIDs.size() - 1, 1, RunIDs.size());
            HistoOuterEPDQxRawByRun[i] = new TProfile(Form("OuterEPDQxRawByRun%d", i), Form("Qx Raw for Outer EPD, Centrality Class %d; Event Index; Q_{x}", i), RunIDs.size() - 1, 1, RunIDs.size());
            HistoOuterEPDQyRawByRun[i] = new TProfile(Form("OuterEPDQyRawByRun%d", i), Form("Qy Raw for Inner EPD, Centrality Class %d; Event Index; Q_{y}", i), RunIDs.size() - 1, 1, RunIDs.size());
            HistoOuterTPCQxRawByRun[i] = new TProfile(Form("OuterTPCQxRawByRun%d", i), Form("Qx Raw for Outer TPC, Centrality Class %d; Event Index; Q_{x}", i), RunIDs.size() - 1, 1, RunIDs.size());
            HistoOuterTPCQyRawByRun[i] = new TProfile(Form("OuterTPCQyRawByRun%d", i), Form("Qy Raw for Outer TPC, Centrality Class %d; Event Index; Q_{y}", i), RunIDs.size() - 1, 1, RunIDs.size());
        }
    }

    if(RunIteration == 1)
    {
        for(int i = 0; i < 16; i++)
        {
            HistoInnerEPDQxRaw[i] = new TH1D(Form("InnerEPDQxRaw%d", i), "Qx Raw for Inner EPD; Qx; Events", 250, -QBounds, QBounds);
            HistoInnerEPDQyRaw[i] = new TH1D(Form("InnerEPDQyRaw%d", i), "Qy Raw for Inner EPD; Qy; Events", 250, -QBounds, QBounds);
            HistoOuterEPDQxRaw[i] = new TH1D(Form("OuterEPDQxRaw%d", i), "Qx Raw for Outer EPD; Qx; Events", 250, -QBounds, QBounds);
            HistoOuterEPDQyRaw[i] = new TH1D(Form("OuterEPDQyRaw%d", i), "Qy Raw for Inner EPD; Qy; Events", 250, -QBounds, QBounds);
            HistoOuterTPCQxRaw[i] = new TH1D(Form("OuterTPCQxRaw%d", i), "Qx Raw for Outer TPC; Qx; Events", 250, -QBounds, QBounds);
            HistoOuterTPCQyRaw[i] = new TH1D(Form("OuterTPCQyRaw%d", i), "Qy Raw for Outer TPC; Qy; Events", 250, -QBounds, QBounds);
        }
    }
    

    ZVertexValues = new TH1D("ZVertexValues", "ZVertex Values; Z Vertex (cm); Events", 120, 197, 203);
    RVertexValues = new TH1D("RVertexValues", "RVertex Values; R Vertex (cm); Events", 120, 0, 5);
    DCAValues = new TH1D("DCAValues", "DCA Values; DCA (cm); Tracks", 80, 0, 4);
    NHitsValues = new TH1D("NHitsValues", "NHits Values; NHits; Tracks", 100, 0, 100);
    NHitsdEdxValues = new TH1D("NHitsdEdxValues", "NHitsdEdx Values; NHitsdEdx; Tracks", 90, 5, 100);
    NHitsFitOverNHitsPossValues = new TH1D("NHitsFitOverNHitsPossValues", "NHitsFitOverNHitsPoss Values; NHitsFitOverNHitsPoss; Tracks", 70, 0.3, 1);
    

    
    pVx = new TProfile("pVx", "Vx for Primary Tracks; Run Index; <Vx>", RunIDs.size() - 1, 1, RunIDs.size());
    pVy = new TProfile("pVy", "Vy for Primary Tracks; Run Index; <Vy>", RunIDs.size() - 1, 1, RunIDs.size());
    pVz = new TProfile("pVz", "Vz for Primary Tracks; Run Index; <Vz>", RunIDs.size() - 1, 1, RunIDs.size());
    pPt = new TProfile("pPt", "Pt for Primary Tracks; Run Index; <Pt> (GeV)", RunIDs.size() - 1, 1, RunIDs.size());
    pEta = new TProfile("pEta", "Eta for Primary Tracks; Run Index; <Eta>", RunIDs.size() - 1, 1, RunIDs.size());
    

    
    HitCountOuterEPD = new TH1D("HitCountOuterEPD","Outer EPD Hit Count; # of Hits; Count", 100, 0, 100);
    
    Centralities = new TH1D("Centralities", "Centralities; Centrality; Count", 16, 0, 16);
    
    for (int index = 1; index < Centralities->GetNbinsX() + 1; index++)
    {
        Centralities->GetXaxis()->SetBinLabel(index, CentralityXLabels[index - 1]);
    }

    CentralitiesNineToFifteenOuterEPDHitsOnly = new TH1D("CentralitiesNineToFifteenOuterEPDHitsOnly", "Centralities for Events with 9 <= OuterEPDHits < 16; Centrality; Count", 16, 0, 16);
    
    for (int index = 1; index < CentralitiesNineToFifteenOuterEPDHitsOnly->GetNbinsX() + 1; index++)
    {
        CentralitiesNineToFifteenOuterEPDHitsOnly->GetXaxis()->SetBinLabel(index, CentralityXLabels[index - 1]);
    }



    HistoDA = new TH1F("DataNSigmaProtonAll", "All NSigmaProton Values; NSigmaProton; Events", 10, -5, 5);
    HistoDA->Sumw2();
    
    HistoDB = new TH1F("DataNSigmaProtonUsed", "Used NSigmaProton Values; NSigmaProton; Events", 10, -5, 5);
    HistoDB->Sumw2();
    
    
    
    h2_zd_vs_mom = new TH2D("h2_zd_vs_mom", "Z_{d} vs Momentum;|p| (GeV/c);z_{d}", 50, 0.0, 5.0, 200, -1.0, 1.0);//140, -0.7, 0.7);
    
    h2_zt_vs_mom  = new TH2D("h2_zt_vs_mom", "Z_{t} vs Momentum;|p| (GeV/c);z_{t}", 50, 0.0, 5.0, 200, -1.0, 1.0);//140, -0.7, 0.7);

    MomentumDistributionBischel = new TH1D("MomDistBischel", "Momentum Distribution for Bischel Tracks;|p| (GeV/c);Counts", 50, 0.0, 5.0);
    ZDeuteronDistribution = new TH1D("ZDeuteronDist", "Bischel Z Distribution for Deuterons;zd;Counts", 140, -0.7, 0.7);
    ZTritonDistribution = new TH1D("ZTritonDist", "Bischel Z Distribution for Tritons;zt;Counts", 140, -0.7, 0.7);
    
    
    
    
    HistoD0 = new TH2F("DataVxVy","Target Vx and Vy; Vx; Vy", 500, -5, 5, 500, -5, 5);
    HistoD0->Sumw2();
    
    HistoD1 = new TH1F("DataPt", "Pt; Pt (GeV); Events", 500, 0, 2);
    HistoD1->Sumw2();

    HistoD2 = new TH1F("DataEta", "Eta; Eta; Events", 500, -3, 0);
    HistoD2->Sumw2();

    HistoD3 = new TH2D("DataPtVsEta", "Pt vs #eta for All Tracks; #eta; Pt (GeV)", 300, -3, 0, 600, 0, 6);
    HistoD3->Sumw2();

    AllTracksToFDetected = new TH2D("AllTracksToFDetected", "Pt vs #eta for ToF Tracks; Eta; Pt (GeV)", 300, -3, 0, 600, 0, 6);
    AllTracksToFDetected->Sumw2();

    HistoD4 = new TH2F("DataMSquaredVsQP", "m^2 vs q|p|; q|p| (GeV); m^2 (GeV^2)", 200, -4, 4, 200, -0.1, 10);
    HistoD4->Sumw2();

    HistoD4A = new TH2F("DataMSquaredVsQPZoomed", "m^2 vs q|p|; q|p| (GeV); m^2 (GeV^2)", 200, -4, 4, 200, -0.1, 0.15);
    HistoD4A->Sumw2();

    HistoD5 = new TH1F("DataYProton", "Y for Protons; y_{CM}; Events", 500, -1, 1);
    HistoD5->Sumw2();

    HistoD6 = new TH1F("DataYKaon", "Y for Kaons; y_{CM}; Events", 500, -1, 1);
    HistoD6->Sumw2();

    HistoD7 = new TH1F("DataYPion", "Y for Pions; y_{CM}; Events", 500, -1, 1);
    HistoD7->Sumw2();

    HistoD8 = new TH1F("DataPtProton", "Pt for Protons, m^2 cut only; Pt (GeV); Events", 500, 0, 2);
    HistoD8->Sumw2();

    HistoD9 = new TH1F("DataPtKaon", "Pt for Kaons, m^2 cut only; Pt (GeV); Events", 500, 0, 2);
    HistoD9->Sumw2();

    HistoD10 = new TH1F("DataPtPion", "Pt for Pions, m^2 cut only; Pt (GeV); Events", 500, 0, 2);
    HistoD10->Sumw2();

    HistoD11 = new TH1F("DataMultiplicity", "Multiplicity; Multiplicity; Events", 200, 0, 200);
    HistoD11->Sumw2();

    HistoD12 = new TH2F("DatadEdxVsP", "dE/dx vs p; p (GeV); dE/dx (Gev/fm)", 200, 0, 2, 200, 0, 10);
    HistoD12->Sumw2();

    HistoD13 = new TH2F("DatadEdxVsPPion", "dE/dx vs p for Pions; p (GeV); dE/dx (Gev/fm)", 200, 0, 2, 200, 0, 10);
    HistoD13->Sumw2();

    HistoD14 = new TH2F("DatadEdxVsPKaon", "dE/dx vs p for Kaons; p (GeV); dE/dx (Gev/fm)", 200, 0, 2, 200, 0, 10);
    HistoD14->Sumw2();

    HistoD15 = new TH2F("DatadEdxVsPProton", "dE/dx vs p for Protons; p (GeV); dE/dx (Gev/fm)", 200, 0, 2, 200, 0, 10);
    HistoD15->Sumw2();

    HistoD16 = new TH2F("DatadEdxVsPDeuteron", "dE/dx vs p for Deuterons; p (GeV); dE/dx (Gev/fm)", 200, 0, 2, 200, 0, 10);
    HistoD16->Sumw2();

    HistoD17 = new TH2F("DatadEdxVsPTriton", "dE/dx vs p for Tritons; p (GeV); dE/dx (Gev/fm)", 200, 0, 2, 200, 0, 10);
    HistoD17->Sumw2();

    HistoD18 = new TH2F("DataMSquaredVsQPProton", "m^2 vs q|p| for Protons; q|p| (GeV); m^2 (GeV^2)", 200, -4, 4, 200, -0.1, 1.5);
    HistoD18->Sumw2();

    HistoD19 = new TH2F("DataMSquaredVsQPKaon", "m^2 vs q|p| for Kaons; q|p| (GeV); m^2 (GeV^2)", 200, -4, 4, 200, -0.1, 1.5);
    HistoD19->Sumw2();

    HistoD20 = new TH2F("DataMSquaredVsQPPion", "m^2 vs q|p| for Pions; q|p| (GeV); m^2 (GeV^2)", 200, -4, 4, 200, -0.1, 1.5);
    HistoD20->Sumw2();

    HistoD21 = new TH1F("DataPtProtonBothCuts", "Pt for Protons, m^2 and dE/dx cuts; Pt (GeV); Events", 500, 0, 2);
    HistoD21->Sumw2();

    HistoD22 = new TH1F("DataPtKaonBothCuts", "Pt for Kaons, m^2 and dE/dx cuts; Pt (GeV); Events", 500, 0, 2);
    HistoD22->Sumw2();

    HistoD23 = new TH1F("DataPtPionBothCuts", "Pt for Pions, m^2 and dE/dx cuts; Pt (GeV); Events", 500, 0, 2);
    HistoD23->Sumw2();

    HistoD24 = new TH2F("DataNSigmaPrVsQPProton", "NSigmaPr vs q|p| for Protons; q|p| (GeV); NSigmaPr", 200, -4, 4, 200, -3, 3);
    HistoD24->Sumw2();

    HistoD25 = new TH2F("DataNSigmaKaVsQPKaon", "NSigmaKa vs q|p| for Kaons; q|p| (GeV); NSigmaKa", 200, -4, 4, 200, -3, 3);
    HistoD25->Sumw2();

    HistoD26 = new TH2F("DataNSigmaPiVsQPPion", "NSigmaPi vs q|p| for Pions; Pt (GeV); NSigmaPi", 200, -4, 4, 200, -3, 3);
    HistoD26->Sumw2();

    HistoD27 = new TH2F("DataPtVsYProton", "Pt vs Y for Protons; y_{CM}; Pt (Gev)", 200, -1, 1, 200, 0, 6);
    HistoD27->Sumw2();
    
    HistoD27A = new TH2F("DataPtVsYDeuteron", "Pt vs Y for Deuterons; y_{CM}; Pt (Gev)", 200, -1, 1, 200, 0, 6);
    HistoD27A->Sumw2();
    
    HistoD27B = new TH2F("DataPtVsYTriton", "Pt vs Y for Tritons; y_{CM}; Pt (Gev)", 200, -1, 1, 200, 0, 6);
    HistoD27B->Sumw2();

    HistoD28 = new TH2F("DataPtVsYKaonPlus", "Pt vs Y for K^{+}; y_{CM}; Pt (Gev)", 200, -1, 1, 200, 0, 2.5);
    HistoD28->Sumw2();

    HistoD29 = new TH2F("DataPtVsYKaonMinus", "Pt vs Y for K^{-}; y_{CM}; Pt (Gev)", 500, -1, 1, 200, 0, 2.5);
    HistoD29->Sumw2();

    HistoD30 = new TH2F("DataPtVsYPionPlus", "Pt vs Y for #pi^{+}; y_{CM}; Pt (Gev)", 200, -1, 1, 200, 0, 2.5);
    HistoD30->Sumw2();

    HistoD31 = new TH2F("DataPtVsYPionMinus", "Pt vs Y for #pi^{-}; y_{CM}; Pt (Gev)", 200, -1, 1, 200, 0, 2.5);
    HistoD31->Sumw2();

    HistoD32 = new TH1F("DataPhiTPC", "TPC Phi; Phi; Events", 500, -3.5, 3.5);
    HistoD32->Sumw2();

    HistoD32A = new TH1F("DataPhiEPD", "EPD Phi; Phi; Events", 500, -3.5, 3.5);
    HistoD32A->Sumw2();

    HistoD32B = new TH2F("DataEPDEastRingVsEta", "EPD East Ring vs Eta; Eta; Ring Number", 200, -6, -1, 200, 0.5, 16.5);
    HistoD32B->Sumw2();

    for(int i = 0; i < 16; i++)
    {
        HistoD33[i] = new TH1F(Form("DataPsi1RawInnerEPD%d", i), Form("Reaction Plane Angle (Raw), #Psi_{1}, Inner EPD, Centrality Class %d; #Psi_{1}; Events", i), 500, -3.5, 3.5);
        HistoD36[i] = new TH1F(Form("DataPsi1RawOuterEPD%d", i), Form("Reaction Plane Angle (Raw), #Psi_{1}, Outer EPD, Centrality Class %d; #Psi_{1}; Events", i), 500, -3.5, 3.5);
        HistoD39[i] = new TH1F(Form("DataPsi1RawOuterTPC%d", i), Form("Reaction Plane Angle (Raw), #Psi_{1}, Outer TPC, Centrality Class %d; #Psi_{1}; Events", i), 500, -3.5, 3.5);
    }
        
    InvariantMassesLambda = new TH1F("InvariantMassesLambda", "p - #pi^{-} Inavariant Masses; InvariantMasses; Count", 500, 1.08, 1.16);
    InvariantMassesLambda->Sumw2();

    InvariantMassesKShort = new TH1F("InvariantMassesKShort", "#pi^{+} - #pi^{-} Inavariant Masses; InvariantMasses; Count", 500, 0.3, 0.8);
    InvariantMassesKShort->Sumw2();

    LambdaAcceptance = new TH2F("DataPtVsYLambda", "Pt vs Y for #Lambda^{0}; y_{CM}; Pt (Gev)", 200, -1, 1, 200, 0, 2.5);
    LambdaAcceptance->Sumw2();

    KShortAcceptance = new TH2F("DataPtVsYKShort", "Pt vs Y for K_{S}; y_{CM}; Pt (Gev)", 200, -1, 1, 200, 0, 2.5);
    KShortAcceptance->Sumw2();

    ProtonMultiplicity = new TH1F("ProtonMultiplicity", "Proton Multiplicity; # of Protons; Count", 101, -1, 100);
    ProtonMultiplicity->Sumw2();

    PionPlusMultiplicity = new TH1F("PionPlusMultiplicity", "#pi^{+} Multiplicity; # of #pi^{+}; Count", 6, -1, 5);
    PionPlusMultiplicity->Sumw2(); 

    PionMinusMultiplicity = new TH1F("PionMinusMultiplicity", "#pi^{-} Multiplicity; # of #pi^{-}; Count", 6, -1, 5);
    PionMinusMultiplicity->Sumw2();

    EToFFlags = new TH1D("EToFFlags", "EToF Flags; Flag Number; Count", 600, -300, 300);
    EToFFlags->Sumw2();

    ProtonTPCDetected = new TH2D("ProtonTPCDetected", "Number of Proton Tracks Detected By TPC; #eta; P_{T} (GeV)", 300, -3, 0, 600, 0, 6);
    ProtonTPCDetected->Sumw2();

    ProtonTPCDetectedRapidity = new TH2D("ProtonTPCDetectedRapidity", "Number of Proton Tracks Detected By TPC; y_{cm}; P_{T} (GeV)", 500, -2.5, 2.5, 600, 0, 6);
    ProtonTPCDetectedRapidity->Sumw2();

    KaonPlusTPCDetected = new TH2D("KaonPlusTPCDetected", "Number of K^{+} Tracks Detected By TPC; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    KaonPlusTPCDetected->Sumw2();

    KaonPlusTPCDetectedRapidity = new TH2D("KaonPlusTPCDetectedRapidity", "Number of K^{+} Tracks Detected By TPC; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonPlusTPCDetectedRapidity->Sumw2();
    
    KaonMinusTPCDetected = new TH2D("KaonMinusTPCDetected", "Number of K^{-} Tracks Detected By TPC; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    KaonMinusTPCDetected->Sumw2();

    KaonMinusTPCDetectedRapidity = new TH2D("KaonMinusTPCDetectedRapidity", "Number of K^{-} Tracks Detected By TPC; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonMinusTPCDetectedRapidity->Sumw2();
    
    PionPlusTPCDetected = new TH2D("PionPlusTPCDetected", "Number of #pi^{+} Tracks Detected By TPC; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    PionPlusTPCDetected->Sumw2();

    PionPlusTPCDetectedRapidity = new TH2D("PionPlusTPCDetectedRapidity", "Number of #pi^{+} Tracks Detected By TPC; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionPlusTPCDetectedRapidity->Sumw2();
    
    PionMinusTPCDetected = new TH2D("PionMinusTPCDetected", "Number of #pi^{-} Tracks Detected By TPC; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    PionMinusTPCDetected->Sumw2();

    PionMinusTPCDetectedRapidity = new TH2D("PionMinusTPCDetectedRapidity", "Number of #pi^{-} Tracks Detected By TPC; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionMinusTPCDetectedRapidity->Sumw2();

    DeuteronTPCDetected = new TH2D("DeuteronTPCDetected", "Number of Deuteron Tracks Detected By TPC; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    DeuteronTPCDetected->Sumw2();

    TritonTPCDetected = new TH2D("TritonTPCDetected", "Number of Triton Tracks Detected By TPC; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    TritonTPCDetected->Sumw2();

    ProtonToFDetected = new TH2D("ProtonToFDetected", "Number of Proton Tracks Detected By ToF; #eta; P_{T} (GeV)", 300, -3, 0, 600, 0, 6);
    ProtonToFDetected->Sumw2();

    ProtonToFDetectedRapidity = new TH2D("ProtonToFDetectedRapidity", "Number of Proton Tracks Detected By ToF; y_{cm}; P_{T} (GeV)", 500, -2.5, 2.5, 600, 0, 6);
    ProtonToFDetectedRapidity->Sumw2();

    ProtonToFDetectedRapidityMSquaredCuts = new TH2D("ProtonToFDetectedRapidityMSquaredCuts", "Number of Proton Tracks Detected By ToF with m^{2} Cuts; y_{cm}; P_{T} (GeV)", 500, -2.5, 2.5, 600, 0, 6);
    ProtonToFDetectedRapidityMSquaredCuts->Sumw2();

    ProtonEToFDetected = new TH2D("ProtonEToFDetected", "Number of Proton Tracks Detected By EToF; #eta; P_{T} (GeV)", 300, -3, 0, 600, 0, 6);
    ProtonEToFDetected->Sumw2();

    ProtonEToFDetectedRapidity = new TH2D("ProtonEToFDetectedRapidity", "Number of Proton Tracks Detected By EToF; y_{cm}; P_{T} (GeV)", 500, -2.5, 2.5, 600, 0, 6);
    ProtonEToFDetectedRapidity->Sumw2();
    
    KaonPlusToFDetected = new TH2D("KaonPlusToFDetected", "Number of K^{+} Tracks Detected By ToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    KaonPlusToFDetected->Sumw2();

    KaonPlusToFDetectedRapidity = new TH2D("KaonPlusToFDetectedRapidity", "Number of K^{+} Tracks Detected By ToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonPlusToFDetectedRapidity->Sumw2();

    KaonPlusToFDetectedRapidityMSquaredCuts = new TH2D("KaonPlusToFDetectedRapidityMSquaredCuts", "Number of K^{+} Tracks Detected By ToF with m^{2} Cuts; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonPlusToFDetectedRapidityMSquaredCuts->Sumw2();

    KaonPlusEToFDetected = new TH2D("KaonPlusEToFDetected", "Number of K^{+} Tracks Detected By EToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    KaonPlusEToFDetected->Sumw2();

    KaonPlusEToFDetectedRapidity = new TH2D("KaonPlusEToFDetectedRapidity", "Number of K^{+} Tracks Detected By EToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonPlusEToFDetectedRapidity->Sumw2();
    
    KaonMinusToFDetected = new TH2D("KaonMinusToFDetected", "Number of K^{-} Tracks Detected By ToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    KaonMinusToFDetected->Sumw2();

    KaonMinusToFDetectedRapidity = new TH2D("KaonMinusToFDetectedRapidity", "Number of K^{-} Tracks Detected By ToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonMinusToFDetectedRapidity->Sumw2();

    KaonMinusToFDetectedRapidityMSquaredCuts = new TH2D("KaonMinusToFDetectedRapidityMSquaredCuts", "Number of K^{-} Tracks Detected By ToF with m^{2} Cuts; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonMinusToFDetectedRapidityMSquaredCuts->Sumw2();

    KaonMinusEToFDetected = new TH2D("KaonMinusEToFDetected", "Number of K^{-} Tracks Detected By EToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    KaonMinusEToFDetected->Sumw2();

    KaonMinusEToFDetectedRapidity = new TH2D("KaonMinusEToFDetectedRapidity", "Number of K^{-} Tracks Detected By EToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonMinusEToFDetectedRapidity->Sumw2();
    
    PionPlusToFDetected = new TH2D("PionPlusToFDetected", "Number of #pi^{+} Tracks Detected By ToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    PionPlusToFDetected->Sumw2();

    PionPlusToFDetectedRapidity = new TH2D("PionPlusToFDetectedRapidity", "Number of #pi^{+} Tracks Detected By ToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionPlusToFDetectedRapidity->Sumw2();

    PionPlusToFDetectedRapidityMSquaredCuts = new TH2D("PionPlusToFDetectedRapidityMSquaredCuts", "Number of #pi^{+} Tracks Detected By ToF with m^{2} Cuts; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionPlusToFDetectedRapidityMSquaredCuts->Sumw2();

    PionPlusEToFDetected = new TH2D("PionPlusEToFDetected", "Number of #pi^{+} Tracks Detected By EToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    PionPlusEToFDetected->Sumw2();

    PionPlusEToFDetectedRapidity = new TH2D("PionPlusEToFDetectedRapidity", "Number of #pi^{+} Tracks Detected By EToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionPlusEToFDetectedRapidity->Sumw2();
    
    PionMinusToFDetected = new TH2D("PionMinusToFDetected", "Number of #pi^{-} Tracks Detected By ToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    PionMinusToFDetected->Sumw2();

    PionMinusToFDetectedRapidity = new TH2D("PionMinusToFDetectedRapidity", "Number of #pi^{-} Tracks Detected By ToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionMinusToFDetectedRapidity->Sumw2();

    PionMinusToFDetectedRapidityMSquaredCuts = new TH2D("PionMinusToFDetectedRapidityMSquaredCuts", "Number of #pi^{-} Tracks Detected By ToF with m^{2} Cuts; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionMinusToFDetectedRapidityMSquaredCuts->Sumw2();

    PionMinusEToFDetected = new TH2D("PionMinusEToFDetected", "Number of #pi^{-} Tracks Detected By EToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    PionMinusEToFDetected->Sumw2();

    PionMinusEToFDetectedRapidity = new TH2D("PionMinusEToFDetectedRapidity", "Number of #pi^{-} Tracks Detected By EToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionMinusEToFDetectedRapidity->Sumw2();

    DeuteronToFDetected = new TH2D("DeuteronToFDetected", "Number of Deuteron Tracks Detected By ToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    DeuteronToFDetected->Sumw2();

    DeuteronEToFDetected = new TH2D("DeuteronEToFDetected", "Number of Deuteron Tracks Detected By EToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    DeuteronEToFDetected->Sumw2();

    TritonToFDetected = new TH2D("TritonToFDetected", "Number of Triton Tracks Detected By ToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    TritonToFDetected->Sumw2();

    TritonEToFDetected = new TH2D("TritonEToFDetected", "Number of Triton Tracks Detected By EToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    TritonEToFDetected->Sumw2();

    GlobalPt = new TH1D("GlobalPt", "Pt of Global Tracks; Pt (GeV); Events", 500, 0, 2);
    GlobalPt->Sumw2();

    GlobalEta = new TH1D("GlobalEta", "Eta of Global Tracks; Eta; Events", 500, -3, 0);
    GlobalEta->Sumw2();

    GlobalPhi = new TH1D("GlobalPhi", "Phi of Global Tracks; Phi; Events", 500, -3.5, 3.5);
    GlobalPhi->Sumw2();

    GlobalPtProton = new TH1D("GlobalPtProton", "Pt of Global Protons; Pt (GeV); Events", 500, 0, 2);
    GlobalPtProton->Sumw2();

    GlobalEtaProton = new TH1D("GlobalEtaProton", "Eta of Global Protons; Eta; Events", 500, -3, 0);
    GlobalEtaProton->Sumw2();

    GlobalPtPionPlus = new TH1D("GlobalPtPionPlus", "Pt of Global #pi^{+}; Pt (GeV); Events", 500, 0, 2);
    GlobalPtPionPlus->Sumw2();

    GlobalEtaPionPlus = new TH1D("GlobalEtaPionPlus", "Eta of Global #pi^{+}; Eta; Events", 500, -3, 0);
    GlobalEtaPionPlus->Sumw2();

    GlobalPtPionMinus = new TH1D("GlobalPtPionMinus", "Pt of Global #pi^{-}; Pt (GeV); Events", 500, 0, 2);
    GlobalPtPionMinus->Sumw2();

    GlobalEtaPionMinus = new TH1D("GlobalEtaPionMinus", "Eta of Global #pi^{-}; Eta; Events", 500, -3, 0);
    GlobalEtaPionMinus->Sumw2();

    GlobaldEdxVsP = new TH2D("GlobaldEdxVsP", "dE/dx vs p for Global Tracks; p (GeV); dE/dx (Gev/fm)", 200, 0, 2, 200, 0, 10);
    GlobaldEdxVsP->Sumw2();

    MSquaredBToF = new TH1D("MSquaredBToF", "m^{2} for the Barrel ToF; m^{2}; Counts", 95, -0.5,9.0);
    MSquaredBToF->Sumw2();
    
    MSquaredEToF = new TH1D("MSquaredEToF", "m^{2} for the Endcap ToF; m^{2}; Counts", 95, -0.5,9.0);
    MSquaredEToF->Sumw2();

    KaonPlusPtOutliersEta = new TH1D("KaonPlusPtOutliersEta", "#eta for Pt Outliers for K^{+}; #eta; Counts", 300, -3, 0);
    KaonPlusPtOutliersEta->Sumw2();
    
    KaonPlusPtOutliersMSquared = new TH1D("KaonPlusPtOutliersMSquared", "m^{2} for for Pt Outliers K^{+}; m^{2}; Counts", 200, 0.15, 0.35);
    KaonPlusPtOutliersMSquared->Sumw2();
    
    PionPlusPtOutliersEta = new TH1D("PionPlusPtOutliersEta", "#eta for Pt Outliers for #pi^{+}; #eta; Counts", 300, -3, 0);
    PionPlusPtOutliersEta->Sumw2();
    
    PionPlusPtOutliersMSquared = new TH1D("PionPlusPtOutliersMSquared", "m^{2} for for Pt Outliers #pi^{+}; m^{2}; Counts", 200, -0.10, 0.10);
    PionPlusPtOutliersMSquared->Sumw2();


    
    
    //Second Pass Histograms

    for(int i = 0; i < 16; i++)
    {
        HistoInnerEPDQxRecentered[i] = new TH1D(Form("InnerEPDQxRecentered%d", i), "Qx Recentered for Inner EPD; Qx; Events", 250, -QBounds, QBounds);
        HistoInnerEPDQyRecentered[i] = new TH1D(Form("InnerEPDQyRecentered%d", i), "Qy Recentered for Inner EPD; Qy; Events", 250, -QBounds, QBounds);
        HistoOuterEPDQxRecentered[i] = new TH1D(Form("OuterEPDQxRecentered%d", i), "Qx Recentered for Outer EPD; Qx; Events", 250, -QBounds, QBounds);
        HistoOuterEPDQyRecentered[i] = new TH1D(Form("OuterEPDQyRecentered%d", i), "Qy Recentered for Outer EPD; Qy; Events", 250, -QBounds, QBounds);
        HistoOuterTPCQxRecentered[i] = new TH1D(Form("OuterTPCQxRecentered%d", i), "Qx Recentered for Outer TPC; Qx; Events", 250, -QBounds, QBounds);
        HistoOuterTPCQyRecentered[i] = new TH1D(Form("OuterTPCQyRecentered%d", i), "Qy Recentered for Outer TPC; Qy; Events", 250, -QBounds, QBounds);
    }
    

    
    
    if(RunIteration == 2)
    {
        for(int i = 0; i < 16; i++)
        {
            HistoInnerEPDSineAverages[i] = new TProfile2D(Form("InnerEPDSineAverages%d", i), Form("Inner EPD Sine Averages, Centrality Class %d; Run Index; j-index; Sine Correction Term", i), RunIDs.size() - 1, 1, RunIDs.size(), FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
            HistoInnerEPDCosineAverages[i] = new TProfile2D(Form("InnerEPDCosineAverages%d", i), Form("Inner EPD Cosine Averages, Centrality Class %d; Run Index; j-index; Cosine Correction Term", i), RunIDs.size() - 1, 1, RunIDs.size(), FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
            HistoOuterEPDSineAverages[i] = new TProfile2D(Form("OuterEPDSineAverages%d", i), Form("Outer EPD Sine Averages, Centrality Class %d; Run Index; j-index; Sine Correction Term", i), RunIDs.size() - 1, 1, RunIDs.size(), FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
            HistoOuterEPDCosineAverages[i] = new TProfile2D(Form("OuterEPDCosineAverages%d", i), Form("Outer EPD Cosine Averages, Centrality Class %d; Run Index; j-index; Cosine Correction Term", i), RunIDs.size() - 1, 1, RunIDs.size(), FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
            HistoOuterTPCSineAverages[i] = new TProfile2D(Form("OuterTPCSineAverages%d", i), Form("Outer TPC Sine Averages, Centrality Class %d; Run Index; j-index; Sine Correction Term", i), RunIDs.size() - 1, 1, RunIDs.size(), FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
            HistoOuterTPCCosineAverages[i] = new TProfile2D(Form("OuterTPCCosineAverages%d", i), Form("Outer TPC Cosine Averages, Centrality Class %d; Run Index; j-index Cosine Correction Term", i), RunIDs.size() - 1, 1, RunIDs.size(), FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
        }
    }

    
    for(int i = 0; i < 16; i++)
    {    
        HistoD34[i] = new TH1F(Form("DataPsi1RecenteredInnerEPD%d", i), "Reaction Plane Angle (Recentered), #Psi_{1}, Inner EPD; #Psi_{1}; Events", 500, -3.5, 3.5);  
        HistoD37[i] = new TH1F(Form("DataPsi1RecenteredOuterEPD%d", i), "Reaction Plane Angle (Recentered), #Psi_{1}, Outer EPD; #Psi_{1}; Events", 500, -3.5, 3.5);
        HistoD40[i] = new TH1F(Form("DataPsi1RecenteredOuterTPC%d", i), "Reaction Plane Angle (Recentered), #Psi_{1}, Outer TPC; #Psi_{1}; Events", 500, -3.5, 3.5);
    }
    
 
    
    
    
    
    //Third Pass Histograms        

    for(int i = 0; i < 16; i++)
    {    
        HistoD35[i] = new TH1F(Form("DataPsi1RecenteredAndShiftedInnerEPD%d", i), "Reaction Plane Angle (Fourier Corrected), #Psi_{1} Inner EPD; #Psi_{1}; Events", 500, -3.5, 3.5);
        HistoD38[i] = new TH1F(Form("DataPsi1RecenteredAndShiftedOuterEPD%d", i), "Reaction Plane Angle (Fourier Corrected), #Psi_{1}, Outer EPD; #Psi_{1}; Events", 500, -3.5, 3.5);
        HistoD41[i] = new TH1F(Form("DataPsi1RecenteredAndShiftedOuterTPC%d", i), "Reaction Plane Angle (Fourier Corrected), #Psi_{1}, Outer TPC; #Psi_{1}; Events", 500, -3.5, 3.5);
    }

    HistoD51 = new TProfile("DataResolutionTopLeftTerm", "Resolution Top Left Term; Centrality; Top Left Term", 16, 0, 16);
    HistoD51->Sumw2();

    HistoD52 = new TProfile("DataResolutionTopRightTerm", "Resolution Top Right Term; Centrality; Top Right Term", 16, 0, 16);
    HistoD52->Sumw2();

    HistoD53 = new TProfile("DataResolutionBottomTerm", "Resolution Bottom Term; Centrality; Bottom Term", 16, 0, 16);
    HistoD53->Sumw2();

    
    
    
    
    
    
    //Fourth Pass Histograms
    
    RunCount = new TH1D("RunCount", "Run Count; Run Index; Count", 509, 1, 510);
    
    EventCheck = new TH1D("EventCheck","Event number after each cut;;Events", 9, 0, 9);
    EventCheck->GetXaxis()->SetBinLabel(1,"No Cuts");
    EventCheck->GetXaxis()->SetBinLabel(2,"Bad Run Cut");
    EventCheck->GetXaxis()->SetBinLabel(3,"Minbias Cut");
    EventCheck->GetXaxis()->SetBinLabel(4,"Valid # of Primary Tracks Cut");
    EventCheck->GetXaxis()->SetBinLabel(5,"V_{Z} Cut");
    EventCheck->GetXaxis()->SetBinLabel(6,"V_{r} Cut");
    EventCheck->GetXaxis()->SetBinLabel(7,"Min # of Events/Tracks Cut");
    EventCheck->GetXaxis()->SetBinLabel(8,"No QVec = 0 Cut");
    EventCheck->GetXaxis()->SetBinLabel(9,"Centrality Cut");
    
    OverallTrackCheckNoCuts = new TH1F("OverallTrackCheckNoCuts","Overall Tracks No Cut; One; Tracks", 2, 0, 2);
    OverallTrackCheckNoCuts->Sumw2();

    OverallTrackCheckQACuts = new TH1F("OverallTrackCheckQACuts","Overall Tracks QA Cuts; One; Tracks", 2, 0, 2);
    OverallTrackCheckQACuts->Sumw2();
    
    OverallTrackCheckIDedAsAny = new TH1F("OverallTrackCheckIDedAsAny","Overall Tracks IDed As Any Particle; One; Tracks", 2, 0, 2);
    OverallTrackCheckIDedAsAny->Sumw2();
    
    ProtonTrackCheck = new TH1F("ProtonTrackCheck","Particles IDed as Protons; One; Tracks", 2, 0, 2);
    ProtonTrackCheck->Sumw2();
    
    MostlyGoodProtonTrackCheck = new TH1F("MostlyGoodProtonTrackCheck","Particles IDed as Mostly Good Protons; One; Tracks", 2, 0, 2);
    MostlyGoodProtonTrackCheck->Sumw2();

    GoodProtonTrackCheck = new TH1F("GoodProtonTrackCheck","Particles IDed as Good Protons; One; Tracks", 2, 0, 2);
    GoodProtonTrackCheck->Sumw2();

    KaonPlusTrackCheck = new TH1F("KaonPlusTrackCheck","Particles IDed as Kaons Plus; One; Tracks", 2, 0, 2);
    KaonPlusTrackCheck->Sumw2();

    MostlyGoodKaonPlusTrackCheck = new TH1F("MostlyGoodKaonPlusTrackCheck","Particles IDed as Mostly Good Kaons Plus; One; Tracks", 2, 0, 2);
    MostlyGoodKaonPlusTrackCheck->Sumw2();

    GoodKaonPlusTrackCheck = new TH1F("GoodKaonPlusTrackCheck","Particles IDed as Good Kaons Plus; One; Tracks", 2, 0, 2);
    GoodKaonPlusTrackCheck->Sumw2();
    
    KaonMinusTrackCheck = new TH1F("KaonMinusTrackCheck","Particles IDed as Kaons Minus; One; Tracks", 2, 0, 2);
    KaonMinusTrackCheck->Sumw2();

    MostlyGoodKaonMinusTrackCheck = new TH1F("MostlyGoodKaonMinusTrackCheck","Particles IDed as Mostly Good Kaons Minus; One; Tracks", 2, 0, 2);
    MostlyGoodKaonMinusTrackCheck->Sumw2();
    
    GoodKaonMinusTrackCheck = new TH1F("GoodKaonMinusTrackCheck","Particles IDed as Good Kaons Minus; One; Tracks", 2, 0, 2);
    GoodKaonMinusTrackCheck->Sumw2();
    
    PionPlusTrackCheck = new TH1F("PionPlusTrackCheck","Particles IDed as Pions Plus; One; Tracks", 2, 0, 2);
    PionPlusTrackCheck->Sumw2();

    MostlyGoodPionPlusTrackCheck = new TH1F("MostlyGoodPionPlusTrackCheck","Particles IDed as Mostly Good Pions Plus; One; Tracks", 2, 0, 2);
    MostlyGoodPionPlusTrackCheck->Sumw2();

    GoodPionPlusTrackCheck = new TH1F("GoodPionPlusTrackCheck","Particles IDed as Good Pions Plus; One; Tracks", 2, 0, 2);
    GoodPionPlusTrackCheck->Sumw2();
    
    PionMinusTrackCheck = new TH1F("PionMinusTrackCheck","Particles IDed as Pions Minus; One; Tracks", 2, 0, 2);
    PionMinusTrackCheck->Sumw2();
    
    MostlyGoodPionMinusTrackCheck = new TH1F("MostlyGoodPionMinusTrackCheck","Particles IDed as Mostly Good Pions Minus; One; Tracks", 2, 0, 2);
    MostlyGoodPionMinusTrackCheck->Sumw2();

    GoodPionMinusTrackCheck = new TH1F("GoodPionMinusTrackCheck","Particles IDed as Good Pions Minus; One; Tracks", 2, 0, 2);
    GoodPionMinusTrackCheck->Sumw2();
    
    DeuteronTrackCheck = new TH1F("DeuteronTrackCheck","Particles IDed as Deuterons; One; Tracks", 2, 0, 2);
    DeuteronTrackCheck->Sumw2();

    MostlyGoodDeuteronTrackCheck = new TH1F("MostlyGoodDeuteronTrackCheck","Particles IDed as Mostly Good Deuterons; One; Tracks", 2, 0, 2);
    MostlyGoodDeuteronTrackCheck->Sumw2();

    GoodDeuteronTrackCheck = new TH1F("GoodDeuteronTrackCheck","Particles IDed as Good Deuterons; One; Tracks", 2, 0, 2);
    GoodDeuteronTrackCheck->Sumw2();
    
    TritonTrackCheck = new TH1F("TritonTrackCheck","Particles IDed as Tritons; One; Tracks", 2, 0, 2);
    TritonTrackCheck->Sumw2();

    MostlyGoodTritonTrackCheck = new TH1F("MostlyGoodTritonTrackCheck","Particles IDed as Mostly Good Tritons; One; Tracks", 2, 0, 2);
    MostlyGoodTritonTrackCheck->Sumw2();

    GoodTritonTrackCheck = new TH1F("GoodTritonTrackCheck","Particles IDed as Good Tritons; One; Tracks", 2, 0, 2);
    GoodTritonTrackCheck->Sumw2();

    
    
    
    
    
    HistoDC = new TH1F("Cos(3(Phi-Psi_1)) for Protons at 35-40% Centrality, No Weighting or Resolution Correction", "Cos(3(Phi-Psi_1)) for Protons, No Weighting or Resolution Correction; Cos(3(Phi-Psi_1)); Protons", 350, -7.0, 7.0);
    HistoDC->Sumw2();
    
    HistoDD = new TH1F("Cos(3(Phi-Psi_1)) for Protons at 35-40% Centrality, Resolution Corrected but no Weighting", "Cos(3(Phi-Psi_1)) for Protons, Resolution Corrected but no Weighting; Cos(3(Phi-Psi_1))/R_31; Protons", 350, -7.0, 7.0);
    HistoDD->Sumw2();
    
    HistoDE = new TH1F("Cos(3(Phi-Psi_1)) for Protons at 35-40% Centrality, Weighted and Resolution Corrected", "Cos(3(Phi-Psi_1)) for Protons, Weighted and Resolution Corrected; Cos(3(Phi-Psi_1))/R_31 and Weighted; Protons", 350, -7.0, 7.0);
    HistoDE->Sumw2();
    
    
    
    TrackMultiplicity = new TH1F("TrackMultiplicity", "Track Multiplicity; Multiplicity; Frequency", 195, 0, 195);
    TrackMultiplicity->Sumw2();

    
    
    
    std::string D54String;

    if(RunIteration == 4)
    {
        if(UsingModifiedBesselResolution)
        {
            D54String = "DataResolutionR" + std::to_string(nV) + std::to_string(nPsi);
        }

        else
        {
            D54String = "DataResolution";
        }
        
        const char *D54Char = &D54String[0];
        
        HistoD54 = (TProfile*)ResolutionFile->Get(D54Char);
    }
    

    
    std::string D44CString = "V_{" + std::to_string(nV) + "} vs Y for Protons, Calculated using Inner EPD; y_{CM}; V_{" + std::to_string(nV) +"}";
    const char *D44CChar = &D44CString[0];
    
    HistoD44C= new TProfile("DataVnVsYPsi1ResolutionCorrectedProton", D44CChar, 75, -0.3, 0.95);
    HistoD44C->Sumw2();
    
    std::string D47BString = "V_{" + std::to_string(nV) + "} vs Y for K^{+}, Calculated using Inner EPD; y_{CM}; V_{" + std::to_string(nV) +"}";
    const char *D47BChar = &D47BString[0];

    HistoD47B = new TProfile("DataVnVsYPsi1ResolutionCorrectedKaonPlus", D47BChar, 75, -0.3, 0.95);
    HistoD47B->Sumw2();
    
    std::string D47CString = "V_{" + std::to_string(nV) + "} vs Y for K^{-}, Calculated using Inner EPD; y_{CM}; V_{" + std::to_string(nV) +"}";
    const char *D47CChar = &D47CString[0];

    HistoD47C = new TProfile("DataVnVsYPsi1ResolutionCorrectedKaonMinus", D47CChar, 75, -0.3, 0.95);
    HistoD47C->Sumw2();
    
    std::string D50BString = "V_{" + std::to_string(nV) + "} vs Y for #pi^{+}, Calculated using Inner EPD; y_{CM}; V_{" + std::to_string(nV) +"}";
    const char *D50BChar = &D50BString[0];

    HistoD50B = new TProfile("DataVnVsYPsi1ResolutionCorrectedPionPlus", D50BChar, 75, -0.3, 0.95);
    HistoD50B->Sumw2();
    
    std::string D50CString = "V_{" + std::to_string(nV) + "} vs Y for #pi^{-}, Calculated using Inner EPD; y_{CM}; V_{" + std::to_string(nV) +"}";
    const char *D50CChar = &D50CString[0];

    HistoD50C = new TProfile("DataVnVsYPsi1ResolutionCorrectedPionMinus", D50CChar, 75, -0.3, 0.95);
    HistoD50C->Sumw2();
    
    std::string D50DString = "V_{" + std::to_string(nV) + "} vs Y for Deuterons, Calculated using Inner EPD; y_{CM}; V_{" + std::to_string(nV) +"}";
    const char *D50DChar = &D50DString[0];
    
    HistoD50D = new TProfile("DataVnVsYPsi1ResolutionCorrectedDeuteron", D50DChar, 75, -0.3, 0.95);
    HistoD50D->Sumw2();
    
    std::string D50EString = "V_{" + std::to_string(nV) + "} vs Y for Tritons, Calculated using Inner EPD; y_{CM}; V_{" + std::to_string(nV) +"}";
    const char *D50EChar = &D50EString[0];

    HistoD50E = new TProfile("DataVnVsYPsi1ResolutionCorrectedTriton", D50EChar, 75, -0.3, 0.95);
    HistoD50E->Sumw2();
    
    std::string D54AString = "V_{" + std::to_string(nV) + "} vs Centrality for Protons; Centrality; V_{" + std::to_string(nV) +"}";
    const char *D54AChar = &D54AString[0];

    HistoD54A = new TProfile("DataVnVsCentralityProtonCorrected", D54AChar, 12, 0, 12);
    HistoD54A->Sumw2();
    
    // for (int i = 1; i < HistoD54A->GetNbinsX() + 1; i++)
    // {
    //     HistoD54A->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    // }

    std::string D54BString = "V_{" + std::to_string(nV) + "} vs Centrality for K^{+}; Centrality; V_{" + std::to_string(nV) +"}";
    const char *D54BChar = &D54BString[0];
    
    HistoD54B = new TProfile("DataVnVsCentralityKaonPlusCorrected", D54BChar, 12, 0, 12);
    HistoD54B->Sumw2();
    
    // for (int i = 1; i < HistoD54B->GetNbinsX() + 1; i++)
    // {
    //     HistoD54B->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    // }
    
    std::string D54CString = "V_{" + std::to_string(nV) + "} vs Centrality for K^{-}; Centrality; V_{" + std::to_string(nV) +"}";
    const char *D54CChar = &D54CString[0];

    HistoD54C = new TProfile("DataVnVsCentralityKaonMinusCorrected", D54CChar, 12, 0, 12);
    HistoD54C->Sumw2();
    
    // for (int i = 1; i < HistoD54C->GetNbinsX() + 1; i++)
    // {
    //     HistoD54C->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    // }
    
    std::string D54DString = "V_{" + std::to_string(nV) + "} vs Centrality for #pi^{+}; Centrality; V_{" + std::to_string(nV) +"}";
    const char *D54DChar = &D54DString[0];

    HistoD54D = new TProfile("DataVnVsCentralityPionPlusCorrected", D54DChar, 12, 0, 12);
    HistoD54D->Sumw2();
    
    // for (int i = 1; i < HistoD54D->GetNbinsX() + 1; i++)
    // {
    //     HistoD54D->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    // }

    std::string D54EString = "V_{" + std::to_string(nV) + "} vs Centrality for #pi^{-}; Centrality; V_{" + std::to_string(nV) +"}";
    const char *D54EChar = &D54EString[0];    
    
    HistoD54E = new TProfile("DataVnVsCentralityPionMinusCorrected", D54EChar, 12, 0, 12);
    HistoD54E->Sumw2();

    // for (int i = 1; i < HistoD54E->GetNbinsX() + 1; i++)
    // {
    //     HistoD54E->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    // }
    
    std::string D54FString = "V_{" + std::to_string(nV) + "} vs Centrality for Deuterons; Centrality; V_{" + std::to_string(nV) +"}";
    const char *D54FChar = &D54FString[0];
    
    HistoD54F = new TProfile("DataVnVsCentralityDeuteronCorrected", D54FChar, 12, 0, 12);
    HistoD54F->Sumw2();
    
    // for (int i = 1; i < HistoD54F->GetNbinsX() + 1; i++)
    // {
    //     HistoD54F->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    // }
    
    std::string D54GString = "V_{" + std::to_string(nV) + "} vs Centrality for Tritons; Centrality; V_{" + std::to_string(nV) +"}";
    const char *D54GChar = &D54GString[0];

    HistoD54G = new TProfile("DataVnVsCentralityTritonCorrected", D54GChar, 12, 0, 12);
    HistoD54G->Sumw2();

    // for (int i = 1; i < HistoD54G->GetNbinsX() + 1; i++)
    // {
    //     HistoD54G->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    // }



    

    std::string VnVsCentralityProtonHighRapidityString = "V" + std::to_string(nV) + " vs Centrality for Protons (Y > 0.5); Centrality; V_{" + std::to_string(nV) +"}";
    const char *VnVsCentralityProtonHighRapidityChar = &VnVsCentralityProtonHighRapidityString[0];

    VnVsCentralityProtonHighRapidity = new TProfile("DataVnVsCentralityProtonHighRapidityCorrected", VnVsCentralityProtonHighRapidityChar, 12, 0, 12);
    VnVsCentralityProtonHighRapidity->Sumw2();

    for (int i = 1; i < VnVsCentralityProtonHighRapidity->GetNbinsX() + 1; i++)
    {
        VnVsCentralityProtonHighRapidity->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }

    std::string VnVsCentralityDeuteronHighRapidityString = "V" + std::to_string(nV) + " vs Centrality for Deuterons (Y > 0.5); Centrality; V_{" + std::to_string(nV) +"}";
    const char *VnVsCentralityDeuteronHighRapidityChar = &VnVsCentralityDeuteronHighRapidityString[0];

    VnVsCentralityDeuteronHighRapidity = new TProfile("DataVnVsCentralityDeuteronHighRapidityCorrected", VnVsCentralityDeuteronHighRapidityChar, 12, 0, 12);
    VnVsCentralityDeuteronHighRapidity->Sumw2();

    for (int i = 1; i < VnVsCentralityDeuteronHighRapidity->GetNbinsX() + 1; i++)
    {
        VnVsCentralityDeuteronHighRapidity->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }

    std::string VnVsCentralityTritonHighRapidityString = "V" + std::to_string(nV) + " vs Centrality for Tritons (Y > 0.5); Centrality; V_{" + std::to_string(nV) +"}";
    const char *VnVsCentralityTritonHighRapidityChar = &VnVsCentralityTritonHighRapidityString[0];

    VnVsCentralityTritonHighRapidity = new TProfile("DataVnVsCentralityTritonHighRapidityCorrected", VnVsCentralityTritonHighRapidityChar, 12, 0, 12);
    VnVsCentralityTritonHighRapidity->Sumw2();

    for (int i = 1; i < VnVsCentralityTritonHighRapidity->GetNbinsX() + 1; i++)
    {
        VnVsCentralityTritonHighRapidity->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }






    

    std::string FlowStrengthString = "V_{" + std::to_string(nV) + "} vs #eta; #eta; V_{" + std::to_string(nV) + "}";
    const char *FlowStrengthChar = &FlowStrengthString[0];
    
    FlowStrength = new TProfile("FlowStrength", FlowStrengthChar, 220, -2.1, 0.1);
    FlowStrength->Sumw2();

    std::string FlowStrengthProtonString = "V_{" + std::to_string(nV) + "} vs #eta from Protons; #eta; V_{" + std::to_string(nV) + "}";
    const char *FlowStrengthProtonChar = &FlowStrengthProtonString[0];
    
    FlowStrengthProton = new TProfile("FlowStrengthProton", FlowStrengthProtonChar, 220, -2.1, 0.1);
    FlowStrengthProton->Sumw2();


    

    
    
    std::string D79String = "V_{" + std::to_string(nV) + "} vs Pt for Protons for Different Centralities; Centrality; Pt (GeV)";
    const char *D79Char = &D79String[0];
    
    HistoD79 = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesProton", D79Char, 12, 0, 12, 20, 0, 2);
    HistoD79->Sumw2();
    
    std::string D80String = "V_{" + std::to_string(nV) + "} vs Y for Protons for Different Centralities; Centrality; y_{CM}";
    const char *D80Char = &D80String[0];

    HistoD80 = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesProton", D80Char, 12, 0, 12, 10, 0, 1);
    HistoD80->Sumw2();
    
    std::string D81String = "V_{" + std::to_string(nV) + "} vs Pt for K^{+} for Different Centralities; Centrality; Pt (GeV)";
    const char *D81Char = &D81String[0];

    HistoD81 = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesKaonPlus", D81Char, 12, 0, 12, 20, 0, 2);
    HistoD81->Sumw2();
    
    std::string D82String = "V_{" + std::to_string(nV) + "} vs Y for K^{+} for Different Centralities; Centrality; y_{CM}";
    const char *D82Char = &D82String[0];

    HistoD82 = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesKaonPlus", D82Char, 12, 0, 12, 10, 0, 1);
    HistoD82->Sumw2();
    
    std::string D83String = "V_{" + std::to_string(nV) + "} vs Pt for K^{-} for Different Centralities; Centrality; Pt (GeV)";
    const char *D83Char = &D83String[0];

    HistoD83 = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesKaonMinus", D83Char, 12, 0, 12, 20, 0, 2);
    HistoD83->Sumw2();
    
    std::string D84String = "V_{" + std::to_string(nV) + "} vs Y for K^{-} for Different Centralities; Centrality; y_{CM}";
    const char *D84Char = &D84String[0];

    HistoD84 = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesKaonMinus", D84Char, 12, 0, 12, 10, 0, 1);
    HistoD84->Sumw2();
    
    std::string D85String = "V_{" + std::to_string(nV) + "} vs Pt for #pi^{+} for Different Centralities; Centrality; Pt (GeV)";
    const char *D85Char = &D85String[0];

    HistoD85 = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesPionPlus", D85Char, 12, 0, 12, 20, 0, 2);
    HistoD85->Sumw2();
    
    std::string D86String = "V_{" + std::to_string(nV) + "} vs Y for #pi^{+} for Different Centralities; Centrality; y_{CM}";
    const char *D86Char = &D86String[0];

    HistoD86 = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesPionPlus", D86Char, 12, 0, 12, 10, 0, 1);
    HistoD86->Sumw2();
    
    std::string D87String = "V_{" + std::to_string(nV) + "} vs Pt for #pi^{-} for Different Centralities; Centrality; Pt (GeV)";
    const char *D87Char = &D87String[0];

    HistoD87 = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesPionMinus", D87Char, 12, 0, 12, 20, 0, 2);
    HistoD87->Sumw2();
    
    std::string D88String = "V_{" + std::to_string(nV) + "} vs Y for #pi^{-} for Different Centralities; Centrality; y_{CM}";
    const char *D88Char = &D88String[0];

    HistoD88 = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesPionMinus", D88Char, 12, 0, 12, 10, 0, 1);
    HistoD88->Sumw2();

    std::string D88AString = "V_{" + std::to_string(nV) + "} vs Pt for Deuterons for Different Centralities; Centrality; Pt (GeV)";
    const char *D88AChar = &D88AString[0];

    HistoD88A = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesDeuterons", D88AChar, 12, 0, 12, 40, 0, 4);
    HistoD88A->Sumw2();
    
    std::string D88BString = "V_{" + std::to_string(nV) + "} vs Y for Deuterons for Different Centralities; Centrality; y_{CM}";
    const char *D88BChar = &D88BString[0];

    HistoD88B = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesDeuterons", D88BChar, 12, 0, 12, 10, 0, 1);
    HistoD88B->Sumw2();
    
    std::string D88CString = "V_{" + std::to_string(nV) + "} vs Pt for Tritons for Different Centralities; Centrality; Pt (GeV)";
    const char *D88CChar = &D88CString[0];
    
    HistoD88C = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesTritons", D88CChar, 12, 0, 12, 60, 0, 6);
    HistoD88C->Sumw2();
    
    std::string D88DString = "V_{" + std::to_string(nV) + "} vs Y for Tritons for Different Centralities; Centrality; y_{CM}";
    const char *D88DChar = &D88DString[0];

    HistoD88D = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesTritons", D88DChar, 12, 0, 12, 10, 0, 1);
    HistoD88D->Sumw2();



    std::string VnVsCentPtProtonHighRapidityString = "V_{" + std::to_string(nV) + "} vs Pt for Protons for Different Centralities (Y > 0.5); Centrality; Pt (GeV)";
    const char *VnVsCentPtProtonHighRapidityChar = &VnVsCentPtProtonHighRapidityString[0];
    
    VnVsCentPtProtonHighRapidity = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesProtonHighRapidity", VnVsCentPtProtonHighRapidityChar, 12, 0, 12, 20, 0, 2);
    VnVsCentPtProtonHighRapidity->Sumw2();

    std::string VnVsCentPtDeuteronHighRapidityString = "V_{" + std::to_string(nV) + "} vs Pt for Deuterons for Different Centralities (Y > 0.5); Centrality; Pt (GeV)";
    const char *VnVsCentPtDeuteronHighRapidityChar = &VnVsCentPtDeuteronHighRapidityString[0];
    
    VnVsCentPtDeuteronHighRapidity = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesDeuteronHighRapidity", VnVsCentPtDeuteronHighRapidityChar, 12, 0, 12, 40, 0, 4);
    VnVsCentPtDeuteronHighRapidity->Sumw2();

    std::string VnVsCentPtTritonHighRapidityString = "V_{" + std::to_string(nV) + "} vs Pt for Tritons for Different Centralities (Y > 0.5); Centrality; Pt (GeV)";
    const char *VnVsCentPtTritonHighRapidityChar = &VnVsCentPtTritonHighRapidityString[0];
    
    VnVsCentPtTritonHighRapidity = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesTritonHighRapidity", VnVsCentPtTritonHighRapidityChar, 12, 0, 12, 60, 0, 6);
    VnVsCentPtTritonHighRapidity->Sumw2();

    

    std::string VnVsYSymmetricProtonString = "V_{" + std::to_string(nV) + "} vs Y (Symmetric) for Protons for Different Centralities; Centrality; y_{CM}";
    const char *VnVsYSymmetricProtonChar = &VnVsYSymmetricProtonString[0];

    VnVsYSymmetricProton = new TProfile2D("DataVnCorrectedVsYSymmetricDifferentCentralitiesProtons", VnVsYSymmetricProtonChar, 12, 0, 12, 10, -0.5, 0.5);
    VnVsYSymmetricProton->Sumw2();
    
 

    
    
    std::string VnVsPtProton0_00Through0_10String = "V_{" + std::to_string(nV) + "} vs Pt for Proton, 0.0-0.1 Rapidity and 10-40% Centrality; Pt (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnVsPtProton0_00Through0_10Char = &VnVsPtProton0_00Through0_10String[0];
    
    VnVsPtProton0_00Through0_10 = new TProfile("VnVsPtProton0_00Through0_10", VnVsPtProton0_00Through0_10Char, 20, 0, 2);
    VnVsPtProton0_00Through0_10->Sumw2();
    
    std::string VnVsPtProton0_10Through0_20String = "V_{" + std::to_string(nV) + "} vs Pt for Proton, 0.1-0.2 Rapidity and 10-40% Centrality; Pt (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnVsPtProton0_10Through0_20Char = &VnVsPtProton0_10Through0_20String[0];
    
    VnVsPtProton0_10Through0_20 = new TProfile("VnVsPtProton0_10Through0_20", VnVsPtProton0_10Through0_20Char, 20, 0, 2);
    VnVsPtProton0_10Through0_20->Sumw2();
    
    std::string VnVsPtProton0_20Through0_30String = "V_{" + std::to_string(nV) + "} vs Pt for Proton, 0.2-0.3 Rapidity and 10-40% Centrality; Pt (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnVsPtProton0_20Through0_30Char = &VnVsPtProton0_20Through0_30String[0];
    
    VnVsPtProton0_20Through0_30 = new TProfile("VnVsPtProton0_20Through0_30", VnVsPtProton0_20Through0_30Char, 20, 0, 2);
    VnVsPtProton0_20Through0_30->Sumw2();
    
    std::string VnVsPtProton0_30Through0_40String = "V_{" + std::to_string(nV) + "} vs Pt for Proton, 0.3-0.4 Rapidity and 10-40% Centrality; Pt (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnVsPtProton0_30Through0_40Char = &VnVsPtProton0_30Through0_40String[0];
    
    VnVsPtProton0_30Through0_40 = new TProfile("VnVsPtProton0_30Through0_40", VnVsPtProton0_30Through0_40Char, 20, 0, 2);
    VnVsPtProton0_30Through0_40->Sumw2();
    
    
    
    
    std::string VnVsPtDeuteron0_00Through0_10String = "V_{" + std::to_string(nV) + "} vs Pt for Deuteron, 0.0-0.1 Rapidity and 10-40% Centrality; Pt (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnVsPtDeuteron0_00Through0_10Char = &VnVsPtDeuteron0_00Through0_10String[0];
    
    VnVsPtDeuteron0_00Through0_10 = new TProfile("VnVsPtDeuteron0_00Through0_10", VnVsPtDeuteron0_00Through0_10Char, 20, 0, 2);
    VnVsPtDeuteron0_00Through0_10->Sumw2();
    
    std::string VnVsPtDeuteron0_10Through0_20String = "V_{" + std::to_string(nV) + "} vs Pt for Deuteron, 0.1-0.2 Rapidity and 10-40% Centrality; Pt (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnVsPtDeuteron0_10Through0_20Char = &VnVsPtDeuteron0_10Through0_20String[0];
    
    VnVsPtDeuteron0_10Through0_20 = new TProfile("VnVsPtDeuteron0_10Through0_20", VnVsPtDeuteron0_10Through0_20Char, 20, 0, 2);
    VnVsPtDeuteron0_10Through0_20->Sumw2();
    
    std::string VnVsPtDeuteron0_20Through0_30String = "V_{" + std::to_string(nV) + "} vs Pt for Deuteron, 0.2-0.3 Rapidity and 10-40% Centrality; Pt (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnVsPtDeuteron0_20Through0_30Char = &VnVsPtDeuteron0_20Through0_30String[0];
    
    VnVsPtDeuteron0_20Through0_30 = new TProfile("VnVsPtDeuteron0_20Through0_30", VnVsPtDeuteron0_20Through0_30Char, 20, 0, 2);
    VnVsPtDeuteron0_20Through0_30->Sumw2();
    
    std::string VnVsPtDeuteron0_30Through0_40String = "V_{" + std::to_string(nV) + "} vs Pt for Deuteron, 0.3-0.4 Rapidity and 10-40% Centrality; Pt (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnVsPtDeuteron0_30Through0_40Char = &VnVsPtDeuteron0_30Through0_40String[0];
    
    VnVsPtDeuteron0_30Through0_40 = new TProfile("VnVsPtDeuteron0_30Through0_40", VnVsPtDeuteron0_30Through0_40Char, 20, 0, 2);
    VnVsPtDeuteron0_30Through0_40->Sumw2();
    
    
    
    
    std::string VnVsPtTriton0_00Through0_10String = "V_{" + std::to_string(nV) + "} vs Pt for Triton, 0.0-0.1 Rapidity and 10-40% Centrality; Pt (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnVsPtTriton0_00Through0_10Char = &VnVsPtTriton0_00Through0_10String[0];
    
    VnVsPtTriton0_00Through0_10 = new TProfile("VnVsPtTriton0_00Through0_10", VnVsPtTriton0_00Through0_10Char, 20, 0, 2);
    VnVsPtTriton0_00Through0_10->Sumw2();
    
    std::string VnVsPtTriton0_10Through0_20String = "V_{" + std::to_string(nV) + "} vs Pt for Triton, 0.1-0.2 Rapidity and 10-40% Centrality; Pt (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnVsPtTriton0_10Through0_20Char = &VnVsPtTriton0_10Through0_20String[0];
    
    VnVsPtTriton0_10Through0_20 = new TProfile("VnVsPtTriton0_10Through0_20", VnVsPtTriton0_10Through0_20Char, 20, 0, 2);
    VnVsPtTriton0_10Through0_20->Sumw2();
    
    std::string VnVsPtTriton0_20Through0_30String = "V_{" + std::to_string(nV) + "} vs Pt for Triton, 0.2-0.3 Rapidity and 10-40% Centrality; Pt (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnVsPtTriton0_20Through0_30Char = &VnVsPtTriton0_20Through0_30String[0];
    
    VnVsPtTriton0_20Through0_30 = new TProfile("VnVsPtTriton0_20Through0_30", VnVsPtTriton0_20Through0_30Char, 20, 0, 2);
    VnVsPtTriton0_20Through0_30->Sumw2();
    
    std::string VnVsPtTriton0_30Through0_40String = "V_{" + std::to_string(nV) + "} vs Pt for Triton, 0.3-0.4 Rapidity and 10-40% Centrality; Pt (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnVsPtTriton0_30Through0_40Char = &VnVsPtTriton0_30Through0_40String[0];
    
    VnVsPtTriton0_30Through0_40 = new TProfile("VnVsPtTriton0_30Through0_40", VnVsPtTriton0_30Through0_40Char, 20, 0, 2);
    VnVsPtTriton0_30Through0_40->Sumw2();
    
    
    
    std::string VnOverAVsPtOverAProton0_00Through0_10String = "V_{" + std::to_string(nV) + "}/A vs Pt/A for Protons, 0.0-0.1 Rapidity and 10-40% Centrality; Pt/A (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnOverAVsPtOverAProton0_00Through0_10Char = &VnOverAVsPtOverAProton0_00Through0_10String[0];
    
    VnOverAVsPtOverAProton0_00Through0_10 = new TProfile("VnOverAVsPtOverAProton0_00Through0_10", VnOverAVsPtOverAProton0_00Through0_10Char, 20, 0, 2);
    VnOverAVsPtOverAProton0_00Through0_10->Sumw2();
    
    std::string VnOverAVsPtOverAProton0_10Through0_20String = "V_{" + std::to_string(nV) + "}/A vs Pt/A for Protons, 0.1-0.2 Rapidity and 10-40% Centrality; Pt/A (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnOverAVsPtOverAProton0_10Through0_20Char = &VnOverAVsPtOverAProton0_10Through0_20String[0];
    
    VnOverAVsPtOverAProton0_10Through0_20 = new TProfile("VnOverAVsPtOverAProton0_10Through0_20", VnOverAVsPtOverAProton0_10Through0_20Char, 20, 0, 2);
    VnOverAVsPtOverAProton0_10Through0_20->Sumw2();
    
    std::string VnOverAVsPtOverAProton0_20Through0_30String = "V_{" + std::to_string(nV) + "}/A vs Pt/A for Protons, 0.2-0.3 Rapidity and 10-40% Centrality; Pt/A (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnOverAVsPtOverAProton0_20Through0_30Char = &VnOverAVsPtOverAProton0_20Through0_30String[0];
    
    VnOverAVsPtOverAProton0_20Through0_30 = new TProfile("VnOverAVsPtOverAProton0_20Through0_30", VnOverAVsPtOverAProton0_20Through0_30Char, 20, 0, 2);
    VnOverAVsPtOverAProton0_20Through0_30->Sumw2();
    
    std::string VnOverAVsPtOverAProton0_30Through0_40String = "V_{" + std::to_string(nV) + "}/A vs Pt/A for Protons, 0.3-0.4 Rapidity and 10-40% Centrality; Pt/A (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnOverAVsPtOverAProton0_30Through0_40Char = &VnOverAVsPtOverAProton0_30Through0_40String[0];
    
    VnOverAVsPtOverAProton0_30Through0_40 = new TProfile("VnOverAVsPtOverAProton0_30Through0_40", VnOverAVsPtOverAProton0_30Through0_40Char, 20, 0, 2);
    VnOverAVsPtOverAProton0_30Through0_40->Sumw2();
    
    
    
    std::string VnOverAVsPtOverADeuteron0_00Through0_10String = "V_{" + std::to_string(nV) + "}/A vs Pt/A for Deuteron, 0.0-0.1 Rapidity and 10-40% Centrality; Pt/A (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnOverAVsPtOverADeuteron0_00Through0_10Char = &VnOverAVsPtOverADeuteron0_00Through0_10String[0];
    
    VnOverAVsPtOverADeuteron0_00Through0_10 = new TProfile("VnOverAVsPtOverADeuteron0_00Through0_10", VnOverAVsPtOverADeuteron0_00Through0_10Char, 20, 0, 2);
    VnOverAVsPtOverADeuteron0_00Through0_10->Sumw2();
    
    std::string VnOverAVsPtOverADeuteron0_10Through0_20String = "V_{" + std::to_string(nV) + "}/A vs Pt/A for Deuteron, 0.1-0.2 Rapidity and 10-40% Centrality; Pt/A (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnOverAVsPtOverADeuteron0_10Through0_20Char = &VnOverAVsPtOverADeuteron0_10Through0_20String[0];
    
    VnOverAVsPtOverADeuteron0_10Through0_20 = new TProfile("VnOverAVsPtOverADeuteron0_10Through0_20", VnOverAVsPtOverADeuteron0_10Through0_20Char, 20, 0, 2);
    VnOverAVsPtOverADeuteron0_10Through0_20->Sumw2();
    
    std::string VnOverAVsPtOverADeuteron0_20Through0_30String = "V_{" + std::to_string(nV) + "}/A vs Pt/A for Deuteron, 0.2-0.3 Rapidity and 10-40% Centrality; Pt/A (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnOverAVsPtOverADeuteron0_20Through0_30Char = &VnOverAVsPtOverADeuteron0_20Through0_30String[0];
    
    VnOverAVsPtOverADeuteron0_20Through0_30 = new TProfile("VnOverAVsPtOverADeuteron0_20Through0_30", VnOverAVsPtOverADeuteron0_20Through0_30Char, 20, 0, 2);
    VnOverAVsPtOverADeuteron0_20Through0_30->Sumw2();
    
    std::string VnOverAVsPtOverADeuteron0_30Through0_40String = "V_{" + std::to_string(nV) + "}/A vs Pt/A for Deuteron, 0.3-0.4 Rapidity and 10-40% Centrality; Pt/A (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnOverAVsPtOverADeuteron0_30Through0_40Char = &VnOverAVsPtOverADeuteron0_30Through0_40String[0];
    
    VnOverAVsPtOverADeuteron0_30Through0_40 = new TProfile("VnOverAVsPtOverADeuteron0_30Through0_40", VnOverAVsPtOverADeuteron0_30Through0_40Char, 20, 0, 2);
    VnOverAVsPtOverADeuteron0_30Through0_40->Sumw2();
    
    
    
    
    std::string VnOverAVsPtOverATriton0_00Through0_10String = "V_{" + std::to_string(nV) + "}/A vs Pt/A for Triton, 0.0-0.1 Rapidity and 10-40% Centrality; Pt/A (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnOverAVsPtOverATriton0_00Through0_10Char = &VnOverAVsPtOverATriton0_00Through0_10String[0];
    
    VnOverAVsPtOverATriton0_00Through0_10 = new TProfile("VnOverAVsPtOverATriton0_00Through0_10", VnOverAVsPtOverATriton0_00Through0_10Char, 20, 0, 2);
    VnOverAVsPtOverATriton0_00Through0_10->Sumw2();
    
    std::string VnOverAVsPtOverATriton0_10Through0_20String = "V_{" + std::to_string(nV) + "}/A vs Pt/A for Triton, 0.1-0.2 Rapidity and 10-40% Centrality; Pt/A (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnOverAVsPtOverATriton0_10Through0_20Char = &VnOverAVsPtOverATriton0_10Through0_20String[0];
    
    VnOverAVsPtOverATriton0_10Through0_20 = new TProfile("VnOverAVsPtOverATriton0_10Through0_20", VnOverAVsPtOverATriton0_10Through0_20Char, 20, 0, 2);
    VnOverAVsPtOverATriton0_10Through0_20->Sumw2();
    
    std::string VnOverAVsPtOverATriton0_20Through0_30String = "V_{" + std::to_string(nV) + "}/A vs Pt/A for Triton, 0.2-0.3 Rapidity and 10-40% Centrality; Pt/A (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnOverAVsPtOverATriton0_20Through0_30Char = &VnOverAVsPtOverATriton0_20Through0_30String[0];
    
    VnOverAVsPtOverATriton0_20Through0_30 = new TProfile("VnOverAVsPtOverATriton0_20Through0_30", VnOverAVsPtOverATriton0_20Through0_30Char, 20, 0, 2);
    VnOverAVsPtOverATriton0_20Through0_30->Sumw2();
    
    std::string VnOverAVsPtOverATriton0_30Through0_40String = "V_{" + std::to_string(nV) + "}/A vs Pt/A for Triton, 0.3-0.4 Rapidity and 10-40% Centrality; Pt/A (GeV); V_{" + std::to_string(nV) + "}";
    const char *VnOverAVsPtOverATriton0_30Through0_40Char = &VnOverAVsPtOverATriton0_30Through0_40String[0];
    
    VnOverAVsPtOverATriton0_30Through0_40 = new TProfile("VnOverAVsPtOverATriton0_30Through0_40", VnOverAVsPtOverATriton0_30Through0_40Char, 20, 0, 2);
    VnOverAVsPtOverATriton0_30Through0_40->Sumw2();    
    
    
    
    epdGeom = new StEpdGeom();
    
    std::cout << "Setup Complete" << std::endl; 
    
    
    return kStOK;
}





Int_t TreeAnalyzer::Make()
{   
    //Bichsel function setup
    Double_t log2dx = 1.0;
    Double_t xStart = 0.01;
    Double_t xStop  = 3.0;
    Int_t npx = 10000;

    const Double_t DeuteronMass = 1.875613;
    const Double_t TritonMass = 2.808921;

    Double_t parameters[2] = {1.0, log2dx};

    parameters[0] = DeuteronMass;
    TF1 *BichselZDeuteron = new TF1(Form("BichselZDeuteron_log2dx_%i",(int)log2dx),BichselZ,xStart,xStop,2);
    BichselZDeuteron->SetParameters(parameters); 
    BichselZDeuteron->SetNpx(npx);

    parameters[0] = TritonMass;
    TF1 *BichselZTriton = new TF1(Form("BichselZTriton_log2dx_%i",(int)log2dx),BichselZ,xStart,xStop,2);
    BichselZTriton->SetParameters(parameters); 
    BichselZTriton->SetNpx(npx);
    
    
    


    
    
    // Parameters
    Double_t yCMShift = -1.05;
    Int_t NumberOfGoodTracksInnerEPD = 5;
    Int_t NumberOfGoodTracksOuterEPD = 9;
    Int_t NumberOfGoodTracksOuterTPC = 5;
    Double_t OuterTPCUpperLimit = 0.0;
    Double_t OuterTPCLowerLimit = -1.0;
    Double_t InnerTPCUpperLimit = -1.1;
    Double_t InnerTPCLowerLimit = -2.0;



    Double_t RVertexBound = 1.5;
    Double_t ZVertexLowerBound = 198.0;
    Double_t ZVertexUpperBound = 202.0;
    
    Double_t DCABound = 3.0;
    Int_t NHitsBound = 15;
    Int_t NHitsdEdxBound = 5;
    Double_t NHitsFitOverNHitsPossBound = 0.52;
    
    Int_t InnerEPDHighRing = 9;
    Int_t OuterEPDLowRing = 10;
    
    
    
    // Double_t ProtonLowerMSquared = 0.6;
    // Double_t ProtonUpperMSquared = 1.2;
    Double_t KaonLowerMSquared = 0.15;
    Double_t KaonUpperMSquared = 0.34;
    Double_t PionLowerMSquared = -0.1;
    Double_t PionUpperMSquared = 0.1;
    Double_t LambdaLowerMass = 1.103;
    Double_t LambdaUpperMass = 1.129;
    Double_t NSigmaPrBound = 2.0;
    Double_t NSigmaKaBound = 3.0;
    Double_t NSigmaPiBound = 3.0;
    Double_t ProtonLowerPt = 0.4;
    Double_t ProtonUpperPt = 2.0;
    Double_t KaonLowerPt = 0.4;
    Double_t KaonUpperPt = 1.6;
    Double_t PionLowerPt = 0.18;
    Double_t PionUpperPt = 1.6;
    Double_t DeuteronLowerPt = 0.8;
    Double_t DeuteronUpperPt = 3.5;
    Double_t TritonLowerPt = 1.2;
    Double_t TritonUpperPt = 4.0;
    // Double_t LambdaLowerPt = 0.4;
    // Double_t LambdaUpperPt = 2.0;
    Double_t LowerYMinusYCMShift = 0.0;
    Double_t UpperYMinusYCMShift = 1.0;
   

    
    
    // Parameter changes for systematic runs
    if (Variation == "RVertex20Low")
    {
        RVertexBound = 1.2;
    }
    if (Variation == "RVertex30Low")
    {
        RVertexBound = 1.05;
    }
    if (Variation == "RVertex20High")
    {
        RVertexBound = 1.8;
    }
    if(Variation == "RVertex30High")
    {
        RVertexBound = 1.95;
    }
    if (Variation == "ZVertex20Low")
    {
        ZVertexLowerBound = 198.4;
        ZVertexUpperBound = 201.6;
    }
    if (Variation == "ZVertex20High")
    {
        ZVertexLowerBound = 197.6;
        ZVertexUpperBound = 202.4;
    }
    if (Variation == "ZVertex30Low")
    {
        ZVertexLowerBound = 198.6;
        ZVertexUpperBound = 201.4;
    }
    if (Variation == "ZVertex30High")
    {
        ZVertexLowerBound = 197.4;
        ZVertexUpperBound = 202.6;
    }
    if (Variation == "DCA20Low")
    {
        DCABound = 2.4;
    }
    if (Variation == "DCA20High")
    {
        DCABound = 3.6;
    }
    if (Variation == "DCA30Low")
    {
        DCABound = 2.1;
    }
    if (Variation == "DCA30High")
    {
        DCABound = 3.9;
    }
    if (Variation == "NHits20Low")
    {
        NHitsBound = 12;
    }
    if (Variation == "NHits20High")
    {
        NHitsBound = 18;
    }
    if (Variation == "NHits30Low")
    {
        NHitsBound = 10;
    }
    if (Variation == "NHits30High")
    {
        NHitsBound = 20;
    }
    if (Variation == "NHitsdEdx20High")
    {
        NHitsdEdxBound = 9;
    }
    if (Variation == "NHitsdEdx30High")
    {
        NHitsdEdxBound = 12;
    }
    if (Variation == "NHitsFitOverNHitsPoss20Low")
    {
        NHitsFitOverNHitsPossBound = 0.416;
    }
    if (Variation == "NHitsFitOverNHitsPoss20High")
    {
        NHitsFitOverNHitsPossBound = 0.624;
    }
    if (Variation == "NHitsFitOverNHitsPoss30Low")
    {
        NHitsFitOverNHitsPossBound = 0.364;
    }
    if (Variation == "NHitsFitOverNHitsPoss30High")
    {
        NHitsFitOverNHitsPossBound = 0.676;
    }
    if (Variation == "NSigmaPion20Low")
    {
        NSigmaPiBound = 2.4;
    }
    if (Variation == "NSigmaPion20High")
    {
        NSigmaPiBound = 3.6;
    }
    if (Variation == "NSigmaPion30Low")
    {
        NSigmaPiBound = 2.1;
    }
    if (Variation == "NSigmaPion30High")
    {
        NSigmaPiBound = 3.9;
    }
    if (Variation == "NSigmaKaon20Low")
    {
        NSigmaKaBound = 2.4;
    }
    if (Variation == "NSigmaKaon20High")
    {
        NSigmaKaBound = 3.6;
    }
    if (Variation == "NSigmaKaon30Low")
    {
        NSigmaKaBound = 2.1;
    }
    if (Variation == "NSigmaKaon30High")
    {
        NSigmaKaBound = 3.9;
    }
    if (Variation == "NSigmaProton20Low")
    {
        NSigmaPrBound = 1.6;
    }
    if (Variation == "NSigmaProton20High")
    {
        NSigmaPrBound = 2.4;
    }
    if (Variation == "NSigmaProton30Low")
    {
        NSigmaPrBound = 1.4;
    }
    if (Variation == "NSigmaProton30High")
    {
        NSigmaPrBound = 2.6;
    }
    if (Variation == "MSquaredPion20Low")
    {
        PionLowerMSquared = -0.08;
        PionUpperMSquared = 0.08;
    }
    if (Variation == "MSquaredPion20High")
    {
        PionLowerMSquared = -0.12;
        PionUpperMSquared = 0.12;
    }
    if (Variation == "MSquaredPion30Low")
    {
        PionLowerMSquared = -0.07;
        PionUpperMSquared = 0.07;
    }
    if (Variation == "MSquaredPion30High")
    {
        PionLowerMSquared = -0.13;
        PionUpperMSquared = 0.13;
    }
    if (Variation == "MSquaredKaon20Low")
    {
        KaonLowerMSquared = 0.169;
        KaonUpperMSquared = 0.321;
    }
    if (Variation == "MSquaredKaon20High")
    {
        KaonLowerMSquared = 0.131;
        KaonUpperMSquared = 0.359;
    }
    if (Variation == "MSquaredKaon30Low")
    {
        KaonLowerMSquared = 0.1785;
        KaonUpperMSquared = 0.3115;
    }
    if (Variation == "MSquaredKaon30High")
    {
        KaonLowerMSquared = 0.1215;
        KaonUpperMSquared = 0.3685;
    }
    if (Variation == "OuterEPDLow")
    {
        if(RunIteration <= 3)
        {
            OuterEPDLowRing = 10;
        }
        else
        {
            OuterEPDLowRing = 9;
        }
    }
    if (Variation == "OuterEPDHigh")
    {
        if(RunIteration <= 3)
        {
            OuterEPDLowRing = 13;
        }
        else
        {
            OuterEPDLowRing = 9;
        }
    }
    
    std::vector<int> RunIDs {0, 79020,79021,79022,78002,78003,78004,78005,78006,78007,78008,78009,78010,78011,78012,78013,77002,77003,77004,77005,77006,77007,77008,77012,77013,77014,76001,76002,76003,76004,76005,76006,76007,76008,76009,76011,76012,75001,75002,75003,75004,75005,75006,75007,75008,75010,75011,75013,75031,75032,74002,74003,74004,74005,74006,74007,74010,74011,74012,74013,74014,74018,74019,74046,74047,74048,74049,74050,74054,74055,74056,74057,74058,74059,74060,74061,74062,73001,73002,73003,73004,73005,73006,73009,73010,73011,73012,73013,73014,73015,73016,73017,73018,73019,73020,73023,73024,73025,73026,73027,73028,73029,73030,73031,73032,73033,73034,73035,72001,72002,72003,72004,72005,72006,72007,72008,72009,72010,72022,72024,72025,71021,71022,71023,71024,71025,71026,71027,71028,71029,71030,71031,71032,71033,70001,70002,70003,70004,70005,70006,70007,70008,70009,70014,70015,70016,70017,70018,70019,70020,70021,70022,69001,69002,69003,69004,69005,69006,69007,69008,69009,69010,69011,69018,69022,69023,68003,68004,68005,68006,68007,68008,68009,68010,68015,67001,67002,67003,67004,67005,67006,67007,67008,67009,67010,67011,67012,67016,67017,67021,67022,67023,67024,67025,67027,67028,67029,66001,66002,66003,66004,66005,66006,66009,66010,66013,66014,66015,66016,66017,66018,66019,66020,66023,66024,66026,66028,66029,66030,66031,66034,66035,66036,66037,66038,66039,65001,65002,65003,65004,65005,65006,65007,65008,65009,65010,65012,65013,65014,65015,65016,65017,65018,65019,65021,65024,65025,65026,65027,65028,65029,65031,65032,65033,65034,65035,64001,64002,64003,64004,64005,64006,64007,64008,64009,64010,64011,64012,64013,64014,64015,64016,64017,64018,64019,64022,64024,64025,64026,64027,64028,64029,64030,64031,64032,64033,63002,63003,63004,63005,63006,63007,63008,63009,63010,63011,63012,63013,63014,63015,63016,63017,63018,63019,63020,63026,63027,63028,63029,63030,63031,63032,63034,63035,63036,62001,62003,62006,62007,62008,62009,62015,62018,62019,62021,62022,62023,61001,61002,61003,61004,61005,61006,61009,61010,61012,61013,61014,61015,61016,61018,61019,61020,61023,61024,61025,61026,61027,61028,61029,61030,61031,61032,61033,60001,60002,60003,60004,60005,60006,60007,60008,60009,60010,60011,60012,60013,60014,60015,60016,60017,60018,60019,60020,60021,60022,60024,60025,60026,60027,60028,60029,60030,60031,60032,60046,60047,60048,60049,60050,60051,60052,60053,59001,59003,59008,59009,59010,59011,59012,59013,59015,59051,59052,59053,58032,58033,58036,25001,25002,25003,25004,25005,25006,25007,25008,25009,25010,25011,24002,24003,24004,24005,24006,24007,24008,24011,24012,24013,24014,24018,24027,24028,24031,23001,23002,23003,23004,23005,23006,23007,23008,23009,23010,23011,23012,23013,23014,23015,23016,23017,23018,23020,23021,23025,23026,23027,23028,23030,23031,23032,23034,23035,23037,23038,23040,23041,22001,22002,22003,22004,22005,22006,22007,22008,22009,22010,22011,22014,22016,22017,22018,22019,22020,22021,22024,22025,22026,22027,22028,22029,22031,22032,22034,22035,21033,21036,21037,21038,21039,21040,21041,21044,21045,21046,21048,21049,21050,21052,21053};



// For my Data
    const Int_t NumBadRuns = 67;
        
    const Int_t BadRuns[NumBadRuns] = {22121046, 22122004, 22122005, 22122021, 22122034, 22123002, 22123007, 22123016, 22124011, 22158032, 22158033, 22158036, 22159001, 22159003, 22159009, 22159010, 22159012, 22159015, 22160003, 22160031, 22161016, 22162015, 22163002, 22163003, 22163007, 22163010, 22164010, 22164018, 22164025, 22163004, 22163005, 22163006, 22165012, 22165034, 22166003, 22166013, 22166026, 22166030, 22167004, 22167009, 22168009, 22169009, 22171023, 22173026, 22173035, 22174004, 22174005, 22174006, 22174007, 22174010, 22174011, 22174012, 22174013, 22174014, 22174019, 22174049, 22176007, 22177004, 22177006, 22178004, 22178013, 22179020, 22171029, 22172003, 22172007, 22173004, 22173013};
    
    const Int_t TriggerIDs[3] = {820010, 820020, 820030};

    
// For Cameron's Data
    // const Int_t NumBadRuns = 24;

    // const Int_t BadRuns[NumBadRuns] = {19151029, 19151045, 19152001, 19152078, 19153023, 19153032, 19153065, 19154012, 19154013, 19154014, 19154015, 19154016, 19154017, 19154018, 19154019, 19154020, 19154021, 19154022, 19154023, 19154024, 19154026, 19154046, 19154051, 19154056};

    // const Int_t TriggerIDs[1] = {620052};



// For QA Runs
    // const Int_t NumBadRuns = 0;
    
    // const Int_t BadRuns[NumBadRuns] = {};

    // const Int_t TriggerIDs[3] = {680002, 680003, 680004};




    const Int_t NumEToFMatchFlags = 3;

    const Int_t EToFMatchFlags[NumEToFMatchFlags] = {-52, -42, -32};
    
    
    
    const char* CentralityXLabels[16] = {"0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60", "60-65", "65-70", "70-75", "75-80"};
    
  

    if(!mPicoDstMaker) {
        LOG_WARN << " No PicoDstMaker! Skip! " << endm;
        return kStWarn;
    }
    mPicoDst = mPicoDstMaker->picoDst();
    if(!mPicoDst) {
        LOG_WARN << " No PicoDst! Skip! " << endm;
        return kStWarn;
    }
    picoEvent = (StPicoEvent*)mPicoDst->event();
    if( !picoEvent ){
        LOG_WARN << " No PicoEvent! Skip! " << endm;
        return kStWarn;
    }

    EventCheck->Fill(0);

    Int_t RunID = picoEvent->runId();

    Bool_t IsBadRun = false;

    for(Int_t i = 0; i < NumBadRuns; i++)
    {
        if(RunID == BadRuns[i])
        {
            IsBadRun = true;
        }
    }

    if(IsBadRun)
    {
        return kStOK;
    }

    EventCheck->Fill(1);

    Bool_t IsTriggered = false;
    
    for(Int_t i = 0; i < 3; i++)
    {
         if(picoEvent->isTrigger(TriggerIDs[i]))
         {
             IsTriggered = true;
         }
    }

    if(!IsTriggered)
    {
        return kStOK;
    }

    EventCheck->Fill(2);
    
    Int_t RunIndex = 0;

    RunID -= 22100000;

    auto iterator = std::find(RunIDs.begin(), RunIDs.end(), RunID);

    if(iterator != RunIDs.end())
    {
        RunIndex = std::distance(RunIDs.begin(), iterator);
    }

    RunCount->Fill(RunIndex);

    TVector3 PrimaryVertex = picoEvent->primaryVertex();

    Double_t vx = PrimaryVertex.x();
    Double_t vy = PrimaryVertex.y();
    Double_t vz = PrimaryVertex.z();

    Double_t vr = sqrt(pow(vx, 2) + pow(vy + 2, 2));
    
    pVx->Fill(RunIndex, vx);
    pVy->Fill(RunIndex, vy);
    pVz->Fill(RunIndex, vz);
    
    HistoD0->Fill(vx, vy);
    
    ZVertexValues->Fill(vz);
    
    RVertexValues->Fill(vr);
    
    Int_t TotalTracks = mPicoDst->numberOfTracks();
    Int_t NumPrimaryTracks = 0;
    
    for (Int_t TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
    {
        StPicoTrack *pTrack = (StPicoTrack*)mPicoDst->track(TrackNum);
    
        if(!pTrack->isPrimary())
        {
            continue;
        }
        
        Double_t DCA = pTrack->gDCA(vx,vy,vz);
        Int_t NHits = pTrack->nHits();
        Int_t NHitsdEdx = pTrack->nHitsDedx();
        Int_t NHitsFit = pTrack->nHitsFit();
        Int_t NHitsPoss = pTrack->nHitsPoss();

        DCAValues->Fill(DCA);

        NHitsValues->Fill(NHits);

        NHitsdEdxValues->Fill(NHitsdEdx);

        NHitsFitOverNHitsPossValues->Fill((Double_t)NHitsFit / (Double_t)NHitsPoss);
        
        NumPrimaryTracks++;
    }
    
    
    
    Int_t Centrality = -1;

    if     ( NumPrimaryTracks >=   5 && NumPrimaryTracks <=   6 ) Centrality =  0;  // 75% - 80% (Peripheral)
    else if( NumPrimaryTracks >=   7 && NumPrimaryTracks <=   9 ) Centrality =  1;
    else if( NumPrimaryTracks >=  10 && NumPrimaryTracks <=  12 ) Centrality =  2;
    else if( NumPrimaryTracks >=  13 && NumPrimaryTracks <=  17 ) Centrality =  3;
    else if( NumPrimaryTracks >=  18 && NumPrimaryTracks <=  23 ) Centrality =  4;
    else if( NumPrimaryTracks >=  24 && NumPrimaryTracks <=  30 ) Centrality =  5;
    else if( NumPrimaryTracks >=  31 && NumPrimaryTracks <=  38 ) Centrality =  6;
    else if( NumPrimaryTracks >=  39 && NumPrimaryTracks <=  48 ) Centrality =  7;
    else if( NumPrimaryTracks >=  49 && NumPrimaryTracks <=  59 ) Centrality =  8;
    else if( NumPrimaryTracks >=  60 && NumPrimaryTracks <=  72 ) Centrality =  9;
    else if( NumPrimaryTracks >=  73 && NumPrimaryTracks <=  88 ) Centrality = 10;
    else if( NumPrimaryTracks >=  89 && NumPrimaryTracks <= 105 ) Centrality = 11;
    else if( NumPrimaryTracks >= 106 && NumPrimaryTracks <= 126 ) Centrality = 12;
    else if( NumPrimaryTracks >= 127 && NumPrimaryTracks <= 150 ) Centrality = 13;
    else if( NumPrimaryTracks >= 151 && NumPrimaryTracks <= 179 ) Centrality = 14;
    else if( NumPrimaryTracks >= 180 && NumPrimaryTracks <= 195 ) Centrality = 15;  // 0% - 5% (Central)
    
    
    if(Centrality < 0)
    {
        return kStOK;
    }
    
    EventCheck->Fill(3);
    
    Centralities->Fill(15 - Centrality);

    
    
    if ((vz <= ZVertexLowerBound) || (vz >= ZVertexUpperBound))
    {
        return kStOK;
    }

    EventCheck->Fill(4);

    if (vr >= RVertexBound)
    {
        return kStOK;
    }

    EventCheck->Fill(5);

    
    
    Double_t ProtonMass = 0.938;
    Double_t KaonMass = 0.493;
    Double_t PionMass = 0.13957;
    Double_t LambdaMass = 1.115683;
    Double_t KShortMass = 0.497611;

    Double_t InnerEPDQx = 0;
    Double_t InnerEPDQy = 0;
    Double_t OuterEPDQx = 0;
    Double_t OuterEPDQy = 0;
    Double_t InnerTPCQx = 0;
    Double_t InnerTPCQy = 0;
    Double_t OuterTPCQx = 0;
    Double_t OuterTPCQy = 0;



    if(RunIteration == 1)
    {
        //Kinematics Track Loop
        for (Int_t TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
        {
            StPicoTrack *pTrack = (StPicoTrack*)mPicoDst->track(TrackNum);

            
            if(!pTrack->isPrimary())
            {
                continue;
            } 
            
            
            Double_t px = pTrack->pMom().X();
            Double_t py = pTrack->pMom().Y();
            Double_t pz = pTrack->pMom().Z();
            Int_t q = pTrack->charge();
            Double_t tofBeta = -999.0;
            Double_t dEdx = pTrack->dEdx();
            Double_t NSigmaPr = pTrack->nSigmaProton();
            Double_t NSigmaKa = pTrack->nSigmaKaon();
            Double_t NSigmaPi = pTrack->nSigmaPion();
            Double_t DCA = pTrack->gDCA(vx,vy,vz);
            Int_t NHits = pTrack->nHits();
            Int_t NHitsdEdx = pTrack->nHitsDedx();
            Int_t NHitsFit = pTrack->nHitsFit();
            Int_t NHitsPoss = pTrack->nHitsPoss();



            Double_t BToFBeta = -999.0;
            Double_t EToFBeta = -999.0;

            Bool_t IsGoodEToFMatchFlag = false;
            
            if(pTrack->isTofTrack())
            {
                tofBeta = mPicoDst->btofPidTraits(pTrack->bTofPidTraitsIndex())->btofBeta();
                BToFBeta = mPicoDst->btofPidTraits(pTrack->bTofPidTraitsIndex())->btofBeta();
            }

            if((pTrack->isETofTrack()))
            {
                EToFFlags->Fill(mPicoDst->etofPidTraits(pTrack->eTofPidTraitsIndex())->matchFlag());

                for(int i = 0; i < NumEToFMatchFlags; i++)
                {
                    if((mPicoDst->etofPidTraits(pTrack->eTofPidTraitsIndex())->matchFlag()) == EToFMatchFlags[i])
                    {
                        IsGoodEToFMatchFlag = true;
                    }
                }
                
                if( (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag))
                {
                    tofBeta = mPicoDst->etofPidTraits(pTrack->eTofPidTraitsIndex())->beta();
                    EToFBeta = mPicoDst->etofPidTraits(pTrack->eTofPidTraitsIndex())->beta();
                }
            }
            



            if((pTrack->isTofTrack()) && ((pTrack->isETofTrack()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag)))
            {
                MSquaredBToF->Fill(BToFBeta);
                MSquaredEToF->Fill(EToFBeta);
                continue;
            }
            


            if (DCA >= DCABound)
            {
                continue;
            }
            if (NHits < NHitsBound)
            {
                continue;
            }
            if (NHitsdEdx <= NHitsdEdxBound)
            {
                continue;
            }
            if ((Double_t)NHitsFit / (Double_t)NHitsPoss <= NHitsFitOverNHitsPossBound)
            {
                continue;
            }



            if(q == 0)
            {
                continue;
            } 



            
            Double_t pt = FlowFunctions::Pt(px, py);

            Double_t p = FlowFunctions::P(px, py, pz);

            Double_t eta = FlowFunctions::Eta(px, py, pz);

            Double_t qp = FlowFunctions::QP(q, px, py, pz);

            Double_t phi = FlowFunctions::Phi(px, py);




            if(std::isnan(p))
            {
                continue;
            }
            
            
            
            pPt->Fill(RunIndex, pt);
            pEta->Fill(RunIndex, eta);



            // if((q == 1) && (pt > 0.16) && (pt < 6.0) && (eta > -2.5) && (eta < 0.0))
            // {
            //     Double_t zDeuteron = TMath::Log(dEdx / BichselZDeuteron->Eval(p));
            //     Double_t zTriton = TMath::Log(dEdx / BichselZTriton->Eval(p));
                
            //     h2_zd_vs_mom->Fill(p, zDeuteron);
            //     h2_zt_vs_mom->Fill(p, zTriton);

            //     MomentumDistributionBischel->Fill(p);
            //     ZDeuteronDistribution->Fill(zDeuteron);
            //     ZTritonDistribution->Fill(zTriton);
            // }

            //Particle Identification
            Bool_t IsKaon = false;
            Bool_t IsPion = false;
            // Bool_t IsProtonToF = false;
            Bool_t IsDeuteron = false;
            Bool_t IsTriton = false;
            Bool_t IsProtonTPC = (abs(NSigmaPr) < NSigmaPrBound) && (q == 1);

            Double_t msquared = 0;
            

            if(tofBeta > 0)
            {
                msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

                IsKaon = (abs(NSigmaKa) < NSigmaKaBound) && (msquared > KaonLowerMSquared) && (msquared < KaonUpperMSquared);
                IsPion = (abs(NSigmaPi) < NSigmaPiBound) && (msquared > PionLowerMSquared) && (msquared < PionUpperMSquared);
                // IsProtonToF = (abs(NSigmaPr) < NSigmaPrBound) && (msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared) && (q == 1);
            }

            Double_t zDeuteron = TMath::Log(dEdx / BichselZDeuteron->Eval(p));
            Double_t zTriton = TMath::Log(dEdx / BichselZTriton->Eval(p));

            DeuteronsAndTritons DAndT (p, dEdx, tofBeta, EToFBeta, zDeuteron, zTriton, false, false, false, false, false, false);




            if(!(IsKaon) && !(IsPion))
            {
                IsDeuteron = DAndT.IsDeuteron() and (q == 1);
                IsTriton = DAndT.IsTriton() and (q == 1);

                if(q == 1)
                {
                    h2_zd_vs_mom->Fill(p, zDeuteron);
                    h2_zt_vs_mom->Fill(p, zTriton);
    
                    MomentumDistributionBischel->Fill(p);
                    ZDeuteronDistribution->Fill(zDeuteron);
                    ZTritonDistribution->Fill(zTriton);
                }
            }



            



            if((IsDeuteron) && (IsTriton))
            {
                IsDeuteron = false;
                IsTriton = false;
            }

            if((IsKaon) && (IsProtonTPC))
            {
                IsProtonTPC = false;
            }

            if((IsPion) && (IsProtonTPC))
            {
                IsProtonTPC = false;
            }

            if((IsDeuteron) && (IsProtonTPC))
            {
                IsProtonTPC = false;
            }

            if((IsTriton) && (IsProtonTPC))
            {
                IsProtonTPC = false;
            }




            // if(abs(NSigmaPr) < NSigmaPrBound)
            // {
            //     Double_t mass = ProtonMass;
                
            //     Double_t y = FlowFunctions::Y(px, py, pz, mass);
                
            //     ProtonTPCDetected->Fill(eta, pt);
            //     ProtonTPCDetectedRapidity->Fill(y - yCMShift, pt);

            //     if((pTrack->isTofTrack()) && (tofBeta > 0.001))
            //     {   
            //         ProtonToFDetected->Fill(eta, pt);
            //         ProtonToFDetectedRapidity->Fill(y - yCMShift, pt);

            //         msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

            //         if((msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared))
            //         {
            //             ProtonToFDetectedRapidityMSquaredCuts->Fill(y - yCMShift, pt);
            //         }
            //     }

            //     if((pTrack->isETofTrack()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag) && (EToFBeta > 0.001))
            //     {
            //         ProtonEToFDetected->Fill(eta, pt);
            //         ProtonEToFDetectedRapidity->Fill(y - yCMShift, pt);
            //     }      
            // }
            

            // if((abs(NSigmaKa) < NSigmaKaBound) && (q > 0))
            // {
            //     Double_t mass = KaonMass;

            //     Double_t y = FlowFunctions::Y(px, py, pz, mass);
                
            //     KaonPlusTPCDetected->Fill(eta, pt);
            //     KaonPlusTPCDetectedRapidity->Fill(y - yCMShift, pt);

            //     if((pTrack->isTofTrack()) && (tofBeta > 0.001))
            //     {   
            //         KaonPlusToFDetected->Fill(eta, pt);
            //         KaonPlusToFDetectedRapidity->Fill(y - yCMShift, pt);

            //         msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

            //         if((msquared > KaonLowerMSquared) && (msquared < KaonUpperMSquared))
            //         {
            //             KaonPlusToFDetectedRapidityMSquaredCuts->Fill(y - yCMShift, pt);

            //             if(pt > 3.0)
            //             {
            //                 KaonPlusPtOutliersEta->Fill(eta);
            //                 KaonPlusPtOutliersMSquared->Fill(msquared);
            //             }
            //         }
            //     }

            //     if((pTrack->isETofTrack()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag) && (EToFBeta > 0.001))
            //     {
            //         KaonPlusEToFDetected->Fill(eta, pt);
            //         KaonPlusEToFDetectedRapidity->Fill(y - yCMShift, pt);
            //     }     
            // }

            // if((abs(NSigmaKa) < NSigmaKaBound) && (q < 0))
            // {
            //     Double_t mass = KaonMass;

            //     Double_t y = FlowFunctions::Y(px, py, pz, mass);
                
            //     KaonMinusTPCDetected->Fill(eta, pt);
            //     KaonMinusTPCDetectedRapidity->Fill(y - yCMShift, pt);

            //     if((pTrack->isTofTrack()) && (tofBeta > 0.001))
            //     {
            //         KaonMinusToFDetected->Fill(eta, pt);
            //         KaonMinusToFDetectedRapidity->Fill(y - yCMShift, pt);

            //         msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

            //         if((msquared > KaonLowerMSquared) && (msquared < KaonUpperMSquared))
            //         {
            //             KaonMinusToFDetectedRapidityMSquaredCuts->Fill(y - yCMShift, pt);
            //         }
            //     }
                
            //     if((pTrack->isETofTrack()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag) && (EToFBeta > 0.001))
            //     {
            //         KaonMinusEToFDetected->Fill(eta, pt);
            //         KaonMinusEToFDetectedRapidity->Fill(y - yCMShift, pt);
            //     }     
            // }

            // if((abs(NSigmaPi) < NSigmaPiBound) && (q > 0))
            // {
            //     Double_t mass = PionMass;

            //     Double_t y = FlowFunctions::Y(px, py, pz, mass);
                
            //     PionPlusTPCDetected->Fill(eta, pt);
            //     PionPlusTPCDetectedRapidity->Fill(y - yCMShift, pt);

            //     if((pTrack->isTofTrack()) && (tofBeta > 0.001))
            //     {
            //         PionPlusToFDetected->Fill(eta, pt);
            //         PionPlusToFDetectedRapidity->Fill(y - yCMShift, pt);

            //         msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

            //         if((msquared > PionLowerMSquared) && (msquared < PionUpperMSquared))
            //         {
            //             PionPlusToFDetectedRapidityMSquaredCuts->Fill(y - yCMShift, pt);

            //             if(pt > 3.0)
            //             {
            //                 PionPlusPtOutliersEta->Fill(eta);
            //                 PionPlusPtOutliersMSquared->Fill(msquared);
            //             }
            //         }
            //     }

            //     if((pTrack->isETofTrack()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag) && (EToFBeta > 0.001))
            //     {
            //         PionPlusEToFDetected->Fill(eta, pt);
            //         PionPlusEToFDetectedRapidity->Fill(y - yCMShift, pt);
            //     }     
            // }

            // if((abs(NSigmaPi) < NSigmaPiBound) && (q < 0))
            // {
            //     Double_t mass = PionMass;

            //     Double_t y = FlowFunctions::Y(px, py, pz, mass);
                
            //     PionMinusTPCDetected->Fill(eta, pt);
            //     PionMinusTPCDetectedRapidity->Fill(y - yCMShift, pt);

            //     if((pTrack->isTofTrack()) && (tofBeta > 0.001))
            //     {
            //         PionMinusToFDetected->Fill(eta, pt);
            //         PionMinusToFDetectedRapidity->Fill(y - yCMShift, pt);

            //         msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

            //         if((msquared > PionLowerMSquared) && (msquared < PionUpperMSquared))
            //         {
            //             PionMinusToFDetectedRapidityMSquaredCuts->Fill(y - yCMShift, pt);
            //         }
            //     }

            //     if((pTrack->isETofTrack()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag) && (EToFBeta > 0.001))
            //     {
            //         PionMinusEToFDetected->Fill(eta, pt);
            //         PionMinusEToFDetectedRapidity->Fill(y - yCMShift, pt);
            //     }     
            // }

            // if((IsDeuteron) && (DAndT.GetFoundWithDeuteronTPC()))
            // {
            //     DeuteronTPCDetected->Fill(eta, pt);

            //     if((DAndT.GetFoundWithDeuteronToF()) && (tofBeta > 0.001))
            //     {
            //         DeuteronToFDetected->Fill(eta, pt);
            //     }

            //     if((DAndT.GetFoundWithDeuteronEToF()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag) && (EToFBeta > 0.001))
            //     {
            //         DeuteronEToFDetected->Fill(eta, pt);
            //     }
            // }

            // if((IsTriton) && (DAndT.GetFoundWithTritonTPC()))
            // {
            //     TritonTPCDetected->Fill(eta, pt);

            //     if((DAndT.GetFoundWithTritonToF()) && (tofBeta > 0.001))
            //     {
            //         TritonToFDetected->Fill(eta, pt);
            //     }

            //     if((DAndT.GetFoundWithTritonEToF()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag) && (EToFBeta > 0.001))
            //     {
            //         TritonEToFDetected->Fill(eta, pt);
            //     }
            // }            





            

            if(tofBeta > 0)
            {

                Double_t msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

                HistoD4->Fill(qp, msquared);
//                     HistoD4A->Fill(qp, msquared);

//                     HistoD24->Fill(qp, NSigmaPr);
//                     HistoD25->Fill(qp, NSigmaKa);
//                     HistoD26->Fill(qp, NSigmaPi);

                // Proton criteria
                // if(IsProtonToF)
                // {
                //     double mass = ProtonMass;

                //     double y = FlowFunctions::Y(px, py, pz, mass);

                //     HistoD5->Fill(y - yCMShift);
                //     HistoD8->Fill(pt);
                //         HistoD15->Fill(p, dEdx);
                //         HistoD18->Fill(qp, msquared);

                //     HistoD21->Fill(pt);

                //     HistoD27->Fill(y - yCMShift, pt);
                // }

                // Kaon criteria
                if(IsKaon)
                {
                    Double_t mass = KaonMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                    HistoD22->Fill(pt);

                    HistoD6->Fill(y - yCMShift);
                    HistoD9->Fill(pt);
                    HistoD14->Fill(p, dEdx);
//                         HistoD19->Fill(qp, msquared);

                    if(q > 0)
                    {
                        HistoD28->Fill(y - yCMShift, pt);
                    }

                    else if(q < 0)
                    {
                        HistoD29->Fill(y - yCMShift, pt);
                    }
                }

                // Pion criteria
                if(IsPion)
                {
                    Double_t mass = PionMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                    HistoD23->Fill(pt);

                    HistoD7->Fill(y - yCMShift);
                    HistoD10->Fill(pt);
                    HistoD13->Fill(p, dEdx);
//                         HistoD20->Fill(qp, msquared);

                    if(q > 0)
                    {
                        HistoD30->Fill(y - yCMShift, pt);
                    }

                    else if(q < 0)
                    {
                        HistoD31->Fill(y - yCMShift, pt);
                    }
                }
            }

            if(IsDeuteron)
            {
                Double_t mass = DeuteronMass;

                Double_t y = FlowFunctions::Y(px, py, pz, mass);

                HistoD16->Fill(p, dEdx);
                HistoD27A->Fill(y - yCMShift, pt);
            }

            if(IsTriton)
            {
                Double_t mass = TritonMass;

                Double_t y = FlowFunctions::Y(px, py, pz, mass);

                HistoD17->Fill(p, dEdx);
                HistoD27B->Fill(y - yCMShift, pt);
            }

            if(IsProtonTPC)
            {
                    Double_t mass = ProtonMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                    HistoD5->Fill(y - yCMShift);
                    HistoD8->Fill(pt);
                    HistoD15->Fill(p, dEdx);

                    HistoD21->Fill(pt);

                    HistoD27->Fill(y - yCMShift, pt);
            }

            HistoD1->Fill(pt);
            HistoD2->Fill(eta);
            HistoD3->Fill(eta, pt);

            if(pTrack->isTofTrack())
            {
                AllTracksToFDetected->Fill(eta, pt);
            }
//                 HistoD11->Fill(Multiplicity);
            HistoD12->Fill(p, dEdx);
            HistoD32->Fill(phi);
        }
    }//End of Kinematics Track Loop


    std::vector<double> ProtonPtVec;
    std::vector<double> ProtonEtaVec;
    std::vector<double> ProtonPhiVec;
    std::vector<double> ProtonMassVec;
    std::vector<double> PionPlusPtVec;
    std::vector<double> PionPlusEtaVec;
    std::vector<double> PionPlusPhiVec;
    std::vector<double> PionPlusMassVec;
    std::vector<double> PionMinusPtVec;
    std::vector<double> PionMinusEtaVec;
    std::vector<double> PionMinusPhiVec;
    std::vector<double> PionMinusMassVec;
    
    
    //Lambda Baryon and K-Short Track Loop
    if((RunIteration == 1) || (RunIteration == 4))
    {
        for (Int_t TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
        {
            StPicoTrack *gTrack = (StPicoTrack*)mPicoDst->track(TrackNum);

            
        
        
            Double_t gpx = gTrack->gMom().X();
            Double_t gpy = gTrack->gMom().Y();
            Double_t gpz = gTrack->gMom().Z();
            Int_t q = gTrack->charge();
            Double_t tofBeta = -999.0;
            Double_t EToFBeta = -999.0;
            Double_t dEdx = gTrack->dEdx();
            Double_t NSigmaPr = gTrack->nSigmaProton();
            Double_t NSigmaKa = gTrack->nSigmaKaon();
            Double_t NSigmaPi = gTrack->nSigmaPion();
            Double_t DCA = gTrack->gDCA(vx,vy,vz);
            Int_t NHits = gTrack->nHits();
            Int_t NHitsdEdx = gTrack->nHitsDedx();
            Int_t NHitsFit = gTrack->nHitsFit();
            Int_t NHitsPoss = gTrack->nHitsPoss();



            Bool_t IsGoodEToFMatchFlag = false;
            
            if(gTrack->isTofTrack())
            {
                tofBeta = mPicoDst->btofPidTraits(gTrack->bTofPidTraitsIndex())->btofBeta();
            }

            if(gTrack->isETofTrack())
            {
                for(int i = 0; i < NumEToFMatchFlags; i++)
                {
                    if((mPicoDst->etofPidTraits(gTrack->eTofPidTraitsIndex())->matchFlag()) == EToFMatchFlags[i])
                    {
                        IsGoodEToFMatchFlag = true;
                    }
                }

                if( (mPicoDst->etofHit(gTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag))
                {
                    tofBeta = mPicoDst->etofPidTraits(gTrack->eTofPidTraitsIndex())->beta();
                    EToFBeta = mPicoDst->etofPidTraits(gTrack->eTofPidTraitsIndex())->beta();
                }
            }



            if((gTrack->isTofTrack()) && ((gTrack->isETofTrack()) && (mPicoDst->etofHit(gTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag)))
            {
                continue;
            }





            if (NHits < NHitsBound)
            {
                continue;
            }
            if (NHitsdEdx <= NHitsdEdxBound)
            {
                continue;
            }
            if ((Double_t)NHitsFit / (Double_t)NHitsPoss <= NHitsFitOverNHitsPossBound)
            {
                continue;
            }

            


            if(q == 0)
            {
                continue;
            }


            Double_t pt = FlowFunctions::Pt(gpx, gpy);

            Double_t p = FlowFunctions::P(gpx, gpy, gpz);

            Double_t eta = FlowFunctions::Eta(gpx, gpy, gpz);

            Double_t phi = FlowFunctions::Phi(gpx, gpy);

        
            
            if(std::isnan(p))
            {
                continue;
            }

            
            GlobalPt->Fill(pt);
            GlobalEta->Fill(eta);
            GlobalPhi->Fill(phi);
            GlobaldEdxVsP->Fill(p, dEdx);

        
            //Particle Identification
            Bool_t IsKaon = false;
            Bool_t IsPion = false;
            // Bool_t IsProtonToF = false;
            Bool_t IsDeuteron = false;
            Bool_t IsTriton = false;
            Bool_t IsProtonTPC = (abs(NSigmaPr) < NSigmaPrBound) && (q == 1);

            Double_t msquared = 0;



            if(tofBeta > 0)
            {
                msquared = FlowFunctions::MSquared(gpx, gpy, gpz, tofBeta);

                IsKaon = (abs(NSigmaKa) < NSigmaKaBound) && (msquared > KaonLowerMSquared) && (msquared < KaonUpperMSquared);
                IsPion = (abs(NSigmaPi) < NSigmaPiBound) && (msquared > PionLowerMSquared) && (msquared < PionUpperMSquared);
                // IsProtonToF = (abs(NSigmaPr) < NSigmaPrBound) && (msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared) && (q == 1);
            }


            
            Double_t zDeuteron = TMath::Log(dEdx / BichselZDeuteron->Eval(p));
            Double_t zTriton = TMath::Log(dEdx / BichselZTriton->Eval(p));
    
            DeuteronsAndTritons DAndT (p, dEdx, tofBeta, EToFBeta, zDeuteron, zTriton, false, false, false, false, false, false);
    
            if(!(IsKaon) && !(IsPion))
            {
                IsDeuteron = DAndT.IsDeuteron() && (q == 1);
                IsTriton = DAndT.IsTriton() && (q == 1);
            }

        

            if((IsDeuteron) && (IsTriton))
            {
                IsDeuteron = false;
                IsTriton = false;
            }

            if((IsKaon) && (IsProtonTPC))
            {
                IsProtonTPC = false;
            }

            if((IsPion) && (IsProtonTPC))
            {
                IsProtonTPC = false;
            }

            if((IsDeuteron) && (IsProtonTPC))
            {
                IsProtonTPC = false;
            }

            if((IsTriton) && (IsProtonTPC))
            {
                IsProtonTPC = false;
            }



            if((IsProtonTPC) && (DCA < 0.01))
            {
                continue;
            }

            if((IsPion) && (q < 0) && (DCA < 0.05))
            {
                continue;
            }


            
        
            if(IsProtonTPC)
            {
                ProtonPtVec.push_back(pt);
                ProtonEtaVec.push_back(eta);
                ProtonPhiVec.push_back(phi);
                ProtonMassVec.push_back(ProtonMass);

                GlobalPtProton->Fill(pt);
                GlobalEtaProton->Fill(eta);
            }

            if((IsPion) && (q > 0))
            {
                PionPlusPtVec.push_back(pt);
                PionPlusEtaVec.push_back(eta);
                PionPlusPhiVec.push_back(phi);
                PionPlusMassVec.push_back(PionMass);

                GlobalPtPionPlus->Fill(pt);
                GlobalEtaPionPlus->Fill(eta);
            }

            if((IsPion) && (q < 0))
            {
                PionMinusPtVec.push_back(pt);
                PionMinusEtaVec.push_back(eta);
                PionMinusPhiVec.push_back(phi);
                PionMinusMassVec.push_back(PionMass);

                GlobalPtPionMinus->Fill(pt);
                GlobalEtaPionMinus->Fill(eta);
            }
        }
    }//End of Lambda Baryon and K-Short Track Loop

    ProtonMultiplicity->Fill(ProtonPtVec.size());
    PionPlusMultiplicity->Fill(PionPlusPtVec.size());
    PionMinusMultiplicity->Fill(PionMinusPtVec.size());
  
    if(RunIteration == 1)
    {
        Double_t Im;

        for(size_t i = 0; i < ProtonPtVec.size(); i++)
        {
            for(size_t j = 0; j < PionMinusPtVec.size(); j++)
            {
                ROOT::Math::PtEtaPhiMVector ProtonFourVector(ProtonPtVec[i], ProtonEtaVec[i], ProtonPhiVec[i], ProtonMassVec[i]);

                ROOT::Math::PtEtaPhiMVector PionMinusFourVector(PionMinusPtVec[j], PionMinusEtaVec[j], PionMinusPhiVec[j], PionMinusMassVec[j]);

                Im = (ProtonFourVector + PionMinusFourVector).M();

                InvariantMassesLambda->Fill(Im);
                
                if((Im > LambdaLowerMass) && (Im < LambdaUpperMass))
                {                    
                    Double_t px = (ProtonFourVector + PionMinusFourVector).Px();

                    Double_t py = (ProtonFourVector + PionMinusFourVector).Py();
    
                    Double_t pz = (ProtonFourVector + PionMinusFourVector).Pz();
    
                    Double_t pt = sqrt(pow(px,2)+pow(py,2));
                    
                    Double_t mass = LambdaMass;
    
                    Double_t y = FlowFunctions::Y(px, py, pz, mass);
                 
                    LambdaAcceptance->Fill(y - yCMShift, pt);
                }
            }
        }

        for(size_t i = 0; i < PionPlusPtVec.size(); i++)
        {
            for(size_t j = 0; j < PionMinusPtVec.size(); j++)
            {
                ROOT::Math::PtEtaPhiMVector PionPlusFourVector(PionPlusPtVec[i], PionPlusEtaVec[i], PionPlusPhiVec[i], PionPlusMassVec[i]);

                ROOT::Math::PtEtaPhiMVector PionMinusFourVector(PionMinusPtVec[j], PionMinusEtaVec[j], PionMinusPhiVec[j], PionMinusMassVec[j]);

                Im = (PionPlusFourVector + PionMinusFourVector).M();

                InvariantMassesKShort->Fill(Im);

                if(false)
                {                    
                    Double_t px = (PionPlusFourVector + PionMinusFourVector).Px();

                    Double_t py = (PionPlusFourVector + PionMinusFourVector).Py();
    
                    Double_t pz = (PionPlusFourVector + PionMinusFourVector).Pz();
    
                    Double_t pt = sqrt(pow(px,2)+pow(py,2));
                    
                    Double_t mass = KShortMass;
    
                    Double_t y = FlowFunctions::Y(px, py, pz, mass);
                 
                    KShortAcceptance->Fill(y - yCMShift, pt);
                }
            }
        }
    }

    Double_t FourierCorrectionTermInnerEPD = 0;
    Double_t FourierCorrectionTermOuterEPD = 0;
    Double_t FourierCorrectionTermOuterTPC = 0;

    Int_t GoodTracksCounterInnerEPD = 0;
    Int_t GoodTracksCounterOuterEPD = 0;
    Int_t GoodTracksCounterOuterTPC = 0;

    //TPC Track Counting loop
    for (Int_t TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
    {
            StPicoTrack *pTrack = (StPicoTrack*)mPicoDst->track(TrackNum);

            if(!pTrack->isPrimary())
            {
                continue;
            }

            Double_t px = pTrack->pMom().X();
            Double_t py = pTrack->pMom().Y();
            Double_t pz = pTrack->pMom().Z();
            Int_t q = pTrack->charge();
            Double_t DCA = pTrack->gDCA(vx,vy,vz);
            Int_t NHits = pTrack->nHits();
            Int_t NHitsdEdx = pTrack->nHitsDedx();
            Int_t NHitsFit = pTrack->nHitsFit();
            Int_t NHitsPoss = pTrack->nHitsPoss();



            OverallTrackCheckNoCuts->Fill(1);

            if (DCA >= DCABound)
            {
                continue;
            }
            if (NHits < NHitsBound)
            {
                continue;
            }
            if (NHitsdEdx <= NHitsdEdxBound)
            {
                continue;
            }
            if ((double)NHitsFit / (double)NHitsPoss <= NHitsFitOverNHitsPossBound)
            {
                continue;
            }

            OverallTrackCheckQACuts->Fill(1);


            if(q == 0)
            {
                continue;
            }

            Double_t eta = FlowFunctions::Eta(px, py, pz);

            if ((eta > OuterTPCLowerLimit) && (eta < OuterTPCUpperLimit))
            {
                GoodTracksCounterOuterTPC += 1;
            }
    }//End TPC Track Counting loop

    Int_t nEPDHits = mPicoDst->numberOfEpdHits();

//         Int_t nEPDHits = (Int_t)nEPDhits;

    //EPD Hit Counting loop
    for (Int_t index = 0; index < nEPDHits; index++)
    {
        StPicoEpdHit *pEpdHit = mPicoDst->epdHit(index);

        if(!pEpdHit->isGood())
        {
            continue;
        }

        Int_t EPDID = pEpdHit->id();

        if(EPDID > 0)
        {
            continue;
        }

        TileVector *TVec = new TileVector(epdGeom, EPDID, vx, vy, vz, InnerEPDHighRing, OuterEPDLowRing);

        Double_t eta = TVec->EPDEta();

        Int_t RingNumber = TVec->EPDRow();

        HistoD32B->Fill(eta, RingNumber);

        if (TVec->IsInnerEPD() && !(TVec->IsOuterEPD()))
        {
            GoodTracksCounterInnerEPD += 1;
        }

        if (TVec->IsOuterEPD() && !(TVec->IsInnerEPD()))
        {
            GoodTracksCounterOuterEPD += 1;
        }

        delete TVec;
    }//End EPD Hit Counting loop


    
    HitCountOuterEPD->Fill(GoodTracksCounterOuterEPD);

    if((GoodTracksCounterOuterEPD >= 9) && (GoodTracksCounterOuterEPD < 16))
    {   
        CentralitiesNineToFifteenOuterEPDHitsOnly->Fill(15 - Centrality);
    }


    
    if((GoodTracksCounterInnerEPD < NumberOfGoodTracksInnerEPD) || (GoodTracksCounterOuterEPD < NumberOfGoodTracksOuterEPD) || (GoodTracksCounterOuterTPC < NumberOfGoodTracksOuterTPC))
    {
        return kStOK;
    }


    EventCheck->Fill(6);

    //Q Vector Calulator loop (TPC)
    for (Int_t TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
    {
            StPicoTrack *pTrack = (StPicoTrack*)mPicoDst->track(TrackNum);

            if(!pTrack->isPrimary())
            {
                continue;
            }

            Double_t px = pTrack->pMom().X();
            Double_t py = pTrack->pMom().Y();
            Double_t pz = pTrack->pMom().Z();
            Int_t q = pTrack->charge();
            Double_t DCA = pTrack->gDCA(vx,vy,vz);
            Int_t NHits = pTrack->nHits();
            Int_t NHitsdEdx = pTrack->nHitsDedx();
            Int_t NHitsFit = pTrack->nHitsFit();
            Int_t NHitsPoss = pTrack->nHitsPoss();
        


            if (DCA >= DCABound)
            {
                continue;
            }

            if (NHits < NHitsBound)
            {
                continue;
            }

            if (NHitsdEdx <= NHitsdEdxBound)
            {
                continue;
            }

            if ((double)NHitsFit / (double)NHitsPoss <= NHitsFitOverNHitsPossBound)
            {
                continue;
            }



            if(q == 0)
            {
                continue;
            }

            Double_t pt = FlowFunctions::Pt(px, py);

            Double_t eta = FlowFunctions::Eta(px, py, pz);

            Double_t phi = FlowFunctions::Phi(px, py);

            if((pt < 0.2) || (pt > 2.0))
            {
                continue;
            }

            if ((eta > InnerTPCLowerLimit) && (eta < InnerTPCUpperLimit))
            {
                if(nV % 2 == 0)
                {
                    InnerTPCQy += pt*sin(nPsi*phi);
                    InnerTPCQx += pt*cos(nPsi*phi);
                }

                else if(nV % 2 == 1)
                {
                    if(eta > yCMShift)
                    {
                        InnerTPCQy += pt*sin(nPsi*phi);
                        InnerTPCQx += pt*cos(nPsi*phi);
                    }

                    else if(eta < yCMShift)
                    {
                        InnerTPCQy -= pt*sin(nPsi*phi);
                        InnerTPCQx -= pt*cos(nPsi*phi);
                    }
                }
            }

            if ((eta > OuterTPCLowerLimit) && (eta < OuterTPCUpperLimit))
            {
                if(nV % 2 == 0)
                {
                    OuterTPCQy += pt*sin(nPsi*phi);
                    OuterTPCQx += pt*cos(nPsi*phi);
                }

                else if(nV % 2 == 1)
                {
                    if(eta > yCMShift)
                    {
                        OuterTPCQy += pt*sin(nPsi*phi);
                        OuterTPCQx += pt*cos(nPsi*phi);
                    }

                    else if(eta < yCMShift)
                    {
                        OuterTPCQy -= pt*sin(nPsi*phi);
                        OuterTPCQx -= pt*cos(nPsi*phi);
                    }
                }

            }
    }

    //Q Vector Calculator loop (EPD)
    for (int index = 0; index < nEPDHits; index++)
    {
        StPicoEpdHit *pEpdHit = mPicoDst->epdHit(index);

        Int_t EPDID = pEpdHit->id();
        Double_t EPDnMIP = pEpdHit->nMIP();

        if(EPDID > 0)
        {
            continue;
        }

        TileVector *TVec = new TileVector(epdGeom, EPDID, vx, vy, vz, InnerEPDHighRing, OuterEPDLowRing);

        Double_t phi = TVec->EPDPhi();

        HistoD32A->Fill(phi);

        if(EPDnMIP < 0.3)
        {
            EPDnMIP = 0;
        }

        if(EPDnMIP > 2.0)
        {
            EPDnMIP = 2.0;
        }

        if(nV % 2 == 0)
        {
            if (TVec->IsInnerEPD() && !(TVec->IsOuterEPD()))
            {
                InnerEPDQy += EPDnMIP*sin(nPsi*phi);
                InnerEPDQx += EPDnMIP*cos(nPsi*phi);
            }

            if (TVec->IsOuterEPD() && !(TVec->IsInnerEPD()))
            {
                OuterEPDQy += EPDnMIP*sin(nPsi*phi);
                OuterEPDQx += EPDnMIP*cos(nPsi*phi);
            }
        }

        else
        {
            if (TVec->IsInnerEPD() && !(TVec->IsOuterEPD()))
            {
                InnerEPDQy -= EPDnMIP*sin(nPsi*phi);
                InnerEPDQx -= EPDnMIP*cos(nPsi*phi);
            }

            if (TVec->IsOuterEPD() && !(TVec->IsInnerEPD()))
            {
                OuterEPDQy -= EPDnMIP*sin(nPsi*phi);
                OuterEPDQx -= EPDnMIP*cos(nPsi*phi);
            }
        }

        delete TVec;
    }

    if((InnerEPDQx == 0) && (InnerEPDQy == 0))
    {
        return kStOK;
    }

    if((OuterEPDQx == 0) && (OuterEPDQy == 0))
    {
        return kStOK;
    }

//         if((InnerTPCQx == 0) && (InnerTPCQy == 0))
//         {
//             return 0;
//         }

    if((OuterTPCQx == 0) && (OuterTPCQy == 0))
    {
        return kStOK;
    }

    EventCheck->Fill(7);





    Double_t PsiInnerEPDRaw = 0;
    Double_t PsiOuterEPDRaw = 0;
    Double_t PsiOuterTPCRaw = 0;

    Double_t PsiInnerEPDRecentered = 0;
    Double_t PsiOuterEPDRecentered = 0;
    Double_t PsiOuterTPCRecentered = 0;

    Double_t InnerEPDSineAverageJth = 0;
    Double_t InnerEPDCosineAverageJth = 0;
    Double_t OuterEPDSineAverageJth = 0;
    Double_t OuterEPDCosineAverageJth = 0;
    Double_t OuterTPCSineAverageJth = 0;
    Double_t OuterTPCCosineAverageJth = 0;

    Double_t PsiInnerEPDFourierCorrected = 0;
    Double_t PsiOuterEPDFourierCorrected = 0;
    Double_t PsiOuterTPCFourierCorrected = 0;

    if(RunIteration == 1)
    {
        HistoInnerEPDQxRaw[Centrality]->Fill(InnerEPDQx);
        HistoInnerEPDQyRaw[Centrality]->Fill(InnerEPDQy);
        HistoOuterEPDQxRaw[Centrality]->Fill(OuterEPDQx);
        HistoOuterEPDQyRaw[Centrality]->Fill(OuterEPDQy);  
        HistoOuterTPCQxRaw[Centrality]->Fill(OuterTPCQx);
        HistoOuterTPCQyRaw[Centrality]->Fill(OuterTPCQy);

        HistoInnerEPDQxRawByRun[Centrality]->Fill(RunIndex, InnerEPDQx);
        HistoInnerEPDQyRawByRun[Centrality]->Fill(RunIndex, InnerEPDQy);
        HistoOuterEPDQxRawByRun[Centrality]->Fill(RunIndex, OuterEPDQx);
        HistoOuterEPDQyRawByRun[Centrality]->Fill(RunIndex, OuterEPDQy);  
        HistoOuterTPCQxRawByRun[Centrality]->Fill(RunIndex, OuterTPCQx);
        HistoOuterTPCQyRawByRun[Centrality]->Fill(RunIndex, OuterTPCQy);

        PsiInnerEPDRaw = (1.0/nPsi)*atan2(InnerEPDQy, InnerEPDQx);
        PsiOuterEPDRaw = (1.0/nPsi)*atan2(OuterEPDQy, OuterEPDQx);
        PsiOuterTPCRaw = (1.0/nPsi)*atan2(OuterTPCQy, OuterTPCQx);

        HistoD33[Centrality]->Fill(PsiInnerEPDRaw);
        HistoD36[Centrality]->Fill(PsiOuterEPDRaw);
        HistoD39[Centrality]->Fill(PsiOuterTPCRaw);
    }

    if(RunIteration >= 2)
    {
        InnerEPDQxMean = InnerEPDQxMeanHisto[Centrality]->GetBinContent(RunIndex);
        InnerEPDQyMean = InnerEPDQyMeanHisto[Centrality]->GetBinContent(RunIndex);
        OuterEPDQxMean = OuterEPDQxMeanHisto[Centrality]->GetBinContent(RunIndex);
        OuterEPDQyMean = OuterEPDQyMeanHisto[Centrality]->GetBinContent(RunIndex);
        OuterTPCQxMean = OuterTPCQxMeanHisto[Centrality]->GetBinContent(RunIndex);
        OuterTPCQyMean = OuterTPCQyMeanHisto[Centrality]->GetBinContent(RunIndex);

        PsiInnerEPDRecentered = (1.0/nPsi)*atan2(InnerEPDQy - InnerEPDQyMean, InnerEPDQx - InnerEPDQxMean);
        PsiOuterEPDRecentered = (1.0/nPsi)*atan2(OuterEPDQy - OuterEPDQyMean, OuterEPDQx - OuterEPDQxMean);
        PsiOuterTPCRecentered = (1.0/nPsi)*atan2(OuterTPCQy - OuterTPCQyMean, OuterTPCQx - OuterTPCQxMean);
    }

    if(RunIteration == 2)
    {
        HistoInnerEPDQxRecentered[Centrality]->Fill(InnerEPDQx - InnerEPDQxMean);
        HistoInnerEPDQyRecentered[Centrality]->Fill(InnerEPDQy - InnerEPDQyMean);

        HistoOuterEPDQxRecentered[Centrality]->Fill(OuterEPDQx - OuterEPDQxMean);
        HistoOuterEPDQyRecentered[Centrality]->Fill(OuterEPDQy - OuterEPDQyMean);

        HistoOuterTPCQxRecentered[Centrality]->Fill(OuterTPCQx - OuterTPCQxMean);
        HistoOuterTPCQyRecentered[Centrality]->Fill(OuterTPCQy - OuterTPCQyMean);
    }

    if(RunIteration == 2)
    {
        HistoD34[Centrality]->Fill(PsiInnerEPDRecentered);
        HistoD37[Centrality]->Fill(PsiOuterEPDRecentered);
        HistoD40[Centrality]->Fill(PsiOuterTPCRecentered);

        for (int j = 1; j < FourierCorrectionTerms + 1; j++)
        {
            HistoInnerEPDSineAverages[Centrality]->Fill(RunIndex, j, -1*sin(j*nPsi*PsiInnerEPDRecentered));
            HistoInnerEPDCosineAverages[Centrality]->Fill(RunIndex, j, cos(j*nPsi*PsiInnerEPDRecentered));
            HistoOuterEPDSineAverages[Centrality]->Fill(RunIndex, j, -1*sin(j*nPsi*PsiOuterEPDRecentered));
            HistoOuterEPDCosineAverages[Centrality]->Fill(RunIndex, j, cos(j*nPsi*PsiOuterEPDRecentered));
            HistoOuterTPCSineAverages[Centrality]->Fill(RunIndex, j, -1*sin(j*nPsi*PsiOuterTPCRecentered));
            HistoOuterTPCCosineAverages[Centrality]->Fill(RunIndex, j, cos(j*nPsi*PsiOuterTPCRecentered));
        }
    }

    if(RunIteration >= 3)
    {
        for (int j = 1; j < FourierCorrectionTerms + 1; j++)
        {
            InnerEPDSineAverageJth = InnerEPDSineAverageProfile[Centrality]->GetBinContent(RunIndex, j);
            InnerEPDCosineAverageJth = InnerEPDCosineAverageProfile[Centrality]->GetBinContent(RunIndex, j);
            OuterEPDSineAverageJth = OuterEPDSineAverageProfile[Centrality]->GetBinContent(RunIndex, j);
            OuterEPDCosineAverageJth = OuterEPDCosineAverageProfile[Centrality]->GetBinContent(RunIndex, j);
            OuterTPCSineAverageJth = OuterTPCSineAverageProfile[Centrality]->GetBinContent(RunIndex, j);
            OuterTPCCosineAverageJth = OuterTPCCosineAverageProfile[Centrality]->GetBinContent(RunIndex, j);

            FourierCorrectionTermInnerEPD += (2.0/(j*(Double_t)nPsi))*(InnerEPDSineAverageJth*cos(j*nPsi*PsiInnerEPDRecentered) + InnerEPDCosineAverageJth*sin(j*nPsi*PsiInnerEPDRecentered));
            FourierCorrectionTermOuterEPD += (2.0/(j*(Double_t)nPsi))*(OuterEPDSineAverageJth*cos(j*nPsi*PsiOuterEPDRecentered) + OuterEPDCosineAverageJth*sin(j*nPsi*PsiOuterEPDRecentered));
            FourierCorrectionTermOuterTPC += (2.0/(j*(Double_t)nPsi))*(OuterTPCSineAverageJth*cos(j*nPsi*PsiOuterTPCRecentered) + OuterTPCCosineAverageJth*sin(j*nPsi*PsiOuterTPCRecentered));
        }

        PsiInnerEPDFourierCorrected = PsiInnerEPDRecentered + FourierCorrectionTermInnerEPD;
        PsiOuterEPDFourierCorrected = PsiOuterEPDRecentered + FourierCorrectionTermOuterEPD;
        PsiOuterTPCFourierCorrected = PsiOuterTPCRecentered + FourierCorrectionTermOuterTPC;
    }

    if(RunIteration == 3)
    {
        HistoD35[Centrality]->Fill(PsiInnerEPDFourierCorrected);
        HistoD38[Centrality]->Fill(PsiOuterEPDFourierCorrected);
        HistoD41[Centrality]->Fill(PsiOuterTPCFourierCorrected);

        Double_t R11TopLeftTerm = cos(nV*(PsiInnerEPDFourierCorrected - PsiOuterEPDFourierCorrected));
        Double_t R11TopRightTerm = cos(nV*(PsiInnerEPDFourierCorrected - PsiOuterTPCFourierCorrected));
        Double_t R11BottomTerm = cos(nV*(PsiOuterEPDFourierCorrected - PsiOuterTPCFourierCorrected));

        Centrality = 15 - Centrality;

        HistoD51->Fill(Centrality, R11TopLeftTerm);
        HistoD52->Fill(Centrality, R11TopRightTerm);
        HistoD53->Fill(Centrality, R11BottomTerm);

        for (int index = 1; index < HistoD51->GetNbinsX() + 1; index++)
        {
            HistoD51->GetXaxis()->SetBinLabel(index, CentralityXLabels[index - 1]);
            HistoD52->GetXaxis()->SetBinLabel(index, CentralityXLabels[index - 1]);
            HistoD53->GetXaxis()->SetBinLabel(index, CentralityXLabels[index - 1]);
        }
    }



    if(Centrality < 4)
    {
        return kStOK;
    }

    EventCheck->Fill(8);




    Double_t ResolutionCorrectionFactor = 0;

    Centrality = 15 - Centrality;

    if(RunIteration == 4)
    {
        ResolutionCorrectionFactor = HistoD54->GetBinContent(Centrality + 1);

        if (ResolutionCorrectionFactor == 0)
        {
            return kStOK;
        }
    }





    //Fourth Pass (Resolution Corrected values)
    if(RunIteration == 4)
    {
        TH2D *TPCEfficiencyHistogramKaonPlus = (TH2D*)TPCEfficiencyFile->Get("h2_ratio_kp");
        TH2D *ToFEfficiencyHistogramKaonPlus = (TH2D*)ToFEfficiencyFile->Get("h2_ratio_tof");
    
        TH2D *TPCEfficiencyHistogramKaonMinus = (TH2D*)TPCEfficiencyFile->Get("h2_ratio_km");
        TH2D *ToFEfficiencyHistogramKaonMinus = (TH2D*)ToFEfficiencyFile->Get("h2_ratio_tof");
    
        TH2D *TPCEfficiencyHistogramPionPlus = (TH2D*)TPCEfficiencyFile->Get("h2_ratio_pp");
        TH2D *ToFEfficiencyHistogramPionPlus = (TH2D*)ToFEfficiencyFile->Get("h2_ratio_tof");
    
        TH2D *TPCEfficiencyHistogramPionMinus = (TH2D*)TPCEfficiencyFile->Get("h2_ratio_pm");
        TH2D *ToFEfficiencyHistogramPionMinus = (TH2D*)ToFEfficiencyFile->Get("h2_ratio_tof");
    
        TH2D *TPCEfficiencyHistogramDeuteron = (TH2D*)TPCEfficiencyFileDandT->Get("h2_ratio_de");
        TH2D *ToFEfficiencyHistogramDeuteron = (TH2D*)ToFEfficiencyFile->Get("h2_ratio_tof");
    
        TH2D *TPCEfficiencyHistogramTriton = (TH2D*)TPCEfficiencyFileDandT->Get("h2_ratio_tr");
        TH2D *ToFEfficiencyHistogramTriton = (TH2D*)ToFEfficiencyFile->Get("h2_ratio_tof");
    
        TH2D *TPCEfficiencyHistogramProton = (TH2D*)TPCEfficiencyFile->Get("h2_ratio_pr");


        
        //Flow Calulator loop
        for (int TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
        {
            StPicoTrack *pTrack = (StPicoTrack*)mPicoDst->track(TrackNum);
    
            if(!pTrack->isPrimary())
            {
                continue;
            }
    
            Double_t px = pTrack->pMom().X();
            Double_t py = pTrack->pMom().Y();
            Double_t pz = pTrack->pMom().Z();
            Int_t q = pTrack->charge();
            Double_t tofBeta = -999.0;
            Double_t EToFBeta = -999.0;
            Double_t dEdx = pTrack->dEdx();
            Double_t NSigmaPr = pTrack->nSigmaProton();
            Double_t NSigmaKa = pTrack->nSigmaKaon();
            Double_t NSigmaPi = pTrack->nSigmaPion();
            Double_t DCA = pTrack->gDCA(vx,vy,vz);
            Int_t NHits = pTrack->nHits();
            Int_t NHitsdEdx = pTrack->nHitsDedx();
            Int_t NHitsFit = pTrack->nHitsFit();
            Int_t NHitsPoss = pTrack->nHitsPoss();
    
    
            
    
            Bool_t IsGoodEToFMatchFlag = false;
            
            if(pTrack->isTofTrack())
            {
                tofBeta = mPicoDst->btofPidTraits(pTrack->bTofPidTraitsIndex())->btofBeta();
            }
    
            if(pTrack->isETofTrack())
            {
                for(int i = 0; i < NumEToFMatchFlags; i++)
                {
                    if((mPicoDst->etofPidTraits(pTrack->eTofPidTraitsIndex())->matchFlag()) == EToFMatchFlags[i])
                    {
                        IsGoodEToFMatchFlag = true;
                    }
                }
    
                if((mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag))
                {
                    tofBeta = mPicoDst->etofPidTraits(pTrack->eTofPidTraitsIndex())->beta();
                    EToFBeta = mPicoDst->etofPidTraits(pTrack->eTofPidTraitsIndex())->beta();
                }
            }
    
    
    
            if((pTrack->isTofTrack()) && (pTrack->isETofTrack()) && ((mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag)))
            {
                continue;
            }
    
            
    
            if (DCA >= DCABound)
            {
                continue;
            }
    
            if (NHits < NHitsBound)
            {
                continue;
            }
    
            if (NHitsdEdx <= NHitsdEdxBound)
            {
                continue;
            }
    
            if ((Double_t)NHitsFit / (Double_t)NHitsPoss <= NHitsFitOverNHitsPossBound)
            {
                continue;
            }
    
    
    
            if(q == 0)
            {
                continue;
            }
    
    
    
    
    
            Double_t pt = FlowFunctions::Pt(px, py);
    
            Double_t p = FlowFunctions::P(px, py, pz);
    
            Double_t eta = FlowFunctions::Eta(px, py, pz);
    
    
    
            if(std::isnan(p))
            {
                continue;
            }


    
    
 
    
            //Particle Identification
            Bool_t IsKaon = false;
            Bool_t IsPion = false;
            // Bool_t IsProtonToF = false;
            Bool_t IsDeuteron = false;
            Bool_t IsTriton = false;
            Bool_t IsProtonTPC = (abs(NSigmaPr) < NSigmaPrBound) && (q == 1);//(p < 2.0) && (q == 1);
    
    
            if(tofBeta > 0)
            {
                Double_t msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);
    
                IsKaon = (abs(NSigmaKa) < NSigmaKaBound) && (msquared > KaonLowerMSquared) && (msquared < KaonUpperMSquared);
                IsPion = (abs(NSigmaPi) < NSigmaPiBound) && (msquared > PionLowerMSquared) && (msquared < PionUpperMSquared);
                // IsProtonToF = (abs(NSigmaPr) < NSigmaPrBound) && (msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared) && (p > 2.0) && (q == 1);
            }
    
            Bool_t FoundWithDeuteronTPC = false;
            Bool_t FoundWithDeuteronToF = false;
            Bool_t FoundWithDeuteronEToF = false;
            Bool_t FoundWithTritonTPC = false;
            Bool_t FoundWithTritonToF = false;
            Bool_t FoundWithTritonEToF = false;
            
            Double_t zDeuteron = TMath::Log(dEdx / BichselZDeuteron->Eval(p));
            Double_t zTriton = TMath::Log(dEdx / BichselZTriton->Eval(p));
    
            DeuteronsAndTritons DAndT (p, dEdx, tofBeta, EToFBeta, zDeuteron, zTriton, FoundWithDeuteronTPC, FoundWithDeuteronToF, FoundWithDeuteronEToF, FoundWithTritonTPC, FoundWithTritonToF, FoundWithTritonEToF);
    
            if(!(IsKaon) && !(IsPion))
            {
                IsDeuteron = DAndT.IsDeuteron() && (q == 1);
                IsTriton = DAndT.IsTriton() && (q == 1);
    
                FoundWithDeuteronTPC = DAndT.GetFoundWithDeuteronTPC();
                FoundWithDeuteronToF = DAndT.GetFoundWithDeuteronToF();
                FoundWithDeuteronEToF = DAndT.GetFoundWithDeuteronEToF();
                FoundWithTritonTPC = DAndT.GetFoundWithTritonTPC();
                FoundWithTritonToF = DAndT.GetFoundWithTritonToF();
                FoundWithTritonEToF = DAndT.GetFoundWithTritonEToF();
            }
    
            if((IsDeuteron) && (IsTriton))
            {
                IsDeuteron = false;
                IsTriton = false;
            }
    
            if((IsKaon) && (IsProtonTPC))
            {
                IsProtonTPC = false;
            }
    
            if((IsPion) && (IsProtonTPC))
            {
                IsProtonTPC = false;
            }
    
            if((IsDeuteron) && (IsProtonTPC))
            {
                IsProtonTPC = false;
            }
    
            if((IsTriton) && (IsProtonTPC))
            {
                IsProtonTPC = false;
            }


            


            if(tofBeta > 0)
            {
                 // if(IsProtonToF)
                 // {
                 //    Double_t mass = ProtonMass;

                 //    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                 //    Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

                 //    Bool_t IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                 //     TH2D *TPCEfficiencyHistogram = (TH2D*)TPCEfficiencyFile->Get("h2_ratio_pr");
                 //     TH2D *ToFEfficiencyHistogram = (TH2D*)ToFEfficiencyFile->Get("h2_ratio_tof");

                 //    Int_t TPCEfficiencyBinX = TPCEfficiencyHistogram->GetXaxis()->FindBin(y - yCMShift);
                 //    Int_t TPCEfficiencyBinY = TPCEfficiencyHistogram->GetYaxis()->FindBin(pt);
                 //    Int_t ToFEfficiencyBinX = ToFEfficiencyHistogram->GetXaxis()->FindBin(eta);
                 //    Int_t ToFEfficiencyBinY = ToFEfficiencyHistogram->GetYaxis()->FindBin(pt);

                 //    Double_t TPCEfficiency = TPCEfficiencyHistogram->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);
                 //    Double_t ToFEfficiency = ToFEfficiencyHistogram->GetBinContent(ToFEfficiencyBinX, ToFEfficiencyBinY);

                 //    if((TPCEfficiency == 0) || (TPCEfficiency > 1.3) || (ToFEfficiency == 0))
                 //    {
                 //        continue;
                 //    }

                 //     if(IsGoodProton)
                 //     {
                 //         MostlyGoodProtonTrackCheck->Fill(1);

                 //         HistoD44C->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                 //         HistoD80->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));

                 //         if((y - yCMShift) < (UpperYMinusYCMShift / 2))
                 //         {
                 //             GoodProtonTrackCheck->Fill(1);

                 //             HistoD54A->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                 //             HistoD79->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));

                 //             if((Centrality >= 2) || (Centrality <= 7))
                 //             {
                 //                 if(((y - yCMShift) > 0.0) && ((y - yCMShift) < 0.1))
                 //                 {
                 //                     VnVsPtProton0_00Through0_10->Fill(pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                 //                     VnOverAVsPtOverAProton0_00Through0_10->Fill(pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                 //                 }

                 //                 if(((y - yCMShift) > 0.1) && ((y - yCMShift) < 0.2))
                 //                 {
                 //                     VnVsPtProton0_10Through0_20->Fill(pt, 1.5 * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (TPCEfficiency * ToFEfficiency));
                 //                     VnOverAVsPtOverAProton0_10Through0_20->Fill(pt, 1.5 * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (TPCEfficiency * ToFEfficiency));
                 //                 }

                 //                 if(((y - yCMShift) > 0.2) && ((y - yCMShift) < 0.3))
                 //                 {
                 //                     VnVsPtProton0_20Through0_30->Fill(pt, 2.0 * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (TPCEfficiency * ToFEfficiency));
                 //                     VnOverAVsPtOverAProton0_20Through0_30->Fill(pt, 2.0 * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (TPCEfficiency * ToFEfficiency));
                 //                 }

                 //                 if(((y - yCMShift) > 0.3) && ((y - yCMShift) < 0.4))
                 //                 {
                 //                     VnVsPtProton0_30Through0_40->Fill(pt, 2.5 * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (TPCEfficiency * ToFEfficiency));
                 //                     VnOverAVsPtOverAProton0_30Through0_40->Fill(pt, 2.5 * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (TPCEfficiency * ToFEfficiency));
                 //                 }
                 //             }
                 //         }
                 //     }
                 //  }

                if(IsKaon)
                {
                    Double_t mass = KaonMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                    Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

                    Bool_t IsGoodKaon = (pt > KaonLowerPt) && (pt < KaonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                    if(q > 0)
                    {
                        Int_t TPCEfficiencyBinX = TPCEfficiencyHistogramKaonPlus->GetXaxis()->FindBin(y - yCMShift);
                        Int_t TPCEfficiencyBinY = TPCEfficiencyHistogramKaonPlus->GetYaxis()->FindBin(pt);
                        Int_t ToFEfficiencyBinX = ToFEfficiencyHistogramKaonPlus->GetXaxis()->FindBin(eta);
                        Int_t ToFEfficiencyBinY = ToFEfficiencyHistogramKaonPlus->GetYaxis()->FindBin(pt);

                        Double_t TPCEfficiency = TPCEfficiencyHistogramKaonPlus->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);
                        Double_t ToFEfficiency = ToFEfficiencyHistogramKaonPlus->GetBinContent(ToFEfficiencyBinX, ToFEfficiencyBinY);

                        if((TPCEfficiency == 0) || (TPCEfficiency > 1.3) || (ToFEfficiency == 0))
                        {
                            continue;
                        }

                        KaonPlusTrackCheck->Fill(1);

                        if(IsGoodKaon)
                        {
                            MostlyGoodKaonPlusTrackCheck->Fill(1);

                            HistoD47B->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                            HistoD82->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));

                            if((y - yCMShift) < (UpperYMinusYCMShift / 2))
                            {
                                GoodKaonPlusTrackCheck->Fill(1);

                                HistoD54B->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                                HistoD81->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                            }
                        }
                    }

                    else if(q < 0)
                    {
                        Int_t TPCEfficiencyBinX = TPCEfficiencyHistogramKaonMinus->GetXaxis()->FindBin(y - yCMShift);
                        Int_t TPCEfficiencyBinY = TPCEfficiencyHistogramKaonMinus->GetYaxis()->FindBin(pt);
                        Int_t ToFEfficiencyBinX = ToFEfficiencyHistogramKaonMinus->GetXaxis()->FindBin(eta);
                        Int_t ToFEfficiencyBinY = ToFEfficiencyHistogramKaonMinus->GetYaxis()->FindBin(pt);

                        Double_t TPCEfficiency = TPCEfficiencyHistogramKaonMinus->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);
                        Double_t ToFEfficiency = ToFEfficiencyHistogramKaonMinus->GetBinContent(ToFEfficiencyBinX, ToFEfficiencyBinY);

                        if((TPCEfficiency == 0) || (TPCEfficiency > 1.3) || (ToFEfficiency == 0))
                        {
                            continue;
                        }

                        KaonMinusTrackCheck->Fill(1);

                        if(IsGoodKaon)
                        {
                            MostlyGoodKaonMinusTrackCheck->Fill(1);

                            HistoD47C->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                            HistoD84->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                            
                            if((y - yCMShift) < (UpperYMinusYCMShift / 2))
                            {
                                GoodKaonMinusTrackCheck->Fill(1);

                                HistoD54C->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                                HistoD83->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                            }
                        }
                    }

                }


                if(IsPion)
                {
                    Double_t mass = PionMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                    Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

                    Bool_t IsGoodPion = (pt > PionLowerPt) && (pt < PionUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                    if(q > 0)
                    {
                        Int_t TPCEfficiencyBinX = TPCEfficiencyHistogramPionPlus->GetXaxis()->FindBin(y - yCMShift);
                        Int_t TPCEfficiencyBinY = TPCEfficiencyHistogramPionPlus->GetYaxis()->FindBin(pt);
                        Int_t ToFEfficiencyBinX = ToFEfficiencyHistogramPionPlus->GetXaxis()->FindBin(eta);
                        Int_t ToFEfficiencyBinY = ToFEfficiencyHistogramPionPlus->GetYaxis()->FindBin(pt);

                        Double_t TPCEfficiency = TPCEfficiencyHistogramPionPlus->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);
                        Double_t ToFEfficiency = ToFEfficiencyHistogramPionPlus->GetBinContent(ToFEfficiencyBinX, ToFEfficiencyBinY);

                        if((TPCEfficiency == 0) || (TPCEfficiency > 1.3) || (ToFEfficiency == 0))
                        {
                            continue;
                        }  

                        PionPlusTrackCheck->Fill(1);

                        if(IsGoodPion)
                        {
                            MostlyGoodPionPlusTrackCheck->Fill(1);

                            HistoD50B->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency)); 
                            HistoD86->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                            
                            if((y - yCMShift) < (UpperYMinusYCMShift / 2))
                            {
                                GoodPionPlusTrackCheck->Fill(1);            

                                HistoD54D->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                                HistoD85->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                            }
                        }
                    }

                    else if(q < 0)
                    {
                        Int_t TPCEfficiencyBinX = TPCEfficiencyHistogramPionMinus->GetXaxis()->FindBin(y - yCMShift);
                        Int_t TPCEfficiencyBinY = TPCEfficiencyHistogramPionMinus->GetYaxis()->FindBin(pt);
                        Int_t ToFEfficiencyBinX = ToFEfficiencyHistogramPionMinus->GetXaxis()->FindBin(eta);
                        Int_t ToFEfficiencyBinY = ToFEfficiencyHistogramPionMinus->GetYaxis()->FindBin(pt);

                        Double_t TPCEfficiency = TPCEfficiencyHistogramPionMinus->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);
                        Double_t ToFEfficiency = ToFEfficiencyHistogramPionMinus->GetBinContent(ToFEfficiencyBinX, ToFEfficiencyBinY);

                        if((TPCEfficiency == 0) || (TPCEfficiency > 1.3) || (ToFEfficiency == 0))
                        {
                            continue;
                        }  

                        PionMinusTrackCheck->Fill(1);

                        if(IsGoodPion)
                        {
                            MostlyGoodPionMinusTrackCheck->Fill(1);

                            HistoD50C->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                            HistoD88->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                        
                            if((y - yCMShift) < (UpperYMinusYCMShift / 2))
                            {
                                GoodPionMinusTrackCheck->Fill(1);

                                HistoD54E->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                                HistoD87->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                            }
                        }
                    }
                }
            }





            if(IsDeuteron)
            {
                Double_t mass = DeuteronMass;

                Double_t y = FlowFunctions::Y(px, py, pz, mass);

                Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

                Bool_t IsGoodDeuteron = (pt > DeuteronLowerPt) && (pt < DeuteronUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                Int_t TPCEfficiencyBinX = TPCEfficiencyHistogramDeuteron->GetXaxis()->FindBin(y - yCMShift);
                Int_t TPCEfficiencyBinY = TPCEfficiencyHistogramDeuteron->GetYaxis()->FindBin(pt);
                Int_t ToFEfficiencyBinX = ToFEfficiencyHistogramDeuteron->GetXaxis()->FindBin(eta);
                Int_t ToFEfficiencyBinY = ToFEfficiencyHistogramDeuteron->GetYaxis()->FindBin(pt);
                
                Double_t TPCEfficiency = TPCEfficiencyHistogramDeuteron->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);
                Double_t ToFEfficiency = ToFEfficiencyHistogramDeuteron->GetBinContent(ToFEfficiencyBinX, ToFEfficiencyBinY);

                if((TPCEfficiency == 0) || (TPCEfficiency > 1.3) || (ToFEfficiency == 0))
                {
                    continue;
                }

                Double_t Efficiency = 1;

                if((!FoundWithDeuteronTPC) && (FoundWithDeuteronToF))
                {
                    Efficiency = 1;
                }

                else
                {
                    if(FoundWithDeuteronTPC)
                    {
                        Efficiency = Efficiency * TPCEfficiency;   
                    }
    
                    if(FoundWithDeuteronToF)
                    {
                        Efficiency = Efficiency * ToFEfficiency;
                    }
                }

                DeuteronTrackCheck->Fill(1);

                if(IsGoodDeuteron)
                {
                    MostlyGoodDeuteronTrackCheck->Fill(1);

                    HistoD50D->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));
                    HistoD88B->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));

                    if((y - yCMShift) < (UpperYMinusYCMShift / 2))
                    {
                        GoodDeuteronTrackCheck->Fill(1);

                        HistoD54F->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));
                        HistoD88A->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));
                        
                         if((Centrality >= 2) || (Centrality <= 7))
                         {
                             if(((y - yCMShift) > 0.0) && ((y - yCMShift) < 0.1))
                             {
                                 VnVsPtDeuteron0_00Through0_10->Fill(pt, (1.0/2.0) * VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));
                                 VnOverAVsPtOverADeuteron0_00Through0_10->Fill(pt / 2.0, (1.0/2.0) * VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));
                             }

                             if(((y - yCMShift) > 0.1) && ((y - yCMShift) < 0.2))
                             {
                                 VnVsPtDeuteron0_10Through0_20->Fill(pt, (1.0/2.0) * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (Efficiency));
                                 VnOverAVsPtOverADeuteron0_10Through0_20->Fill(pt / 2.0, (1.0/2.0) * 1.5 * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (Efficiency));
                             }

                             if(((y - yCMShift) > 0.2) && ((y - yCMShift) < 0.3))
                             {
                                 VnVsPtDeuteron0_20Through0_30->Fill(pt, (1.0/2.0) * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (Efficiency));
                                 VnOverAVsPtOverADeuteron0_20Through0_30->Fill(pt / 2.0, (1.0/2.0) * 2.0 * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (Efficiency));
                             }

                             if(((y - yCMShift) > 0.3) && ((y - yCMShift) < 0.4))
                             {
                                 VnVsPtDeuteron0_30Through0_40->Fill(pt, (1.0/2.0) * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (Efficiency));
                                 VnOverAVsPtOverADeuteron0_30Through0_40->Fill(pt / 2.0, (1.0/2.0) * 2.5 * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (Efficiency));
                             }
                         }
                    }

                    if((y - yCMShift) > (UpperYMinusYCMShift / 2))
                    {
                        VnVsCentralityDeuteronHighRapidity->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));
                        VnVsCentPtDeuteronHighRapidity->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));
                    }
                }
            }

            if(IsTriton)
            {
                Double_t mass = TritonMass;

                Double_t y = FlowFunctions::Y(px, py, pz, mass);

                Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

                Bool_t IsGoodTriton = (pt > TritonLowerPt) && (pt < TritonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                Int_t TPCEfficiencyBinX = TPCEfficiencyHistogramTriton->GetXaxis()->FindBin(y - yCMShift);
                Int_t TPCEfficiencyBinY = TPCEfficiencyHistogramTriton->GetYaxis()->FindBin(pt);
                Int_t ToFEfficiencyBinX = ToFEfficiencyHistogramTriton->GetXaxis()->FindBin(eta);
                Int_t ToFEfficiencyBinY = ToFEfficiencyHistogramTriton->GetYaxis()->FindBin(pt);

                Double_t TPCEfficiency = TPCEfficiencyHistogramTriton->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);
                Double_t ToFEfficiency = ToFEfficiencyHistogramTriton->GetBinContent(ToFEfficiencyBinX, ToFEfficiencyBinY);

                if((TPCEfficiency == 0) || (TPCEfficiency > 1.3) || (ToFEfficiency == 0))
                {
                    continue;
                }

                Double_t Efficiency = 1;

                if((!FoundWithTritonTPC) && (FoundWithTritonToF))
                {
                    Efficiency = 1;
                }                

                else
                {
                    if(FoundWithTritonTPC)
                    {
                        Efficiency = Efficiency * TPCEfficiency;
                    }
    
                    if(FoundWithTritonToF)
                    {
                        Efficiency = Efficiency * ToFEfficiency;
                    }
                }

                TritonTrackCheck->Fill(1);

                if(IsGoodTriton)
                {
                    MostlyGoodTritonTrackCheck->Fill(1);

                    HistoD50E->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));
                    HistoD88D->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));

                    if((y - yCMShift) < (UpperYMinusYCMShift / 2))
                    {
                        GoodTritonTrackCheck->Fill(1);

                        HistoD54G->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));
                        HistoD88C->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));
                        
                         if((Centrality >= 2) || (Centrality <= 7))
                         {
                             if(((y - yCMShift) > 0.0) && ((y - yCMShift) < 0.1))
                             {
                                 if(pt / 3.0 > 0.7)
                                 {
                                     VnVsPtTriton0_00Through0_10->Fill(pt, (1.0/3.0) * VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));
                                     VnOverAVsPtOverATriton0_00Through0_10->Fill(pt / 3.0, (1.0/3.0) * VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));
                                 }
                             }

                             if(((y - yCMShift) > 0.1) && ((y - yCMShift) < 0.2))
                             {
                                 VnVsPtTriton0_10Through0_20->Fill(pt, (1.0/3.0) * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (Efficiency));
                                 VnOverAVsPtOverATriton0_10Through0_20->Fill(pt / 3.0, (1.0/3.0) * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (Efficiency));
                             }

                             if(((y - yCMShift) > 0.2) && ((y - yCMShift) < 0.3))
                             {
                                 VnVsPtTriton0_20Through0_30->Fill(pt, (1.0/3.0) * 2.0 * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (Efficiency));
                                 VnOverAVsPtOverATriton0_20Through0_30->Fill(pt / 3.0, (1.0/3.0) * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (Efficiency));
                             }

                             if(((y - yCMShift) > 0.3) && ((y - yCMShift) < 0.4))
                             {
                                 VnVsPtTriton0_30Through0_40->Fill(pt, (1.0/3.0) * 2.5 * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (Efficiency));
                                 VnOverAVsPtOverATriton0_30Through0_40->Fill(pt / 3.0, (1.0/3.0) * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (Efficiency));
                             }
                         }
                    }

                    if((y - yCMShift) > (UpperYMinusYCMShift / 2))
                    {
                        VnVsCentralityTritonHighRapidity->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));
                        VnVsCentPtTritonHighRapidity->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (Efficiency));
                    }
                }
            }







            if(IsProtonTPC)
            {
                Double_t mass = ProtonMass;

                Double_t y = FlowFunctions::Y(px, py, pz, mass);

                Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

                Bool_t IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                Int_t TPCEfficiencyBinX = TPCEfficiencyHistogramProton->GetXaxis()->FindBin(y - yCMShift);
                Int_t TPCEfficiencyBinY = TPCEfficiencyHistogramProton->GetYaxis()->FindBin(pt);

                Double_t TPCEfficiency = TPCEfficiencyHistogramProton->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);

                if((TPCEfficiency == 0) || (TPCEfficiency > 1.3))
                {
                    continue;
                }

                ProtonTrackCheck->Fill(1);

                if(IsGoodProton)
                {
                    if(Centrality == 8)
                    {
                        HistoDC->Fill(VnInnerEPDFourierCorrected);
                        HistoDD->Fill(VnInnerEPDFourierCorrected / ResolutionCorrectionFactor);
                        HistoDE->Fill(VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                    }

                    MostlyGoodProtonTrackCheck->Fill(1);

                    HistoD44C->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                    HistoD80->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                    
                    if((y - yCMShift) < (UpperYMinusYCMShift / 2))
                    {
                        GoodProtonTrackCheck->Fill(1);

                        HistoD54A->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                        HistoD79->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));

                         if((Centrality >= 2) || (Centrality <= 7))
                         {
                             if(((y - yCMShift) > 0.0) && ((y - yCMShift) < 0.1))
                             {
                                 VnVsPtProton0_00Through0_10->Fill(pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                                 VnOverAVsPtOverAProton0_00Through0_10->Fill(pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                             }

                             if(((y - yCMShift) > 0.1) && ((y - yCMShift) < 0.2))
                             {
                                 VnVsPtProton0_10Through0_20->Fill(pt, 1.5 * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (TPCEfficiency));
                                 VnOverAVsPtOverAProton0_10Through0_20->Fill(pt, (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (TPCEfficiency));
                             }

                             if(((y - yCMShift) > 0.2) && ((y - yCMShift) < 0.3))
                             {
                                 VnVsPtProton0_20Through0_30->Fill(pt, 2.0 * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (TPCEfficiency));
                                 VnOverAVsPtOverAProton0_20Through0_30->Fill(pt, (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (TPCEfficiency));
                             }

                             if(((y - yCMShift) > 0.3) && ((y - yCMShift) < 0.4))
                             {
                                 VnVsPtProton0_30Through0_40->Fill(pt, 2.5 * (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (TPCEfficiency));
                                 VnOverAVsPtOverAProton0_30Through0_40->Fill(pt, (VnInnerEPDFourierCorrected / ResolutionCorrectionFactor), 1.0 / (TPCEfficiency));
                             }
                         }

                    }

                    if((y - yCMShift) > (UpperYMinusYCMShift / 2))
                    {
                        VnVsCentralityProtonHighRapidity->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                        VnVsCentPtProtonHighRapidity->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                    }
                }



                if((pt > 1.0) && (pt < 2.5) && ((y - yCMShift) > -0.5) && ((y - yCMShift) < 0.5))
                {
                    VnVsYSymmetricProton->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                }
            }      
        }       
    }//End Flow Calculator loop

    ProtonPtVec.clear();
    ProtonEtaVec.clear();
    ProtonPhiVec.clear();
    ProtonMassVec.clear();   
    PionPlusPtVec.clear();
    PionPlusEtaVec.clear();
    PionPlusPhiVec.clear();
    PionPlusMassVec.clear();
    PionMinusPtVec.clear();
    PionMinusEtaVec.clear();
    PionMinusPhiVec.clear();
    PionMinusMassVec.clear();

    delete BichselZDeuteron;
    delete BichselZTriton;

    return kStOK;   
}

