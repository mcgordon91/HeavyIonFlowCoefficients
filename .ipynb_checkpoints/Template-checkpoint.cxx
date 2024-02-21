#include <iostream>
#include <string>
#include <vector>

#include "FlowFunctions.h"
#include "DeuteronsAndTritons.h"
#include "TileVector.h"


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
    
    TFile *Data = TFile::Open(argv[1]);

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Template(int argc, char *argv[])
{
if(RunIteration == 1)
{
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
    
        // Event Loop
    for (int EventNum = 0; EventNum < AutreeData->GetEntries(); EventNum++)
    {
        if (EventNum % 5000 == 0)
        {
            std::cout << "Data First Pass (Raw Values and Kinematics) " << EventNum << std::endl;
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

                DeuteronsAndTritons DAndT (p, dEdx, tofBeta);

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
        
        int GoodTracksCounterInnerEPD = 0
        int GoodTracksCounterOuterEPD = 0
        int GoodTracksCounterOuterTPC = 0
            
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
        
        int NEPDHits = nEPDhits;
        
        //EPD Hit Counting loop
        for (int index = 0; index < NEPDHits; index++)
        {
            if(EPDID[index] > 0)
            {
                continue;
            }

            TileVector *TVec (EPDID[index], vx, vy, vz, InnerEPDHighRing, OuterEPDLowRing);

            double eta = TVec.EPDEta();

            int RingNumber = TVec.EPDRow();

            HistoD32B.Fill(eta, RingNumber)

            if (TVec.IsInnerEPD() && !(TileVector.IsOuterEPD()))
            {
                GoodTracksCounterInnerEPD += 1;
            }

            if (TVec.IsOuterEPD() and not(TVec.IsInnerEPD()))
            {
                GoodTracksCounterOuterEPD += 1;
            }
        }//EPD Hit Counting loop
        
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
            
                double pt = Pt(px, py);

                double eta = Eta(px, py, pz);

                double phi = Phi(px, py);

                if ((eta > InnerTPCLowerLimit) && (eta < InnerTPCUpperLimit))
                {
                    if(nV % 2 == 0)
                    {
                        InnerTPCQy += pt*sin(nPsi*phi);
                        InnerTPCQx += pt*cos(nPsi*phi);
                    }

                    elif(nV % 2 == 1)
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
    }
    
    
}
}