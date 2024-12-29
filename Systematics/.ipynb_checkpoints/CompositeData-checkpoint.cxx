#include <iostream>
#include "TMath.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "PlotUtils.h"
#include "CompositeData.h"
using namespace std;

// Constructor for one variation.
CompositeData::CompositeData(TString prefix, Variation* normalData, Variation* var1Data)
{
  onlyOneVariation = true;
  nVariations = 1;
  ID = prefix;
  initialize();
  combine(normalData, var1Data);
  saveDetails(normalData);
}


// Constructor for two related variations.
CompositeData::CompositeData(TString prefix, Variation* normalData, Variation* var1Data, Variation* var2Data)
{
  onlyOneVariation = false;
  nVariations = 2;
  ID = prefix;
  initialize();
  combine(normalData, var1Data, var2Data);
  saveDetails(normalData);
}

// Constructor for three related variations.
CompositeData::CompositeData(TString prefix, Variation* normalData, Variation* var1Data, Variation* var2Data, Variation* var3Data)
{
  onlyOneVariation = false;
  nVariations = 3;
  ID = prefix;
  initialize();
  combine(normalData, var1Data, var2Data, var3Data);
  saveDetails(normalData);
}

// Constructor for four related variations.
CompositeData::CompositeData(TString prefix, Variation* normalData, Variation* var1Data, Variation* var2Data, Variation* var3Data, Variation* var4Data)
{
  onlyOneVariation = false;
  nVariations = 4;
  ID = prefix;
  initialize();
  combine(normalData, var1Data, var2Data, var3Data, var4Data);
  saveDetails(normalData);
}


CompositeData::~CompositeData()
{
//   delete barlow_vn_pp;
//   delete barlow_vn_pm;
//   delete barlow_vn_kp;
//   delete barlow_vn_km;
//   delete barlow_vn_pr;
//   delete barlow_vn_de;
//   delete barlow_vn_tr;
//   delete barlow_vn_he3;
//   delete barlow_vn_he4;
  
//   delete barlow_vn_yCM_00to10_pr;
  delete barlow_vn_yCM_10to40_pr;
//   delete barlow_vn_yCM_40to60_pr;
//   delete barlow_vn_yCM_00to10_kp;
  delete barlow_vn_yCM_10to40_kp;
//   delete barlow_vn_yCM_40to60_kp;
//   delete barlow_vn_yCM_00to10_km;
  delete barlow_vn_yCM_10to40_km;
//   delete barlow_vn_yCM_40to60_km;
//   delete barlow_vn_yCM_00to10_pp;
  delete barlow_vn_yCM_10to40_pp;
//   delete barlow_vn_yCM_40to60_pp;
//   delete barlow_vn_yCM_00to10_pm;
  delete barlow_vn_yCM_10to40_pm;
//   delete barlow_vn_yCM_40to60_pm;
    
//   delete barlow_vn_yCM_00to10_pr_symm;
//   delete barlow_vn_yCM_10to40_pr_symm;
//   delete barlow_vn_yCM_40to60_pr_symm;

//   delete barlow_vn_yCM_00to10_de;
  delete barlow_vn_yCM_10to40_de;
//   delete barlow_vn_yCM_40to60_de;
//   delete barlow_vn_yCM_00to10_tr;
  delete barlow_vn_yCM_10to40_tr;
//   delete barlow_vn_yCM_40to60_tr;
//   delete barlow_vn_yCM_00to10_he3;
//   delete barlow_vn_yCM_10to40_he3;
//   delete barlow_vn_yCM_40to60_he3;
//   delete barlow_vn_yCM_00to10_he4;
//   delete barlow_vn_yCM_10to40_he4;
//   delete barlow_vn_yCM_40to60_he4;

//   delete barlow_vn_pT_00to10_pr;
//   delete barlow_vn_pT_10to40_pr;
//   delete barlow_vn_pT_40to60_pr;
//   delete barlow_vn_pT_00to10_pr_yMid;
//   delete barlow_vn_pT_10to40_pr_yMid;
//   delete barlow_vn_pT_40to60_pr_yMid;
//   delete barlow_vn_pT_00to10_pr_yFor;
//   delete barlow_vn_pT_10to40_pr_yFor;
//   delete barlow_vn_pT_40to60_pr_yFor;
//   delete barlow_vn_pT_00to10_pr_yExt;
//   delete barlow_vn_pT_10to40_pr_yExt;
//   delete barlow_vn_pT_40to60_pr_yExt;
//   delete barlow_vn_pT_00to10_pr_yEnd;
//   delete barlow_vn_pT_10to40_pr_yEnd;
//   delete barlow_vn_pT_40to60_pr_yEnd;

//   delete barlow_vn_pT_00to10_de;
//   delete barlow_vn_pT_10to40_de;
//   delete barlow_vn_pT_40to60_de;
//   delete barlow_vn_pT_00to10_de_yMid;
//   delete barlow_vn_pT_10to40_de_yMid;
//   delete barlow_vn_pT_40to60_de_yMid;
//   delete barlow_vn_pT_00to10_de_yFor;
//   delete barlow_vn_pT_10to40_de_yFor;
//   delete barlow_vn_pT_40to60_de_yFor;
//   delete barlow_vn_pT_00to10_de_yExt;
//   delete barlow_vn_pT_10to40_de_yExt;
//   delete barlow_vn_pT_40to60_de_yExt;
//   delete barlow_vn_pT_00to10_de_yEnd;
//   delete barlow_vn_pT_10to40_de_yEnd;
//   delete barlow_vn_pT_40to60_de_yEnd;

//   delete barlow_vn_pT_00to10_tr;
//   delete barlow_vn_pT_10to40_tr;
//   delete barlow_vn_pT_40to60_tr;
//   delete barlow_vn_pT_00to10_tr_yMid;
//   delete barlow_vn_pT_10to40_tr_yMid;
//   delete barlow_vn_pT_40to60_tr_yMid;
//   delete barlow_vn_pT_00to10_tr_yFor;
//   delete barlow_vn_pT_10to40_tr_yFor;
//   delete barlow_vn_pT_40to60_tr_yFor;
//   delete barlow_vn_pT_00to10_tr_yExt;
//   delete barlow_vn_pT_10to40_tr_yExt;
//   delete barlow_vn_pT_40to60_tr_yExt;
//   delete barlow_vn_pT_00to10_tr_yEnd;
//   delete barlow_vn_pT_10to40_tr_yEnd;
//   delete barlow_vn_pT_40to60_tr_yEnd;

//   delete barlow_vn_pT_00to10_he3;
//   delete barlow_vn_pT_10to40_he3;
//   delete barlow_vn_pT_40to60_he3;
//   delete barlow_vn_pT_00to10_he3_yMid;
//   delete barlow_vn_pT_10to40_he3_yMid;
//   delete barlow_vn_pT_40to60_he3_yMid;
//   delete barlow_vn_pT_00to10_he3_yFor;
//   delete barlow_vn_pT_10to40_he3_yFor;
//   delete barlow_vn_pT_40to60_he3_yFor;
//   delete barlow_vn_pT_00to10_he3_yExt;
//   delete barlow_vn_pT_10to40_he3_yExt;
//   delete barlow_vn_pT_40to60_he3_yExt;
//   delete barlow_vn_pT_00to10_he3_yEnd;
//   delete barlow_vn_pT_10to40_he3_yEnd;
//   delete barlow_vn_pT_40to60_he3_yEnd;

//   delete barlow_vn_pT_00to10_he4;
//   delete barlow_vn_pT_10to40_he4;
//   delete barlow_vn_pT_40to60_he4;
//   delete barlow_vn_pT_00to10_he4_yMid;
//   delete barlow_vn_pT_10to40_he4_yMid;
//   delete barlow_vn_pT_40to60_he4_yMid;
//   delete barlow_vn_pT_00to10_he4_yFor;
//   delete barlow_vn_pT_10to40_he4_yFor;
//   delete barlow_vn_pT_40to60_he4_yFor;
//   delete barlow_vn_pT_00to10_he4_yExt;
//   delete barlow_vn_pT_10to40_he4_yExt;
//   delete barlow_vn_pT_40to60_he4_yExt;
//   delete barlow_vn_pT_00to10_he4_yEnd;
//   delete barlow_vn_pT_10to40_he4_yEnd;
//   delete barlow_vn_pT_40to60_he4_yEnd;

}


void CompositeData::initialize()
{
  // Centrality
//   barlow_vn_pp = new TH1D("barlow_vn_pp_"+ID, "pp vs cent;Centrality;#Delta/#sigma_{#Delta}", 12, 0, 12);
//   barlow_vn_pm = new TH1D("barlow_vn_pm_"+ID, "pm vs cent;Centrality;#Delta/#sigma_{#Delta}", 12, 0, 12);
//   barlow_vn_kp = new TH1D("barlow_vn_kp_"+ID, "kp vs cent;Centrality;#Delta/#sigma_{#Delta}", 6, 0, 6);
//   barlow_vn_km = new TH1D("barlow_vn_km_"+ID, "km vs cent;Centrality;#Delta/#sigma_{#Delta}", 6, 0, 6);
//   barlow_vn_pr = new TH1D("barlow_vn_pr_"+ID, "pr vs cent;Centrality;#Delta/#sigma_{#Delta}", 12, 0, 12);
//   barlow_vn_de = new TH1D("barlow_vn_de_"+ID, "de vs cent;Centrality;#Delta/#sigma_{#Delta}", 12, 0, 12);
//   barlow_vn_tr = new TH1D("barlow_vn_tr_"+ID, "tr vs cent;Centrality;#Delta/#sigma_{#Delta}", 12, 0, 12);
    
//   barlow_vn_he3 = new TH1D("barlow_vn_he3_"+ID, "pr vs cent;Centrality;#Delta/#sigma_{#Delta}", 12, 0, 60);
//   barlow_vn_he4 = new TH1D("barlow_vn_he4_"+ID, "pr vs cent;Centrality;#Delta/#sigma_{#Delta}", 12, 0, 60);

  // Proton, Kaon, Pion y
//   barlow_vn_yCM_00to10_pr = new TH1D("barlow_vn_yCM_00to10_pr_"+ID, "0-10% pr vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
  barlow_vn_yCM_10to40_pr = new TH1D("barlow_vn_yCM_10to40_pr_"+ID, "10-40% pr vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
//   barlow_vn_yCM_40to60_pr = new TH1D("barlow_vn_yCM_40to60_pr_"+ID, "40-60% pr vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
 
//   barlow_vn_yCM_00to10_kp = new TH1D("barlow_vn_yCM_00to10_kp_"+ID, "0-10% kp vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
  barlow_vn_yCM_10to40_kp = new TH1D("barlow_vn_yCM_10to40_kp_"+ID, "10-40% kp vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
//   barlow_vn_yCM_40to60_kp = new TH1D("barlow_vn_yCM_40to60_kp_"+ID, "40-60% kp vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);

//   barlow_vn_yCM_00to10_km = new TH1D("barlow_vn_yCM_00to10_km_"+ID, "0-10% km vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
  barlow_vn_yCM_10to40_km = new TH1D("barlow_vn_yCM_10to40_km_"+ID, "10-40% km vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 5, 0, 1);
//   barlow_vn_yCM_40to60_km = new TH1D("barlow_vn_yCM_40to60_km_"+ID, "40-60% km vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
    
//   barlow_vn_yCM_00to10_pp = new TH1D("barlow_vn_yCM_00to10_pp_"+ID, "0-10% pp vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
  barlow_vn_yCM_10to40_pp = new TH1D("barlow_vn_yCM_10to40_pp_"+ID, "10-40% pp vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
//   barlow_vn_yCM_40to60_pp = new TH1D("barlow_vn_yCM_40to60_pp_"+ID, "40-60% pp vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
    
//   barlow_vn_yCM_00to10_pm = new TH1D("barlow_vn_yCM_00to10_pm_"+ID, "0-10% pm vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
  barlow_vn_yCM_10to40_pm = new TH1D("barlow_vn_yCM_10to40_pm_"+ID, "10-40% pm vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
//   barlow_vn_yCM_40to60_pm = new TH1D("barlow_vn_yCM_40to60_pm_"+ID, "40-60% pm vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);

  // Proton y symmetric
//   barlow_vn_yCM_00to10_pr_symm = new TH1D("barlow_vn_yCM_00to10_pr_symm_"+ID, "0-10% pr vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, -0.5, 0.5);
//   barlow_vn_yCM_10to40_pr_symm = new TH1D("barlow_vn_yCM_10to40_pr_symm_"+ID, "10-40% pr vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, -0.5, 0.5);
//   barlow_vn_yCM_40to60_pr_symm = new TH1D("barlow_vn_yCM_40to60_pr_symm_"+ID, "40-60% pr vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, -0.5, 0.5);
  
  // Deuteron, Triton, Helium-3, Helium-4 y
//   barlow_vn_yCM_00to10_de = new TH1D("barlow_vn_yCM_00to10_de_"+ID, "0-10% de vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
  barlow_vn_yCM_10to40_de = new TH1D("barlow_vn_yCM_10to40_de_"+ID, "10-40% de vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
//   barlow_vn_yCM_40to60_de = new TH1D("barlow_vn_yCM_40to60_de_"+ID, "40-60% de vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
    
//   barlow_vn_yCM_00to10_tr = new TH1D("barlow_vn_yCM_00to10_tr_"+ID, "0-10% de vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
  barlow_vn_yCM_10to40_tr = new TH1D("barlow_vn_yCM_10to40_tr_"+ID, "10-40% de vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);
//   barlow_vn_yCM_40to60_tr = new TH1D("barlow_vn_yCM_40to60_tr_"+ID, "40-60% de vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 10, 0, 1);

//   barlow_vn_yCM_00to10_he3 = new TH1D("barlow_vn_yCM_00to10_he3_"+ID, "0-10% de vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 20, -1, 1);
//   barlow_vn_yCM_10to40_he3 = new TH1D("barlow_vn_yCM_10to40_he3_"+ID, "10-40% de vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 20, -1, 1);
//   barlow_vn_yCM_40to60_he3 = new TH1D("barlow_vn_yCM_40to60_he3_"+ID, "40-60% de vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 20, -1, 1);
//   barlow_vn_yCM_00to10_he4 = new TH1D("barlow_vn_yCM_00to10_he4_"+ID, "0-10% de vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 20, -1, 1);
//   barlow_vn_yCM_10to40_he4 = new TH1D("barlow_vn_yCM_10to40_he4_"+ID, "10-40% de vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 20, -1, 1);
//   barlow_vn_yCM_40to60_he4 = new TH1D("barlow_vn_yCM_40to60_he4_"+ID, "40-60% de vs yCM;y-y_{mid};#Delta/#sigma_{#Delta}", 20, -1, 1);

  // Proton pT
//   barlow_vn_pT_00to10_pr = new TH1D("barlow_vn_pT_00to10_pr_"+ID, "0-10% pr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_pr = new TH1D("barlow_vn_pT_10to40_pr_"+ID, "10-40% pr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_pr = new TH1D("barlow_vn_pT_40to60_pr_"+ID, "40-60% pr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_pr_yMid = new TH1D("barlow_vn_pT_00to10_pr_yMid_"+ID, "0-10% pr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_pr_yMid = new TH1D("barlow_vn_pT_10to40_pr_yMid_"+ID, "10-40% pr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_pr_yMid = new TH1D("barlow_vn_pT_40to60_pr_yMid_"+ID, "40-60% pr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_pr_yFor = new TH1D("barlow_vn_pT_00to10_pr_yFor_"+ID, "0-10% pr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_pr_yFor = new TH1D("barlow_vn_pT_10to40_pr_yFor_"+ID, "10-40% pr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_pr_yFor = new TH1D("barlow_vn_pT_40to60_pr_yFor_"+ID, "40-60% pr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_pr_yExt = new TH1D("barlow_vn_pT_00to10_pr_yExt_"+ID, "0-10% pr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_pr_yExt = new TH1D("barlow_vn_pT_10to40_pr_yExt_"+ID, "10-40% pr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_pr_yExt = new TH1D("barlow_vn_pT_40to60_pr_yExt_"+ID, "40-60% pr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_pr_yEnd = new TH1D("barlow_vn_pT_00to10_pr_yEnd_"+ID, "0-10% pr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_pr_yEnd = new TH1D("barlow_vn_pT_10to40_pr_yEnd_"+ID, "10-40% pr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_pr_yEnd = new TH1D("barlow_vn_pT_40to60_pr_yEnd_"+ID, "40-60% pr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);

  // Deuteron pT
//   barlow_vn_pT_00to10_de = new TH1D("barlow_vn_pT_00to10_de_"+ID, "0-10% de vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_de = new TH1D("barlow_vn_pT_10to40_de_"+ID, "10-40% de vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_de = new TH1D("barlow_vn_pT_40to60_de_"+ID, "40-60% de vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_de_yMid = new TH1D("barlow_vn_pT_00to10_de_yMid_"+ID, "0-10% de vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_de_yMid = new TH1D("barlow_vn_pT_10to40_de_yMid_"+ID, "10-40% de vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_de_yMid = new TH1D("barlow_vn_pT_40to60_de_yMid_"+ID, "40-60% de vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_de_yFor = new TH1D("barlow_vn_pT_00to10_de_yFor_"+ID, "0-10% de vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_de_yFor = new TH1D("barlow_vn_pT_10to40_de_yFor_"+ID, "10-40% de vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_de_yFor = new TH1D("barlow_vn_pT_40to60_de_yFor_"+ID, "40-60% de vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_de_yExt = new TH1D("barlow_vn_pT_00to10_de_yExt_"+ID, "0-10% de vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_de_yExt = new TH1D("barlow_vn_pT_10to40_de_yExt_"+ID, "10-40% de vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_de_yExt = new TH1D("barlow_vn_pT_40to60_de_yExt_"+ID, "40-60% de vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_de_yEnd = new TH1D("barlow_vn_pT_00to10_de_yEnd_"+ID, "0-10% de vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_de_yEnd = new TH1D("barlow_vn_pT_10to40_de_yEnd_"+ID, "10-40% de vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_de_yEnd = new TH1D("barlow_vn_pT_40to60_de_yEnd_"+ID, "40-60% de vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);

  // Triton pT
//   barlow_vn_pT_00to10_tr      = new TH1D("barlow_vn_pT_00to10_tr_"+ID, "0-10% tr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_tr      = new TH1D("barlow_vn_pT_10to40_tr_"+ID, "10-40% tr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_tr      = new TH1D("barlow_vn_pT_40to60_tr_"+ID, "40-60% tr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_tr_yMid = new TH1D("barlow_vn_pT_00to10_tr_yMid_"+ID, "0-10% tr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_tr_yMid = new TH1D("barlow_vn_pT_10to40_tr_yMid_"+ID, "10-40% tr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_tr_yMid = new TH1D("barlow_vn_pT_40to60_tr_yMid_"+ID, "40-60% tr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_tr_yFor = new TH1D("barlow_vn_pT_00to10_tr_yFor_"+ID, "0-10% tr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_tr_yFor = new TH1D("barlow_vn_pT_10to40_tr_yFor_"+ID, "10-40% tr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_tr_yFor = new TH1D("barlow_vn_pT_40to60_tr_yFor_"+ID, "40-60% tr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_tr_yExt = new TH1D("barlow_vn_pT_00to10_tr_yExt_"+ID, "0-10% tr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_tr_yExt = new TH1D("barlow_vn_pT_10to40_tr_yExt_"+ID, "10-40% tr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_tr_yExt = new TH1D("barlow_vn_pT_40to60_tr_yExt_"+ID, "40-60% tr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_tr_yEnd = new TH1D("barlow_vn_pT_00to10_tr_yEnd_"+ID, "0-10% tr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_tr_yEnd = new TH1D("barlow_vn_pT_10to40_tr_yEnd_"+ID, "10-40% tr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_tr_yEnd = new TH1D("barlow_vn_pT_40to60_tr_yEnd_"+ID, "40-60% tr vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);


  // Helium-3 pT
//   barlow_vn_pT_00to10_he3      = new TH1D("barlow_vn_pT_00to10_he3_"+ID, "0-10% he3 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_he3      = new TH1D("barlow_vn_pT_10to40_he3_"+ID, "10-40% he3 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_he3      = new TH1D("barlow_vn_pT_40to60_he3_"+ID, "40-60% he3 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_he3_yMid = new TH1D("barlow_vn_pT_00to10_he3_yMid_"+ID, "0-10% he3 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_he3_yMid = new TH1D("barlow_vn_pT_10to40_he3_yMid_"+ID, "10-40% he3 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_he3_yMid = new TH1D("barlow_vn_pT_40to60_he3_yMid_"+ID, "40-60% he3 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_he3_yFor = new TH1D("barlow_vn_pT_00to10_he3_yFor_"+ID, "0-10% he3 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_he3_yFor = new TH1D("barlow_vn_pT_10to40_he3_yFor_"+ID, "10-40% he3 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_he3_yFor = new TH1D("barlow_vn_pT_40to60_he3_yFor_"+ID, "40-60% he3 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_he3_yExt = new TH1D("barlow_vn_pT_00to10_he3_yExt_"+ID, "0-10% he3 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_he3_yExt = new TH1D("barlow_vn_pT_10to40_he3_yExt_"+ID, "10-40% he3 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_he3_yExt = new TH1D("barlow_vn_pT_40to60_he3_yExt_"+ID, "40-60% he3 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_he3_yEnd = new TH1D("barlow_vn_pT_00to10_he3_yEnd_"+ID, "0-10% he3 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_he3_yEnd = new TH1D("barlow_vn_pT_10to40_he3_yEnd_"+ID, "10-40% he3 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_he3_yEnd = new TH1D("barlow_vn_pT_40to60_he3_yEnd_"+ID, "40-60% he3 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);

  // Helium-4 pT
//   barlow_vn_pT_00to10_he4      = new TH1D("barlow_vn_pT_00to10_he4_"+ID, "0-10% he4 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_he4      = new TH1D("barlow_vn_pT_10to40_he4_"+ID, "10-40% he4 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_he4      = new TH1D("barlow_vn_pT_40to60_he4_"+ID, "40-60% he4 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_he4_yMid = new TH1D("barlow_vn_pT_00to10_he4_yMid_"+ID, "0-10% he4 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_he4_yMid = new TH1D("barlow_vn_pT_10to40_he4_yMid_"+ID, "10-40% he4 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_he4_yMid = new TH1D("barlow_vn_pT_40to60_he4_yMid_"+ID, "40-60% he4 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_he4_yFor = new TH1D("barlow_vn_pT_00to10_he4_yFor_"+ID, "0-10% he4 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_he4_yFor = new TH1D("barlow_vn_pT_10to40_he4_yFor_"+ID, "10-40% he4 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_he4_yFor = new TH1D("barlow_vn_pT_40to60_he4_yFor_"+ID, "40-60% he4 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_he4_yExt = new TH1D("barlow_vn_pT_00to10_he4_yExt_"+ID, "0-10% he4 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_he4_yExt = new TH1D("barlow_vn_pT_10to40_he4_yExt_"+ID, "10-40% he4 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_he4_yExt = new TH1D("barlow_vn_pT_40to60_he4_yExt_"+ID, "40-60% he4 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_00to10_he4_yEnd = new TH1D("barlow_vn_pT_00to10_he4_yEnd_"+ID, "0-10% he4 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_10to40_he4_yEnd = new TH1D("barlow_vn_pT_10to40_he4_yEnd_"+ID, "10-40% he4 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);
//   barlow_vn_pT_40to60_he4_yEnd = new TH1D("barlow_vn_pT_40to60_he4_yEnd_"+ID, "40-60% he4 vs p_{T};p_{T} (GeV);#Delta/#sigma_{#Delta}", 10, 0, 2);

}


// Save normal and varied flow values for each point to the file supplied.
void CompositeData::addRawValuesToFile(TFile* file, TString histogramName, std::vector<DataPoint> vectorOfPoints)
{
  TH1D* temp;
  TString nameWithBinNo;
  file->cd();

  for (int i = 0; i < vectorOfPoints.size(); i++)
  {
    nameWithBinNo.Form(histogramName+"_bin%d", i+1);
    temp = new TH1D(nameWithBinNo, nameWithBinNo, 500, 1, 1);

    temp->Fill(vectorOfPoints.at(i).normalValue);
    temp->Fill(vectorOfPoints.at(i).var1Value);

    if (nVariations > 1) // at least 2 variations
    {
      temp->Fill(vectorOfPoints.at(i).var2Value);

      if (nVariations > 2) // at least 3 variations
      {
        temp->Fill(vectorOfPoints.at(i).var3Value);

        if (nVariations > 3) // 4 variations
        {
          temp->Fill(vectorOfPoints.at(i).var4Value);
        }
      }
    }
    
    temp->Write();
    delete temp;
  }
}


void CompositeData::addBarlowValuesToFile(TFile* file, TH1D* barlowHistogram, std::vector<DataPoint> vectorOfPoints)
{
  for (int i = 1; i <= vectorOfPoints.size(); i++)
    {barlowHistogram->SetBinContent(i, vectorOfPoints.at(i-1).deltaByDeltaError); }

  file->cd();
  barlowHistogram->Write();
}


// Save each flow value along with the same value from one variation to see the effect on every point.
//Also save the values used for the Barlow check.
//Normal Variation is only used to get names of histograms.
void CompositeData::saveDetails(Variation* normalData)
{
  TFile *detailsFile = new TFile("Details_"+ID+".root", "RECREATE");

  // Save the flow values 
//   addRawValuesToFile(detailsFile, normalData->h_vn_pp->GetName(), v_vn_pp);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pm->GetName(), v_vn_pm);
//   addRawValuesToFile(detailsFile, normalData->h_vn_kp->GetName(), v_vn_kp);
//   addRawValuesToFile(detailsFile, normalData->h_vn_km->GetName(), v_vn_km);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pr->GetName(), v_vn_pr);
//   addRawValuesToFile(detailsFile, normalData->h_vn_de->GetName(), v_vn_de);
//   addRawValuesToFile(detailsFile, normalData->h_vn_tr->GetName(), v_vn_tr);
//   addRawValuesToFile(detailsFile, normalData->h_vn_he3->GetName(), v_vn_he3);
//   addRawValuesToFile(detailsFile, normalData->h_vn_he4->GetName(), v_vn_he4);
  
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_00to10_pr->GetName(), v_vn_yCM_00to10_pr);
  addRawValuesToFile(detailsFile, normalData->h_vn_yCM_10to40_pr->GetName(), v_vn_yCM_10to40_pr);
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_40to60_pr->GetName(), v_vn_yCM_40to60_pr);

//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_00to10_kp->GetName(), v_vn_yCM_00to10_kp);
  addRawValuesToFile(detailsFile, normalData->h_vn_yCM_10to40_kp->GetName(), v_vn_yCM_10to40_kp);
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_40to60_kp->GetName(), v_vn_yCM_40to60_kp);
    
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_00to10_km->GetName(), v_vn_yCM_00to10_km);
  addRawValuesToFile(detailsFile, normalData->h_vn_yCM_10to40_km->GetName(), v_vn_yCM_10to40_km);
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_40to60_km->GetName(), v_vn_yCM_40to60_km);
    
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_00to10_pp->GetName(), v_vn_yCM_00to10_pp);
  addRawValuesToFile(detailsFile, normalData->h_vn_yCM_10to40_pp->GetName(), v_vn_yCM_10to40_pp);
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_40to60_pp->GetName(), v_vn_yCM_40to60_pp);
    
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_00to10_pm->GetName(), v_vn_yCM_00to10_pm);
  addRawValuesToFile(detailsFile, normalData->h_vn_yCM_10to40_pm->GetName(), v_vn_yCM_10to40_pm);
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_40to60_pm->GetName(), v_vn_yCM_40to60_pm);

//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_00to10_pr_symm->GetName(), v_vn_yCM_00to10_pr_symm);
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_10to40_pr_symm->GetName(), v_vn_yCM_10to40_pr_symm);
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_40to60_pr_symm->GetName(), v_vn_yCM_40to60_pr_symm);

//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_00to10_de->GetName(), v_vn_yCM_00to10_de);
  addRawValuesToFile(detailsFile, normalData->h_vn_yCM_10to40_de->GetName(), v_vn_yCM_10to40_de);
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_40to60_de->GetName(), v_vn_yCM_40to60_de);
    
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_00to10_tr->GetName(), v_vn_yCM_00to10_tr);
  addRawValuesToFile(detailsFile, normalData->h_vn_yCM_10to40_tr->GetName(), v_vn_yCM_10to40_tr);
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_40to60_tr->GetName(), v_vn_yCM_40to60_tr);

//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_00to10_he3->GetName(), v_vn_yCM_00to10_he3);
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_10to40_he3->GetName(), v_vn_yCM_10to40_he3);
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_40to60_he3->GetName(), v_vn_yCM_40to60_he3);
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_00to10_he4->GetName(), v_vn_yCM_00to10_he4);
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_10to40_he4->GetName(), v_vn_yCM_10to40_he4);
//   addRawValuesToFile(detailsFile, normalData->h_vn_yCM_40to60_he4->GetName(), v_vn_yCM_40to60_he4);

//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_pr->GetName(), v_vn_pT_00to10_pr);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_pr->GetName(), v_vn_pT_10to40_pr);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_pr->GetName(), v_vn_pT_40to60_pr);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_pr_yMid->GetName(), v_vn_pT_00to10_pr_yMid);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_pr_yMid->GetName(), v_vn_pT_10to40_pr_yMid);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_pr_yMid->GetName(), v_vn_pT_40to60_pr_yMid);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_pr_yFor->GetName(), v_vn_pT_00to10_pr_yFor);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_pr_yFor->GetName(), v_vn_pT_10to40_pr_yFor);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_pr_yFor->GetName(), v_vn_pT_40to60_pr_yFor);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_pr_yExt->GetName(), v_vn_pT_00to10_pr_yExt);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_pr_yExt->GetName(), v_vn_pT_10to40_pr_yExt);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_pr_yExt->GetName(), v_vn_pT_40to60_pr_yExt);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_pr_yEnd->GetName(), v_vn_pT_00to10_pr_yEnd);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_pr_yEnd->GetName(), v_vn_pT_10to40_pr_yEnd);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_pr_yEnd->GetName(), v_vn_pT_40to60_pr_yEnd);

//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_de->GetName(), v_vn_pT_00to10_de);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_de->GetName(), v_vn_pT_10to40_de);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_de->GetName(), v_vn_pT_40to60_de);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_de_yMid->GetName(), v_vn_pT_00to10_de_yMid);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_de_yMid->GetName(), v_vn_pT_10to40_de_yMid);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_de_yMid->GetName(), v_vn_pT_40to60_de_yMid);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_de_yFor->GetName(), v_vn_pT_00to10_de_yFor);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_de_yFor->GetName(), v_vn_pT_10to40_de_yFor);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_de_yFor->GetName(), v_vn_pT_40to60_de_yFor);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_de_yExt->GetName(), v_vn_pT_00to10_de_yExt);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_de_yExt->GetName(), v_vn_pT_10to40_de_yExt);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_de_yExt->GetName(), v_vn_pT_40to60_de_yExt);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_de_yEnd->GetName(), v_vn_pT_00to10_de_yEnd);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_de_yEnd->GetName(), v_vn_pT_10to40_de_yEnd);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_de_yEnd->GetName(), v_vn_pT_40to60_de_yEnd);

//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_tr->GetName(), v_vn_pT_00to10_tr);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_tr->GetName(), v_vn_pT_10to40_tr);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_tr->GetName(), v_vn_pT_40to60_tr);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_tr_yMid->GetName(), v_vn_pT_00to10_tr_yMid);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_tr_yMid->GetName(), v_vn_pT_10to40_tr_yMid);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_tr_yMid->GetName(), v_vn_pT_40to60_tr_yMid);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_tr_yFor->GetName(), v_vn_pT_00to10_tr_yFor);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_tr_yFor->GetName(), v_vn_pT_10to40_tr_yFor);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_tr_yFor->GetName(), v_vn_pT_40to60_tr_yFor);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_tr_yExt->GetName(), v_vn_pT_00to10_tr_yExt);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_tr_yExt->GetName(), v_vn_pT_10to40_tr_yExt);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_tr_yExt->GetName(), v_vn_pT_40to60_tr_yExt);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_tr_yEnd->GetName(), v_vn_pT_00to10_tr_yEnd);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_tr_yEnd->GetName(), v_vn_pT_10to40_tr_yEnd);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_tr_yEnd->GetName(), v_vn_pT_40to60_tr_yEnd);


//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_he3->GetName(),      v_vn_pT_00to10_he3);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_he3->GetName(),      v_vn_pT_10to40_he3);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_he3->GetName(),      v_vn_pT_40to60_he3);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_he3_yMid->GetName(), v_vn_pT_00to10_he3_yMid);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_he3_yMid->GetName(), v_vn_pT_10to40_he3_yMid);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_he3_yMid->GetName(), v_vn_pT_40to60_he3_yMid);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_he3_yFor->GetName(), v_vn_pT_00to10_he3_yFor);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_he3_yFor->GetName(), v_vn_pT_10to40_he3_yFor);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_he3_yFor->GetName(), v_vn_pT_40to60_he3_yFor);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_he3_yExt->GetName(), v_vn_pT_00to10_he3_yExt);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_he3_yExt->GetName(), v_vn_pT_10to40_he3_yExt);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_he3_yExt->GetName(), v_vn_pT_40to60_he3_yExt);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_he3_yEnd->GetName(), v_vn_pT_00to10_he3_yEnd);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_he3_yEnd->GetName(), v_vn_pT_10to40_he3_yEnd);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_he3_yEnd->GetName(), v_vn_pT_40to60_he3_yEnd);

//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_he4->GetName(),      v_vn_pT_00to10_he4);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_he4->GetName(),      v_vn_pT_10to40_he4);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_he4->GetName(),      v_vn_pT_40to60_he4);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_he4_yMid->GetName(), v_vn_pT_00to10_he4_yMid);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_he4_yMid->GetName(), v_vn_pT_10to40_he4_yMid);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_he4_yMid->GetName(), v_vn_pT_40to60_he4_yMid);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_he4_yFor->GetName(), v_vn_pT_00to10_he4_yFor);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_he4_yFor->GetName(), v_vn_pT_10to40_he4_yFor);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_he4_yFor->GetName(), v_vn_pT_40to60_he4_yFor);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_he4_yExt->GetName(), v_vn_pT_00to10_he4_yExt);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_he4_yExt->GetName(), v_vn_pT_10to40_he4_yExt);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_he4_yExt->GetName(), v_vn_pT_40to60_he4_yExt);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_00to10_he4_yEnd->GetName(), v_vn_pT_00to10_he4_yEnd);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_10to40_he4_yEnd->GetName(), v_vn_pT_10to40_he4_yEnd);
//   addRawValuesToFile(detailsFile, normalData->h_vn_pT_40to60_he4_yEnd->GetName(), v_vn_pT_40to60_he4_yEnd);

  ////

  // Save the significance values
//   addBarlowValuesToFile(detailsFile, barlow_vn_pp, v_vn_pp);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pm, v_vn_pm);
//   addBarlowValuesToFile(detailsFile, barlow_vn_kp, v_vn_kp);
//   addBarlowValuesToFile(detailsFile, barlow_vn_km, v_vn_km);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pr, v_vn_pr);
//   addBarlowValuesToFile(detailsFile, barlow_vn_de, v_vn_de);
//   addBarlowValuesToFile(detailsFile, barlow_vn_tr, v_vn_tr);
//   addBarlowValuesToFile(detailsFile, barlow_vn_he3, v_vn_he3);
//   addBarlowValuesToFile(detailsFile, barlow_vn_he4, v_vn_he4);

//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_00to10_pr, v_vn_yCM_00to10_pr);
  addBarlowValuesToFile(detailsFile, barlow_vn_yCM_10to40_pr, v_vn_yCM_10to40_pr);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_40to60_pr, v_vn_yCM_40to60_pr);

//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_00to10_kp, v_vn_yCM_00to10_kp);
  addBarlowValuesToFile(detailsFile, barlow_vn_yCM_10to40_kp, v_vn_yCM_10to40_kp);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_40to60_kp, v_vn_yCM_40to60_kp);

//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_00to10_km, v_vn_yCM_00to10_km);
  addBarlowValuesToFile(detailsFile, barlow_vn_yCM_10to40_km, v_vn_yCM_10to40_km);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_40to60_km, v_vn_yCM_40to60_km);
    
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_00to10_pp, v_vn_yCM_00to10_pp);
  addBarlowValuesToFile(detailsFile, barlow_vn_yCM_10to40_pp, v_vn_yCM_10to40_pp);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_40to60_pp, v_vn_yCM_40to60_pp);
    
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_00to10_pm, v_vn_yCM_00to10_pm);
  addBarlowValuesToFile(detailsFile, barlow_vn_yCM_10to40_pm, v_vn_yCM_10to40_pm);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_40to60_pm, v_vn_yCM_40to60_pm);

//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_00to10_pr_symm, v_vn_yCM_00to10_pr_symm);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_10to40_pr_symm, v_vn_yCM_10to40_pr_symm);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_40to60_pr_symm, v_vn_yCM_40to60_pr_symm);

//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_00to10_de, v_vn_yCM_00to10_de);
  addBarlowValuesToFile(detailsFile, barlow_vn_yCM_10to40_de, v_vn_yCM_10to40_de);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_40to60_de, v_vn_yCM_40to60_de);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_00to10_tr, v_vn_yCM_00to10_tr);
  addBarlowValuesToFile(detailsFile, barlow_vn_yCM_10to40_tr, v_vn_yCM_10to40_tr);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_40to60_tr, v_vn_yCM_40to60_tr);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_00to10_he3, v_vn_yCM_00to10_he3);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_10to40_he3, v_vn_yCM_10to40_he3);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_40to60_he3, v_vn_yCM_40to60_he3);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_00to10_he4, v_vn_yCM_00to10_he4);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_10to40_he4, v_vn_yCM_10to40_he4);
//   addBarlowValuesToFile(detailsFile, barlow_vn_yCM_40to60_he4, v_vn_yCM_40to60_he4);

//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_pr, v_vn_pT_00to10_pr);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_pr, v_vn_pT_10to40_pr);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_pr, v_vn_pT_40to60_pr);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_pr_yMid, v_vn_pT_00to10_pr_yMid);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_pr_yMid, v_vn_pT_10to40_pr_yMid);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_pr_yMid, v_vn_pT_40to60_pr_yMid);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_pr_yFor, v_vn_pT_00to10_pr_yFor);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_pr_yFor, v_vn_pT_10to40_pr_yFor);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_pr_yFor, v_vn_pT_40to60_pr_yFor);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_pr_yExt, v_vn_pT_00to10_pr_yExt);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_pr_yExt, v_vn_pT_10to40_pr_yExt);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_pr_yExt, v_vn_pT_40to60_pr_yExt);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_pr_yEnd, v_vn_pT_00to10_pr_yEnd);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_pr_yEnd, v_vn_pT_10to40_pr_yEnd);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_pr_yEnd, v_vn_pT_40to60_pr_yEnd);

//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_de, v_vn_pT_00to10_de);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_de, v_vn_pT_10to40_de);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_de, v_vn_pT_40to60_de);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_de_yMid, v_vn_pT_00to10_de_yMid);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_de_yMid, v_vn_pT_10to40_de_yMid);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_de_yMid, v_vn_pT_40to60_de_yMid);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_de_yFor, v_vn_pT_00to10_de_yFor);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_de_yFor, v_vn_pT_10to40_de_yFor);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_de_yFor, v_vn_pT_40to60_de_yFor);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_de_yExt, v_vn_pT_00to10_de_yExt);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_de_yExt, v_vn_pT_10to40_de_yExt);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_de_yExt, v_vn_pT_40to60_de_yExt);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_de_yEnd, v_vn_pT_00to10_de_yEnd);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_de_yEnd, v_vn_pT_10to40_de_yEnd);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_de_yEnd, v_vn_pT_40to60_de_yEnd);

//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_tr,      v_vn_pT_00to10_tr);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_tr,      v_vn_pT_10to40_tr);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_tr,      v_vn_pT_40to60_tr);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_tr_yMid, v_vn_pT_00to10_tr_yMid);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_tr_yMid, v_vn_pT_10to40_tr_yMid);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_tr_yMid, v_vn_pT_40to60_tr_yMid);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_tr_yFor, v_vn_pT_00to10_tr_yFor);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_tr_yFor, v_vn_pT_10to40_tr_yFor);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_tr_yFor, v_vn_pT_40to60_tr_yFor);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_tr_yExt, v_vn_pT_00to10_tr_yExt);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_tr_yExt, v_vn_pT_10to40_tr_yExt);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_tr_yExt, v_vn_pT_40to60_tr_yExt);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_tr_yEnd, v_vn_pT_00to10_tr_yEnd);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_tr_yEnd, v_vn_pT_10to40_tr_yEnd);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_tr_yEnd, v_vn_pT_40to60_tr_yEnd);

//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_he3,      v_vn_pT_00to10_he3);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_he3,      v_vn_pT_10to40_he3);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_he3,      v_vn_pT_40to60_he3);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_he3_yMid, v_vn_pT_00to10_he3_yMid);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_he3_yMid, v_vn_pT_10to40_he3_yMid);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_he3_yMid, v_vn_pT_40to60_he3_yMid);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_he3_yFor, v_vn_pT_00to10_he3_yFor);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_he3_yFor, v_vn_pT_10to40_he3_yFor);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_he3_yFor, v_vn_pT_40to60_he3_yFor);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_he3_yExt, v_vn_pT_00to10_he3_yExt);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_he3_yExt, v_vn_pT_10to40_he3_yExt);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_he3_yExt, v_vn_pT_40to60_he3_yExt);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_he3_yEnd, v_vn_pT_00to10_he3_yEnd);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_he3_yEnd, v_vn_pT_10to40_he3_yEnd);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_he3_yEnd, v_vn_pT_40to60_he3_yEnd);

//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_he4,      v_vn_pT_00to10_he4);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_he4,      v_vn_pT_10to40_he4);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_he4,      v_vn_pT_40to60_he4);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_he4_yMid, v_vn_pT_00to10_he4_yMid);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_he4_yMid, v_vn_pT_10to40_he4_yMid);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_he4_yMid, v_vn_pT_40to60_he4_yMid);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_he4_yFor, v_vn_pT_00to10_he4_yFor);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_he4_yFor, v_vn_pT_10to40_he4_yFor);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_he4_yFor, v_vn_pT_40to60_he4_yFor);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_he4_yExt, v_vn_pT_00to10_he4_yExt);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_he4_yExt, v_vn_pT_10to40_he4_yExt);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_he4_yExt, v_vn_pT_40to60_he4_yExt);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_00to10_he4_yEnd, v_vn_pT_00to10_he4_yEnd);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_10to40_he4_yEnd, v_vn_pT_10to40_he4_yEnd);
//   addBarlowValuesToFile(detailsFile, barlow_vn_pT_40to60_he4_yEnd, v_vn_pT_40to60_he4_yEnd);

  ////
  
  detailsFile->Close();
  delete detailsFile;
}


// Calculate necessary info for one histogram type with normal data and one variation
void CompositeData::mergePoints(TH1D* normalHisto, TH1D* var1Histo, std::vector<DataPoint>& vectorOfPoints)
{
  for (int i = 1; i <= normalHisto->GetNbinsX(); i++)
  { 
    DataPoint point;
    point.normalValue = normalHisto->GetBinContent(i);
    point.normalError = normalHisto->GetBinError(i);
    
    point.var1Value = var1Histo->GetBinContent(i);
    point.var1Error = var1Histo->GetBinError(i);

    point.delta = TMath::Abs(point.var1Value - point.normalValue);
    point.deltaError = TMath::Sqrt(TMath::Abs(TMath::Power(point.var1Error, 2) - TMath::Power(point.normalError, 2)));
    point.deltaByDeltaError = (point.deltaError == 0.0)?0.0:point.delta/point.deltaError;
    //point.stdDev = point.delta / TMath::Sqrt(12.0);
    //point.variance = TMath::Power(point.delta/TMath::Sqrt(12.0), 2.0);

    point.mean = (point.normalValue + point.var1Value) / 2.0;
    Double_t Nvariance = TMath::Power(point.normalValue - point.mean, 2.0) + 
                          TMath::Power(point.var1Value - point.mean, 2.0);

    point.variance = Nvariance / 2.0;
    point.stdDev = TMath::Sqrt(point.variance);
    point.stdDevPercentage = 100.0 * point.stdDev / TMath::Abs(point.normalValue);

    vectorOfPoints.push_back(point);
  }
}


// Calculate necessary info for one histogram type with normal data and two variations
void CompositeData::mergePoints(TH1D* normalHisto, TH1D* var1Histo, TH1D* var2Histo, std::vector<DataPoint>& vectorOfPoints)
{
  for (int i = 1; i <= normalHisto->GetNbinsX(); i++)
  {
    DataPoint point;
    point.normalValue = normalHisto->GetBinContent(i);
    point.normalError = normalHisto->GetBinError(i);
    
    point.var1Value = var1Histo->GetBinContent(i);
    point.var1Error = var1Histo->GetBinError(i);

    point.var2Value = var2Histo->GetBinContent(i);
    point.var2Error = var2Histo->GetBinError(i);

    point.getMax();
    point.getMin();
    
    point.delta = TMath::Abs(point.maxValue - point.minValue);
    point.deltaError = TMath::Sqrt(TMath::Abs(TMath::Power(point.maxError, 2) - TMath::Power(point.minError, 2)));
    point.deltaByDeltaError = (point.deltaError == 0.0)?0.0:point.delta/point.deltaError;
    //point.stdDev = point.delta / TMath::Sqrt(12.0);
    //point.variance = TMath::Power(point.delta/TMath::Sqrt(12.0), 2.0);

    point.mean = (point.normalValue + point.var1Value + point.var2Value) / 3.0;
    
    Double_t Nvariance = TMath::Power(point.normalValue - point.mean, 2.0) + 
                          TMath::Power(point.var1Value - point.mean, 2.0) + 
                          TMath::Power(point.var2Value - point.mean, 2.0);

    point.variance = Nvariance / 3.0;
    point.stdDev = TMath::Sqrt(point.variance);
    point.stdDevPercentage = 100.0 * point.stdDev / TMath::Abs(point.normalValue);

    vectorOfPoints.push_back(point);
  }
}


// Calculate necessary info for one histogram type with normal data and three variations
void CompositeData::mergePoints(TH1D* normalHisto, TH1D* var1Histo, TH1D* var2Histo, TH1D* var3Histo, std::vector<DataPoint>& vectorOfPoints)
{
 for (int i = 1; i <= normalHisto->GetNbinsX(); i++)
  {
    DataPoint point;
    point.normalValue = normalHisto->GetBinContent(i);
    point.normalError = normalHisto->GetBinError(i);
    
    point.var1Value = var1Histo->GetBinContent(i);
    point.var1Error = var1Histo->GetBinError(i);

    point.var2Value = var2Histo->GetBinContent(i);
    point.var2Error = var2Histo->GetBinError(i);

    point.var3Value = var3Histo->GetBinContent(i);
    point.var3Error = var3Histo->GetBinError(i);

    point.getMax();
    point.getMin();
    
    point.delta = TMath::Abs(point.maxValue - point.minValue);
    point.deltaError = TMath::Sqrt(TMath::Abs(TMath::Power(point.maxError, 2) - TMath::Power(point.minError, 2)));
    point.deltaByDeltaError = (point.deltaError == 0.0)?0.0:point.delta/point.deltaError;
    //point.stdDev = point.delta / TMath::Sqrt(12.0);
    //point.variance = TMath::Power(point.delta/TMath::Sqrt(12.0), 2.0);

    point.mean = (point.normalValue + point.var1Value + point.var2Value + point.var3Value) / 4.0;
    
    Double_t Nvariance = TMath::Power(point.normalValue - point.mean, 2.0) + 
                          TMath::Power(point.var1Value - point.mean, 2.0) + 
                          TMath::Power(point.var2Value - point.mean, 2.0) + 
                          TMath::Power(point.var3Value - point.mean, 2.0);

    point.variance = Nvariance / 4.0;
    point.stdDev = TMath::Sqrt(point.variance);
    point.stdDevPercentage = 100.0 * point.stdDev / TMath::Abs(point.normalValue);

    vectorOfPoints.push_back(point);
  }
}

// Calculate necessary info for one histogram type with normal data and four variations
void CompositeData::mergePoints(TH1D* normalHisto, TH1D* var1Histo, TH1D* var2Histo, TH1D* var3Histo, TH1D* var4Histo, std::vector<DataPoint>& vectorOfPoints)
{
  for (int i = 1; i <= normalHisto->GetNbinsX(); i++)
  {
    DataPoint point;
    point.normalValue = normalHisto->GetBinContent(i);
    point.normalError = normalHisto->GetBinError(i);
    
    point.var1Value = var1Histo->GetBinContent(i);
    point.var1Error = var1Histo->GetBinError(i);

    point.var2Value = var2Histo->GetBinContent(i);
    point.var2Error = var2Histo->GetBinError(i);

    point.var3Value = var3Histo->GetBinContent(i);
    point.var3Error = var3Histo->GetBinError(i);

    point.var4Value = var4Histo->GetBinContent(i);
    point.var4Error = var4Histo->GetBinError(i);

    point.getMax();
    point.getMin();
    
    point.delta = TMath::Abs(point.maxValue - point.minValue);
    point.deltaError = TMath::Sqrt(TMath::Abs(TMath::Power(point.maxError, 2) - TMath::Power(point.minError, 2)));
    point.deltaByDeltaError = (point.deltaError == 0.0)?0.0:point.delta/point.deltaError;
    //point.stdDev = point.delta / TMath::Sqrt(12.0);
    //point.variance = TMath::Power(point.delta/TMath::Sqrt(12.0), 2.0);

    point.mean = (point.normalValue + point.var1Value + point.var2Value + point.var3Value + point.var4Value) / 5.0;
    
    Double_t Nvariance = TMath::Power(point.normalValue - point.mean, 2.0) + 
                          TMath::Power(point.var1Value - point.mean, 2.0) + 
                          TMath::Power(point.var2Value - point.mean, 2.0) + 
                          TMath::Power(point.var3Value - point.mean, 2.0) +
                          TMath::Power(point.var4Value - point.mean, 2.0);

    point.variance = Nvariance / 5.0;
    point.stdDev = TMath::Sqrt(point.variance);
    point.stdDevPercentage = 100.0 * point.stdDev / TMath::Abs(point.normalValue);

    vectorOfPoints.push_back(point);
  }
}


// Combine one variation with the normal data to get the attributes for systematics
void CompositeData::combine(Variation* normalData, Variation* var1Data)
{
//   mergePoints(normalData->h_vn_pp, var1Data->h_vn_pp, v_vn_pp);
//   mergePoints(normalData->h_vn_pm, var1Data->h_vn_pm, v_vn_pm);
//   mergePoints(normalData->h_vn_kp, var1Data->h_vn_kp, v_vn_kp);
//   mergePoints(normalData->h_vn_km, var1Data->h_vn_km, v_vn_km);
//   mergePoints(normalData->h_vn_pr, var1Data->h_vn_pr, v_vn_pr);
//   mergePoints(normalData->h_vn_de, var1Data->h_vn_de, v_vn_de);
//   mergePoints(normalData->h_vn_tr, var1Data->h_vn_tr, v_vn_tr);
//   mergePoints(normalData->h_vn_he3, var1Data->h_vn_he3, v_vn_he3);
//   mergePoints(normalData->h_vn_he4, var1Data->h_vn_he4, v_vn_he4);
                            
//   mergePoints(normalData->h_vn_yCM_00to10_pr, var1Data->h_vn_yCM_00to10_pr, v_vn_yCM_00to10_pr);
  mergePoints(normalData->h_vn_yCM_10to40_pr, var1Data->h_vn_yCM_10to40_pr, v_vn_yCM_10to40_pr);
//   mergePoints(normalData->h_vn_yCM_40to60_pr, var1Data->h_vn_yCM_40to60_pr, v_vn_yCM_40to60_pr);
    
//   mergePoints(normalData->h_vn_yCM_00to10_kp, var1Data->h_vn_yCM_00to10_kp, v_vn_yCM_00to10_kp);
  mergePoints(normalData->h_vn_yCM_10to40_kp, var1Data->h_vn_yCM_10to40_kp, v_vn_yCM_10to40_kp);
//   mergePoints(normalData->h_vn_yCM_40to60_kp, var1Data->h_vn_yCM_40to60_kp, v_vn_yCM_40to60_kp);
   
//   mergePoints(normalData->h_vn_yCM_00to10_km, var1Data->h_vn_yCM_00to10_km, v_vn_yCM_00to10_km);
  mergePoints(normalData->h_vn_yCM_10to40_km, var1Data->h_vn_yCM_10to40_km, v_vn_yCM_10to40_km);
//   mergePoints(normalData->h_vn_yCM_40to60_km, var1Data->h_vn_yCM_40to60_km, v_vn_yCM_40to60_km);
    
//   mergePoints(normalData->h_vn_yCM_00to10_pp, var1Data->h_vn_yCM_00to10_pp, v_vn_yCM_00to10_pp);
  mergePoints(normalData->h_vn_yCM_10to40_pp, var1Data->h_vn_yCM_10to40_pp, v_vn_yCM_10to40_pp);
//   mergePoints(normalData->h_vn_yCM_40to60_pp, var1Data->h_vn_yCM_40to60_pp, v_vn_yCM_40to60_pp);
    
//   mergePoints(normalData->h_vn_yCM_00to10_pm, var1Data->h_vn_yCM_00to10_pm, v_vn_yCM_00to10_pm);
  mergePoints(normalData->h_vn_yCM_10to40_pm, var1Data->h_vn_yCM_10to40_pm, v_vn_yCM_10to40_pm);
//   mergePoints(normalData->h_vn_yCM_40to60_pm, var1Data->h_vn_yCM_40to60_pm, v_vn_yCM_40to60_pm);

//   mergePoints(normalData->h_vn_yCM_00to10_pr_symm, var1Data->h_vn_yCM_00to10_pr_symm, v_vn_yCM_00to10_pr_symm);
//   mergePoints(normalData->h_vn_yCM_10to40_pr_symm, var1Data->h_vn_yCM_10to40_pr_symm, v_vn_yCM_10to40_pr_symm);
//   mergePoints(normalData->h_vn_yCM_40to60_pr_symm, var1Data->h_vn_yCM_40to60_pr_symm, v_vn_yCM_40to60_pr_symm);

//   mergePoints(normalData->h_vn_pT_00to10_pr, var1Data->h_vn_pT_00to10_pr, v_vn_pT_00to10_pr);
//   mergePoints(normalData->h_vn_pT_10to40_pr, var1Data->h_vn_pT_10to40_pr, v_vn_pT_10to40_pr);
//   mergePoints(normalData->h_vn_pT_40to60_pr, var1Data->h_vn_pT_40to60_pr, v_vn_pT_40to60_pr);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yMid, var1Data->h_vn_pT_00to10_pr_yMid, v_vn_pT_00to10_pr_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yMid, var1Data->h_vn_pT_10to40_pr_yMid, v_vn_pT_10to40_pr_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yMid, var1Data->h_vn_pT_40to60_pr_yMid, v_vn_pT_40to60_pr_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yFor, var1Data->h_vn_pT_00to10_pr_yFor, v_vn_pT_00to10_pr_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yFor, var1Data->h_vn_pT_10to40_pr_yFor, v_vn_pT_10to40_pr_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yFor, var1Data->h_vn_pT_40to60_pr_yFor, v_vn_pT_40to60_pr_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yExt, var1Data->h_vn_pT_00to10_pr_yExt, v_vn_pT_00to10_pr_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yExt, var1Data->h_vn_pT_10to40_pr_yExt, v_vn_pT_10to40_pr_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yExt, var1Data->h_vn_pT_40to60_pr_yExt, v_vn_pT_40to60_pr_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yEnd, var1Data->h_vn_pT_00to10_pr_yEnd, v_vn_pT_00to10_pr_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yEnd, var1Data->h_vn_pT_10to40_pr_yEnd, v_vn_pT_10to40_pr_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yEnd, var1Data->h_vn_pT_40to60_pr_yEnd, v_vn_pT_40to60_pr_yEnd);
 
//   mergePoints(normalData->h_vn_yCM_00to10_de, var1Data->h_vn_yCM_00to10_de, v_vn_yCM_00to10_de);
  mergePoints(normalData->h_vn_yCM_10to40_de, var1Data->h_vn_yCM_10to40_de, v_vn_yCM_10to40_de);
//   mergePoints(normalData->h_vn_yCM_40to60_de, var1Data->h_vn_yCM_40to60_de, v_vn_yCM_40to60_de);
//   mergePoints(normalData->h_vn_yCM_00to10_tr, var1Data->h_vn_yCM_00to10_tr, v_vn_yCM_00to10_tr);
  mergePoints(normalData->h_vn_yCM_10to40_tr, var1Data->h_vn_yCM_10to40_tr, v_vn_yCM_10to40_tr);
//   mergePoints(normalData->h_vn_yCM_40to60_tr, var1Data->h_vn_yCM_40to60_tr, v_vn_yCM_40to60_tr);

//   mergePoints(normalData->h_vn_yCM_00to10_he3, var1Data->h_vn_yCM_00to10_he3, v_vn_yCM_00to10_he3);
//   mergePoints(normalData->h_vn_yCM_10to40_he3, var1Data->h_vn_yCM_10to40_he3, v_vn_yCM_10to40_he3);
//   mergePoints(normalData->h_vn_yCM_40to60_he3, var1Data->h_vn_yCM_40to60_he3, v_vn_yCM_40to60_he3);
//   mergePoints(normalData->h_vn_yCM_00to10_he4, var1Data->h_vn_yCM_00to10_he4, v_vn_yCM_00to10_he4);
//   mergePoints(normalData->h_vn_yCM_10to40_he4, var1Data->h_vn_yCM_10to40_he4, v_vn_yCM_10to40_he4);
//   mergePoints(normalData->h_vn_yCM_40to60_he4, var1Data->h_vn_yCM_40to60_he4, v_vn_yCM_40to60_he4);
//   mergePoints(normalData->h_vn_pT_00to10_de, var1Data->h_vn_pT_00to10_de, v_vn_pT_00to10_de);
//   mergePoints(normalData->h_vn_pT_10to40_de, var1Data->h_vn_pT_10to40_de, v_vn_pT_10to40_de);
//   mergePoints(normalData->h_vn_pT_40to60_de, var1Data->h_vn_pT_40to60_de, v_vn_pT_40to60_de);
//   mergePoints(normalData->h_vn_pT_00to10_de_yMid, var1Data->h_vn_pT_00to10_de_yMid, v_vn_pT_00to10_de_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_de_yMid, var1Data->h_vn_pT_10to40_de_yMid, v_vn_pT_10to40_de_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_de_yMid, var1Data->h_vn_pT_40to60_de_yMid, v_vn_pT_40to60_de_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_de_yFor, var1Data->h_vn_pT_00to10_de_yFor, v_vn_pT_00to10_de_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_de_yFor, var1Data->h_vn_pT_10to40_de_yFor, v_vn_pT_10to40_de_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_de_yFor, var1Data->h_vn_pT_40to60_de_yFor, v_vn_pT_40to60_de_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_de_yExt, var1Data->h_vn_pT_00to10_de_yExt, v_vn_pT_00to10_de_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_de_yExt, var1Data->h_vn_pT_10to40_de_yExt, v_vn_pT_10to40_de_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_de_yExt, var1Data->h_vn_pT_40to60_de_yExt, v_vn_pT_40to60_de_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_de_yEnd, var1Data->h_vn_pT_00to10_de_yEnd, v_vn_pT_00to10_de_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_de_yEnd, var1Data->h_vn_pT_10to40_de_yEnd, v_vn_pT_10to40_de_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_de_yEnd, var1Data->h_vn_pT_40to60_de_yEnd, v_vn_pT_40to60_de_yEnd);

  //mergePoints(normalData->h_vn_yCM_00to10_tr, var1Data->h_vn_yCM_00to10_tr, v_vn_yCM_00to10_tr);
  //mergePoints(normalData->h_vn_yCM_10to40_tr, var1Data->h_vn_yCM_10to40_tr, v_vn_yCM_10to40_tr);
  //mergePoints(normalData->h_vn_yCM_40to60_tr, var1Data->h_vn_yCM_40to60_tr, v_vn_yCM_40to60_tr);

//   mergePoints(normalData->h_vn_pT_00to10_tr,      var1Data->h_vn_pT_00to10_tr,      v_vn_pT_00to10_tr);
//   mergePoints(normalData->h_vn_pT_10to40_tr,      var1Data->h_vn_pT_10to40_tr,      v_vn_pT_10to40_tr);
//   mergePoints(normalData->h_vn_pT_40to60_tr,      var1Data->h_vn_pT_40to60_tr,      v_vn_pT_40to60_tr);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yMid, var1Data->h_vn_pT_00to10_tr_yMid, v_vn_pT_00to10_tr_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yMid, var1Data->h_vn_pT_10to40_tr_yMid, v_vn_pT_10to40_tr_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yMid, var1Data->h_vn_pT_40to60_tr_yMid, v_vn_pT_40to60_tr_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yFor, var1Data->h_vn_pT_00to10_tr_yFor, v_vn_pT_00to10_tr_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yFor, var1Data->h_vn_pT_10to40_tr_yFor, v_vn_pT_10to40_tr_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yFor, var1Data->h_vn_pT_40to60_tr_yFor, v_vn_pT_40to60_tr_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yExt, var1Data->h_vn_pT_00to10_tr_yExt, v_vn_pT_00to10_tr_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yExt, var1Data->h_vn_pT_10to40_tr_yExt, v_vn_pT_10to40_tr_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yExt, var1Data->h_vn_pT_40to60_tr_yExt, v_vn_pT_40to60_tr_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yEnd, var1Data->h_vn_pT_00to10_tr_yEnd, v_vn_pT_00to10_tr_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yEnd, var1Data->h_vn_pT_10to40_tr_yEnd, v_vn_pT_10to40_tr_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yEnd, var1Data->h_vn_pT_40to60_tr_yEnd, v_vn_pT_40to60_tr_yEnd);


//   mergePoints(normalData->h_vn_pT_00to10_he3,      var1Data->h_vn_pT_00to10_he3,      v_vn_pT_00to10_he3);
//   mergePoints(normalData->h_vn_pT_10to40_he3,      var1Data->h_vn_pT_10to40_he3,      v_vn_pT_10to40_he3);
//   mergePoints(normalData->h_vn_pT_40to60_he3,      var1Data->h_vn_pT_40to60_he3,      v_vn_pT_40to60_he3);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yMid, var1Data->h_vn_pT_00to10_he3_yMid, v_vn_pT_00to10_he3_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yMid, var1Data->h_vn_pT_10to40_he3_yMid, v_vn_pT_10to40_he3_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yMid, var1Data->h_vn_pT_40to60_he3_yMid, v_vn_pT_40to60_he3_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yFor, var1Data->h_vn_pT_00to10_he3_yFor, v_vn_pT_00to10_he3_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yFor, var1Data->h_vn_pT_10to40_he3_yFor, v_vn_pT_10to40_he3_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yFor, var1Data->h_vn_pT_40to60_he3_yFor, v_vn_pT_40to60_he3_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yExt, var1Data->h_vn_pT_00to10_he3_yExt, v_vn_pT_00to10_he3_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yExt, var1Data->h_vn_pT_10to40_he3_yExt, v_vn_pT_10to40_he3_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yExt, var1Data->h_vn_pT_40to60_he3_yExt, v_vn_pT_40to60_he3_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yEnd, var1Data->h_vn_pT_00to10_he3_yEnd, v_vn_pT_00to10_he3_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yEnd, var1Data->h_vn_pT_10to40_he3_yEnd, v_vn_pT_10to40_he3_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yEnd, var1Data->h_vn_pT_40to60_he3_yEnd, v_vn_pT_40to60_he3_yEnd);

//   mergePoints(normalData->h_vn_pT_00to10_he4,      var1Data->h_vn_pT_00to10_he4,      v_vn_pT_00to10_he4);
//   mergePoints(normalData->h_vn_pT_10to40_he4,      var1Data->h_vn_pT_10to40_he4,      v_vn_pT_10to40_he4);
//   mergePoints(normalData->h_vn_pT_40to60_he4,      var1Data->h_vn_pT_40to60_he4,      v_vn_pT_40to60_he4);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yMid, var1Data->h_vn_pT_00to10_he4_yMid, v_vn_pT_00to10_he4_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yMid, var1Data->h_vn_pT_10to40_he4_yMid, v_vn_pT_10to40_he4_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yMid, var1Data->h_vn_pT_40to60_he4_yMid, v_vn_pT_40to60_he4_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yFor, var1Data->h_vn_pT_00to10_he4_yFor, v_vn_pT_00to10_he4_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yFor, var1Data->h_vn_pT_10to40_he4_yFor, v_vn_pT_10to40_he4_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yFor, var1Data->h_vn_pT_40to60_he4_yFor, v_vn_pT_40to60_he4_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yExt, var1Data->h_vn_pT_00to10_he4_yExt, v_vn_pT_00to10_he4_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yExt, var1Data->h_vn_pT_10to40_he4_yExt, v_vn_pT_10to40_he4_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yExt, var1Data->h_vn_pT_40to60_he4_yExt, v_vn_pT_40to60_he4_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yEnd, var1Data->h_vn_pT_00to10_he4_yEnd, v_vn_pT_00to10_he4_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yEnd, var1Data->h_vn_pT_10to40_he4_yEnd, v_vn_pT_10to40_he4_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yEnd, var1Data->h_vn_pT_40to60_he4_yEnd, v_vn_pT_40to60_he4_yEnd);

}



// Combine two variations with the normal data to get the attributes for systematics
void CompositeData::combine(Variation* normalData, Variation* var1Data, Variation* var2Data)
{
//   mergePoints(normalData->h_vn_pp, var1Data->h_vn_pp, var2Data->h_vn_pp, v_vn_pp);
//   mergePoints(normalData->h_vn_pm, var1Data->h_vn_pm, var2Data->h_vn_pm, v_vn_pm);
//   mergePoints(normalData->h_vn_kp, var1Data->h_vn_kp, var2Data->h_vn_kp, v_vn_kp);
//   mergePoints(normalData->h_vn_km, var1Data->h_vn_km, var2Data->h_vn_km, v_vn_km);
//   mergePoints(normalData->h_vn_pr, var1Data->h_vn_pr, var2Data->h_vn_pr, v_vn_pr);
//   mergePoints(normalData->h_vn_de, var1Data->h_vn_de, var2Data->h_vn_de, v_vn_de);
//   mergePoints(normalData->h_vn_tr, var1Data->h_vn_tr, var2Data->h_vn_tr, v_vn_tr);
//   mergePoints(normalData->h_vn_he3, var1Data->h_vn_he3, var2Data->h_vn_he3, v_vn_he3);
//   mergePoints(normalData->h_vn_he4, var1Data->h_vn_he4, var2Data->h_vn_he4, v_vn_he4);
  
//   mergePoints(normalData->h_vn_yCM_00to10_pr, var1Data->h_vn_yCM_00to10_pr, var2Data->h_vn_yCM_00to10_pr, v_vn_yCM_00to10_pr);
  mergePoints(normalData->h_vn_yCM_10to40_pr, var1Data->h_vn_yCM_10to40_pr, var2Data->h_vn_yCM_10to40_pr, v_vn_yCM_10to40_pr);
//   mergePoints(normalData->h_vn_yCM_40to60_pr, var1Data->h_vn_yCM_40to60_pr, var2Data->h_vn_yCM_40to60_pr, v_vn_yCM_40to60_pr);
    
//   mergePoints(normalData->h_vn_yCM_00to10_kp, var1Data->h_vn_yCM_00to10_kp, var2Data->h_vn_yCM_00to10_kp, v_vn_yCM_00to10_kp);
  mergePoints(normalData->h_vn_yCM_10to40_kp, var1Data->h_vn_yCM_10to40_kp, var2Data->h_vn_yCM_10to40_kp, v_vn_yCM_10to40_kp);
//   mergePoints(normalData->h_vn_yCM_40to60_kp, var1Data->h_vn_yCM_40to60_kp, var2Data->h_vn_yCM_40to60_kp, v_vn_yCM_40to60_kp);
    
//   mergePoints(normalData->h_vn_yCM_00to10_km, var1Data->h_vn_yCM_00to10_km, var2Data->h_vn_yCM_00to10_km, v_vn_yCM_00to10_km);
  mergePoints(normalData->h_vn_yCM_10to40_km, var1Data->h_vn_yCM_10to40_km, var2Data->h_vn_yCM_10to40_km, v_vn_yCM_10to40_km);
//   mergePoints(normalData->h_vn_yCM_40to60_km, var1Data->h_vn_yCM_40to60_km, var2Data->h_vn_yCM_40to60_km, v_vn_yCM_40to60_km);
    
//   mergePoints(normalData->h_vn_yCM_00to10_pp, var1Data->h_vn_yCM_00to10_pp, var2Data->h_vn_yCM_00to10_pp, v_vn_yCM_00to10_pp);
  mergePoints(normalData->h_vn_yCM_10to40_pp, var1Data->h_vn_yCM_10to40_pp, var2Data->h_vn_yCM_10to40_pp, v_vn_yCM_10to40_pp);
//   mergePoints(normalData->h_vn_yCM_40to60_pp, var1Data->h_vn_yCM_40to60_pp, var2Data->h_vn_yCM_40to60_pp, v_vn_yCM_40to60_pp);
    
//   mergePoints(normalData->h_vn_yCM_00to10_pm, var1Data->h_vn_yCM_00to10_pm, var2Data->h_vn_yCM_00to10_pm, v_vn_yCM_00to10_pm);
  mergePoints(normalData->h_vn_yCM_10to40_pm, var1Data->h_vn_yCM_10to40_pm, var2Data->h_vn_yCM_10to40_pm, v_vn_yCM_10to40_pm);
//   mergePoints(normalData->h_vn_yCM_40to60_pm, var1Data->h_vn_yCM_40to60_pm, var2Data->h_vn_yCM_40to60_pm, v_vn_yCM_40to60_pm);

//   mergePoints(normalData->h_vn_yCM_00to10_pr_symm, var1Data->h_vn_yCM_00to10_pr_symm, var2Data->h_vn_yCM_00to10_pr_symm, v_vn_yCM_00to10_pr_symm);
//   mergePoints(normalData->h_vn_yCM_10to40_pr_symm, var1Data->h_vn_yCM_10to40_pr_symm, var2Data->h_vn_yCM_10to40_pr_symm, v_vn_yCM_10to40_pr_symm);
//   mergePoints(normalData->h_vn_yCM_40to60_pr_symm, var1Data->h_vn_yCM_40to60_pr_symm, var2Data->h_vn_yCM_40to60_pr_symm, v_vn_yCM_40to60_pr_symm);

//   mergePoints(normalData->h_vn_yCM_00to10_de, var1Data->h_vn_yCM_00to10_de, var2Data->h_vn_yCM_00to10_de, v_vn_yCM_00to10_de);
  mergePoints(normalData->h_vn_yCM_10to40_de, var1Data->h_vn_yCM_10to40_de, var2Data->h_vn_yCM_10to40_de, v_vn_yCM_10to40_de);
//   mergePoints(normalData->h_vn_yCM_40to60_de, var1Data->h_vn_yCM_40to60_de, var2Data->h_vn_yCM_40to60_de, v_vn_yCM_40to60_de);
//   mergePoints(normalData->h_vn_yCM_00to10_tr, var1Data->h_vn_yCM_00to10_tr, var2Data->h_vn_yCM_00to10_tr, v_vn_yCM_00to10_tr);
  mergePoints(normalData->h_vn_yCM_10to40_tr, var1Data->h_vn_yCM_10to40_tr, var2Data->h_vn_yCM_10to40_tr, v_vn_yCM_10to40_tr);
//   mergePoints(normalData->h_vn_yCM_40to60_tr, var1Data->h_vn_yCM_40to60_tr, var2Data->h_vn_yCM_40to60_tr, v_vn_yCM_40to60_tr);
//   mergePoints(normalData->h_vn_yCM_00to10_he3, var1Data->h_vn_yCM_00to10_he3, var2Data->h_vn_yCM_00to10_he3, v_vn_yCM_00to10_he3);
//   mergePoints(normalData->h_vn_yCM_10to40_he3, var1Data->h_vn_yCM_10to40_he3, var2Data->h_vn_yCM_10to40_he3, v_vn_yCM_10to40_he3);
//   mergePoints(normalData->h_vn_yCM_40to60_he3, var1Data->h_vn_yCM_40to60_he3, var2Data->h_vn_yCM_40to60_he3, v_vn_yCM_40to60_he3);
//   mergePoints(normalData->h_vn_yCM_00to10_he4, var1Data->h_vn_yCM_00to10_he4, var2Data->h_vn_yCM_00to10_he4, v_vn_yCM_00to10_he4);
//   mergePoints(normalData->h_vn_yCM_10to40_he4, var1Data->h_vn_yCM_10to40_he4, var2Data->h_vn_yCM_10to40_he4, v_vn_yCM_10to40_he4);
//   mergePoints(normalData->h_vn_yCM_40to60_he4, var1Data->h_vn_yCM_40to60_he4, var2Data->h_vn_yCM_40to60_he4, v_vn_yCM_40to60_he4);

//   mergePoints(normalData->h_vn_pT_00to10_pr, var1Data->h_vn_pT_00to10_pr, var2Data->h_vn_pT_00to10_pr, v_vn_pT_00to10_pr);
//   mergePoints(normalData->h_vn_pT_10to40_pr, var1Data->h_vn_pT_10to40_pr, var2Data->h_vn_pT_10to40_pr, v_vn_pT_10to40_pr);
//   mergePoints(normalData->h_vn_pT_40to60_pr, var1Data->h_vn_pT_40to60_pr, var2Data->h_vn_pT_40to60_pr, v_vn_pT_40to60_pr);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yMid, var1Data->h_vn_pT_00to10_pr_yMid, var2Data->h_vn_pT_00to10_pr_yMid, v_vn_pT_00to10_pr_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yMid, var1Data->h_vn_pT_10to40_pr_yMid, var2Data->h_vn_pT_10to40_pr_yMid, v_vn_pT_10to40_pr_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yMid, var1Data->h_vn_pT_40to60_pr_yMid, var2Data->h_vn_pT_40to60_pr_yMid, v_vn_pT_40to60_pr_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yFor, var1Data->h_vn_pT_00to10_pr_yFor, var2Data->h_vn_pT_00to10_pr_yFor, v_vn_pT_00to10_pr_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yFor, var1Data->h_vn_pT_10to40_pr_yFor, var2Data->h_vn_pT_10to40_pr_yFor, v_vn_pT_10to40_pr_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yFor, var1Data->h_vn_pT_40to60_pr_yFor, var2Data->h_vn_pT_40to60_pr_yFor, v_vn_pT_40to60_pr_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yExt, var1Data->h_vn_pT_00to10_pr_yExt, var2Data->h_vn_pT_00to10_pr_yExt, v_vn_pT_00to10_pr_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yExt, var1Data->h_vn_pT_10to40_pr_yExt, var2Data->h_vn_pT_10to40_pr_yExt, v_vn_pT_10to40_pr_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yExt, var1Data->h_vn_pT_40to60_pr_yExt, var2Data->h_vn_pT_40to60_pr_yExt, v_vn_pT_40to60_pr_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yEnd, var1Data->h_vn_pT_00to10_pr_yEnd, var2Data->h_vn_pT_00to10_pr_yEnd, v_vn_pT_00to10_pr_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yEnd, var1Data->h_vn_pT_10to40_pr_yEnd, var2Data->h_vn_pT_10to40_pr_yEnd, v_vn_pT_10to40_pr_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yEnd, var1Data->h_vn_pT_40to60_pr_yEnd, var2Data->h_vn_pT_40to60_pr_yEnd, v_vn_pT_40to60_pr_yEnd);

//   mergePoints(normalData->h_vn_pT_00to10_de, var1Data->h_vn_pT_00to10_de, var2Data->h_vn_pT_00to10_de, v_vn_pT_00to10_de);
//   mergePoints(normalData->h_vn_pT_10to40_de, var1Data->h_vn_pT_10to40_de, var2Data->h_vn_pT_10to40_de, v_vn_pT_10to40_de);
//   mergePoints(normalData->h_vn_pT_40to60_de, var1Data->h_vn_pT_40to60_de, var2Data->h_vn_pT_40to60_de, v_vn_pT_40to60_de);
//   mergePoints(normalData->h_vn_pT_00to10_de_yMid, var1Data->h_vn_pT_00to10_de_yMid, var2Data->h_vn_pT_00to10_de_yMid, v_vn_pT_00to10_de_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_de_yMid, var1Data->h_vn_pT_10to40_de_yMid, var2Data->h_vn_pT_10to40_de_yMid, v_vn_pT_10to40_de_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_de_yMid, var1Data->h_vn_pT_40to60_de_yMid, var2Data->h_vn_pT_40to60_de_yMid, v_vn_pT_40to60_de_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_de_yFor, var1Data->h_vn_pT_00to10_de_yFor, var2Data->h_vn_pT_00to10_de_yFor, v_vn_pT_00to10_de_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_de_yFor, var1Data->h_vn_pT_10to40_de_yFor, var2Data->h_vn_pT_10to40_de_yFor, v_vn_pT_10to40_de_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_de_yFor, var1Data->h_vn_pT_40to60_de_yFor, var2Data->h_vn_pT_40to60_de_yFor, v_vn_pT_40to60_de_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_de_yExt, var1Data->h_vn_pT_00to10_de_yExt, var2Data->h_vn_pT_00to10_de_yExt, v_vn_pT_00to10_de_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_de_yExt, var1Data->h_vn_pT_10to40_de_yExt, var2Data->h_vn_pT_10to40_de_yExt, v_vn_pT_10to40_de_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_de_yExt, var1Data->h_vn_pT_40to60_de_yExt, var2Data->h_vn_pT_40to60_de_yExt, v_vn_pT_40to60_de_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_de_yEnd, var1Data->h_vn_pT_00to10_de_yEnd, var2Data->h_vn_pT_00to10_de_yEnd, v_vn_pT_00to10_de_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_de_yEnd, var1Data->h_vn_pT_10to40_de_yEnd, var2Data->h_vn_pT_10to40_de_yEnd, v_vn_pT_10to40_de_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_de_yEnd, var1Data->h_vn_pT_40to60_de_yEnd, var2Data->h_vn_pT_40to60_de_yEnd, v_vn_pT_40to60_de_yEnd);

//   mergePoints(normalData->h_vn_pT_00to10_tr, var1Data->h_vn_pT_00to10_tr, var2Data->h_vn_pT_00to10_tr, v_vn_pT_00to10_tr);
//   mergePoints(normalData->h_vn_pT_10to40_tr, var1Data->h_vn_pT_10to40_tr, var2Data->h_vn_pT_10to40_tr, v_vn_pT_10to40_tr);
//   mergePoints(normalData->h_vn_pT_40to60_tr, var1Data->h_vn_pT_40to60_tr, var2Data->h_vn_pT_40to60_tr, v_vn_pT_40to60_tr);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yMid, var1Data->h_vn_pT_00to10_tr_yMid, var2Data->h_vn_pT_00to10_tr_yMid, v_vn_pT_00to10_tr_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yMid, var1Data->h_vn_pT_10to40_tr_yMid, var2Data->h_vn_pT_10to40_tr_yMid, v_vn_pT_10to40_tr_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yMid, var1Data->h_vn_pT_40to60_tr_yMid, var2Data->h_vn_pT_40to60_tr_yMid, v_vn_pT_40to60_tr_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yFor, var1Data->h_vn_pT_00to10_tr_yFor, var2Data->h_vn_pT_00to10_tr_yFor, v_vn_pT_00to10_tr_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yFor, var1Data->h_vn_pT_10to40_tr_yFor, var2Data->h_vn_pT_10to40_tr_yFor, v_vn_pT_10to40_tr_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yFor, var1Data->h_vn_pT_40to60_tr_yFor, var2Data->h_vn_pT_40to60_tr_yFor, v_vn_pT_40to60_tr_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yExt, var1Data->h_vn_pT_00to10_tr_yExt, var2Data->h_vn_pT_00to10_tr_yExt, v_vn_pT_00to10_tr_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yExt, var1Data->h_vn_pT_10to40_tr_yExt, var2Data->h_vn_pT_10to40_tr_yExt, v_vn_pT_10to40_tr_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yExt, var1Data->h_vn_pT_40to60_tr_yExt, var2Data->h_vn_pT_40to60_tr_yExt, v_vn_pT_40to60_tr_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yEnd, var1Data->h_vn_pT_00to10_tr_yEnd, var2Data->h_vn_pT_00to10_tr_yEnd, v_vn_pT_00to10_tr_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yEnd, var1Data->h_vn_pT_10to40_tr_yEnd, var2Data->h_vn_pT_10to40_tr_yEnd, v_vn_pT_10to40_tr_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yEnd, var1Data->h_vn_pT_40to60_tr_yEnd, var2Data->h_vn_pT_40to60_tr_yEnd, v_vn_pT_40to60_tr_yEnd);

//   mergePoints(normalData->h_vn_pT_00to10_he3,      var1Data->h_vn_pT_00to10_he3,      var2Data->h_vn_pT_00to10_he3,      v_vn_pT_00to10_he3);
//   mergePoints(normalData->h_vn_pT_10to40_he3,      var1Data->h_vn_pT_10to40_he3,      var2Data->h_vn_pT_10to40_he3,      v_vn_pT_10to40_he3);
//   mergePoints(normalData->h_vn_pT_40to60_he3,      var1Data->h_vn_pT_40to60_he3,      var2Data->h_vn_pT_40to60_he3,      v_vn_pT_40to60_he3);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yMid, var1Data->h_vn_pT_00to10_he3_yMid, var2Data->h_vn_pT_00to10_he3_yMid, v_vn_pT_00to10_he3_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yMid, var1Data->h_vn_pT_10to40_he3_yMid, var2Data->h_vn_pT_10to40_he3_yMid, v_vn_pT_10to40_he3_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yMid, var1Data->h_vn_pT_40to60_he3_yMid, var2Data->h_vn_pT_40to60_he3_yMid, v_vn_pT_40to60_he3_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yFor, var1Data->h_vn_pT_00to10_he3_yFor, var2Data->h_vn_pT_00to10_he3_yFor, v_vn_pT_00to10_he3_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yFor, var1Data->h_vn_pT_10to40_he3_yFor, var2Data->h_vn_pT_10to40_he3_yFor, v_vn_pT_10to40_he3_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yFor, var1Data->h_vn_pT_40to60_he3_yFor, var2Data->h_vn_pT_40to60_he3_yFor, v_vn_pT_40to60_he3_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yExt, var1Data->h_vn_pT_00to10_he3_yExt, var2Data->h_vn_pT_00to10_he3_yExt, v_vn_pT_00to10_he3_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yExt, var1Data->h_vn_pT_10to40_he3_yExt, var2Data->h_vn_pT_10to40_he3_yExt, v_vn_pT_10to40_he3_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yExt, var1Data->h_vn_pT_40to60_he3_yExt, var2Data->h_vn_pT_40to60_he3_yExt, v_vn_pT_40to60_he3_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yEnd, var1Data->h_vn_pT_00to10_he3_yEnd, var2Data->h_vn_pT_00to10_he3_yEnd, v_vn_pT_00to10_he3_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yEnd, var1Data->h_vn_pT_10to40_he3_yEnd, var2Data->h_vn_pT_10to40_he3_yEnd, v_vn_pT_10to40_he3_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yEnd, var1Data->h_vn_pT_40to60_he3_yEnd, var2Data->h_vn_pT_40to60_he3_yEnd, v_vn_pT_40to60_he3_yEnd);

//   mergePoints(normalData->h_vn_pT_00to10_he4,      var1Data->h_vn_pT_00to10_he4,      var2Data->h_vn_pT_00to10_he4,      v_vn_pT_00to10_he4);
//   mergePoints(normalData->h_vn_pT_10to40_he4,      var1Data->h_vn_pT_10to40_he4,      var2Data->h_vn_pT_10to40_he4,      v_vn_pT_10to40_he4);
//   mergePoints(normalData->h_vn_pT_40to60_he4,      var1Data->h_vn_pT_40to60_he4,      var2Data->h_vn_pT_40to60_he4,      v_vn_pT_40to60_he4);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yMid, var1Data->h_vn_pT_00to10_he4_yMid, var2Data->h_vn_pT_00to10_he4_yMid, v_vn_pT_00to10_he4_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yMid, var1Data->h_vn_pT_10to40_he4_yMid, var2Data->h_vn_pT_10to40_he4_yMid, v_vn_pT_10to40_he4_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yMid, var1Data->h_vn_pT_40to60_he4_yMid, var2Data->h_vn_pT_40to60_he4_yMid, v_vn_pT_40to60_he4_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yFor, var1Data->h_vn_pT_00to10_he4_yFor, var2Data->h_vn_pT_00to10_he4_yFor, v_vn_pT_00to10_he4_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yFor, var1Data->h_vn_pT_10to40_he4_yFor, var2Data->h_vn_pT_10to40_he4_yFor, v_vn_pT_10to40_he4_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yFor, var1Data->h_vn_pT_40to60_he4_yFor, var2Data->h_vn_pT_40to60_he4_yFor, v_vn_pT_40to60_he4_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yExt, var1Data->h_vn_pT_00to10_he4_yExt, var2Data->h_vn_pT_00to10_he4_yExt, v_vn_pT_00to10_he4_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yExt, var1Data->h_vn_pT_10to40_he4_yExt, var2Data->h_vn_pT_10to40_he4_yExt, v_vn_pT_10to40_he4_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yExt, var1Data->h_vn_pT_40to60_he4_yExt, var2Data->h_vn_pT_40to60_he4_yExt, v_vn_pT_40to60_he4_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yEnd, var1Data->h_vn_pT_00to10_he4_yEnd, var2Data->h_vn_pT_00to10_he4_yEnd, v_vn_pT_00to10_he4_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yEnd, var1Data->h_vn_pT_10to40_he4_yEnd, var2Data->h_vn_pT_10to40_he4_yEnd, v_vn_pT_10to40_he4_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yEnd, var1Data->h_vn_pT_40to60_he4_yEnd, var2Data->h_vn_pT_40to60_he4_yEnd, v_vn_pT_40to60_he4_yEnd);

}


// Combine three variations with the normal data to get the attributes for systematics
void CompositeData::combine(Variation* normalData, Variation* var1Data, Variation* var2Data, Variation* var3Data)
{
//   mergePoints(normalData->h_vn_pp, var1Data->h_vn_pp, var2Data->h_vn_pp, var3Data->h_vn_pp, v_vn_pp);
//   mergePoints(normalData->h_vn_pm, var1Data->h_vn_pm, var2Data->h_vn_pm, var3Data->h_vn_pm, v_vn_pm);
//   mergePoints(normalData->h_vn_kp, var1Data->h_vn_kp, var2Data->h_vn_kp, var3Data->h_vn_kp, v_vn_kp);
//   mergePoints(normalData->h_vn_km, var1Data->h_vn_km, var2Data->h_vn_km, var3Data->h_vn_km, v_vn_km);
//   mergePoints(normalData->h_vn_pr, var1Data->h_vn_pr, var2Data->h_vn_pr, var3Data->h_vn_pr, v_vn_pr);
//   mergePoints(normalData->h_vn_de, var1Data->h_vn_de, var2Data->h_vn_de, var3Data->h_vn_de, v_vn_de);
//   mergePoints(normalData->h_vn_tr, var1Data->h_vn_tr, var2Data->h_vn_tr, var3Data->h_vn_tr, v_vn_tr);
//   mergePoints(normalData->h_vn_he3, var1Data->h_vn_he3, var2Data->h_vn_he3, var3Data->h_vn_he3, v_vn_he3);
//   mergePoints(normalData->h_vn_he4, var1Data->h_vn_he4, var2Data->h_vn_he4, var3Data->h_vn_he4, v_vn_he4);
  
//   mergePoints(normalData->h_vn_yCM_00to10_pr, var1Data->h_vn_yCM_00to10_pr, var2Data->h_vn_yCM_00to10_pr, var3Data->h_vn_yCM_00to10_pr, v_vn_yCM_00to10_pr);
  mergePoints(normalData->h_vn_yCM_10to40_pr, var1Data->h_vn_yCM_10to40_pr, var2Data->h_vn_yCM_10to40_pr, var3Data->h_vn_yCM_10to40_pr, v_vn_yCM_10to40_pr);
//   mergePoints(normalData->h_vn_yCM_40to60_pr, var1Data->h_vn_yCM_40to60_pr, var2Data->h_vn_yCM_40to60_pr, var3Data->h_vn_yCM_40to60_pr, v_vn_yCM_40to60_pr);
    
//   mergePoints(normalData->h_vn_yCM_00to10_kp, var1Data->h_vn_yCM_00to10_kp, var2Data->h_vn_yCM_00to10_kp, var3Data->h_vn_yCM_00to10_kp, v_vn_yCM_00to10_kp);
  mergePoints(normalData->h_vn_yCM_10to40_kp, var1Data->h_vn_yCM_10to40_kp, var2Data->h_vn_yCM_10to40_kp, var3Data->h_vn_yCM_10to40_kp, v_vn_yCM_10to40_kp);
//   mergePoints(normalData->h_vn_yCM_40to60_kp, var1Data->h_vn_yCM_40to60_kp, var2Data->h_vn_yCM_40to60_kp, var3Data->h_vn_yCM_40to60_kp, v_vn_yCM_40to60_kp);
    
//   mergePoints(normalData->h_vn_yCM_00to10_km, var1Data->h_vn_yCM_00to10_km, var2Data->h_vn_yCM_00to10_km, var3Data->h_vn_yCM_00to10_km, v_vn_yCM_00to10_km);
  mergePoints(normalData->h_vn_yCM_10to40_km, var1Data->h_vn_yCM_10to40_km, var2Data->h_vn_yCM_10to40_km, var3Data->h_vn_yCM_10to40_km, v_vn_yCM_10to40_km);
//   mergePoints(normalData->h_vn_yCM_40to60_km, var1Data->h_vn_yCM_40to60_km, var2Data->h_vn_yCM_40to60_km, var3Data->h_vn_yCM_40to60_km, v_vn_yCM_40to60_km);
    
//   mergePoints(normalData->h_vn_yCM_00to10_pp, var1Data->h_vn_yCM_00to10_pp, var2Data->h_vn_yCM_00to10_pp, var3Data->h_vn_yCM_00to10_pp, v_vn_yCM_00to10_pp);
  mergePoints(normalData->h_vn_yCM_10to40_pp, var1Data->h_vn_yCM_10to40_pp, var2Data->h_vn_yCM_10to40_pp, var3Data->h_vn_yCM_10to40_pp, v_vn_yCM_10to40_pp);
//   mergePoints(normalData->h_vn_yCM_40to60_pp, var1Data->h_vn_yCM_40to60_pp, var2Data->h_vn_yCM_40to60_pp, var3Data->h_vn_yCM_40to60_pp, v_vn_yCM_40to60_pp);
    
//   mergePoints(normalData->h_vn_yCM_00to10_pm, var1Data->h_vn_yCM_00to10_pm, var2Data->h_vn_yCM_00to10_pm, var3Data->h_vn_yCM_00to10_pm, v_vn_yCM_00to10_pm);
  mergePoints(normalData->h_vn_yCM_10to40_pm, var1Data->h_vn_yCM_10to40_pm, var2Data->h_vn_yCM_10to40_pm, var3Data->h_vn_yCM_10to40_pm, v_vn_yCM_10to40_pm);
//   mergePoints(normalData->h_vn_yCM_40to60_pm, var1Data->h_vn_yCM_40to60_pm, var2Data->h_vn_yCM_40to60_pm, var3Data->h_vn_yCM_40to60_pm, v_vn_yCM_40to60_pm);

//   mergePoints(normalData->h_vn_yCM_00to10_pr_symm, var1Data->h_vn_yCM_00to10_pr_symm, var2Data->h_vn_yCM_00to10_pr_symm,
// 	      var3Data->h_vn_yCM_00to10_pr_symm, v_vn_yCM_00to10_pr_symm);
//   mergePoints(normalData->h_vn_yCM_10to40_pr_symm, var1Data->h_vn_yCM_10to40_pr_symm, var2Data->h_vn_yCM_10to40_pr_symm,
// 	      var3Data->h_vn_yCM_10to40_pr_symm, v_vn_yCM_10to40_pr_symm);
//   mergePoints(normalData->h_vn_yCM_40to60_pr_symm, var1Data->h_vn_yCM_40to60_pr_symm, var2Data->h_vn_yCM_40to60_pr_symm,
// 	      var3Data->h_vn_yCM_40to60_pr_symm, v_vn_yCM_40to60_pr_symm);

//   mergePoints(normalData->h_vn_yCM_00to10_de, var1Data->h_vn_yCM_00to10_de, var2Data->h_vn_yCM_00to10_de, var3Data->h_vn_yCM_00to10_de, v_vn_yCM_00to10_de);
  mergePoints(normalData->h_vn_yCM_10to40_de, var1Data->h_vn_yCM_10to40_de, var2Data->h_vn_yCM_10to40_de, var3Data->h_vn_yCM_10to40_de, v_vn_yCM_10to40_de);
//   mergePoints(normalData->h_vn_yCM_40to60_de, var1Data->h_vn_yCM_40to60_de, var2Data->h_vn_yCM_40to60_de, var3Data->h_vn_yCM_40to60_de, v_vn_yCM_40to60_de);
//   mergePoints(normalData->h_vn_yCM_00to10_tr, var1Data->h_vn_yCM_00to10_tr, var2Data->h_vn_yCM_00to10_tr, var3Data->h_vn_yCM_00to10_tr, v_vn_yCM_00to10_tr);
  mergePoints(normalData->h_vn_yCM_10to40_tr, var1Data->h_vn_yCM_10to40_tr, var2Data->h_vn_yCM_10to40_tr, var3Data->h_vn_yCM_10to40_tr, v_vn_yCM_10to40_tr);
//   mergePoints(normalData->h_vn_yCM_40to60_tr, var1Data->h_vn_yCM_40to60_tr, var2Data->h_vn_yCM_40to60_tr, var3Data->h_vn_yCM_40to60_tr, v_vn_yCM_40to60_tr);
//   mergePoints(normalData->h_vn_yCM_00to10_he3, var1Data->h_vn_yCM_00to10_he3, var2Data->h_vn_yCM_00to10_he3, var3Data->h_vn_yCM_00to10_he3, v_vn_yCM_00to10_he3);
//   mergePoints(normalData->h_vn_yCM_10to40_he3, var1Data->h_vn_yCM_10to40_he3, var2Data->h_vn_yCM_10to40_he3, var3Data->h_vn_yCM_10to40_he3, v_vn_yCM_10to40_he3);
//   mergePoints(normalData->h_vn_yCM_40to60_he3, var1Data->h_vn_yCM_40to60_he3, var2Data->h_vn_yCM_40to60_he3, var3Data->h_vn_yCM_40to60_he3, v_vn_yCM_40to60_he3);
//   mergePoints(normalData->h_vn_yCM_00to10_he4, var1Data->h_vn_yCM_00to10_he4, var2Data->h_vn_yCM_00to10_he4, var3Data->h_vn_yCM_00to10_he4, v_vn_yCM_00to10_he4);
//   mergePoints(normalData->h_vn_yCM_10to40_he4, var1Data->h_vn_yCM_10to40_he4, var2Data->h_vn_yCM_10to40_he4, var3Data->h_vn_yCM_10to40_he4, v_vn_yCM_10to40_he4);
//   mergePoints(normalData->h_vn_yCM_40to60_he4, var1Data->h_vn_yCM_40to60_he4, var2Data->h_vn_yCM_40to60_he4, var3Data->h_vn_yCM_40to60_he4, v_vn_yCM_40to60_he4);

//   mergePoints(normalData->h_vn_pT_00to10_pr, var1Data->h_vn_pT_00to10_pr, var2Data->h_vn_pT_00to10_pr, var3Data->h_vn_pT_00to10_pr, v_vn_pT_00to10_pr);
//   mergePoints(normalData->h_vn_pT_10to40_pr, var1Data->h_vn_pT_10to40_pr, var2Data->h_vn_pT_10to40_pr, var3Data->h_vn_pT_10to40_pr, v_vn_pT_10to40_pr);
//   mergePoints(normalData->h_vn_pT_40to60_pr, var1Data->h_vn_pT_40to60_pr, var2Data->h_vn_pT_40to60_pr, var3Data->h_vn_pT_40to60_pr, v_vn_pT_40to60_pr);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yMid, var1Data->h_vn_pT_00to10_pr_yMid, var2Data->h_vn_pT_00to10_pr_yMid, var3Data->h_vn_pT_00to10_pr_yMid, v_vn_pT_00to10_pr_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yMid, var1Data->h_vn_pT_10to40_pr_yMid, var2Data->h_vn_pT_10to40_pr_yMid, var3Data->h_vn_pT_10to40_pr_yMid, v_vn_pT_10to40_pr_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yMid, var1Data->h_vn_pT_40to60_pr_yMid, var2Data->h_vn_pT_40to60_pr_yMid, var3Data->h_vn_pT_40to60_pr_yMid, v_vn_pT_40to60_pr_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yFor, var1Data->h_vn_pT_00to10_pr_yFor, var2Data->h_vn_pT_00to10_pr_yFor, var3Data->h_vn_pT_00to10_pr_yFor, v_vn_pT_00to10_pr_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yFor, var1Data->h_vn_pT_10to40_pr_yFor, var2Data->h_vn_pT_10to40_pr_yFor, var3Data->h_vn_pT_10to40_pr_yFor, v_vn_pT_10to40_pr_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yFor, var1Data->h_vn_pT_40to60_pr_yFor, var2Data->h_vn_pT_40to60_pr_yFor, var3Data->h_vn_pT_40to60_pr_yFor, v_vn_pT_40to60_pr_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yExt, var1Data->h_vn_pT_00to10_pr_yExt, var2Data->h_vn_pT_00to10_pr_yExt, var3Data->h_vn_pT_00to10_pr_yExt, v_vn_pT_00to10_pr_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yExt, var1Data->h_vn_pT_10to40_pr_yExt, var2Data->h_vn_pT_10to40_pr_yExt, var3Data->h_vn_pT_10to40_pr_yExt, v_vn_pT_10to40_pr_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yExt, var1Data->h_vn_pT_40to60_pr_yExt, var2Data->h_vn_pT_40to60_pr_yExt, var3Data->h_vn_pT_40to60_pr_yExt, v_vn_pT_40to60_pr_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yEnd, var1Data->h_vn_pT_00to10_pr_yEnd, var2Data->h_vn_pT_00to10_pr_yEnd, var3Data->h_vn_pT_00to10_pr_yEnd, v_vn_pT_00to10_pr_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yEnd, var1Data->h_vn_pT_10to40_pr_yEnd, var2Data->h_vn_pT_10to40_pr_yEnd, var3Data->h_vn_pT_10to40_pr_yEnd, v_vn_pT_10to40_pr_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yEnd, var1Data->h_vn_pT_40to60_pr_yEnd, var2Data->h_vn_pT_40to60_pr_yEnd, var3Data->h_vn_pT_40to60_pr_yEnd, v_vn_pT_40to60_pr_yEnd);

//   mergePoints(normalData->h_vn_pT_00to10_de, var1Data->h_vn_pT_00to10_de, var2Data->h_vn_pT_00to10_de, var3Data->h_vn_pT_00to10_de, v_vn_pT_00to10_de);
//   mergePoints(normalData->h_vn_pT_10to40_de, var1Data->h_vn_pT_10to40_de, var2Data->h_vn_pT_10to40_de, var3Data->h_vn_pT_10to40_de, v_vn_pT_10to40_de);
//   mergePoints(normalData->h_vn_pT_40to60_de, var1Data->h_vn_pT_40to60_de, var2Data->h_vn_pT_40to60_de, var3Data->h_vn_pT_40to60_de, v_vn_pT_40to60_de);
//   mergePoints(normalData->h_vn_pT_00to10_de_yMid, var1Data->h_vn_pT_00to10_de_yMid, var2Data->h_vn_pT_00to10_de_yMid, var3Data->h_vn_pT_00to10_de_yMid, v_vn_pT_00to10_de_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_de_yMid, var1Data->h_vn_pT_10to40_de_yMid, var2Data->h_vn_pT_10to40_de_yMid, var3Data->h_vn_pT_10to40_de_yMid, v_vn_pT_10to40_de_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_de_yMid, var1Data->h_vn_pT_40to60_de_yMid, var2Data->h_vn_pT_40to60_de_yMid, var3Data->h_vn_pT_40to60_de_yMid, v_vn_pT_40to60_de_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_de_yFor, var1Data->h_vn_pT_00to10_de_yFor, var2Data->h_vn_pT_00to10_de_yFor, var3Data->h_vn_pT_00to10_de_yFor, v_vn_pT_00to10_de_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_de_yFor, var1Data->h_vn_pT_10to40_de_yFor, var2Data->h_vn_pT_10to40_de_yFor, var3Data->h_vn_pT_10to40_de_yFor, v_vn_pT_10to40_de_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_de_yFor, var1Data->h_vn_pT_40to60_de_yFor, var2Data->h_vn_pT_40to60_de_yFor, var3Data->h_vn_pT_40to60_de_yFor, v_vn_pT_40to60_de_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_de_yExt, var1Data->h_vn_pT_00to10_de_yExt, var2Data->h_vn_pT_00to10_de_yExt, var3Data->h_vn_pT_00to10_de_yExt, v_vn_pT_00to10_de_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_de_yExt, var1Data->h_vn_pT_10to40_de_yExt, var2Data->h_vn_pT_10to40_de_yExt, var3Data->h_vn_pT_10to40_de_yExt, v_vn_pT_10to40_de_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_de_yExt, var1Data->h_vn_pT_40to60_de_yExt, var2Data->h_vn_pT_40to60_de_yExt, var3Data->h_vn_pT_40to60_de_yExt, v_vn_pT_40to60_de_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_de_yEnd, var1Data->h_vn_pT_00to10_de_yEnd, var2Data->h_vn_pT_00to10_de_yEnd, var3Data->h_vn_pT_00to10_de_yEnd, v_vn_pT_00to10_de_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_de_yEnd, var1Data->h_vn_pT_10to40_de_yEnd, var2Data->h_vn_pT_10to40_de_yEnd, var3Data->h_vn_pT_10to40_de_yEnd, v_vn_pT_10to40_de_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_de_yEnd, var1Data->h_vn_pT_40to60_de_yEnd, var2Data->h_vn_pT_40to60_de_yEnd, var3Data->h_vn_pT_40to60_de_yEnd, v_vn_pT_40to60_de_yEnd);


//   mergePoints(normalData->h_vn_pT_00to10_tr,      var1Data->h_vn_pT_00to10_tr,      var2Data->h_vn_pT_00to10_tr,      var3Data->h_vn_pT_00to10_tr,      v_vn_pT_00to10_tr);
//   mergePoints(normalData->h_vn_pT_10to40_tr,      var1Data->h_vn_pT_10to40_tr,      var2Data->h_vn_pT_10to40_tr,      var3Data->h_vn_pT_10to40_tr,      v_vn_pT_10to40_tr);
//   mergePoints(normalData->h_vn_pT_40to60_tr,      var1Data->h_vn_pT_40to60_tr,      var2Data->h_vn_pT_40to60_tr,      var3Data->h_vn_pT_40to60_tr,      v_vn_pT_40to60_tr);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yMid, var1Data->h_vn_pT_00to10_tr_yMid, var2Data->h_vn_pT_00to10_tr_yMid, var3Data->h_vn_pT_00to10_tr_yMid, v_vn_pT_00to10_tr_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yMid, var1Data->h_vn_pT_10to40_tr_yMid, var2Data->h_vn_pT_10to40_tr_yMid, var3Data->h_vn_pT_10to40_tr_yMid, v_vn_pT_10to40_tr_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yMid, var1Data->h_vn_pT_40to60_tr_yMid, var2Data->h_vn_pT_40to60_tr_yMid, var3Data->h_vn_pT_40to60_tr_yMid, v_vn_pT_40to60_tr_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yFor, var1Data->h_vn_pT_00to10_tr_yFor, var2Data->h_vn_pT_00to10_tr_yFor, var3Data->h_vn_pT_00to10_tr_yFor, v_vn_pT_00to10_tr_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yFor, var1Data->h_vn_pT_10to40_tr_yFor, var2Data->h_vn_pT_10to40_tr_yFor, var3Data->h_vn_pT_10to40_tr_yFor, v_vn_pT_10to40_tr_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yFor, var1Data->h_vn_pT_40to60_tr_yFor, var2Data->h_vn_pT_40to60_tr_yFor, var3Data->h_vn_pT_40to60_tr_yFor, v_vn_pT_40to60_tr_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yExt, var1Data->h_vn_pT_00to10_tr_yExt, var2Data->h_vn_pT_00to10_tr_yExt, var3Data->h_vn_pT_00to10_tr_yExt, v_vn_pT_00to10_tr_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yExt, var1Data->h_vn_pT_10to40_tr_yExt, var2Data->h_vn_pT_10to40_tr_yExt, var3Data->h_vn_pT_10to40_tr_yExt, v_vn_pT_10to40_tr_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yExt, var1Data->h_vn_pT_40to60_tr_yExt, var2Data->h_vn_pT_40to60_tr_yExt, var3Data->h_vn_pT_40to60_tr_yExt, v_vn_pT_40to60_tr_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yEnd, var1Data->h_vn_pT_00to10_tr_yEnd, var2Data->h_vn_pT_00to10_tr_yEnd, var3Data->h_vn_pT_00to10_tr_yEnd, v_vn_pT_00to10_tr_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yEnd, var1Data->h_vn_pT_10to40_tr_yEnd, var2Data->h_vn_pT_10to40_tr_yEnd, var3Data->h_vn_pT_10to40_tr_yEnd, v_vn_pT_10to40_tr_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yEnd, var1Data->h_vn_pT_40to60_tr_yEnd, var2Data->h_vn_pT_40to60_tr_yEnd, var3Data->h_vn_pT_40to60_tr_yEnd, v_vn_pT_40to60_tr_yEnd);


//   mergePoints(normalData->h_vn_pT_00to10_he3,      var1Data->h_vn_pT_00to10_he3,      var2Data->h_vn_pT_00to10_he3,      var3Data->h_vn_pT_00to10_he3,      v_vn_pT_00to10_he3);
//   mergePoints(normalData->h_vn_pT_10to40_he3,      var1Data->h_vn_pT_10to40_he3,      var2Data->h_vn_pT_10to40_he3,      var3Data->h_vn_pT_10to40_he3,      v_vn_pT_10to40_he3);
//   mergePoints(normalData->h_vn_pT_40to60_he3,      var1Data->h_vn_pT_40to60_he3,      var2Data->h_vn_pT_40to60_he3,      var3Data->h_vn_pT_40to60_he3,      v_vn_pT_40to60_he3);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yMid, var1Data->h_vn_pT_00to10_he3_yMid, var2Data->h_vn_pT_00to10_he3_yMid, var3Data->h_vn_pT_00to10_he3_yMid, v_vn_pT_00to10_he3_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yMid, var1Data->h_vn_pT_10to40_he3_yMid, var2Data->h_vn_pT_10to40_he3_yMid, var3Data->h_vn_pT_10to40_he3_yMid, v_vn_pT_10to40_he3_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yMid, var1Data->h_vn_pT_40to60_he3_yMid, var2Data->h_vn_pT_40to60_he3_yMid, var3Data->h_vn_pT_40to60_he3_yMid, v_vn_pT_40to60_he3_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yFor, var1Data->h_vn_pT_00to10_he3_yFor, var2Data->h_vn_pT_00to10_he3_yFor, var3Data->h_vn_pT_00to10_he3_yFor, v_vn_pT_00to10_he3_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yFor, var1Data->h_vn_pT_10to40_he3_yFor, var2Data->h_vn_pT_10to40_he3_yFor, var3Data->h_vn_pT_10to40_he3_yFor, v_vn_pT_10to40_he3_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yFor, var1Data->h_vn_pT_40to60_he3_yFor, var2Data->h_vn_pT_40to60_he3_yFor, var3Data->h_vn_pT_40to60_he3_yFor, v_vn_pT_40to60_he3_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yExt, var1Data->h_vn_pT_00to10_he3_yExt, var2Data->h_vn_pT_00to10_he3_yExt, var3Data->h_vn_pT_00to10_he3_yExt, v_vn_pT_00to10_he3_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yExt, var1Data->h_vn_pT_10to40_he3_yExt, var2Data->h_vn_pT_10to40_he3_yExt, var3Data->h_vn_pT_10to40_he3_yExt, v_vn_pT_10to40_he3_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yExt, var1Data->h_vn_pT_40to60_he3_yExt, var2Data->h_vn_pT_40to60_he3_yExt, var3Data->h_vn_pT_40to60_he3_yExt, v_vn_pT_40to60_he3_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yEnd, var1Data->h_vn_pT_00to10_he3_yEnd, var2Data->h_vn_pT_00to10_he3_yEnd, var3Data->h_vn_pT_00to10_he3_yEnd, v_vn_pT_00to10_he3_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yEnd, var1Data->h_vn_pT_10to40_he3_yEnd, var2Data->h_vn_pT_10to40_he3_yEnd, var3Data->h_vn_pT_10to40_he3_yEnd, v_vn_pT_10to40_he3_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yEnd, var1Data->h_vn_pT_40to60_he3_yEnd, var2Data->h_vn_pT_40to60_he3_yEnd, var3Data->h_vn_pT_40to60_he3_yEnd, v_vn_pT_40to60_he3_yEnd);

//   mergePoints(normalData->h_vn_pT_00to10_he4,      var1Data->h_vn_pT_00to10_he4,      var2Data->h_vn_pT_00to10_he4,      var3Data->h_vn_pT_00to10_he4,      v_vn_pT_00to10_he4);
//   mergePoints(normalData->h_vn_pT_10to40_he4,      var1Data->h_vn_pT_10to40_he4,      var2Data->h_vn_pT_10to40_he4,      var3Data->h_vn_pT_10to40_he4,      v_vn_pT_10to40_he4);
//   mergePoints(normalData->h_vn_pT_40to60_he4,      var1Data->h_vn_pT_40to60_he4,      var2Data->h_vn_pT_40to60_he4,      var3Data->h_vn_pT_40to60_he4,      v_vn_pT_40to60_he4);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yMid, var1Data->h_vn_pT_00to10_he4_yMid, var2Data->h_vn_pT_00to10_he4_yMid, var3Data->h_vn_pT_00to10_he4_yMid, v_vn_pT_00to10_he4_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yMid, var1Data->h_vn_pT_10to40_he4_yMid, var2Data->h_vn_pT_10to40_he4_yMid, var3Data->h_vn_pT_10to40_he4_yMid, v_vn_pT_10to40_he4_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yMid, var1Data->h_vn_pT_40to60_he4_yMid, var2Data->h_vn_pT_40to60_he4_yMid, var3Data->h_vn_pT_40to60_he4_yMid, v_vn_pT_40to60_he4_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yFor, var1Data->h_vn_pT_00to10_he4_yFor, var2Data->h_vn_pT_00to10_he4_yFor, var3Data->h_vn_pT_00to10_he4_yFor, v_vn_pT_00to10_he4_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yFor, var1Data->h_vn_pT_10to40_he4_yFor, var2Data->h_vn_pT_10to40_he4_yFor, var3Data->h_vn_pT_10to40_he4_yFor, v_vn_pT_10to40_he4_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yFor, var1Data->h_vn_pT_40to60_he4_yFor, var2Data->h_vn_pT_40to60_he4_yFor, var3Data->h_vn_pT_40to60_he4_yFor, v_vn_pT_40to60_he4_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yExt, var1Data->h_vn_pT_00to10_he4_yExt, var2Data->h_vn_pT_00to10_he4_yExt, var3Data->h_vn_pT_00to10_he4_yExt, v_vn_pT_00to10_he4_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yExt, var1Data->h_vn_pT_10to40_he4_yExt, var2Data->h_vn_pT_10to40_he4_yExt, var3Data->h_vn_pT_10to40_he4_yExt, v_vn_pT_10to40_he4_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yExt, var1Data->h_vn_pT_40to60_he4_yExt, var2Data->h_vn_pT_40to60_he4_yExt, var3Data->h_vn_pT_40to60_he4_yExt, v_vn_pT_40to60_he4_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yEnd, var1Data->h_vn_pT_00to10_he4_yEnd, var2Data->h_vn_pT_00to10_he4_yEnd, var3Data->h_vn_pT_00to10_he4_yEnd, v_vn_pT_00to10_he4_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yEnd, var1Data->h_vn_pT_10to40_he4_yEnd, var2Data->h_vn_pT_10to40_he4_yEnd, var3Data->h_vn_pT_10to40_he4_yEnd, v_vn_pT_10to40_he4_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yEnd, var1Data->h_vn_pT_40to60_he4_yEnd, var2Data->h_vn_pT_40to60_he4_yEnd, var3Data->h_vn_pT_40to60_he4_yEnd, v_vn_pT_40to60_he4_yEnd);

}



// Combine four variations with the normal data to get the attributes for systematics
void CompositeData::combine(Variation* normalData, Variation* var1Data, Variation* var2Data, Variation* var3Data, Variation* var4Data)
{
//   mergePoints(normalData->h_vn_pp, var1Data->h_vn_pp, var2Data->h_vn_pp, var3Data->h_vn_pp, var4Data->h_vn_pp, v_vn_pp);
//   mergePoints(normalData->h_vn_pm, var1Data->h_vn_pm, var2Data->h_vn_pm, var3Data->h_vn_pm, var4Data->h_vn_pm, v_vn_pm);
//   mergePoints(normalData->h_vn_kp, var1Data->h_vn_kp, var2Data->h_vn_kp, var3Data->h_vn_kp, var4Data->h_vn_kp, v_vn_kp);
//   mergePoints(normalData->h_vn_km, var1Data->h_vn_km, var2Data->h_vn_km, var3Data->h_vn_km, var4Data->h_vn_km, v_vn_km);
//   mergePoints(normalData->h_vn_pr, var1Data->h_vn_pr, var2Data->h_vn_pr, var3Data->h_vn_pr, var4Data->h_vn_pr, v_vn_pr);
//   mergePoints(normalData->h_vn_de, var1Data->h_vn_de, var2Data->h_vn_de, var3Data->h_vn_de, var4Data->h_vn_de, v_vn_de);
//   mergePoints(normalData->h_vn_tr, var1Data->h_vn_tr, var2Data->h_vn_tr, var3Data->h_vn_tr, var4Data->h_vn_tr, v_vn_tr);
//   mergePoints(normalData->h_vn_he3, var1Data->h_vn_he3, var2Data->h_vn_he3, var3Data->h_vn_he3, var4Data->h_vn_he3, v_vn_he3);
//   mergePoints(normalData->h_vn_he4, var1Data->h_vn_he4, var2Data->h_vn_he4, var3Data->h_vn_he4, var4Data->h_vn_he4, v_vn_he4);

//   mergePoints(normalData->h_vn_yCM_00to10_pr, var1Data->h_vn_yCM_00to10_pr, var2Data->h_vn_yCM_00to10_pr, var3Data->h_vn_yCM_00to10_pr, var4Data->h_vn_yCM_00to10_pr, v_vn_yCM_00to10_pr);
  mergePoints(normalData->h_vn_yCM_10to40_pr, var1Data->h_vn_yCM_10to40_pr, var2Data->h_vn_yCM_10to40_pr, var3Data->h_vn_yCM_10to40_pr, var4Data->h_vn_yCM_10to40_pr, v_vn_yCM_10to40_pr);
//   mergePoints(normalData->h_vn_yCM_40to60_pr, var1Data->h_vn_yCM_40to60_pr, var2Data->h_vn_yCM_40to60_pr, var3Data->h_vn_yCM_40to60_pr, var4Data->h_vn_yCM_40to60_pr, v_vn_yCM_40to60_pr);
    
//   mergePoints(normalData->h_vn_yCM_00to10_kp, var1Data->h_vn_yCM_00to10_kp, var2Data->h_vn_yCM_00to10_kp, var3Data->h_vn_yCM_00to10_kp, var4Data->h_vn_yCM_00to10_kp, v_vn_yCM_00to10_kp);
  mergePoints(normalData->h_vn_yCM_10to40_kp, var1Data->h_vn_yCM_10to40_kp, var2Data->h_vn_yCM_10to40_kp, var3Data->h_vn_yCM_10to40_kp, var4Data->h_vn_yCM_10to40_kp, v_vn_yCM_10to40_kp);
//   mergePoints(normalData->h_vn_yCM_40to60_kp, var1Data->h_vn_yCM_40to60_kp, var2Data->h_vn_yCM_40to60_kp, var3Data->h_vn_yCM_40to60_kp, var4Data->h_vn_yCM_40to60_kp, v_vn_yCM_40to60_kp);
    
//   mergePoints(normalData->h_vn_yCM_00to10_km, var1Data->h_vn_yCM_00to10_km, var2Data->h_vn_yCM_00to10_km, var3Data->h_vn_yCM_00to10_km, var4Data->h_vn_yCM_00to10_km, v_vn_yCM_00to10_km);
  mergePoints(normalData->h_vn_yCM_10to40_km, var1Data->h_vn_yCM_10to40_km, var2Data->h_vn_yCM_10to40_km, var3Data->h_vn_yCM_10to40_km, var4Data->h_vn_yCM_10to40_km, v_vn_yCM_10to40_km);
//   mergePoints(normalData->h_vn_yCM_40to60_km, var1Data->h_vn_yCM_40to60_km, var2Data->h_vn_yCM_40to60_km, var3Data->h_vn_yCM_40to60_km, var4Data->h_vn_yCM_40to60_km, v_vn_yCM_40to60_km);
    
//   mergePoints(normalData->h_vn_yCM_00to10_pp, var1Data->h_vn_yCM_00to10_pp, var2Data->h_vn_yCM_00to10_pp, var3Data->h_vn_yCM_00to10_pp, var4Data->h_vn_yCM_00to10_pp, v_vn_yCM_00to10_pp);
  mergePoints(normalData->h_vn_yCM_10to40_pp, var1Data->h_vn_yCM_10to40_pp, var2Data->h_vn_yCM_10to40_pp, var3Data->h_vn_yCM_10to40_pp, var4Data->h_vn_yCM_10to40_pp, v_vn_yCM_10to40_pp);
//   mergePoints(normalData->h_vn_yCM_40to60_pp, var1Data->h_vn_yCM_40to60_pp, var2Data->h_vn_yCM_40to60_pp, var3Data->h_vn_yCM_40to60_pp, var4Data->h_vn_yCM_40to60_pp, v_vn_yCM_40to60_pp);
    
//   mergePoints(normalData->h_vn_yCM_00to10_pm, var1Data->h_vn_yCM_00to10_pm, var2Data->h_vn_yCM_00to10_pm, var3Data->h_vn_yCM_00to10_pm, var4Data->h_vn_yCM_00to10_pm, v_vn_yCM_00to10_pm);
  mergePoints(normalData->h_vn_yCM_10to40_pm, var1Data->h_vn_yCM_10to40_pm, var2Data->h_vn_yCM_10to40_pm, var3Data->h_vn_yCM_10to40_pm, var4Data->h_vn_yCM_10to40_pm, v_vn_yCM_10to40_pm);
//   mergePoints(normalData->h_vn_yCM_40to60_pm, var1Data->h_vn_yCM_40to60_pm, var2Data->h_vn_yCM_40to60_pm, var3Data->h_vn_yCM_40to60_pm, var4Data->h_vn_yCM_40to60_pm, v_vn_yCM_40to60_pm);

//   mergePoints(normalData->h_vn_yCM_00to10_pr_symm, var1Data->h_vn_yCM_00to10_pr_symm, var2Data->h_vn_yCM_00to10_pr_symm, var3Data->h_vn_yCM_00to10_pr_symm, var4Data->h_vn_yCM_00to10_pr_symm, v_vn_yCM_00to10_pr_symm);
//   mergePoints(normalData->h_vn_yCM_10to40_pr_symm, var1Data->h_vn_yCM_10to40_pr_symm, var2Data->h_vn_yCM_10to40_pr_symm, var3Data->h_vn_yCM_10to40_pr_symm, var4Data->h_vn_yCM_10to40_pr_symm, v_vn_yCM_10to40_pr_symm);
//   mergePoints(normalData->h_vn_yCM_40to60_pr_symm, var1Data->h_vn_yCM_40to60_pr_symm, var2Data->h_vn_yCM_40to60_pr_symm, var3Data->h_vn_yCM_40to60_pr_symm, var4Data->h_vn_yCM_40to60_pr_symm, v_vn_yCM_40to60_pr_symm);

//   mergePoints(normalData->h_vn_yCM_00to10_de, var1Data->h_vn_yCM_00to10_de, var2Data->h_vn_yCM_00to10_de, var3Data->h_vn_yCM_00to10_de, var4Data->h_vn_yCM_00to10_de, v_vn_yCM_00to10_de);
  mergePoints(normalData->h_vn_yCM_10to40_de, var1Data->h_vn_yCM_10to40_de, var2Data->h_vn_yCM_10to40_de, var3Data->h_vn_yCM_10to40_de, var4Data->h_vn_yCM_10to40_de, v_vn_yCM_10to40_de);
//   mergePoints(normalData->h_vn_yCM_40to60_de, var1Data->h_vn_yCM_40to60_de, var2Data->h_vn_yCM_40to60_de, var3Data->h_vn_yCM_40to60_de, var4Data->h_vn_yCM_40to60_de, v_vn_yCM_40to60_de);
//   mergePoints(normalData->h_vn_yCM_00to10_tr, var1Data->h_vn_yCM_00to10_tr, var2Data->h_vn_yCM_00to10_tr, var3Data->h_vn_yCM_00to10_tr, var4Data->h_vn_yCM_00to10_tr, v_vn_yCM_00to10_tr);
  mergePoints(normalData->h_vn_yCM_10to40_tr, var1Data->h_vn_yCM_10to40_tr, var2Data->h_vn_yCM_10to40_tr, var3Data->h_vn_yCM_10to40_tr, var4Data->h_vn_yCM_10to40_tr, v_vn_yCM_10to40_tr);
//   mergePoints(normalData->h_vn_yCM_40to60_tr, var1Data->h_vn_yCM_40to60_tr, var2Data->h_vn_yCM_40to60_tr, var3Data->h_vn_yCM_40to60_tr, var4Data->h_vn_yCM_40to60_tr, v_vn_yCM_40to60_tr);
//   mergePoints(normalData->h_vn_yCM_00to10_he3, var1Data->h_vn_yCM_00to10_he3, var2Data->h_vn_yCM_00to10_he3, var3Data->h_vn_yCM_00to10_he3, var4Data->h_vn_yCM_00to10_he3, v_vn_yCM_00to10_he3);
//   mergePoints(normalData->h_vn_yCM_10to40_he3, var1Data->h_vn_yCM_10to40_he3, var2Data->h_vn_yCM_10to40_he3, var3Data->h_vn_yCM_10to40_he3, var4Data->h_vn_yCM_10to40_he3, v_vn_yCM_10to40_he3);
//   mergePoints(normalData->h_vn_yCM_40to60_he3, var1Data->h_vn_yCM_40to60_he3, var2Data->h_vn_yCM_40to60_he3, var3Data->h_vn_yCM_40to60_he3, var4Data->h_vn_yCM_40to60_he3, v_vn_yCM_40to60_he3);
//   mergePoints(normalData->h_vn_yCM_00to10_he4, var1Data->h_vn_yCM_00to10_he4, var2Data->h_vn_yCM_00to10_he4, var3Data->h_vn_yCM_00to10_he4, var4Data->h_vn_yCM_00to10_he4, v_vn_yCM_00to10_he4);
//   mergePoints(normalData->h_vn_yCM_10to40_he4, var1Data->h_vn_yCM_10to40_he4, var2Data->h_vn_yCM_10to40_he4, var3Data->h_vn_yCM_10to40_he4, var4Data->h_vn_yCM_10to40_he4, v_vn_yCM_10to40_he4);
//   mergePoints(normalData->h_vn_yCM_40to60_he4, var1Data->h_vn_yCM_40to60_he4, var2Data->h_vn_yCM_40to60_he4, var3Data->h_vn_yCM_40to60_he4, var4Data->h_vn_yCM_40to60_he4, v_vn_yCM_40to60_he4);

//   mergePoints(normalData->h_vn_pT_00to10_pr, var1Data->h_vn_pT_00to10_pr, var2Data->h_vn_pT_00to10_pr, var3Data->h_vn_pT_00to10_pr, var4Data->h_vn_pT_00to10_pr, v_vn_pT_00to10_pr);
//   mergePoints(normalData->h_vn_pT_10to40_pr, var1Data->h_vn_pT_10to40_pr, var2Data->h_vn_pT_10to40_pr, var3Data->h_vn_pT_10to40_pr, var4Data->h_vn_pT_10to40_pr, v_vn_pT_10to40_pr);
//   mergePoints(normalData->h_vn_pT_40to60_pr, var1Data->h_vn_pT_40to60_pr, var2Data->h_vn_pT_40to60_pr, var3Data->h_vn_pT_40to60_pr, var4Data->h_vn_pT_40to60_pr, v_vn_pT_40to60_pr);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yMid, var1Data->h_vn_pT_00to10_pr_yMid, var2Data->h_vn_pT_00to10_pr_yMid, var3Data->h_vn_pT_00to10_pr_yMid, var4Data->h_vn_pT_00to10_pr_yMid, v_vn_pT_00to10_pr_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yMid, var1Data->h_vn_pT_10to40_pr_yMid, var2Data->h_vn_pT_10to40_pr_yMid, var3Data->h_vn_pT_10to40_pr_yMid, var4Data->h_vn_pT_10to40_pr_yMid, v_vn_pT_10to40_pr_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yMid, var1Data->h_vn_pT_40to60_pr_yMid, var2Data->h_vn_pT_40to60_pr_yMid, var3Data->h_vn_pT_40to60_pr_yMid, var4Data->h_vn_pT_40to60_pr_yMid, v_vn_pT_40to60_pr_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yFor, var1Data->h_vn_pT_00to10_pr_yFor, var2Data->h_vn_pT_00to10_pr_yFor, var3Data->h_vn_pT_00to10_pr_yFor, var4Data->h_vn_pT_00to10_pr_yFor, v_vn_pT_00to10_pr_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yFor, var1Data->h_vn_pT_10to40_pr_yFor, var2Data->h_vn_pT_10to40_pr_yFor, var3Data->h_vn_pT_10to40_pr_yFor, var4Data->h_vn_pT_10to40_pr_yFor, v_vn_pT_10to40_pr_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yFor, var1Data->h_vn_pT_40to60_pr_yFor, var2Data->h_vn_pT_40to60_pr_yFor, var3Data->h_vn_pT_40to60_pr_yFor, var4Data->h_vn_pT_40to60_pr_yFor, v_vn_pT_40to60_pr_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yExt, var1Data->h_vn_pT_00to10_pr_yExt, var2Data->h_vn_pT_00to10_pr_yExt, var3Data->h_vn_pT_00to10_pr_yExt, var4Data->h_vn_pT_00to10_pr_yExt, v_vn_pT_00to10_pr_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yExt, var1Data->h_vn_pT_10to40_pr_yExt, var2Data->h_vn_pT_10to40_pr_yExt, var3Data->h_vn_pT_10to40_pr_yExt, var4Data->h_vn_pT_10to40_pr_yExt, v_vn_pT_10to40_pr_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yExt, var1Data->h_vn_pT_40to60_pr_yExt, var2Data->h_vn_pT_40to60_pr_yExt, var3Data->h_vn_pT_40to60_pr_yExt, var4Data->h_vn_pT_40to60_pr_yExt, v_vn_pT_40to60_pr_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_pr_yEnd, var1Data->h_vn_pT_00to10_pr_yEnd, var2Data->h_vn_pT_00to10_pr_yEnd, var3Data->h_vn_pT_00to10_pr_yEnd, var4Data->h_vn_pT_00to10_pr_yEnd, v_vn_pT_00to10_pr_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_pr_yEnd, var1Data->h_vn_pT_10to40_pr_yEnd, var2Data->h_vn_pT_10to40_pr_yEnd, var3Data->h_vn_pT_10to40_pr_yEnd, var4Data->h_vn_pT_10to40_pr_yEnd, v_vn_pT_10to40_pr_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_pr_yEnd, var1Data->h_vn_pT_40to60_pr_yEnd, var2Data->h_vn_pT_40to60_pr_yEnd, var3Data->h_vn_pT_40to60_pr_yEnd, var4Data->h_vn_pT_40to60_pr_yEnd, v_vn_pT_40to60_pr_yEnd);


//   mergePoints(normalData->h_vn_pT_00to10_de, var1Data->h_vn_pT_00to10_de, var2Data->h_vn_pT_00to10_de, var3Data->h_vn_pT_00to10_de, var4Data->h_vn_pT_00to10_de, v_vn_pT_00to10_de);
//   mergePoints(normalData->h_vn_pT_10to40_de, var1Data->h_vn_pT_10to40_de, var2Data->h_vn_pT_10to40_de, var3Data->h_vn_pT_10to40_de, var4Data->h_vn_pT_10to40_de, v_vn_pT_10to40_de);
//   mergePoints(normalData->h_vn_pT_40to60_de, var1Data->h_vn_pT_40to60_de, var2Data->h_vn_pT_40to60_de, var3Data->h_vn_pT_40to60_de, var4Data->h_vn_pT_40to60_de, v_vn_pT_40to60_de);
//   mergePoints(normalData->h_vn_pT_00to10_de_yMid, var1Data->h_vn_pT_00to10_de_yMid, var2Data->h_vn_pT_00to10_de_yMid, var3Data->h_vn_pT_00to10_de_yMid, var4Data->h_vn_pT_00to10_de_yMid, v_vn_pT_00to10_de_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_de_yMid, var1Data->h_vn_pT_10to40_de_yMid, var2Data->h_vn_pT_10to40_de_yMid, var3Data->h_vn_pT_10to40_de_yMid, var4Data->h_vn_pT_10to40_de_yMid, v_vn_pT_10to40_de_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_de_yMid, var1Data->h_vn_pT_40to60_de_yMid, var2Data->h_vn_pT_40to60_de_yMid, var3Data->h_vn_pT_40to60_de_yMid, var4Data->h_vn_pT_40to60_de_yMid, v_vn_pT_40to60_de_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_de_yFor, var1Data->h_vn_pT_00to10_de_yFor, var2Data->h_vn_pT_00to10_de_yFor, var3Data->h_vn_pT_00to10_de_yFor, var4Data->h_vn_pT_00to10_de_yFor, v_vn_pT_00to10_de_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_de_yFor, var1Data->h_vn_pT_10to40_de_yFor, var2Data->h_vn_pT_10to40_de_yFor, var3Data->h_vn_pT_10to40_de_yFor, var4Data->h_vn_pT_10to40_de_yFor, v_vn_pT_10to40_de_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_de_yFor, var1Data->h_vn_pT_40to60_de_yFor, var2Data->h_vn_pT_40to60_de_yFor, var3Data->h_vn_pT_40to60_de_yFor, var4Data->h_vn_pT_40to60_de_yFor, v_vn_pT_40to60_de_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_de_yExt, var1Data->h_vn_pT_00to10_de_yExt, var2Data->h_vn_pT_00to10_de_yExt, var3Data->h_vn_pT_00to10_de_yExt, var4Data->h_vn_pT_00to10_de_yExt, v_vn_pT_00to10_de_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_de_yExt, var1Data->h_vn_pT_10to40_de_yExt, var2Data->h_vn_pT_10to40_de_yExt, var3Data->h_vn_pT_10to40_de_yExt, var4Data->h_vn_pT_10to40_de_yExt, v_vn_pT_10to40_de_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_de_yExt, var1Data->h_vn_pT_40to60_de_yExt, var2Data->h_vn_pT_40to60_de_yExt, var3Data->h_vn_pT_40to60_de_yExt, var4Data->h_vn_pT_40to60_de_yExt, v_vn_pT_40to60_de_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_de_yEnd, var1Data->h_vn_pT_00to10_de_yEnd, var2Data->h_vn_pT_00to10_de_yEnd, var3Data->h_vn_pT_00to10_de_yEnd, var4Data->h_vn_pT_00to10_de_yEnd, v_vn_pT_00to10_de_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_de_yEnd, var1Data->h_vn_pT_10to40_de_yEnd, var2Data->h_vn_pT_10to40_de_yEnd, var3Data->h_vn_pT_10to40_de_yEnd, var4Data->h_vn_pT_10to40_de_yEnd, v_vn_pT_10to40_de_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_de_yEnd, var1Data->h_vn_pT_40to60_de_yEnd, var2Data->h_vn_pT_40to60_de_yEnd, var3Data->h_vn_pT_40to60_de_yEnd, var4Data->h_vn_pT_40to60_de_yEnd, v_vn_pT_40to60_de_yEnd);


//   mergePoints(normalData->h_vn_pT_00to10_tr,      var1Data->h_vn_pT_00to10_tr,      var2Data->h_vn_pT_00to10_tr,      var3Data->h_vn_pT_00to10_tr,      var4Data->h_vn_pT_00to10_tr,      v_vn_pT_00to10_tr);
//   mergePoints(normalData->h_vn_pT_10to40_tr,      var1Data->h_vn_pT_10to40_tr,      var2Data->h_vn_pT_10to40_tr,      var3Data->h_vn_pT_10to40_tr,      var4Data->h_vn_pT_10to40_tr,      v_vn_pT_10to40_tr);
//   mergePoints(normalData->h_vn_pT_40to60_tr,      var1Data->h_vn_pT_40to60_tr,      var2Data->h_vn_pT_40to60_tr,      var3Data->h_vn_pT_40to60_tr,      var4Data->h_vn_pT_40to60_tr,      v_vn_pT_40to60_tr);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yMid, var1Data->h_vn_pT_00to10_tr_yMid, var2Data->h_vn_pT_00to10_tr_yMid, var3Data->h_vn_pT_00to10_tr_yMid, var4Data->h_vn_pT_00to10_tr_yMid, v_vn_pT_00to10_tr_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yMid, var1Data->h_vn_pT_10to40_tr_yMid, var2Data->h_vn_pT_10to40_tr_yMid, var3Data->h_vn_pT_10to40_tr_yMid, var4Data->h_vn_pT_10to40_tr_yMid, v_vn_pT_10to40_tr_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yMid, var1Data->h_vn_pT_40to60_tr_yMid, var2Data->h_vn_pT_40to60_tr_yMid, var3Data->h_vn_pT_40to60_tr_yMid, var4Data->h_vn_pT_40to60_tr_yMid, v_vn_pT_40to60_tr_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yFor, var1Data->h_vn_pT_00to10_tr_yFor, var2Data->h_vn_pT_00to10_tr_yFor, var3Data->h_vn_pT_00to10_tr_yFor, var4Data->h_vn_pT_00to10_tr_yFor, v_vn_pT_00to10_tr_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yFor, var1Data->h_vn_pT_10to40_tr_yFor, var2Data->h_vn_pT_10to40_tr_yFor, var3Data->h_vn_pT_10to40_tr_yFor, var4Data->h_vn_pT_10to40_tr_yFor, v_vn_pT_10to40_tr_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yFor, var1Data->h_vn_pT_40to60_tr_yFor, var2Data->h_vn_pT_40to60_tr_yFor, var3Data->h_vn_pT_40to60_tr_yFor, var4Data->h_vn_pT_40to60_tr_yFor, v_vn_pT_40to60_tr_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yExt, var1Data->h_vn_pT_00to10_tr_yExt, var2Data->h_vn_pT_00to10_tr_yExt, var3Data->h_vn_pT_00to10_tr_yExt, var4Data->h_vn_pT_00to10_tr_yExt, v_vn_pT_00to10_tr_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yExt, var1Data->h_vn_pT_10to40_tr_yExt, var2Data->h_vn_pT_10to40_tr_yExt, var3Data->h_vn_pT_10to40_tr_yExt, var4Data->h_vn_pT_10to40_tr_yExt, v_vn_pT_10to40_tr_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yExt, var1Data->h_vn_pT_40to60_tr_yExt, var2Data->h_vn_pT_40to60_tr_yExt, var3Data->h_vn_pT_40to60_tr_yExt, var4Data->h_vn_pT_40to60_tr_yExt, v_vn_pT_40to60_tr_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_tr_yEnd, var1Data->h_vn_pT_00to10_tr_yEnd, var2Data->h_vn_pT_00to10_tr_yEnd, var3Data->h_vn_pT_00to10_tr_yEnd, var4Data->h_vn_pT_00to10_tr_yEnd, v_vn_pT_00to10_tr_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_tr_yEnd, var1Data->h_vn_pT_10to40_tr_yEnd, var2Data->h_vn_pT_10to40_tr_yEnd, var3Data->h_vn_pT_10to40_tr_yEnd, var4Data->h_vn_pT_10to40_tr_yEnd, v_vn_pT_10to40_tr_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_tr_yEnd, var1Data->h_vn_pT_40to60_tr_yEnd, var2Data->h_vn_pT_40to60_tr_yEnd, var3Data->h_vn_pT_40to60_tr_yEnd, var4Data->h_vn_pT_40to60_tr_yEnd, v_vn_pT_40to60_tr_yEnd);


//   mergePoints(normalData->h_vn_pT_00to10_he3,      var1Data->h_vn_pT_00to10_he3,      var2Data->h_vn_pT_00to10_he3,      var3Data->h_vn_pT_00to10_he3,      var4Data->h_vn_pT_00to10_he3,      v_vn_pT_00to10_he3);
//   mergePoints(normalData->h_vn_pT_10to40_he3,      var1Data->h_vn_pT_10to40_he3,      var2Data->h_vn_pT_10to40_he3,      var3Data->h_vn_pT_10to40_he3,      var4Data->h_vn_pT_10to40_he3,      v_vn_pT_10to40_he3);
//   mergePoints(normalData->h_vn_pT_40to60_he3,      var1Data->h_vn_pT_40to60_he3,      var2Data->h_vn_pT_40to60_he3,      var3Data->h_vn_pT_40to60_he3,      var4Data->h_vn_pT_40to60_he3,      v_vn_pT_40to60_he3);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yMid, var1Data->h_vn_pT_00to10_he3_yMid, var2Data->h_vn_pT_00to10_he3_yMid, var3Data->h_vn_pT_00to10_he3_yMid, var4Data->h_vn_pT_00to10_he3_yMid, v_vn_pT_00to10_he3_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yMid, var1Data->h_vn_pT_10to40_he3_yMid, var2Data->h_vn_pT_10to40_he3_yMid, var3Data->h_vn_pT_10to40_he3_yMid, var4Data->h_vn_pT_10to40_he3_yMid, v_vn_pT_10to40_he3_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yMid, var1Data->h_vn_pT_40to60_he3_yMid, var2Data->h_vn_pT_40to60_he3_yMid, var3Data->h_vn_pT_40to60_he3_yMid, var4Data->h_vn_pT_40to60_he3_yMid, v_vn_pT_40to60_he3_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yFor, var1Data->h_vn_pT_00to10_he3_yFor, var2Data->h_vn_pT_00to10_he3_yFor, var3Data->h_vn_pT_00to10_he3_yFor, var4Data->h_vn_pT_00to10_he3_yFor, v_vn_pT_00to10_he3_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yFor, var1Data->h_vn_pT_10to40_he3_yFor, var2Data->h_vn_pT_10to40_he3_yFor, var3Data->h_vn_pT_10to40_he3_yFor, var4Data->h_vn_pT_10to40_he3_yFor, v_vn_pT_10to40_he3_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yFor, var1Data->h_vn_pT_40to60_he3_yFor, var2Data->h_vn_pT_40to60_he3_yFor, var3Data->h_vn_pT_40to60_he3_yFor, var4Data->h_vn_pT_40to60_he3_yFor, v_vn_pT_40to60_he3_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yExt, var1Data->h_vn_pT_00to10_he3_yExt, var2Data->h_vn_pT_00to10_he3_yExt, var3Data->h_vn_pT_00to10_he3_yExt, var4Data->h_vn_pT_00to10_he3_yExt, v_vn_pT_00to10_he3_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yExt, var1Data->h_vn_pT_10to40_he3_yExt, var2Data->h_vn_pT_10to40_he3_yExt, var3Data->h_vn_pT_10to40_he3_yExt, var4Data->h_vn_pT_10to40_he3_yExt, v_vn_pT_10to40_he3_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yExt, var1Data->h_vn_pT_40to60_he3_yExt, var2Data->h_vn_pT_40to60_he3_yExt, var3Data->h_vn_pT_40to60_he3_yExt, var4Data->h_vn_pT_40to60_he3_yExt, v_vn_pT_40to60_he3_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_he3_yEnd, var1Data->h_vn_pT_00to10_he3_yEnd, var2Data->h_vn_pT_00to10_he3_yEnd, var3Data->h_vn_pT_00to10_he3_yEnd, var4Data->h_vn_pT_00to10_he3_yEnd, v_vn_pT_00to10_he3_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_he3_yEnd, var1Data->h_vn_pT_10to40_he3_yEnd, var2Data->h_vn_pT_10to40_he3_yEnd, var3Data->h_vn_pT_10to40_he3_yEnd, var4Data->h_vn_pT_10to40_he3_yEnd, v_vn_pT_10to40_he3_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_he3_yEnd, var1Data->h_vn_pT_40to60_he3_yEnd, var2Data->h_vn_pT_40to60_he3_yEnd, var3Data->h_vn_pT_40to60_he3_yEnd, var4Data->h_vn_pT_40to60_he3_yEnd, v_vn_pT_40to60_he3_yEnd);

//   mergePoints(normalData->h_vn_pT_00to10_he4,      var1Data->h_vn_pT_00to10_he4,      var2Data->h_vn_pT_00to10_he4,      var3Data->h_vn_pT_00to10_he4,      var4Data->h_vn_pT_00to10_he4,      v_vn_pT_00to10_he4);
//   mergePoints(normalData->h_vn_pT_10to40_he4,      var1Data->h_vn_pT_10to40_he4,      var2Data->h_vn_pT_10to40_he4,      var3Data->h_vn_pT_10to40_he4,      var4Data->h_vn_pT_10to40_he4,      v_vn_pT_10to40_he4);
//   mergePoints(normalData->h_vn_pT_40to60_he4,      var1Data->h_vn_pT_40to60_he4,      var2Data->h_vn_pT_40to60_he4,      var3Data->h_vn_pT_40to60_he4,      var4Data->h_vn_pT_40to60_he4,      v_vn_pT_40to60_he4);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yMid, var1Data->h_vn_pT_00to10_he4_yMid, var2Data->h_vn_pT_00to10_he4_yMid, var3Data->h_vn_pT_00to10_he4_yMid, var4Data->h_vn_pT_00to10_he4_yMid, v_vn_pT_00to10_he4_yMid);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yMid, var1Data->h_vn_pT_10to40_he4_yMid, var2Data->h_vn_pT_10to40_he4_yMid, var3Data->h_vn_pT_10to40_he4_yMid, var4Data->h_vn_pT_10to40_he4_yMid, v_vn_pT_10to40_he4_yMid);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yMid, var1Data->h_vn_pT_40to60_he4_yMid, var2Data->h_vn_pT_40to60_he4_yMid, var3Data->h_vn_pT_40to60_he4_yMid, var4Data->h_vn_pT_40to60_he4_yMid, v_vn_pT_40to60_he4_yMid);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yFor, var1Data->h_vn_pT_00to10_he4_yFor, var2Data->h_vn_pT_00to10_he4_yFor, var3Data->h_vn_pT_00to10_he4_yFor, var4Data->h_vn_pT_00to10_he4_yFor, v_vn_pT_00to10_he4_yFor);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yFor, var1Data->h_vn_pT_10to40_he4_yFor, var2Data->h_vn_pT_10to40_he4_yFor, var3Data->h_vn_pT_10to40_he4_yFor, var4Data->h_vn_pT_10to40_he4_yFor, v_vn_pT_10to40_he4_yFor);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yFor, var1Data->h_vn_pT_40to60_he4_yFor, var2Data->h_vn_pT_40to60_he4_yFor, var3Data->h_vn_pT_40to60_he4_yFor, var4Data->h_vn_pT_40to60_he4_yFor, v_vn_pT_40to60_he4_yFor);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yExt, var1Data->h_vn_pT_00to10_he4_yExt, var2Data->h_vn_pT_00to10_he4_yExt, var3Data->h_vn_pT_00to10_he4_yExt, var4Data->h_vn_pT_00to10_he4_yExt, v_vn_pT_00to10_he4_yExt);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yExt, var1Data->h_vn_pT_10to40_he4_yExt, var2Data->h_vn_pT_10to40_he4_yExt, var3Data->h_vn_pT_10to40_he4_yExt, var4Data->h_vn_pT_10to40_he4_yExt, v_vn_pT_10to40_he4_yExt);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yExt, var1Data->h_vn_pT_40to60_he4_yExt, var2Data->h_vn_pT_40to60_he4_yExt, var3Data->h_vn_pT_40to60_he4_yExt, var4Data->h_vn_pT_40to60_he4_yExt, v_vn_pT_40to60_he4_yExt);
//   mergePoints(normalData->h_vn_pT_00to10_he4_yEnd, var1Data->h_vn_pT_00to10_he4_yEnd, var2Data->h_vn_pT_00to10_he4_yEnd, var3Data->h_vn_pT_00to10_he4_yEnd, var4Data->h_vn_pT_00to10_he4_yEnd, v_vn_pT_00to10_he4_yEnd);
//   mergePoints(normalData->h_vn_pT_10to40_he4_yEnd, var1Data->h_vn_pT_10to40_he4_yEnd, var2Data->h_vn_pT_10to40_he4_yEnd, var3Data->h_vn_pT_10to40_he4_yEnd, var4Data->h_vn_pT_10to40_he4_yEnd, v_vn_pT_10to40_he4_yEnd);
//   mergePoints(normalData->h_vn_pT_40to60_he4_yEnd, var1Data->h_vn_pT_40to60_he4_yEnd, var2Data->h_vn_pT_40to60_he4_yEnd, var3Data->h_vn_pT_40to60_he4_yEnd, var4Data->h_vn_pT_40to60_he4_yEnd, v_vn_pT_40to60_he4_yEnd);

}
