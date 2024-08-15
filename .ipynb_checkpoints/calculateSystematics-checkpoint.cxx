#include "Variation.h"
#include "CompositeData.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "THStack.h"
#include <vector>
#include <iostream>


void printPointErrors(TGraphErrors *graph);

struct AverageContributionTracker
{
  Double_t epdPercentQuadSum = 0.0;
  Double_t nhitsPercentQuadSum = 0.0;
  Double_t nSigPiPercentQuadSum = 0.0;
  Double_t nSigKaPercentQuadSum = 0.0;
  Double_t nSigPrPercentQuadSum = 0.0;
  Double_t zDePercentQuadSum = 0.0;
  Double_t zTrPercentQuadSum = 0.0;
  Double_t zHe3PercentQuadSum = 0.0;
  Double_t zHe4PercentQuadSum = 0.0;
  Double_t rvtxPercentQuadSum = 0.0;
  Double_t zvtxPercentQuadSum = 0.0;
  Double_t dcaPercentQuadSum = 0.0;
  Double_t nhitsdEdxPercentQuadSum = 0.0;
  Double_t nhitsratioPercentQuadSum = 0.0;
  Double_t m2PiPercentQuadSum = 0.0;
  Double_t m2KaPercentQuadSum = 0.0;

  Double_t trackQAPercentQuadSum = 0.0;
  Double_t eventQAPercentQuadSum = 0.0;

  Int_t epdNbins = 0;
  Int_t nhitsNbins = 0;
  Int_t nSigPiNbins = 0;
  Int_t nSigKaNbins = 0;
  Int_t nSigPrNbins = 0;
  Int_t zDeNbins = 0;
  Int_t zTrNbins = 0;
  Int_t zHe3Nbins = 0;
  Int_t zHe4Nbins = 0;
  Int_t rvtxNbins = 0;
  Int_t zvtxNbins = 0;
  Int_t dcaNbins = 0;
  Int_t nhitsdEdxNbins = 0;
  Int_t nhitsratioNbins = 0;
  Int_t m2PiNbins = 0;
  Int_t m2KaNbins = 0;

  Int_t trackQANbins = 0;
  Int_t eventQANbins = 0;

  void addContribution(TString ID, Double_t stdDevContributed)
  {
	                // Check if the input parameter is NaN
    if (std::isnan(stdDevContributed)) {
        std::cout << "Input parameter is NaN. Skipping..." << std::endl;
        return;
    }

    if (ID == "nhits" ||
	ID == "dca" ||
	ID == "nhitsdEdx" ||
	ID == "nhitsratio")
      {
	//std::cout << "ID: "  << ID<< std::endl;
	trackQAPercentQuadSum += stdDevContributed;
	trackQANbins++;
      }
    else if (ID == "rvtx" ||
	     ID == "zvtx")
      {
	//std::cout << "ID: "  << ID<< std::endl;
	eventQAPercentQuadSum += stdDevContributed;
	eventQANbins++;
      }
    else if (ID == "epd")
      {
        epdPercentQuadSum += stdDevContributed;
        epdNbins++;
	//std::cout << "ID: "  << ID<< std::endl;
	//std::cout << "epdNbins: "  << epdNbins<< std::endl;
	//std::cout << "epdPercentQuadSum: "  << epdPercentQuadSum<< std::endl;
      }
    else if (ID == "nSigPi")
     {
       nSigPiPercentQuadSum += stdDevContributed;
       nSigPiNbins++;
     }
    else if (ID == "nSigKa")
     {
       nSigKaPercentQuadSum += stdDevContributed;
       nSigKaNbins++;
     }
    else if (ID == "nSigPr")
      {
	//std::cout << "ID: "  << ID<< std::endl;
	nSigPrPercentQuadSum += stdDevContributed;
	nSigPrNbins++;
      }
    else if (ID == "m2Pi")
      {
	//std::cout << "ID: "  << ID<< std::endl;
	m2PiPercentQuadSum += stdDevContributed;
	m2PiNbins++;
      }
    else if (ID == "m2Ka")
      {
	//std::cout << "ID: "  << ID<< std::endl;
	m2KaPercentQuadSum += stdDevContributed;
	m2KaNbins++;
      }
    else
      {
	//std::cout << "AverageContributionTracker error, check spelling of ID!: "<< ID << std::endl;
	//std::cout << "ID! "  << ID<< std::endl;
      }
  }

  void printContributions()
  {
    std::cout << std::endl 
	      //<< "Std dev of each contribution as a percent of the normal v3 measurement:" << std::endl
	      << "Std dev of each contribution as a percent of the normal v3 measurement:" << std::endl
	      << std::endl
	      << "Track QA, " << trackQAPercentQuadSum / (Double_t)trackQANbins << std::endl
	      << "Event QA, " << eventQAPercentQuadSum / (Double_t)eventQANbins << std::endl
	      << "nSigma Pi, " << nSigPiPercentQuadSum / (Double_t)nSigPiNbins << std::endl
	      << "nSigma Ka, " << nSigKaPercentQuadSum / (Double_t)nSigKaNbins << std::endl
	      << "nSigma Pr, " << nSigPrPercentQuadSum / (Double_t)nSigPrNbins << std::endl
	      << "m^2 Pi, " << m2PiPercentQuadSum / (Double_t)m2PiNbins << std::endl
	      << "m^2 Ka, " << m2KaPercentQuadSum / (Double_t)m2KaNbins << std::endl
	      << "EP Resolution, " << epdPercentQuadSum / (Double_t)epdNbins << std::endl
	      << std::endl;
  }
};






//void calculateSystematics(TString order_n_str = "3")
void calculateSystematics(TString order_n_str = "3")
{
  TFile* newFile = new TFile("systematicErrors.root", "RECREATE");
  //TString directory20Percent = "../thirdDraft/20percentVariations/";
  TString directory30Percent = "../";
  //TString directory30Percent = "../thirdDraft/30percentVariations/";
  TString directoryEPR = "../";
  //TString directoryEPR = "../thirdDraft/eprVariations/";

    
  Variation* Normal = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);


//   Variation* epd_high = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/3-25-24-V3-HistogramOuterEPDHigh.root", order_n_str);
//   Variation* epd_low = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/3-25-24-V3-HistogramOuterEPDLow.root", order_n_str);

    
  Variation* nSigPi_high_20 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nSigPi_low_20  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nSigKa_high_20 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nSigKa_low_20  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nSigPr_high_20 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nSigPr_low_20  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* rvtx_high_20 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* rvtx_low_20  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* zvtx_high_20 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* zvtx_low_20  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* dca_high_20 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* dca_low_20  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nhits_high_20 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nhits_low_20 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nhitsdEdx_high_20 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  //Variation* nhitsdEdx_low_20  = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/3-25-24-V3-Histogram", order_n_str);
  Variation* nhitsratio_high_20 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nhitsratio_low_20  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* m2Pi_high_20 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* m2Pi_low_20  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* m2Ka_high_20 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* m2Ka_low_20  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
    
    

  Variation* nSigPi_high_30 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nSigPi_low_30  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nSigKa_high_30 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nSigKa_low_30  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nSigPr_high_30 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nSigPr_low_30  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* rvtx_high_30 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* rvtx_low_30  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* zvtx_high_30 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* zvtx_low_30  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* dca_high_30 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* dca_low_30  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nhits_high_30 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nhits_low_30 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nhitsdEdx_high_30 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  //Variation* nhitsdEdx_low_30  = new Variation(directory30Percent+"nhitsdEdx_low", order_n_str);
  Variation* nhitsratio_high_30 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* nhitsratio_low_30  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* m2Pi_high_30 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* m2Pi_low_30  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* m2Ka_high_30 = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);
  Variation* m2Ka_low_30  = new Variation("/star/u/mcgordon/SystematicsCameronResolution/.root", order_n_str);



  //CompositeData* epd = new CompositeData("epd", Normal, epd_scaled, epd_high);
//   CompositeData* epd = new CompositeData("epd", Normal, epd_low, epd_high);
    
//   CompositeData* nhits = new CompositeData("nhits", Normal, nhits_low_30, nhits_high_30);  
  //CompositeData* nSigPi = new CompositeData("nSigPi", Normal, nSigPi_low_30, nSigPi_high_30);
  //CompositeData* nSigKa = new CompositeData("nSigKa", Normal, nSigKa_low_30, nSigKa_high_30);
  //CompositeData* nSigPr = new CompositeData("nSigPr", Normal, nSigPr_low_30, nSigPr_high_30);
  //CompositeData* zDe = new CompositeData("zDe", Normal, zDe_low_30, zDe_high_30);
  //CompositeData* zTr = new CompositeData("zTr", Normal, zTr_low_30, zTr_high_30);
//   CompositeData* rvtx = new CompositeData("rvtx", Normal, rvtx_low_30, rvtx_high_30);
//   CompositeData* zvtx = new CompositeData("zvtx", Normal, zvtx_low_30, zvtx_high_30);
//   CompositeData* dca  = new CompositeData("dca", Normal, dca_low_30, dca_high_30);
//   CompositeData* nhitsdEdx = new CompositeData("nhitsdEdx", Normal, nhitsdEdx_high_30);
//   CompositeData* nhitsratio = new CompositeData("nhitsratio", Normal, nhitsratio_low_30, nhitsratio_high_30);
//   CompositeData* m2Pi = new CompositeData("m2Pi", Normal, m2Pi_low_30, m2Pi_high_30);
//   CompositeData* m2Ka = new CompositeData("m2Ka", Normal, m2Ka_low_30, m2Ka_high_30);

  CompositeData* nhits = new CompositeData("nhits", Normal, nhits_low_30, nhits_high_30, nhits_low_20, nhits_high_20);  
  CompositeData* nSigPi = new CompositeData("nSigPi", Normal, nSigPi_low_30, nSigPi_high_30, nSigPi_low_20, nSigPi_high_20);
  CompositeData* nSigKa = new CompositeData("nSigKa", Normal, nSigKa_low_30, nSigKa_high_30, nSigKa_low_20, nSigKa_high_20);
  CompositeData* nSigPr = new CompositeData("nSigPr", Normal, nSigPr_low_30, nSigPr_high_30, nSigPr_low_20, nSigPr_high_20);
  CompositeData* rvtx = new CompositeData("rvtx", Normal, rvtx_low_30, rvtx_high_30, rvtx_low_20, rvtx_high_20);
  CompositeData* zvtx = new CompositeData("zvtx", Normal, zvtx_low_30, zvtx_high_30, zvtx_low_20, zvtx_high_20);
  CompositeData* dca  = new CompositeData("dca", Normal, dca_low_30, dca_high_30, dca_low_20, dca_high_20);
  CompositeData* nhitsdEdx = new CompositeData("nhitsdEdx", Normal, nhitsdEdx_high_30, nhitsdEdx_high_20);
  CompositeData* nhitsratio = new CompositeData("nhitsratio", Normal, nhitsratio_low_30, nhitsratio_high_30, nhitsratio_low_20, nhitsratio_high_20);
  CompositeData* m2Pi = new CompositeData("m2Pi", Normal, m2Pi_low_30, m2Pi_high_30, m2Pi_low_20, m2Pi_high_20);
  CompositeData* m2Ka = new CompositeData("m2Ka", Normal, m2Ka_low_30, m2Ka_high_30, m2Ka_low_20, m2Ka_high_20);


  
  // Any variations applied universally (like epd variation) should not be in this vector.
  std::vector<CompositeData*> composites;
  composites.push_back(nhits);
  composites.push_back(nSigPi);
  composites.push_back(nSigKa);
  composites.push_back(nSigPr);
  composites.push_back(rvtx);
  composites.push_back(zvtx);
  composites.push_back(dca);
  composites.push_back(nhitsdEdx);
  composites.push_back(nhitsratio);
  composites.push_back(m2Pi);
  composites.push_back(m2Ka);
  ////

  newFile->cd();

  //======= CALCULATION OF SYSTEMATIC ERRORS
  Double_t ithBinSysErr = 0.0;
  Double_t quadSum = 0.0;
  Int_t bins;

  AverageContributionTracker avgTracker_00to10;
  AverageContributionTracker avgTracker_10to40;
  AverageContributionTracker avgTracker_40to60;
    
    
    
    
    
    
    
    
    
    
// ======== Vn vs Centrality

  //=== pi+ vs centrality
  //std::cout << "PP VS CENTRALITY" << std::endl;
  std::vector<Double_t> v_sys_pp;
  bins = Normal->h_vn_pp->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_pp.at(ithBin).variance;

//     if (ithBin < 2)
//       avgTracker_00to10.addContribution(epd->ID, epd->v_vn_pp.at(ithBin).stdDevPercentage);
//     else if (ithBin >= 2 && ithBin <= 7)
//       avgTracker_10to40.addContribution(epd->ID, epd->v_vn_pp.at(ithBin).stdDevPercentage);
//     else if (ithBin > 7)
//       avgTracker_40to60.addContribution(epd->ID, epd->v_vn_pp.at(ithBin).stdDevPercentage);
 
    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_pp.at(ithBin).deltaByDeltaError > 1.0)
        {
          quadSum += composites.at(jthCut)->v_vn_pp.at(ithBin).variance;
	  if (ithBin < 2)
	    avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pp.at(ithBin).stdDevPercentage);
	  else if (ithBin >= 2 && ithBin <= 7)
	    avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pp.at(ithBin).stdDevPercentage);
	  else if (ithBin > 7)
	    avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pp.at(ithBin).stdDevPercentage);
        }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_pp.push_back(ithBinSysErr);
  }
  
  ithBinSysErr = 0;
  quadSum = 0.0;
  //=== End h_vn_pp loop


  
  //=== pi- vs centrality
  //std::cout << "PM VS CENTRALITY" << std::endl;
  std::vector<Double_t> v_sys_pm;
  bins = Normal->h_vn_pm->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_pm.at(ithBin).variance;

//     if (ithBin < 2)
//       avgTracker_00to10.addContribution(epd->ID, epd->v_vn_pm.at(ithBin).stdDevPercentage);
//     if (ithBin >= 2 && ithBin <= 7)
//       avgTracker_10to40.addContribution(epd->ID, epd->v_vn_pm.at(ithBin).stdDevPercentage);
//     if (ithBin > 7)
//       avgTracker_40to60.addContribution(epd->ID, epd->v_vn_pm.at(ithBin).stdDevPercentage);
 
    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_pm.at(ithBin).deltaByDeltaError > 1.0)
        {
          quadSum += composites.at(jthCut)->v_vn_pm.at(ithBin).variance;
	  if (ithBin < 2)
	    avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pm.at(ithBin).stdDevPercentage);
	  if (ithBin >= 2 && ithBin <= 7)
	    avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pm.at(ithBin).stdDevPercentage);
	  if (ithBin > 7)
	    avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pm.at(ithBin).stdDevPercentage);
        }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_pm.push_back(ithBinSysErr);
  } 
  ithBinSysErr = 0;
  quadSum = 0.0;
  
  //=== End h_vn_pm loop


  
  //=== K+ vs centrality
  //std::cout << "KP VS CENTRALITY" << std::endl;
  
  std::vector<Double_t> v_sys_kp;
  bins = Normal->h_vn_kp->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_kp.at(ithBin).variance;

//     if (ithBin == 0)
//       avgTracker_00to10.addContribution(epd->ID, epd->v_vn_kp.at(ithBin).stdDevPercentage);
//     if (ithBin >= 1 && ithBin <= 3)
//       avgTracker_10to40.addContribution(epd->ID, epd->v_vn_kp.at(ithBin).stdDevPercentage);
//     if (ithBin > 3)
//       avgTracker_40to60.addContribution(epd->ID, epd->v_vn_kp.at(ithBin).stdDevPercentage);
    
    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_kp.at(ithBin).deltaByDeltaError > 1.0)
	{
	  quadSum += composites.at(jthCut)->v_vn_kp.at(ithBin).variance;
	  if (ithBin == 0)
	    avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_kp.at(ithBin).stdDevPercentage);
	  if (ithBin >= 1 && ithBin <= 3)
	    avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_kp.at(ithBin).stdDevPercentage);
	  if (ithBin > 3)
	    avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_kp.at(ithBin).stdDevPercentage);
	}
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_kp.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  
  //=== End h_vn_kp loop

  //=== K- vs centrality
  //std::cout << "KM VS CENTRALITY" << std::endl;
  
  std::vector<Double_t> v_sys_km;
  bins = Normal->h_vn_km->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_km.at(ithBin).variance;

//     if (ithBin == 0)
//       avgTracker_00to10.addContribution(epd->ID, epd->v_vn_km.at(ithBin).stdDevPercentage);
//     if (ithBin >= 1 && ithBin <= 3)
//       avgTracker_10to40.addContribution(epd->ID, epd->v_vn_km.at(ithBin).stdDevPercentage);
//     if (ithBin > 3)
//       avgTracker_40to60.addContribution(epd->ID, epd->v_vn_km.at(ithBin).stdDevPercentage);
 
 
    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_km.at(ithBin).deltaByDeltaError > 1.0)
	{
	  quadSum += composites.at(jthCut)->v_vn_km.at(ithBin).variance;
	  if (ithBin == 0)
	    avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_km.at(ithBin).stdDevPercentage);
	  if (ithBin >= 1 && ithBin <= 3)
	    avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_km.at(ithBin).stdDevPercentage);
	  if (ithBin > 3)
	    avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_km.at(ithBin).stdDevPercentage);
	}
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_km.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  
  //=== End h_vn_km loop


  //=== proton vs centrality
  //std::cout << "PROTON VS CENTRALITY" << std::endl;
  std::vector<Double_t> v_sys_pr;
  bins = Normal->h_vn_pr->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_pr.at(ithBin).variance;
//     std::cout << "epd variance quadSum: " <<  epd->v_vn_pr.at(ithBin).variance;
//     std::cout << "epd stdDev: " <<  epd->v_vn_pr.at(ithBin).stdDevPercentage;
//     std::cout << "epd ID " <<  epd->ID << std::endl;

//     if (ithBin < 2)
//       avgTracker_00to10.addContribution(epd->ID, epd->v_vn_pr.at(ithBin).stdDevPercentage);
//     if (ithBin >= 2 && ithBin <= 7)
//       avgTracker_10to40.addContribution(epd->ID, epd->v_vn_pr.at(ithBin).stdDevPercentage);
//     if (ithBin > 7)
//       avgTracker_40to60.addContribution(epd->ID, epd->v_vn_pr.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_pr.at(ithBin).deltaByDeltaError > 1.0)
        {
          quadSum += composites.at(jthCut)->v_vn_pr.at(ithBin).variance;
	  if (ithBin < 2)
	    //std::cout << "composites ID: "  << composites.at(jthCut)->ID<< std::endl;
	    avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pr.at(ithBin).stdDevPercentage);
	  if (ithBin >= 2 && ithBin <= 7)
	    //std::cout << "composites ID: "  << composites.at(jthCut)->ID<< std::endl;
	    avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pr.at(ithBin).stdDevPercentage);
	  if (ithBin > 7)
	    //std::cout << "composites ID: "  << composites.at(jthCut)->ID<< std::endl;
	    avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pr.at(ithBin).stdDevPercentage);
        }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_pr.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //=== End h_vn_pr loop
 
  //=== deuteron vs centrality
  //std::cout << "DEUTERON VS CENTRALITY" << std::endl;

  std::vector<Double_t> v_sys_de;
  bins = Normal->h_vn_de->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_de.at(ithBin).variance;

//     if (ithBin < 2)
//       avgTracker_00to10.addContribution(epd->ID, epd->v_vn_de.at(ithBin).stdDevPercentage);
//     if (ithBin >= 2 && ithBin <= 7)
//       avgTracker_10to40.addContribution(epd->ID, epd->v_vn_de.at(ithBin).stdDevPercentage);
//     if (ithBin > 7 && ithBin < 12)
//       avgTracker_40to60.addContribution(epd->ID, epd->v_vn_de.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_de.at(ithBin).deltaByDeltaError > 1.0)
        {
          quadSum += composites.at(jthCut)->v_vn_de.at(ithBin).variance;
	  if (ithBin < 2)
	    avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_de.at(ithBin).stdDevPercentage);
	  if (ithBin >= 2 && ithBin <= 7)
	    avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_de.at(ithBin).stdDevPercentage);
	  if (ithBin > 7 && ithBin < 12)
	    avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_de.at(ithBin).stdDevPercentage);
        }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_de.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;

  //=== End h_vn_de loop


  //=== Triton vs centrality
  //std::cout << "TRITON VS CENTRALITY" << std::endl;

  std::vector<Double_t> v_sys_tr;
  bins = Normal->h_vn_tr->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_tr.at(ithBin).variance;

//     if (ithBin < 2)
//       avgTracker_00to10.addContribution(epd->ID, epd->v_vn_tr.at(ithBin).stdDevPercentage);
//     if (ithBin >= 2 && ithBin <= 7)
//       avgTracker_10to40.addContribution(epd->ID, epd->v_vn_tr.at(ithBin).stdDevPercentage);
//     if (ithBin > 7 && ithBin < 12)
//       avgTracker_40to60.addContribution(epd->ID, epd->v_vn_tr.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_tr.at(ithBin).deltaByDeltaError > 1.0)
        {
          quadSum += composites.at(jthCut)->v_vn_tr.at(ithBin).variance;
	  if (ithBin < 2)
	    avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_tr.at(ithBin).stdDevPercentage);
	  if (ithBin >= 2 && ithBin <= 7)
	    avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_tr.at(ithBin).stdDevPercentage);
	  if (ithBin > 7 && ithBin < 12)
	    avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_tr.at(ithBin).stdDevPercentage);
        }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_tr.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;

  //=== End h_vn_tr loop


    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
  
    
    
//======== Vn vs Rapidity
    

  //=== Proton vs rapidity 0 - 10%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_00to10_pr;
  bins = Normal->h_vn_yCM_00to10_pr->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_00to10_pr.at(ithBin).variance;
 
//     avgTracker_00to10.addContribution(epd->ID, epd->v_vn_yCM_00to10_pr.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_00to10_pr.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_00to10_pr.at(ithBin).variance;
        avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_00to10_pr.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_00to10_pr.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //===



  //=== Proton vs rapidity 10 - 40%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_10to40_pr;
  bins = Normal->h_vn_yCM_10to40_pr->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_10to40_pr.at(ithBin).variance;
    
//     avgTracker_10to40.addContribution(epd->ID, epd->v_vn_yCM_10to40_pr.at(ithBin).stdDevPercentage);
 
    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_10to40_pr.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_10to40_pr.at(ithBin).variance;
        avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_10to40_pr.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_10to40_pr.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //===


  //=== Proton vs rapidity 40 - 60%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_40to60_pr;
  bins = Normal->h_vn_yCM_40to60_pr->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_40to60_pr.at(ithBin).variance;
    
//     avgTracker_40to60.addContribution(epd->ID, epd->v_vn_yCM_40to60_pr.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_40to60_pr.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_40to60_pr.at(ithBin).variance;
        avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_40to60_pr.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_40to60_pr.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //===
    
/*    
  //=== K+ vs rapidity 0 - 10%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_00to10_kp;
  bins = Normal->h_vn_yCM_00to10_kp->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_00to10_kp.at(ithBin).variance;

//     avgTracker_00to10.addContribution(epd->ID, epd->v_vn_yCM_00to10_kp.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_00to10_kp.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_00to10_kp.at(ithBin).variance;
        avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_00to10_kp.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_00to10_kp.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //===



  //=== K+ vs rapidity 10 - 40%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_10to40_kp;
  bins = Normal->h_vn_yCM_10to40_kp->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_10to40_kp.at(ithBin).variance;
    
//     avgTracker_10to40.addContribution(epd->ID, epd->v_vn_yCM_10to40_kp.at(ithBin).stdDevPercentage);
 
    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_10to40_kp.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_10to40_kp.at(ithBin).variance;
        avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_10to40_kp.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_10to40_kp.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //===



  //=== K+ vs rapidity 40 - 60%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_40to60_kp;
  bins = Normal->h_vn_yCM_40to60_kp->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_40to60_kp.at(ithBin).variance;
    
//     avgTracker_40to60.addContribution(epd->ID, epd->v_vn_yCM_40to60_kp.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_40to60_kp.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_40to60_kp.at(ithBin).variance;
        avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_40to60_kp.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_40to60_kp.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //===


    
  //=== K- vs rapidity 0 - 10%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_00to10_km;
  bins = Normal->h_vn_yCM_00to10_km->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_00to10_km.at(ithBin).variance;

//     avgTracker_00to10.addContribution(epd->ID, epd->v_vn_yCM_00to10_km.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_00to10_km.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_00to10_km.at(ithBin).variance;
        avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_00to10_km.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_00to10_km.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //===




  //=== K- vs rapidity 10 - 40%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_10to40_km;
  bins = Normal->h_vn_yCM_10to40_km->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_10to40_km.at(ithBin).variance;
    
//     avgTracker_10to40.addContribution(epd->ID, epd->v_vn_yCM_10to40_km.at(ithBin).stdDevPercentage);
 
    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_10to40_km.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_10to40_km.at(ithBin).variance;
        avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_10to40_km.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_10to40_km.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //===



  //=== K- vs rapidity 40 - 60%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_40to60_km;
  bins = Normal->h_vn_yCM_40to60_km->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_40to60_km.at(ithBin).variance;
    
//     avgTracker_40to60.addContribution(epd->ID, epd->v_vn_yCM_40to60_km.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_40to60_km.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_40to60_km.at(ithBin).variance;
        avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_40to60_km.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_40to60_km.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //===
    

  //=== Pi+ vs rapidity 0 - 10%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_00to10_pp;
  bins = Normal->h_vn_yCM_00to10_pp->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_00to10_pp.at(ithBin).variance;

//     avgTracker_00to10.addContribution(epd->ID, epd->v_vn_yCM_00to10_pp.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_00to10_pp.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_00to10_pp.at(ithBin).variance;
        avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_00to10_pp.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_00to10_pp.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //===



  //=== Pi+ vs rapidity 10 - 40%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_10to40_pp;
  bins = Normal->h_vn_yCM_10to40_pp->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_10to40_pp.at(ithBin).variance;
    
//     avgTracker_10to40.addContribution(epd->ID, epd->v_vn_yCM_10to40_pp.at(ithBin).stdDevPercentage);
 
    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_10to40_pp.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_10to40_pp.at(ithBin).variance;
        avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_10to40_pp.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_10to40_pp.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //===


  //=== Pi+ vs rapidity 40 - 60%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_40to60_pp;
  bins = Normal->h_vn_yCM_40to60_pp->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_40to60_pp.at(ithBin).variance;
    
//     avgTracker_40to60.addContribution(epd->ID, epd->v_vn_yCM_40to60_pp.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_40to60_pp.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_40to60_pp.at(ithBin).variance;
        avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_40to60_pp.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_40to60_pp.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //===


  //=== Pi- vs rapidity 0 - 10%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_00to10_pm;
  bins = Normal->h_vn_yCM_00to10_pm->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_00to10_pm.at(ithBin).variance;

//     avgTracker_00to10.addContribution(epd->ID, epd->v_vn_yCM_00to10_pm.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_00to10_pm.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_00to10_pm.at(ithBin).variance;
        avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_00to10_pm.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_00to10_pm.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //===



  //=== Pi- vs rapidity 10 - 40%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_10to40_pm;
  bins = Normal->h_vn_yCM_10to40_pm->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_10to40_pm.at(ithBin).variance;

//     avgTracker_10to40.addContribution(epd->ID, epd->v_vn_yCM_10to40_pm.at(ithBin).stdDevPercentage);
 
    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_10to40_pm.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_10to40_pm.at(ithBin).variance;
        avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_10to40_pm.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_10to40_pm.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //===


  //=== Pi- vs rapidity 40 - 60%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_40to60_pm;
  bins = Normal->h_vn_yCM_40to60_pm->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_40to60_pm.at(ithBin).variance;
    
//     avgTracker_40to60.addContribution(epd->ID, epd->v_vn_yCM_40to60_pm.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_40to60_pm.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_40to60_pm.at(ithBin).variance;
        avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_40to60_pm.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_40to60_pm.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  //===



  //=== Deuteron vs rapidity 0 - 10%
  //std::cout << "Deuteron VS RAPIDITY" << std::endl;

  std::vector<Double_t> v_sys_yCM_00to10_de;
  bins = Normal->h_vn_yCM_00to10_de->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_00to10_de.at(ithBin).variance;

//     avgTracker_00to10.addContribution(epd->ID, epd->v_vn_yCM_00to10_de.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_00to10_de.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_00to10_de.at(ithBin).variance;
        avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_00to10_de.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_00to10_de.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;

  //===


  //=== Deuteron vs rapidity 10 - 40%
  //std::cout << "Deuteron VS RAPIDITY" << std::endl;
 
  std::vector<Double_t> v_sys_yCM_10to40_de;
  bins = Normal->h_vn_yCM_10to40_de->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_10to40_de.at(ithBin).variance;

//     avgTracker_10to40.addContribution(epd->ID, epd->v_vn_yCM_10to40_de.at(ithBin).stdDevPercentage);
 
    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_10to40_de.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_10to40_de.at(ithBin).variance;
        avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_10to40_de.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_10to40_de.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
 
  //===


  //=== Deuteron vs rapidity 40 - 60%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;

  std::vector<Double_t> v_sys_yCM_40to60_de;
  bins = Normal->h_vn_yCM_40to60_de->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_40to60_de.at(ithBin).variance;

//     avgTracker_40to60.addContribution(epd->ID, epd->v_vn_yCM_40to60_de.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_40to60_de.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_40to60_de.at(ithBin).variance;
        avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_40to60_de.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_40to60_de.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;

  //===


  //=== Triton vs rapidity 0 - 10%
  //std::cout << "Triton VS RAPIDITY" << std::endl;

  std::vector<Double_t> v_sys_yCM_00to10_tr;
  bins = Normal->h_vn_yCM_00to10_tr->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_00to10_tr.at(ithBin).variance;

//     avgTracker_00to10.addContribution(epd->ID, epd->v_vn_yCM_00to10_tr.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_00to10_tr.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_00to10_tr.at(ithBin).variance;
        avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_00to10_tr.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_00to10_tr.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;

  //===


  //=== Trton vs rapidity 10 - 40%
  //std::cout << "Triton VS RAPIDITY" << std::endl;

  std::vector<Double_t> v_sys_yCM_10to40_tr;
  bins = Normal->h_vn_yCM_10to40_tr->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_10to40_tr.at(ithBin).variance;

//     avgTracker_10to40.addContribution(epd->ID, epd->v_vn_yCM_10to40_tr.at(ithBin).stdDevPercentage);
 
    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_10to40_tr.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_10to40_tr.at(ithBin).variance;
        avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_10to40_tr.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_10to40_tr.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;

  //===


  //=== Triton vs rapidity 40 - 60%
  //std::cout << "Triton VS RAPIDITY" << std::endl;

  std::vector<Double_t> v_sys_yCM_40to60_tr;
  bins = Normal->h_vn_yCM_40to60_tr->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_40to60_tr.at(ithBin).variance;

//     avgTracker_40to60.addContribution(epd->ID, epd->v_vn_yCM_40to60_tr.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_40to60_tr.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_40to60_tr.at(ithBin).variance;
        avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_40to60_tr.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_40to60_tr.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;

  //===
*/

    
    
    
    


    
    
    
    
    
    
    
    
    
    

    
    
//============ Vn vs Pt

  //=== Proton vs pT 0 - 10%
  
  std::vector<Double_t> v_sys_pT_00to10_pr;
  bins = Normal->h_vn_pT_00to10_pr->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_pT_00to10_pr.at(ithBin).variance;
    
//     if (ithBin > 1)
//       avgTracker_00to10.addContribution(epd->ID, epd->v_vn_pT_00to10_pr.at(ithBin).stdDevPercentage);
//     if (!epd->v_vn_pT_00to10_pr.empty()) {
//         // Access the first element safely
//         int firstElement = epd->v_vn_pT_00to10_pr.at(0).mean;
//         std::cout << "pr 0010 First element: " << firstElement << std::endl;
//     } else {
//         std::cout << "Vector epd pr is empty." << std::endl;
//     }

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_pT_00to10_pr.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_pT_00to10_pr.at(ithBin).variance;
        avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pT_00to10_pr.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_pT_00to10_pr.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  
  //===

  //=== Proton vs pT 10 - 40%
  
  std::vector<Double_t> v_sys_pT_10to40_pr;
  bins = Normal->h_vn_pT_10to40_pr->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_pT_10to40_pr.at(ithBin).variance;
    
//     if (ithBin  > 1)
//       avgTracker_10to40.addContribution(epd->ID, epd->v_vn_pT_10to40_pr.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_pT_10to40_pr.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_pT_10to40_pr.at(ithBin).variance;
        avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pT_10to40_pr.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_pT_10to40_pr.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  
  //===


  //=== Proton vs pT 40 - 60%
  
  std::vector<Double_t> v_sys_pT_40to60_pr;
  bins = Normal->h_vn_pT_40to60_pr->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_pT_40to60_pr.at(ithBin).variance;
    
//     if (ithBin  > 1)
//       avgTracker_40to60.addContribution(epd->ID, epd->v_vn_pT_40to60_pr.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_pT_40to60_pr.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_pT_40to60_pr.at(ithBin).variance;
        avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pT_40to60_pr.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_pT_40to60_pr.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  
  //===


  //=== Deuteron vs pT 0 - 10%
  /*
  std::cout << "deuteron pt test 0: " << std::endl;
  std::vector<Double_t> v_sys_pT_00to10_de;
  bins = Normal->h_vn_pT_00to10_de->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    std::cout << "deuteron pt test 0.0: " << std::endl;
    quadSum = 0.0;
    quadSum += epd->v_vn_pT_00to10_de.at(ithBin).variance;
    
    if (ithBin > 1)
      avgTracker_00to10.addContribution(epd->ID, epd->v_vn_pT_00to10_de.at(ithBin).stdDevPercentage);

    if (!epd->v_vn_pT_00to10_de.empty()) {
        // Access the first element safely
        int firstElement = epd->v_vn_pT_00to10_de.at(0).mean;
        std::cout << "de First element: " << firstElement << std::endl;
    } else {
        std::cout << "Vector epd de is empty." << std::endl;
    }

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      std::cout << "deuteron pt test 0.0.0: " << std::endl;
    	    std::cout << "jth cut: "<< jthCut << std::endl;
      if (!composites.at(jthCut)->v_vn_pT_00to10_de.empty()) {
          // Access the first element safely
    	    int firstElement = composites.at(jthCut)->v_vn_pT_00to10_de.at(0).mean;
    	    std::cout << "de First element: " << firstElement << std::endl;
    	} else {
    	    std::cout << "Vector composite de is empty." << std::endl;
            continue;
    	}
      if (composites.at(jthCut)->v_vn_pT_00to10_de.at(ithBin).deltaByDeltaError > 1.0)
      {
      	std::cout << "deuteron pt test 0.0.1: " << std::endl;
        quadSum += composites.at(jthCut)->v_vn_pT_00to10_de.at(ithBin).variance;
        avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pT_00to10_de.at(ithBin).stdDevPercentage);
      	std::cout << "deuteron pt test 0.0.2: " << std::endl;
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_pT_00to10_de.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  */
  //===


  //=== Deuteron vs pT 10 - 40%
  /*
  std::cout << "deuteron pt test 2: " << std::endl;
  std::vector<Double_t> v_sys_pT_10to40_de;
  bins = Normal->h_vn_pT_10to40_de->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
    quadSum += epd->v_vn_pT_10to40_de.at(ithBin).variance;
    
    if (ithBin > 1)
      avgTracker_10to40.addContribution(epd->ID, epd->v_vn_pT_10to40_de.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (!composites.at(jthCut)->v_vn_pT_10to40_de.empty()) {
          // Access the first element safely
    	    int firstElement = composites.at(jthCut)->v_vn_pT_10to40_de.at(0).mean;
    	    std::cout << "de yEnd First element: " << firstElement << std::endl;
    	} else {
    	    std::cout << "Vector composite de is empty." << std::endl;
            continue;
    	}
      if (composites.at(jthCut)->v_vn_pT_10to40_de.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_pT_10to40_de.at(ithBin).variance;
        avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pT_10to40_de.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_pT_10to40_de.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  */
  //===

  //=== Deuteron vs pT 40 - 60%
  /*
  std::vector<Double_t> v_sys_pT_40to60_de;
  bins = Normal->h_vn_pT_40to60_de->GetNbinsX();
  std::cout << "deuteron pt test 3: " << std::endl;
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
    quadSum += epd->v_vn_pT_40to60_de.at(ithBin).variance;
    
    if (ithBin > 1)
      avgTracker_40to60.addContribution(epd->ID, epd->v_vn_pT_40to60_de.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (!composites.at(jthCut)->v_vn_pT_40to60_de.empty()) {
          // Access the first element safely
    	    int firstElement = composites.at(jthCut)->v_vn_pT_40to60_de.at(0).mean;
    	    std::cout << "de 4060 First element: " << firstElement << std::endl;
    	} else {
    	    std::cout << "Vector composite de is empty." << std::endl;
            continue;
    	}
      if (composites.at(jthCut)->v_vn_pT_40to60_de.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_pT_40to60_de.at(ithBin).variance;
        avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pT_40to60_de.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_pT_40to60_de.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  */
  //===

  //=== Triton vs pT 0 - 10%
  /*
  std::cout << "triton pt test 0: " << std::endl;
  std::vector<Double_t> v_sys_pT_00to10_tr;
  bins = Normal->h_vn_pT_00to10_tr->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    if (!epd->v_vn_pT_00to10_tr.empty()) {
        // Access the first element safely
        int firstElement = epd->v_vn_pT_00to10_tr.at(0).mean;
        std::cout << "tr 0010 First element: " << firstElement << std::endl;
    } else {
        std::cout << "Vector epd tr is empty." << std::endl;
        continue; 
    }

    std::cout << "triton pt test 0.0: " << std::endl;
    quadSum = 0.0;
    quadSum += epd->v_vn_pT_00to10_tr.at(ithBin).variance;
    std::cout << "triton pt test 0.1: " << std::endl;
    
    if (ithBin > 1)
      avgTracker_00to10.addContribution(epd->ID, epd->v_vn_pT_00to10_tr.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      std::cout << "triton pt test 0.0.0: " << std::endl;
    	    std::cout << "jth cut: "<< jthCut << std::endl;
      if (!composites.at(jthCut)->v_vn_pT_00to10_tr.empty()) {
          // Access the first element safely
    	    int firstElement = composites.at(jthCut)->v_vn_pT_00to10_tr.at(0).mean;
    	    std::cout << "tr 0010 First element: " << firstElement << std::endl;
    	} else {
    	    std::cout << "Vector composite tr is empty." << std::endl;
            continue;
    	}
      if (composites.at(jthCut)->v_vn_pT_00to10_tr.at(ithBin).deltaByDeltaError > 1.0)
      {
      	std::cout << "triton pt test 0.0.1: " << std::endl;
        quadSum += composites.at(jthCut)->v_vn_pT_00to10_tr.at(ithBin).variance;
        avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pT_00to10_tr.at(ithBin).stdDevPercentage);
      	std::cout << "triton pt test 0.0.2: " << std::endl;
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_pT_00to10_tr.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  */
  //===

  //=== Triton vs pT 10 - 40%
  /*
  std::cout << "triton pt test 2: " << std::endl;
  std::vector<Double_t> v_sys_pT_10to40_tr;
  bins = Normal->h_vn_pT_10to40_tr->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
    quadSum += epd->v_vn_pT_10to40_tr.at(ithBin).variance;
    
    if (ithBin > 1)
      avgTracker_10to40.addContribution(epd->ID, epd->v_vn_pT_10to40_tr.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (!composites.at(jthCut)->v_vn_pT_10to40_tr.empty()) {
          // Access the first element safely
    	    int firstElement = composites.at(jthCut)->v_vn_pT_10to40_tr.at(0).mean;
    	    std::cout << "Triton 1040 First element: " << firstElement << std::endl;
    	} else {
    	    std::cout << "Vector composite tr is empty." << std::endl;
            continue;
    	}
      if (composites.at(jthCut)->v_vn_pT_10to40_tr.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_pT_10to40_tr.at(ithBin).variance;
        avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pT_10to40_tr.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_pT_10to40_tr.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  */
  //===

  //=== Triton vs pT 40 - 60%
  /*
  std::vector<Double_t> v_sys_pT_40to60_tr;
  bins = Normal->h_vn_pT_40to60_tr->GetNbinsX();
  std::cout << "triton pt test 3: " << std::endl;
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
    quadSum += epd->v_vn_pT_40to60_tr.at(ithBin).variance;
    
    if (ithBin > 1)
      avgTracker_40to60.addContribution(epd->ID, epd->v_vn_pT_40to60_tr.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (!composites.at(jthCut)->v_vn_pT_40to60_tr.empty()) {
          // Access the first element safely
    	    int firstElement = composites.at(jthCut)->v_vn_pT_40to60_tr.at(0).mean;
    	    std::cout << "Triton 4060 First element: " << firstElement << std::endl;
    	} else {
    	    std::cout << "Vector composite tr is empty." << std::endl;
            continue;
    	}
      if (composites.at(jthCut)->v_vn_pT_40to60_tr.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_pT_40to60_tr.at(ithBin).variance;
        avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_pT_40to60_tr.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_pT_40to60_tr.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  */
  //===


    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
 
    

    //=========== Symmetric Stuff

  //=== Proton vs rapidity 0 - 10% symmetric
  
  std::vector<Double_t> v_sys_yCM_00to10_pr_symm;
  bins = Normal->h_vn_yCM_00to10_pr_symm->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_00to10_pr_symm.at(ithBin).variance;
    
//     if (ithBin >= 0)
//       avgTracker_00to10.addContribution(epd->ID, epd->v_vn_yCM_00to10_pr_symm.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_00to10_pr_symm.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_00to10_pr_symm.at(ithBin).variance;
        avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_00to10_pr_symm.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_00to10_pr_symm.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
    
  //=== Proton vs rapidity 10 - 40% symmetric
 
  std::vector<Double_t> v_sys_yCM_10to40_pr_symm;
  bins = Normal->h_vn_yCM_10to40_pr_symm->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_10to40_pr_symm.at(ithBin).variance;
    
//     if (ithBin >= 0)
//       avgTracker_10to40.addContribution(epd->ID, epd->v_vn_yCM_10to40_pr_symm.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_10to40_pr_symm.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_10to40_pr_symm.at(ithBin).variance;
        avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_10to40_pr_symm.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_10to40_pr_symm.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  
  //===


  //=== Proton vs rapidity 40 - 60% symmetric
  
  std::vector<Double_t> v_sys_yCM_40to60_pr_symm;
  bins = Normal->h_vn_yCM_40to60_pr_symm->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
//     quadSum += epd->v_vn_yCM_40to60_pr_symm.at(ithBin).variance;
    
//     if (ithBin >= 0)
//       avgTracker_40to60.addContribution(epd->ID, epd->v_vn_yCM_40to60_pr_symm.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_40to60_pr_symm.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_40to60_pr_symm.at(ithBin).variance;
        avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_40to60_pr_symm.at(ithBin).stdDevPercentage);
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_40to60_pr_symm.push_back(ithBinSysErr);
  }
  ithBinSysErr = 0;
  quadSum = 0.0;
  
  //===
    
    
    
    
    
    
    
    
    
    
    
    

  std::cout << "0-10% Centrality" << std::endl;
  avgTracker_00to10.printContributions();  
  
  std::cout << "10-40% Centrality" << std::endl;
  avgTracker_10to40.printContributions();

  std::cout << "40-60% Centrality" << std::endl;
  avgTracker_40to60.printContributions();


  // PLOTTING
  TCanvas *canvas = new TCanvas("canvas", "Canvas", 1000, 1000);
  //canvas->SetGrid();
  canvas->SetTicks();
  canvas->SetLeftMargin(0.15);
  canvas->SetTopMargin(0.04);
  canvas->SetRightMargin(0.04);
  canvas->SetBottomMargin(0.1);
  canvas->cd();

  gStyle->SetOptStat(0);
  //gStyle->SetErrorX(0);
  gStyle->SetEndErrorSize(0);

  TLine *zeroLine = new TLine(0, 0, 60, 0);
  zeroLine->SetLineStyle(9);

  TLine *zeroLine_y = new TLine(0, 0, 1, 0);
  zeroLine_y->SetLineStyle(9);

  TLine *zeroLine_y_pr = new TLine(-1, 0, 1, 0);
  zeroLine_y_pr->SetLineStyle(9);

  TLine *zeroLine_y_de = new TLine(-1, 0, 1, 0);
  zeroLine_y_de->SetLineStyle(9);

  TLine *zeroLine_y_tr = new TLine(-1, 0, 1, 0);
  zeroLine_y_tr->SetLineStyle(9);

  TLine *zeroLine_pt = new TLine(0, 0, 2, 0);
  zeroLine_pt->SetLineStyle(9);

    
    

  //if (order_n_str == "3")
  if (order_n_str == "3")
    {      
      TLegend *piLegend = new TLegend(0.67, 0.71, 0.805, 0.87);
      piLegend->AddEntry(Normal->h_vn_pp,"#pi^{+}");
      piLegend->AddEntry(Normal->h_vn_pm,"#pi^{-}");
      piLegend->SetFillColorAlpha(0,0);
      piLegend->SetLineColorAlpha(0,0);

      TLegend *kaLegend = new TLegend(0.7, 0.72, 0.8, 0.87);
      kaLegend->AddEntry(Normal->h_vn_kp,"K^{+}");
      kaLegend->AddEntry(Normal->h_vn_km,"K^{-}");
      kaLegend->SetFillColorAlpha(0,0);
      kaLegend->SetLineColorAlpha(0,0);      

      TLegend *prLegend = new TLegend(0.19, 0.15, 0.39, 0.3);
      prLegend->AddEntry(Normal->h_vn_yCM_00to10_pr, "0 - 10%");
      prLegend->AddEntry(Normal->h_vn_yCM_10to40_pr, "10 - 40%");
      prLegend->AddEntry(Normal->h_vn_yCM_40to60_pr, "40 - 60%");
      prLegend->SetBorderSize(0);
      prLegend->SetFillColorAlpha(0,0);

//       TLegend *deLegend = new TLegend(0.19, 0.15, 0.39, 0.3);
//       deLegend->AddEntry(Normal->h_vn_yCM_00to10_de, "0 - 10%");
//       deLegend->AddEntry(Normal->h_vn_yCM_10to40_de, "10 - 40%");
//       deLegend->AddEntry(Normal->h_vn_yCM_40to60_de, "40 - 60%");
//       deLegend->SetBorderSize(0);
//       deLegend->SetFillColorAlpha(0,0);

//       TLegend *trLegend = new TLegend(0.19, 0.15, 0.39, 0.3);
//       trLegend->AddEntry(Normal->h_vn_yCM_00to10_tr, "0 - 10%");
//       trLegend->AddEntry(Normal->h_vn_yCM_10to40_tr, "10 - 40%");
//       trLegend->AddEntry(Normal->h_vn_yCM_40to60_tr, "40 - 60%");
//       trLegend->SetBorderSize(0);
//       trLegend->SetFillColorAlpha(0,0);


      
      
      


      // Assuming you have your layers and appendix_values defined as before
      //std::vector<TString> layers_p2_vn_pT_cent_pr = {"p2_vn_pT_cent_pr"};
      //std::vector<TString> appendix_values_pr = {"", "yMid", "yFor", "yExt", "yEnd"};

      //TCanvas* canvas = new TCanvas("canvas", "Legend Example", 800, 600);

      //std::vector<TLegend*> prPtLegends;

      // Loop through the layers and appendix values
      //for (const TString& layer : layers_p2_vn_pT_cent_pr) {
      //    for (const TString& appendix : appendix_values_pr) {
      //        TString legend_label = (appendix == "") ? "0 - 10%" : appendix;

      //        // Create a new TLegend object
      //        TString legend_name = "prPtLegend_" + layer + appendix;
      //        TLegend* prPtLegend = new TLegend(0.19, 0.15, 0.39, 0.3);
      //        prPtLegend->AddEntry(layer, legend_label);
      //        prPtLegend->SetBorderSize(0);
      //        prPtLegend->SetFillColorAlpha(0, 0);

      //        prPtLegends.push_back(prPtLegend);
      //    }
      //}

      // Draw the legends and perform other actions as needed
     // for (TLegend* prPtLegend : prPtLegends) {
     //     canvas->Draw();
     //     prPtLegend->Draw();

     //     // ... Other code ...

     //     // Clear the canvas and legend for the next iteration
     //     canvas->Clear();
     //     prPtLegend->Clear();
     // }


      
      TLegend *prPtLegend = new TLegend(0.19, 0.15, 0.39, 0.3);
      prPtLegend->AddEntry(Normal->h_vn_pT_00to10_pr, "0 - 10%");
      prPtLegend->AddEntry(Normal->h_vn_pT_10to40_pr, "10 - 40%");
      prPtLegend->AddEntry(Normal->h_vn_pT_40to60_pr, "40 - 60%");
      prPtLegend->SetBorderSize(0);
      prPtLegend->SetFillColorAlpha(0,0);


//       TLegend *dePtLegend = new TLegend(0.19, 0.15, 0.39, 0.3);
//       dePtLegend->AddEntry(Normal->h_vn_pT_00to10_de, "0 - 10%");
//       dePtLegend->AddEntry(Normal->h_vn_pT_10to40_de, "10 - 40%");
//       dePtLegend->AddEntry(Normal->h_vn_pT_40to60_de, "40 - 60%");
//       dePtLegend->SetBorderSize(0);
//       dePtLegend->SetFillColorAlpha(0,0);


//       TLegend *trPtLegend = new TLegend(0.19, 0.15, 0.39, 0.3);
//       trPtLegend->AddEntry(Normal->h_vn_pT_00to10_tr, "0 - 10%");
//       trPtLegend->AddEntry(Normal->h_vn_pT_10to40_tr, "10 - 40%");
//       trPtLegend->AddEntry(Normal->h_vn_pT_40to60_tr, "40 - 60%");
//       trPtLegend->SetBorderSize(0);
//       trPtLegend->SetFillColorAlpha(0,0);



      
      TPaveText *piText = new TPaveText(5, 0.025, 38, 0.07, "NB");
      piText->AddText("Au+Au #sqrt{s_{NN}} = 3.0 GeV FXT");
      piText->AddText("0 < y_{CM} < 0.5 GeV");
      piText->AddText("0.18 < p_{T} < 1.6 GeV");
      piText->SetFillColorAlpha(0,0);
      piText->SetLineColorAlpha(0,0);

      TPaveText *kaText = new TPaveText(5, 0.025, 38, 0.07, "NB");
      kaText->AddText("Au+Au #sqrt{s_{NN}} = 3.0 GeV FXT");
      kaText->AddText("0 < y_{CM} < 0.5 GeV");
      kaText->AddText("0.4 < p_{T} < 1.6 GeV");
      kaText->SetFillColorAlpha(0,0);
      kaText->SetLineColorAlpha(0,0);
      
//       TPaveText *prText = new TPaveText(5, 0.025, 38, 0.07, "NB");
//       prText->AddText("Proton");
//       prText->AddText("Au+Au #sqrt{s_{NN}} = 3.0 GeV FXT");
//       prText->AddText("0 < y_{CM} < 0.5 GeV");
//       prText->AddText("0.4 < p_{T} < 2.0 GeV");
//       prText->SetFillColorAlpha(0,0);
//       prText->SetLineColorAlpha(0,0);
      
//       TPaveText *deText = new TPaveText(5, 0.025, 38, 0.07, "NB");
//       deText->AddText("Deuteron");
//       deText->AddText("Au+Au #sqrt{s_{NN}} = 3.0 GeV FXT");
//       deText->AddText("0 < y_{CM} < 0.5 GeV");
//       deText->AddText("0.4 < p_{T} < 2.0 GeV");
//       deText->SetFillColorAlpha(0,0);
//       deText->SetLineColorAlpha(0,0);
      
//       TPaveText *trText = new TPaveText(5, 0.025, 38, 0.07, "NB");
//       trText->AddText("Deuteron");
//       trText->AddText("Au+Au #sqrt{s_{NN}} = 3.0 GeV FXT");
//       trText->AddText("0 < y_{CM} < 0.5 GeV");
//       trText->AddText("0.4 < p_{T} < 2.0 GeV");
//       trText->SetFillColorAlpha(0,0);
//       trText->SetLineColorAlpha(0,0);

      
      TPaveText *prText_y = new TPaveText(-0.2, 0.02, 0.9, 0.05, "NB");
      prText_y->AddText("Proton");
      prText_y->AddText("Au+Au #sqrt{s_{NN}} = 3.0 GeV FXT");
      prText_y->AddText("0.4 < p_{T} < 2.0 GeV");
      prText_y->SetFillColorAlpha(0,0);
      prText_y->SetLineColorAlpha(0,0);
      prText_y->SetTextSize(.035);
      
      TPaveText *prText_y_symm = new TPaveText(-0.2, 0.02, 0.9, 0.05, "NB");
      prText_y_symm->AddText("Proton");
      prText_y_symm->AddText("Au+Au #sqrt{s_{NN}} = 3.0 GeV FXT");
      prText_y_symm->AddText("1.0 < p_{T} < 2.5 GeV");
      prText_y_symm->SetFillColorAlpha(0,0);
      prText_y_symm->SetLineColorAlpha(0,0);
      prText_y_symm->SetTextSize(.035);
      
      TPaveText *deText_y = new TPaveText(-0.2, 0.02, 0.9, 0.05, "NB");
      deText_y->AddText("Deuteron");
      deText_y->AddText("Au+Au #sqrt{s_{NN}} = 3.0 GeV FXT");
      deText_y->AddText("0.4 < p_{T} < 2.0 GeV");
      deText_y->SetFillColorAlpha(0,0);
      deText_y->SetLineColorAlpha(0,0);
      deText_y->SetTextSize(.035);
      
      TPaveText *trText_y = new TPaveText(-0.2, 0.02, 0.9, 0.05, "NB");
      trText_y->AddText("Triton");
      trText_y->AddText("Au+Au #sqrt{s_{NN}} = 3.0 GeV FXT");
      trText_y->AddText("0.4 < p_{T} < 2.0 GeV");
      trText_y->SetFillColorAlpha(0,0);
      trText_y->SetLineColorAlpha(0,0);
      trText_y->SetTextSize(.035);
      
      TPaveText *prPtText = new TPaveText(0.2, 0.07, 1.2, 0.18, "NB");
      prPtText->AddText("Proton");
      prPtText->AddText("Au+Au #sqrt{s_{NN}} = 3.0 GeV FXT");
      prPtText->AddText("0 < y_{CM} < 0.5");
      prPtText->SetFillColorAlpha(0,0);
      prPtText->SetLineColorAlpha(0,0);
      prPtText->SetTextSize(.04);

      newFile->cd();
      
      Double_t centralityUpperBound = 0.9;
      Double_t centralityLowerBound = -0.08;
      Double_t rapidityUpperBound = 0.28;
      Double_t rapidityLowerBound = -0.08;
      Double_t rapidityUpperBound_pr = 0.50;
      Double_t rapidityLowerBound_pr = -0.50;
      Double_t rapidityUpperBound_de = 0.90;
      Double_t rapidityLowerBound_de = -0.50;
      Double_t rapidityUpperBound_tr = 0.90;
      Double_t rapidityLowerBound_tr = -0.50;
//       Double_t rapidityUpperBound_he3 = 0.90;
//       Double_t rapidityLowerBound_he3 = -0.50;
//       Double_t rapidityUpperBound_he4 = 0.90;
//       Double_t rapidityLowerBound_he4 = -0.50;
//       Double_t ptUpperBound = 0.9;
//       Double_t ptLowerBound = -0.08;
      
      //Double_t centralityUpperBound = 0.08;
      //Double_t centralityLowerBound = -0.08;
      //Double_t rapidityUpperBound = 0.15;
      //Double_t rapidityLowerBound = -0.1;
      //Double_t rapidityUpperBound_pr = 0.06;
      //Double_t rapidityLowerBound_pr = -0.1;
      Double_t ptUpperBound = 0.25;
      Double_t ptLowerBound = -0.25;
      TGraphErrors *copyWithNewErrors1;
      TGraphErrors *copyWithNewErrors2;
      TGraphErrors *copyWithNewErrors3;
//       TGraphErrors *copyWithNewErrors4;
//       TGraphErrors *copyWithNewErrors5;
  

      
      
      
// =============== Vn vs Centrality

      
      //=== Proton vs centrality
      THStack *prCentralityStack = new THStack("prCentralityStack", ";Centrality (%);v_{"+order_n_str+"}");
      prCentralityStack->Add(Normal->h_vn_pr);
      
      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pr->Clone());
      for (int i = 0; i < v_sys_pr.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_pr.at(i)); }
      
      Normal->h_vn_pr->SetMarkerStyle(20);
      Normal->h_vn_pr->SetLineWidth(0);
      Normal->h_vn_pr->SetMarkerColor(kBlue);
      Normal->h_vn_pr->SetLineColor(kBlue);
      prCentralityStack->Draw();
      prCentralityStack->SetMinimum(0);
      prCentralityStack->SetMaximum(1);
      prCentralityStack->Draw("NOSTACK E1P X0");
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
//       zeroLine->Draw("SAME");
//       prText->Draw();
      canvas->SaveAs("sys_h_vn_pr.png");
      canvas->Clear();
      Normal->h_vn_pr->Write();
      copyWithNewErrors1->Write();      
//       std::cout << "sys_h_vn_pr.png should be saved" << std::endl;
      delete copyWithNewErrors1;
      //===
      
      
      //=== K+ vs centrality
      THStack *kpCentralityStack = new THStack("kpCentralityStack", ";Centrality (%);v_{"+order_n_str+"}");
      kpCentralityStack->Add(Normal->h_vn_kp);
      
      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_kp->Clone());
      for (int i = 0; i < v_sys_kp.size(); i++)
       { copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_kp.at(i)); }

      copyWithNewErrors1->Write();


      Normal->h_vn_kp->SetMarkerStyle(20);
      Normal->h_vn_kp->SetLineWidth(0);
      Normal->h_vn_kp->SetMarkerColor(kBlue);
      Normal->h_vn_kp->SetLineColor(kBlue);
      kpCentralityStack->Draw();
      kpCentralityStack->SetMinimum(0);
      kpCentralityStack->SetMaximum(1);
      kpCentralityStack->Draw("NOSTACK E1P X0");
//       zeroLine->Draw("SAME");
//       kaLegend->Draw();
//       kaText->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_h_vn_kp.png");
      canvas->Clear();
      Normal->h_vn_kp->Write();
      copyWithNewErrors1->Write();      
      delete copyWithNewErrors1;
      //===
      
      
      
      //=== K- vs centrality
      THStack *kmCentralityStack = new THStack("kmCentralityStack", ";Centrality (%);v_{"+order_n_str+"}");
      kmCentralityStack->Add(Normal->h_vn_km);
      
      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_km->Clone());
      for (int i = 0; i < v_sys_km.size(); i++)
       { copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_km.at(i)); }

      copyWithNewErrors1->Write();

      Normal->h_vn_km->SetMarkerStyle(20);
      Normal->h_vn_km->SetLineWidth(0);
      Normal->h_vn_km->SetMarkerColor(kBlue);
      Normal->h_vn_km->SetLineColor(kBlue);
      kmCentralityStack->Draw();
      kmCentralityStack->SetMinimum(0);
      kmCentralityStack->SetMaximum(1);
      kmCentralityStack->Draw("NOSTACK E1P X0");
//       zeroLine->Draw("SAME");
//       kaLegend->Draw();
//       kaText->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_h_vn_km.png");
      canvas->Clear();
      Normal->h_vn_km->Write();
      copyWithNewErrors1->Write(); 
      delete copyWithNewErrors1;
      //===

      //=== pi+ vs centrality
      THStack *ppCentralityStack = new THStack("ppCentralityStack", ";Centrality (%);v_{"+order_n_str+"}");
      ppCentralityStack->Add(Normal->h_vn_pp);      
      
      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pp->Clone());
      for (int i = 0; i < v_sys_pp.size(); i++)
       { copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_pp.at(i)); }

      copyWithNewErrors1->Write();

      Normal->h_vn_pp->SetMarkerStyle(20);
      Normal->h_vn_pp->SetLineWidth(0);
      Normal->h_vn_pp->SetMarkerColor(kBlue);
      Normal->h_vn_pp->SetLineColor(kBlue);
      ppCentralityStack->Draw();
      ppCentralityStack->SetMinimum(.5);
      ppCentralityStack->SetMaximum(1);
      ppCentralityStack->Draw("NOSTACK E1P X0");
//       zeroLine->Draw("SAME");
//       piLegend->Draw();
//       piText->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_h_vn_pp.png");
      canvas->Clear();
      Normal->h_vn_pp->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===
      
      
      //=== pi- vs centrality
      THStack *pmCentralityStack = new THStack("pmCentralityStack", ";Centrality (%);v_{"+order_n_str+"}");
      pmCentralityStack->Add(Normal->h_vn_pm);
      
      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pm->Clone());
      for (int i = 0; i < v_sys_pm.size(); i++)
       { copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_pm.at(i)); }

      copyWithNewErrors1->Write();

      Normal->h_vn_pm->SetMarkerStyle(20);
      Normal->h_vn_pm->SetLineWidth(0);
      Normal->h_vn_pm->SetMarkerColor(kBlue);
      Normal->h_vn_pm->SetLineColor(kBlue);      
      pmCentralityStack->Draw();
      pmCentralityStack->SetMinimum(0);
      pmCentralityStack->SetMaximum(1);
      pmCentralityStack->Draw("NOSTACK E1P X0");
//       zeroLine->Draw("SAME");
//       piLegend->Draw();
//       piText->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_h_vn_pm.png");
      canvas->Clear();
      Normal->h_vn_pm->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===


      //=== Deuteron vs centrality
      THStack *deCentralityStack = new THStack("deCentralityStack", ";Centrality (%);v_{"+order_n_str+"}");
      deCentralityStack->Add(Normal->h_vn_de);
      
      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_de->Clone());
      for (int i = 0; i < v_sys_de.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_de.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_de->SetMarkerStyle(20);
      Normal->h_vn_de->SetLineWidth(0);
      Normal->h_vn_de->SetMarkerColor(kBlue);
      Normal->h_vn_de->SetLineColor(kBlue);
      deCentralityStack->Draw();
      deCentralityStack->SetMinimum(0);
      deCentralityStack->SetMaximum(1);
      deCentralityStack->Draw("NOSTACK E1P X0");
      copyWithNewErrors1->Draw("E2");
//       zeroLine->Draw("SAME");
//       deText->Draw();
      canvas->SaveAs("sys_h_vn_de.png");
      canvas->Clear();
      Normal->h_vn_de->Write();
      copyWithNewErrors1->Write();
//      std::cout << "sys_h_vn_de.png should be saved" << std::endl;
      delete copyWithNewErrors1;
      //===


      //=== Triton vs centrality
      THStack *trCentralityStack = new THStack("trCentralityStack", ";Centrality (%);v_{"+order_n_str+"}");
      trCentralityStack->Add(Normal->h_vn_tr);
      
      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_tr->Clone());
      for (int i = 0; i < v_sys_tr.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_tr.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_tr->SetMarkerStyle(20);
      Normal->h_vn_tr->SetLineWidth(0);
      Normal->h_vn_tr->SetMarkerColor(kBlue);
      Normal->h_vn_tr->SetLineColor(kBlue);
      trCentralityStack->Draw();
      trCentralityStack->SetMinimum(0);
      trCentralityStack->SetMaximum(1);
      trCentralityStack->Draw("NOSTACK E1P X0");
      copyWithNewErrors1->Draw("E2");
//       zeroLine->Draw("SAME");
//       trText->Draw();
      canvas->SaveAs("sys_h_vn_tr.png");
      canvas->Clear();
      Normal->h_vn_tr->Write();
      copyWithNewErrors1->Write();
//      std::cout << "sys_h_vn_tr.png should be saved" << std::endl;
      delete copyWithNewErrors1;
      //===

      
      
      
      
      
      


//============= Vn vs Rapidity

      //=== Proton vs rapidity 0-10
      THStack *prRapidityStackLow = new THStack("prRapidityStackLow", ";y-y_{mid};v_{"+order_n_str+"}");
      prRapidityStackLow->Add(Normal->h_vn_yCM_00to10_pr);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_00to10_pr->Clone());
      for (int i = 0; i < v_sys_yCM_00to10_pr.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_00to10_pr.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_00to10_pr->SetMarkerStyle(20);
      Normal->h_vn_yCM_00to10_pr->SetLineWidth(0);
      Normal->h_vn_yCM_00to10_pr->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_00to10_pr->SetLineColor(kBlue);
      prRapidityStackLow->Draw();
//       prRapidityStackLow->GetYaxis()->SetTitleOffset(1.9);
//       prRapidityStackLow->GetXaxis()->SetNdivisions(210);
      prRapidityStackLow->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      prRapidityStackLow->SetMaximum(-0.011);
      prRapidityStackLow->SetMinimum(0.003);
//       prRapidityStackLow->GetXaxis()->SetTitleSize(0.045);
//       prRapidityStackLow->GetYaxis()->SetTitleSize(0.05);
//       prRapidityStackLow->GetXaxis()->SetRangeUser(0, 1);
      prRapidityStackLow->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_prRapidity_00-10.png");
      canvas->Clear();
      Normal->h_vn_yCM_00to10_pr->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
//       //===
      
      
//       //=== Proton vs rapidity 10-40
      THStack *prRapidityStackMiddle = new THStack("prRapidityStackMiddle", ";y-y_{mid};v_{"+order_n_str+"}");
      prRapidityStackMiddle->Add(Normal->h_vn_yCM_10to40_pr);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_10to40_pr->Clone());
      for (int i = 0; i < v_sys_yCM_10to40_pr.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_10to40_pr.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_10to40_pr->SetMarkerStyle(20);
      Normal->h_vn_yCM_10to40_pr->SetLineWidth(0);
      Normal->h_vn_yCM_10to40_pr->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_10to40_pr->SetLineColor(kBlue);
      prRapidityStackMiddle->Draw();
//       prRapidityStackMiddle->GetYaxis()->SetTitleOffset(1.9);
//       prRapidityStackMiddle->GetXaxis()->SetNdivisions(210);
      prRapidityStackMiddle->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      prRapidityStackMiddle->SetMaximum(0);
      prRapidityStackMiddle->SetMinimum(-0.02);
//       prRapidityStackMiddle->GetXaxis()->SetTitleSize(0.045);
//       prRapidityStackMiddle->GetYaxis()->SetTitleSize(0.05);
//       prRapidityStackMiddle->GetXaxis()->SetRangeUser(0, 1);
      prRapidityStackMiddle->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_prRapidity_10-40.png");
      canvas->Clear();
      Normal->h_vn_yCM_10to40_pr->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
//       //===
      
      
//       //=== Proton vs rapidity 40-60
      THStack *prRapidityStackHigh = new THStack("prRapidityStackHigh", ";y-y_{mid};v_{"+order_n_str+"}");
      prRapidityStackHigh->Add(Normal->h_vn_yCM_40to60_pr);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_40to60_pr->Clone());
      for (int i = 0; i < v_sys_yCM_40to60_pr.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_40to60_pr.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_40to60_pr->SetMarkerStyle(20);
      Normal->h_vn_yCM_40to60_pr->SetLineWidth(0);
      Normal->h_vn_yCM_40to60_pr->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_40to60_pr->SetLineColor(kBlue);
      prRapidityStackHigh->Draw();
//       prRapidityStackHigh->GetYaxis()->SetTitleOffset(1.9);
//       prRapidityStackHigh->GetXaxis()->SetNdivisions(210);
      prRapidityStackHigh->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      prRapidityStackHigh->SetMaximum(0);
      prRapidityStackHigh->SetMinimum(-0.05);
//       prRapidityStackHigh->GetXaxis()->SetTitleSize(0.045);
//       prRapidityStackHigh->GetYaxis()->SetTitleSize(0.05);
//       prRapidityStackHigh->GetXaxis()->SetRangeUser(0, 1);
      prRapidityStackHigh->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_prRapidity_40-60.png");
      canvas->Clear();
      Normal->h_vn_yCM_40to60_pr->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===
         
      
      
        //=== Proton vs rapidity symmetric 0-10
      THStack *prRapiditySymmetricStackLow = new THStack("prRapiditySymmetricStackLow", ";y-y_{mid};v_{"+order_n_str+"}");
      prRapiditySymmetricStackLow->Add(Normal->h_vn_yCM_00to10_pr_symm);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_00to10_pr_symm->Clone());
      for (int i = 0; i < v_sys_yCM_00to10_pr_symm.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_00to10_pr_symm.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_00to10_pr_symm->SetMarkerStyle(20);
      Normal->h_vn_yCM_00to10_pr_symm->SetLineWidth(0);
      Normal->h_vn_yCM_00to10_pr_symm->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_00to10_pr_symm->SetLineColor(kBlue);
      prRapiditySymmetricStackLow->Draw();
      //prRapiditySymmetricStackLow->GetYaxis()->SetTitleOffset(1.9);
      //prRapiditySymmetricStackLow->GetXaxis()->SetNdivisions(210);
      prRapiditySymmetricStackLow->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      prRapiditySymmetricStackLow->SetMaximum(-0.011);
      prRapiditySymmetricStackLow->SetMinimum(0.003);
      //prRapiditySymmetricStackLow->GetXaxis()->SetTitleSize(0.045);
      //prRapiditySymmetricStackLow->GetYaxis()->SetTitleSize(0.05);
      //prRapiditySymmetricStackLow->GetXaxis()->SetRangeUser(0, 1);
      prRapiditySymmetricStackLow->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_prRapiditySymmetric_00-10.png");
      canvas->Clear();
      Normal->h_vn_yCM_00to10_pr_symm->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //=== 
      
      
      //=== Proton vs rapidity symmetric 10-40
      THStack *prRapiditySymmetricStackMiddle = new THStack("prRapiditySymmetricStackMiddle", ";y-y_{mid};v_{"+order_n_str+"}");
      prRapiditySymmetricStackMiddle->Add(Normal->h_vn_yCM_10to40_pr_symm);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_10to40_pr_symm->Clone());
      for (int i = 0; i < v_sys_yCM_10to40_pr_symm.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_10to40_pr_symm.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_10to40_pr_symm->SetMarkerStyle(20);
      Normal->h_vn_yCM_10to40_pr_symm->SetLineWidth(0);
      Normal->h_vn_yCM_10to40_pr_symm->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_10to40_pr_symm->SetLineColor(kBlue);
      prRapiditySymmetricStackMiddle->Draw();
//       prRapidityStackMiddle->GetYaxis()->SetTitleOffset(1.9);
//       prRapidityStackMiddle->GetXaxis()->SetNdivisions(210);
      prRapiditySymmetricStackMiddle->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      prRapiditySymmetricStackMiddle->SetMaximum(0);
      prRapiditySymmetricStackMiddle->SetMinimum(-0.02);
//       prRapidityStackMiddle->GetXaxis()->SetTitleSize(0.045);
//       prRapidityStackMiddle->GetYaxis()->SetTitleSize(0.05);
//       prRapidityStackMiddle->GetXaxis()->SetRangeUser(0, 1);
      prRapiditySymmetricStackMiddle->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_prRapiditySymmetric_10-40.png");
      canvas->Clear();
      Normal->h_vn_yCM_10to40_pr_symm->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===
      
      
      //=== Proton vs rapidity symmetric 40-60
      THStack *prRapiditySymmetricStackHigh = new THStack("prRapiditySymmetricStackHigh", ";y-y_{mid};v_{"+order_n_str+"}");
      prRapiditySymmetricStackHigh->Add(Normal->h_vn_yCM_40to60_pr_symm);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_40to60_pr_symm->Clone());
      for (int i = 0; i < v_sys_yCM_40to60_pr_symm.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_40to60_pr_symm.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_40to60_pr_symm->SetMarkerStyle(20);
      Normal->h_vn_yCM_40to60_pr_symm->SetLineWidth(0);
      Normal->h_vn_yCM_40to60_pr_symm->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_40to60_pr_symm->SetLineColor(kBlue);
      prRapiditySymmetricStackHigh->Draw();
//       prRapidityStackHigh->GetYaxis()->SetTitleOffset(1.9);
//       prRapidityStackHigh->GetXaxis()->SetNdivisions(210);
      prRapiditySymmetricStackHigh->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      prRapiditySymmetricStackHigh->SetMaximum(0);
      prRapiditySymmetricStackHigh->SetMinimum(-0.05);
//       prRapidityStackHigh->GetXaxis()->SetTitleSize(0.045);
//       prRapidityStackHigh->GetYaxis()->SetTitleSize(0.05);
//       prRapidityStackHigh->GetXaxis()->SetRangeUser(0, 1);
      prRapiditySymmetricStackHigh->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_prRapiditySymmetric_40-60.png");
      canvas->Clear();
      Normal->h_vn_yCM_40to60_pr_symm->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1; 
     
/*      
      //=== K+ vs rapidity 0-10
      THStack *kpRapidityStackLow = new THStack("kpRapidityStackLow", ";y-y_{mid};v_{"+order_n_str+"}");
      kpRapidityStackLow->Add(Normal->h_vn_yCM_00to10_kp);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_00to10_kp->Clone());
      for (int i = 0; i < v_sys_yCM_00to10_kp.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_00to10_kp.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_00to10_kp->SetMarkerStyle(20);
      Normal->h_vn_yCM_00to10_kp->SetLineWidth(0);
      Normal->h_vn_yCM_00to10_kp->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_00to10_kp->SetLineColor(kBlue);
      kpRapidityStackLow->Draw();
      kpRapidityStackLow->GetYaxis()->SetTitleOffset(1.9);
      kpRapidityStackLow->GetXaxis()->SetNdivisions(210);
      kpRapidityStackLow->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      kpRapidityStackLow->SetMaximum(0.1);
      kpRapidityStackLow->SetMinimum(-0.15);
      kpRapidityStackLow->GetXaxis()->SetTitleSize(0.045);
      kpRapidityStackLow->GetYaxis()->SetTitleSize(0.05);
      kpRapidityStackLow->GetXaxis()->SetRangeUser(0, 1);
      kpRapidityStackLow->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_kpRapidity_00-10.png");
      canvas->Clear();
      Normal->h_vn_yCM_00to10_kp->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===
*/
/*
      
      //=== K+ vs rapidity 10-40
      THStack *kpRapidityStackMiddle = new THStack("kpRapidityStackMiddle", ";y-y_{mid};v_{"+order_n_str+"}");
      kpRapidityStackMiddle->Add(Normal->h_vn_yCM_10to40_kp);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_10to40_kp->Clone());
      for (int i = 0; i < v_sys_yCM_10to40_kp.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_10to40_kp.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_10to40_kp->SetMarkerStyle(20);
      Normal->h_vn_yCM_10to40_kp->SetLineWidth(0);
      Normal->h_vn_yCM_10to40_kp->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_10to40_kp->SetLineColor(kBlue);
      kpRapidityStackMiddle->Draw();
      kpRapidityStackMiddle->GetYaxis()->SetTitleOffset(1.9);
      kpRapidityStackMiddle->GetXaxis()->SetNdivisions(210);
      kpRapidityStackMiddle->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      kpRapidityStackMiddle->SetMaximum(0.01);
      kpRapidityStackMiddle->SetMinimum(-0.03);
      kpRapidityStackMiddle->GetXaxis()->SetTitleSize(0.045);
      kpRapidityStackMiddle->GetYaxis()->SetTitleSize(0.05);
      kpRapidityStackMiddle->GetXaxis()->SetRangeUser(0, 1);
      kpRapidityStackMiddle->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_kpRapidity_10-40.png");
      canvas->Clear();
      Normal->h_vn_yCM_10to40_kp->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===
*/
/*
      
      //=== K+ vs rapidity 40-60
      THStack *kpRapidityStackHigh = new THStack("kpRapidityStackHigh", ";y-y_{mid};v_{"+order_n_str+"}");
      kpRapidityStackHigh->Add(Normal->h_vn_yCM_40to60_kp);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_40to60_kp->Clone());
      for (int i = 0; i < v_sys_yCM_40to60_kp.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_40to60_kp.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_40to60_kp->SetMarkerStyle(20);
      Normal->h_vn_yCM_40to60_kp->SetLineWidth(0);
      Normal->h_vn_yCM_40to60_kp->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_40to60_kp->SetLineColor(kBlue);
      kpRapidityStackHigh->Draw();
      kpRapidityStackHigh->GetYaxis()->SetTitleOffset(1.9);
      kpRapidityStackHigh->GetXaxis()->SetNdivisions(210);
      kpRapidityStackHigh->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      kpRapidityStackHigh->SetMaximum(0.1);
      kpRapidityStackHigh->SetMinimum(-0.15);
      kpRapidityStackHigh->GetXaxis()->SetTitleSize(0.045);
      kpRapidityStackHigh->GetYaxis()->SetTitleSize(0.05);
      kpRapidityStackHigh->GetXaxis()->SetRangeUser(0, 1);
      kpRapidityStackHigh->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_kpRapidity_40-60.png");
      canvas->Clear();
      Normal->h_vn_yCM_40to60_kp->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===
*/
/*
      
      //=== K- vs rapidity 0-10
      THStack *kmRapidityStackLow = new THStack("kmRapidityStackLow", ";y-y_{mid};v_{"+order_n_str+"}");
      kmRapidityStackLow->Add(Normal->h_vn_yCM_00to10_km);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_00to10_km->Clone());
      for (int i = 0; i < v_sys_yCM_00to10_km.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_00to10_km.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_00to10_km->SetMarkerStyle(20);
      Normal->h_vn_yCM_00to10_km->SetLineWidth(0);
      Normal->h_vn_yCM_00to10_km->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_00to10_km->SetLineColor(kBlue);
      kmRapidityStackLow->Draw();
      kmRapidityStackLow->GetYaxis()->SetTitleOffset(1.9);
      kmRapidityStackLow->GetXaxis()->SetNdivisions(210);
      kmRapidityStackLow->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      kmRapidityStackLow->SetMaximum(0.6);
      kmRapidityStackLow->SetMinimum(-0.4);
      kmRapidityStackLow->GetXaxis()->SetTitleSize(0.045);
      kmRapidityStackLow->GetYaxis()->SetTitleSize(0.05);
      kmRapidityStackLow->GetXaxis()->SetRangeUser(0, 1);
      kmRapidityStackLow->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_kmRapidity_00-10.png");
      canvas->Clear();
      Normal->h_vn_yCM_00to10_km->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===
      
      
      //=== K- vs rapidity 10-40
      THStack *kmRapidityStackMiddle = new THStack("kmRapidityStackMiddle", ";y-y_{mid};v_{"+order_n_str+"}");
      kmRapidityStackMiddle->Add(Normal->h_vn_yCM_10to40_km);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_10to40_km->Clone());
      for (int i = 0; i < v_sys_yCM_10to40_km.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_10to40_km.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_10to40_km->SetMarkerStyle(20);
      Normal->h_vn_yCM_10to40_km->SetLineWidth(0);
      Normal->h_vn_yCM_10to40_km->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_10to40_km->SetLineColor(kBlue);
      kmRapidityStackMiddle->Draw();
      kmRapidityStackMiddle->GetYaxis()->SetTitleOffset(1.9);
      kmRapidityStackMiddle->GetXaxis()->SetNdivisions(210);
      kmRapidityStackMiddle->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      kmRapidityStackMiddle->SetMaximum(0.15);
      kmRapidityStackMiddle->SetMinimum(-0.05);
      kmRapidityStackMiddle->GetXaxis()->SetTitleSize(0.045);
      kmRapidityStackMiddle->GetYaxis()->SetTitleSize(0.05);
      kmRapidityStackMiddle->GetXaxis()->SetRangeUser(0, 1);
      kmRapidityStackMiddle->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_kmRapidity_10-40.png");
      canvas->Clear();
      Normal->h_vn_yCM_10to40_km->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===
      
      
      //=== K- vs rapidity 40-60
      THStack *kmRapidityStackHigh = new THStack("kmRapidityStackHigh", ";y-y_{mid};v_{"+order_n_str+"}");
      kmRapidityStackHigh->Add(Normal->h_vn_yCM_40to60_km);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_40to60_km->Clone());
      for (int i = 0; i < v_sys_yCM_40to60_km.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_40to60_km.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_40to60_km->SetMarkerStyle(20);
      Normal->h_vn_yCM_40to60_km->SetLineWidth(0);
      Normal->h_vn_yCM_40to60_km->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_40to60_km->SetLineColor(kBlue);
      kmRapidityStackHigh->Draw();
      kmRapidityStackHigh->GetYaxis()->SetTitleOffset(1.9);
      kmRapidityStackHigh->GetXaxis()->SetNdivisions(210);
      kmRapidityStackHigh->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      kmRapidityStackHigh->SetMaximum(0.4);
      kmRapidityStackHigh->SetMinimum(-0.2);
      kmRapidityStackHigh->GetXaxis()->SetTitleSize(0.045);
      kmRapidityStackHigh->GetYaxis()->SetTitleSize(0.05);
      kmRapidityStackHigh->GetXaxis()->SetRangeUser(0, 1);
      kmRapidityStackHigh->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_kmRapidity_40-60.png");
      canvas->Clear();
      Normal->h_vn_yCM_40to60_km->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===
*/
/*
      
      //=== Pi+ vs rapidity 0-10
      THStack *ppRapidityStackLow = new THStack("ppRapidityStackLow", ";y-y_{mid};v_{"+order_n_str+"}");
      ppRapidityStackLow->Add(Normal->h_vn_yCM_00to10_pp);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_00to10_pp->Clone());
      for (int i = 0; i < v_sys_yCM_00to10_pp.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_00to10_pp.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_00to10_pp->SetMarkerStyle(20);
      Normal->h_vn_yCM_00to10_pp->SetLineWidth(0);
      Normal->h_vn_yCM_00to10_pp->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_00to10_pp->SetLineColor(kBlue);
      ppRapidityStackLow->Draw();
      ppRapidityStackLow->GetYaxis()->SetTitleOffset(1.9);
      ppRapidityStackLow->GetXaxis()->SetNdivisions(210);
      ppRapidityStackLow->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      ppRapidityStackLow->SetMaximum(0);
      ppRapidityStackLow->SetMinimum(-0.02);
      ppRapidityStackLow->GetXaxis()->SetTitleSize(0.05);
      ppRapidityStackLow->GetYaxis()->SetTitleSize(-0.05);
      ppRapidityStackLow->GetXaxis()->SetRangeUser(0, 1);
      ppRapidityStackLow->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_ppRapidity_00-10.png");
      canvas->Clear();
      Normal->h_vn_yCM_00to10_pp->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===
      
      
      //=== Pi+ vs rapidity 10-40
      THStack *ppRapidityStackMiddle = new THStack("ppRapidityStackMiddle", ";y-y_{mid};v_{"+order_n_str+"}");
      ppRapidityStackMiddle->Add(Normal->h_vn_yCM_10to40_pp);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_10to40_pp->Clone());
      for (int i = 0; i < v_sys_yCM_10to40_pp.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_10to40_pp.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_10to40_pp->SetMarkerStyle(20);
      Normal->h_vn_yCM_10to40_pp->SetLineWidth(0);
      Normal->h_vn_yCM_10to40_pp->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_10to40_pp->SetLineColor(kBlue);
      ppRapidityStackMiddle->Draw();
      ppRapidityStackMiddle->GetYaxis()->SetTitleOffset(1.9);
      ppRapidityStackMiddle->GetXaxis()->SetNdivisions(210);
      ppRapidityStackMiddle->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      ppRapidityStackMiddle->SetMaximum(0.005);
      ppRapidityStackMiddle->SetMinimum(-0.005);
      ppRapidityStackMiddle->GetXaxis()->SetTitleSize(0.045);
      ppRapidityStackMiddle->GetYaxis()->SetTitleSize(0.05);
      ppRapidityStackMiddle->GetXaxis()->SetRangeUser(0, 1);
      ppRapidityStackMiddle->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_ppRapidity_10-40.png");
      canvas->Clear();
      Normal->h_vn_yCM_10to40_pp->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===
      
      
      //=== Pi+ vs rapidity 40-60
      THStack *ppRapidityStackHigh = new THStack("ppRapidityStackHigh", ";y-y_{mid};v_{"+order_n_str+"}");
      ppRapidityStackHigh->Add(Normal->h_vn_yCM_40to60_pp);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_40to60_pp->Clone());
      for (int i = 0; i < v_sys_yCM_40to60_pp.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_40to60_pp.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_40to60_pp->SetMarkerStyle(20);
      Normal->h_vn_yCM_40to60_pp->SetLineWidth(0);
      Normal->h_vn_yCM_40to60_pp->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_40to60_pp->SetLineColor(kBlue);
      ppRapidityStackHigh->Draw();
      ppRapidityStackHigh->GetYaxis()->SetTitleOffset(1.9);
      ppRapidityStackHigh->GetXaxis()->SetNdivisions(210);
      ppRapidityStackHigh->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      ppRapidityStackHigh->SetMaximum(0.02);
      ppRapidityStackHigh->SetMinimum(-0.02);
      ppRapidityStackHigh->GetXaxis()->SetTitleSize(0.045);
      ppRapidityStackHigh->GetYaxis()->SetTitleSize(0.05);
      ppRapidityStackHigh->GetXaxis()->SetRangeUser(0, 1);
      ppRapidityStackHigh->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_ppRapidity_40-60.png");
      canvas->Clear();
      Normal->h_vn_yCM_40to60_pp->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===
*/
/*
      
      //=== Pi- vs rapidity 0-10
      THStack *pmRapidityStackLow = new THStack("pmRapidityStackLow", ";y-y_{mid};v_{"+order_n_str+"}");
      pmRapidityStackLow->Add(Normal->h_vn_yCM_00to10_pm);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_00to10_pm->Clone());
      for (int i = 0; i < v_sys_yCM_00to10_pm.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_00to10_pm.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_00to10_pm->SetMarkerStyle(20);
      Normal->h_vn_yCM_00to10_pm->SetLineWidth(0);
      Normal->h_vn_yCM_00to10_pm->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_00to10_pm->SetLineColor(kBlue);
      pmRapidityStackLow->Draw();
      pmRapidityStackLow->GetYaxis()->SetTitleOffset(1.9);
      pmRapidityStackLow->GetXaxis()->SetNdivisions(210);
      pmRapidityStackLow->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      pmRapidityStackLow->SetMaximum(0.02);
      pmRapidityStackLow->SetMinimum(-0.02);
      pmRapidityStackLow->GetXaxis()->SetTitleSize(0.045);
      pmRapidityStackLow->GetYaxis()->SetTitleSize(0.05);
      pmRapidityStackLow->GetXaxis()->SetRangeUser(0, 1);
      pmRapidityStackLow->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_pmRapidity_00-10.png");
      canvas->Clear();
      Normal->h_vn_yCM_00to10_pm->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===
      
      
      //=== Pi- vs rapidity 10-40
      THStack *pmRapidityStackMiddle = new THStack("pmRapidityStackMiddle", ";y-y_{mid};v_{"+order_n_str+"}");
      pmRapidityStackMiddle->Add(Normal->h_vn_yCM_10to40_pm);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_10to40_pm->Clone());
      for (int i = 0; i < v_sys_yCM_10to40_pm.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_10to40_pm.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_10to40_pm->SetMarkerStyle(20);
      Normal->h_vn_yCM_10to40_pm->SetLineWidth(0);
      Normal->h_vn_yCM_10to40_pm->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_10to40_pm->SetLineColor(kBlue);
      pmRapidityStackMiddle->Draw();
      pmRapidityStackMiddle->GetYaxis()->SetTitleOffset(1.9);
      pmRapidityStackMiddle->GetXaxis()->SetNdivisions(210);
      pmRapidityStackMiddle->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      pmRapidityStackMiddle->SetMaximum(0.002);
      pmRapidityStackMiddle->SetMinimum(-0.006);
      pmRapidityStackMiddle->GetXaxis()->SetTitleSize(0.045);
      pmRapidityStackMiddle->GetYaxis()->SetTitleSize(0.05);
      pmRapidityStackMiddle->GetXaxis()->SetRangeUser(0, 1);
      pmRapidityStackMiddle->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_pmRapidity_10-40.png");
      canvas->Clear();
      Normal->h_vn_yCM_10to40_pm->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===
      
      
      //=== Pi- vs rapidity 40-60
      THStack *pmRapidityStackHigh = new THStack("pmRapidityStackHigh", ";y-y_{mid};v_{"+order_n_str+"}");
      pmRapidityStackHigh->Add(Normal->h_vn_yCM_40to60_pm);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_40to60_pm->Clone());
      for (int i = 0; i < v_sys_yCM_40to60_pm.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_40to60_pm.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_40to60_pm->SetMarkerStyle(20);
      Normal->h_vn_yCM_40to60_pm->SetLineWidth(0);
      Normal->h_vn_yCM_40to60_pm->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_40to60_pm->SetLineColor(kBlue);
      pmRapidityStackHigh->Draw();
      pmRapidityStackHigh->GetYaxis()->SetTitleOffset(1.9);
      pmRapidityStackHigh->GetXaxis()->SetNdivisions(210);
      pmRapidityStackHigh->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      pmRapidityStackHigh->SetMaximum(0.02);
      pmRapidityStackHigh->SetMinimum(-0.01);
      pmRapidityStackHigh->GetXaxis()->SetTitleSize(0.045);
      pmRapidityStackHigh->GetYaxis()->SetTitleSize(0.05);
      pmRapidityStackHigh->GetXaxis()->SetRangeUser(0, 1);
      pmRapidityStackHigh->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_pmRapidity_40-60.png");
      canvas->Clear();
      Normal->h_vn_yCM_40to60_pm->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;
      //===
*/     
/*
      //=== Proton vs rapidity symmetric across midrapidity
      
      THStack *prRapidityStack_symm = new THStack("prRapidityStack_symm", ";y-y_{mid};v_{"+order_n_str+"}");
      prRapidityStack_symm->Add(Normal->h_vn_yCM_00to10_pr_symm);
      prRapidityStack_symm->Add(Normal->h_vn_yCM_10to40_pr_symm);
      prRapidityStack_symm->Add(Normal->h_vn_yCM_40to60_pr_symm);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_00to10_pr_symm->Clone());
      for (int i = 0; i < v_sys_yCM_00to10_pr_symm.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_yCM_00to10_pr_symm.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_10to40_pr_symm->Clone());
      for (int i = 0; i < v_sys_yCM_10to40_pr_symm.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_yCM_10to40_pr_symm.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_40to60_pr_symm->Clone());
      for (int i = 0; i < v_sys_yCM_40to60_pr_symm.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_yCM_40to60_pr_symm.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      prRapidityStack_symm->Draw();
      prRapidityStack_symm->GetYaxis()->SetTitleOffset(1.9);
      prRapidityStack_symm->GetXaxis()->SetNdivisions(210);
      prRapidityStack_symm->SetMaximum(rapidityUpperBound_pr);
      prRapidityStack_symm->SetMinimum(rapidityLowerBound_pr);
      prRapidityStack_symm->Draw("NOSTACK E1P X0");
      zeroLine_y_pr->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors2->Draw("2");
      copyWithNewErrors3->Draw("2");
      prLegend->Draw();
      //prText_y_symm->Draw();
      canvas->SaveAs("sys_pr_symmRapidityStack.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      
      //===
*/
/*
      //=== Deuteron vs rapidity 0-10
      THStack *deRapidityStackLow = new THStack("deRapidityStackLow", ";y-y_{mid};v_{"+order_n_str+"}");
      deRapidityStackLow->Add(Normal->h_vn_yCM_00to10_de);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_00to10_de->Clone());
      for (int i = 0; i < v_sys_yCM_00to10_de.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_00to10_de.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_00to10_de->SetMarkerStyle(20);
      Normal->h_vn_yCM_00to10_de->SetLineWidth(0);
      Normal->h_vn_yCM_00to10_de->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_00to10_de->SetLineColor(kBlue);
      deRapidityStackLow->Draw();
      deRapidityStackLow->GetYaxis()->SetTitleOffset(1.9);
      deRapidityStackLow->GetXaxis()->SetNdivisions(210);
      deRapidityStackLow->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      deRapidityStackLow->SetMaximum(0.06);
      deRapidityStackLow->SetMinimum(-0.1);
      deRapidityStackLow->GetXaxis()->SetTitleSize(0.045);
      deRapidityStackLow->GetYaxis()->SetTitleSize(0.05);
      deRapidityStackLow->GetXaxis()->SetRangeUser(0, 1);
      deRapidityStackLow->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_deRapidity_00-10.png");
      canvas->Clear();
      Normal->h_vn_yCM_00to10_de->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;      
      //===
      
      //=== Deuteron vs rapidity 10-40
      THStack *deRapidityStackMiddle = new THStack("deRapidityStackMiddle", ";y-y_{mid};v_{"+order_n_str+"}");
      deRapidityStackMiddle->Add(Normal->h_vn_yCM_10to40_de);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_10to40_de->Clone());
      for (int i = 0; i < v_sys_yCM_10to40_de.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_10to40_de.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_10to40_de->SetMarkerStyle(20);
      Normal->h_vn_yCM_10to40_de->SetLineWidth(0);
      Normal->h_vn_yCM_10to40_de->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_10to40_de->SetLineColor(kBlue);
      deRapidityStackMiddle->Draw();
      deRapidityStackMiddle->GetYaxis()->SetTitleOffset(1.9);
      deRapidityStackMiddle->GetXaxis()->SetNdivisions(210);
      deRapidityStackMiddle->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      deRapidityStackMiddle->SetMaximum(0.005);
      deRapidityStackMiddle->SetMinimum(-0.03);
      deRapidityStackMiddle->GetXaxis()->SetTitleSize(0.045);
      deRapidityStackMiddle->GetYaxis()->SetTitleSize(0.05);
      deRapidityStackMiddle->GetXaxis()->SetRangeUser(0, 1);
      deRapidityStackMiddle->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_deRapidity_10-40.png");
      canvas->Clear();
      Normal->h_vn_yCM_10to40_de->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;      
      //===
      
      
      //=== Deuteron vs rapidity 40-60
      THStack *deRapidityStackHigh = new THStack("deRapidityStackHigh", ";y-y_{mid};v_{"+order_n_str+"}");
      deRapidityStackHigh->Add(Normal->h_vn_yCM_40to60_de);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_40to60_de->Clone());
      for (int i = 0; i < v_sys_yCM_40to60_de.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_40to60_de.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_40to60_de->SetMarkerStyle(20);
      Normal->h_vn_yCM_40to60_de->SetLineWidth(0);
      Normal->h_vn_yCM_40to60_de->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_40to60_de->SetLineColor(kBlue);
      deRapidityStackHigh->Draw();
      deRapidityStackHigh->GetYaxis()->SetTitleOffset(1.9);
      deRapidityStackHigh->GetXaxis()->SetNdivisions(210);
      deRapidityStackHigh->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      deRapidityStackHigh->SetMaximum(0.01);
      deRapidityStackHigh->SetMinimum(-0.1);
      deRapidityStackHigh->GetXaxis()->SetTitleSize(0.045);
      deRapidityStackHigh->GetYaxis()->SetTitleSize(0.05);
      deRapidityStackHigh->GetXaxis()->SetRangeUser(0, 1);
      deRapidityStackHigh->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_deRapidity_40-60.png");
      canvas->Clear();
      Normal->h_vn_yCM_40to60_de->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;      
      //===
*/
/*

      //=== Triton vs rapidity 0-10
      THStack *trRapidityStackLow = new THStack("trRapidityStackLow", ";y-y_{mid};v_{"+order_n_str+"}");
      trRapidityStackLow->Add(Normal->h_vn_yCM_00to10_tr);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_00to10_tr->Clone());
      for (int i = 0; i < v_sys_yCM_00to10_tr.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_00to10_tr.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_00to10_tr->SetMarkerStyle(20);
      Normal->h_vn_yCM_00to10_tr->SetLineWidth(0);
      Normal->h_vn_yCM_00to10_tr->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_00to10_tr->SetLineColor(kBlue);
      trRapidityStackLow->Draw();
      trRapidityStackLow->GetYaxis()->SetTitleOffset(1.9);
      trRapidityStackLow->GetXaxis()->SetNdivisions(210);
      trRapidityStackLow->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      trRapidityStackLow->SetMaximum(0.25);
      trRapidityStackLow->SetMinimum(-0.15);
      trRapidityStackLow->GetXaxis()->SetTitleSize(0.045);
      trRapidityStackLow->GetYaxis()->SetTitleSize(0.05);
      trRapidityStackLow->GetXaxis()->SetRangeUser(0, 1);
      trRapidityStackLow->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_trRapidity_00-10.png");
      canvas->Clear();
      Normal->h_vn_yCM_00to10_tr->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;      
      //===
      
      //=== Triton vs rapidity 10-40
      THStack *trRapidityStackMiddle = new THStack("trRapidityStackMiddle", ";y-y_{mid};v_{"+order_n_str+"}");
      trRapidityStackMiddle->Add(Normal->h_vn_yCM_10to40_tr);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_10to40_tr->Clone());
      for (int i = 0; i < v_sys_yCM_10to40_tr.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_10to40_tr.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_10to40_tr->SetMarkerStyle(20);
      Normal->h_vn_yCM_10to40_tr->SetLineWidth(0);
      Normal->h_vn_yCM_10to40_tr->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_10to40_tr->SetLineColor(kBlue);
      trRapidityStackMiddle->Draw();
      trRapidityStackMiddle->GetYaxis()->SetTitleOffset(1.9);
      trRapidityStackMiddle->GetXaxis()->SetNdivisions(210);
      trRapidityStackMiddle->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      trRapidityStackMiddle->SetMaximum(0.08);
      trRapidityStackMiddle->SetMinimum(-0.05);
      trRapidityStackMiddle->GetXaxis()->SetTitleSize(0.045);
      trRapidityStackMiddle->GetYaxis()->SetTitleSize(0.05);
      trRapidityStackMiddle->GetXaxis()->SetRangeUser(0, 1);
      trRapidityStackMiddle->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_trRapidity_10-40.png");
      canvas->Clear();
      Normal->h_vn_yCM_10to40_tr->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;      
      //===
      
      
      //=== Triton vs rapidity 40-60
      THStack *trRapidityStackHigh = new THStack("trRapidityStackHigh", ";y-y_{mid};v_{"+order_n_str+"}");
      trRapidityStackHigh->Add(Normal->h_vn_yCM_40to60_tr);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_40to60_tr->Clone());
      for (int i = 0; i < v_sys_yCM_40to60_tr.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_40to60_tr.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_yCM_40to60_tr->SetMarkerStyle(20);
      Normal->h_vn_yCM_40to60_tr->SetLineWidth(0);
      Normal->h_vn_yCM_40to60_tr->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_40to60_tr->SetLineColor(kBlue);
      trRapidityStackHigh->Draw();
      trRapidityStackHigh->GetYaxis()->SetTitleOffset(1.9);
      trRapidityStackHigh->GetXaxis()->SetNdivisions(210);
      trRapidityStackHigh->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      trRapidityStackHigh->SetMaximum(0.15);
      trRapidityStackHigh->SetMinimum(-0.2);
      trRapidityStackHigh->GetXaxis()->SetTitleSize(0.045);
      trRapidityStackHigh->GetYaxis()->SetTitleSize(0.05);
      trRapidityStackHigh->GetXaxis()->SetRangeUser(0, 1);
      trRapidityStackHigh->Draw("NOSTACK E1P X0");
//       zeroLine_y_pr->Draw("SAME");
//       prLegend->Draw();
      //prText_y->Draw();
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_trRapidity_40-60.png");
      canvas->Clear();
      Normal->h_vn_yCM_40to60_tr->Write();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;      
      //===
*/



      //=== Helium3 vs rapidity
      /*
      THStack *he3RapidityStack = new THStack("he3RapidityStack", ";y-y_{mid};v_{"+order_n_str+"}");
      he3RapidityStack->Add(Normal->h_vn_yCM_00to10_he3);
      he3RapidityStack->Add(Normal->h_vn_yCM_10to40_he3);
      he3RapidityStack->Add(Normal->h_vn_yCM_40to60_he3);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_00to10_he3->Clone());
      for (int i = 0; i < v_sys_yCM_00to10_he3.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_yCM_00to10_he3.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_10to40_he3->Clone());
      for (int i = 0; i < v_sys_yCM_10to40_he3.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_yCM_10to40_he3.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_40to60_he3->Clone());
      for (int i = 0; i < v_sys_yCM_40to60_he3.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_yCM_40to60_he3.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      he3RapidityStack->Draw();
      he3RapidityStack->GetYaxis()->SetTitleOffset(1.9);
      he3RapidityStack->GetXaxis()->SetNdivisions(210);
      he3RapidityStack->SetMaximum(rapidityUpperBound_he3);
      he3RapidityStack->SetMinimum(rapidityLowerBound_he3);
      he3RapidityStack->Draw("NOSTACK E1P X0");
      zeroLine_y_he3->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors2->Draw("2");
      copyWithNewErrors3->Draw("2");
      he3Legend->Draw();
      //he3Text_y->Draw();
      canvas->SaveAs("sys_he3RapidityStack.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Helium4 vs rapidity
      /*
      THStack *he4RapidityStack = new THStack("he4RapidityStack", ";y-y_{mid};v_{"+order_n_str+"}");
      he4RapidityStack->Add(Normal->h_vn_yCM_00to10_he4);
      he4RapidityStack->Add(Normal->h_vn_yCM_10to40_he4);
      he4RapidityStack->Add(Normal->h_vn_yCM_40to60_he4);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_00to10_he4->Clone());
      for (int i = 0; i < v_sys_yCM_00to10_he4.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_yCM_00to10_he4.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_10to40_he4->Clone());
      for (int i = 0; i < v_sys_yCM_10to40_he4.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_yCM_10to40_he4.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_40to60_he4->Clone());
      for (int i = 0; i < v_sys_yCM_40to60_he4.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_yCM_40to60_he4.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      he4RapidityStack->Draw();
      he4RapidityStack->GetYaxis()->SetTitleOffset(1.9);
      he4RapidityStack->GetXaxis()->SetNdivisions(210);
      he4RapidityStack->SetMaximum(rapidityUpperBound_he4);
      he4RapidityStack->SetMinimum(rapidityLowerBound_he4);
      he4RapidityStack->Draw("NOSTACK E1P X0");
      zeroLine_y_he4->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors2->Draw("2");
      copyWithNewErrors3->Draw("2");
      he4Legend->Draw();
      //he4Text_y->Draw();
      canvas->SaveAs("sys_he4RapidityStack.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Proton vs pT 00-10
      
      THStack *prPtStackLow = new THStack("prPtStackLow", ";p_{T} (GeV);v_{"+order_n_str+"}");
      prPtStackLow->Add(Normal->h_vn_pT_00to10_pr);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_pr->Clone());
      for (int i = 0; i < v_sys_pT_00to10_pr.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_pT_00to10_pr.at(i)); }

      copyWithNewErrors1->Write();

      Normal->h_vn_pT_00to10_pr->SetMarkerStyle(20);
      Normal->h_vn_pT_00to10_pr->SetLineWidth(0);
      Normal->h_vn_pT_00to10_pr->SetMarkerColor(kBlue);
      Normal->h_vn_pT_00to10_pr->SetLineColor(kBlue);
      prPtStackLow->Draw();
//       prPtStack->GetYaxis()->SetTitleOffset(1.9);
//       prPtStack->GetXaxis()->SetNdivisions(210);
      prPtStackLow->SetMaximum(ptUpperBound);
      prPtStackLow->SetMinimum(ptLowerBound);
      prPtStackLow->Draw("NOSTACK E1P X0");
      //zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      //prPtLegend->Draw();
      //prPtText->Draw();
      Normal->h_vn_pT_00to10_pr->Write();
      canvas->SaveAs("sys_prPtLow.png");
      canvas->Clear();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;

      

      
      //=== Proton vs pT 10-40
      
      THStack *prPtStackMiddle = new THStack("prPtStackMiddle", ";p_{T} (GeV);v_{"+order_n_str+"}");
      prPtStackMiddle->Add(Normal->h_vn_pT_10to40_pr);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_pr->Clone());
      for (int i = 0; i < v_sys_pT_10to40_pr.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_pT_10to40_pr.at(i)); }

      copyWithNewErrors1->Write();
      
      Normal->h_vn_pT_10to40_pr->SetMarkerStyle(20);
      Normal->h_vn_pT_10to40_pr->SetLineWidth(0);
      Normal->h_vn_pT_10to40_pr->SetMarkerColor(kBlue);
      Normal->h_vn_pT_10to40_pr->SetLineColor(kBlue);
      prPtStackMiddle->Draw();
//       prPtStack->GetYaxis()->SetTitleOffset(1.9);
//       prPtStack->GetXaxis()->SetNdivisions(210);
      prPtStackMiddle->SetMaximum(ptUpperBound);
      prPtStackMiddle->SetMinimum(ptLowerBound);
      prPtStackMiddle->Draw("NOSTACK E1P X0");
      //zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      //prPtLegend->Draw();
      //prPtText->Draw();
      Normal->h_vn_pT_10to40_pr->Write();
      canvas->SaveAs("sys_prPtMiddle.png");
      canvas->Clear();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;

      
      

      //=== Proton vs pT 40-60
      
      THStack *prPtStackHigh = new THStack("prPtStackHigh", ";p_{T} (GeV);v_{"+order_n_str+"}");
      prPtStackHigh->Add(Normal->h_vn_pT_40to60_pr);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_pr->Clone());
      for (int i = 0; i < v_sys_pT_40to60_pr.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_pT_40to60_pr.at(i)); }


      copyWithNewErrors1->Write();
      
      
      Normal->h_vn_pT_40to60_pr->SetMarkerStyle(20);
      Normal->h_vn_pT_40to60_pr->SetLineWidth(0);
      Normal->h_vn_pT_40to60_pr->SetMarkerColor(kBlue);
      Normal->h_vn_pT_40to60_pr->SetLineColor(kBlue);
      prPtStackHigh->Draw();
//       prPtStack->GetYaxis()->SetTitleOffset(1.9);
//       prPtStack->GetXaxis()->SetNdivisions(210);
      prPtStackHigh->SetMaximum(ptUpperBound);
      prPtStackHigh->SetMinimum(ptLowerBound);
      prPtStackHigh->Draw("NOSTACK E1P X0");
      //zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      //prPtLegend->Draw();
      //prPtText->Draw();
      Normal->h_vn_pT_40to60_pr->Write();
      canvas->SaveAs("sys_prPtHigh.png");
      canvas->Clear();
      copyWithNewErrors1->Write();
      delete copyWithNewErrors1;

      
      //===

      //=== Proton yMid vs pT
      /*
      THStack *prPtStack_yMid = new THStack("prPtStack_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}");
      prPtStack_yMid->Add(Normal->h_vn_pT_00to10_pr_yMid);
      prPtStack_yMid->Add(Normal->h_vn_pT_40to60_pr_yMid);
      prPtStack_yMid->Add(Normal->h_vn_pT_10to40_pr_yMid);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_pr_yMid->Clone());
      for (int i = 0; i < v_sys_pT_00to10_pr_yMid.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_pr_yMid.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_pr_yMid->Clone());
      for (int i = 0; i < v_sys_pT_10to40_pr_yMid.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_pr_yMid.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_pr_yMid->Clone());
      for (int i = 0; i < v_sys_pT_40to60_pr_yMid.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_pr_yMid.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      prPtStack_yMid->Draw();
      prPtStack_yMid->GetYaxis()->SetTitleOffset(1.9);
      prPtStack_yMid->GetXaxis()->SetNdivisions(210);
      prPtStack_yMid->SetMaximum(ptUpperBound);
      prPtStack_yMid->SetMinimum(ptLowerBound);
      prPtStack_yMid->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      prPtLegend_yMid->Draw();
      //prPtText_yMid->Draw();
      canvas->SaveAs("sys_prPtStack_yMid.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Proton yFor vs pT
      /*
      THStack *prPtStack_yFor = new THStack("prPtStack_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}");
      prPtStack_yFor->Add(Normal->h_vn_pT_00to10_pr_yFor);
      prPtStack_yFor->Add(Normal->h_vn_pT_40to60_pr_yFor);
      prPtStack_yFor->Add(Normal->h_vn_pT_10to40_pr_yFor);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_pr_yFor->Clone());
      for (int i = 0; i < v_sys_pT_00to10_pr_yFor.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_pr_yFor.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_pr_yFor->Clone());
      for (int i = 0; i < v_sys_pT_10to40_pr_yFor.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_pr_yFor.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_pr_yFor->Clone());
      for (int i = 0; i < v_sys_pT_40to60_pr_yFor.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_pr_yFor.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      prPtStack_yFor->Draw();
      prPtStack_yFor->GetYaxis()->SetTitleOffset(1.9);
      prPtStack_yFor->GetXaxis()->SetNdivisions(210);
      prPtStack_yFor->SetMaximum(ptUpperBound);
      prPtStack_yFor->SetMinimum(ptLowerBound);
      prPtStack_yFor->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      prPtLegend_yFor->Draw();
      //prPtText_yFor->Draw();
      canvas->SaveAs("sys_prPtStack_yFor.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Proton yExt vs pT
      /*
      THStack *prPtStack_yExt = new THStack("prPtStack_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}");
      prPtStack_yExt->Add(Normal->h_vn_pT_00to10_pr_yExt);
      prPtStack_yExt->Add(Normal->h_vn_pT_40to60_pr_yExt);
      prPtStack_yExt->Add(Normal->h_vn_pT_10to40_pr_yExt);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_pr_yExt->Clone());
      for (int i = 0; i < v_sys_pT_00to10_pr_yExt.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_pr_yExt.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_pr_yExt->Clone());
      for (int i = 0; i < v_sys_pT_10to40_pr_yExt.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_pr_yExt.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_pr_yExt->Clone());
      for (int i = 0; i < v_sys_pT_40to60_pr_yExt.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_pr_yExt.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      prPtStack_yExt->Draw();
      prPtStack_yExt->GetYaxis()->SetTitleOffset(1.9);
      prPtStack_yExt->GetXaxis()->SetNdivisions(210);
      prPtStack_yExt->SetMaximum(ptUpperBound);
      prPtStack_yExt->SetMinimum(ptLowerBound);
      prPtStack_yExt->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      prPtLegend_yExt->Draw();
      //prPtText_yExt->Draw();
      canvas->SaveAs("sys_prPtStack_yExt.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Proton yEnd vs pT
      /*
      THStack *prPtStack_yEnd = new THStack("prPtStack_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}");
      prPtStack_yEnd->Add(Normal->h_vn_pT_00to10_pr_yEnd);
      prPtStack_yEnd->Add(Normal->h_vn_pT_40to60_pr_yEnd);
      prPtStack_yEnd->Add(Normal->h_vn_pT_10to40_pr_yEnd);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_pr_yEnd->Clone());
      for (int i = 0; i < v_sys_pT_00to10_pr_yEnd.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_pr_yEnd.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_pr_yEnd->Clone());
      for (int i = 0; i < v_sys_pT_10to40_pr_yEnd.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_pr_yEnd.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_pr_yEnd->Clone());
      for (int i = 0; i < v_sys_pT_40to60_pr_yEnd.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_pr_yEnd.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      prPtStack_yEnd->Draw();
      prPtStack_yEnd->GetYaxis()->SetTitleOffset(1.9);
      prPtStack_yEnd->GetXaxis()->SetNdivisions(210);
      prPtStack_yEnd->SetMaximum(ptUpperBound);
      prPtStack_yEnd->SetMinimum(ptLowerBound);
      prPtStack_yEnd->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      prPtLegend_yEnd->Draw();
      //prPtText_yEnd->Draw();
      canvas->SaveAs("sys_prPtStack_yEnd.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Deuteron vs pT
      /*
      THStack *dePtStack = new THStack("dePtStack", ";p_{T} (GeV);v_{"+order_n_str+"}");
      dePtStack->Add(Normal->h_vn_pT_00to10_de);
      dePtStack->Add(Normal->h_vn_pT_40to60_de);
      dePtStack->Add(Normal->h_vn_pT_10to40_de);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_de->Clone());
      for (int i = 0; i < v_sys_pT_00to10_de.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_de.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_de->Clone());
      for (int i = 0; i < v_sys_pT_10to40_de.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_de.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_de->Clone());
      for (int i = 0; i < v_sys_pT_40to60_de.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_de.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      dePtStack->Draw();
      dePtStack->GetYaxis()->SetTitleOffset(1.9);
      dePtStack->GetXaxis()->SetNdivisions(210);
      dePtStack->SetMaximum(ptUpperBound);
      dePtStack->SetMinimum(ptLowerBound);
      dePtStack->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      dePtLegend->Draw();
      //dePtText->Draw();
      canvas->SaveAs("sys_dePtStack.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Proton yMid vs pT
      /*
      THStack *dePtStack_yMid = new THStack("dePtStack_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}");
      dePtStack_yMid->Add(Normal->h_vn_pT_00to10_de_yMid);
      dePtStack_yMid->Add(Normal->h_vn_pT_40to60_de_yMid);
      dePtStack_yMid->Add(Normal->h_vn_pT_10to40_de_yMid);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_de_yMid->Clone());
      for (int i = 0; i < v_sys_pT_00to10_de_yMid.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_de_yMid.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_de_yMid->Clone());
      for (int i = 0; i < v_sys_pT_10to40_de_yMid.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_de_yMid.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_de_yMid->Clone());
      for (int i = 0; i < v_sys_pT_40to60_de_yMid.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_de_yMid.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      dePtStack_yMid->Draw();
      dePtStack_yMid->GetYaxis()->SetTitleOffset(1.9);
      dePtStack_yMid->GetXaxis()->SetNdivisions(210);
      dePtStack_yMid->SetMaximum(ptUpperBound);
      dePtStack_yMid->SetMinimum(ptLowerBound);
      dePtStack_yMid->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      dePtLegend_yMid->Draw();
      //dePtText_yMid->Draw();
      canvas->SaveAs("sys_dePtStack_yMid.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Proton yFor vs pT
      /*
      THStack *dePtStack_yFor = new THStack("dePtStack_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}");
      dePtStack_yFor->Add(Normal->h_vn_pT_00to10_de_yFor);
      dePtStack_yFor->Add(Normal->h_vn_pT_40to60_de_yFor);
      dePtStack_yFor->Add(Normal->h_vn_pT_10to40_de_yFor);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_de_yFor->Clone());
      for (int i = 0; i < v_sys_pT_00to10_de_yFor.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_de_yFor.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_de_yFor->Clone());
      for (int i = 0; i < v_sys_pT_10to40_de_yFor.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_de_yFor.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_de_yFor->Clone());
      for (int i = 0; i < v_sys_pT_40to60_de_yFor.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_de_yFor.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      dePtStack_yFor->Draw();
      dePtStack_yFor->GetYaxis()->SetTitleOffset(1.9);
      dePtStack_yFor->GetXaxis()->SetNdivisions(210);
      dePtStack_yFor->SetMaximum(ptUpperBound);
      dePtStack_yFor->SetMinimum(ptLowerBound);
      dePtStack_yFor->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      dePtLegend_yFor->Draw();
      //dePtText_yFor->Draw();
      canvas->SaveAs("sys_dePtStack_yFor.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Proton yExt vs pT
      /*
      THStack *dePtStack_yExt = new THStack("dePtStack_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}");
      dePtStack_yExt->Add(Normal->h_vn_pT_00to10_de_yExt);
      dePtStack_yExt->Add(Normal->h_vn_pT_40to60_de_yExt);
      dePtStack_yExt->Add(Normal->h_vn_pT_10to40_de_yExt);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_de_yExt->Clone());
      for (int i = 0; i < v_sys_pT_00to10_de_yExt.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_de_yExt.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_de_yExt->Clone());
      for (int i = 0; i < v_sys_pT_10to40_de_yExt.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_de_yExt.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_de_yExt->Clone());
      for (int i = 0; i < v_sys_pT_40to60_de_yExt.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_de_yExt.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      dePtStack_yExt->Draw();
      dePtStack_yExt->GetYaxis()->SetTitleOffset(1.9);
      dePtStack_yExt->GetXaxis()->SetNdivisions(210);
      dePtStack_yExt->SetMaximum(ptUpperBound);
      dePtStack_yExt->SetMinimum(ptLowerBound);
      dePtStack_yExt->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      dePtLegend_yExt->Draw();
      //dePtText_yExt->Draw();
      canvas->SaveAs("sys_dePtStack_yExt.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Deuteron yEnd vs pT
      /*
      THStack *dePtStack_yEnd = new THStack("dePtStack_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}");
      dePtStack_yEnd->Add(Normal->h_vn_pT_00to10_de_yEnd);
      dePtStack_yEnd->Add(Normal->h_vn_pT_40to60_de_yEnd);
      dePtStack_yEnd->Add(Normal->h_vn_pT_10to40_de_yEnd);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_de_yEnd->Clone());
      for (int i = 0; i < v_sys_pT_00to10_de_yEnd.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_de_yEnd.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_de_yEnd->Clone());
      for (int i = 0; i < v_sys_pT_10to40_de_yEnd.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_de_yEnd.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_de_yEnd->Clone());
      for (int i = 0; i < v_sys_pT_40to60_de_yEnd.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_de_yEnd.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      dePtStack_yEnd->Draw();
      dePtStack_yEnd->GetYaxis()->SetTitleOffset(1.9);
      dePtStack_yEnd->GetXaxis()->SetNdivisions(210);
      dePtStack_yEnd->SetMaximum(ptUpperBound);
      dePtStack_yEnd->SetMinimum(ptLowerBound);
      dePtStack_yEnd->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      dePtLegend_yEnd->Draw();
      //dePtText_yEnd->Draw();
      canvas->SaveAs("sys_dePtStack_yEnd.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===


      //=== Triton vs pT
      /*
      THStack *trPtStack = new THStack("trPtStack", ";p_{T} (GeV);v_{"+order_n_str+"}");
      trPtStack->Add(Normal->h_vn_pT_00to10_tr);
      trPtStack->Add(Normal->h_vn_pT_40to60_tr);
      trPtStack->Add(Normal->h_vn_pT_10to40_tr);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_tr->Clone());
      for (int i = 0; i < v_sys_pT_00to10_tr.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_tr.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_tr->Clone());
      for (int i = 0; i < v_sys_pT_10to40_tr.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_tr.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_tr->Clone());
      for (int i = 0; i < v_sys_pT_40to60_tr.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_tr.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      trPtStack->Draw();
      trPtStack->GetYaxis()->SetTitleOffset(1.9);
      trPtStack->GetXaxis()->SetNdivisions(210);
      trPtStack->SetMaximum(ptUpperBound);
      trPtStack->SetMinimum(ptLowerBound);
      trPtStack->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      trPtLegend->Draw();
      //trPtText->Draw();
      canvas->SaveAs("sys_trPtStack.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Triton yMid vs pT
      /*
      THStack *trPtStack_yMid = new THStack("trPtStack_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}");
      trPtStack_yMid->Add(Normal->h_vn_pT_00to10_tr_yMid);
      trPtStack_yMid->Add(Normal->h_vn_pT_40to60_tr_yMid);
      trPtStack_yMid->Add(Normal->h_vn_pT_10to40_tr_yMid);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_tr_yMid->Clone());
      for (int i = 0; i < v_sys_pT_00to10_tr_yMid.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_tr_yMid.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_tr_yMid->Clone());
      for (int i = 0; i < v_sys_pT_10to40_tr_yMid.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_tr_yMid.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_tr_yMid->Clone());
      for (int i = 0; i < v_sys_pT_40to60_tr_yMid.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_tr_yMid.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      trPtStack_yMid->Draw();
      trPtStack_yMid->GetYaxis()->SetTitleOffset(1.9);
      trPtStack_yMid->GetXaxis()->SetNdivisions(210);
      trPtStack_yMid->SetMaximum(ptUpperBound);
      trPtStack_yMid->SetMinimum(ptLowerBound);
      trPtStack_yMid->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      trPtLegend_yMid->Draw();
      //trPtText_yMid->Draw();
      canvas->SaveAs("sys_trPtStack_yMid.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Triton yFor vs pT
      /*
      THStack *trPtStack_yFor = new THStack("trPtStack_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}");
      trPtStack_yFor->Add(Normal->h_vn_pT_00to10_tr_yFor);
      trPtStack_yFor->Add(Normal->h_vn_pT_40to60_tr_yFor);
      trPtStack_yFor->Add(Normal->h_vn_pT_10to40_tr_yFor);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_tr_yFor->Clone());
      for (int i = 0; i < v_sys_pT_00to10_tr_yFor.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_tr_yFor.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_tr_yFor->Clone());
      for (int i = 0; i < v_sys_pT_10to40_tr_yFor.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_tr_yFor.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_tr_yFor->Clone());
      for (int i = 0; i < v_sys_pT_40to60_tr_yFor.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_tr_yFor.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      trPtStack_yFor->Draw();
      trPtStack_yFor->GetYaxis()->SetTitleOffset(1.9);
      trPtStack_yFor->GetXaxis()->SetNdivisions(210);
      trPtStack_yFor->SetMaximum(ptUpperBound);
      trPtStack_yFor->SetMinimum(ptLowerBound);
      trPtStack_yFor->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      trPtLegend_yFor->Draw();
      //trPtText_yFor->Draw();
      canvas->SaveAs("sys_trPtStack_yFor.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Proton yExt vs pT
      /*
      THStack *trPtStack_yExt = new THStack("trPtStack_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}");
      trPtStack_yExt->Add(Normal->h_vn_pT_00to10_tr_yExt);
      trPtStack_yExt->Add(Normal->h_vn_pT_40to60_tr_yExt);
      trPtStack_yExt->Add(Normal->h_vn_pT_10to40_tr_yExt);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_tr_yExt->Clone());
      for (int i = 0; i < v_sys_pT_00to10_tr_yExt.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_tr_yExt.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_tr_yExt->Clone());
      for (int i = 0; i < v_sys_pT_10to40_tr_yExt.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_tr_yExt.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_tr_yExt->Clone());
      for (int i = 0; i < v_sys_pT_40to60_tr_yExt.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_tr_yExt.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      trPtStack_yExt->Draw();
      trPtStack_yExt->GetYaxis()->SetTitleOffset(1.9);
      trPtStack_yExt->GetXaxis()->SetNdivisions(210);
      trPtStack_yExt->SetMaximum(ptUpperBound);
      trPtStack_yExt->SetMinimum(ptLowerBound);
      trPtStack_yExt->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      trPtLegend_yExt->Draw();
      //trPtText_yExt->Draw();
      canvas->SaveAs("sys_trPtStack_yExt.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Triton yEnd vs pT
      /*
      THStack *trPtStack_yEnd = new THStack("trPtStack_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}");
      trPtStack_yEnd->Add(Normal->h_vn_pT_00to10_tr_yEnd);
      trPtStack_yEnd->Add(Normal->h_vn_pT_40to60_tr_yEnd);
      trPtStack_yEnd->Add(Normal->h_vn_pT_10to40_tr_yEnd);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_tr_yEnd->Clone());
      for (int i = 0; i < v_sys_pT_00to10_tr_yEnd.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_tr_yEnd.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_tr_yEnd->Clone());
      for (int i = 0; i < v_sys_pT_10to40_tr_yEnd.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_tr_yEnd.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_tr_yEnd->Clone());
      for (int i = 0; i < v_sys_pT_40to60_tr_yEnd.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_tr_yEnd.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      trPtStack_yEnd->Draw();
      trPtStack_yEnd->GetYaxis()->SetTitleOffset(1.9);
      trPtStack_yEnd->GetXaxis()->SetNdivisions(210);
      trPtStack_yEnd->SetMaximum(ptUpperBound);
      trPtStack_yEnd->SetMinimum(ptLowerBound);
      trPtStack_yEnd->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      trPtLegend_yEnd->Draw();
      //trPtText_yEnd->Draw();
      canvas->SaveAs("sys_trPtStack_yEnd.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Helium3 vs pT
      /*
      THStack *he3PtStack = new THStack("he3PtStack", ";p_{T} (GeV);v_{"+order_n_str+"}");
      he3PtStack->Add(Normal->h_vn_pT_00to10_he3);
      he3PtStack->Add(Normal->h_vn_pT_40to60_he3);
      he3PtStack->Add(Normal->h_vn_pT_10to40_he3);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_he3->Clone());
      for (int i = 0; i < v_sys_pT_00to10_he3.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_he3.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_he3->Clone());
      for (int i = 0; i < v_sys_pT_10to40_he3.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_he3.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_he3->Clone());
      for (int i = 0; i < v_sys_pT_40to60_he3.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_he3.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      he3PtStack->Draw();
      he3PtStack->GetYaxis()->SetTitleOffset(1.9);
      he3PtStack->GetXaxis()->SetNdivisions(210);
      he3PtStack->SetMaximum(ptUpperBound);
      he3PtStack->SetMinimum(ptLowerBound);
      he3PtStack->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      he3PtLegend->Draw();
      //trPtText->Draw();
      canvas->SaveAs("sys_he3PtStack.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Triton yMid vs pT
      /*
      THStack *he3PtStack_yMid = new THStack("he3PtStack_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}");
      he3PtStack_yMid->Add(Normal->h_vn_pT_00to10_he3_yMid);
      he3PtStack_yMid->Add(Normal->h_vn_pT_40to60_he3_yMid);
      he3PtStack_yMid->Add(Normal->h_vn_pT_10to40_he3_yMid);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_he3_yMid->Clone());
      for (int i = 0; i < v_sys_pT_00to10_he3_yMid.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_he3_yMid.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_he3_yMid->Clone());
      for (int i = 0; i < v_sys_pT_10to40_he3_yMid.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_he3_yMid.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_he3_yMid->Clone());
      for (int i = 0; i < v_sys_pT_40to60_he3_yMid.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_he3_yMid.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      he3PtStack_yMid->Draw();
      he3PtStack_yMid->GetYaxis()->SetTitleOffset(1.9);
      he3PtStack_yMid->GetXaxis()->SetNdivisions(210);
      he3PtStack_yMid->SetMaximum(ptUpperBound);
      he3PtStack_yMid->SetMinimum(ptLowerBound);
      he3PtStack_yMid->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      he3PtLegend_yMid->Draw();
      //trPtText_yMid->Draw();
      canvas->SaveAs("sys_he3PtStack_yMid.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Triton yFor vs pT
      /*
      THStack *he3PtStack_yFor = new THStack("he3PtStack_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}");
      he3PtStack_yFor->Add(Normal->h_vn_pT_00to10_he3_yFor);
      he3PtStack_yFor->Add(Normal->h_vn_pT_40to60_he3_yFor);
      he3PtStack_yFor->Add(Normal->h_vn_pT_10to40_he3_yFor);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_he3_yFor->Clone());
      for (int i = 0; i < v_sys_pT_00to10_he3_yFor.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_he3_yFor.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_he3_yFor->Clone());
      for (int i = 0; i < v_sys_pT_10to40_he3_yFor.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_he3_yFor.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_he3_yFor->Clone());
      for (int i = 0; i < v_sys_pT_40to60_he3_yFor.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_he3_yFor.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      he3PtStack_yFor->Draw();
      he3PtStack_yFor->GetYaxis()->SetTitleOffset(1.9);
      he3PtStack_yFor->GetXaxis()->SetNdivisions(210);
      he3PtStack_yFor->SetMaximum(ptUpperBound);
      he3PtStack_yFor->SetMinimum(ptLowerBound);
      he3PtStack_yFor->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      he3PtLegend_yFor->Draw();
      //trPtText_yFor->Draw();
      canvas->SaveAs("sys_he3PtStack_yFor.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Proton yExt vs pT
      /*
      THStack *he3PtStack_yExt = new THStack("he3PtStack_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}");
      he3PtStack_yExt->Add(Normal->h_vn_pT_00to10_he3_yExt);
      he3PtStack_yExt->Add(Normal->h_vn_pT_40to60_he3_yExt);
      he3PtStack_yExt->Add(Normal->h_vn_pT_10to40_he3_yExt);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_he3_yExt->Clone());
      for (int i = 0; i < v_sys_pT_00to10_he3_yExt.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_he3_yExt.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_he3_yExt->Clone());
      for (int i = 0; i < v_sys_pT_10to40_he3_yExt.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_he3_yExt.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_he3_yExt->Clone());
      for (int i = 0; i < v_sys_pT_40to60_he3_yExt.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_he3_yExt.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      he3PtStack_yExt->Draw();
      he3PtStack_yExt->GetYaxis()->SetTitleOffset(1.9);
      he3PtStack_yExt->GetXaxis()->SetNdivisions(210);
      he3PtStack_yExt->SetMaximum(ptUpperBound);
      he3PtStack_yExt->SetMinimum(ptLowerBound);
      he3PtStack_yExt->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      he3PtLegend_yExt->Draw();
      //trPtText_yExt->Draw();
      canvas->SaveAs("sys_he3PtStack_yExt.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Triton yEnd vs pT
      /*
      THStack *he3PtStack_yEnd = new THStack("he3PtStack_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}");
      he3PtStack_yEnd->Add(Normal->h_vn_pT_00to10_he3_yEnd);
      he3PtStack_yEnd->Add(Normal->h_vn_pT_40to60_he3_yEnd);
      he3PtStack_yEnd->Add(Normal->h_vn_pT_10to40_he3_yEnd);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_he3_yEnd->Clone());
      for (int i = 0; i < v_sys_pT_00to10_he3_yEnd.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_he3_yEnd.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_he3_yEnd->Clone());
      for (int i = 0; i < v_sys_pT_10to40_he3_yEnd.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_he3_yEnd.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_he3_yEnd->Clone());
      for (int i = 0; i < v_sys_pT_40to60_he3_yEnd.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_he3_yEnd.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      he3PtStack_yEnd->Draw();
      he3PtStack_yEnd->GetYaxis()->SetTitleOffset(1.9);
      he3PtStack_yEnd->GetXaxis()->SetNdivisions(210);
      he3PtStack_yEnd->SetMaximum(ptUpperBound);
      he3PtStack_yEnd->SetMinimum(ptLowerBound);
      he3PtStack_yEnd->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      he3PtLegend_yEnd->Draw();
      //he3PtText_yEnd->Draw();
      canvas->SaveAs("sys_he3PtStack_yEnd.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Helium4 vs pT
      /*
      THStack *he4PtStack = new THStack("he4PtStack", ";p_{T} (GeV);v_{"+order_n_str+"}");
      he4PtStack->Add(Normal->h_vn_pT_00to10_he4);
      he4PtStack->Add(Normal->h_vn_pT_40to60_he4);
      he4PtStack->Add(Normal->h_vn_pT_10to40_he4);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_he4->Clone());
      for (int i = 0; i < v_sys_pT_00to10_he4.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_he4.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_he4->Clone());
      for (int i = 0; i < v_sys_pT_10to40_he4.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_he4.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_he4->Clone());
      for (int i = 0; i < v_sys_pT_40to60_he4.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_he4.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      he4PtStack->Draw();
      he4PtStack->GetYaxis()->SetTitleOffset(1.9);
      he4PtStack->GetXaxis()->SetNdivisions(210);
      he4PtStack->SetMaximum(ptUpperBound);
      he4PtStack->SetMinimum(ptLowerBound);
      he4PtStack->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      he4PtLegend->Draw();
      //trPtText->Draw();
      canvas->SaveAs("sys_he4PtStack.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Triton yMid vs pT
      /*
      THStack *he4PtStack_yMid = new THStack("he4PtStack_yMid", ";p_{T} (GeV);v_{"+order_n_str+"}");
      he4PtStack_yMid->Add(Normal->h_vn_pT_00to10_he4_yMid);
      he4PtStack_yMid->Add(Normal->h_vn_pT_40to60_he4_yMid);
      he4PtStack_yMid->Add(Normal->h_vn_pT_10to40_he4_yMid);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_he4_yMid->Clone());
      for (int i = 0; i < v_sys_pT_00to10_he4_yMid.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_he4_yMid.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_he4_yMid->Clone());
      for (int i = 0; i < v_sys_pT_10to40_he4_yMid.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_he4_yMid.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_he4_yMid->Clone());
      for (int i = 0; i < v_sys_pT_40to60_he4_yMid.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_he4_yMid.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      he4PtStack_yMid->Draw();
      he4PtStack_yMid->GetYaxis()->SetTitleOffset(1.9);
      he4PtStack_yMid->GetXaxis()->SetNdivisions(210);
      he4PtStack_yMid->SetMaximum(ptUpperBound);
      he4PtStack_yMid->SetMinimum(ptLowerBound);
      he4PtStack_yMid->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      he4PtLegend_yMid->Draw();
      //trPtText_yMid->Draw();
      canvas->SaveAs("sys_he4PtStack_yMid.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Triton yFor vs pT
      /*
      THStack *he4PtStack_yFor = new THStack("he4PtStack_yFor", ";p_{T} (GeV);v_{"+order_n_str+"}");
      he4PtStack_yFor->Add(Normal->h_vn_pT_00to10_he4_yFor);
      he4PtStack_yFor->Add(Normal->h_vn_pT_40to60_he4_yFor);
      he4PtStack_yFor->Add(Normal->h_vn_pT_10to40_he4_yFor);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_he4_yFor->Clone());
      for (int i = 0; i < v_sys_pT_00to10_he4_yFor.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_he4_yFor.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_he4_yFor->Clone());
      for (int i = 0; i < v_sys_pT_10to40_he4_yFor.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_he4_yFor.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_he4_yFor->Clone());
      for (int i = 0; i < v_sys_pT_40to60_he4_yFor.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_he4_yFor.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      he4PtStack_yFor->Draw();
      he4PtStack_yFor->GetYaxis()->SetTitleOffset(1.9);
      he4PtStack_yFor->GetXaxis()->SetNdivisions(210);
      he4PtStack_yFor->SetMaximum(ptUpperBound);
      he4PtStack_yFor->SetMinimum(ptLowerBound);
      he4PtStack_yFor->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      he4PtLegend_yFor->Draw();
      //trPtText_yFor->Draw();
      canvas->SaveAs("sys_he4PtStack_yFor.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Proton yExt vs pT
      /*
      THStack *he4PtStack_yExt = new THStack("he4PtStack_yExt", ";p_{T} (GeV);v_{"+order_n_str+"}");
      he4PtStack_yExt->Add(Normal->h_vn_pT_00to10_he4_yExt);
      he4PtStack_yExt->Add(Normal->h_vn_pT_40to60_he4_yExt);
      he4PtStack_yExt->Add(Normal->h_vn_pT_10to40_he4_yExt);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_he4_yExt->Clone());
      for (int i = 0; i < v_sys_pT_00to10_he4_yExt.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_he4_yExt.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_he4_yExt->Clone());
      for (int i = 0; i < v_sys_pT_10to40_he4_yExt.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_he4_yExt.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_he4_yExt->Clone());
      for (int i = 0; i < v_sys_pT_40to60_he4_yExt.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_he4_yExt.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      he4PtStack_yExt->Draw();
      he4PtStack_yExt->GetYaxis()->SetTitleOffset(1.9);
      he4PtStack_yExt->GetXaxis()->SetNdivisions(210);
      he4PtStack_yExt->SetMaximum(ptUpperBound);
      he4PtStack_yExt->SetMinimum(ptLowerBound);
      he4PtStack_yExt->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      he4PtLegend_yExt->Draw();
      //trPtText_yExt->Draw();
      canvas->SaveAs("sys_he4PtStack_yExt.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      //=== Triton yEnd vs pT
      /*
      THStack *he4PtStack_yEnd = new THStack("he4PtStack_yEnd", ";p_{T} (GeV);v_{"+order_n_str+"}");
      he4PtStack_yEnd->Add(Normal->h_vn_pT_00to10_he4_yEnd);
      he4PtStack_yEnd->Add(Normal->h_vn_pT_40to60_he4_yEnd);
      he4PtStack_yEnd->Add(Normal->h_vn_pT_10to40_he4_yEnd);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_pT_00to10_he4_yEnd->Clone());
      for (int i = 0; i < v_sys_pT_00to10_he4_yEnd.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, 0.0, v_sys_pT_00to10_he4_yEnd.at(i)); }

      copyWithNewErrors2 = new TGraphErrors((TH1D*)Normal->h_vn_pT_10to40_he4_yEnd->Clone());
      for (int i = 0; i < v_sys_pT_10to40_he4_yEnd.size(); i++)
	{ copyWithNewErrors2->SetPointError(i, 0.0, v_sys_pT_10to40_he4_yEnd.at(i)); }

      copyWithNewErrors3 = new TGraphErrors((TH1D*)Normal->h_vn_pT_40to60_he4_yEnd->Clone());
      for (int i = 0; i < v_sys_pT_40to60_he4_yEnd.size(); i++)
	{ copyWithNewErrors3->SetPointError(i, 0.0, v_sys_pT_40to60_he4_yEnd.at(i)); }

      copyWithNewErrors1->Write();
      copyWithNewErrors2->Write();
      copyWithNewErrors3->Write();
      
      he4PtStack_yEnd->Draw();
      he4PtStack_yEnd->GetYaxis()->SetTitleOffset(1.9);
      he4PtStack_yEnd->GetXaxis()->SetNdivisions(210);
      he4PtStack_yEnd->SetMaximum(ptUpperBound);
      he4PtStack_yEnd->SetMinimum(ptLowerBound);
      he4PtStack_yEnd->Draw("NOSTACK E1P X0");
      zeroLine_pt->Draw("SAME");
      copyWithNewErrors1->Draw("2");
      copyWithNewErrors3->Draw("2");
      copyWithNewErrors2->Draw("2");
      he4PtLegend_yEnd->Draw();
      //he4PtText_yEnd->Draw();
      canvas->SaveAs("sys_he4PtStack_yEnd.png");
      canvas->Clear();
      delete copyWithNewErrors1;
      delete copyWithNewErrors2;
      delete copyWithNewErrors3;
      */
      //===

      delete canvas;
    }// End if order_n_str == 3


  //delete epd;
  //delete nhits;
  //delete nSigPi;
  //delete nSigKa;
  //delete nSigPr;
//   delete zDe;
//   delete zTr;
//   delete zHe3;
//   delete zHe4;
  //delete rvtx;
  //delete zvtx;
  //delete dca;
  //delete nhitsdEdx;
  //delete nhitsratio;
  //delete m2Pi;
  //delete m2Ka;

  delete Normal;
  //delete epd_high;
  //delete epd_low;
  //delete epd_scaled;

  //delete nSigPi_high_30;
  //delete nSigPi_low_30;
  //delete nSigKa_high_30;
  //delete nSigKa_low_30;
  //delete nSigPr_high_30;
  //delete nSigPr_low_30;
//   delete zDe_high_30;
//   delete zDe_low_30;
//   delete zTr_high_30;
//   delete zTr_low_30;
//   delete zHe3_high_30;
//   delete zHe3_low_30;
//   delete zHe4_high_30;
//   delete zHe4_low_30;
  delete rvtx_high_30;
  delete rvtx_low_30;
  delete zvtx_high_30;
  delete zvtx_low_30;
  delete dca_high_30;
  delete dca_low_30;
  delete nhits_high_30;
  delete nhits_low_30;
  delete nhitsdEdx_high_30;
  //delete nhitsdEdx_low_30;
  delete nhitsratio_high_30;
  delete nhitsratio_low_30;
  //delete m2Pi_high_30;
  //delete m2Pi_low_30;
  //delete m2Ka_high_30;
  //delete m2Ka_low_30;


  //delete nSigPi_high_20;
  //delete nSigPi_low_20;
  //delete nSigKa_high_20;
  //delete nSigKa_low_20;
  //delete nSigPr_high_20;
  //delete nSigPr_low_20;
  //delete rvtx_high_20;
  //delete rvtx_low_20;
  //delete zvtx_high_20;
  //delete zvtx_low_20;
  //delete dca_high_20;
  //delete dca_low_20;
  //delete nhits_high_20;
  //delete nhits_low_20;
  //delete nhitsdEdx_high_20;
//   delete nhitsdEdx_low_20;
  //delete nhitsratio_high_20;
  //delete nhitsratio_low_20;
  //delete m2Pi_high_20;
  //delete m2Pi_low_20;
  //delete m2Ka_high_20;
  //delete m2Ka_low_20;
  

  newFile->Close();
  delete newFile;
}



void printPointErrors(TGraphErrors *graph)
{
  Int_t nPoints = graph->GetN();

  std::cout << graph->GetName() << ":" << std::endl;
  
  for (int i = 0; i < nPoints; i++)
    {
      std::cout << "Bin " << i+1 << ": " << graph->GetErrorY(i) << std::endl;
    }
}
