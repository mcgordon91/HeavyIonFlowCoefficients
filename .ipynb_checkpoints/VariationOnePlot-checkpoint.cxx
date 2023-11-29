#include <iostream>
#include "TProfile.h"
#include "TProfile2D.h"
#include "TMath.h"
#include "Variation.h"
#include "PlotUtils.h"

using namespace std;
using namespace PlotUtils;

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
  delete h_vn_yCM_10to40_pr;

  file->Close();
}

// Initialize all histograms
void Variation::initialize(TString order_n_str)
{
//   TProfile *p_vn_pr = (TProfile*)file->Get("DataV3VsPtForProtonsCentrality10-40");

//   h_vn_pr = p_vn_pr->ProjectionX((TString)p_vn_pr->GetName() +"_"+ ID);
  
//   h_vn_pr = flipHisto(h_vn_pr);
  
//   h_vn_pr = trimCentralityPlot(h_vn_pr);
  
  //=== vn vs rapidity stuff
  //TProfile2D *p2_vn_yCM_cent_pr = (TProfile2D*)file->Get("DataV3VsYForProtonsCentrality10-40");

  TProfile *p_vn_yCM_10to40_pr = (TProfile*)file->Get("DataV3VsYForProtonsCentrality10-40");

  h_vn_yCM_10to40_pr = new TH1D("h_vn_yCM_10to40_pr", ";y-y_{mid};v_{"+order_n_str+"}", 10, 0, 1);

  
  // Convert profiles to histograms
  h_vn_yCM_10to40_pr = p_vn_yCM_10to40_pr->ProjectionX();
}


// Use this with the "Normal" Variation to clean up the plots
void Variation::fixAttributes(TString order_n_str)
{
  if (order_n_str == "3")
    {
      Double_t centralityUpperBounds = 0.15;
      Double_t centralityLowerBounds = -0.15;

      //=== vn vs rapidity
      h_vn_yCM_10to40_pr->SetMarkerStyle(20);
      h_vn_yCM_10to40_pr->SetMarkerColor(4);
      h_vn_yCM_10to40_pr->SetMarkerSize(2);
      h_vn_yCM_10to40_pr->SetLineColor(4);
      h_vn_yCM_10to40_pr->SetLineWidth(3);
    }
}// End fixAttributes()
