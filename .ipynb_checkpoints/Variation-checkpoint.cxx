#include <iostream>
#include "TProfile.h"
#include "TProfile2D.h"
#include "TMath.h"
#include "Variation.h"
#include "PlotUtils.h"

using namespace PlotUtils;
using namespace std;

// Constructor for the "normal" results.
Variation::Variation(TString prefix, TString order_n_str)
{
  ID = prefix;
  fileName = prefix + "";

  file = TFile::Open(fileName);

  initialize(order_n_str);
  fixAttributes(order_n_str);
}


// Destructor
Variation::~Variation()
{
  delete h_vn_pp;
  delete h_vn_pm;
  delete h_vn_kp;
  delete h_vn_km;
  delete h_vn_pr;
  delete h_vn_de;
  delete h_vn_tr;
//   delete h_vn_he3;
//   delete h_vn_he4;
  delete h_vn_yCM_00to10_pr;
  delete h_vn_yCM_10to40_pr;
  delete h_vn_yCM_40to60_pr;
  delete h_vn_yCM_00to10_kp;
  delete h_vn_yCM_10to40_kp;
  delete h_vn_yCM_40to60_kp;
  delete h_vn_yCM_00to10_km;
  delete h_vn_yCM_10to40_km;
  delete h_vn_yCM_40to60_km;
  delete h_vn_yCM_00to10_pp;
  delete h_vn_yCM_10to40_pp;
  delete h_vn_yCM_40to60_pp;
  delete h_vn_yCM_00to10_pm;
  delete h_vn_yCM_10to40_pm;
  delete h_vn_yCM_40to60_pm;

  delete h_vn_yCM_00to10_pr_symm;
  delete h_vn_yCM_10to40_pr_symm;
  delete h_vn_yCM_40to60_pr_symm;
  //std::cout << "h_vn_yCM_00to10_de address: "<<  h_vn_yCM_00to10_de << std::endl;
//   delete h_vn_yCM_00to10_de;
//   delete h_vn_yCM_10to40_de;
//   delete h_vn_yCM_40to60_de;
//   delete h_vn_yCM_00to10_tr;
//   delete h_vn_yCM_10to40_tr;
//   delete h_vn_yCM_40to60_tr;
//   delete h_vn_yCM_00to10_he3;
//   delete h_vn_yCM_10to40_he3;
//   delete h_vn_yCM_40to60_he3;
//   delete h_vn_yCM_00to10_he4;
//   delete h_vn_yCM_10to40_he4;
//   delete h_vn_yCM_40to60_he4;

  delete h_vn_pT_00to10_pr;
  delete h_vn_pT_10to40_pr;
  delete h_vn_pT_40to60_pr;
//   delete h_vn_pT_00to10_pr_yMid;
//   delete h_vn_pT_10to40_pr_yMid;
//   delete h_vn_pT_40to60_pr_yMid;
//   delete h_vn_pT_00to10_pr_yFor;
//   delete h_vn_pT_10to40_pr_yFor;
//   delete h_vn_pT_40to60_pr_yFor;
//   delete h_vn_pT_00to10_pr_yExt;
//   delete h_vn_pT_10to40_pr_yExt;
//   delete h_vn_pT_40to60_pr_yExt;
//   delete h_vn_pT_00to10_pr_yEnd;
//   delete h_vn_pT_10to40_pr_yEnd;
//   delete h_vn_pT_40to60_pr_yEnd;

//   delete h_vn_pT_00to10_de;
//   delete h_vn_pT_10to40_de;
//   delete h_vn_pT_40to60_de;
//   delete h_vn_pT_00to10_de_yMid;
//   delete h_vn_pT_10to40_de_yMid;
//   delete h_vn_pT_40to60_de_yMid;
//   delete h_vn_pT_00to10_de_yFor;
//   delete h_vn_pT_10to40_de_yFor;
//   delete h_vn_pT_40to60_de_yFor;
//   delete h_vn_pT_00to10_de_yExt;
//   delete h_vn_pT_10to40_de_yExt;
//   delete h_vn_pT_40to60_de_yExt;
//   delete h_vn_pT_00to10_de_yEnd;
//   delete h_vn_pT_10to40_de_yEnd;
//   delete h_vn_pT_40to60_de_yEnd;

//   delete h_vn_pT_00to10_tr;
//   delete h_vn_pT_10to40_tr;
//   delete h_vn_pT_40to60_tr;
//   delete h_vn_pT_00to10_tr_yMid;
//   delete h_vn_pT_10to40_tr_yMid;
//   delete h_vn_pT_40to60_tr_yMid;
//   delete h_vn_pT_00to10_tr_yFor;
//   delete h_vn_pT_10to40_tr_yFor;
//   delete h_vn_pT_40to60_tr_yFor;
//   delete h_vn_pT_00to10_tr_yExt;
//   delete h_vn_pT_10to40_tr_yExt;
//   delete h_vn_pT_40to60_tr_yExt;
//   delete h_vn_pT_00to10_tr_yEnd;
//   delete h_vn_pT_10to40_tr_yEnd;
//   delete h_vn_pT_40to60_tr_yEnd;

//   delete h_vn_pT_00to10_he3;
//   delete h_vn_pT_10to40_he3;
//   delete h_vn_pT_40to60_he3;
//   delete h_vn_pT_00to10_he3_yMid;
//   delete h_vn_pT_10to40_he3_yMid;
//   delete h_vn_pT_40to60_he3_yMid;
//   delete h_vn_pT_00to10_he3_yFor;
//   delete h_vn_pT_10to40_he3_yFor;
//   delete h_vn_pT_40to60_he3_yFor;
//   delete h_vn_pT_00to10_he3_yExt;
//   delete h_vn_pT_10to40_he3_yExt;
//   delete h_vn_pT_40to60_he3_yExt;
//   delete h_vn_pT_00to10_he3_yEnd;
//   delete h_vn_pT_10to40_he3_yEnd;
//   delete h_vn_pT_40to60_he3_yEnd;

//   delete h_vn_pT_00to10_he4;
//   delete h_vn_pT_10to40_he4;
//   delete h_vn_pT_40to60_he4;
//   delete h_vn_pT_00to10_he4_yMid;
//   delete h_vn_pT_10to40_he4_yMid;
//   delete h_vn_pT_40to60_he4_yMid;
//   delete h_vn_pT_00to10_he4_yFor;
//   delete h_vn_pT_10to40_he4_yFor;
//   delete h_vn_pT_40to60_he4_yFor;
//   delete h_vn_pT_00to10_he4_yExt;
//   delete h_vn_pT_10to40_he4_yExt;
//   delete h_vn_pT_40to60_he4_yExt;
//   delete h_vn_pT_00to10_he4_yEnd;
//   delete h_vn_pT_10to40_he4_yEnd;
//   delete h_vn_pT_40to60_he4_yEnd;

  file->Close();
}

// Initialize all histograms
void Variation::initialize(TString order_n_str)
{
  TProfile *p_vn_pp = (TProfile*)file->Get("DataVnVsCentralityPionPlusCorrected");
  TProfile *p_vn_pm = (TProfile*)file->Get("DataVnVsCentralityPionMinusCorrected");
  TProfile *p_vn_kp = (TProfile*)file->Get("DataVnVsCentralityKaonPlusCorrected");
  TProfile *p_vn_km = (TProfile*)file->Get("DataVnVsCentralityKaonMinusCorrected");
  TProfile *p_vn_pr = (TProfile*)file->Get("DataVnVsCentralityProtonCorrected");
  TProfile *p_vn_de = (TProfile*)file->Get("DataVnVsCentralityDeuteronCorrected");
  TProfile *p_vn_tr = (TProfile*)file->Get("DataVnVsCentralityTritonCorrected");
//   TProfile *p_vn_he3 = (TProfile*)file->Get("p_vn_he3");
//   TProfile *p_vn_he4 = (TProfile*)file->Get("p_vn_he4");


//   p_vn_kp->Rebin();  
//   p_vn_km->Rebin();

    
  h_vn_pp = p_vn_pp->ProjectionX();
  h_vn_pm = p_vn_pm->ProjectionX();
std::cout << "Before" << std::endl;
  h_vn_kp = p_vn_kp->ProjectionX();
  h_vn_km = p_vn_km->ProjectionX();
std::cout << "After" << std::endl;
  h_vn_pr = p_vn_pr->ProjectionX();
  h_vn_de = p_vn_de->ProjectionX();
  h_vn_tr = p_vn_tr->ProjectionX();

//   h_vn_he3 = p_vn_he3->ProjectionX((TString)p_vn_he3->GetName() +"_"+ ID);
//   h_vn_he4 = p_vn_he4->ProjectionX((TString)p_vn_he4->GetName() +"_"+ ID);
  
//   h_vn_pp = flipHisto(h_vn_pp);
//   h_vn_pm = flipHisto(h_vn_pm);
//   h_vn_kp = flipHisto(h_vn_kp);
//   h_vn_km = flipHisto(h_vn_km);
//   h_vn_pr = flipHisto(h_vn_pr);
//   h_vn_de = flipHisto(h_vn_de);
//   h_vn_tr = flipHisto(h_vn_tr);
//   h_vn_he3 = flipHisto(h_vn_he3);
//   h_vn_he4 = flipHisto(h_vn_he4);
  
//   h_vn_pp = trimCentralityPlot(h_vn_pp);
//   h_vn_pm = trimCentralityPlot(h_vn_pm);
//   h_vn_kp = trimCentralityPlot(h_vn_kp);
//   h_vn_km = trimCentralityPlot(h_vn_km);
//   h_vn_pr = trimCentralityPlot(h_vn_pr);
//   h_vn_de = trimCentralityPlot(h_vn_de);
//   h_vn_tr = trimCentralityPlot(h_vn_tr);
//   h_vn_he3 = trimCentralityPlot(h_vn_he3);
//   h_vn_he4 = trimCentralityPlot(h_vn_he4);
  
  
  //=== vn vs rapidity stuff
//   TProfile2D *p2_vn_yCM_cent_pr = (TProfile2D*)file->Get("p2_vn_yCM_cent_pr");
//   TProfile2D *p2_vn_yCM_cent_pr_symmetry = (TProfile2D*)file->Get("p2_vn_yCM_cent_pr_symmetry");
//   TProfile2D *p2_vn_yCM_cent_de = (TProfile2D*)file->Get("p2_vn_yCM_cent_de_alt");
//   TProfile2D *p2_vn_yCM_cent_tr = (TProfile2D*)file->Get("p2_vn_yCM_cent_tr_alt");
//   TProfile2D *p2_vn_yCM_cent_he3 = (TProfile2D*)file->Get("p2_vn_yCM_cent_he3");
//   TProfile2D *p2_vn_yCM_cent_he4 = (TProfile2D*)file->Get("p2_vn_yCM_cent_he4");

  TProfile *p_vn_yCM_00to10_pr = (TProfile*)file->Get("DataVnVsYForProtonsCentrality0-10");
  TProfile *p_vn_yCM_10to40_pr = (TProfile*)file->Get("DataVnVsYForProtonsCentrality10-40");
  TProfile *p_vn_yCM_40to60_pr = (TProfile*)file->Get("DataVnVsYForProtonsCentrality40-60");

  TProfile *p_vn_yCM_00to10_kp = (TProfile*)file->Get("DataVnVsYForKaonsPlusCentrality0-10");
  TProfile *p_vn_yCM_10to40_kp = (TProfile*)file->Get("DataVnVsYForKaonsPlusCentrality10-40");
  TProfile *p_vn_yCM_40to60_kp = (TProfile*)file->Get("DataVnVsYForKaonsPlusCentrality40-60");
    
  TProfile *p_vn_yCM_00to10_km = (TProfile*)file->Get("DataVnVsYForKaonsMinusCentrality0-10");
  TProfile *p_vn_yCM_10to40_km = (TProfile*)file->Get("DataVnVsYForKaonsMinusCentrality10-40");
  TProfile *p_vn_yCM_40to60_km = (TProfile*)file->Get("DataVnVsYForKaonsMinusCentrality40-60");
    
  TProfile *p_vn_yCM_00to10_pp = (TProfile*)file->Get("DataVnVsYForPionsPlusCentrality0-10");
  TProfile *p_vn_yCM_10to40_pp = (TProfile*)file->Get("DataVnVsYForPionsPlusCentrality10-40");
  TProfile *p_vn_yCM_40to60_pp = (TProfile*)file->Get("DataVnVsYForPionsPlusCentrality40-60");
    
  TProfile *p_vn_yCM_00to10_pm = (TProfile*)file->Get("DataVnVsYForPionsMinusCentrality0-10");
  TProfile *p_vn_yCM_10to40_pm = (TProfile*)file->Get("DataVnVsYForPionsMinusCentrality10-40");
  TProfile *p_vn_yCM_40to60_pm = (TProfile*)file->Get("DataVnVsYForPionsMinusCentrality40-60");

  TProfile *p_vn_yCM_00to10_pr_symm = (TProfile*)file->Get("DataVnVsYSymmetricForProtonsCentrality0-10");
  TProfile *p_vn_yCM_10to40_pr_symm = (TProfile*)file->Get("DataVnVsYSymmetricForProtonsCentrality10-40");
  TProfile *p_vn_yCM_40to60_pr_symm = (TProfile*)file->Get("DataVnVsYSymmetricForProtonsCentrality40-60");

  TProfile *p_vn_yCM_00to10_de = (TProfile*)file->Get("DataVnVsYForDeuteronsCentrality0-10");
  TProfile *p_vn_yCM_10to40_de = (TProfile*)file->Get("DataVnVsYForDeuteronsCentrality10-40");
  TProfile *p_vn_yCM_40to60_de = (TProfile*)file->Get("DataVnVsYForDeuteronsCentrality40-60");
    
  TProfile *p_vn_yCM_00to10_tr = (TProfile*)file->Get("DataVnVsYForTritonsCentrality0-10");
  TProfile *p_vn_yCM_10to40_tr = (TProfile*)file->Get("DataVnVsYForTritonsCentrality10-40");
  TProfile *p_vn_yCM_40to60_tr = (TProfile*)file->Get("DataVnVsYForTritonsCentrality40-60");

//   TProfile *p_vn_yCM_00to10_he3 = p2_vn_yCM_cent_he3->ProfileY("p_vn_yCM_00to10_he3", 15, 16); // normal: kT; alt: pT
//   TProfile *p_vn_yCM_10to40_he3 = p2_vn_yCM_cent_he3->ProfileY("p_vn_yCM_10to40_he3", 9, 14); // normal: kT; alt: pT
//   TProfile *p_vn_yCM_40to60_he3 = p2_vn_yCM_cent_he3->ProfileY("p_vn_yCM_40to60_he3", 5, 8); // normal: kT; alt: pT
//   TProfile *p_vn_yCM_00to10_he4 = p2_vn_yCM_cent_he4->ProfileY("p_vn_yCM_00to10_he4", 15, 16); // normal: kT; alt: pT
//   TProfile *p_vn_yCM_10to40_he4 = p2_vn_yCM_cent_he4->ProfileY("p_vn_yCM_10to40_he4", 9, 14); // normal: kT; alt: pT
//   TProfile *p_vn_yCM_40to60_he4 = p2_vn_yCM_cent_he4->ProfileY("p_vn_yCM_40to60_he4", 5, 8); // normal: kT; alt: pT


  h_vn_yCM_00to10_pr = new TH1D("h_vn_yCM_00to10_pr", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
  h_vn_yCM_10to40_pr = new TH1D("h_vn_yCM_10to40_pr", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
  h_vn_yCM_40to60_pr = new TH1D("h_vn_yCM_40to60_pr", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
    
  h_vn_yCM_00to10_kp = new TH1D("h_vn_yCM_00to10_kp", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
  h_vn_yCM_10to40_kp = new TH1D("h_vn_yCM_10to40_kp", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
  h_vn_yCM_40to60_kp = new TH1D("h_vn_yCM_40to60_kp", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);

  h_vn_yCM_00to10_km = new TH1D("h_vn_yCM_00to10_km", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
  h_vn_yCM_10to40_km = new TH1D("h_vn_yCM_10to40_km", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
  h_vn_yCM_40to60_km = new TH1D("h_vn_yCM_40to60_km", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);

  h_vn_yCM_00to10_pp = new TH1D("h_vn_yCM_00to10_pp", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
  h_vn_yCM_10to40_pp = new TH1D("h_vn_yCM_10to40_pp", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
  h_vn_yCM_40to60_pp = new TH1D("h_vn_yCM_40to60_pp", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
    
  h_vn_yCM_00to10_pm = new TH1D("h_vn_yCM_00to10_pm", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
  h_vn_yCM_10to40_pm = new TH1D("h_vn_yCM_10to40_pm", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
  h_vn_yCM_40to60_pm = new TH1D("h_vn_yCM_40to60_pm", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);

     h_vn_yCM_00to10_pr_symm = new TH1D("h_vn_yCM_00to10_pr_symm", ";y-y_{mid};v_{"+order_n_str+"}", 10, -0.5, 0.5);
     h_vn_yCM_10to40_pr_symm = new TH1D("h_vn_yCM_10to40_pr_symm", ";y-y_{mid};v_{"+order_n_str+"}", 10, -0.5, 0.5);
     h_vn_yCM_40to60_pr_symm = new TH1D("h_vn_yCM_40to60_pr_symm", ";y-y_{mid};v_{"+order_n_str+"}", 10, -0.5, 0.5);

  h_vn_yCM_00to10_de = new TH1D("h_vn_yCM_00to10_de", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
  h_vn_yCM_10to40_de = new TH1D("h_vn_yCM_10to40_de", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
  h_vn_yCM_40to60_de = new TH1D("h_vn_yCM_40to60_de", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
    
  h_vn_yCM_00to10_tr = new TH1D("h_vn_yCM_00to10_tr", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
  h_vn_yCM_10to40_tr = new TH1D("h_vn_yCM_10to40_tr", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
  h_vn_yCM_40to60_tr = new TH1D("h_vn_yCM_40to60_tr", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);
    
//   h_vn_yCM_00to10_he3 = new TH1D("h_vn_yCM_00to10_he3", ";y-y_{mid};v_{"+order_n_str+"}", 20, -1, 1);
//   h_vn_yCM_10to40_he3 = new TH1D("h_vn_yCM_10to40_he3", ";y-y_{mid};v_{"+order_n_str+"}", 20, -1, 1);
//   h_vn_yCM_40to60_he3 = new TH1D("h_vn_yCM_40to60_he3", ";y-y_{mid};v_{"+order_n_str+"}", 20, -1, 1);
//   h_vn_yCM_00to10_he4 = new TH1D("h_vn_yCM_00to10_he4", ";y-y_{mid};v_{"+order_n_str+"}", 20, -1, 1);
//   h_vn_yCM_10to40_he4 = new TH1D("h_vn_yCM_10to40_he4", ";y-y_{mid};v_{"+order_n_str+"}", 20, -1, 1);
//   h_vn_yCM_40to60_he4 = new TH1D("h_vn_yCM_40to60_he4", ";y-y_{mid};v_{"+order_n_str+"}", 20, -1, 1);


  // Convert profiles to histograms
    h_vn_yCM_00to10_pr = p_vn_yCM_00to10_pr->ProjectionX();
    h_vn_yCM_10to40_pr = p_vn_yCM_10to40_pr->ProjectionX();
    h_vn_yCM_40to60_pr = p_vn_yCM_40to60_pr->ProjectionX();
    
  h_vn_yCM_00to10_kp = p_vn_yCM_00to10_kp->ProjectionX();
  h_vn_yCM_10to40_kp = p_vn_yCM_10to40_kp->ProjectionX();
  h_vn_yCM_40to60_kp = p_vn_yCM_40to60_kp->ProjectionX();
    
  h_vn_yCM_00to10_km = p_vn_yCM_00to10_km->ProjectionX();
  h_vn_yCM_10to40_km = p_vn_yCM_10to40_km->ProjectionX();
  h_vn_yCM_40to60_km = p_vn_yCM_40to60_km->ProjectionX();
    
  h_vn_yCM_00to10_pp = p_vn_yCM_00to10_pp->ProjectionX();
  h_vn_yCM_10to40_pp = p_vn_yCM_10to40_pp->ProjectionX();
  h_vn_yCM_40to60_pp = p_vn_yCM_40to60_pp->ProjectionX();
    
  h_vn_yCM_00to10_pm = p_vn_yCM_00to10_pm->ProjectionX();
  h_vn_yCM_10to40_pm = p_vn_yCM_10to40_pm->ProjectionX();
  h_vn_yCM_40to60_pm = p_vn_yCM_40to60_pm->ProjectionX();

     h_vn_yCM_00to10_pr_symm = p_vn_yCM_00to10_pr_symm->ProjectionX();
     h_vn_yCM_10to40_pr_symm = p_vn_yCM_10to40_pr_symm->ProjectionX();
     h_vn_yCM_40to60_pr_symm = p_vn_yCM_40to60_pr_symm->ProjectionX();

  h_vn_yCM_00to10_de = p_vn_yCM_00to10_de->ProjectionX();
  h_vn_yCM_10to40_de = p_vn_yCM_10to40_de->ProjectionX();
  h_vn_yCM_40to60_de = p_vn_yCM_40to60_de->ProjectionX();
    
  h_vn_yCM_00to10_tr = p_vn_yCM_00to10_tr->ProjectionX();
  h_vn_yCM_10to40_tr = p_vn_yCM_10to40_tr->ProjectionX();
  h_vn_yCM_40to60_tr = p_vn_yCM_40to60_tr->ProjectionX();
     
//   h_vn_yCM_00to10_he3 = p_vn_yCM_00to10_he3->ProjectionX();
//   h_vn_yCM_10to40_he3 = p_vn_yCM_10to40_he3->ProjectionX();
//   h_vn_yCM_40to60_he3 = p_vn_yCM_40to60_he3->ProjectionX();
//   h_vn_yCM_00to10_he4 = p_vn_yCM_00to10_he4->ProjectionX();
//   h_vn_yCM_10to40_he4 = p_vn_yCM_10to40_he4->ProjectionX();
//   h_vn_yCM_40to60_he4 = p_vn_yCM_40to60_he4->ProjectionX();



  //=== vn vs pT stuff
//   TProfile2D *p2_vn_pT_cent_pr =      (TProfile2D*)file->Get("p2_vn_pT_cent_pr");
//   TProfile2D *p2_vn_pT_cent_pr_yMid = (TProfile2D*)file->Get("p2_vn_pT_cent_pr_yMid");
//   TProfile2D *p2_vn_pT_cent_pr_yFor = (TProfile2D*)file->Get("p2_vn_pT_cent_pr_yFor");
//   TProfile2D *p2_vn_pT_cent_pr_yExt = (TProfile2D*)file->Get("p2_vn_pT_cent_pr_yExt");
//   TProfile2D *p2_vn_pT_cent_pr_yEnd = (TProfile2D*)file->Get("p2_vn_pT_cent_pr_yEnd");

//   TProfile2D *p2_vn_pT_cent_de =      (TProfile2D*)file->Get("p2_vn_pT_cent_de");
//   TProfile2D *p2_vn_pT_cent_de_yMid = (TProfile2D*)file->Get("p2_vn_pT_cent_de_yMid");
//   TProfile2D *p2_vn_pT_cent_de_yFor = (TProfile2D*)file->Get("p2_vn_pT_cent_de_yFor");
//   TProfile2D *p2_vn_pT_cent_de_yExt = (TProfile2D*)file->Get("p2_vn_pT_cent_de_yExt");
//   TProfile2D *p2_vn_pT_cent_de_yEnd = (TProfile2D*)file->Get("p2_vn_pT_cent_de_yEnd");

//   TProfile2D *p2_vn_pT_cent_tr =      (TProfile2D*)file->Get("p2_vn_pT_cent_tr");
//   TProfile2D *p2_vn_pT_cent_tr_yMid = (TProfile2D*)file->Get("p2_vn_pT_cent_tr_yMid");
//   TProfile2D *p2_vn_pT_cent_tr_yFor = (TProfile2D*)file->Get("p2_vn_pT_cent_tr_yFor");
//   TProfile2D *p2_vn_pT_cent_tr_yExt = (TProfile2D*)file->Get("p2_vn_pT_cent_tr_yExt");
//   TProfile2D *p2_vn_pT_cent_tr_yEnd = (TProfile2D*)file->Get("p2_vn_pT_cent_tr_yEnd");

//   TProfile2D *p2_vn_pT_cent_he3 =      (TProfile2D*)file->Get("p2_vn_pT_cent_he3");
//   TProfile2D *p2_vn_pT_cent_he3_yMid = (TProfile2D*)file->Get("p2_vn_pT_cent_he3_yMid");
//   TProfile2D *p2_vn_pT_cent_he3_yFor = (TProfile2D*)file->Get("p2_vn_pT_cent_he3_yFor");
//   TProfile2D *p2_vn_pT_cent_he3_yExt = (TProfile2D*)file->Get("p2_vn_pT_cent_he3_yExt");
//   TProfile2D *p2_vn_pT_cent_he3_yEnd = (TProfile2D*)file->Get("p2_vn_pT_cent_he3_yEnd");

//   TProfile2D *p2_vn_pT_cent_he4 =      (TProfile2D*)file->Get("p2_vn_pT_cent_he4");
//   TProfile2D *p2_vn_pT_cent_he4_yMid = (TProfile2D*)file->Get("p2_vn_pT_cent_he4_yMid");
//   TProfile2D *p2_vn_pT_cent_he4_yFor = (TProfile2D*)file->Get("p2_vn_pT_cent_he4_yFor");
//   TProfile2D *p2_vn_pT_cent_he4_yExt = (TProfile2D*)file->Get("p2_vn_pT_cent_he4_yExt");
//   TProfile2D *p2_vn_pT_cent_he4_yEnd = (TProfile2D*)file->Get("p2_vn_pT_cent_he4_yEnd");

  TProfile *p_vn_pT_00to10_pr = (TProfile*)file->Get("DataVnVsPtForProtonsCentrality0-10");
  TProfile *p_vn_pT_10to40_pr = (TProfile*)file->Get("DataVnVsPtForProtonsCentrality10-40");
  TProfile *p_vn_pT_40to60_pr = (TProfile*)file->Get("DataVnVsPtForProtonsCentrality40-60");

  p_vn_pT_00to10_pr->Rebin();
  p_vn_pT_10to40_pr->Rebin();    
  p_vn_pT_40to60_pr->Rebin();

//   TProfile *p_vn_pT_00to10_pr_yMid = p2_vn_pT_cent_pr_yMid->ProfileY("p_vn_pT_00to10_pr_yMid", 15, 16);
//   TProfile *p_vn_pT_10to40_pr_yMid = p2_vn_pT_cent_pr_yMid->ProfileY("p_vn_pT_10to40_pr_yMid", 9, 14);
//   TProfile *p_vn_pT_40to60_pr_yMid = p2_vn_pT_cent_pr_yMid->ProfileY("p_vn_pT_40to60_pr_yMid", 5, 8);
//   TProfile *p_vn_pT_00to10_pr_yFor = p2_vn_pT_cent_pr_yFor->ProfileY("p_vn_pT_00to10_pr_yFor", 15, 16);
//   TProfile *p_vn_pT_10to40_pr_yFor = p2_vn_pT_cent_pr_yFor->ProfileY("p_vn_pT_10to40_pr_yFor", 9, 14);
//   TProfile *p_vn_pT_40to60_pr_yFor = p2_vn_pT_cent_pr_yFor->ProfileY("p_vn_pT_40to60_pr_yFor", 5, 8);
//   TProfile *p_vn_pT_00to10_pr_yExt = p2_vn_pT_cent_pr_yExt->ProfileY("p_vn_pT_00to10_pr_yExt", 15, 16);
//   TProfile *p_vn_pT_10to40_pr_yExt = p2_vn_pT_cent_pr_yExt->ProfileY("p_vn_pT_10to40_pr_yExt", 9, 14);
//   TProfile *p_vn_pT_40to60_pr_yExt = p2_vn_pT_cent_pr_yExt->ProfileY("p_vn_pT_40to60_pr_yExt", 5, 8);
//   TProfile *p_vn_pT_00to10_pr_yEnd = p2_vn_pT_cent_pr_yEnd->ProfileY("p_vn_pT_00to10_pr_yEnd", 15, 16);
//   TProfile *p_vn_pT_10to40_pr_yEnd = p2_vn_pT_cent_pr_yEnd->ProfileY("p_vn_pT_10to40_pr_yEnd", 9, 14);
//   TProfile *p_vn_pT_40to60_pr_yEnd = p2_vn_pT_cent_pr_yEnd->ProfileY("p_vn_pT_40to60_pr_yEnd", 5, 8);

//   TProfile *p_vn_pT_00to10_de = p2_vn_pT_cent_de->ProfileY("p_vn_pT_00to10_de", 15, 16);
//   TProfile *p_vn_pT_10to40_de = p2_vn_pT_cent_de->ProfileY("p_vn_pT_10to40_de", 9, 14);
//   TProfile *p_vn_pT_40to60_de = p2_vn_pT_cent_de->ProfileY("p_vn_pT_40to60_de", 5, 8);
//   TProfile *p_vn_pT_00to10_de_yMid = p2_vn_pT_cent_de_yMid->ProfileY("p_vn_pT_00to10_de_yMid", 15, 16);
//   TProfile *p_vn_pT_10to40_de_yMid = p2_vn_pT_cent_de_yMid->ProfileY("p_vn_pT_10to40_de_yMid", 9, 14);
//   TProfile *p_vn_pT_40to60_de_yMid = p2_vn_pT_cent_de_yMid->ProfileY("p_vn_pT_40to60_de_yMid", 5, 8);
//   TProfile *p_vn_pT_00to10_de_yFor = p2_vn_pT_cent_de_yFor->ProfileY("p_vn_pT_00to10_de_yFor", 15, 16);
//   TProfile *p_vn_pT_10to40_de_yFor = p2_vn_pT_cent_de_yFor->ProfileY("p_vn_pT_10to40_de_yFor", 9, 14);
//   TProfile *p_vn_pT_40to60_de_yFor = p2_vn_pT_cent_de_yFor->ProfileY("p_vn_pT_40to60_de_yFor", 5, 8);
//   TProfile *p_vn_pT_00to10_de_yExt = p2_vn_pT_cent_de_yExt->ProfileY("p_vn_pT_00to10_de_yExt", 15, 16);
//   TProfile *p_vn_pT_10to40_de_yExt = p2_vn_pT_cent_de_yExt->ProfileY("p_vn_pT_10to40_de_yExt", 9, 14);
//   TProfile *p_vn_pT_40to60_de_yExt = p2_vn_pT_cent_de_yExt->ProfileY("p_vn_pT_40to60_de_yExt", 5, 8);
//   TProfile *p_vn_pT_00to10_de_yEnd = p2_vn_pT_cent_de_yEnd->ProfileY("p_vn_pT_00to10_de_yEnd", 15, 16);
//   TProfile *p_vn_pT_10to40_de_yEnd = p2_vn_pT_cent_de_yEnd->ProfileY("p_vn_pT_10to40_de_yEnd", 9, 14);
//   TProfile *p_vn_pT_40to60_de_yEnd = p2_vn_pT_cent_de_yEnd->ProfileY("p_vn_pT_40to60_de_yEnd", 5, 8);

//   TProfile *p_vn_pT_00to10_tr =      p2_vn_pT_cent_tr->     ProfileY("p_vn_pT_00to10_tr", 15, 16);
//   TProfile *p_vn_pT_10to40_tr =      p2_vn_pT_cent_tr->     ProfileY("p_vn_pT_10to40_tr", 9, 14);
//   TProfile *p_vn_pT_40to60_tr =      p2_vn_pT_cent_tr->     ProfileY("p_vn_pT_40to60_tr", 5, 8);
//   TProfile *p_vn_pT_00to10_tr_yMid = p2_vn_pT_cent_tr_yMid->ProfileY("p_vn_pT_00to10_tr_yMid", 15, 16);
//   TProfile *p_vn_pT_10to40_tr_yMid = p2_vn_pT_cent_tr_yMid->ProfileY("p_vn_pT_10to40_tr_yMid", 9, 14);
//   TProfile *p_vn_pT_40to60_tr_yMid = p2_vn_pT_cent_tr_yMid->ProfileY("p_vn_pT_40to60_tr_yMid", 5, 8);
//   TProfile *p_vn_pT_00to10_tr_yFor = p2_vn_pT_cent_tr_yFor->ProfileY("p_vn_pT_00to10_tr_yFor", 15, 16);
//   TProfile *p_vn_pT_10to40_tr_yFor = p2_vn_pT_cent_tr_yFor->ProfileY("p_vn_pT_10to40_tr_yFor", 9, 14);
//   TProfile *p_vn_pT_40to60_tr_yFor = p2_vn_pT_cent_tr_yFor->ProfileY("p_vn_pT_40to60_tr_yFor", 5, 8);
//   TProfile *p_vn_pT_00to10_tr_yExt = p2_vn_pT_cent_tr_yExt->ProfileY("p_vn_pT_00to10_tr_yExt", 15, 16);
//   TProfile *p_vn_pT_10to40_tr_yExt = p2_vn_pT_cent_tr_yExt->ProfileY("p_vn_pT_10to40_tr_yExt", 9, 14);
//   TProfile *p_vn_pT_40to60_tr_yExt = p2_vn_pT_cent_tr_yExt->ProfileY("p_vn_pT_40to60_tr_yExt", 5, 8);
//   TProfile *p_vn_pT_00to10_tr_yEnd = p2_vn_pT_cent_tr_yEnd->ProfileY("p_vn_pT_00to10_tr_yEnd", 15, 16);
//   TProfile *p_vn_pT_10to40_tr_yEnd = p2_vn_pT_cent_tr_yEnd->ProfileY("p_vn_pT_10to40_tr_yEnd", 9, 14);
//   TProfile *p_vn_pT_40to60_tr_yEnd = p2_vn_pT_cent_tr_yEnd->ProfileY("p_vn_pT_40to60_tr_yEnd", 5, 8);

//   TProfile *p_vn_pT_00to10_he3 =      p2_vn_pT_cent_he3->     ProfileY("p_vn_pT_00to10_he3", 15, 16);
//   TProfile *p_vn_pT_10to40_he3 =      p2_vn_pT_cent_he3->     ProfileY("p_vn_pT_10to40_he3", 9, 14);
//   TProfile *p_vn_pT_40to60_he3 =      p2_vn_pT_cent_he3->     ProfileY("p_vn_pT_40to60_he3", 5, 8);
//   TProfile *p_vn_pT_00to10_he3_yMid = p2_vn_pT_cent_he3_yMid->ProfileY("p_vn_pT_00to10_he3_yMid", 15, 16);
//   TProfile *p_vn_pT_10to40_he3_yMid = p2_vn_pT_cent_he3_yMid->ProfileY("p_vn_pT_10to40_he3_yMid", 9, 14);
//   TProfile *p_vn_pT_40to60_he3_yMid = p2_vn_pT_cent_he3_yMid->ProfileY("p_vn_pT_40to60_he3_yMid", 5, 8);
//   TProfile *p_vn_pT_00to10_he3_yFor = p2_vn_pT_cent_he3_yFor->ProfileY("p_vn_pT_00to10_he3_yFor", 15, 16);
//   TProfile *p_vn_pT_10to40_he3_yFor = p2_vn_pT_cent_he3_yFor->ProfileY("p_vn_pT_10to40_he3_yFor", 9, 14);
//   TProfile *p_vn_pT_40to60_he3_yFor = p2_vn_pT_cent_he3_yFor->ProfileY("p_vn_pT_40to60_he3_yFor", 5, 8);
//   TProfile *p_vn_pT_00to10_he3_yExt = p2_vn_pT_cent_he3_yExt->ProfileY("p_vn_pT_00to10_he3_yExt", 15, 16);
//   TProfile *p_vn_pT_10to40_he3_yExt = p2_vn_pT_cent_he3_yExt->ProfileY("p_vn_pT_10to40_he3_yExt", 9, 14);
//   TProfile *p_vn_pT_40to60_he3_yExt = p2_vn_pT_cent_he3_yExt->ProfileY("p_vn_pT_40to60_he3_yExt", 5, 8);
//   TProfile *p_vn_pT_00to10_he3_yEnd = p2_vn_pT_cent_he3_yEnd->ProfileY("p_vn_pT_00to10_he3_yEnd", 15, 16);
//   TProfile *p_vn_pT_10to40_he3_yEnd = p2_vn_pT_cent_he3_yEnd->ProfileY("p_vn_pT_10to40_he3_yEnd", 9, 14);
//   TProfile *p_vn_pT_40to60_he3_yEnd = p2_vn_pT_cent_he3_yEnd->ProfileY("p_vn_pT_40to60_he3_yEnd", 5, 8);

//   TProfile *p_vn_pT_00to10_he4 =      p2_vn_pT_cent_he4->     ProfileY("p_vn_pT_00to10_he4", 15, 16);
//   TProfile *p_vn_pT_10to40_he4 =      p2_vn_pT_cent_he4->     ProfileY("p_vn_pT_10to40_he4", 9, 14);
//   TProfile *p_vn_pT_40to60_he4 =      p2_vn_pT_cent_he4->     ProfileY("p_vn_pT_40to60_he4", 5, 8);
//   TProfile *p_vn_pT_00to10_he4_yMid = p2_vn_pT_cent_he4_yMid->ProfileY("p_vn_pT_00to10_he4_yMid", 15, 16);
//   TProfile *p_vn_pT_10to40_he4_yMid = p2_vn_pT_cent_he4_yMid->ProfileY("p_vn_pT_10to40_he4_yMid", 9, 14);
//   TProfile *p_vn_pT_40to60_he4_yMid = p2_vn_pT_cent_he4_yMid->ProfileY("p_vn_pT_40to60_he4_yMid", 5, 8);
//   TProfile *p_vn_pT_00to10_he4_yFor = p2_vn_pT_cent_he4_yFor->ProfileY("p_vn_pT_00to10_he4_yFor", 15, 16);
//   TProfile *p_vn_pT_10to40_he4_yFor = p2_vn_pT_cent_he4_yFor->ProfileY("p_vn_pT_10to40_he4_yFor", 9, 14);
//   TProfile *p_vn_pT_40to60_he4_yFor = p2_vn_pT_cent_he4_yFor->ProfileY("p_vn_pT_40to60_he4_yFor", 5, 8);
//   TProfile *p_vn_pT_00to10_he4_yExt = p2_vn_pT_cent_he4_yExt->ProfileY("p_vn_pT_00to10_he4_yExt", 15, 16);
//   TProfile *p_vn_pT_10to40_he4_yExt = p2_vn_pT_cent_he4_yExt->ProfileY("p_vn_pT_10to40_he4_yExt", 9, 14);
//   TProfile *p_vn_pT_40to60_he4_yExt = p2_vn_pT_cent_he4_yExt->ProfileY("p_vn_pT_40to60_he4_yExt", 5, 8);
//   TProfile *p_vn_pT_00to10_he4_yEnd = p2_vn_pT_cent_he4_yEnd->ProfileY("p_vn_pT_00to10_he4_yEnd", 15, 16);
//   TProfile *p_vn_pT_10to40_he4_yEnd = p2_vn_pT_cent_he4_yEnd->ProfileY("p_vn_pT_10to40_he4_yEnd", 9, 14);
//   TProfile *p_vn_pT_40to60_he4_yEnd = p2_vn_pT_cent_he4_yEnd->ProfileY("p_vn_pT_40to60_he4_yEnd", 5, 8);


  h_vn_pT_00to10_pr = new TH1D("h_vn_pT_00to10_pr", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
  h_vn_pT_10to40_pr = new TH1D("h_vn_pT_10to40_pr", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
  h_vn_pT_40to60_pr = new TH1D("h_vn_pT_40to60_pr", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_pr_yMid = new TH1D("h_vn_pT_00to10_pr_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_pr_yMid = new TH1D("h_vn_pT_10to40_pr_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_pr_yMid = new TH1D("h_vn_pT_40to60_pr_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_pr_yFor = new TH1D("h_vn_pT_00to10_pr_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_pr_yFor = new TH1D("h_vn_pT_10to40_pr_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_pr_yFor = new TH1D("h_vn_pT_40to60_pr_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_pr_yExt = new TH1D("h_vn_pT_00to10_pr_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_pr_yExt = new TH1D("h_vn_pT_10to40_pr_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_pr_yExt = new TH1D("h_vn_pT_40to60_pr_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_pr_yEnd = new TH1D("h_vn_pT_00to10_pr_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_pr_yEnd = new TH1D("h_vn_pT_10to40_pr_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_pr_yEnd = new TH1D("h_vn_pT_40to60_pr_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
  
//   h_vn_pT_00to10_tr      = new TH1D("h_vn_pT_00to10_tr", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_tr      = new TH1D("h_vn_pT_10to40_tr", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_tr      = new TH1D("h_vn_pT_40to60_tr", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_tr_yMid = new TH1D("h_vn_pT_00to10_tr_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_tr_yMid = new TH1D("h_vn_pT_10to40_tr_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_tr_yMid = new TH1D("h_vn_pT_40to60_tr_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_tr_yFor = new TH1D("h_vn_pT_00to10_tr_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_tr_yFor = new TH1D("h_vn_pT_10to40_tr_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_tr_yFor = new TH1D("h_vn_pT_40to60_tr_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_tr_yExt = new TH1D("h_vn_pT_00to10_tr_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_tr_yExt = new TH1D("h_vn_pT_10to40_tr_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_tr_yExt = new TH1D("h_vn_pT_40to60_tr_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_tr_yEnd = new TH1D("h_vn_pT_00to10_tr_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_tr_yEnd = new TH1D("h_vn_pT_10to40_tr_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_tr_yEnd = new TH1D("h_vn_pT_40to60_tr_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
  
//   h_vn_pT_00to10_he3      = new TH1D("h_vn_pT_00to10_he3", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_he3      = new TH1D("h_vn_pT_10to40_he3", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_he3      = new TH1D("h_vn_pT_40to60_he3", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_he3_yMid = new TH1D("h_vn_pT_00to10_he3_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_he3_yMid = new TH1D("h_vn_pT_10to40_he3_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_he3_yMid = new TH1D("h_vn_pT_40to60_he3_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_he3_yFor = new TH1D("h_vn_pT_00to10_he3_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_he3_yFor = new TH1D("h_vn_pT_10to40_he3_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_he3_yFor = new TH1D("h_vn_pT_40to60_he3_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_he3_yExt = new TH1D("h_vn_pT_00to10_he3_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_he3_yExt = new TH1D("h_vn_pT_10to40_he3_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_he3_yExt = new TH1D("h_vn_pT_40to60_he3_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_he3_yEnd = new TH1D("h_vn_pT_00to10_he3_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_he3_yEnd = new TH1D("h_vn_pT_10to40_he3_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_he3_yEnd = new TH1D("h_vn_pT_40to60_he3_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
  
//   h_vn_pT_00to10_he4      = new TH1D("h_vn_pT_00to10_he4", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_he4      = new TH1D("h_vn_pT_10to40_he4", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_he4      = new TH1D("h_vn_pT_40to60_he4", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_he4_yMid = new TH1D("h_vn_pT_00to10_he4_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_he4_yMid = new TH1D("h_vn_pT_10to40_he4_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_he4_yMid = new TH1D("h_vn_pT_40to60_he4_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_he4_yFor = new TH1D("h_vn_pT_00to10_he4_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_he4_yFor = new TH1D("h_vn_pT_10to40_he4_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_he4_yFor = new TH1D("h_vn_pT_40to60_he4_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_he4_yExt = new TH1D("h_vn_pT_00to10_he4_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_he4_yExt = new TH1D("h_vn_pT_10to40_he4_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_he4_yExt = new TH1D("h_vn_pT_40to60_he4_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_00to10_he4_yEnd = new TH1D("h_vn_pT_00to10_he4_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_10to40_he4_yEnd = new TH1D("h_vn_pT_10to40_he4_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);
//   h_vn_pT_40to60_he4_yEnd = new TH1D("h_vn_pT_40to60_he4_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}", 10, 0, 2);

  h_vn_pT_00to10_pr = p_vn_pT_00to10_pr->ProjectionX();
  h_vn_pT_10to40_pr = p_vn_pT_10to40_pr->ProjectionX();
  h_vn_pT_40to60_pr = p_vn_pT_40to60_pr->ProjectionX();
//   h_vn_pT_00to10_pr_yMid = p_vn_pT_00to10_pr_yMid->ProjectionX();
//   h_vn_pT_10to40_pr_yMid = p_vn_pT_10to40_pr_yMid->ProjectionX();
//   h_vn_pT_40to60_pr_yMid = p_vn_pT_40to60_pr_yMid->ProjectionX();
//   h_vn_pT_00to10_pr_yFor = p_vn_pT_00to10_pr_yFor->ProjectionX();
//   h_vn_pT_10to40_pr_yFor = p_vn_pT_10to40_pr_yFor->ProjectionX();
//   h_vn_pT_40to60_pr_yFor = p_vn_pT_40to60_pr_yFor->ProjectionX();
//   h_vn_pT_00to10_pr_yExt = p_vn_pT_00to10_pr_yExt->ProjectionX();
//   h_vn_pT_10to40_pr_yExt = p_vn_pT_10to40_pr_yExt->ProjectionX();
//   h_vn_pT_40to60_pr_yExt = p_vn_pT_40to60_pr_yExt->ProjectionX();
//   h_vn_pT_00to10_pr_yEnd = p_vn_pT_00to10_pr_yEnd->ProjectionX();
//   h_vn_pT_10to40_pr_yEnd = p_vn_pT_10to40_pr_yEnd->ProjectionX();
//   h_vn_pT_40to60_pr_yEnd = p_vn_pT_40to60_pr_yEnd->ProjectionX();

//   h_vn_pT_00to10_de = p_vn_pT_00to10_de->ProjectionX();
//   h_vn_pT_10to40_de = p_vn_pT_10to40_de->ProjectionX();
//   h_vn_pT_40to60_de = p_vn_pT_40to60_de->ProjectionX();
//   h_vn_pT_00to10_de_yMid = p_vn_pT_00to10_de_yMid->ProjectionX();
//   h_vn_pT_10to40_de_yMid = p_vn_pT_10to40_de_yMid->ProjectionX();
//   h_vn_pT_40to60_de_yMid = p_vn_pT_40to60_de_yMid->ProjectionX();
//   h_vn_pT_00to10_de_yFor = p_vn_pT_00to10_de_yFor->ProjectionX();
//   h_vn_pT_10to40_de_yFor = p_vn_pT_10to40_de_yFor->ProjectionX();
//   h_vn_pT_40to60_de_yFor = p_vn_pT_40to60_de_yFor->ProjectionX();
//   h_vn_pT_00to10_de_yExt = p_vn_pT_00to10_de_yExt->ProjectionX();
//   h_vn_pT_10to40_de_yExt = p_vn_pT_10to40_de_yExt->ProjectionX();
//   h_vn_pT_40to60_de_yExt = p_vn_pT_40to60_de_yExt->ProjectionX();
//   h_vn_pT_00to10_de_yEnd = p_vn_pT_00to10_de_yEnd->ProjectionX();
//   h_vn_pT_10to40_de_yEnd = p_vn_pT_10to40_de_yEnd->ProjectionX();
//   h_vn_pT_40to60_de_yEnd = p_vn_pT_40to60_de_yEnd->ProjectionX();

//   h_vn_pT_00to10_tr =      p_vn_pT_00to10_tr->ProjectionX();
//   h_vn_pT_10to40_tr =      p_vn_pT_10to40_tr->ProjectionX();
//   h_vn_pT_40to60_tr =      p_vn_pT_40to60_tr->ProjectionX();
//   h_vn_pT_00to10_tr_yMid = p_vn_pT_00to10_tr_yMid->ProjectionX();
//   h_vn_pT_10to40_tr_yMid = p_vn_pT_10to40_tr_yMid->ProjectionX();
//   h_vn_pT_40to60_tr_yMid = p_vn_pT_40to60_tr_yMid->ProjectionX();
//   h_vn_pT_00to10_tr_yFor = p_vn_pT_00to10_tr_yFor->ProjectionX();
//   h_vn_pT_10to40_tr_yFor = p_vn_pT_10to40_tr_yFor->ProjectionX();
//   h_vn_pT_40to60_tr_yFor = p_vn_pT_40to60_tr_yFor->ProjectionX();
//   h_vn_pT_00to10_tr_yExt = p_vn_pT_00to10_tr_yExt->ProjectionX();
//   h_vn_pT_10to40_tr_yExt = p_vn_pT_10to40_tr_yExt->ProjectionX();
//   h_vn_pT_40to60_tr_yExt = p_vn_pT_40to60_tr_yExt->ProjectionX();
//   h_vn_pT_00to10_tr_yEnd = p_vn_pT_00to10_tr_yEnd->ProjectionX();
//   h_vn_pT_10to40_tr_yEnd = p_vn_pT_10to40_tr_yEnd->ProjectionX();
//   h_vn_pT_40to60_tr_yEnd = p_vn_pT_40to60_tr_yEnd->ProjectionX();

//   h_vn_pT_00to10_he3 =      p_vn_pT_00to10_he3->ProjectionX();
//   h_vn_pT_10to40_he3 =      p_vn_pT_10to40_he3->ProjectionX();
//   h_vn_pT_40to60_he3 =      p_vn_pT_40to60_he3->ProjectionX();
//   h_vn_pT_00to10_he3_yMid = p_vn_pT_00to10_he3_yMid->ProjectionX();
//   h_vn_pT_10to40_he3_yMid = p_vn_pT_10to40_he3_yMid->ProjectionX();
//   h_vn_pT_40to60_he3_yMid = p_vn_pT_40to60_he3_yMid->ProjectionX();
//   h_vn_pT_00to10_he3_yFor = p_vn_pT_00to10_he3_yFor->ProjectionX();
//   h_vn_pT_10to40_he3_yFor = p_vn_pT_10to40_he3_yFor->ProjectionX();
//   h_vn_pT_40to60_he3_yFor = p_vn_pT_40to60_he3_yFor->ProjectionX();
//   h_vn_pT_00to10_he3_yExt = p_vn_pT_00to10_he3_yExt->ProjectionX();
//   h_vn_pT_10to40_he3_yExt = p_vn_pT_10to40_he3_yExt->ProjectionX();
//   h_vn_pT_40to60_he3_yExt = p_vn_pT_40to60_he3_yExt->ProjectionX();
//   h_vn_pT_00to10_he3_yEnd = p_vn_pT_00to10_he3_yEnd->ProjectionX();
//   h_vn_pT_10to40_he3_yEnd = p_vn_pT_10to40_he3_yEnd->ProjectionX();
//   h_vn_pT_40to60_he3_yEnd = p_vn_pT_40to60_he3_yEnd->ProjectionX();

//   h_vn_pT_00to10_he4 =      p_vn_pT_00to10_he4->ProjectionX();
//   h_vn_pT_10to40_he4 =      p_vn_pT_10to40_he4->ProjectionX();
//   h_vn_pT_40to60_he4 =      p_vn_pT_40to60_he4->ProjectionX();
//   h_vn_pT_00to10_he4_yMid = p_vn_pT_00to10_he4_yMid->ProjectionX();
//   h_vn_pT_10to40_he4_yMid = p_vn_pT_10to40_he4_yMid->ProjectionX();
//   h_vn_pT_40to60_he4_yMid = p_vn_pT_40to60_he4_yMid->ProjectionX();
//   h_vn_pT_00to10_he4_yFor = p_vn_pT_00to10_he4_yFor->ProjectionX();
//   h_vn_pT_10to40_he4_yFor = p_vn_pT_10to40_he4_yFor->ProjectionX();
//   h_vn_pT_40to60_he4_yFor = p_vn_pT_40to60_he4_yFor->ProjectionX();
//   h_vn_pT_00to10_he4_yExt = p_vn_pT_00to10_he4_yExt->ProjectionX();
//   h_vn_pT_10to40_he4_yExt = p_vn_pT_10to40_he4_yExt->ProjectionX();
//   h_vn_pT_40to60_he4_yExt = p_vn_pT_40to60_he4_yExt->ProjectionX();
//   h_vn_pT_00to10_he4_yEnd = p_vn_pT_00to10_he4_yEnd->ProjectionX();
//   h_vn_pT_10to40_he4_yEnd = p_vn_pT_10to40_he4_yEnd->ProjectionX();
//   h_vn_pT_40to60_he4_yEnd = p_vn_pT_40to60_he4_yEnd->ProjectionX();

}// End initialize()



// Use this with the "Normal" Variation to clean up the plots
void Variation::fixAttributes(TString order_n_str)
{
  //if (order_n_str == "3")
  if (order_n_str == "3")
    {
      Double_t centralityUpperBounds = 0.15;
      Double_t centralityLowerBounds = -0.15;
      
      h_vn_pp->SetMarkerStyle(20);
      h_vn_pp->SetMarkerSize(2.5);
      h_vn_pp->SetMarkerColor(2);
      h_vn_pp->SetLineColor(2);
      h_vn_pp->SetLineWidth(3);
//       h_vn_pp->GetYaxis()->SetTitleOffset(1.7);
//       h_vn_pp->GetXaxis()->SetNdivisions(210);
//       //h_vn_pp->SetMaximum(centralityUpperBounds);
//       //h_vn_pp->SetMinimum(centralityLowerBounds);

      h_vn_pm->SetMarkerStyle(20);
      h_vn_pm->SetMarkerSize(2.5);
      h_vn_pm->SetMarkerColor(4);
      h_vn_pm->SetLineColor(4);
      h_vn_pm->SetLineWidth(3);
//       h_vn_pm->GetYaxis()->SetTitleOffset(1.7);
//       h_vn_pm->GetXaxis()->SetNdivisions(210);
//       //h_vn_pm->SetMaximum(centralityUpperBounds);
//       //h_vn_pm->SetMinimum(centralityLowerBounds);

      h_vn_kp->SetMarkerStyle(20);
      h_vn_kp->SetMarkerSize(2.5);
      h_vn_kp->SetMarkerColor(2);
      h_vn_kp->SetLineColor(2);
      h_vn_kp->SetLineWidth(3);
//       h_vn_kp->GetYaxis()->SetTitleOffset(1.7);
//       h_vn_kp->GetXaxis()->SetNdivisions(210);
//       //h_vn_kp->SetMaximum(centralityUpperBounds);
//       //h_vn_kp->SetMinimum(centralityLowerBounds);

      h_vn_km->SetMarkerStyle(20);
      h_vn_km->SetMarkerSize(2.5);
      h_vn_km->SetMarkerColor(4);
      h_vn_km->SetLineColor(4);
      h_vn_km->SetLineWidth(3);
//       h_vn_km->GetYaxis()->SetTitleOffset(1.7);
//       h_vn_km->GetXaxis()->SetNdivisions(210);
//       //h_vn_km->SetMaximum(centralityUpperBounds);
//       //h_vn_km->SetMinimum(centralityLowerBounds);

  
//      h_vn_pr->SetTitle(";Centrality (%);v_{"+order_n_str+"}");
      h_vn_pr->SetMarkerStyle(20);
      h_vn_pr->SetMarkerSize(2.5);
      h_vn_pr->SetMarkerColor(2);
      h_vn_pr->SetLineColor(2);
      h_vn_pr->SetLineWidth(3);
//       h_vn_pr->GetYaxis()->SetTitleOffset(1.7);
//       h_vn_pr->GetXaxis()->SetNdivisions(210);
//       //h_vn_pr->SetMaximum(centralityUpperBounds);
//       //h_vn_pr->SetMinimum(centralityLowerBounds);

      h_vn_de->SetTitle(";Centrality (%);v_{"+order_n_str+"}");
      h_vn_de->SetMarkerStyle(20);
      h_vn_de->SetMarkerSize(2.5);
      h_vn_de->SetMarkerColor(2);
      h_vn_de->SetLineColor(2);
      h_vn_de->SetLineWidth(3);
//       h_vn_de->GetYaxis()->SetTitleOffset(1.7);
//       h_vn_de->GetXaxis()->SetNdivisions(210);

      h_vn_tr->SetTitle(";Centrality (%);v_{"+order_n_str+"}");
      h_vn_tr->SetMarkerStyle(20);
      h_vn_tr->SetMarkerSize(2.5);
      h_vn_tr->SetMarkerColor(2);
      h_vn_tr->SetLineColor(2);
      h_vn_tr->SetLineWidth(3);
//       h_vn_tr->GetYaxis()->SetTitleOffset(1.7);
//       h_vn_tr->GetXaxis()->SetNdivisions(210);

//       h_vn_he3->SetTitle(";Centrality (%);v_{"+order_n_str+"}");
//       h_vn_he3->SetMarkerStyle(20);
//       h_vn_he3->SetMarkerSize(2.5);
//       h_vn_he3->SetMarkerColor(2);
//       h_vn_he3->SetLineColor(2);
//       h_vn_he3->SetLineWidth(3);
//       h_vn_he3->GetYaxis()->SetTitleOffset(1.7);
//       h_vn_he3->GetXaxis()->SetNdivisions(210);

//       h_vn_he4->SetTitle(";Centrality (%);v_{"+order_n_str+"}");
//       h_vn_he4->SetMarkerStyle(20);
//       h_vn_he4->SetMarkerSize(2.5);
//       h_vn_he4->SetMarkerColor(2);
//       h_vn_he4->SetLineColor(2);
//       h_vn_he4->SetLineWidth(3);
//       h_vn_he4->GetYaxis()->SetTitleOffset(1.7);
//       h_vn_he4->GetXaxis()->SetNdivisions(210);

      //=== vn vs rapidity
//       h_vn_yCM_00to10_pr->SetMarkerStyle(20);
//       h_vn_yCM_10to40_pr->SetMarkerStyle(20);
//       h_vn_yCM_40to60_pr->SetMarkerStyle(20);
//       h_vn_yCM_00to10_pr->SetMarkerColor(2);
//       h_vn_yCM_10to40_pr->SetMarkerColor(4);
//       h_vn_yCM_40to60_pr->SetMarkerColor(8);
//       h_vn_yCM_00to10_pr->SetMarkerSize(2);
//       h_vn_yCM_10to40_pr->SetMarkerSize(2);
//       h_vn_yCM_40to60_pr->SetMarkerSize(2);
//       h_vn_yCM_00to10_pr->SetLineColor(2);
//       h_vn_yCM_10to40_pr->SetLineColor(4);
//       h_vn_yCM_40to60_pr->SetLineColor(8);
//       h_vn_yCM_00to10_pr->SetLineWidth(3);
//       h_vn_yCM_10to40_pr->SetLineWidth(3);
//       h_vn_yCM_40to60_pr->SetLineWidth(3);
      
//       h_vn_yCM_00to10_kp->SetMarkerStyle(20);
//       h_vn_yCM_10to40_kp->SetMarkerStyle(20);
//       h_vn_yCM_40to60_kp->SetMarkerStyle(20);
//       h_vn_yCM_00to10_kp->SetMarkerColor(2);
//       h_vn_yCM_10to40_kp->SetMarkerColor(4);
//       h_vn_yCM_40to60_kp->SetMarkerColor(8);
//       h_vn_yCM_00to10_kp->SetMarkerSize(2);
//       h_vn_yCM_10to40_kp->SetMarkerSize(2);
//       h_vn_yCM_40to60_kp->SetMarkerSize(2);
//       h_vn_yCM_00to10_kp->SetLineColor(2);
//       h_vn_yCM_10to40_kp->SetLineColor(4);
//       h_vn_yCM_40to60_kp->SetLineColor(8);
//       h_vn_yCM_00to10_kp->SetLineWidth(3);
//       h_vn_yCM_10to40_kp->SetLineWidth(3);
//       h_vn_yCM_40to60_kp->SetLineWidth(3);
      
//       h_vn_yCM_00to10_km->SetMarkerStyle(20);
//       h_vn_yCM_10to40_km->SetMarkerStyle(20);
//       h_vn_yCM_40to60_km->SetMarkerStyle(20);
//       h_vn_yCM_00to10_km->SetMarkerColor(2);
//       h_vn_yCM_10to40_km->SetMarkerColor(4);
//       h_vn_yCM_40to60_km->SetMarkerColor(8);
//       h_vn_yCM_00to10_km->SetMarkerSize(2);
//       h_vn_yCM_10to40_km->SetMarkerSize(2);
//       h_vn_yCM_40to60_km->SetMarkerSize(2);
//       h_vn_yCM_00to10_km->SetLineColor(2);
//       h_vn_yCM_10to40_km->SetLineColor(4);
//       h_vn_yCM_40to60_km->SetLineColor(8);
//       h_vn_yCM_00to10_km->SetLineWidth(3);
//       h_vn_yCM_10to40_km->SetLineWidth(3);
//       h_vn_yCM_40to60_km->SetLineWidth(3);
      
//       h_vn_yCM_00to10_pp->SetMarkerStyle(20);
//       h_vn_yCM_10to40_pp->SetMarkerStyle(20);
//       h_vn_yCM_40to60_pp->SetMarkerStyle(20);
//       h_vn_yCM_00to10_pp->SetMarkerColor(2);
//       h_vn_yCM_10to40_pp->SetMarkerColor(4);
//       h_vn_yCM_40to60_pp->SetMarkerColor(8);
//       h_vn_yCM_00to10_pp->SetMarkerSize(2);
//       h_vn_yCM_10to40_pp->SetMarkerSize(2);
//       h_vn_yCM_40to60_pp->SetMarkerSize(2);
//       h_vn_yCM_00to10_pp->SetLineColor(2);
//       h_vn_yCM_10to40_pp->SetLineColor(4);
//       h_vn_yCM_40to60_pp->SetLineColor(8);
//       h_vn_yCM_00to10_pp->SetLineWidth(3);
//       h_vn_yCM_10to40_pp->SetLineWidth(3);
//       h_vn_yCM_40to60_pp->SetLineWidth(3);
      
//       h_vn_yCM_00to10_pm->SetMarkerStyle(20);
//       h_vn_yCM_10to40_pm->SetMarkerStyle(20);
//       h_vn_yCM_40to60_pm->SetMarkerStyle(20);
//       h_vn_yCM_00to10_pm->SetMarkerColor(2);
//       h_vn_yCM_10to40_pm->SetMarkerColor(4);
//       h_vn_yCM_40to60_pm->SetMarkerColor(8);
//       h_vn_yCM_00to10_pm->SetMarkerSize(2);
//       h_vn_yCM_10to40_pm->SetMarkerSize(2);
//       h_vn_yCM_40to60_pm->SetMarkerSize(2);
//       h_vn_yCM_00to10_pm->SetLineColor(2);
//       h_vn_yCM_10to40_pm->SetLineColor(4);
//       h_vn_yCM_40to60_pm->SetLineColor(8);
//       h_vn_yCM_00to10_pm->SetLineWidth(3);
//       h_vn_yCM_10to40_pm->SetLineWidth(3);
//       h_vn_yCM_40to60_pm->SetLineWidth(3);

//       h_vn_yCM_00to10_pr_symm->SetMarkerStyle(20);
//       h_vn_yCM_10to40_pr_symm->SetMarkerStyle(20);
//       h_vn_yCM_40to60_pr_symm->SetMarkerStyle(20);
//       h_vn_yCM_00to10_pr_symm->SetMarkerColor(2);
//       h_vn_yCM_10to40_pr_symm->SetMarkerColor(4);
//       h_vn_yCM_40to60_pr_symm->SetMarkerColor(8);
//       h_vn_yCM_00to10_pr_symm->SetMarkerSize(2);
//       h_vn_yCM_10to40_pr_symm->SetMarkerSize(2);
//       h_vn_yCM_40to60_pr_symm->SetMarkerSize(2);
//       h_vn_yCM_00to10_pr_symm->SetLineColor(2);
//       h_vn_yCM_10to40_pr_symm->SetLineColor(4);
//       h_vn_yCM_40to60_pr_symm->SetLineColor(8);
//       h_vn_yCM_00to10_pr_symm->SetLineWidth(3);
//       h_vn_yCM_10to40_pr_symm->SetLineWidth(3);
//       h_vn_yCM_40to60_pr_symm->SetLineWidth(3);

//       h_vn_yCM_00to10_de->SetMarkerStyle(20);
//       h_vn_yCM_10to40_de->SetMarkerStyle(20);
//       h_vn_yCM_40to60_de->SetMarkerStyle(20);
//       h_vn_yCM_00to10_de->SetMarkerColor(2);
//       h_vn_yCM_10to40_de->SetMarkerColor(4);
//       h_vn_yCM_40to60_de->SetMarkerColor(8);
//       h_vn_yCM_00to10_de->SetMarkerSize(2);
//       h_vn_yCM_10to40_de->SetMarkerSize(2);
//       h_vn_yCM_40to60_de->SetMarkerSize(2);
//       h_vn_yCM_00to10_de->SetLineColor(2);
//       h_vn_yCM_10to40_de->SetLineColor(4);
//       h_vn_yCM_40to60_de->SetLineColor(8);
//       h_vn_yCM_00to10_de->SetLineWidth(3);
//       h_vn_yCM_10to40_de->SetLineWidth(3);
//       h_vn_yCM_40to60_de->SetLineWidth(3);

//       h_vn_yCM_00to10_tr->SetMarkerStyle(20);
//       h_vn_yCM_10to40_tr->SetMarkerStyle(20);
//       h_vn_yCM_40to60_tr->SetMarkerStyle(20);
//       h_vn_yCM_00to10_tr->SetMarkerColor(2);
//       h_vn_yCM_10to40_tr->SetMarkerColor(4);
//       h_vn_yCM_40to60_tr->SetMarkerColor(8);
//       h_vn_yCM_00to10_tr->SetMarkerSize(2);
//       h_vn_yCM_10to40_tr->SetMarkerSize(2);
//       h_vn_yCM_40to60_tr->SetMarkerSize(2);
//       h_vn_yCM_00to10_tr->SetLineColor(2);
//       h_vn_yCM_10to40_tr->SetLineColor(4);
//       h_vn_yCM_40to60_tr->SetLineColor(8);
//       h_vn_yCM_00to10_tr->SetLineWidth(3);
//       h_vn_yCM_10to40_tr->SetLineWidth(3);
//       h_vn_yCM_40to60_tr->SetLineWidth(3);

//       h_vn_yCM_00to10_he3->SetMarkerStyle(20);
//       h_vn_yCM_10to40_he3->SetMarkerStyle(20);
//       h_vn_yCM_40to60_he3->SetMarkerStyle(20);
//       h_vn_yCM_00to10_he3->SetMarkerColor(2);
//       h_vn_yCM_10to40_he3->SetMarkerColor(4);
//       h_vn_yCM_40to60_he3->SetMarkerColor(8);
//       h_vn_yCM_00to10_he3->SetMarkerSize(2);
//       h_vn_yCM_10to40_he3->SetMarkerSize(2);
//       h_vn_yCM_40to60_he3->SetMarkerSize(2);
//       h_vn_yCM_00to10_he3->SetLineColor(2);
//       h_vn_yCM_10to40_he3->SetLineColor(4);
//       h_vn_yCM_40to60_he3->SetLineColor(8);
//       h_vn_yCM_00to10_he3->SetLineWidth(3);
//       h_vn_yCM_10to40_he3->SetLineWidth(3);
//       h_vn_yCM_40to60_he3->SetLineWidth(3);

//       h_vn_yCM_00to10_he4->SetMarkerStyle(20);
//       h_vn_yCM_10to40_he4->SetMarkerStyle(20);
//       h_vn_yCM_40to60_he4->SetMarkerStyle(20);
//       h_vn_yCM_00to10_he4->SetMarkerColor(2);
//       h_vn_yCM_10to40_he4->SetMarkerColor(4);
//       h_vn_yCM_40to60_he4->SetMarkerColor(8);
//       h_vn_yCM_00to10_he4->SetMarkerSize(2);
//       h_vn_yCM_10to40_he4->SetMarkerSize(2);
//       h_vn_yCM_40to60_he4->SetMarkerSize(2);
//       h_vn_yCM_00to10_he4->SetLineColor(2);
//       h_vn_yCM_10to40_he4->SetLineColor(4);
//       h_vn_yCM_40to60_he4->SetLineColor(8);
//       h_vn_yCM_00to10_he4->SetLineWidth(3);
//       h_vn_yCM_10to40_he4->SetLineWidth(3);
//       h_vn_yCM_40to60_he4->SetLineWidth(3);


      //=== vn vs pT  
//       h_vn_pT_00to10_pr->SetMarkerStyle(20);
//       h_vn_pT_10to40_pr->SetMarkerStyle(20);
//       h_vn_pT_40to60_pr->SetMarkerStyle(20);
//       h_vn_pT_00to10_pr->SetMarkerColor(2);
//       h_vn_pT_10to40_pr->SetMarkerColor(4);
//       h_vn_pT_40to60_pr->SetMarkerColor(8);
//       h_vn_pT_00to10_pr->SetMarkerSize(2);
//       h_vn_pT_10to40_pr->SetMarkerSize(2);
//       h_vn_pT_40to60_pr->SetMarkerSize(2);
//       h_vn_pT_00to10_pr->SetLineColor(2);
//       h_vn_pT_10to40_pr->SetLineColor(4);
//       h_vn_pT_40to60_pr->SetLineColor(8);
//       h_vn_pT_00to10_pr->SetLineWidth(3);
//       h_vn_pT_10to40_pr->SetLineWidth(3);
//       h_vn_pT_40to60_pr->SetLineWidth(3);
//       h_vn_pT_00to10_pr_yMid->SetMarkerStyle(20);
//       h_vn_pT_10to40_pr_yMid->SetMarkerStyle(20);
//       h_vn_pT_40to60_pr_yMid->SetMarkerStyle(20);
//       h_vn_pT_00to10_pr_yMid->SetMarkerColor(2);
//       h_vn_pT_10to40_pr_yMid->SetMarkerColor(4);
//       h_vn_pT_40to60_pr_yMid->SetMarkerColor(8);
//       h_vn_pT_00to10_pr_yMid->SetMarkerSize(2);
//       h_vn_pT_10to40_pr_yMid->SetMarkerSize(2);
//       h_vn_pT_40to60_pr_yMid->SetMarkerSize(2);
//       h_vn_pT_00to10_pr_yMid->SetLineColor(2);
//       h_vn_pT_10to40_pr_yMid->SetLineColor(4);
//       h_vn_pT_40to60_pr_yMid->SetLineColor(8);
//       h_vn_pT_00to10_pr_yMid->SetLineWidth(3);
//       h_vn_pT_10to40_pr_yMid->SetLineWidth(3);
//       h_vn_pT_40to60_pr_yMid->SetLineWidth(3);
//       h_vn_pT_00to10_pr_yFor->SetMarkerStyle(20);
//       h_vn_pT_10to40_pr_yFor->SetMarkerStyle(20);
//       h_vn_pT_40to60_pr_yFor->SetMarkerStyle(20);
//       h_vn_pT_00to10_pr_yFor->SetMarkerColor(2);
//       h_vn_pT_10to40_pr_yFor->SetMarkerColor(4);
//       h_vn_pT_40to60_pr_yFor->SetMarkerColor(8);
//       h_vn_pT_00to10_pr_yFor->SetMarkerSize(2);
//       h_vn_pT_10to40_pr_yFor->SetMarkerSize(2);
//       h_vn_pT_40to60_pr_yFor->SetMarkerSize(2);
//       h_vn_pT_00to10_pr_yFor->SetLineColor(2);
//       h_vn_pT_10to40_pr_yFor->SetLineColor(4);
//       h_vn_pT_40to60_pr_yFor->SetLineColor(8);
//       h_vn_pT_00to10_pr_yFor->SetLineWidth(3);
//       h_vn_pT_10to40_pr_yFor->SetLineWidth(3);
//       h_vn_pT_40to60_pr_yFor->SetLineWidth(3);
//       h_vn_pT_00to10_pr_yExt->SetMarkerStyle(20);
//       h_vn_pT_10to40_pr_yExt->SetMarkerStyle(20);
//       h_vn_pT_40to60_pr_yExt->SetMarkerStyle(20);
//       h_vn_pT_00to10_pr_yExt->SetMarkerColor(2);
//       h_vn_pT_10to40_pr_yExt->SetMarkerColor(4);
//       h_vn_pT_40to60_pr_yExt->SetMarkerColor(8);
//       h_vn_pT_00to10_pr_yExt->SetMarkerSize(2);
//       h_vn_pT_10to40_pr_yExt->SetMarkerSize(2);
//       h_vn_pT_40to60_pr_yExt->SetMarkerSize(2);
//       h_vn_pT_00to10_pr_yExt->SetLineColor(2);
//       h_vn_pT_10to40_pr_yExt->SetLineColor(4);
//       h_vn_pT_40to60_pr_yExt->SetLineColor(8);
//       h_vn_pT_00to10_pr_yExt->SetLineWidth(3);
//       h_vn_pT_10to40_pr_yExt->SetLineWidth(3);
//       h_vn_pT_40to60_pr_yExt->SetLineWidth(3);
//       h_vn_pT_00to10_pr_yEnd->SetMarkerStyle(20);
//       h_vn_pT_10to40_pr_yEnd->SetMarkerStyle(20);
//       h_vn_pT_40to60_pr_yEnd->SetMarkerStyle(20);
//       h_vn_pT_00to10_pr_yEnd->SetMarkerColor(2);
//       h_vn_pT_10to40_pr_yEnd->SetMarkerColor(4);
//       h_vn_pT_40to60_pr_yEnd->SetMarkerColor(8);
//       h_vn_pT_00to10_pr_yEnd->SetMarkerSize(2);
//       h_vn_pT_10to40_pr_yEnd->SetMarkerSize(2);
//       h_vn_pT_40to60_pr_yEnd->SetMarkerSize(2);
//       h_vn_pT_00to10_pr_yEnd->SetLineColor(2);
//       h_vn_pT_10to40_pr_yEnd->SetLineColor(4);
//       h_vn_pT_40to60_pr_yEnd->SetLineColor(8);
//       h_vn_pT_00to10_pr_yEnd->SetLineWidth(3);
//       h_vn_pT_10to40_pr_yEnd->SetLineWidth(3);
//       h_vn_pT_40to60_pr_yEnd->SetLineWidth(3);


//       h_vn_pT_00to10_de->SetMarkerStyle(20);
//       h_vn_pT_10to40_de->SetMarkerStyle(20);
//       h_vn_pT_40to60_de->SetMarkerStyle(20);
//       h_vn_pT_00to10_de->SetMarkerColor(2);
//       h_vn_pT_10to40_de->SetMarkerColor(4);
//       h_vn_pT_40to60_de->SetMarkerColor(8);
//       h_vn_pT_00to10_de->SetMarkerSize(2);
//       h_vn_pT_10to40_de->SetMarkerSize(2);
//       h_vn_pT_40to60_de->SetMarkerSize(2);
//       h_vn_pT_00to10_de->SetLineColor(2);
//       h_vn_pT_10to40_de->SetLineColor(4);
//       h_vn_pT_40to60_de->SetLineColor(8);
//       h_vn_pT_00to10_de->SetLineWidth(3);
//       h_vn_pT_10to40_de->SetLineWidth(3);
//       h_vn_pT_40to60_de->SetLineWidth(3);
//       h_vn_pT_00to10_de_yMid->SetMarkerStyle(20);
//       h_vn_pT_10to40_de_yMid->SetMarkerStyle(20);
//       h_vn_pT_40to60_de_yMid->SetMarkerStyle(20);
//       h_vn_pT_00to10_de_yMid->SetMarkerColor(2);
//       h_vn_pT_10to40_de_yMid->SetMarkerColor(4);
//       h_vn_pT_40to60_de_yMid->SetMarkerColor(8);
//       h_vn_pT_00to10_de_yMid->SetMarkerSize(2);
//       h_vn_pT_10to40_de_yMid->SetMarkerSize(2);
//       h_vn_pT_40to60_de_yMid->SetMarkerSize(2);
//       h_vn_pT_00to10_de_yMid->SetLineColor(2);
//       h_vn_pT_10to40_de_yMid->SetLineColor(4);
//       h_vn_pT_40to60_de_yMid->SetLineColor(8);
//       h_vn_pT_00to10_de_yMid->SetLineWidth(3);
//       h_vn_pT_10to40_de_yMid->SetLineWidth(3);
//       h_vn_pT_40to60_de_yMid->SetLineWidth(3);
//       h_vn_pT_00to10_de_yFor->SetMarkerStyle(20);
//       h_vn_pT_10to40_de_yFor->SetMarkerStyle(20);
//       h_vn_pT_40to60_de_yFor->SetMarkerStyle(20);
//       h_vn_pT_00to10_de_yFor->SetMarkerColor(2);
//       h_vn_pT_10to40_de_yFor->SetMarkerColor(4);
//       h_vn_pT_40to60_de_yFor->SetMarkerColor(8);
//       h_vn_pT_00to10_de_yFor->SetMarkerSize(2);
//       h_vn_pT_10to40_de_yFor->SetMarkerSize(2);
//       h_vn_pT_40to60_de_yFor->SetMarkerSize(2);
//       h_vn_pT_00to10_de_yFor->SetLineColor(2);
//       h_vn_pT_10to40_de_yFor->SetLineColor(4);
//       h_vn_pT_40to60_de_yFor->SetLineColor(8);
//       h_vn_pT_00to10_de_yFor->SetLineWidth(3);
//       h_vn_pT_10to40_de_yFor->SetLineWidth(3);
//       h_vn_pT_40to60_de_yFor->SetLineWidth(3);
//       h_vn_pT_00to10_de_yExt->SetMarkerStyle(20);
//       h_vn_pT_10to40_de_yExt->SetMarkerStyle(20);
//       h_vn_pT_40to60_de_yExt->SetMarkerStyle(20);
//       h_vn_pT_00to10_de_yExt->SetMarkerColor(2);
//       h_vn_pT_10to40_de_yExt->SetMarkerColor(4);
//       h_vn_pT_40to60_de_yExt->SetMarkerColor(8);
//       h_vn_pT_00to10_de_yExt->SetMarkerSize(2);
//       h_vn_pT_10to40_de_yExt->SetMarkerSize(2);
//       h_vn_pT_40to60_de_yExt->SetMarkerSize(2);
//       h_vn_pT_00to10_de_yExt->SetLineColor(2);
//       h_vn_pT_10to40_de_yExt->SetLineColor(4);
//       h_vn_pT_40to60_de_yExt->SetLineColor(8);
//       h_vn_pT_00to10_de_yExt->SetLineWidth(3);
//       h_vn_pT_10to40_de_yExt->SetLineWidth(3);
//       h_vn_pT_40to60_de_yExt->SetLineWidth(3);
//       h_vn_pT_00to10_de_yEnd->SetMarkerStyle(20);
//       h_vn_pT_10to40_de_yEnd->SetMarkerStyle(20);
//       h_vn_pT_40to60_de_yEnd->SetMarkerStyle(20);
//       h_vn_pT_00to10_de_yEnd->SetMarkerColor(2);
//       h_vn_pT_10to40_de_yEnd->SetMarkerColor(4);
//       h_vn_pT_40to60_de_yEnd->SetMarkerColor(8);
//       h_vn_pT_00to10_de_yEnd->SetMarkerSize(2);
//       h_vn_pT_10to40_de_yEnd->SetMarkerSize(2);
//       h_vn_pT_40to60_de_yEnd->SetMarkerSize(2);
//       h_vn_pT_00to10_de_yEnd->SetLineColor(2);
//       h_vn_pT_10to40_de_yEnd->SetLineColor(4);
//       h_vn_pT_40to60_de_yEnd->SetLineColor(8);
//       h_vn_pT_00to10_de_yEnd->SetLineWidth(3);
//       h_vn_pT_10to40_de_yEnd->SetLineWidth(3);
//       h_vn_pT_40to60_de_yEnd->SetLineWidth(3);

//       h_vn_pT_00to10_tr->SetMarkerStyle(20);
//       h_vn_pT_10to40_tr->SetMarkerStyle(20);
//       h_vn_pT_40to60_tr->SetMarkerStyle(20);
//       h_vn_pT_00to10_tr->SetMarkerColor(2);
//       h_vn_pT_10to40_tr->SetMarkerColor(4);
//       h_vn_pT_40to60_tr->SetMarkerColor(8);
//       h_vn_pT_00to10_tr->SetMarkerSize(2);
//       h_vn_pT_10to40_tr->SetMarkerSize(2);
//       h_vn_pT_40to60_tr->SetMarkerSize(2);
//       h_vn_pT_00to10_tr->SetLineColor(2);
//       h_vn_pT_10to40_tr->SetLineColor(4);
//       h_vn_pT_40to60_tr->SetLineColor(8);
//       h_vn_pT_00to10_tr->SetLineWidth(3);
//       h_vn_pT_10to40_tr->SetLineWidth(3);
//       h_vn_pT_40to60_tr->SetLineWidth(3);
//       h_vn_pT_00to10_tr_yMid->SetMarkerStyle(20);
//       h_vn_pT_10to40_tr_yMid->SetMarkerStyle(20);
//       h_vn_pT_40to60_tr_yMid->SetMarkerStyle(20);
//       h_vn_pT_00to10_tr_yMid->SetMarkerColor(2);
//       h_vn_pT_10to40_tr_yMid->SetMarkerColor(4);
//       h_vn_pT_40to60_tr_yMid->SetMarkerColor(8);
//       h_vn_pT_00to10_tr_yMid->SetMarkerSize(2);
//       h_vn_pT_10to40_tr_yMid->SetMarkerSize(2);
//       h_vn_pT_40to60_tr_yMid->SetMarkerSize(2);
//       h_vn_pT_00to10_tr_yMid->SetLineColor(2);
//       h_vn_pT_10to40_tr_yMid->SetLineColor(4);
//       h_vn_pT_40to60_tr_yMid->SetLineColor(8);
//       h_vn_pT_00to10_tr_yMid->SetLineWidth(3);
//       h_vn_pT_10to40_tr_yMid->SetLineWidth(3);
//       h_vn_pT_40to60_tr_yMid->SetLineWidth(3);
//       h_vn_pT_00to10_tr_yFor->SetMarkerStyle(20);
//       h_vn_pT_10to40_tr_yFor->SetMarkerStyle(20);
//       h_vn_pT_40to60_tr_yFor->SetMarkerStyle(20);
//       h_vn_pT_00to10_tr_yFor->SetMarkerColor(2);
//       h_vn_pT_10to40_tr_yFor->SetMarkerColor(4);
//       h_vn_pT_40to60_tr_yFor->SetMarkerColor(8);
//       h_vn_pT_00to10_tr_yFor->SetMarkerSize(2);
//       h_vn_pT_10to40_tr_yFor->SetMarkerSize(2);
//       h_vn_pT_40to60_tr_yFor->SetMarkerSize(2);
//       h_vn_pT_00to10_tr_yFor->SetLineColor(2);
//       h_vn_pT_10to40_tr_yFor->SetLineColor(4);
//       h_vn_pT_40to60_tr_yFor->SetLineColor(8);
//       h_vn_pT_00to10_tr_yFor->SetLineWidth(3);
//       h_vn_pT_10to40_tr_yFor->SetLineWidth(3);
//       h_vn_pT_40to60_tr_yFor->SetLineWidth(3);
//       h_vn_pT_00to10_tr_yExt->SetMarkerStyle(20);
//       h_vn_pT_10to40_tr_yExt->SetMarkerStyle(20);
//       h_vn_pT_40to60_tr_yExt->SetMarkerStyle(20);
//       h_vn_pT_00to10_tr_yExt->SetMarkerColor(2);
//       h_vn_pT_10to40_tr_yExt->SetMarkerColor(4);
//       h_vn_pT_40to60_tr_yExt->SetMarkerColor(8);
//       h_vn_pT_00to10_tr_yExt->SetMarkerSize(2);
//       h_vn_pT_10to40_tr_yExt->SetMarkerSize(2);
//       h_vn_pT_40to60_tr_yExt->SetMarkerSize(2);
//       h_vn_pT_00to10_tr_yExt->SetLineColor(2);
//       h_vn_pT_10to40_tr_yExt->SetLineColor(4);
//       h_vn_pT_40to60_tr_yExt->SetLineColor(8);
//       h_vn_pT_00to10_tr_yExt->SetLineWidth(3);
//       h_vn_pT_10to40_tr_yExt->SetLineWidth(3);
//       h_vn_pT_40to60_tr_yExt->SetLineWidth(3);
//       h_vn_pT_00to10_tr_yEnd->SetMarkerStyle(20);
//       h_vn_pT_10to40_tr_yEnd->SetMarkerStyle(20);
//       h_vn_pT_40to60_tr_yEnd->SetMarkerStyle(20);
//       h_vn_pT_00to10_tr_yEnd->SetMarkerColor(2);
//       h_vn_pT_10to40_tr_yEnd->SetMarkerColor(4);
//       h_vn_pT_40to60_tr_yEnd->SetMarkerColor(8);
//       h_vn_pT_00to10_tr_yEnd->SetMarkerSize(2);
//       h_vn_pT_10to40_tr_yEnd->SetMarkerSize(2);
//       h_vn_pT_40to60_tr_yEnd->SetMarkerSize(2);
//       h_vn_pT_00to10_tr_yEnd->SetLineColor(2);
//       h_vn_pT_10to40_tr_yEnd->SetLineColor(4);
//       h_vn_pT_40to60_tr_yEnd->SetLineColor(8);
//       h_vn_pT_00to10_tr_yEnd->SetLineWidth(3);
//       h_vn_pT_10to40_tr_yEnd->SetLineWidth(3);
//       h_vn_pT_40to60_tr_yEnd->SetLineWidth(3);

//       h_vn_pT_00to10_he3->SetMarkerStyle(20);
//       h_vn_pT_10to40_he3->SetMarkerStyle(20);
//       h_vn_pT_40to60_he3->SetMarkerStyle(20);
//       h_vn_pT_00to10_he3->SetMarkerColor(2);
//       h_vn_pT_10to40_he3->SetMarkerColor(4);
//       h_vn_pT_40to60_he3->SetMarkerColor(8);
//       h_vn_pT_00to10_he3->SetMarkerSize(2);
//       h_vn_pT_10to40_he3->SetMarkerSize(2);
//       h_vn_pT_40to60_he3->SetMarkerSize(2);
//       h_vn_pT_00to10_he3->SetLineColor(2);
//       h_vn_pT_10to40_he3->SetLineColor(4);
//       h_vn_pT_40to60_he3->SetLineColor(8);
//       h_vn_pT_00to10_he3->SetLineWidth(3);
//       h_vn_pT_10to40_he3->SetLineWidth(3);
//       h_vn_pT_40to60_he3->SetLineWidth(3);
//       h_vn_pT_00to10_he3_yMid->SetMarkerStyle(20);
//       h_vn_pT_10to40_he3_yMid->SetMarkerStyle(20);
//       h_vn_pT_40to60_he3_yMid->SetMarkerStyle(20);
//       h_vn_pT_00to10_he3_yMid->SetMarkerColor(2);
//       h_vn_pT_10to40_he3_yMid->SetMarkerColor(4);
//       h_vn_pT_40to60_he3_yMid->SetMarkerColor(8);
//       h_vn_pT_00to10_he3_yMid->SetMarkerSize(2);
//       h_vn_pT_10to40_he3_yMid->SetMarkerSize(2);
//       h_vn_pT_40to60_he3_yMid->SetMarkerSize(2);
//       h_vn_pT_00to10_he3_yMid->SetLineColor(2);
//       h_vn_pT_10to40_he3_yMid->SetLineColor(4);
//       h_vn_pT_40to60_he3_yMid->SetLineColor(8);
//       h_vn_pT_00to10_he3_yMid->SetLineWidth(3);
//       h_vn_pT_10to40_he3_yMid->SetLineWidth(3);
//       h_vn_pT_40to60_he3_yMid->SetLineWidth(3);
//       h_vn_pT_00to10_he3_yFor->SetMarkerStyle(20);
//       h_vn_pT_10to40_he3_yFor->SetMarkerStyle(20);
//       h_vn_pT_40to60_he3_yFor->SetMarkerStyle(20);
//       h_vn_pT_00to10_he3_yFor->SetMarkerColor(2);
//       h_vn_pT_10to40_he3_yFor->SetMarkerColor(4);
//       h_vn_pT_40to60_he3_yFor->SetMarkerColor(8);
//       h_vn_pT_00to10_he3_yFor->SetMarkerSize(2);
//       h_vn_pT_10to40_he3_yFor->SetMarkerSize(2);
//       h_vn_pT_40to60_he3_yFor->SetMarkerSize(2);
//       h_vn_pT_00to10_he3_yFor->SetLineColor(2);
//       h_vn_pT_10to40_he3_yFor->SetLineColor(4);
//       h_vn_pT_40to60_he3_yFor->SetLineColor(8);
//       h_vn_pT_00to10_he3_yFor->SetLineWidth(3);
//       h_vn_pT_10to40_he3_yFor->SetLineWidth(3);
//       h_vn_pT_40to60_he3_yFor->SetLineWidth(3);
//       h_vn_pT_00to10_he3_yExt->SetMarkerStyle(20);
//       h_vn_pT_10to40_he3_yExt->SetMarkerStyle(20);
//       h_vn_pT_40to60_he3_yExt->SetMarkerStyle(20);
//       h_vn_pT_00to10_he3_yExt->SetMarkerColor(2);
//       h_vn_pT_10to40_he3_yExt->SetMarkerColor(4);
//       h_vn_pT_40to60_he3_yExt->SetMarkerColor(8);
//       h_vn_pT_00to10_he3_yExt->SetMarkerSize(2);
//       h_vn_pT_10to40_he3_yExt->SetMarkerSize(2);
//       h_vn_pT_40to60_he3_yExt->SetMarkerSize(2);
//       h_vn_pT_00to10_he3_yExt->SetLineColor(2);
//       h_vn_pT_10to40_he3_yExt->SetLineColor(4);
//       h_vn_pT_40to60_he3_yExt->SetLineColor(8);
//       h_vn_pT_00to10_he3_yExt->SetLineWidth(3);
//       h_vn_pT_10to40_he3_yExt->SetLineWidth(3);
//       h_vn_pT_40to60_he3_yExt->SetLineWidth(3);
//       h_vn_pT_00to10_he3_yEnd->SetMarkerStyle(20);
//       h_vn_pT_10to40_he3_yEnd->SetMarkerStyle(20);
//       h_vn_pT_40to60_he3_yEnd->SetMarkerStyle(20);
//       h_vn_pT_00to10_he3_yEnd->SetMarkerColor(2);
//       h_vn_pT_10to40_he3_yEnd->SetMarkerColor(4);
//       h_vn_pT_40to60_he3_yEnd->SetMarkerColor(8);
//       h_vn_pT_00to10_he3_yEnd->SetMarkerSize(2);
//       h_vn_pT_10to40_he3_yEnd->SetMarkerSize(2);
//       h_vn_pT_40to60_he3_yEnd->SetMarkerSize(2);
//       h_vn_pT_00to10_he3_yEnd->SetLineColor(2);
//       h_vn_pT_10to40_he3_yEnd->SetLineColor(4);
//       h_vn_pT_40to60_he3_yEnd->SetLineColor(8);
//       h_vn_pT_00to10_he3_yEnd->SetLineWidth(3);
//       h_vn_pT_10to40_he3_yEnd->SetLineWidth(3);
//       h_vn_pT_40to60_he3_yEnd->SetLineWidth(3);

//       h_vn_pT_00to10_he4->SetMarkerStyle(20);
//       h_vn_pT_10to40_he4->SetMarkerStyle(20);
//       h_vn_pT_40to60_he4->SetMarkerStyle(20);
//       h_vn_pT_00to10_he4->SetMarkerColor(2);
//       h_vn_pT_10to40_he4->SetMarkerColor(4);
//       h_vn_pT_40to60_he4->SetMarkerColor(8);
//       h_vn_pT_00to10_he4->SetMarkerSize(2);
//       h_vn_pT_10to40_he4->SetMarkerSize(2);
//       h_vn_pT_40to60_he4->SetMarkerSize(2);
//       h_vn_pT_00to10_he4->SetLineColor(2);
//       h_vn_pT_10to40_he4->SetLineColor(4);
//       h_vn_pT_40to60_he4->SetLineColor(8);
//       h_vn_pT_00to10_he4->SetLineWidth(3);
//       h_vn_pT_10to40_he4->SetLineWidth(3);
//       h_vn_pT_40to60_he4->SetLineWidth(3);
//       h_vn_pT_00to10_he4_yMid->SetMarkerStyle(20);
//       h_vn_pT_10to40_he4_yMid->SetMarkerStyle(20);
//       h_vn_pT_40to60_he4_yMid->SetMarkerStyle(20);
//       h_vn_pT_00to10_he4_yMid->SetMarkerColor(2);
//       h_vn_pT_10to40_he4_yMid->SetMarkerColor(4);
//       h_vn_pT_40to60_he4_yMid->SetMarkerColor(8);
//       h_vn_pT_00to10_he4_yMid->SetMarkerSize(2);
//       h_vn_pT_10to40_he4_yMid->SetMarkerSize(2);
//       h_vn_pT_40to60_he4_yMid->SetMarkerSize(2);
//       h_vn_pT_00to10_he4_yMid->SetLineColor(2);
//       h_vn_pT_10to40_he4_yMid->SetLineColor(4);
//       h_vn_pT_40to60_he4_yMid->SetLineColor(8);
//       h_vn_pT_00to10_he4_yMid->SetLineWidth(3);
//       h_vn_pT_10to40_he4_yMid->SetLineWidth(3);
//       h_vn_pT_40to60_he4_yMid->SetLineWidth(3);
//       h_vn_pT_00to10_he4_yFor->SetMarkerStyle(20);
//       h_vn_pT_10to40_he4_yFor->SetMarkerStyle(20);
//       h_vn_pT_40to60_he4_yFor->SetMarkerStyle(20);
//       h_vn_pT_00to10_he4_yFor->SetMarkerColor(2);
//       h_vn_pT_10to40_he4_yFor->SetMarkerColor(4);
//       h_vn_pT_40to60_he4_yFor->SetMarkerColor(8);
//       h_vn_pT_00to10_he4_yFor->SetMarkerSize(2);
//       h_vn_pT_10to40_he4_yFor->SetMarkerSize(2);
//       h_vn_pT_40to60_he4_yFor->SetMarkerSize(2);
//       h_vn_pT_00to10_he4_yFor->SetLineColor(2);
//       h_vn_pT_10to40_he4_yFor->SetLineColor(4);
//       h_vn_pT_40to60_he4_yFor->SetLineColor(8);
//       h_vn_pT_00to10_he4_yFor->SetLineWidth(3);
//       h_vn_pT_10to40_he4_yFor->SetLineWidth(3);
//       h_vn_pT_40to60_he4_yFor->SetLineWidth(3);
//       h_vn_pT_00to10_he4_yExt->SetMarkerStyle(20);
//       h_vn_pT_10to40_he4_yExt->SetMarkerStyle(20);
//       h_vn_pT_40to60_he4_yExt->SetMarkerStyle(20);
//       h_vn_pT_00to10_he4_yExt->SetMarkerColor(2);
//       h_vn_pT_10to40_he4_yExt->SetMarkerColor(4);
//       h_vn_pT_40to60_he4_yExt->SetMarkerColor(8);
//       h_vn_pT_00to10_he4_yExt->SetMarkerSize(2);
//       h_vn_pT_10to40_he4_yExt->SetMarkerSize(2);
//       h_vn_pT_40to60_he4_yExt->SetMarkerSize(2);
//       h_vn_pT_00to10_he4_yExt->SetLineColor(2);
//       h_vn_pT_10to40_he4_yExt->SetLineColor(4);
//       h_vn_pT_40to60_he4_yExt->SetLineColor(8);
//       h_vn_pT_00to10_he4_yExt->SetLineWidth(3);
//       h_vn_pT_10to40_he4_yExt->SetLineWidth(3);
//       h_vn_pT_40to60_he4_yExt->SetLineWidth(3);
//       h_vn_pT_00to10_he4_yEnd->SetMarkerStyle(20);
//       h_vn_pT_10to40_he4_yEnd->SetMarkerStyle(20);
//       h_vn_pT_40to60_he4_yEnd->SetMarkerStyle(20);
//       h_vn_pT_00to10_he4_yEnd->SetMarkerColor(2);
//       h_vn_pT_10to40_he4_yEnd->SetMarkerColor(4);
//       h_vn_pT_40to60_he4_yEnd->SetMarkerColor(8);
//       h_vn_pT_00to10_he4_yEnd->SetMarkerSize(2);
//       h_vn_pT_10to40_he4_yEnd->SetMarkerSize(2);
//       h_vn_pT_40to60_he4_yEnd->SetMarkerSize(2);
//       h_vn_pT_00to10_he4_yEnd->SetLineColor(2);
//       h_vn_pT_10to40_he4_yEnd->SetLineColor(4);
//       h_vn_pT_40to60_he4_yEnd->SetLineColor(8);
//       h_vn_pT_00to10_he4_yEnd->SetLineWidth(3);
//       h_vn_pT_10to40_he4_yEnd->SetLineWidth(3);
//       h_vn_pT_40to60_he4_yEnd->SetLineWidth(3);

    }
}// End fixAttributes()
