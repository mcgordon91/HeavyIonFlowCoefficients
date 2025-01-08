//Author: Michael Gordon
//Date: 2-20-24



#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
    const Int_t nV = 3;

    
    
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
    
    Int_t InnerEPDHighRing = 8;
    Int_t OuterEPDLowRing = 9;
    
    
    
    //double ProtonLowerMSquared = 0.6;
    //double ProtonUpperMSquared = 1.2;
    Double_t KaonLowerMSquared = 0.15;
    Double_t KaonUpperMSquared = 0.34;
    Double_t PionLowerMSquared = -0.1;
    Double_t PionUpperMSquared = 0.1;
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
    Double_t DeuteronUpperPt = 4.0;
    Double_t TritonLowerPt = 1.2;
    Double_t TritonUpperPt = 6.0;
    Double_t LowerYMinusYCMShift = 0.0;
    Double_t UpperYMinusYCMShift = 1.0;



    Int_t QBounds = 100;
    Int_t FourierCorrectionTerms = 10;


    const char* CentralityXLabels[16] = {"0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60", "60-65", "65-70", "70-75", "75-80"};
    
    // Parameter changes for systematic runs
    if (std::string(argv[3]) == "Normal")
    {
        QBounds = 100;
        FourierCorrectionTerms = 10;
    }
    if (std::string(argv[3]) == "RVertex20Low")
    {
        RVertexBound = 1.2;
    }
    if (std::string(argv[3]) == "RVertex30Low")
    {
        RVertexBound = 1.05;
    }
    if (std::string(argv[3]) == "RVertex20High")
    {
        RVertexBound = 1.8;
    }
    if(std::string(argv[3]) == "RVertex30High")
    {
        RVertexBound = 1.95;
    }
    if (std::string(argv[3]) == "ZVertex20Low")
    {
        ZVertexLowerBound = 198.4;
        ZVertexUpperBound = 201.6;
    }
    if (std::string(argv[3]) == "ZVertex20High")
    {
        ZVertexLowerBound = 197.6;
        ZVertexUpperBound = 202.4;
    }
    if (std::string(argv[3]) == "ZVertex30Low")
    {
        ZVertexLowerBound = 198.6;
        ZVertexUpperBound = 201.4;
    }
    if (std::string(argv[3]) == "ZVertex30High")
    {
        ZVertexLowerBound = 197.4;
        ZVertexUpperBound = 202.6;
    }
    if (std::string(argv[3]) == "DCA20Low")
    {
        DCABound = 2.4;
    }
    if (std::string(argv[3]) == "DCA20High")
    {
        DCABound = 3.6;
    }
    if (std::string(argv[3]) == "DCA30Low")
    {
        DCABound = 2.1;
    }
    if (std::string(argv[3]) == "DCA30High")
    {
        DCABound = 3.9;
    }
    if (std::string(argv[3]) == "NHits20Low")
    {
        NHitsBound = 12;
    }
    if (std::string(argv[3]) == "NHits20High")
    {
        NHitsBound = 18;
    }
    if (std::string(argv[3]) == "NHits30Low")
    {
        NHitsBound = 10;
    }
    if (std::string(argv[3]) == "NHits30High")
    {
        NHitsBound = 20;
    }
    if (std::string(argv[3]) == "NHitsdEdx20High")
    {
        NHitsdEdxBound = 9;
    }
    if (std::string(argv[3]) == "NHitsdEdx30High")
    {
        NHitsdEdxBound = 12;
    }
    if (std::string(argv[3]) == "NHitsFitOverNHitsPoss20Low")
    {
        NHitsFitOverNHitsPossBound = 0.416;
    }
    if (std::string(argv[3]) == "NHitsFitOverNHitsPoss20High")
    {
        NHitsFitOverNHitsPossBound = 0.624;
    }
    if (std::string(argv[3]) == "NHitsFitOverNHitsPoss30Low")
    {
        NHitsFitOverNHitsPossBound = 0.364;
    }
    if (std::string(argv[3]) == "NHitsFitOverNHitsPoss30High")
    {
        NHitsFitOverNHitsPossBound = 0.676;
    }
    if (std::string(argv[3]) == "NSigmaPion20Low")
    {
        NSigmaPiBound = 2.4;
    }
    if (std::string(argv[3]) == "NSigmaPion20High")
    {
        NSigmaPiBound = 3.6;
    }
    if (std::string(argv[3]) == "NSigmaPion30Low")
    {
        NSigmaPiBound = 2.1;
    }
    if (std::string(argv[3]) == "NSigmaPion30High")
    {
        NSigmaPiBound = 3.9;
    }
    if (std::string(argv[3]) == "NSigmaKaon20Low")
    {
        NSigmaKaBound = 2.4;
    }
    if (std::string(argv[3]) == "NSigmaKaon20High")
    {
        NSigmaKaBound = 3.6;
    }
    if (std::string(argv[3]) == "NSigmaKaon30Low")
    {
        NSigmaKaBound = 2.1;
    }
    if (std::string(argv[3]) == "NSigmaKaon30High")
    {
        NSigmaKaBound = 3.9;
    }
    if (std::string(argv[3]) == "NSigmaProton20Low")
    {
        NSigmaPrBound = 1.6;
    }
    if (std::string(argv[3]) == "NSigmaProton20High")
    {
        NSigmaPrBound = 2.4;
    }
    if (std::string(argv[3]) == "NSigmaProton30Low")
    {
        NSigmaPrBound = 1.4;
    }
    if (std::string(argv[3]) == "NSigmaProton30High")
    {
        NSigmaPrBound = 2.6;
    }
    if (std::string(argv[3]) == "MSquaredPion20Low")
    {
        PionLowerMSquared = -0.08;
        PionUpperMSquared = 0.08;
    }
    if (std::string(argv[3]) == "MSquaredPion20High")
    {
        PionLowerMSquared = -0.12;
        PionUpperMSquared = 0.12;
    }
    if (std::string(argv[3]) == "MSquaredPion30Low")
    {
        PionLowerMSquared = -0.07;
        PionUpperMSquared = 0.07;
    }
    if (std::string(argv[3]) == "MSquaredPion30High")
    {
        PionLowerMSquared = -0.13;
        PionUpperMSquared = 0.13;
    }
    if (std::string(argv[3]) == "MSquaredKaon20Low")
    {
        KaonLowerMSquared = 0.169;
        KaonUpperMSquared = 0.321;
    }
    if (std::string(argv[3]) == "MSquaredKaon20High")
    {
        KaonLowerMSquared = 0.131;
        KaonUpperMSquared = 0.359;
    }
    if (std::string(argv[3]) == "MSquaredKaon30Low")
    {
        KaonLowerMSquared = 0.1785;
        KaonUpperMSquared = 0.3115;
    }
    if (std::string(argv[3]) == "MSquaredKaon30High")
    {
        KaonLowerMSquared = 0.1215;
        KaonUpperMSquared = 0.3685;
    }
    if (std::string(argv[3]) == "OuterEPDLow")
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
    if (std::string(argv[3]) == "OuterEPDHigh")
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
//     else
//     {
//         std::cout << "No Matching Systematic Error type (or Normal)" << std::endl;
//         exit(0);
//     }

//     std::cout << RVertexBound << std::endl;
//     std::cout << ZVertexLowerBound << std::endl;
//     std::cout << ZVertexUpperBound << std::endl;
//     std::cout << DCABound << std::endl;



//     std::cout << NHitsBound << std::endl;
//     std::cout << NHitsdEdxBound << std::endl;
//     std::cout << NHitsFitOverNHitsPossBound << std::endl;
//     std::cout << InnerEPDHighRing << std::endl;
//     std::cout << OuterEPDLowRing << std::endl;
//     std::cout << KaonLowerMSquared << std::endl;
//     std::cout << KaonUpperMSquared << std::endl;
//     std::cout << PionLowerMSquared << std::endl;
//     std::cout << PionUpperMSquared << std::endl;
//     std::cout << NSigmaPrBound << std::endl;
//     std::cout << NSigmaKaBound << std::endl;
//     std::cout << NSigmaPiBound << std::endl;

    
    //Input files
    TFile *Data = TFile::Open(argv[1]);
    
    TFile *QVectorHistogramFileFirst;
    TFile *QVectorHistogramFileSecond;
    TFile *ResolutionFile;
    TFile *TPCEfficiencyFile;
    TFile *ToFEfficiencyFile;
    TFile *TPCEfficiencyFileDandT;
//     TH1D *HistoD54;
    
    
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
        
//         std::string ResolutionFileString = "/star/u/mcgordon/SystematicsCameronResolution/resolutionInfo_INPUT_epd_low.root";
//         const char* ResolutionFileChar = &ResolutionFileString[0];
    
//         ResolutionFile = TFile::Open(ResolutionFileChar, "READ");
        
//         TH1D *ResolutionPlot = (TH1D*)ResolutionFile->Get("h_resolutions");

//         HistoD54 = new TH1D("ResolutionRescaledAverage", " ; ; ", 12, 0, 12);

//         for (int index = 0; index < ResolutionPlot->GetNbinsX() + 1; index++)
//         {
//             HistoD54->SetBinContent(17 - index, ResolutionPlot->GetBinContent(index));
//             HistoD54->SetBinError(17 - index, ResolutionPlot->GetBinError(index));
//         }

        TPCEfficiencyFile = TFile::Open("/star/u/mcgordon/VnFromEPD/Efficiencies/TPCEfficiency.root","READ");
        ToFEfficiencyFile = TFile::Open("/star/u/mcgordon/VnFromEPD/Efficiencies/ToFEfficiency.root","READ");
        TPCEfficiencyFileDandT = TFile::Open("/star/u/mcgordon/VnFromEPD/Efficiencies/TPCEfficiencyDandT.root","READ");
    }
    

    
    Double_t InnerEPDQxMean = 0;
    Double_t InnerEPDQyMean = 0;
    Double_t OuterEPDQxMean = 0;
    Double_t OuterEPDQyMean = 0;
    Double_t OuterTPCQxMean = 0;
    Double_t OuterTPCQyMean = 0;
        
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

    TProfile *InnerEPDSineAverageProfile;
    TProfile *InnerEPDCosineAverageProfile;
    TProfile *OuterEPDSineAverageProfile;
    TProfile *OuterEPDCosineAverageProfile;
    TProfile *OuterTPCSineAverageProfile;
    TProfile *OuterTPCCosineAverageProfile;
    
    if(RunIteration >= 3)
    {
        InnerEPDSineAverageProfile = (TProfile*)QVectorHistogramFileSecond->Get("InnerEPDSineAverages");
        InnerEPDCosineAverageProfile = (TProfile*)QVectorHistogramFileSecond->Get("InnerEPDCosineAverages");
        OuterEPDSineAverageProfile = (TProfile*)QVectorHistogramFileSecond->Get("OuterEPDSineAverages");
        OuterEPDCosineAverageProfile = (TProfile*)QVectorHistogramFileSecond->Get("OuterEPDCosineAverages");
        OuterTPCSineAverageProfile = (TProfile*)QVectorHistogramFileSecond->Get("OuterTPCSineAverages");
        OuterTPCCosineAverageProfile = (TProfile*)QVectorHistogramFileSecond->Get("OuterTPCCosineAverages");
    }
    

                
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

    
//     std::cout << Data->ls() << std::endl;

//     std::cout << AutreeData->Print() << std::endl;   
    

    
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
    
    
    TH1D *ZVertexValues = new TH1D("ZVertexValues", "ZVertex Values; Z Vertex (cm); Events", 120, 197, 203);
    ZVertexValues->Sumw2();
    
    TH1D *RVertexValues = new TH1D("RVertexValues", "RVertex Values; R Vertex (cm); Events", 120, 0, 5);
    RVertexValues->Sumw2();
    
    TH1D *DCAValues = new TH1D("DCAValues", "DCA Values; DCA (cm); Tracks", 80, 0, 4);
    DCAValues->Sumw2();
    
    TH1D *NHitsValues = new TH1D("NHitsValues", "NHits Values; NHits; Tracks", 100, 0, 100);
    NHitsValues->Sumw2();
    
    TH1D *NHitsdEdxValues = new TH1D("NHitsdEdxValues", "NHitsdEdx Values; NHitsdEdx; Tracks", 90, 5, 100);
    NHitsdEdxValues->Sumw2();
    
    TH1D *NHitsFitOverNHitsPossValues = new TH1D("NHitsFitOverNHitsPossValues", "NHitsFitOverNHitsPoss Values; NHitsFitOverNHitsPoss; Tracks", 70, 0.3, 1);
    NHitsFitOverNHitsPossValues->Sumw2();
    

    
    std::vector<int> RunIDs {0, 79020,79021,79022,78002,78003,78004,78005,78006,78007,78008,78009,78010,78011,78012,78013,77002,77003,77004,77005,77006,77007,77008,77012,77013,77014,76001,76002,76003,76004,76005,76006,76007,76008,76009,76011,76012,75001,75002,75003,75004,75005,75006,75007,75008,75010,75011,75013,75031,75032,74002,74003,74004,74005,74006,74007,74010,74011,74012,74013,74014,74018,74019,74046,74047,74048,74049,74050,74054,74055,74056,74057,74058,74059,74060,74061,74062,73001,73002,73003,73004,73005,73006,73009,73010,73011,73012,73013,73014,73015,73016,73017,73018,73019,73020,73023,73024,73025,73026,73027,73028,73029,73030,73031,73032,73033,73034,73035,72001,72002,72003,72004,72005,72006,72007,72008,72009,72010,72022,72024,72025,71021,71022,71023,71024,71025,71026,71027,71028,71029,71030,71031,71032,71033,70001,70002,70003,70004,70005,70006,70007,70008,70009,70014,70015,70016,70017,70018,70019,70020,70021,70022,69001,69002,69003,69004,69005,69006,69007,69008,69009,69010,69011,69018,69022,69023,68003,68004,68005,68006,68007,68008,68009,68010,68015,67001,67002,67003,67004,67005,67006,67007,67008,67009,67010,67011,67012,67016,67017,67021,67022,67023,67024,67025,67027,67028,67029,66001,66002,66003,66004,66005,66006,66009,66010,66013,66014,66015,66016,66017,66018,66019,66020,66023,66024,66026,66028,66029,66030,66031,66034,66035,66036,66037,66038,66039,65001,65002,65003,65004,65005,65006,65007,65008,65009,65010,65012,65013,65014,65015,65016,65017,65018,65019,65021,65024,65025,65026,65027,65028,65029,65031,65032,65033,65034,65035,64001,64002,64003,64004,64005,64006,64007,64008,64009,64010,64011,64012,64013,64014,64015,64016,64017,64018,64019,64022,64024,64025,64026,64027,64028,64029,64030,64031,64032,64033,63002,63003,63004,63005,63006,63007,63008,63009,63010,63011,63012,63013,63014,63015,63016,63017,63018,63019,63020,63026,63027,63028,63029,63030,63031,63032,63034,63035,63036,62001,62003,62006,62007,62008,62009,62015,62018,62019,62021,62022,62023,61001,61002,61003,61004,61005,61006,61009,61010,61012,61013,61014,61015,61016,61018,61019,61020,61023,61024,61025,61026,61027,61028,61029,61030,61031,61032,61033,60001,60002,60003,60004,60005,60006,60007,60008,60009,60010,60011,60012,60013,60014,60015,60016,60017,60018,60019,60020,60021,60022,60024,60025,60026,60027,60028,60029,60030,60031,60032,60046,60047,60048,60049,60050,60051,60052,60053,59001,59003,59008,59009,59010,59011,59012,59013,59015,59051,59052,59053,58032,58033,58036,25001,25002,25003,25004,25005,25006,25007,25008,25009,25010,25011,24002,24003,24004,24005,24006,24007,24008,24011,24012,24013,24014,24018,24027,24028,24031,23001,23002,23003,23004,23005,23006,23007,23008,23009,23010,23011,23012,23013,23014,23015,23016,23017,23018,23020,23021,23025,23026,23027,23028,23030,23031,23032,23034,23035,23037,23038,23040,23041,22001,22002,22003,22004,22005,22006,22007,22008,22009,22010,22011,22014,22016,22017,22018,22019,22020,22021,22024,22025,22026,22027,22028,22029,22031,22032,22034,22035,21033,21036,21037,21038,21039,21040,21041,21044,21045,21046,21048,21049,21050,21052,21053};
   
    int RunIndex;
 
    
    TProfile *pVx = new TProfile("pVx", "Vx for Primary Tracks; Run Index; <Vx>", 509, 1, 510);
    pVx->Sumw2();
    
    TProfile *pVy = new TProfile("pVy", "Vy for Primary Tracks; Run Index; <Vy>", 509, 1, 510);
    pVy->Sumw2();
    
    TProfile *pVz = new TProfile("pVz", "Vz for Primary Tracks; Run Index; <Vz>", 509, 1, 510);
    pVz->Sumw2();
    
    TProfile *pPt = new TProfile("pPt", "Pt for Primary Tracks; Run Index; <Pt> (GeV)", 509, 1, 510);
    pPt->Sumw2();
    
    TProfile *pEta = new TProfile("pEta", "Eta for Primary Tracks; Run Index; <Eta>", 509, 1, 510);
    pEta->Sumw2();
    
    TProfile *pQxEPDA = new TProfile("pQxEPDA", "Qx for EPDA for Primary Tracks; Run Index; <Qx>", 509, 1, 510);
    pQxEPDA->Sumw2();
    
    TProfile *pQyEPDA = new TProfile("pQyEPDA", "Qy for EPDA for Primary Tracks; Run Index; <Qy>", 509, 1, 510);
    pQyEPDA->Sumw2();
    
    TProfile *pQxEPDB = new TProfile("pQxEPDB", "Qx for EPDB for Primary Tracks; Run Index; <Qx>", 509, 1, 510);
    pQxEPDB->Sumw2();
    
    TProfile *pQyEPDB = new TProfile("pQyEPDB", "Qy for EPDB for Primary Tracks; Run Index; <Qy>", 509, 1, 510);
    pQyEPDB->Sumw2();

    TProfile *pQxTPCA = new TProfile("pQxTPCA", "Qx for TPCA for Primary Tracks; Run Index; <Qx>", 509, 1, 510);
    pQxTPCA->Sumw2();
    
    TProfile *pQyTPCA = new TProfile("pQyTPCA", "Qy for TPCA for Primary Tracks; Run Index; <Qy>", 509, 1, 510);
    pQyTPCA->Sumw2();
    
    TProfile *pQxTPCB = new TProfile("pQxTPCB", "Qx for TPCB for Primary Tracks; Run Index; <Qx>", 509, 1, 510);
    pQxTPCB->Sumw2();
    
    TProfile *pQyTPCB = new TProfile("pQyTPCB", "Qy for TPCB for Primary Tracks; Run Index; <Qy>", 509, 1, 510);
    pQyTPCB->Sumw2();
    

    
    TH1D *HitCountOuterEPD = new TH1D("HitCountOuterEPD","Outer EPD Hit Count; # of Hits; Count", 100, 0, 100);
    
    TH1D *Centralities = new TH1D("Centralities", "Centralities; Centrality; Count", 16, 0, 16);
    
    for (int index = 1; index < Centralities->GetNbinsX() + 1; index++)
    {
        Centralities->GetXaxis()->SetBinLabel(index, CentralityXLabels[index - 1]);
    }
    
    TH1D *CentralitiesNineToFifteenOuterEPDHitsOnly = new TH1D("CentralitiesNineToFifteenOuterEPDHitsOnly", "Centralities for Events with 9 <= OuterEPDHits < 16; Centrality; Count", 16, 0, 16);
    
    for (int index = 1; index < CentralitiesNineToFifteenOuterEPDHitsOnly->GetNbinsX() + 1; index++)
    {
        CentralitiesNineToFifteenOuterEPDHitsOnly->GetXaxis()->SetBinLabel(index, CentralityXLabels[index - 1]);
    }
    
    TH2D *EPDPhiVsEta = new TH2D("EPDPhiVsEta","EPD Phi Vs Eta; Eta; Phi", 700, -6, -2.5, 3000, -4, 4);
    
    TProfile2D *EtaVsRingNumberVsTruncatednMIP = new TProfile2D("EtaVsRingNumberVsTruncatednMIP","<Truncated nMIP> for Ring Number vs Eta; Eta; Ring Number", 40, -6, -2, 12, 0.5, 12.5);
    
    TProfile *nMIPVsPhi = new TProfile("nMIPVsPhi", "<nMIP> vs Phi; Phi; <nMIP>", 500, -3.5, 3.5);
    

    
    TH2D *h2_zd_vs_mom = new TH2D("h2_zd_vs_mom", ";|p| (GeV/c);z_{d}", 50, 0.0, 5.0, 140, -0.7, 0.7);
    
    TH2D *h2_zt_vs_mom  = new TH2D("h2_zt_vs_mom", ";|p| (GeV/c);z_{t}", 50, 0.0, 5.0, 140, -0.7, 0.7);
    
    
    
    
    TH2F *HistoD0 = new TH2F("DataVxVy","Target Vx and Vy; Vx; Vy", 500, -5, 5, 500, -5, 5);
    HistoD0->Sumw2();
    
    TH1F *HistoD1 = new TH1F("DataPt", "Pt (Data); Pt (GeV); Tracks", 500, 0, 5);
    HistoD1->Sumw2();

    TH1F *HistoD2 = new TH1F("DataEta", "Eta (Data); Eta; Tracks", 500, -3, 0);
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
    
    

    TH1D *EventCheck = (TH1D*)Data->Get("h_eventCheck");
    
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
    
    TProfile *HistoD54B = new TProfile("DataVnVsCentralityKaonPlusCorrected", D54BChar, 12, 0, 12);
    HistoD54B->Sumw2();
    
    for (int i = 1; i < HistoD54B->GetNbinsX() + 1; i++)
    {
        HistoD54B->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }
    
    std::string D54BBString = "V" + std::to_string(nV) + " vs Centrality for Kaon+ (Data) Rebined; Centrality; V" + std::to_string(nV) +"";
    const char *D54BBChar = &D54BBString[0];
    
    TProfile *HistoD54BB = new TProfile("DataVnVsCentralityKaonPlusCorrectedRebined", D54BBChar, 6, 0, 6);
    HistoD54BB->Sumw2();    
    
    std::string D54CString = "V" + std::to_string(nV) + " vs Centrality for Kaon- (Data); Centrality; V" + std::to_string(nV) +"";
    const char *D54CChar = &D54CString[0];

    TProfile *HistoD54C = new TProfile("DataVnVsCentralityKaonMinusCorrected", D54CChar, 12, 0, 12);
    HistoD54C->Sumw2();
    
    for (int i = 1; i < HistoD54C->GetNbinsX() + 1; i++)
    {
        HistoD54C->GetXaxis()->SetBinLabel(i, CentralityXLabels[i - 1]);
    }
    
    std::string D54CCString = "V" + std::to_string(nV) + " vs Centrality for Kaon+ (Data) Rebined; Centrality; V" + std::to_string(nV) +"";
    const char *D54CCChar = &D54BBString[0];
    
    TProfile *HistoD54CC = new TProfile("DataVnVsCentralityKaonMinusCorrectedRebined", D54CCChar, 6, 0, 6);
    HistoD54CC->Sumw2();    
    
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

    TProfile2D *HistoD88A = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesDeuterons", D88AChar, 12, 0, 12, 40, 0, 4);
    HistoD88A->Sumw2();
    
    std::string D88BString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for Deuterons for Different Centralities (Data); Centrality; y_{CM}";
    const char *D88BChar = &D88BString[0];

    TProfile2D *HistoD88B = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesDeuterons", D88BChar, 12, 0, 12, 10, 0, 1);
    HistoD88B->Sumw2();
    
    std::string D88CString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Pt for Tritons for Different Centralities (Data); Centrality; Pt";
    const char *D88CChar = &D88CString[0];
    
    TProfile2D *HistoD88C = new TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesTritons", D88CChar, 12, 0, 12, 60, 0, 6);
    HistoD88C->Sumw2();
    
    std::string D88DString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y for Tritons for Different Centralities (Data); Centrality; y_{CM}";
    const char *D88DChar = &D88DString[0];

    TProfile2D *HistoD88D = new TProfile2D("DataVnCorrectedVsYDifferentCentralitiesTritons", D88DChar, 12, 0, 12, 10, 0, 1);
    HistoD88D->Sumw2();
    
    
    
    
    
    std::string VnVsYSymmetricProtonString = "V" + std::to_string(nV) + " (Resolution Corrected) vs Y (Symmetric) for Protons for Different Centralities (Data) ; Centrality; y_{CM}";
    const char *VnVsYSymmetricProtonChar = &VnVsYSymmetricProtonString[0];

    TProfile2D *VnVsYSymmetricProton = new TProfile2D("DataVnCorrectedVsYSymmetricDifferentCentralitiesProtons", VnVsYSymmetricProtonChar, 12, 0, 12, 10, -0.5, 0.5);
    VnVsYSymmetricProton->Sumw2();
    




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
        
        RunIndex = 0;

        Int_t TotalTracks = (Int_t)tracknumber;
        Double_t vx = Vx;
        Double_t vy = Vy;
        Double_t vz = Vz;
        Int_t Centrality = (Int_t)centrality;
        Int_t RunId = (Int_t)runId;
        
//         RunId -= 22100000;
  
//         auto iterator = std::find(RunIDs.begin(), RunIDs.end(), RunId);
        
//         if(iterator != RunIDs.end())
//         {
//             RunIndex = std::distance(RunIDs.begin(), iterator);
//         }

//         pVx->Fill(RunIndex, vx);
//         pVy->Fill(RunIndex, vy);
//         pVz->Fill(RunIndex, vz);

        HistoD0->Fill(vx, vy);

        Double_t vr = sqrt(pow(vx, 2) + pow(vy + 2, 2));

        ZVertexValues->Fill(vz);
    
        RVertexValues->Fill(vr);
        
        for (Int_t TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
        {
            Double_t DCA = dca[TrackNum];
            Int_t NHits = nHits[TrackNum];
            Int_t NHitsdEdx = nHitsdEdx[TrackNum];
            Int_t NHitsFit = nHitsFit[TrackNum];
            Int_t NHitsPoss = nHitsPoss[TrackNum];

            DCAValues->Fill(DCA);

            NHitsValues->Fill(NHits);

            NHitsdEdxValues->Fill(NHitsdEdx);

            NHitsFitOverNHitsPossValues->Fill((Double_t)NHitsFit / (Double_t)NHitsPoss);
        }

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
                Int_t NHits = nHits[TrackNum];
                Int_t NHitsdEdx = nHitsdEdx[TrackNum];
                Int_t NHitsFit = nHitsFit[TrackNum];
                Int_t NHitsPoss = nHitsPoss[TrackNum];

               
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
                

//                 pPt->Fill(RunIndex, pt);
//                 pEta->Fill(RunIndex, eta);
                

                //Particle Identification
                Bool_t IsKaon = false;
                Bool_t IsPion = false;
                //bool IsProtonToF = false;
                Bool_t IsDeuteron = false;
                Bool_t IsTriton = false;
                Bool_t IsProtonTPC = (abs(NSigmaPr) < NSigmaPrBound) and (q == 1);
                
                

                if(tofBeta > 0)
                {
                    Double_t msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

                    IsKaon = (abs(NSigmaKa) < NSigmaKaBound) && (msquared > KaonLowerMSquared) && (msquared < KaonUpperMSquared);
                    IsPion = (abs(NSigmaPi) < NSigmaPiBound) && (msquared > PionLowerMSquared) && (msquared < PionUpperMSquared);
                    //IsProtonToF = (abs(NSigmaPr) < NSigmaPrBound) && (msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared) && (p > 2.0));
                }

                Double_t zDeuteron = TMath::Log(dEdx / BichselZDeuteron->Eval(p));
                Double_t zTriton = TMath::Log(dEdx / BichselZTriton->Eval(p));

                DeuteronsAndTritons DAndT (p, dEdx, tofBeta, zDeuteron, zTriton);

                if(!(IsKaon) && !(IsPion))
                {
                    IsDeuteron = DAndT.IsDeuteron() and (q == 1);
                    IsTriton = DAndT.IsTriton() and (q == 1);
                    
                    if(q == 1)
                    {
                        h2_zd_vs_mom->Fill(p, zDeuteron);
                        h2_zt_vs_mom->Fill(p, zTriton);
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



                if(tofBeta > 0)
                {

                    Double_t msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

                    HistoD4->Fill(qp, msquared);
//                     HistoD4A->Fill(qp, msquared);

//                     HistoD24->Fill(qp, NSigmaPr);
//                     HistoD25->Fill(qp, NSigmaKa);
//                     HistoD26->Fill(qp, NSigmaPi);

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

        Int_t GoodTracksCounterInnerEPD = 0;
        Int_t GoodTracksCounterOuterEPD = 0;
        Int_t GoodTracksCounterOuterTPC = 0;

        //TPC Track Counting loop
        for (Int_t TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
        {
                Double_t px = Px[TrackNum];
                Double_t py = Py[TrackNum];
                Double_t pz = Pz[TrackNum];
                Int_t q = (Int_t)Charge[TrackNum];
                Double_t DCA = dca[TrackNum];
                Int_t NHits = nHits[TrackNum];
                Int_t NHitsdEdx = nHitsdEdx[TrackNum];
                Int_t NHitsFit = nHitsFit[TrackNum];
                Int_t NHitsPoss = nHitsPoss[TrackNum]; 

                
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
            
                if(q == 0)
                {
                    continue;
                }
            
            

                OverallTrackCheckQACuts->Fill(1);

                Double_t eta = FlowFunctions::Eta(px, py, pz);

                if ((eta > OuterTPCLowerLimit) && (eta < OuterTPCUpperLimit))
                {
                    GoodTracksCounterOuterTPC += 1;
                }
        }//End TPC Track Counting loop

        Int_t nEPDHits = (Int_t)nEPDhits;

        //EPD Hit Counting loop
        for (Int_t index = 0; index < nEPDHits; index++)
        {
            Int_t EPDID = (Int_t)EPDid[index];
            Double_t EPDnMIP = EPDnMip[index];
            
            if(EPDID > 0)
            {
                continue;
            }

            TileVector *TVec = new TileVector(epdGeom, EPDID, vx, vy, vz, InnerEPDHighRing, OuterEPDLowRing);
            
            Double_t eta = TVec->EPDEta();
            Double_t phi = TVec->EPDPhi();
            
            Int_t RingNumber = TVec->EPDRow();
            
            HistoD32B->Fill(eta, RingNumber);
            
            EPDPhiVsEta->Fill(eta, phi);
                
            EtaVsRingNumberVsTruncatednMIP->Fill(eta, RingNumber, EPDnMIP);
            
            nMIPVsPhi->Fill(phi, EPDnMIP);

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
            continue;
        }
        
        EventCheck->Fill(5);
        
         
        //Q Vector Calulator loop (TPC)
        for (Int_t TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
        {
                Double_t px = Px[TrackNum];
                Double_t py = Py[TrackNum];
                Double_t pz = Pz[TrackNum];
                Int_t q = (Int_t)Charge[TrackNum];
                Double_t DCA = dca[TrackNum];
                Int_t NHits = nHits[TrackNum];
                Int_t NHitsdEdx = nHitsdEdx[TrackNum];
                Int_t NHitsFit = nHitsFit[TrackNum];
                Int_t NHitsPoss = nHitsPoss[TrackNum]; 


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
 
//         EventCheck->Fill(6);
        

        
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
            
            pQxEPDA->Fill(RunIndex, InnerEPDQx);
            pQyEPDA->Fill(RunIndex, InnerEPDQy);
            pQxEPDB->Fill(RunIndex, OuterEPDQx);
            pQyEPDB->Fill(RunIndex, OuterEPDQy);
            pQxTPCA->Fill(RunIndex, InnerTPCQx);
            pQyTPCA->Fill(RunIndex, InnerTPCQy);
            pQxTPCB->Fill(RunIndex, OuterTPCQx);
            pQyTPCB->Fill(RunIndex, OuterTPCQy);
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
            PsiInnerEPDRecentered = (1/nPsi)*atan2(InnerEPDQy - InnerEPDQyMean, InnerEPDQx - InnerEPDQxMean);
            PsiOuterEPDRecentered = (1/nPsi)*atan2(OuterEPDQy - OuterEPDQyMean, OuterEPDQx - OuterEPDQxMean);
            PsiOuterTPCRecentered = (1/nPsi)*atan2(OuterTPCQy - OuterTPCQyMean, OuterTPCQx - OuterTPCQxMean);
        }
        
        if(RunIteration == 2)
        {
            HistoD34->Fill(PsiInnerEPDRecentered);
            HistoD37->Fill(PsiOuterEPDRecentered);
            HistoD40->Fill(PsiOuterTPCRecentered);

            for (int j = 1; j < FourierCorrectionTerms + 1; j++)
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
            for (int j = 1; j < FourierCorrectionTerms + 1; j++)
            {   
                InnerEPDSineAverageJth = InnerEPDSineAverageProfile->GetBinContent(j);
                InnerEPDCosineAverageJth = InnerEPDCosineAverageProfile->GetBinContent(j);
                OuterEPDSineAverageJth = OuterEPDSineAverageProfile->GetBinContent(j);
                OuterEPDCosineAverageJth = OuterEPDCosineAverageProfile->GetBinContent(j);
                OuterTPCSineAverageJth = OuterTPCSineAverageProfile->GetBinContent(j);
                OuterTPCCosineAverageJth = OuterTPCCosineAverageProfile->GetBinContent(j);
                
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
            HistoD35->Fill(PsiInnerEPDFourierCorrected);
            HistoD38->Fill(PsiOuterEPDFourierCorrected);
            HistoD41->Fill(PsiOuterTPCFourierCorrected);
            
            Double_t R11TopLeftTerm = cos(nV*(PsiInnerEPDFourierCorrected - PsiOuterEPDFourierCorrected));
            Double_t R11TopRightTerm = cos(nV*(PsiInnerEPDFourierCorrected - PsiOuterTPCFourierCorrected));
            Double_t R11BottomTerm = cos(nV*(PsiOuterEPDFourierCorrected - PsiOuterTPCFourierCorrected));

            Centrality = 15 - Centrality;

            HistoD51->Fill(Centrality, R11TopLeftTerm);
            HistoD52->Fill(Centrality, R11TopRightTerm);
            HistoD53->Fill(Centrality, R11BottomTerm);
        
            const char* CentralityXLabels[12] = {"0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60"};

            for (int index = 1; index < HistoD51->GetNbinsX() + 1; index++)
            {
                HistoD51->GetXaxis()->SetBinLabel(index, CentralityXLabels[index - 1]);
                HistoD52->GetXaxis()->SetBinLabel(index, CentralityXLabels[index - 1]);
                HistoD53->GetXaxis()->SetBinLabel(index, CentralityXLabels[index - 1]);
            }
        }
        

        
        Centralities->Fill(15 - Centrality);

        if(Centrality < 4)
        {
            continue;
        }
        

//         EventCheck->Fill(7);


        
        Double_t ResolutionCorrectionFactor = 0;
        
        Centrality = 15 - Centrality;

        if(RunIteration == 4)
        {
            ResolutionCorrectionFactor = HistoD54->GetBinContent(Centrality + 1);

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
            Int_t NHits = nHits[TrackNum];
            Int_t NHitsdEdx = nHitsdEdx[TrackNum];
            Int_t NHitsFit = nHitsFit[TrackNum];
            Int_t NHitsPoss = nHitsPoss[TrackNum];


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
            Bool_t IsDeuteron = false;
            Bool_t IsTriton = false;
            Bool_t IsProtonTPC = (abs(NSigmaPr) < NSigmaPrBound) && (q == 1);


            if(tofBeta > 0)
            {
                Double_t msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

                IsKaon = (abs(NSigmaKa) < NSigmaKaBound) && (msquared > KaonLowerMSquared) && (msquared < KaonUpperMSquared);
                IsPion = (abs(NSigmaPi) < NSigmaPiBound) && (msquared > PionLowerMSquared) && (msquared < PionUpperMSquared);
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
//                     Bool_t IsProtonToF = (abs(NSigmaPr) < NSigmaPrBound) && (msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared) and (p > 2.0);

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

                    if(IsKaon)
                    {
                        Double_t mass = KaonMass;

                        Double_t y = FlowFunctions::Y(px, py, pz, mass);

                        Double_t VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

                        Bool_t IsGoodKaon = (pt > KaonLowerPt) && (pt < KaonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

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
                        Double_t mass = PionMass;

                        Double_t y = FlowFunctions::Y(px, py, pz, mass);

                        Double_t VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

                        Bool_t IsGoodPion = (pt > PionLowerPt) && (pt < PionUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

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

                if(IsDeuteron)
                {
                    Double_t mass = DeuteronMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                    Double_t VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

                    Bool_t IsGoodDeuteron = (pt > DeuteronLowerPt) && (pt < DeuteronUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                    if(IsGoodDeuteron)
                    {
                        HistoD42A->Fill(y - yCMShift, VnInnerEPDRaw);
                    }
                }

                else if(IsTriton)
                {
                    Double_t mass = TritonMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                    Double_t VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

                    Bool_t IsGoodTriton = (pt > TritonLowerPt) && (pt < TritonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                    if(IsGoodTriton)
                    {
                        HistoD42B->Fill(y - yCMShift, VnInnerEPDRaw);
                    }
                }


                if(IsProtonTPC)
                {
                    Double_t mass = ProtonMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                    Double_t VnInnerEPDRaw = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRaw);

                    Bool_t IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                    if(IsGoodProton)
                    {
                        HistoD42->Fill(y - yCMShift, VnInnerEPDRaw);
                    }
                }
            }
            
            
            //Second Pass (Recentered values)
            if(RunIteration == 2)
            {
                if(tofBeta > 0)
                {
//                     Bool_t IsProtonToF = (abs(NSigmaPr) < NSigmaPrBound) && (msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared) and (p > 2.0);

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

                    if(IsKaon)
                    {
                        Double_t mass = KaonMass;

                        Double_t y = FlowFunctions::Y(px, py, pz, mass);

                        Double_t VnInnerEPDRecentered = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRecentered);

                        Bool_t IsGoodKaon = (pt > KaonLowerPt) && (pt < KaonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                        if(IsGoodKaon)
                        {
                            if(q > 0)
                            {
                                HistoD46->Fill(y - yCMShift, VnInnerEPDRecentered);
                            }

                            if(q < 0)
                            {
                                HistoD46A->Fill(y - yCMShift, VnInnerEPDRecentered);
                            }
                        }
                    }

                    else if(IsPion)
                    {
                        Double_t mass = PionMass;

                        Double_t y = FlowFunctions::Y(px, py, pz, mass);

                        Double_t VnInnerEPDRecentered = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRecentered);

                        Bool_t IsGoodPion = (pt > PionLowerPt) && (pt < PionUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                        if(IsGoodPion)
                        {
                            if(q > 0)
                            {
                                HistoD49->Fill(y - yCMShift, VnInnerEPDRecentered);
                            }

                            if(q < 0)
                            {
                                HistoD49A->Fill(y - yCMShift, VnInnerEPDRecentered);
                            }
                        }
                     }
            
                    
                }

                if(IsDeuteron)
                {
                    Double_t mass = DeuteronMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                    Double_t VnInnerEPDRecentered = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRecentered);

                    Bool_t IsGoodDeuteron = (pt > DeuteronLowerPt) && (pt < DeuteronUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                    if(IsGoodDeuteron)
                    {
                        HistoD43A->Fill(y - yCMShift, VnInnerEPDRecentered);
                    }
                }

                else if(IsTriton)
                {
                    Double_t mass = TritonMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                    Double_t VnInnerEPDRecentered = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRecentered);

                    Bool_t IsGoodTriton = (pt > TritonLowerPt) && (pt < TritonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                    if(IsGoodTriton)
                    {
                        HistoD43B->Fill(y - yCMShift, VnInnerEPDRecentered);
                    }
                }


                if(IsProtonTPC)
                {
                    Double_t mass = ProtonMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                    Double_t VnInnerEPDRecentered = FlowFunctions::V_n(nV, px, py, PsiInnerEPDRecentered);

                    Bool_t IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                    if(IsGoodProton)
                    {
                        HistoD43->Fill(y - yCMShift, VnInnerEPDRecentered);
                    }
                }                
            }
            
            
            //Third Pass (Fourier Corrected values)
            if(RunIteration == 3)
            {
                if(tofBeta > 0)
                {
//                     Bool_t IsProtonToF = (abs(NSigmaPr) < NSigmaPrBound) && (msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared) and (p > 2.0);

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

                    if(IsKaon)
                    {
                        Double_t mass = KaonMass;

                        Double_t y = FlowFunctions::Y(px, py, pz, mass);

                        Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

                        Bool_t IsGoodKaon = (pt > KaonLowerPt) && (pt < KaonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                        if(IsGoodKaon)
                        {
                            if(q > 0)
                            {
                                HistoD47->Fill(y - yCMShift, VnInnerEPDFourierCorrected);
                            }

                            if(q < 0)
                            {
                                HistoD47A->Fill(y - yCMShift, VnInnerEPDFourierCorrected);
                            }
                        }
                    }

                    else if(IsPion)
                    {
                        Double_t mass = PionMass;

                        Double_t y = FlowFunctions::Y(px, py, pz, mass);

                        Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

                        Bool_t IsGoodPion = (pt > PionLowerPt) && (pt < PionUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                        if(IsGoodPion)
                        {
                            if(q > 0)
                            {
                                HistoD50->Fill(y - yCMShift, VnInnerEPDFourierCorrected);
                            }

                            if(q < 0)
                            {
                                HistoD50A->Fill(y - yCMShift, VnInnerEPDFourierCorrected);
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

                    if(IsGoodDeuteron)
                    {
                        HistoD44A->Fill(y - yCMShift, VnInnerEPDFourierCorrected);
                    }
                }

                else if(IsTriton)
                {
                    Double_t mass = TritonMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                    Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

                    Bool_t IsGoodTriton = (pt > TritonLowerPt) && (pt < TritonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                    if(IsGoodTriton)
                    {
                        HistoD44B->Fill(y - yCMShift, VnInnerEPDFourierCorrected);
                    }
                }


                if(IsProtonTPC)
                {
                    Double_t mass = ProtonMass;

                    Double_t y = FlowFunctions::Y(px, py, pz, mass);

                    Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

                    Bool_t IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

                    if(IsGoodProton)
                    {
                        HistoD44->Fill(y - yCMShift, VnInnerEPDFourierCorrected);
                    }
                }                
            }
            
            
            
            
            //Fourth Pass (Resolution Corrected values)
            if(RunIteration == 4)
            {
                if(tofBeta > 0)
                {

//                     Bool_t IsProtonToF = (abs(NSigmaPr) < NSigmaPrBound) && (msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared) && (p > 2.0);

//                      if(IsProtonToF)
//                      {
//                          Double_t mass = ProtonMass;

//                          Double_t y = FlowFunctions::Y(px, py, pz, mass);

//                          Double_t VnInnerEPDFourierCorrected = FlowFunctions::V_n(nV, px, py, PsiInnerEPDFourierCorrected);

//                          Bool_t IsGoodProton = (pt > ProtonLowerPt) && (pt < ProtonUpperPt) && ((y - yCMShift) > LowerYMinusYCMShift) && ((y - yCMShift) < UpperYMinusYCMShift);

//                          TH2D *TPCEfficiencyHistogram = (TH2D*)TPCEfficiencyFile->Get("h2_ratio_pr");
//                          TH2D *ToFEfficiencyHistogram = (TH2D*)ToFEfficiencyFile->Get("h2_ratio_tof");

//                          Int_t TPCEfficiencyBinX = TPCEfficiencyHistogram->GetXaxis()->FindBin(y - yCMShift);
//                          Int_t TPCEfficiencyBinY = TPCEfficiencyHistogram->GetYaxis()->FindBin(pt);
//                          Int_t ToFEfficiencyBinX = ToFEfficiencyHistogram->GetXaxis()->FindBin(eta);
//                          Int_t ToFEfficiencyBinY = ToFEfficiencyHistogram->GetYaxis()->FindBin(pt);

//                          Double_t TPCEfficiency = TPCEfficiencyHistogram->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);
//                          Double_t ToFEfficiency = ToFEfficiencyHistogram->GetBinContent(ToFEfficiencyBinX, ToFEfficiencyBinY);

//                          if((TPCEfficiency == 0) || (TPCEfficiency > 1.3) || (ToFEfficiency == 0))
//                          {
//                              continue;
//                          }

//                          if(IsGoodProton)
//                          {
//                              HistoD44C->Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
//                              HistoD54A->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
//                              HistoD79->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
//                              HistoD80->Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));

//                          for (int i = 0; i < HistoD54A.GetNbinsX() + 1; i++)
//                          {
//                              HistoD54A->GetXaxis().SetBinLabel(i, CentralityXLabels[i - 1]);
//                          }
//                       }
                    
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
                                    HistoD54BB->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
                                    HistoD81->Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
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
                                    HistoD54CC->Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0 / (TPCEfficiency * ToFEfficiency));
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
                            TH2D *TPCEfficiencyHistogram = (TH2D*)TPCEfficiencyFile->Get("h2_ratio_pp");
                            TH2D *ToFEfficiencyHistogram = (TH2D*)ToFEfficiencyFile->Get("h2_ratio_tof");

                            Int_t TPCEfficiencyBinX = TPCEfficiencyHistogram->GetXaxis()->FindBin(y - yCMShift);
                            Int_t TPCEfficiencyBinY = TPCEfficiencyHistogram->GetYaxis()->FindBin(pt);
                            Int_t ToFEfficiencyBinX = ToFEfficiencyHistogram->GetXaxis()->FindBin(eta);
                            Int_t ToFEfficiencyBinY = ToFEfficiencyHistogram->GetYaxis()->FindBin(pt);

                            Double_t TPCEfficiency = TPCEfficiencyHistogram->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);
                            Double_t ToFEfficiency = ToFEfficiencyHistogram->GetBinContent(ToFEfficiencyBinX, ToFEfficiencyBinY);

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
                            TH2D *TPCEfficiencyHistogram = (TH2D*)TPCEfficiencyFile->Get("h2_ratio_pm");
                            TH2D *ToFEfficiencyHistogram = (TH2D*)ToFEfficiencyFile->Get("h2_ratio_tof");

                            Int_t TPCEfficiencyBinX = TPCEfficiencyHistogram->GetXaxis()->FindBin(y - yCMShift);
                            Int_t TPCEfficiencyBinY = TPCEfficiencyHistogram->GetYaxis()->FindBin(pt);
                            Int_t ToFEfficiencyBinX = ToFEfficiencyHistogram->GetXaxis()->FindBin(eta);
                            Int_t ToFEfficiencyBinY = ToFEfficiencyHistogram->GetYaxis()->FindBin(pt);

                            Double_t TPCEfficiency = TPCEfficiencyHistogram->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);
                            Double_t ToFEfficiency = ToFEfficiencyHistogram->GetBinContent(ToFEfficiencyBinX, ToFEfficiencyBinY);

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

                    TH2D *TPCEfficiencyHistogram = (TH2D*)TPCEfficiencyFileDandT->Get("h2_ratio_de");

                    Int_t TPCEfficiencyBinX = TPCEfficiencyHistogram->GetXaxis()->FindBin(y - yCMShift);
                    Int_t TPCEfficiencyBinY = TPCEfficiencyHistogram->GetYaxis()->FindBin(pt);

                    Double_t TPCEfficiency = TPCEfficiencyHistogram->GetBinContent(TPCEfficiencyBinX, TPCEfficiencyBinY);

                    if((TPCEfficiency == 0) || (TPCEfficiency > 1.3))
                    {
                        continue;
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

                    if((TPCEfficiency == 0) || (TPCEfficiency > 1.3))
                    {
                        continue;
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
        HistoInnerEPDQxRaw->SetDirectory(0);
        HistoInnerEPDQyRaw->SetDirectory(0);
        HistoOuterEPDQxRaw->SetDirectory(0);
        HistoOuterEPDQyRaw->SetDirectory(0);
        HistoOuterTPCQxRaw->SetDirectory(0);
        HistoOuterTPCQyRaw->SetDirectory(0);
        ZVertexValues->SetDirectory(0);
        RVertexValues->SetDirectory(0);
        DCAValues->SetDirectory(0);
        NHitsValues->SetDirectory(0);
        NHitsdEdxValues->SetDirectory(0);
        NHitsFitOverNHitsPossValues->SetDirectory(0);
        pVx->SetDirectory(0);
        pVy->SetDirectory(0);
        pVz->SetDirectory(0);
        pPt->SetDirectory(0);
        pEta->SetDirectory(0);
        pQxEPDA->SetDirectory(0);
        pQyEPDA->SetDirectory(0);
        pQxEPDB->SetDirectory(0);
        pQyEPDB->SetDirectory(0);
        pQxTPCA->SetDirectory(0);
        pQyTPCA->SetDirectory(0);
        pQxTPCB->SetDirectory(0);
        pQyTPCB->SetDirectory(0);
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

        HistoInnerEPDQxRaw->Write();
        HistoInnerEPDQyRaw->Write();
        HistoOuterEPDQxRaw->Write();
        HistoOuterEPDQyRaw->Write();
        HistoOuterTPCQxRaw->Write();
        HistoOuterTPCQyRaw->Write();

        QVectorHistogramRootFile->Close();
        



        std::string HistogramRootFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/HistogramFirstPass" + argv[3] + argv[2] + ".root";
        const char *HistogramRootFileChar = &HistogramRootFileString[0];

        TFile *HistogramRootFile =TFile::Open(HistogramRootFileChar, "RECREATE");
        HistogramRootFile->cd();

        ZVertexValues->Write();
        RVertexValues->Write();
        DCAValues->Write();
        NHitsValues->Write();
        NHitsdEdxValues->Write();
        NHitsFitOverNHitsPossValues->Write();
        pVx->Write();
        pVy->Write();
        pVz->Write();
        pPt->Write();
        pEta->Write();
        pQxEPDA->Write();
        pQyEPDA->Write();
        pQxEPDB->Write();
        pQyEPDB->Write();
        pQxTPCA->Write();
        pQyTPCA->Write();
        pQxTPCB->Write();
        pQyTPCB->Write();
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
        HistoInnerEPDQxRecentered->SetDirectory(0);
        HistoInnerEPDQyRecentered->SetDirectory(0);
        HistoOuterEPDQxRecentered->SetDirectory(0);
        HistoOuterEPDQyRecentered->SetDirectory(0);
        HistoOuterTPCQxRecentered->SetDirectory(0);
        HistoOuterTPCQyRecentered->SetDirectory(0);
        HistoInnerEPDSineAverages->SetDirectory(0);
        HistoInnerEPDCosineAverages->SetDirectory(0);
        HistoOuterEPDSineAverages->SetDirectory(0);
        HistoOuterEPDCosineAverages->SetDirectory(0);
        HistoOuterTPCSineAverages->SetDirectory(0);
        HistoOuterTPCCosineAverages->SetDirectory(0);
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

        HistoInnerEPDQxRecentered->Write();
        HistoInnerEPDQyRecentered->Write();
        HistoOuterEPDQxRecentered->Write();
        HistoOuterEPDQyRecentered->Write();
        HistoOuterTPCQxRecentered->Write();
        HistoOuterTPCQyRecentered->Write();
        HistoInnerEPDSineAverages->Write();
        HistoInnerEPDCosineAverages->Write();
        HistoOuterEPDSineAverages->Write();
        HistoOuterEPDCosineAverages->Write();
        HistoOuterTPCSineAverages->Write();
        HistoOuterTPCCosineAverages->Write();

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

        
        

        
        
        HitCountOuterEPD->SetDirectory(0);
        Centralities->SetDirectory(0);
        CentralitiesNineToFifteenOuterEPDHitsOnly->SetDirectory(0);
        EPDPhiVsEta->SetDirectory(0);
        EtaVsRingNumberVsTruncatednMIP->SetDirectory(0);
        nMIPVsPhi->SetDirectory(0);
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
        HistoD54BB->SetDirectory(0);
        HistoD54C->SetDirectory(0);
        HistoD54CC->SetDirectory(0);
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
        
        
        HitCountOuterEPD->Write();
        Centralities->Write();
        CentralitiesNineToFifteenOuterEPDHitsOnly->Write();
        EPDPhiVsEta->Write();
        EtaVsRingNumberVsTruncatednMIP->Write();
        nMIPVsPhi->Write();
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
        HistoD54BB->Write();
        HistoD54C->Write();
        HistoD54CC->Write();
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
        delete pQxEPDA;
        delete pQyEPDA;
        delete pQxEPDB;
        delete pQyEPDB;
        delete pQxTPCA;
        delete pQyTPCA;
        delete pQxTPCB;
        delete pQyTPCB;
        delete h2_zd_vs_mom;
        delete h2_zt_vs_mom;
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
    }
   
    
    
    if(RunIteration == 2)
    {
        delete HistoInnerEPDQxRecentered;
        delete HistoInnerEPDQyRecentered;
        delete HistoOuterEPDQxRecentered;
        delete HistoOuterEPDQyRecentered;
        delete HistoOuterTPCQxRecentered;
        delete HistoOuterTPCQyRecentered;
        delete HistoInnerEPDSineAverages;
        delete HistoInnerEPDCosineAverages;
        delete HistoOuterEPDSineAverages;
        delete HistoOuterEPDCosineAverages;
        delete HistoOuterTPCSineAverages;
        delete HistoOuterTPCCosineAverages;
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
        delete HitCountOuterEPD;
        delete Centralities;
        delete CentralitiesNineToFifteenOuterEPDHitsOnly;
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
        delete HistoD54BB;
        delete HistoD54C;
        delete HistoD54CC;
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
