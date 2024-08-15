#ifndef VARIATION_H
#define VARIATION_H

#include <vector>
#include "TString.h"
#include "TH1D.h"
#include "TFile.h"

class Variation
{
 public:
  Variation(TString prefix, TString order_n_str);
  ~Variation();
  TString ID;

  TH1D *h_vn_pp;
  TH1D *h_vn_pm;
  TH1D *h_vn_kp;
  TH1D *h_vn_km;
  TH1D *h_vn_pr;
  TH1D *h_vn_de;
  TH1D *h_vn_tr;
//   TH1D *h_vn_he3;
//   TH1D *h_vn_he4;
  
  TH1D *h_vn_yCM_00to10_pr;
  TH1D *h_vn_yCM_10to40_pr;
  TH1D *h_vn_yCM_40to60_pr;
  TH1D *h_vn_yCM_00to10_kp;
  TH1D *h_vn_yCM_10to40_kp;
  TH1D *h_vn_yCM_40to60_kp;
  TH1D *h_vn_yCM_00to10_km;
  TH1D *h_vn_yCM_10to40_km;
  TH1D *h_vn_yCM_40to60_km;
  TH1D *h_vn_yCM_00to10_pp;
  TH1D *h_vn_yCM_10to40_pp;
  TH1D *h_vn_yCM_40to60_pp;
  TH1D *h_vn_yCM_00to10_pm;
  TH1D *h_vn_yCM_10to40_pm;
  TH1D *h_vn_yCM_40to60_pm;
  
  TH1D *h_vn_yCM_00to10_pr_symm;
  TH1D *h_vn_yCM_10to40_pr_symm;
  TH1D *h_vn_yCM_40to60_pr_symm;

  TH1D *h_vn_yCM_00to10_de;
  TH1D *h_vn_yCM_10to40_de;
  TH1D *h_vn_yCM_40to60_de;
  TH1D *h_vn_yCM_00to10_tr;
  TH1D *h_vn_yCM_10to40_tr;
  TH1D *h_vn_yCM_40to60_tr;
//   TH1D *h_vn_yCM_00to10_he3;
//   TH1D *h_vn_yCM_10to40_he3;
//   TH1D *h_vn_yCM_40to60_he3;
//   TH1D *h_vn_yCM_00to10_he4;
//   TH1D *h_vn_yCM_10to40_he4;
//   TH1D *h_vn_yCM_40to60_he4;

  TH1D *h_vn_pT_00to10_pr;
  TH1D *h_vn_pT_10to40_pr;
  TH1D *h_vn_pT_40to60_pr;  
//   TH1D *h_vn_pT_00to10_pr_yMid;
//   TH1D *h_vn_pT_10to40_pr_yMid;
//   TH1D *h_vn_pT_40to60_pr_yMid;  
//   TH1D *h_vn_pT_00to10_pr_yFor;
//   TH1D *h_vn_pT_10to40_pr_yFor;
//   TH1D *h_vn_pT_40to60_pr_yFor;  
//   TH1D *h_vn_pT_00to10_pr_yExt;
//   TH1D *h_vn_pT_10to40_pr_yExt;
//   TH1D *h_vn_pT_40to60_pr_yExt;  
//   TH1D *h_vn_pT_00to10_pr_yEnd;
//   TH1D *h_vn_pT_10to40_pr_yEnd;
//   TH1D *h_vn_pT_40to60_pr_yEnd;  
  
//   TH1D *h_vn_pT_00to10_de;
//   TH1D *h_vn_pT_10to40_de;
//   TH1D *h_vn_pT_40to60_de;  
//   TH1D *h_vn_pT_00to10_de_yMid;
//   TH1D *h_vn_pT_10to40_de_yMid;
//   TH1D *h_vn_pT_40to60_de_yMid;  
//   TH1D *h_vn_pT_00to10_de_yFor;
//   TH1D *h_vn_pT_10to40_de_yFor;
//   TH1D *h_vn_pT_40to60_de_yFor;  
//   TH1D *h_vn_pT_00to10_de_yExt;
//   TH1D *h_vn_pT_10to40_de_yExt;
//   TH1D *h_vn_pT_40to60_de_yExt;  
//   TH1D *h_vn_pT_00to10_de_yEnd;
//   TH1D *h_vn_pT_10to40_de_yEnd;
//   TH1D *h_vn_pT_40to60_de_yEnd;  
  
//   TH1D *h_vn_pT_00to10_tr;
//   TH1D *h_vn_pT_10to40_tr;
//   TH1D *h_vn_pT_40to60_tr;  
//   TH1D *h_vn_pT_00to10_tr_yMid;
//   TH1D *h_vn_pT_10to40_tr_yMid;
//   TH1D *h_vn_pT_40to60_tr_yMid;  
//   TH1D *h_vn_pT_00to10_tr_yFor;
//   TH1D *h_vn_pT_10to40_tr_yFor;
//   TH1D *h_vn_pT_40to60_tr_yFor;  
//   TH1D *h_vn_pT_00to10_tr_yExt;
//   TH1D *h_vn_pT_10to40_tr_yExt;
//   TH1D *h_vn_pT_40to60_tr_yExt;  
//   TH1D *h_vn_pT_00to10_tr_yEnd;
//   TH1D *h_vn_pT_10to40_tr_yEnd;
//   TH1D *h_vn_pT_40to60_tr_yEnd;  

//   TH1D *h_vn_pT_00to10_he3;
//   TH1D *h_vn_pT_10to40_he3;
//   TH1D *h_vn_pT_40to60_he3;  
//   TH1D *h_vn_pT_00to10_he3_yMid;
//   TH1D *h_vn_pT_10to40_he3_yMid;
//   TH1D *h_vn_pT_40to60_he3_yMid;  
//   TH1D *h_vn_pT_00to10_he3_yFor;
//   TH1D *h_vn_pT_10to40_he3_yFor;
//   TH1D *h_vn_pT_40to60_he3_yFor;  
//   TH1D *h_vn_pT_00to10_he3_yExt;
//   TH1D *h_vn_pT_10to40_he3_yExt;
//   TH1D *h_vn_pT_40to60_he3_yExt;  
//   TH1D *h_vn_pT_00to10_he3_yEnd;
//   TH1D *h_vn_pT_10to40_he3_yEnd;
//   TH1D *h_vn_pT_40to60_he3_yEnd;  

//   TH1D *h_vn_pT_00to10_he4;
//   TH1D *h_vn_pT_10to40_he4;
//   TH1D *h_vn_pT_40to60_he4;  
//   TH1D *h_vn_pT_00to10_he4_yMid;
//   TH1D *h_vn_pT_10to40_he4_yMid;
//   TH1D *h_vn_pT_40to60_he4_yMid;  
//   TH1D *h_vn_pT_00to10_he4_yFor;
//   TH1D *h_vn_pT_10to40_he4_yFor;
//   TH1D *h_vn_pT_40to60_he4_yFor;  
//   TH1D *h_vn_pT_00to10_he4_yExt;
//   TH1D *h_vn_pT_10to40_he4_yExt;
//   TH1D *h_vn_pT_40to60_he4_yExt;  
//   TH1D *h_vn_pT_00to10_he4_yEnd;
//   TH1D *h_vn_pT_10to40_he4_yEnd;
//   TH1D *h_vn_pT_40to60_he4_yEnd;  

 private:
  TString fileName;
  TFile *file;
  void initialize(TString order_n_str);
  void fixAttributes(TString order_n_str);
};

#endif
