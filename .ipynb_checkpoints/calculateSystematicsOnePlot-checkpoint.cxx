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
    //else if (ID == "nSigPi")
    //  {
    //    nSigPiPercentQuadSum += stdDevContributed;
    //    nSigPiNbins++;
    //  }
    //else if (ID == "nSigKa")
    //  {
    //    nSigKaPercentQuadSum += stdDevContributed;
    //    nSigKaNbins++;
    //  }
    else if (ID == "nSigPr")
      {
	//std::cout << "ID: "  << ID<< std::endl;
	nSigPrPercentQuadSum += stdDevContributed;
	nSigPrNbins++;
      }

      
      
    if (ID == "rvtx")
      {
        //std::cout << "ID: "  << ID<< std::endl;
        rvtxPercentQuadSum += stdDevContributed;
        rvtxNbins++;
      }
    else if (ID == "zvtx")
      {
        //std::cout << "ID: "  << ID<< std::endl;
        zvtxPercentQuadSum += stdDevContributed;
        zvtxNbins++;
      }
    else if (ID == "dca")
      {
	//std::cout << "ID: "  << ID<< std::endl;
	dcaPercentQuadSum += stdDevContributed;
	dcaNbins++;
      }
    else if (ID == "nhits")
      {
	//std::cout << "ID: "  << ID<< std::endl;
	nhitsPercentQuadSum += stdDevContributed;
	nhitsNbins++;
      }
    else if (ID == "nhitsdEdx")
      {
	//std::cout << "ID: "  << ID<< std::endl;
	nhitsdEdxPercentQuadSum += stdDevContributed;
	nhitsdEdxNbins++;
      }
    else if (ID == "nhitsratio")
      {
	//std::cout << "ID: "  << ID<< std::endl;
	nhitsratioPercentQuadSum += stdDevContributed;
	nhitsratioNbins++;
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
	      //<< "Std dev of each contribution as a percent of the normal v1 measurement:" << std::endl
	      << "Std dev of each contribution as a percent of the normal v3 measurement:" << std::endl
	      << std::endl
	      << "Track QA, " << trackQAPercentQuadSum / (Double_t)trackQANbins << std::endl
      	      << "Event QA, " << eventQAPercentQuadSum / (Double_t)eventQANbins << std::endl
            
	      << "nHits, " << nhitsPercentQuadSum / (Double_t)nhitsNbins << std::endl
	      << "nHits dEdx, " << nhitsdEdxPercentQuadSum / (Double_t)nhitsdEdxNbins << std::endl
	      << "nHits Ratio, " << nhitsratioPercentQuadSum / (Double_t)nhitsratioNbins << std::endl
	      << "DCA, " << dcaPercentQuadSum / (Double_t)dcaNbins << std::endl
	      << "r Vertex, " << rvtxPercentQuadSum / (Double_t)rvtxNbins << std::endl
	      << "z Vertex, " << zvtxPercentQuadSum / (Double_t)zvtxNbins << std::endl
	    
	      //<< "nSigma Pi, " << nSigPiPercentQuadSum / (Double_t)nSigPiNbins << std::endl
	      //<< "nSigma Ka, " << nSigKaPercentQuadSum / (Double_t)nSigKaNbins << std::endl
	      << "nSigma Pr, " << nSigPrPercentQuadSum / (Double_t)nSigPrNbins << std::endl
	      //<< "m^2 Pi, " << m2PiPercentQuadSum / (Double_t)m2PiNbins << std::endl
	      //<< "m^2 Ka, " << m2KaPercentQuadSum / (Double_t)m2KaNbins << std::endl
	      << "EP Resolution, " << epdPercentQuadSum / (Double_t)epdNbins << std::endl
	      << std::endl;
  }
};






//void calculateSystematics(TString order_n_str = "3")
void calculateSystematicsOnePlot(TString order_n_str = "3")
{
  TFile* newFile = new TFile("systematicErrors.root", "RECREATE");

  //TString directory20Percent = "../thirdDraft/20percentVariations/";
  TString directory30Percent = "../";
  //TString directory30Percent = "../thirdDraft/30percentVariations/";
  TString directoryEPR = "../";
  //TString directoryEPR = "../thirdDraft/eprVariations/";

  Variation* Normal = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/1-2-24-V3-HistogramsNormal.root", order_n_str);
  Variation* epd_high = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/1-23-24-V3-HistogramOuterEPDHigh.root", order_n_str);
  Variation* epd_low = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/1-23-24-V3-HistogramOuterEPDLow.root", order_n_str);


  //Variation* nSigPi_high_20 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsNSigmaPion20High.root", order_n_str);
  //Variation* nSigPi_low_20  = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsNSigmaPion20Low.root", order_n_str);
  //Variation* nSigKa_high_20 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsNSigmaKaon20High.root", order_n_str);
  //Variation* nSigKa_low_20  = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsNSigmaKaon20Low.root", order_n_str);
  Variation* nSigPr_high_20 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/1-23-24-V3-HistogramNSigmaProton20High.root", order_n_str);
  Variation* nSigPr_low_20  = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/1-23-24-V3-HistogramNSigmaProton20Low.root", order_n_str);
  //Variation* rvtx_high_20 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsRVertex20High.root", order_n_str);
  //Variation* rvtx_low_20  = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsRVertex20Low.root", order_n_str);
  //Variation* zvtx_high_20 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsZVertex20High.root", order_n_str);
  //Variation* zvtx_low_20  = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsZVertex20Low.root", order_n_str);
  //Variation* dca_high_20 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsDCA20High.root", order_n_str);
  //Variation* dca_low_20  = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsDCA20Low.root", order_n_str);
  //Variation* nhits_high_20 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsNHits20High.root", order_n_str);
  //Variation* nhits_low_20 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsNHits20Low.root", order_n_str);
  //Variation* nhitsdEdx_high_20 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsNHitsdEdx20High.root", order_n_str);
  //Variation* nhitsdEdx_low_20  = new Variation(directory20Percent+"nhitsdEdx_low", order_n_str);
  //Variation* nhitsratio_high_20 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsNHitsFitOverNHitsPoss20High.root", order_n_str);
  //Variation* nhitsratio_low_20  = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsNHitsFitOverNHitsPoss20Low.root", order_n_str);
  //Variation* m2Pi_high_20 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsMSquaredPion20High.root", order_n_str);
  //Variation* m2Pi_low_20  = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsMSquaredPion20Low.root", order_n_str);
  //Variation* m2Ka_high_20 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsMSquaredKaon20High.root", order_n_str);
  //Variation* m2Ka_low_20  = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/10-30-23-V3-HistogramsMSquaredKaon20Low.root", order_n_str);    
    
    
  Variation* nSigPr_high_30 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/1-23-24-V3-HistogramNSigmaProton30High.root", order_n_str);
  Variation* nSigPr_low_30  = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/1-23-24-V3-HistogramNSigmaProton30Low.root", order_n_str);
//   Variation* rvtx_high_30 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/9-24-23-V3-HistogramsRVertex30High.root", order_n_str);
//   Variation* rvtx_low_30  = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/9-24-23-V3-HistogramsRVertex30Low.root", order_n_str);
//   Variation* zvtx_high_30 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/9-24-23-V3-HistogramsZVertex30High.root", order_n_str);
//   Variation* zvtx_low_30  = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/9-24-23-V3-HistogramsZVertex30Low.root", order_n_str);
//   Variation* dca_high_30 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/9-24-23-V3-HistogramsDCA30High.root", order_n_str);
//   Variation* dca_low_30  = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/9-24-23-V3-HistogramsDCA30Low.root", order_n_str);
//   Variation* nhits_high_30 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/9-24-23-V3-HistogramsNHits30High.root", order_n_str);
//   Variation* nhits_low_30 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/9-24-23-V3-HistogramsNHits30Low.root", order_n_str);
//   Variation* nhitsdEdx_high_30 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/9-24-23-V3-HistogramsNHitsdEdx30High.root", order_n_str);
//   Variation* nhitsratio_high_30 = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/9-24-23-V3-HistogramsNHitsFitOverNHitsPoss30High.root", order_n_str);
//   Variation* nhitsratio_low_30  = new Variation("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/9-24-23-V3-HistogramsNHitsFitOverNHitsPoss30Low.root", order_n_str);


  CompositeData* epd = new CompositeData("epd", Normal, epd_low, epd_high);
//  CompositeData* nhits = new CompositeData("nhits", Normal, nhits_low_30, nhits_high_30);  
  //CompositeData* nSigPi = new CompositeData("nSigPi", Normal, nSigPi_low_30, nSigPi_high_30);
  //CompositeData* nSigKa = new CompositeData("nSigKa", Normal, nSigKa_low_30, nSigKa_high_30);
//   CompositeData* nSigPr = new CompositeData("nSigPr", Normal, nSigPr_low_30, nSigPr_high_30);
//   CompositeData* rvtx = new CompositeData("rvtx", Normal, rvtx_low_30, rvtx_high_30);
//   CompositeData* zvtx = new CompositeData("zvtx", Normal, zvtx_low_30, zvtx_high_30);
//   CompositeData* dca  = new CompositeData("dca", Normal, dca_low_30, dca_high_30);
//   CompositeData* nhitsdEdx = new CompositeData("nhitsdEdx", Normal, nhitsdEdx_high_30);
//   CompositeData* nhitsratio = new CompositeData("nhitsratio", Normal, nhitsratio_low_30, nhitsratio_high_30);
  //CompositeData* m2Pi = new CompositeData("m2Pi", Normal, m2Pi_low_30, m2Pi_high_30);
  //CompositeData* m2Ka = new CompositeData("m2Ka", Normal, m2Ka_low_30, m2Ka_high_30);
  
//   CompositeData* nhits = new CompositeData("nhits", Normal, nhits_low_30, nhits_high_30, nhits_low_20, nhits_high_20);  
//   CompositeData* nSigPi = new CompositeData("nSigPi", Normal, nSigPi_low_30, nSigPi_high_30, nSigPi_low_20, nSigPi_high_20);
//   CompositeData* nSigKa = new CompositeData("nSigKa", Normal, nSigKa_low_30, nSigKa_high_30, nSigKa_low_20, nSigKa_high_20);
  CompositeData* nSigPr = new CompositeData("nSigPr", Normal, nSigPr_low_30, nSigPr_high_30, nSigPr_low_20, nSigPr_high_20);
//   CompositeData* rvtx = new CompositeData("rvtx", Normal, rvtx_low_30, rvtx_high_30, rvtx_low_20, rvtx_high_20);
//   CompositeData* zvtx = new CompositeData("zvtx", Normal, zvtx_low_30, zvtx_high_30, zvtx_low_20, zvtx_high_20);
//   CompositeData* dca  = new CompositeData("dca", Normal, dca_low_30, dca_high_30, dca_low_20, dca_high_20);
//   CompositeData* nhitsdEdx = new CompositeData("nhitsdEdx", Normal, nhitsdEdx_high_30, nhitsdEdx_high_20, nhitsdEdx_low_20);
//   CompositeData* nhitsratio = new CompositeData("nhitsratio", Normal, nhitsratio_low_30, nhitsratio_high_30, nhitsratio_low_20, nhitsratio_high_20);
//   CompositeData* m2Pi = new CompositeData("m2Pi", Normal, m2Pi_low_30, m2Pi_high_30, m2Pi_low_20, m2Pi_high_20);
//   CompositeData* m2Ka = new CompositeData("m2Ka", Normal, m2Ka_low_30, m2Ka_high_30, m2Ka_low_20, m2Ka_high_20);


  
  // Any variations applied universally (like epd variation) should not be in this vector.
  std::vector<CompositeData*> composites;
//  composites.push_back(nhits);
  //composites.push_back(nSigPi);
  //composites.push_back(nSigKa);
  composites.push_back(nSigPr);
//   composites.push_back(rvtx);
//   composites.push_back(zvtx);
//   composites.push_back(dca);
//   composites.push_back(nhitsdEdx);
//   composites.push_back(nhitsratio);
  //composites.push_back(m2Pi);
  //composites.push_back(m2Ka);
  ////
  
  newFile->cd();

  //======= CALCULATION OF SYSTEMATIC ERRORS
  Double_t ithBinSysErr = 0.0;
  Double_t quadSum = 0.0;
  Int_t bins;

  AverageContributionTracker avgTracker_00to10;
  AverageContributionTracker avgTracker_10to40;
  AverageContributionTracker avgTracker_40to60;


/*
  //=== proton vs centrality
  //std::cout << "PROTON VS CENTRALITY" << std::endl;
  std::vector<Double_t> v_sys_pr;
  bins = Normal->h_vn_pr->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
    //quadSum += epd->v_vn_pr.at(ithBin).variance;
    //std::cout << "epd variance quadSum: " <<  epd->v_vn_pr.at(ithBin).variance;
    //std::cout << "epd stdDev: " <<  epd->v_vn_pr.at(ithBin).stdDevPercentage;
    //std::cout << "epd ID " <<  epd->ID << std::endl;

    //if (ithBin < 2)
      //avgTracker_00to10.addContribution(epd->ID, epd->v_vn_pr.at(ithBin).stdDevPercentage);
    //if (ithBin >= 2 && ithBin <= 7)
      //avgTracker_10to40.addContribution(epd->ID, epd->v_vn_pr.at(ithBin).stdDevPercentage);
    //if (ithBin > 7 && ithBin < 12)
      //avgTracker_40to60.addContribution(epd->ID, epd->v_vn_pr.at(ithBin).stdDevPercentage);

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
	  if (ithBin > 7 && ithBin < 12)
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
*/    
    
    
    
  //=== Proton vs rapidity 0 - 10%
  //std::cout << "PROTON VS RAPIDITY" << std::endl;
  std::vector<Double_t> v_sys_yCM_00to10_pr;
  bins = Normal->h_vn_yCM_00to10_pr->GetNbinsX();
  for (int ithBin = 0; ithBin < bins; ithBin++)
  {
    quadSum = 0.0;
    //quadSum += epd->v_vn_yCM_00to10_pr.at(ithBin).variance;
 
    //if (ithBin <= 1)
        //avgTracker_00to10.addContribution(epd->ID, epd->v_vn_yCM_00to10_pr.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_00to10_pr.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_00to10_pr.at(ithBin).variance;
        
        if(ithBin < 2)
        {
            avgTracker_00to10.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_00to10_pr.at(ithBin).stdDevPercentage);
        }
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
    //quadSum += epd->v_vn_yCM_10to40_pr.at(ithBin).variance;
    
      //if (ithBin >= 2 && ithBin <= 7)
         //avgTracker_10to40.addContribution(epd->ID, epd->v_vn_yCM_10to40_pr.at(ithBin).stdDevPercentage);
 
    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_10to40_pr.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_10to40_pr.at(ithBin).variance;
        
        if(ithBin >= 2 && ithBin <= 7)
        {
            avgTracker_10to40.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_10to40_pr.at(ithBin).stdDevPercentage);
        }
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
    //quadSum += epd->v_vn_yCM_40to60_pr.at(ithBin).variance;
    
    //if (ithBin >= 8 && ithBin <= 11)
      //avgTracker_40to60.addContribution(epd->ID, epd->v_vn_yCM_40to60_pr.at(ithBin).stdDevPercentage);

    for (int jthCut = 0; jthCut < composites.size(); jthCut++)
    {
      if (composites.at(jthCut)->v_vn_yCM_40to60_pr.at(ithBin).deltaByDeltaError > 1.0)
      {
        quadSum += composites.at(jthCut)->v_vn_yCM_40to60_pr.at(ithBin).variance;
        
        if (ithBin > 7 && ithBin < 12)
        {
            avgTracker_40to60.addContribution(composites.at(jthCut)->ID, composites.at(jthCut)->v_vn_yCM_40to60_pr.at(ithBin).stdDevPercentage);
        }
      }
    }
    
    ithBinSysErr = TMath::Sqrt(quadSum);
    v_sys_yCM_40to60_pr.push_back(ithBinSysErr);
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

  TLine *zeroLine_y_he3 = new TLine(-1, 0, 1, 0);
  zeroLine_y_he3->SetLineStyle(9);

  TLine *zeroLine_y_he4 = new TLine(-1, 0, 1, 0);
  zeroLine_y_he4->SetLineStyle(9);

  TLine *zeroLine_pt = new TLine(0, 0, 2, 0);
  zeroLine_pt->SetLineStyle(9);
    
  if (order_n_str == "3")
    {        
      TLegend *prLegend = new TLegend(0.19, 0.15, 0.39, 0.3);
      prLegend->AddEntry(Normal->h_vn_yCM_10to40_pr, "10 - 40%");
      prLegend->SetBorderSize(0);
      prLegend->SetFillColorAlpha(0,0);




      
     
      
      TPaveText *prText = new TPaveText(5, 0.025, 38, 0.07, "NB");
      prText->AddText("Proton");
      prText->AddText("Au+Au #sqrt{s_{NN}} = 3.0 GeV FXT");
      prText->AddText("0 < y_{CM} < 0.5 GeV");
      prText->AddText("0.4 < p_{T} < 2.0 GeV");
      prText->SetFillColorAlpha(0,0);
      prText->SetLineColorAlpha(0,0);
      

      
      TPaveText *prText_y = new TPaveText(-0.2, 0.02, 0.9, 0.05, "NB");
      prText_y->AddText("Proton");
      prText_y->AddText("Au+Au #sqrt{s_{NN}} = 3.0 GeV FXT");
      prText_y->AddText("0.4 < p_{T} < 2.0 GeV");
      prText_y->SetFillColorAlpha(0,0);
      prText_y->SetLineColorAlpha(0,0);
      prText_y->SetTextSize(.035);

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
      Double_t rapidityUpperBound_he3 = 0.90;
      Double_t rapidityLowerBound_he3 = -0.50;
      Double_t rapidityUpperBound_he4 = 0.90;
      Double_t rapidityLowerBound_he4 = -0.50;
      Double_t ptUpperBound = 0.9;
      Double_t ptLowerBound = -0.08;
      
      TGraphErrors *copyWithNewErrors1;
      TGraphErrors *copyWithNewErrors2;
      TGraphErrors *copyWithNewErrors3;
      TGraphErrors *copyWithNewErrors4;
      TGraphErrors *copyWithNewErrors5;


      
      
      
      
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
      prRapidityStackLow->GetYaxis()->SetTitleOffset(1.9);
      prRapidityStackLow->GetXaxis()->SetNdivisions(210);
      prRapidityStackLow->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      prRapidityStackLow->SetMaximum(-0.011);
      prRapidityStackLow->SetMinimum(0.003);
      prRapidityStackLow->GetXaxis()->SetTitleSize(0.045);
      prRapidityStackLow->GetYaxis()->SetTitleSize(0.05);
      prRapidityStackLow->GetXaxis()->SetRangeUser(0, 1);
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
      //===
      
      
      
      
      
      

      //=== p, d, t, he3, he4 vs rapidity 1040
      THStack *pdthe3he4Rapidity_10to40 = new THStack("pdthe3he4Rapidity_10to40", ";y-y_{mid};v_{"+order_n_str+"}{#psi_{1}}");
      pdthe3he4Rapidity_10to40->Add(Normal->h_vn_yCM_10to40_pr);

      copyWithNewErrors1 = new TGraphErrors((TH1D*)Normal->h_vn_yCM_10to40_pr->Clone());
      for (int i = 0; i < v_sys_yCM_10to40_pr.size(); i++)
	{ copyWithNewErrors1->SetPointError(i, (Double_t)copyWithNewErrors1->GetErrorX(i), v_sys_yCM_10to40_pr.at(i)); }
      
      Normal->h_vn_yCM_10to40_pr->SetMarkerStyle(20);
      Normal->h_vn_yCM_10to40_pr->SetLineWidth(0);
      Normal->h_vn_yCM_10to40_pr->SetMarkerColor(kBlue);
      Normal->h_vn_yCM_10to40_pr->SetLineColor(kBlue);
      pdthe3he4Rapidity_10to40->Draw();
      pdthe3he4Rapidity_10to40->GetYaxis()->SetTitleOffset(1.2);
      pdthe3he4Rapidity_10to40->GetXaxis()->SetNdivisions(210);
      pdthe3he4Rapidity_10to40->Draw();
      //pdthe3he4Rapidity_10to40->SetMaximum(rapidityUpperBound_pdthe3he4);
      //pdthe3he4Rapidity_10to40->SetMinimum(rapidityLowerBound_pdthe3he4);
      pdthe3he4Rapidity_10to40->SetMaximum(0);
      pdthe3he4Rapidity_10to40->SetMinimum(-0.02);
      pdthe3he4Rapidity_10to40->GetXaxis()->SetTitleSize(0.045);
      pdthe3he4Rapidity_10to40->GetYaxis()->SetTitleSize(0.05);
      pdthe3he4Rapidity_10to40->GetXaxis()->SetRangeUser(0, 1); // Set the desired x-axis range
      pdthe3he4Rapidity_10to40->Draw("NOSTACK E1P X0");
      //zeroLine_y->Draw("SAME");
      //pdthe3he4Rapidity_10to40->Draw("NOSTACK E1P X0 SAME");
      copyWithNewErrors1->SetFillColorAlpha(kBlue, 0.3);
      copyWithNewErrors1->Draw("E2");
      canvas->SaveAs("sys_prRapidity_10-40.png");
      canvas->Clear();
      
      Normal->h_vn_yCM_10to40_pr->Write();
      copyWithNewErrors1->Write();
      
      delete copyWithNewErrors1;
      
      
      
      
      
      //=== Proton vs rapidity 40-60
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
      prRapidityStackHigh->GetYaxis()->SetTitleOffset(1.9);
      prRapidityStackHigh->GetXaxis()->SetNdivisions(210);
      prRapidityStackHigh->Draw();
//       prRapidityStack->SetMaximum(rapidityUpperBound_pr);
//       prRapidityStack->SetMinimum(rapidityLowerBound_pr);
      prRapidityStackHigh->SetMaximum(0);
      prRapidityStackHigh->SetMinimum(-0.05);
      prRapidityStackHigh->GetXaxis()->SetTitleSize(0.045);
      prRapidityStackHigh->GetYaxis()->SetTitleSize(0.05);
      prRapidityStackHigh->GetXaxis()->SetRangeUser(0, 1);
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

    
      delete canvas;
    }// End if order_n_str == 3
   

//   delete epd;
//   delete nhits;
  //delete nSigPi;
  //delete nSigKa;
  delete nSigPr;
//   delete rvtx;
//   delete zvtx;
//   delete dca;
//   delete nhitsdEdx;
//   delete nhitsratio;
  //delete m2Pi;
  //delete m2Ka;

  delete Normal;
  delete epd_high;
  delete epd_low;
  //delete epd_scaled;
  
  //delete nSigPi_high_30;
  //delete nSigPi_low_30;
  //delete nSigKa_high_30;
  //delete nSigKa_low_30;
  delete nSigPr_high_30;
  delete nSigPr_low_30;
//   delete rvtx_high_30;
//   delete rvtx_low_30;
//   delete zvtx_high_30;
//   delete zvtx_low_30;
//   delete dca_high_30;
//   delete dca_low_30;
//   delete nhits_high_30;
//   delete nhits_low_30;
//   delete nhitsdEdx_high_30;
  //delete nhitsdEdx_low_30;
//   delete nhitsratio_high_30;
//   delete nhitsratio_low_30;
  //delete m2Pi_high_30;
  //delete m2Pi_low_30;
  //delete m2Ka_high_30;
  //delete m2Ka_low_30;


  /*delete nSigPi_high_20;
  delete nSigPi_low_20;
  delete nSigKa_high_20;
  delete nSigKa_low_20;
  delete nSigPr_high_20;
  delete nSigPr_low_20;
  delete rvtx_high_20;
  delete rvtx_low_20;
  delete zvtx_high_20;
  delete zvtx_low_20;
  delete dca_high_20;
  delete dca_low_20;
  delete nhits_high_20;
  delete nhits_low_20;
  delete nhitsdEdx_high_20;
  delete nhitsdEdx_low_20;
  delete nhitsratio_high_20;
  delete nhitsratio_low_20;
  delete m2Pi_high_20;
  delete m2Pi_low_20;
  delete m2Ka_high_20;
  delete m2Ka_low_20;
  */

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
