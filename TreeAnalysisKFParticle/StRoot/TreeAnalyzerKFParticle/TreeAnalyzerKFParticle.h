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
        const Int_t nV = 4;

        const Bool_t UsingModifiedBesselResolution = true;
        
        const Int_t QBounds = 100;
        const Int_t FourierCorrectionTerms = 10;

        Int_t QVectorDirectoryNumber;
    
        StPicoDstMaker *mPicoDstMaker;
        StPicoDst   *mPicoDst;
        StPicoEvent *picoEvent;
  
        string ID;
        string Variation;
        
        Int_t RunIteration;
        
        TH1D *InnerEPDQxMeanHisto[16];
        TH1D *InnerEPDQyMeanHisto[16];
        TH1D *OuterEPDQxMeanHisto[16];
        TH1D *OuterEPDQyMeanHisto[16];
        TH1D *OuterTPCQxMeanHisto[16];
        TH1D *OuterTPCQyMeanHisto[16];
        
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
        
        TProfile2D *InnerEPDSineAverageProfile[16];
        TProfile2D *InnerEPDCosineAverageProfile[16];
        TProfile2D *OuterEPDSineAverageProfile[16];
        TProfile2D *OuterEPDCosineAverageProfile[16];
        TProfile2D *OuterTPCSineAverageProfile[16];
        TProfile2D *OuterTPCCosineAverageProfile[16];
        
        
        
        
        
        //Histograms

        //First Pass Histograms
        TH1D *HistoInnerEPDQxRaw[16];
        TH1D *HistoInnerEPDQyRaw[16];
        TH1D *HistoOuterEPDQxRaw[16];
        TH1D *HistoOuterEPDQyRaw[16];
        TH1D *HistoOuterTPCQxRaw[16];
        TH1D *HistoOuterTPCQyRaw[16];

        TProfile *HistoInnerEPDQxRawByRun[16];
        TProfile *HistoInnerEPDQyRawByRun[16];
        TProfile *HistoOuterEPDQxRawByRun[16];
        TProfile *HistoOuterEPDQyRawByRun[16];
        TProfile *HistoOuterTPCQxRawByRun[16];
        TProfile *HistoOuterTPCQyRawByRun[16];
        
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
        TH1D *CentralitiesNineToFifteenOuterEPDHitsOnly;

        TH1F *HistoDA;
        TH1F *HistoDB;

        TH2D *h2_zd_vs_mom;
        TH2D *h2_zt_vs_mom;
        TH1D *MomentumDistributionBischel;
        TH1D *ZDeuteronDistribution;
        TH1D *ZTritonDistribution;

        TH2F *HistoD0;
        TH1F *HistoD1;
        TH1F *HistoD2;
        TH2D *HistoD3;
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
        TH1F *HistoD33[16];
        TH1F *HistoD36[16];
        TH1F *HistoD39[16];

        TH1F *InvariantMassesLambda;
        TH1F *InvariantMassesKShort;
        TH2F *LambdaAcceptance;
        TH2F *KShortAcceptance;
        TH1F *ProtonMultiplicity;
        TH1F *PionPlusMultiplicity;
        TH1F *PionMinusMultiplicity;

        TH1D *EToFFlags;
        TH2D *ProtonTPCDetected;
        TH2D *ProtonTPCDetectedRapidity;
        TH2D *KaonPlusTPCDetected;
        TH2D *KaonPlusTPCDetectedRapidity;
        TH2D *KaonMinusTPCDetected;
        TH2D *KaonMinusTPCDetectedRapidity;
        TH2D *PionPlusTPCDetected;
        TH2D *PionPlusTPCDetectedRapidity;
        TH2D *PionMinusTPCDetected;
        TH2D *PionMinusTPCDetectedRapidity;
        TH2D *DeuteronTPCDetected;
        TH2D *TritonTPCDetected;
        TH2D *ProtonToFDetected;
        TH2D *ProtonToFDetectedRapidity;
        TH2D *ProtonToFDetectedRapidityMSquaredCuts;
        TH2D *ProtonEToFDetected;
        TH2D *ProtonEToFDetectedRapidity;
        TH2D *KaonPlusToFDetected;
        TH2D *KaonPlusToFDetectedRapidity;
        TH2D *KaonPlusToFDetectedRapidityMSquaredCuts;
        TH2D *KaonPlusEToFDetected;
        TH2D *KaonPlusEToFDetectedRapidity;
        TH2D *KaonMinusToFDetected;
        TH2D *KaonMinusToFDetectedRapidity;
        TH2D *KaonMinusToFDetectedRapidityMSquaredCuts;
        TH2D *KaonMinusEToFDetected;
        TH2D *KaonMinusEToFDetectedRapidity;
        TH2D *PionPlusToFDetected;
        TH2D *PionPlusToFDetectedRapidity;
        TH2D *PionPlusToFDetectedRapidityMSquaredCuts;
        TH2D *PionPlusEToFDetected;
        TH2D *PionPlusEToFDetectedRapidity;
        TH2D *PionMinusToFDetected;
        TH2D *PionMinusToFDetectedRapidity;
        TH2D *PionMinusToFDetectedRapidityMSquaredCuts;
        TH2D *PionMinusEToFDetected;
        TH2D *PionMinusEToFDetectedRapidity;
        TH2D *DeuteronToFDetected;
        TH2D *DeuteronEToFDetected;
        TH2D *TritonToFDetected;
        TH2D *TritonEToFDetected;
        TH2D *AllTracksToFDetected;

        TH1D *GlobalPt;
        TH1D *GlobalEta;
        TH1D *GlobalPhi;
        TH1D *GlobalPtProton;
        TH1D *GlobalEtaProton;
        TH1D *GlobalPtPionPlus;
        TH1D *GlobalEtaPionPlus;
        TH1D *GlobalPtPionMinus;
        TH1D *GlobalEtaPionMinus;
        TH2D *GlobaldEdxVsP;

        TH1D *KaonPlusPtOutliersEta;
        TH1D *KaonPlusPtOutliersMSquared;
        TH1D *PionPlusPtOutliersEta;
        TH1D *PionPlusPtOutliersMSquared;

        TH1D *MSquaredBToF;
        TH1D *MSquaredEToF;



        //Second Pass Histograms

        TH1D *HistoInnerEPDQxRecentered[16];
        TH1D *HistoInnerEPDQyRecentered[16];
        TH1D *HistoOuterEPDQxRecentered[16];
        TH1D *HistoOuterEPDQyRecentered[16];
        TH1D *HistoOuterTPCQxRecentered[16];
        TH1D *HistoOuterTPCQyRecentered[16];

        TProfile2D *HistoInnerEPDSineAverages[16];
        TProfile2D *HistoInnerEPDCosineAverages[16];
        TProfile2D *HistoOuterEPDSineAverages[16];
        TProfile2D *HistoOuterEPDCosineAverages[16];
        TProfile2D *HistoOuterTPCSineAverages[16];
        TProfile2D *HistoOuterTPCCosineAverages[16];

        TH1F *HistoD34[16];
        TH1F *HistoD37[16];
        TH1F *HistoD40[16];



        //Third Pass Histograms        

        TH1F *HistoD35[16];
        TH1F *HistoD38[16];
        TH1F *HistoD41[16];
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
        TProfile *VnVsCentralityProtonHighRapidity;
        TProfile *VnVsCentralityDeuteronHighRapidity;
        TProfile *VnVsCentralityTritonHighRapidity;
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
        TProfile2D *VnVsCentPtProtonHighRapidity;
        TProfile2D *VnVsCentPtDeuteronHighRapidity;
        TProfile2D *VnVsCentPtTritonHighRapidity;
        TProfile *FlowStrength;
        TProfile *FlowStrengthProton;


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
