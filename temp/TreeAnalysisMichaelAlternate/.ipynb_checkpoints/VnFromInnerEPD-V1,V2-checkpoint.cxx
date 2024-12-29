//Author: Michael Gordon
//Date: 2-20-24



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
#include "TProfile3D.h"
#include "TString.h"
#include "TKey.h"
#include "TF1.h"
#include "TMath.h"
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
    
    
    
    const Int_t nPsi = 1;
    const Int_t nV = 1;

    
    
    Int_t RunIteration;
    
    std::string FirstPassString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramFirstPass" + argv[3] + ".root";
    char *FirstPassChar = &FirstPassString[0];
    
    std::string SecondPassString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramSecondPass" + argv[3] + ".root";
    char *SecondPassChar = &SecondPassString[0];
    
    std::string ThirdPassString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramThirdPass" + argv[3] + ".root";
    char *ThirdPassChar = &ThirdPassString[0];

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
    
//     RunIteration = 1;

    
    
    // Parameters
    Double_t yCMShift = -1.05;
//     Int_t NumberOfGoodTracksInnerEPD = 5;
//     Int_t NumberOfGoodTracksOuterEPD = 9;
//     Int_t NumberOfGoodTracksOuterTPC = 5;
    Double_t OuterTPCUpperLimit = 0.0;
    Double_t OuterTPCLowerLimit = -1.0;
    Double_t InnerTPCUpperLimit = -1.1;
    Double_t InnerTPCLowerLimit = -2.0;



    Double_t RVertexBound = 2.0;
    Double_t ZVertexLowerBound = 198.0;
    Double_t ZVertexUpperBound = 202.0;
    
    Double_t DCABound = 3.0;
    Int_t NHitsFitBound = 15;
//     Int_t NHitsdEdxBound = 5;
    Double_t NHitsFitOverNHitsPossBound = 0.52;
    
    Int_t InnerEPDHighRing = 8;
    Int_t OuterEPDLowRing = 9;
    
    
    double ProtonLowerMSquared = 0.6;
    double ProtonUpperMSquared = 1.2;
    Double_t KaonLowerMSquared = 0.16;
    Double_t KaonUpperMSquared = 0.36;
    Double_t PionLowerMSquared = -0.1;
    Double_t PionUpperMSquared = 0.15;
    Double_t NSigmaPrBound = 2.0;
    Double_t NSigmaKaBound = 3.0;
    Double_t NSigmaPiBound = 3.0;
    Double_t ProtonLowerPt = 0.4;
    Double_t ProtonUpperPt = 1.0;
    Double_t KaonLowerPt = 0.4;
    Double_t KaonUpperPt = 1.6;
    Double_t PionLowerPt = 0.2;
    Double_t PionUpperPt = 1.6;
    Double_t DeuteronLowerPt = 0.8;
    Double_t DeuteronUpperPt = 2.0;
    Double_t TritonLowerPt = 1.2;
    Double_t TritonUpperPt = 3.0;
    Double_t LowerYMinusYCMShift = 0.0;
    Double_t UpperYMinusYCMShift = 1.0;



    Int_t QBounds = 100;
    Int_t FourierCorrectionTerms = 20;


    
    // Parameter changes for systematic runs
    if (std::string(argv[3]) == "Normal")
    {
        QBounds = 100;
        FourierCorrectionTerms = 20;
    }
    if (std::string(argv[3]) == "DCA1")
    {
        DCABound = 1.0;
    }
    if (std::string(argv[3]) == "DCA2")
    {
        DCABound = 2.0;
    }
    if (std::string(argv[3]) == "NHits1")
    {
        NHitsFitBound = 10;
    }
    if (std::string(argv[3]) == "NHits2")
    {
        NHitsFitBound = 20;
    }
    if (std::string(argv[3]) == "NSigmaPion1")
    {
        NSigmaPiBound = 2.0;
    }
    if (std::string(argv[3]) == "NSigmaPion2")
    {
        NSigmaPiBound = 2.5;
    }
    if (std::string(argv[3]) == "NSigmaKaon1")
    {
        NSigmaKaBound = 2.0;
    }
    if (std::string(argv[3]) == "NSigmaKaon2")
    {
        NSigmaKaBound = 2.5;
    }
    if (std::string(argv[3]) == "NSigmaProton1")
    {
        NSigmaPrBound = 3.0;
    }
    if (std::string(argv[3]) == "NSigmaProton2")
    {
        NSigmaPrBound = 2.5;
    }
    if (std::string(argv[3]) == "MSquaredPion")
    {
        PionLowerMSquared = -0.05;
        PionUpperMSquared = 0.1;
    }
    if (std::string(argv[3]) == "MSquaredKaon")
    {
        KaonLowerMSquared = 0.18;
        KaonUpperMSquared = 0.32;
    }
    if (std::string(argv[3]) == "MSquaredProton")
    {
        ProtonLowerMSquared = 0.7;
        ProtonUpperMSquared = 1.1;
    }
    if (std::string(argv[3]) == "OuterEPDLow")
    {
        OuterEPDLowRing = 13;
    }
    if (std::string(argv[3]) == "OuterEPDHigh")
    {
        OuterEPDLowRing = 10;
    }
//     else
//     {
//         std::cout << "No Matching Systematic Error type (or Normal)" << std::endl;
//         exit(0);
//     }
    
    
        Int_t NumberOfRuns = 191;
        int RunIds[191] = {19151029,
        19151031,
        19151034,
        19151036,
        19151039,
        19151041,
        19151043,
        19151044,
        19151045,
        19151046,
        19151047,
        19151048,
        19151049,
        19151050,
        19151052,
        19151053,
        19151054,
        19151055,
        19151056,
        19151066,
        19151067,
        19151068,
        19151069,
        19151070,
        19151071,
        19151072,
        19151082,
        19151083,
        19151084,
        19152001,
        19152002,
        19152003,
        19152008,
        19152009,
        19152010,
        19152014,
        19152016,
        19152021,
        19152023,
        19152024,
        19152025,
        19152027,
        19152028,
        19152029,
        19152030,
        19152031,
        19152032,
        19152033,
        19152034,
        19152035,
        19152036,
        19152037,
        19152038,
        19152039,
        19152040,
        19152041,
        19152042,
        19152043,
        19152044,
        19152045,
        19152046,
        19152048,
        19152051,
        19152052,
        19152053,
        19152054,
        19152055,
        19152071,
        19152073,
        19152074,
        19152075,
        19152076,
        19152078,
        19152081,
        19153001,
        19153002,
        19153003,
        19153004,
        19153007,
        19153009,
        19153010,
        19153011,
        19153012,
        19153013,
        19153014,
        19153015,
        19153016,
        19153017,
        19153018,
        19153019,
        19153020,
        19153021,
        19153022,
        19153023,
        19153024,
        19153025,
        19153027,
        19153028,
        19153029,
        19153031,
        19153032,
        19153033,
        19153034,
        19153035,
        19153036,
        19153037,
        19153042,
        19153043,
        19153044,
        19153050,
        19153051,
        19153052,
        19153053,
        19153054,
        19153055,
        19153056,
        19153057,
        19153058,
        19153059,
        19153061,
        19153062,
        19153063,
        19153064,
        19153065,
        19153066,
        19154001,
        19154002,
        19154005,
        19154007,
        19154012,
        19154013,
        19154014,
        19154015,
        19154016,
        19154017,
        19154018,
        19154019,
        19154020,
        19154021,
        19154022,
        19154023,
        19154024,
        19154026,
        19154027,
        19154028,
        19154029,
        19154030,
        19154031,
        19154032,
        19154036,
        19154037,
        19154038,
        19154039,
        19154040,
        19154041,
        19154044,
        19154045,
        19154046,
        19154047,
        19154048,
        19154049,
        19154051,
        19154052,
        19154053,
        19154054,
        19154055,
        19154056,
        19154057,
        19154058,
        19154061,
        19154063,
        19154064,
        19154065,
        19154066,
        19154067,
        19155001,
        19155003,
        19155004,
        19155005,
        19155006,
        19155008,
        19155009,
        19155010,
        19155011,
        19155016,
        19155017,
        19155018,
        19155019,
        19155020,
        19155021,
        19155022};
    
    
    //Input files
    TFile *Data = TFile::Open(argv[1]);
    
    TFile *QVectorHistogramFileFirst;
    TFile *QVectorHistogramFileSecond;
    TFile *ResolutionFile;
    TFile *TPCEfficiencyFile;
    TFile *ToFEfficiencyFile;
    TFile *TPCEfficiencyFileDandT;

    
    if(RunIteration == 2)
    {
        std::string QVectorHistogramFirstString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/QVectorFirstPass" + argv[3] + ".root";
        char *QVectorHistogramFirstChar = &QVectorHistogramFirstString[0];

        QVectorHistogramFileFirst = TFile::Open(QVectorHistogramFirstChar, "READ");
    }
    
    if(RunIteration == 3)
    {
        std::string QVectorHistogramFirstString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/QVectorFirstPass" + argv[3] + ".root";
        char *QVectorHistogramFirstChar = &QVectorHistogramFirstString[0];

        QVectorHistogramFileFirst = TFile::Open(QVectorHistogramFirstChar, "READ");
        
        std::string QVectorHistogramSecondString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/QVectorSecondPass" + argv[3] + ".root";
        char *QVectorHistogramSecondChar = &QVectorHistogramSecondString[0];
    
        QVectorHistogramFileSecond = TFile::Open(QVectorHistogramSecondChar, "READ");
    }
    
    if(RunIteration == 4)
    {
        std::string QVectorHistogramFirstString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/QVectorFirstPass" + argv[3] + ".root";
        char *QVectorHistogramFirstChar = &QVectorHistogramFirstString[0];

        QVectorHistogramFileFirst = TFile::Open(QVectorHistogramFirstChar, "READ");
        
        std::string QVectorHistogramSecondString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/QVectorSecondPass" + argv[3] + ".root";
        char *QVectorHistogramSecondChar = &QVectorHistogramSecondString[0];
    
        QVectorHistogramFileSecond = TFile::Open(QVectorHistogramSecondChar, "READ");
        
        std::string ResolutionFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/R_" + std::to_string(nV) + std::to_string(nPsi) + "_" + argv[3] + ".root";
        const char* ResolutionFileChar = &ResolutionFileString[0];
    
        ResolutionFile = TFile::Open(ResolutionFileChar, "READ");
        
        TPCEfficiencyFile = TFile::Open("/star/u/mcgordon/VnFromEPD/Efficiencies/TPCEfficiency.root","READ");
        ToFEfficiencyFile = TFile::Open("/star/u/mcgordon/VnFromEPD/Efficiencies/ToFEfficiency.root","READ");
        TPCEfficiencyFileDandT = TFile::Open("/star/u/mcgordon/VnFromEPD/Efficiencies/TPCEfficiencyDandT.root","READ");
    }


    

    
//     TProfile *InnerEPDSineAverageProfile;
//     TProfile *InnerEPDCosineAverageProfile;
//     TProfile *OuterEPDSineAverageProfile;
//     TProfile *OuterEPDCosineAverageProfile;
//     TProfile *OuterTPCSineAverageProfile;
//     TProfile *OuterTPCCosineAverageProfile;
    
//     if(RunIteration >= 3)
//     {
//         InnerEPDSineAverageProfile = (TProfile*)QVectorHistogramFileSecond->Get("InnerEPDSineAverages");
//         InnerEPDCosineAverageProfile = (TProfile*)QVectorHistogramFileSecond->Get("InnerEPDCosineAverages");
//         OuterEPDSineAverageProfile = (TProfile*)QVectorHistogramFileSecond->Get("OuterEPDSineAverages");
//         OuterEPDCosineAverageProfile = (TProfile*)QVectorHistogramFileSecond->Get("OuterEPDCosineAverages");
//         OuterTPCSineAverageProfile = (TProfile*)QVectorHistogramFileSecond->Get("OuterTPCSineAverages");
//         OuterTPCCosineAverageProfile = (TProfile*)QVectorHistogramFileSecond->Get("OuterTPCCosineAverages");
//     }
    

                
    Int_t MaxTracks = 195;
    
    //Tree Setup
    Int_t runId;
    Int_t eventId;
    UShort_t tracknumber;
    Float_t Px[MaxTracks];
    Float_t Py[MaxTracks];
    Float_t Pz[MaxTracks];
    Short_t Charge[MaxTracks];
    Float_t ToFBeta[MaxTracks];
    Float_t dedx[MaxTracks];
    Float_t nSigmaPr[MaxTracks];
    Float_t nSigmaKa[MaxTracks];
    Float_t nSigmaPi[MaxTracks];
    Float_t Vx;
    Float_t Vy;
    Float_t Vz;
    UShort_t centrality;
    Float_t dca[MaxTracks];
    Int_t nHits[MaxTracks];
    Int_t nHitsdEdx[MaxTracks];
    Int_t nHitsFit[MaxTracks];
    Int_t nHitsPoss[MaxTracks];
    UShort_t nEPDhits;
    Float_t EPDnMip[744];
    Short_t EPDid[744];
    
    
    
    TTree *AutreeData = (TTree*)Data->Get("Autree");
    AutreeData->SetBranchAddress("runId", &runId);
    AutreeData->SetBranchAddress("eventId", &eventId);
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
    
    TProfile2D *HistoEPDQxRecenterParameter[7];
    TProfile2D *HistoEPDQyRecenterParameter[7];

    // 0 is for EPD_A, 1 is for EPD_B, 2 is for EPD_C, 3 is for EPD_D, 4 is for EPD_AB, 5 is for EPD_CD, 6 is for EPD_ABCD
    for(int i = 0; i < 7; i++)
    {
        HistoEPDQxRecenterParameter[i] = new TProfile2D(Form("EPDQxRecenterParameter%d", i), "", 9, -0.5, 8.5, 500, -0.5, 499.5);
        HistoEPDQyRecenterParameter[i] = new TProfile2D(Form("EPDQyRecenterParameter%d", i), "", 9, -0.5, 8.5, 500, -0.5, 499.5);
    }
    TProfile2D *HistoOuterTPCQxRecenterParameter = new TProfile2D("OuterTPCQxRecenterParameter", "", 9, -0.5, 8.5, 500, -0.5, 499.5);
    TProfile2D *HistoOuterTPCQyRecenterParameter = new TProfile2D("OuterTPCQyRecenterParameter", "", 9, -0.5, 8.5, 500, -0.5, 499.5);
    TProfile2D *HistoInnerTPCQxRecenterParameter = new TProfile2D("InnerTPCQxRecenterParameter", "", 9, -0.5, 8.5, 500, -0.5, 499.5);
    TProfile2D *HistoInnerTPCQyRecenterParameter = new TProfile2D("InnerTPCQyRecenterParameter", "", 9, -0.5, 8.5, 500, -0.5, 499.5);
    
    

    TH1F *HistoDA = new TH1F("DataNSigmaProtonAll", "All NSigmaProton Values; NSigmaProton; Events", 10, -5, 5);
    HistoDA->Sumw2();
    
    TH1F *HistoDB = new TH1F("DataNSigmaProtonUsed", "Used NSigmaProton Values; NSigmaProton; Events", 10, -5, 5);
    HistoDB->Sumw2();
    
    
    
    TH2D *h2_zd_vs_mom = new TH2D("h2_zd_vs_mom", ";|p| (GeV/c);z_{d}", 50, 0.0, 5.0, 140, -0.7, 0.7);
    
    TH2D *h2_zt_vs_mom  = new TH2D("h2_zt_vs_mom", ";|p| (GeV/c);z_{t}", 50, 0.0, 5.0, 140, -0.7, 0.7);
    
    
    
    
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
    
    TProfile3D *HistoEPDShiftParameterCosine[7];
    TProfile3D *HistoEPDShiftParameterSine[7];
    
    // 0 is for EPD_A, 1 is for EPD_B, 2 is for EPD_C, 3 is for EPD_D, 4 is for EPD_AB, 5 is for EPD_CD, 6 is for EPD_ABCD
    for(int i = 0; i < 7; i++)
    {
        HistoEPDShiftParameterCosine[i] = new TProfile3D(Form("EPDShiftParameterCosine%d", i), "", 9, -0.5, 8.5, 20, -0.5, 19.5, 500, -0.5, 499.5);
        HistoEPDShiftParameterSine[i] = new TProfile3D(Form("EPDShiftParameterSine%d", i), "", 9, -0.5, 8.5, 20, -0.5, 19.5, 500, -0.5, 499.5);
    }
    TProfile3D *HistoOuterTPCShiftParameterCosine = new TProfile3D("OuterTPCShiftParameterCosine", "", 9, -0.5, 8.5, 20, -0.5, 19.5, 500, -0.5, 499.5);
    TProfile3D *HistoOuterTPCShiftParameterSine = new TProfile3D("OuterTPCShiftParameterSine", "", 9, -0.5, 8.5, 20, -0.5, 19.5, 500, -0.5, 499.5);
    TProfile3D *HistoInnerTPCShiftParameterCosine = new TProfile3D("InnerTPCShiftParameterCosine", "", 9, -0.5, 8.5, 20, -0.5, 19.5, 500, -0.5, 499.5);
    TProfile3D *HistoInnerTPCShiftParameterSine = new TProfile3D("InnerTPCShiftParameterSine", "", 9, -0.5, 8.5, 20, -0.5, 19.5, 500, -0.5, 499.5);
    
    
    TH1D *HistoInnerEPDQxRecentered = new TH1D("InnerEPDQxRecentered", "Qx Recentered for Inner EPD; Qx; Events", 250, -QBounds, QBounds);
    TH1D *HistoInnerEPDQyRecentered = new TH1D("InnerEPDQyRecentered", "Qy Recentered for Inner EPD; Qy; Events", 250, -QBounds, QBounds);
    TH1D *HistoOuterEPDQxRecentered = new TH1D("OuterEPDQxRecentered", "Qx Recentered for Outer EPD; Qx; Events", 250, -QBounds, QBounds);
    TH1D *HistoOuterEPDQyRecentered = new TH1D("OuterEPDQyRecentered", "Qy Recentered for Outer EPD; Qy; Events", 250, -QBounds, QBounds);
    TH1D *HistoOuterTPCQxRecentered = new TH1D("OuterTPCQxRecentered", "Qx Recentered for TPC; Qx; Events", 250, -QBounds, QBounds);
    TH1D *HistoOuterTPCQyRecentered = new TH1D("OuterTPCQyRecentered", "Qy Recentered for TPC; Qy; Events", 250, -QBounds, QBounds);
    

    
    TProfile *HistoInnerEPDSineAverages = 0;
    TProfile *HistoInnerEPDCosineAverages = 0;
    TProfile *HistoOuterEPDSineAverages = 0;
    TProfile *HistoOuterEPDCosineAverages = 0;
    TProfile *HistoOuterTPCSineAverages = 0;
    TProfile *HistoOuterTPCCosineAverages = 0;
    
    if(RunIteration == 2)
    {
        HistoInnerEPDSineAverages = new TProfile("InnerEPDSineAverages", "Inner EPD Sine Averages; j; Sine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
        HistoInnerEPDCosineAverages = new TProfile("InnerEPDCosineAverages", "Inner EPD Cosine Averages; j; Cosine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
        HistoOuterEPDSineAverages = new TProfile("OuterEPDSineAverages", "Outer EPD Sine Averages; j; Sine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
        HistoOuterEPDCosineAverages = new TProfile("OuterEPDCosineAverages", "Outer EPD Cosine Averages; j; Cosine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
        HistoOuterTPCSineAverages = new TProfile("OuterTPCSineAverages", "Outer TPC Sine Averages; j; Sine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
        HistoOuterTPCCosineAverages = new TProfile("OuterTPCCosineAverages", "Outer TPC Cosine Averages; j; Cosine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1);
    }
    
    
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

    TH1D *InnerTPCRawEP[10];
    TH1D *OuterTPCRawEP[10];
    TH1D *InnerTPCRecenteredEP[10];
    TH1D *OuterTPCRecenteredEP[10];
    TH1D *InnerTPCShiftedEP[10];
    TH1D *OuterTPCShiftedEP[10];
    
    TH1D *EPDRawEP[10][7];
    TH1D *EPDRecenteredEP[10][7];
    TH1D *EPDShiftedEP[10][7];
    
    for(int i = 0; i < 10; i++)
    {
        InnerTPCRawEP[i] = new TH1D(Form("InnerTPCRawEP%d",i),"",314,-3.14, 3.14);
        OuterTPCRawEP[i] = new TH1D(Form("OuterTPCRawEP%d",i),"",314,-3.14, 3.14);
        InnerTPCRecenteredEP[i] = new TH1D(Form("InnerTPCRecenteredEP%d",i),"",314,-3.14, 3.14);
        OuterTPCRecenteredEP[i] = new TH1D(Form("OuterTPCRecenteredEP%d",i),"",314,-3.14, 3.14);
        InnerTPCShiftedEP[i] = new TH1D(Form("InnerTPCShiftedEP%d",i),"",314,-3.14, 3.14);
        OuterTPCShiftedEP[i] = new TH1D(Form("OuterTPCShiftedEP%d",i),"",314,-3.14, 3.14);
        
        for(int j = 0; j < 8; j++)
        {
            EPDRawEP[i][j] = new TH1D(Form("EPDRawEP_Ring%d_ModifiedCent%d",j,i),"",314,-3.14, 3.14);
            EPDRecenteredEP[i][j] = new TH1D(Form("EPDRecenteredEP_Ring%d_ModifiedCent%d",j,i),"",314,-3.14, 3.14);
            EPDShiftedEP[i][j] = new TH1D(Form("EPDShiftedEP_Ring%d_ModifiedCent%d",j,i),"",314,-3.14, 3.14);
        }
    }
    
  
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
    
//     TProfile *HistoD51 = new TProfile("DataResolutionTopLeftTerm", "Resolution Top Left Term (Data); Centrality; Top Left Term", 12, 0, 12);
//     HistoD51->Sumw2();

//     TProfile *HistoD52 = new TProfile("DataResolutionTopRightTerm", "Resolution Top Right Term (Data); Centrality; Top Right Term", 12, 0, 12);
//     HistoD52->Sumw2();

//     TProfile *HistoD53 = new TProfile("DataResolutionBottomTerm", "Resolution Bottom Term (Data); Centrality; Bottom Term", 12, 0, 12);
//     HistoD53->Sumw2();
    
    const Int_t NumberOfCentralityBins = 7;
    Double_t CentralityBinEdges[NumberOfCentralityBins + 1] = {0.0, 1.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0};
    
    TProfile *HistoD51 = new TProfile("DataResolutionTopLeftTerm", "Resolution Top Left Term (Data); Centrality; Top Left Term", NumberOfCentralityBins, CentralityBinEdges);
    HistoD51->Sumw2();

    TProfile *HistoD52 = new TProfile("DataResolutionTopRightTerm", "Resolution Top Right Term (Data); Centrality; Top Right Term", NumberOfCentralityBins, CentralityBinEdges);
    HistoD52->Sumw2();

    TProfile *HistoD53 = new TProfile("DataResolutionBottomTerm", "Resolution Bottom Term (Data); Centrality; Bottom Term", NumberOfCentralityBins, CentralityBinEdges);
    HistoD53->Sumw2();
    
    
    
    //Fourth Pass Histograms
    
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

    
    
    
    TProfile *HistoD54;

    if(RunIteration == 4)
    {
        HistoD54 = (TProfile*)ResolutionFile->Get("DataResolution");
    }
    
    const char* CentralityXLabels[12] = {"0-5", "5-10", "10-20", "20-30", "30-40", "40-50", "50-60"};
    
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

    TProfile *HistoD54A = new TProfile("DataVnVsCentralityProtonCorrected", D54AChar, NumberOfCentralityBins, CentralityBinEdges);
    HistoD54A->Sumw2();
    
    for (int i = 1; i < HistoD54A->GetNbinsX() + 1; i++)
    {
        HistoD54A->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }

    std::string D54BString = "V" + std::to_string(nV) + " vs Centrality for Kaon+ (Data); Centrality; V" + std::to_string(nV) +"";
    const char *D54BChar = &D54BString[0];
    
    TProfile *HistoD54B = new TProfile("DataVnVsCentralityKaonPlusCorrected", D54BChar, NumberOfCentralityBins, CentralityBinEdges);
    HistoD54B->Sumw2();
    
    for (int i = 1; i < HistoD54B->GetNbinsX() + 1; i++)
    {
        HistoD54B->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }
    
    std::string D54CString = "V" + std::to_string(nV) + " vs Centrality for Kaon- (Data); Centrality; V" + std::to_string(nV) +"";
    const char *D54CChar = &D54CString[0];

    TProfile *HistoD54C = new TProfile("DataVnVsCentralityKaonMinusCorrected", D54CChar, NumberOfCentralityBins, CentralityBinEdges);
    HistoD54C->Sumw2();
    
    for (int i = 1; i < HistoD54C->GetNbinsX() + 1; i++)
    {
        HistoD54C->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }
    
    std::string D54DString = "V" + std::to_string(nV) + " vs Centrality for Pion+ (Data); Centrality; V" + std::to_string(nV) +"";
    const char *D54DChar = &D54DString[0];

    TProfile *HistoD54D = new TProfile("DataVnVsCentralityPionPlusCorrected", D54DChar, NumberOfCentralityBins, CentralityBinEdges);
    HistoD54D->Sumw2();
    
    for (int i = 1; i < HistoD54D->GetNbinsX() + 1; i++)
    {
        HistoD54D->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }

    std::string D54EString = "V" + std::to_string(nV) + " vs Centrality for Pion- (Data); Centrality; V" + std::to_string(nV) +"";
    const char *D54EChar = &D54EString[0];    
    
    TProfile *HistoD54E = new TProfile("DataVnVsCentralityPionMinusCorrected", D54EChar, NumberOfCentralityBins, CentralityBinEdges);
    HistoD54E->Sumw2();

    for (int i = 1; i < HistoD54E->GetNbinsX() + 1; i++)
    {
        HistoD54E->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }
    
    std::string D54FString = "V" + std::to_string(nV) + " vs Centrality for Deuterons (Data); Centrality; V" + std::to_string(nV) +"";
    const char *D54FChar = &D54FString[0];
    
    TProfile *HistoD54F = new TProfile("DataVnVsCentralityDeuteronCorrected", D54FChar, NumberOfCentralityBins, CentralityBinEdges);
    HistoD54F->Sumw2();
    
    for (int i = 1; i < HistoD54F->GetNbinsX() + 1; i++)
    {
        HistoD54F->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }
    
    std::string D54GString = "V" + std::to_string(nV) + " vs Centrality for Tritons (Data); Centrality; V" + std::to_string(nV) +"";
    const char *D54GChar = &D54GString[0];

    TProfile *HistoD54G = new TProfile("DataVnVsCentralityTritonCorrected", D54GChar, NumberOfCentralityBins, CentralityBinEdges);
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

    

    std::string VnVsYSymmetricProtonString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y (Symmetric) for Protons for Different Centralities (Data) ; Centrality; y_{CM}";
    const char *VnVsYSymmetricProtonChar = &VnVsYSymmetricProtonString[0];

    TProfile2D *VnVsYSymmetricProton = new TProfile2D("DataVnCorrectedVsYSymmetricDifferentCentralitiesProtons", VnVsYSymmetricProtonChar, 12, 0, 12, 10, -0.5, 0.5);
    VnVsYSymmetricProton->Sumw2();
    
    
    
    // For the first index, the first value is for Qx and the second value is for Qy
    TProfile2D *GetEPDRecentered[2][7];
    TProfile2D *GetInnerTPCRecentered[2];
    TProfile2D *GetOuterTPCRecentered[2];
    
    if(RunIteration >= 2)
    {
        GetInnerTPCRecentered[0]     = (TProfile2D*)QVectorHistogramFileFirst -> Get("OuterTPCQxRecenterParameter");
        GetInnerTPCRecentered[1]     = (TProfile2D*)QVectorHistogramFileFirst -> Get("OuterTPCQyRecenterParameter");
        GetOuterTPCRecentered[0]     = (TProfile2D*)QVectorHistogramFileFirst -> Get("InnerTPCQxRecenterParameter");
        GetOuterTPCRecentered[1]     = (TProfile2D*)QVectorHistogramFileFirst -> Get("InnerTPCQyRecenterParameter");
        
        for(int i=0; i<7; i++)
        {
            GetEPDRecentered[0][i]     = (TProfile2D*)QVectorHistogramFileFirst -> Get(Form("EPDQxRecenterParameter%d", i));
            GetEPDRecentered[1][i]     = (TProfile2D*)QVectorHistogramFileFirst -> Get(Form("EPDQyRecenterParameter%d", i));
        }
    }
    
    
    
    TProfile3D *GetEPDShiftParameterCosine[7];
    TProfile3D *GetEPDShiftParameterSine[7];
    TProfile3D *GetInnerTPCShiftParameterCosine;
    TProfile3D *GetInnerTPCShiftParameterSine;
    TProfile3D *GetOuterTPCShiftParameterCosine;
    TProfile3D *GetOuterTPCShiftParameterSine;
    
    if(RunIteration >= 3)
    {
        GetInnerTPCShiftParameterCosine     = (TProfile3D*)QVectorHistogramFileSecond -> Get("InnerTPCShiftParameterCosine");
        GetInnerTPCShiftParameterSine     = (TProfile3D*)QVectorHistogramFileSecond -> Get("InnerTPCShiftParameterSine");
        GetOuterTPCShiftParameterCosine     = (TProfile3D*)QVectorHistogramFileSecond -> Get("OuterTPCShiftParameterCosine");
        GetOuterTPCShiftParameterSine     = (TProfile3D*)QVectorHistogramFileSecond -> Get("OuterTPCShiftParameterSine");
        
        for(int i=0; i<7; i++)
        {
            GetEPDShiftParameterCosine[i]     = (TProfile3D*)QVectorHistogramFileFirst -> Get(Form("EPDShiftParameterCosine%d", i));
            GetEPDShiftParameterSine[i]     = (TProfile3D*)QVectorHistogramFileFirst -> Get(Form("EPDShiftParameterSine%d", i));
        }
    }
    

    std::cout << "Setup Complete" << std::endl;
    
    StEpdGeom* epdGeom = new StEpdGeom();

    // Event Loop
    for (Long64_t EventNum = 0; EventNum < AutreeData->GetEntries(); EventNum++)
    {
        if (RunIteration == 1)
        {
            if (EventNum % 5000 == 0)
            {
                std::cout << "Data First Pass (Raw Values and Kinematics)" << EventNum << std::endl;
            }
        }
        
        if (RunIteration == 2)
        {
            if (EventNum % 5000 == 0)
            {
                std::cout << "Data Second Pass (Recentered Values)" << EventNum << std::endl;
            }
        }
        
        if (RunIteration == 3)
        {
            if (EventNum % 5000 == 0)
            {
                std::cout << "Data Third Pass (Fourier Corrected Values)" << EventNum << std::endl;
            }
        }
        
        if (RunIteration == 4)
        {
            if (EventNum % 5000 == 0)
            {
                std::cout << "Data Fourth Pass (Vn Corrected for Resolution)" << EventNum << std::endl;
            }
        }

        AutreeData->GetEntry(EventNum);


        Int_t TotalTracks = (Int_t)tracknumber;
        Double_t vx = Vx;
        Double_t vy = Vy;
        Double_t vz = Vz;
        Int_t Centrality = (Int_t)centrality;
        Int_t RunId = (Int_t)runId;

        
        Int_t RunIndex = -999;
        for(Int_t i=0; i < NumberOfRuns; i++)
        {
            if(RunId == RunIds[i])
            {
                RunIndex = i;
            }
        }
        
        
        
        Int_t ModifiedCentrality;
        
        switch(Centrality)
        {
            case 0:
                ModifiedCentrality = 0;
                break;
            case 1:
                ModifiedCentrality = 1;
                break;
            case 2:
                ModifiedCentrality = 2;
                break;
            case 3:
                ModifiedCentrality = 2;
                break;
            case 4:
                ModifiedCentrality = 3;
                break;
            case 5:
                ModifiedCentrality = 3;
                break;
            case 6:
                ModifiedCentrality = 4;
                break;
            case 7:
                ModifiedCentrality = 4;
                break;
            case 8:
                ModifiedCentrality = 5;
                break;
            case 9:
                ModifiedCentrality = 5;
                break;
            case 10:
                ModifiedCentrality = 6;
                break;
            case 11:
                ModifiedCentrality = 6;
                break;
        }


        
        Double_t vr = sqrt(pow(vx, 2) + pow(vy + 2, 2));

        if (vz <= ZVertexLowerBound || vz >= ZVertexUpperBound)
        {
            continue;
        }

        EventCheck->Fill(3);

        if (vr >= RVertexBound)
        {
            continue;
        }

        EventCheck->Fill(4);

        Int_t Multiplicity = TotalTracks;

        Double_t ProtonMass = 0.938272;
        Double_t KaonMass = 0.493677;
        Double_t PionMass = 0.139571;
        Double_t DeuteronMass = 1.875613;
        Double_t TritonMass = 2.808921;


        if(Centrality < 4)
        {
            continue;
        }
        
//         EventCheck->Fill(7);
                
       
        
        if(RunIteration == 1)
        {
            //Kinematics Track Loop
            for (Int_t TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
            {               
                Double_t px = Px[TrackNum];
                Double_t py = Py[TrackNum];
                Double_t pz = Pz[TrackNum];
                Int_t q = (Int_t)Charge[TrackNum];
                Double_t tofBeta = ToFBeta[TrackNum];
                Double_t dEdx = dedx[TrackNum];
                Double_t NSigmaPr = nSigmaPr[TrackNum];
                Double_t NSigmaKa = nSigmaKa[TrackNum];
                Double_t NSigmaPi = nSigmaPi[TrackNum];
                Double_t DCA = dca[TrackNum];
//                 Int_t NHits = nHits[TrackNum];
                Int_t NHitsFit = nHitsFit[TrackNum];
                Int_t NHitsPoss = nHitsPoss[TrackNum]; 
                
                if (DCA >= DCABound)
                {
                    continue;
                }
                if (NHitsFit < NHitsFitBound)
                {
                    continue;
                }
//                 if (NHitsdEdx <= NHitsdEdxBound)
//                 {
//                     continue;
//                 }
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



                //Particle Identification
                Bool_t IsKaon = false;
                Bool_t IsPion = false;
                Bool_t IsProtonToF = false;
                Bool_t IsDeuteron = false;
                Bool_t IsTriton = false;
                Bool_t IsProtonTPC = (abs(NSigmaPr) < NSigmaPrBound) && (p < 2.0) && (q == 1);
                
                

                if(tofBeta > 0)
                {
                    Double_t msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

                    IsKaon = (abs(NSigmaKa) < NSigmaKaBound) && (msquared > KaonLowerMSquared) && (msquared < KaonUpperMSquared);
                    IsPion = (abs(NSigmaPi) < NSigmaPiBound) && (msquared > PionLowerMSquared) && (msquared < PionUpperMSquared);
                    IsProtonToF = (abs(NSigmaPr) < NSigmaPrBound) && (msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared) && (p > 2.0)  && (q == 1);
                }

                Double_t zDeuteron = TMath::Log(dEdx / BichselZDeuteron->Eval(p));
                Double_t zTriton = TMath::Log(dEdx / BichselZTriton->Eval(p));
                
                DeuteronsAndTritons DAndT (p, dEdx, tofBeta, zDeuteron, zTriton);

                if(!(IsKaon) && !(IsPion) && !(IsProtonToF))
                {
                    IsDeuteron = DAndT.IsDeuteron() and (q == 1);
                    IsTriton = DAndT.IsTriton() and (q == 1);
                    
                    if(q == 1)
                    {
                        h2_zd_vs_mom->Fill(p, zDeuteron);
                        h2_zt_vs_mom->Fill(p, zTriton);
                    }
                }



                if(tofBeta > 0)
                {

                    Double_t msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

                    HistoD4->Fill(qp, msquared);
//                     HistoD4A->Fill(qp, msquared);

//                     HistoD24->Fill(qp, NSigmaPr);
//                     HistoD25->Fill(qp, NSigmaKa);
//                     HistoD26->Fill(qp, NSigmaPi);

                    // Proton criteria
                    if(IsProtonToF)
                    {
                        double mass = ProtonMass;

                        double y = FlowFunctions::Y(px, py, pz, mass);

                        HistoD5->Fill(y - yCMShift);
                        HistoD8->Fill(pt);
//                         HistoD15->Fill(p, dEdx);
//                         HistoD18->Fill(qp, msquared);

                        HistoD21->Fill(pt);

                        HistoD27->Fill(y - yCMShift, pt);
                    }

                    // Kaon criteria
                    if(IsKaon)
                    {
                        Double_t mass = KaonMass;

                        Double_t y = FlowFunctions::Y(px, py, pz, mass);

                        HistoD22->Fill(pt);

                        HistoD6->Fill(y - yCMShift);
                        HistoD9->Fill(pt);
//                         HistoD14->Fill(p, dEdx);
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
//                         HistoD13->Fill(p, dEdx);
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

//                     HistoD16->Fill(p, dEdx);
                    HistoD27A->Fill(y - yCMShift, pt);
                }

                if(IsTriton)
                {
                    Double_t mass = TritonMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                     HistoD17->Fill(p, dEdx);
                    HistoD27B->Fill(y - yCMShift, pt);
                }

                if(IsProtonTPC)
                {
                        Double_t mass = ProtonMass;

                        Double_t y = FlowFunctions::Y(px, py, pz, mass);

                        HistoD5->Fill(y - yCMShift);
                        HistoD8->Fill(pt);
//                         HistoD15->Fill(p, dEdx);

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
        
        
        

        
        Double_t FourierCorrectionTermInnerEPD = 0;
        Double_t FourierCorrectionTermOuterEPD = 0;
        Double_t FourierCorrectionTermOuterTPC = 0;
        
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
        
        Bool_t GoodEventFlag1 = true;
        
        if(RunIteration == 1)
        {
            Double_t InnerTPCQx = 0;
            Double_t InnerTPCQy = 0;
            Double_t OuterTPCQx = 0;
            Double_t OuterTPCQy = 0;
            
            //Q Vector Calculator loop (TPC)
            for (Int_t TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
            {
                    Double_t px = Px[TrackNum];
                    Double_t py = Py[TrackNum];
                    Double_t pz = Pz[TrackNum];
//                     Int_t q = (Int_t)Charge[TrackNum];
                    Double_t DCA = dca[TrackNum];
    //                 Int_t NHits = nHits[TrackNum];
                    Int_t NHitsFit = nHitsFit[TrackNum];
                    Int_t NHitsPoss = nHitsPoss[TrackNum]; 



                    OverallTrackCheckNoCuts->Fill(1);

                    if (DCA >= DCABound)
                    {
                        continue;
                    }
                    if (NHitsFit < NHitsFitBound)
                    {
                        continue;
                    }
    //                 if (NHitsdEdx <= NHitsdEdxBound)
    //                 {
    //                     continue;
    //                 }
                    if ((double)NHitsFit / (double)NHitsPoss <= NHitsFitOverNHitsPossBound)
                    {
                        continue;
                    }

                    OverallTrackCheckQACuts->Fill(1);


    //                 if(q == 0)
    //                 {
    //                     continue;
    //                 }
                

                    Double_t pt = FlowFunctions::Pt(px, py);

                    Double_t eta = FlowFunctions::Eta(px, py, pz);

                    Double_t phi = FlowFunctions::Phi(px, py);

                    if((pt < 0.2) || (pt > 2.0))
                    {
                        continue;
                    }

                    if ((eta > InnerTPCLowerLimit) && (eta < InnerTPCUpperLimit))
                    {
                        InnerTPCQy = pt*sin(nPsi*phi);
                        InnerTPCQx = pt*cos(nPsi*phi);
                        HistoInnerTPCQxRecenterParameter->Fill(ModifiedCentrality, RunIndex, InnerTPCQx);
                        HistoInnerTPCQyRecenterParameter->Fill(ModifiedCentrality, RunIndex, InnerTPCQy);
                    }

                    if ((eta > OuterTPCLowerLimit) && (eta < OuterTPCUpperLimit))
                    {
                        OuterTPCQy = pt*sin(nPsi*phi);
                        OuterTPCQx = pt*cos(nPsi*phi);
                        HistoOuterTPCQxRecenterParameter->Fill(ModifiedCentrality, RunIndex, OuterTPCQx);
                        HistoOuterTPCQyRecenterParameter->Fill(ModifiedCentrality, RunIndex, OuterTPCQy);
                    }
            }
            
            Int_t nEPDHits = (Int_t)nEPDhits;
            Double_t EPDQx[7] = {0};
            Double_t EPDQy[7] = {0};
            Double_t WeightEPD[7] = {0};
            
            //Q Vector Calculator loop (EPD)
            for (int index = 0; index < nEPDHits; index++)
            {
                Int_t EPDID = (Int_t)EPDid[index];
                Double_t EPDnMIP = EPDnMip[index];

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

                

                if (TVec->IsInnerEPD())
                {
                    EPDQy[4] += EPDnMIP*sin(nPsi*phi);
                    EPDQx[4] += EPDnMIP*cos(nPsi*phi);
                    WeightEPD[4] += EPDnMIP;
                }

                if (TVec->IsOuterEPD())
                {
                    EPDQy[5] += EPDnMIP*sin(nPsi*phi);
                    EPDQx[5] += EPDnMIP*cos(nPsi*phi);
                    WeightEPD[5] += EPDnMIP;
                }

                if (TVec->IsEPDA())
                {
                    EPDQy[0] += EPDnMIP*sin(nPsi*phi);
                    EPDQx[0] += EPDnMIP*cos(nPsi*phi);
                    WeightEPD[0] += EPDnMIP;
                }

                if (TVec->IsEPDB())
                {
                    EPDQy[1] += EPDnMIP*sin(nPsi*phi);
                    EPDQx[1] += EPDnMIP*cos(nPsi*phi);
                    WeightEPD[1] += EPDnMIP;
                }

                if (TVec->IsEPDC())
                {
                    EPDQy[2] += EPDnMIP*sin(nPsi*phi);
                    EPDQx[2] += EPDnMIP*cos(nPsi*phi);
                    WeightEPD[2] += EPDnMIP;
                }

                if (TVec->IsEPDD())
                {
                    EPDQy[3] += EPDnMIP*sin(nPsi*phi);
                    EPDQx[3] += EPDnMIP*cos(nPsi*phi);
                    WeightEPD[3] += EPDnMIP;
                }
                
                if ((TVec->IsInnerEPD()) || (TVec->IsOuterEPD()))
                {
                    EPDQy[6] += EPDnMIP*sin(nPsi*phi);
                    EPDQx[6] += EPDnMIP*cos(nPsi*phi);
                    WeightEPD[6] += EPDnMIP;
                }
                
                delete TVec;
            }
            

            
            for(int i = 0; i < 7; i++)
            {
                if((WeightEPD[i] == 0) || (EPDQx[i] == 0) || (EPDQy[i] == 0))
                {
                    GoodEventFlag1 = false;
                    
                    break;
                }

                EPDQx[i] /= WeightEPD[i];
                EPDQy[i] /= WeightEPD[i];
            }
            
            if(!GoodEventFlag1)
            {
                continue;
            }
        
            for(int i = 0; i < 7; i++)
            {
                HistoEPDQxRecenterParameter[i]->Fill(ModifiedCentrality, RunIndex, EPDQx[i]);
                HistoEPDQyRecenterParameter[i]->Fill(ModifiedCentrality, RunIndex, EPDQy[i]);
            }
        }
        
        
        

        
        
        Bool_t GoodEventFlag2 = true;
        
        if(RunIteration == 2)
        {
                            
            Double_t InnerTPCQxRecentered = 0;
            Double_t InnerTPCQyRecentered = 0;
            Double_t OuterTPCQxRecentered = 0;
            Double_t OuterTPCQyRecentered = 0;
            
            Double_t PsiInnerTPC = 0;
            Double_t PsiOuterTPC = 0;
            
            //Q Vector Calculator loop (TPC)
            for (Int_t TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
            {
                    Double_t px = Px[TrackNum];
                    Double_t py = Py[TrackNum];
                    Double_t pz = Pz[TrackNum];
//                     Int_t q = (Int_t)Charge[TrackNum];
                    Double_t DCA = dca[TrackNum];
    //                 Int_t NHits = nHits[TrackNum];
                    Int_t NHitsFit = nHitsFit[TrackNum];
                    Int_t NHitsPoss = nHitsPoss[TrackNum]; 



                    OverallTrackCheckNoCuts->Fill(1);

                    if (DCA >= DCABound)
                    {
                        continue;
                    }
                    if (NHitsFit < NHitsFitBound)
                    {
                        continue;
                    }
    //                 if (NHitsdEdx <= NHitsdEdxBound)
    //                 {
    //                     continue;
    //                 }
                    if ((double)NHitsFit / (double)NHitsPoss <= NHitsFitOverNHitsPossBound)
                    {
                        continue;
                    }

                    OverallTrackCheckQACuts->Fill(1);


    //                 if(q == 0)
    //                 {
    //                     continue;
    //                 }

                    Double_t pt = FlowFunctions::Pt(px, py);

                    Double_t eta = FlowFunctions::Eta(px, py, pz);

                    Double_t phi = FlowFunctions::Phi(px, py);

                    if((pt < 0.2) || (pt > 2.0))
                    {
                        continue;
                    }

                    if ((eta > InnerTPCLowerLimit) && (eta < InnerTPCUpperLimit))
                    {
                        InnerTPCQxRecentered += pt*(cos(nPsi*phi) - GetInnerTPCRecentered[0]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1));
                        InnerTPCQyRecentered += pt*(sin(nPsi*phi) - GetInnerTPCRecentered[1]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1));
                    }

                    if ((eta > OuterTPCLowerLimit) && (eta < OuterTPCUpperLimit))
                    {
                        OuterTPCQxRecentered += pt*(cos(nPsi*phi) - GetOuterTPCRecentered[0]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1));
                        OuterTPCQyRecentered += pt*(sin(nPsi*phi) - GetOuterTPCRecentered[1]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1));
                    }
            }
                
            if((InnerTPCQxRecentered == 0) || (InnerTPCQyRecentered == 0) || (OuterTPCQxRecentered == 0) || (OuterTPCQyRecentered == 0))
            {
                continue;
            }

            PsiInnerTPC = (1.0/nPsi)*atan2(InnerTPCQyRecentered, InnerTPCQxRecentered);
            PsiOuterTPC = (1.0/nPsi)*atan2(OuterTPCQyRecentered, OuterTPCQxRecentered);

            
            Int_t nEPDHits = (Int_t)nEPDhits;
            Double_t EPDQxRecentered[7] = {0};
            Double_t EPDQyRecentered[7] = {0};
            Double_t WeightEPD[7] = {0};

            //Q Vector Calculator loop (EPD)
            for (int index = 0; index < nEPDHits; index++)
            {  
                Int_t EPDID = (Int_t)EPDid[index];
                Double_t EPDnMIP = EPDnMip[index];

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

                

                if (TVec->IsInnerEPD())
                {
                    EPDQxRecentered[4] += EPDnMIP*cos(nPsi*phi) - GetEPDRecentered[0][4]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    EPDQyRecentered[4] += EPDnMIP*sin(nPsi*phi) - GetEPDRecentered[1][4]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    WeightEPD[4] += EPDnMIP;
                }

                if (TVec->IsOuterEPD())
                {
                    EPDQxRecentered[5] += EPDnMIP*cos(nPsi*phi) - GetEPDRecentered[0][5]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    EPDQyRecentered[5] += EPDnMIP*sin(nPsi*phi) - GetEPDRecentered[1][5]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    WeightEPD[5] += EPDnMIP;
                }

                if (TVec->IsEPDA())
                {
                    EPDQxRecentered[0] += EPDnMIP*cos(nPsi*phi) - GetEPDRecentered[0][0]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    EPDQyRecentered[0] += EPDnMIP*sin(nPsi*phi) - GetEPDRecentered[1][0]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    WeightEPD[0] += EPDnMIP;
                }

                if (TVec->IsEPDB())
                {
                    EPDQxRecentered[1] += EPDnMIP*cos(nPsi*phi) - GetEPDRecentered[0][1]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    EPDQyRecentered[1] += EPDnMIP*sin(nPsi*phi) - GetEPDRecentered[1][1]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    WeightEPD[1] += EPDnMIP;
                }

                if (TVec->IsEPDC())
                {
                    EPDQxRecentered[2] += EPDnMIP*cos(nPsi*phi) - GetEPDRecentered[0][2]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    EPDQyRecentered[2] += EPDnMIP*sin(nPsi*phi) - GetEPDRecentered[1][2]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    WeightEPD[2] += EPDnMIP;
                }

                if (TVec->IsEPDD())
                {
                    EPDQxRecentered[3] += EPDnMIP*cos(nPsi*phi) - GetEPDRecentered[0][3]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    EPDQyRecentered[3] += EPDnMIP*sin(nPsi*phi) - GetEPDRecentered[1][3]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    WeightEPD[3] += EPDnMIP;
                }
                
                if ((TVec->IsInnerEPD()) || (TVec->IsOuterEPD()))
                {
                    EPDQxRecentered[6] += EPDnMIP*cos(nPsi*phi) - GetEPDRecentered[0][6]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    EPDQyRecentered[6] += EPDnMIP*sin(nPsi*phi) - GetEPDRecentered[1][6]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    WeightEPD[6] += EPDnMIP;
                }
                
                delete TVec;
            }

            Double_t PsiEPD[7] = {0};
            
            for(int i = 0; i < 7; i++)
            {
                if((WeightEPD[i] == 0) || (EPDQxRecentered[i] == 0) || (EPDQyRecentered[i] == 0))
                {
                    GoodEventFlag2 = false;
                    
                    break;
                }

                EPDQxRecentered[i] /= WeightEPD[i];
                EPDQyRecentered[i] /= WeightEPD[i];
            }

            if(!GoodEventFlag2)
            {
                continue;
            }
            
            for(int i = 0; i < 7; i++)
            {
                PsiEPD[i] = (1.0/nPsi)*atan2(EPDQyRecentered[i], EPDQxRecentered[i]);
            }

            for(int i = 0; i < 7; i++)
            {
                for(int j = 0; j < FourierCorrectionTerms; j++)
                {
                    HistoEPDShiftParameterSine[i]->Fill(ModifiedCentrality, j, RunIndex, sin(nPsi*(j+1)*PsiEPD[i]));
                    HistoEPDShiftParameterCosine[i]->Fill(ModifiedCentrality, j, RunIndex, cos(nPsi*(j+1)*PsiEPD[i]));
                }
            }

            for(int i = 0; i < FourierCorrectionTerms; i++)
            {
                HistoInnerTPCShiftParameterSine->Fill(ModifiedCentrality, i, RunIndex, sin(nPsi*(i+1)*PsiInnerTPC));
                HistoInnerTPCShiftParameterCosine->Fill(ModifiedCentrality, i, RunIndex, cos(nPsi*(i+1)*PsiInnerTPC));
                HistoOuterTPCShiftParameterSine->Fill(ModifiedCentrality, i, RunIndex, sin(nPsi*(i+1)*PsiOuterTPC));
                HistoOuterTPCShiftParameterCosine->Fill(ModifiedCentrality, i, RunIndex, cos(nPsi*(i+1)*PsiOuterTPC));
            }
            
        }
        
        

        
        
        Bool_t GoodEventFlag3 = true;
        
        if(RunIteration == 3)
        {
                            
            Double_t InnerTPCQxRaw = 0;
            Double_t InnerTPCQyRaw = 0;
            Double_t OuterTPCQxRaw = 0;
            Double_t OuterTPCQyRaw = 0;
            Double_t InnerTPCQxRecentered = 0;
            Double_t InnerTPCQyRecentered = 0;
            Double_t OuterTPCQxRecentered = 0;
            Double_t OuterTPCQyRecentered = 0;
            
            Double_t InnerTPCWeight = 0;
            Double_t OuterTPCWeight = 0;
            
            Double_t PsiInnerTPCRaw = 0;
            Double_t PsiOuterTPCRaw = 0;
            Double_t PsiInnerTPCRecentered = 0;
            Double_t PsiOuterTPCRecentered = 0;
            Double_t PsiInnerTPCShifted = 0;
            Double_t PsiOuterTPCShifted = 0;
            
            //Q Vector Calculator loop (TPC)
            for (Int_t TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
            {
                    Double_t px = Px[TrackNum];
                    Double_t py = Py[TrackNum];
                    Double_t pz = Pz[TrackNum];
//                     Int_t q = (Int_t)Charge[TrackNum];
                    Double_t DCA = dca[TrackNum];
    //                 Int_t NHits = nHits[TrackNum];
                    Int_t NHitsFit = nHitsFit[TrackNum];
                    Int_t NHitsPoss = nHitsPoss[TrackNum]; 



                    OverallTrackCheckNoCuts->Fill(1);

                    if (DCA >= DCABound)
                    {
                        continue;
                    }
                    if (NHitsFit < NHitsFitBound)
                    {
                        continue;
                    }
    //                 if (NHitsdEdx <= NHitsdEdxBound)
    //                 {
    //                     continue;
    //                 }
                    if ((double)NHitsFit / (double)NHitsPoss <= NHitsFitOverNHitsPossBound)
                    {
                        continue;
                    }

                    OverallTrackCheckQACuts->Fill(1);


    //                 if(q == 0)
    //                 {
    //                     continue;
    //                 }

                    Double_t pt = FlowFunctions::Pt(px, py);

                    Double_t eta = FlowFunctions::Eta(px, py, pz);

                    Double_t phi = FlowFunctions::Phi(px, py);

                    if((pt < 0.2) || (pt > 2.0))
                    {
                        continue;
                    }

                    if ((eta > InnerTPCLowerLimit) && (eta < InnerTPCUpperLimit))
                    {
                        InnerTPCQxRaw += pt*cos(nPsi*phi);
                        InnerTPCQyRaw += pt*sin(nPsi*phi);
                        InnerTPCQxRecentered += pt*(cos(nPsi*phi) - GetInnerTPCRecentered[0]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1));
                        InnerTPCQyRecentered += pt*(sin(nPsi*phi) - GetInnerTPCRecentered[1]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1));
                        InnerTPCWeight++;
                    }

                    if ((eta > OuterTPCLowerLimit) && (eta < OuterTPCUpperLimit))
                    {
                        OuterTPCQxRaw += pt*cos(nPsi*phi);
                        OuterTPCQyRaw += pt*sin(nPsi*phi);
                        OuterTPCQxRecentered += pt*(cos(nPsi*phi) - GetOuterTPCRecentered[0]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1));
                        OuterTPCQyRecentered += pt*(sin(nPsi*phi) - GetOuterTPCRecentered[1]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1));
                        OuterTPCWeight++;
                    }
            }
            
            if((InnerTPCQxRaw == 0) || (InnerTPCQyRaw == 0) || (OuterTPCQxRaw == 0) || (OuterTPCQyRaw == 0))
            {
                continue;
            }            
                
            if((InnerTPCQxRecentered == 0) || (InnerTPCQyRecentered == 0) || (OuterTPCQxRecentered == 0) || (OuterTPCQyRecentered == 0))
            {
                continue;
            }
            
            if((InnerTPCWeight == 0) || (OuterTPCWeight == 0))
            {
                continue;
            }
            
            InnerTPCQxRaw /= InnerTPCWeight;
            InnerTPCQyRaw /= InnerTPCWeight;
            InnerTPCQxRecentered /= InnerTPCWeight;
            InnerTPCQyRecentered /= InnerTPCWeight;
            OuterTPCQxRaw /= OuterTPCWeight;
            OuterTPCQyRaw /= OuterTPCWeight;
            OuterTPCQxRecentered /= OuterTPCWeight;
            OuterTPCQyRecentered /= OuterTPCWeight;            
            

            PsiInnerTPCRaw = (1.0/nPsi)*atan2(InnerTPCQyRaw, InnerTPCQxRaw);
            PsiOuterTPCRaw = (1.0/nPsi)*atan2(OuterTPCQyRaw, OuterTPCQxRaw);
            
            PsiInnerTPCRecentered = (1.0/nPsi)*atan2(InnerTPCQyRecentered, InnerTPCQxRecentered);
            PsiOuterTPCRecentered = (1.0/nPsi)*atan2(OuterTPCQyRecentered, OuterTPCQxRecentered);
            
            PsiInnerTPCShifted = PsiInnerTPCRecentered;
            PsiOuterTPCShifted = PsiOuterTPCRecentered;
            
            for(int i=0; i<FourierCorrectionTerms; i++)
            {
                PsiInnerTPCShifted += (2.0/(i+1)) * (-1*GetInnerTPCShiftParameterSine->GetBinContent(ModifiedCentrality+1, i+1, RunIndex+1)*cos(nPsi*(i+1)*PsiInnerTPCRecentered) + GetInnerTPCShiftParameterCosine->GetBinContent(ModifiedCentrality+1, i+1, RunIndex+1)*sin(nPsi*(i+1)*PsiInnerTPCRecentered));
                PsiOuterTPCShifted += (2.0/(i+1)) * (-1*GetOuterTPCShiftParameterSine->GetBinContent(ModifiedCentrality+1, i+1, RunIndex+1)*cos(nPsi*(i+1)*PsiOuterTPCRecentered) + GetOuterTPCShiftParameterCosine->GetBinContent(ModifiedCentrality+1, i+1, RunIndex+1)*sin(nPsi*(i+1)*PsiOuterTPCRecentered));
            }

           
            Int_t nEPDHits = (Int_t)nEPDhits;
            Double_t EPDQxRaw[7] = {0};
            Double_t EPDQyRaw[7] = {0};
            Double_t EPDQxRecentered[7] = {0};
            Double_t EPDQyRecentered[7] = {0};
            
            Double_t PsiEPDRaw[7] = {0};
            Double_t PsiEPDRecentered[7] = {0};
            Double_t PsiEPDShifted[7] = {0};
            Double_t WeightEPD[7] = {0};

            //Q Vector Calculator loop (EPD)
            for (int index = 0; index < nEPDHits; index++)
            {  
                Int_t EPDID = (Int_t)EPDid[index];
                Double_t EPDnMIP = EPDnMip[index];

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

                

                if (TVec->IsInnerEPD())
                {
                    EPDQxRaw[4] += EPDnMIP*cos(nPsi*phi);
                    EPDQyRaw[4] += EPDnMIP*sin(nPsi*phi);
                    EPDQxRecentered[4] += EPDnMIP*cos(nPsi*phi) - GetEPDRecentered[0][4]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    EPDQyRecentered[4] += EPDnMIP*sin(nPsi*phi) - GetEPDRecentered[1][4]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    WeightEPD[4] += EPDnMIP;
                }

                if (TVec->IsOuterEPD())
                {
                    EPDQxRaw[5] += EPDnMIP*cos(nPsi*phi);
                    EPDQyRaw[5] += EPDnMIP*sin(nPsi*phi);
                    EPDQxRecentered[5] += EPDnMIP*cos(nPsi*phi) - GetEPDRecentered[0][5]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    EPDQyRecentered[5] += EPDnMIP*sin(nPsi*phi) - GetEPDRecentered[1][5]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    WeightEPD[5] += EPDnMIP;
                }

                if (TVec->IsEPDA())
                {
                    EPDQxRaw[0] += EPDnMIP*cos(nPsi*phi);
                    EPDQyRaw[0] += EPDnMIP*sin(nPsi*phi);
                    EPDQxRecentered[0] += EPDnMIP*cos(nPsi*phi) - GetEPDRecentered[0][0]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    EPDQyRecentered[0] += EPDnMIP*sin(nPsi*phi) - GetEPDRecentered[1][0]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    WeightEPD[0] += EPDnMIP;
                }

                if (TVec->IsEPDB())
                {
                    EPDQxRaw[1] += EPDnMIP*cos(nPsi*phi);
                    EPDQyRaw[1] += EPDnMIP*sin(nPsi*phi);
                    EPDQxRecentered[1] += EPDnMIP*cos(nPsi*phi) - GetEPDRecentered[0][1]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    EPDQyRecentered[1] += EPDnMIP*sin(nPsi*phi) - GetEPDRecentered[1][1]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    WeightEPD[1] += EPDnMIP;
                }

                if (TVec->IsEPDC())
                {
                    EPDQxRaw[2] += EPDnMIP*cos(nPsi*phi);
                    EPDQyRaw[2] += EPDnMIP*sin(nPsi*phi);
                    EPDQxRecentered[2] += EPDnMIP*cos(nPsi*phi) - GetEPDRecentered[0][2]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    EPDQyRecentered[2] += EPDnMIP*sin(nPsi*phi) - GetEPDRecentered[1][2]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    WeightEPD[2] += EPDnMIP;
                }

                if (TVec->IsEPDD())
                {
                    EPDQxRaw[3] += EPDnMIP*cos(nPsi*phi);
                    EPDQyRaw[3] += EPDnMIP*sin(nPsi*phi);
                    EPDQxRecentered[3] += EPDnMIP*cos(nPsi*phi) - GetEPDRecentered[0][3]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    EPDQyRecentered[3] += EPDnMIP*sin(nPsi*phi) - GetEPDRecentered[1][3]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    WeightEPD[3] += EPDnMIP;
                }
                
                if ((TVec->IsInnerEPD()) || (TVec->IsOuterEPD()))
                {
                    EPDQxRaw[6] += EPDnMIP*cos(nPsi*phi);
                    EPDQyRaw[6] += EPDnMIP*sin(nPsi*phi);
                    EPDQxRecentered[6] += EPDnMIP*cos(nPsi*phi) - GetEPDRecentered[0][6]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    EPDQyRecentered[6] += EPDnMIP*sin(nPsi*phi) - GetEPDRecentered[1][6]->GetBinContent(ModifiedCentrality + 1, RunIndex + 1);
                    WeightEPD[6] += EPDnMIP;
                }
                
                delete TVec;
            }
         
            for(int i = 0; i < 7; i++)
            {
                if((WeightEPD[i] == 0) || (EPDQxRecentered[i] == 0) || (EPDQyRecentered[i] == 0))
                {
                    GoodEventFlag3 = false;
                    
                    break;
                }

                EPDQxRaw[i] /= WeightEPD[i];
                EPDQyRaw[i] /= WeightEPD[i];
                EPDQxRecentered[i] /= WeightEPD[i];
                EPDQyRecentered[i] /= WeightEPD[i];
            }

            if(!GoodEventFlag3)
            {
                continue;
            }
            
            for(int i = 0; i < 7; i++)
            {
                PsiEPDRaw[i] = (1.0/nPsi)*atan2(EPDQyRaw[i], EPDQxRaw[i]);
                PsiEPDRecentered[i] = (1.0/nPsi)*atan2(EPDQyRecentered[i], EPDQxRecentered[i]);
                PsiEPDShifted[i] = PsiEPDRecentered[i];
            }

            for(int i = 0; i < 7; i++)
            {
                for(int j = 0; j < FourierCorrectionTerms; j++)
                {
                    PsiEPDShifted[i] = (2.0/(j+1)) * (-1*GetEPDShiftParameterSine[i]->GetBinContent(ModifiedCentrality+1, j+1, RunIndex+1)*cos(nPsi*(j+1)*PsiEPDRecentered[i]) + GetEPDShiftParameterCosine[i]->GetBinContent(ModifiedCentrality+1, j+1, RunIndex+1)*sin(nPsi*(j+1)*PsiEPDRecentered[i]));
                }
            }
          
            InnerTPCRawEP[ModifiedCentrality]->Fill(PsiInnerTPCRaw);
            OuterTPCRawEP[ModifiedCentrality]->Fill(PsiOuterTPCRaw);
            InnerTPCRecenteredEP[ModifiedCentrality]->Fill(PsiInnerTPCRecentered);
            OuterTPCRecenteredEP[ModifiedCentrality]->Fill(PsiOuterTPCRecentered);
            InnerTPCShiftedEP[ModifiedCentrality]->Fill(PsiInnerTPCShifted);
            OuterTPCShiftedEP[ModifiedCentrality]->Fill(PsiOuterTPCShifted);
            
            for(int i=0; i<7; i++)
            {
                EPDRawEP[ModifiedCentrality][i]->Fill(PsiEPDRaw[i]);
                EPDRecenteredEP[ModifiedCentrality][i]->Fill(PsiEPDRecentered[i]);
                EPDShiftedEP[ModifiedCentrality][i]->Fill(PsiEPDShifted[i]);
            }
        }




        
        
        Double_t ResolutionCorrectionFactor = 0;

        if(RunIteration == 4)
        {
            Centrality = 15 - Centrality;

            ResolutionCorrectionFactor = HistoD54->GetBinContent(ModifiedCentrality + 1);

            if (ResolutionCorrectionFactor == 0)
            {
                continue;
            }
        }




        
        
        //Flow Calulator loop
        for (int TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
        {
            Double_t px = Px[TrackNum];
            Double_t py = Py[TrackNum];
            Double_t pz = Pz[TrackNum];
            Int_t q = (Int_t)Charge[TrackNum];
            Double_t tofBeta = ToFBeta[TrackNum];
            Double_t dEdx = dedx[TrackNum];
            Double_t NSigmaPr = nSigmaPr[TrackNum];
            Double_t NSigmaKa = nSigmaKa[TrackNum];
            Double_t NSigmaPi = nSigmaPi[TrackNum];
            Double_t DCA = dca[TrackNum];
//             Int_t NHits = nHits[TrackNum];
            Int_t NHitsFit = nHitsFit[TrackNum];
            Int_t NHitsPoss = nHitsPoss[TrackNum];


            if (DCA >= DCABound)
            {
                continue;
            }
            if (NHitsFit < NHitsFitBound)
            {
                continue;
            }
//             if (NHitsdEdx <= NHitsdEdxBound)
//             {
//                 continue;
//             }
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
            Bool_t IsProtonToF = false;
            Bool_t IsDeuteron = false;
            Bool_t IsTriton = false;
            Bool_t IsProtonTPC = (abs(NSigmaPr) < NSigmaPrBound) && (p < 2.0) && (q == 1);


            if(tofBeta > 0)
            {
                Double_t msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

                IsKaon = (abs(NSigmaKa) < NSigmaKaBound) && (msquared > KaonLowerMSquared) && (msquared < KaonUpperMSquared);
                IsPion = (abs(NSigmaPi) < NSigmaPiBound) && (msquared > PionLowerMSquared) && (msquared < PionUpperMSquared);
//                 IsProtonToF = (abs(NSigmaPr) < NSigmaPrBound) && (msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared) && (p > 2.0) && (q == 1);
            }
            
            Double_t zDeuteron = TMath::Log(dEdx / BichselZDeuteron->Eval(p));
            Double_t zTriton = TMath::Log(dEdx / BichselZTriton->Eval(p));

            DeuteronsAndTritons DAndT (p, dEdx, tofBeta, zDeuteron, zTriton);

            if(!(IsKaon) && !(IsPion) && !(IsProtonToF))
            {
                IsDeuteron = DAndT.IsDeuteron() and (q == 1);
                IsTriton = DAndT.IsTriton() and (q == 1);
            }

//             if((IsDeuteron) && (IsTriton))
//             {
//                 IsDeuteron = false;
//                 IsTriton = false;
//             }

//             if((IsKaon) && (IsProtonTPC))
//             {
//                 IsProtonTPC = false;
//             }

//             if((IsPion) && (IsProtonTPC))
//             {
//                 IsProtonTPC = false;
//             }

//             if((IsDeuteron) && (IsProtonTPC))
//             {
//                 IsProtonTPC = false;
//             }

//             if((IsTriton) && (IsProtonTPC))
//             {
//                 IsProtonTPC = false;
//             }
            
//             if((IsProtonToF) && (IsProtonTPC))
//             {
//                 IsProtonTPC = false;
//             }
            


//             //First Pass (Raw values)
//             if(RunIteration == 1)
//             {
//                 if(tofBeta > 0)
//                 {
//                     if(IsProtonToF)
//                     {
//                         Double_t mass = ProtonMass;

//                         Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                         Double_t VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

//                         Bool_t IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                         if(IsGoodProton)
//                         {
//                             HistoD42->Fill(y - yCMShift, VnInnerEPDRaw);
//                         }
//                     }

//                     if(IsKaon)
//                     {
//                         Double_t mass = KaonMass;

//                         Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                         Double_t VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

//                         Bool_t IsGoodKaon = (pt > KaonLowerPt) && (pt < KaonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                         if(IsGoodKaon)
//                         {
//                             if(q > 0)
//                             {
//                                 HistoD45->Fill(y - yCMShift, VnInnerEPDRaw);
//                             }

//                             if(q < 0)
//                             {
//                                 HistoD45A->Fill(y - yCMShift, VnInnerEPDRaw);
//                             }
//                         }
//                     }

//                     else if(IsPion)
//                     {
//                         Double_t mass = PionMass;

//                         Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                         Double_t VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

//                         Bool_t IsGoodPion = (pt > PionLowerPt) && (pt < PionUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                         if(IsGoodPion)
//                         {
//                             if(q > 0)
//                             {
//                                 HistoD48->Fill(y - yCMShift, VnInnerEPDRaw);
//                             }

//                             if(q < 0)
//                             {
//                                 HistoD48A->Fill(y - yCMShift, VnInnerEPDRaw);
//                             }
//                         }
//                      }
            
                    
//                 }

//                 if(IsDeuteron)
//                 {
//                     Double_t mass = DeuteronMass;

//                     Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                     Double_t VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

//                     Bool_t IsGoodDeuteron = (pt > DeuteronLowerPt) && (pt < DeuteronUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                     if(IsGoodDeuteron)
//                     {
//                         HistoD42A->Fill(y - yCMShift, VnInnerEPDRaw);
//                     }
//                 }

//                 else if(IsTriton)
//                 {
//                     Double_t mass = TritonMass;

//                     Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                     Double_t VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

//                     Bool_t IsGoodTriton = (pt > TritonLowerPt) && (pt < TritonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                     if(IsGoodTriton)
//                     {
//                         HistoD42B->Fill(y - yCMShift, VnInnerEPDRaw);
//                     }
//                 }


//                 if(IsProtonTPC)
//                 {
//                     Double_t mass = ProtonMass;

//                     Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                     Double_t VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

//                     Bool_t IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                     if(IsGoodProton)
//                     {
//                         HistoD42->Fill(y - yCMShift, VnInnerEPDRaw);
//                     }
//                 }
//             }
            
            
//             //Second Pass (Recentered values)
//             if(RunIteration == 2)
//             {
//                 if(tofBeta > 0)
//                 {
//                     if(IsProtonToF)
//                     {
//                         Double_t mass = ProtonMass;

//                         Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                         Double_t VnInnerEPDRecentered = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRecentered);

//                         Bool_t IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                         if(IsGoodProton)
//                         {
//                             HistoD43->Fill(y - yCMShift, VnInnerEPDRecentered);
//                         }
//                     }

//                     if(IsKaon)
//                     {
//                         Double_t mass = KaonMass;

//                         Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                         Double_t VnInnerEPDRecentered = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRecentered);

//                         Bool_t IsGoodKaon = (pt > KaonLowerPt) && (pt < KaonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                         if(IsGoodKaon)
//                         {
//                             if(q > 0)
//                             {
//                                 HistoD46->Fill(y - yCMShift, VnInnerEPDRecentered);
//                             }

//                             if(q < 0)
//                             {
//                                 HistoD46A->Fill(y - yCMShift, VnInnerEPDRecentered);
//                             }
//                         }
//                     }

//                     else if(IsPion)
//                     {
//                         Double_t mass = PionMass;

//                         Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                         Double_t VnInnerEPDRecentered = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRecentered);

//                         Bool_t IsGoodPion = (pt > PionLowerPt) && (pt < PionUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                         if(IsGoodPion)
//                         {
//                             if(q > 0)
//                             {
//                                 HistoD49->Fill(y - yCMShift, VnInnerEPDRecentered);
//                             }

//                             if(q < 0)
//                             {
//                                 HistoD49A->Fill(y - yCMShift, VnInnerEPDRecentered);
//                             }
//                         }
//                      }
            
                    
//                 }

//                 if(IsDeuteron)
//                 {
//                     Double_t mass = DeuteronMass;

//                     Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                     Double_t VnInnerEPDRecentered = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRecentered);

//                     Bool_t IsGoodDeuteron = (pt > DeuteronLowerPt) && (pt < DeuteronUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                     if(IsGoodDeuteron)
//                     {
//                         HistoD43A->Fill(y - yCMShift, VnInnerEPDRecentered);
//                     }
//                 }

//                 else if(IsTriton)
//                 {
//                     Double_t mass = TritonMass;

//                     Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                     Double_t VnInnerEPDRecentered = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRecentered);

//                     Bool_t IsGoodTriton = (pt > TritonLowerPt) && (pt < TritonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                     if(IsGoodTriton)
//                     {
//                         HistoD43B->Fill(y - yCMShift, VnInnerEPDRecentered);
//                     }
//                 }


//                 if(IsProtonTPC)
//                 {
//                     Double_t mass = ProtonMass;

//                     Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                     Double_t VnInnerEPDRecentered = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRecentered);

//                     Bool_t IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                     if(IsGoodProton)
//                     {
//                         HistoD43->Fill(y - yCMShift, VnInnerEPDRecentered);
//                     }
//                 }                
//             }
            
            
//             //Third Pass (Fourier Corrected values)
//             if(RunIteration == 3)
//             {
//                 if(tofBeta > 0)
//                 {
//                     if(IsProtonToF)
//                     {
//                         Double_t mass = ProtonMass;

//                         Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                         Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

//                         Bool_t IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                         if(IsGoodProton)
//                         {
//                             HistoD44->Fill(y - yCMShift, VnInnerEPDFourierCorrected);
//                         }
//                     }

//                     if(IsKaon)
//                     {
//                         Double_t mass = KaonMass;

//                         Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                         Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

//                         Bool_t IsGoodKaon = (pt > KaonLowerPt) && (pt < KaonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                         if(IsGoodKaon)
//                         {
//                             if(q > 0)
//                             {
//                                 HistoD47->Fill(y - yCMShift, VnInnerEPDFourierCorrected);
//                             }

//                             if(q < 0)
//                             {
//                                 HistoD47A->Fill(y - yCMShift, VnInnerEPDFourierCorrected);
//                             }
//                         }
//                     }

//                     else if(IsPion)
//                     {
//                         Double_t mass = PionMass;

//                         Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                         Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

//                         Bool_t IsGoodPion = (pt > PionLowerPt) && (pt < PionUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                         if(IsGoodPion)
//                         {
//                             if(q > 0)
//                             {
//                                 HistoD50->Fill(y - yCMShift, VnInnerEPDFourierCorrected);
//                             }

//                             if(q < 0)
//                             {
//                                 HistoD50A->Fill(y - yCMShift, VnInnerEPDFourierCorrected);
//                             }
//                         }
//                      }
            
                    
//                 }

//                 if(IsDeuteron)
//                 {
//                     Double_t mass = DeuteronMass;

//                     Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                     Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

//                     Bool_t IsGoodDeuteron = (pt > DeuteronLowerPt) && (pt < DeuteronUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                     if(IsGoodDeuteron)
//                     {
//                         HistoD44A->Fill(y - yCMShift, VnInnerEPDFourierCorrected);
//                     }
//                 }

//                 else if(IsTriton)
//                 {
//                     Double_t mass = TritonMass;

//                     Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                     Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

//                     Bool_t IsGoodTriton = (pt > TritonLowerPt) && (pt < TritonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                     if(IsGoodTriton)
//                     {
//                         HistoD44B->Fill(y - yCMShift, VnInnerEPDFourierCorrected);
//                     }
//                 }


//                 if(IsProtonTPC)
//                 {
//                     Double_t mass = ProtonMass;

//                     Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                     Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

//                     Bool_t IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                     if(IsGoodProton)
//                     {
//                         HistoD44->Fill(y - yCMShift, VnInnerEPDFourierCorrected);
//                     }
//                 }                
//             }
            
            
            
            
            //Fourth Pass (Resolution Corrected values)
            if(RunIteration == 4)
            {
                if(tofBeta > 0)
                {
                     if(IsProtonToF)
                     {
                         Double_t mass = ProtonMass;

                         Double_t y = FlowFunctions::Y(px, py, pz, mass);

                         Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

                         Bool_t IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                         TH2D *TPCEfficiencyHistogram = (TH2D*)TPCEfficiencyFile->Get("h2_ratio_pr");
                         TH2D *ToFEfficiencyHistogram = (TH2D*)ToFEfficiencyFile->Get("h2_ratio_tof");

                         Int_t TPCEfficiencyBinX = TPCEfficiencyHistogram->GetXaxis()->FindBin(y - yCMShift);
                         Int_t TPCEfficiencyBinY = TPCEfficiencyHistogram->GetYaxis()->FindBin(pt);
                         Int_t ToFEfficiencyBinX = ToFEfficiencyHistogram->GetXaxis()->FindBin(eta);
                         Int_t ToFEfficiencyBinY = ToFEfficiencyHistogram->GetYaxis()->FindBin(pt);

                         Double_t TPCEfficiency = TPCEfficiencyHistogram->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);
                         Double_t ToFEfficiency = ToFEfficiencyHistogram->GetBinContent(ToFEfficiencyBinX, ToFEfficiencyBinY);

                         if((TPCEfficiency <= 0) || (TPCEfficiency > 1.0))
                         {
                             TPCEfficiency = 1;
                         }

                         if(IsGoodProton)
                         {
                             MostlyGoodProtonTrackCheck->Fill(1);

                             HistoD44C->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                             HistoD80->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));

                             if((y - yCMShift) < (UpperYMinusYCMShift / 2))
                             {
                                 GoodProtonTrackCheck->Fill(1);

                                 HistoD54A->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                                 HistoD79->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));

                             }
                         }
                      }
                    
                    if(IsKaon)
                    {
                        Double_t mass = KaonMass;

                        Double_t y = FlowFunctions::Y(px, py, pz, mass);

                        Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

                        Bool_t IsGoodKaon = (pt > KaonLowerPt) && (pt < KaonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                        if(q > 0)
                        {
                            TH2D *TPCEfficiencyHistogram = (TH2D*)TPCEfficiencyFile->Get("h2_ratio_kp");
                            TH2D *ToFEfficiencyHistogram = (TH2D*)ToFEfficiencyFile->Get("h2_ratio_tof");

                            Int_t TPCEfficiencyBinX = TPCEfficiencyHistogram->GetXaxis()->FindBin(y - yCMShift);
                            Int_t TPCEfficiencyBinY = TPCEfficiencyHistogram->GetYaxis()->FindBin(pt);
                            Int_t ToFEfficiencyBinX = ToFEfficiencyHistogram->GetXaxis()->FindBin(eta);
                            Int_t ToFEfficiencyBinY = ToFEfficiencyHistogram->GetYaxis()->FindBin(pt);

                            Double_t TPCEfficiency = TPCEfficiencyHistogram->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);
                            Double_t ToFEfficiency = ToFEfficiencyHistogram->GetBinContent(ToFEfficiencyBinX, ToFEfficiencyBinY);

                            if((TPCEfficiency <= 0) || (TPCEfficiency > 1.0))
                            {
                                TPCEfficiency = 1;
                            }

                            KaonPlusTrackCheck->Fill(1);

                            if(IsGoodKaon)
                            {
                                MostlyGoodKaonPlusTrackCheck->Fill(1);

                                HistoD47B->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                                HistoD82->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));

                                if((y - yCMShift) < (UpperYMinusYCMShift / 2))
                                {
                                    GoodKaonPlusTrackCheck->Fill(1);

                                    HistoD54B->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                                    HistoD81->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                                }
                            }
                        }
                                        
                        else if(q < 0)
                        {
                            TH2D *TPCEfficiencyHistogram = (TH2D*)TPCEfficiencyFile->Get("h2_ratio_km");
                            TH2D *ToFEfficiencyHistogram = (TH2D*)ToFEfficiencyFile->Get("h2_ratio_tof");

                            Int_t TPCEfficiencyBinX = TPCEfficiencyHistogram->GetXaxis()->FindBin(y - yCMShift);
                            Int_t TPCEfficiencyBinY = TPCEfficiencyHistogram->GetYaxis()->FindBin(pt);
                            Int_t ToFEfficiencyBinX = ToFEfficiencyHistogram->GetXaxis()->FindBin(eta);
                            Int_t ToFEfficiencyBinY = ToFEfficiencyHistogram->GetYaxis()->FindBin(pt);

                            Double_t TPCEfficiency = TPCEfficiencyHistogram->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);
                            Double_t ToFEfficiency = ToFEfficiencyHistogram->GetBinContent(ToFEfficiencyBinX, ToFEfficiencyBinY);

                            if((TPCEfficiency <= 0) || (TPCEfficiency > 1.0))
                            {
                                TPCEfficiency = 1;
                            }

                            KaonMinusTrackCheck->Fill(1);

                            if(IsGoodKaon)
                            {
                                MostlyGoodKaonMinusTrackCheck->Fill(1);

                                HistoD47C->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                                HistoD84->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));

                                if((y - yCMShift) < (UpperYMinusYCMShift / 2))
                                {
                                    GoodKaonMinusTrackCheck->Fill(1);

                                    HistoD54C->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                                    HistoD83->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
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
                            TH2D *TPCEfficiencyHistogram = (TH2D*)TPCEfficiencyFile->Get("h2_ratio_pp");
                            TH2D *ToFEfficiencyHistogram = (TH2D*)ToFEfficiencyFile->Get("h2_ratio_tof");

                            Int_t TPCEfficiencyBinX = TPCEfficiencyHistogram->GetXaxis()->FindBin(y - yCMShift);
                            Int_t TPCEfficiencyBinY = TPCEfficiencyHistogram->GetYaxis()->FindBin(pt);
                            Int_t ToFEfficiencyBinX = ToFEfficiencyHistogram->GetXaxis()->FindBin(eta);
                            Int_t ToFEfficiencyBinY = ToFEfficiencyHistogram->GetYaxis()->FindBin(pt);

                            Double_t TPCEfficiency = TPCEfficiencyHistogram->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);
                            Double_t ToFEfficiency = ToFEfficiencyHistogram->GetBinContent(ToFEfficiencyBinX, ToFEfficiencyBinY);

                            if((TPCEfficiency <= 0) || (TPCEfficiency > 1.0))
                            {
                                TPCEfficiency = 1;
                            }

                            PionPlusTrackCheck->Fill(1);

                            if(IsGoodPion)
                            {
                                MostlyGoodPionPlusTrackCheck->Fill(1);

                                HistoD50B->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency)); 
                                HistoD86->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));

                                if((y - yCMShift) < (UpperYMinusYCMShift / 2))
                                {
                                    GoodPionPlusTrackCheck->Fill(1);            

                                    HistoD54D->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                                    HistoD85->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                                }
                            }
                        }
                        
                        else if(q < 0)
                        {
                            TH2D *TPCEfficiencyHistogram = (TH2D*)TPCEfficiencyFile->Get("h2_ratio_pm");
                            TH2D *ToFEfficiencyHistogram = (TH2D*)ToFEfficiencyFile->Get("h2_ratio_tof");

                            Int_t TPCEfficiencyBinX = TPCEfficiencyHistogram->GetXaxis()->FindBin(y - yCMShift);
                            Int_t TPCEfficiencyBinY = TPCEfficiencyHistogram->GetYaxis()->FindBin(pt);
                            Int_t ToFEfficiencyBinX = ToFEfficiencyHistogram->GetXaxis()->FindBin(eta);
                            Int_t ToFEfficiencyBinY = ToFEfficiencyHistogram->GetYaxis()->FindBin(pt);

                            Double_t TPCEfficiency = TPCEfficiencyHistogram->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);
                            Double_t ToFEfficiency = ToFEfficiencyHistogram->GetBinContent(ToFEfficiencyBinX, ToFEfficiencyBinY);

                            if((TPCEfficiency <= 0) || (TPCEfficiency > 1.0))
                            {
                                TPCEfficiency = 1;
                            }

                            PionMinusTrackCheck->Fill(1);

                            if(IsGoodPion)
                            {
                                MostlyGoodPionMinusTrackCheck->Fill(1);

                                HistoD50C->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                                HistoD88->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));

                                if((y - yCMShift) < (UpperYMinusYCMShift / 2))
                                {
                                    GoodPionMinusTrackCheck->Fill(1);

                                    HistoD54E->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                                    HistoD87->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
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

                    TH2D *TPCEfficiencyHistogram = (TH2D*)TPCEfficiencyFileDandT->Get("h2_ratio_de");

                    Int_t TPCEfficiencyBinX = TPCEfficiencyHistogram->GetXaxis()->FindBin(y - yCMShift);
                    Int_t TPCEfficiencyBinY = TPCEfficiencyHistogram->GetYaxis()->FindBin(pt);

                    Double_t TPCEfficiency = TPCEfficiencyHistogram->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);

                    if((TPCEfficiency <= 0) || (TPCEfficiency > 1.0))
                    {
                        TPCEfficiency = 1;
                    }

                    DeuteronTrackCheck->Fill(1);

                    if(IsGoodDeuteron)
                    {
                        MostlyGoodDeuteronTrackCheck->Fill(1);

                        HistoD50D->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                        HistoD88B->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));

                        if((y - yCMShift) < (UpperYMinusYCMShift / 2))
                        {
                            GoodDeuteronTrackCheck->Fill(1);

                            HistoD54F->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                            HistoD88A->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                        }
                    }
                }

                if(IsTriton)
                {
                    Double_t mass = TritonMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                    Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

                    Bool_t IsGoodTriton = (pt > TritonLowerPt) && (pt < TritonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                    TH2D *TPCEfficiencyHistogram = (TH2D*)TPCEfficiencyFileDandT->Get("h2_ratio_tr");

                    Int_t TPCEfficiencyBinX = TPCEfficiencyHistogram->GetXaxis()->FindBin(y - yCMShift);
                    Int_t TPCEfficiencyBinY = TPCEfficiencyHistogram->GetYaxis()->FindBin(pt);

                    Double_t TPCEfficiency = TPCEfficiencyHistogram->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);

                    if((TPCEfficiency <= 0) || (TPCEfficiency > 1.0))
                    {
                        TPCEfficiency = 1;
                    }
                
                    TritonTrackCheck->Fill(1);

                    if(IsGoodTriton)
                    {
                        MostlyGoodTritonTrackCheck->Fill(1);

                        HistoD50E->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                        HistoD88D->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));

                        if((y - yCMShift) < (UpperYMinusYCMShift / 2))
                        {
                            GoodTritonTrackCheck->Fill(1);

                            HistoD54G->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                            HistoD88C->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                        }
                    }
                }







                if(IsProtonTPC)
                {
                    Double_t mass = ProtonMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                    Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

                    Bool_t IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                    TH2D *TPCEfficiencyHistogram = (TH2D*)TPCEfficiencyFile->Get("h2_ratio_pr");

                    Int_t TPCEfficiencyBinX = TPCEfficiencyHistogram->GetXaxis()->FindBin(y - yCMShift);
                    Int_t TPCEfficiencyBinY = TPCEfficiencyHistogram->GetYaxis()->FindBin(pt);

                    Double_t TPCEfficiency = TPCEfficiencyHistogram->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);

                    if((TPCEfficiency <= 0) || (TPCEfficiency > 1.0))
                    {
                        TPCEfficiency = 1;
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
                        
                        }
                    }
                    
                    if((pt > 1.0) && (pt < 2.5) && ((y - yCMShift) > -0.5) && ((y - yCMShift) < 0.5))
                    {
                        VnVsYSymmetricProton->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency));
                    }
                }      
            }       
        }//End Flow Calculator loop 
        
    }//End Event loop
    
    


    //Outputting the Histograms
    if(RunIteration == 1)
    {
        for(int i = 0; i < 7; i++)
        {
            HistoEPDQxRecenterParameter[i]->SetDirectory(0);
            HistoEPDQyRecenterParameter[i]->SetDirectory(0);
        }
        HistoOuterTPCQxRecenterParameter->SetDirectory(0);
        HistoOuterTPCQyRecenterParameter->SetDirectory(0);
        HistoInnerTPCQxRecenterParameter->SetDirectory(0);
        HistoInnerTPCQyRecenterParameter->SetDirectory(0);
        h2_zd_vs_mom->SetDirectory(0);
        h2_zt_vs_mom->SetDirectory(0);
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

        for(int i = 0; i < 7; i++)
        {
            HistoEPDQxRecenterParameter[i]->Write();
            HistoEPDQyRecenterParameter[i]->Write();
        }
        HistoOuterTPCQxRecenterParameter->Write();
        HistoOuterTPCQyRecenterParameter->Write();
        HistoInnerTPCQxRecenterParameter->Write();
        HistoInnerTPCQyRecenterParameter->Write();

        QVectorHistogramRootFile->Close();
        
        
       

        std::string HistogramRootFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramFirstPass" + argv[3] + argv[2] + ".root";
        const char *HistogramRootFileChar = &HistogramRootFileString[0];

        TFile *HistogramRootFile =TFile::Open(HistogramRootFileChar, "RECREATE");
        HistogramRootFile->cd();

        h2_zd_vs_mom->Write();
        h2_zt_vs_mom->Write();
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
    
    
    if(RunIteration == 2)
    {  
        for(int i = 0; i < 7; i++)
        {
            HistoEPDShiftParameterCosine[i]->SetDirectory(0);
            HistoEPDShiftParameterSine[i]->SetDirectory(0);
        }
        HistoInnerTPCShiftParameterCosine->SetDirectory(0);
        HistoInnerTPCShiftParameterSine->SetDirectory(0);
        HistoOuterTPCShiftParameterCosine->SetDirectory(0);
        HistoOuterTPCShiftParameterSine->SetDirectory(0);
        HistoD34->SetDirectory(0);
        HistoD37->SetDirectory(0);
        HistoD40->SetDirectory(0);
        HistoD43->SetDirectory(0);
        HistoD43A->SetDirectory(0);
        HistoD43B->SetDirectory(0);
        HistoD46->SetDirectory(0);
        HistoD46A->SetDirectory(0);
        HistoD49->SetDirectory(0);
        HistoD49A->SetDirectory(0);
        
        
        
        std::string QVectorHistogramFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/QVectorSecondPass" + argv[3] + argv[2] +".root";
        const char *QVectorHistogramFileChar = &QVectorHistogramFileString[0];        

        TFile *QVectorHistogramRootFile = TFile::Open(QVectorHistogramFileChar, "RECREATE");
        QVectorHistogramRootFile->cd();

        for(int i = 0; i < 7; i++)
        {
            HistoEPDShiftParameterCosine[i]->Write();
            HistoEPDShiftParameterSine[i]->Write();
        }
        HistoInnerTPCShiftParameterCosine->Write();
        HistoInnerTPCShiftParameterSine->Write();
        HistoOuterTPCShiftParameterCosine->Write();
        HistoOuterTPCShiftParameterSine->Write();

        QVectorHistogramRootFile->Close();

            
            


        std::string HistogramRootFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramSecondPass" + argv[3] + argv[2] + ".root";
        const char *HistogramRootFileChar = &HistogramRootFileString[0];
        
        TFile *HistogramRootFile = TFile::Open(HistogramRootFileChar, "RECREATE");
        HistogramRootFile->cd();
        
        HistoD34->Write();
        HistoD37->Write();
        HistoD40->Write();
        HistoD43->Write();
        HistoD43A->Write();
        HistoD43B->Write();
        HistoD46->Write();
        HistoD46A->Write();
        HistoD49->Write();
        HistoD49A->Write();

        HistogramRootFile->Close();
    }
    
    
    
    if(RunIteration == 3)
    {
        for(int ModifiedCentrality = 0; ModifiedCentrality < 10; ModifiedCentrality++)
        {
            InnerTPCRawEP[ModifiedCentrality]->SetDirectory(0);
            OuterTPCRawEP[ModifiedCentrality]->SetDirectory(0);
            InnerTPCRecenteredEP[ModifiedCentrality]->SetDirectory(0);
            OuterTPCRecenteredEP[ModifiedCentrality]->SetDirectory(0);
            InnerTPCShiftedEP[ModifiedCentrality]->SetDirectory(0);
            OuterTPCShiftedEP[ModifiedCentrality]->SetDirectory(0);
            for(int i=0; i<7; i++)
            {
                EPDRawEP[ModifiedCentrality][i]->SetDirectory(0);
                EPDRecenteredEP[ModifiedCentrality][i]->SetDirectory(0);
                EPDShiftedEP[ModifiedCentrality][i]->SetDirectory(0);
            }
        }
        HistoD35->SetDirectory(0);
        HistoD38->SetDirectory(0);
        HistoD41->SetDirectory(0);
        HistoD44->SetDirectory(0);
        HistoD44A->SetDirectory(0);
        HistoD44B->SetDirectory(0);
        HistoD47->SetDirectory(0);
        HistoD47A->SetDirectory(0);
        HistoD50->SetDirectory(0);
        HistoD50A->SetDirectory(0);
        HistoD51->SetDirectory(0);
        HistoD52->SetDirectory(0);
        HistoD53->SetDirectory(0);
                    
            


        std::string HistogramRootFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramThirdPass" + argv[3] + argv[2] + ".root";
        const char *HistogramRootFileChar = &HistogramRootFileString[0];
        
        TFile *HistogramRootFile = TFile::Open(HistogramRootFileChar, "RECREATE");
        HistogramRootFile->cd();

        
        for(int ModifiedCentrality = 0; ModifiedCentrality < 10; ModifiedCentrality++)
        {
            InnerTPCRawEP[ModifiedCentrality]->Write();
            OuterTPCRawEP[ModifiedCentrality]->Write();
            InnerTPCRecenteredEP[ModifiedCentrality]->Write();
            OuterTPCRecenteredEP[ModifiedCentrality]->Write();
            InnerTPCShiftedEP[ModifiedCentrality]->Write();
            OuterTPCShiftedEP[ModifiedCentrality]->Write();
            for(int i=0; i<7; i++)
            {
                EPDRawEP[ModifiedCentrality][i]->Write();
                EPDRecenteredEP[ModifiedCentrality][i]->Write();
                EPDShiftedEP[ModifiedCentrality][i]->Write();
            }
        }
        HistoD35->Write();
        HistoD38->Write();
        HistoD41->Write();
        HistoD44->Write();
        HistoD44A->Write();
        HistoD44B->Write();
        HistoD47->Write();
        HistoD47A->Write();
        HistoD50->Write();
        HistoD50A->Write();
        HistoD51->Write();
        HistoD52->Write();
        HistoD53->Write();

        HistogramRootFile->Close();
    }
    
    
    
    if(RunIteration == 4)
    {
        std::string YAxisString = "V" + std::to_string(nV) +"";
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
        
        
        
        TProfile *HistoD89 = (TProfile*)HistoD79->ProfileY(HistoD89Char, 1, 2);
        HistoD89->SetXTitle("Pt");
        HistoD89->SetYTitle(YAxisChar);
        TProfile *HistoD90 = (TProfile*)HistoD79->ProfileY(HistoD90Char, 3, 8);
        HistoD90->SetXTitle("Pt");
        HistoD90->SetYTitle(YAxisChar);
        TProfile *HistoD91 = (TProfile*)HistoD79->ProfileY(HistoD91Char, 9, 12);
        HistoD91->SetXTitle("Pt");
        HistoD91->SetYTitle(YAxisChar);
        TProfile *HistoD92 = (TProfile*)HistoD80->ProfileY(HistoD92Char, 1, 2);
        HistoD92->SetXTitle("y_{CM}");
        HistoD92->SetYTitle(YAxisChar);
        TProfile *HistoD93 = (TProfile*)HistoD80->ProfileY(HistoD93Char, 3, 8);
        HistoD93->SetXTitle("y_{CM}");
        HistoD93->SetYTitle(YAxisChar);
        TProfile *HistoD94 = (TProfile*)HistoD80->ProfileY(HistoD94Char, 9, 12);
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


        TProfile *HistoD95 = (TProfile*)HistoD81->ProfileY(HistoD95Char, 1, 2);
        HistoD95->SetXTitle("Pt");
        HistoD95->SetYTitle(YAxisChar);
        TProfile *HistoD96 = (TProfile*)HistoD81->ProfileY(HistoD96Char, 3, 8);
        HistoD96->SetXTitle("Pt");
        HistoD96->SetYTitle(YAxisChar);
        TProfile *HistoD97 = (TProfile*)HistoD81->ProfileY(HistoD97Char, 9, 12);
        HistoD97->SetXTitle("Pt");
        HistoD97->SetYTitle(YAxisChar);
        TProfile *HistoD98 = (TProfile*)HistoD82->ProfileY(HistoD98Char, 1, 2);
        HistoD98->SetXTitle("y_{CM}");
        HistoD98->SetYTitle(YAxisChar);
        TProfile *HistoD99 = (TProfile*)HistoD82->ProfileY(HistoD99Char, 3, 8);
        HistoD99->SetXTitle("y_{CM}");
        HistoD99->SetYTitle(YAxisChar);
        TProfile *HistoD100 = (TProfile*)HistoD82->ProfileY(HistoD100Char, 9, 12);
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
        


        TProfile *HistoD101 = (TProfile*)HistoD83->ProfileY(HistoD101Char, 1, 2);
        HistoD101->SetXTitle("Pt");
        HistoD101->SetYTitle(YAxisChar);
        TProfile *HistoD102 = (TProfile*)HistoD83->ProfileY(HistoD102Char, 3, 8);
        HistoD102->SetXTitle("Pt");
        HistoD102->SetYTitle(YAxisChar);
        TProfile *HistoD103 = (TProfile*)HistoD83->ProfileY(HistoD103Char, 9, 12);
        HistoD103->SetXTitle("Pt");
        HistoD103->SetYTitle(YAxisChar);
        TProfile *HistoD104 = (TProfile*)HistoD84->ProfileY(HistoD104Char, 1, 2);
        HistoD104->SetXTitle("y_{CM}");
        HistoD104->SetYTitle(YAxisChar);
        TProfile *HistoD105 = (TProfile*)HistoD84->ProfileY(HistoD105Char, 3, 8);
        HistoD105->SetXTitle("y_{CM}");
        HistoD105->SetYTitle(YAxisChar);
        TProfile *HistoD106 = (TProfile*)HistoD84->ProfileY(HistoD106Char, 9, 12);
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

        TProfile *HistoD107 = (TProfile*)HistoD85->ProfileY(HistoD107Char, 1, 2);
        HistoD107->SetXTitle("Pt");
        HistoD107->SetYTitle(YAxisChar);
        TProfile *HistoD108 = (TProfile*)HistoD85->ProfileY(HistoD108Char, 3, 8);
        HistoD108->SetXTitle("Pt");
        HistoD108->SetYTitle(YAxisChar);
        TProfile *HistoD109 = (TProfile*)HistoD85->ProfileY(HistoD109Char, 9, 12);
        HistoD109->SetXTitle("Pt");
        HistoD109->SetYTitle(YAxisChar);
        TProfile *HistoD110 = (TProfile*)HistoD86->ProfileY(HistoD110Char, 1, 2);
        HistoD110->SetXTitle("y_{CM}");
        HistoD110->SetYTitle(YAxisChar);
        TProfile *HistoD111 = (TProfile*)HistoD86->ProfileY(HistoD111Char, 3, 8);
        HistoD111->SetXTitle("y_{CM}");
        HistoD111->SetYTitle(YAxisChar);
        TProfile *HistoD112 = (TProfile*)HistoD86->ProfileY(HistoD112Char, 9, 12);
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
        


        TProfile *HistoD113 = (TProfile*)HistoD87->ProfileY(HistoD113Char, 1, 2);
        HistoD113->SetXTitle("Pt");
        HistoD113->SetYTitle(YAxisChar);
        TProfile *HistoD114 = (TProfile*)HistoD87->ProfileY(HistoD114Char, 3, 8);
        HistoD114->SetXTitle("Pt");
        HistoD114->SetYTitle(YAxisChar);
        TProfile *HistoD115 = (TProfile*)HistoD87->ProfileY(HistoD115Char, 9, 12);
        HistoD115->SetXTitle("Pt");
        HistoD115->SetYTitle(YAxisChar);
        TProfile *HistoD116 = (TProfile*)HistoD88->ProfileY(HistoD116Char, 1, 2);
        HistoD116->SetXTitle("y_{CM}");
        HistoD116->SetYTitle(YAxisChar);
        TProfile *HistoD117 = (TProfile*)HistoD88->ProfileY(HistoD117Char, 3, 8);
        HistoD117->SetXTitle("y_{CM}");
        HistoD117->SetYTitle(YAxisChar);
        TProfile *HistoD118 = (TProfile*)HistoD88->ProfileY(HistoD118Char, 9, 12);
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


        TProfile *HistoD119 = (TProfile*)HistoD88A->ProfileY(HistoD119Char, 1, 2);
        HistoD119->SetXTitle("Pt");
        HistoD119->SetYTitle(YAxisChar);
        TProfile *HistoD120 = (TProfile*)HistoD88A->ProfileY(HistoD120Char, 3, 8);
        HistoD120->SetXTitle("Pt");
        HistoD120->SetYTitle(YAxisChar);
        TProfile *HistoD121 = (TProfile*)HistoD88A->ProfileY(HistoD121Char, 9, 12);
        HistoD121->SetXTitle("Pt");
        HistoD121->SetYTitle(YAxisChar);
        TProfile *HistoD122 = (TProfile*)HistoD88B->ProfileY(HistoD122Char, 1, 2);
        HistoD122->SetXTitle("y_{CM}");
        HistoD122->SetYTitle(YAxisChar);
        TProfile *HistoD123 = (TProfile*)HistoD88B->ProfileY(HistoD123Char, 3, 8);
        HistoD123->SetXTitle("y_{CM}");
        HistoD123->SetYTitle(YAxisChar);
        TProfile *HistoD124 = (TProfile*)HistoD88B->ProfileY(HistoD124Char, 9, 12);
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


        TProfile *HistoD125 = (TProfile*)HistoD88C->ProfileY(HistoD125Char, 1, 2);
        HistoD125->SetXTitle("Pt");
        HistoD125->SetYTitle(YAxisChar);
        TProfile *HistoD126 = (TProfile*)HistoD88C->ProfileY(HistoD126Char, 3, 8);
        HistoD126->SetXTitle("Pt");
        HistoD126->SetYTitle(YAxisChar);
        TProfile *HistoD127 = (TProfile*)HistoD88C->ProfileY(HistoD127Char, 9, 12);
        HistoD127->SetXTitle("Pt");
        HistoD127->SetYTitle(YAxisChar);
        TProfile *HistoD128 = (TProfile*)HistoD88D->ProfileY(HistoD128Char, 1, 2);
        HistoD128->SetXTitle("y_{CM}");
        HistoD128->SetYTitle(YAxisChar);
        TProfile *HistoD129 = (TProfile*)HistoD88D->ProfileY(HistoD129Char, 3, 8);
        HistoD129->SetXTitle("y_{CM}");
        HistoD129->SetYTitle(YAxisChar);
        TProfile *HistoD130 = (TProfile*)HistoD88D->ProfileY(HistoD130Char, 9, 12);
        HistoD130->SetXTitle("y_{CM}");
        HistoD130->SetYTitle(YAxisChar);
        
        
        
        
        std::string VnVsYSymmetricProtonCentrality0_10String = "DataVnVsYSymmetricForProtonsCentrality0-10";
        const char* VnVsYSymmetricProtonCentrality0_10Char = &VnVsYSymmetricProtonCentrality0_10String[0];
        
        std::string VnVsYSymmetricProtonCentrality10_40String = "DataVnVsYSymmetricForProtonsCentrality10-40";
        const char* VnVsYSymmetricProtonCentrality10_40Char = &VnVsYSymmetricProtonCentrality10_40String[0];
        
        std::string VnVsYSymmetricProtonCentrality40_60String = "DataVnVsYSymmetricForProtonsCentrality40-60";
        const char* VnVsYSymmetricProtonCentrality40_60Char = &VnVsYSymmetricProtonCentrality40_60String[0]; 


        TProfile *VnVsYSymmetricProtonCentrality0_10 = (TProfile*)VnVsYSymmetricProton->ProfileY(VnVsYSymmetricProtonCentrality0_10Char, 1, 2);
        VnVsYSymmetricProtonCentrality0_10->SetXTitle("Y_{CM}");
        VnVsYSymmetricProtonCentrality0_10->SetYTitle(YAxisChar);
        TProfile *VnVsYSymmetricProtonCentrality10_40 = (TProfile*)VnVsYSymmetricProton->ProfileY(VnVsYSymmetricProtonCentrality10_40Char, 3, 8);
        VnVsYSymmetricProtonCentrality10_40->SetXTitle("Y_{CM}");
        VnVsYSymmetricProtonCentrality10_40->SetYTitle(YAxisChar);
        TProfile *VnVsYSymmetricProtonCentrality40_60 = (TProfile*)VnVsYSymmetricProton->ProfileY(VnVsYSymmetricProtonCentrality40_60Char, 9, 12);
        VnVsYSymmetricProtonCentrality40_60->SetXTitle("Y_{CM}");
        VnVsYSymmetricProtonCentrality40_60->SetYTitle(YAxisChar);  
        
        
        
        
        
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
        VnVsYSymmetricProton->SetDirectory(0);
        VnVsYSymmetricProtonCentrality0_10->SetDirectory(0);
        VnVsYSymmetricProtonCentrality10_40->SetDirectory(0);
        VnVsYSymmetricProtonCentrality40_60->SetDirectory(0);

        
        std::string HistogramRootFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramFourthPass" + argv[3] + argv[2] + ".root";
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
        VnVsYSymmetricProton->Write();
        VnVsYSymmetricProtonCentrality0_10->Write();
        VnVsYSymmetricProtonCentrality10_40->Write();
        VnVsYSymmetricProtonCentrality40_60->Write();
        
 
            

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
    }

    Data->Close();

    delete BichselZDeuteron;
    delete BichselZTriton;

    if(RunIteration == 1)
    {
        delete h2_zd_vs_mom;
        delete h2_zt_vs_mom;
        delete HistoInnerTPCQxRecenterParameter;
        delete HistoInnerTPCQyRecenterParameter;
        delete HistoOuterTPCQxRecenterParameter;
        delete HistoOuterTPCQyRecenterParameter;
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
    }
   
    

    if(RunIteration == 2)
    {
        delete HistoInnerTPCShiftParameterCosine;
        delete HistoInnerTPCShiftParameterSine;
        delete HistoOuterTPCShiftParameterCosine;
        delete HistoOuterTPCShiftParameterSine;
        delete HistoD34;
        delete HistoD37;
        delete HistoD40;
        delete HistoD43;
        delete HistoD43A;
        delete HistoD43B;
        delete HistoD46;
        delete HistoD46A;
        delete HistoD49;
        delete HistoD49A;
    }
  
    
    if(RunIteration == 3)
    {
        delete HistoD35;
        delete HistoD38;
        delete HistoD41;
        delete HistoD44;
        delete HistoD44A;
        delete HistoD44B;
        delete HistoD47;
        delete HistoD47A;
        delete HistoD50;
        delete HistoD50A;
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
    }


    std::cout << "DONE" << std::endl;
           
    return(0);
    
}//End main()
