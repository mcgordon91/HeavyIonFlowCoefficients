#ifndef TreeAnalyzer_def
#define TreeAnalyzer_def


#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>


#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TProfile3D.h>


#include "StMaker.h"
#include "StEpdUtil/StEpdGeom.h"
#include "StEpdUtil/StEpdEpInfo.h"


class StPicoDst;
class StPicoDstMaker;
class StPicoEvent;
class TFile;
class TH1;
class TH2;
class TProfile;



//  The class declaration. It innherits from StMaker.
class TreeAnalyzer : public StMaker 
{

    public:
        TreeAnalyzer(StPicoDstMaker *picoMaker, Char_t *JobID, Char_t *Systematic);   // constructor
        virtual ~TreeAnalyzer(){}                                 // destructor

        virtual void Clear(Option_t *option=""); // called after every event to cleanup
        virtual Int_t  Init();                   // called once at the beginning of your job
        virtual Int_t  Make();                   // invoked for every event
        virtual Int_t  Finish();                 // called once at the end



    private:
        const Int_t nPsi = 1;
        const Int_t nV = 3;
        
        const Int_t QBounds = 100;
        const Int_t FourierCorrectionTerms = 10;
    
        StPicoDstMaker *mPicoDstMaker;
        StPicoDst   *mPicoDst;
        StPicoEvent *picoEvent;
  
        string ID;
        string Variation;
        
        Int_t RunIteration;
        
        TH1D *InnerEPDQxMeanHisto;
        TH1D *InnerEPDQyMeanHisto;
        TH1D *OuterEPDQxMeanHisto;
        TH1D *OuterEPDQyMeanHisto;
        TH1D *OuterTPCQxMeanHisto;
        TH1D *OuterTPCQyMeanHisto;
        
        TFile *QVectorHistogramFileFirst;
        TFile *QVectorHistogramFileSecond;
        TFile *ResolutionFile;
        TFile *TPCEfficiencyFile;
        TFile *ToFEfficiencyFile;
        TFile *TPCEfficiencyFileDandT;
        
        Double_t InnerEPDQxMean;
        Double_t InnerEPDQyMean;
        Double_t OuterEPDQxMean;
        Double_t OuterEPDQyMean;
        Double_t OuterTPCQxMean;
        Double_t OuterTPCQyMean;
        
        TProfile *InnerEPDSineAverageProfile;
        TProfile *InnerEPDCosineAverageProfile;
        TProfile *OuterEPDSineAverageProfile;
        TProfile *OuterEPDCosineAverageProfile;
        TProfile *OuterTPCSineAverageProfile;
        TProfile *OuterTPCCosineAverageProfile;
        
        
        
        
        
        //Histograms

        //First Pass Histograms
        TH1D *HistoInnerEPDQxRaw;
        TH1D *HistoInnerEPDQyRaw;
        TH1D *HistoOuterEPDQxRaw;
        TH1D *HistoOuterEPDQyRaw;
        TH1D *HistoOuterTPCQxRaw;
        TH1D *HistoOuterTPCQyRaw;
        
        TH1D *ZVertexValues;
        TH1D *RVertexValues;
        TH1D *DCAValues;
        TH1D *NHitsValues;
        TH1D *NHitsdEdxValues;
        TH1D *NHitsFitOverNHitsPossValues;
        
        TProfile *pVx;
        TProfile *pVy;
        TProfile *pVz;
        TProfile *pPt;
        TProfile *pEta;

        TH1D *HitCountOuterEPD;
        TH1D *Centralities;

        TH1F *HistoDA;
        TH1F *HistoDB;

        TH2D *h2_zd_vs_mom;
        TH2D *h2_zt_vs_mom;

        TH2F *HistoD0;
        TH1F *HistoD1;
        TH1F *HistoD2;
        TH2F *HistoD3;
        TH2F *HistoD4;
        TH2F *HistoD4A;
        TH1F *HistoD5;
        TH1F *HistoD6;
        TH1F *HistoD7;
        TH1F *HistoD8;
        TH1F *HistoD9;
        TH1F *HistoD10;
        TH1F *HistoD11;
        TH2F *HistoD12;
        TH2F *HistoD13;
        TH2F *HistoD14;
        TH2F *HistoD15;
        TH2F *HistoD16;
        TH2F *HistoD17;
        TH2F *HistoD18;
        TH2F *HistoD19;
        TH2F *HistoD20;
        TH1F *HistoD21;
        TH1F *HistoD22;
        TH1F *HistoD23;
        TH2F *HistoD24;
        TH2F *HistoD25;
        TH2F *HistoD26;
        TH2F *HistoD27;
        TH2F *HistoD27A;
        TH2F *HistoD27B;
        TH2F *HistoD28;
        TH2F *HistoD29;
        TH2F *HistoD30;
        TH2F *HistoD31;
        TH1F *HistoD32;
        TH1F *HistoD32A;
        TH2F *HistoD32B;
        TH1F *HistoD33;
        TH1F *HistoD36;
        TH1F *HistoD39;

        TH1F *InvariantMasses;
        TH2F *LambdaAcceptance;



        //Second Pass Histograms

        TH1D *HistoInnerEPDQxRecentered;
        TH1D *HistoInnerEPDQyRecentered;
        TH1D *HistoOuterEPDQxRecentered;
        TH1D *HistoOuterEPDQyRecentered;
        TH1D *HistoOuterTPCQxRecentered;
        TH1D *HistoOuterTPCQyRecentered;

        TProfile *HistoInnerEPDSineAverages;
        TProfile *HistoInnerEPDCosineAverages;
        TProfile *HistoOuterEPDSineAverages;
        TProfile *HistoOuterEPDCosineAverages;
        TProfile *HistoOuterTPCSineAverages;
        TProfile *HistoOuterTPCCosineAverages;

        TH1F *HistoD34;
        TH1F *HistoD37;
        TH1F *HistoD40;



        //Third Pass Histograms        

        TH1F *HistoD35;
        TH1F *HistoD38;
        TH1F *HistoD41;
        TProfile *HistoD51;
        TProfile *HistoD52;
        TProfile *HistoD53;






        //Fourth Pass Histograms
        
        TH1D *RunCount;

        TH1D *EventCheck;

        TH1F *OverallTrackCheckNoCuts;
        TH1F *OverallTrackCheckQACuts;
        TH1F *OverallTrackCheckIDedAsAny;
        TH1F *ProtonTrackCheck;
        TH1F *MostlyGoodProtonTrackCheck;
        TH1F *GoodProtonTrackCheck;
        TH1F *KaonPlusTrackCheck;
        TH1F *MostlyGoodKaonPlusTrackCheck;
        TH1F *GoodKaonPlusTrackCheck;
        TH1F *KaonMinusTrackCheck;
        TH1F *MostlyGoodKaonMinusTrackCheck;
        TH1F *GoodKaonMinusTrackCheck;
        TH1F *PionPlusTrackCheck;
        TH1F *MostlyGoodPionPlusTrackCheck;
        TH1F *GoodPionPlusTrackCheck;
        TH1F *PionMinusTrackCheck;
        TH1F *MostlyGoodPionMinusTrackCheck;
        TH1F *GoodPionMinusTrackCheck;
        TH1F *DeuteronTrackCheck;
        TH1F *MostlyGoodDeuteronTrackCheck;
        TH1F *GoodDeuteronTrackCheck;
        TH1F *TritonTrackCheck;
        TH1F *MostlyGoodTritonTrackCheck;
        TH1F *GoodTritonTrackCheck;

        TH1F *HistoDC;
        TH1F *HistoDD;
        TH1F *HistoDE;

        TH1F *TrackMultiplicity;
        
        TProfile *HistoD54;

        TProfile *HistoD44C;
        TProfile *HistoD47B;
        TProfile *HistoD47C;
        TProfile *HistoD50B;
        TProfile *HistoD50C;
        TProfile *HistoD50D;
        TProfile *HistoD50E;
        TProfile *HistoD54A;
        TProfile *HistoD54B;
        TProfile *HistoD54C;
        TProfile *HistoD54D;
        TProfile *HistoD54E;
        TProfile *HistoD54F;
        TProfile *HistoD54G;
        TProfile2D *HistoD79;
        TProfile2D *HistoD80;
        TProfile2D *HistoD81;
        TProfile2D *HistoD82;
        TProfile2D *HistoD83;
        TProfile2D *HistoD84;
        TProfile2D *HistoD85;
        TProfile2D *HistoD86;
        TProfile2D *HistoD87;
        TProfile2D *HistoD88;
        TProfile2D *HistoD88A;
        TProfile2D *HistoD88B;
        TProfile2D *HistoD88C;
        TProfile2D *HistoD88D;

        TProfile2D *VnVsYSymmetricProton;

        TProfile *VnVsPtProton0_00Through0_10;
        TProfile *VnVsPtProton0_10Through0_20;
        TProfile *VnVsPtProton0_20Through0_30;
        TProfile *VnVsPtProton0_30Through0_40;

        TProfile *VnVsPtDeuteron0_00Through0_10;
        TProfile *VnVsPtDeuteron0_10Through0_20;
        TProfile *VnVsPtDeuteron0_20Through0_30;
        TProfile *VnVsPtDeuteron0_30Through0_40;

        TProfile *VnVsPtTriton0_00Through0_10;
        TProfile *VnVsPtTriton0_10Through0_20;
        TProfile *VnVsPtTriton0_20Through0_30;
        TProfile *VnVsPtTriton0_30Through0_40;

        TProfile *VnOverAVsPtOverAProton0_00Through0_10;
        TProfile *VnOverAVsPtOverAProton0_10Through0_20;
        TProfile *VnOverAVsPtOverAProton0_20Through0_30;
        TProfile *VnOverAVsPtOverAProton0_30Through0_40;

        TProfile *VnOverAVsPtOverADeuteron0_00Through0_10;
        TProfile *VnOverAVsPtOverADeuteron0_10Through0_20;
        TProfile *VnOverAVsPtOverADeuteron0_20Through0_30 ;
        TProfile *VnOverAVsPtOverADeuteron0_30Through0_40;

        TProfile *VnOverAVsPtOverATriton0_00Through0_10;
        TProfile *VnOverAVsPtOverATriton0_10Through0_20;
        TProfile *VnOverAVsPtOverATriton0_20Through0_30;
        TProfile *VnOverAVsPtOverATriton0_30Through0_40 ;
        
    
        StEpdGeom* epdGeom;

ClassDef(TreeAnalyzer,1)
};
#endif