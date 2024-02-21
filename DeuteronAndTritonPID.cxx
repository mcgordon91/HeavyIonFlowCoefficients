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


// C++ headers
#include <iostream>
#include <vector>
#include <sys/resource.h>

// ROOT headers
#include "TROOT.h"
#include "TObject.h"
#include "TChain.h"
#include "TF1.h"
#include "TSystem.h"
#include "TKey.h"
#include "TStopwatch.h"

// EPD Util headers
#include "StRoot/StEpdUtil/StEpdGeom.h"

// Bichsel header
#include "StRoot/StBichsel/Bichsel.h"

// Configuration file reader
#include "StRoot/ConfigReader/ConfigReader.h"

// My Util Header
#include "FlowUtils.h"

// psn0770 cut
//#include "StRoot/StPileupUtil/StPileupUtil.h"

// Bichsel Function
Double_t bichselZ(Double_t *x,Double_t *par) 
{
  Double_t pove   = x[0];
  Double_t poverm = pove/par[0];
  return TMath::Exp(Bichsel::Instance()->GetMostProbableZ(TMath::Log10(poverm),par[1]));
}

Double_t bichselZcharge2(Double_t *x,Double_t *par) 
{
  Double_t pove   = 2.0 * x[0];
  Double_t poverm = pove/par[0];
  //return TMath::Exp(Bichsel::Instance()->GetMostProbableZ(TMath::Log10(poverm),par[1]));
  //Double_t D_ScaleCharge = 1.05;
  Double_t D_ScaleCharge = 1.0;

  //return D_ScaleCharge * D_ScaleCharge * 2.0 * 2.0 * TMath::Exp(Bichsel::Instance()->GetMostProbableZM(TMath::Log10(poverm),par[1]));
  return D_ScaleCharge * D_ScaleCharge * 2.0 * 2.0 * TMath::Exp(Bichsel::Instance()->GetMostProbableZM(TMath::Log10(poverm),1));
}

Float_t CalculateZ(Int_t charge, Float_t mass, Float_t p, Float_t dedx)
{
        Float_t sigma = -999;
        Float_t dedx_expected;
        dedx_expected = charge*charge*(TMath::Exp(Bichsel::Instance()->GetMostProbableZM(TMath::Log10(p*TMath::Abs(charge)/mass), 1))); 
        //if(charge==1) dedx_expected = charge*charge*Bichsel::Instance()->GetI70M(TMath::Log10(p*TMath::Abs(charge)/mass)); 
        //if(charge==2) dedx_expected = charge*charge*Bichsel::Instance()->GetI70M(TMath::Log10(p*TMath::Abs(charge)/mass), 2.321928); 
        sigma = TMath::Log(dedx/dedx_expected);
             
        return sigma;
}

//===========3p2gev================ from Chengdong
Float_t CalculatepZ(Float_t p, Float_t dedx)  //calculate z value of proton
{
  Float_t ParfpMean[4] = {4.59254,-0.866981,0.39528,-0.0233809};

  Float_t dedx_expected = ParfpMean[0]*TMath::Power(p, ParfpMean[1] + ParfpMean[2]*log(p) + ParfpMean[3]*log(p)*log(p));
  Float_t sigma = TMath::Log(dedx/dedx_expected);

  return sigma;
}
Float_t CalculatedZ(Float_t p, Float_t dedx) //calculate z value of deuteron
{
  Float_t ParfdMean[4] = {10.4424,-1.42789,0.273101,0.073392};

  Float_t dedx_expected = ParfdMean[0]*TMath::Power(p, ParfdMean[1] + ParfdMean[2]*log(p) + ParfdMean[3]*log(p)*log(p));
  Float_t sigma = TMath::Log(dedx/dedx_expected);

  return sigma;
}
Float_t CalculatetZ(Float_t p, Float_t dedx) //calculate z value of triton
{
  Float_t ParftMean[4] = {19.873,-1.5669,-0.0366403,0.192115};

  Float_t dedx_expected = ParftMean[0]*TMath::Power(p, ParftMean[1] + ParftMean[2]*log(p) + ParftMean[3]*log(p)*log(p));
  Float_t sigma = TMath::Log(dedx/dedx_expected);

  return sigma;
}
Float_t Calculate3HeZ(Float_t p, Float_t dedx) //calculate z value of He3
{
  Float_t ParfHe3Mean[4] = {29.211,-0.988318,0.17178,0.110356};

  Float_t dedx_expected = ParfHe3Mean[0]*TMath::Power(p, ParfHe3Mean[1] + ParfHe3Mean[2]*log(p) + ParfHe3Mean[3]*log(p)*log(p));
  Float_t sigma = TMath::Log(dedx/dedx_expected);

  return sigma;
}
Float_t Calculate4HeZ(Float_t p, Float_t dedx) //calculate z value of He4
{
  Float_t ParfHe4Mean[4] = {39.1887,-1.01737,-0.0505702,0.19047};

  Float_t dedx_expected = ParfHe4Mean[0]*TMath::Power(p, ParfHe4Mean[1] + ParfHe4Mean[2]*log(p) + ParfHe4Mean[3]*log(p)*log(p));
  Float_t sigma = TMath::Log(dedx/dedx_expected);

  return sigma;
}

 //Cent16toCent9
int Cent16toCent9(int centb_16) {

   int centb = -1; 
   if (centb_16 > 15 || centb_16 < 0) return centb;

   if (centb_16 == 0  || centb_16 == 1 ) centb = 0;
   if (centb_16 == 2  || centb_16 == 3 ) centb = 1;
   if (centb_16 == 4  || centb_16 == 5 ) centb = 2;
   if (centb_16 == 6  || centb_16 == 7 ) centb = 3;
   if (centb_16 == 8  || centb_16 == 9 ) centb = 4;
   if (centb_16 == 10 || centb_16 == 11) centb = 5;
   if (centb_16 == 12 || centb_16 == 13) centb = 6;
   if (centb_16 == 14)                   centb = 7;
   if (centb_16 == 15)                   centb = 8;
 
   return centb;
}



//=========================================================
//          SOME CONTROLS
//=========================================================
const Int_t CENT_BINS  = 16;             // Number of centrality bins to show (max 16)  LEAVE AT 16 FOR NOW, BEST FOR RESOLUTION STUFF
const Int_t FIRST_CENT = 16 - CENT_BINS;            // Starting point for centrality dependent plots

const Double_t D_M0_PI = 0.139571;   //Rest masses
const Double_t D_M0_KA = 0.493677;
const Double_t D_M0_PR = 0.938272;
const Double_t D_M0_DE = 1.875613;   // Deuteron
//const Double_t D_M0_TR = 2.808921;   // Triton
const Double_t D_M0_TR = 2.80892;   // Triton
const Double_t D_M0_HE3 = 2.80932;   // Helium-3 // psn0770 number
//const Double_t D_M0_HE3 = 2.809414;   // Helium-3
const Double_t D_M0_HE4 = 3.727379;   // Alpha

const Double_t PI = TMath::Pi();

Int_t RUN_ITERATION = 0;
// 0 = No correction info yet; save raw (Xn,Yn) distributions
// 1 = Correction file found, but only <Xn> and <Yn> for re-centering.
//     Also save <sin> <cos> at this step for shifting in the next step.
// 2 = Correction file found, and <sin> <cos> values found so that shifting can be performed.
//=========================================================
//          
//=========================================================

int main(int argc, char *argv[])
{
  TStopwatch* stopWatch = new TStopwatch();
  stopWatch->Start();

  std::cout << "Initializing..." << std::endl;

  TString inFile = argv[1];
  TString jobID  = argv[2];
  std::string configFileName = argv[3];
  TString correctionFileName = argv[4];
  TString resolutionFileName = argv[5];

  if (gSystem->AccessPathName(inFile)) { std::cout << "Error reading input file!" << std::endl; return 1;}

  //=========================================================
  //          Set up various files
  //=========================================================
  ConfigReader configs;
  configs.read(configFileName);
  if (configs.errorFound()) { std::cout << "There was an error reading the configurations! Aborting analysis!" << std::endl; return 1; }
  configs.printAll();

  const Double_t ORDER_N = configs.order_n;   // Order of anisotropic flow (v_n)
  const Double_t ORDER_M = configs.order_m;   // Order of event plane angle (psi_m)
  const Double_t Y_MID   = configs.y_mid;     // Mid rapidity for the current energy
  const Double_t Y_BEAM  = configs.y_beam;    // Beam rapidity for the current energy
  TString ORDER_N_STR;
  TString ORDER_M_STR;
  ORDER_N_STR.Form("%.0f", ORDER_N);
  ORDER_M_STR.Form("%.0f", ORDER_M);
  const Double_t PSI_BOUNDS = TMath::Pi()/ORDER_M + 1;  // Boundaries for many histograms
  const Double_t Q_BOUNDS = 100;
  const Bool_t ODD_PLANE = ((int)ORDER_M % 2 == 1) ? true : false;

  //=== INITIALIZE TTREE
  Int_t N_track = 0;  // Max number of tracks in an event. Depends on energy and centrality definition!
  if      (configs.sqrt_s_NN == 3.0)  { N_track = 195;  }
  else if (configs.sqrt_s_NN == 3.2) { N_track = 287;  }
  else if (configs.sqrt_s_NN == 3.5)  { N_track = 325;  }
  else if (configs.sqrt_s_NN == 3.9)  { N_track = 287;  }  // UPDATE THIS WHEN CENTRALITY IS OFFICIAL!
  else if (configs.sqrt_s_NN == 4.49) { N_track = 195;  }  // UPDATE THIS WHEN CENTRALITY IS OFFICIAL!
  else if (configs.sqrt_s_NN == 7.2)  { N_track = 240;  }
  else if (configs.sqrt_s_NN == 7.7 && configs.fixed_target )  { N_track = 450;  }  // UPDATE THIS WHEN CENTRALITY IS OFFICIAL!
  else if (configs.sqrt_s_NN == 7.7 && !configs.fixed_target )  { N_track = 500;  }  // UPDATE THIS WHEN CENTRALITY IS OFFICIAL!
  //else if (configs.sqrt_s_NN == 14.5) { N_track = 2048; } // UPDATE THIS WHEN THE CENTRALITY IS OFFICIAL
  else if (configs.sqrt_s_NN == 19.6) { N_track = 2048; } // UPDATE THIS WHEN THE CENTRALITY IS OFFICIAL
  else
    {
      std::cout << "Unknown energy! N_track is not set!" << std::endl;
      return 1;
    }

  Int_t i_runID;
  Int_t i_eventID;
  Float_t f_bField;
  Float_t f_xvtx;
  Float_t f_yvtx;
  Float_t f_zvtx;
  UShort_t i_centrality;
  UShort_t i_trackNumber;
  Short_t charge[N_track];
  Float_t Px[N_track];
  Float_t Py[N_track];
  Float_t Pz[N_track];
  Float_t DCA[N_track];
  Float_t nSigmaPi[N_track];
  Float_t nSigmaKa[N_track];
  Float_t nSigmaPr[N_track];
  Float_t tofBeta[N_track];
  Float_t EtofBeta[N_track];
  Int_t nHits[N_track];
  Int_t nHitsFit[N_track];
  Int_t nHitsPoss[N_track];
  Int_t nHitsDedx[N_track];
  Float_t dEdx[N_track];
  UShort_t i_nEPDhits;
  Short_t EPDids[744];
  Float_t EPDnMip[744];


  TFile *inputFile = TFile::Open(inFile);
  if (!inputFile) { std::cout << "Input file could not be opened properly!" << std::endl; return 1; }

  TTree *tree = (TTree*)inputFile->Get("Autree");  
  tree->SetBranchAddress("runId", &i_runID);
  tree->SetBranchAddress("eventId",&i_eventID);
  tree->SetBranchAddress("bField",&f_bField);
  tree->SetBranchAddress("Vx",&f_xvtx);
  tree->SetBranchAddress("Vy",&f_yvtx);
  tree->SetBranchAddress("Vz",&f_zvtx);
  tree->SetBranchAddress("centrality",&i_centrality);
  tree->SetBranchAddress("tracknumber",&i_trackNumber);
  tree->SetBranchAddress("Charge",&charge);
  tree->SetBranchAddress("Px",&Px);
  tree->SetBranchAddress("Py",&Py);
  tree->SetBranchAddress("Pz",&Pz);
  tree->SetBranchAddress("DCA",&DCA);
  tree->SetBranchAddress("nSigmaPi",&nSigmaPi);
  tree->SetBranchAddress("nSigmaKa",&nSigmaKa);
  tree->SetBranchAddress("nSigmaPr",&nSigmaPr);
  tree->SetBranchAddress("tofBeta",&tofBeta);
  TBranch *branchEtof = tree->GetBranch("EtofBeta"); // Get the branch
  if (branchEtof) {
      std::cout << "The branchEtof exists." << std::endl;
      tree->SetBranchAddress("EtofBeta",&EtofBeta);
  } else {
      std::cout << "The branchEtof does not exist." << std::endl;
      branchEtof = nullptr; // Explicitly set the pointer to null
      for(int i = 0; i < N_track; i++) {
          EtofBeta[i] = -999.0; // Set element to -999
      }
  }

  tree->SetBranchAddress("dEdx",&dEdx);
  tree->SetBranchAddress("nHits",&nHits);
  tree->SetBranchAddress("nHitsFit",&nHitsFit);
  tree->SetBranchAddress("nHitsPoss",&nHitsPoss);
  tree->SetBranchAddress("nHitsDedx",&nHitsDedx);
  tree->SetBranchAddress("nEPDhits",&i_nEPDhits);
  tree->SetBranchAddress("EPDid",&EPDids);
  tree->SetBranchAddress("EPDnMip",&EPDnMip);
  //=== END TTREE SETUP


  // INPUT FILE FOR CORRECTION INFORMATION
  TFile *correctionInputFile = TFile::Open(correctionFileName, "READ");
  if (!correctionInputFile)
    {
      RUN_ITERATION = 0;
      std::cout << "No correction file found." << std::endl
		<< "Re-centering and shifting will not be performed." << std::endl;
    }
  else
    {
      TKey *key;
      TIter next(correctionInputFile->GetListOfKeys());
      TProfile *profile;

      while( (key = (TKey*)next()) )
	{
	  TClass *cl = gROOT->GetClass(key->GetClassName());
	  
	  if (cl->InheritsFrom("TProfile"))
	    {
	      profile = (TProfile*)key->ReadObj();
	      if (profile->GetEntries() == 0)
		{
		  std::cout << "TProfiles are empty!" << std::endl
			    << "Re-centering will be performed and TProfiles will be filled." << std::endl;
		  RUN_ITERATION = 1;
		  break;
		}
	      else if (profile->GetEntries() != 0)
		{
		  std::cout << "Non-empty TProfiles found!" << std::endl
			    << "Re-centering and event plane shifting will be performed." << std::endl;
		  RUN_ITERATION = 2;
		  break;
		}
	    }
	}
    }
  ////

  // INPUT FILE FOR EVENT PLANE RESOLUTION INFORMATION
  Bool_t resolutionsFound = false;
  TFile *resolutionInputFile;
  if (RUN_ITERATION == 2) 
    { 
      resolutionInputFile = TFile::Open(resolutionFileName, "READ"); 
      if (!resolutionInputFile) { std::cout << "No resolution file was found!" << std::endl; }
      else 
	{ 
	  resolutionsFound = true;
	  std::cout << "Resolution file found!" << std::endl; 
	}
    }
  ////

  // INPUT FILE FOR TPC EFFICIENCY CORRECTIONS
  TString pikpEfficiencyFileName;
  TString protonEfficiencyFileName;
  TString pikEfficiencyFileName = "pikp_efficiency.root";
  if (configs.sqrt_s_NN != 3.0)
    pikEfficiencyFileName = "eff_tpc_pr_3p2GeV.root";
  //if (setup.getRunIteration() == 2 && configs.sqrt_s_NN == 3.0)
  //  {
  //    pikpEfficiencyFileName = "pikp_efficiency.root";
  //    setup.setTPCEfficiencyFile(pikpEfficiencyFileName);
  //  }
  //else if (setup.getRunIteration() == 2 && configs.sqrt_s_NN != 3.0)
  //  {
  //    protonEfficiencyFileName = "eff_tpc_pr_3p2GeV.root";
  //    setup.setProtonEfficiencyFile(protonEfficiencyFileName);
  //  }
  ////


  // INPUT FILE FOR TOF EFFICIENCY CORRECTIONS
  TString tofEfficiencyFileName = "tof_efficiency.root";
  if (configs.sqrt_s_NN == 3.2)
    tofEfficiencyFileName = "tof_efficiency_3p2GeV.root";
  else if (configs.sqrt_s_NN == 3.5)
    tofEfficiencyFileName = "tof_efficiency_3p5GeV.root";
  else if (configs.sqrt_s_NN == 3.9)
    tofEfficiencyFileName = "tof_efficiency_3p9GeV.root";
  else if (configs.sqrt_s_NN == 4.5)
    tofEfficiencyFileName = "tof_efficiency_4p5GeV.root";

  //if (setup.getRunIteration() == 2)
  //  setup.setTOFEfficiencyFile(tofEfficiencyFileName);
  //else
  //  std::cout << "This energy has no TOF efficiency corrections!" << std::endl;
  ////
  //std::cout << "test 0" << std::endl;
  // INPUT FILE FOR EPD PileUp cut
  //TString epdPileupFileName = "EPDPileUpCutsNch.root";
  // INPUT FILE FOR TPC EFFICIENCY CORRECTIONS
  TString pdtEfficiencyFileName = "pdt_efficiency.root";
  TString he3he4EfficiencyFileName = "he3he4_efficiency.root";
  TString RefMultPrimGlauberFileName = "RefMultPrimGlauberFit.root";
  //TFile *epdPileupFile;
  TFile *pdtEfficiencyFile;
  TFile *pikEfficiencyFile;
  TFile *he3he4EfficiencyFile;
  TFile *fcent;
  Bool_t efficienciesFound = false;
  TH2D *h2_tracking_pp;//=nullptr;
  TH2D *h2_tracking_pm;//=nullptr;
  TH2D *h2_tracking_kp;//=nullptr;
  TH2D *h2_tracking_km;//=nullptr;
  TH2D *h2_tracking_pr;//=nullptr;
  TH2D *h2_tracking_de;//=nullptr;
  TH2D *h2_tracking_tr;//=nullptr;
  TH1F *m_hreweight;
  //TH2D *h2_tracking_de;
  TH2D *h2_tracking_he3;
  TH2D *h2_tracking_he4;
  TH1D *tpc_de;
  TH1D *tpc_tr;
  TH1D *tpc_he3;
  TH1D *tpc_he4;

  /// tof m2 cut
  TH1D* tof_d;
  TH1D* tof_t;
  //TH1D* tof_he3;
  //TH1D* tof_he4;

  /// tof matching
  TH2D* tofmatch;


  // StPileupUtil cut
  //TH1F* m_hpucuts_default ;
  //std::cout << "test 1" << std::endl;
  if (RUN_ITERATION == 2)
    {
      // StPileupUtil cut
      //epdPileupFile = TFile::Open(epdPileupFileName, "READ");
      //if (epdPileupFile->IsOpen() && !epdPileupFile->IsZombie() && epdPileupFile->GetListOfKeys()->GetEntries() > 0) {
      //    // The file is not empty
      //  m_hpucuts_default = (TH1F*)((TH1F*)epdPileupFile->Get("hpucuts_default"))->Clone("m_hpucuts_default");  m_hpucuts_default->SetDirectory(0);
      //}
      //else {
      //  
      //    std::cout << "StPileupUtil File is empty!" << std::endl; 
      //    // The file is empty or there was an error opening it
      //}
      pdtEfficiencyFile = TFile::Open(pdtEfficiencyFileName, "READ");
      pikEfficiencyFile = TFile::Open(pikEfficiencyFileName, "READ");
      he3he4EfficiencyFile = TFile::Open(he3he4EfficiencyFileName, "READ");
      fcent = TFile::Open(RefMultPrimGlauberFileName,"READ");
      //if (!pdtEfficiencyFile || !pikEfficiencyFile) { std::cout << "One or both efficiency files missing! All efficiencies will default to 1!" << std::endl; }
      if (!pdtEfficiencyFile || !pikEfficiencyFile || !he3he4EfficiencyFile || !fcent) { std::cout << "One or both efficiency files missing! All efficiencies will default to 1!" << std::endl; }
      if (!pdtEfficiencyFile || !pikEfficiencyFile || !he3he4EfficiencyFile ) { std::cout << "One or both efficiency files missing! All efficiencies will default to 1!" << std::endl; }
      if (!pdtEfficiencyFile || !pikEfficiencyFile ) { std::cout << "One or both efficiency files missing! All efficiencies will default to 1!" << std::endl; }
      else 
	{ 
	  efficienciesFound = true;
	  //std::cout << "TPC pik and pdt efficiency files were found!" << std::endl; 
	  std::cout << "TPC pik, pdt, he3, he4, Glauber efficiency files were found!" << std::endl; 

	  h2_tracking_pp = (TH2D*)pikEfficiencyFile->Get("h2_ratio_pp");
	  h2_tracking_pm = (TH2D*)pikEfficiencyFile->Get("h2_ratio_pm");
	  h2_tracking_kp = (TH2D*)pikEfficiencyFile->Get("h2_ratio_kp");
	  h2_tracking_km = (TH2D*)pikEfficiencyFile->Get("h2_ratio_km");
	  h2_tracking_pr = (TH2D*)pikEfficiencyFile->Get("h2_ratio_pr");

	  //h2_tracking_pr = (TH2D*)pdtEfficiencyFile->Get("tracking_p");
	  //h2_tracking_de = (TH2D*)pdtEfficiencyFile->Get("tracking_d");
	  //h2_tracking_tr = (TH2D*)pdtEfficiencyFile->Get("tracking_t");
	  //h2_tracking_pr = (TH2D*)pdtEfficiencyFile->Get("h2_ratio_pr");
	  h2_tracking_de = (TH2D*)pdtEfficiencyFile->Get("h2_ratio_de");
	  h2_tracking_tr = (TH2D*)pdtEfficiencyFile->Get("h2_ratio_tr");

	  m_hreweight = (TH1F*)((TH1F*)fcent->Get("Ratioglaubertodata"))->Clone("m_hreweight"); m_hreweight->SetDirectory(0);
	  h2_tracking_de = (TH2D*)he3he4EfficiencyFile->Get("tracking_d");
	  h2_tracking_he3 = (TH2D*)he3he4EfficiencyFile->Get("tracking_he3");
	  h2_tracking_he4 = (TH2D*)he3he4EfficiencyFile->Get("tracking_he4");

	  tpc_de = (TH1D*)he3he4EfficiencyFile->Get("tpc_d");
	  tpc_tr = (TH1D*)he3he4EfficiencyFile->Get("tpc_t");
	  tpc_he3 = (TH1D*)he3he4EfficiencyFile->Get("tpc_he3");
	  tpc_he4 = (TH1D*)he3he4EfficiencyFile->Get("tpc_he4");

          /// tof m2 cut
          tof_d = (TH1D*)he3he4EfficiencyFile->Get("tof_d");
          tof_t = (TH1D*)he3he4EfficiencyFile->Get("tof_t");
          //tof_he3 = (TH1D*)he3he4EfficiencyFile->Get("tof_he3");
          //tof_he4 = (TH1D*)he3he4EfficiencyFile->Get("tof_he4");

          /// tof matching
          tofmatch = (TH2D*)he3he4EfficiencyFile->Get("tofmatch");

          if(!(h2_tracking_pp && h2_tracking_pm && h2_tracking_kp && h2_tracking_km 
	    && h2_tracking_pr && h2_tracking_de && h2_tracking_tr
	    && m_hreweight && h2_tracking_he3 && h2_tracking_he4
	    && tpc_he3 && tpc_he4)) std::cout << "Warning: One or both efficiency histograms missing!" << std::endl;
	}
    }
    Float_t de_eff(-1.);
    Float_t tr_eff(-1.);
    Float_t he3_eff(-1.);
    Float_t he4_eff(-1.);
    //Float_t he3_eff(1.);
    Float_t mCentWeight = -1.0;

    //he4_eff = he4_eff*(Float_t)h2_tracking_he4->GetBinContent(h2_tracking_he4->FindBin(-mRapidity_he4, 2*mPt));
    //he4_eff = he4_eff*(Float_t)tpc_he4->GetBinContent(tpc_he4->FindBin(2*mP));
    //Float_t he4_eff(1.);
  ////

  // OUTPUT FILE FOR CORRECTION INFORMATION
  TString correctionOutputName = "correctionInfo_OUTPUT_"+jobID+".root";
  TFile *correctionOutputFile;
  if (RUN_ITERATION == 0 || RUN_ITERATION == 1) { correctionOutputFile = new TFile(correctionOutputName, "RECREATE"); }
  ////

  // MAIN OUTPUT FILE
  TString outFile = jobID+".picoDst.result.root";
  TFile *outputFile = new TFile(outFile,"RECREATE");
  outputFile->cd();
  ////
  //=========================================================
  //          END file setup
  //=========================================================

  //std::cout << "test 2" << std::endl;

  //=========================================================
  //          Bichsel Function Setup
  //=========================================================
  Double_t log2dx = 1.0;
  Double_t xStart = 0.01;
  Double_t xStop  = 3.0;
  Int_t npx = 10000;
  //                      Mass  log2(dx)
  Double_t params[2] = {  1.0,   log2dx  };

  params[0] = D_M0_DE;
  TF1 *bichselZ_de = new TF1(Form("BichselZ_de_log2dx_%i",(int)log2dx),bichselZ,xStart,xStop,2);
  if (!bichselZ_de) { std::cout << "De function error" << std::endl; return 1; }
  bichselZ_de->SetParameters(params); 
  bichselZ_de->SetNpx(npx);

  params[0] = D_M0_TR;
  TF1 *bichselZ_tr = new TF1(Form("BichselZ_tr_log2dx_%i",(int)log2dx),bichselZ,xStart,xStop,2);
  if (!bichselZ_tr) { std::cout << "Tr function error" << std::endl; return 1; }
  bichselZ_tr->SetParameters(params); 
  bichselZ_tr->SetNpx(npx);

  params[0] = D_M0_HE3;
  TF1 *bichselZ_he3 = new TF1(Form("BichselZ_he3_log2dx_%i",(int)log2dx),bichselZcharge2,xStart,xStop,2);
  if (!bichselZ_he3) { std::cout << "He3 function error" << std::endl; return 1; }
  bichselZ_he3->SetParameters(params); 
  bichselZ_he3->SetNpx(npx);

  params[0] = D_M0_HE4;
  TF1 *bichselZ_al = new TF1(Form("BichselZ_al_log2dx_%i",(int)log2dx),bichselZcharge2,xStart,xStop,2);
  if (!bichselZ_al) { std::cout << "Al function error" << std::endl; return 1; }
  bichselZ_al->SetParameters(params); 
  bichselZ_al->SetNpx(npx);
  //=========================================================
  //          END Bichsel Function Setup
  //=========================================================


  // HISTOGRAMS

  // temporary variables when histogram bins/bounds depend on the energy
  int tempBins1 = 0;
  double tempLowBound1 = 0;
  double tempHighBound1 = 0;
  int tempBins2 = 0;
  double tempLowBound2 = 0;
  double tempHighBound2 = 0;
  //std::cout << "test 3" << std::endl;


  TH1D *h_eventCheck = (TH1D*)inputFile->Get("h_eventCheck");
  h_eventCheck->SetStats(0);
  TH1D *h_event_de = new TH1D("h_event_de","Event # Count with deuteron;;eventID", 25000, 310000, 335000);

  TH1D *h_trackCheck = new TH1D("h_trackCheck","Track number after each cut;;Tracks", 3, 0, 3);
  h_trackCheck->GetXaxis()->SetBinLabel(1,"Event Cuts Only");
  h_trackCheck->GetXaxis()->SetBinLabel(2,"QA Cuts");
  h_trackCheck->GetXaxis()->SetBinLabel(3,"PID Cuts");
  h_trackCheck->SetStats(0);


  TH1D *h_simulationCheck_pp = new TH1D ("h_simulationCheck_pp", "N_{#pi+} with no TPC efficiency", 3, 0, 3);
  TH1D *h_simulationCheck_pm = new TH1D ("h_simulationCheck_pm", "N_{#pi-} with no TPC efficiency", 3, 0, 3);
  TH1D *h_simulationCheck_kp = new TH1D ("h_simulationCheck_kp", "N_{K+} with no TPC efficiency", 3, 0, 3);
  TH1D *h_simulationCheck_km = new TH1D ("h_simulationCheck_km", "N_{K-} with no TPC efficiency", 3, 0, 3);
  TH1D *h_simulationCheck_pr = new TH1D ("h_simulationCheck_pr", "N_{pr} with no TPC efficiency", 3, 0, 3);
  TH1D *h_simulationCheck_de = new TH1D ("h_simulationCheck_de", "N_{de} with no TPC efficiency", 3, 0, 3);
  TH1D *h_simulationCheck_tr = new TH1D ("h_simulationCheck_tr", "N_{tr} with no TPC efficiency", 3, 0, 3);
  TH1D *h_simulationCheck_he3 = new TH1D ("h_simulationCheck_he3", "N_{he3} with no TPC efficiency", 3, 0, 3);
  TH1D *h_simulationCheck_he4 = new TH1D ("h_simulationCheck_he4", "N_{he4} with no TPC efficiency", 3, 0, 3);
  TH1D *h_simulationCheck_total = new TH1D ("h_simulationCheck_total", "Total N_{trk}", 3, 0, 3);

  TH1D *h_nhits       = new TH1D("h_nhits", "nHits;Number of hits;Tracks", 50, 0, 50);
  TH1D *h_nhits_dEdx  = new TH1D("h_nhits_dEdx","nHitsdEdx;Number of hits;Tracks", 50, 0, 50);
  TH1D *h_nhitsFit    = new TH1D("h_nhitsFit", "nHitsFit;Number of hits for fitting;Tracks", 50, 0, 50);
  TH1D *h_nhitsPoss   = new TH1D("h_nhitsPoss", "nHitsFit;Number of hits possible;Tracks", 50, 0, 50);
  TH1D *h_nhits_ratio = new TH1D("h_nhits_ratio","nhitsFit/nhitsPoss;nhitsFit/nhitsPoss;Tracks",200,0.0,2.0);    
  TH1D *h_DCA         = new TH1D("h_DCA","DCA (cm);DCA (cm);Tracks",100,0.0,10.0);
  TH1D *h_DCA_pr_alt  = new TH1D("h_DCA_pr_alt","Alt Proton DCA (cm);DCA (cm);Tracks",100,0.0,10.0);
  TH1D *h_DCA_de      = new TH1D("h_DCA_de","Deuteron DCA (cm);DCA (cm);Tracks",100,0.0,10.0);
  TH1D *h_DCA_tr      = new TH1D("h_DCA_tr","Triton DCA (cm);DCA (cm);Tracks",100,0.0,10.0);
  TH1D *h_DCA_he3      = new TH1D("h_DCA_he3","Helium-3 DCA (cm);DCA (cm);Tracks",100,0.0,10.0);
  TH1D *h_DCA_he4      = new TH1D("h_DCA_he4","Helium-4 DCA (cm);DCA (cm);Tracks",100,0.0,10.0);

  TH1D *h_primTracks = new TH1D("h_primTracks","Raw Number of Primary Tracks;Tracks;Events", 200, 0, 200);

  tempBins1      = (configs.fixed_target) ? 200 : 500;
  tempLowBound1  = (configs.fixed_target) ? 190.0 : -210.0;
  tempHighBound1 = 210.0;
  TH1D* h_zvtx = new TH1D("h_zvtx","Primary Vertex Position in z;Distance (cm);Events", tempBins1, tempLowBound1, tempHighBound1);

  TH1D *h_tileWeights = new TH1D("h_tileWeights", "EPD Tile Weights;nMIP Weights;Hits", 5, -1, 4);
  TH1D *h_centralities = new TH1D("h_centralities", "Centralities;Centrality ID;Events", CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS);
  TH1D *h_centralities_final = new TH1D("h_centralities_final", "Final Good Centralities;Centrality ID;Events", CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS);

  TH1*      hCent9  = new     TH1D("hCent9", "hCent9", 10, -1, 9);
  TProfile* hCent9W = new TProfile("hCent9W", "hCent9W", 10, -1, 9);
  TH1*      hCent3  = new     TH1D("hCent3", "hCent3", 4, -1, 3);


  TH1D *h_trackmult = (TH1D*)inputFile->Get("h_trackmult");
  TH1D *h_refmult   = (TH1D*)inputFile->Get("h_refmult");
  TH1D *h_tofmult   = (TH1D*)inputFile->Get("h_tofmult");

  TH1D *h_pT = new TH1D("h_pT","p_{T};p_{T};Tracks",1000,0.0,10.0);
  TH1D *h_eta = new TH1D("h_eta","#eta;#eta;Tracks",600,-6.0,6.0);
  TH1D *h_phi = new TH1D("h_phi","#phi (Radian);#phi;Tracks",1000,-1.5*PI,1.5*PI);
  TH2D *h2_dEdx_vs_qp = new TH2D("h2_dEdx_vs_qp", "dE/dx vs q|p|;|p|/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_dEdx_vs_qp_m2_0 = new TH2D("h2_dEdx_vs_qp_0", "dE/dx vs p/q;p/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_dEdx_vs_qp_m2_1 = new TH2D("h2_dEdx_vs_qp_1", "dE/dx vs p/q;p/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_dEdx_vs_qp_m2_2 = new TH2D("h2_dEdx_vs_qp_2", "dE/dx vs p/q;p/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);

  TH2D *h2_dEdx_vs_qp_charge2 = new TH2D("h2_dEdx_vs_qp_charge2", "dE/dx vs q|p|;p/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_dEdx_vs_qp_half = new TH2D("h2_dEdx_vs_qp_half", "dE/dx vs q|p|;p/q (GeV/c);dE/dx (keV/cm)", 600, 0, 6, 2500, 0, 50);
  TH2D *h2_beta_vs_qp = new TH2D("h2_beta_vs_qp","1/#beta vs Momentum;p/q (GeV/c);1/#beta", 300, -3, 3, 300, 0.5, 3.5);
  TH2D *h2_Etofbeta_vs_qp = new TH2D("h2_Etofbeta_vs_qp","1/#beta vs Momentum;p/q (GeV/c);1/#beta", 300, -3, 3, 300, 0.5, 3.5);
  //TH2D *h2_m2_vs_qp = new TH2D("h2_m2_vs_qp", "m^2 vs q*|p|;q*|p| (GeV);m^2 (GeV^2)", 400, -4, 4, 400, -0.1, 1.5);
  TH2D *h2_m2_vs_qp = new TH2D("h2_m2_vs_qp", "m^2 vs q*|p|;p/q (GeV/c);m^2 (GeV^2)", 400, -4, 4, 1010, -0.1, 20.1);
  TH2D *h2_m2Etof_vs_qp = new TH2D("h2_m2Etof_vs_qp", "m^2 vs q*|p|;p/q (GeV/c);m^2 (GeV^2)", 400, -4, 4, 1010, -0.1, 20.1);
  TH2D *h2_m2_vs_qp_m2_0 = new TH2D("h2_m2_vs_qp_m2_0", "^{3}He m^2 vs q*|p|;p/q (GeV/c);m^2 (GeV^2)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_m2_vs_qp_m2_1 = new TH2D("h2_m2_vs_qp_m2_1", "d, ^{4}He, ^{6}Li m^2 vs q*|p|;p/q (GeV/c);m^2 (GeV^2)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_m2_vs_qp_m2_2 = new TH2D("h2_m2_vs_qp_m2_2", "t, ^{6}He m^2 vs q*|p|;p/q (GeV/c);m^2 (GeV^2)", 800, -2, 6, 2500, 0, 50);



  TH1D *h_tofBeta = new TH1D("h_tofBeta", "TOF #beta;#beta;Tracks", 150, 0, 1.5);
  TH1D *h_EtofBeta = new TH1D("h_EtofBeta", "TOF #beta;#beta;Tracks", 150, 0, 1.5);
  TH1D *h_m2 = new TH1D("h_m2", "m^{2};m^{2} (GeV^{2}/c^{4});Tracks", 1000, 0, 15);
  TH1D *h_m2Etof = new TH1D("h_m2Etof", "m^{2};m^{2} (GeV^{2}/c^{4});Tracks", 1000, 0, 15);
  TH1D *h_m2_alpha_he3 = new TH1D("h_m2_alpha_he3", "m^{2};m^{2} (GeV^{2}/c^{4});Tracks", 1000, 0, 15);
  TH1D *h_zTriton = new TH1D("h_zTriton", "z^{t};z^{t};Tracks", 700, -6, 1);
  TH1D *h_zHelium3 = new TH1D("h_zHelium3_he3", "z^{He-3};z^{He-3};Tracks", 700, -6, 1);
  TH1D *h_zHelium4 = new TH1D("h_zHelium4_he4", "z^{He-4};z^{He-4};Tracks", 700, -6, 1);

  TH1D *h_mom_pp = new TH1D("h_mom_pp", "#pi^{+} Total Momentum;|p| (GeV);", 100, 0, 5);
  TH1D *h_mom_pm = new TH1D("h_mom_pm", "#pi^{-} Total Momentum;|p| (GeV);", 100, 0, 5);
  TH1D *h_mom_kp = new TH1D("h_mom_kp", "K^{+} Total Momentum;|p| (GeV);",   100, 0, 5);
  TH1D *h_mom_km = new TH1D("h_mom_km", "K^{-} Total Momentum;|p| (GeV);",   100, 0, 5);
  TH1D *h_mom_pr = new TH1D("h_mom_pr", "Proton Total Momentum;|p| (GeV);",  100, 0, 5);
  TH1D *h_mom_de = new TH1D("h_mom_de", "Deuteron Total Momentum;|p| (GeV);",100, 0, 5);
  TH1D *h_mom_tr = new TH1D("h_mom_tr", "Triton Total Momentum;|p| (GeV);",  100, 0, 5);
  TH1D *h_mom_he3 = new TH1D("h_mom_he3", "Helium-3 Total Momentum;|p| (GeV);",100, 0, 5);
  TH1D *h_mom_he4 = new TH1D("h_mom_he4", "Helium-4 Total Momentum;|p| (GeV);",100, 0, 5);

  TH1D *h_pT_pp = new TH1D("h_pT_pp","#pi^{+} p_{T};p_{T} (GeV/c);Tracks",1000,0.0,5.0);
  TH1D *h_pT_pm = new TH1D("h_pT_pm","#pi^{-} p_{T}; p_{T} (GeV/c);Tracks",1000,0.0,5.0);
  TH1D *h_pT_kp = new TH1D("h_pT_kp","K^{+} p_{T}; p_{T} (GeV/c);Tracks",1000,0.0,5.0);
  TH1D *h_pT_km = new TH1D("h_pT_km","K^{-} p_{T}; p_{T} (GeV/c);Tracks",1000,0.0,5.0);
  TH1D *h_pT_pr = new TH1D("h_pT_pr","Proton p_{T};p_{T} (GeV/c);Tracks",1000,0.0,5.0);
  TH1D *h_pT_de = new TH1D("h_pT_de","Deuteron p_{T};p_{T} (GeV/c);Tracks",1000,0.0,5.0);
  TH1D *h_pT_tr = new TH1D("h_pT_tr","Triton p_{T};p_{T} (GeV/c);Tracks",1000,0.0,5.0);
  TH1D *h_pT_he3 = new TH1D("h_pT_he3","Helium-3 p_{T};p_{T} (GeV/c);Tracks",1000,0.0,5.0);
  TH1D *h_pT_he4 = new TH1D("h_pT_he4","Helium-4 p_{T};p_{T} (GeV/c);Tracks",1000,0.0,5.0);

  TH2D *h2_pT_vs_cent_pr = new TH2D("h2_pT_vs_cent_pr", "Proton;Centrality;p_{T} (GeV/c)", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 1000, 0.0, 5.0);
  TH2D *h2_pT_vs_cent_de = new TH2D("h2_pT_vs_cent_de", "Deuteron;Centrality;p_{T} (GeV/c)", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 1000, 0.0, 5.0);
  TH2D *h2_pT_vs_cent_tr = new TH2D("h2_pT_vs_cent_tr", "Triton;Centrality;p_{T} (GeV/c)", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 1000, 0.0, 5.0);
  TH2D *h2_pT_vs_cent_he3 = new TH2D("h2_pT_vs_cent_he3", "Helium-3;Centrality;p_{T} (GeV/c)", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 1000, 0.0, 5.0);
  TH2D *h2_pT_vs_cent_he4 = new TH2D("h2_pT_vs_cent_he4", "Helium-4;Centrality;p_{T} (GeV/c)", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 1000, 0.0, 5.0);

  TH2D *h2_dndDeltaPhi_vs_cent_pr_alt = new TH2D("h2_dndDeltaPhi_pr_alt", "Alt Proton;Centrality;dN/d(#Delta#phi)", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 100, -1.0*PI, PI);
  TH2D *h2_dndDeltaPhi_vs_cent_de     = new TH2D("h2_dndDeltaPhi_de", "Deuteron;Centrality;dN/d(#Delta#phi)", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 100, -1.0*PI, PI);
  TH2D *h2_dndDeltaPhi_vs_cent_tr     = new TH2D("h2_dndDeltaPhi_tr", "Triton;Centrality;dN/d(#Delta#phi)", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 100, -1.0*PI, PI);
  TH2D *h2_dndDeltaPhi_vs_cent_he3     = new TH2D("h2_dndDeltaPhi_he3", "Helium-3;Centrality;dN/d(#Delta#phi)", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 100, -1.0*PI, PI);
  TH2D *h2_dndDeltaPhi_vs_cent_he4     = new TH2D("h2_dndDeltaPhi_he4", "Helium-4;Centrality;dN/d(#Delta#phi)", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 100, -1.0*PI, PI);

  TH1D *h_eta_pp = new TH1D("h_eta_pp","#pi^{+} #eta;#eta;Tracks",500,-5.0,5.0);
  TH1D *h_eta_pm = new TH1D("h_eta_pm","#pi^{-} #eta;#eta;Tracks",500,-5.0,5.0);
  TH1D *h_eta_kp = new TH1D("h_eta_kp","K^{+} #eta;#eta;Tracks",500,-5.0,5.0);
  TH1D *h_eta_km = new TH1D("h_eta_km","K^{-} #eta;#eta;Tracks",500,-5.0,5.0);
  TH1D *h_eta_pr = new TH1D("h_eta_pr","Proton #eta;#eta;Tracks",500,-5.0,5.0);
  TH1D *h_eta_de = new TH1D("h_eta_de","Deuteron #eta;#eta;Tracks",500,-5.0,5.0);
  TH1D *h_eta_tr = new TH1D("h_eta_tr","Triton #eta;#eta;Tracks",500,-5.0,5.0);
  TH1D *h_eta_he3 = new TH1D("h_eta_he3","Helium-3 #eta;#eta;Tracks",500,-5.0,5.0);
  TH1D *h_eta_he4 = new TH1D("h_eta_he4","Helium-4 #eta;#eta;Tracks",500,-5.0,5.0);

  TH1D *h_dndy_pp = new TH1D("h_dndy_pp", "#pi^{+} Raw Rapidity Spectrum;y;dN/dy", 80, -2, 2);
  TH1D *h_dndy_pm = new TH1D("h_dndy_pm", "#pi^{-} Raw Rapidity Spectrum;y;dN/dy", 80, -2, 2);
  TH1D *h_dndy_kp = new TH1D("h_dndy_kp", "K^{+} Raw Rapidity Spectrum;y;dN/dy",   80, -2, 2);
  TH1D *h_dndy_km = new TH1D("h_dndy_km", "K^{-} Raw Rapidity Spectrum;y;dN/dy",   80, -2, 2);
  TH1D *h_dndy_pr = new TH1D("h_dndy_pr", "Proton Raw Rapidity Spectrum;y;dN/dy",  80, -2, 2);
  TH1D *h_dndy_de = new TH1D("h_dndy_de", "Deuteron Raw Rapidity Spectrum;y;dN/dy",  80, -2, 2);
  TH1D *h_dndy_tr = new TH1D("h_dndy_tr", "Triton Raw Rapidity Spectrum;y;dN/dy",  80, -2, 2);
  TH1D *h_dndy_he3 = new TH1D("h_dndy_he3", "Helium-3 Raw Rapidity Spectrum;y;dN/dy",  80, -2, 2);
  TH1D *h_dndy_he4 = new TH1D("h_dndy_he4", "Helium-4 Raw Rapidity Spectrum;y;dN/dy",  80, -2, 2);
  
  TH1D *h_phi_pp = new TH1D("h_phi_pp","#pi^{+} #phi (Radian);#phi;Tracks",1000,-1.5*PI,1.5*PI);
  TH1D *h_phi_pm = new TH1D("h_phi_pm","#pi^{-} #phi (Radian);#phi;Tracks",1000,-1.5*PI,1.5*PI);
  TH1D *h_phi_kp = new TH1D("h_phi_kp","K^{+} #phi (Radian);#phi;Tracks",1000,-1.5*PI,1.5*PI);
  TH1D *h_phi_km = new TH1D("h_phi_km","K^{-} #phi (Radian);#phi;Tracks",1000,-1.5*PI,1.5*PI);
  TH1D *h_phi_pr = new TH1D("h_phi_pr","Proton #phi (Radian);#phi;Tracks",1000,-1.5*PI,1.5*PI);
  TH1D *h_phi_de = new TH1D("h_phi_de","Deuteron #phi (Radian);#phi;Tracks",1000,-1.5*PI,1.5*PI);
  TH1D *h_phi_tr = new TH1D("h_phi_tr","Triton #phi (Radian);#phi;Tracks",1000,-1.5*PI,1.5*PI);
  TH1D *h_phi_he3 = new TH1D("h_phi_he3","Helium-3 #phi (Radian);#phi;Tracks",1000,-1.5*PI,1.5*PI);
  TH1D *h_phi_he4 = new TH1D("h_phi_he4","Helium-4 #phi (Radian);#phi;Tracks",1000,-1.5*PI,1.5*PI);

  TH1D *h_dndm_pp = new TH1D("h_dndm_pp", "#pi^{+} Raw m_{T} Spectrum;m_{T}-m_{0} (GeV);dN/dm_{T}", 60, 0, 3);
  TH1D *h_dndm_pm = new TH1D("h_dndm_pm", "#pi^{-} Raw m_{T} Spectrum;m_{T}-m_{0} (GeV);dN/dm_{T}", 60, 0, 3);
  TH1D *h_dndm_kp = new TH1D("h_dndm_kp", "K^{+} Raw m_{T} Spectrum;m_{T}-m_{0} (GeV);dN/dm_{T}",   60, 0, 3);
  TH1D *h_dndm_km = new TH1D("h_dndm_km", "K^{-} Raw m_{T} Spectrum;m_{T}-m_{0} (GeV);dN/dm_{T}",   60, 0, 3);
  TH1D *h_dndm_pr = new TH1D("h_dndm_pr", "Proton Raw m_{T} Spectrum;m_{T}-m_{0} (GeV);dN/dm_{T}",  60, 0, 3);
  TH1D *h_dndm_de = new TH1D("h_dndm_de", "Deuteron Raw m_{T} Spectrum;m_{T}-m_{0} (GeV);dN/dm_{T}",60, 0, 3);
  TH1D *h_dndm_tr = new TH1D("h_dndm_tr", "Triton Raw m_{T} Spectrum;m_{T}-m_{0} (GeV);dN/dm_{T}",  60, 0, 3);
  TH1D *h_dndm_he3 = new TH1D("h_dndm_he3", "Helium-3 Raw m_{T} Spectrum;m_{T}-m_{0} (GeV);dN/dm_{T}",60, 0, 3);
  TH1D *h_dndm_he4 = new TH1D("h_dndm_he4", "Helium-4 Raw m_{T} Spectrum;m_{T}-m_{0} (GeV);dN/dm_{T}",60, 0, 3);
  
  TH1D *h_mult_pp = new TH1D("h_mult_pp","#pi^{+} track multiplicity;#pi^{+} Mult;Events",1001,-0.5,1000.5);
  TH1D *h_mult_pm = new TH1D("h_mult_pm","#pi^{-} track multiplicity;#pi^{-} Mult;Events",1001,-0.5,1000.5);
  TH1D *h_mult_kp = new TH1D("h_mult_kp","K^{#plus} track multiplicity;K^{+} Mult;Events",1001,-0.5,1000.5);
  TH1D *h_mult_km = new TH1D("h_mult_km","K^{-} track multiplicity;K^{-} Mult;Events",1001,-0.5,1000.5);
  TH1D *h_mult_pr = new TH1D("h_mult_pr","Proton track multiplicity;Proton Mult;Events",1001,-0.5,1000.5);
  TH1D *h_mult_de = new TH1D("h_mult_de","Deuteron track multiplicity;Deuteron Mult;Events",1001,-0.5,1000.5);
  TH1D *h_mult_tr = new TH1D("h_mult_tr","Triton track multiplicity;Triton Mult;Events",1001,-0.5,1000.5);
  TH1D *h_mult_he3 = new TH1D("h_mult_he3","Helium-3 track multiplicity;Deuteron Mult;Events",1001,-0.5,1000.5);
  TH1D *h_mult_he4 = new TH1D("h_mult_he4","Helium-4 track multiplicity;Deuteron Mult;Events",1001,-0.5,1000.5);
  
  TH2D *h2_dEdx_vs_qp_pp = new TH2D("h2_dEdx_vs_qp_pp", "#pi^{+} dE/dx vs q|p|;|p|/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_dEdx_vs_qp_pm = new TH2D("h2_dEdx_vs_qp_pm", "#pi^{-} dE/dx vs q|p|;|p|/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_dEdx_vs_qp_kp = new TH2D("h2_dEdx_vs_qp_kp", "K^{+} dE/dx vs q|p|;|p|/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_dEdx_vs_qp_km = new TH2D("h2_dEdx_vs_qp_km", "K^{-} dE/dx vs q|p|;|p|/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_dEdx_vs_qp_pr = new TH2D("h2_dEdx_vs_qp_pr", "Proton dE/dx vs q|p|;|p|/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_dEdx_vs_qp_de = new TH2D("h2_dEdx_vs_qp_de", "Deuteron dE/dx vs q|p|;|p|/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_dEdx_vs_qp_tr = new TH2D("h2_dEdx_vs_qp_tr", "Triton dE/dx vs q|p|;|p|/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_dEdx_vs_qp_he3 = new TH2D("h2_dEdx_vs_qp_he3", "Helium-3 dE/dx vs q|p|;|p|/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_dEdx_vs_qp_he3_norm = new TH2D("h2_dEdx_vs_qp_he3_norm", "Helium-3 dE/dx vs q|p|;|p|/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_dEdx_vs_qp_he4 = new TH2D("h2_dEdx_vs_qp_he4", "Helium-4 dE/dx vs q|p|;|p|/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);
  TH2D *h2_dEdx_vs_qp_he4_norm = new TH2D("h2_dEdx_vs_qp_he4_norm", "Helium-4 dE/dx vs q|p|;|p|/q (GeV/c);dE/dx (keV/cm)", 800, -2, 6, 2500, 0, 50);
  
  TH2D *h2_beta_vs_qp_pp = new TH2D("h2_beta_vs_qp_pp","#pi^{+} 1/#beta vs Momentum;q*|p| (GeV);1/#beta", 300, -3, 3, 300, 0.5, 3.5);
  TH2D *h2_beta_vs_qp_pm = new TH2D("h2_beta_vs_qp_pm","#pi^{-} 1/#beta vs Momentum;q*|p| (GeV);1/#beta", 300, -3, 3, 300, 0.5, 3.5);
  TH2D *h2_beta_vs_qp_kp = new TH2D("h2_beta_vs_qp_kp","K^{+} 1/#beta vs Momentum;q*|p| (GeV);1/#beta", 300, -3, 3, 300, 0.5, 3.5);
  TH2D *h2_beta_vs_qp_km = new TH2D("h2_beta_vs_qp_km","K^{-} 1/#beta vs Momentum;q*|p| (GeV);1/#beta", 300, -3, 3, 300, 0.5, 3.5);
  //TH2D *h2_beta_vs_qp_pr = new TH2D("h2_beta_vs_qp_pr","Proton 1/#beta vs Momentum;q*|p| (GeV);1/#beta", 300, -3, 3, 300, 0.5, 3.5);
  //TH2D *h2_beta_vs_qp_de = new TH2D("h2_beta_vs_qp_de","Deuteron 1/#beta vs Momentum;q*|p| (GeV);1/#beta", 300, -3, 3, 300, 0.5, 3.5);
  //TH2D *h2_beta_vs_qp_tr = new TH2D("h2_beta_vs_qp_tr","Triton 1/#beta vs Momentum;q*|p| (GeV);1/#beta", 300, -3, 3, 300, 0.5, 3.5);
 
  TH2D *h2_m2_vs_qp_pp = new TH2D("h2_m2_vs_qp_pp", "#pi^{+} m^2 vs q*|p|;q*|p| (GeV);m^2 (GeV^2)", 500, -4, 6, 4000, -1, 15);
  TH2D *h2_m2_vs_qp_pm = new TH2D("h2_m2_vs_qp_pm", "#pi^{-} m^2 vs q*|p|;q*|p| (GeV);m^2 (GeV^2)", 500, -4, 6, 4000, -1, 15);
  TH2D *h2_m2_vs_qp_kp = new TH2D("h2_m2_vs_qp_kp", "K^{+} m^2 vs q*|p|;q*|p| (GeV);m^2 (GeV^2)",   500, -4, 6, 4000, -1, 15);
  TH2D *h2_m2_vs_qp_km = new TH2D("h2_m2_vs_qp_km", "K^{-} m^2 vs q*|p|;q*|p| (GeV);m^2 (GeV^2)",   500, -4, 6, 4000, -1, 15);
  TH2D *h2_m2_vs_qp_pr = new TH2D("h2_m2_vs_qp_pr", "Proton m^2 vs q*|p|;q*|p| (GeV);m^2 (GeV^2)",  500, -4, 6, 4000, -1, 15);
  TH2D *h2_m2_vs_qp_de = new TH2D("h2_m2_vs_qp_de", "Deuteron m^2 vs q*|p|;q*|p| (GeV);m^2 (GeV^2)",  500, -4, 6, 4000, -1, 15);
  TH2D *h2_m2_vs_qp_tr = new TH2D("h2_m2_vs_qp_tr", "Triton m^2 vs q*|p|;q*|p| (GeV);m^2 (GeV^2)",  500, -4, 6, 4000, -1, 15);
  TH2D *h2_m2_vs_qp_he3 = new TH2D("h2_m2_vs_qp_he3", "Helium-3 m^2 vs q*|p|;q*|p| (GeV);m^2 (GeV^2)",  500, -4, 6, 4000, -1, 15);
  TH2D *h2_m2_vs_qp_he3_norm = new TH2D("h2_m2_vs_qp_he3_norm", "Helium-3 m^2 vs q*|p|;q*|p| (GeV);m^2 (GeV^2)",  500, -4, 6, 4000, -1, 15);
  TH2D *h2_m2_vs_qp_he4 = new TH2D("h2_m2_vs_qp_he4", "Helium-4 m^2 vs q*|p|;q*|p| (GeV);m^2 (GeV^2)",  500, -4, 6, 4000, -1, 15);
  TH2D *h2_m2_vs_qp_he4_norm = new TH2D("h2_m2_vs_qp_he4_norm", "Helium-4 m^2 vs q*|p|;q*|p| (GeV);m^2 (GeV^2)",  500, -4, 6, 4000, -1, 15);

  if (configs.sqrt_s_NN == 3.0)
    {
      tempBins1 = 300;
      tempLowBound1 = -1.2;
      tempHighBound1 = 1.2;
      tempBins2 = 500;
      tempLowBound2  = 0.0;
      tempHighBound2 = 5.0;
    }
  else if (configs.sqrt_s_NN == 3.2 || configs.sqrt_s_NN == 3.9)
    {
      tempBins1 = 300;
      tempLowBound1 = -1.2;
      tempHighBound1 = 1.2;
      tempBins2 = 300;
      tempLowBound2  = 0.0;
      tempHighBound2 = 2.5;
    }
  else if (configs.sqrt_s_NN == 3.5)
    {
      tempBins1 = 300;
      tempLowBound1 = -1.0;
      tempHighBound1 = 1.4;
      tempBins2 = 300;
      tempLowBound2  = 0.0;
      tempHighBound2 = 2.5;
    }
  else if (configs.sqrt_s_NN == 4.49)
    {
      tempBins1 = 300;
      tempLowBound1 = -1.0;
      tempHighBound1 = 1.7;
      tempBins2 = 300;
      tempLowBound2  = 0.0;
      tempHighBound2 = 2.5;
    }
  else if (configs.sqrt_s_NN == 7.2)
    {
      tempBins1 = 300;
      tempLowBound1 = -0.2;
      tempHighBound1 = 2.2;
      tempBins2 = 300;
      tempLowBound2  = 0.0;
      tempHighBound2 = 2.5;
    }
  else if (configs.sqrt_s_NN == 7.7)
    {
      tempBins1 = 300;
      tempLowBound1 = -0.2;
      tempHighBound1 = 2.2;
      tempBins2 = 300;
      tempLowBound2  = 0.0;
      tempHighBound2 = 2.5;
    }
  else if (configs.sqrt_s_NN == 19.6)
    {
      tempBins1 = 400;
      tempLowBound1 = -2.0;
      tempHighBound1 = 2.0;
      tempBins2 = 500;
      tempLowBound2  = 0.0;
      tempHighBound2 = 5.0;
    }
  else
    {
      tempBins1 = 0;
      tempLowBound1 = 0.0;
      tempHighBound1 = 0.0;
      tempBins2 = 0;
      tempLowBound2  = 0.0;
      tempHighBound2 = 0.0;
    }
  TH2D *h2_pT_vs_yCM_pp = new TH2D("h2_pT_vs_yCM_pp", "#pi^{+};y-y_{mid};p_{T} (GeV/c)", tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pT_vs_yCM_pm = new TH2D("h2_pT_vs_yCM_pm", "#pi^{-};y-y_{mid};p_{T} (GeV/c)", tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pT_vs_yCM_kp = new TH2D("h2_pT_vs_yCM_kp", "K^{+};y-y_{mid};p_{T} (GeV/c)",   tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pT_vs_yCM_km = new TH2D("h2_pT_vs_yCM_km", "K^{-};y-y_{mid};p_{T} (GeV/c)",   tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pT_vs_yCM_pr = new TH2D("h2_pT_vs_yCM_pr", "Proton;y-y_{mid};p_{T} (GeV/c)",  tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pT_vs_yCM_pr_alt = new TH2D("h2_pT_vs_yCM_pr_alt", "Proton;y-y_{mid};p_{T} (GeV/c)",  tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pT_vs_yCM_de = new TH2D("h2_pT_vs_yCM_de", "Deuteron;y-y_{mid};p_{T} (GeV/c)",tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pT_vs_yCM_tr = new TH2D("h2_pT_vs_yCM_tr", "Triton;y-y_{mid};p_{T} (GeV/c)",  tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pT_vs_yCM_he3 = new TH2D("h2_pT_vs_yCM_he3", "Helium-3;y-y_{mid};p_{T} (GeV/c)",tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pT_vs_yCM_he3_norm = new TH2D("h2_pT_vs_yCM_he3_norm", "Helium-3;y-y_{mid};p_{T} (GeV/c)",tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pT_vs_yCM_he3_weight = new TH2D("h2_pT_vs_yCM_he3_weight", "Helium-3;y-y_{mid};p_{T} (GeV/c)",tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pT_vs_yCM_he3_weight_check = new TH2D("h2_pT_vs_yCM_he3_weight_check", "Helium-3;y-y_{mid};p_{T} (GeV/c)",tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pT_vs_yCM_he4 = new TH2D("h2_pT_vs_yCM_he4", "Helium-4;y-y_{mid};p_{T} (GeV/c)",tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pT_vs_yCM_he4_norm = new TH2D("h2_pT_vs_yCM_he4_norm", "Helium-4;y-y_{mid};p_{T} (GeV/c)",tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pT_vs_yCM_he4_weight = new TH2D("h2_pT_vs_yCM_he4_weight", "Helium-4;y-y_{mid};p_{T} (GeV/c)",tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);

  TH2D *h2_pT_vs_yCM_pp_noEff = new TH2D("h2_pT_vs_yCM_pp_noEff", "#pi^{+} with No TPC Efficiency;y-y_{mid};p_{T} (GeV/c)",  
					 tempBins1, tempLowBound1, tempHighBound1, 500, 0.0, 5.0);
  TH2D *h2_pT_vs_yCM_pm_noEff = new TH2D("h2_pT_vs_yCM_pm_noEff", "#pi^{-} with No TPC Efficiency;y-y_{mid};p_{T} (GeV/c)",  
					 tempBins1, tempLowBound1, tempHighBound1, 500, 0.0, 5.0);
  TH2D *h2_pT_vs_yCM_kp_noEff = new TH2D("h2_pT_vs_yCM_kp_noEff", "K^{+} with No TPC Efficiency;y-y_{mid};p_{T} (GeV/c)",  
					 tempBins1, tempLowBound1, tempHighBound1, 500, 0.0, 5.0);
  TH2D *h2_pT_vs_yCM_km_noEff = new TH2D("h2_pT_vs_yCM_km_noEff", "K^{-} with No TPC Efficiency;y-y_{mid};p_{T} (GeV/c)",  
					 tempBins1, tempLowBound1, tempHighBound1, 500, 0.0, 5.0);
  TH2D *h2_pT_vs_yCM_pr_noEff = new TH2D("h2_pT_vs_yCM_pr_noEff", "Protons with No TPC Efficiency;y-y_{mid};p_{T} (GeV/c)",  
					 tempBins1, tempLowBound1, tempHighBound1, 500, 0.0, 5.0);
  TH2D *h2_pT_vs_yCM_de_noEff = new TH2D("h2_pT_vs_yCM_de_noEff", "Deuterons with No TPC Efficiency;y-y_{mid};p_{T} (GeV/c)",  
					 tempBins1, tempLowBound1, tempHighBound1, 500, 0.0, 5.0);
  TH2D *h2_pT_vs_yCM_tr_noEff = new TH2D("h2_pT_vs_yCM_tr_noEff", "Tritons with No TPC Efficiency;y-y_{mid};p_{T} (GeV/c)",  
					 tempBins1, tempLowBound1, tempHighBound1, 500, 0.0, 5.0);
  TH2D *h2_pT_vs_yCM_he3_noEff = new TH2D("h2_pT_vs_yCM_he3_noEff", "Helium-3 with No TPC Efficiency;y-y_{mid};p_{T} (GeV/c)",  
        				 tempBins1, tempLowBound1, tempHighBound1, 500, 0.0, 5.0);
  TH2D *h2_pT_vs_yCM_he4_noEff = new TH2D("h2_pT_vs_yCM_he4_noEff", "Helium-4 with No TPC Efficiency;y-y_{mid};p_{T} (GeV/c)",  
        				 tempBins1, tempLowBound1, tempHighBound1, 500, 0.0, 5.0);

//Cross check with psn0770
        // define histogtrams
  TH2D* hDpty[4];
  TH2D* hDMass2p[4];
  TH2D* hDdEdxp[4];
  TH2D* hDpty_weight[4];
  TH2D* hTpty[4];
  TH2D* hTMass2p[4];
  TH2D* hTdEdxp[4];
  TH2D* hTpty_weight[4];
  //TH2D* hHe3pty[4];
  //TH2D* hHe3Mass2p[4];
  //TH2D* hHe3dEdxp[4];
  //TH2D* hHe3pty_weight[4];
  //TH2D* hHe3pty_noEff[4];
  //TH2D* hHe4pty[4];
  //TH2D* hHe4Mass2p[4];
  //TH2D* hHe4dEdxp[4];
  //TH2D* hHe4pty_weight[4];
  char buff[255];

  for(Int_t i =0; i<4; i++) {
                sprintf(buff, "hDpty_cent%d", i);
                //hDpty[i]  = new TH2D(buff, "", 340, -1.2, 0.5, 500, 0.0, 5.0);
                hDpty[i]  = new TH2D(buff, "", 340, -0.5, 1.2, 500, 0.0, 5.0);
                sprintf(buff, "hDpty_weight_cent%d", i);
                hDpty_weight[i]  = new TH2D(buff, "", 340, -0.5, 1.2, 500, 0.0, 5.0);
                sprintf(buff, "hDMass2p_cent%d", i);
                hDMass2p[i]  = new TH2D(buff, "",  800, -2.0, 6.0,750, 0.0, 15);
                sprintf(buff, "hDdEdxp_cent%d", i);
                hDdEdxp[i]  = new TH2D(buff, "",  800, -2.0, 6.0,2500, 0.0, 50);

                
		sprintf(buff, "hTpty_cent%d", i);
                hTpty[i]  = new TH2D(buff, "",  340, -0.5, 1.2, 600, 0.0, 6.0);
                sprintf(buff, "hTpty_weight_cent%d", i);
                hTpty_weight[i]  = new TH2D(buff, "",  340, -0.5, 1.2, 600, 0.0, 6.0);
                sprintf(buff, "hTMass2p_cent%d", i);
                hTMass2p[i]  = new TH2D(buff, "",  800, -2.0, 6.0,750, 0.0, 15);
                sprintf(buff, "hTdEdxp_cent%d", i);
                hTdEdxp[i]  = new TH2D(buff, "",  800, -2.0, 6.0,2500, 0.0, 50);
		
                //sprintf(buff, "hHe3pty_cent%d", i);
                //hHe3pty[i]  = new TH2D(buff, "",  340, -1.2, 0.5, 600, 0.0, 6.0);
                //sprintf(buff, "hHe3Mass2p_cent%d", i);
                //hHe3Mass2p[i]  = new TH2D(buff, "",  800, -2.0, 6.0,750, 0.0, 15);
                //sprintf(buff, "hHe3dEdxp_cent%d", i);
                //hHe3dEdxp[i]  = new TH2D(buff, "",  800, -2.0, 6.0,2500, 0.0, 50);
                //sprintf(buff, "hHe4pty_cent%d", i);
                //hHe4pty[i]  = new TH2D(buff, "",  340, -1.2, 0.5, 600, 0.0, 6.0);
                //sprintf(buff, "hHe4Mass2p_cent%d", i);
                //hHe4Mass2p[i]  = new TH2D(buff, "",  800, -2.0, 6.0,750, 0.0, 15);
                //sprintf(buff, "hHe4dEdxp_cent%d", i);
                //hHe4dEdxp[i]  = new TH2D(buff, "",  800, -2.0, 6.0,2500, 0.0, 50);
                //sprintf(buff, "hHe4pty_cent%d", i);
                //sprintf(buff, "hHe3pty_weight_cent%d", i);
                //hHe3pty_weight[i]  = new TH2D(buff, "",  340, -1.2, 0.5, 600, 0.0, 6.0);
                //sprintf(buff, "hHe3pty_noEff_cent%d", i);
                //hHe3pty_noEff[i]  = new TH2D(buff, "",  340, -1.2, 0.5, 600, 0.0, 6.0);
                //sprintf(buff, "hHe4pty_weight_cent%d", i);
                //hHe4pty_weight[i]  = new TH2D(buff, "",  340, -1.2, 0.5, 600, 0.0, 6.0);
        }


  TH1D *h_psiTpc_RAW  = new TH1D("h_psiTpc_RAW", "Raw Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS);
  TH1D *h_psiTpcA_RAW = new TH1D("h_psiTpcA_RAW", "Raw Event Plane Angles (m = "+ORDER_M_STR+", TPC A);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS);
  TH1D *h_psiTpcB_RAW = new TH1D("h_psiTpcB_RAW", "Raw Event Plane Angles (m = "+ORDER_M_STR+", TPC B);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS);
  TH1D *h_psiEpd_RAW  = new TH1D("h_psiEpd_RAW", "Raw Event Plane Angles (m = "+ORDER_M_STR+", EPD);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS);
  TH1D *h_psiEpdA_RAW = new TH1D("h_psiEpdA_RAW", "Raw Event Plane Angles (m = "+ORDER_M_STR+", EPD A);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS);
  TH1D *h_psiEpdB_RAW = new TH1D("h_psiEpdB_RAW", "Raw Event Plane Angles (m = "+ORDER_M_STR+", EPD B);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS);

  TH2D *h2_psiTpc_RAW_Cent16   = new TH2D("h2_psiTpc_RAW_Cent16", "Raw Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS); 
  TH2D *h2_psiTpcA_RAW_Cent16  = new TH2D("h2_psiTpcA_RAW_Cent16", "Raw Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS); 
  TH2D *h2_psiTpcB_RAW_Cent16  = new TH2D("h2_psiTpcB_RAW_Cent16", "Raw Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS); 
  TH2D *h2_psiEpd_RAW_Cent16   = new TH2D("h2_psiEpd_RAW_Cent16", "Raw Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);  
  TH2D *h2_psiEpdA_RAW_Cent16  = new TH2D("h2_psiEpdA_RAW_Cent16", "Raw Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS); 
  TH2D *h2_psiEpdB_RAW_Cent16  = new TH2D("h2_psiEpdB_RAW_Cent16", "Raw Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS); 

  // Enable Sumw2 by default for all TH1 histograms
  TProfile::SetDefaultSumw2();
  TProfile2D::SetDefaultSumw2();
    //
  TProfile *p_meanpT_vs_yCM_pp = new TProfile("p_meanpT_vs_yCM_pp","#pi^{+} <p_{T}>;y-y_{mid};<p_{T}>", 44, -2.2, 2.2);
  TProfile *p_meanpT_vs_yCM_pm = new TProfile("p_meanpT_vs_yCM_pm","#pi^{-} <p_{T}>;y-y_{mid};<p_{T}>", 44, -2.2, 2.2);
  TProfile *p_meanpT_vs_yCM_kp = new TProfile("p_meanpT_vs_yCM_kp","K^{+} <p_{T}>;y-y_{mid};<p_{T}>", 44, -2.2, 2.2);
  TProfile *p_meanpT_vs_yCM_km = new TProfile("p_meanpT_vs_yCM_km","K^{-} <p_{T}>;y-y_{mid};<p_{T}>", 44, -2.2, 2.2);
  TProfile *p_meanpT_vs_yCM_pr = new TProfile("p_meanpT_vs_yCM_pr","Proton <p_{T}>;y-y_{mid};<p_{T}>", 44, -2.2, 2.2);
  TProfile *p_meanpT_vs_yCM_pr_alt = new TProfile("p_meanpT_vs_yCM_pr_alt","Proton <p_{T}>;y-y_{mid};<p_{T}>", 44, -2.2, 2.2);
  TProfile *p_meanpT_vs_yCM_de = new TProfile("p_meanpT_vs_yCM_de","Deuteron <p_{T}>;y-y_{mid};<p_{T}>", 44, -2.2, 2.2);
  TProfile *p_meanpT_vs_yCM_tr = new TProfile("p_meanpT_vs_yCM_tr","Triton <p_{T}>;y-y_{mid};<p_{T}>", 44, -2.2, 2.2);
  TProfile *p_meanpT_vs_yCM_he3 = new TProfile("p_meanpT_vs_yCM_he3","Helium-3 <p_{T}>;y-y_{mid};<p_{T}>", 44, -2.2, 2.2);
  TProfile *p_meanpT_vs_yCM_he4 = new TProfile("p_meanpT_vs_yCM_he4","Helium-4 <p_{T}>;y-y_{mid};<p_{T}>", 44, -2.2, 2.2);


  TProfile *p_vn_pp = new TProfile("p_vn_pp", "#pi^{+} v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
				   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_pm = new TProfile("p_vn_pm", "#pi^{-} v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
				   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_kp = new TProfile("p_vn_kp", "K^{+} v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
				   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_km = new TProfile("p_vn_km", "K^{-} v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
				   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_pr = new TProfile("p_vn_pr", "Proton v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
				   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_pr_alt = new TProfile("p_vn_pr_alt", "Proton v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
				       CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_pr_pTlt1 = new TProfile("p_vn_pr_pTlt1", "Proton v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
					 CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_pr_pTgt1 = new TProfile("p_vn_pr_pTgt1", "Proton v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
					 CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_de = new TProfile("p_vn_de", "Deuteron v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
				   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_tr = new TProfile("p_vn_tr", "Triton v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
				   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_he3 = new TProfile("p_vn_he3", "Helium-3 v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
        			   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_he4 = new TProfile("p_vn_he4", "Helium-4 v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
        			   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);

  TProfile *p_vn_pr_alt_y0to0p6 = new TProfile("p_vn_pr_alt_y0to0p6", 
					       "Proton v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
					       CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_de_y0to0p6 = new TProfile("p_vn_de_y0to0p6", 
					   "Deuteron v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}",
					   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_tr_y0to0p6 = new TProfile("p_vn_tr_y0to0p6", 
					   "Triton v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
					   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_he3_y0to0p6 = new TProfile("p_vn_he3_y0to0p6", 
					   "Helium-3 v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}",
					   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_he4_y0to0p6 = new TProfile("p_vn_he4_y0to0p6", 
					   "Helium-4 v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}",
					   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);

  TProfile *p_vn_pr_alt_y0p6to1p0 = new TProfile("p_vn_pr_alt_y0p6to1p0", 
						 "Proton v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
						 CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_de_y0p6to1p0 = new TProfile("p_vn_de_y0p6to1p0", 
					     "Deuteron v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
					     CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_tr_y0p6to1p0 = new TProfile("p_vn_tr_y0p6to1p0", 
					     "Triton v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
					     CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_he3_y0p6to1p0 = new TProfile("p_vn_he3_y0p6to1p0", 
					     "Helium-3 v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
					     CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_he4_y0p6to1p0 = new TProfile("p_vn_he4_y0p6to1p0", 
					     "Helium-4 v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
					     CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);

  // vn profiles at "extended" rapidity range 0.5 < y_CM < 1.0
  TProfile *p_vn_pp_ext = new TProfile("p_vn_pp_ext", "#pi^{+} v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
				       CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_pm_ext = new TProfile("p_vn_pm_ext", "#pi^{-} v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
				       CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_kp_ext = new TProfile("p_vn_kp_ext", "K^{+} v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
				       CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_km_ext = new TProfile("p_vn_km_ext", "K^{-} v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
				       CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_pr_ext = new TProfile("p_vn_pr_ext", "Proton v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
				       CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);

  // vn profiles at the "forward" raidity range y_CM < 0
  TProfile *p_vn_pr_for = new TProfile("p_vn_pr_for", "Proton v_{"+ORDER_N_STR+"};Centrality;v_{"+ORDER_N_STR+"}{#psi_{"+ORDER_M_STR+"}}/R_{"+ORDER_N_STR+ORDER_M_STR+"}", 
				       CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);


  // "Observed" flow values (uncorrected by event plane resolution)
  TProfile *p_vn_pp_obs = new TProfile("p_vn_pp_obs", "#pi^{+} v_{"+ORDER_N_STR+"}^{obs};Centrality;v_{"+ORDER_N_STR+"}^{obs}{#psi_{"+ORDER_M_STR+"}}", 
				   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_pm_obs = new TProfile("p_vn_pm_obs", "#pi^{-} v_{"+ORDER_N_STR+"}^{obs};Centrality;v_{"+ORDER_N_STR+"}^{obs}{#psi_{"+ORDER_M_STR+"}}", 
				    CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_kp_obs = new TProfile("p_vn_kp_obs", "K^{+} v_{"+ORDER_N_STR+"}^{obs};Centrality;v_{"+ORDER_N_STR+"}^{obs}{#psi_{"+ORDER_M_STR+"}}", 
				    CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_km_obs = new TProfile("p_vn_km_obs", "K^{-} v_{"+ORDER_N_STR+"}^{obs};Centrality;v_{"+ORDER_N_STR+"}^{obs}{#psi_{"+ORDER_M_STR+"}}", 
				    CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_pr_obs = new TProfile("p_vn_pr_obs", "Proton v_{"+ORDER_N_STR+"}^{obs};Centrality;v_{"+ORDER_N_STR+"}^{obs}{#psi_{"+ORDER_M_STR+"}}", 
				    CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_pr_alt_obs = new TProfile("p_vn_pr_alt_obs", "Proton v_{"+ORDER_N_STR+"}^{obs};Centrality;v_{"+ORDER_N_STR+"}^{obs}{#psi_{"+ORDER_M_STR+"}}", 
				       CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_de_obs = new TProfile("p_vn_de_obs", "Deuteron v_{"+ORDER_N_STR+"}^{obs};Centrality;v_{"+ORDER_N_STR+"}^{obs}{#psi_{"+ORDER_M_STR+"}}", 
				   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_tr_obs = new TProfile("p_vn_tr_obs", "Triton v_{"+ORDER_N_STR+"}^{obs};Centrality;v_{"+ORDER_N_STR+"}^{obs}{#psi_{"+ORDER_M_STR+"}}", 
				    CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_he3_obs = new TProfile("p_vn_he3_obs", "Helium-3 v_{"+ORDER_N_STR+"}^{obs};Centrality;v_{"+ORDER_N_STR+"}^{obs}{#psi_{"+ORDER_M_STR+"}}", 
				   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);
  TProfile *p_vn_he4_obs = new TProfile("p_vn_he4_obs", "Helium-4 v_{"+ORDER_N_STR+"}^{obs};Centrality;v_{"+ORDER_N_STR+"}^{obs}{#psi_{"+ORDER_M_STR+"}}", 
				   CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);


  // Differential Flow Profiles
  //TProfile2D *p2_v1_pT_eta_TPCB_pr = new TProfile2D("p2_v1_pT_eta_TPCB_pr", "TPC B Proton v_{1};#eta;p_{T}", 25, -1.0, 0.0, 25, 0, 2.5);
  //TProfile *p_v1_EPD_ring = new TProfile("p_v1_EPD_ring", "EPD v_{1} by Ring;Ring;v_{1}", 16, 0.5, 16.5);

  TProfile2D *p2_vn_yCM_cent_pp = new TProfile2D("p2_vn_yCM_cent_pp", "#pi^{+} v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  TProfile2D *p2_vn_yCM_cent_pm = new TProfile2D("p2_vn_yCM_cent_pm", "#pi^{-} v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  TProfile2D *p2_vn_yCM_cent_kp = new TProfile2D("p2_vn_yCM_cent_kp", "K^{+} v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  TProfile2D *p2_vn_yCM_cent_km = new TProfile2D("p2_vn_yCM_cent_km", "K^{-} v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  TProfile2D *p2_vn_yCM_cent_pr = new TProfile2D("p2_vn_yCM_cent_pr", "Proton v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  TProfile2D *p2_vn_yCM_cent_pr_alt = 
    new TProfile2D("p2_vn_yCM_cent_pr_alt", "Proton v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  TProfile2D *p2_vn_yCM_cent_pr_symmetry = 
    new TProfile2D("p2_vn_yCM_cent_pr_symmetry", "Proton v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  TProfile2D *p2_vn_yCM_cent_de = new TProfile2D("p2_vn_yCM_cent_de", "Deuteron v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  TProfile2D *p2_vn_yCM_cent_de_alt = new TProfile2D("p2_vn_yCM_cent_de_alt", "Deuteron v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  TProfile2D *p2_vn_yCM_cent_tr = new TProfile2D("p2_vn_yCM_cent_tr", "Triton v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  TProfile2D *p2_vn_yCM_cent_tr_alt = new TProfile2D("p2_vn_yCM_cent_tr_alt", "Triton v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);

  TProfile2D *p2_vn_yCM_cent_he3 = new TProfile2D("p2_vn_yCM_cent_he3", "Helium-3 v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  p2_vn_yCM_cent_he3->Sumw2();
  TProfile2D *p2_vn_yCM_cent_he3_alt = new TProfile2D("p2_vn_yCM_cent_he3_alt", "Helium-3 v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  p2_vn_yCM_cent_he3_alt->Sumw2();
  TProfile2D *p2_vn_yCM_cent_he3_noEff = new TProfile2D("p2_vn_yCM_cent_he3_noEff", "Helium-3 v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  p2_vn_yCM_cent_he3_noEff->Sumw2();
  TProfile2D *p2_vn_yCM_cent_he4 = new TProfile2D("p2_vn_yCM_cent_he4", "Helium-4 v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  p2_vn_yCM_cent_he4->Sumw2();
  TProfile2D *p2_vn_yCM_cent_he4_alt = new TProfile2D("p2_vn_yCM_cent_he4_alt", "Helium-4 v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  p2_vn_yCM_cent_he4_alt->Sumw2();
  TProfile2D *p2_vn_yCM_cent_he4_noEff = new TProfile2D("p2_vn_yCM_cent_he4_noEff", "Helium-3 v_{"+ORDER_N_STR+"};Centrality;y-y_{mid}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 44, -2.2, 2.2);
  p2_vn_yCM_cent_he4_noEff->Sumw2();

  TProfile2D *p2_vn_yOverYbeam_cent_pr_alt = 
    new TProfile2D("p2_vn_yOverYbeam_cent_pr_alt", "Proton v_{"+ORDER_N_STR+"};Centrality;y/|y_{beam}|", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 25, -0.5, 0.0);
  TProfile2D *p2_vn_yOverYbeam_cent_de = 
    new TProfile2D("p2_vn_yOverYbeam_cent_de", "Deuteron v_{"+ORDER_N_STR+"};Centrality;y/|y_{beam}|", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 25, -0.5, 0.0);
  TProfile2D *p2_vn_yOverYbeam_cent_tr = 
    new TProfile2D("p2_vn_yOverYbeam_cent_tr", "Triton v_{"+ORDER_N_STR+"};Centrality;y/|y_{beam}|", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 25, -0.5, 0.0);
  TProfile2D *p2_vn_yOverYbeam_cent_he3 = 
    new TProfile2D("p2_vn_yOverYbeam_cent_he3", "Helium-3 v_{"+ORDER_N_STR+"};Centrality;y/|y_{beam}|", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 25, -0.5, 0.0);
  TProfile2D *p2_vn_yOverYbeam_cent_he4 = 
    new TProfile2D("p2_vn_yOverYbeam_cent_he4", "Helium-4 v_{"+ORDER_N_STR+"};Centrality;y/|y_{beam}|", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 25, -0.5, 0.0);

  
  TProfile2D *p2_vn_pT_cent_pp = new TProfile2D("p2_vn_pT_cent_pp", "#pi^{+} v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 10, 0, 2);
  TProfile2D *p2_vn_pT_cent_pm = new TProfile2D("p2_vn_pT_cent_pm", "#pi^{-} v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 10, 0, 2);
  TProfile2D *p2_vn_pT_cent_kp = new TProfile2D("p2_vn_pT_cent_kp", "K^{+} v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 10, 0, 2);
  TProfile2D *p2_vn_pT_cent_km = new TProfile2D("p2_vn_pT_cent_km", "K^{-} v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 10, 0, 2);
  TProfile2D *p2_vn_pT_cent_pr = new TProfile2D("p2_vn_pT_cent_pr", "Proton v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 60, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_pr_alt = new TProfile2D("p2_vn_pT_cent_pr_alt", "Proton v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 60, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_pr_ext = new TProfile2D("p2_vn_pT_cent_pr_ext", "Proton v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 60, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_pr_yMid = new TProfile2D("p2_vn_pT_cent_pr_yMid", "Proton v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 60, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_pr_yFor = new TProfile2D("p2_vn_pT_cent_pr_yFor", "Proton v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 60, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_pr_yExt = new TProfile2D("p2_vn_pT_cent_pr_yExt", "Proton v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 60, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_pr_yEnd = new TProfile2D("p2_vn_pT_cent_pr_yEnd", "Proton v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 60, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_de = new TProfile2D("p2_vn_pT_cent_de", "Deuteron v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_de_yMid = new TProfile2D("p2_vn_pT_cent_de_yMid", "Deuteron v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_de_yFor = new TProfile2D("p2_vn_pT_cent_de_yFor", "Deuteron v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_de_yExt = new TProfile2D("p2_vn_pT_cent_de_yExt", "Deuteron v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_de_yEnd = new TProfile2D("p2_vn_pT_cent_de_yEnd", "Deuteron v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_tr = new TProfile2D("p2_vn_pT_cent_tr", "Triton v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_tr_yMid = new TProfile2D("p2_vn_pT_cent_tr_yMid", "Triton v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_tr_yFor = new TProfile2D("p2_vn_pT_cent_tr_yFor", "Triton v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_tr_yExt = new TProfile2D("p2_vn_pT_cent_tr_yExt", "Triton v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_tr_yEnd = new TProfile2D("p2_vn_pT_cent_tr_yEnd", "Triton v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_he3 = new TProfile2D("p2_vn_pT_cent_he3", "Helium-3 v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_he3_yMid = new TProfile2D("p2_vn_pT_cent_he3_yMid", "Helium-3 v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_he3_yFor = new TProfile2D("p2_vn_pT_cent_he3_yFor", "Helium-3 v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_he3_yExt = new TProfile2D("p2_vn_pT_cent_he3_yExt", "Helium-3 v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_he3_yEnd = new TProfile2D("p2_vn_pT_cent_he3_yEnd", "Helium-3 v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_he4 = new TProfile2D("p2_vn_pT_cent_he4", "Helium-4 v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_he4_yMid = new TProfile2D("p2_vn_pT_cent_he4_yMid", "Helium-4 v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_he4_yFor = new TProfile2D("p2_vn_pT_cent_he4_yFor", "Helium-4 v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_he4_yExt = new TProfile2D("p2_vn_pT_cent_he4_yExt", "Helium-4 v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  TProfile2D *p2_vn_pT_cent_he4_yEnd = new TProfile2D("p2_vn_pT_cent_he4_yEnd", "Helium-4 v_{"+ORDER_N_STR+"};Centrality;p_{T}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 30, 0, 5.0);
  p2_vn_pT_cent_he3->Sumw2();
  p2_vn_pT_cent_he3_yMid->Sumw2(); 
  p2_vn_pT_cent_he3_yFor->Sumw2(); 
  p2_vn_pT_cent_he3_yExt->Sumw2(); 
  p2_vn_pT_cent_he3_yEnd->Sumw2(); 
  p2_vn_pT_cent_he4->Sumw2();

  // helium3 v1 pt bins
  //Float_t Ybin = 10;
  //Float_t YBins[6] = {0, -0.1, -0.2, -0.3, -0.4, -0.5};
  Float_t YBins[6] = {0, 0.1, 0.2, 0.3, 0.4, 0.5};
  //Float_t DPtBins[4]   = {0.8, 1.4, 2.0, 3.5};
  //Float_t TPtBins[4]   = {1.2, 2.1, 3.0, 4.};
  //Float_t He4PtBins[4] = {1.6, 2.8, 3.9999, 4.0};

  Float_t yLowCut = 0.;
  Float_t yHighCut = 0.5;
  //Float_t DptLowCut = 0.8;
  //Float_t DptHighCut = 3.5;
  //Float_t TptLowCut = 1.0;
  //Float_t TptHighCut = 2.5;
  Float_t He3ptLowCut = 1.0;
  Float_t He3ptHighCut = 2.5;
  //Float_t He4ptLowCut = 1.0;
  //Float_t He4ptHighCut = 3.0;

  Float_t he3pt_v1bins[10]  = {
          1.2, 1.4, 1.6, 1.9, 2.2, 2.5,
          2.8, 3.2, 3.6, 4.0};
  Int_t  he3v1binnum = sizeof(he3pt_v1bins)/sizeof(Float_t) - 1;
  TProfile* pHe3v1Pt[4][6];
  //char buff[255];
  for(int i=0; i<4; i++) {
    for(int j=0; j<6; j++) {
      /// pt dependence
      sprintf(buff, "pHe3v1Pt_cent%d_y%d", i, j);
      pHe3v1Pt[i][j]    = new TProfile(buff, "", he3v1binnum, he3pt_v1bins);
      pHe3v1Pt[i][j]->Sumw2();
        		   }
  }



  //TProfile* pHe3vnPt[4][6];

  //      for(int i=0; i<4; i++) {
  //              for(int j=0; j<6; j++) {
  //                      /// pt dependence
  //                      //sprintf(buff, "pDv1Pt_cent%d_y%d", i, j); 
  //                      //pDv1Pt[i][j]    = new TProfile(buff, "", dv1binnum, dpt_v1bins);
  //                      //pDv1Pt[i][j]->Sumw2();

  //                      //sprintf(buff, "pTv1Pt_cent%d_y%d", i, j); 
  //                      //pTv1Pt[i][j]    = new TProfile(buff, "", tv1binnum, tpt_v1bins);
  //                      //pTv1Pt[i][j]->Sumw2();

  //                      sprintf(buff, "pHe3vnPt_cent%d_y%d", i, j); 
  //                      pHe3vnPt[i][j]    = new TProfile(buff, "", he3vnbinnum, he3pt_vnbins);
  //                      pHe3vnPt[i][j]->Sumw2();

  //                      //sprintf(buff, "pHe4v1Pt_cent%d_y%d", i, j); 
  //                      //pHe4v1Pt[i][j]    = new TProfile(buff, "", he4v1binnum, he4pt_v1bins);
  //                      //pHe4v1Pt[i][j]->Sumw2();

  //                      //sprintf(buff, "pDv2Pt_cent%d_y%d", i, j); 
  //                      //pDv2Pt[i][j]    = new TProfile(buff, "", dv2binnum, dpt_v2bins);
  //                      //pDv2Pt[i][j]->Sumw2();

  //                      //sprintf(buff, "pTv2Pt_cent%d_y%d", i, j); 
  //                      //pTv2Pt[i][j]    = new TProfile(buff, "", tv2binnum, tpt_v2bins);
  //                      //pTv2Pt[i][j]->Sumw2();

  //                      //sprintf(buff, "pHe3v2Pt_cent%d_y%d", i, j); 
  //                      //pHe3v2Pt[i][j]    = new TProfile(buff, "", he3v2binnum, he3pt_v2bins);
  //                      //pHe3v2Pt[i][j]->Sumw2();

  //                      //sprintf(buff, "pHe4v2Pt_cent%d_y%d", i, j); 
  //                      //pHe4v2Pt[i][j]    = new TProfile(buff, "", he4v2binnum, he4pt_v2bins);
  //                      //pHe4v2Pt[i][j]->Sumw2();
  //              }
  //      }   


  // yCM stratified by pT
  TProfile2D *p2_vn_pT_vs_yCM_pp = new TProfile2D("p2_vn_pT_vs_yCM_pp", "#pi^{+} v_{3};y-y_{mid};p_{T} (GeV/c)", 44, -2.2, 2.2, 10, 0.0, 2.0);
  TProfile2D *p2_vn_pT_vs_yCM_pm = new TProfile2D("p2_vn_pT_vs_yCM_pm", "#pi^{-} v_{3};y-y_{mid};p_{T} (GeV/c)", 44, -2.2, 2.2, 10, 0.0, 2.0);
  TProfile2D *p2_vn_pT_vs_yCM_pr = new TProfile2D("p2_vn_pT_vs_yCM_pr", "Proton v_{3};y-y_{mid};p_{T} (GeV/c)",  44, -2.2, 2.2, 10, 0.0, 2.5);
  ////

  TProfile2D *p2_vn_KT_cent_pp = new TProfile2D("p2_vn_KT_cent_pp", "#pi^{+} v_{"+ORDER_N_STR+"};Centrality;m_{T}-m_{0}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 10, 0, 2);
  TProfile2D *p2_vn_KT_cent_pm = new TProfile2D("p2_vn_KT_cent_pm", "#pi^{-} v_{"+ORDER_N_STR+"};Centrality;m_{T}-m_{0}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 10, 0, 2);
  TProfile2D *p2_vn_KT_cent_kp = new TProfile2D("p2_vn_KT_cent_kp", "K^{+} v_{"+ORDER_N_STR+"};Centrality;m_{T}-m_{0}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 10, 0, 2);
  TProfile2D *p2_vn_KT_cent_km = new TProfile2D("p2_vn_KT_cent_km", "K^{-} v_{"+ORDER_N_STR+"};Centrality;m_{T}-m_{0}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 10, 0, 2);
  TProfile2D *p2_vn_KT_cent_pr = new TProfile2D("p2_vn_KT_cent_pr", "Proton v_{"+ORDER_N_STR+"};Centrality;m_{T}-m_{0}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 10, 0, 2);
  TProfile2D *p2_vn_KT_cent_pr_alt = new TProfile2D("p2_vn_KT_cent_pr_alt", "Proton v_{"+ORDER_N_STR+"};Centrality;m_{T}-m_{0}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 10, 0, 2);
  TProfile2D *p2_vn_KT_cent_de = new TProfile2D("p2_vn_KT_cent_de", "Deuteron v_{"+ORDER_N_STR+"};Centrality;m_{T}-m_{0}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 10, 0, 2);
  TProfile2D *p2_vn_KT_cent_tr = new TProfile2D("p2_vn_KT_cent_tr", "Triton v_{"+ORDER_N_STR+"};Centrality;m_{T}-m_{0}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 10, 0, 2);
  TProfile2D *p2_vn_KT_cent_he3 = new TProfile2D("p2_vn_KT_cent_he3", "Helium-3 v_{"+ORDER_N_STR+"};Centrality;m_{T}-m_{0}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 10, 0, 2);
  TProfile2D *p2_vn_KT_cent_he4 = new TProfile2D("p2_vn_KT_cent_he4", "Helium-4 v_{"+ORDER_N_STR+"};Centrality;m_{T}-m_{0}", CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS, 10, 0, 2);

  // Profiles for resolution terms
  TProfile *p_TpcAB = new TProfile("p_TpcAB","TPC A-B Correlations;Centrality;<cos("+ORDER_N_STR+"(#psi^{TPC,A}_{"+ORDER_M_STR+"}-#psi^{TPC,B}_{"+ORDER_M_STR+"}))>",
				   CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS);

  TProfile *p_TpcAEpdA = new TProfile("p_TpcAEpdA","TPC A EPD A Correlations;Centrality;<cos("+ORDER_N_STR+"(#psi^{TPC,A}_{"+ORDER_M_STR+"}-#psi^{EPD,A}_{"+ORDER_M_STR+"}))>", 
				      CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS);
  TProfile *p_TpcAEpdB = new TProfile("p_TpcAEpdB","TPC A EPD B Correlations;Centrality;<cos("+ORDER_N_STR+"(#psi^{TPC,A}_{"+ORDER_M_STR+"}-#psi^{EPD,B}_{"+ORDER_M_STR+"}))>",
				      CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS);

  TProfile *p_TpcBEpdA = new TProfile("p_TpcBEpdA","TPC B EPD A Correlations;Centrality;<cos("+ORDER_N_STR+"(#psi^{TPC,B}_{"+ORDER_M_STR+"}-#psi^{EPD,A}_{"+ORDER_M_STR+"}))>",
				      CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS);
  TProfile *p_TpcBEpdB = new TProfile("p_TpcBEpdB","TPC B EPD B Correlations;Centrality;<cos("+ORDER_N_STR+"(#psi^{TPC,B}_{"+ORDER_M_STR+"}-#psi^{EPD,B}_{"+ORDER_M_STR+"}))>",
				      CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS);

  TProfile *p_EpdAEpdB = new TProfile("p_EpdAEpdB","EPD A EPD B Correlations;Centrality;<cos("+ORDER_N_STR+"(#psi^{EPD,A}_{"+ORDER_M_STR+"}-#psi^{EPD,B}_{"+ORDER_M_STR+"}))>", 
				      CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS);
  ////

  tempBins1      = (configs.fixed_target) ? 400 : 800;
  tempLowBound1  = (configs.fixed_target) ? -6.0 : -6.0;
  tempHighBound1 = (configs.fixed_target) ? -2.0 : 6.0;
  TProfile2D *p2_pp_vs_eta = new TProfile2D("p2_pp_vs_eta","<TnMIP> for Supersectors vs #eta;#eta;Supersector", tempBins1, tempLowBound1, tempHighBound1, 12, 0.5, 12.5);

  TH2D *h2_ring_vs_eta = new TH2D("h2_ring_vs_eta","EPD East Ring vs #eta;#eta;Ring", 500, -6.0, -1.0, 16, 0.5, 16.5);

  TH2D *h2_trans_vtx = new TH2D("h2_trans_vtx","Primary Vertex after V_{z} Cut;x (cm);y (cm)", 500, -5, 5, 500, -5, 5);
  TH2D *h2_trans_vtx_cut = new TH2D("h2_trans_vtx_cut","Final Primary Vertices;x (cm);y (cm)", 500, -5, 5, 500, -5, 5);

  TH2D *h2_refmult_vs_trackmult = (TH2D*)inputFile->Get("h2_refmult_vs_trackmult");
  TH2D *h2_tofmult_vs_trackmult = (TH2D*)inputFile->Get("h2_tofmult_vs_trackmult");
  TH2D *h2_tofmult_vs_refmult   = (TH2D*)inputFile->Get("h2_tofmult_vs_refmult");

  TH2D *h2_hits_vs_cent_EpdA = new TH2D("h2_nHits_vs_cent_EpdA", "EPD A;Centrality;Hits", CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS, 50, 0, 50);
  TH2D *h2_hits_vs_cent_EpdB = new TH2D("h2_nHits_vs_cent_EpdB", "EPD B;Centrality;Hits", CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS, 50, 0, 50);
  TH2D *h2_hits_vs_cent_TpcB = new TH2D("h2_nHits_vs_cent_TpcB", "TPC B;Centrality;Hits", CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS, 50, 0, 50);

  TH2D *h2_dEdx_vs_qp_id_pr = new TH2D("h2_dEdx_vs_qp_id_pr", ";|p| (GeV/c);dE/dx (keV/cm)", 25, 0.0, 2.5, 500, 0.0, 20.0);
  TH2D *h2_dEdx_vs_qp_id_pr_alt = new TH2D("h2_dEdx_vs_qp_id_pr_alt", ";|p| (GeV/c);dE/dx (keV/cm)", 25, 0.0, 2.5, 500, 0.0, 20.0);
  TH2D *h2_dEdx_vs_qp_id_de = new TH2D("h2_dEdx_vs_qp_id_de", ";|p| (GeV/c);dE/dx (keV/cm)", 25, 0.0, 2.5, 500, 0.0, 20.0);
  TH2D *h2_dEdx_vs_qp_id_tr = new TH2D("h2_dEdx_vs_qp_id_tr", ";|p| (GeV/c);dE/dx (keV/cm)", 25, 0.0, 2.5, 500, 0.0, 20.0);
  TH2D *h2_dEdx_vs_qp_id_he3 = new TH2D("h2_dEdx_vs_qp_id_he3", ";|p| (GeV/c);dE/dx (keV/cm)", 25, 0.0, 2.5, 500, 0.0, 20.0);
  TH2D *h2_dEdx_vs_qp_id_he4 = new TH2D("h2_dEdx_vs_qp_id_he4", ";|p| (GeV/c);dE/dx (keV/cm)", 25, 0.0, 2.5, 500, 0.0, 20.0);

  TH2D *h2_nSigp_vs_mom = new TH2D("h2_nSigp_vs_mom", ";|p| (GeV/c);n#sigma_{p}", 60, 0.0, 6.0, 600, -3.0, 3.0);
  TH2D *h2_zd_vs_mom = new TH2D("h2_zd_vs_mom", ";|p| (GeV/c);z_{d}", 60, 0.0, 6.0, 140, -0.7, 0.7);
  TH2D *h2_zd_vs_mom_check = new TH2D("h2_zd_vs_mom_check", ";|p| (GeV/c);z_{d}", 60, 0.0, 6.0, 140, -0.7, 0.7);
  TH2D *h2_zt_vs_mom = new TH2D("h2_zt_vs_mom", ";|p| (GeV/c);z_{t}", 60, 0.0, 6.0, 280, -1.4, 1.4);
  TH2D *h2_zt_vs_mom_check = new TH2D("h2_zt_vs_mom_check", ";|p| (GeV/c);z_{t}", 60, 0.0, 6.0, 280, -1.4, 1.4);
  TH2D *h2_zHe3_vs_mom = new TH2D("h2_zHe3_vs_mom", ";|p| (GeV/c);z_{He3}", 60, 0.0, 6.0, 2000, -10., 10.);
  TH2D *h2_zHe3_vs_mom_yMid = new TH2D("h2_zHe3_vs_mom_yMid", ";|p| (GeV/c);z_{He3}", 60, 0.0, 6.0, 2000, -10., 10.);
  TH2D *h2_zHe3_vs_mom_yFor = new TH2D("h2_zHe3_vs_mom_yFor", ";|p| (GeV/c);z_{He3}", 60, 0.0, 6.0, 2000, -10., 10.);
  TH2D *h2_zHe4_vs_mom = new TH2D("h2_zHe4_vs_mom", ";|p| (GeV/c);z_{He4}", 60, 0.0, 6.0, 2000, -10., 10.);
  TH2D *h2_zHe3_vs_mom_m2cut = new TH2D("h2_zHe3_vs_mom_m2cut", ";|p| (GeV/c);z_{He3}", 60, 0.0, 6.0, 2000, -10., 10.);
  TH2D *h2_zHe4_vs_mom_m2cut = new TH2D("h2_zHe4_vs_mom_m2cut", ";|p| (GeV/c);z_{He4}", 60, 0.0, 6.0, 2000, -10., 10.);
  

  tempBins1      = (configs.fixed_target) ?  300 :  600;
  tempLowBound1  = (configs.fixed_target) ? -2.2 : -2.5;
  tempHighBound1 = (configs.fixed_target) ?  0.2 :  2.5;
  TH2D *h2_phi_vs_eta_TPC = new TH2D("h2_phi_vs_eta_TPC", "TPC;#eta;#phi", tempBins1, tempLowBound1, tempHighBound1, 300, -4, 4);

  tempBins1      = (configs.fixed_target) ?  300 :  600;
  tempLowBound1  = (configs.fixed_target) ? -6.0 : -6.0;
  tempHighBound1 = (configs.fixed_target) ? -2.5 :  6.0;
  TH2D *h2_phi_vs_eta_EPD = new TH2D("h2_phi_vs_eta_EPD", "EPD;#eta;#phi", tempBins1, tempLowBound1, tempHighBound1, 300, -4, 4);


  if (configs.sqrt_s_NN == 3.0 || configs.sqrt_s_NN == 3.2 || configs.sqrt_s_NN == 3.5 || configs.sqrt_s_NN == 3.9 || configs.sqrt_s_NN == 4.5)
    {
      tempBins1 = 300;
      tempLowBound1 = -1.2;
      tempHighBound1 = 1.2;
      tempBins2 = 300;
      tempLowBound2  = 0.0;
      tempHighBound2 = 2.5;
    }
  else if (configs.sqrt_s_NN == 7.2)
    {
      tempBins1 = 300;
      tempLowBound1 = -0.2;
      tempHighBound1 = 2.2;
      tempBins2 = 300;
      tempLowBound2  = 0.0;
      tempHighBound2 = 2.5;
    }
  else if (configs.sqrt_s_NN == 7.7)
    {
      tempBins1 = 300;
      tempLowBound1 = -0.2;
      tempHighBound1 = 2.2;
      tempBins2 = 300;
      tempLowBound2  = 0.0;
      tempHighBound2 = 2.5;
    }
  else if (configs.sqrt_s_NN == 19.6)
    {
      tempBins1 = 400;
      tempLowBound1 = -2.0;
      tempHighBound1 = 2.0;
      tempBins2 = 500;
      tempLowBound2  = 0.0;
      tempHighBound2 = 5.0;
    }
  else
    {
      tempBins1 = 0;
      tempLowBound1 = 0.0;
      tempHighBound1 = 0.0;
      tempBins2 = 0;
      tempLowBound2  = 0.0;
      tempHighBound2 = 0.0;
    }
  TH2D *h2_pToverA_vs_yCM_de = 
    new TH2D("h2_pToverA_vs_yCM_de","Deuteron;y-y_{mid};p_{T}/A (GeV/c)",tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pToverA_vs_yCM_tr = 
    new TH2D("h2_pToverA_vs_yCM_tr", "Triton;y-y_{mid};p_{T}/A (GeV/c)", tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pToverA_vs_yCM_he3 = 
    new TH2D("h2_pToverA_vs_yCM_he3","Helium-3;y-y_{mid};p_{T}/A (GeV/c)",tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_pToverA_vs_yCM_he4 = 
    new TH2D("h2_pToverA_vs_yCM_he4","Helium-4;y-y_{mid};p_{T}/A (GeV/c)",tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);

  TH2D *h2_KToverA_vs_yCM_pr = 
    new TH2D("h2_KToverA_vs_yCM_pr", "Proton;y-y_{mid};m_{T}-m_{0} (GeV)",  tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_KToverA_vs_yCM_de = 
    new TH2D("h2_KToverA_vs_yCM_de", "Deuteron;y-y_{mid};m_{T}-m_{0} (GeV)",tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_KToverA_vs_yCM_tr = 
    new TH2D("h2_KToverA_vs_yCM_tr", "Triton;y-y_{mid};m_{T}-m_{0} (GeV)",  tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_KToverA_vs_yCM_he3 = 
    new TH2D("h2_KToverA_vs_yCM_he3", "Helium-3;y-y_{mid};m_{T}-m_{0} (GeV)",tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  TH2D *h2_KToverA_vs_yCM_he4 = 
    new TH2D("h2_KToverA_vs_yCM_he4", "Helium-4;y-y_{mid};m_{T}-m_{0} (GeV)",tempBins1, tempLowBound1, tempHighBound1, tempBins2, tempLowBound2, tempHighBound2);
  /////

  // Here the name refers to the eta region that will be displayed/searched using the event plane angle from the opposite region
  tempBins1      = (configs.fixed_target) ?  50  :  100;
  tempLowBound1  = (configs.fixed_target) ? -2.0 : -2.3;
  tempHighBound1 = (configs.fixed_target) ?  0.0 :  2.3;
  TProfile2D *h2_vnScanTpc = new TProfile2D("h2_vnScanTpc", "<cos("+ORDER_N_STR+"(#phi^{TPC} - #psi^{EPD}_{"+ORDER_M_STR+"}))>;#eta;Centrality (%)", 
					    tempBins1, tempLowBound1, tempHighBound1, CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS);
  TProfile2D *h2_vnScanTpcEpdA = new TProfile2D("h2_vnScanTpcEpdA", "<cos("+ORDER_N_STR+"(#phi^{TPC} - #psi^{EPD,A}_{"+ORDER_M_STR+"}))>;#eta;Centrality (%)", 
						tempBins1, tempLowBound1, tempHighBound1, CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS);
  TProfile2D *h2_vnScanTpcEpdB = new TProfile2D("h2_vnScanTpcEpdB", "<cos("+ORDER_N_STR+"(#phi^{TPC} - #psi^{EPD,B}_{"+ORDER_M_STR+"}))>;#eta;Centrality (%)", 
						tempBins1, tempLowBound1, tempHighBound1, CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS);
  TProfile2D *h2_vnScanEpd = new TProfile2D("h2_vnScanEpd", "<cos("+ORDER_N_STR+"(#phi^{EPD} - #psi^{TPC}_{"+ORDER_M_STR+"}))>;#eta;Centrality (%)", 
					    50, -5.2, -2.3, CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS);
  TProfile2D *h2_vnScanEpdTpcA = new TProfile2D("h2_vnScanEpdTpcA", "<cos("+ORDER_N_STR+"(#phi^{EPD} - #psi^{TPC,A}_{"+ORDER_M_STR+"}))>;#eta;Centrality (%)", 
						50, -5.2, -2.3, CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS);
  TProfile2D *h2_vnScanEpdTpcB = new TProfile2D("h2_vnScanEpdTpcB", "<cos("+ORDER_N_STR+"(#phi^{EPD} - #psi^{TPC,B}_{"+ORDER_M_STR+"}))>;#eta;Centrality (%)", 
						50, -5.2, -2.3, CENT_BINS, FIRST_CENT, FIRST_CENT + CENT_BINS);
  h2_vnScanTpc->SetStats(0);
  h2_vnScanTpcEpdA->SetStats(0);
  h2_vnScanTpcEpdB->SetStats(0);
  h2_vnScanEpd->SetStats(0);
  h2_vnScanEpdTpcA->SetStats(0);
  h2_vnScanEpdTpcB->SetStats(0);
  ////

  // Raw correlations between event planes
  TH2D *h2_psiEpdATpcA = new TH2D("h2_psiEpdATpcA", "#psi^{EPD,A} vs #psi^{TPC,A} (Order "+ORDER_M_STR+");#psi^{TPC}_{A};#psi^{EPD}_{A}", 
				  200, -PSI_BOUNDS, PSI_BOUNDS, 200, -PSI_BOUNDS, PSI_BOUNDS);
  TH2D *h2_psiEpdBTpcA = new TH2D("h2_psiEpdBTpcA", "#psi^{EPD,B} vs #psi^{TPC,A} (Order "+ORDER_M_STR+");#psi^{TPC}_{A};#psi^{EPD}_{B}", 
				  200, -PSI_BOUNDS, PSI_BOUNDS, 200, -PSI_BOUNDS, PSI_BOUNDS);

  TH2D *h2_psiEpdATpcB = new TH2D("h2_psiEpdATpcB", "#psi^{EPD,A} vs #psi^{TPC,B} (Order "+ORDER_M_STR+");#psi^{TPC}_{B};#psi^{EPD}_{A}", 
				  200, -PSI_BOUNDS, PSI_BOUNDS, 200, -PSI_BOUNDS, PSI_BOUNDS);
  TH2D *h2_psiEpdBTpcB = new TH2D("h2_psiEpdBTpcB", "#psi^{EPD,B} vs #psi^{TPC,B} (Order "+ORDER_M_STR+");#psi^{TPC}_{B};#psi^{EPD}_{B}", 
				  200, -PSI_BOUNDS, PSI_BOUNDS, 200, -PSI_BOUNDS, PSI_BOUNDS);

  TH2D *h2_psiTpcATpcB = new TH2D("h2_psiTpcATpcB", "#psi^{TPC,A} vs #psi^{TPC,B} (Order "+ORDER_M_STR+");#psi^{TPC}_{B};#psi^{TPC}_{A}", 
				  200, -PSI_BOUNDS, PSI_BOUNDS, 200, -PSI_BOUNDS, PSI_BOUNDS);

  TH2D *h2_psiEpdAEpdB = new TH2D("h2_psiEpdAEpdB", "#psi^{EPD,A} vs #psi^{EPD,B} (Order "+ORDER_M_STR+");#psi^{EPD}_{B};#psi^{EPD}_{A}", 
				  200, -PSI_BOUNDS, PSI_BOUNDS, 200, -PSI_BOUNDS, PSI_BOUNDS);
  ////


  TH1D *h_XnTpc  = new TH1D("h_XnTpc", "X_n Distribution (TPC);X_n;Events",    250, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_YnTpc  = new TH1D("h_YnTpc", "Y_n Distribution (TPC);Y_n;Events",    250, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_XnTpcA = new TH1D("h_XnTpcA", "X_n Distribution (TPC A);X_n;Events", 250, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_YnTpcA = new TH1D("h_YnTpcA", "Y_n Distribution (TPC A);Y_n;Events", 250, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_XnTpcB = new TH1D("h_XnTpcB", "X_n Distribution (TPC B);X_n;Events", 250, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_YnTpcB = new TH1D("h_YnTpcB", "Y_n Distribution (TPC B);Y_n;Events", 250, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_XnEpd  = new TH1D("h_XnEpd", "X_n Distribution (EPD);X_n;Events",    250, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_YnEpd  = new TH1D("h_YnEpd", "Y_n Distribution (EPD);Y_n;Events",    250, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_XnEpdA = new TH1D("h_XnEpdA", "X_n Distribution (EPD A);X_n;Events", 250, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_YnEpdA = new TH1D("h_YnEpdA", "Y_n Distribution (EPD A);Y_n;Events", 250, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_XnEpdB = new TH1D("h_XnEpdB", "X_n Distribution (EPD B);X_n;Events", 250, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_YnEpdB = new TH1D("h_YnEpdB", "Y_n Distribution (EPD B);Y_n;Events", 250, -Q_BOUNDS, Q_BOUNDS);

  // CORRECTION HISTOGRAMS
  TProfile *p_sinAvgsTpc  = new TProfile("p_sinAvgsTpc", "Sin Averages (TPC);j (Correction term);<sin(jn#psi^{TPC}_{n})>",      configs.shift_terms, 1, configs.shift_terms + 1);
  TProfile *p_cosAvgsTpc  = new TProfile("p_cosAvgsTpc", "Cos Averages (TPC);j (Correction term);<sin(jn#psi^{TPC}_{n})>",      configs.shift_terms, 1, configs.shift_terms + 1);
  TProfile *p_sinAvgsTpcA = new TProfile("p_sinAvgsTpcA", "Sin Averages (TPC A);j (Correction term);<sin(jn#psi^{TPC,A}_{n})>", configs.shift_terms, 1, configs.shift_terms + 1);
  TProfile *p_cosAvgsTpcA = new TProfile("p_cosAvgsTpcA", "Cos Averages (TPC A);j (Correction term);<sin(jn#psi^{TPC,A}_{n})>", configs.shift_terms, 1, configs.shift_terms + 1);
  TProfile *p_sinAvgsTpcB = new TProfile("p_sinAvgsTpcB", "Sin Averages (TPC B);j (Correction term);<sin(jn#psi^{TPC,B}_{n})>", configs.shift_terms, 1, configs.shift_terms + 1);
  TProfile *p_cosAvgsTpcB = new TProfile("p_cosAvgsTpcB", "Cos Averages (TPC B);j (Correction term);<sin(jn#psi^{TPC,B}_{n})>", configs.shift_terms, 1, configs.shift_terms + 1);
  TProfile *p_sinAvgsEpd  = new TProfile("p_sinAvgsEpd", "Sin Averages (EPD);j (Correction term);<sin(jn#psi^{EPD}_{n})>",      configs.shift_terms, 1, configs.shift_terms + 1);
  TProfile *p_cosAvgsEpd  = new TProfile("p_cosAvgsEpd", "Cos Averages (EPD);j (Correction term);<sin(jn#psi^{EPD}_{n})>",      configs.shift_terms, 1, configs.shift_terms + 1);
  TProfile *p_sinAvgsEpdA = new TProfile("p_sinAvgsEpdA", "Sin Averages (EPD A);j (Correction term);<sin(jn#psi^{EPD,A}_{n})>", configs.shift_terms, 1, configs.shift_terms + 1);
  TProfile *p_cosAvgsEpdA = new TProfile("p_cosAvgsEpdA", "Cos Averages (EPD A);j (Correction term);<sin(jn#psi^{EPD,A}_{n})>", configs.shift_terms, 1, configs.shift_terms + 1);
  TProfile *p_sinAvgsEpdB = new TProfile("p_sinAvgsEpdB", "Sin Averages (EPD B);j (Correction term);<sin(jn#psi^{EPD,B}_{n})>", configs.shift_terms, 1, configs.shift_terms + 1);
  TProfile *p_cosAvgsEpdB = new TProfile("p_cosAvgsEpdB", "Cos Averages (EPD B);j (Correction term);<sin(jn#psi^{EPD,B}_{n})>", configs.shift_terms, 1, configs.shift_terms + 1);

  // RECENTERED (RC) HISTOGRAMS
  TH1D *h_XnTpc_RC  = new TH1D("h_XnTpc_RC", "Re-centered X_n Distribution (TPC);X_n;Events",    200, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_YnTpc_RC  = new TH1D("h_YnTpc_RC", "Re-centered Y_n Distribution (TPC);Y_n;Events",    200, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_XnTpcA_RC = new TH1D("h_XnTpcA_RC", "Re-centered X_n Distribution (TPC A);X_n;Events", 200, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_YnTpcA_RC = new TH1D("h_YnTpcA_RC", "Re-centered Y_n Distribution (TPC A);Y_n;Events", 200, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_XnTpcB_RC = new TH1D("h_XnTpcB_RC", "Re-centered X_n Distribution (TPC B);X_n;Events", 200, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_YnTpcB_RC = new TH1D("h_YnTpcB_RC", "Re-centered Y_n Distribution (TPC B);Y_n;Events", 200, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_XnEpd_RC  = new TH1D("h_XnEpd_RC", "Re-centered X_n Distribution (EPD);X_n;Events",    200, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_YnEpd_RC  = new TH1D("h_YnEpd_RC", "Re-centered Y_n Distribution (EPD);Y_n;Events",    200, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_XnEpdA_RC = new TH1D("h_XnEpdA_RC", "Re-centered X_n Distribution (EPD A);X_n;Events", 200, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_YnEpdA_RC = new TH1D("h_YnEpdA_RC", "Re-centered Y_n Distribution (EPD A);Y_n;Events", 200, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_XnEpdB_RC = new TH1D("h_XnEpdB_RC", "Re-centered X_n Distribution (EPD B);X_n;Events", 200, -Q_BOUNDS, Q_BOUNDS);
  TH1D *h_YnEpdB_RC = new TH1D("h_YnEpdB_RC", "Re-centered Y_n Distribution (EPD B);Y_n;Events", 200, -Q_BOUNDS, Q_BOUNDS);

  TH1D *h_psiTpc_RC  = new TH1D("h_psiTpc_RC", "Re-centered Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events",    400, -PSI_BOUNDS, PSI_BOUNDS);
  TH1D *h_psiTpcA_RC = new TH1D("h_psiTpcA_RC", "Re-centered Event Plane Angles (m = "+ORDER_M_STR+", TPC A);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS);
  TH1D *h_psiTpcB_RC = new TH1D("h_psiTpcB_RC", "Re-centered Event Plane Angles (m = "+ORDER_M_STR+", TPC B);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS);
  TH1D *h_psiEpd_RC  = new TH1D("h_psiEpd_RC", "Re-centered Event Plane Angles (m = "+ORDER_M_STR+", EPD);#psi_{"+ORDER_M_STR+"};Events",    400, -PSI_BOUNDS, PSI_BOUNDS);
  TH1D *h_psiEpdA_RC = new TH1D("h_psiEpdA_RC", "Re-centered Event Plane Angles (m = "+ORDER_M_STR+", EPD A);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS);
  TH1D *h_psiEpdB_RC = new TH1D("h_psiEpdB_RC", "Re-centered Event Plane Angles (m = "+ORDER_M_STR+", EPD B);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS);

  TH2D *h2_psiTpc_RC_Cent16   = new TH2D("h2_psiTpc_RC_Cent16", "Re-centered Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS); 
  TH2D *h2_psiTpcA_RC_Cent16  = new TH2D("h2_psiTpcA_RC_Cent16", "Re-centered Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS); 
  TH2D *h2_psiTpcB_RC_Cent16  = new TH2D("h2_psiTpcB_RC_Cent16", "Re-centered Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS); 
  TH2D *h2_psiEpd_RC_Cent16   = new TH2D("h2_psiEpd_RC_Cent16", "Re-centered Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);  
  TH2D *h2_psiEpdA_RC_Cent16  = new TH2D("h2_psiEpdA_RC_Cent16", "Re-centered Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS); 
  TH2D *h2_psiEpdB_RC_Cent16  = new TH2D("h2_psiEpdB_RC_Cent16", "Re-centered Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS); 

  // RECENTERED AND SHIFTED HISTOGRAMS
  TH1D *h_psiTpc_FLAT  = new TH1D("h_psiTpc_FLAT", "Flattened Event Plane Angle (TPC, order "+ORDER_M_STR+");#psi_{"+ORDER_M_STR+"};Events",    400, -PSI_BOUNDS, PSI_BOUNDS);      
  TH1D *h_psiTpcA_FLAT = new TH1D("h_psiTpcA_FLAT", "Flattened Event Plane Angle (TPC A, order "+ORDER_M_STR+");#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS);
  TH1D *h_psiTpcB_FLAT = new TH1D("h_psiTpcB_FLAT", "Flattened Event Plane Angle (TPC B, order "+ORDER_M_STR+");#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS);
  TH1D *h_psiEpd_FLAT  = new TH1D("h_psiEpd_FLAT", "Flattened Event Plane Angle (EPD, order "+ORDER_M_STR+");#psi_{"+ORDER_M_STR+"};Events",    400, -PSI_BOUNDS, PSI_BOUNDS);
  TH1D *h_psiEpdA_FLAT = new TH1D("h_psiEpdA_FLAT", "Flattened Event Plane Angle (EPD A, order "+ORDER_M_STR+");#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS);
  TH1D *h_psiEpdB_FLAT = new TH1D("h_psiEpdB_FLAT", "Flattened Event Plane Angle (EPD B, order "+ORDER_M_STR+");#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS);

  TH2D *h2_psiTpc_FLAT_Cent16   = new TH2D("h2_psiTpc_FLAT_Cent16", "Flattened Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS); 
  TH2D *h2_psiTpcA_FLAT_Cent16  = new TH2D("h2_psiTpcA_FLAT_Cent16", "Flattened Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS); 
  TH2D *h2_psiTpcB_FLAT_Cent16  = new TH2D("h2_psiTpcB_FLAT_Cent16", "Flattened Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS); 
  TH2D *h2_psiEpd_FLAT_Cent16   = new TH2D("h2_psiEpd_FLAT_Cent16", "Flattened Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS);  
  TH2D *h2_psiEpdA_FLAT_Cent16  = new TH2D("h2_psiEpdA_FLAT_Cent16", "Flattened Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS); 
  TH2D *h2_psiEpdB_FLAT_Cent16  = new TH2D("h2_psiEpdB_FLAT_Cent16", "Flattened Event Plane Angles (m = "+ORDER_M_STR+", TPC);#psi_{"+ORDER_M_STR+"};Events", 400, -PSI_BOUNDS, PSI_BOUNDS, CENT_BINS, FIRST_CENT, FIRST_CENT+CENT_BINS); 
  
  FlowUtils::Event eventInfo;        // These hold info for each event
  FlowUtils::Particle particleInfo;  // These hold info for each track/hit
  StEpdGeom *epdGeom = new StEpdGeom();

  //StPileupUtil* mPileupTool;
  //mPileupTool = new StPileupUtil();

  //std::cout << "test 4" << std::endl;

  // EVENT LOOP
  Int_t events2read = tree->GetEntries();
  std::cout << "Setup complete, beginning analysis on " << events2read << " events..." << std::endl;
  double d_deEvents = 0;
  double d_allEvents = 0;
  Int_t eventID = -1;
  for (Long64_t ievent = 0; ievent < events2read; ievent++)
    {

      eventInfo.reset();
      //std::cout << ievent << " ievent" << std::endl;
      //std::cout << eventID << " eventID" << std::endl;
      //std::cout << i_eventID << " i_eventID" << std::endl;

      tree->GetEntry(ievent);

      // At this point, all bad runs and bad trigger events are removed by TreeMaker.
      // Now check event vertex
      TVector3 pVtx(f_xvtx, f_yvtx, f_zvtx);
      Double_t d_rvtx = (configs.fixed_target) ? TMath::Sqrt(f_xvtx * f_xvtx + (f_yvtx + 2) * (f_yvtx + 2)) : TMath::Sqrt(f_xvtx * f_xvtx + f_yvtx * f_yvtx);
      
      h_zvtx->Fill(f_zvtx); // All events that pass minbias and wide TreeMaker cuts. Possibly move this past Vz cut.

      Bool_t goodVertexZ = (f_zvtx > configs.z_vtx_low && f_zvtx < configs.z_vtx_high);
      if (!goodVertexZ) continue;
      h_eventCheck->Fill(3);    // Count # of events after Vz cut
      h2_trans_vtx->Fill(pVtx.X(),pVtx.Y()); // transverse vtx position after z cut

      Bool_t goodVertexR = (d_rvtx < configs.r_vtx);
      if(!goodVertexR) continue;
      h_eventCheck->Fill(4);    // Count # of events after Vr cut
      h2_trans_vtx_cut->Fill(pVtx.X(),pVtx.Y()); // transverse vtx position after z cut and Vr cut

      eventInfo.centID = i_centrality;
      if (i_centrality == -99) continue;  // Remove undefined events
      h_eventCheck->Fill(5); // Count # of events after centrality cut
      h_centralities->Fill(i_centrality);
      int mCentrality = Cent16toCent9(i_centrality);
      Int_t Cent=0;             

      if(mCentrality < 2 )Cent = -1 ;//return kStOK;
      else if(mCentrality < 4 ) Cent=0;
      else if (mCentrality < 7) Cent=1;
      else if (mCentrality < 9) Cent=2;
      // TRACK LOOP OVER PRIMARY TRACKS
      //Int_t nTracks = (Int_t)i_trackNumber;
      //float mCentWeight = -1.0;  
      //if(m_hreweight)mCentWeight = m_hreweight->GetBinContent(nTracks);
      //std::cout << "mCentWeight = " << mCentWeight <<std::endl;


      //Double mCentWeight = 1.;
      
       


      //he3_eff = 1./mCentWeight;

      Double_t d_px;
      Double_t d_py;
      Double_t d_pz;
      Double_t d_pT;
      Double_t d_mom;
      Double_t d_eta;
      Double_t d_phi;
      Double_t d_DCA;
      Double_t d_nSigmaPi;
      Double_t d_nSigmaKa;
      Double_t d_nSigmaPr;
      Double_t d_tofBeta;
      Double_t d_EtofBeta;
      Double_t d_dEdx;
      Int_t i_nHits;
      Int_t i_nHitsFit;
      Int_t i_nHitsPoss;
      Int_t i_nHitsDedx;
      Short_t s_charge;

      Int_t N_pp = 0;
      Int_t N_pm = 0;
      Int_t N_kp = 0;
      Int_t N_km = 0;
      Int_t N_pr = 0;
      Int_t N_de = 0;
      Int_t N_tr = 0;
      Int_t N_he3 = 0;
      Int_t N_he4 = 0;


      // TRACK LOOP OVER PRIMARY TRACKS

      //std::cout << "test 4.1" << std::endl;
       Int_t nTracks = (Int_t)i_trackNumber;
       //std::cout << "nTracks: " << nTracks << std::endl; 
       //std::cout << "m_hreweight: " << m_hreweight << std::endl; 
       if(efficienciesFound && m_hreweight) mCentWeight  = m_hreweight->GetBinContent(nTracks);
       else mCentWeight = 1.;
       //mCentWeight = 1.;
       //he3_eff = 1.;
       de_eff = 1./mCentWeight;
       tr_eff = 1./mCentWeight;
       he3_eff = 1./mCentWeight;
       he4_eff = 1./mCentWeight;
       //he4_eff = 1./mCentWeight;
       //std::cout << "i_trackNumber: " << i_trackNumber << std::endl;
       //std::cout << "1./mCentWeight: " << 1./mCentWeight << std::endl;
       //std::cout << "he3_eff mCent: " << he3_eff << std::endl;
       //std::cout << "he4_eff: " << he4_eff << std::endl;
      if(mCentrality>1){
      hCent9->Fill(mCentrality, mCentWeight);
      hCent9W->Fill(mCentrality, mCentWeight);
      hCent3->Fill(Cent, mCentWeight);
      }
	  // StPileupUtil cut
      int m_nch = 0;
      for(Int_t iTrk = 0; iTrk < nTracks; iTrk++)
	{ // TPC track loop
      //std::cout << "test 4.1.1" << std::endl;
	  particleInfo.reset();

	  eventInfo.primTracks++;
	  h_trackCheck->Fill(0);  // Only event cuts

	  d_px  = Px[iTrk];
	  d_py  = Py[iTrk];
	  d_pz  = Pz[iTrk];
	  d_phi = FlowUtils::phi(Px[iTrk], Py[iTrk]);
	  d_eta = FlowUtils::pseudorapidity(Px[iTrk], Py[iTrk], Pz[iTrk]);
	  d_pT  = FlowUtils::transMomentum(Px[iTrk], Py[iTrk]);
	  d_mom = FlowUtils::totalMomentum(Px[iTrk], Py[iTrk], Pz[iTrk]);
	  s_charge = charge[iTrk];
	  d_DCA = DCA[iTrk];
	  d_nSigmaPi = nSigmaPi[iTrk];
	  d_nSigmaKa = nSigmaKa[iTrk];
	  d_nSigmaPr = nSigmaPr[iTrk];
	  d_tofBeta = tofBeta[iTrk];
	  d_EtofBeta = EtofBeta[iTrk];
	  d_dEdx = dEdx[iTrk];
	  i_nHits = nHits[iTrk];
	  i_nHitsFit = nHitsFit[iTrk];
	  i_nHitsPoss = nHitsPoss[iTrk];
	  i_nHitsDedx = nHitsDedx[iTrk];


	  h_nhits->Fill(i_nHits);
	  h_nhitsFit->Fill(i_nHitsFit);
	  h_nhitsPoss->Fill(i_nHitsPoss);
	  h_nhits_ratio->Fill((double)i_nHitsFit/(double)i_nHitsPoss);
	  h_nhits_dEdx->Fill(i_nHitsDedx);
	  h_DCA->Fill(d_DCA);
          //std::cout << "test 4.1.1.1" << std::endl;

	  // StPileupUtil cut
          //bool StPileupUtil::isGoodTrackNch(const StPicoTrack *ptrk, const StPicoDst* pico) const {
          
             if (!(
                (d_eta < -1.5 || -0.5 < d_eta) 
             || (fabs(d_DCA)>3.0 )             
             || (i_nHitsFit < 15 )             
             || ((double)i_nHitsFit/(double)i_nHitsPoss < 0.52 )         
             || (d_tofBeta== -999.0)
		  )) m_nch++;                   
             //bool TofMatch = kFALSE;
             //int tofIndex = ptrk->bTofPidTraitsIndex();
             //StPicoBTofPidTraits* tofPidTraits;
             //if (tofIndex >= 0)   tofPidTraits = pico->btofPidTraits(tofIndex);
             //if (tofIndex >= 0 && tofPidTraits && tofPidTraits->btofMatchFlag() > 0)  TofMatch = kTRUE;
             //if (!TofMatch)                return false;
          
             //float beta = getTofBeta(ptrk, pico);
             //bool tofAvailable = !isnan(beta) && beta > 0;
          
             //return true;
          //}

	  //=========================================================
	  //          Track QA Cuts
	  //=========================================================
	  //bool b_bad_hits  = ( i_nHits < configs.nHits );
	  bool b_bad_hits  = ( i_nHits <= configs.nHits ); //follow the psn0770
	  bool b_bad_dEdx  = ( i_nHitsDedx <= configs.nHits_dEdx );
	  bool b_bad_ratio = ( ((double)i_nHitsFit / (double)i_nHitsPoss) <= configs.nHits_ratio );
	  bool b_bad_DCA   = ( d_DCA >= configs.dca );
          //std::cout << "test 4.1.1.2" << std::endl;

          //std::cout << b_bad_hits << " " << b_bad_dEdx <<" "<< b_bad_ratio <<" "<< b_bad_DCA << std::endl;
	  //std::cout << "itrack: " << iTrk << std::endl;
	  //std::cout << "nTracks: " << nTracks << std::endl;
	  if (b_bad_hits || b_bad_dEdx || b_bad_ratio || b_bad_DCA) continue;
          //std::cout << "test 4.1.1.3" << std::endl;
	  //=========================================================
	  //          End Track QA Cuts
	  //=========================================================
	  h_trackCheck->Fill(1); // After QA Cuts

	  h_phi->Fill(d_phi);
	  h_eta->Fill(d_eta);
	  h_pT->Fill(d_pT);
	  if (s_charge <= 1 && s_charge >= -1) h2_dEdx_vs_qp->Fill(s_charge * d_mom, d_dEdx);
	  if (s_charge == 2 || s_charge == -2) h2_dEdx_vs_qp_charge2->Fill(s_charge * d_mom, d_dEdx);
	  if (s_charge == 1) h2_dEdx_vs_qp_half->Fill(s_charge * d_mom, d_dEdx);

          //std::cout << "test 4.1.2" << std::endl;
	  // Get event planes from the TPC here before the TOF cut
	  if (s_charge != 0)
	    {
	      eventInfo.nTracksTpc++;

	      // TOF information here before full PID next
	      // d_tofBeta = -999.0 if it's not a TOF hit
	      //=========================================================
	      //          TOF Beta Cuts
	      //=========================================================
	      Double_t d_m2 = -999.0;
	      Bool_t tofTrack = (d_tofBeta != -999.0);

	      if (tofTrack)
		{
		  d_m2 = d_mom*d_mom*( (1.0 / (d_tofBeta*d_tofBeta)) - 1.0);		    
		  h_m2->Fill(d_m2);
		  h_tofBeta->Fill(d_tofBeta);		  
		  h2_beta_vs_qp->Fill(s_charge*d_mom, 1.0/d_tofBeta);
		  h2_m2_vs_qp->Fill(s_charge*d_mom, d_m2);

		}
	      //=========================================================
	      //          End TOF Beta Cuts
	      //=========================================================
	      
	      // ETOF information here before full PID next
	      // d_EtofBeta = -999.0 if it's not a TOF hit
	      //=========================================================
	      //          ETOF Beta Cuts
	      //=========================================================
	      Bool_t EtofTrack = (d_EtofBeta != -999.0);

	      if (EtofTrack)
		{
		  d_m2 = d_mom*d_mom*( (1.0 / (d_EtofBeta*d_EtofBeta)) - 1.0);		    
		  //h_m2->Fill(d_m2);
		  h_m2Etof->Fill(d_m2);
		  h_EtofBeta->Fill(d_EtofBeta);		  
		  h2_Etofbeta_vs_qp->Fill(s_charge*d_mom, 1.0/d_EtofBeta);
		  h2_m2Etof_vs_qp->Fill(s_charge*d_mom, d_m2);
		 
    		  d_tofBeta = d_EtofBeta; // test the eTofBeta
		  tofTrack = true; // test the tofTrack if the EtofTrack is true

		}
	      //=========================================================
	      //          End TOF Beta Cuts
	      //=========================================================
	      

	      particleInfo.phi = d_phi;
	      particleInfo.eta = d_eta;
	      particleInfo.pT  = d_pT;
	      particleInfo.mom = d_mom;
	      particleInfo.dEdx = d_dEdx;
	      particleInfo.M2 = d_m2;
	      particleInfo.weight = (configs.sqrt_s_NN == 7.2) ? 1.0/*TMath::Abs(d_eta-Y_MID)*/ : d_pT;

	      h2_phi_vs_eta_TPC->Fill(d_eta, d_phi);

	      eventInfo.incrementQvectorTPC(ODD_PLANE, ORDER_M, Y_MID, particleInfo.eta, particleInfo.phi, particleInfo.weight);

	      // TPC A
	      if (d_eta > configs.tpc_A_low_eta && d_eta < configs.tpc_A_high_eta)
		{
		  eventInfo.nTracksTpcA++;
		  particleInfo.isInTpcA = true;
		  eventInfo.incrementQvectorTPCA(ODD_PLANE, ORDER_M, Y_MID, particleInfo.eta, particleInfo.phi, particleInfo.weight);
		}
	      // TPC B
	      if (d_eta > configs.tpc_B_low_eta && d_eta < configs.tpc_B_high_eta)
		{
		  eventInfo.nTracksTpcB++;
		  particleInfo.isInTpcB = true;
		  eventInfo.incrementQvectorTPCB(ODD_PLANE, ORDER_M, Y_MID, particleInfo.eta, particleInfo.phi, particleInfo.weight);
		}
	      
	      


	      Double_t d_zDeuteron, d_zTriton, d_zHelium3, d_zAlpha;
	      if( configs.sqrt_s_NN == 3.0 )
	      {
	        d_zDeuteron = (s_charge == 1) ? CalculateZ(1, D_M0_DE, d_mom, d_dEdx) : -999.0;
	        d_zTriton   = (s_charge == 1) ? CalculateZ(1, D_M0_TR, d_mom, d_dEdx) : -999.0;
	        d_zHelium3  = (s_charge == 1) ? CalculateZ(2, D_M0_HE3, d_mom, d_dEdx) : -999.0;
	        d_zAlpha    = (s_charge == 1) ? CalculateZ(2, D_M0_HE4, d_mom, d_dEdx) : -999.0;
	      }
	      else if( configs.sqrt_s_NN == 3.2 )
	      {
	        d_zDeuteron = (s_charge == 1) ? CalculatedZ(d_mom, d_dEdx) : -999.0;
	        d_zTriton   = (s_charge == 1) ? CalculatetZ(d_mom, d_dEdx) : -999.0;
	        d_zHelium3  = (s_charge == 1) ? Calculate3HeZ(d_mom, d_dEdx) : -999.0;
	        d_zAlpha    = (s_charge == 1) ? Calculate4HeZ(d_mom, d_dEdx) : -999.0;
	      }
	      else if( configs.sqrt_s_NN == 7.7 )
	      {
	        d_zDeuteron = (s_charge == 1) ? CalculatedZ(d_mom, d_dEdx) : -999.0;
	        d_zTriton   = (s_charge == 1) ? CalculatetZ(d_mom, d_dEdx) : -999.0;
	        d_zHelium3  = (s_charge == 1) ? Calculate3HeZ(d_mom, d_dEdx) : -999.0;
	        d_zAlpha    = (s_charge == 1) ? Calculate4HeZ(d_mom, d_dEdx) : -999.0;
	      }
	      h_zTriton->Fill(d_zTriton);
	      h_zHelium3->Fill(d_zHelium3);
	      h_zHelium4->Fill(d_zAlpha);

              //if(s_charge == 1 && d_zHelium3 != -999.0)std::cout << "d_zHelium3 = "<< d_zHelium3 << "; d_zAlpha= "<< d_zAlpha << std::endl;
	      if (tofTrack && d_zHelium3 < 10 && d_zHelium3 > -10) { h_m2_alpha_he3->Fill(d_m2); }
	      if (tofTrack && d_zAlpha < 10 && d_zAlpha > -10) { h_m2_alpha_he3->Fill(d_m2); }

	      //=========================================================
	      //          PID Cuts
	      //=========================================================
	      Bool_t pion   = false;
	      Bool_t kaon   = false;
	      //Bool_t proton = (d_nSigmaPr > configs.nSig_pr_low) && (d_nSigmaPr < configs.nSig_pr_high) && (s_charge == 1);
	      Bool_t proton = (d_nSigmaPr > configs.nSig_pr_low) && (d_nSigmaPr < configs.nSig_pr_high) && (s_charge == 1) && d_mom <= 2.8
		      	      && tofTrack && d_m2 >= 0.8 && d_m2 <= 1.0; // BES-I PID psn0564
	//      Bool_t proton = (
	//		      (d_nSigmaPr > configs.nSig_pr_low) && (d_nSigmaPr < configs.nSig_pr_high) && (s_charge == 1) && d_mom < 2.0
	//		      ) ||
	//	      (
	//		      (d_nSigmaPr > configs.nSig_pr_low) && (d_nSigmaPr < configs.nSig_pr_high) && (s_charge == 1) 
	//		      && d_mom >= 2.0 
	//		      && tofTrack && d_m2 > 0.6 && d_m2 < 1.2
	//	       );
	      
	      
	      //Bool_t proton = false;
	      Bool_t deuteron = false;
	      Bool_t triton   = false;
	      Bool_t helium3 = false;
	      Bool_t helium4 = false;
	      //Bool_t deuteron = false;
	      //Bool_t deuteron = (d_zDeuteron > configs.z_de_low) && (d_zDeuteron < configs.z_de_high);
	      //Bool_t triton   = (d_zTriton > configs.z_tr_low) && (d_zTriton < configs.z_tr_high);
          //std::cout << "test 4.1.3" << std::endl;

	      if (tofTrack)
		{
		  pion = (d_nSigmaPi > configs.nSig_pi_low) &&
		    (d_nSigmaPi < configs.nSig_pi_high) &&
		    (d_m2 > configs.m2_pi_low) &&
		    (d_m2 < configs.m2_pi_high);

		  kaon = (d_nSigmaKa > configs.nSig_ka_low) &&
		    (d_nSigmaKa < configs.nSig_ka_high) &&
		    (d_m2 > configs.m2_ka_low) &&
		    (d_m2 < configs.m2_ka_high);
		  /*
		  deuteron = (d_zDeuteron > configs.z_de_low) &&
		    (d_zDeuteron < configs.z_de_high) &&
		    (d_m2 > configs.m2_de_low) &&
		    (d_m2 < configs.m2_de_high);

		  triton   = (d_zTriton > configs.z_tr_low) &&
		  (d_zTriton < configs.z_tr_high) &&
		    (d_m2 > configs.m2_tr_low) &&
		    (d_m2 < configs.m2_tr_high);
		  */
                  if(d_m2 > 1.5 && d_m2 < 2.5)
                  {   
                    h2_dEdx_vs_qp_m2_0->Fill(s_charge * d_mom, d_dEdx);
                    h2_m2_vs_qp_m2_0->Fill(d_mom/s_charge, d_m2);
		    h2_zHe3_vs_mom_m2cut->Fill(d_mom, d_zHelium3);
                  } else
                  if(d_m2 > 2.8 && d_m2 < 4.8)
                  {   
                    h2_dEdx_vs_qp_m2_1->Fill(s_charge * d_mom, d_dEdx);
                    h2_m2_vs_qp_m2_1->Fill(d_mom/s_charge, d_m2);
		    h2_zHe4_vs_mom_m2cut->Fill(d_mom, d_zAlpha);
                  } else
                  if(d_m2 > 6.4 && d_m2 < 9.4)
                  {   
                    h2_dEdx_vs_qp_m2_2->Fill(s_charge * d_mom, d_dEdx);
                    h2_m2_vs_qp_m2_2->Fill(d_mom/s_charge, d_m2);
                  }   
		}
          //std::cout << "test 4.1.3.1" << std::endl;

	      // 3.0 GeV d and t, he3,he4 PID
	      if (!pion && !kaon && configs.sqrt_s_NN == 3.0)
		{
		  deuteron = FlowUtils::momDepDeuteronID_psn0770(configs.sqrt_s_NN, configs.fixed_target, d_mom, d_zDeuteron, tofTrack, d_m2, 
		  					 configs.z_de_low, configs.z_de_high, configs.m2_de_low, configs.m2_de_high, configs.z_de_scale);

		  triton = FlowUtils::momDepTritonID_psn0770(configs.sqrt_s_NN, d_mom, d_zTriton, tofTrack, d_m2, 
		  				     configs.z_tr_low, configs.z_tr_high, configs.m2_tr_low, configs.m2_tr_high, configs.z_tr_scale);
		  if(fabs(d_zHelium3-0.12)<0.4 && 2*d_pT>0.8){
		  	helium3 = FlowUtils::momDepHelium3ID(configs.sqrt_s_NN, d_mom, d_zHelium3, tofTrack, d_m2, 
		  					 configs.z_he3_low, configs.z_he3_high, configs.m2_he3_low, configs.m2_he3_high, configs.z_he3_scale);
		  } 

		  if(fabs(d_zAlpha-0.12)<0.4 && 2*d_pT>1.0){
		  	helium4 = FlowUtils::momDepHelium4ID(configs.sqrt_s_NN, d_mom, d_zAlpha, tofTrack, d_m2, 
		  					 configs.z_he4_low, configs.z_he4_high, configs.m2_he4_low, configs.m2_he4_high, configs.z_he4_scale);
		  }
		}
          //std::cout << "test 4.1.3.2" << std::endl;
	      // 3.2 GeV d and t, he3,he4 PID
	      else if (!pion && !kaon && configs.sqrt_s_NN == 3.2)
		{
		  deuteron = FlowUtils::momDepDeuteronID_psn0770(configs.sqrt_s_NN, configs.fixed_target, d_mom, d_zDeuteron, tofTrack, d_m2, 
		  			             configs.z_de_low, configs.z_de_high, configs.m2_de_low, configs.m2_de_high, configs.z_de_scale);

		  triton = FlowUtils::momDepTritonID_psn0770(configs.sqrt_s_NN, d_mom, d_zTriton, tofTrack, d_m2, 
		  				     configs.z_tr_low, configs.z_tr_high, configs.m2_tr_low, configs.m2_tr_high, configs.z_tr_scale);

		  helium3 = FlowUtils::momDepHelium3ID(configs.sqrt_s_NN, d_mom, d_zHelium3, tofTrack, d_m2, 
		  				     configs.z_he3_low, configs.z_he3_high, configs.m2_he3_low, configs.m2_he3_high, configs.z_he3_scale);

		  helium4 = FlowUtils::momDepHelium4ID(configs.sqrt_s_NN, d_mom, d_zAlpha, tofTrack, d_m2, 
		  			             configs.z_he4_low, configs.z_he4_high, configs.m2_he4_low, configs.m2_he4_high, configs.z_he4_scale);
		}
	      // 7.7 GeV FXT d and t, he3,he4 PID
	      else if (!pion && !kaon && configs.sqrt_s_NN == 7.7 && configs.fixed_target)
		{
		  deuteron = FlowUtils::momDepDeuteronID_psn0770(configs.sqrt_s_NN, configs.fixed_target, d_mom, d_zDeuteron, tofTrack, d_m2, 
		  			             configs.z_de_low, configs.z_de_high, configs.m2_de_low, configs.m2_de_high, configs.z_de_scale);
		  //if(deuteron)
                  //std::cout << "deuteron ? " << deuteron << "; momentum: "<< d_mom << std::endl;

		  /*
		   * triton = FlowUtils::momDepTritonID_psn0770(configs.sqrt_s_NN, d_mom, d_zTriton, tofTrack, d_m2, 
		  				     configs.z_tr_low, configs.z_tr_high, configs.m2_tr_low, configs.m2_tr_high, configs.z_tr_scale);

		  helium3 = FlowUtils::momDepHelium3ID(configs.sqrt_s_NN, d_mom, d_zHelium3, tofTrack, d_m2, 
		  				     configs.z_he3_low, configs.z_he3_high, configs.m2_he3_low, configs.m2_he3_high, configs.z_he3_scale);

		  helium4 = FlowUtils::momDepHelium4ID(configs.sqrt_s_NN, d_mom, d_zAlpha, tofTrack, d_m2, 
		  			             configs.z_he4_low, configs.z_he4_high, configs.m2_he4_low, configs.m2_he4_high, configs.z_he4_scale);
		  */

		  //  TRITON
		  //if (tofTrack)
		  //  {
		      if (d_zTriton > configs.z_tr_low &&
			  d_zTriton < configs.z_tr_high)// &&
			  //d_m2 > configs.m2_tr_low &&
			  //d_m2 < configs.m2_tr_high)
			triton = true;
		    //}
          //std::cout << "test 4.1.3.3" << std::endl;
		  
		  //  Helium3
		  if (tofTrack)
		    {
		      if (d_zHelium3 > configs.z_he3_low &&
			  d_zHelium3 < configs.z_he3_high &&
			  d_m2 > configs.m2_he3_low &&
			  d_m2 < configs.m2_he3_high)
			helium3 = true;
		    }

		  //  Helium4
		  if (tofTrack)
		    {
		      if (d_zAlpha > configs.z_he4_low &&
			  d_zAlpha < configs.z_he4_high &&
			  d_m2 > configs.m2_he4_low &&
			  d_m2 < configs.m2_he4_high)
			helium4 = true;
		    }
		}
	      // Basic d and t PID
	      else if (!pion && !kaon && (configs.sqrt_s_NN == 7.7 || configs.sqrt_s_NN == 7.2 || configs.sqrt_s_NN == 3.9))
		{
		  //  DEUTERON
		  //if (tofTrack)
		    //{
		      if (d_zDeuteron > configs.z_de_low &&
			  d_zDeuteron < configs.z_de_high)// &&
			  //d_m2 > configs.m2_de_low &&
			  //d_m2 < configs.m2_de_high)
			deuteron = true;
		    //}

		  //  TRITON
		  if (tofTrack)
		    {
		      if (d_zTriton > configs.z_tr_low &&
			  d_zTriton < configs.z_tr_high &&
			  d_m2 > configs.m2_tr_low &&
			  d_m2 < configs.m2_tr_high)
			triton = true;
		    }
          //std::cout << "test 4.1.3.3" << std::endl;
		  
		  //  Helium3
		  if (tofTrack)
		    {
		      if (d_zHelium3 > configs.z_he3_low &&
			  d_zHelium3 < configs.z_he3_high &&
			  d_m2 > configs.m2_he3_low &&
			  d_m2 < configs.m2_he3_high)
			helium3 = true;
		    }

		  //  Helium4
		  if (tofTrack)
		    {
		      if (d_zAlpha > configs.z_he4_low &&
			  d_zAlpha < configs.z_he4_high &&
			  d_m2 > configs.m2_he4_low &&
			  d_m2 < configs.m2_he4_high)
			helium4 = true;
		    }

		}

	      /*
		if (deuteron && proton) 
		{ 
		if (TMath::Abs(d_zDeuteron) < TMath::Abs(d_nSigmaPr)) { proton = false; }
		else if (TMath::Abs(d_zDeuteron) == TMath::Abs(d_nSigmaPr)) { proton = false; deuteron = false; }
		else { deuteron = false; }
		}
		if (triton && proton)
		{
		if (TMath::Abs(d_zTriton) < TMath::Abs(d_nSigmaPr)) { proton = false; }
		else if (TMath::Abs(d_zTriton) == TMath::Abs(d_nSigmaPr)) { proton = false; triton = false; }
		else { triton = false; }
		}
		if (deuteron && triton)
		{
		if (TMath::Abs(d_zDeuteron) < TMath::Abs(d_zTriton)) { triton = false; }
		else if (TMath::Abs(d_zDeuteron) == TMath::Abs(d_zTriton)) { triton = false; deuteron = false; }
		else { deuteron = false; }
		}
	      */
		  h2_zHe3_vs_mom->Fill(2*d_mom, d_zHelium3);
		  h2_zHe4_vs_mom->Fill(2*d_mom, d_zAlpha);

              Double_t d_rapidityHe3 = FlowUtils::rapidity(2*d_px, 2*d_py, 2*d_pz, D_M0_HE3);
          //std::cout << "test 4.1.3.4" << std::endl;

	      if(d_rapidityHe3 - Y_MID >= 0. && d_rapidityHe3 - Y_MID < 0.5) h2_zHe3_vs_mom_yMid->Fill(2*d_mom, d_zHelium3);
	      else if(d_rapidityHe3 - Y_MID >= 0.5 && d_rapidityHe3 - Y_MID < 1.0) h2_zHe3_vs_mom_yFor->Fill(2*d_mom, d_zHelium3);


	      //if (helium3 && deuteron) { helium3 = true; } // Ignore the contamination for he3 
	      //if (helium3 && triton) { helium3 = true; }   // Ignore the contamination for he3 
	      //if (helium3 && proton) { helium3 = true; }   // Ignore the contamination for he3 
	      //if (helium3 && deuteron) { helium3 = false; } // Ignore the contamination for he3 
	      //if (helium3 && triton) { helium3 = false; }   // Ignore the contamination for he3 
	      //if (helium3 && proton) { helium3 = false; }   // Ignore the contamination for he3 
	      if (deuteron && triton) { deuteron = false; } // triton use ToF, keep true for it's PID.
	      if (deuteron && proton) { proton = false; } // d and t will have some contamination from p, but that has been minimized
	      //if (deuteron && proton) { deuteron = false; proton = false;} // better d measurement d and t will have some contamination from p, but that has been minimized
	      if (triton && proton)   { proton = false; }

	      if (pion && proton)   { proton = false; }
	      if (kaon && proton)   { proton = false; }
	      //=========================================================
	      //          END PID Cuts
	      //=========================================================

	      if (pion || kaon || proton || deuteron || triton || helium3) h_trackCheck->Fill(2);

	      if (!pion && !kaon) 
		{
		  h2_nSigp_vs_mom->Fill(d_mom, d_nSigmaPr);
		  h2_zd_vs_mom->Fill(d_mom, d_zDeuteron);
		  h2_zt_vs_mom->Fill(d_mom, d_zTriton);
		  //h2_zHe3_vs_mom->Fill(2*d_mom, d_zHelium3);
		  //h2_zHe4_vs_mom->Fill(2*d_mom, d_zAlpha);
		}


	      Double_t d_rapidity = 999.0;
	      Double_t d_mT = -999.0;
	      Double_t massNumber;

          //std::cout << "test 4.1.3.4" << std::endl;
	      if(pion) // PID Pions
		{ 
		  d_rapidity = FlowUtils::rapidity(d_px, d_py, d_pz, D_M0_PI);
		  d_mT = FlowUtils::transMass(d_px, d_py, D_M0_PI);
		  d_m2 = d_mom*d_mom*( (1.0 / (d_tofBeta*d_tofBeta)) - 1.0);		    
          //std::cout << "test 4.1.3.4.1" << std::endl;

		  particleInfo.rapidity = d_rapidity;
		  particleInfo.KT = d_mT - D_M0_PI;

		  if(s_charge > 0)
		    {
		      particleInfo.ppTag = true;
		      N_pp++;
		      h_eta_pp->Fill(d_eta);
		      h_phi_pp->Fill(d_phi);
		      h_pT_pp->Fill(d_pT);
		      h_mom_pp->Fill(d_mom);
		      h_dndy_pp->Fill(d_rapidity);
		      h_dndm_pp->Fill(d_mT - D_M0_PI);
		      h2_pT_vs_yCM_pp->Fill(d_rapidity - Y_MID, d_pT);
		      h2_dEdx_vs_qp_pp->Fill(s_charge*d_mom, d_dEdx);
		      h2_beta_vs_qp_pp->Fill(s_charge*d_mom, 1.0/d_tofBeta);
		      h2_m2_vs_qp_pp->Fill(s_charge*d_mom, d_m2);
			  
		      if (d_rapidity - Y_MID > configs.yCM_norm_pi_low && d_rapidity - Y_MID < configs.yCM_norm_pi_high && 
			  d_pT >= configs.pt_norm_pi_low && d_pT <= configs.pt_norm_pi_high)
			{
			  //h2_y_vs_eta->Fill(d_eta, d_rapidity);
			  //h2_y_vs_eta_pp->Fill(d_eta, d_rapidity);
			  p_meanpT_vs_yCM_pp->Fill(d_rapidity - Y_MID, particleInfo.pT);
			}
		    }
		  else if(s_charge < 0)
		    {
		      particleInfo.pmTag = true;
		      N_pm++;
		      h_eta_pm->Fill(d_eta);
		      h_phi_pm->Fill(d_phi);
		      h_pT_pm->Fill(d_pT);
		      h_mom_pm->Fill(d_mom);
		      h_dndy_pm->Fill(d_rapidity);
		      h_dndm_pm->Fill(d_mT - D_M0_PI);
		      h2_pT_vs_yCM_pm->Fill(d_rapidity - Y_MID, d_pT);
		      h2_dEdx_vs_qp_pm->Fill(s_charge*d_mom, d_dEdx);
		      h2_beta_vs_qp_pm->Fill(s_charge*d_mom, 1.0/d_tofBeta);
		      h2_m2_vs_qp_pm->Fill(s_charge*d_mom, d_m2);

		      if (d_rapidity - Y_MID > configs.yCM_norm_pi_low && d_rapidity - Y_MID < configs.yCM_norm_pi_high && 
			  d_pT >= configs.pt_norm_pi_low && d_pT <= configs.pt_norm_pi_high)
			{
			  //h2_y_vs_eta->Fill(d_eta, d_rapidity);
			  //h2_y_vs_eta_pm->Fill(d_eta, d_rapidity);
			  p_meanpT_vs_yCM_pm->Fill(d_rapidity - Y_MID, particleInfo.pT);
			}
		    }
		}
	      else if(kaon) // PID Kaons
		{
          //std::cout << "test 4.1.3.4.2" << std::endl;
		  d_rapidity = FlowUtils::rapidity(d_px, d_py, d_pz, D_M0_KA);
		  d_mT = FlowUtils::transMass(d_px, d_py, D_M0_KA);

		  particleInfo.rapidity = d_rapidity;
		  particleInfo.KT = d_mT - D_M0_KA;
				  
		  if(s_charge > 0)
		    {
		      particleInfo.kpTag = true;
		      N_kp++;
		      h_eta_kp->Fill(d_eta);
		      h_phi_kp->Fill(d_phi);
		      h_pT_kp->Fill(d_pT);
		      h_mom_kp->Fill(d_mom);
		      h_dndy_kp->Fill(d_rapidity);
		      h_dndm_kp->Fill(d_mT - D_M0_KA);
		      h2_pT_vs_yCM_kp->Fill(d_rapidity - Y_MID, d_pT);
		      h2_dEdx_vs_qp_kp->Fill(s_charge*d_mom, d_dEdx);
		      h2_beta_vs_qp_kp->Fill(s_charge*d_mom, 1.0/d_tofBeta);
		      h2_m2_vs_qp_kp->Fill(s_charge*d_mom, d_m2);

		      if (d_rapidity - Y_MID > configs.yCM_norm_ka_low && d_rapidity - Y_MID < configs.yCM_norm_ka_high && 
			  d_pT >= configs.pt_norm_ka_low && d_pT <= configs.pt_norm_ka_high)
			{
			  //h2_y_vs_eta->Fill(d_eta, d_rapidity);
			  //h2_y_vs_eta_kp->Fill(d_eta, d_rapidity);
			  p_meanpT_vs_yCM_kp->Fill(d_rapidity - Y_MID, particleInfo.pT);
			}

		    }
		  else if(s_charge < 0)
		    {
		      particleInfo.kmTag = true;
		      N_km++;
		      h_eta_km->Fill(d_eta);
		      h_phi_km->Fill(d_phi);
		      h_pT_km->Fill(d_pT);
		      h_mom_km->Fill(d_mom);
		      h_dndy_km->Fill(d_rapidity);
		      h_dndm_km->Fill(d_mT - D_M0_KA);
		      h2_pT_vs_yCM_km->Fill(d_rapidity - Y_MID, d_pT);
		      h2_dEdx_vs_qp_km->Fill(s_charge*d_mom, d_dEdx);
		      h2_beta_vs_qp_km->Fill(s_charge*d_mom, 1.0/d_tofBeta);
		      h2_m2_vs_qp_km->Fill(s_charge*d_mom, d_m2);

		      if (d_rapidity - Y_MID > configs.yCM_norm_ka_low && d_rapidity - Y_MID < configs.yCM_norm_ka_high && 
			  d_pT >= configs.pt_norm_ka_low && d_pT <= configs.pt_norm_ka_high)
			{
			  //h2_y_vs_eta->Fill(d_eta, d_rapidity);
			  //h2_y_vs_eta_km->Fill(d_eta, d_rapidity);
			  p_meanpT_vs_yCM_km->Fill(d_rapidity - Y_MID, particleInfo.pT);
			}
		    }
		}
	      else if(proton) // PID Proton
		{
          //std::cout << "test 4.1.3.4.3" << std::endl;
		  particleInfo.prTag = true;
		  N_pr++;
		  d_rapidity = FlowUtils::rapidity(d_px, d_py, d_pz, D_M0_PR);
		  d_mT = FlowUtils::transMass(d_px, d_py, D_M0_PR);
		  massNumber = 1.0;

		  particleInfo.rapidity = d_rapidity;
		  particleInfo.KT = d_mT - D_M0_PR;
				  
		  h_eta_pr->Fill(d_eta);
		  h_phi_pr->Fill(d_phi);
		  h_pT_pr->Fill(d_pT);
		  h_mom_pr->Fill(d_mom);
		  h_dndy_pr->Fill(d_rapidity);
		  h_dndm_pr->Fill(d_mT - D_M0_PR);
		  h2_pT_vs_yCM_pr->Fill(d_rapidity - Y_MID, d_pT);
		  h2_KToverA_vs_yCM_pr->Fill(d_rapidity - Y_MID, (d_mT - D_M0_PR)/1.0);
		  h2_dEdx_vs_qp_pr->Fill(s_charge*d_mom, d_dEdx);
		  //h2_beta_vs_qp_pr->Fill(s_charge*d_mom, 1.0/d_tofBeta);
		  h2_m2_vs_qp_pr->Fill(s_charge*d_mom, d_m2);

		  // Normal acceptance region
		  if (d_rapidity - Y_MID > configs.yCM_norm_pr_low && d_rapidity - Y_MID < configs.yCM_norm_pr_high && 
		      d_pT >= configs.pt_norm_pr_low && d_pT <= configs.pt_norm_pr_high)
		    {
		      p_meanpT_vs_yCM_pr->Fill(d_rapidity - Y_MID, d_pT);
		      h2_dEdx_vs_qp_id_pr->Fill(d_mom, d_dEdx);
		      //h2_y_vs_eta->Fill(d_eta, d_rapidity);
		      //h2_y_vs_eta_pr->Fill(d_eta, d_rapidity);
		    }
		  // Alternate acceptance region
		  if (d_rapidity - Y_MID > configs.yCM_alt_pr_low && d_rapidity - Y_MID < configs.yCM_alt_pr_high && 
		      (d_mT-D_M0_PR)/massNumber >= configs.KT_pdt_low && (d_mT-D_M0_PR)/massNumber <= configs.KT_pdt_high)
		    {
		      h2_dEdx_vs_qp_id_pr_alt->Fill(d_mom, d_dEdx);
		      p_meanpT_vs_yCM_pr_alt->Fill(d_rapidity - Y_MID, d_pT);
		      h2_pT_vs_cent_pr->Fill(i_centrality, d_pT);
		      h2_pT_vs_yCM_pr_alt->Fill(d_rapidity - Y_MID, d_pT);
		      h_DCA_pr_alt->Fill(d_DCA);
		    }
		}		    
	      else if(deuteron) // PID Deuteron
		{
          //std::cout << "test 4.1.3.4.4" << std::endl;
		  particleInfo.deTag = true;
		  N_de++;
		  d_rapidity = FlowUtils::rapidity(d_px, d_py, d_pz, D_M0_DE);
		  d_mT = FlowUtils::transMass(d_px, d_py, D_M0_DE);
		  massNumber = 2.0;

		  particleInfo.rapidity = d_rapidity;
		  particleInfo.KT = d_mT - D_M0_DE;
		  particleInfo.zValue = d_zDeuteron;
		  
		  h_eta_de->Fill(d_eta);
		  h_phi_de->Fill(d_phi);
		  h_pT_de->Fill(d_pT);
		  h_mom_de->Fill(d_mom);
		  h_dndy_de->Fill(d_rapidity);
		  h_dndm_de->Fill(d_mT - D_M0_DE);
		  h2_pT_vs_yCM_de->Fill(d_rapidity - Y_MID, d_pT);
                  //de_eff = de_eff*(Float_t)h2_tracking_de->GetBinContent(h2_tracking_de->FindBin(d_rapidity - Y_MID, d_pT));
                  //de_eff = de_eff*(Float_t)tpc_de->GetBinContent(tpc_de->FindBin(d_mom));
                  //if(d_mom>3.2) de_eff = de_eff*(Float_t)tof_d->GetBinContent(tof_d->FindBin(d_mom));
                  //if(d_mom>3.2) de_eff = de_eff*(Float_t)tofmatch->GetBinContent(tofmatch->FindBin(d_eta, d_pT));
		  particleInfo.eff = de_eff;
                  //std::cout << "de_eff: " << de_eff << std::endl;
 
		  h2_dEdx_vs_qp_de->Fill(s_charge*d_mom, d_dEdx);
		  //h2_beta_vs_qp_de->Fill(s_charge*d_mom, 1.0/d_tofBeta);
		  h2_m2_vs_qp_de->Fill(s_charge*d_mom, d_m2);
		  h2_pToverA_vs_yCM_de->Fill(d_rapidity - Y_MID, d_pT/2.0);
		  h2_KToverA_vs_yCM_de->Fill(d_rapidity - Y_MID, (d_mT - D_M0_DE)/2.0);
		  //h2_dEdx_vs_qp_half_postZdCut->Fill(s_charge * d_mom, d_dEdx);

		  if (d_rapidity - Y_MID > configs.yCM_norm_de_low && d_rapidity - Y_MID < configs.yCM_norm_de_high && 
		      (d_mT-D_M0_DE)/massNumber >= configs.KT_pdt_low && (d_mT-D_M0_DE)/massNumber <= configs.KT_pdt_high)
		    {
		      //h2_y_vs_eta->Fill(d_eta, d_rapidity);
		      //h2_y_vs_eta_de->Fill(d_eta, d_rapidity);
		      p_meanpT_vs_yCM_de->Fill(d_rapidity - Y_MID, d_pT);
		      h2_dEdx_vs_qp_id_de->Fill(d_mom, d_dEdx);
		      h2_pT_vs_cent_de->Fill(i_centrality, d_pT);
		      h_DCA_de->Fill(d_DCA);
		    }
		}		    
	      else if(triton) // PID Triton
		{
          //std::cout << "test 4.1.3.4.5" << std::endl;
		  particleInfo.trTag = true;
		  N_tr++;
		  d_rapidity = FlowUtils::rapidity(d_px, d_py, d_pz, D_M0_TR);
		  d_mT = FlowUtils::transMass(d_px, d_py, D_M0_TR);
		  massNumber = 3.0;

		  particleInfo.rapidity = d_rapidity;
		  particleInfo.KT = d_mT - D_M0_TR;
		  particleInfo.zValue = d_zTriton;
				  
		  h_eta_tr->Fill(d_eta);
		  h_phi_tr->Fill(d_phi);
		  h_pT_tr->Fill(d_pT);
		  h_mom_tr->Fill(d_mom);
		  h_dndy_tr->Fill(d_rapidity);
		  h_dndm_tr->Fill(d_mT - D_M0_TR);
		  h2_pT_vs_yCM_tr->Fill(d_rapidity - Y_MID, d_pT);
		  particleInfo.eff = tr_eff;
		  h2_dEdx_vs_qp_tr->Fill(s_charge*d_mom, d_dEdx);
		  //h2_beta_vs_qp_tr->Fill(s_charge*d_mom, 1.0/d_tofBeta);
		  h2_m2_vs_qp_tr->Fill(s_charge*d_mom, d_m2);
		  h2_pToverA_vs_yCM_tr->Fill(d_rapidity - Y_MID, d_pT/3.0);
		  h2_KToverA_vs_yCM_tr->Fill(d_rapidity - Y_MID, (d_mT - D_M0_TR)/3.0);
		  //h2_dEdx_vs_qp_half_postZtCut->Fill(s_charge * d_mom, d_dEdx);

		  if (d_rapidity - Y_MID > configs.yCM_norm_tr_low && d_rapidity - Y_MID < configs.yCM_norm_tr_high && 
		      (d_mT-D_M0_TR)/massNumber >= configs.KT_pdt_low && (d_mT-D_M0_TR)/massNumber <= configs.KT_pdt_high)
		    {
		      //h2_y_vs_eta->Fill(d_eta, d_rapidity);
		      //h2_y_vs_eta_tr->Fill(d_eta, d_rapidity);
		      p_meanpT_vs_yCM_tr->Fill(d_rapidity - Y_MID, d_pT);
		      h2_dEdx_vs_qp_id_tr->Fill(d_mom, d_dEdx);
		      h2_pT_vs_cent_tr->Fill(i_centrality, d_pT);
		      h_DCA_tr->Fill(d_DCA);
		    }
		}		    
	      else if(helium3) // PID Helium3
		{
          //std::cout << "test 4.1.3.4.6" << std::endl;
		  particleInfo.he3Tag = true;
		  N_he3++;
		  d_rapidity = FlowUtils::rapidity(2*d_px, 2*d_py, 2*d_pz, D_M0_HE3);
		  d_mT = FlowUtils::transMass(2*d_px, 2*d_py, D_M0_HE3);
		  massNumber = 3.0;
          //std::cout << "test 4.1.3.4.6.1" << std::endl;

		  particleInfo.rapidity = d_rapidity;
		  particleInfo.KT = d_mT - D_M0_HE3;
		  
		  h_eta_he3->Fill(d_eta);
		  h_phi_he3->Fill(d_phi);
		  h_pT_he3->Fill(d_pT);
		  h_mom_he3->Fill(d_mom);
		  h_dndy_he3->Fill(d_rapidity);
		  h_dndm_he3->Fill(d_mT - D_M0_HE3);
		  //h2_pT_vs_yCM_he3->Fill(d_rapidity - Y_MID, d_pT);
                  //Float_t he3_eff_f = he3_eff*(Float_t)h2_tracking_he3->GetBinContent(h2_tracking_he3->FindBin((Float_t)(d_rapidity - Y_MID), (Float_t)2*d_pT));
                  he3_eff = (efficienciesFound) ?  he3_eff*(Float_t)h2_tracking_he3->GetBinContent(h2_tracking_he3->FindBin(d_rapidity - Y_MID, 2*d_pT)) : he3_eff;
          //std::cout << "test 4.1.3.4.6.2" << std::endl;
                  //std::cout << "d_rapidity - Y_MID: " << d_rapidity - Y_MID << "; 2* d_pT: "<< 2*d_pT << "; he3_eff h2_tracking_he3: " << he3_eff << std::endl;
                  //std::cout << "(Float_t)(d_rapidity - Y_MID): " << Float_t(d_rapidity - Y_MID) << "; Float_t2* d_pT: "<< (Float_t)2*d_pT << "; he3_eff_f h2_tracking_he3: " << he3_eff_f << std::endl;
                  //std::cout << "difference: " << he3_eff - he3_eff_f << std::endl;
                  he3_eff = (efficienciesFound) ? he3_eff*(Float_t)tpc_he3->GetBinContent(tpc_he3->FindBin(2*d_mom)) : he3_eff;
                  //std::cout << "he3_eff tpc: " << he3_eff << std::endl;
		  if(he3_eff>1.)	{ he3_eff = 1.; }
		  if(he3_eff>0.) {
		  	h2_pT_vs_yCM_he3_weight->Fill(d_rapidity - Y_MID, 2*d_pT, 1./he3_eff);
                  	//std::cout << "he3.eff tpc: " << particleInfo.eff << std::endl;
		  }
		  particleInfo.eff = he3_eff;
		  h2_pT_vs_yCM_he3->Fill(d_rapidity - Y_MID, 2*d_pT);
		  h2_dEdx_vs_qp_he3->Fill(s_charge*d_mom, d_dEdx);
		  //h2_beta_vs_qp_he3->Fill(s_charge*d_mom, 1.0/d_tofBeta);
		  h2_m2_vs_qp_he3->Fill(s_charge*d_mom, d_m2);
		  h2_pToverA_vs_yCM_he3->Fill(d_rapidity - Y_MID, d_pT/3.0);
		  h2_KToverA_vs_yCM_he3->Fill(d_rapidity - Y_MID, (d_mT - D_M0_HE3)/3.0);
		  if (2*d_pT >= configs.pt_norm_he3_low && 2*d_pT <= configs.pt_norm_he3_high &&
			  d_rapidity - Y_MID > configs.yCM_norm_he3_low && d_rapidity - Y_MID < configs.yCM_norm_he3_high)
                  {
		  	h2_dEdx_vs_qp_he3_norm->Fill(s_charge*d_mom, d_dEdx);
		  	h2_m2_vs_qp_he3_norm->Fill(s_charge*d_mom, d_m2);
		        h2_pT_vs_yCM_he3_norm->Fill(d_rapidity - Y_MID, 2*d_pT);
		  
		  }
		  //h2_dEdx_vs_qp_half_postZdCut->Fill(s_charge * d_mom, d_dEdx);

		  if (d_rapidity - Y_MID > configs.yCM_norm_he3_low && d_rapidity - Y_MID < configs.yCM_norm_he3_high && 
		      (d_mT-D_M0_HE3)/massNumber >= configs.KT_pdt_low && (d_mT-D_M0_HE3)/massNumber <= configs.KT_pdt_high)
		    {
		      //h2_y_vs_eta->Fill(d_eta, d_rapidity);
		      //h2_y_vs_eta_he3->Fill(d_eta, d_rapidity);
		      p_meanpT_vs_yCM_he3->Fill(d_rapidity - Y_MID, d_pT);
		      h2_dEdx_vs_qp_id_he3->Fill(d_mom, d_dEdx);
		      h2_pT_vs_cent_he3->Fill(i_centrality, d_pT);
		      h_DCA_he3->Fill(d_DCA);
		    }
		}		    
	      else if(helium4) // PID Helium4
		{
          //std::cout << "test 4.1.3.4.7" << std::endl;
		  particleInfo.he4Tag = true;
		  N_he4++;
		  d_rapidity = FlowUtils::rapidity(2*d_px, 2*d_py, 2*d_pz, D_M0_HE4);
		  d_mT = FlowUtils::transMass(2*d_px, 2*d_py, D_M0_HE4);
		  massNumber = 4.0;

		  particleInfo.rapidity = d_rapidity;
		  particleInfo.KT = d_mT - D_M0_HE4;
		  
		  h_eta_he4->Fill(d_eta);
		  h_phi_he4->Fill(d_phi);
		  h_pT_he4->Fill(d_pT);
		  h_mom_he4->Fill(d_mom);
		  h_dndy_he4->Fill(d_rapidity);
		  h_dndm_he4->Fill(d_mT - D_M0_HE4);
		  h2_pT_vs_yCM_he4->Fill(d_rapidity - Y_MID, 2*d_pT);
                  he4_eff = (efficienciesFound) ? he4_eff*(Float_t)h2_tracking_he4->GetBinContent(h2_tracking_he4->FindBin(d_rapidity - Y_MID, 2*d_pT)) : he4_eff;
                  he4_eff = (efficienciesFound) ? he4_eff*(Float_t)tpc_he4->GetBinContent(tpc_he4->FindBin(2*d_mom)) : he4_eff;
		  if(he4_eff>1)	{ he4_eff = 1.; }
		  if(he4_eff>0.) {
		  	h2_pT_vs_yCM_he4_weight->Fill(d_rapidity - Y_MID, 2*d_pT, 1./he4_eff);
		  }
		  particleInfo.eff = he4_eff;
		  h2_dEdx_vs_qp_he4->Fill(s_charge*d_mom, d_dEdx);
		  //h2_beta_vs_qp_he4->Fill(s_charge*d_mom, 1.0/d_tofBeta);
		  h2_m2_vs_qp_he4->Fill(s_charge*d_mom, d_m2);
		  h2_pToverA_vs_yCM_he4->Fill(d_rapidity - Y_MID, d_pT/2.0);
		  h2_KToverA_vs_yCM_he4->Fill(d_rapidity - Y_MID, (d_mT - D_M0_HE4)/2.0);
		  if (2*d_pT >= configs.pt_norm_he4_low && 2*d_pT <= configs.pt_norm_he4_high &&
		          d_rapidity - Y_MID > configs.yCM_norm_he4_low && d_rapidity - Y_MID < configs.yCM_norm_he4_high)
                  {
		  	h2_dEdx_vs_qp_he4_norm->Fill(s_charge*d_mom, d_dEdx);
		  	h2_m2_vs_qp_he4_norm->Fill(s_charge*d_mom, d_m2);
		        h2_pT_vs_yCM_he4_norm->Fill(d_rapidity - Y_MID, 2*d_pT);
		  
		  }
		  //h2_dEdx_vs_qp_half_postZdCut->Fill(s_charge * d_mom, d_dEdx);

		  if (d_rapidity - Y_MID > configs.yCM_norm_he4_low && d_rapidity - Y_MID < configs.yCM_norm_he4_high && 
		      (d_mT-D_M0_HE4)/massNumber >= configs.KT_pdt_low && (d_mT-D_M0_HE4)/massNumber <= configs.KT_pdt_high)
		    {
		      //h2_y_vs_eta->Fill(d_eta, d_rapidity);
		      //h2_y_vs_eta_he4->Fill(d_eta, d_rapidity);
		      p_meanpT_vs_yCM_he4->Fill(d_rapidity - Y_MID, d_pT);
		      h2_dEdx_vs_qp_id_he4->Fill(d_mom, d_dEdx);
		      h2_pT_vs_cent_he4->Fill(i_centrality, d_pT);
		      h_DCA_he4->Fill(d_DCA);
		    }
		}		    

          //std::cout << "test 4.1.3.5" << std::endl;
	      eventInfo.tpcParticles.push_back(particleInfo);
	    }// End if(s_charge != 0)
          //std::cout << "test 4.1.4" << std::endl;
	}//End TPC track loop
          //std::cout << "test 5" << std::endl;
      particleInfo.reset();

      h_mult_pp->Fill(N_pp);
      h_mult_pm->Fill(N_pm);
      h_mult_kp->Fill(N_kp);
      h_mult_km->Fill(N_km);
      h_mult_pr->Fill(N_pr);
      h_mult_de->Fill(N_de);
      h_mult_tr->Fill(N_tr);
      h_mult_he3->Fill(N_he3);
      h_mult_he4->Fill(N_he4);

      //=========================================================
      //                EPD STUFF
      //=========================================================
      Short_t tileID;
      TVector3 tileVector;     // Vector from vertex to center of tile that was hit
      Int_t tileSector;
      Int_t tileRow;
      Double_t tileWeight;
      Double_t tileEta;
      Double_t tilePhi;
      Double_t tilenMip;

      FlowUtils::Particle epdParticleInfo;
          //std::cout << "test 6" << std::endl;
      // StPileupUtil cut
      float m_nmipsum = 0;
      for (UShort_t iEpdHit = 0; iEpdHit < i_nEPDhits; iEpdHit++)
	{
	  epdParticleInfo.reset();

	  tileID = EPDids[iEpdHit];
	  Bool_t epdAside = (tileID < 0);  // East side
	  Bool_t epdBside = (configs.fixed_target) ? (tileID < 0) : (tileID > 0); // EPD B is also on the East side in FXT
	  
	  tileVector = epdGeom->TileCenter(tileID) - pVtx;
	  tileSector = FlowUtils::epdSector(tileID);
	  tileRow = FlowUtils::epdRow(tileID);
	  tileEta = tileVector.Eta();
	  tilePhi = tileVector.Phi();
	  tilenMip = EPDnMip[iEpdHit];
	  //std::cout << "tileID: " << tileID << ", tilenMip: " << tilenMip << std::endl;
	  //h2_EPD_Nmip->Fill(tileID, tilenMip);
	  tileWeight = (tilenMip > configs.epd_threshold) ? ( (tilenMip > configs.epd_max_weight)?configs.epd_max_weight:tilenMip ) : 0;

	  h_eta->Fill(tileEta);
	  //if (configs.sqrt_s_NN == 7.2) tileWeight *= TMath::Abs(tileEta - Y_MID);
	  // StPileupUtil cut
	  if ( (tileEta>-4.0 && tileEta<-2.5) && (tilenMip>0.3 && tilenMip<=4.0)) m_nmipsum  += tilenMip;

	  if (epdAside)
	    {
	      eventInfo.nHitsEpd++;
	      h2_ring_vs_eta->Fill(tileEta, tileRow);

	      eventInfo.incrementQvectorEPD(ODD_PLANE, ORDER_M, Y_MID, tileEta, tilePhi, tileWeight);
	    }

	  if (epdAside && tileRow >= configs.epdA_inner_row && tileRow <= configs.epdA_outer_row)
	    {
	      eventInfo.nHitsEpdA++;
	      epdParticleInfo.isInEpdA = true;
	      epdParticleInfo.phi    = tilePhi;
	      epdParticleInfo.eta    = tileEta;
	      epdParticleInfo.weight = tileWeight;

	      h_tileWeights->Fill(tileWeight);
	      h2_phi_vs_eta_EPD->Fill(tileEta, tilePhi);
	      p2_pp_vs_eta->Fill(tileEta, tileSector, tileWeight);

	      eventInfo.incrementQvectorEPDA(ODD_PLANE, ORDER_M, Y_MID, tileEta, tilePhi, tileWeight);
	      eventInfo.epdParticles.push_back(epdParticleInfo);
	    }
	  else if (epdBside && tileRow >= configs.epdB_inner_row && tileRow <= configs.epdB_outer_row)
	    {
	      eventInfo.nHitsEpdB++;
	      epdParticleInfo.isInEpdB = true;
	      epdParticleInfo.phi    = tilePhi;
	      epdParticleInfo.eta    = tileEta;
	      epdParticleInfo.weight = tileWeight;

	      h_tileWeights->Fill(tileWeight);
	      h2_phi_vs_eta_EPD->Fill(tileEta, tilePhi);
	      p2_pp_vs_eta->Fill(tileEta, tileSector, tileWeight);

	      if (configs.fixed_target) h2_ring_vs_eta->Fill(tileEta, tileRow);  // Only need the East side for this plot

	      eventInfo.incrementQvectorEPDB(ODD_PLANE, ORDER_M, Y_MID, tileEta, tilePhi, tileWeight);
	      eventInfo.epdParticles.push_back(epdParticleInfo);
	    }
	}// End EPD hit loop
          //std::cout << "test 7" << std::endl;
      epdParticleInfo.reset();
      //=========================================================
      //            END EPD STUFF
      //=========================================================

      //if (eventInfo.nTracksTpcA < configs.min_tracks) continue;
      if (eventInfo.nTracksTpcB < configs.min_tracks) continue;
      //if (eventInfo.nHitsEpd    < configs.min_tracks) continue;
      if (eventInfo.nHitsEpdA   < configs.min_tracks) continue;
      //if (eventInfo.nHitsEpdB   < configs.min_tracks) continue;
      if (configs.fixed_target && configs.sqrt_s_NN == 3.0 && eventInfo.nHitsEpdB < configs.min_tracks+4) continue;
      else if (configs.fixed_target && configs.sqrt_s_NN == 3.2 && eventInfo.nHitsEpdB < configs.min_tracks+4) continue;
      else if (configs.fixed_target && configs.sqrt_s_NN == 3.9  && eventInfo.nHitsEpdB < configs.min_tracks+4) continue;
      else if (configs.fixed_target && configs.sqrt_s_NN == 7.7  && eventInfo.nHitsEpdB < configs.min_tracks+4) continue;

      h_centralities_final->Fill(i_centrality);

      FlowUtils::checkZeroQ(eventInfo);  // Remove events with no flow
      if (eventInfo.badEvent) continue;

      FlowUtils::getAllPsi(eventInfo, ORDER_M);

      h2_hits_vs_cent_EpdA->Fill(eventInfo.centID, eventInfo.nHitsEpdA);
      h2_hits_vs_cent_EpdB->Fill(eventInfo.centID, eventInfo.nHitsEpdB);
      h2_hits_vs_cent_TpcB->Fill(eventInfo.centID, eventInfo.nTracksTpcB);

      h_primTracks->Fill(eventInfo.primTracks);      

      h_XnTpc->Fill(eventInfo.XnTpc);
      h_YnTpc->Fill(eventInfo.YnTpc);
      h_XnTpcA->Fill(eventInfo.XnTpcA);
      h_YnTpcA->Fill(eventInfo.YnTpcA);
      h_XnTpcB->Fill(eventInfo.XnTpcB);
      h_YnTpcB->Fill(eventInfo.YnTpcB);
      h_XnEpd->Fill(eventInfo.XnEpd);
      h_YnEpd->Fill(eventInfo.YnEpd);
      h_XnEpdA->Fill(eventInfo.XnEpdA);
      h_YnEpdA->Fill(eventInfo.YnEpdA);
      h_XnEpdB->Fill(eventInfo.XnEpdB);
      h_YnEpdB->Fill(eventInfo.YnEpdB);

      h_psiTpc_RAW->Fill(eventInfo.psiTpc);
      h_psiTpcA_RAW->Fill(eventInfo.psiTpcA);
      h_psiTpcB_RAW->Fill(eventInfo.psiTpcB);
      h_psiEpd_RAW->Fill(eventInfo.psiEpd);
      h_psiEpdA_RAW->Fill(eventInfo.psiEpdA);
      h_psiEpdB_RAW->Fill(eventInfo.psiEpdB);

      h2_psiTpc_RAW_Cent16->Fill(eventInfo.psiTpc, eventInfo.centID);
      h2_psiTpcA_RAW_Cent16->Fill(eventInfo.psiTpcA, eventInfo.centID);
      h2_psiTpcB_RAW_Cent16->Fill(eventInfo.psiTpcB, eventInfo.centID);
      h2_psiEpd_RAW_Cent16->Fill(eventInfo.psiEpd, eventInfo.centID);
      h2_psiEpdA_RAW_Cent16->Fill(eventInfo.psiEpdA, eventInfo.centID);
      h2_psiEpdB_RAW_Cent16->Fill(eventInfo.psiEpdB, eventInfo.centID);


      //=========================================================
      //          Re-centering (Xn, Yn) Distributions
      //=========================================================
          //std::cout << "test 8" << std::endl;
          //std::cout << "RUN_ITERATION == " << RUN_ITERATION << std::endl;

      if (RUN_ITERATION == 1 || RUN_ITERATION == 2)
	{
	  FlowUtils::recenterQ(eventInfo, correctionInputFile, ORDER_M);
          //std::cout << "test 8.1" << std::endl;

	  if (eventInfo.badEvent) continue;
          //std::cout << "test 8.2" << std::endl;

	  h_XnTpc_RC->Fill(eventInfo.XnTpc);
	  h_XnTpcA_RC->Fill(eventInfo.XnTpcA);
	  h_XnTpcB_RC->Fill(eventInfo.XnTpcB);
	  h_XnEpd_RC->Fill(eventInfo.XnEpd);
	  h_XnEpdA_RC->Fill(eventInfo.XnEpdA);
	  h_XnEpdB_RC->Fill(eventInfo.XnEpdB);

	  h_YnTpc_RC->Fill(eventInfo.YnTpc);
	  h_YnTpcA_RC->Fill(eventInfo.YnTpcA);
	  h_YnTpcB_RC->Fill(eventInfo.YnTpcB);
	  h_YnEpd_RC->Fill(eventInfo.YnEpd);
	  h_YnEpdA_RC->Fill(eventInfo.YnEpdA);
	  h_YnEpdB_RC->Fill(eventInfo.YnEpdB);

	  h_psiTpc_RC->Fill(eventInfo.psiTpc);
	  h_psiTpcA_RC->Fill(eventInfo.psiTpcA);
	  h_psiTpcB_RC->Fill(eventInfo.psiTpcB);
	  h_psiEpd_RC->Fill(eventInfo.psiEpd);
	  h_psiEpdA_RC->Fill(eventInfo.psiEpdA);
	  h_psiEpdB_RC->Fill(eventInfo.psiEpdB);

          h2_psiTpc_RC_Cent16->Fill(eventInfo.psiTpc, eventInfo.centID);
          h2_psiTpcA_RC_Cent16->Fill(eventInfo.psiTpcA, eventInfo.centID);
          h2_psiTpcB_RC_Cent16->Fill(eventInfo.psiTpcB, eventInfo.centID);
          h2_psiEpd_RC_Cent16->Fill(eventInfo.psiEpd, eventInfo.centID);
          h2_psiEpdA_RC_Cent16->Fill(eventInfo.psiEpdA, eventInfo.centID);
          h2_psiEpdB_RC_Cent16->Fill(eventInfo.psiEpdB, eventInfo.centID);

	  // Accumulate terms for averages over the re-centered angles for event plane angle shifting
	  for (int j = 1; j <= configs.shift_terms; j++)
	    {
	      p_sinAvgsTpc->Fill(j,  TMath::Sin((Double_t)j * ORDER_M * eventInfo.psiTpc));
	      p_cosAvgsTpc->Fill(j,  TMath::Cos((Double_t)j * ORDER_M * eventInfo.psiTpc));
	      p_sinAvgsTpcA->Fill(j, TMath::Sin((Double_t)j * ORDER_M * eventInfo.psiTpcA));
	      p_cosAvgsTpcA->Fill(j, TMath::Cos((Double_t)j * ORDER_M * eventInfo.psiTpcA));
	      p_sinAvgsTpcB->Fill(j, TMath::Sin((Double_t)j * ORDER_M * eventInfo.psiTpcB));
	      p_cosAvgsTpcB->Fill(j, TMath::Cos((Double_t)j * ORDER_M * eventInfo.psiTpcB));
	      p_sinAvgsEpd->Fill(j,  TMath::Sin((Double_t)j * ORDER_M * eventInfo.psiEpd));
	      p_cosAvgsEpd->Fill(j,  TMath::Cos((Double_t)j * ORDER_M * eventInfo.psiEpd));
	      p_sinAvgsEpdA->Fill(j, TMath::Sin((Double_t)j * ORDER_M * eventInfo.psiEpdA));
	      p_cosAvgsEpdA->Fill(j, TMath::Cos((Double_t)j * ORDER_M * eventInfo.psiEpdA));
	      p_sinAvgsEpdB->Fill(j, TMath::Sin((Double_t)j * ORDER_M * eventInfo.psiEpdB));
	      p_cosAvgsEpdB->Fill(j, TMath::Cos((Double_t)j * ORDER_M * eventInfo.psiEpdB));
	    }
	}
      //=========================================================
      //          End Re-centering
      //=========================================================



      //=========================================================
      //          Event Plane Angle Shifting and Flow
      //=========================================================
          //std::cout << "test 9" << std::endl;

      if (RUN_ITERATION == 2)
	{
          //std::cout << "test 9.1" << std::endl;
	  FlowUtils::shiftPsi(eventInfo, correctionInputFile, ORDER_M, configs.shift_terms);

	  h_psiTpc_FLAT->Fill(eventInfo.psiTpc);
	  h_psiTpcA_FLAT->Fill(eventInfo.psiTpcA);
	  h_psiTpcB_FLAT->Fill(eventInfo.psiTpcB);
	  h_psiEpd_FLAT->Fill(eventInfo.psiEpd);
	  h_psiEpdA_FLAT->Fill(eventInfo.psiEpdA);
	  h_psiEpdB_FLAT->Fill(eventInfo.psiEpdB);

          h2_psiTpc_FLAT_Cent16->Fill(eventInfo.psiTpc, eventInfo.centID);
          h2_psiTpcA_FLAT_Cent16->Fill(eventInfo.psiTpcA, eventInfo.centID);
          h2_psiTpcB_FLAT_Cent16->Fill(eventInfo.psiTpcB, eventInfo.centID);
          h2_psiEpd_FLAT_Cent16->Fill(eventInfo.psiEpd, eventInfo.centID);
          h2_psiEpdA_FLAT_Cent16->Fill(eventInfo.psiEpdA, eventInfo.centID);
          h2_psiEpdB_FLAT_Cent16->Fill(eventInfo.psiEpdB, eventInfo.centID);

	  //=========================================================
	  //          End Event Plane Angle Shifting
	  //=========================================================
          //std::cout << "test 9.1.1" << std::endl;


	  // 2D Correlations between event planes
	  h2_psiEpdATpcA->Fill(eventInfo.psiTpcA,eventInfo.psiEpdA);
	  h2_psiEpdBTpcA->Fill(eventInfo.psiTpcA,eventInfo.psiEpdB);

	  h2_psiEpdATpcB->Fill(eventInfo.psiTpcB,eventInfo.psiEpdA);
	  h2_psiEpdBTpcB->Fill(eventInfo.psiTpcB,eventInfo.psiEpdB);

	  h2_psiTpcATpcB->Fill(eventInfo.psiTpcB,eventInfo.psiTpcA);
          //std::cout << "test 9.1.2" << std::endl;

	  h2_psiEpdAEpdB->Fill(eventInfo.psiEpdB,eventInfo.psiEpdA);
	  //


	  // 1D correlation averages used in calculating resolution using the 3 sub-event method
	  p_TpcAB->Fill(eventInfo.centID,    TMath::Cos(ORDER_N * (eventInfo.psiTpcA - eventInfo.psiTpcB)));

	  p_TpcAEpdA->Fill(eventInfo.centID, TMath::Cos(ORDER_N * (eventInfo.psiTpcA - eventInfo.psiEpdA)));
	  p_TpcAEpdB->Fill(eventInfo.centID, TMath::Cos(ORDER_N * (eventInfo.psiTpcA - eventInfo.psiEpdB)));
	  p_TpcBEpdA->Fill(eventInfo.centID, TMath::Cos(ORDER_N * (eventInfo.psiTpcB - eventInfo.psiEpdA)));
	  p_TpcBEpdB->Fill(eventInfo.centID, TMath::Cos(ORDER_N * (eventInfo.psiTpcB - eventInfo.psiEpdB)));

	  p_EpdAEpdB->Fill(eventInfo.centID, TMath::Cos(ORDER_N * (eventInfo.psiEpdA - eventInfo.psiEpdB)));
	  //


	  //=========================================================
	  //          v_n Scan Plots
	  //=========================================================
	  // 2D searches through eta and centrality for correlations between detectors
	  // SHOULD PROBABLY ONLY USE THIS SECTION IF THE EPD REGIONS COVER THE WHOLE EPD!! Otherwise there might be gaps or undercounting in some bins.
	  Int_t tpcHits = eventInfo.tpcParticles.size();
	  Int_t epdHits = eventInfo.epdParticles.size();
	  Double_t phiTpc;
	  Double_t etaTpc;
	  Double_t phiEpd;
	  Double_t etaEpd;
	  Double_t psiTpc  = eventInfo.psiTpc;
	  Double_t psiEpd  = eventInfo.psiEpd;
	  Double_t psiEpdA = eventInfo.psiEpdA;
	  Double_t psiEpdB = eventInfo.psiEpdB;
	  Double_t psiTpcA = eventInfo.psiTpcA;
	  Double_t psiTpcB = eventInfo.psiTpcB;
	  Int_t centralityID = eventInfo.centID;

	  for (int j = 0; j < epdHits; j++)
	    {
	      phiEpd = eventInfo.epdParticles.at(j).phi;
	      etaEpd = eventInfo.epdParticles.at(j).eta;

	      h2_vnScanEpd->Fill(etaEpd, centralityID, TMath::Cos(ORDER_M * (phiEpd - psiTpc)));
	      h2_vnScanEpdTpcA->Fill(etaEpd, centralityID, TMath::Cos(ORDER_M * (phiEpd - psiTpcA)));
	      h2_vnScanEpdTpcB->Fill(etaEpd, centralityID, TMath::Cos(ORDER_M * (phiEpd - psiTpcB)));
	    }
          //std::cout << "test 9.1.3" << std::endl;
	  for (int j = 0; j < tpcHits; j++)
	    {
	      phiTpc = eventInfo.tpcParticles.at(j).phi;
	      etaTpc = eventInfo.tpcParticles.at(j).eta;

	      h2_vnScanTpc->Fill(etaTpc, centralityID, TMath::Cos(ORDER_M * (phiTpc - psiEpd)));
	      h2_vnScanTpcEpdA->Fill(etaTpc, centralityID, TMath::Cos(ORDER_M * (phiTpc - psiEpdA)));
	      h2_vnScanTpcEpdB->Fill(etaTpc, centralityID, TMath::Cos(ORDER_M * (phiTpc - psiEpdB)));
	    }
	  //=========================================================
	  //          End v_n Scan Plots
	  //=========================================================


	  //=========================================================
	  //        Flow Calculations
	  //=========================================================
	  Double_t jthPhi;
	  Double_t jthEta;
	  Double_t jthpT;
	  Double_t jthmom;
	  Double_t jthKT;
	  Double_t jthRapidity;
	  Double_t jthdEdx;
	  Double_t jthM2;
	  Double_t jthzValue;
	  Double_t jtheff;
	  Double_t psi = eventInfo.psiEpdA;
	  //Double_t psi_epdA = eventInfo.psiEpdA;
	  //Double_t psi_tpcB = eventInfo.psiTpcB;
	  Double_t tpcEfficiency = 1.0;  // Default
	  Int_t centID = eventInfo.centID;

	  if (configs.sqrt_s_NN == 3.0 && centID < 4) continue;  // ONLY LOOKING AT CENTRALITY 60% AND LOWER FOR 3.0 GeV
	  else if (configs.sqrt_s_NN == 3.2 && centID < 4) continue;
	  //else if (configs.sqrt_s_NN == 7.7 && centID < 4) continue;

	  // StPileupUtil cut
	  std::vector<int> m_nchaBins;
	  int NCHA = 20;//, NCHB = 11;
	  float ncha_bins[] = {0,8,10,12,14,18,22,28,34,40,48,52,56,60,64,68,72,76,80,300};
	  for (int in=0;in<NCHA;in++) m_nchaBins.push_back(ncha_bins[in]);
	  //int StPileupUtil::get_nchBin_a() const {
	     int centb = -1;
	     for (unsigned int ic=0;ic<m_nchaBins.size()-1;ic++) {
	        if (m_nch >= m_nchaBins[ic] && m_nch < m_nchaBins[ic+1]) {centb = ic; break;}
	     }    
	     //return centb;
	  //}
	 // if(m_hpucuts_default->GetEntries() > 0 )
	 //	{
	 //       	//std::cout << "StPileupUtil histogram in place" << std::endl;
	 //       	if( m_nmipsum >= m_hpucuts_default->GetBinContent(centb+1)){
	 //       	//std::cout << "m_nmipsum: " << m_nmipsum << ", m_hpucuts_default->GetBinContent(centb+1): "<< m_hpucuts_default->GetBinContent(centb+1) << std::endl;
	 //       	 continue;
	 //       	}
	 //	}

	  // StPileupUtil cut


	  // JUST v1 FOR WEIGHTING (NOT READY TO USE)
	  /*
	  // TPC B region
	  for (UInt_t j = 0; j < eventInfo.tpcParticles.size(); j++)
	    {
	      tpcEfficiency = 1.0; // Make sure efficiency is reset each time.

	      jthPhi = eventInfo.tpcParticles.at(j).phi;
	      jthEta = eventInfo.tpcParticles.at(j).eta;
	      jthpT  = eventInfo.tpcParticles.at(j).pT;
	      jthKT  = eventInfo.tpcParticles.at(j).KT;
	      jthRapidity = eventInfo.tpcParticles.at(j).rapidity;
	      if (jthPhi == FlowUtils::D_BAD_VALUE || jthpT == FlowUtils::D_BAD_VALUE || jthEta == FlowUtils::D_BAD_VALUE ||
		  jthKT == FlowUtils::D_BAD_VALUE  || jthRapidity == FlowUtils::D_BAD_VALUE) 
		continue;

	      if (efficienciesFound && configs.sqrt_s_NN == 3.0)
		{
		  if      (eventInfo.tpcParticles.at(j).prTag) tpcEfficiency = FlowUtils::getTpcEff(jthRapidity - Y_MID, jthpT, h2_tracking_pr);
		  else if (eventInfo.tpcParticles.at(j).deTag) tpcEfficiency = FlowUtils::getTpcEff(jthRapidity - Y_MID, jthpT, h2_tracking_de);
		  else if (eventInfo.tpcParticles.at(j).trTag) tpcEfficiency = FlowUtils::getTpcEff(jthRapidity - Y_MID, jthpT, h2_tracking_tr);
		}
	      if (tpcEfficiency == -1) { continue; }
		  
	      if (eventInfo.tpcParticles.at(j).isInTpcB)
		{ 
		  //p2_v1_eta_cent_TPCB->Fill(centID, jthEta, TMath::Cos(1.0 * (jthPhi - psi_epdA))); 

		  if (eventInfo.tpcParticles.at(j).prTag)
		    { p2_v1_pT_eta_TPCB_pr->Fill(jthEta, jthpT, TMath::Cos(1.0 * (jthPhi - psi_epdA)) / tpcEfficiency); }
		}
	    }// END TPC v1

	  // EPD regions

	  for (UInt_t j = 0; j < eventInfo.epdParticles.size(); j++)
	    {
	      jthPhi = eventInfo.epdParticles.at(j).phi;
	      jthEta = eventInfo.epdParticles.at(j).eta;
	      if (jthPhi == FlowUtils::D_BAD_VALUE || jthEta == FlowUtils::D_BAD_VALUE)
		continue;

	      if (eventInfo.epdParticles.at(j).isInEpdA)
		{ p2_v1_eta_cent_EPDA->Fill(centID, jthEta, TMath::Cos(1.0 * (jthPhi - psi_tpcB))); }
	      else if (eventInfo.epdParticles.at(j).isInEpdB)
		{ p2_v1_eta_cent_EPDB->Fill(centID, jthEta, TMath::Cos(1.0 * (jthPhi - psi_tpcB))); }	    
	    }// End EPD v1
	  */

	  // "OBSERVED" FLOW VALUES HERE, no resolutions or efficiencies
          //std::cout << "test 9.1.4" << std::endl;
	  for (UInt_t j = 0; j < eventInfo.tpcParticles.size(); j++) // tpc particles loop
	    {
	      jthPhi = eventInfo.tpcParticles.at(j).phi;
	      jthEta = eventInfo.tpcParticles.at(j).eta;
	      jthpT  = eventInfo.tpcParticles.at(j).pT;
	      jthmom  = eventInfo.tpcParticles.at(j).mom;
	      jthKT  = eventInfo.tpcParticles.at(j).KT;
	      jthRapidity = eventInfo.tpcParticles.at(j).rapidity;
	      jtheff = eventInfo.tpcParticles.at(j).eff;
	      jthdEdx = eventInfo.tpcParticles.at(j).dEdx;
	      jthM2 = eventInfo.tpcParticles.at(j).M2;
	      jthzValue = eventInfo.tpcParticles.at(j).zValue;
	      //jtheff = 1.0; //Disable efficiency correction for he3 and he4
                          //std::cout << "he3 jtheff: " << jtheff << std::endl;
	      if (jthPhi == FlowUtils::D_BAD_VALUE || jthpT == FlowUtils::D_BAD_VALUE || 
		  jthKT == FlowUtils::D_BAD_VALUE  || jthRapidity == FlowUtils::D_BAD_VALUE) 
		continue;

	      // PI+
	      // Normal acceptance 0 < yCM < 0.5
	      if (eventInfo.tpcParticles.at(j).ppTag && 
		  jthpT >= configs.pt_norm_pi_low && jthpT <= configs.pt_norm_pi_high &&
		  jthRapidity - Y_MID > configs.yCM_norm_pi_low && jthRapidity - Y_MID < configs.yCM_norm_pi_high)
		{ p_vn_pp_obs->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi))); }
	      // PI-
	      // Normal acceptance 0 < yCM < 0.5
	      else if (eventInfo.tpcParticles.at(j).pmTag && 
		       jthpT >= configs.pt_norm_pi_low && jthpT <= configs.pt_norm_pi_high &&
		       jthRapidity - Y_MID > configs.yCM_norm_pi_low && jthRapidity - Y_MID < configs.yCM_norm_pi_high)
		{ p_vn_pm_obs->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi))); }
	      // K+
	      // Normal acceptance 0 < yCM < 0.5
	      else if (eventInfo.tpcParticles.at(j).kpTag && 
		       jthpT >= configs.pt_norm_ka_low && jthpT <= configs.pt_norm_ka_high &&
		       jthRapidity - Y_MID > configs.yCM_norm_ka_low && jthRapidity - Y_MID < configs.yCM_norm_ka_high)
		{ p_vn_kp_obs->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi))); }
	      // K-
	      // Normal acceptance 0 < yCM < 0.5
	      else if (eventInfo.tpcParticles.at(j).kmTag && 
		       jthpT >= configs.pt_norm_ka_low && jthpT <= configs.pt_norm_ka_high &&
		       jthRapidity - Y_MID > configs.yCM_norm_ka_low && jthRapidity - Y_MID < configs.yCM_norm_ka_high)
		{ p_vn_km_obs->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi))); }
	      // PROTON
	      else if (eventInfo.tpcParticles.at(j).prTag)
		{
		  // NORMAL ACCEPTANCE 0 < y_cm < 0.5
		  if (jthRapidity - Y_MID > configs.yCM_norm_pr_low && jthRapidity - Y_MID < configs.yCM_norm_pr_high &&
		      jthpT > configs.pt_norm_pr_low && jthpT < configs.pt_norm_pr_high)
		    { p_vn_pr_obs->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi))); }
		  // ALTERNATE ACCEPTANCE REGION
		  if (jthKT/1.0 >= configs.KT_pdt_low && jthKT/1.0 <= configs.KT_pdt_high &&
		      jthRapidity - Y_MID > configs.yCM_alt_pr_low && jthRapidity - Y_MID < configs.yCM_alt_pr_high)
		    { p_vn_pr_alt_obs->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi))); }
		}
	      // DEUTERON
	      else if (eventInfo.tpcParticles.at(j).deTag && 
		       jthKT/2.0 >= configs.KT_pdt_low && jthKT/2.0 <= configs.KT_pdt_high &&
		       jthRapidity - Y_MID > configs.yCM_norm_de_low && jthRapidity - Y_MID < configs.yCM_norm_de_high)
		{ p_vn_de_obs->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi))); }

	      // TRITON
	      else if (eventInfo.tpcParticles.at(j).trTag && 
		       jthKT/3.0 >= configs.KT_pdt_low && jthKT/3.0 <= configs.KT_pdt_high &&
		       jthRapidity - Y_MID > configs.yCM_norm_tr_low && jthRapidity - Y_MID < configs.yCM_norm_tr_high)
		{ p_vn_tr_obs->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi))); }
	      // HELIUM3
	      else if (eventInfo.tpcParticles.at(j).he3Tag && 
		       jthKT/3.0 >= configs.KT_pdt_low && jthKT/3.0 <= configs.KT_pdt_high &&
		       jthRapidity - Y_MID > configs.yCM_norm_he3_low && jthRapidity - Y_MID < configs.yCM_norm_he3_high)
		//{ p_vn_he3_obs->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi))); }
		{  
                  //he3_eff = he3_eff*(Float_t)h2_tracking_he3->GetBinContent(h2_tracking_he3->FindBin(jthRapidity - Y_MID, 2*jthpT));
                  //he3_eff = he3_eff*(Float_t)tpc_he3->GetBinContent(tpc_he3->FindBin(2*jthmom));
		  //if(he3_eff>1.) he3_eff = 1.;
                  //std::cout << "2285 he3Tag. jtheff: " << jtheff << std::endl;
		  if(jtheff>0.) p_vn_he3_obs->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)),1./jtheff); 
		}
	      // HELIUM4
	      else if (eventInfo.tpcParticles.at(j).he4Tag && 
		       jthKT/4.0 >= configs.KT_pdt_low && jthKT/4.0 <= configs.KT_pdt_high &&
		       jthRapidity - Y_MID > configs.yCM_norm_he4_low && jthRapidity - Y_MID < configs.yCM_norm_he4_high)
		{ p_vn_he4_obs->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi))); }
	    } //  end tpc particles loop
	  //////
          //std::cout << "test 9.1.5" << std::endl;


	  // RESOLUTION CORRECTED FLOW VALUES HERE
	  bool b_de = 0; // check if the this event has deuteron at all
	  if (resolutionsFound)
	    {
	      TH1D *resolutionHistogram = (configs.fixed_target) ? (TH1D*)resolutionInputFile->Get("h_resolutions") : (TH1D*)resolutionInputFile->Get("h_resolutions_2sub");
	      Double_t resolution = resolutionHistogram->GetBinContent(centID+1);	      
	      if (resolution == 0.0) continue;  // Skip centralities without resolutions.
              //he3_eff = 1./mCentWeight;

          //std::cout << "test 9.1.6.1" << std::endl;
	      for (UInt_t j = 0; j < eventInfo.tpcParticles.size(); j++)
		{
                  bool b_newEvent = 0;
                  if(eventID == -1 || eventID != i_eventID){
                          b_newEvent = 1;
                          eventID = i_eventID;
                          //std::cout <<"initial evt ID: " << eventID << std::endl;
                  } 
                  if(b_newEvent) d_allEvents++;
		  tpcEfficiency = 1.0; // Make sure efficiency is reset each time.

		  jthPhi = eventInfo.tpcParticles.at(j).phi;
		  jthEta = eventInfo.tpcParticles.at(j).eta;
		  jthpT  = eventInfo.tpcParticles.at(j).pT;
		  jthKT  = eventInfo.tpcParticles.at(j).KT;
	          jthmom  = eventInfo.tpcParticles.at(j).mom;
		  jthRapidity = eventInfo.tpcParticles.at(j).rapidity;
		  jtheff = eventInfo.tpcParticles.at(j).eff;
	          jthdEdx = eventInfo.tpcParticles.at(j).dEdx;
	          jthM2 = eventInfo.tpcParticles.at(j).M2;
	          jthzValue = eventInfo.tpcParticles.at(j).zValue;
	          //jtheff = 1.0; //Disable efficiency correction for he3 and he4
		  if (jthPhi == FlowUtils::D_BAD_VALUE || jthpT == FlowUtils::D_BAD_VALUE || 
		      jthKT == FlowUtils::D_BAD_VALUE  || jthRapidity == FlowUtils::D_BAD_VALUE) 
		    continue;
          //std::cout << "test 9.1.6.1.1" << std::endl;
		  
		  h_simulationCheck_total->Fill(1);
		  if (efficienciesFound && configs.sqrt_s_NN == 3.0)
		    {
          //std::cout << "test 9.1.6.1.1.1" << std::endl;
		  tpcEfficiency = 1.0; // Make sure efficiency is reset each time.
		      if      (eventInfo.tpcParticles.at(j).ppTag) tpcEfficiency = FlowUtils::getTpcEff(jthRapidity - Y_MID, jthpT, h2_tracking_pp);// std::cout << "test 9.1.6.1.1.2" << std::endl;
		      else if (eventInfo.tpcParticles.at(j).pmTag) tpcEfficiency = FlowUtils::getTpcEff(jthRapidity - Y_MID, jthpT, h2_tracking_pm);// std::cout << "test 9.1.6.1.1.3" << std::endl;
		      else if (eventInfo.tpcParticles.at(j).kpTag) tpcEfficiency = FlowUtils::getTpcEff(jthRapidity - Y_MID, jthpT, h2_tracking_kp);// std::cout << "test 9.1.6.1.1.4" << std::endl;
		      else if (eventInfo.tpcParticles.at(j).kmTag) tpcEfficiency = FlowUtils::getTpcEff(jthRapidity - Y_MID, jthpT, h2_tracking_km);// std::cout << "test 9.1.6.1.1.5" << std::endl;
		      else if (eventInfo.tpcParticles.at(j).prTag) tpcEfficiency = FlowUtils::getTpcEff(jthRapidity - Y_MID, jthpT, h2_tracking_pr);// std::cout << "test 9.1.6.1.1.6" << std::endl;
		      else if (eventInfo.tpcParticles.at(j).deTag) tpcEfficiency = FlowUtils::getTpcEff(jthRapidity - Y_MID, jthpT, h2_tracking_de);// std::cout << "test 9.1.6.1.1.7" << std::endl;
		      else if (eventInfo.tpcParticles.at(j).trTag) tpcEfficiency = FlowUtils::getTpcEff(jthRapidity - Y_MID, jthpT, h2_tracking_tr);// std::cout << "test 9.1.6.1.1.8" << std::endl;
		      //else if (eventInfo.tpcParticles.at(j).he3Tag) tpcEfficiency = FlowUtils::getTpcEff(jthRapidity - Y_MID, jthpT, h2_tracking_he3);
         //std::cout << "test 9.1.6.1.1.9" << std::endl;
		    }
          //std::cout << "test 9.1.6.1.2" << std::endl;
		  if (tpcEfficiency == -1) // Checks here for tracks with no recorded efficiency values.
		    { 
		      if (eventInfo.tpcParticles.at(j).ppTag)
			{
			  h_simulationCheck_pp->Fill(1);
			  h2_pT_vs_yCM_pp_noEff->Fill(jthRapidity - Y_MID, jthpT);
			}
		      else if (eventInfo.tpcParticles.at(j).pmTag)
			{
			  h_simulationCheck_pm->Fill(1);
			  h2_pT_vs_yCM_pm_noEff->Fill(jthRapidity - Y_MID, jthpT);
			}
		      else if (eventInfo.tpcParticles.at(j).kpTag)
			{
			  h_simulationCheck_kp->Fill(1);
			  h2_pT_vs_yCM_kp_noEff->Fill(jthRapidity - Y_MID, jthpT);
			}
		      else if (eventInfo.tpcParticles.at(j).kmTag)
			{
			  h_simulationCheck_km->Fill(1);
			  h2_pT_vs_yCM_km_noEff->Fill(jthRapidity - Y_MID, jthpT);
			}
		      else if (eventInfo.tpcParticles.at(j).prTag)
			{
			  h_simulationCheck_pr->Fill(1);
			  h2_pT_vs_yCM_pr_noEff->Fill(jthRapidity - Y_MID, jthpT);
			}
		      else if (eventInfo.tpcParticles.at(j).deTag) 
			{
			  h_simulationCheck_de->Fill(1); 
			  h2_pT_vs_yCM_de_noEff->Fill(jthRapidity - Y_MID, jthpT);
			}
		      else if (eventInfo.tpcParticles.at(j).trTag) 
			{
			  h_simulationCheck_tr->Fill(1); 
			  h2_pT_vs_yCM_tr_noEff->Fill(jthRapidity - Y_MID, jthpT);
			}
		      
		      //continue; 
		    }
          //std::cout << "test 9.1.6.1.3" << std::endl;
		  if (jtheff == -1) // Checks here for tracks with no recorded efficiency values.
                    {
		      if (eventInfo.tpcParticles.at(j).he3Tag) 
			{
			  h_simulationCheck_he3->Fill(1); 
			  h2_pT_vs_yCM_he3_noEff->Fill(jthRapidity - Y_MID, 2*jthpT);
			}
		      else if (eventInfo.tpcParticles.at(j).he4Tag) 
			{
			  h_simulationCheck_he4->Fill(1); 
			  h2_pT_vs_yCM_he4_noEff->Fill(jthRapidity - Y_MID, 2*jthpT);
			}
                    
		      //continue; 
                    }


		  // PI+
		  if (eventInfo.tpcParticles.at(j).ppTag)
		    {
		      // Normal acceptance 0 < yCM < 0.5
		      if (jthpT >= configs.pt_norm_pi_low && jthpT <= configs.pt_norm_pi_high &&
			  jthRapidity - Y_MID > configs.yCM_norm_pi_low && jthRapidity - Y_MID < configs.yCM_norm_pi_high)
			{
			  p2_vn_yCM_cent_pp->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p_vn_pp->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); 
			  p2_vn_pT_cent_pp->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p2_vn_KT_cent_pp->Fill(centID, jthKT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			}
		      // Extended rapidity acceptance 0.5 <= yCM < 1.0
		      else if (jthpT >= configs.pt_yExt_pi_low && jthpT <= configs.pt_yExt_pi_high &&
			       jthRapidity - Y_MID >= configs.yCM_yExt_pi_low && jthRapidity - Y_MID < configs.yCM_yExt_pi_high)
			{
			  p2_vn_yCM_cent_pp->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p_vn_pp_ext->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			}
		      // rapidity stratified by pT
		      if (jthRapidity - Y_MID > -1.0 && jthRapidity - Y_MID < 1.0 && 
			  jthpT > configs.pt_norm_pi_low && jthpT < configs.pt_norm_pi_high)
			{ p2_vn_pT_vs_yCM_pp->Fill(jthRapidity - Y_MID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); }
		    }
		  
		  // PI-
		  else if (eventInfo.tpcParticles.at(j).pmTag)
		    {
		      // Normal acceptance 0 < yCM < 0.5
		      if (jthpT >= configs.pt_norm_pi_low && jthpT <= configs.pt_norm_pi_high &&
			  jthRapidity - Y_MID > configs.yCM_norm_pi_low && jthRapidity - Y_MID < configs.yCM_norm_pi_high)
			{
			  p2_vn_yCM_cent_pm->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p_vn_pm->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); 
			  p2_vn_pT_cent_pm->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p2_vn_KT_cent_pm->Fill(centID, jthKT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			}
		      // Extended rapidity acceptance 0.5 <= yCM < 1.0
		      else if (jthpT >= configs.pt_yExt_pi_low && jthpT <= configs.pt_yExt_pi_high &&
			       jthRapidity - Y_MID >= configs.yCM_yExt_pi_low && jthRapidity - Y_MID < configs.yCM_yExt_pi_high)
			{
			  p2_vn_yCM_cent_pm->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p_vn_pm_ext->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			}
		      // rapidity stratified by pT
		      if (jthRapidity - Y_MID > -1.0 && jthRapidity - Y_MID < 1.0 && 
			  jthpT > configs.pt_norm_pi_low && jthpT < configs.pt_norm_pi_high)
			{ p2_vn_pT_vs_yCM_pm->Fill(jthRapidity - Y_MID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); }
		    }

		  // K+
		  else if (eventInfo.tpcParticles.at(j).kpTag)
		    {
		      // Normal acceptance 0 < yCM < 0.5
		      if (jthpT >= configs.pt_norm_ka_low && jthpT <= configs.pt_norm_ka_high &&
			  jthRapidity - Y_MID > configs.yCM_norm_ka_low && jthRapidity - Y_MID < configs.yCM_norm_ka_high)
			{
			  p2_vn_yCM_cent_kp->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p_vn_kp->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); 
			  p2_vn_pT_cent_kp->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p2_vn_KT_cent_kp->Fill(centID, jthKT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			}
		      // Extended rapidity acceptance 0.5 <= yCM < 1.0
		      else if (jthpT >= configs.pt_yExt_ka_low && jthpT <= configs.pt_yExt_ka_high &&
			       jthRapidity - Y_MID >= configs.yCM_yExt_ka_low && jthRapidity - Y_MID < configs.yCM_yExt_ka_high)
			{
			  p2_vn_yCM_cent_kp->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p_vn_kp_ext->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			}
		    }

		  // K-
		  else if (eventInfo.tpcParticles.at(j).kmTag)
		    {
		      // Normal acceptance 0 < yCM < 0.5
		      if (jthpT >= configs.pt_norm_ka_low && jthpT <= configs.pt_norm_ka_high &&
			  jthRapidity - Y_MID > configs.yCM_norm_ka_low && jthRapidity - Y_MID < configs.yCM_norm_ka_high)
			{
			  p2_vn_yCM_cent_km->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p_vn_km->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); 
			  p2_vn_pT_cent_km->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p2_vn_KT_cent_km->Fill(centID, jthKT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			}
		      // Extended rapidity acceptance 0.5 <= yCM < 1.0
		      else if (jthpT >= configs.pt_yExt_ka_low && jthpT <= configs.pt_yExt_ka_high &&
			       jthRapidity - Y_MID >= configs.yCM_yExt_ka_low && jthRapidity - Y_MID < configs.yCM_yExt_ka_high)
			{
			  p2_vn_yCM_cent_km->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p_vn_km_ext->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			}
		    }

		  // PROTON
		  else if (eventInfo.tpcParticles.at(j).prTag)
		    {
		      if (jthRapidity - Y_MID > -1.0 && jthRapidity - Y_MID < 1.0 && 
			  jthpT > 0.4 && jthpT < 2.5)
			{ p2_vn_pT_vs_yCM_pr->Fill(jthRapidity - Y_MID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); }
		      
		      // RAPIDITY DEPENDENT PLOT
		      if (jthRapidity - Y_MID > configs.yCM_yDep_pr_low && jthRapidity - Y_MID < configs.yCM_yDep_pr_high && 
			  jthpT > configs.pt_yDep_pr_low && jthpT < configs.pt_yDep_pr_high)
			{ p2_vn_yCM_cent_pr->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); }

		      // NORMAL ACCEPTANCE 0 < y_cm < 0.5
		      if (jthRapidity - Y_MID > configs.yCM_yTot_LiNu_low && jthRapidity - Y_MID < configs.yCM_yTot_LiNu_high &&
			  jthpT > configs.pt_norm_pr_low && jthpT < configs.pt_norm_pr_high)
			{ 
			  p_vn_pr->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); 
			  p2_vn_pT_cent_pr->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p2_vn_KT_cent_pr->Fill(centID, jthKT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);

			  if (jthpT < 1.0)
			    { p_vn_pr_pTlt1->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); }
			  else if (jthpT > 1.0)
			    { p_vn_pr_pTgt1->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); }
			}
		      // EXTENDED RAPIDITY 0.5 <= y_cm < 1.0
		      else if (jthRapidity - Y_MID >= configs.yCM_yExt_pr_low && jthRapidity - Y_MID < configs.yCM_yExt_pr_high &&
			       jthpT > configs.pt_yExt_pr_low && jthpT < configs.pt_yExt_pr_high)
			{ 
			  p_vn_pr_ext->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); 
			  p2_vn_pT_cent_pr_ext->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			}
          //std::cout << "test 9.1.6.1.4" << std::endl;

		      // ALTERNATE ACCEPTANCE REGION
		      if (jthKT/1.0 >= configs.KT_pdt_low && jthKT/1.0 <= configs.KT_pdt_high &&
			  jthRapidity - Y_MID > configs.yCM_alt_pr_low && jthRapidity - Y_MID < configs.yCM_alt_pr_high)
			{ 
			  p_vn_pr_alt->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p2_vn_yCM_cent_pr_alt->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p2_vn_pT_cent_pr_alt->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  p2_vn_KT_cent_pr_alt->Fill(centID, jthKT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  h2_dndDeltaPhi_vs_cent_pr_alt->Fill(centID, jthPhi - psi);
			}

		      if (jthpT >= configs.pt_yDep_pr_low && jthpT <= configs.pt_yDep_pr_high &&
		       jthRapidity - Y_MID > configs.yCM_yMid_LiNu_low && jthRapidity - Y_MID < configs.yCM_yMid_LiNu_high)
		       {
		         p2_vn_pT_cent_pr_yMid->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
		       }
		        if (jthpT >= configs.pt_yDep_pr_low && jthpT <= configs.pt_yDep_pr_high &&
		         jthRapidity - Y_MID > configs.yCM_yFor_LiNu_low && jthRapidity - Y_MID < configs.yCM_yFor_LiNu_high)
		       {
		         p2_vn_pT_cent_pr_yFor->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
		       }
		        if (jthpT >= configs.pt_yDep_pr_low && jthpT <= configs.pt_yDep_pr_high &&
		         jthRapidity - Y_MID > configs.yCM_yExt_LiNu_low && jthRapidity - Y_MID < configs.yCM_yExt_LiNu_high)
		       {
		         p2_vn_pT_cent_pr_yExt->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
		       }
		        if (jthpT >= configs.pt_yDep_pr_low && jthpT <= configs.pt_yDep_pr_high &&
		         jthRapidity - Y_MID > configs.yCM_yEnd_LiNu_low && jthRapidity - Y_MID < configs.yCM_yEnd_LiNu_high)
		       {
		         p2_vn_pT_cent_pr_yEnd->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
		       }

		      if (jthKT/1.0 >= configs.KT_pdt_low && jthKT/1.0 <= configs.KT_pdt_high &&
			  jthRapidity - Y_MID > 0.0 && jthRapidity - Y_MID < 0.6)
			{
			  p_vn_pr_alt_y0to0p6->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); 
			}

		      if (jthKT/1.0 >= configs.KT_pdt_low && jthKT/1.0 <= configs.KT_pdt_high &&
			  jthRapidity - Y_MID > 0.6 && jthRapidity - Y_MID < 1.0)
			{
			  p_vn_pr_alt_y0p6to1p0->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); 
			}
		      if (jthKT/1.0 >= configs.KT_pdt_low && jthKT/1.0 <= configs.KT_pdt_high &&
			  jthRapidity/Y_BEAM > -1.0 && jthRapidity/Y_BEAM < 0.0)
			{ 
			  p2_vn_yOverYbeam_cent_pr_alt->Fill(centID, jthRapidity/Y_BEAM, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			}
		      // RAPIDITY SYMMETRIC ACCEPTANCE REGION
		      if (jthRapidity - Y_MID > configs.yCM_ySym_pr_low && jthRapidity - Y_MID < configs.yCM_ySym_pr_high && 
			  jthpT > configs.pt_ySym_pr_low && jthpT < configs.pt_ySym_pr_high)
			{ p2_vn_yCM_cent_pr_symmetry->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); }

		      // ONLY FORWARD ACCEPTANCE REGION
		      if (jthRapidity - Y_MID > configs.yCM_yFor_pr_low && jthRapidity - Y_MID < configs.yCM_yFor_pr_high && 
			  jthpT > configs.pt_yFor_pr_low && jthpT < configs.pt_yFor_pr_high)
			{ p_vn_pr_for->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); }
		    }

		  // DEUTERON
		  else if (eventInfo.tpcParticles.at(j).deTag)
		    {
      		      int mCentrality = Cent16toCent9(centID);
      		      Int_t Cent=-1;             

      		      if(mCentrality < 2 ) continue; //Cent = -1 ;//return kStOK;
      		      else if(mCentrality < 4 ) Cent=0;
      		      else if (mCentrality < 7) Cent=1;
      		      else if (mCentrality < 9) Cent=2;
			

		      if(!(fabs(jthzValue-0.05)<0.4 && jthpT>0.6))
			      continue;
                      //if(jthmom<0.6)
				//continue;
                      jtheff = (efficienciesFound) ?  jtheff*(Float_t)h2_tracking_de->GetBinContent(h2_tracking_de->FindBin(jthRapidity - Y_MID, jthpT)) : jtheff;
                      jtheff = (efficienciesFound) ?  jtheff*(Float_t)tpc_de->GetBinContent(tpc_de->FindBin(jthmom)) : jtheff;
                      if(jthmom>3.2) jtheff = (efficienciesFound) ?  jtheff*(Float_t)tof_d->GetBinContent(tof_d->FindBin(jthmom)) : jtheff;
                      if(jthmom>3.2) jtheff = (efficienciesFound) ?  jtheff*(Float_t)tofmatch->GetBinContent(tofmatch->FindBin(jthEta, jthpT)) : jtheff;
                      if(jtheff>1.)
                              jtheff = 1.;

                      if(jtheff>0.) { 
			      b_de = true;
			      if(b_de && b_newEvent)  d_deEvents ++;
			      h_event_de->Fill(i_eventID);
                              hDpty[0]->Fill(jthRapidity - Y_MID, jthpT);     
                              hDpty[Cent+1]->Fill(jthRapidity - Y_MID, jthpT);            
                              hDpty_weight[0]->Fill(jthRapidity - Y_MID, jthpT, 1./jtheff);     
                              hDpty_weight[Cent+1]->Fill(jthRapidity - Y_MID, jthpT, 1./jtheff);
			      //std::cout <<  "Rapidity: " << jthRapidity - Y_MID <<"; "<< "pT: "<< jthpT << "; efficiency: " << jtheff <<"; "<< "z value deuteron: "<< jthzValue << std::endl;
			      //std::cout << "efficiency: " << jtheff <<"; "<< "z value deuteron: "<< jthzValue << std::endl;
			      //std::cout << "Rapidity: " << jthRapidity - Y_MID <<"; "<< "pT: "<< jthpT << std::endl;
		  	      h2_zd_vs_mom_check->Fill(jthmom, jthzValue);
                              hDMass2p[0]->Fill(jthmom,jthM2);     
                              hDMass2p[Cent+1]->Fill(jthmom,jthM2);
                              hDdEdxp[0]->Fill(jthmom,jthdEdx);
                              hDdEdxp[Cent+1]->Fill(jthmom,jthdEdx);
        
                      //d_eff = 1./mCentWeight;

		      // RAPIDITY DEPENDENT PLOT
		      if (jthKT/2.0 >= configs.KT_pdt_low && jthKT/2.0 <= configs.KT_pdt_high &&
			  jthRapidity - Y_MID > configs.yCM_norm_de_low && jthRapidity - Y_MID < configs.yCM_norm_de_high)
			{ p2_vn_yCM_cent_de_alt->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff); }
			//{ p2_vn_yCM_cent_de_alt->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); }

		      if (jthRapidity - Y_MID > configs.yCM_yTot_LiNu_low && jthRapidity - Y_MID < configs.yCM_yTot_LiNu_high && 
			  jthpT > configs.pt_yDep_de_low && jthpT < configs.pt_yDep_de_high)
			{
			  p2_vn_yCM_cent_de->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
			  //p2_vn_yCM_cent_de->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);

			  p_vn_de->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff); 
			  p2_vn_pT_cent_de->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
			  p2_vn_KT_cent_de->Fill(centID, jthKT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
			  //p_vn_de->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); 
			  //p2_vn_pT_cent_de->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  //p2_vn_KT_cent_de->Fill(centID, jthKT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  h2_dndDeltaPhi_vs_cent_de->Fill(centID, jthPhi - psi);
			}

		      if (jthpT >= configs.pt_yDep_de_low && jthpT <= configs.pt_yDep_de_high &&
		       jthRapidity - Y_MID > configs.yCM_yMid_LiNu_low && jthRapidity - Y_MID < configs.yCM_yMid_LiNu_high)
		       {
		         p2_vn_pT_cent_de_yMid->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
		         //p2_vn_pT_cent_de_yMid->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
		       }
		        if (jthpT >= configs.pt_yDep_de_low && jthpT <= configs.pt_yDep_de_high &&
		         jthRapidity - Y_MID > configs.yCM_yFor_LiNu_low && jthRapidity - Y_MID < configs.yCM_yFor_LiNu_high)
		       {
		         p2_vn_pT_cent_de_yFor->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
		         //p2_vn_pT_cent_de_yFor->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
		       }
		        if (jthpT >= configs.pt_yDep_de_low && jthpT <= configs.pt_yDep_de_high &&
		         jthRapidity - Y_MID > configs.yCM_yExt_LiNu_low && jthRapidity - Y_MID < configs.yCM_yExt_LiNu_high)
		       {
		         p2_vn_pT_cent_de_yExt->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
		         //p2_vn_pT_cent_de_yExt->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
		       }
		        if (jthpT >= configs.pt_yDep_de_low && jthpT <= configs.pt_yDep_de_high &&
		         jthRapidity - Y_MID > configs.yCM_yEnd_LiNu_low && jthRapidity - Y_MID < configs.yCM_yEnd_LiNu_high)
		       {
		         p2_vn_pT_cent_de_yEnd->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
		         //p2_vn_pT_cent_de_yEnd->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
		       }

		      //if (jthKT/2.0 >= configs.KT_pdt_low && jthKT/2.0 <= configs.KT_pdt_high &&
		      if (jthRapidity - Y_MID > configs.yCM_yDep_de_low && jthRapidity - Y_MID < configs.yCM_yDep_de_high && 
			  jthRapidity - Y_MID > 0.0 && jthRapidity - Y_MID < 0.6)
			{
			  p_vn_de_y0to0p6->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff); 
			  //p_vn_de_y0to0p6->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); 
			}

		      //if (jthKT/2.0 >= configs.KT_pdt_low && jthKT/2.0 <= configs.KT_pdt_high &&
		      if (jthRapidity - Y_MID > configs.yCM_yDep_de_low && jthRapidity - Y_MID < configs.yCM_yDep_de_high && 
			  jthRapidity - Y_MID > 0.6 && jthRapidity - Y_MID < 1.0)
			{
			  p_vn_de_y0p6to1p0->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff); 
			  //p_vn_de_y0p6to1p0->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); 
			}

		      //if (jthKT/2.0 >= configs.KT_pdt_low && jthKT/2.0 <= configs.KT_pdt_high &&
		      if (jthRapidity - Y_MID > configs.yCM_yDep_de_low && jthRapidity - Y_MID < configs.yCM_yDep_de_high && 
			  jthRapidity/Y_BEAM > -1.0 && jthRapidity/Y_BEAM < 0.0)
			{
			  p2_vn_yOverYbeam_cent_de->Fill(centID, jthRapidity/Y_BEAM, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
			  //p2_vn_yOverYbeam_cent_de->Fill(centID, jthRapidity/Y_BEAM, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			}
                      } // End eff > 1
		    }

		  // TRITON
		  else if (eventInfo.tpcParticles.at(j).trTag)
		    {
      		      int mCentrality = Cent16toCent9(centID);
      		      Int_t Cent=-1;             
		      jtheff = -1.0;

      		      if(mCentrality < 2 ) continue; //Cent = -1 ;//return kStOK;
      		      else if(mCentrality < 4 ) Cent=0;
      		      else if (mCentrality < 7) Cent=1;
      		      else if (mCentrality < 9) Cent=2;
			
		//      if(!(fabs(jthzValue-0.05)<0.4 && jthpT>0.8))
		//	      continue;
                      //if(jthmom<0.6)
				//continue;
		      jtheff = 1./mCentWeight;
		      //std::cout << "eff raw: " << jtheff <<std::endl;
                      jtheff = (efficienciesFound) ?  jtheff*(Float_t)h2_tracking_tr->GetBinContent(h2_tracking_tr->FindBin(jthRapidity - Y_MID, jthpT)) : jtheff;
		      //std::cout << "eff tracking: " << jtheff <<std::endl;
                      jtheff = (efficienciesFound) ?  jtheff*(Float_t)tpc_tr->GetBinContent(tpc_tr->FindBin(jthmom)) : jtheff;
		      //std::cout << "eff tpc_t: " << jtheff <<std::endl;
                      if(jthmom>3.8) (efficienciesFound) ?  jtheff = jtheff*(Float_t)tof_t->GetBinContent(tof_t->FindBin(jthmom)) : jtheff;
                      if(jthmom>3.8) (efficienciesFound) ?  jtheff = jtheff*(Float_t)tofmatch->GetBinContent(tofmatch->FindBin(jthEta, jthpT)) : jtheff;
		      //if(jthmom>3.8)  std::cout << "eff tpc_tof: " << jtheff <<std::endl;
                      if(jtheff>1.)
                              jtheff = 1.;

                      if(jtheff>0.) { 
			      //b_tr = true;
			      //if(b_tr && b_newEvent)  d_trEvents ++;
			      //h_event_tr->Fill(i_eventID);
                              hTpty[0]->Fill(jthRapidity - Y_MID, jthpT);     
                              hTpty[Cent+1]->Fill(jthRapidity - Y_MID, jthpT);            
                              hTpty_weight[0]->Fill(jthRapidity - Y_MID, jthpT, 1./jtheff);     
                              hTpty_weight[Cent+1]->Fill(jthRapidity - Y_MID, jthpT, 1./jtheff);
			      //std::cout <<  "Rapidity: " << jthRapidity - Y_MID <<"; "<< "pT: "<< jthpT << "; efficiency: " << jtheff <<"; "<< "z value triton: "<< jthzValue << std::endl;
			      //std::cout << "efficiency: " << jtheff <<"; "<< "z value triton: "<< jthzValue << std::endl;
			      //std::cout << "Rapidity: " << jthRapidity - Y_MID <<"; "<< "pT: "<< jthpT << std::endl;
		  	      h2_zt_vs_mom_check->Fill(jthmom, jthzValue);
                              hTMass2p[0]->Fill(jthmom,jthM2);     
                              hTMass2p[Cent+1]->Fill(jthmom,jthM2);
                              hTdEdxp[0]->Fill(jthmom,jthdEdx);
                              hTdEdxp[Cent+1]->Fill(jthmom,jthdEdx);
			
		      // RAPIDITY DEPENDENT PLOT
		      if (jthKT/3.0 >= configs.KT_pdt_low && jthKT/3.0 <= configs.KT_pdt_high &&
			  jthRapidity - Y_MID > configs.yCM_norm_tr_low && jthRapidity - Y_MID < configs.yCM_norm_tr_high)
			{ p2_vn_yCM_cent_tr_alt->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff); }
			//{ p2_vn_yCM_cent_tr_alt->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); }

		      //if (jthRapidity - Y_MID > configs.yCM_yDep_tr_low && jthRapidity - Y_MID < configs.yCM_yDep_tr_high && 
		      if (jthRapidity - Y_MID > configs.yCM_yTot_LiNu_low && jthRapidity - Y_MID < configs.yCM_yTot_LiNu_high && 
			  jthpT > configs.pt_yDep_tr_low && jthpT < configs.pt_yDep_tr_high)
			{
			  p2_vn_yCM_cent_tr->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
			  //p2_vn_yCM_cent_tr->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);

			  p_vn_tr->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff); 
			  p2_vn_pT_cent_tr->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
			  p2_vn_KT_cent_tr->Fill(centID, jthKT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
			  //p_vn_tr->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency); 
			  //p2_vn_pT_cent_tr->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  //p2_vn_KT_cent_tr->Fill(centID, jthKT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./tpcEfficiency);
			  h2_dndDeltaPhi_vs_cent_tr->Fill(centID, jthPhi - psi);
			}

		      if (jthpT >= configs.pt_yDep_tr_low && jthpT <= configs.pt_yDep_tr_high &&
		       jthRapidity - Y_MID > configs.yCM_yMid_LiNu_low && jthRapidity - Y_MID < configs.yCM_yMid_LiNu_high)
		       {
		         p2_vn_pT_cent_tr_yMid->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);//tpcEfficiency
		       }
		        if (jthpT >= configs.pt_yDep_tr_low && jthpT <= configs.pt_yDep_tr_high &&
		         jthRapidity - Y_MID > configs.yCM_yFor_LiNu_low && jthRapidity - Y_MID < configs.yCM_yFor_LiNu_high)
		       {
		         p2_vn_pT_cent_tr_yFor->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);//tpcEfficiency
		       }
		        if (jthpT >= configs.pt_yDep_tr_low && jthpT <= configs.pt_yDep_tr_high &&
		         jthRapidity - Y_MID > configs.yCM_yExt_LiNu_low && jthRapidity - Y_MID < configs.yCM_yExt_LiNu_high)
		       {
		         p2_vn_pT_cent_tr_yExt->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);//tpcEfficiency
		       }
		        if (jthpT >= configs.pt_yDep_tr_low && jthpT <= configs.pt_yDep_tr_high &&
		         jthRapidity - Y_MID > configs.yCM_yEnd_LiNu_low && jthRapidity - Y_MID < configs.yCM_yEnd_LiNu_high)
		       {
		         p2_vn_pT_cent_tr_yEnd->Fill(centID, jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);//tpcEfficiency
		       }

		      //if (jthKT/3.0 >= configs.KT_pdt_low && jthKT/3.0 <= configs.KT_pdt_high &&
		      if (jthRapidity - Y_MID > configs.yCM_yDep_tr_low && jthRapidity - Y_MID < configs.yCM_yDep_tr_high && 
			  jthRapidity - Y_MID > 0.0 && jthRapidity - Y_MID < 0.6)
			{
			  p_vn_tr_y0to0p6->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);//tpcEfficiency
			}

		      //if (jthKT/3.0 >= configs.KT_pdt_low && jthKT/3.0 <= configs.KT_pdt_high &&
		      if (jthRapidity - Y_MID > configs.yCM_yDep_tr_low && jthRapidity - Y_MID < configs.yCM_yDep_tr_high && 
			  jthRapidity - Y_MID > 0.6 && jthRapidity - Y_MID < 1.0)
			{
			  p_vn_tr_y0p6to1p0->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);//tpcEfficiency
			}

		      //if (jthKT/3.0 >= configs.KT_pdt_low && jthKT/3.0 <= configs.KT_pdt_high &&
		      if (jthRapidity - Y_MID > configs.yCM_yDep_tr_low && jthRapidity - Y_MID < configs.yCM_yDep_tr_high && 
			  jthRapidity/Y_BEAM > -1.0 && jthRapidity/Y_BEAM < 0.0)
			{
			  p2_vn_yOverYbeam_cent_tr->Fill(centID, jthRapidity/Y_BEAM, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);//tpcEfficiency
			}

                      }

		    }

		  // HELIUM3
		  else if (eventInfo.tpcParticles.at(j).he3Tag)
		    {
		      //if (jthKT/3.0 >= configs.KT_pdt_low && jthKT/3.0 <= configs.KT_pdt_high &&
		      if (2*jthpT >= configs.pt_norm_he3_low && 2*jthpT <= configs.pt_norm_he3_high &&
			  //jthRapidity - Y_MID > configs.yCM_norm_he3_low && jthRapidity - Y_MID < configs.yCM_norm_he3_high)
			  jthRapidity - Y_MID > configs.yCM_yTot_LiNu_low && jthRapidity - Y_MID < configs.yCM_yTot_LiNu_high)
			{
			  if(jtheff>0.01){
				  // vn vs y
				p2_vn_yCM_cent_he3->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
		  		h2_pT_vs_yCM_he3_weight_check->Fill(jthRapidity - Y_MID, 2*jthpT, 1./jtheff);
			  	p2_vn_yCM_cent_he3_noEff->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ));

			  	p_vn_he3->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff); 

				 // vn vs pT
			  	p2_vn_pT_cent_he3->Fill(centID, 2*jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
			  	p2_vn_KT_cent_he3->Fill(centID, jthKT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
			  	h2_dndDeltaPhi_vs_cent_he3->Fill(centID, jthPhi - psi);
			  }

                          //he3_eff = he3_eff*(Float_t)h2_tracking_he3->GetBinContent(h2_tracking_he3->FindBin(jthRapidity, 2*jthpT));
                          //he3_eff = he3_eff*(Float_t)tpc_he3->GetBinContent(tpc_he3->FindBin(2*jthmom));
                          //std::cout << "2979: he3 jtheff: " << jtheff << std::endl;
			}

		      if (jthKT/3.0 >= configs.KT_pdt_low && jthKT/3.0 <= configs.KT_pdt_high &&
			  jthRapidity - Y_MID > configs.yCM_norm_he3_low && jthRapidity - Y_MID < configs.yCM_norm_he3_high)
		      {
			  if(jtheff>0.01){
				  p2_vn_yCM_cent_he3_alt->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
			  }
		      
		      }
                        Int_t DyBin(-1);
                        //Int_t DptBin(-1);

                        for(Int_t jj=0; jj<5; jj++) {
                                if(jthRapidity - Y_MID>=YBins[jj] && YBins[jj+1]>jthRapidity - Y_MID)
                                        DyBin = jj+1;
                                //if(jj<3 && 2*jthpT>=TPtBins[jj] && TPtBins[jj+1]>2*jthpT)
                                        //DptBin = jj+3;
                        }

                      if(2*jthpT>He3ptLowCut && 2*jthpT<He3ptHighCut && jthRapidity - Y_MID>yLowCut && jthRapidity - Y_MID<yHighCut  && DyBin != -1 && he3_eff>0.) 
			{
			  if(jtheff>0.01) 
			    {
                                pHe3v1Pt[0][0]->Fill(2*jthpT/1., TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ), 1./jtheff);  /// all centrality and pt bins
                                //pHe3v2Pt[0][0]->Fill(2*jthpT/1., v2/1., 1./jtheff);
                                pHe3v1Pt[Cent+1][0]->Fill(2*jthpT/1., TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ), 1./jtheff); /// all pt bins
                                //pHe3v2Pt[Cent+1][0]->Fill(2*jthpT/1., v2/1., 1./jtheff);

                                pHe3v1Pt[0][DyBin]->Fill(2*jthpT/1., TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ), 1./jtheff);  /// all centrality bins
                                //pHe3v2Pt[0][DyBin]->Fill(2*jthpT/1., v2/1., 1./jtheff);
                                pHe3v1Pt[Cent+1][DyBin]->Fill(2*jthpT/1., TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ), 1./jtheff);
                                //pHe3v2Pt[Cent+1][DyBin]->Fill(2*jthpT/1., v2/1., 1./jtheff);
			    
			    }
                        }

		      if(jtheff>0.01) 
		      {
		         if (2*jthpT >= configs.pt_norm_he3_low && 2*jthpT <= configs.pt_norm_he3_high &&
		   	  jthRapidity - Y_MID > configs.yCM_yMid_LiNu_low && jthRapidity - Y_MID < configs.yCM_yMid_LiNu_high)
		   	  {
		   	    p2_vn_pT_cent_he3_yMid->Fill(centID, 2*jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
		   	  }
		           if (2*jthpT >= configs.pt_norm_he3_low && 2*jthpT <= configs.pt_norm_he3_high &&
		   	    jthRapidity - Y_MID > configs.yCM_yFor_LiNu_low && jthRapidity - Y_MID < configs.yCM_yFor_LiNu_high)
		   	  {
		   	    p2_vn_pT_cent_he3_yFor->Fill(centID, 2*jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
		   	  }
		           if (2*jthpT >= configs.pt_norm_he3_low && 2*jthpT <= configs.pt_norm_he3_high &&
		   	    jthRapidity - Y_MID > configs.yCM_yExt_LiNu_low && jthRapidity - Y_MID < configs.yCM_yExt_LiNu_high)
		   	  {
		   	    p2_vn_pT_cent_he3_yExt->Fill(centID, 2*jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
		   	  }
		           if (2*jthpT >= configs.pt_norm_he3_low && 2*jthpT <= configs.pt_norm_he3_high &&
		   	    jthRapidity - Y_MID > configs.yCM_yEnd_LiNu_low && jthRapidity - Y_MID < configs.yCM_yEnd_LiNu_high)
		   	  {
		   	    p2_vn_pT_cent_he3_yEnd->Fill(centID, 2*jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
		   	  }
		           //if (jthKT/3.0 >= configs.KT_pdt_low && jthKT/3.0 <= configs.KT_pdt_high &&
		           if (2*jthpT >= configs.pt_norm_he3_low && 2*jthpT <= configs.pt_norm_he3_high &&
		   	    jthRapidity - Y_MID > 0.0 && jthRapidity - Y_MID < 0.6)
		   	  {
		   	    p_vn_he3_y0to0p6->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff); 
		   	  }

		           //if (jthKT/3.0 >= configs.KT_pdt_low && jthKT/3.0 <= configs.KT_pdt_high &&
		           if (2*jthpT >= configs.pt_norm_he3_low && 2*jthpT <= configs.pt_norm_he3_high &&
		   	    jthRapidity - Y_MID > 0.6 && jthRapidity - Y_MID < 1.0)
		   	  {
		   	    p_vn_he3_y0p6to1p0->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff); 
		   	  }

		           //if (jthKT/3.0 >= configs.KT_pdt_low && jthKT/3.0 <= configs.KT_pdt_high &&
		           if (2*jthpT >= configs.pt_norm_he3_low && 2*jthpT <= configs.pt_norm_he3_high &&
		   	    jthRapidity/Y_BEAM > -1.0 && jthRapidity/Y_BEAM < 0.0)
		   	  {
		   	    p2_vn_yOverYbeam_cent_he3->Fill(centID, jthRapidity/Y_BEAM, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
		   	  }
		      
		      }

		    }
          //std::cout << "test 9.1.9" << std::endl;
		  // HELIUM4
		  else if (eventInfo.tpcParticles.at(j).he4Tag)
		    {
		      //if (jthKT/4.0 >= configs.KT_pdt_low && jthKT/4.0 <= configs.KT_pdt_high &&
			  //jthRapidity - Y_MID > configs.yCM_norm_he4_low && jthRapidity - Y_MID < configs.yCM_norm_he4_high)
		      if (2*jthpT >= configs.pt_norm_he4_low && 2*jthpT <= configs.pt_norm_he4_high &&
			  //jthRapidity - Y_MID > configs.yCM_norm_he4_low && jthRapidity - Y_MID < configs.yCM_norm_he4_high)
			  jthRapidity - Y_MID > configs.yCM_yTot_LiNu_low && jthRapidity - Y_MID < configs.yCM_yTot_LiNu_high)
			{
			  //if(jtheff>0.1)
			  if(jtheff>0.01){
			    p2_vn_yCM_cent_he4->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
			    p_vn_he4->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff); 
			    p2_vn_pT_cent_he4->Fill(centID, 2*jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
			    p2_vn_KT_cent_he4->Fill(centID, jthKT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
			    h2_dndDeltaPhi_vs_cent_he4->Fill(centID, jthPhi - psi);
			  }
			  p2_vn_yCM_cent_he4_noEff->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ));
			}
		      
		      if (jthKT/4.0 >= configs.KT_pdt_low && jthKT/4.0 <= configs.KT_pdt_high &&
			  jthRapidity - Y_MID > configs.yCM_norm_he4_low && jthRapidity - Y_MID < configs.yCM_norm_he4_high)
		      {
			  if(jtheff>0.01){
				  p2_vn_yCM_cent_he4_alt->Fill(centID, jthRapidity - Y_MID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
			  }
		      
		      }

		      if (jtheff>0.01){
		        //if (jthKT/4.0 >= configs.KT_pdt_low && jthKT/4.0 <= configs.KT_pdt_high &&
		         //if (2*jthpT >= configs.pt_yMid_he4_low && 2*jthpT <= configs.pt_yMid_he4_high &&
		         if (2*jthpT >= configs.pt_norm_he4_low && 2*jthpT <= configs.pt_norm_he4_high &&
		   	  jthRapidity - Y_MID > configs.yCM_yMid_LiNu_low && jthRapidity - Y_MID < configs.yCM_yMid_LiNu_high)
		   	  {
		   	    p2_vn_pT_cent_he4_yMid->Fill(centID, 2*jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
		   	  }
		           //if (2*jthpT >= configs.pt_yFor_he4_low && 2*jthpT <= configs.pt_yFor_he4_high &&
		           if (2*jthpT >= configs.pt_norm_he4_low && 2*jthpT <= configs.pt_norm_he4_high &&
		   	    jthRapidity - Y_MID > configs.yCM_yFor_LiNu_low && jthRapidity - Y_MID < configs.yCM_yFor_LiNu_high)
		   	  {
		   	    p2_vn_pT_cent_he4_yFor->Fill(centID, 2*jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
		   	  }
		           //if (2*jthpT >= configs.pt_yExt_he4_low && 2*jthpT <= configs.pt_yExt_he4_high &&
		           if (2*jthpT >= configs.pt_norm_he4_low && 2*jthpT <= configs.pt_norm_he4_high &&
		   	    jthRapidity - Y_MID > configs.yCM_yExt_LiNu_low && jthRapidity - Y_MID < configs.yCM_yExt_LiNu_high)
		   	  {
		   	    p2_vn_pT_cent_he4_yExt->Fill(centID, 2*jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
		   	  }
		           //if (2*jthpT >= configs.pt_yEnd_he4_low && 2*jthpT <= configs.pt_yEnd_he4_high &&
		           if (2*jthpT >= configs.pt_norm_he4_low && 2*jthpT <= configs.pt_norm_he4_high &&
		   	    jthRapidity - Y_MID > configs.yCM_yEnd_LiNu_low && jthRapidity - Y_MID < configs.yCM_yEnd_LiNu_high)
		   	  {
		   	    p2_vn_pT_cent_he4_yEnd->Fill(centID, 2*jthpT, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
		   	  }
		        if (2*jthpT >= configs.pt_norm_he4_low && 2*jthpT <= configs.pt_norm_he4_high &&
		  	    jthRapidity - Y_MID > 0.0 && jthRapidity - Y_MID < 0.6)
		  	  {
		  	    p_vn_he4_y0to0p6->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff); 
		  	  }

		        //if (jthKT/4.0 >= configs.KT_pdt_low && jthKT/4.0 <= configs.KT_pdt_high &&
		        if (2*jthpT >= configs.pt_norm_he4_low && 2*jthpT <= configs.pt_norm_he4_high &&
		  	    jthRapidity - Y_MID > 0.6 && jthRapidity - Y_MID < 1.0)
		  	  {
		  	    p_vn_he4_y0p6to1p0->Fill(centID, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff); 
		  	  }

		        //if (jthKT/4.0 >= configs.KT_pdt_low && jthKT/4.0 <= configs.KT_pdt_high &&
		        if (2*jthpT >= configs.pt_norm_he4_low && 2*jthpT <= configs.pt_norm_he4_high &&
		  	    jthRapidity/Y_BEAM > -1.0 && jthRapidity/Y_BEAM < 0.0)
		  	  {
		  	    p2_vn_yOverYbeam_cent_he4->Fill(centID, jthRapidity/Y_BEAM, TMath::Cos(ORDER_N * (jthPhi - psi)) / (resolution ),1./jtheff);
		  	  }
			}
		    }
          //std::cout << "test 9.1.10" << std::endl;
		}// End tpc particles loop
          //std::cout << "test 9.2" << std::endl;
	    }// End if(resolutionsFound)
            //if(b_de && b_newEvent)  d_deEvents ++;
	    //if(b_de) d_deEvents ++;
          //std::cout << "test 9.3" << std::endl;
	  //=========================================================
	  //            End Flow Calculations
	  //=========================================================
	}// End if(RUN_ITERATION == 2)
          //std::cout << "test 10" << std::endl;
    }//END EVENT LOOP
  std::cout << "d_deEvents: " << d_deEvents << std::endl;
  std::cout << "d_allEvents: " << d_allEvents << std::endl;
  eventInfo.reset();

  // Switch axis labels on some plots, put in centrality percentages

  // The indices here are equivalent to the corresponding centrality ID
  const char *centralityBins[16] = {"75-80", "70-75", "65-70", "60-65", "55-60", "50-55", "45-50", "40-45", "35-40", "30-35", "25-30", "20-25", "15-20", "10-15", "5-10", "0-5"};

  Int_t labelIndex;
  for (int i = 1; i <= CENT_BINS; i++) 
    {
      labelIndex = FIRST_CENT + i - 1;
      h2_vnScanTpc->GetYaxis()->SetBinLabel(i, centralityBins[labelIndex]); 
      h2_vnScanTpcEpdA->GetYaxis()->SetBinLabel(i, centralityBins[labelIndex]); 
      h2_vnScanTpcEpdB->GetYaxis()->SetBinLabel(i, centralityBins[labelIndex]); 
      h2_vnScanEpd->GetYaxis()->SetBinLabel(i, centralityBins[labelIndex]);
      h2_vnScanEpdTpcA->GetYaxis()->SetBinLabel(i, centralityBins[labelIndex]);
      h2_vnScanEpdTpcB->GetYaxis()->SetBinLabel(i, centralityBins[labelIndex]);
    }
  ////

  // Manually write the few plots that were pulled from the trees
  h_eventCheck->Write();
  h_trackmult->Write();
  h_refmult->Write();
  h_tofmult->Write();
  h2_refmult_vs_trackmult->Write();
  h2_tofmult_vs_trackmult->Write();
  h2_tofmult_vs_refmult->Write();
  ////

  // Check ending memory usage to help spot memory leaks
  int who = RUSAGE_SELF;
  struct rusage usage;
  int ret;  
  ret = getrusage(who, &usage);

  if (ret == 0) { std::cout << "Ending memory usage: " << usage.ru_maxrss / 1000 << " MB" << std::endl; }
  else { std::cout << "Could not retrieve memory usage!" << std::endl; }
  //

  // Write all main output
  outputFile->cd();
  outputFile->Write();
  //

  // Save re-centering and Fourier shifting information
  if (RUN_ITERATION == 0 || RUN_ITERATION == 1)
    {
      correctionOutputFile->cd();

      p_sinAvgsTpc   ->Write();
      p_cosAvgsTpc   ->Write();
      p_sinAvgsTpcA  ->Write();
      p_cosAvgsTpcA  ->Write();
      p_sinAvgsTpcB  ->Write();
      p_cosAvgsTpcB  ->Write();
      p_sinAvgsEpd   ->Write();
      p_cosAvgsEpd   ->Write();
      p_sinAvgsEpdA  ->Write();
      p_cosAvgsEpdA  ->Write();
      p_sinAvgsEpdB  ->Write();
      p_cosAvgsEpdB  ->Write();
      h_XnTpc        ->Write();
      h_YnTpc        ->Write();
      h_XnTpcA       ->Write();
      h_YnTpcA       ->Write();
      h_XnTpcB       ->Write();
      h_YnTpcB       ->Write();
      h_XnEpd        ->Write();
      h_YnEpd        ->Write();
      h_XnEpdA       ->Write();
      h_YnEpdA       ->Write();
      h_XnEpdB       ->Write();
      h_YnEpdB       ->Write();

      gROOT->GetListOfFiles()->Remove(correctionOutputFile);
      correctionOutputFile->Close();
    }
  //

  // Close files
  gROOT->GetListOfFiles()->Remove(outputFile);
  outputFile->Close();
  if (RUN_ITERATION == 1 || RUN_ITERATION == 2)
    {
      gROOT->GetListOfFiles()->Remove(correctionInputFile);
      correctionInputFile->Close();
    }
  //

  std::cout << "Done!" << std::endl;
}//End main()
