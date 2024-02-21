//////
// THIS IS A VERSION OF FlowAnalyzer.cxx THAT ANALYZES TREES RATHER THAN PICODSTS.
//
// This program reads trees made from picoDsts that have already passed 
// through event cuts. It performs an analysis of anisotropic
// flow coefficients. Many of the controls are, or should be, located
// within the config file that is supplied to the ConfigReader.
// The config files are used to maximize the modularity of the program
// and minimize hardcoding of settings/parameters. Event/track QA cuts, 
// bad runs, and centrality definitions should have been handled when 
// the trees were produced.
//
// Author: Cameron Racz
// Date: 2021
//////


//////
// Do not use vector::erase() to change any vectors. 
// This will invalidate any for() loops iterating over the vectors
// and make things much more complicated. For bad events after 
// creation of the "Event" vector, use the badEvent flag.
//////



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
#include "../StRoot/StBichsel/Bichsel.h"
#include "../StRoot/StEpdUtil/StEpdGeom.h"
#include "FlowFunctions.h"
#include "DeuteronsAndTritons.h"
#include "TileVector.h"


//Bichsel function
Double_t BichselZ(Double_t *p, Double_t *parameters) 
{
    Double_t POverM = p[0] / parameters[0];

    return TMath::Exp(Bichsel::Instance()->GetMostProbableZ(TMath::Log10(POverM),parameters[1]));
}



int main(int argc, char *argv[])
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
    
    
    
    const int nPsi = 1;
    const int nV = 3;



//     TFile *LastHistogramFile = TFile::Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/HistogramThirdPass" + argv[3] +".root");
//     if(!LastHistogramFile)
//     {
//         TFile *LastHistogramFile = TFile::Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/HistogramSecondPass" + argv[3] +".root");
//         if(!LastHistogramFile)
//         {
//             TFile *LastHistogramFile = TFile::Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/HistogramFirstPass" + argv[3] +".root")
//             {
//                 if(!LastHistogramFile)
//                 {
//                     int RunIteration = 1;
//                 }
                
//                 int RunIteration = 2;
//             }
            
//             int RunIteration = 3;
            
//         }
        
//         RunIteration = 4;
//     }


    int RunIteration = 1;

    
    
    // Parameters
    double yCMShift = -1.05;
    int NumberOfGoodTracksInnerEPD = 5;
    int NumberOfGoodTracksOuterEPD = 9;
    int NumberOfGoodTracksOuterTPC = 5;
    double OuterTPCUpperLimit = 0.0;
    double OuterTPCLowerLimit = -1.0;
    double InnerTPCUpperLimit = -1.1;
    double InnerTPCLowerLimit = -2.0;



    double RVertexBound = 1.5;
    double ZVertexLowerBound = 198.0;
    double ZVertexUpperBound = 202.0;
    double DCABound = 3.0;



    int NHitsBound = 15;
    int NHitsdEdxBound = 5;
    double NHitsFitOverNHitsPossBound = 0.52;
    int InnerEPDHighRing = 8;
    int OuterEPDLowRing = 9;
    //double ProtonLowerMSquared = 0.6;
    //double ProtonUpperMSquared = 1.2;
    double KaonLowerMSquared = 0.15;
    double KaonUpperMSquared = 0.34;
    double PionLowerMSquared = -0.1;
    double PionUpperMSquared = 0.1;
    double NSigmaPrBound = 2.0;
    double NSigmaKaBound = 3.0;
    double NSigmaPiBound = 3.0;
    double ProtonLowerPt = 0.4;
    double ProtonUpperPt = 2.0;
    double KaonLowerPt = 0.4;
    double KaonUpperPt = 1.6;
    double PionLowerPt = 0.18;
    double PionUpperPt = 1.6;
    double DeuteronLowerPt = 0.2;
    double DeuteronUpperPt = 1.0;
    double TritonLowerPt = 0.2;
    double TritonUpperPt = 1.0;
    double LowerYMinusYCMShift = 0.0;
    double UpperYMinusYCMShift = 1.0;



    int QBounds = 100;
    int FourierCorrectionTerms = 10;


    
    // Parameter changes for systematic runs
    if (strcmp(argv[3], "Normal") == 0)
    {
        QBounds = 100;
        FourierCorrectionTerms = 10;
    }
    else if (strcmp(argv[3], "RVertex20Low") == 0)
    {
        RVertexBound = 1.2;
    }
    else if (strcmp(argv[3], "RVertex30Low") == 0)
    {
        RVertexBound = 1.05;
    }
    else if (strcmp(argv[3], "RVertex20High") == 0)
    {
        RVertexBound = 1.8;
    }
    else if(strcmp(argv[3], "RVertex30High") == 0)
    {
        RVertexBound = 1.95;
    }
    else if (strcmp(argv[3], "ZVertex20Low") == 0)
    {
        ZVertexLowerBound = 198.4;
        ZVertexUpperBound = 201.6;
    }
    else if (strcmp(argv[3], "ZVertex20High") == 0)
    {
        ZVertexLowerBound = 197.6;
        ZVertexUpperBound = 202.4;
    }
    else if (strcmp(argv[3], "ZVertex30Low") == 0)
    {
        ZVertexLowerBound = 198.6;
        ZVertexUpperBound = 201.4;
    }
    else if (strcmp(argv[3], "ZVertex30High") == 0)
    {
        ZVertexLowerBound = 197.4;
        ZVertexUpperBound = 202.6;
    }
    else if (strcmp(argv[3], "DCA20Low") == 0)
    {
        DCABound = 2.4;
    }
    else if (strcmp(argv[3], "DCA20High") == 0)
    {
        DCABound = 3.6;
    }
    else if (strcmp(argv[3], "DCA30Low") == 0)
    {
        DCABound = 2.1;
    }
    else if (strcmp(argv[3], "DCA30High") == 0)
    {
        DCABound = 3.9;
    }
    else if (strcmp(argv[3], "NHits20Low") == 0)
    {
        NHitsBound = 12;
    }
    else if (strcmp(argv[3], "NHits20High") == 0)
    {
        NHitsBound = 18;
    }
    else if (strcmp(argv[3], "NHits30Low") == 0)
    {
        NHitsBound = 10;
    }
    else if (strcmp(argv[3], "NHits30High") == 0)
    {
        NHitsBound = 20;
    }
    else if (strcmp(argv[3], "NHitsdEdx20High") == 0)
    {
        NHitsdEdxBound = 9;
    }
    else if (strcmp(argv[3], "NHitsdEdx30High") == 0)
    {
        NHitsdEdxBound = 12;
    }
    else if (strcmp(argv[3], "NHitsFitOverNHitsPoss20Low") == 0)
    {
        NHitsFitOverNHitsPossBound = 0.416;
    }
    else if (strcmp(argv[3], "NHitsFitOverNHitsPoss20High") == 0)
    {
        NHitsFitOverNHitsPossBound = 0.624;
    }
    else if (strcmp(argv[3], "NHitsFitOverNHitsPoss30Low") == 0)
    {
        NHitsFitOverNHitsPossBound = 0.364;
    }
    else if (strcmp(argv[3], "NHitsFitOverNHitsPoss30High") == 0)
    {
        NHitsFitOverNHitsPossBound = 0.676;
    }
    else if (strcmp(argv[3], "NSigmaPion20Low") == 0)
    {
        NSigmaPiBound = 2.4;
    }
    else if (strcmp(argv[3], "NSigmaPion20High") == 0)
    {
        NSigmaPiBound = 3.6;
    }
    else if (strcmp(argv[3], "NSigmaPion30Low") == 0)
    {
        NSigmaPiBound = 2.1;
    }
    else if (strcmp(argv[3], "NSigmaPion30High") == 0)
    {
        NSigmaPiBound = 3.9;
    }
    else if (strcmp(argv[3], "NSigmaKaon20Low") == 0)
    {
        NSigmaKaBound = 2.4;
    }
    else if (strcmp(argv[3], "NSigmaKaon20High") == 0)
    {
        NSigmaKaBound = 3.6;
    }
    else if (strcmp(argv[3], "NSigmaKaon30Low") == 0)
    {
        NSigmaKaBound = 2.1;
    }
    else if (strcmp(argv[3], "NSigmaKaon30High") == 0)
    {
        NSigmaKaBound = 3.9;
    }
    else if (strcmp(argv[3], "NSigmaProton20Low") == 0)
    {
        NSigmaPrBound = 1.6;
    }
    else if (strcmp(argv[3], "NSigmaProton20High") == 0)
    {
        NSigmaPrBound = 2.4;
    }
    else if (strcmp(argv[3], "NSigmaProton30Low") == 0)
    {
        NSigmaPrBound = 1.4;
    }
    else if (strcmp(argv[3], "NSigmaProton30High") == 0)
    {
        NSigmaPrBound = 2.6;
    }
    else if (strcmp(argv[3], "MSquaredPion20Low") == 0)
    {
        PionLowerMSquared = -0.08;
        PionUpperMSquared = 0.08;
    }
    else if (strcmp(argv[3], "MSquaredPion20High") == 0)
    {
        PionLowerMSquared = -0.12;
        PionUpperMSquared = 0.12;
    }
    else if (strcmp(argv[3], "MSquaredPion30Low") == 0)
    {
        PionLowerMSquared = -0.07;
        PionUpperMSquared = 0.07;
    }
    else if (strcmp(argv[3], "MSquaredPion30High") == 0)
    {
        PionLowerMSquared = -0.13;
        PionUpperMSquared = 0.13;
    }
    else if (strcmp(argv[3], "MSquaredKaon20Low") == 0)
    {
        KaonLowerMSquared = 0.169;
        KaonUpperMSquared = 0.321;
    }
    else if (strcmp(argv[3], "MSquaredKaon20High") == 0)
    {
        KaonLowerMSquared = 0.131;
        KaonUpperMSquared = 0.359;
    }
    else if (strcmp(argv[3], "MSquaredKaon30Low") == 0)
    {
        KaonLowerMSquared = 0.1785;
        KaonUpperMSquared = 0.3115;
    }
    else if (strcmp(argv[3], "MSquaredKaon30High") == 0)
    {
        KaonLowerMSquared = 0.1215;
        KaonUpperMSquared = 0.3685;
    }
    else if (strcmp(argv[3], "OuterEPDLow") == 0)
    {
        InnerEPDHighRing = 12;
        OuterEPDLowRing = 13;
    }
    else if (strcmp(argv[3], "OuterEPDHigh") == 0)
    {
        InnerEPDHighRing = 9;
        OuterEPDLowRing = 10;
    }
    else
    {
        std::cout << "No Matching Systematic Error type (or Normal)" << std::endl;
        exit(0);
    }
    
    
    //Input files
    TFile *Data = TFile::Open(argv[1]);
    
    TFile *QVectorHistogramFileFirst;
    TFile *QVectorHistogramFileSecond;
    TFile *ResolutionFile; 

    
    if(RunIteration == 2)
    {
        std::string QVectorHistogramFirstString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/QVectorFirstPass" + argv[3] + ".root";
        char *QVectorHistogramFirstChar = &QVectorHistogramFirstString[0];

        QVectorHistogramFileFirst = TFile::Open(QVectorHistogramFirstChar);
    }
    
    if(RunIteration == 3)
    {
        std::string QVectorHistogramFirstString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/QVectorFirstPass" + argv[3] + ".root";
        char *QVectorHistogramFirstChar = &QVectorHistogramFirstString[0];

        QVectorHistogramFileFirst = TFile::Open(QVectorHistogramFirstChar);
        
        std::string QVectorHistogramSecondString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/QVectorSecondPass" + argv[3] + ".root";
        char *QVectorHistogramSecondChar = &QVectorHistogramSecondString[0];
    
        QVectorHistogramFileSecond = TFile::Open(QVectorHistogramSecondChar);
    }
    
    if(RunIteration == 4)
    {
        std::string QVectorHistogramFirstString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/QVectorFirstPass" + argv[3] + ".root";
        char *QVectorHistogramFirstChar = &QVectorHistogramFirstString[0];

        QVectorHistogramFileFirst = TFile::Open(QVectorHistogramFirstChar);
        
        std::string QVectorHistogramSecondString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/QVectorSecondPass" + argv[3] + ".root";
        char *QVectorHistogramSecondChar = &QVectorHistogramSecondString[0];
    
        QVectorHistogramFileSecond = TFile::Open(QVectorHistogramSecondChar);
        
        std::string ResolutionFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/R_" + std::to_string(nV) + std::to_string(nPsi) + "_" + argv[3] + ".root";
        const char* ResolutionFileChar = &ResolutionFileString[0];
    
        ResolutionFile = TFile::Open(ResolutionFileChar);
    }
    
    
    
    //Tree Setup
    int tracknumber;
    float Px[tracknumber];
    float Py[tracknumber];
    float Pz[tracknumber];
    int Charge[tracknumber];
    float ToFBeta[tracknumber];
    float dedx[tracknumber];
    float nSigmaPr[tracknumber];
    float nSigmaKa[tracknumber];
    float nSigmaPi[tracknumber];
    float Vx;
    float Vy;
    float Vz;
    int centrality;
    float dca[tracknumber];
    int nHits[tracknumber];
    int nHitsdEdx[tracknumber];
    int nHitsFit[tracknumber];
    int nHitsPoss[tracknumber];
    int nEPDhits;
    float EPDnMip[744];
    int EPDid[744];
    
    
    
    TTree *AutreeData = (TTree*)Data->Get("Autree");
    AutreeData->SetBranchAddress("tracknumber", &tracknumber);
    AutreeData->SetBranchAddress("Px", &Px);
    AutreeData->SetBranchAddress("Py", &Py);
    AutreeData->SetBranchAddress("Pz", &Pz);
    AutreeData->SetBranchAddress("Charge", &Charge);
    AutreeData->SetBranchAddress("tofBeta", &ToFBeta);
    AutreeData->SetBranchAddress("dEdx", &dedx);
    AutreeData->SetBranchAddress("nSigmaPr", &nSigmaPr);
    AutreeData->SetBranchAddress("nSigmaKa", &nSigmaKa);
    AutreeData->SetBranchAddress("nSigmaPi", &nSigmaPi);
    AutreeData->SetBranchAddress("Vx", &Vx);
    AutreeData->SetBranchAddress("Vy", &Vy);
    AutreeData->SetBranchAddress("Vz", &Vz);
    AutreeData->SetBranchAddress("centrality", &centrality);
    AutreeData->SetBranchAddress("DCA", &dca); 
    AutreeData->SetBranchAddress("nHits", &nHits);
    AutreeData->SetBranchAddress("nHitsDedx", &nHitsdEdx);
    AutreeData->SetBranchAddress("nHitsFit", &nHitsFit);
    AutreeData->SetBranchAddress("nHitsPoss", &nHitsPoss);
    AutreeData->SetBranchAddress("nEPDhits", &nEPDhits);
    AutreeData->SetBranchAddress("EPDnMip", &EPDnMip);
    AutreeData->SetBranchAddress("EPDid", &EPDid);
    
    //print(Data.ls())

    //print(AutreeData.Print())    
    
    
    
    
    //Histograms
    
    //First Pass Histograms
    TH1D *HistoInnerEPDQxRaw = new TH1D("InnerEPDQxRaw", "Qx Raw for Inner EPD; Qx; Events", 250, -QBounds, QBounds);
    TH1D *HistoInnerEPDQyRaw = new TH1D("InnerEPDQyRaw", "Qy Raw for Inner EPD; Qy; Events", 250, -QBounds, QBounds);
    TH1D *HistoOuterEPDQxRaw = new TH1D("OuterEPDQxRaw", "Qx Raw for Outer EPD; Qx; Events", 250, -QBounds, QBounds);
    TH1D *HistoOuterEPDQyRaw = new TH1D("OuterEPDQyRaw", "Qy Raw for Inner EPD; Qy; Events", 250, -QBounds, QBounds);
    TH1D *HistoOuterTPCQxRaw = new TH1D("OuterTPCQxRaw", "Qx Raw for Outer TPC; Qx; Events", 250, -QBounds, QBounds);
    TH1D *HistoOuterTPCQyRaw = new TH1D("OuterTPCQyRaw", "Qy Raw for Outer TPC; Qy; Events", 250, -QBounds, QBounds);

    

    TH1F *HistoDA = new TH1F("DataNSigmaProtonAll", "All NSigmaProton Values; NSigmaProton; Events", 10, -5, 5);
    HistoDA->Sumw2();
    
    TH1F *HistoDB = new TH1F("DataNSigmaProtonUsed", "Used NSigmaProton Values; NSigmaProton; Events", 10, -5, 5);
    HistoDB->Sumw2();
    

    
    
    
    
    
    TH2F *HistoD0 = new TH2F("DataVxVy","Target Vx and Vy; Vx; Vy", 500, -5, 5, 500, -5, 5);
    HistoD0->Sumw2();
    
    TH1F *HistoD1 = new TH1F("DataPt", "Pt (Data); Pt (GeV); Events", 500, 0, 2);
    HistoD1->Sumw2();

    TH1F *HistoD2 = new TH1F("DataEta", "Eta (Data); Eta; Events", 500, -3, 0);
    HistoD2->Sumw2();

    TH2F *HistoD3 = new TH2F("DataPtVsEta", "Pt vs Eta (Data); Eta; Pt (GeV)", 500, -3, 0, 500, 0, 2);
    HistoD3->Sumw2();

    TH2F *HistoD4 = new TH2F("DataMSquaredVsQP", "m^2 vs q|p| (Data); q|p| (GeV); m^2 (GeV^2)", 1000, -4, 4, 1000, -0.1, 10);
    HistoD4->Sumw2();

    TH2F *HistoD4A = new TH2F("DataMSquaredVsQPZoomed", "m^2 vs q|p| (Data); q|p| (GeV); m^2 (GeV^2)", 1000, -4, 4, 1000, -0.1, 0.15);
    HistoD4A->Sumw2();

    TH1F *HistoD5 = new TH1F("DataYProton", "Y for Protons (Data); Y - Y_CM; Events", 500, -1, 1);
    HistoD5->Sumw2();

    TH1F *HistoD6 = new TH1F("DataYKaon", "Y for Kaons (Data); Y - Y_CM; Events", 500, -1, 1);
    HistoD6->Sumw2();

    TH1F *HistoD7 = new TH1F("DataYPion", "Y for Pions (Data); Y - Y_CM; Events", 500, -1, 1);
    HistoD7->Sumw2();

    TH1F *HistoD8 = new TH1F("DataPtProton", "Pt for Protons, m^2 cut only (Data); Pt (GeV); Events", 500, 0, 2);
    HistoD8->Sumw2();

    TH1F *HistoD9 = new TH1F("DataPtKaon", "Pt for Kaons, m^2 cut only (Data); Pt (GeV); Events", 500, 0, 2);
    HistoD9->Sumw2();

    TH1F *HistoD10 = new TH1F("DataPtPion", "Pt for Pions, m^2 cut only (Data); Pt (GeV); Events", 500, 0, 2);
    HistoD10->Sumw2();

    TH1F *HistoD11 = new TH1F("DataMultiplicity", "Multiplicity (Data); Multiplicity; Events", 200, 0, 200);
    HistoD11->Sumw2();

    TH2F *HistoD12 = new TH2F("DatadEdxVsP", "dE/dx vs p (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10);
    HistoD12->Sumw2();

    TH2F *HistoD13 = new TH2F("DatadEdxVsPPion", "dE/dx vs p for Pions (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10);
    HistoD13->Sumw2();

    TH2F *HistoD14 = new TH2F("DatadEdxVsPKaon", "dE/dx vs p for Kaons (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10);
    HistoD14->Sumw2();

    TH2F *HistoD15 = new TH2F("DatadEdxVsPProton", "dE/dx vs p for Protons (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10);
    HistoD15->Sumw2();

    TH2F *HistoD16 = new TH2F("DatadEdxVsPDeuteron", "dE/dx vs p for Deuterons (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10);
    HistoD16->Sumw2();

    TH2F *HistoD17 = new TH2F("DatadEdxVsPTriton", "dE/dx vs p for Tritons (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10);
    HistoD17->Sumw2();

    TH2F *HistoD18 = new TH2F("DataMSquaredVsQPProton", "m^2 vs q|p| for Protons (Data); q|p| (GeV); m^2 (GeV^2)", 1000, -4, 4, 1000, -0.1, 1.5);
    HistoD18->Sumw2();

    TH2F *HistoD19 = new TH2F("DataMSquaredVsQPKaon", "m^2 vs q|p| for Kaons (Data); q|p| (GeV); m^2 (GeV^2)", 1000, -4, 4, 1000, -0.1, 1.5);
    HistoD19->Sumw2();

    TH2F *HistoD20 = new TH2F("DataMSquaredVsQPPion", "m^2 vs q|p| for Pions (Data); q|p| (GeV); m^2 (GeV^2)", 1000, -4, 4, 1000, -0.1, 1.5);
    HistoD20->Sumw2();

    TH1F *HistoD21 = new TH1F("DataPtProtonBothCuts", "Pt for Protons, m^2 and dE/dx cuts (Data); Pt (GeV); Events", 500, 0, 2);
    HistoD21->Sumw2();

    TH1F *HistoD22 = new TH1F("DataPtKaonBothCuts", "Pt for Kaons, m^2 and dE/dx cuts (Data); Pt (GeV); Events", 500, 0, 2);
    HistoD22->Sumw2();

    TH1F *HistoD23 = new TH1F("DataPtPionBothCuts", "Pt for Pions, m^2 and dE/dx cuts (Data); Pt (GeV); Events", 500, 0, 2);
    HistoD23->Sumw2();

    TH2F *HistoD24 = new TH2F("DataNSigmaPrVsQPProton", "NSigmaPr vs q|p| for Protons (Data); q|p| (GeV); NSigmaPr", 1000, -4, 4, 1000, -3, 3);
    HistoD24->Sumw2();

    TH2F *HistoD25 = new TH2F("DataNSigmaKaVsQPKaon", "NSigmaKa vs q|p| for Kaons (Data); q|p| (GeV); NSigmaKa", 1000, -4, 4, 1000, -3, 3);
    HistoD25->Sumw2();

    TH2F *HistoD26 = new TH2F("DataNSigmaPiVsQPPion", "NSigmaPi vs q|p| for Pions (Data); Pt (GeV); NSigmaPi", 1000, -4, 4, 1000, -3, 3);
    HistoD26->Sumw2();

    TH2F *HistoD27 = new TH2F("DataPtVsYProton", "Pt vs Y for Protons (Data); y_{CM}; Pt (Gev)", 500, -1, 1, 1000, 0, 3);
    HistoD27->Sumw2();
    
    TH2F *HistoD27A = new TH2F("DataPtVsYDeuteron", "Pt vs Y for Deuterons (Data); y_{CM}; Pt (Gev)", 500, -1, 1, 1000, 0, 5);
    HistoD27A->Sumw2();
    
    TH2F *HistoD27B = new TH2F("DataPtVsYTriton", "Pt vs Y for Tritons (Data); y_{CM}; Pt (Gev)", 500, -1, 1, 1000, 0, 7);
    HistoD27B->Sumw2();

    TH2F *HistoD28 = new TH2F("DataPtVsYKaonPlus", "Pt vs Y for K+ (Data); y_{CM}; Pt (Gev)", 500, -1, 1, 1000, 0, 2.5);
    HistoD28->Sumw2();

    TH2F *HistoD29 = new TH2F("DataPtVsYKaonMinus", "Pt vs Y for K- (Data); y_{CM}; Pt (Gev)", 500, -1, 1, 1000, 0, 2.5);
    HistoD29->Sumw2();

    TH2F *HistoD30 = new TH2F("DataPtVsYPionPlus", "Pt vs Y for Pi+ (Data); y_{CM}; Pt (Gev)", 500, -1, 1, 1000, 0, 2.5);
    HistoD30->Sumw2();

    TH2F *HistoD31 = new TH2F("DataPtVsYPionMinus", "Pt vs Y for Pi- (Data); y_{CM}; Pt (Gev)", 500, -1, 1, 1000, 0, 2.5);
    HistoD31->Sumw2();

    TH1F *HistoD32 = new TH1F("DataPhiTPC", "TPC Phi (Data); Phi; Events", 500, -3.5, 3.5);
    HistoD32->Sumw2();

    TH1F *HistoD32A = new TH1F("DataPhiEPD", "EPD Phi (Data); Phi; Events", 500, -3.5, 3.5);
    HistoD32A->Sumw2();

    TH2F *HistoD32B = new TH2F("DataEPDEastRingVsEta", "EPD East Ring vs Eta; Eta; Ring Number", 500, -6, -1, 500, 0.5, 16.5);
    HistoD32B->Sumw2();

    TH1F *HistoD33 = new TH1F("DataPsi1RawInnerEPD", "Reaction Plane Angle, Psi_1, Inner EPD (Data); Psi; Events", 500, -3.5, 3.5);
    HistoD33->Sumw2();

    TH1F *HistoD36 = new TH1F("DataPsi1RawOuterEPD", "Reaction Plane Angle, Psi_1, Outer EPD (Data); Psi; Events", 500, -3.5, 3.5);
    HistoD36->Sumw2();

    TH1F *HistoD39 = new TH1F("DataPsi1RawOuterTPC", "Reaction Plane Angle, Psi_1, Outer TPC (Data); Psi; Events", 500, -3.5, 3.5);
    HistoD39->Sumw2();
    
    std::string StringD42 = "V" + std::to_string(nV) + " Observed vs Y for Protons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *CharD42 = &StringD42[0];
    
    TProfile *HistoD42 = new TProfile("DataVnVsYPsi1RawInnerEPDProton", CharD42, 75, -0.3, 0.95);
    HistoD42->Sumw2();
    
    std::string StringD42A = "V" + std::to_string(nV) + " Observed vs Y for Deuterons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *CharD42A = &StringD42A[0];
    
    TProfile *HistoD42A = new TProfile("DataVnVsYPsi1RawInnerEPDDeuteron", CharD42A, 75, -0.3, 0.95);
    HistoD42A->Sumw2();
    
    std::string StringD42B = "V" + std::to_string(nV) + " Observed vs Y for Tritons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *CharD42B = &StringD42B[0];

    TProfile *HistoD42B = new TProfile("DataVnVsYPsi1RawInnerEPDTriton", CharD42B, 75, -0.3, 0.95);
    HistoD42B->Sumw2();
    
    std::string StringD45 = "V" + std::to_string(nV) + " Observed vs Y for Kaons Plus, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *CharD45 = &StringD45[0];

    TProfile *HistoD45 = new TProfile("DataVnVsYPsi1RawInnerEPDKaonPlus", CharD45, 75, -0.3, 0.95);
    HistoD45->Sumw2();
    
    std::string StringD45A = "V" + std::to_string(nV) + " Observed vs Y for Kaons Minus, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *CharD45A = &StringD45A[0];

    TProfile *HistoD45A = new TProfile("DataVnVsYPsi1RawInnerEPDKaonMinus", CharD45A, 75, -0.3, 0.95);
    HistoD45A->Sumw2();

    std::string StringD48 = "V" + std::to_string(nV) + " Observed vs Y for Deuterons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *CharD48 = &StringD48[0];    
    
    TProfile *HistoD48 = new TProfile("DataVnVsYPsi1RawInnerEPDPionPlus", CharD48, 75, -0.3, 0.95);
    HistoD48->Sumw2();
    
    std::string StringD48A = "V" + std::to_string(nV) + " Observed vs Y for Tritons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *CharD48A = &StringD48A[0];

    TProfile *HistoD48A = new TProfile("DataVnVsYPsi1RawInnerEPDPionMinus", CharD48A, 75, -0.3, 0.95);
    HistoD48A->Sumw2();
    
    
    //Second Pass Histograms
    
    TH1D *HistoInnerEPDQxRecentered = new TH1D("InnerEPDQxRecentered", "Qx Recentered for Inner EPD; Qx; Events", 250, -QBounds, QBounds);
    TH1D *HistoInnerEPDQyRecentered = new TH1D("InnerEPDQyRecentered", "Qy Recentered for Inner EPD; Qy; Events", 250, -QBounds, QBounds);
    TH1D *HistoOuterEPDQxRecentered = new TH1D("OuterEPDQxRecentered", "Qx Recentered for Outer EPD; Qx; Events", 250, -QBounds, QBounds);
    TH1D *HistoOuterEPDQyRecentered = new TH1D("OuterEPDQyRecentered", "Qy Recentered for Outer EPD; Qy; Events", 250, -QBounds, QBounds);
    TH1D *HistoOuterTPCQxRecentered = new TH1D("OuterTPCQxRecentered", "Qx Recentered for TPC; Qx; Events", 250, -QBounds, QBounds);
    TH1D *HistoOuterTPCQyRecentered = new TH1D("OuterTPCQyRecentered", "Qy Recentered for TPC; Qy; Events", 250, -QBounds, QBounds);
    
    
    TProfile *HistoInnerEPDSineAverages = new TProfile("InnerEPDSineAverages", "Inner EPD Sine Averages; j; Sine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
    TProfile *HistoInnerEPDCosineAverages = new TProfile("InnerEPDCosineAverages", "Inner EPD Cosine Averages; j; Cosine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
    TProfile *HistoOuterEPDSineAverages = new TProfile("OuterEPDSineAverages", "Outer EPD Sine Averages; j; Sine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
    TProfile *HistoOuterEPDCosineAverages = new TProfile("OuterEPDCosineAverages", "Outer EPD Cosine Averages; j; Cosine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
    TProfile *HistoOuterTPCSineAverages = new TProfile("OuterTPCSineAverages", "Outer TPC Sine Averages; j; Sine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
    TProfile *HistoOuterTPCCosineAverages = new TProfile("OuterTPCCosineAverages", "Outer TPC Cosine Averages; j; Cosine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
    
    
    

    TH1F *HistoD34 = new TH1F("DataPsi1RecenteredInnerEPD", "Reaction Plane Angle, Psi_1, Inner EPD (Data); Psi; Events", 500, -3.5, 3.5);
    HistoD34->Sumw2();
    
    TH1F *HistoD37 = new TH1F("DataPsi1RecenteredOuterEPD", "Reaction Plane Angle, Psi_1, Outer EPD (Data); Psi; Events", 500, -3.5, 3.5);
    HistoD37->Sumw2();    
    
    TH1F *HistoD40 = new TH1F("DataPsi1RecenteredOuterTPC", "Reaction Plane Angle, Psi_1, Outer TPC (Data); Psi; Events", 500, -3.5, 3.5);
    HistoD40->Sumw2();
    
    std::string D43String = "V" + std::to_string(nV) + " Observed vs Y for Protons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D43Char = &D43String[0];

    TProfile *HistoD43 = new TProfile("DataVnVsYPsi1RecenteredInnerEPDProton", D43Char, 75, -0.3, 0.95);
    HistoD43->Sumw2();
    
    std::string D43AString = "V" + std::to_string(nV) + " Observed vs Y for Protons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D43AChar = &D43AString[0];

    TProfile *HistoD43A = new TProfile("DataVnVsYPsi1RecenteredInnerEPDDeuteron", D43AChar, 75, -0.3, 0.95);
    HistoD43A->Sumw2();
    
    std::string D43BString = "V" + std::to_string(nV) + " Observed vs Y for Protons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D43BChar = &D43BString[0];

    TProfile *HistoD43B = new TProfile("DataVnVsYPsi1RecenteredInnerEPDTriton", D43BChar, 75, -0.3, 0.95);
    HistoD43B->Sumw2();
    
    std::string D46String = "V" + std::to_string(nV) + " Observed vs Y for Protons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D46Char = &D46String[0];
    
    TProfile *HistoD46 = new TProfile("DataVnVsYPsi1RecenteredInnerEPDKaonPlus", D46Char, 75, -0.3, 0.95);
    HistoD46->Sumw2();
    
    std::string D46AString = "V" + std::to_string(nV) + " Observed vs Y for Protons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D46AChar = &D46AString[0];

    TProfile *HistoD46A = new TProfile("DataVnVsYPsi1RecenteredInnerEPDKaonMinus", D46AChar, 75, -0.3, 0.95);
    HistoD46A->Sumw2();
    
    std::string D49String = "V" + std::to_string(nV) + " Observed vs Y for Protons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D49Char = &D49String[0];

    TProfile *HistoD49 = new TProfile("DataVnVsYPsi1RecenteredInnerEPDPionPlus", D49Char, 75, -0.3, 0.95);
    HistoD49->Sumw2();
    
    std::string D49AString = "V" + std::to_string(nV)+ " Observed vs Y for Protons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D49AChar = &D49AString[0];

    TProfile *HistoD49A = new TProfile("DataVnVsYPsi1RecenteredInnerEPDPionMinus", D49AChar, 75, -0.3, 0.95);
    HistoD49A->Sumw2();
    
    
    
    //Third Pass Histograms        
        
    TH1F *HistoD35 = new TH1F("DataPsi1RecenteredAndShiftedInnerEPD", "Reaction Plane Angle, Psi_1 Inner EPD (Data); Psi; Events", 500, -3.5, 3.5);
    HistoD35->Sumw2();

    TH1F *HistoD38 = new TH1F("DataPsi1RecenteredAndShiftedOuterEPD", "Reaction Plane Angle, Psi_1, Outer EPD (Data); Psi; Events", 500, -3.5, 3.5);
    HistoD38->Sumw2();

    TH1F *HistoD41 = new TH1F("DataPsi1RecenteredAndShiftedOuterTPC", "Reaction Plane Angle, Psi_1, Outer TPC (Data); Psi; Events", 500, -3.5, 3.5);
    HistoD41->Sumw2();
        
    std::string D44String = "V" + std::to_string(nV) + " Observed vs Y for Protons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D44Char = &D44String[0];    

    TProfile *HistoD44 = new TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDProton", D44Char, 75, -0.3, 0.95);
    HistoD44->Sumw2();
        
    std::string D44AString = "V" + std::to_string(nV) + " Observed vs Y for Deuterons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D44AChar = &D44AString[0];  
    
    TProfile *HistoD44A = new TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDDeuteron", D44AChar, 75, -0.3, 0.95);
    HistoD44A->Sumw2();
        
    std::string D44BString = "V" + std::to_string(nV) + " Observed vs Y for Tritons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D44BChar = &D44BString[0];  

    TProfile *HistoD44B = new TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDTriton", D44BChar, 75, -0.3, 0.95);
    HistoD44B->Sumw2();
        
    std::string D47String = "V" + std::to_string(nV) + " Observed vs Y for K+, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D47Char = &D47String[0];  

    TProfile *HistoD47 = new TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDKaonPlus", D47Char, 75, -0.3, 0.95);
    HistoD47->Sumw2();
        
    std::string D47AString = "V" + std::to_string(nV) + " Observed vs Y for K-, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D47AChar = &D47AString[0];  

    TProfile *HistoD47A = new TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDKaonMinus", D47AChar, 75, -0.3, 0.95);
    HistoD47A->Sumw2();
        
    std::string D50String = "V" + std::to_string(nV) + " Observed vs Y for Pi+, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D50Char = &D50String[0];  

    TProfile *HistoD50 = new TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDPionPlus", D50Char, 75, -0.3, 0.95);
    HistoD50->Sumw2();
        
    std::string D50AString = "V" + std::to_string(nV) + " Observed vs Y for K-, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D50AChar = &D50AString[0];  

    TProfile *HistoD50A = new TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDPionMinus", D50AChar, 75, -0.3, 0.95);
    HistoD50A->Sumw2();
    
    TProfile *HistoD51 = new TProfile("DataResolutionTopLeftTerm", "Resolution Top Left Term (Data); Centrality; Top Left Term", 12, 0, 12);
    HistoD51->Sumw2();

    TProfile *HistoD52 = new TProfile("DataResolutionTopRightTerm", "Resolution Top Right Term (Data); Centrality; Top Right Term", 12, 0, 12);
    HistoD52->Sumw2();

    TProfile *HistoD53 = new TProfile("DataResolutionBottomTerm", "Resolution Bottom Term (Data); Centrality; Bottom Term", 12, 0, 12);
    HistoD53->Sumw2();
    
    
    
    //Fourth Pass Histograms

    TFile *TPCEfficiencyFile = TFile::Open("/star/u/mcgordon/VnFromEPD/TPCEfficiency.root","READ");
    TFile *ToFEfficiencyFile = TFile::Open("/star/u/mcgordon/VnFromEPD/ToFEfficiency.root","READ");
    TFile *TPCEfficiencyFileDandT = TFile::Open("/star/u/mcgordon/VnFromEPD/TPCEfficiencyDandT.root","READ");

    
    
    
//     OverallTrackCheckLabels = ["No Track Cuts", "After QA Cuts", "IDed as a Particle"]
//     ProtonTrackLabels = ["IDed as Any Particle", "IDed as a Proton", "IDed as a Good Proton"]
//     KaonPlusTrackLabels = ["IDed as Any Particle", "IDed as a K-", "IDed as a Good K+"]    
//     KaonMinusTrackLabels = ["IDed as Any Particle", "IDed as a K+", "IDed as a Good K-"]    
//     PionPlusTrackLabels = ["IDed as Any Particle", "IDed as a Pi+", "IDed as a Good Pi+"]    
//     PionMinusTrackLabels = ["IDed as Any Particle", "IDed as a Pi-", "IDed as a Good Pi-"]    
//     DeuteronTrackLabels = ["IDed as Any Particle", "IDed as a d", "IDed as a Good d"]     
//     TritonTrackLabels = ["IDed as Any Particle", "IDed as a t", "IDed as a Good t"]     
    
    

    TH1D *EventCheck = (TH1D*)Data->Get("h_eventCheck");
    EventCheck->GetXaxis()->SetBinLabel(6,"Min Hits Cut");
    
    TH1F *OverallTrackCheckNoCuts = new TH1F("OverallTrackCheckNoCuts","Overall Tracks No Cut; One; Tracks", 2, 0, 2);
    OverallTrackCheckNoCuts->Sumw2();

//     for i in range(1, OverallTrackCheck.GetNbinsX() + 1):
//         OverallTrackCheck.GetXaxis().SetBinLabel(i, OverallTrackCheckLabels[i - 1])

    TH1F *OverallTrackCheckQACuts = new TH1F("OverallTrackCheckQACuts","Overall Tracks QA Cuts; One; Tracks", 2, 0, 2);
    OverallTrackCheckQACuts->Sumw2();
    
    TH1F *OverallTrackCheckIDedAsAny = new TH1F("OverallTrackCheckIDedAsAny","Overall Tracks IDed As Any Particle; One; Tracks", 2, 0, 2);
    OverallTrackCheckIDedAsAny->Sumw2();
    
    TH1F *ProtonTrackCheck = new TH1F("ProtonTrackCheck","Particles IDed as Protons; One; Tracks", 2, 0, 2);
    ProtonTrackCheck->Sumw2();
    
//     for i in range(1, ProtonTrackCheck.GetNbinsX() + 1):
//         ProtonTrackCheck.GetXaxis().SetBinLabel(i, ProtonTrackLabels[i - 1])

    TH1F *MostlyGoodProtonTrackCheck = new TH1F("MostlyGoodProtonTrackCheck","Particles IDed as Mostly Good Protons; One; Tracks", 2, 0, 2);
    MostlyGoodProtonTrackCheck->Sumw2();

    TH1F *GoodProtonTrackCheck = new TH1F("GoodProtonTrackCheck","Particles IDed as Good Protons; One; Tracks", 2, 0, 2);
    GoodProtonTrackCheck->Sumw2();

    TH1F *KaonPlusTrackCheck = new TH1F("KaonPlusTrackCheck","Particles IDed as Kaons Plus; One; Tracks", 2, 0, 2);
    KaonPlusTrackCheck->Sumw2();
    
//     for i in range(1, KaonPlusTrackCheck.GetNbinsX() + 1):
//         KaonPlusTrackCheck.GetXaxis().SetBinLabel(i, KaonPlusTrackLabels[i - 1])

    TH1F *MostlyGoodKaonPlusTrackCheck = new TH1F("MostlyGoodKaonPlusTrackCheck","Particles IDed as Mostly Good Kaons Plus; One; Tracks", 2, 0, 2);
    MostlyGoodKaonPlusTrackCheck->Sumw2();

    TH1F *GoodKaonPlusTrackCheck = new TH1F("GoodKaonPlusTrackCheck","Particles IDed as Good Kaons Plus; One; Tracks", 2, 0, 2);
    GoodKaonPlusTrackCheck->Sumw2();
    
    TH1F *KaonMinusTrackCheck = new TH1F("KaonMinusTrackCheck","Particles IDed as Kaons Minus; One; Tracks", 2, 0, 2);
    KaonMinusTrackCheck->Sumw2();
    
//     for i in range(1, KaonMinusTrackCheck.GetNbinsX() + 1):
//         KaonMinusTrackCheck.GetXaxis().SetBinLabel(i, KaonMinusTrackLabels[i - 1])

    TH1F *MostlyGoodKaonMinusTrackCheck = new TH1F("MostlyGoodKaonMinusTrackCheck","Particles IDed as Mostly Good Kaons Minus; One; Tracks", 2, 0, 2);
    MostlyGoodKaonMinusTrackCheck->Sumw2();
    
    TH1F *GoodKaonMinusTrackCheck = new TH1F("GoodKaonMinusTrackCheck","Particles IDed as Good Kaons Minus; One; Tracks", 2, 0, 2);
    GoodKaonMinusTrackCheck->Sumw2();
    
    TH1F *PionPlusTrackCheck = new TH1F("PionPlusTrackCheck","Particles IDed as Pions Plus; One; Tracks", 2, 0, 2);
    PionPlusTrackCheck->Sumw2();
    
//     for i in range(1, PionPlusTrackCheck.GetNbinsX() + 1):
//         PionPlusTrackCheck.GetXaxis().SetBinLabel(i, PionPlusTrackLabels[i - 1])

    TH1F *MostlyGoodPionPlusTrackCheck = new TH1F("MostlyGoodPionPlusTrackCheck","Particles IDed as Mostly Good Pions Plus; One; Tracks", 2, 0, 2);
    MostlyGoodPionPlusTrackCheck->Sumw2();

    TH1F *GoodPionPlusTrackCheck = new TH1F("GoodPionPlusTrackCheck","Particles IDed as Good Pions Plus; One; Tracks", 2, 0, 2);
    GoodPionPlusTrackCheck->Sumw2();
    
    TH1F *PionMinusTrackCheck = new TH1F("PionMinusTrackCheck","Particles IDed as Pions Minus; One; Tracks", 2, 0, 2);
    PionMinusTrackCheck->Sumw2();
    
//     for i in range(1, PionMinusTrackCheck.GetNbinsX() + 1):
//         PionMinusTrackCheck.GetXaxis().SetBinLabel(i, PionMinusTrackLabels[i - 1])

    TH1F *MostlyGoodPionMinusTrackCheck = new TH1F("MostlyGoodPionMinusTrackCheck","Particles IDed as Mostly Good Pions Minus; One; Tracks", 2, 0, 2);
    MostlyGoodPionMinusTrackCheck->Sumw2();

    TH1F *GoodPionMinusTrackCheck = new TH1F("GoodPionMinusTrackCheck","Particles IDed as Good Pions Minus; One; Tracks", 2, 0, 2);
    GoodPionMinusTrackCheck->Sumw2();
    
    TH1F *DeuteronTrackCheck = new TH1F("DeuteronTrackCheck","Particles IDed as Deuterons; One; Tracks", 2, 0, 2);
    DeuteronTrackCheck->Sumw2();
    
//     for i in range(1, DeuteronTrackCheck.GetNbinsX() + 1):
//         DeuteronTrackCheck.GetXaxis().SetBinLabel(i, DeuteronTrackLabels[i - 1])

    TH1F *MostlyGoodDeuteronTrackCheck = new TH1F("MostlyGoodDeuteronTrackCheck","Particles IDed as Mostly Good Deuterons; One; Tracks", 2, 0, 2);
    MostlyGoodDeuteronTrackCheck->Sumw2();

    TH1F *GoodDeuteronTrackCheck = new TH1F("GoodDeuteronTrackCheck","Particles IDed as Good Deuterons; One; Tracks", 2, 0, 2);
    GoodDeuteronTrackCheck->Sumw2();
    
    TH1F *TritonTrackCheck = new TH1F("TritonTrackCheck","Particles IDed as Tritons; One; Tracks", 2, 0, 2);
    TritonTrackCheck->Sumw2();
    
//     for i in range(1, TritonTrackCheck.GetNbinsX() + 1):
//         TritonTrackCheck.GetXaxis().SetBinLabel(i, TritonTrackLabels[i - 1])

    TH1F *MostlyGoodTritonTrackCheck = new TH1F("MostlyGoodTritonTrackCheck","Particles IDed as Mostly Good Tritons; One; Tracks", 2, 0, 2);
    MostlyGoodTritonTrackCheck->Sumw2();

    TH1F *GoodTritonTrackCheck = new TH1F("GoodTritonTrackCheck","Particles IDed as Good Tritons; One; Tracks", 2, 0, 2);
    GoodTritonTrackCheck->Sumw2();

    
    
    
    
    
    TH1F *HistoDC = new TH1F("Cos(3(Phi-Psi_1)) for Protons at 35-40% Centrality, No Weighting or Resolution Correction", "Cos(3(Phi-Psi_1)) for Protons, No Weighting or Resolution Correction; Cos(3(Phi-Psi_1)); Protons", 350, -7.0, 7.0);
    HistoDC->Sumw2();
    
    TH1F *HistoDD = new TH1F("Cos(3(Phi-Psi_1)) for Protons at 35-40% Centrality, Resolution Corrected but no Weighting", "Cos(3(Phi-Psi_1)) for Protons, Resolution Corrected but no Weighting; Cos(3(Phi-Psi_1))/R_31; Protons", 350, -7.0, 7.0);
    HistoDD->Sumw2();
    
    TH1F *HistoDE = new TH1F("Cos(3(Phi-Psi_1)) for Protons at 35-40% Centrality, Weighted and Resolution Corrected", "Cos(3(Phi-Psi_1)) for Protons, Weighted and Resolution Corrected; Cos(3(Phi-Psi_1))/R_31 and Weighted; Protons", 350, -7.0, 7.0);
    HistoDE->Sumw2();
    
    
    
    TH1F *TrackMultiplicity = new TH1F("TrackMultiplicity", "Track Multiplicity; Multiplicity; Frequency", 195, 0, 195);
    TrackMultiplicity->Sumw2();

    
    
    
    

    
    TProfile *HistoD54 = (TProfile*)ResolutionFile->Get("DataResolution");
    
    const char* CentralityXLabels[12] = {"0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60"};
    const char* CentralityXLabelsKaon[6] = {"0-10", "10-20", "20-30", "30-40", "40-50", "50-60"};
    
    std::string D44CString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for Protons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D44CChar = &D44CString[0];
    
    TProfile *HistoD44C= new TProfile("DataVnVsYPsi1ResolutionCorrectedProton", D44CChar, 75, -0.3, 0.95);
    HistoD44C->Sumw2();
    
    std::string D47BString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for K+, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D47BChar = &D47BString[0];

    TProfile *HistoD47B = new TProfile("DataVnVsYPsi1ResolutionCorrectedKaonPlus", D47BChar, 75, -0.3, 0.95);
    HistoD47B->Sumw2();
    
    std::string D47CString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for K-, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D47CChar = &D47CString[0];

    TProfile *HistoD47C = new TProfile("DataVnVsYPsi1ResolutionCorrectedKaonMinus", D47CChar, 75, -0.3, 0.95);
    HistoD47C->Sumw2();
    
    std::string D50BString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for Pi+, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D50BChar = &D50BString[0];

    TProfile *HistoD50B = new TProfile("DataVnVsYPsi1ResolutionCorrectedPionPlus", D50BChar, 75, -0.3, 0.95);
    HistoD50B->Sumw2();
    
    std::string D50CString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for Pi-, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D50CChar = &D50CString[0];

    TProfile *HistoD50C = new TProfile("DataVnVsYPsi1ResolutionCorrectedPionMinus", D50CChar, 75, -0.3, 0.95);
    HistoD50C->Sumw2();
    
    std::string D50DString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for Deuterons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D50DChar = &D50DString[0];
    
    TProfile *HistoD50D = new TProfile("DataVnVsYPsi1ResolutionCorrectedDeuteron", D50DChar, 75, -0.3, 0.95);
    HistoD50D->Sumw2();
    
    std::string D50EString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for Tritons, Calculated using Inner EPD (Data); y_{CM}; V" + std::to_string(nV) +"";
    const char *D50EChar = &D50EString[0];

    TProfile *HistoD50E = new TProfile("DataVnVsYPsi1ResolutionCorrectedTriton", D50EChar, 75, -0.3, 0.95);
    HistoD50E->Sumw2();
    
    std::string D54AString = "V" + std::to_string(nV) + " vs Centrality for Protons (Data); Centrality; V" + std::to_string(nV) +"";
    const char *D54AChar = &D54AString[0];

    TProfile *HistoD54A = new TProfile("DataVnVsCentralityProtonCorrected", D54AChar, 12, 0, 12);
    HistoD54A->Sumw2();
    
    for (int i = 1; i < HistoD54A->GetNbinsX() + 1; i++)
    {
        HistoD54A->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }

    std::string D54BString = "V" + std::to_string(nV) + " vs Centrality for Kaon+ (Data); Centrality; V" + std::to_string(nV) +"";
    const char *D54BChar = &D54BString[0];
    
    TProfile *HistoD54B = new TProfile("DataVnVsCentralityKaonPlusCorrected", D54BChar, 6, 0, 6);
    HistoD54B->Sumw2();
    
    for (int i = 1; i < HistoD54B->GetNbinsX() + 1; i++)
    {
        HistoD54B->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }
    
    std::string D54CString = "V" + std::to_string(nV) + " vs Centrality for Kaon- (Data); Centrality; V" + std::to_string(nV) +"";
    const char *D54CChar = &D54CString[0];

    TProfile *HistoD54C = new TProfile("DataVnVsCentralityKaonMinusCorrected", D54CChar, 6, 0, 6);
    HistoD54C->Sumw2();
    
    for (int i = 1; i < HistoD54C->GetNbinsX() + 1; i++)
    {
        HistoD54C->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }
    
    std::string D54DString = "V" + std::to_string(nV) + " vs Centrality for Pion+ (Data); Centrality; V" + std::to_string(nV) +"";
    const char *D54DChar = &D54DString[0];

    TProfile *HistoD54D = new TProfile("DataVnVsCentralityPionPlusCorrected", D54DChar, 12, 0, 12);
    HistoD54D->Sumw2();
    
    for (int i = 1; i < HistoD54D->GetNbinsX() + 1; i++)
    {
        HistoD54D->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }

    std::string D54EString = "V" + std::to_string(nV) + " vs Centrality for Pion- (Data); Centrality; V" + std::to_string(nV) +"";
    const char *D54EChar = &D54EString[0];    
    
    TProfile *HistoD54E = new TProfile("DataVnVsCentralityPionMinusCorrected", D54EChar, 12, 0, 12);
    HistoD54E->Sumw2();

    for (int i = 1; i < HistoD54E->GetNbinsX() + 1; i++)
    {
        HistoD54E->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }
    
    std::string D54FString = "V" + std::to_string(nV) + " vs Centrality for Deuterons (Data); Centrality; V" + std::to_string(nV) +"";
    const char *D54FChar = &D54FString[0];
    
    TProfile *HistoD54F = new TProfile("DataVnVsCentralityDeuteronCorrected", D54FChar, 12, 0, 12);
    HistoD54F->Sumw2();
    
    for (int i = 1; i < HistoD54F->GetNbinsX() + 1; i++)
    {
        HistoD54F->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }
    
    std::string D54GString = "V" + std::to_string(nV) + " vs Centrality for Tritons (Data); Centrality; V" + std::to_string(nV) +"";
    const char *D54GChar = &D54GString[0];

    TProfile *HistoD54G = new TProfile("DataVnVsCentralityTritonCorrected", D54GChar, 12, 0, 12);
    HistoD54G->Sumw2();

    for (int i = 1; i < HistoD54G->GetNbinsX() + 1; i++)
    {
        HistoD54G->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }
    
    std::string D79String = "V" + std::to_string(nV) + " (Resolution Corrected) vs Pt for Protons for Different Centralities (Data); Centrality; Pt";
    const char *D79Char = &D79String[0];
    
    TProfile2D *HistoD79 = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesProton", D79Char, 12, 0, 12, 20, 0, 2);
    HistoD79->Sumw2();
    
    std::string D80String = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for Protons for Different Centralities (Data); Centrality; y_{CM}";
    const char *D80Char = &D80String[0];

    TProfile2D *HistoD80 = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesProton", D80Char, 12, 0, 12, 10, 0, 1);
    HistoD80->Sumw2();
    
    std::string D81String = "V" + std::to_string(nV) + " (Resolution Corrected) vs Pt for K+ for Different Centralities (Data); Centrality; Pt";
    const char *D81Char = &D81String[0];

    TProfile2D *HistoD81 = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesKaonPlus", D81Char, 12, 0, 12, 20, 0, 2);
    HistoD81->Sumw2();
    
    std::string D82String = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for K+ for Different Centralities (Data); Centrality; y_{CM}";
    const char *D82Char = &D82String[0];

    TProfile2D *HistoD82 = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesKaonPlus", D82Char, 12, 0, 12, 10, 0, 1);
    HistoD82->Sumw2();
    
    std::string D83String = "V" + std::to_string(nV) + " (Resolution Corrected) vs Pt for K- for Different Centralities (Data); Centrality; Pt";
    const char *D83Char = &D83String[0];

    TProfile2D *HistoD83 = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesKaonMinus", D83Char, 12, 0, 12, 20, 0, 2);
    HistoD83->Sumw2();
    
    std::string D84String = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for K- for Different Centralities (Data); Centrality; y_{CM}";
    const char *D84Char = &D84String[0];

    TProfile2D *HistoD84 = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesKaonMinus", D84Char, 12, 0, 12, 10, 0, 1);
    HistoD84->Sumw2();
    
    std::string D85String = "V" + std::to_string(nV) + " (Resolution Corrected) vs Pt for Pi+ for Different Centralities (Data); Centrality; Pt";
    const char *D85Char = &D85String[0];

    TProfile2D *HistoD85 = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesPionPlus", D85Char, 12, 0, 12, 20, 0, 2);
    HistoD85->Sumw2();
    
    std::string D86String = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for Pi+ for Different Centralities (Data); Centrality; y_{CM}";
    const char *D86Char = &D86String[0];

    TProfile2D *HistoD86 = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesPionPlus", D86Char, 12, 0, 12, 10, 0, 1);
    HistoD86->Sumw2();
    
    std::string D87String = "V" + std::to_string(nV) + " (Resolution Corrected) vs Pt for Pi- for Different Centralities (Data); Centrality; Pt";
    const char *D87Char = &D87String[0];

    TProfile2D *HistoD87 = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesPionMinus", D87Char, 12, 0, 12, 20, 0, 2);
    HistoD87->Sumw2();
    
    std::string D88String = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for Pi- for Different Centralities (Data); Centrality; y_{CM}";
    const char *D88Char = &D88String[0];

    TProfile2D *HistoD88 = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesPionMinus", D88Char, 12, 0, 12, 10, 0, 1);
    HistoD88->Sumw2();

    std::string D88AString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Pt for Deuterons for Different Centralities (Data); Centrality; Pt";
    const char *D88AChar = &D88AString[0];

    TProfile2D *HistoD88A = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesDeuterons", D88AChar, 12, 0, 12, 20, 0, 2);
    HistoD88A->Sumw2();
    
    std::string D88BString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for Deuterons for Different Centralities (Data); Centrality; y_{CM}";
    const char *D88BChar = &D88BString[0];

    TProfile2D *HistoD88B = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesDeuterons", D88BChar, 12, 0, 12, 10, 0, 1);
    HistoD88B->Sumw2();
    
    std::string D88CString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Pt for Tritons for Different Centralities (Data); Centrality; Pt";
    const char *D88CChar = &D88CString[0];
    
    TProfile2D *HistoD88C = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesTritons", D88CChar, 12, 0, 12, 20, 0, 2);
    HistoD88C->Sumw2();
    
    std::string D88DString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for Tritons for Different Centralities (Data); Centrality; y_{CM}";
    const char *D88DChar = &D88DString[0];

    TProfile2D *HistoD88D = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesTritons", D88DChar, 12, 0, 12, 10, 0, 1);
    HistoD88D->Sumw2();






    // Event Loop
    for (int EventNum = 0; EventNum < AutreeData->GetEntries(); EventNum++)
    {
        if (RunIteration == 1)
        {
            if (EventNum % 5000 == 0)
            {
                std::cout << "Data First Pass (Raw Values and Kinematics) " << EventNum << std::endl;
            }
        }

        AutreeData->GetEntry(EventNum);


        int TotalTracks = tracknumber;
        double vx = Vx;
        double vy = Vy;
        double vz = Vz;
        int Centrality = centrality;

        double vr = sqrt(pow(vx, 2) + pow(vy + 2, 2));

        if (vz <= ZVertexLowerBound || vz >= ZVertexUpperBound)
        {
            continue;
        }

        //EventCheck->Fill(3);

        if (vr >= RVertexBound)
        {
            continue;
        }

        //EventCheck->Fill(4);

        int Multiplicity = TotalTracks;

        double ProtonMass = 0.938272;
        double KaonMass = 0.493677;
        double PionMass = 0.139571;
        double DeuteronMass = 1.875613;
        double TritonMass = 2.808921;

        double InnerEPDQx = 0;
        double InnerEPDQy = 0;
        double OuterEPDQx = 0;
        double OuterEPDQy = 0;
        double InnerTPCQx = 0;
        double InnerTPCQy = 0;
        double OuterTPCQx = 0;
        double OuterTPCQy = 0;

        if(RunIteration == 1)
        {
            //Kinematics Track Loop
            for (int TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
            {               
                float px = Px[TrackNum];
                float py = Py[TrackNum];
                float pz = Pz[TrackNum];
                int q = Charge[TrackNum];
                float tofBeta = ToFBeta[TrackNum];
                float dEdx = dedx[TrackNum];
                float NSigmaPr = nSigmaPr[TrackNum];
                float NSigmaKa = nSigmaKa[TrackNum];
                float NSigmaPi = nSigmaPi[TrackNum];
                float DCA = dca[TrackNum];
                int NHits = nHits[TrackNum];
                int NHitsdEdx = nHitsdEdx[TrackNum];
                int NHitsFit = nHitsFit[TrackNum];
                int NHitsPoss = nHitsPoss[TrackNum]; 

                if (DCA > DCABound)
                {
                    continue;
                }
                if (NHits < NHitsBound)
                {
                    continue;
                }
                if (NHitsdEdx < NHitsdEdxBound)
                {
                    continue;
                }
                if (NHitsFit / NHitsPoss < NHitsFitOverNHitsPossBound)
                {
                    continue;
                }

                if(q == 0)
                {
                    continue;
                }


                double pt = FlowFunctions::Pt(px, py);

                double p = FlowFunctions::P(px, py, pz);

                double eta = FlowFunctions::Eta(px, py, pz);

                double qp = FlowFunctions::QP(q, px, py, pz);

                double phi = FlowFunctions::Phi(px, py);



                //Particle Identification
                bool IsKaon = false;
                bool IsPion = false;
                bool IsDeuteron = false;
                bool IsTriton = false;
                bool IsProtonTPC = (abs(NSigmaPr) < NSigmaPrBound) and (q == 1);


                if(tofBeta > 0)
                {
                    double msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

                    bool IsKaon = (abs(NSigmaKa) < NSigmaKaBound) and (msquared > KaonLowerMSquared) and (msquared < KaonUpperMSquared);
                    bool IsPion = (abs(NSigmaPi) < NSigmaPiBound) and (msquared > PionLowerMSquared) and (msquared < PionUpperMSquared);
                }

                Double_t zDeuteron = TMath::Log(dEdx / BichselZDeuteron->Eval(p));
                Double_t zTriton = TMath::Log(dEdx / BichselZTriton->Eval(p));
                
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


                //Kinematics Plots
                if(tofBeta > 0)
                {

                    double msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

    //                bool IsProtonToF = (abs(NSigmaPr) < NSigmaPrBound) && (msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared) && (p > 2.0));

                    HistoD4->Fill(qp, msquared);
                    HistoD4A->Fill(qp, msquared);

                    HistoD24->Fill(qp, NSigmaPr);
                    HistoD25->Fill(qp, NSigmaKa);
                    HistoD26->Fill(qp, NSigmaPi);

                    // Proton criteria
    //              if(IsProtonToF)
                    {
    //                     double mass = ProtonMass;

    //                     double y = FlowFunctions::Y(px, py, pz, mass);

    //                     HistoD5->Fill(y - yCMShift);
    //                     HistoD8->Fill(pt);
    //                     HistoD15->Fill(p, dEdx);
    //                     HistoD18->Fill(qp, msquared);

    //                     HistoD21->Fill(pt);

    //                     HistoD27->Fill(y - yCMShift, pt);
                    }

                    // Kaon criteria
                    if(IsKaon)
                    {
                        double mass = KaonMass;

                        double y = FlowFunctions::Y(px, py, pz, mass);

                        HistoD22->Fill(pt);

                        HistoD6->Fill(y - yCMShift);
                        HistoD9->Fill(pt);
                        HistoD14->Fill(p, dEdx);
                        HistoD19->Fill(qp, msquared);

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
                        double mass = PionMass;

                        double y = FlowFunctions::Y(px, py, pz, mass);

                        HistoD23->Fill(pt);

                        HistoD7->Fill(y - yCMShift);
                        HistoD10->Fill(pt);
                        HistoD13->Fill(p, dEdx);
                        HistoD20->Fill(qp, msquared);

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
                    double mass = DeuteronMass;

                    double y = FlowFunctions::Y(px, py, pz, mass);

                    HistoD16->Fill(p, dEdx);
                    HistoD27A->Fill(y - yCMShift, pt);
                }

                if(IsTriton)
                {
                    double mass = TritonMass;

                    double y = FlowFunctions::Y(px, py, pz, mass);

                    HistoD17->Fill(p, dEdx);
                    HistoD27B->Fill(y - yCMShift, pt);
                }

                if(IsProtonTPC)
                {
                        double mass = ProtonMass;

                        double y = FlowFunctions::Y(px, py, pz, mass);

                        HistoD5->Fill(y - yCMShift);
                        HistoD8->Fill(pt);
                        HistoD15->Fill(p, dEdx);

                        HistoD21->Fill(pt);

                        HistoD27->Fill(y - yCMShift, pt);
                }

                HistoD1->Fill(pt);
                HistoD2->Fill(eta);
                HistoD3->Fill(eta, pt);
                HistoD11->Fill(Multiplicity);
                HistoD12->Fill(p, dEdx);
                HistoD32->Fill(phi);
            }
        }//End of Kinematics Track Loop
        
        double InnerEPDQxMean = 0;
        double InnerEPDQyMean = 0;
        double OuterEPDQxMean = 0;
        double OuterEPDQyMean = 0;
        double OuterTPCQxMean = 0;
        double OuterTPCQyMean = 0;  
            
        if(RunIteration >= 2)
        {
            TH1D *InnerEPDQxMeanHisto = (TH1D*)QVectorHistogramFileFirst->Get("InnerEPDQxRaw");
            TH1D *InnerEPDQyMeanHisto = (TH1D*)QVectorHistogramFileFirst->Get("InnerEPDQyRaw");
            TH1D *OuterEPDQxMeanHisto = (TH1D*)QVectorHistogramFileFirst->Get("OuterEPDQxRaw");
            TH1D *OuterEPDQyMeanHisto = (TH1D*)QVectorHistogramFileFirst->Get("OuterEPDQyRaw");
            TH1D *OuterTPCQxMeanHisto = (TH1D*)QVectorHistogramFileFirst->Get("OuterTPCQxRaw");
            TH1D *OuterTPCQyMeanHisto = (TH1D*)QVectorHistogramFileFirst->Get("OuterTPCQyRaw");

            InnerEPDQxMean = InnerEPDQxMeanHisto->GetMean();
            InnerEPDQyMean = InnerEPDQyMeanHisto->GetMean();
            OuterEPDQxMean = OuterEPDQxMeanHisto->GetMean();
            OuterEPDQyMean = OuterEPDQyMeanHisto->GetMean();
            OuterTPCQxMean = OuterTPCQxMeanHisto->GetMean();
            OuterTPCQyMean = OuterTPCQyMeanHisto->GetMean();
        }
        
        double FourierCorrectionTermInnerEPD = 0;
        double FourierCorrectionTermOuterEPD = 0;
        double FourierCorrectionTermOuterTPC = 0;

        int GoodTracksCounterInnerEPD = 0;
        int GoodTracksCounterOuterEPD = 0;
        int GoodTracksCounterOuterTPC = 0;

        //TPC Track Counting loop
        for (int TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
        {
                float px = Px[TrackNum];
                float py = Py[TrackNum];
                float pz = Pz[TrackNum];
                int q = Charge[TrackNum];
                float tofBeta = ToFBeta[TrackNum];
                float dEdx = dedx[TrackNum];
                float NSigmaPr = nSigmaPr[TrackNum];
                float NSigmaKa = nSigmaKa[TrackNum];
                float NSigmaPi = nSigmaPi[TrackNum];
                float DCA = dca[TrackNum];
                int NHits = nHits[TrackNum];
                int NHitsdEdx = nHitsdEdx[TrackNum];
                int NHitsFit = nHitsFit[TrackNum];
                int NHitsPoss = nHitsPoss[TrackNum]; 


                if (DCA > DCABound)
                {
                    continue;
                }
                if (NHits < NHitsBound)
                {
                    continue;
                }
                if (NHitsdEdx < NHitsdEdxBound)
                {
                    continue;
                }
                if (NHitsFit / NHitsPoss < NHitsFitOverNHitsPossBound)
                {
                    continue;
                }

                if(q == 0)
                {
                    continue;
                }

                double eta = FlowFunctions::Eta(px, py, pz);

                if ((eta > OuterTPCLowerLimit) && (eta < OuterTPCUpperLimit))
                {
                    GoodTracksCounterOuterTPC += 1;
                }
        }//End TPC Track Counting loop

        int nEPDHits = nEPDhits;

        //EPD Hit Counting loop
        for (int index = 0; index < nEPDHits; index++)
        {
            int EPDID = EPDid[index];

            if(EPDID > 0)
            {
                continue;
            }

            TileVector *TVec = new TileVector(EPDID, vx, vy, vz, InnerEPDHighRing, OuterEPDLowRing);

            double eta = TVec->EPDEta();

            int RingNumber = TVec->EPDRow();

            HistoD32B->Fill(eta, RingNumber);

            if (TVec->IsInnerEPD() && !(TVec->IsOuterEPD()))
            {
                GoodTracksCounterInnerEPD += 1;
            }

            if (TVec->IsOuterEPD() and not(TVec->IsInnerEPD()))
            {
                GoodTracksCounterOuterEPD += 1;
            }

            delete TVec;
        }//End EPD Hit Counting loop

        if((GoodTracksCounterInnerEPD < NumberOfGoodTracksInnerEPD) || (GoodTracksCounterOuterEPD < NumberOfGoodTracksOuterEPD) || (GoodTracksCounterOuterTPC < NumberOfGoodTracksOuterTPC))
        {
            continue;
        }

        //Q Vector Calulator loop (TPC)
        for (int TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
        {
                float px = Px[TrackNum];
                float py = Py[TrackNum];
                float pz = Pz[TrackNum];
                int q = Charge[TrackNum];
                float tofBeta = ToFBeta[TrackNum];
                float dEdx = dedx[TrackNum];
                float NSigmaPr = nSigmaPr[TrackNum];
                float NSigmaKa = nSigmaKa[TrackNum];
                float NSigmaPi = nSigmaPi[TrackNum];
                float DCA = dca[TrackNum];
                int NHits = nHits[TrackNum];
                int NHitsdEdx = nHitsdEdx[TrackNum];
                int NHitsFit = nHitsFit[TrackNum];
                int NHitsPoss = nHitsPoss[TrackNum]; 


                if (DCA > DCABound)
                {
                    continue;
                }
                if (NHits < NHitsBound)
                {
                    continue;
                }
                if (NHitsdEdx < NHitsdEdxBound)
                {
                    continue;
                }
                if (NHitsFit / NHitsPoss < NHitsFitOverNHitsPossBound)
                {
                    continue;
                }

                if(q == 0)
                {
                    continue;
                }

                double pt = FlowFunctions::Pt(px, py);

                double eta = FlowFunctions::Eta(px, py, pz);

                double phi = FlowFunctions::Phi(px, py);

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
            int EPDID = EPDid[index];
            double EPDnMIP = EPDnMip[index];

            if(EPDID > 0)
            {
                continue;
            }

            TileVector *TVec = new TileVector(EPDID, vx, vy, vz, InnerEPDHighRing, OuterEPDLowRing);

            double phi = TVec->EPDPhi();

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
            continue;
        }
            
        if((OuterEPDQx == 0) && (OuterEPDQy == 0))
        {
            continue;
        }
            
//         if((InnerTPCQx == 0) && (InnerTPCQy == 0))
//         {
//             continue;
//         }
            
        if((OuterTPCQx == 0) && (OuterTPCQy == 0))
        {
            continue;
        }
        
        double PsiInnerEPDRaw = 0;
        double PsiOuterEPDRaw = 0;
        double PsiOuterTPCRaw = 0;
        
        double PsiInnerEPDRecentered = 0;
        double PsiOuterEPDRecentered = 0;
        double PsiOuterTPCRecentered = 0;
        
        if(RunIteration == 1)
        {
            HistoInnerEPDQxRaw->Fill(InnerEPDQx);
            HistoInnerEPDQyRaw->Fill(InnerEPDQy);
            HistoOuterEPDQxRaw->Fill(OuterEPDQx);
            HistoOuterEPDQyRaw->Fill(OuterEPDQy);  
            HistoOuterTPCQxRaw->Fill(OuterTPCQx);
            HistoOuterTPCQyRaw->Fill(OuterTPCQy);

            PsiInnerEPDRaw = (1/nPsi)*atan2(InnerEPDQy, InnerEPDQx);
            PsiOuterEPDRaw = (1/nPsi)*atan2(OuterEPDQy, OuterEPDQx);
            PsiOuterTPCRaw = (1/nPsi)*atan2(OuterTPCQy, OuterTPCQx);

            HistoD33->Fill(PsiInnerEPDRaw);
            HistoD36->Fill(PsiOuterEPDRaw);
            HistoD39->Fill(PsiOuterTPCRaw);
        }
        
        if(RunIteration == 2)
        {
            HistoInnerEPDQxRecentered->Fill(InnerEPDQx - InnerEPDQxMean);
            HistoInnerEPDQyRecentered->Fill(InnerEPDQy - InnerEPDQyMean);
            
            HistoOuterEPDQxRecentered->Fill(OuterEPDQx - OuterEPDQxMean);
            HistoOuterEPDQyRecentered->Fill(OuterEPDQy - OuterEPDQyMean);
            
            HistoOuterTPCQxRecentered->Fill(OuterTPCQx - OuterTPCQxMean);
            HistoOuterTPCQyRecentered->Fill(OuterTPCQy - OuterTPCQyMean);
        }
        
        if(RunIteration >= 2)
        {
            PsiInnerEPDRecentered = (1/nPsi)*atan2(InnerEPDQy - InnerEPDQyMean, InnerEPDQx - InnerEPDQxMean)
            PsiOuterEPDRecentered = (1/nPsi)*atan2(OuterEPDQy - OuterEPDQyMean, OuterEPDQx - OuterEPDQxMean)
            PsiOuterTPCRecentered = (1/nPsi)*atan2(OuterTPCQy - OuterTPCQyMean, OuterTPCQx - OuterTPCQxMean)
        }
        
        if(RunIteration == 2)
        {
            HistoD34->Fill(PsiInnerEPDRecentered);
            HistoD37->Fill(PsiOuterEPDRecentered);
            HistoD40->Fill(PsiOuterTPCRecentered);

            for (j = 1; j < FourierCorrectionTerms + 1; j++)
            {
                HistoInnerEPDSineAverages->Fill(j, -1*sin(j*nPsi*PsiInnerEPDRecentered));
                HistoInnerEPDCosineAverages->Fill(j, cos(j*nPsi*PsiInnerEPDRecentered));
                HistoOuterEPDSineAverages->Fill(j, -1*sin(j*nPsi*PsiOuterEPDRecentered));
                HistoOuterEPDCosineAverages->Fill(j, cos(j*nPsi*PsiOuterEPDRecentered));
                HistoOuterTPCSineAverages->Fill(j, -1*sin(j*nPsi*PsiOuterTPCRecentered));
                HistoOuterTPCCosineAverages->Fill(j, cos(j*nPsi*PsiOuterTPCRecentered));
            }
        }
        
        if(RunIteration >= 3)
        {
            for (int j = 0; j < FourierCorrectionTerms + 1; j++)
            {
                double InnerEPDSineAverageJth = QVectorHistogramFileSecond->Get("InnerEPDSineAverages")->GetBinContent(j);
                double InnerEPDCosineAverageJth = QVectorHistogramFileSecond->Get("InnerEPDCosineAverages")->GetBinContent(j);
                double OuterEPDSineAverageJth = QVectorHistogramFileSecond->Get("OuterEPDSineAverages")->GetBinContent(j);
                double OuterEPDCosineAverageJth = QVectorHistogramFileSecond->Get("OuterEPDCosineAverages")->GetBinContent(j);
                double OuterTPCSineAverageJth = QVectorHistogramFileSecond->Get("OuterTPCSineAverages")->GetBinContent(j);
                double OuterTPCCosineAverageJth = QVectorHistogramFileSecond->Get("OuterTPCCosineAverages")->GetBinContent(j);

                FourierCorrectionTermInnerEPD += (2/(j*nPsi))*(InnerEPDSineAverageJth*cos(j*nPsi*PsiInnerEPDRecentered) + InnerEPDCosineAverageJth*sin(j*nPsi*PsiInnerEPDRecentered));
                FourierCorrectionTermOuterEPD += (2/(j*nPsi))*(OuterEPDSineAverageJth*cos(j*nPsi*PsiOuterEPDRecentered) + OuterEPDCosineAverageJth*sin(j*nPsi*PsiOuterEPDRecentered));
                FourierCorrectionTermOuterTPC += (2/(j*nPsi))*(OuterTPCSineAverageJth*cos(j*nPsi*PsiOuterTPCRecentered) + OuterTPCCosineAverageJth*sin(j*nPsi*PsiOuterTPCRecentered));
            }
            
            double PsiInnerEPDFourierCorrected = PsiInnerEPDRecentered + FourierCorrectionTermInnerEPD;
            double PsiOuterEPDFourierCorrected = PsiOuterEPDRecentered + FourierCorrectionTermOuterEPD;
            double PsiOuterTPCFourierCorrected = PsiOuterTPCRecentered + FourierCorrectionTermOuterTPC;
        }
        
        if(RunIteration == 3)
        {   
            HistoD35->Fill(PsiInnerEPDFourierCorrected);
            HistoD38->Fill(PsiOuterEPDFourierCorrected);
            HistoD41->Fill(PsiOuterTPCFourierCorrected);
        }
        
        
        
        if(Centrality < 4)
        {
            continue;
        }
        
        
        
        
        //Flow Calulator loop
        for (int TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
        {
            float px = Px[TrackNum];
            float py = Py[TrackNum];
            float pz = Pz[TrackNum];
            int q = Charge[TrackNum];
            float tofBeta = ToFBeta[TrackNum];
            float dEdx = dedx[TrackNum];
            float NSigmaPr = nSigmaPr[TrackNum];
            float NSigmaKa = nSigmaKa[TrackNum];
            float NSigmaPi = nSigmaPi[TrackNum];
            float DCA = dca[TrackNum];
            int NHits = nHits[TrackNum];
            int NHitsdEdx = nHitsdEdx[TrackNum];
            int NHitsFit = nHitsFit[TrackNum];
            int NHitsPoss = nHitsPoss[TrackNum]; 


            if (DCA > DCABound)
            {
                continue;
            }
            if (NHits < NHitsBound)
            {
                continue;
            }
            if (NHitsdEdx < NHitsdEdxBound)
            {
                continue;
            }
            if (NHitsFit / NHitsPoss < NHitsFitOverNHitsPossBound)
            {
                continue;
            }

            if(q == 0)
            {
                continue;
            }
            
            
            double pt = FlowFunctions::Pt(px, py);

            double p = FlowFunctions::P(px, py, pz);

            double eta = FlowFunctions::Eta(px, py, pz);

            double phi = FlowFunctions::Phi(px, py);
            
            
            
            //Particle Identification
            bool IsKaon = false;
            bool IsPion = false;
            bool IsDeuteron = false;
            bool IsTriton = false;
            bool IsProtonTPC = (abs(NSigmaPr) < NSigmaPrBound) and (q == 1);


            if(tofBeta > 0)
            {
                double msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

                bool IsKaon = (abs(NSigmaKa) < NSigmaKaBound) and (msquared > KaonLowerMSquared) and (msquared < KaonUpperMSquared);
                bool IsPion = (abs(NSigmaPi) < NSigmaPiBound) and (msquared > PionLowerMSquared) and (msquared < PionUpperMSquared);
            }
            
            Double_t zDeuteron = TMath::Log(dEdx / BichselZDeuteron->Eval(p));
            Double_t zTriton = TMath::Log(dEdx / BichselZTriton->Eval(p));

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
            
            
            
            //First Pass (Raw values)
            if(RunIteration == 1)
            {
                if(tofBeta > 0)
                {
//                     bool IsProtonToF = (abs(NSigmaPr) < NSigmaPrBound) && (msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared) and (p > 2.0);

//                     if(IsProtonToF)
//                     {
//                         double mass = ProtonMass;

//                         double y = FlowFunctions::Y(px, py, pz, mass);

//                         double VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

//                         bool IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                         if(IsGoodProton)
//                         {
//                             HistoD42->Fill(y - yCMShift, VnInnerEPDRaw);
//                         }
//                     }

                    if(IsKaon)
                    {
                        double mass = KaonMass;

                        double y = FlowFunctions::Y(px, py, pz, mass);

                        double VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

                        bool IsGoodKaon = (pt > KaonLowerPt) && (pt < KaonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                        if(IsGoodKaon)
                        {
                            if(q > 0)
                            {
                                HistoD45->Fill(y - yCMShift, VnInnerEPDRaw);
                            }

                            if(q < 0)
                            {
                                HistoD45A->Fill(y - yCMShift, VnInnerEPDRaw);
                            }
                        }
                    }

                    else if(IsPion)
                    {
                        double mass = PionMass;

                        double y = FlowFunctions::Y(px, py, pz, mass);

                        double VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

                        bool IsGoodPion = (pt > PionLowerPt) && (pt < PionUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                        if(IsGoodPion)
                        {
                            if(q > 0)
                            {
                                HistoD48->Fill(y - yCMShift, VnInnerEPDRaw);
                            }

                            if(q < 0)
                            {
                                HistoD48A->Fill(y - yCMShift, VnInnerEPDRaw);
                            }
                        }
                     }
            
                    
                }
            }

                if(IsDeuteron)
                {
                    double mass = DeuteronMass;

                    double y = FlowFunctions::Y(px, py, pz, mass);

                    double VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

                    bool IsGoodDeuteron = (pt > DeuteronLowerPt) && (pt < DeuteronUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                    if(IsGoodDeuteron)
                    {
                        HistoD42A->Fill(y - yCMShift, VnInnerEPDRaw);
                    }
                }

                else if(IsTriton)
                {
                    double mass = TritonMass;

                    double y = FlowFunctions::Y(px, py, pz, mass);

                    double VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

                    bool IsGoodTriton = (pt > TritonLowerPt) && (pt < TritonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                    if(IsGoodTriton)
                    {
                        HistoD42B->Fill(y - yCMShift, VnInnerEPDRaw);
                    }
                }


                if(IsProtonTPC)
                {
                    double mass = ProtonMass;

                    double y = FlowFunctions::Y(px, py, pz, mass);

                    double VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

                    bool IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                    if(IsGoodProton)
                    {
                        HistoD42->Fill(y - yCMShift, VnInnerEPDRaw);
                    }
                }
            }//End Flow Calculator loop
        
        
        }//End Event loop

    


    //Outputting the Histograms
    if(RunIteration == 1)
    {
        HistoInnerEPDQxRaw->SetDirectory(0);
        HistoInnerEPDQyRaw->SetDirectory(0);
        HistoOuterEPDQxRaw->SetDirectory(0);
        HistoOuterEPDQyRaw->SetDirectory(0);
        HistoOuterTPCQxRaw->SetDirectory(0);
        HistoOuterTPCQyRaw->SetDirectory(0);
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
        HistoD33->SetDirectory(0);
        HistoD36->SetDirectory(0);
        HistoD39->SetDirectory(0);
        HistoD42->SetDirectory(0);
        HistoD42A->SetDirectory(0);
        HistoD42B->SetDirectory(0);
        HistoD45->SetDirectory(0);
        HistoD45A->SetDirectory(0);
        HistoD48->SetDirectory(0);
        HistoD48A->SetDirectory(0);
        
        
        std::string QVectorHistogramFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/QVectorFirstPass" + argv[3] + argv[2] +".root";
        const char *QVectorHistogramFileChar = &QVectorHistogramFileString[0];
        
        TFile *QVectorHistogramRootFile = TFile::Open(QVectorHistogramFileChar, "RECREATE");
        QVectorHistogramRootFile->cd();

        HistoInnerEPDQxRaw->Write();
        HistoInnerEPDQyRaw->Write();
        HistoOuterEPDQxRaw->Write();
        HistoOuterEPDQyRaw->Write();
        HistoOuterTPCQxRaw->Write();
        HistoOuterTPCQyRaw->Write();

        QVectorHistogramRootFile->Close();
        
        
        
        
        std::string HistogramRootFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramSecondPass" + argv[3] + argv[2] + ".root";
        const char *HistogramRootFileChar = &HistogramRootFileString[0];
        
        TFile *HistogramRootFile =TFile::Open(HistogramRootFileChar, "RECREATE");
        HistogramRootFile->cd();

        HistoDA->Write();
        HistoDB->Write();
        HistoD0->Write();
        HistoD1->Write();
        HistoD2->Write();
        HistoD3->Write();
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
        HistoD33->Write();
        HistoD36->Write();
        HistoD39->Write();
        HistoD42->Write();
        HistoD42A->Write();
        HistoD42B->Write();
        HistoD45->Write();
        HistoD45A->Write();
        HistoD48->Write();
        HistoD48A->Write();


        HistogramRootFile->Close();
    }

    Data->Close();

    delete BichselZDeuteron;
    delete BichselZTriton;
    
    delete HistoInnerEPDQxRaw;
    delete HistoInnerEPDQyRaw;
    delete HistoOuterEPDQxRaw;
    delete HistoOuterEPDQyRaw;
    delete HistoOuterTPCQxRaw;
    delete HistoOuterTPCQyRaw;
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
    delete HistoD33;
    delete HistoD36;
    delete HistoD39;
    delete HistoD42;
    delete HistoD42A;
    delete HistoD42B;
    delete HistoD45;
    delete HistoD45A;
    delete HistoD48;
    delete HistoD48A;

    std::cout << "DONE" << std::endl;
           
    return(0);
    
}//End main()
