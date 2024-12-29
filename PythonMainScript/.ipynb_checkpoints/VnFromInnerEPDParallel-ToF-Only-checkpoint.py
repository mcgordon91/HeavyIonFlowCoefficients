#!/usr/bin/env python
# coding: utf-8

from __future__ import division
import ROOT
from math import sqrt, pow, log, atanh, atan2, sin, cos, exp
import os
import sys
from KinematicFunctions import *
ROOT.gROOT.ProcessLine(".L StEpdGeom.cxx")
ROOT.gInterpreter.Declare("""
    const UInt_t barWidth = 60;
    ULong64_t processed = 0, totalEvents = 0;
    std::string progressBar;
    std::mutex barMutex; 
    auto registerEvents = [](ULong64_t nIncrement) {totalEvents += nIncrement;};
    ROOT::RDF::RResultPtr<ULong64_t> AddProgressBar(ROOT::RDF::RNode df, int everyN=10000, int totalN=100000) {
        registerEvents(totalN);
        auto c = df.Count();
        c.OnPartialResultSlot(everyN, [everyN] (unsigned int slot, ULong64_t &cnt){
            std::lock_guard<std::mutex> l(barMutex);
            processed += everyN; //everyN captured by value for this lambda
            progressBar = "[";
            for(UInt_t i = 0; i < static_cast<UInt_t>(static_cast<Float_t>(processed)/totalEvents*barWidth); ++i){
                progressBar.push_back('|');
            }
            // escape the '\' when defined in python string
            std::cout << "\\r" << std::left << std::setw(barWidth) << progressBar << "] " << processed << "/" << totalEvents << std::flush;
        });
        return c;
    }
""")
# Enables multithreading
#useRange = False
#if not useRange:
#    nThreads = 8
#    ROOT.EnableImplicitMT(nThreads)


nPsi = 1
nV = 1



if(os.path.exists("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/HistogramThirdPass.root")):
    RunIteration = 4
elif(os.path.exists("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/HistogramSecondPass.root")):
    RunIteration = 3
elif(os.path.exists("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) +"Histograms/HistogramFirstPass.root")):
    RunIteration = 2
else:
    RunIteration = 1

# RunIteration = 1





yCMShift = -1.045
NumberOfGoodTracksInnerEPD = 5
NumberOfGoodTracksOuterEPD = 9
NumberOfGoodTracksTPC = 5
TPCUpperLimit = 0
TPCLowerLimit = -1
ProtonLowerMSquared = 0.45
ProtonUpperMSquared = 2.0
KaonLowerMSquared = 0.15
KaonUpperMSquared = 0.34
PionLowerMSquared = 0
PionUpperMSquared = 0.1
NSigmaPrBound = 2
NSigmaKaBound = 3
NSigmaPiBound = 3
ProtonLowerPt = 0.4
ProtonUpperPt = 2.0
KaonLowerPt = 0.4
KaonUpperPt = 1.6
PionLowerPt = 0.18
PionUpperPt = 1.6
DeuteronLowerPt = 0.8
DeuteronUpperPt = 2.0
TritonLowerPt = 1.2
TritonUpperPt = 3.0
LowerYMinusYCM = 0
UpperYMinusYCM = 1

QBounds = 100
FourierCorrectionTerms = 10

cpp_code = """
#include <cmath>
#include "StEpdGeom.h"
#include "/star/u/mcgordon/VnFromEPD/StRoot/StBichsel/dEdxParameterization.cxx"
#include "/star/u/mcgordon/VnFromEPD/StRoot/StBichsel/Bichsel.h"
#include "/star/u/mcgordon/VnFromEPD/StRoot/StBichsel/Bichsel.cxx"
#include "/star/u/mcgordon/VnFromEPD/bichselComparison.cxx"

class EPDKinematics
{
    private:
        int EPDID;
        float vx;
        float vy;
        float vz;
    
    public:
        EPDKinematics();
        EPDKinematics(int EPDID, float vx, float vy, float vz);
        
        float EPDEta();
        float EPDPhi();
        int EPDSector();
        int EPDRow();
        bool IsInnerEPD();
        bool IsOuterEPD();
};


EPDKinematics::EPDKinematics()
{
    this->EPDID = 0;
    this->vx = 0;
    this->vy = 0;
    this->vz = 0;
}

EPDKinematics::EPDKinematics(int EPDID, float vx, float vy, float vz)
{
    this->EPDID = EPDID;
    this->vx = vx;
    this->vy = vy;
    this->vz = vz;
}

float EPDKinematics::EPDEta()
{
    StEpdGeom* epdGeom = new StEpdGeom();
    
    TVector3 VertexVector(this->vx, this->vy, this->vz);
    
    TVector3 TileVector = epdGeom->TileCenter(this->EPDID) - VertexVector;
    
    delete epdGeom;

    return TileVector.Eta();
}

float EPDKinematics::EPDPhi()
{
    StEpdGeom* epdGeom = new StEpdGeom();
    
    TVector3 VertexVector(this->vx, this->vy, this->vz);
    
    TVector3 TileVector = epdGeom->TileCenter(this->EPDID) - VertexVector;
    
    delete epdGeom;
    
    return TileVector.Phi();
}

int EPDKinematics::EPDSector()
{
    return TMath::Abs(this->EPDID/100);
}

int EPDKinematics::EPDRow()
{
    int absID = TMath::Abs(this->EPDID);
    int tileNum = absID % 100;
    int rowNum = 0;
    
    if (tileNum == 1) rowNum = 1;
    else if (tileNum == 2 || tileNum == 3) rowNum = 2;
    else if (tileNum == 4 || tileNum == 5) rowNum = 3;
    else if (tileNum == 6 || tileNum == 7) rowNum = 4;
    else if (tileNum == 8 || tileNum == 9) rowNum = 5;
    else if (tileNum == 10 || tileNum == 11) rowNum = 6;
    else if (tileNum == 12 || tileNum == 13) rowNum = 7;
    else if (tileNum == 14 || tileNum == 15) rowNum = 8;
    else if (tileNum == 16 || tileNum == 17) rowNum = 9;
    else if (tileNum == 18 || tileNum == 19) rowNum = 10;
    else if (tileNum == 20 || tileNum == 21) rowNum = 11;
    else if (tileNum == 22 || tileNum == 23) rowNum = 12;
    else if (tileNum == 24 || tileNum == 25) rowNum = 13;
    else if (tileNum == 26 || tileNum == 27) rowNum = 14;
    else if (tileNum == 28 || tileNum == 29) rowNum = 15;
    else if (tileNum == 30 || tileNum == 31) rowNum = 16;

    return rowNum;
}

bool EPDKinematics::IsInnerEPD()
{
    int RowNum = EPDRow();
    
    return ((RowNum >= 1) && (RowNum <= 8));
}

bool EPDKinematics::IsOuterEPD()
{
    int RowNum = EPDRow();
    
    return ((RowNum >= 9) && (RowNum <= 16));
}





Double_t BichselZ(Double_t *p, Double_t *parameters) 
{
    Double_t POverM = p[0] / parameters[0];
  
    return TMath::Exp(Bichsel::Instance()->GetMostProbableZ(TMath::Log10(POverM),parameters[1]));
}





class DeuteronsAndTritons
{
    private:
        float p;
        float dEdx;
        float tofBeta;
    
    public:
        DeuteronsAndTritons();
        DeuteronsAndTritons(float p, float dEdx, float tofBeta);
        
        bool IsDeuteron();
        bool IsTriton();
        
};

DeuteronsAndTritons::DeuteronsAndTritons()
{
    this->p = 0;
    this->dEdx = 0;
    this->tofBeta = 0;
}

DeuteronsAndTritons::DeuteronsAndTritons(float p, float dEdx, float tofBeta)
{
    this->p = p;
    this->dEdx = dEdx;
    this->tofBeta = tofBeta;
}


bool DeuteronsAndTritons::IsDeuteron()
{
    const Double_t DeuteronMass = 1.875613;
    const float zLow = -0.2;
    const float zHigh = 0.2;
    const float msquaredLow = 3.15;
    const float msquaredHigh = 3.88;
    
    Double_t log2dx = 1.0;
    Double_t xStart = 0.01;
    Double_t xStop  = 3.0;
    Int_t npx = 10000;
    
    Double_t parameters[2] = {DeuteronMass, log2dx};

    TF1 *BichselZDeuteron = new TF1(Form("BichselZDeuteron_log2dx_%i",(int)log2dx),BichselZ,xStart,xStop,2);

    BichselZDeuteron->SetParameters(parameters); 
    BichselZDeuteron->SetNpx(npx);
    
    float zDeuteron = TMath::Log(this->dEdx / BichselZDeuteron->Eval(this->p));
  
    delete BichselZDeuteron;

    
    
    
    
    float momentum = this->p;
    bool deuteron = false;
    
    if (momentum >= 0.4 && momentum < 3.0)
    {
        if      (momentum >= 0.4 && momentum < 0.5 && zDeuteron > -0.4036469 && zDeuteron < 0.1760739) deuteron = true;
        else if (momentum >= 0.5 && momentum < 0.6 && zDeuteron > -0.3699729 && zDeuteron < 0.2353959) deuteron = true;
        else if (momentum >= 0.6 && momentum < 0.7 && zDeuteron > -0.3539096 && zDeuteron < 0.2554536) deuteron = true;
        else if (momentum >= 0.7 && momentum < 0.8 && zDeuteron > -0.340315 && zDeuteron < 0.265653) deuteron = true;
        else if (momentum >= 0.8 && momentum < 0.9 && zDeuteron > -0.3305487 && zDeuteron < 0.2637977) deuteron = true;
        else if (momentum >= 0.9 && momentum < 1.0 && zDeuteron > -0.3029986  && zDeuteron < 0.2665326) deuteron = true;
        else if (momentum >= 1.0 && momentum < 1.1 && zDeuteron > -0.2636499  && zDeuteron < 0.2660309) deuteron = true;
        else if (momentum >= 1.1 && momentum < 1.2 && zDeuteron > -0.2671373 && zDeuteron < 0.2597243) deuteron = true;
        else if (momentum >= 1.2 && momentum < 1.3 && zDeuteron > -0.2435773 && zDeuteron < 0.2569643) deuteron = true;
        else if (momentum >= 1.3 && momentum < 1.4 && zDeuteron > -0.2170656 && zDeuteron < 0.2543056) deuteron = true;
        else if (momentum >= 1.4 && momentum < 1.5 && zDeuteron > -0.1952265 && zDeuteron < 0.2466735) deuteron = true;
        else if (momentum >= 1.5 && momentum < 1.6 && zDeuteron > -0.1634066 && zDeuteron < 0.2504206) deuteron = true;
        else if (momentum >= 1.6 && momentum < 1.7 && zDeuteron > -0.1281953 && zDeuteron < 0.2601063) deuteron = true;
        else if (momentum >= 1.7 && momentum < 1.8 && zDeuteron > -0.1151064 && zDeuteron < 0.2509704) deuteron = true;
        else if (momentum >= 1.8 && momentum < 1.9 && zDeuteron > -0.1061879 && zDeuteron < 0.2383009) deuteron = true;
        else if (momentum >= 1.9 && momentum < 2.0 && zDeuteron > -0.04742523 && zDeuteron < 0.23782653) deuteron = true;
        else if (momentum >= 2.0 && momentum < 2.1 && zDeuteron > -0.0317317 && zDeuteron < 0.2361667) deuteron = true;
        else if (momentum >= 2.1 && momentum < 2.2 && zDeuteron > -0.0180606  && zDeuteron < 0.2336146) deuteron = true;
        else if (momentum >= 2.2 && momentum < 2.3 && zDeuteron > -0.00642016 && zDeuteron < 0.22928576) deuteron = true;
        else if (momentum >= 2.3 && momentum < 2.4 && zDeuteron > 0.00561631 && zDeuteron < 0.22545959) deuteron = true;
        else if (momentum >= 2.4 && momentum < 2.5 && zDeuteron > 0.01413343 && zDeuteron < 0.21855527) deuteron = true;
        else if (momentum >= 2.5 && momentum < 2.6 && zDeuteron > 0.019947933 && zDeuteron < 0.184808437) deuteron = true;
        else if (momentum >= 2.6 && momentum < 2.7 && zDeuteron > 0.0293964  && zDeuteron < 0.1792716) deuteron = true;
        else if (momentum >= 2.7 && momentum < 2.8 && zDeuteron > 0.03725255 && zDeuteron < 0.17222095) deuteron = true;
        else if (momentum >= 2.8 && momentum < 2.9 && zDeuteron > 0.04636483 && zDeuteron < 0.16629387) deuteron = true;
        else if (momentum >= 2.9 && momentum < 3.0 && zDeuteron > 0.05767728 && zDeuteron < 0.16157392) deuteron = true;
    }
    
    else if(this->tofBeta > 0)
    {
        float msquared = (pow(momentum,2) * ((1/pow(this->tofBeta,2)) - 1));
        
        if (zDeuteron > zLow && zDeuteron < zHigh && msquared > msquaredLow && msquared < msquaredHigh)
        {
            deuteron = true;
        }
    }
  
    return deuteron;
}

bool DeuteronsAndTritons::IsTriton()
{
    const Double_t TritonMass = 2.808921;
    const float zLow = -0.2;
    const float zHigh = 0.2;
    const float msquaredLow = 7.01;
    const float msquaredHigh = 8.76;
    
    Double_t log2dx = 1.0;
    Double_t xStart = 0.01;
    Double_t xStop  = 3.0;
    Int_t npx = 10000;
    
    Double_t parameters[2] = {TritonMass, log2dx};

    TF1 *BichselZTriton = new TF1(Form("BichselZTriton_log2dx_%i",(int)log2dx),BichselZ,xStart,xStop,2);

    BichselZTriton->SetParameters(parameters); 
    BichselZTriton->SetNpx(npx);
    
    float zTriton = TMath::Log(this->dEdx / BichselZTriton->Eval(this->p));
  
    delete BichselZTriton;

    
    
    
    
    float momentum = this->p;
    bool triton = false;
    
    if (momentum >= 1.0 && momentum < 4.0)
    {
        if      (momentum >= 1.0 && momentum < 1.1 && zTriton > -0.332011 && zTriton < 0.251103) triton = true;
        else if (momentum >= 1.1 && momentum < 1.2 && zTriton > -0.310412 && zTriton < 0.296090) triton = true;
        else if (momentum >= 1.2 && momentum < 1.3 && zTriton > -0.293322 && zTriton < 0.334467) triton = true;
        else if (momentum >= 1.3 && momentum < 1.4 && zTriton > -0.270550 && zTriton < 0.373857) triton = true;
        else if (momentum >= 1.4 && momentum < 1.5 && zTriton > -0.248412 && zTriton < 0.406237) triton = true;
        else if (momentum >= 1.5 && momentum < 1.6 && zTriton > -0.228044 && zTriton < 0.333261) triton = true;
        else if (momentum >= 1.6 && momentum < 1.7 && zTriton > -0.210093 && zTriton < 0.343588) triton = true;
        else if (momentum >= 1.7 && momentum < 1.8 && zTriton > -0.190900 && zTriton < 0.332586) triton = true;
        else if (momentum >= 1.8 && momentum < 1.9 && zTriton > -0.183153 && zTriton < 0.334197) triton = true;
        else if (momentum >= 1.9 && momentum < 2.0 && zTriton > -0.166020 && zTriton < 0.323303) triton = true;
        else if (momentum >= 2.0 && momentum < 2.1 && zTriton > -0.102334 && zTriton < 0.307724) triton = true;
        else if (momentum >= 2.1 && momentum < 2.2 && zTriton > -0.091053 && zTriton < 0.294345) triton = true;
        else if (momentum >= 2.2 && momentum < 2.3 && zTriton > -0.076457 && zTriton < 0.285978) triton = true;
        else if (momentum >= 2.3 && momentum < 2.4 && zTriton > -0.055669 && zTriton < 0.253769) triton = true;
        else if (momentum >= 2.4 && momentum < 2.5 && zTriton > -0.035848 && zTriton < 0.254487) triton = true;
        else if (momentum >= 2.5 && momentum < 2.6 && zTriton > -0.027266 && zTriton < 0.249350) triton = true;
        else if (momentum >= 2.6 && momentum < 2.7 && zTriton > -0.028152 && zTriton < 0.236713) triton = true;
        else if (momentum >= 2.7 && momentum < 2.8 && zTriton > -0.027867 && zTriton < 0.227672) triton = true;
        else if (momentum >= 2.8 && momentum < 2.9 && zTriton > -0.024675 && zTriton < 0.222215) triton = true;
        else if (momentum >= 2.9 && momentum < 3.0 && zTriton > -0.019179 && zTriton < 0.227362) triton = true;
        else if (momentum >= 3.0 && momentum < 3.1 && zTriton > -0.013267 && zTriton < 0.236052) triton = true;
        else if (momentum >= 3.1 && momentum < 3.2 && zTriton > -0.007851 && zTriton < 0.246071) triton = true;
        else if (momentum >= 3.2 && momentum < 3.3 && zTriton > -0.006311 && zTriton < 0.254907) triton = true;
        else if (momentum >= 3.3 && momentum < 3.4 && zTriton > 0.019834  && zTriton < 0.244291) triton = true;
        else if (momentum >= 3.4 && momentum < 3.5 && zTriton > 0.031221  && zTriton < 0.273652) triton = true;
        else if (momentum >= 3.5 && momentum < 3.6 && zTriton > 0.068248  && zTriton < 0.257484) triton = true;
        else if (momentum >= 3.6 && momentum < 3.7 && zTriton > 0.088804  && zTriton < 0.260799) triton = true;
        else if (momentum >= 3.7 && momentum < 3.8 && zTriton > 0.091490  && zTriton < 0.271776) triton = true;
        else if (momentum >= 3.8 && momentum < 3.9 && zTriton > 0.106161  && zTriton < 0.285652) triton = true;
        else if (momentum >= 3.9 && momentum < 4.0 && zTriton > 0.103653  && zTriton < 0.299234) triton = true;
    }
    
    else if(this->tofBeta > 0)
    {
        float msquared = (pow(momentum,2) * ((1/pow(this->tofBeta,2)) - 1));

        if (zTriton > zLow && zTriton < zHigh && msquared > msquaredLow && msquared < msquaredHigh)
        {
            triton = true;
        }
    }
    
    
    return triton;
}

"""
ROOT.gInterpreter.Declare(cpp_code)


if(RunIteration == 1):
    Data = ROOT.TFile.Open(sys.argv[1])
    #Data = ROOT.TFile.Open("/star/data01/pwg/cracz/Data_3p0GeV_FXT/FXT_3p0GeV_SL20d_2018_11.root")

    # print(Data.ls())

    AutreeData = Data.Get("Autree")

    # print(AutreeData.Print())

    QVectorHistograms = []
    Histograms = []

 
    
    
    
    HistoInnerEPDQxRaw = ROOT.TH1D("InnerEPDQxRaw", "Qx Raw for Inner EPD; Qx; Events", 250, -QBounds, QBounds)
    HistoInnerEPDQyRaw = ROOT.TH1D("InnerEPDQyRaw", "Qy Raw for Inner EPD; Qy; Events", 250, -QBounds, QBounds)
    HistoOuterEPDQxRaw = ROOT.TH1D("OuterEPDQxRaw", "Qx Raw for Outer EPD; Qx; Events", 250, -QBounds, QBounds)
    HistoOuterEPDQyRaw = ROOT.TH1D("OuterEPDQyRaw", "Qy Raw for Inner EPD; Qy; Events", 250, -QBounds, QBounds)
    HistoTPCQxRaw = ROOT.TH1D("TPCQxRaw", "Qx Raw for TPC; Qx; Events", 250, -QBounds, QBounds)
    HistoTPCQyRaw = ROOT.TH1D("TPCQyRaw", "Qy Raw for TPC; Qy; Events", 250, -QBounds, QBounds)

    
    
    
    
    
    HistoD1 = ROOT.TH1F("DataPt", "Pt (Data); Pt (GeV); Events", 500, 0, 2)
    HistoD1.Sumw2()

    HistoD2 = ROOT.TH1F("DataEta", "Eta (Data); Eta; Events", 500, -3, 0)
    HistoD2.Sumw2()

    HistoD3 = ROOT.TH2F("DataPtVsEta", "Pt vs Eta (Data); Eta; Pt (GeV)", 500, -3, 0, 500, 0, 2)
    HistoD3.Sumw2()

    HistoD4 = ROOT.TH2F("DataMSquaredVsQP", "m^2 vs q|p| (Data); q|p| (GeV); m^2 (GeV^2)", 1000, -4, 4, 1000, -0.1, 10)
    HistoD4.Sumw2()

    HistoD4A = ROOT.TH2F("DataMSquaredVsQPZoomed", "m^2 vs q|p| (Data); q|p| (GeV); m^2 (GeV^2)", 1000, -4, 4, 1000, -0.1, 0.15)
    HistoD4A.Sumw2()

    HistoD5 = ROOT.TH1F("DataYProton", "Y for Protons (Data); Y - Y_CM; Events", 500, -1, 1)
    HistoD5.Sumw2()

    HistoD6 = ROOT.TH1F("DataYKaon", "Y for Kaons (Data); Y - Y_CM; Events", 500, -1, 1)
    HistoD6.Sumw2()

    HistoD7 = ROOT.TH1F("DataYPion", "Y for Pions (Data); Y - Y_CM; Events", 500, -1, 1)
    HistoD7.Sumw2()

    HistoD8 = ROOT.TH1F("DataPtProton", "Pt for Protons, m^2 cut only (Data); Pt (GeV); Events", 500, 0, 2)
    HistoD8.Sumw2()

    HistoD9 = ROOT.TH1F("DataPtKaon", "Pt for Kaons, m^2 cut only (Data); Pt (GeV); Events", 500, 0, 2)
    HistoD9.Sumw2()

    HistoD10 = ROOT.TH1F("DataPtPion", "Pt for Pions, m^2 cut only (Data); Pt (GeV); Events", 500, 0, 2)
    HistoD10.Sumw2()

    HistoD11 = ROOT.TH1F("DataMultiplicity", "Multiplicity (Data); Multiplicity; Events", 200, 0, 200)
    HistoD11.Sumw2()

    HistoD12 = ROOT.TH2F("DatadEdxVsP", "dE/dx vs p (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10)
    HistoD12.Sumw2()

    HistoD13 = ROOT.TH2F("DatadEdxVsPPion", "dE/dx vs p for Pions (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10)
    HistoD13.Sumw2()

    HistoD14 = ROOT.TH2F("DatadEdxVsPKaon", "dE/dx vs p for Kaons (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10)
    HistoD14.Sumw2()

    HistoD15 = ROOT.TH2F("DatadEdxVsPProton", "dE/dx vs p for Protons (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10)
    HistoD15.Sumw2()

    HistoD16 = ROOT.TH2F("DatadEdxVsPDeuteron", "dE/dx vs p for Deuterons (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10)
    HistoD16.Sumw2()

    HistoD17 = ROOT.TH2F("DatadEdxVsPTriton", "dE/dx vs p for Tritons (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10)
    HistoD17.Sumw2()

    HistoD18 = ROOT.TH2F("DataMSquaredVsQPProton", "m^2 vs q|p| for Protons (Data); q|p| (GeV); m^2 (GeV^2)", 1000, -4, 4, 1000, -0.1, 1.5)
    HistoD18.Sumw2()

    HistoD19 = ROOT.TH2F("DataMSquaredVsQPKaon", "m^2 vs q|p| for Kaons (Data); q|p| (GeV); m^2 (GeV^2)", 1000, -4, 4, 1000, -0.1, 1.5)
    HistoD19.Sumw2()

    HistoD20 = ROOT.TH2F("DataMSquaredVsQPPion", "m^2 vs q|p| for Pions (Data); q|p| (GeV); m^2 (GeV^2)", 1000, -4, 4, 1000, -0.1, 1.5)
    HistoD20.Sumw2()

    HistoD21 = ROOT.TH1F("DataPtProtonBothCuts", "Pt for Protons, m^2 and dE/dx cuts (Data); Pt (GeV); Events", 500, 0, 2)
    HistoD21.Sumw2()

    HistoD22 = ROOT.TH1F("DataPtKaonBothCuts", "Pt for Kaons, m^2 and dE/dx cuts (Data); Pt (GeV); Events", 500, 0, 2)
    HistoD22.Sumw2()

    HistoD23 = ROOT.TH1F("DataPtPionBothCuts", "Pt for Pions, m^2 and dE/dx cuts (Data); Pt (GeV); Events", 500, 0, 2)
    HistoD23.Sumw2()

    HistoD24 = ROOT.TH2F("DataNSigmaPrVsQPProton", "NSigmaPr vs q|p| for Protons (Data); q|p| (GeV); NSigmaPr", 1000, -4, 4, 1000, -3, 3)
    HistoD24.Sumw2()

    HistoD25 = ROOT.TH2F("DataNSigmaKaVsQPKaon", "NSigmaKa vs q|p| for Kaons (Data); q|p| (GeV); NSigmaKa", 1000, -4, 4, 1000, -3, 3)
    HistoD25.Sumw2()

    HistoD26 = ROOT.TH2F("DataNSigmaPiVsQPPion", "NSigmaPi vs q|p| for Pions (Data); Pt (GeV); NSigmaPi", 1000, -4, 4, 1000, -3, 3)
    HistoD26.Sumw2()

    HistoD27 = ROOT.TH2F("DataPtVsYProton", "Pt vs Y for Protons (Data); Y - Y_CM; Pt (Gev)", 500, -1, 1, 1000, 0, 3)
    HistoD27.Sumw2()
    
    HistoD27A = ROOT.TH2F("DataPtVsYDeuteron", "Pt vs Y for Deuterons (Data); Y - Y_CM; Pt (Gev)", 500, -1, 1, 1000, 0, 5)
    HistoD27A.Sumw2()
    
    HistoD27B = ROOT.TH2F("DataPtVsYTriton", "Pt vs Y for Tritons (Data); Y - Y_CM; Pt (Gev)", 500, -1, 1, 1000, 0, 7)
    HistoD27B.Sumw2()

    HistoD28 = ROOT.TH2F("DataPtVsYKaonPlus", "Pt vs Y for K+ (Data); Y - Y_CM; Pt (Gev)", 500, -1, 1, 1000, 0, 2.5)
    HistoD28.Sumw2()

    HistoD29 = ROOT.TH2F("DataPtVsYKaonMinus", "Pt vs Y for K- (Data); Y - Y_CM; Pt (Gev)", 500, -1, 1, 1000, 0, 2.5)
    HistoD29.Sumw2()

    HistoD30 = ROOT.TH2F("DataPtVsYPionPlus", "Pt vs Y for Pi+ (Data); Y - Y_CM; Pt (Gev)", 500, -1, 1, 1000, 0, 2.5)
    HistoD30.Sumw2()

    HistoD31 = ROOT.TH2F("DataPtVsYPionMinus", "Pt vs Y for Pi- (Data); Y - Y_CM; Pt (Gev)", 500, -1, 1, 1000, 0, 2.5)
    HistoD31.Sumw2()

    HistoD32 = ROOT.TH1F("DataPhiTPC", "TPC Phi (Data); Phi; Events", 500, -3.5, 3.5)
    HistoD32.Sumw2()

    HistoD32A = ROOT.TH1F("DataPhiEPD", "EPD Phi (Data); Phi; Events", 500, -3.5, 3.5)
    HistoD32A.Sumw2()

    HistoD32B = ROOT.TH2F("DataEPDEastRingVsEta", "EPD East Ring vs Eta; Eta; Ring Number", 500, -6, -1, 500, 0.5, 16.5)
    HistoD32B.Sumw2()

    HistoD33 = ROOT.TH1F("DataPsi1RawInnerEPD", "Reaction Plane Angle, Psi_1, Inner EPD (Data); Psi; Events", 500, -3.5, 3.5)
    HistoD33.Sumw2()

    HistoD36 = ROOT.TH1F("DataPsi1RawOuterEPD", "Reaction Plane Angle, Psi_1, Outer EPD (Data); Psi; Events", 500, -3.5, 3.5)
    HistoD36.Sumw2()

    HistoD39 = ROOT.TH1F("DataPsi1RawTPC", "Reaction Plane Angle, Psi_1, TPC (Data); Psi; Events", 500, -3.5, 3.5)
    HistoD39.Sumw2()
    
    HistoD42 = ROOT.TProfile("DataVnVsYPsi1RawInnerEPDProton", "V" + str(nV) + " Observed vs Y for Protons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD42.Sumw2()
    
    HistoD42A = ROOT.TProfile("DataVnVsYPsi1RawInnerEPDDeuteron", "V" + str(nV) + " Observed vs Y for Deuterons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD42A.Sumw2()

    HistoD42B = ROOT.TProfile("DataVnVsYPsi1RawInnerEPDTriton", "V" + str(nV) + " Observed vs Y for Tritons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD42B.Sumw2()

    HistoD45 = ROOT.TProfile("DataVnVsYPsi1RawInnerEPDKaonPlus", "V" + str(nV) + " Observed vs Y for K+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD45.Sumw2()

    HistoD45A = ROOT.TProfile("DataVnVsYPsi1RawInnerEPDKaonMinus", "V" + str(nV) + " Observed vs Y for K-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD45A.Sumw2()

    HistoD48 = ROOT.TProfile("DataVnVsYPsi1RawInnerEPDPionPlus", "V" + str(nV) + " Observed vs Y for Pi+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD48.Sumw2()

    HistoD48A = ROOT.TProfile("DataVnVsYPsi1RawInnerEPDPionMinus", "V" + str(nV) + " Observed vs Y for Pi-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD48A.Sumw2()


    for entryNum in range (0, AutreeData.GetEntries()):
        if (entryNum % 5000 == 0):
            print("Data First Pass (Raw Values and Kinematics)", entryNum)

        AutreeData.GetEntry(entryNum)

        px = AutreeData.Px
        py = AutreeData.Py
        pz = AutreeData.Pz
        q = AutreeData.Charge
        tofBeta = AutreeData.tofBeta
        dEdx = AutreeData.dEdx
        NSigmaPr = AutreeData.nSigmaPr
        NSigmaKa = AutreeData.nSigmaKa
        NSigmaPi = AutreeData.nSigmaPi
        vx = AutreeData.Vx
        vy = AutreeData.Vy
        vz = AutreeData.Vz
        EPDnMIP = AutreeData.EPDnMip
        EPDID = AutreeData.EPDid

        ProtonMass = 0.938
        KaonMass = 0.494
        PionMass = 0.140
        DeuteronMass = 1.875613
        TritonMass = 2.808921

        Multiplicity = len(px)

        InnerEPDQx = 0
        InnerEPDQy = 0
        OuterEPDQx = 0
        OuterEPDQy = 0
        TPCQx = 0
        TPCQy = 0

        for index in range(len(px)):
            pt = Pt(px[index], py[index])

            p = P(px[index], py[index], pz[index])

            eta = Eta(px[index], py[index], pz[index])

            qp = QP(q[index], px[index], py[index], pz[index])

            phi = Phi(px[index], py[index])

            DAndT = ROOT.DeuteronsAndTritons(p, dEdx[index], tofBeta[index])
            
            IsDeuteron = DAndT.IsDeuteron()
            IsTriton = DAndT.IsTriton()
            
            if(IsDeuteron):
                mass = DeuteronMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                HistoD16.Fill(p, dEdx[index])
                HistoD27A.Fill(y - yCMShift, pt)

            elif(IsTriton):
                mass = TritonMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                HistoD17.Fill(p, dEdx[index])
                HistoD27B.Fill(y - yCMShift, pt)
                
#             if(tofBeta[index] <= 0):
#                 HistoD24.Fill(qp, NSigmaPr[index])
#                 HistoD25.Fill(qp, NSigmaKa[index])
#                 HistoD26.Fill(qp, NSigmaPi[index])
                    
#                 if((abs(NSigmaPr[index]) < NSigmaPrBound) and (p < 2.0)):
#                     mass = ProtonMass
                    
#                     energy = Energy(px[index], py[index], pz[index], mass)

#                     y = Y(px[index], py[index], pz[index], mass)

#                     HistoD27.Fill(y - yCMShift, pt)
                    
                    

            if(tofBeta[index] > 0):

                msquared = MSquared(px[index], py[index], pz[index], tofBeta[index])

                HistoD4.Fill(qp, msquared)
                HistoD4A.Fill(qp, msquared)

                HistoD24.Fill(qp, NSigmaPr[index])
                HistoD25.Fill(qp, NSigmaKa[index])
                HistoD26.Fill(qp, NSigmaPi[index])

                # Proton criteria
                if((abs(NSigmaPr[index]) < NSigmaPrBound) and (msquared > ProtonLowerMSquared) and (msquared < ProtonUpperMSquared)): 
                    mass = ProtonMass

                    energy = Energy(px[index], py[index], pz[index], mass)

                    y = Y(px[index], py[index], pz[index], mass)

                    HistoD5.Fill(y - yCMShift)
                    HistoD8.Fill(pt)
                    HistoD15.Fill(p, dEdx[index])
                    HistoD18.Fill(qp, msquared)

                    HistoD21.Fill(pt)

                    HistoD27.Fill(y - yCMShift, pt)

                # Kaon criteria
                elif((abs(NSigmaKa[index]) < NSigmaKaBound) and (msquared > KaonLowerMSquared) and (msquared < KaonUpperMSquared)):
                    mass = KaonMass

                    energy = Energy(px[index], py[index], pz[index], mass)

                    y = Y(px[index], py[index], pz[index], mass)

                    HistoD22.Fill(pt)

                    HistoD6.Fill(y - yCMShift)
                    HistoD9.Fill(pt)
                    HistoD14.Fill(p, dEdx[index])
                    HistoD19.Fill(qp, msquared)

                    if(q[index] > 0):
                        HistoD28.Fill(y - yCMShift, pt)

                    elif(q[index] < 0):
                        HistoD29.Fill(y - yCMShift, pt)

                # Pion criteria
                elif((abs(NSigmaPi[index]) < NSigmaPiBound) and (msquared > PionLowerMSquared) and (msquared < PionUpperMSquared)):
                    mass = PionMass

                    energy = Energy(px[index], py[index], pz[index], mass)

                    y = Y(px[index], py[index], pz[index], mass)

                    HistoD23.Fill(pt)

                    HistoD7.Fill(y - yCMShift)
                    HistoD10.Fill(pt)
                    HistoD13.Fill(p, dEdx[index])
                    HistoD20.Fill(qp, msquared)

                    if(q[index] > 0):
                        HistoD30.Fill(y - yCMShift, pt)

                    elif(q[index] < 0):
                        HistoD31.Fill(y - yCMShift, pt)

            HistoD1.Fill(pt)
            HistoD2.Fill(eta)
            HistoD3.Fill(eta, pt)
            HistoD11.Fill(Multiplicity)
            HistoD12.Fill(p, dEdx[index])
            HistoD32.Fill(phi)

        GoodTracksCounterInnerEPD = 0
        GoodTracksCounterOuterEPD = 0
        GoodTracksCounterTPC = 0

        for index in range(len(px)):
            p = P(px[index], py[index], pz[index])

            eta = Eta(px[index], py[index], pz[index])

            if ((eta > TPCLowerLimit) and (eta < TPCUpperLimit)):
                GoodTracksCounterTPC += 1

        for index in range(len(EPDID)):
            if(EPDID[index] > 0):
                continue

            TileVector = ROOT.EPDKinematics(EPDID[index], vx, vy, vz)

            eta = TileVector.EPDEta()

            RingNumber = TileVector.EPDRow()

            HistoD32B.Fill(eta, RingNumber)

            if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
                GoodTracksCounterInnerEPD += 1

            if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
                GoodTracksCounterOuterEPD += 1

        if((GoodTracksCounterInnerEPD < NumberOfGoodTracksInnerEPD) or (GoodTracksCounterOuterEPD < NumberOfGoodTracksOuterEPD) or (GoodTracksCounterTPC < NumberOfGoodTracksTPC)):
            continue

        for index in range(len(px)):
            pt = Pt(px[index], py[index])

            p = P(px[index], py[index], pz[index])

            eta = Eta(px[index], py[index], pz[index])

            phi = Phi(px[index], py[index])

            if ((eta > TPCLowerLimit) and (eta < TPCUpperLimit)):
                TPCQy += pt*sin(nPsi*phi)
                TPCQx += pt*cos(nPsi*phi)

        for index in range(len(EPDID)):
            if(EPDID[index] > 0):
                continue

            TileVector = ROOT.EPDKinematics(EPDID[index], vx, vy, vz)

            phi = TileVector.EPDPhi()

            HistoD32A.Fill(phi)

            if(EPDnMIP[index] < 0.3):
                EPDnMIP[index] = 0

            if(EPDnMIP[index] > 2.0):
                EPDnMIP[index] = 2.0

            if(nV % 2 == 0):
                if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
                    InnerEPDQy += EPDnMIP[index]*sin(nPsi*phi)
                    InnerEPDQx += EPDnMIP[index]*cos(nPsi*phi)

                if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
                    OuterEPDQy += EPDnMIP[index]*sin(nPsi*phi)
                    OuterEPDQx += EPDnMIP[index]*cos(nPsi*phi)
                
            else:
                if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
                    InnerEPDQy -= EPDnMIP[index]*sin(nPsi*phi)
                    InnerEPDQx -= EPDnMIP[index]*cos(nPsi*phi)

                if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
                    OuterEPDQy -= EPDnMIP[index]*sin(nPsi*phi)
                    OuterEPDQx -= EPDnMIP[index]*cos(nPsi*phi)

        if((InnerEPDQx == 0) and (InnerEPDQy == 0)):
            continue
            
        if((OuterEPDQx == 0) and (OuterEPDQy == 0)):
            continue
            
        if((TPCQx == 0) and (TPCQy == 0)):
            continue
            
        HistoInnerEPDQxRaw.Fill(InnerEPDQx)
        HistoInnerEPDQyRaw.Fill(InnerEPDQy)
        HistoOuterEPDQxRaw.Fill(OuterEPDQx)
        HistoOuterEPDQyRaw.Fill(OuterEPDQy)    
        HistoTPCQxRaw.Fill(TPCQx)
        HistoTPCQyRaw.Fill(TPCQy)
            
        PsiInnerEPDRaw = (1/nPsi)*atan2(InnerEPDQy, InnerEPDQx)
        PsiOuterEPDRaw = (1/nPsi)*atan2(OuterEPDQy, OuterEPDQx)
        PsiTPCRaw = (1/nPsi)*atan2(TPCQy, TPCQx)

        HistoD33.Fill(PsiInnerEPDRaw)
        HistoD36.Fill(PsiOuterEPDRaw)
        HistoD39.Fill(PsiTPCRaw)

        for index in range(len(px)):
            
            pt = Pt(px[index], py[index])

            p = P(px[index], py[index], pz[index])

            eta = Eta(px[index], py[index], pz[index])

            phi = Phi(px[index], py[index])
            
            DAndT = ROOT.DeuteronsAndTritons(p, dEdx[index], tofBeta[index])
            
            IsDeuteron = DAndT.IsDeuteron()
            IsTriton = DAndT.IsTriton()
            
            if((IsDeuteron) and (pt > DeuteronLowerPt) and (pt < DeuteronUpperPt)):
                mass = DeuteronMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                VnInnerEPDRaw = V_n(nV, px[index], py[index], PsiInnerEPDRaw)

                if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                    HistoD42A.Fill(y - yCMShift, VnInnerEPDRaw)

            elif((IsTriton) and (pt > TritonLowerPt) and (pt < TritonUpperPt)):
                mass = TritonMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                VnInnerEPDRaw = V_n(nV, px[index], py[index], PsiInnerEPDRaw)

                if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                    HistoD42B.Fill(y - yCMShift, VnInnerEPDRaw)
                    
            
#             if(tofBeta[index] < 0):
                
#                 if((abs(NSigmaPr[index]) < NSigmaPrBound) and (pt > ProtonLowerPt) and (pt < ProtonUpperPt) and (p < 2.0)): 
#                     mass = ProtonMass

#                     energy = Energy(px[index], py[index], pz[index], mass)

#                     y = Y(px[index], py[index], pz[index], mass)

#                     VnInnerEPDRaw = V_n(nV, px[index], py[index], PsiInnerEPDRaw)
                    
#                     if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
#                         HistoD42.Fill(y - yCMShift, VnInnerEPDRaw)


            if(tofBeta[index] > 0):

                msquared = MSquared(px[index], py[index], pz[index], tofBeta[index])

                if((abs(NSigmaPr[index]) < NSigmaPrBound) and (msquared > ProtonLowerMSquared) and (msquared < ProtonUpperMSquared) and (pt > ProtonLowerPt) and (pt < ProtonUpperPt)): 
                    mass = ProtonMass

                    energy = Energy(px[index], py[index], pz[index], mass)

                    y = Y(px[index], py[index], pz[index], mass)

                    VnInnerEPDRaw = V_n(nV, px[index], py[index], PsiInnerEPDRaw)
                    
                    if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                        HistoD42.Fill(y - yCMShift, VnInnerEPDRaw)

                if((abs(NSigmaKa[index]) < NSigmaKaBound) and (msquared > KaonLowerMSquared) and (msquared < KaonUpperMSquared) and (pt > KaonLowerPt) and (pt < KaonUpperPt)): 
                    mass = KaonMass

                    energy = Energy(px[index], py[index], pz[index], mass)

                    y = Y(px[index], py[index], pz[index], mass)

                    VnInnerEPDRaw = V_n(nV, px[index], py[index], PsiInnerEPDRaw)
                    
                    if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                        if(q[index] > 0):
                            HistoD45.Fill(y - yCMShift, VnInnerEPDRaw)

                        if(q[index] < 0):
                            HistoD45A.Fill(y - yCMShift, VnInnerEPDRaw)

                if((abs(NSigmaPi[index]) < NSigmaPiBound) and (msquared > PionLowerMSquared) and (msquared < PionUpperMSquared)  and (pt > PionLowerPt) and (pt < PionUpperPt)): 
                    mass = PionMass

                    energy = Energy(px[index], py[index], pz[index], mass)

                    y = Y(px[index], py[index], pz[index], mass)

                    VnInnerEPDRaw = V_n(nV, px[index], py[index], PsiInnerEPDRaw)

                    if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                        if(q[index] > 0):
                            HistoD48.Fill(y - yCMShift, VnInnerEPDRaw)

                        if(q[index] < 0):
                            HistoD48A.Fill(y - yCMShift, VnInnerEPDRaw)

    HistoInnerEPDQxRaw.SetDirectory(0)
    HistoInnerEPDQyRaw.SetDirectory(0)
    HistoOuterEPDQxRaw.SetDirectory(0)
    HistoOuterEPDQyRaw.SetDirectory(0)
    HistoTPCQxRaw.SetDirectory(0)
    HistoTPCQyRaw.SetDirectory(0)
    HistoD1.SetDirectory(0)
    HistoD2.SetDirectory(0)
    HistoD3.SetDirectory(0)
    HistoD4.SetDirectory(0)
    HistoD4A.SetDirectory(0)
    HistoD5.SetDirectory(0)
    HistoD6.SetDirectory(0)
    HistoD7.SetDirectory(0)
    HistoD8.SetDirectory(0)
    HistoD9.SetDirectory(0)
    HistoD10.SetDirectory(0)
    HistoD11.SetDirectory(0)
    HistoD12.SetDirectory(0)
    HistoD13.SetDirectory(0)
    HistoD14.SetDirectory(0)
    HistoD15.SetDirectory(0)
    HistoD16.SetDirectory(0)
    HistoD17.SetDirectory(0)
    HistoD18.SetDirectory(0)
    HistoD19.SetDirectory(0)
    HistoD20.SetDirectory(0)
    HistoD21.SetDirectory(0)
    HistoD22.SetDirectory(0)
    HistoD23.SetDirectory(0)
    HistoD24.SetDirectory(0)
    HistoD25.SetDirectory(0)
    HistoD26.SetDirectory(0)
    HistoD27.SetDirectory(0)
    HistoD27A.SetDirectory(0)
    HistoD27B.SetDirectory(0)
    HistoD28.SetDirectory(0)
    HistoD29.SetDirectory(0)
    HistoD30.SetDirectory(0)
    HistoD31.SetDirectory(0)
    HistoD32.SetDirectory(0)
    HistoD32A.SetDirectory(0)
    HistoD32B.SetDirectory(0)
    HistoD33.SetDirectory(0)
    HistoD36.SetDirectory(0)
    HistoD39.SetDirectory(0)
    HistoD42.SetDirectory(0)
    HistoD42A.SetDirectory(0)
    HistoD42B.SetDirectory(0)
    HistoD45.SetDirectory(0)
    HistoD45A.SetDirectory(0)
    HistoD48.SetDirectory(0)
    HistoD48A.SetDirectory(0)
    
    
    QVectorHistograms.append(HistoInnerEPDQxRaw)
    QVectorHistograms.append(HistoInnerEPDQyRaw)
    QVectorHistograms.append(HistoOuterEPDQxRaw)
    QVectorHistograms.append(HistoOuterEPDQyRaw)
    QVectorHistograms.append(HistoTPCQxRaw)
    QVectorHistograms.append(HistoTPCQyRaw)
    Histograms.append(HistoD1)
    Histograms.append(HistoD2)
    Histograms.append(HistoD3)
    Histograms.append(HistoD4)
    Histograms.append(HistoD4A)
    Histograms.append(HistoD5)
    Histograms.append(HistoD6)
    Histograms.append(HistoD7)
    Histograms.append(HistoD8)
    Histograms.append(HistoD9)
    Histograms.append(HistoD10)
    Histograms.append(HistoD11)
    Histograms.append(HistoD12)
    Histograms.append(HistoD13)
    Histograms.append(HistoD14)
    Histograms.append(HistoD15)
    Histograms.append(HistoD16)
    Histograms.append(HistoD17)
    Histograms.append(HistoD18)
    Histograms.append(HistoD19)
    Histograms.append(HistoD20)
    Histograms.append(HistoD21)
    Histograms.append(HistoD22)
    Histograms.append(HistoD23)
    Histograms.append(HistoD24)
    Histograms.append(HistoD25)
    Histograms.append(HistoD26)
    Histograms.append(HistoD27)
    Histograms.append(HistoD27A)
    Histograms.append(HistoD27B)
    Histograms.append(HistoD28)
    Histograms.append(HistoD29)
    Histograms.append(HistoD30)
    Histograms.append(HistoD31)
    Histograms.append(HistoD32)
    Histograms.append(HistoD32A)
    Histograms.append(HistoD32B)
    Histograms.append(HistoD33)
    Histograms.append(HistoD36)
    Histograms.append(HistoD39)
    Histograms.append(HistoD42)
    Histograms.append(HistoD42A)
    Histograms.append(HistoD42B)
    Histograms.append(HistoD45)
    Histograms.append(HistoD45A)
    Histograms.append(HistoD48)
    Histograms.append(HistoD48A)
    
    
    Data.Close()

    #QVectorHistogramRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/QVectorFirstPassTest.root", "RECREATE")
    QVectorHistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/QVectorFirstPass" + sys.argv[2] + ".root", "RECREATE")
    QVectorHistogramRootFile.cd()

    for index in range(0,len(QVectorHistograms)):
        QVectorHistograms[index].Write()

    QVectorHistogramRootFile.Close()

    
    
    #HistogramRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/HistogramFirstPassTest.root", "RECREATE")
    HistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/HistogramFirstPass" + sys.argv[2] + ".root", "RECREATE")
    HistogramRootFile.cd()

    for index in range(0,len(Histograms)):
        Histograms[index].Write()

    HistogramRootFile.Close()


    print("Done")
################################################################################################################
if(RunIteration == 2):
    Data = ROOT.TFile.Open(sys.argv[1])
    #Data = ROOT.TFile.Open("/star/data01/pwg/cracz/Data_3p0GeV_FXT/FXT_3p0GeV_SL20d_2018_127.root")

    AutreeData = Data.Get("Autree")

    QVectorHistograms = []
    Histograms = []

        
        
        
    #QVectorHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/QVectorFirstPassTest.root")
    QVectorHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/QVectorFirstPass.root")
    #HistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/HistogramFirstPassTest.root")
    HistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/HistogramFirstPass.root")
    
    
    HistoInnerEPDQxRecentered = ROOT.TH1D("InnerEPDQxRecentered", "Qx Recentered for Inner EPD; Qx; Events", 250, -QBounds, QBounds)
    HistoInnerEPDQyRecentered = ROOT.TH1D("InnerEPDQyRecentered", "Qy Recentered for Inner EPD; Qy; Events", 250, -QBounds, QBounds)
    HistoOuterEPDQxRecentered = ROOT.TH1D("OuterEPDQxRecentered", "Qx Recentered for Outer EPD; Qx; Events", 250, -QBounds, QBounds)
    HistoOuterEPDQyRecentered = ROOT.TH1D("OuterEPDQyRecentered", "Qy Recentered for Inner EPD; Qy; Events", 250, -QBounds, QBounds)
    HistoTPCQxRecentered = ROOT.TH1D("TPCQxRecentered", "Qx Recentered for TPC; Qx; Events", 250, -QBounds, QBounds)
    HistoTPCQyRecentered = ROOT.TH1D("TPCQyRecentered", "Qy Recentered for TPC; Qy; Events", 250, -QBounds, QBounds)
    
    
    HistoInnerEPDSineAverages = ROOT.TProfile("InnerEPDSineAverages", "Inner EPD Sine Averages; j; Sine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1)
    HistoInnerEPDCosineAverages = ROOT.TProfile("InnerEPDCosineAverages", "Inner EPD Cosine Averages; j; Cosine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1)
    HistoOuterEPDSineAverages = ROOT.TProfile("OuterEPDSineAverages", "Outer EPD Sine Averages; j; Sine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1)
    HistoOuterEPDCosineAverages = ROOT.TProfile("OuterEPDCosineAverages", "Outer EPD Cosine Averages; j; Cosine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1)
    HistoTPCSineAverages = ROOT.TProfile("TPCSineAverages", "TPC Sine Averages; j; Sine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1)
    HistoTPCCosineAverages = ROOT.TProfile("TPCCosineAverages", "TPC Cosine Averages; j; Cosine Correction Term", FourierCorrectionTerms, 1, FourierCorrectionTerms + 1)
    
    
    

    HistoD34 = ROOT.TH1F("DataPsi1RecenteredInnerEPD", "Reaction Plane Angle, Psi_1, Inner EPD (Data); Psi; Events", 500, -3.5, 3.5)
    HistoD34.Sumw2()
    
    HistoD37 = ROOT.TH1F("DataPsi1RecenteredOuterEPD", "Reaction Plane Angle, Psi_1, Outer EPD (Data); Psi; Events", 500, -3.5, 3.5)
    HistoD37.Sumw2()    
    
    HistoD40 = ROOT.TH1F("DataPsi1RecenteredTPC", "Reaction Plane Angle, Psi_1, TPC (Data); Psi; Events", 500, -3.5, 3.5)
    HistoD40.Sumw2()    

    HistoD43 = ROOT.TProfile("DataVnVsYPsi1RecenteredInnerEPDProton", "V" + str(nV) + " Observed vs Y for Protons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD43.Sumw2()

    HistoD43A = ROOT.TProfile("DataVnVsYPsi1RecenteredInnerEPDDeuteron", "V" + str(nV) + " Observed vs Y for Deuterons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD43A.Sumw2()

    HistoD43B = ROOT.TProfile("DataVnVsYPsi1RecenteredInnerEPDTriton", "V" + str(nV) + " Observed vs Y for Tritons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD43B.Sumw2()
    
    HistoD46 = ROOT.TProfile("DataVnVsYPsi1RecenteredInnerEPDKaonPlus", "V" + str(nV) + " Observed vs Y for K+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD46.Sumw2()

    HistoD46A = ROOT.TProfile("DataVnVsYPsi1RecenteredInnerEPDKaonMinus", "V" + str(nV) + " Observed vs Y for K-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD46A.Sumw2()    

    HistoD49 = ROOT.TProfile("DataVnVsYPsi1RecenteredInnerEPDPionPlus", "V" + str(nV) + " Observed vs Y for Pi+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD49.Sumw2()

    HistoD49A = ROOT.TProfile("DataVnVsYPsi1RecenteredInnerEPDPionMinus", "V" + str(nV) + " Observed vs Y for Pi-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD49A.Sumw2()




    # Loop through every event; skip anything with a PID not equal to a p,K, or pi; we shift the Q-vectors now
    for entryNum in range (0, AutreeData.GetEntries()):
        if (entryNum % 5000 == 0):
            print("Data Second Pass (Recentered Values)", entryNum)

        AutreeData.GetEntry(entryNum)

        px = AutreeData.Px
        py = AutreeData.Py
        pz = AutreeData.Pz
        q = AutreeData.Charge
        tofBeta = AutreeData.tofBeta
        dEdx = AutreeData.dEdx
        NSigmaPr = AutreeData.nSigmaPr
        NSigmaKa = AutreeData.nSigmaKa
        NSigmaPi = AutreeData.nSigmaPi
        vx = AutreeData.Vx
        vy = AutreeData.Vy
        vz = AutreeData.Vz
        EPDnMIP = AutreeData.EPDnMip
        EPDID = AutreeData.EPDid

        ProtonID = 2212
        KaonPlusID = 321
        PionPlusID = 211

        ProtonMass = 0.938
        KaonMass = 0.494
        PionMass = 0.140
        DeuteronMass = 1.875613
        TritonMass = 2.808921

        InnerEPDQx = 0
        InnerEPDQy = 0
        OuterEPDQx = 0
        OuterEPDQy = 0
        TPCQx = 0
        TPCQy = 0
        
        InnerEPDQxMean = QVectorHistogramFile.Get("InnerEPDQxRaw").GetMean()
        InnerEPDQyMean = QVectorHistogramFile.Get("InnerEPDQyRaw").GetMean()
        OuterEPDQxMean = QVectorHistogramFile.Get("OuterEPDQxRaw").GetMean()
        OuterEPDQyMean = QVectorHistogramFile.Get("OuterEPDQyRaw").GetMean()
        TPCQxMean = QVectorHistogramFile.Get("TPCQxRaw").GetMean()
        TPCQyMean = QVectorHistogramFile.Get("TPCQyRaw").GetMean()

        GoodTracksCounterInnerEPD = 0
        GoodTracksCounterOuterEPD = 0
        GoodTracksCounterTPC = 0

        for index in range(len(px)):
            p = P(px[index], py[index], pz[index])

            eta = Eta(px[index], py[index], pz[index])

            if ((eta > TPCLowerLimit) and (eta < TPCUpperLimit)):
                GoodTracksCounterTPC += 1  

        for index in range(len(EPDID)):
            if(EPDID[index] > 0):
                continue

            TileVector = ROOT.EPDKinematics(EPDID[index], vx, vy, vz)

            if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
                GoodTracksCounterInnerEPD += 1

            if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
                GoodTracksCounterOuterEPD += 1

        if((GoodTracksCounterInnerEPD < NumberOfGoodTracksInnerEPD) or (GoodTracksCounterOuterEPD < NumberOfGoodTracksOuterEPD) or (GoodTracksCounterTPC < NumberOfGoodTracksTPC)):
            continue
            
        for index in range(len(px)):
            pt = Pt(px[index], py[index])

            p = P(px[index], py[index], pz[index])

            eta = Eta(px[index], py[index], pz[index])

            phi = Phi(px[index], py[index])

            if ((eta > TPCLowerLimit) and (eta < TPCUpperLimit)):
                TPCQy += pt*sin(nPsi*phi)
                TPCQx += pt*cos(nPsi*phi)

        for index in range(len(EPDID)):
            if(EPDID[index] > 0):
                continue

            TileVector = ROOT.EPDKinematics(EPDID[index], vx, vy, vz)

            phi = TileVector.EPDPhi()

            if(EPDnMIP[index] < 0.3):
                EPDnMIP[index] = 0

            if(EPDnMIP[index] > 2.0):
                EPDnMIP[index] = 2.0

            if(nV % 2 == 0):
                if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
                    InnerEPDQy += EPDnMIP[index]*sin(nPsi*phi)
                    InnerEPDQx += EPDnMIP[index]*cos(nPsi*phi)

                if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
                    OuterEPDQy += EPDnMIP[index]*sin(nPsi*phi)
                    OuterEPDQx += EPDnMIP[index]*cos(nPsi*phi)
                
            else:
                if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
                    InnerEPDQy -= EPDnMIP[index]*sin(nPsi*phi)
                    InnerEPDQx -= EPDnMIP[index]*cos(nPsi*phi)

                if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
                    OuterEPDQy -= EPDnMIP[index]*sin(nPsi*phi)
                    OuterEPDQx -= EPDnMIP[index]*cos(nPsi*phi)
                    
        if((InnerEPDQx == 0) and (InnerEPDQy == 0)):
            continue
            
        if((OuterEPDQx == 0) and (OuterEPDQy == 0)):
            continue
            
        if((TPCQx == 0) and (TPCQy == 0)):
            continue        
            
        HistoInnerEPDQxRecentered.Fill(InnerEPDQx - InnerEPDQxMean)
        HistoInnerEPDQyRecentered.Fill(InnerEPDQy - InnerEPDQyMean)
            
        HistoOuterEPDQxRecentered.Fill(OuterEPDQx - OuterEPDQxMean)
        HistoOuterEPDQyRecentered.Fill(OuterEPDQy - OuterEPDQyMean)
            
        HistoTPCQxRecentered.Fill(TPCQx - TPCQxMean)
        HistoTPCQyRecentered.Fill(TPCQy - TPCQyMean)

        PsiInnerEPDRecentered = (1/nPsi)*atan2(InnerEPDQy - InnerEPDQyMean, InnerEPDQx - InnerEPDQxMean)
        PsiOuterEPDRecentered = (1/nPsi)*atan2(OuterEPDQy - OuterEPDQyMean, OuterEPDQx - OuterEPDQxMean)
        PsiTPCRecentered = (1/nPsi)*atan2(TPCQy - TPCQyMean, TPCQx - TPCQxMean)

        HistoD34.Fill(PsiInnerEPDRecentered)
        HistoD37.Fill(PsiOuterEPDRecentered)
        HistoD40.Fill(PsiTPCRecentered)
        
        for j in range(1, FourierCorrectionTerms + 1):
            HistoInnerEPDSineAverages.Fill(j, -1*sin(j*nPsi*PsiInnerEPDRecentered))
            HistoInnerEPDCosineAverages.Fill(j, cos(j*nPsi*PsiInnerEPDRecentered))
            HistoOuterEPDSineAverages.Fill(j, -1*sin(j*nPsi*PsiOuterEPDRecentered))
            HistoOuterEPDCosineAverages.Fill(j, cos(j*nPsi*PsiOuterEPDRecentered))
            HistoTPCSineAverages.Fill(j, -1*sin(j*nPsi*PsiTPCRecentered))
            HistoTPCCosineAverages.Fill(j, cos(j*nPsi*PsiTPCRecentered))

        for index in range(len(px)):
            pt = Pt(px[index], py[index])

            p = P(px[index], py[index], pz[index])

            eta = Eta(px[index], py[index], pz[index])

            phi = Phi(px[index], py[index])
            
            DAndT = ROOT.DeuteronsAndTritons(p, dEdx[index], tofBeta[index])
            
            IsDeuteron = DAndT.IsDeuteron()
            IsTriton = DAndT.IsTriton()
            
            if((IsDeuteron) and (pt > DeuteronLowerPt) and (pt < DeuteronUpperPt)):
                mass = DeuteronMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                VnInnerEPDRecentered = V_n(nV, px[index], py[index], PsiInnerEPDRecentered)

                if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                    HistoD43A.Fill(y - yCMShift, VnInnerEPDRecentered)

            elif((IsTriton) and (pt > TritonLowerPt) and (pt < TritonUpperPt)):
                mass = TritonMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                VnInnerEPDRecentered = V_n(nV, px[index], py[index], PsiInnerEPDRecentered)

                if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                    HistoD43B.Fill(y - yCMShift, VnInnerEPDRecentered)
                

                
#             if(tofBeta[index] < 0):
                
#                 if((abs(NSigmaPr[index]) < NSigmaPrBound) and (pt > ProtonLowerPt) and (pt < ProtonUpperPt) and (p < 2.0)): 
#                     mass = ProtonMass

#                     energy = Energy(px[index], py[index], pz[index], mass)

#                     y = Y(px[index], py[index], pz[index], mass)

#                     VnInnerEPDRecentered = V_n(nV, px[index], py[index], PsiInnerEPDRecentered)
                    
#                     if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
#                         HistoD43.Fill(y - yCMShift, VnInnerEPDRecentered)

            

            if(tofBeta[index] > 0):

                msquared = MSquared(px[index], py[index], pz[index], tofBeta[index])

                if((abs(NSigmaPr[index]) < NSigmaPrBound) and (msquared > ProtonLowerMSquared) and (msquared < ProtonUpperMSquared) and (pt > ProtonLowerPt) and (pt < ProtonUpperPt)): 
                    mass = ProtonMass

                    energy = Energy(px[index], py[index], pz[index], mass)

                    y = Y(px[index], py[index], pz[index], mass)

                    VnInnerEPDRecentered = V_n(nV, px[index], py[index], PsiInnerEPDRecentered)
                    
                    if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                        HistoD43.Fill(y - yCMShift, VnInnerEPDRecentered)

                if((abs(NSigmaKa[index]) < NSigmaKaBound) and (msquared > KaonLowerMSquared) and (msquared < KaonUpperMSquared) and (pt > KaonLowerPt) and (pt < KaonUpperPt)): 
                    mass = KaonMass

                    energy = Energy(px[index], py[index], pz[index], mass)

                    y = Y(px[index], py[index], pz[index], mass)

                    VnInnerEPDRecentered = V_n(nV, px[index], py[index], PsiInnerEPDRecentered)
                    
                    if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                        if(q[index] > 0):
                            HistoD46.Fill(y - yCMShift, VnInnerEPDRecentered)

                        if(q[index] < 0):
                            HistoD46A.Fill(y - yCMShift, VnInnerEPDRecentered)

                if((abs(NSigmaPi[index]) < NSigmaPiBound) and (msquared > PionLowerMSquared) and (msquared < PionUpperMSquared) and (pt > PionLowerPt) and (pt < PionUpperPt)): 
                    mass = PionMass

                    energy = Energy(px[index], py[index], pz[index], mass)

                    y = Y(px[index], py[index], pz[index], mass)

                    VnInnerEPDRecentered = V_n(nV, px[index], py[index], PsiInnerEPDRecentered)

                    if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):                    
                        if(q[index] > 0):
                            HistoD49.Fill(y - yCMShift, VnInnerEPDRecentered)

                        if(q[index] < 0):
                            HistoD49A.Fill(y - yCMShift, VnInnerEPDRecentered)

    HistoInnerEPDQxRecentered.SetDirectory(0)
    HistoInnerEPDQyRecentered.SetDirectory(0)
    HistoOuterEPDQxRecentered.SetDirectory(0)
    HistoOuterEPDQyRecentered.SetDirectory(0)
    HistoTPCQxRecentered.SetDirectory(0)
    HistoTPCQyRecentered.SetDirectory(0)
    HistoInnerEPDSineAverages.SetDirectory(0)
    HistoInnerEPDCosineAverages.SetDirectory(0)
    HistoOuterEPDSineAverages.SetDirectory(0)
    HistoOuterEPDCosineAverages.SetDirectory(0)
    HistoTPCSineAverages.SetDirectory(0)
    HistoTPCCosineAverages.SetDirectory(0)
    HistoD34.SetDirectory(0)
    HistoD37.SetDirectory(0)
    HistoD40.SetDirectory(0)
    HistoD43.SetDirectory(0)
    HistoD43A.SetDirectory(0)
    HistoD43B.SetDirectory(0)
    HistoD46.SetDirectory(0)
    HistoD46A.SetDirectory(0)
    HistoD49.SetDirectory(0)
    HistoD49A.SetDirectory(0)
        
        
    QVectorHistograms.append(HistoInnerEPDQxRecentered)
    QVectorHistograms.append(HistoInnerEPDQyRecentered)
    QVectorHistograms.append(HistoOuterEPDQxRecentered)
    QVectorHistograms.append(HistoOuterEPDQyRecentered)
    QVectorHistograms.append(HistoTPCQxRecentered)
    QVectorHistograms.append(HistoTPCQyRecentered)        
    QVectorHistograms.append(HistoInnerEPDSineAverages)
    QVectorHistograms.append(HistoInnerEPDCosineAverages)
    QVectorHistograms.append(HistoOuterEPDSineAverages)
    QVectorHistograms.append(HistoOuterEPDCosineAverages)
    QVectorHistograms.append(HistoTPCSineAverages)
    QVectorHistograms.append(HistoTPCCosineAverages)        
    Histograms.append(HistoD34)
    Histograms.append(HistoD37)
    Histograms.append(HistoD40)
    Histograms.append(HistoD43)
    Histograms.append(HistoD43A)
    Histograms.append(HistoD43B)
    Histograms.append(HistoD46)
    Histograms.append(HistoD46A)
    Histograms.append(HistoD49)
    Histograms.append(HistoD49A)
        
    Data.Close()
    QVectorHistogramFile.Close()
    HistogramFile.Close()
    

    #QVectorHistogramRootFile = ROOT.TFile.Open("/star/u/mcgordon/mcgordon/VnFromEPD/QVectorSecondPassTest.root", "RECREATE")
    QVectorHistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/QVectorSecondPass" + sys.argv[2] + ".root", "RECREATE")
    QVectorHistogramRootFile.cd()

    for index in range(0,len(QVectorHistograms)):
        QVectorHistograms[index].Write()

    QVectorHistogramRootFile.Close()

    
    
    #HistogramRootFile = ROOT.TFile.Open("/star/u/mcgordon/mcgordon/VnFromEPD/HistogramSecondPassTest.root", "RECREATE")
    HistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/HistogramSecondPass" + sys.argv[2] + ".root", "RECREATE")
    HistogramRootFile.cd()

    for index in range(0,len(Histograms)):
        Histograms[index].Write()

    HistogramRootFile.Close()

    print("Done")
#############################################################################################################
if(RunIteration == 3):
    Data = ROOT.TFile.Open(sys.argv[1])
    #Data = ROOT.TFile.Open("/star/data01/pwg/cracz/Data_3p0GeV_FXT/FXT_3p0GeV_SL20d_2018_127.root")
    # MonteCarlo = ROOT.TFile.Open("/eos/user/m/migordon/SWAN_projects/HeavyIonStuff/CombinedMonteCarloFiles.root")

    AutreeData = Data.Get("Autree")

    Histograms = []
        

    #QVectorHistogramFileFirst = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/QVectorFirstPassTest.root")
    #QVectorHistogramFileSecond = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/QVectorSecondPassTest.root")
    QVectorHistogramFileFirst = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/QVectorFirstPass.root")
    QVectorHistogramFileSecond = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/QVectorSecondPass.root")
    #HistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/HistogramSecondPassTest.root")
    HistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/HistogramSecondPass.root")
        
        
    HistoD35 = ROOT.TH1F("DataPsi1RecenteredAndShiftedInnerEPD", "Reaction Plane Angle, Psi_1 Inner EPD (Data); Psi; Events", 500, -3.5, 3.5)
    HistoD35.Sumw2()

    HistoD38 = ROOT.TH1F("DataPsi1RecenteredAndShiftedOuterEPD", "Reaction Plane Angle, Psi_1, Outer EPD (Data); Psi; Events", 500, -3.5, 3.5)
    HistoD38.Sumw2()

    HistoD41 = ROOT.TH1F("DataPsi1RecenteredAndShiftedTPC", "Reaction Plane Angle, Psi_1, TPC (Data); Psi; Events", 500, -3.5, 3.5)
    HistoD41.Sumw2() 

    HistoD44 = ROOT.TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDProton", "V" + str(nV) + " Observed vs Y for Protons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD44.Sumw2()
    
    HistoD44A = ROOT.TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDDeuteron", "V" + str(nV) + " Observed vs Y for Deuterons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD44A.Sumw2()

    HistoD44B = ROOT.TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDTriton", "V" + str(nV) + " Observed vs Y for Tritons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD44B.Sumw2()

    HistoD47 = ROOT.TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDKaonPlus", "V" + str(nV) + " Observed vs Y for K+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD47.Sumw2()

    HistoD47A = ROOT.TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDKaonMinus", "V" + str(nV) + " Observed vs Y for K-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD47A.Sumw2()

    HistoD50 = ROOT.TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDPionPlus", "V" + str(nV) + " Observed vs Y for Pi+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD50.Sumw2()

    HistoD50A = ROOT.TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDPionMinus", "V" + str(nV) + " Observed vs Y for Pi-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD50A.Sumw2()
    
    HistoD51 = ROOT.TProfile("DataResolutionTopLeftTerm", "Resolution Top Left Term (Data); Centrality; Top Left Term", 12, 0, 12)
    HistoD51.Sumw2()

    HistoD52 = ROOT.TProfile("DataResolutionTopRightTerm", "Resolution Top Right Term (Data); Centrality; Top Right Term", 12, 0, 12)
    HistoD52.Sumw2()

    HistoD53 = ROOT.TProfile("DataResolutionBottomTerm", "Resolution Bottom Term (Data); Centrality; Bottom Term", 12, 0, 12)
    HistoD53.Sumw2()
    
    
    
    for entryNum in range (0, AutreeData.GetEntries()):
        if (entryNum % 5000 == 0):
            print("Data Third Pass (Fourier Corrected Values)", entryNum)

        AutreeData.GetEntry(entryNum)

        px = AutreeData.Px
        py = AutreeData.Py
        pz = AutreeData.Pz
        q = AutreeData.Charge
        tofBeta = AutreeData.tofBeta
        dEdx = AutreeData.dEdx
        NSigmaPr = AutreeData.nSigmaPr
        NSigmaKa = AutreeData.nSigmaKa
        NSigmaPi = AutreeData.nSigmaPi
        vx = AutreeData.Vx
        vy = AutreeData.Vy
        vz = AutreeData.Vz
        Centrality = AutreeData.centrality
        EPDnMIP = AutreeData.EPDnMip
        EPDID = AutreeData.EPDid

        ProtonID = 2212
        KaonPlusID = 321
        PionPlusID = 211

        ProtonMass = 0.938
        KaonMass = 0.494
        PionMass = 0.140
        DeuteronMass = 1.875613
        TritonMass = 2.808921

        Multiplicity = len(px)

        InnerEPDQx = 0
        InnerEPDQy = 0
        OuterEPDQx = 0
        OuterEPDQy = 0
        TPCQx = 0
        TPCQy = 0
        
        InnerEPDQxMean = QVectorHistogramFileFirst.Get("InnerEPDQxRaw").GetMean()
        InnerEPDQyMean = QVectorHistogramFileFirst.Get("InnerEPDQyRaw").GetMean()
        OuterEPDQxMean = QVectorHistogramFileFirst.Get("OuterEPDQxRaw").GetMean()
        OuterEPDQyMean = QVectorHistogramFileFirst.Get("OuterEPDQyRaw").GetMean()
        TPCQxMean = QVectorHistogramFileFirst.Get("TPCQxRaw").GetMean()
        TPCQyMean = QVectorHistogramFileFirst.Get("TPCQyRaw").GetMean()

        FourierCorrectionTermInnerEPD = 0
        FourierCorrectionTermOuterEPD = 0
        FourierCorrectionTermTPC = 0

        GoodTracksCounterInnerEPD = 0
        GoodTracksCounterOuterEPD = 0
        GoodTracksCounterTPC = 0

        for index in range(len(px)):
            p = P(px[index], py[index], pz[index])

            eta = Eta(px[index], py[index], pz[index])

            if ((eta > TPCLowerLimit) and (eta < TPCUpperLimit)):
                GoodTracksCounterTPC += 1 

        for index in range(len(EPDID)):
            if(EPDID[index] > 0):
                continue

            TileVector = ROOT.EPDKinematics(EPDID[index], vx, vy, vz)

            if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
                GoodTracksCounterInnerEPD += 1

            if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
                GoodTracksCounterOuterEPD += 1

        if((GoodTracksCounterInnerEPD < NumberOfGoodTracksInnerEPD) or (GoodTracksCounterOuterEPD < NumberOfGoodTracksOuterEPD) or (GoodTracksCounterTPC < NumberOfGoodTracksTPC)):
            continue

        for index in range(len(px)):
            pt = Pt(px[index], py[index])

            p = P(px[index], py[index], pz[index])

            eta = Eta(px[index], py[index], pz[index])

            phi = Phi(px[index], py[index])

            if ((eta > TPCLowerLimit) and (eta < TPCUpperLimit)):
                TPCQy += pt*sin(nPsi*phi)
                TPCQx += pt*cos(nPsi*phi)

        for index in range(len(EPDID)):
            if(EPDID[index] > 0):
                continue

            TileVector = ROOT.EPDKinematics(EPDID[index], vx, vy, vz)

            phi = TileVector.EPDPhi()

            if(EPDnMIP[index] < 0.3):
                EPDnMIP[index] = 0

            if(EPDnMIP[index] > 2.0):
                EPDnMIP[index] = 2.0

            if(nV % 2 == 0):
                if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
                    InnerEPDQy += EPDnMIP[index]*sin(nPsi*phi)
                    InnerEPDQx += EPDnMIP[index]*cos(nPsi*phi)

                if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
                    OuterEPDQy += EPDnMIP[index]*sin(nPsi*phi)
                    OuterEPDQx += EPDnMIP[index]*cos(nPsi*phi)
                
            else:
                if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
                    InnerEPDQy -= EPDnMIP[index]*sin(nPsi*phi)
                    InnerEPDQx -= EPDnMIP[index]*cos(nPsi*phi)

                if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
                    OuterEPDQy -= EPDnMIP[index]*sin(nPsi*phi)
                    OuterEPDQx -= EPDnMIP[index]*cos(nPsi*phi)
                
        if((InnerEPDQx == 0) and (InnerEPDQy == 0)):
            continue
            
        if((OuterEPDQx == 0) and (OuterEPDQy == 0)):
            continue
            
        if((TPCQx == 0) and (TPCQy == 0)):
            continue
                
        PsiInnerEPDRecentered = (1/nPsi)*atan2(InnerEPDQy - InnerEPDQyMean, InnerEPDQx - InnerEPDQxMean)
        PsiOuterEPDRecentered = (1/nPsi)*atan2(OuterEPDQy - OuterEPDQyMean, OuterEPDQx - OuterEPDQxMean)
        PsiTPCRecentered = (1/nPsi)*atan2(TPCQy - TPCQyMean, TPCQx - TPCQxMean)
                
        for j in range(1, FourierCorrectionTerms + 1):
            InnerEPDSineAverageJth = QVectorHistogramFileSecond.Get("InnerEPDSineAverages").GetBinContent(j)
            InnerEPDCosineAverageJth = QVectorHistogramFileSecond.Get("InnerEPDCosineAverages").GetBinContent(j)
            OuterEPDSineAverageJth = QVectorHistogramFileSecond.Get("OuterEPDSineAverages").GetBinContent(j)
            OuterEPDCosineAverageJth = QVectorHistogramFileSecond.Get("OuterEPDCosineAverages").GetBinContent(j)
            TPCSineAverageJth = QVectorHistogramFileSecond.Get("TPCSineAverages").GetBinContent(j)
            TPCCosineAverageJth = QVectorHistogramFileSecond.Get("TPCCosineAverages").GetBinContent(j)
            
            FourierCorrectionTermInnerEPD += (2/(j*nPsi))*(InnerEPDSineAverageJth*cos(j*nPsi*PsiInnerEPDRecentered) + InnerEPDCosineAverageJth*sin(j*nPsi*PsiInnerEPDRecentered))
            FourierCorrectionTermOuterEPD += (2/(j*nPsi))*(OuterEPDSineAverageJth*cos(j*nPsi*PsiOuterEPDRecentered) + OuterEPDCosineAverageJth*sin(j*nPsi*PsiOuterEPDRecentered))
            FourierCorrectionTermTPC += (2/(j*nPsi))*(TPCSineAverageJth*cos(j*nPsi*PsiTPCRecentered) + TPCCosineAverageJth*sin(j*nPsi*PsiTPCRecentered))

        PsiInnerEPDFourierCorrected = PsiInnerEPDRecentered + FourierCorrectionTermInnerEPD
        PsiOuterEPDFourierCorrected = PsiOuterEPDRecentered + FourierCorrectionTermOuterEPD
        PsiTPCFourierCorrected = PsiTPCRecentered + FourierCorrectionTermTPC
            
        HistoD35.Fill(PsiInnerEPDFourierCorrected)
        HistoD38.Fill(PsiOuterEPDFourierCorrected)
        HistoD41.Fill(PsiTPCFourierCorrected)

        for index in range(len(px)):
            pt = Pt(px[index], py[index])

            p = P(px[index], py[index], pz[index])

            eta = Eta(px[index], py[index], pz[index])

            phi = Phi(px[index], py[index])
            
            DAndT = ROOT.DeuteronsAndTritons(p, dEdx[index], tofBeta[index])
            
            IsDeuteron = DAndT.IsDeuteron()
            IsTriton = DAndT.IsTriton()
            
            if((IsDeuteron)):# and (pt > DeuteronLowerPt) and (pt < DeuteronUpperPt)):
                mass = DeuteronMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                VnInnerEPDFourierCorrected = V_n(nV, px[index], py[index], PsiInnerEPDFourierCorrected)

                if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                    HistoD44A.Fill(y - yCMShift, VnInnerEPDFourierCorrected)

            elif((IsTriton)):# and (pt > TritonLowerPt) and (pt < TritonUpperPt)):
                mass = TritonMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                VnInnerEPDFourierCorrected = V_n(nV, px[index], py[index], PsiInnerEPDFourierCorrected)

                if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                    HistoD44B.Fill(y - yCMShift, VnInnerEPDFourierCorrected)
                    
                    
                    
            
#             if(tofBeta[index] < 0):
#                 if((abs(NSigmaPr[index]) < NSigmaPrBound) and (pt > ProtonLowerPt) and (pt < ProtonUpperPt) and (p < 2.0)): 
#                     mass = ProtonMass

#                     energy = Energy(px[index], py[index], pz[index], mass)

#                     y = Y(px[index], py[index], pz[index], mass)

#                     VnInnerEPDFourierCorrected = V_n(nV, px[index], py[index], PsiInnerEPDFourierCorrected)

#                     if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
#                         HistoD44.Fill(y - yCMShift, VnInnerEPDFourierCorrected)
                        
                        

            if(tofBeta[index] > 0):

                msquared = MSquared(px[index], py[index], pz[index], tofBeta[index])

                if((abs(NSigmaPr[index]) < 3) and (msquared > ProtonLowerMSquared) and (msquared < ProtonUpperMSquared) and (pt > ProtonLowerPt) and (pt < ProtonUpperPt)): 
                    mass = ProtonMass

                    energy = Energy(px[index], py[index], pz[index], mass)

                    y = Y(px[index], py[index], pz[index], mass)

                    VnInnerEPDFourierCorrected = V_n(nV, px[index], py[index], PsiInnerEPDFourierCorrected)

                    if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                        HistoD44.Fill(y - yCMShift, VnInnerEPDFourierCorrected)

                if((abs(NSigmaKa[index]) < 3) and (msquared > KaonLowerMSquared) and (msquared < KaonUpperMSquared) and (pt > KaonLowerPt) and (pt < KaonUpperPt)): 
                    mass = KaonMass

                    energy = Energy(px[index], py[index], pz[index], mass)

                    y = Y(px[index], py[index], pz[index], mass)

                    VnInnerEPDFourierCorrected = V_n(nV, px[index], py[index], PsiInnerEPDFourierCorrected)

                    if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                        if(q[index] > 0):
                            HistoD47.Fill(y - yCMShift, VnInnerEPDFourierCorrected)

                        elif(q[index] < 0):
                            HistoD47A.Fill(y - yCMShift, VnInnerEPDFourierCorrected)

                if((abs(NSigmaPi[index]) < 3) and (msquared > PionLowerMSquared) and (msquared < PionUpperMSquared) and (pt > PionLowerPt) and (pt < PionUpperPt)): 
                    mass = PionMass

                    energy = Energy(px[index], py[index], pz[index], mass)

                    y = Y(px[index], py[index], pz[index], mass)

                    VnInnerEPDFourierCorrected = V_n(nV, px[index], py[index], PsiInnerEPDFourierCorrected)

                    if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                        if(q[index] > 0):
                            HistoD50.Fill(y - yCMShift, VnInnerEPDFourierCorrected)

                        elif(q[index] < 0):
                            HistoD50A.Fill(y - yCMShift, VnInnerEPDFourierCorrected)

                        
        R11TopLeftTerm = cos(nV*(PsiInnerEPDFourierCorrected - PsiOuterEPDFourierCorrected))
        R11TopRightTerm = cos(nV*(PsiInnerEPDFourierCorrected - PsiTPCFourierCorrected))
        R11BottomTerm = cos(nV*(PsiOuterEPDFourierCorrected - PsiTPCFourierCorrected))

        Centrality = 15 - Centrality

        HistoD51.Fill(Centrality, R11TopLeftTerm)
        HistoD52.Fill(Centrality, R11TopRightTerm)
        HistoD53.Fill(Centrality, R11BottomTerm)
        
        CentralityXLabels = ["0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60"]

        R11 = 0
        R11Error = 0

        for index in range(1, HistoD51.GetNbinsX() + 1):
            HistoD51.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])
            HistoD52.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])
            HistoD53.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])
                        
    HistoD35.SetDirectory(0)
    HistoD38.SetDirectory(0)
    HistoD41.SetDirectory(0)
    HistoD44.SetDirectory(0)
    HistoD44A.SetDirectory(0)
    HistoD44B.SetDirectory(0)
    HistoD47.SetDirectory(0)
    HistoD47A.SetDirectory(0)
    HistoD50.SetDirectory(0)
    HistoD50A.SetDirectory(0)
    HistoD51.SetDirectory(0)
    HistoD52.SetDirectory(0)
    HistoD53.SetDirectory(0)                


    Histograms.append(HistoD35)
    Histograms.append(HistoD38)
    Histograms.append(HistoD41)
    Histograms.append(HistoD44)
    Histograms.append(HistoD44A)
    Histograms.append(HistoD44B)
    Histograms.append(HistoD47)
    Histograms.append(HistoD47A)
    Histograms.append(HistoD50)
    Histograms.append(HistoD50A)
    Histograms.append(HistoD51)
    Histograms.append(HistoD52)
    Histograms.append(HistoD53)

    Data.Close()
    QVectorHistogramFileFirst.Close()
    QVectorHistogramFileSecond.Close()    
    HistogramFile.Close()



    #HistogramRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/HistogramThirdPassTest.root", "UPDATE")
    HistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/HistogramThirdPass" + sys.argv[2] + ".root", "RECREATE")
    HistogramRootFile.cd()

    for index in range(0,len(Histograms)):
        Histograms[index].Write()

    HistogramRootFile.Close()

    print("Done")                                    
################################################################################################################################################                        
if(RunIteration == 4):
    Data = ROOT.TFile.Open(sys.argv[1])
    #Data = ROOT.TFile.Open("/star/data01/pwg/cracz/Data_3p0GeV_FXT/FXT_3p0GeV_SL20d_2018_11.root")
    # MonteCarlo = ROOT.TFile.Open("/eos/user/m/migordon/SWAN_projects/HeavyIonStuff/CombinedMonteCarloFiles.root")

    AutreeData = Data.Get("Autree")

    Histograms = []
        

    #QVectorHistogramFileFirst = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/QVectorFirstPassTest.root")
    #QVectorHistogramFileSecond = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/QVectorSecondPassTest.root")
    QVectorHistogramFileFirst = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/QVectorFirstPass.root")
    QVectorHistogramFileSecond = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/QVectorSecondPass.root")
    #HistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/HistogramThirdPassTest.root")
    HistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/HistogramThirdPass.root")
    
    
    TPCEfficiencyFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/TPCEfficiency.root","READ")
    ToFEfficiencyFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/ToFEfficiency.root","READ")  


    
    HistoD54 = HistogramFile.Get("DataResolution")
    
    CentralityXLabels = ["0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60"]
    
    HistoD44C= ROOT.TProfile("DataVnVsYPsi1ResolutionCorrectedProton", "V" + str(nV) + " (Resolution Corrected) vs Y for Protons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD44C.Sumw2()

    HistoD47B = ROOT.TProfile("DataVnVsYPsi1ResolutionCorrectedKaonPlus", "V" + str(nV) + " (Resolution Corrected) vs Y for K+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD47B.Sumw2()

    HistoD47C = ROOT.TProfile("DataVnVsYPsi1ResolutionCorrectedKaonMinus", "V" + str(nV) + " (Resolution Corrected) vs Y for K-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD47C.Sumw2()

    HistoD50B = ROOT.TProfile("DataVnVsYPsi1ResolutionCorrectedPionPlus", "V" + str(nV) + " (Resolution Corrected) vs Y for Pi+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD50B.Sumw2()

    HistoD50C = ROOT.TProfile("DataVnVsYPsi1ResolutionCorrectedPionMinus", "V" + str(nV) + " (Resolution Corrected) vs Y for Pi-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD50C.Sumw2()
    
    HistoD50D = ROOT.TProfile("DataVnVsYPsi1ResolutionCorrectedDeuteron", "V" + str(nV) + " (Resolution Corrected) vs Y for Deuterons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD50D.Sumw2()

    HistoD50E = ROOT.TProfile("DataVnVsYPsi1ResolutionCorrectedTriton", "V" + str(nV) + " (Resolution Corrected) vs Y for Tritons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
    HistoD50E.Sumw2()

    HistoD54A = ROOT.TProfile("DataVnVsCentralityProtonCorrected", "V" + str(nV) + " vs Centrality for Protons (Data); Centrality; V" + str(nV) +"", 12, 0, 12)
    HistoD54A.Sumw2()

    HistoD54B = ROOT.TProfile("DataVnVsCentralityKaonPlusCorrected", "V" + str(nV) + " vs Centrality for Kaon+ (Data); Centrality; V" + str(nV) +"", 12, 0, 12)
    HistoD54B.Sumw2()

    HistoD54C = ROOT.TProfile("DataVnVsCentralityKaonMinusCorrected", "V" + str(nV) + " vs Centrality for Kaon- (Data); Centrality; V" + str(nV) +"", 12, 0, 12)
    HistoD54C.Sumw2()

    HistoD54D = ROOT.TProfile("DataVnVsCentralityPionPlusCorrected", "V" + str(nV) + " vs Centrality for Pion+ (Data); Centrality; V" + str(nV) +"", 12, 0, 12)
    HistoD54D.Sumw2()

    HistoD54E = ROOT.TProfile("DataVnVsCentralityPionMinusCorrected", "V" + str(nV) + " vs Centrality for Pion- (Data); Centrality; V" + str(nV) +"", 12, 0, 12)
    HistoD54E.Sumw2()
    
    HistoD54F = ROOT.TProfile("DataVnVsCentralityDeuteronCorrected", "V" + str(nV) + " vs Centrality for Deuterons (Data); Centrality; V" + str(nV) +"", 12, 0, 12)
    HistoD54F.Sumw2()

    HistoD54G = ROOT.TProfile("DataVnVsCentralityTritonCorrected", "V" + str(nV) + " vs Centrality for Tritons (Data); Centrality; V" + str(nV) +"", 12, 0, 12)
    HistoD54G.Sumw2()

    HistoD79 = ROOT.TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesProton", "V" + str(nV) + " (Resolution Corrected) vs Pt for Protons for Different Centralities (Data); Centrality; Pt", 12, 0, 12, 20, 0, 2)
    HistoD79.Sumw2()

    HistoD80 = ROOT.TProfile2D("DataVnCorrectedVsYDifferentCentralitiesProton", "V" + str(nV) + " (Resolution Corrected) vs Y for Protons for Different Centralities (Data); Centrality; Y - Y_CM", 12, 0, 12, 10, 0, 1)
    HistoD80.Sumw2()

    HistoD81 = ROOT.TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesKaonPlus", "V" + str(nV) + " (Resolution Corrected) vs Pt for K+ for Different Centralities (Data); Centrality; Pt", 12, 0, 12, 20, 0, 2)
    HistoD81.Sumw2()

    HistoD82 = ROOT.TProfile2D("DataVnCorrectedVsYDifferentCentralitiesKaonPlus", "V" + str(nV) + " (Resolution Corrected) vs Y for K+ for Different Centralities (Data); Centrality; Y - Y_CM", 12, 0, 12, 10, 0, 1)
    HistoD82.Sumw2()

    HistoD83 = ROOT.TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesKaonNegative", "V" + str(nV) + " (Resolution Corrected) vs Pt for K- for Different Centralities (Data); Centrality; Pt", 12, 0, 12, 20, 0, 2)
    HistoD83.Sumw2()

    HistoD84 = ROOT.TProfile2D("DataVnCorrectedVsYDifferentCentralitiesKaonNegative", "V" + str(nV) + " (Resolution Corrected) vs Y for K- for Different Centralities (Data); Centrality; Y - Y_CM", 12, 0, 12, 10, 0, 1)
    HistoD84.Sumw2()

    HistoD85 = ROOT.TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesPionPlus", "V" + str(nV) + " (Resolution Corrected) vs Pt for Pi+ for Different Centralities (Data); Centrality; Pt", 12, 0, 12, 20, 0, 2)
    HistoD85.Sumw2()

    HistoD86 = ROOT.TProfile2D("DataVnCorrectedVsYDifferentCentralitiesPionPlus", "V" + str(nV) + " (Resolution Corrected) vs Y for Pi+ for Different Centralities (Data); Centrality; Y - Y_CM", 12, 0, 12, 10, 0, 1)
    HistoD86.Sumw2()

    HistoD87 = ROOT.TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesPionNegative", "V" + str(nV) + " (Resolution Corrected) vs Pt for Pi- for Different Centralities (Data); Centrality; Pt", 12, 0, 12, 20, 0, 2)
    HistoD87.Sumw2()

    HistoD88 = ROOT.TProfile2D("DataVnCorrectedVsYDifferentCentralitiesPionNegative", "V" + str(nV) + " (Resolution Corrected) vs Y for Pi- for Different Centralities (Data); Centrality; Y - Y_CM", 12, 0, 12, 10, 0, 1)
    HistoD88.Sumw2()

    HistoD88A = ROOT.TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesDeuterons", "V" + str(nV) + " (Resolution Corrected) vs Pt for Deuterons for Different Centralities (Data); Centrality; Pt", 12, 0, 12, 20, 0, 2)
    HistoD88A.Sumw2()

    HistoD88B = ROOT.TProfile2D("DataVnCorrectedVsYDifferentCentralitiesDeuterons", "V" + str(nV) + " (Resolution Corrected) vs Y for Deuterons for Different Centralities (Data); Centrality; Y - Y_CM", 12, 0, 12, 10, 0, 1)
    HistoD88B.Sumw2()
    
    HistoD88C = ROOT.TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesTritons", "V" + str(nV) + " (Resolution Corrected) vs Pt for Tritons for Different Centralities (Data); Centrality; Pt", 12, 0, 12, 20, 0, 2)
    HistoD88C.Sumw2()

    HistoD88D = ROOT.TProfile2D("DataVnCorrectedVsYDifferentCentralitiesTritons", "V" + str(nV) + " (Resolution Corrected) vs Y for Tritons for Different Centralities (Data); Centrality; Y - Y_CM", 12, 0, 12, 10, 0, 1)
    HistoD88D.Sumw2()


    # Calculation of Fourier correction terms
    for entryNum in range (0, AutreeData.GetEntries()):
        if (entryNum % 5000 == 0):
            print("Data Fourth Pass (V1 Corrected for Resolution)", entryNum)

        AutreeData.GetEntry(entryNum)

        px = AutreeData.Px
        py = AutreeData.Py
        pz = AutreeData.Pz
        q = AutreeData.Charge
        tofBeta = AutreeData.tofBeta
        dEdx = AutreeData.dEdx
        NSigmaPr = AutreeData.nSigmaPr
        NSigmaKa = AutreeData.nSigmaKa
        NSigmaPi = AutreeData.nSigmaPi
        vx = AutreeData.Vx
        vy = AutreeData.Vy
        vz = AutreeData.Vz
        Centrality = AutreeData.centrality
        EPDnMIP = AutreeData.EPDnMip
        EPDID = AutreeData.EPDid

        ProtonID = 2212
        KaonPlusID = 321
        PionPlusID = 211

        ProtonMass = 0.938
        KaonMass = 0.494
        PionMass = 0.140
        DeuteronMass = 1.875613
        TritonMass = 2.808921

        Multiplicity = len(px)

        InnerEPDQx = 0
        InnerEPDQy = 0
        OuterEPDQx = 0
        OuterEPDQy = 0
        TPCQx = 0
        TPCQy = 0
        
        InnerEPDQxMean = QVectorHistogramFileFirst.Get("InnerEPDQxRaw").GetMean()
        InnerEPDQyMean = QVectorHistogramFileFirst.Get("InnerEPDQyRaw").GetMean()
        OuterEPDQxMean = QVectorHistogramFileFirst.Get("OuterEPDQxRaw").GetMean()
        OuterEPDQyMean = QVectorHistogramFileFirst.Get("OuterEPDQyRaw").GetMean()
        TPCQxMean = QVectorHistogramFileFirst.Get("TPCQxRaw").GetMean()
        TPCQyMean = QVectorHistogramFileFirst.Get("TPCQyRaw").GetMean()

        FourierCorrectionTermInnerEPD = 0
        FourierCorrectionTermOuterEPD = 0
        FourierCorrectionTermTPC = 0

        GoodTracksCounterInnerEPD = 0
        GoodTracksCounterOuterEPD = 0
        GoodTracksCounterTPC = 0

        if(Centrality < 4):
            continue

        for index in range(len(px)):
            p = P(px[index], py[index], pz[index])

            eta = Eta(px[index], py[index], pz[index])

            if ((eta > TPCLowerLimit) and (eta < TPCUpperLimit)):
                GoodTracksCounterTPC += 1   

        for index in range(len(EPDID)):
            if(EPDID[index] > 0):
                continue

            TileVector = ROOT.EPDKinematics(EPDID[index], vx, vy, vz)

            if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
                GoodTracksCounterInnerEPD += 1

            if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
                GoodTracksCounterOuterEPD += 1

        if((GoodTracksCounterInnerEPD < NumberOfGoodTracksInnerEPD) or (GoodTracksCounterOuterEPD < NumberOfGoodTracksOuterEPD) or (GoodTracksCounterTPC < NumberOfGoodTracksTPC)):
            continue

        for index in range(len(px)):
            pt = Pt(px[index], py[index])

            p = P(px[index], py[index], pz[index])

            eta = Eta(px[index], py[index], pz[index])

            phi = Phi(px[index], py[index])

            if ((eta > TPCLowerLimit) and (eta < TPCUpperLimit)):
                TPCQy += pt*sin(nPsi*phi)
                TPCQx += pt*cos(nPsi*phi)

        for index in range(len(EPDID)):
            if(EPDID[index] > 0):
                continue

            TileVector = ROOT.EPDKinematics(EPDID[index], vx, vy, vz)

            phi = TileVector.EPDPhi()

            if(EPDnMIP[index] < 0.3):
                EPDnMIP[index] = 0

            if(EPDnMIP[index] > 2.0):
                EPDnMIP[index] = 2.0

            if(nV % 2 == 0):
                if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
                    InnerEPDQy += EPDnMIP[index]*sin(nPsi*phi)
                    InnerEPDQx += EPDnMIP[index]*cos(nPsi*phi)

                if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
                    OuterEPDQy += EPDnMIP[index]*sin(nPsi*phi)
                    OuterEPDQx += EPDnMIP[index]*cos(nPsi*phi)
                
            else:
                if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
                    InnerEPDQy -= EPDnMIP[index]*sin(nPsi*phi)
                    InnerEPDQx -= EPDnMIP[index]*cos(nPsi*phi)

                if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
                    OuterEPDQy -= EPDnMIP[index]*sin(nPsi*phi)
                    OuterEPDQx -= EPDnMIP[index]*cos(nPsi*phi)
                
        if((InnerEPDQx == 0) and (InnerEPDQy == 0)):
            continue
            
        if((OuterEPDQx == 0) and (OuterEPDQy == 0)):
            continue
            
        if((TPCQx == 0) and (TPCQy == 0)):
            continue

        PsiInnerEPDRecentered = (1/nPsi)*atan2(InnerEPDQy - InnerEPDQyMean, InnerEPDQx - InnerEPDQxMean)
        PsiOuterEPDRecentered = (1/nPsi)*atan2(OuterEPDQy - OuterEPDQyMean, OuterEPDQx - OuterEPDQxMean)
        PsiTPCRecentered = (1/nPsi)*atan2(TPCQy - TPCQyMean, TPCQx - TPCQxMean)
                
        for j in range(1, FourierCorrectionTerms + 1):
            InnerEPDSineAverageJth = QVectorHistogramFileSecond.Get("InnerEPDSineAverages").GetBinContent(j)
            InnerEPDCosineAverageJth = QVectorHistogramFileSecond.Get("InnerEPDCosineAverages").GetBinContent(j)
            OuterEPDSineAverageJth = QVectorHistogramFileSecond.Get("OuterEPDSineAverages").GetBinContent(j)
            OuterEPDCosineAverageJth = QVectorHistogramFileSecond.Get("OuterEPDCosineAverages").GetBinContent(j)
            TPCSineAverageJth = QVectorHistogramFileSecond.Get("TPCSineAverages").GetBinContent(j)
            TPCCosineAverageJth = QVectorHistogramFileSecond.Get("TPCCosineAverages").GetBinContent(j)
            
            FourierCorrectionTermInnerEPD += (2/(j*nPsi))*(InnerEPDSineAverageJth*cos(j*nPsi*PsiInnerEPDRecentered) + InnerEPDCosineAverageJth*sin(j*nPsi*PsiInnerEPDRecentered))
            FourierCorrectionTermOuterEPD += (2/(j*nPsi))*(OuterEPDSineAverageJth*cos(j*nPsi*PsiOuterEPDRecentered) + OuterEPDCosineAverageJth*sin(j*nPsi*PsiOuterEPDRecentered))
            FourierCorrectionTermTPC += (2/(j*nPsi))*(TPCSineAverageJth*cos(j*nPsi*PsiTPCRecentered) + TPCCosineAverageJth*sin(j*nPsi*PsiTPCRecentered))

        PsiInnerEPDFourierCorrected = PsiInnerEPDRecentered + FourierCorrectionTermInnerEPD
        PsiOuterEPDFourierCorrected = PsiOuterEPDRecentered + FourierCorrectionTermOuterEPD
        PsiTPCFourierCorrected = PsiTPCRecentered + FourierCorrectionTermTPC

        

        Centrality = 15 - Centrality

        ResolutionCorrectionFactor = HistoD54.GetBinContent(Centrality + 1)

        for index in range(len(px)):
            pt = Pt(px[index], py[index])

            p = P(px[index], py[index], pz[index])

            eta = Eta(px[index], py[index], pz[index])

            phi = Phi(px[index], py[index])
            
            DAndT = ROOT.DeuteronsAndTritons(p, dEdx[index], tofBeta[index])
            
            IsDeuteron = DAndT.IsDeuteron()
            IsTriton = DAndT.IsTriton()
            
            if((IsDeuteron) and (pt > DeuteronLowerPt) and (pt < DeuteronUpperPt)):
                mass = DeuteronMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                VnInnerEPDFourierCorrected = V_n(nV, px[index], py[index], PsiInnerEPDFourierCorrected)

                if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                    HistoD50D.Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                    HistoD54F.Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                    HistoD88A.Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                    HistoD88B.Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                
                for i in range(1, HistoD54F.GetNbinsX() + 1):
                    HistoD54F.GetXaxis().SetBinLabel(i, CentralityXLabels[i - 1])

            elif((IsTriton) and (pt > TritonLowerPt) and (pt < TritonUpperPt)):
                mass = TritonMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                VnInnerEPDFourierCorrected = V_n(nV, px[index], py[index], PsiInnerEPDFourierCorrected)

                if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                    HistoD50E.Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                    HistoD54G.Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                    HistoD88C.Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                    HistoD88D.Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                
                for i in range(1, HistoD54G.GetNbinsX() + 1):
                    HistoD54G.GetXaxis().SetBinLabel(i, CentralityXLabels[i - 1])
                    
                    
                    
            
#             if(tofBeta[index] < 0):
                
#                 if((abs(NSigmaPr[index]) < NSigmaPrBound) and (pt > ProtonLowerPt) and (pt < ProtonUpperPt) and (p < 2.0)): 
#                     mass = ProtonMass

#                     energy = Energy(px[index], py[index], pz[index], mass)

#                     y = Y(px[index], py[index], pz[index], mass)

#                     VnInnerEPDFourierCorrected = V_n(nV, px[index], py[index], PsiInnerEPDFourierCorrected)

#                     TPCEfficiencyHistogram = TPCEfficiencyFile.Get("h2_ratio_pr")
#                     ToFEfficiencyHistogram = ToFEfficiencyFile.Get("h2_ratio_tof")

#                     TPCEfficiencyBin = TPCEfficiencyHistogram.FindBin(y, pt)
#                     ToFEfficiencyBin = ToFEfficiencyHistogram.FindBin(y, pt)
                    
#                     TPCEfficiency = TPCEfficiencyHistogram.GetBinContent(TPCEfficiencyBin)
#                     ToFEfficiency = ToFEfficiencyHistogram.GetBinContent(ToFEfficiencyBin)
                    
#                     if((TPCEfficiency == 0) or (TPCEfficiency > 1.3) or (ToFEfficiency == 0)):
#                         continue
                    
#                     if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
#                         HistoD44C.Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0/(TPCEfficiency * ToFEfficiency))
#                         HistoD54A.Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0/(TPCEfficiency * ToFEfficiency))
#                         HistoD79.Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0/(TPCEfficiency * ToFEfficiency))
#                         HistoD80.Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor, 1.0/(TPCEfficiency * ToFEfficiency))

#                     for i in range(1, HistoD54A.GetNbinsX() + 1):
#                         HistoD54A.GetXaxis().SetBinLabel(i, CentralityXLabels[i - 1])
                        
                        
                        
        
                        
                        

            if(tofBeta[index] > 0):

                msquared = MSquared(px[index], py[index], pz[index], tofBeta[index])

                if((abs(NSigmaPr[index]) < 3) and (msquared > ProtonLowerMSquared) and (msquared < ProtonUpperMSquared) and (pt > ProtonLowerPt) and (pt < ProtonUpperPt)): 
                    mass = ProtonMass

                    energy = Energy(px[index], py[index], pz[index], mass)

                    y = Y(px[index], py[index], pz[index], mass)

                    VnInnerEPDFourierCorrected = V_n(nV, px[index], py[index], PsiInnerEPDFourierCorrected)
                    
#                     TPCEfficiencyHistogram = TPCEfficiencyFile.Get("h2_ratio_pr")
#                     ToFEfficiencyHistogram = ToFEfficiencyFile.Get("h2_ratio_tof")
                    
#                     TPCEfficiencyBin = TPCEfficiencyHistogram.FindBin(y, pt)
#                     ToFEfficiencyBin = ToFEfficiencyHistogram.FindBin(y, pt)
                    
#                     TPCEfficiency = TPCEfficiencyHistogram.GetBinContent(TPCEfficiencyBin)
#                     ToFEfficiency = ToFEfficiencyHistogram.GetBinContent(ToFEfficiencyBin)
                    
#                     if((TPCEfficiency == 0) or (TPCEfficiency > 1.3) or (ToFEfficiency == 0)):
#                         continue

                    if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                        HistoD44C.Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                        HistoD54A.Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                        HistoD79.Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                        HistoD80.Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)

                    for i in range(1, HistoD54A.GetNbinsX() + 1):
                        HistoD54A.GetXaxis().SetBinLabel(i, CentralityXLabels[i - 1])

                if((abs(NSigmaKa[index]) < 3) and (msquared > KaonLowerMSquared) and (msquared < KaonUpperMSquared) and (pt > KaonLowerPt) and (pt < KaonUpperPt)): 
                    mass = KaonMass

                    energy = Energy(px[index], py[index], pz[index], mass)

                    y = Y(px[index], py[index], pz[index], mass)

                    VnInnerEPDFourierCorrected = V_n(nV, px[index], py[index], PsiInnerEPDFourierCorrected)
            
                    if(q[index] > 0):
#                         TPCEfficiencyHistogram = TPCEfficiencyFile.Get("h2_ratio_kp")
#                         ToFEfficiencyHistogram = ToFEfficiencyFile.Get("h2_ratio_tof")

#                         TPCEfficiencyBin = TPCEfficiencyHistogram.FindBin(y, pt)
#                         ToFEfficiencyBin = ToFEfficiencyHistogram.FindBin(y, pt)

#                         TPCEfficiency = TPCEfficiencyHistogram.GetBinContent(TPCEfficiencyBin)
#                         ToFEfficiency = ToFEfficiencyHistogram.GetBinContent(ToFEfficiencyBin)
                        
#                         if((TPCEfficiency == 0) or (TPCEfficiency > 1.3) or (ToFEfficiency == 0)):
#                             continue
                    
                        if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                            HistoD47B.Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                            HistoD54B.Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                            HistoD81.Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                            HistoD82.Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)

                        for i in range(1, HistoD54B.GetNbinsX() + 1):
                            HistoD54B.GetXaxis().SetBinLabel(i, CentralityXLabels[i - 1])

                    elif(q[index] < 0):
#                         TPCEfficiencyHistogram = TPCEfficiencyFile.Get("h2_ratio_km")
#                         ToFEfficiencyHistogram = ToFEfficiencyFile.Get("h2_ratio_tof")

#                         TPCEfficiencyBin = TPCEfficiencyHistogram.FindBin(y, pt)
#                         ToFEfficiencyBin = ToFEfficiencyHistogram.FindBin(y, pt)

#                         TPCEfficiency = TPCEfficiencyHistogram.GetBinContent(TPCEfficiencyBin)
#                         ToFEfficiency = ToFEfficiencyHistogram.GetBinContent(ToFEfficiencyBin)
                        
#                         if((TPCEfficiency == 0) or (TPCEfficiency > 1.3) or (ToFEfficiency == 0)):
#                             continue
                        
                        if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                            HistoD47C.Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                            HistoD54C.Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                            HistoD83.Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                            HistoD84.Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)

                        for i in range(1, HistoD54C.GetNbinsX() + 1):
                            HistoD54C.GetXaxis().SetBinLabel(i, CentralityXLabels[i - 1])

                if((abs(NSigmaPi[index]) < 3) and (msquared > PionLowerMSquared) and (msquared < PionUpperMSquared) and (pt > PionLowerPt) and (pt < PionUpperPt)): 
                    mass = PionMass

                    energy = Energy(px[index], py[index], pz[index], mass)

                    y = Y(px[index], py[index], pz[index], mass)

                    VnInnerEPDFourierCorrected = V_n(nV, px[index], py[index], PsiInnerEPDFourierCorrected)

                    if(q[index] > 0):
#                         TPCEfficiencyHistogram = TPCEfficiencyFile.Get("h2_ratio_pp")
#                         ToFEfficiencyHistogram = ToFEfficiencyFile.Get("h2_ratio_tof")

#                         TPCEfficiencyBin = TPCEfficiencyHistogram.FindBin(y, pt)
#                         ToFEfficiencyBin = ToFEfficiencyHistogram.FindBin(y, pt)

#                         TPCEfficiency = TPCEfficiencyHistogram.GetBinContent(TPCEfficiencyBin)
#                         ToFEfficiency = ToFEfficiencyHistogram.GetBinContent(ToFEfficiencyBin)
                        
#                         if((TPCEfficiency == 0) or (TPCEfficiency > 1.3) or (ToFEfficiency == 0)):
#                             continue
                        
                        if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                            HistoD50B.Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor) 
                            HistoD54D.Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                            HistoD85.Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                            HistoD86.Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)

                        for i in range(1, HistoD54D.GetNbinsX() + 1):
                            HistoD54D.GetXaxis().SetBinLabel(i, CentralityXLabels[i - 1])

                    elif(q[index] < 0):
#                         TPCEfficiencyHistogram = TPCEfficiencyFile.Get("h2_ratio_pm")
#                         ToFEfficiencyHistogram = ToFEfficiencyFile.Get("h2_ratio_tof")

#                         TPCEfficiencyBin = TPCEfficiencyHistogram.FindBin(y, pt)
#                         ToFEfficiencyBin = ToFEfficiencyHistogram.FindBin(y, pt)

#                         TPCEfficiency = TPCEfficiencyHistogram.GetBinContent(TPCEfficiencyBin)
#                         ToFEfficiency = ToFEfficiencyHistogram.GetBinContent(ToFEfficiencyBin)
                        
#                         if((TPCEfficiency == 0) or (TPCEfficiency > 1.3) or (ToFEfficiency == 0)):
#                             continue
                        
                        if(((y - yCMShift) > LowerYMinusYCM) and ((y - yCMShift) < UpperYMinusYCM)):
                            HistoD50C.Fill(y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                            HistoD54E.Fill(Centrality, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                            HistoD87.Fill(Centrality, pt, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)
                            HistoD88.Fill(Centrality, y - yCMShift, VnInnerEPDFourierCorrected / ResolutionCorrectionFactor)

                        for i in range(1, HistoD54E.GetNbinsX() + 1):
                            HistoD54E.GetXaxis().SetBinLabel(i, CentralityXLabels[i - 1])


    HistoD89 = HistoD79.ProfileY("DataV" + str(nV) +"VsPtForProtonsCentrality0-10", 1, 2)
    HistoD89.SetXTitle("Pt")
    HistoD89.SetYTitle("V" + str(nV) +"")
    HistoD90 = HistoD79.ProfileY("DataV" + str(nV) +"VsPtForProtonsCentrality10-40", 3, 8)
    HistoD90.SetXTitle("Pt")
    HistoD90.SetYTitle("V" + str(nV) +"")
    HistoD91 = HistoD79.ProfileY("DataV" + str(nV) +"VsPtForProtonsCentrality40-60", 9, 12)
    HistoD91.SetXTitle("Pt")
    HistoD91.SetYTitle("V" + str(nV) +"")
    HistoD92 = HistoD80.ProfileY("DataV" + str(nV) +"VsYForProtonsCentrality0-10", 1, 2)
    HistoD92.SetXTitle("Y - Y_CM")
    HistoD92.SetYTitle("V" + str(nV) +"")
    HistoD93 = HistoD80.ProfileY("DataV" + str(nV) +"VsYForProtonsCentrality10-40", 3, 8)
    HistoD93.SetXTitle("Y - Y_CM")
    HistoD93.SetYTitle("V" + str(nV) +"")
    HistoD94 = HistoD80.ProfileY("DataV" + str(nV) +"VsYForProtonsCentrality40-60", 9, 12)
    HistoD94.SetXTitle("Y - Y_CM")
    HistoD94.SetYTitle("V" + str(nV) +"")


    HistoD95 = HistoD81.ProfileY("DataV" + str(nV) +"VsPtForKaonsPlusCentrality0-10", 1, 2)
    HistoD95.Rebin()
    HistoD95.SetXTitle("Pt")
    HistoD95.SetYTitle("V" + str(nV) +"")
    HistoD96 = HistoD81.ProfileY("DataV" + str(nV) +"VsPtForKaonsPlusCentrality10-40", 3, 8)
    HistoD96.Rebin()
    HistoD96.SetXTitle("Pt")
    HistoD96.SetYTitle("V" + str(nV) +"")
    HistoD97 = HistoD81.ProfileY("DataV" + str(nV) +"VsPtForKaonsPlusCentrality40-60", 9, 12)
    HistoD97.Rebin()
    HistoD97.SetXTitle("Pt")
    HistoD97.SetYTitle("V" + str(nV) +"")
    HistoD98 = HistoD82.ProfileY("DataV" + str(nV) +"VsYForKaonsPlusCentrality0-10", 1, 2)
    HistoD98.Rebin()
    HistoD98.SetXTitle("Y - Y_CM")
    HistoD98.SetYTitle("V" + str(nV) +"")
    HistoD99 = HistoD82.ProfileY("DataV" + str(nV) +"VsYForKaonsPlusCentrality10-40", 3, 8)
    HistoD99.Rebin()
    HistoD99.SetXTitle("Y - Y_CM")
    HistoD99.SetYTitle("V" + str(nV) +"")
    HistoD100 = HistoD82.ProfileY("DataV" + str(nV) +"VsYForKaonsPlusCentrality40-60", 9, 12)
    HistoD100.Rebin()
    HistoD100.SetXTitle("Y - Y_CM")
    HistoD100.SetYTitle("V" + str(nV) +"")


    HistoD101 = HistoD83.ProfileY("DataV" + str(nV) +"VsPtForKaonsMinusCentrality0-10", 1, 2)
    HistoD101.Rebin()
    HistoD101.SetXTitle("Pt")
    HistoD101.SetYTitle("V" + str(nV) +"")
    HistoD102 = HistoD83.ProfileY("DataV" + str(nV) +"VsPtForKaonsMinusCentrality10-40", 3, 8)
    HistoD102.Rebin()
    HistoD102.SetXTitle("Pt")
    HistoD102.SetYTitle("V" + str(nV) +"")
    HistoD103 = HistoD83.ProfileY("DataV" + str(nV) +"VsPtForKaonsMinusCentrality40-60", 9, 12)
    HistoD103.Rebin()
    HistoD103.SetXTitle("Pt")
    HistoD103.SetYTitle("V" + str(nV) +"")
    HistoD104 = HistoD84.ProfileY("DataV" + str(nV) +"VsYForKaonsMinusCentrality0-10", 1, 2)
    HistoD104.Rebin()
    HistoD104.SetXTitle("Y - Y_CM")
    HistoD104.SetYTitle("V" + str(nV) +"")
    HistoD105 = HistoD84.ProfileY("DataV" + str(nV) +"VsYForKaonsMinusCentrality10-40", 3, 8)
    HistoD105.Rebin()
    HistoD105.SetXTitle("Y - Y_CM")
    HistoD105.SetYTitle("V" + str(nV) +"")
    HistoD106 = HistoD84.ProfileY("DataV" + str(nV) +"VsYForKaonsMinusCentrality40-60", 9, 12)
    HistoD106.Rebin()
    HistoD106.SetXTitle("Y - Y_CM")
    HistoD106.SetYTitle("V" + str(nV) +"")



    HistoD107 = HistoD85.ProfileY("DataV" + str(nV) +"VsPtForPionsPlusCentrality0-10", 1, 2)
    HistoD107.SetXTitle("Pt")
    HistoD107.SetYTitle("V" + str(nV) +"")
    HistoD108 = HistoD85.ProfileY("DataV" + str(nV) +"VsPtForPionsPlusCentrality10-40", 3, 8)
    HistoD108.SetXTitle("Pt")
    HistoD108.SetYTitle("V" + str(nV) +"")
    HistoD109 = HistoD85.ProfileY("DataV" + str(nV) +"VsPtForPionsPlusCentrality40-60", 9, 12)
    HistoD109.SetXTitle("Pt")
    HistoD109.SetYTitle("V" + str(nV) +"")
    HistoD110 = HistoD86.ProfileY("DataV" + str(nV) +"VsYForPionsPlusCentrality0-10", 1, 2)
    HistoD110.SetXTitle("Y - Y_CM")
    HistoD110.SetYTitle("V" + str(nV) +"")
    HistoD111 = HistoD86.ProfileY("DataV" + str(nV) +"VsYForPionsPlusCentrality10-40", 3, 8)
    HistoD111.SetXTitle("Y - Y_CM")
    HistoD111.SetYTitle("V" + str(nV) +"")
    HistoD112 = HistoD86.ProfileY("DataV" + str(nV) +"VsYForPionsPlusCentrality40-60", 9, 12)
    HistoD112.SetXTitle("Y - Y_CM")
    HistoD112.SetYTitle("V" + str(nV) +"")


    HistoD113 = HistoD87.ProfileY("DataV" + str(nV) +"VsPtForPionsMinusCentrality0-10", 1, 2)
    HistoD113.SetXTitle("Pt")
    HistoD113.SetYTitle("V" + str(nV) +"")
    HistoD114 = HistoD87.ProfileY("DataV" + str(nV) +"VsPtForPionsMinusCentrality10-40", 3, 8)
    HistoD114.SetXTitle("Pt")
    HistoD114.SetYTitle("V" + str(nV) +"")
    HistoD115 = HistoD87.ProfileY("DataV" + str(nV) +"VsPtForPionsMinusCentrality40-60", 9, 12)
    HistoD115.SetXTitle("Pt")
    HistoD115.SetYTitle("V" + str(nV) +"")
    HistoD116 = HistoD88.ProfileY("DataV" + str(nV) +"VsYForPionsMinusCentrality0-10", 1, 2)
    HistoD116.SetXTitle("Y - Y_CM")
    HistoD116.SetYTitle("V" + str(nV) +"")
    HistoD117 = HistoD88.ProfileY("DataV" + str(nV) +"VsYForPionsMinusCentrality10-40", 3, 8)
    HistoD117.SetXTitle("Y - Y_CM")
    HistoD117.SetYTitle("V" + str(nV) +"")
    HistoD118 = HistoD88.ProfileY("DataV" + str(nV) +"VsYForPionsMinusCentrality40-60", 9, 12)
    HistoD118.SetXTitle("Y - Y_CM")
    HistoD118.SetYTitle("V" + str(nV) +"")

    
    HistoD119 = HistoD88A.ProfileY("DataV" + str(nV) +"VsPtForDeuteronsCentrality0-10", 1, 2)
    HistoD119.SetXTitle("Pt")
    HistoD119.SetYTitle("V" + str(nV) +"")
    HistoD120 = HistoD88A.ProfileY("DataV" + str(nV) +"VsPtForDeuteronsCentrality10-40", 3, 8)
    HistoD120.SetXTitle("Pt")
    HistoD120.SetYTitle("V" + str(nV) +"")
    HistoD121 = HistoD88A.ProfileY("DataV" + str(nV) +"VsPtForDeuteronsCentrality40-60", 9, 12)
    HistoD121.SetXTitle("Pt")
    HistoD121.SetYTitle("V" + str(nV) +"")
    HistoD122 = HistoD88B.ProfileY("DataV" + str(nV) +"VsYForDeuteronsCentrality0-10", 1, 2)
    HistoD122.SetXTitle("Y - Y_CM")
    HistoD122.SetYTitle("V" + str(nV) +"")
    HistoD123 = HistoD88B.ProfileY("DataV" + str(nV) +"VsYForDeuteronsCentrality10-40", 3, 8)
    HistoD123.SetXTitle("Y - Y_CM")
    HistoD123.SetYTitle("V" + str(nV) +"")
    HistoD124 = HistoD88B.ProfileY("DataV" + str(nV) +"VsYForDeuteronsCentrality40-60", 9, 12)
    HistoD124.SetXTitle("Y - Y_CM")
    HistoD124.SetYTitle("V" + str(nV) +"")


    HistoD125 = HistoD88C.ProfileY("DataV" + str(nV) +"VsPtForTritonsCentrality0-10", 1, 2)
    HistoD125.SetXTitle("Pt")
    HistoD125.SetYTitle("V" + str(nV) +"")
    HistoD126 = HistoD88C.ProfileY("DataV" + str(nV) +"VsPtForTritonsCentrality10-40", 3, 8)
    HistoD126.SetXTitle("Pt")
    HistoD126.SetYTitle("V" + str(nV) +"")
    HistoD127 = HistoD88C.ProfileY("DataV" + str(nV) +"VsPtForTritonsCentrality40-60", 9, 12)
    HistoD127.SetXTitle("Pt")
    HistoD127.SetYTitle("V" + str(nV) +"")
    HistoD128 = HistoD88D.ProfileY("DataV" + str(nV) +"VsYForTritonsCentrality0-10", 1, 2)
    HistoD128.SetXTitle("Y - Y_CM")
    HistoD128.SetYTitle("V" + str(nV) +"")
    HistoD129 = HistoD88D.ProfileY("DataV" + str(nV) +"VsYForTritonsCentrality10-40", 3, 8)
    HistoD129.SetXTitle("Y - Y_CM")
    HistoD129.SetYTitle("V" + str(nV) +"")
    HistoD130 = HistoD88D.ProfileY("DataV" + str(nV) +"VsYForTritonsCentrality40-60", 9, 12)
    HistoD130.SetXTitle("Y - Y_CM")
    HistoD130.SetYTitle("V" + str(nV) +"")




    HistoD44C.SetDirectory(0)
    HistoD47B.SetDirectory(0)
    HistoD47C.SetDirectory(0)
    HistoD50B.SetDirectory(0)
    HistoD50C.SetDirectory(0)
    HistoD50D.SetDirectory(0)
    HistoD50E.SetDirectory(0)
    HistoD54A.SetDirectory(0)
    HistoD54B.SetDirectory(0)
    HistoD54C.SetDirectory(0)
    HistoD54D.SetDirectory(0)
    HistoD54E.SetDirectory(0)
    HistoD54F.SetDirectory(0)
    HistoD54G.SetDirectory(0)
    HistoD79.SetDirectory(0)
    HistoD80.SetDirectory(0)
    HistoD81.SetDirectory(0)
    HistoD82.SetDirectory(0)
    HistoD83.SetDirectory(0)
    HistoD84.SetDirectory(0)
    HistoD85.SetDirectory(0)
    HistoD86.SetDirectory(0)
    HistoD87.SetDirectory(0)
    HistoD88.SetDirectory(0)
    HistoD88A.SetDirectory(0)
    HistoD88B.SetDirectory(0)
    HistoD88C.SetDirectory(0)
    HistoD88D.SetDirectory(0)
    HistoD89.SetDirectory(0)
    HistoD90.SetDirectory(0)
    HistoD91.SetDirectory(0)
    HistoD92.SetDirectory(0)
    HistoD93.SetDirectory(0)
    HistoD94.SetDirectory(0)
    HistoD95.SetDirectory(0)
    HistoD96.SetDirectory(0)
    HistoD97.SetDirectory(0)
    HistoD98.SetDirectory(0)
    HistoD99.SetDirectory(0)
    HistoD100.SetDirectory(0)
    HistoD101.SetDirectory(0)
    HistoD102.SetDirectory(0)
    HistoD103.SetDirectory(0)
    HistoD104.SetDirectory(0)
    HistoD105.SetDirectory(0)
    HistoD106.SetDirectory(0)
    HistoD107.SetDirectory(0)
    HistoD108.SetDirectory(0)
    HistoD109.SetDirectory(0)
    HistoD110.SetDirectory(0)
    HistoD111.SetDirectory(0)
    HistoD112.SetDirectory(0)
    HistoD113.SetDirectory(0)
    HistoD114.SetDirectory(0)
    HistoD115.SetDirectory(0)
    HistoD116.SetDirectory(0)
    HistoD117.SetDirectory(0)
    HistoD118.SetDirectory(0)
    HistoD119.SetDirectory(0)
    HistoD120.SetDirectory(0)
    HistoD121.SetDirectory(0)
    HistoD122.SetDirectory(0)
    HistoD123.SetDirectory(0)
    HistoD124.SetDirectory(0)
    HistoD125.SetDirectory(0)
    HistoD126.SetDirectory(0)
    HistoD127.SetDirectory(0)
    HistoD128.SetDirectory(0)
    HistoD129.SetDirectory(0)
    HistoD130.SetDirectory(0)



    Histograms.append(HistoD44C)
    Histograms.append(HistoD47B)
    Histograms.append(HistoD47C)
    Histograms.append(HistoD50B)
    Histograms.append(HistoD50C)
    Histograms.append(HistoD50D)
    Histograms.append(HistoD50E)
    Histograms.append(HistoD54A)
    Histograms.append(HistoD54B)
    Histograms.append(HistoD54C)
    Histograms.append(HistoD54D)
    Histograms.append(HistoD54E)
    Histograms.append(HistoD54F)
    Histograms.append(HistoD54G)
    Histograms.append(HistoD79)
    Histograms.append(HistoD80)
    Histograms.append(HistoD81)
    Histograms.append(HistoD82)
    Histograms.append(HistoD83)
    Histograms.append(HistoD84)
    Histograms.append(HistoD85)
    Histograms.append(HistoD86)
    Histograms.append(HistoD87)
    Histograms.append(HistoD88)
    Histograms.append(HistoD88A)
    Histograms.append(HistoD88B)
    Histograms.append(HistoD88C)
    Histograms.append(HistoD88D)
    Histograms.append(HistoD89)
    Histograms.append(HistoD90)
    Histograms.append(HistoD91)
    Histograms.append(HistoD92)
    Histograms.append(HistoD93)
    Histograms.append(HistoD94)
    Histograms.append(HistoD95)
    Histograms.append(HistoD96)
    Histograms.append(HistoD97)
    Histograms.append(HistoD98)
    Histograms.append(HistoD99)
    Histograms.append(HistoD100)
    Histograms.append(HistoD101)
    Histograms.append(HistoD102)
    Histograms.append(HistoD103)
    Histograms.append(HistoD104)
    Histograms.append(HistoD105)
    Histograms.append(HistoD106)
    Histograms.append(HistoD107)
    Histograms.append(HistoD108)
    Histograms.append(HistoD109)
    Histograms.append(HistoD110)
    Histograms.append(HistoD111)
    Histograms.append(HistoD112)
    Histograms.append(HistoD113)
    Histograms.append(HistoD114)
    Histograms.append(HistoD115)
    Histograms.append(HistoD116)
    Histograms.append(HistoD117)
    Histograms.append(HistoD118)
    Histograms.append(HistoD119)
    Histograms.append(HistoD120)
    Histograms.append(HistoD121)
    Histograms.append(HistoD122)
    Histograms.append(HistoD123)
    Histograms.append(HistoD124)
    Histograms.append(HistoD125)
    Histograms.append(HistoD126)
    Histograms.append(HistoD127)
    Histograms.append(HistoD128)
    Histograms.append(HistoD129)
    Histograms.append(HistoD130)
    
    Data.Close()
    QVectorHistogramFileFirst.Close()
    QVectorHistogramFileSecond.Close()
    HistogramFile.Close()
    TPCEfficiencyFile.Close()
    ToFEfficiencyFile.Close()



    #HistogramRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/HistogramFourthPassTest.root", "UPDATE")
    HistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/HistogramFourthPass" + sys.argv[2] + ".root", "RECREATE")
    HistogramRootFile.cd()

    for index in range(0,len(Histograms)):
        Histograms[index].Write()

    HistogramRootFile.Close()


    print("Done")