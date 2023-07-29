#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <string>
#include <map>
#include <vector>
#include "TString.h"

class ConfigReader
{
 public:
  ConfigReader();
  ~ConfigReader();

  bool errorFound();
  void notifyError();
  void initialize();
  void setAllCuts();
  void read(std::string fileName);
  void printAll();
  void checkForNonSetKeys();
  Bool_t triggersMatch(UInt_t readTrigger);

  std::vector<UInt_t> triggers;

  Int_t fixed_target; // boolean: 0 or 1
  Int_t epd_max_weight;
  Int_t nHits;
  Int_t nHits_dEdx;
  Int_t m_nHits;
  Int_t m_nHits_dEdx;
  Int_t min_tracks;
  Int_t shift_terms;
  Int_t epdA_inner_row;
  Int_t epdA_outer_row;
  Int_t epdB_inner_row;
  Int_t epdB_outer_row;
  Double_t sqrt_s_NN;
  Double_t order_n;
  Double_t order_m;
  Double_t epd_threshold;
  Double_t nHits_ratio;
  Double_t dca;
  Double_t m_nHits_ratio;
  Double_t m_dca;
  Double_t tpc_A_low_eta;
  Double_t tpc_A_high_eta;
  Double_t tpc_B_low_eta;
  Double_t tpc_B_high_eta;
  Double_t r_vtx;
  Double_t z_vtx_low;
  Double_t z_vtx_high;
  Double_t m_r_vtx;
  Double_t m_z_vtx_low;
  Double_t m_z_vtx_high;
  Double_t y_mid;
  Double_t y_beam;
  Double_t nSig_pi_low;
  Double_t nSig_pi_high;
  Double_t nSig_ka_low;
  Double_t nSig_ka_high;
  Double_t nSig_pr_low;
  Double_t nSig_pr_high;
  Double_t z_de_low;
  Double_t z_de_high;
  Double_t z_tr_low;
  Double_t z_tr_high;
  Double_t m2_pi_low;
  Double_t m2_pi_high;
  Double_t m2_ka_low;
  Double_t m2_ka_high;
  Double_t m2_de_low;
  Double_t m2_de_high;
  Double_t m2_tr_low;
  Double_t m2_tr_high;

  // Pion
  Double_t yCM_norm_pi_low;
  Double_t yCM_norm_pi_high;
  Double_t pt_norm_pi_low;
  Double_t pt_norm_pi_high;
  Double_t yCM_yExt_pi_low;
  Double_t yCM_yExt_pi_high;
  Double_t pt_yExt_pi_low;
  Double_t pt_yExt_pi_high;

  // Kaon
  Double_t yCM_norm_ka_low;
  Double_t yCM_norm_ka_high;
  Double_t pt_norm_ka_low;
  Double_t pt_norm_ka_high;
  Double_t yCM_yExt_ka_low;
  Double_t yCM_yExt_ka_high;
  Double_t pt_yExt_ka_low;
  Double_t pt_yExt_ka_high;

  // Proton 
  Double_t yCM_norm_pr_low;
  Double_t yCM_norm_pr_high;
  Double_t pt_norm_pr_low;
  Double_t pt_norm_pr_high;
  Double_t yCM_yDep_pr_low;
  Double_t yCM_yDep_pr_high;
  Double_t pt_yDep_pr_low;
  Double_t pt_yDep_pr_high;
  Double_t yCM_yExt_pr_low;
  Double_t yCM_yExt_pr_high;
  Double_t pt_yExt_pr_low;
  Double_t pt_yExt_pr_high;
  Double_t yCM_ySym_pr_low;
  Double_t yCM_ySym_pr_high;
  Double_t pt_ySym_pr_low;
  Double_t pt_ySym_pr_high;
  Double_t yCM_yFor_pr_low;
  Double_t yCM_yFor_pr_high;
  Double_t pt_yFor_pr_low;
  Double_t pt_yFor_pr_high;
  Double_t yCM_alt_pr_low;
  Double_t yCM_alt_pr_high;
  Double_t pt_alt_pr_low;
  Double_t pt_alt_pr_high;

  // Deuteron
  Double_t yCM_norm_de_low;
  Double_t yCM_norm_de_high;
  Double_t pt_norm_de_low;
  Double_t pt_norm_de_high;

  // Triton
  Double_t yCM_norm_tr_low;
  Double_t yCM_norm_tr_high;
  Double_t pt_norm_tr_low;
  Double_t pt_norm_tr_high;

  // Proton, Deuteron, and Triton
  Double_t KT_pdt_low;
  Double_t KT_pdt_high;

 private:
  bool errorFlag;
  TString lastKey;
  TString lastValue;
  std::map<std::string, int> intValCuts;
  std::map<std::string, double> dblValCuts;
};

#endif
