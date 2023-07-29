#!/usr/bin/env python
# coding: utf-8

# In[1]:


#%run -i KinematicFunctions.ipynb
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

# In[3]:


# This box extracts the TTrees we want from the files we have

#Data = ROOT.TFile.Open(sys.argv[1])
Data = ROOT.TFile.Open("/star/data01/pwg/cracz/Data_3p0GeV_FXT/FXT_3p0GeV_SL20d_2018_127.root")
# MonteCarlo = ROOT.TFile.Open("/eos/user/m/migordon/SWAN_projects/HeavyIonStuff/CombinedMonteCarloFiles.root")

# Print the contents of the files
# print(Data.ls())
# print(MonteCarlo.ls())

# Get the TTree that we care about
AutreeData = Data.Get("Autree")
# JamMonteCarlo = MonteCarlo.Get("jam")

# List the contents of the TTree
# print(AutreeData.Print())
# print(JamMonteCarlo.Print())

# Create a dictionary of histograms
Histograms = []

if(AutreeData.GetEntries() == 0):
    print("No Entries Found")
    sys.exit(0)

# In[3]:


cpp_code = """
#include "StEpdGeom.h"

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
"""
ROOT.gInterpreter.Declare(cpp_code)

# In[4]:

nPsi = 1
nV = 1

# Data histograms
# Make the histograms
HistoD1 = ROOT.TH1F("DataPt", "Pt (Data); Pt (GeV); Events", 500, 0, 2)
# Uncertainties are calculated using the sum of weights, squared
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

HistoD27 = ROOT.TH2F("DataPtVsYProton", "Pt vs Y for Protons (Data); Y - Y_CM; Pt (Gev)", 500, -1, 1, 1000, 0, 2.5)
HistoD27.Sumw2()

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

HistoD33 = ROOT.TH1F("DataPsi1RawInnerEPD", "Reaction Plane Angle, Psi_1, Inner EPD (Data); Psi; Events", 75, -3.5, 3.5)
HistoD33.Sumw2()

HistoD34 = ROOT.TH1F("DataPsi1RecenteredInnerEPD", "Reaction Plane Angle, Psi_1, Inner EPD (Data); Psi; Events", 75, -3.5, 3.5)
HistoD34.Sumw2()

HistoD35 = ROOT.TH1F("DataPsi1RecenteredAndShiftedInnerEPD", "Reaction Plane Angle, Psi_1 Inner EPD (Data); Psi; Events", 75, -3.5, 3.5)
HistoD35.Sumw2()

HistoD36 = ROOT.TH1F("DataPsi1RawOuterEPD", "Reaction Plane Angle, Psi_1, Outer EPD (Data); Psi; Events", 800, 0.3, 0.7)
HistoD36.Sumw2()

HistoD37 = ROOT.TH1F("DataPsi1RecenteredOuterEPD", "Reaction Plane Angle, Psi_1, Outer EPD (Data); Psi; Events", 800, 0.3, 0.7)
HistoD37.Sumw2()

HistoD38 = ROOT.TH1F("DataPsi1RecenteredAndShiftedOuterEPD", "Reaction Plane Angle, Psi_1, Outer EPD (Data); Psi; Events", 800, 0.3, 0.7)
HistoD38.Sumw2()

HistoD39 = ROOT.TH1F("DataPsi1RawTPC", "Reaction Plane Angle, Psi_1, TPC (Data); Psi; Events", 75, -3.5, 3.5)
HistoD39.Sumw2()

HistoD40 = ROOT.TH1F("DataPsi1RecenteredTPC", "Reaction Plane Angle, Psi_1, TPC (Data); Psi; Events", 75, -3.5, 3.5)
HistoD40.Sumw2()

HistoD41 = ROOT.TH1F("DataPsi1RecenteredAndShiftedTPC", "Reaction Plane Angle, Psi_1, TPC (Data); Psi; Events", 75, -3.5, 3.5)
HistoD41.Sumw2()

HistoD42 = ROOT.TProfile("DataVnVsYPsi1RawInnerEPDProton", "V" + str(nV) + " Observed vs Y for Protons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD42.Sumw2()

HistoD43 = ROOT.TProfile("DataVnVsYPsi1RecenteredInnerEPDProton", "V" + str(nV) + " Observed vs Y for Protons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD43.Sumw2()

HistoD44 = ROOT.TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDProton", "V" + str(nV) + " Observed vs Y for Protons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD44.Sumw2()

HistoD44A = ROOT.TProfile("DataVnVsYPsi1ResolutionCorrectedProton", "V" + str(nV) + " Observed and Resolution Corrected vs Y for Protons, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD44A.Sumw2()

HistoD45 = ROOT.TProfile("DataVnVsYPsi1RawInnerEPDKaonPlus", "V" + str(nV) + " Observed vs Y for K+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD45.Sumw2()

HistoD45A = ROOT.TProfile("DataVnVsYPsi1RawInnerEPDKaonMinus", "V" + str(nV) + " Observed vs Y for K-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD45A.Sumw2()

HistoD46 = ROOT.TProfile("DataVnVsYPsi1RecenteredInnerEPDKaonPlus", "V" + str(nV) + " Observed vs Y for K+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD46.Sumw2()

HistoD46A = ROOT.TProfile("DataVnVsYPsi1RecenteredInnerEPDKaonMinus", "V" + str(nV) + " Observed vs Y for K-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD46A.Sumw2()

HistoD47 = ROOT.TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDKaonPlus", "V" + str(nV) + " Observed vs Y for K+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD47.Sumw2()

HistoD47A = ROOT.TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDKaonMinus", "V" + str(nV) + " Observed vs Y for K-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD47A.Sumw2()

HistoD47B = ROOT.TProfile("DataVnVsYPsi1ResolutionCorrectedKaonPlus", "V" + str(nV) + " Observed and Resolution Corrected vs Y for K+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD47B.Sumw2()

HistoD47C = ROOT.TProfile("DataVnVsYPsi1ResolutionCorrectedKaonMinus", "V" + str(nV) + " Observed and Resolution Corrected vs Y for K-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD47C.Sumw2()

HistoD48 = ROOT.TProfile("DataVnVsYPsi1RawInnerEPDPionPlus", "V" + str(nV) + " Observed vs Y for Pi+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD48.Sumw2()

HistoD48A = ROOT.TProfile("DataVnVsYPsi1RawInnerEPDPionMinus", "V" + str(nV) + " Observed vs Y for Pi-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD48A.Sumw2()

HistoD49 = ROOT.TProfile("DataVnVsYPsi1RecenteredInnerEPDPionPlus", "V" + str(nV) + " Observed vs Y for Pi+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD49.Sumw2()

HistoD49A = ROOT.TProfile("DataVnVsYPsi1RecenteredInnerEPDPionMinus", "V" + str(nV) + " Observed vs Y for Pi-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD49A.Sumw2()

HistoD50 = ROOT.TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDPionPlus", "V" + str(nV) + " Observed vs Y for Pi+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD50.Sumw2()

HistoD50A = ROOT.TProfile("DataVnVsYPsi1RecenteredAndShiftedInnerEPDPionMinus", "V" + str(nV) + " Observed vs Y for Pi-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD50A.Sumw2()

HistoD50B = ROOT.TProfile("DataVnVsYPsi1ResolutionCorrectedPionPlus", "V" + str(nV) + " Observed and Resolution Corrected vs Y for Pi+, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD50B.Sumw2()

HistoD50C = ROOT.TProfile("DataVnVsYPsi1ResolutionCorrectedPionMinus", "V" + str(nV) + " Observed and Resolution Corrected vs Y for Pi-, Calculated using Inner EPD (Data); Y - Y_CM; V" + str(nV) +"", 75, -0.3, 0.95)
HistoD50C.Sumw2()

HistoD51 = ROOT.TProfile("DataResolutionTopLeftTerm", "Resolution Top Left Term (Data); Centrality; Top Left Term", 12, -0.5, 11.5)
HistoD51.Sumw2()

HistoD52 = ROOT.TProfile("DataResolutionTopRightTerm", "Resolution Top Right Term (Data); Centrality; Top Right Term", 12, -0.5, 11.5)
HistoD52.Sumw2()

HistoD53 = ROOT.TProfile("DataResolutionBottomTerm", "Resolution Bottom Term (Data); Centrality; Bottom Term", 12, -0.5, 11.5)
HistoD53.Sumw2()

HistoD54 = ROOT.TProfile("DataResolution", "Resolution (R" + str(nV) + "1) (Data); Centrality; Resolution", 12, -0.5, 11.5)
HistoD54.Sumw2()

HistoD54A = ROOT.TProfile("DataVnVsCentralityProtonCorrected", "V" + str(nV) + " vs Centrality for Protons (Data); Centrality; V" + str(nV) +"", 12, -0.5, 11.5)
HistoD54A.Sumw2()

HistoD54B = ROOT.TProfile("DataVnVsCentralityKaonPlusCorrected", "V" + str(nV) + " vs Centrality for Kaon+ (Data); Centrality; V" + str(nV) +"", 12, -0.5, 11.5)
HistoD54B.Sumw2()

HistoD54C = ROOT.TProfile("DataVnVsCentralityKaonMinusCorrected", "V" + str(nV) + " vs Centrality for Kaon- (Data); Centrality; V" + str(nV) +"", 12, -0.5, 11.5)
HistoD54C.Sumw2()

HistoD54D = ROOT.TProfile("DataVnVsCentralityPionPlusCorrected", "V" + str(nV) + " vs Centrality for Pion+ (Data); Centrality; V" + str(nV) +"", 12, -0.5, 11.5)
HistoD54D.Sumw2()

HistoD54E = ROOT.TProfile("DataVnVsCentralityPionMinusCorrected", "V" + str(nV) + " vs Centrality for Pion- (Data); Centrality; V" + str(nV) +"", 12, -0.5, 11.5)
HistoD54E.Sumw2()

HistoD79 = ROOT.TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesProton", "V" + str(nV) + " (Resolution Corrected) vs Pt for Protons for Different Centralities (Data); Centrality; Pt", 12, -0.5, 11.5, 20, 0, 2)
HistoD79.Sumw2()

HistoD80 = ROOT.TProfile2D("DataVnCorrectedVsYDifferentCentralitiesProton", "V" + str(nV) + " (Resolution Corrected) vs Y for Protons for Different Centralities (Data); Centrality; Y - Y_CM", 12, -0.5, 11.5, 10, 0, 1)
HistoD80.Sumw2()

HistoD81 = ROOT.TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesKaonPlus", "V" + str(nV) + " (Resolution Corrected) vs Pt for K+ for Different Centralities (Data); Centrality; Pt", 12, -0.5, 11.5, 20, 0, 2)
HistoD81.Sumw2()

HistoD82 = ROOT.TProfile2D("DataVnCorrectedVsYDifferentCentralitiesKaonPlus", "V" + str(nV) + " (Resolution Corrected) vs Y for K+ for Different Centralities (Data); Centrality; Y - Y_CM", 12, -0.5, 11.5, 10, 0, 1)
HistoD82.Sumw2()

HistoD83 = ROOT.TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesKaonNegative", "V" + str(nV) + " (Resolution Corrected) vs Pt for K- for Different Centralities (Data); Centrality; Pt", 12, -0.5, 11.5, 20, 0, 2)
HistoD83.Sumw2()

HistoD84 = ROOT.TProfile2D("DataVnCorrectedVsYDifferentCentralitiesKaonNegative", "V" + str(nV) + " (Resolution Corrected) vs Y for K- for Different Centralities (Data); Centrality; Y - Y_CM", 12, -0.5, 11.5, 10, 0, 1)
HistoD84.Sumw2()

HistoD85 = ROOT.TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesPionPlus", "V" + str(nV) + " (Resolution Corrected) vs Pt for Pi+ for Different Centralities (Data); Centrality; Pt", 12, -0.5, 11.5, 20, 0, 2)
HistoD85.Sumw2()

HistoD86 = ROOT.TProfile2D("DataVnCorrectedVsYDifferentCentralitiesPionPlus", "V" + str(nV) + " (Resolution Corrected) vs Y for Pi+ for Different Centralities (Data); Centrality; Y - Y_CM", 12, -0.5, 11.5, 10, 0, 1)
HistoD86.Sumw2()

HistoD87 = ROOT.TProfile2D("DataVnCorrectedVsPtDifferentCentralitiesPionNegative", "V" + str(nV) + " (Resolution Corrected) vs Pt for Pi- for Different Centralities (Data); Centrality; Pt", 12, -0.5, 11.5, 20, 0, 2)
HistoD87.Sumw2()

HistoD88 = ROOT.TProfile2D("DataVnCorrectedVsYDifferentCentralitiesPionNegative", "V" + str(nV) + " (Resolution Corrected) vs Y for Pi- for Different Centralities (Data); Centrality; Y - Y_CM", 12, -0.5, 11.5, 10, 0, 1)
HistoD88.Sumw2()




yCMShift = -1.045
NumberOfGoodTracksInnerEPD = 5
NumberOfGoodTracksOuterEPD = 9
NumberOfGoodTracksTPC = 5
InnerEPDUpperLimit = -3.5
InnerEPDLowerLimit = -5.6
OuterEPDUpperLimit = -2.4
OuterEPDLowerLimit = -3.5
TPCUpperLimit = 0
TPCLowerLimit = -1
ProtonLowerPt = 0.4
ProtonUpperPt = 2.0
KaonLowerPt = 0.4
KaonUpperPt = 1.6
PionLowerPt = 0.2
PionUpperPt = 1.6

# Used for the calculation of Psi_1, recentering, and Fourier adjustments
ReactionPlaneNumeratorInnerEPD = 0
ReactionPlaneDenominatorInnerEPD = 0
ReactionPlaneNumeratorOuterEPD = 0
ReactionPlaneDenominatorOuterEPD = 0
ReactionPlaneNumeratorTPC = 0
ReactionPlaneDenominatorTPC = 0
QVectorCountInnerEPD = 0
QVectorCountOuterEPD = 0
QVectorCountTPC = 0

# Fill the histogram
for entryNum in range (0, AutreeData.GetEntries()):
    if (entryNum % 5000 == 0):
        print("Data First Pass (Recentering)", entryNum)
        
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
    
    Multiplicity = len(px)

    ReactionPlaneNumeratorInnerEPDOneEvent = 0
    ReactionPlaneDenominatorInnerEPDOneEvent = 0
    ReactionPlaneNumeratorOuterEPDOneEvent = 0
    ReactionPlaneDenominatorOuterEPDOneEvent = 0
    ReactionPlaneNumeratorTPCOneEvent = 0
    ReactionPlaneDenominatorTPCOneEvent = 0

    # Skip anything where tofBeta <= 0
    for index in range(len(px)):
        pt = Pt(px[index], py[index])
    
        p = P(px[index], py[index], pz[index])

        eta = Eta(px[index], py[index], pz[index])
        
        qp = QP(q[index], px[index], py[index], pz[index])
        
        phi = Phi(px[index], py[index])
            
        if(tofBeta[index] > 0):

            msquared = MSquared(px[index], py[index], pz[index], tofBeta[index])
            
            HistoD4.Fill(qp, msquared)
            HistoD4A.Fill(qp, msquared)
            
            HistoD24.Fill(qp, NSigmaPr[index])
            HistoD25.Fill(qp, NSigmaKa[index])
            HistoD26.Fill(qp, NSigmaPi[index])

            # Proton criteria
            if((abs(NSigmaPr[index]) < 3) and (msquared > 0.45) and (msquared < 2.0)): 
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
            elif((abs(NSigmaKa[index]) < 3) and (msquared > 0.15) and (msquared < 0.45)):
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
            elif((abs(NSigmaPi[index]) < 3) and (msquared < 0.15)):
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
                    
            elif((msquared > 2.0) and (msquared < 5.0)):
                HistoD16.Fill(p, dEdx[index])

            elif(msquared > 5.0):
                HistoD17.Fill(p, dEdx[index])
        
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
            ReactionPlaneNumeratorTPCOneEvent += pt*sin(nPsi*phi)
            ReactionPlaneDenominatorTPCOneEvent += pt*cos(nPsi*phi)
            
#         elif ((eta > TPCLowerLimit) and (eta < yCMShift)):
#             ReactionPlaneNumeratorTPCOneEvent -= pt*sin(nPsi*phi)
#             ReactionPlaneDenominatorTPCOneEvent -= pt*cos(nPsi*phi)
            
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
        
        if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
            ReactionPlaneNumeratorInnerEPDOneEvent -= EPDnMIP[index]*sin(nPsi*phi)
            ReactionPlaneDenominatorInnerEPDOneEvent -= EPDnMIP[index]*cos(nPsi*phi)
            
        if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
            ReactionPlaneNumeratorOuterEPDOneEvent -= EPDnMIP[index]*sin(nPsi*phi)
            ReactionPlaneDenominatorOuterEPDOneEvent -= EPDnMIP[index]*cos(nPsi*phi)
            
    ReactionPlaneNumeratorInnerEPD += ReactionPlaneNumeratorInnerEPDOneEvent
    ReactionPlaneDenominatorInnerEPD += ReactionPlaneDenominatorInnerEPDOneEvent
    
    ReactionPlaneNumeratorOuterEPD += ReactionPlaneNumeratorOuterEPDOneEvent
    ReactionPlaneDenominatorOuterEPD += ReactionPlaneDenominatorOuterEPDOneEvent
    
    ReactionPlaneNumeratorTPC += ReactionPlaneNumeratorTPCOneEvent
    ReactionPlaneDenominatorTPC += ReactionPlaneDenominatorTPCOneEvent

    PsiInnerEPDRaw = (1/nPsi)*atan2(ReactionPlaneNumeratorInnerEPDOneEvent, ReactionPlaneDenominatorInnerEPDOneEvent)
    PsiOuterEPDRaw = (1/nPsi)*atan2(ReactionPlaneNumeratorOuterEPDOneEvent, ReactionPlaneDenominatorOuterEPDOneEvent)
    PsiTPCRaw = (1/nPsi)*atan2(ReactionPlaneNumeratorTPCOneEvent, ReactionPlaneDenominatorTPCOneEvent)

    if(PsiOuterEPDRaw != 0):
        HistoD36.Fill(PsiOuterEPDRaw)
        QVectorCountOuterEPD += 1

    HistoD39.Fill(PsiTPCRaw)

    QVectorCountTPC += 1
        
    if(PsiInnerEPDRaw == 0):
        continue
 
    HistoD33.Fill(PsiInnerEPDRaw)
    
    QVectorCountInnerEPD += 1
    
    for index in range(len(px)):
        pt = Pt(px[index], py[index])
    
        p = P(px[index], py[index], pz[index])
        
        eta = Eta(px[index], py[index], pz[index])
        
        phi = Phi(px[index], py[index])
            
        if(tofBeta[index] > 0):

            msquared = MSquared(px[index], py[index], pz[index], tofBeta[index])
            
            if((abs(NSigmaPr[index]) < 3) and (msquared > 0.45) and (msquared < 2.0) and (pt > ProtonLowerPt) and (pt < ProtonUpperPt)): 
                mass = ProtonMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                VnInnerEPD = V_n(nV, px[index], py[index], PsiInnerEPDRaw)

                HistoD42.Fill(y - yCMShift, VnInnerEPD)
                
            if((abs(NSigmaKa[index]) < 3) and (msquared > 0.15) and (msquared < 0.45) and (pt > KaonLowerPt) and (pt < KaonUpperPt)): 
                mass = KaonMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)
                
                VnInnerEPD = V_n(nV, px[index], py[index], PsiInnerEPDRaw)
                
                if(q[index] > 0):
                    HistoD45.Fill(y - yCMShift, VnInnerEPD)
                    
                if(q[index] < 0):
                    HistoD45A.Fill(y - yCMShift, VnInnerEPD)
                
            if((abs(NSigmaPi[index]) < 3) and (msquared < 0.15)  and (pt > PionLowerPt) and (pt < PionUpperPt)): 
                mass = PionMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)
                
                VnInnerEPD = V_n(nV, px[index], py[index], PsiInnerEPDRaw)

                if(q[index] > 0):
                    HistoD48.Fill(y - yCMShift, VnInnerEPD)
                    
                if(q[index] < 0):
                    HistoD48A.Fill(y - yCMShift, VnInnerEPD)
            
# Recentering
AverageQNumeratorInnerEPD = ReactionPlaneNumeratorInnerEPD / QVectorCountInnerEPD
AverageQDenominatorInnerEPD = ReactionPlaneDenominatorInnerEPD / QVectorCountInnerEPD
AverageQNumeratorOuterEPD = ReactionPlaneNumeratorOuterEPD / QVectorCountOuterEPD
AverageQDenominatorOuterEPD = ReactionPlaneDenominatorOuterEPD / QVectorCountOuterEPD
AverageQNumeratorTPC = ReactionPlaneNumeratorTPC / QVectorCountTPC
AverageQDenominatorTPC = ReactionPlaneDenominatorTPC / QVectorCountTPC


# In[ ]:











QVectorCountInnerEPD = 0
QVectorCountOuterEPD = 0
QVectorCountTPC = 0

FourierCorrectionInnerEPDSineJ1 = 0
FourierCorrectionInnerEPDSineJ2 = 0
FourierCorrectionInnerEPDSineJ3 = 0
FourierCorrectionInnerEPDSineJ4 = 0
FourierCorrectionInnerEPDSineJ5 = 0
FourierCorrectionInnerEPDSineJ6 = 0
FourierCorrectionInnerEPDSineJ7 = 0
FourierCorrectionInnerEPDSineJ8 = 0
FourierCorrectionInnerEPDSineJ9 = 0
FourierCorrectionInnerEPDSineJ10 = 0
FourierCorrectionInnerEPDSineJ11 = 0
FourierCorrectionInnerEPDSineJ12 = 0
FourierCorrectionInnerEPDSineJ13 = 0
FourierCorrectionInnerEPDSineJ14 = 0
FourierCorrectionInnerEPDSineJ15 = 0
FourierCorrectionInnerEPDSineJ16 = 0
FourierCorrectionInnerEPDSineJ17 = 0
FourierCorrectionInnerEPDSineJ18 = 0
FourierCorrectionInnerEPDSineJ19 = 0
FourierCorrectionInnerEPDSineJ20 = 0
FourierCorrectionInnerEPDCosineJ1 = 0
FourierCorrectionInnerEPDCosineJ2 = 0
FourierCorrectionInnerEPDCosineJ3 = 0
FourierCorrectionInnerEPDCosineJ4 = 0
FourierCorrectionInnerEPDCosineJ5 = 0
FourierCorrectionInnerEPDCosineJ6 = 0
FourierCorrectionInnerEPDCosineJ7 = 0
FourierCorrectionInnerEPDCosineJ8 = 0
FourierCorrectionInnerEPDCosineJ9 = 0
FourierCorrectionInnerEPDCosineJ10 = 0
FourierCorrectionInnerEPDCosineJ11 = 0
FourierCorrectionInnerEPDCosineJ12 = 0
FourierCorrectionInnerEPDCosineJ13 = 0
FourierCorrectionInnerEPDCosineJ14 = 0
FourierCorrectionInnerEPDCosineJ15 = 0
FourierCorrectionInnerEPDCosineJ16 = 0
FourierCorrectionInnerEPDCosineJ17 = 0
FourierCorrectionInnerEPDCosineJ18 = 0
FourierCorrectionInnerEPDCosineJ19 = 0
FourierCorrectionInnerEPDCosineJ20 = 0
FourierCorrectionOuterEPDSineJ1 = 0
FourierCorrectionOuterEPDSineJ2 = 0
FourierCorrectionOuterEPDSineJ3 = 0
FourierCorrectionOuterEPDSineJ4 = 0
FourierCorrectionOuterEPDSineJ5 = 0
FourierCorrectionOuterEPDSineJ6 = 0
FourierCorrectionOuterEPDSineJ7 = 0
FourierCorrectionOuterEPDSineJ8 = 0
FourierCorrectionOuterEPDSineJ9 = 0
FourierCorrectionOuterEPDSineJ10 = 0
FourierCorrectionOuterEPDSineJ11 = 0
FourierCorrectionOuterEPDSineJ12 = 0
FourierCorrectionOuterEPDSineJ13 = 0
FourierCorrectionOuterEPDSineJ14 = 0
FourierCorrectionOuterEPDSineJ15 = 0
FourierCorrectionOuterEPDSineJ16 = 0
FourierCorrectionOuterEPDSineJ17 = 0
FourierCorrectionOuterEPDSineJ18 = 0
FourierCorrectionOuterEPDSineJ19 = 0
FourierCorrectionOuterEPDSineJ20 = 0
FourierCorrectionOuterEPDCosineJ1 = 0
FourierCorrectionOuterEPDCosineJ2 = 0
FourierCorrectionOuterEPDCosineJ3 = 0
FourierCorrectionOuterEPDCosineJ4 = 0
FourierCorrectionOuterEPDCosineJ5 = 0
FourierCorrectionOuterEPDCosineJ6 = 0
FourierCorrectionOuterEPDCosineJ7 = 0
FourierCorrectionOuterEPDCosineJ8 = 0
FourierCorrectionOuterEPDCosineJ9 = 0
FourierCorrectionOuterEPDCosineJ10 = 0
FourierCorrectionOuterEPDCosineJ11 = 0
FourierCorrectionOuterEPDCosineJ12 = 0
FourierCorrectionOuterEPDCosineJ13 = 0
FourierCorrectionOuterEPDCosineJ14 = 0
FourierCorrectionOuterEPDCosineJ15 = 0
FourierCorrectionOuterEPDCosineJ16 = 0
FourierCorrectionOuterEPDCosineJ17 = 0
FourierCorrectionOuterEPDCosineJ18 = 0
FourierCorrectionOuterEPDCosineJ19 = 0
FourierCorrectionOuterEPDCosineJ20 = 0
FourierCorrectionTPCSineJ1 = 0
FourierCorrectionTPCSineJ2 = 0
FourierCorrectionTPCSineJ3 = 0
FourierCorrectionTPCSineJ4 = 0
FourierCorrectionTPCSineJ5 = 0
FourierCorrectionTPCSineJ6 = 0
FourierCorrectionTPCSineJ7 = 0
FourierCorrectionTPCSineJ8 = 0
FourierCorrectionTPCSineJ9 = 0
FourierCorrectionTPCSineJ10 = 0
FourierCorrectionTPCSineJ11 = 0
FourierCorrectionTPCSineJ12 = 0
FourierCorrectionTPCSineJ13 = 0
FourierCorrectionTPCSineJ14 = 0
FourierCorrectionTPCSineJ15 = 0
FourierCorrectionTPCSineJ16 = 0
FourierCorrectionTPCSineJ17 = 0
FourierCorrectionTPCSineJ18 = 0
FourierCorrectionTPCSineJ19 = 0
FourierCorrectionTPCSineJ20 = 0
FourierCorrectionTPCCosineJ1 = 0
FourierCorrectionTPCCosineJ2 = 0
FourierCorrectionTPCCosineJ3 = 0
FourierCorrectionTPCCosineJ4 = 0
FourierCorrectionTPCCosineJ5 = 0
FourierCorrectionTPCCosineJ6 = 0
FourierCorrectionTPCCosineJ7 = 0
FourierCorrectionTPCCosineJ8 = 0
FourierCorrectionTPCCosineJ9 = 0
FourierCorrectionTPCCosineJ10 = 0
FourierCorrectionTPCCosineJ11 = 0
FourierCorrectionTPCCosineJ12 = 0
FourierCorrectionTPCCosineJ13 = 0
FourierCorrectionTPCCosineJ14 = 0
FourierCorrectionTPCCosineJ15 = 0
FourierCorrectionTPCCosineJ16 = 0
FourierCorrectionTPCCosineJ17 = 0
FourierCorrectionTPCCosineJ18 = 0
FourierCorrectionTPCCosineJ19 = 0
FourierCorrectionTPCCosineJ20 = 0

# Loop through every event; skip anything with a PID not equal to a p,K, or pi; we shift the Q-vectors now
for entryNum in range (0, AutreeData.GetEntries()):
    if (entryNum % 5000 == 0):
        print("Data Second Pass (Fourier Correction Sine and Cosine Term Calculation)", entryNum)

    AutreeData.GetEntry(entryNum)

    px = AutreeData.Px
    py = AutreeData.Py
    pz = AutreeData.Pz
    q = AutreeData.Charge
    tofBeta = AutreeData.tofBeta
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
    
    ReactionPlaneNumeratorInnerEPDOneEvent = 0
    ReactionPlaneDenominatorInnerEPDOneEvent = 0
    ReactionPlaneNumeratorOuterEPDOneEvent = 0
    ReactionPlaneDenominatorOuterEPDOneEvent = 0
    ReactionPlaneNumeratorTPCOneEvent = 0
    ReactionPlaneDenominatorTPCOneEvent = 0
    
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
            ReactionPlaneNumeratorTPCOneEvent += pt*sin(nPsi*phi)
            ReactionPlaneDenominatorTPCOneEvent += pt*cos(nPsi*phi)
            
#         elif ((eta > TPCLowerLimit) and (eta < yCMShift)):
#             ReactionPlaneNumeratorTPCOneEvent -= pt*sin(nPsi*phi)
#             ReactionPlaneDenominatorTPCOneEvent -= pt*cos(nPsi*phi)

    for index in range(len(EPDID)):
        if(EPDID[index] > 0):
            continue
            
        TileVector = ROOT.EPDKinematics(EPDID[index], vx, vy, vz)
        
        phi = TileVector.EPDPhi()
        
        if(EPDnMIP[index] < 0.3):
            EPDnMIP[index] = 0
            
        if(EPDnMIP[index] > 2.0):
            EPDnMIP[index] = 2.0
       
        if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
            ReactionPlaneNumeratorInnerEPDOneEvent -= EPDnMIP[index]*sin(nPsi*phi)
            ReactionPlaneDenominatorInnerEPDOneEvent -= EPDnMIP[index]*cos(nPsi*phi)
            
        if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
            ReactionPlaneNumeratorOuterEPDOneEvent -= EPDnMIP[index]*sin(nPsi*phi)
            ReactionPlaneDenominatorOuterEPDOneEvent -= EPDnMIP[index]*cos(nPsi*phi)
    
    PsiInnerEPD = (1/nPsi)*atan2((ReactionPlaneNumeratorInnerEPDOneEvent - AverageQNumeratorInnerEPD), (ReactionPlaneDenominatorInnerEPDOneEvent - AverageQDenominatorInnerEPD))
    PsiOuterEPD = (1/nPsi)*atan2((ReactionPlaneNumeratorOuterEPDOneEvent - AverageQNumeratorOuterEPD), (ReactionPlaneDenominatorOuterEPDOneEvent - AverageQDenominatorOuterEPD))
    PsiTPC = (1/nPsi)*atan2((ReactionPlaneNumeratorTPCOneEvent - AverageQNumeratorTPC), (ReactionPlaneDenominatorTPCOneEvent - AverageQDenominatorTPC))
    
    if(PsiOuterEPD != 0):
        FourierCorrectionOuterEPDSineJ1 += (-1)*sin(1*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ2 += (-1)*sin(2*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ3 += (-1)*sin(3*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ4 += (-1)*sin(4*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ5 += (-1)*sin(5*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ6 += (-1)*sin(6*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ7 += (-1)*sin(7*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ8 += (-1)*sin(8*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ9 += (-1)*sin(9*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ10 += (-1)*sin(10*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ11 += (-1)*sin(11*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ12 += (-1)*sin(12*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ13 += (-1)*sin(13*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ14 += (-1)*sin(14*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ15 += (-1)*sin(15*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ16 += (-1)*sin(16*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ17 += (-1)*sin(17*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ18 += (-1)*sin(18*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ19 += (-1)*sin(19*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDSineJ20 += (-1)*sin(20*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ1 += cos(1*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ2 += cos(2*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ3 += cos(3*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ4 += cos(4*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ5 += cos(5*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ6 += cos(6*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ7 += cos(7*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ8 += cos(8*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ9 += cos(9*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ10 += cos(10*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ11 += cos(11*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ12 += cos(12*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ13 += cos(13*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ14 += cos(14*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ15 += cos(15*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ16 += cos(16*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ17 += cos(17*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ18 += cos(18*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ19 += cos(19*nPsi*PsiOuterEPD)
        FourierCorrectionOuterEPDCosineJ20 += cos(20*nPsi*PsiOuterEPD)
        
        QVectorCountOuterEPD += 1
        
        HistoD37.Fill(PsiOuterEPD)
        
    FourierCorrectionTPCSineJ1 += (-1)*sin(1*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ2 += (-1)*sin(2*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ3 += (-1)*sin(3*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ4 += (-1)*sin(4*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ5 += (-1)*sin(5*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ6 += (-1)*sin(6*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ7 += (-1)*sin(7*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ8 += (-1)*sin(8*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ9 += (-1)*sin(9*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ10 += (-1)*sin(10*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ11 += (-1)*sin(11*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ12 += (-1)*sin(12*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ13 += (-1)*sin(13*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ14 += (-1)*sin(14*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ15 += (-1)*sin(15*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ16 += (-1)*sin(16*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ17 += (-1)*sin(17*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ18 += (-1)*sin(18*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ19 += (-1)*sin(19*nPsi*PsiTPC)
    FourierCorrectionTPCSineJ20 += (-1)*sin(20*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ1 += cos(1*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ2 += cos(2*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ3 += cos(3*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ4 += cos(4*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ5 += cos(5*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ6 += cos(6*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ7 += cos(7*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ8 += cos(8*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ9 += cos(9*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ10 += cos(10*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ11 += cos(11*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ12 += cos(12*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ13 += cos(13*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ14 += cos(14*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ15 += cos(15*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ16 += cos(16*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ17 += cos(17*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ18 += cos(18*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ19 += cos(19*nPsi*PsiTPC)
    FourierCorrectionTPCCosineJ20 += cos(20*nPsi*PsiTPC)
    
    QVectorCountTPC += 1
        
    HistoD40.Fill(PsiTPC)
    
    if(PsiInnerEPD == 0):
        continue
    
    FourierCorrectionInnerEPDSineJ1 += (-1)*sin(1*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ2 += (-1)*sin(2*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ3 += (-1)*sin(3*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ4 += (-1)*sin(4*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ5 += (-1)*sin(5*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ6 += (-1)*sin(6*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ7 += (-1)*sin(7*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ8 += (-1)*sin(8*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ9 += (-1)*sin(9*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ10 += (-1)*sin(10*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ11 += (-1)*sin(11*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ12 += (-1)*sin(12*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ13 += (-1)*sin(13*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ14 += (-1)*sin(14*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ15 += (-1)*sin(15*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ16 += (-1)*sin(16*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ17 += (-1)*sin(17*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ18 += (-1)*sin(18*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ19 += (-1)*sin(19*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDSineJ20 += (-1)*sin(20*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ1 += cos(1*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ2 += cos(2*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ3 += cos(3*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ4 += cos(4*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ5 += cos(5*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ6 += cos(6*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ7 += cos(7*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ8 += cos(8*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ9 += cos(9*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ10 += cos(10*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ11 += cos(11*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ12 += cos(12*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ13 += cos(13*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ14 += cos(14*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ15 += cos(15*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ16 += cos(16*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ17 += cos(17*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ18 += cos(18*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ19 += cos(19*nPsi*PsiInnerEPD)
    FourierCorrectionInnerEPDCosineJ20 += cos(20*nPsi*PsiInnerEPD)

    QVectorCountInnerEPD += 1

    HistoD34.Fill(PsiInnerEPD)
    
    for index in range(len(px)):
        pt = Pt(px[index], py[index])
    
        p = P(px[index], py[index], pz[index])
        
        eta = Eta(px[index], py[index], pz[index])
        
        phi = Phi(px[index], py[index])
            
        if(tofBeta[index] > 0):

            msquared = MSquared(px[index], py[index], pz[index], tofBeta[index])
            
            if((abs(NSigmaPr[index]) < 3) and (msquared > 0.45) and (msquared < 2.0) and (pt > ProtonLowerPt) and (pt < ProtonUpperPt)): 
                mass = ProtonMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                VnInnerEPD = V_n(nV, px[index], py[index], PsiInnerEPD)

                HistoD43.Fill(y - yCMShift, VnInnerEPD)
                
            if((abs(NSigmaKa[index]) < 3) and (msquared > 0.15) and (msquared < 0.45) and (pt > KaonLowerPt) and (pt < KaonUpperPt)): 
                mass = KaonMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)
                
                VnInnerEPD = V_n(nV, px[index], py[index], PsiInnerEPD)

                if(q[index] > 0):
                    HistoD46.Fill(y - yCMShift, VnInnerEPD)
                    
                if(q[index] < 0):
                    HistoD46A.Fill(y - yCMShift, VnInnerEPD)
                
            if((abs(NSigmaPi[index]) < 3) and (msquared < 0.15) and (pt > PionLowerPt) and (pt < PionUpperPt)): 
                mass = PionMass
                
                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)
                
                VnInnerEPD = V_n(nV, px[index], py[index], PsiInnerEPD)

                if(q[index] > 0):
                    HistoD49.Fill(y - yCMShift, VnInnerEPD)
                    
                if(q[index] < 0):
                    HistoD49A.Fill(y - yCMShift, VnInnerEPD)
    
FourierCorrectionInnerEPDSineJ1 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ2 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ3 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ4 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ5 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ6 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ7 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ8 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ9 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ10 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ11 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ12 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ13 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ14 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ15 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ16 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ17 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ18 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ19 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDSineJ20 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ1 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ2 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ3 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ4 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ5 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ6 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ7 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ8 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ9 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ10 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ11 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ12 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ13 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ14 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ15 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ16 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ17 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ18 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ19 /= QVectorCountInnerEPD
FourierCorrectionInnerEPDCosineJ20 /= QVectorCountInnerEPD
FourierCorrectionOuterEPDSineJ1 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ2 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ3 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ4 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ5 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ6 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ7 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ8 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ9 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ10 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ11 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ12 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ13 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ14 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ15 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ16 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ17 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ18 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ19 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDSineJ20 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ1 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ2 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ3 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ4 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ5 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ6 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ7 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ8 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ9 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ10 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ11 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ12 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ13 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ14 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ15 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ16 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ17 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ18 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ19 /= QVectorCountOuterEPD
FourierCorrectionOuterEPDCosineJ20 /= QVectorCountOuterEPD
FourierCorrectionTPCSineJ1 /= QVectorCountTPC
FourierCorrectionTPCSineJ2 /= QVectorCountTPC
FourierCorrectionTPCSineJ3 /= QVectorCountTPC
FourierCorrectionTPCSineJ4 /= QVectorCountTPC
FourierCorrectionTPCSineJ5 /= QVectorCountTPC
FourierCorrectionTPCSineJ6 /= QVectorCountTPC
FourierCorrectionTPCSineJ7 /= QVectorCountTPC
FourierCorrectionTPCSineJ8 /= QVectorCountTPC
FourierCorrectionTPCSineJ9 /= QVectorCountTPC
FourierCorrectionTPCSineJ10 /= QVectorCountTPC
FourierCorrectionTPCSineJ11 /= QVectorCountTPC
FourierCorrectionTPCSineJ12 /= QVectorCountTPC
FourierCorrectionTPCSineJ13 /= QVectorCountTPC
FourierCorrectionTPCSineJ14 /= QVectorCountTPC
FourierCorrectionTPCSineJ15 /= QVectorCountTPC
FourierCorrectionTPCSineJ16 /= QVectorCountTPC
FourierCorrectionTPCSineJ17 /= QVectorCountTPC
FourierCorrectionTPCSineJ18 /= QVectorCountTPC
FourierCorrectionTPCSineJ19 /= QVectorCountTPC
FourierCorrectionTPCSineJ20 /= QVectorCountTPC
FourierCorrectionTPCCosineJ1 /= QVectorCountTPC
FourierCorrectionTPCCosineJ2 /= QVectorCountTPC
FourierCorrectionTPCCosineJ3 /= QVectorCountTPC
FourierCorrectionTPCCosineJ4 /= QVectorCountTPC
FourierCorrectionTPCCosineJ5 /= QVectorCountTPC
FourierCorrectionTPCCosineJ6 /= QVectorCountTPC
FourierCorrectionTPCCosineJ7 /= QVectorCountTPC
FourierCorrectionTPCCosineJ8 /= QVectorCountTPC
FourierCorrectionTPCCosineJ9 /= QVectorCountTPC
FourierCorrectionTPCCosineJ10 /= QVectorCountTPC
FourierCorrectionTPCCosineJ11 /= QVectorCountTPC
FourierCorrectionTPCCosineJ12 /= QVectorCountTPC
FourierCorrectionTPCCosineJ13 /= QVectorCountTPC
FourierCorrectionTPCCosineJ14 /= QVectorCountTPC
FourierCorrectionTPCCosineJ15 /= QVectorCountTPC
FourierCorrectionTPCCosineJ16 /= QVectorCountTPC
FourierCorrectionTPCCosineJ17 /= QVectorCountTPC
FourierCorrectionTPCCosineJ18 /= QVectorCountTPC
FourierCorrectionTPCCosineJ19 /= QVectorCountTPC
FourierCorrectionTPCCosineJ20 /= QVectorCountTPC


# In[ ]:





















# Calculation of Fourier correction terms
for entryNum in range (0, AutreeData.GetEntries()):
    if (entryNum % 5000 == 0):
        print("Data Third Pass (Fourier Correction Term Calculation)", entryNum)

    AutreeData.GetEntry(entryNum)

    px = AutreeData.Px
    py = AutreeData.Py
    pz = AutreeData.Pz
    q = AutreeData.Charge
    tofBeta = AutreeData.tofBeta
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
    
    Multiplicity = len(px)
    
    ReactionPlaneNumeratorInnerEPDOneEvent = 0
    ReactionPlaneDenominatorInnerEPDOneEvent = 0
    ReactionPlaneNumeratorOuterEPDOneEvent = 0
    ReactionPlaneDenominatorOuterEPDOneEvent = 0
    ReactionPlaneNumeratorTPCOneEvent = 0
    ReactionPlaneDenominatorTPCOneEvent = 0

    FourierCorrectionTermInnerEPD = 0
    FourierCorrectionTermOuterEPD = 0
    FourierCorrectionTermTPC = 0
    
    GoodTracksCounterInnerEPD = 0
    GoodTracksCounterOuterePD = 0
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
            ReactionPlaneNumeratorTPCOneEvent += pt*sin(nPsi*phi)
            ReactionPlaneDenominatorTPCOneEvent += pt*cos(nPsi*phi)
            
#         elif ((eta > TPCLowerLimit) and (eta < yCMShift)):
#             ReactionPlaneNumeratorTPCOneEvent -= pt*sin(nPsi*phi)
#             ReactionPlaneDenominatorTPCOneEvent -= pt*cos(nPsi*phi)
            
    for index in range(len(EPDID)):
        if(EPDID[index] > 0):
            continue
            
        TileVector = ROOT.EPDKinematics(EPDID[index], vx, vy, vz)
        
        phi = TileVector.EPDPhi()
        
        if(EPDnMIP[index] < 0.3):
            EPDnMIP[index] = 0
            
        if(EPDnMIP[index] > 2.0):
            EPDnMIP[index] = 2.0
       
        if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
            ReactionPlaneNumeratorInnerEPDOneEvent -= EPDnMIP[index]*sin(nPsi*phi)
            ReactionPlaneDenominatorInnerEPDOneEvent -= EPDnMIP[index]*cos(nPsi*phi)
            
        if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
            ReactionPlaneNumeratorOuterEPDOneEvent -= EPDnMIP[index]*sin(nPsi*phi)
            ReactionPlaneDenominatorOuterEPDOneEvent -= EPDnMIP[index]*cos(nPsi*phi)
    
    PsiInnerEPD = (1/nPsi)*atan2((ReactionPlaneNumeratorInnerEPDOneEvent - AverageQNumeratorInnerEPD), (ReactionPlaneDenominatorInnerEPDOneEvent - AverageQDenominatorInnerEPD))
    PsiOuterEPD = (1/nPsi)*atan2((ReactionPlaneNumeratorOuterEPDOneEvent - AverageQNumeratorOuterEPD), (ReactionPlaneDenominatorOuterEPDOneEvent - AverageQDenominatorOuterEPD))
    PsiTPC = (1/nPsi)*atan2((ReactionPlaneNumeratorTPCOneEvent - AverageQNumeratorTPC), (ReactionPlaneDenominatorTPCOneEvent - AverageQDenominatorTPC))
    
    FourierCorrectionTermTPC += (2/(1*nPsi))*((FourierCorrectionTPCSineJ1*cos(1*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ1*sin(1*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(2*nPsi))*((FourierCorrectionTPCSineJ2*cos(2*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ2*sin(2*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(3*nPsi))*((FourierCorrectionTPCSineJ3*cos(3*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ3*sin(3*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(4*nPsi))*((FourierCorrectionTPCSineJ4*cos(4*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ4*sin(4*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(5*nPsi))*((FourierCorrectionTPCSineJ5*cos(5*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ5*sin(5*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(6*nPsi))*((FourierCorrectionTPCSineJ6*cos(6*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ6*sin(6*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(7*nPsi))*((FourierCorrectionTPCSineJ7*cos(7*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ7*sin(7*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(8*nPsi))*((FourierCorrectionTPCSineJ8*cos(8*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ8*sin(8*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(9*nPsi))*((FourierCorrectionTPCSineJ9*cos(9*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ9*sin(9*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(10*nPsi))*((FourierCorrectionTPCSineJ10*cos(10*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ10*sin(10*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(11*nPsi))*((FourierCorrectionTPCSineJ11*cos(11*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ1*sin(11*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(12*nPsi))*((FourierCorrectionTPCSineJ12*cos(12*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ2*sin(12*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(13*nPsi))*((FourierCorrectionTPCSineJ13*cos(13*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ3*sin(13*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(14*nPsi))*((FourierCorrectionTPCSineJ14*cos(14*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ4*sin(14*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(15*nPsi))*((FourierCorrectionTPCSineJ15*cos(15*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ5*sin(15*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(16*nPsi))*((FourierCorrectionTPCSineJ16*cos(16*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ6*sin(16*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(17*nPsi))*((FourierCorrectionTPCSineJ17*cos(17*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ7*sin(17*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(18*nPsi))*((FourierCorrectionTPCSineJ18*cos(18*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ8*sin(18*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(19*nPsi))*((FourierCorrectionTPCSineJ19*cos(19*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ9*sin(19*nPsi*PsiTPC)))
    FourierCorrectionTermTPC += (2/(20*nPsi))*((FourierCorrectionTPCSineJ20*cos(20*nPsi*PsiTPC))+(FourierCorrectionTPCCosineJ10*sin(20*nPsi*PsiTPC)))
    
    HistoD41.Fill(PsiTPC + FourierCorrectionTermTPC)
    
    if(PsiOuterEPD != 0):
        FourierCorrectionTermOuterEPD += (2/(1*nPsi))*((FourierCorrectionOuterEPDSineJ1*cos(1*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ1*sin(1*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(2*nPsi))*((FourierCorrectionOuterEPDSineJ2*cos(2*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ2*sin(2*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(3*nPsi))*((FourierCorrectionOuterEPDSineJ3*cos(3*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ3*sin(3*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(4*nPsi))*((FourierCorrectionOuterEPDSineJ4*cos(4*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ4*sin(4*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(5*nPsi))*((FourierCorrectionOuterEPDSineJ5*cos(5*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ5*sin(5*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(6*nPsi))*((FourierCorrectionOuterEPDSineJ6*cos(6*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ6*sin(6*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(7*nPsi))*((FourierCorrectionOuterEPDSineJ7*cos(7*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ7*sin(7*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(8*nPsi))*((FourierCorrectionOuterEPDSineJ8*cos(8*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ8*sin(8*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(9*nPsi))*((FourierCorrectionOuterEPDSineJ9*cos(9*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ9*sin(9*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(10*nPsi))*((FourierCorrectionOuterEPDSineJ10*cos(10*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ10*sin(10*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(11*nPsi))*((FourierCorrectionOuterEPDSineJ11*cos(11*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ11*sin(11*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(12*nPsi))*((FourierCorrectionOuterEPDSineJ12*cos(12*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ12*sin(12*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(13*nPsi))*((FourierCorrectionOuterEPDSineJ13*cos(13*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ13*sin(13*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(14*nPsi))*((FourierCorrectionOuterEPDSineJ14*cos(14*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ14*sin(14*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(15*nPsi))*((FourierCorrectionOuterEPDSineJ15*cos(15*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ15*sin(15*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(16*nPsi))*((FourierCorrectionOuterEPDSineJ16*cos(16*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ16*sin(16*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(17*nPsi))*((FourierCorrectionOuterEPDSineJ17*cos(17*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ17*sin(17*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(18*nPsi))*((FourierCorrectionOuterEPDSineJ18*cos(18*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ18*sin(18*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(19*nPsi))*((FourierCorrectionOuterEPDSineJ19*cos(19*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ19*sin(19*nPsi*PsiOuterEPD)))
        FourierCorrectionTermOuterEPD += (2/(20*nPsi))*((FourierCorrectionOuterEPDSineJ20*cos(20*nPsi*PsiOuterEPD))+(FourierCorrectionOuterEPDCosineJ20*sin(20*nPsi*PsiOuterEPD)))
        
        HistoD38.Fill(PsiOuterEPD + FourierCorrectionTermOuterEPD)
        
    if(PsiInnerEPD == 0):
        continue
    
    FourierCorrectionTermInnerEPD += (2/(1*nPsi))*((FourierCorrectionInnerEPDSineJ1*cos(1*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ1*sin(1*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(2*nPsi))*((FourierCorrectionInnerEPDSineJ2*cos(2*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ2*sin(2*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(3*nPsi))*((FourierCorrectionInnerEPDSineJ3*cos(3*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ3*sin(3*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(4*nPsi))*((FourierCorrectionInnerEPDSineJ4*cos(4*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ4*sin(4*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(5*nPsi))*((FourierCorrectionInnerEPDSineJ5*cos(5*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ5*sin(5*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(6*nPsi))*((FourierCorrectionInnerEPDSineJ6*cos(6*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ6*sin(6*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(7*nPsi))*((FourierCorrectionInnerEPDSineJ7*cos(7*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ7*sin(7*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(8*nPsi))*((FourierCorrectionInnerEPDSineJ8*cos(8*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ8*sin(8*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(9*nPsi))*((FourierCorrectionInnerEPDSineJ9*cos(9*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ9*sin(9*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(10*nPsi))*((FourierCorrectionInnerEPDSineJ10*cos(10*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ10*sin(10*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(11*nPsi))*((FourierCorrectionInnerEPDSineJ11*cos(11*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ11*sin(11*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(12*nPsi))*((FourierCorrectionInnerEPDSineJ12*cos(12*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ12*sin(12*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(13*nPsi))*((FourierCorrectionInnerEPDSineJ13*cos(13*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ13*sin(13*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(14*nPsi))*((FourierCorrectionInnerEPDSineJ14*cos(14*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ14*sin(14*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(15*nPsi))*((FourierCorrectionInnerEPDSineJ15*cos(15*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ15*sin(15*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(16*nPsi))*((FourierCorrectionInnerEPDSineJ16*cos(16*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ16*sin(16*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(17*nPsi))*((FourierCorrectionInnerEPDSineJ17*cos(17*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ17*sin(17*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(18*nPsi))*((FourierCorrectionInnerEPDSineJ18*cos(18*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ18*sin(18*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(19*nPsi))*((FourierCorrectionInnerEPDSineJ19*cos(19*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ19*sin(19*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(20*nPsi))*((FourierCorrectionInnerEPDSineJ20*cos(20*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ20*sin(20*nPsi*PsiInnerEPD)))

    HistoD35.Fill(PsiInnerEPD + FourierCorrectionTermInnerEPD)

    if(PsiOuterEPD == 0):
        continue
    
    R11TopLeftTerm = cos(nV*((PsiInnerEPD + FourierCorrectionTermInnerEPD) - (PsiOuterEPD + FourierCorrectionTermOuterEPD)))
    R11TopRightTerm = cos(nV*((PsiInnerEPD  + FourierCorrectionTermInnerEPD) - (PsiTPC + FourierCorrectionTermTPC)))
    R11BottomTerm = cos(nV*((PsiOuterEPD + FourierCorrectionTermOuterEPD) - (PsiTPC + FourierCorrectionTermTPC)))
    
    Centrality = 15 - Centrality
    
    HistoD51.Fill(Centrality, R11TopLeftTerm)
    HistoD52.Fill(Centrality, R11TopRightTerm)
    HistoD53.Fill(Centrality, R11BottomTerm)

    for index in range(len(px)):
        pt = Pt(px[index], py[index])
    
        p = P(px[index], py[index], pz[index])
        
        eta = Eta(px[index], py[index], pz[index])
        
        phi = Phi(px[index], py[index])
            
        if(tofBeta[index] > 0):

            msquared = MSquared(px[index], py[index], pz[index], tofBeta[index])
            
            if((abs(NSigmaPr[index]) < 3) and (msquared > 0.45) and (msquared < 2.0) and (pt > ProtonLowerPt) and (pt < ProtonUpperPt)): 
                mass = ProtonMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                VnInnerEPD = V_n(nV, px[index], py[index], PsiInnerEPD)

                HistoD44.Fill(y - yCMShift, VnInnerEPD)

            if((abs(NSigmaKa[index]) < 3) and (msquared > 0.15) and (msquared < 0.45) and (pt > KaonLowerPt) and (pt < KaonUpperPt)): 
                mass = KaonMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)
                
                VnInnerEPD = V_n(nV, px[index], py[index], PsiInnerEPD)

                if(q[index] > 0):
                    HistoD47.Fill(y - yCMShift, VnInnerEPD)
                    
                elif(q[index] < 0):
                    HistoD47A.Fill(y - yCMShift, VnInnerEPD)
                
            if((abs(NSigmaPi[index]) < 3) and (msquared < 0.15) and (pt > PionLowerPt) and (pt < PionUpperPt)): 
                mass = PionMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)
                
                VnInnerEPD = V_n(nV, px[index], py[index], PsiInnerEPD)

                if(q[index] > 0):
                    HistoD50.Fill(y - yCMShift, VnInnerEPD)
                    
                elif(q[index] < 0):
                    HistoD50A.Fill(y - yCMShift, VnInnerEPD)


CentralityXLabels = ["0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60"]

R11 = 0
R11Error = 0

for index in range(1, HistoD51.GetNbinsX() + 1):
    TopLeftTerm = HistoD51.GetBinContent(index)
    TopRightTerm = HistoD52.GetBinContent(index)
    BottomTerm = HistoD53.GetBinContent(index)

    R11 = sqrt((TopLeftTerm * TopRightTerm)/BottomTerm)

    TopLeftTermError = HistoD51.GetBinError(index)
    TopRightTermError = HistoD52.GetBinError(index)
    BottomTermError = HistoD53.GetBinError(index)
    
    R11Error = R11*sqrt(pow((TopLeftTermError/TopLeftTerm),2) + pow((TopRightTermError/TopRightTerm),2) + pow((BottomTermError/BottomTerm),2))

    HistoD54.SetBinContent(index, R11)
    HistoD54.SetBinEntries(index, 1)
    HistoD54.SetBinError(index, R11Error)
    
    HistoD51.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])
    HistoD52.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])
    HistoD53.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])
    HistoD54.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])


# In[ ]:

















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
    
    Multiplicity = len(px)
    
    ReactionPlaneNumeratorInnerEPDOneEvent = 0
    ReactionPlaneDenominatorInnerEPDOneEvent = 0
    ReactionPlaneNumeratorOuterEPDOneEvent = 0
    ReactionPlaneDenominatorOuterEPDOneEvent = 0
    ReactionPlaneNumeratorTPCOneEvent = 0
    ReactionPlaneDenominatorTPCOneEvent = 0

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
            ReactionPlaneNumeratorTPCOneEvent += pt*sin(nPsi*phi)
            ReactionPlaneDenominatorTPCOneEvent += pt*cos(nPsi*phi)
            
#         elif ((eta > TPCLowerLimit) and (eta < yCMShift)):
#             ReactionPlaneNumeratorTPCOneEvent -= pt*sin(nPsi*phi)
#             ReactionPlaneDenominatorTPCOneEvent -= pt*cos(nPsi*phi)
            
    for index in range(len(EPDID)):
        if(EPDID[index] > 0):
            continue
        
        TileVector = ROOT.EPDKinematics(EPDID[index], vx, vy, vz)
        
        phi = TileVector.EPDPhi()
        
        if(EPDnMIP[index] < 0.3):
            EPDnMIP[index] = 0
            
        if(EPDnMIP[index] > 2.0):
            EPDnMIP[index] = 2.0

        if (TileVector.IsInnerEPD() and not(TileVector.IsOuterEPD())):
            ReactionPlaneNumeratorInnerEPDOneEvent -= EPDnMIP[index]*sin(nPsi*phi)
            ReactionPlaneDenominatorInnerEPDOneEvent -= EPDnMIP[index]*cos(nPsi*phi)
            
        if (TileVector.IsOuterEPD() and not(TileVector.IsInnerEPD())):
            ReactionPlaneNumeratorOuterEPDOneEvent -= EPDnMIP[index]*sin(nPsi*phi)
            ReactionPlaneDenominatorOuterEPDOneEvent -= EPDnMIP[index]*cos(nPsi*phi)
    
    PsiInnerEPD = (1/nPsi)*atan2((ReactionPlaneNumeratorInnerEPDOneEvent - AverageQNumeratorInnerEPD), (ReactionPlaneDenominatorInnerEPDOneEvent - AverageQDenominatorInnerEPD))
    
    if(PsiInnerEPD == 0):
        continue
    
    FourierCorrectionTermInnerEPD += (2/(1*nPsi))*((FourierCorrectionInnerEPDSineJ1*cos(1*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ1*sin(1*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(2*nPsi))*((FourierCorrectionInnerEPDSineJ2*cos(2*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ2*sin(2*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(3*nPsi))*((FourierCorrectionInnerEPDSineJ3*cos(3*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ3*sin(3*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(4*nPsi))*((FourierCorrectionInnerEPDSineJ4*cos(4*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ4*sin(4*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(5*nPsi))*((FourierCorrectionInnerEPDSineJ5*cos(5*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ5*sin(5*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(6*nPsi))*((FourierCorrectionInnerEPDSineJ6*cos(6*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ6*sin(6*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(7*nPsi))*((FourierCorrectionInnerEPDSineJ7*cos(7*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ7*sin(7*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(8*nPsi))*((FourierCorrectionInnerEPDSineJ8*cos(8*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ8*sin(8*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(9*nPsi))*((FourierCorrectionInnerEPDSineJ9*cos(9*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ9*sin(9*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(10*nPsi))*((FourierCorrectionInnerEPDSineJ10*cos(10*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ10*sin(10*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(11*nPsi))*((FourierCorrectionInnerEPDSineJ11*cos(11*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ11*sin(11*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(12*nPsi))*((FourierCorrectionInnerEPDSineJ12*cos(12*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ12*sin(12*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(13*nPsi))*((FourierCorrectionInnerEPDSineJ13*cos(13*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ13*sin(13*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(14*nPsi))*((FourierCorrectionInnerEPDSineJ14*cos(14*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ14*sin(14*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(15*nPsi))*((FourierCorrectionInnerEPDSineJ15*cos(15*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ15*sin(15*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(16*nPsi))*((FourierCorrectionInnerEPDSineJ16*cos(16*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ16*sin(16*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(17*nPsi))*((FourierCorrectionInnerEPDSineJ17*cos(17*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ17*sin(17*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(18*nPsi))*((FourierCorrectionInnerEPDSineJ18*cos(18*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ18*sin(18*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(19*nPsi))*((FourierCorrectionInnerEPDSineJ19*cos(19*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ19*sin(19*nPsi*PsiInnerEPD)))
    FourierCorrectionTermInnerEPD += (2/(20*nPsi))*((FourierCorrectionInnerEPDSineJ20*cos(20*nPsi*PsiInnerEPD))+(FourierCorrectionInnerEPDCosineJ20*sin(20*nPsi*PsiInnerEPD)))
    
    PsiInnerEPD += FourierCorrectionTermInnerEPD

    Centrality = 15 - Centrality
    
    ResolutionCorrectionFactor = HistoD54.GetBinContent(Centrality + 1)

    for index in range(len(px)):
        pt = Pt(px[index], py[index])
    
        p = P(px[index], py[index], pz[index])
        
        eta = Eta(px[index], py[index], pz[index])
        
        phi = Phi(px[index], py[index])
            
        if(tofBeta[index] > 0):

            msquared = MSquared(px[index], py[index], pz[index], tofBeta[index])
            
            if((abs(NSigmaPr[index]) < 3) and (msquared > 0.45) and (msquared < 2.0)): 
                mass = ProtonMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                VnInnerEPD = V_n(nV, px[index], py[index], PsiInnerEPD)
  
                if((pt > ProtonLowerPt) and (pt < ProtonUpperPt)):
                    HistoD44A.Fill(y - yCMShift, VnInnerEPD / ResolutionCorrectionFactor)
                    HistoD54A.Fill(Centrality, VnInnerEPD / ResolutionCorrectionFactor)
                    HistoD79.Fill(Centrality, pt, VnInnerEPD / ResolutionCorrectionFactor)
                    HistoD80.Fill(Centrality, y - yCMShift, VnInnerEPD / ResolutionCorrectionFactor)
                    
                    for i in range(1, HistoD54A.GetNbinsX() + 1):
                        HistoD54A.GetXaxis().SetBinLabel(i, CentralityXLabels[i - 1])
                    
            if((abs(NSigmaKa[index]) < 3) and (msquared > 0.15) and (msquared < 0.45)): 
                mass = KaonMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                VnInnerEPD = V_n(nV, px[index], py[index], PsiInnerEPD)

                if(q[index] > 0):
                        
                    if((pt > KaonLowerPt) and (pt < KaonUpperPt)):
                        HistoD47B.Fill(y - yCMShift, VnInnerEPD)
                        HistoD54B.Fill(Centrality, VnInnerEPD)
                        HistoD81.Fill(Centrality, pt, VnInnerEPD)
                        HistoD82.Fill(Centrality, y - yCMShift, VnInnerEPD)
                        
                    for i in range(1, HistoD54B.GetNbinsX() + 1):
                        HistoD54B.GetXaxis().SetBinLabel(i, CentralityXLabels[i - 1])
                        
                elif(q[index] < 0):
                    
                    if((pt > KaonLowerPt) and (pt < KaonUpperPt)):
                        HistoD47C.Fill(y - yCMShift, VnInnerEPD)
                        HistoD54C.Fill(Centrality, VnInnerEPD)
                        HistoD83.Fill(Centrality, pt, VnInnerEPD)
                        HistoD84.Fill(Centrality, y - yCMShift, VnInnerEPD)
                        
                    for i in range(1, HistoD54C.GetNbinsX() + 1):
                        HistoD54C.GetXaxis().SetBinLabel(i, CentralityXLabels[i - 1])
                
            if((abs(NSigmaPi[index]) < 3) and (msquared < 0.15)): 
                mass = PionMass

                energy = Energy(px[index], py[index], pz[index], mass)

                y = Y(px[index], py[index], pz[index], mass)

                VnInnerEPD = V_n(nV, px[index], py[index], PsiInnerEPD)
                
                if(q[index] > 0):
  
                    if((pt > PionLowerPt) and (pt < PionUpperPt)):
                        HistoD50B.Fill(y - yCMShift, VnInnerEPD / ResolutionCorrectionFactor) 
                        HistoD54D.Fill(Centrality, VnInnerEPD/ResolutionCorrectionFactor)
                        HistoD85.Fill(Centrality, pt, VnInnerEPD / ResolutionCorrectionFactor)
                        HistoD86.Fill(Centrality, y - yCMShift, VnInnerEPD / ResolutionCorrectionFactor)
                        
                    for i in range(1, HistoD54D.GetNbinsX() + 1):
                        HistoD54D.GetXaxis().SetBinLabel(i, CentralityXLabels[i - 1])

                elif(q[index] < 0):
                    
                    if((pt > PionLowerPt) and (pt < PionUpperPt)):
                        HistoD50C.Fill(y - yCMShift, VnInnerEPD / ResolutionCorrectionFactor)
                        HistoD54E.Fill(Centrality, VnInnerEPD/ResolutionCorrectionFactor)
                        HistoD87.Fill(Centrality, pt, VnInnerEPD / ResolutionCorrectionFactor)
                        HistoD88.Fill(Centrality, y - yCMShift, VnInnerEPD / ResolutionCorrectionFactor)
                        
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
HistoD95.SetXTitle("Pt")
HistoD95.SetYTitle("V" + str(nV) +"")
HistoD96 = HistoD81.ProfileY("DataV" + str(nV) +"VsPtForKaonsPlusCentrality10-40", 3, 8)
HistoD96.SetXTitle("Pt")
HistoD96.SetYTitle("V" + str(nV) +"")
HistoD97 = HistoD81.ProfileY("DataV" + str(nV) +"VsPtForKaonsPlusCentrality40-60", 9, 12)
HistoD97.SetXTitle("Pt")
HistoD97.SetYTitle("V" + str(nV) +"")
HistoD98 = HistoD82.ProfileY("DataV" + str(nV) +"VsYForKaonsPlusCentrality0-10", 1, 2)
HistoD98.SetXTitle("Y - Y_CM")
HistoD98.SetYTitle("V" + str(nV) +"")
HistoD99 = HistoD82.ProfileY("DataV" + str(nV) +"VsYForKaonsPlusCentrality10-40", 3, 8)
HistoD99.SetXTitle("Y - Y_CM")
HistoD99.SetYTitle("V" + str(nV) +"")
HistoD100 = HistoD82.ProfileY("DataV" + str(nV) +"VsYForKaonsPlusCentrality40-60", 9, 12)
HistoD100.SetXTitle("Y - Y_CM")
HistoD100.SetYTitle("V" + str(nV) +"")


HistoD101 = HistoD83.ProfileY("DataV" + str(nV) +"VsPtForKaonsMinusCentrality0-10", 1, 2)
HistoD101.SetXTitle("Pt")
HistoD101.SetYTitle("V" + str(nV) +"")
HistoD102 = HistoD83.ProfileY("DataV" + str(nV) +"VsPtForKaonsMinusCentrality10-40", 3, 8)
HistoD102.SetXTitle("Pt")
HistoD102.SetYTitle("V" + str(nV) +"")
HistoD103 = HistoD83.ProfileY("DataV" + str(nV) +"VsPtForKaonsMinusCentrality40-60", 9, 12)
HistoD103.SetXTitle("Pt")
HistoD103.SetYTitle("V" + str(nV) +"")
HistoD104 = HistoD84.ProfileY("DataV" + str(nV) +"VsYForKaonsMinusCentrality0-10", 1, 2)
HistoD104.SetXTitle("Y - Y_CM")
HistoD104.SetYTitle("V" + str(nV) +"")
HistoD105 = HistoD84.ProfileY("DataV" + str(nV) +"VsYForKaonsMinusCentrality10-40", 3, 8)
HistoD105.SetXTitle("Y - Y_CM")
HistoD105.SetYTitle("V" + str(nV) +"")
HistoD106 = HistoD84.ProfileY("DataV" + str(nV) +"VsYForKaonsMinusCentrality40-60", 9, 12)
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



# Change the histogram scope so that it doesn't close when the last file closes
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
HistoD28.SetDirectory(0)
HistoD29.SetDirectory(0)
HistoD30.SetDirectory(0)
HistoD31.SetDirectory(0)
HistoD32.SetDirectory(0)
HistoD32A.SetDirectory(0)
HistoD32B.SetDirectory(0)
HistoD33.SetDirectory(0)
HistoD34.SetDirectory(0)
HistoD35.SetDirectory(0)
HistoD36.SetDirectory(0)
HistoD37.SetDirectory(0)
HistoD38.SetDirectory(0)
HistoD39.SetDirectory(0)
HistoD40.SetDirectory(0)
HistoD41.SetDirectory(0)
HistoD42.SetDirectory(0)
HistoD43.SetDirectory(0)
HistoD44.SetDirectory(0)
HistoD44A.SetDirectory(0)
HistoD45.SetDirectory(0)
HistoD45A.SetDirectory(0)
HistoD46.SetDirectory(0)
HistoD46A.SetDirectory(0)
HistoD47.SetDirectory(0)
HistoD47A.SetDirectory(0)
HistoD47B.SetDirectory(0)
HistoD47C.SetDirectory(0)
HistoD48.SetDirectory(0)
HistoD48A.SetDirectory(0)
HistoD49.SetDirectory(0)
HistoD49A.SetDirectory(0)
HistoD50.SetDirectory(0)
HistoD50A.SetDirectory(0)
HistoD50B.SetDirectory(0)
HistoD50C.SetDirectory(0)
HistoD51.SetDirectory(0)
HistoD52.SetDirectory(0)
HistoD53.SetDirectory(0)
HistoD54.SetDirectory(0)
HistoD54A.SetDirectory(0)
HistoD54B.SetDirectory(0)
HistoD54C.SetDirectory(0)
HistoD54D.SetDirectory(0)
HistoD54E.SetDirectory(0)
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
Histograms.append(HistoD28)
Histograms.append(HistoD29)
Histograms.append(HistoD30)
Histograms.append(HistoD31)
Histograms.append(HistoD32)
Histograms.append(HistoD32A)
Histograms.append(HistoD32B)
Histograms.append(HistoD33)
Histograms.append(HistoD34)
Histograms.append(HistoD35)
Histograms.append(HistoD36)
Histograms.append(HistoD37)
Histograms.append(HistoD38)
Histograms.append(HistoD39)
Histograms.append(HistoD40)
Histograms.append(HistoD41)
Histograms.append(HistoD42)
Histograms.append(HistoD43)
Histograms.append(HistoD44)
Histograms.append(HistoD44A)
Histograms.append(HistoD45)
Histograms.append(HistoD45A)
Histograms.append(HistoD46)
Histograms.append(HistoD46A)
Histograms.append(HistoD47)
Histograms.append(HistoD47A)
Histograms.append(HistoD47B)
Histograms.append(HistoD47C)
Histograms.append(HistoD48)
Histograms.append(HistoD48A)
Histograms.append(HistoD49)
Histograms.append(HistoD49A)
Histograms.append(HistoD50)
Histograms.append(HistoD50A)
Histograms.append(HistoD50B)
Histograms.append(HistoD50C)
Histograms.append(HistoD51)
Histograms.append(HistoD52)
Histograms.append(HistoD53)
Histograms.append(HistoD54)
Histograms.append(HistoD54A)
Histograms.append(HistoD54B)
Histograms.append(HistoD54C)
Histograms.append(HistoD54D)
Histograms.append(HistoD54E)
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


# In[ ]:


# # Monte Carlo histograms
# HistoMC1 = ROOT.TH2F("MonteCarloPtVsEta", "Pt vs Y (Monte Carlo); Y; Pt (GeV)", 500, -1.8, 1.8, 500, 0, 2)
# HistoMC1.Sumw2()

# HistoMC2 = ROOT.TH1F("MonteCarloYProton", "Y for Protons (Monte Carlo); Y; Events", 500, -1.8, 1.8)
# HistoMC2.Sumw2()

# HistoMC3 = ROOT.TH1F("MonteCarloYKaon", "Y for Kaons (Monte Carlo); Y; Events", 500, -1.8, 1.8)
# HistoMC3.Sumw2()

# HistoMC4 = ROOT.TH1F("MonteCarloYPion", "Y for Pions (Monte Carlo); Y; Events", 500, -1.8, 1.8)
# HistoMC4.Sumw2()

# HistoMC5 = ROOT.TH1F("MonteCarloPtProton", "Pt for Protons (Monte Carlo); Pt; Events", 500, 0, 2)
# HistoMC5.Sumw2()

# HistoMC6 = ROOT.TH1F("MonteCarloPtKaon", "Pt for Kaons (Monte Carlo); Pt; Events", 500, 0, 2)
# HistoMC6.Sumw2()

# HistoMC7 = ROOT.TH1F("MonteCarloPtPion", "Pt for Pions (Monte Carlo); Pt; Events", 500, 0, 2)
# HistoMC7.Sumw2()

# HistoMC8 = ROOT.TH1F("MonteCarloImpactParameter", "Impact Parameter (Monte Carlo); b; Events", 500, 0, 15)
# HistoMC8.Sumw2()

# HistoMC8A = ROOT.TH1F("MonteCarloImpactParameterFlattened", "Impact Parameter Flattened (Monte Carlo); b^2; Events", 500, 0, 200)
# HistoMC8A.Sumw2()

# HistoMC9 = ROOT.TH2F("MonteCarloMultiplicityVsImpactParameter", "Multiplicity vs Impact Parameter (Monte Carlo); b; Multiplicity", 500, 0, 15, 1000, 300, 800)
# HistoMC9.Sumw2()

# HistoMC10 = ROOT.TH1F("MonteCarloPhi", "Phi (Monte Carlo); Phi; Events", 500, -3.5, 3.5)
# HistoMC10.Sumw2()

# HistoMC11 = ROOT.TH1F("MonteCarloReactionPlanePsi1Angle", "Reaction Plane Angle, Psi_1 (Monte Carlo); Angle; Events", 500, -3.5, 3.5)
# HistoMC11.Sumw2()

# HistoMC12 = ROOT.TH1F("MonteCarloReactionPlanePsi2Angle", "Reaction Plane Angle, Psi_2 (Monte Carlo); Angle; Events", 500, -3.5, 3.5)
# HistoMC12.Sumw2()

# HistoMC13 = ROOT.TH1F("MonteCarloReactionPlanePsi3Angle", "Reaction Plane Angle, Psi_3 (Monte Carlo); Angle; Events", 500, -3.5, 3.5)
# HistoMC13.Sumw2()

# HistoMC14 = ROOT.TProfile("MonteCarloV1VsYProtonNoPsi", "v1 (Psi_1 = 0) vs Y for Protons (Monte Carlo); Y; v1", 500, -1, 1)
# HistoMC14.Sumw2()

# HistoMC15 = ROOT.TProfile("MonteCarloV1VsYKaonPlusNoPsi", "v1 (Psi_1 = 0) vs Y for Kaon+ (Monte Carlo); Y; v1", 500, -1, 1)
# HistoMC15.Sumw2()

# HistoMC16 = ROOT.TProfile("MonteCarloV1VsYPionPlusNoPsi", "v1 (Psi_1 = 0) vs Y for Pion+ (Monte Carlo); Y; v1", 500, -1, 1)
# HistoMC16.Sumw2()

# HistoMC17 = ROOT.TProfile("MonteCarloV1VsYAllNoPsi", "v1 (Psi_1 = 0) vs Y for Everything (Monte Carlo); Y; v1", 500, -1, 1)
# HistoMC17.Sumw2()

# HistoMC18 = ROOT.TProfile("MonteCarloV1VsYProton", "v1 vs Y for Protons (Monte Carlo); Y; v1", 500, -1, 1)
# HistoMC18.Sumw2()

# HistoMC19 = ROOT.TProfile("MonteCarloV1VsYKaonPlus", "v1 vs Y for Kaon+ (Monte Carlo); Y; v1", 500, -1, 1)
# HistoMC19.Sumw2()

# HistoMC20 = ROOT.TProfile("MonteCarloV1VsYPionPlus", "v1 vs Y for Pion+ (Monte Carlo); Y; v1", 500, -1, 1)
# HistoMC20.Sumw2()

# HistoMC21 = ROOT.TProfile("MonteCarloV1VsYAll", "v1 vs Y for Everything (Monte Carlo); Y; v1", 500, -1, 1)
# HistoMC21.Sumw2()


# # Loop through every event; skip anything with a PID not equal to a p,K, or pi
# for entryNum in range (0, 5000):#JamMonteCarlo.GetEntries()):
#     if (entryNum % 5000 == 0):
#         print("Monte Carlo", entryNum)

#     JamMonteCarlo.GetEntry(entryNum)

#     px = JamMonteCarlo.px
#     py = JamMonteCarlo.py
#     pz = JamMonteCarlo.pz
#     pid = JamMonteCarlo.pid
#     b = JamMonteCarlo.b
#     mul = JamMonteCarlo.mul

#     ProtonID = 2212
#     KaonPlusID = 321
#     PionPlusID = 211
    
#     ProtonMass = 0.938
#     KaonMass = 0.494
#     PionMass = 0.140
    
#     ReactionPlaneNumerator = []
#     ReactionPlaneDenominator = []
#     ReactionPlane = []

#     NumberOfOrders = 3

#     for order in range(1, NumberOfOrders + 1):
#         ReactionPlaneNumerator.append(0)
#         ReactionPlaneDenominator.append(0)

#     # Loop through every track in the event
#     for index in range(len(px)):

#         pt = sqrt(pow(px[index], 2) + pow(py[index], 2))

#         p = sqrt(pow(px[index],2) + pow(py[index],2) + pow(pz[index],2))
        
#         eta = 0.5*log((p + pz[index])/(p - pz[index]))
        
#         phi = atan2(py[index], px[index])
        
#         if ((eta > 0) and (eta < 0.7)):
#             for order in range(1, NumberOfOrders + 1):
#                 ReactionPlaneNumerator[order - 1] += pt*sin(order*phi)
#                 ReactionPlaneDenominator[order - 1] += pt*cos(order*phi)

#         if (pid[index] == ProtonID):
#             if ((eta > 0) and (eta < 0.7)):
#                 for order in range(1, NumberOfOrders + 1):
#                     ReactionPlaneNumerator[order - 1] += pt*sin(order*phi)
#                     ReactionPlaneDenominator[order - 1] += pt*cos(order*phi)

#             mass = ProtonMass
            
#             energy = sqrt(pow(p,2) + pow(mass,2))
            
#             Y = atanh(pz[index]/energy)

#             HistoMC1.Fill(Y, pt)
            
#             HistoMC2.Fill(Y)
            
#             HistoMC5.Fill(pt)

#         elif ((pid[index] == KaonPlusID) or (pid[index] == -1 * KaonPlusID)):
#             if ((eta > 0) and (eta < 0.7)):
#                 for order in range(1, NumberOfOrders + 1):
#                     ReactionPlaneNumerator[order - 1] += pt*sin(order*phi)
#                     ReactionPlaneDenominator[order - 1] += pt*cos(order*phi)
        
#             mass = KaonMass
            
#             energy = sqrt(pow(p,2) + pow(mass,2))
            
#             Y = atanh(pz[index]/energy)

#             HistoMC1.Fill(Y, pt)
            
#             HistoMC3.Fill(Y)
            
#             HistoMC6.Fill(pt)

#         elif ((pid[index] == PionPlusID) or (pid[index] == -1 * PionPlusID)):
#             if ((eta > 0) and (eta < 0.7)):
#                 for order in range(1, NumberOfOrders + 1):
#                     ReactionPlaneNumerator[order - 1] += pt*sin(order*phi)
#                     ReactionPlaneDenominator[order - 1] += pt*cos(order*phi)
        
#             mass = PionMass
            
#             energy = sqrt(pow(p,2) + pow(mass,2))
            
#             Y = atanh(pz[index]/energy)

#             HistoMC1.Fill(Y, pt)
            
#             HistoMC4.Fill(Y)
            
#             HistoMC7.Fill(pt)
    
#     FlattenedImpactParameter = pow(b,2)
    
#     Centrality = FlattenedImpactParameter / 1.766

#     HistoMC8.Fill(b)
#     HistoMC8A.Fill(FlattenedImpactParameter)
#     HistoMC9.Fill(b, mul)
#     HistoMC10.Fill(phi)
    
#     # Completion of reaction plane calculation
#     for order in range(1, NumberOfOrders + 1):
#         ReactionPlane.append((1/order)*atan2(ReactionPlaneNumerator[order - 1], ReactionPlaneDenominator[order - 1]))

#     GoodTracksCounter = 0
    
#     for index in range(len(px)):
#         p = sqrt(pow(px[index],2) + pow(py[index],2) + pow(pz[index],2))
        
#         eta = 0.5*log((p + pz[index])/(p - pz[index]))
        
#         if ((eta > 0) and (eta < 0.7)):
#             GoodTracksCounter += 1
            
#     if((GoodTracksCounter < 1)):
#         continue
    
#     HistoMC11.Fill(ReactionPlane[0])
#     HistoMC12.Fill(ReactionPlane[1])
#     HistoMC13.Fill(ReactionPlane[2])

#     for index in range(len(px)):
            
#         p = sqrt(pow(px[index],2) + pow(py[index],2) + pow(pz[index],2))
        
#         phi = atan2(py[index], px[index])

#         if (pid[index] == ProtonID):

#             mass = ProtonMass
            
#             energy = sqrt(pow(p,2) + pow(mass,2))
            
#             Y = atanh(pz[index]/energy)

#             V1NoPsi = cos(1*(phi))
#             V1 = cos(1*(phi - ReactionPlane[0]))

#             HistoMC14.Fill(Y, V1NoPsi)
#             HistoMC17.Fill(Y, V1NoPsi)
#             HistoMC18.Fill(Y, V1)
#             HistoMC21.Fill(Y, V1)
            
#         elif ((pid[index] == KaonPlusID)):
            
#             mass = KaonMass
            
#             energy = sqrt(pow(p,2) + pow(mass,2))
            
#             Y = atanh(pz[index]/energy)
            
#             V1NoPsi = cos(1*(phi))
#             V1 = cos(1*(phi - ReactionPlane[0]))
            
#             HistoMC15.Fill(Y, V1NoPsi)
#             HistoMC17.Fill(Y, V1NoPsi)
#             HistoMC19.Fill(Y, V1)
#             HistoMC21.Fill(Y, V1)
            
#         elif ((pid[index] == PionPlusID)):

#             mass = PionMass
            
#             energy = sqrt(pow(p,2) + pow(mass,2))
            
#             Y = atanh(pz[index]/energy)
            
#             V1NoPsi = cos(1*(phi))
#             V1 = cos(1*(phi - ReactionPlane[0]))
            
#             HistoMC16.Fill(Y, V1NoPsi)
#             HistoMC17.Fill(Y, V1NoPsi)
#             HistoMC20.Fill(Y, V1)
#             HistoMC21.Fill(Y, V1)      
    
    
# HistoMC1.SetDirectory(0)
# HistoMC2.SetDirectory(0)
# HistoMC3.SetDirectory(0)
# HistoMC4.SetDirectory(0)
# HistoMC5.SetDirectory(0)
# HistoMC6.SetDirectory(0)
# HistoMC7.SetDirectory(0)
# HistoMC8.SetDirectory(0)
# HistoMC8A.SetDirectory(0)
# HistoMC9.SetDirectory(0)
# HistoMC10.SetDirectory(0)
# HistoMC11.SetDirectory(0)
# HistoMC12.SetDirectory(0)
# HistoMC13.SetDirectory(0)
# HistoMC14.SetDirectory(0)
# HistoMC15.SetDirectory(0)
# HistoMC16.SetDirectory(0)
# HistoMC17.SetDirectory(0)
# HistoMC18.SetDirectory(0)
# HistoMC19.SetDirectory(0)
# HistoMC20.SetDirectory(0)
# HistoMC21.SetDirectory(0)



# Histograms.append(HistoMC1)
# Histograms.append(HistoMC2)
# Histograms.append(HistoMC3)
# Histograms.append(HistoMC4)
# Histograms.append(HistoMC5)
# Histograms.append(HistoMC6)
# Histograms.append(HistoMC7)
# Histograms.append(HistoMC8)
# Histograms.append(HistoMC8A)
# Histograms.append(HistoMC9)
# Histograms.append(HistoMC10)
# Histograms.append(HistoMC11)
# Histograms.append(HistoMC12)
# Histograms.append(HistoMC13)
# Histograms.append(HistoMC14)
# Histograms.append(HistoMC15)
# Histograms.append(HistoMC16)
# Histograms.append(HistoMC17)
# Histograms.append(HistoMC18)
# Histograms.append(HistoMC19)
# Histograms.append(HistoMC20)
# Histograms.append(HistoMC21)


# In[ ]:


# Close the input Root files
Data.Close()
# MonteCarlo.Close()

# Open the output Root file
HistogramRootFile = ROOT.TFile.Open("HistogramTest.root", "RECREATE")
#HistogramRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/V1Histograms/Histogram" + sys.argv[2] + ".root", "RECREATE")
# Change the scope to be within the file
HistogramRootFile.cd()

# Write to the output Root file
for index in range(0,len(Histograms)):
    Histograms[index].Write()

# Close the output Root file
HistogramRootFile.Close()

print("Done")


# In[ ]:




