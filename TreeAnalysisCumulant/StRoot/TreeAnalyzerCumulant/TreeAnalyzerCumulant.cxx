//Author: Michael Gordon
//Date: 3-18-26


#include <iostream>
#include <string>
#include <vector>
#include <cmath>

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
#include "TComplex.h"

#include "TreeAnalyzerCumulant.h"
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



#include <Math/Vector4D.h>

ClassImp(TreeAnalyzerCumulant)

    
TreeAnalyzerCumulant::TreeAnalyzerCumulant(StPicoDstMaker *picoMaker, Char_t *JobID, Char_t *Systematic):StMaker()
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



void TreeAnalyzerCumulant::Clear(Option_t *opt)
{
    StMaker::Clear();
}



Int_t TreeAnalyzerCumulant::Finish()
{
    //Outputting the Histograms
    QxRefA->SetDirectory(0);
    QyRefA->SetDirectory(0);
    QxRefB->SetDirectory(0);
    QyRefB->SetDirectory(0);
    QxPOI->SetDirectory(0);
    QyPOI->SetDirectory(0); 


    AvgCosCentEPD->SetDirectory(0);
    AvgSinCentEPD->SetDirectory(0);

    for(int i = 0; i < 7; i++)
    {
        AvgCosCentTPC[i]->SetDirectory(0);
        AvgSinCentTPC[i]->SetDirectory(0);
        AvgCosPt00_10TPC[i]->SetDirectory(0);
        AvgSinPt00_10TPC[i]->SetDirectory(0);
        AvgCosPt10_40TPC[i]->SetDirectory(0);
        AvgSinPt10_40TPC[i]->SetDirectory(0);
        AvgCosPt40_60TPC[i]->SetDirectory(0);
        AvgSinPt40_60TPC[i]->SetDirectory(0);
        AvgCosY00_10TPC[i]->SetDirectory(0);
        AvgSinY00_10TPC[i]->SetDirectory(0);
        AvgCosY10_40TPC[i]->SetDirectory(0);
        AvgSinY10_40TPC[i]->SetDirectory(0);
        AvgCosY40_60TPC[i]->SetDirectory(0);
        AvgSinY40_60TPC[i]->SetDirectory(0);
    }


    TPCPhi->SetDirectory(0);
    EPDPhi->SetDirectory(0);
    RunCount->SetDirectory(0);
    HistoD12->SetDirectory(0);
    HistoD13->SetDirectory(0);
    HistoD14->SetDirectory(0);
    HistoD15->SetDirectory(0);
    HistoD16->SetDirectory(0);
    HistoD17->SetDirectory(0);
    HistoD27->SetDirectory(0);
    HistoD27A->SetDirectory(0);
    HistoD27B->SetDirectory(0);
    HistoD28->SetDirectory(0);
    HistoD29->SetDirectory(0);
    HistoD30->SetDirectory(0);
    HistoD31->SetDirectory(0);
    TPCAcceptance->SetDirectory(0);
    EPDAcceptance->SetDirectory(0);



    
    EventCheck->SetDirectory(0);
    OverallTrackCheckNoCuts->SetDirectory(0);
    OverallTrackCheckQACuts->SetDirectory(0);
    TwoPartRefVsCent->SetDirectory(0);
    FourPartRefVsCent->SetDirectory(0);
    for(int i = 0; i < 7; i++)
    {
        TwoPartDiffVsCent[i]->SetDirectory(0);
        TwoPartDiffVsCentVsPt[i]->SetDirectory(0);
        TwoPartDiffVsCentVsY[i]->SetDirectory(0);
        FourPartDiffVsCent[i]->SetDirectory(0);
        FourPartDiffVsCentVsPt[i]->SetDirectory(0);
        FourPartDiffVsCentVsY[i]->SetDirectory(0);
    }







    std::string HistogramRootFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/Correlations" + Variation + ID + ".root";
    const char *HistogramRootFileChar = &HistogramRootFileString[0];

    TFile *HistogramRootFile = TFile::Open(HistogramRootFileChar, "RECREATE");
    HistogramRootFile->cd();




    QxRefA->Write();
    QyRefA->Write();
    QxRefB->Write();
    QyRefB->Write();
    QxPOI->Write();
    QyPOI->Write();



    AvgCosCentEPD->Write();
    AvgSinCentEPD->Write();

    for(int i = 0; i < 7; i++)
    {
        AvgCosCentTPC[i]->Write();
        AvgSinCentTPC[i]->Write();
        AvgCosPt00_10TPC[i]->Write();
        AvgSinPt00_10TPC[i]->Write();
        AvgCosPt10_40TPC[i]->Write();
        AvgSinPt10_40TPC[i]->Write();
        AvgCosPt40_60TPC[i]->Write();
        AvgSinPt40_60TPC[i]->Write();
        AvgCosY00_10TPC[i]->Write();
        AvgSinY00_10TPC[i]->Write();
        AvgCosY10_40TPC[i]->Write();
        AvgSinY10_40TPC[i]->Write();
        AvgCosY40_60TPC[i]->Write();
        AvgSinY40_60TPC[i]->Write();
    }

    
    

    TPCPhi->Write();
    EPDPhi->Write();
    RunCount->Write();
    HistoD12->Write();
    HistoD13->Write();
    HistoD14->Write();
    HistoD15->Write();
    HistoD16->Write();
    HistoD17->Write();
    HistoD27->Write();
    HistoD27A->Write();
    HistoD27B->Write();
    HistoD28->Write();
    HistoD29->Write();
    HistoD30->Write();
    HistoD31->Write();
    TPCAcceptance->Write();
    EPDAcceptance->Write();
    

    EventCheck->Write();
    OverallTrackCheckNoCuts->Write();
    OverallTrackCheckQACuts->Write();
    TwoPartRefVsCent->Write();
    FourPartRefVsCent->Write();
    for(int i = 0; i < 7; i++)
    {
        TwoPartDiffVsCent[i]->Write();
        TwoPartDiffVsCentVsPt[i]->Write();
        TwoPartDiffVsCentVsY[i]->Write();
        FourPartDiffVsCent[i]->Write();
        FourPartDiffVsCentVsPt[i]->Write();
        FourPartDiffVsCentVsY[i]->Write();
    }

        

    HistogramRootFile->Close();




    delete QxRefA;
    delete QyRefA;
    delete QxRefB;
    delete QyRefB;
    delete QxPOI;
    delete QyPOI;



    delete AvgCosCentEPD;
    delete AvgSinCentEPD;

    for(int i = 0; i < 7; i++)
    {
        delete AvgCosCentTPC[i];
        delete AvgSinCentTPC[i];
        delete AvgCosPt00_10TPC[i];
        delete AvgSinPt00_10TPC[i];
        delete AvgCosPt10_40TPC[i];
        delete AvgSinPt10_40TPC[i];
        delete AvgCosPt40_60TPC[i];
        delete AvgSinPt40_60TPC[i];
        delete AvgCosY00_10TPC[i];
        delete AvgSinY00_10TPC[i];
        delete AvgCosY10_40TPC[i];
        delete AvgSinY10_40TPC[i];
        delete AvgCosY40_60TPC[i];
        delete AvgSinY40_60TPC[i];
    }

    

    delete TPCPhi;
    delete EPDPhi;
    delete RunCount;
    delete HistoD12;
    delete HistoD13;
    delete HistoD14;
    delete HistoD15;
    delete HistoD16;
    delete HistoD17;
    delete HistoD27;
    delete HistoD27A;
    delete HistoD27B;
    delete HistoD28;
    delete HistoD29;
    delete HistoD30;
    delete HistoD31;
    delete TPCAcceptance;
    delete EPDAcceptance;


   
    

    delete EventCheck;
    delete OverallTrackCheckNoCuts;
    delete OverallTrackCheckQACuts;
    delete TwoPartRefVsCent;
    delete FourPartRefVsCent;
    for(int i = 0; i < 7; i++)
    {
        delete TwoPartDiffVsCent[i];
        delete TwoPartDiffVsCentVsPt[i];
        delete TwoPartDiffVsCentVsY[i];
        delete FourPartDiffVsCent[i];
        delete FourPartDiffVsCentVsPt[i];
        delete FourPartDiffVsCentVsY[i];
    }
    
    return kStOK;
}



Int_t TreeAnalyzerCumulant::Init()
{
    std::vector<int> RunIDs {0, 79020,79021,79022,78002,78003,78004,78005,78006,78007,78008,78009,78010,78011,78012,78013,77002,77003,77004,77005,77006,77007,77008,77012,77013,77014,76001,76002,76003,76004,76005,76006,76007,76008,76009,76011,76012,75001,75002,75003,75004,75005,75006,75007,75008,75010,75011,75013,75031,75032,74002,74003,74004,74005,74006,74007,74010,74011,74012,74013,74014,74018,74019,74046,74047,74048,74049,74050,74054,74055,74056,74057,74058,74059,74060,74061,74062,73001,73002,73003,73004,73005,73006,73009,73010,73011,73012,73013,73014,73015,73016,73017,73018,73019,73020,73023,73024,73025,73026,73027,73028,73029,73030,73031,73032,73033,73034,73035,72001,72002,72003,72004,72005,72006,72007,72008,72009,72010,72022,72024,72025,71021,71022,71023,71024,71025,71026,71027,71028,71029,71030,71031,71032,71033,70001,70002,70003,70004,70005,70006,70007,70008,70009,70014,70015,70016,70017,70018,70019,70020,70021,70022,69001,69002,69003,69004,69005,69006,69007,69008,69009,69010,69011,69018,69022,69023,68003,68004,68005,68006,68007,68008,68009,68010,68015,67001,67002,67003,67004,67005,67006,67007,67008,67009,67010,67011,67012,67016,67017,67021,67022,67023,67024,67025,67027,67028,67029,66001,66002,66003,66004,66005,66006,66009,66010,66013,66014,66015,66016,66017,66018,66019,66020,66023,66024,66026,66028,66029,66030,66031,66034,66035,66036,66037,66038,66039,65001,65002,65003,65004,65005,65006,65007,65008,65009,65010,65012,65013,65014,65015,65016,65017,65018,65019,65021,65024,65025,65026,65027,65028,65029,65031,65032,65033,65034,65035,64001,64002,64003,64004,64005,64006,64007,64008,64009,64010,64011,64012,64013,64014,64015,64016,64017,64018,64019,64022,64024,64025,64026,64027,64028,64029,64030,64031,64032,64033,63002,63003,63004,63005,63006,63007,63008,63009,63010,63011,63012,63013,63014,63015,63016,63017,63018,63019,63020,63026,63027,63028,63029,63030,63031,63032,63034,63035,63036,62001,62003,62006,62007,62008,62009,62015,62018,62019,62021,62022,62023,61001,61002,61003,61004,61005,61006,61009,61010,61012,61013,61014,61015,61016,61018,61019,61020,61023,61024,61025,61026,61027,61028,61029,61030,61031,61032,61033,60001,60002,60003,60004,60005,60006,60007,60008,60009,60010,60011,60012,60013,60014,60015,60016,60017,60018,60019,60020,60021,60022,60024,60025,60026,60027,60028,60029,60030,60031,60032,60046,60047,60048,60049,60050,60051,60052,60053,59001,59003,59008,59009,59010,59011,59012,59013,59015,59051,59052,59053,58032,58033,58036,25001,25002,25003,25004,25005,25006,25007,25008,25009,25010,25011,24002,24003,24004,24005,24006,24007,24008,24011,24012,24013,24014,24018,24027,24028,24031,23001,23002,23003,23004,23005,23006,23007,23008,23009,23010,23011,23012,23013,23014,23015,23016,23017,23018,23020,23021,23025,23026,23027,23028,23030,23031,23032,23034,23035,23037,23038,23040,23041,22001,22002,22003,22004,22005,22006,22007,22008,22009,22010,22011,22014,22016,22017,22018,22019,22020,22021,22024,22025,22026,22027,22028,22029,22031,22032,22034,22035,21033,21036,21037,21038,21039,21040,21041,21044,21045,21046,21048,21049,21050,21052,21053};


    
    
    const char* CentralityXLabels[16] = {"0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60", "60-65", "65-70", "70-75", "75-80"};



    QxRefA = new TH1D("QxRefA", "Qx Reference A; Qx; Events", 250, -100, 100);
    QyRefA = new TH1D("QyRefA", "Qy Reference A; Qy; Events", 250, -100, 100);
    QxRefB = new TH1D("QxRefB", "Qx Reference B; Qx; Events", 250, -100, 100);
    QyRefB = new TH1D("QyRefB", "Qy Reference B; Qy; Events", 250, -100, 100);
    QxPOI = new TH1D("QxPOI", "Qx POI Protons; Qx; Events", 250, -100, 100);
    QyPOI = new TH1D("QyPOI", "Qy POI Protons; Qy; Events", 250, -100, 100);    

    


    TPCPhi = new TH1D("TPCPhi", "TPC #phi; #phi; Counts", 500, -3.5, 3.5);
    TPCPhi->Sumw2();

    EPDPhi = new TH1D("EPDPhi", "EPD #phi; #phi; Counts", 500, -3.5, 3.5);
    EPDPhi->Sumw2();

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


    TPCAcceptance = new TH2D("TPCAcceptance","TPC Acceptance; #eta; #phi", 200, -4, 4, 200, -2, 0);
    TPCAcceptance->Sumw2();

    EPDAcceptance = new TH2D("EPDAcceptance","EPD Acceptance; #eta; #phi", 200, -.5, 7, 300, -5.5, -2.5);
    EPDAcceptance->Sumw2();


    




    std::string ParticleNames[7] = {"Protons", "K^{+}", "K^{-}", "#pi^{+}", "#pi^{-}", "Deuterons", "Tritons"};

    std::string TwoPartRefVsCentString = "Reference Flow vs Centrality from Two-Particle Correlations; Centrality; Reference Flow";
    const char *TwoPartRefVsCentChar = &TwoPartRefVsCentString[0];
    
    TwoPartRefVsCent = new TProfile("TwoPartRefVsCent", TwoPartRefVsCentChar, 12, 0, 12);
    TwoPartRefVsCent->Sumw2();

    std::string FourPartRefVsCentString = "Reference Flow vs Centrality from Four-Particle Correlations; Centrality; Reference Flow";
    const char *FourPartRefVsCentChar = &FourPartRefVsCentString[0];
    
    FourPartRefVsCent = new TProfile("FourPartRefVsCent", FourPartRefVsCentChar, 12, 0, 12);
    FourPartRefVsCent->Sumw2();




    


    std::string AvgCosCentEPDString = "Average of cos(#phi) for Reference Particles for Different Centralities in the EPD; Centrality; <cos(#phi)>";
    const char *AvgCosCentEPDChar = &AvgCosCentEPDString[0];

    AvgCosCentEPD = new TProfile("AvgCosCentEPD", AvgCosCentEPDChar, 12, 0, 12);
    AvgCosCentEPD->Sumw2();

    std::string AvgSinCentEPDString = "Average of sin(#phi) for Reference Particles for Different Centralities in the EPD; Centrality; <sin(#phi)>";
    const char *AvgSinCentEPDChar = &AvgSinCentEPDString[0];

    AvgSinCentEPD = new TProfile("AvgSinCentEPD", AvgSinCentEPDChar, 12, 0, 12);
    AvgSinCentEPD->Sumw2();

    for (int i = 1; i < TwoPartRefVsCent->GetNbinsX() + 1; i++)
    {
        TwoPartRefVsCent->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
        FourPartRefVsCent->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
        AvgCosCentEPD->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
        AvgSinCentEPD->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }



   
    for(int i = 0; i < 7; i++)
    {
        Int_t NumPtBins[7] = {20, 20, 20, 20, 20, 40, 60};
        Double_t LowerPt[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        Double_t UpperPt[7] = {2.0, 2.0, 2.0, 2.0, 2.0, 4.0, 4.0};

        Double_t LowerY = 0.0;
        Double_t UpperY = 1.0;


        std::string TwoPartDiffVsCentString = "Differential Flow vs Centrality for " + ParticleNames[i] + " from Two-Particle Correlations; Centrality; Differential Correlation";
        const char *TwoPartDiffVsCentChar = &TwoPartDiffVsCentString[0];
        
        TwoPartDiffVsCent[i] = new TProfile(Form("TwoPartDiffVsCent%s", ParticleNames[i].c_str()), TwoPartDiffVsCentChar, 12, 0, 12);
        TwoPartDiffVsCent[i]->Sumw2();
        
        std::string TwoPartDiffVsCentVsPtString = "Differential Flow vs Centrality vs Pt for " + ParticleNames[i] + " from Two-Particle Correlations; Centrality; Pt, Differential Correlation";
        const char *TwoPartDiffVsCentVsPtChar = &TwoPartDiffVsCentVsPtString[0];
        
        TwoPartDiffVsCentVsPt[i] = new TProfile2D(Form("TwoPartDiffVsCentVsPt%s", ParticleNames[i].c_str()), TwoPartDiffVsCentVsPtChar, 12, 0, 12, NumPtBins[i], LowerPt[i], UpperPt[i]);
        TwoPartDiffVsCentVsPt[i]->Sumw2();

        std::string TwoPartDiffVsCentVsYString = "Differential Flow vs Centrality vs Y for " + ParticleNames[i] + " from Two-Particle Correlations; Centrality; Y, Differential Correlation";
        const char *TwoPartDiffVsCentVsYChar = &TwoPartDiffVsCentVsYString[0];
        
        TwoPartDiffVsCentVsY[i] = new TProfile2D(Form("TwoPartDiffVsCentVsY%s", ParticleNames[i].c_str()), TwoPartDiffVsCentVsYChar, 12, 0, 12, 10, LowerY, UpperY);
        TwoPartDiffVsCentVsY[i]->Sumw2();




        std::string FourPartDiffVsCentString = "Differential Flow vs Centrality for " + ParticleNames[i] + " from Four-Particle Correlations; Centrality; Differential Correlation";
        const char *FourPartDiffVsCentChar = &FourPartDiffVsCentString[0];
        
        FourPartDiffVsCent[i] = new TProfile(Form("FourPartDiffVsCent%s", ParticleNames[i].c_str()), FourPartDiffVsCentChar, 12, 0, 12);
        FourPartDiffVsCent[i]->Sumw2();
        
        std::string FourPartDiffVsCentVsPtString = "Differential Flow vs Centrality vs Pt for " + ParticleNames[i] + " from Four-Particle Correlations; Centrality; Pt, Differential Correlation";
        const char *FourPartDiffVsCentVsPtChar = &FourPartDiffVsCentVsPtString[0];
        
        FourPartDiffVsCentVsPt[i] = new TProfile2D(Form("FourPartDiffVsCentVsPt%s", ParticleNames[i].c_str()), FourPartDiffVsCentVsPtChar, 12, 0, 12, NumPtBins[i], LowerPt[i], UpperPt[i]);
        FourPartDiffVsCentVsPt[i]->Sumw2();

        std::string FourPartDiffVsCentVsYString = "Differential Flow vs Centrality vs Y for " + ParticleNames[i] + " from Four-Particle Correlations; Centrality; Y, Differential Correlation";
        const char *FourPartDiffVsCentVsYChar = &FourPartDiffVsCentVsYString[0];
        
        FourPartDiffVsCentVsY[i] = new TProfile2D(Form("FourPartDiffVsCentVsY%s", ParticleNames[i].c_str()), FourPartDiffVsCentVsYChar, 12, 0, 12, 10, LowerY, UpperY);
        FourPartDiffVsCentVsY[i]->Sumw2();

        

  

        
        std::string AvgCosCentTPCString = "Average of cos(#phi) for " + ParticleNames[i] + "for Different Centralities in the TPC; Centrality; <cos(#phi)>";
        const char *AvgCosCentTPCChar = &AvgCosCentTPCString[0];

        AvgCosCentTPC[i] = new TProfile(Form("AvgCosCent%sTPC", ParticleNames[i].c_str()), AvgCosCentTPCChar, 12, 0, 12);
        AvgCosCentTPC[i]->Sumw2();

        std::string AvgSinCentTPCString = "Average of sin(#phi) for " + ParticleNames[i] + "for Different Centralities in the TPC; Centrality; <sin(#phi)>";
        const char *AvgSinCentTPCChar = &AvgSinCentTPCString[0];

        AvgSinCentTPC[i] = new TProfile(Form("AvgSinCent%sTPC", ParticleNames[i].c_str()), AvgSinCentTPCChar, 12, 0, 12);
        AvgSinCentTPC[i]->Sumw2();
        

 




        std::string AvgCosPt00_10TPCString = "Average of cos(#phi) for " + ParticleNames[i] + " for Pt with Centrality 0-10% in the TPC; Pt; <cos(#phi)>";
        const char *AvgCosPt00_10TPCChar = &AvgCosPt00_10TPCString[0];

        AvgCosPt00_10TPC[i] = new TProfile(Form("AvgCosPt00_10%sTPC", ParticleNames[i].c_str()), AvgCosPt00_10TPCChar, NumPtBins[i], LowerPt[i], UpperPt[i]);
        AvgCosPt00_10TPC[i]->Sumw2();

        std::string AvgSinPt00_10TPCString = "Average of sin(#phi) for " + ParticleNames[i] + " for Pt with Centrality 0-10% in the TPC; Pt; <sin(#phi)>";
        const char *AvgSinPt00_10TPCChar = &AvgSinPt00_10TPCString[0];

        AvgSinPt00_10TPC[i] = new TProfile(Form("AvgSinPt00_10%sTPC", ParticleNames[i].c_str()), AvgSinPt00_10TPCChar, NumPtBins[i], LowerPt[i], UpperPt[i]);
        AvgSinPt00_10TPC[i]->Sumw2();


        
        std::string AvgCosPt10_40TPCString = "Average of cos(#phi) for " + ParticleNames[i] + " for Pt with Centrality 10-40% in the TPC; Pt; <cos(#phi)>";
        const char *AvgCosPt10_40TPCChar = &AvgCosPt10_40TPCString[0];

        AvgCosPt10_40TPC[i] = new TProfile(Form("AvgCosPt10_40%sTPC", ParticleNames[i].c_str()), AvgCosPt10_40TPCChar, NumPtBins[i], LowerPt[i], UpperPt[i]);
        AvgCosPt10_40TPC[i]->Sumw2();

        std::string AvgSinPt10_40TPCString = "Average of sin(#phi) for " + ParticleNames[i] + " for Pt with Centrality 10-40% in the TPC; Pt; <sin(#phi)>";
        const char *AvgSinPt10_40TPCChar = &AvgSinPt10_40TPCString[0];

        AvgSinPt10_40TPC[i] = new TProfile(Form("AvgSinPt10_40%sTPC", ParticleNames[i].c_str()), AvgSinPt10_40TPCChar, NumPtBins[i], LowerPt[i], UpperPt[i]);
        AvgSinPt10_40TPC[i]->Sumw2();

 

        std::string AvgCosPt40_60TPCString = "Average of cos(#phi) for " + ParticleNames[i] + " for Pt with Centrality 40-60% in the TPC; Pt; <cos(#phi)>";
        const char *AvgCosPt40_60TPCChar = &AvgCosPt40_60TPCString[0];

        AvgCosPt40_60TPC[i] = new TProfile(Form("AvgCosPt40_60%sTPC", ParticleNames[i].c_str()), AvgCosPt40_60TPCChar, NumPtBins[i], LowerPt[i], UpperPt[i]);
        AvgCosPt40_60TPC[i]->Sumw2();

        std::string AvgSinPt40_60TPCString = "Average of sin(#phi) for " + ParticleNames[i] + " for Pt with Centrality 40-60% in the TPC; Pt; <sin(#phi)>";
        const char *AvgSinPt40_60TPCChar = &AvgSinPt40_60TPCString[0];

        AvgSinPt40_60TPC[i] = new TProfile(Form("AvgSinPt40_60%sTPC", ParticleNames[i].c_str()), AvgSinPt40_60TPCChar, NumPtBins[i], LowerPt[i], UpperPt[i]);
        AvgSinPt40_60TPC[i]->Sumw2();        



 



        
        std::string AvgCosY00_10TPCString = "Average of cos(#phi) for " + ParticleNames[i] + " for Y with Centrality 0-10% in the TPC; Y; <cos(#phi)>";
        const char *AvgCosY00_10TPCChar = &AvgCosY00_10TPCString[0];

        AvgCosY00_10TPC[i] = new TProfile(Form("AvgCosY00_10%sTPC", ParticleNames[i].c_str()), AvgCosY00_10TPCChar, 10, LowerY, UpperY);
        AvgCosY00_10TPC[i]->Sumw2();

        std::string AvgSinY00_10TPCString = "Average of sin(#phi) for " + ParticleNames[i] + " for Y with Centrality 0-10% in the TPC; Y; <sin(#phi)>";
        const char *AvgSinY00_10TPCChar = &AvgSinY00_10TPCString[0];

        AvgSinY00_10TPC[i] = new TProfile(Form("AvgSinY00_10%sTPC", ParticleNames[i].c_str()), AvgSinY00_10TPCChar, 10, LowerY, UpperY);
        AvgSinY00_10TPC[i]->Sumw2();

 
        
        std::string AvgCosY10_40TPCString = "Average of cos(#phi) for " + ParticleNames[i] + " for Y with Centrality 10-40% in the TPC; Y; <cos(#phi)>";
        const char *AvgCosY10_40TPCChar = &AvgCosY10_40TPCString[0];

        AvgCosY10_40TPC[i] = new TProfile(Form("AvgCosY10_40%sTPC", ParticleNames[i].c_str()), AvgCosY10_40TPCChar, 10, LowerY, UpperY);
        AvgCosY10_40TPC[i]->Sumw2();

        std::string AvgSinY10_40TPCString = "Average of sin(#phi) for " + ParticleNames[i] + " for Y with Centrality 10-40% in the TPC; Y; <sin(#phi)>";
        const char *AvgSinY10_40TPCChar = &AvgSinY10_40TPCString[0];

        AvgSinY10_40TPC[i] = new TProfile(Form("AvgSinY10_40%sTPC", ParticleNames[i].c_str()), AvgSinY10_40TPCChar, 10, LowerY, UpperY);
        AvgSinY10_40TPC[i]->Sumw2();



        std::string AvgCosY40_60TPCString = "Average of cos(#phi) for " + ParticleNames[i] + "for Y with Centrality 40-60% in the TPC; Y; <cos(#phi)>";
        const char *AvgCosY40_60TPCChar = &AvgCosY40_60TPCString[0];

        AvgCosY40_60TPC[i] = new TProfile(Form("AvgCosY40_60%sTPC", ParticleNames[i].c_str()), AvgCosY40_60TPCChar, 10, LowerY, UpperY);
        AvgCosY40_60TPC[i]->Sumw2();

        std::string AvgSinY40_60TPCString = "Average of sin(#phi) for " + ParticleNames[i] + "for Y with Centrality 40-60% in the TPC; Y; <sin(#phi)>";
        const char *AvgSinY40_60TPCChar = &AvgSinY40_60TPCString[0];

        AvgSinY40_60TPC[i] = new TProfile(Form("AvgSinY40_60%sTPC", ParticleNames[i].c_str()), AvgSinY40_60TPCChar, 10, LowerY, UpperY);
        AvgSinY40_60TPC[i]->Sumw2();        
    }







    
  
    
    
    
    epdGeom = new StEpdGeom();
    
    std::cout << "Setup Complete" << std::endl; 
    
    return kStOK;
}





Int_t TreeAnalyzerCumulant::Make()
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
    // Int_t NumberOfGoodTracksInnerEPD = 5;
    // Int_t NumberOfGoodTracksOuterEPD = 9;
    // Int_t NumberOfGoodTracksTPC = 5;
    // Double_t TPCLowerLimit = -1.8;
    // Double_t TPCUpperLimit = -0.3;



    Double_t RVertexBound = 1.5;
    Double_t ZVertexLowerBound = 198.0;
    Double_t ZVertexUpperBound = 202.0;
    
    Double_t DCABound = 3.0;
    Int_t NHitsBound = 15;
    Int_t NHitsdEdxBound = 5;
    Double_t NHitsFitOverNHitsPossBound = 0.52;
    
    Int_t InnerEPDHighRing = 8;
    Int_t OuterEPDLowRing = 9;
    
    
    
    // Double_t ProtonLowerMSquared = 0.6;
    // Double_t ProtonUpperMSquared = 1.2;
    Double_t KaonLowerMSquared = 0.15;
    Double_t KaonUpperMSquared = 0.34;
    Double_t PionLowerMSquared = -0.1;
    Double_t PionUpperMSquared = 0.1;
    Double_t NSigmaPrBound = 2.0;
    Double_t NSigmaKaBound = 3.0;
    Double_t NSigmaPiBound = 3.0;
    Double_t LowerYMinusYCMShift = 0.0;
    Double_t UpperYMinusYCMShift = 1.0;



   

    
    
    // // Parameter changes for systematic runs
    // if (Variation == "RVertex20Low")
    // {
    //     RVertexBound = 1.2;
    // }
    // if (Variation == "RVertex30Low")
    // {
    //     RVertexBound = 1.05;
    // }
    // if (Variation == "RVertex20High")
    // {
    //     RVertexBound = 1.8;
    // }
    // if(Variation == "RVertex30High")
    // {
    //     RVertexBound = 1.95;
    // }
    // if (Variation == "ZVertex20Low")
    // {
    //     ZVertexLowerBound = 198.4;
    //     ZVertexUpperBound = 201.6;
    // }
    // if (Variation == "ZVertex20High")
    // {
    //     ZVertexLowerBound = 197.6;
    //     ZVertexUpperBound = 202.4;
    // }
    // if (Variation == "ZVertex30Low")
    // {
    //     ZVertexLowerBound = 198.6;
    //     ZVertexUpperBound = 201.4;
    // }
    // if (Variation == "ZVertex30High")
    // {
    //     ZVertexLowerBound = 197.4;
    //     ZVertexUpperBound = 202.6;
    // }
    // if (Variation == "DCA20Low")
    // {
    //     DCABound = 2.4;
    // }
    // if (Variation == "DCA20High")
    // {
    //     DCABound = 3.6;
    // }
    // if (Variation == "DCA30Low")
    // {
    //     DCABound = 2.1;
    // }
    // if (Variation == "DCA30High")
    // {
    //     DCABound = 3.9;
    // }
    // if (Variation == "NHits20Low")
    // {
    //     NHitsBound = 12;
    // }
    // if (Variation == "NHits20High")
    // {
    //     NHitsBound = 18;
    // }
    // if (Variation == "NHits30Low")
    // {
    //     NHitsBound = 10;
    // }
    // if (Variation == "NHits30High")
    // {
    //     NHitsBound = 20;
    // }
    // if (Variation == "NHitsdEdx20High")
    // {
    //     NHitsdEdxBound = 9;
    // }
    // if (Variation == "NHitsdEdx30High")
    // {
    //     NHitsdEdxBound = 12;
    // }
    // if (Variation == "NHitsFitOverNHitsPoss20Low")
    // {
    //     NHitsFitOverNHitsPossBound = 0.416;
    // }
    // if (Variation == "NHitsFitOverNHitsPoss20High")
    // {
    //     NHitsFitOverNHitsPossBound = 0.624;
    // }
    // if (Variation == "NHitsFitOverNHitsPoss30Low")
    // {
    //     NHitsFitOverNHitsPossBound = 0.364;
    // }
    // if (Variation == "NHitsFitOverNHitsPoss30High")
    // {
    //     NHitsFitOverNHitsPossBound = 0.676;
    // }
    // if (Variation == "NSigmaPion20Low")
    // {
    //     NSigmaPiBound = 2.4;
    // }
    // if (Variation == "NSigmaPion20High")
    // {
    //     NSigmaPiBound = 3.6;
    // }
    // if (Variation == "NSigmaPion30Low")
    // {
    //     NSigmaPiBound = 2.1;
    // }
    // if (Variation == "NSigmaPion30High")
    // {
    //     NSigmaPiBound = 3.9;
    // }
    // if (Variation == "NSigmaKaon20Low")
    // {
    //     NSigmaKaBound = 2.4;
    // }
    // if (Variation == "NSigmaKaon20High")
    // {
    //     NSigmaKaBound = 3.6;
    // }
    // if (Variation == "NSigmaKaon30Low")
    // {
    //     NSigmaKaBound = 2.1;
    // }
    // if (Variation == "NSigmaKaon30High")
    // {
    //     NSigmaKaBound = 3.9;
    // }
    // if (Variation == "NSigmaProton20Low")
    // {
    //     NSigmaPrBound = 1.6;
    // }
    // if (Variation == "NSigmaProton20High")
    // {
    //     NSigmaPrBound = 2.4;
    // }
    // if (Variation == "NSigmaProton30Low")
    // {
    //     NSigmaPrBound = 1.4;
    // }
    // if (Variation == "NSigmaProton30High")
    // {
    //     NSigmaPrBound = 2.6;
    // }
    // if (Variation == "MSquaredPion20Low")
    // {
    //     PionLowerMSquared = -0.08;
    //     PionUpperMSquared = 0.08;
    // }
    // if (Variation == "MSquaredPion20High")
    // {
    //     PionLowerMSquared = -0.12;
    //     PionUpperMSquared = 0.12;
    // }
    // if (Variation == "MSquaredPion30Low")
    // {
    //     PionLowerMSquared = -0.07;
    //     PionUpperMSquared = 0.07;
    // }
    // if (Variation == "MSquaredPion30High")
    // {
    //     PionLowerMSquared = -0.13;
    //     PionUpperMSquared = 0.13;
    // }
    // if (Variation == "MSquaredKaon20Low")
    // {
    //     KaonLowerMSquared = 0.169;
    //     KaonUpperMSquared = 0.321;
    // }
    // if (Variation == "MSquaredKaon20High")
    // {
    //     KaonLowerMSquared = 0.131;
    //     KaonUpperMSquared = 0.359;
    // }
    // if (Variation == "MSquaredKaon30Low")
    // {
    //     KaonLowerMSquared = 0.1785;
    //     KaonUpperMSquared = 0.3115;
    // }
    // if (Variation == "MSquaredKaon30High")
    // {
    //     KaonLowerMSquared = 0.1215;
    //     KaonUpperMSquared = 0.3685;
    // }
    // if (Variation == "OuterEPDLow")
    // {
    //     if(RunIteration <= 3)
    //     {
    //         OuterEPDLowRing = 10;
    //     }
    //     else
    //     {
    //         OuterEPDLowRing = 9;
    //     }
    // }
    // if (Variation == "OuterEPDHigh")
    // {
    //     if(RunIteration <= 3)
    //     {
    //         OuterEPDLowRing = 13;
    //     }
    //     else
    //     {
    //         OuterEPDLowRing = 9;
    //     }
    // }
    
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
    
    
    
    // const char* CentralityXLabels[16] = {"0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60", "60-65", "65-70", "70-75", "75-80"};
    
  

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
        return 0;
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
        return 0;
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
    
    Int_t TotalTracks = mPicoDst->numberOfTracks();
    Int_t NumPrimaryTracks = 0;
    
    for (Int_t TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
    {
        StPicoTrack *pTrack = (StPicoTrack*)mPicoDst->track(TrackNum);
    
        if(!pTrack->isPrimary())
        {
            continue;
        }
        
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
        return 0;
    }
    
    EventCheck->Fill(3);


    
    
    if ((vz <= ZVertexLowerBound) || (vz >= ZVertexUpperBound))
    {
        return 0;
    }

    EventCheck->Fill(4);

    if (vr >= RVertexBound)
    {
        return 0;
    }

    EventCheck->Fill(5);

    
    
    Double_t ProtonMass = 0.938;
    Double_t KaonMass = 0.493;
    Double_t PionMass = 0.13957;



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



        Double_t EToFBeta = -999.0;

        Bool_t IsGoodEToFMatchFlag = false;
        
        if(pTrack->isTofTrack())
        {
            tofBeta = mPicoDst->btofPidTraits(pTrack->bTofPidTraitsIndex())->btofBeta();
        }

        if((pTrack->isETofTrack()))
        {
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





        if(std::isnan(p))
        {
            continue;
        }
        
        
        




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
        

        if((tofBeta > 0) || (EToFBeta > 0))
        {
            msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

            IsKaon = (abs(NSigmaKa) < NSigmaKaBound) && (msquared > KaonLowerMSquared) && (msquared < KaonUpperMSquared);
            IsPion = (abs(NSigmaPi) < NSigmaPiBound) && (msquared > PionLowerMSquared) && (msquared < PionUpperMSquared);
            // IsProtonToF = (abs(NSigmaPr) < NSigmaPrBound) && (msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared) && (q == 1);
        }

        Double_t zDeuteron = TMath::Log(dEdx / BichselZDeuteron->Eval(p));
        Double_t zTriton = TMath::Log(dEdx / BichselZTriton->Eval(p));

        // DeuteronsAndTritons DAndT (p, dEdx, tofBeta, EToFBeta, zDeuteron, zTriton, false, false, false, false, false, false);
        DeuteronsAndTritons DAndT (p, dEdx, tofBeta, zDeuteron, zTriton);




        if(!(IsKaon) && !(IsPion))
        {
            IsDeuteron = DAndT.IsDeuteron() and (q == 1);
            IsTriton = DAndT.IsTriton() and (q == 1);
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






        

        if((tofBeta > 0) || (EToFBeta > 0))
        {
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

                HistoD14->Fill(p, dEdx);

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

                HistoD13->Fill(p, dEdx);

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

                HistoD15->Fill(p, dEdx);

                HistoD27->Fill(y - yCMShift, pt);
        }

        HistoD12->Fill(p, dEdx);
    }//End of Kinematics Track Loop






    Int_t nEPDHits = mPicoDst->numberOfEpdHits();
    

    Double_t NMipA = 0;
    Double_t NMipB = 0;
    Double_t NMipSquaredA = 0;
    Double_t NMipSquaredB = 0;
    Double_t NMipCubedA = 0;
    Double_t NMipCubedB = 0;
    Double_t NMipFourthA = 0;
    Double_t NMipFourthB = 0;


    
    TComplex QVectorRefAHarmonic;
    TComplex QVectorRefBHarmonic;
    TComplex QVectorRefACubedHarmonic;
    TComplex QVectorRefBCubedHarmonic;
    TComplex QVectorRefASquaredDoubleHarmonic;
    TComplex QVectorRefBSquaredDoubleHarmonic;



 
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

        Double_t eta = TVec->EPDEta();
        
        Double_t phi = TVec->EPDPhi();

        EPDPhi->Fill(phi);

        EPDAcceptance->Fill(eta, phi);

        if(EPDnMIP < 0.3)
        {
            EPDnMIP = 0;
        }

        if(EPDnMIP > 2.0)
        {
            EPDnMIP = 2.0;
        }

        if (TVec->IsInnerEPD() && !(TVec->IsOuterEPD()))
        { 
            QVectorRefAHarmonic += TComplex(EPDnMIP*cos(nPsi*phi), EPDnMIP*sin(nPsi*phi), false);
            QVectorRefACubedHarmonic += TComplex(pow(EPDnMIP,3)*cos(nPsi*phi), pow(EPDnMIP,3)*sin(nPsi*phi), false);
            QVectorRefASquaredDoubleHarmonic += TComplex(pow(EPDnMIP,2)*cos(2*nPsi*phi), pow(EPDnMIP,2)*sin(2*nPsi*phi), false);
            NMipA += EPDnMIP;
            NMipSquaredA += (EPDnMIP * EPDnMIP);
            NMipCubedA += (EPDnMIP * EPDnMIP * EPDnMIP);
            NMipFourthA += (EPDnMIP * EPDnMIP * EPDnMIP * EPDnMIP);
        }

        else if (TVec->IsOuterEPD() && !(TVec->IsInnerEPD()))
        { 
            QVectorRefBHarmonic += TComplex(EPDnMIP*cos(nPsi*phi), EPDnMIP*sin(nPsi*phi), false);
            QVectorRefBCubedHarmonic += TComplex(pow(EPDnMIP,3)*cos(nPsi*phi), pow(EPDnMIP,3)*sin(nPsi*phi), false);
            QVectorRefBSquaredDoubleHarmonic += TComplex(pow(EPDnMIP,2)*cos(2*nPsi*phi), pow(EPDnMIP,2)*sin(2*nPsi*phi), false);
            NMipB += EPDnMIP;
            NMipSquaredB += (EPDnMIP * EPDnMIP);
            NMipCubedB += (EPDnMIP * EPDnMIP * EPDnMIP);
            NMipFourthB += (EPDnMIP * EPDnMIP * EPDnMIP * EPDnMIP);
        }

        delete TVec;
    }


    Bool_t GoodEvent = true;

    if(NMipB <= 0.1)
    {
        GoodEvent = false;
    }

    if(!GoodEvent)
    {
        return kStOK;
    }



    if(Centrality < 4)
    {
        return kStOk;
    }

    EventCheck->Fill(8);

 

    QxRefA->Fill(QVectorRefAHarmonic.Re());
    QyRefA->Fill(QVectorRefAHarmonic.Im());
    QxRefB->Fill(QVectorRefBHarmonic.Re());
    QyRefB->Fill(QVectorRefBHarmonic.Im());
    // QxPOI->Fill(QVectorHarmonicPOI[0][0].Re());
    // QyPOI->Fill(QVectorHarmonicPOI[0][0].Im());


    Double_t S_11 = NMipB;
    Double_t S_12 = NMipSquaredB;
    Double_t S_21 = NMipB * NMipB;
    Double_t S_41 = pow(NMipB,4);
    Double_t S_13 = NMipCubedB;
    Double_t S_22 = pow(NMipSquaredB,2);
    Double_t S_14 = NMipFourthB;
    

    Double_t TwoPartRefCorrDenom = S_21 - S_12;
    Double_t FourPartRefCorrDenom = S_41 - 6 * S_12 * S_21 + 8 * S_13 * S_11 + 3 * S_22 - 6 * S_14;

    
    if(((TwoPartRefCorrDenom) <= 1e-6) || ((FourPartRefCorrDenom) <= 1e-6))
    {
        return kStOK;
    }

    Double_t QnSquaredRef = (QVectorRefBHarmonic).Rho2();

    Double_t QnSquaredSquaredDoubleRef = (QVectorRefBSquaredDoubleHarmonic).Rho2();

    Double_t QnFourPartCorrectionTermFirst = (QVectorRefBSquaredDoubleHarmonic * TComplex::Conjugate(QVectorRefBHarmonic) * TComplex::Conjugate(QVectorRefBHarmonic)).Re();

    Double_t QnFourPartCorrectionTermSecond = (QVectorRefBCubedHarmonic * TComplex::Conjugate(QVectorRefBHarmonic)).Re();


    

    Double_t TwoPartRefCorr = (QnSquaredRef - S_12) / (TwoPartRefCorrDenom);

    Double_t FourPartRefCorr = (pow(QnSquaredRef,2) + QnSquaredSquaredDoubleRef - 2 * QnFourPartCorrectionTermFirst + 8 * QnFourPartCorrectionTermSecond - 4 * S_12 * QnSquaredRef - 6 * S_14 - 2 * S_22) / (FourPartRefCorrDenom);



    AvgCosCentEPD->Fill(15 - Centrality, QVectorRefBHarmonic.Re() / NMipB, NMipB);
    AvgSinCentEPD->Fill(15 - Centrality, QVectorRefBHarmonic.Im() / NMipB, NMipB);

    
    
    TwoPartRefVsCent->Fill(15 - Centrality, TwoPartRefCorr);
    FourPartRefVsCent->Fill(15 - Centrality, FourPartRefCorr);
    
 
    
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
        Double_t dEdx = pTrack->dEdx();
        Double_t NSigmaPr = pTrack->nSigmaProton();
        Double_t NSigmaKa = pTrack->nSigmaKaon();
        Double_t NSigmaPi = pTrack->nSigmaPion();
        Double_t DCA = pTrack->gDCA(vx,vy,vz);
        Int_t NHits = pTrack->nHits();
        Int_t NHitsdEdx = pTrack->nHitsDedx();
        Int_t NHitsFit = pTrack->nHitsFit();
        Int_t NHitsPoss = pTrack->nHitsPoss();


        Double_t tofBeta = -999.0;
        Double_t EToFBeta = -999.0;

        Bool_t IsGoodEToFMatchFlag = false;
        
        if(pTrack->isTofTrack())
        {
            tofBeta = mPicoDst->btofPidTraits(pTrack->bTofPidTraitsIndex())->btofBeta();
        }

        if((pTrack->isETofTrack()))
        {
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
            continue;
        }
        
        Int_t ParticleIndex = -1;

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

        Double_t p = FlowFunctions::P(px, py, pz);

        Double_t eta = FlowFunctions::Eta(px, py, pz);

        Double_t phi = FlowFunctions::Phi(px, py);



        TPCAcceptance->Fill(eta, phi);

        

        if(std::isnan(p))
        {
            continue;
        }



        //Particle Identification
        Bool_t IsKaon = false;
        Bool_t IsPion = false;
        Bool_t IsDeuteron = false;
        Bool_t IsTriton = false;
        Bool_t IsProtonTPC = (abs(NSigmaPr) < NSigmaPrBound) && (q == 1);

        Double_t msquared = 0;
        

        if((tofBeta > 0) || (EToFBeta > 0))
        {
            msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

            IsKaon = (abs(NSigmaKa) < NSigmaKaBound) && (msquared > KaonLowerMSquared) && (msquared < KaonUpperMSquared);
            IsPion = (abs(NSigmaPi) < NSigmaPiBound) && (msquared > PionLowerMSquared) && (msquared < PionUpperMSquared);
            // IsProtonToF = (abs(NSigmaPr) < NSigmaPrBound) && (msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared) && (q == 1);
        }
    
        Double_t zDeuteron = TMath::Log(dEdx / BichselZDeuteron->Eval(p));
        Double_t zTriton = TMath::Log(dEdx / BichselZTriton->Eval(p));

        // DeuteronsAndTritons DAndT (p, dEdx, tofBeta, EToFBeta, zDeuteron, zTriton, false, false, false, false, false, false);
        DeuteronsAndTritons DAndT (p, dEdx, tofBeta, zDeuteron, zTriton);
   



        if(!(IsKaon) && !(IsPion))
        {
            IsDeuteron = DAndT.IsDeuteron() and (q == 1);
            IsTriton = DAndT.IsTriton() and (q == 1);
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




        Double_t Mass = 0;
        Double_t PtLow = 0;
        Double_t PtHigh = 0;

        if(IsProtonTPC)
        {
            ParticleIndex = 0;
            Mass = 0.938;
            PtLow = 0.4;
            PtHigh = 2.0;
        }

        if((IsKaon) && (q > 0))
        {
            ParticleIndex = 1;
            Mass = 0.493;
            PtLow = 0.4;
            PtHigh = 1.6;
        }

        if((IsKaon) && (q < 0))
        {
            ParticleIndex = 2;
            Mass = 0.493;
            PtLow = 0.4;
            PtHigh = 1.6;
        }

        if((IsPion) && (q > 0))
        {
            ParticleIndex = 3;
            Mass = 0.13957;
            PtLow = 0.18;
            PtHigh = 1.6;
        }

        if((IsPion) && (q < 0))
        {
            ParticleIndex = 4;
            Mass = 0.13957;
            PtLow = 0.18;
            PtHigh = 1.6;
        }

        if(IsDeuteron)
        {
            ParticleIndex = 5;
            Mass = 1.875613;
            PtLow = 0.8;
            PtHigh = 3.5;
        }

        if(IsTriton)
        {
            ParticleIndex = 6;
            Mass = 2.808921;
            PtLow = 1.2;
            PtHigh = 4.0;
        }




        if(ParticleIndex == -1)
        {
            continue;
        }





        Double_t y = FlowFunctions::Y(px, py, pz, Mass);



        TComplex QVectorSingleParticlePOIHarmonic;

        QVectorSingleParticlePOIHarmonic = TComplex(cos(nPsi*phi), sin(nPsi*phi), false);





        Double_t TwoPartDiffCorrNum = (QVectorSingleParticlePOIHarmonic * TComplex::Conjugate(QVectorRefBHarmonic)).Re(); 

        Double_t TwoPartDiffCorr = (TwoPartDiffCorrNum) / (Double_t)(NMipB);



        Double_t FourPartDiffCorrNum = ((QVectorSingleParticlePOIHarmonic * QVectorRefBHarmonic * TComplex::Conjugate(QVectorRefBHarmonic) * TComplex::Conjugate(QVectorRefBHarmonic)).Re() - (QVectorSingleParticlePOIHarmonic * QVectorRefBHarmonic * TComplex::Conjugate(QVectorRefBSquaredDoubleHarmonic)).Re() - 2 * S_12 * (QVectorSingleParticlePOIHarmonic * TComplex::Conjugate(QVectorRefBHarmonic)).Re() + 2 * (QVectorSingleParticlePOIHarmonic * TComplex::Conjugate(QVectorRefBCubedHarmonic)).Re());

        Double_t FourPartDiffCorr = FourPartDiffCorrNum / (pow(S_11,3) - 3 * S_11 * S_12 + 2 * S_13);







        AvgCosCentTPC[ParticleIndex]->Fill(15 - Centrality, cos(nPsi*phi));
        AvgSinCentTPC[ParticleIndex]->Fill(15 - Centrality, sin(nPsi*phi));

        if(15 - Centrality <= 1)
        {
            AvgCosPt00_10TPC[ParticleIndex]->Fill(pt, cos(nPsi*phi));
            AvgSinPt00_10TPC[ParticleIndex]->Fill(pt, sin(nPsi*phi));
            AvgCosY00_10TPC[ParticleIndex]->Fill(y - yCMShift, cos(nPsi*phi));
            AvgSinY00_10TPC[ParticleIndex]->Fill(y - yCMShift, sin(nPsi*phi));
        }
        else if((15 - Centrality >= 2) && (15 - Centrality <= 7))
        {
            AvgCosPt10_40TPC[ParticleIndex]->Fill(pt, cos(nPsi*phi));
            AvgSinPt10_40TPC[ParticleIndex]->Fill(pt, sin(nPsi*phi));
            AvgCosY10_40TPC[ParticleIndex]->Fill(y - yCMShift, cos(nPsi*phi));
            AvgSinY10_40TPC[ParticleIndex]->Fill(y - yCMShift, sin(nPsi*phi));
        }
        else if(15 - Centrality >= 8)
        {
            AvgCosPt40_60TPC[ParticleIndex]->Fill(pt, cos(nPsi*phi));
            AvgSinPt40_60TPC[ParticleIndex]->Fill(pt, sin(nPsi*phi));
            AvgCosY40_60TPC[ParticleIndex]->Fill(y - yCMShift, cos(nPsi*phi));
            AvgSinY40_60TPC[ParticleIndex]->Fill(y - yCMShift, sin(nPsi*phi));
        }

        
        
             


        if((pt > PtLow) && (pt < PtHigh) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift))
        {
            TwoPartDiffVsCentVsY[ParticleIndex]->Fill(15 - Centrality, y - yCMShift, TwoPartDiffCorr);
            FourPartDiffVsCentVsY[ParticleIndex]->Fill(15 - Centrality, y - yCMShift, FourPartDiffCorr);
            
            if((y - yCMShift) < (UpperYMinusYCMShift / 2))
            {
                TwoPartDiffVsCent[ParticleIndex]->Fill(15 - Centrality, TwoPartDiffCorr);
                FourPartDiffVsCent[ParticleIndex]->Fill(15 - Centrality, FourPartDiffCorr);

                TwoPartDiffVsCentVsPt[ParticleIndex]->Fill(15 - Centrality, pt, TwoPartDiffCorr);
                FourPartDiffVsCentVsPt[ParticleIndex]->Fill(15 - Centrality, pt, FourPartDiffCorr);
            }
        }
    }


    delete BichselZDeuteron;
    delete BichselZTriton;

    return kStOK;   
}

