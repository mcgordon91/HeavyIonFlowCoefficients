#ifndef TreeAnalyzerCumulant_def
#define TreeAnalyzerCumulant_def


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
class TreeAnalyzerCumulant : public StMaker 
{

    public:
        TreeAnalyzerCumulant(StPicoDstMaker *picoMaker, Char_t *JobID, Char_t *Systematic);   // constructor
        virtual ~TreeAnalyzerCumulant(){}                                 // destructor

        virtual void Clear(Option_t *option=""); // called after every event to cleanup
        virtual Int_t  Init();                   // called once at the beginning of your job
        virtual Int_t  Make();                   // invoked for every event
        virtual Int_t  Finish();                 // called once at the end



    private:
        const Int_t nPsi = 1;
        const Int_t nV = 1;
    
        StPicoDstMaker *mPicoDstMaker;
        StPicoDst   *mPicoDst;
        StPicoEvent *picoEvent;

        TFile *TPCEfficiencyFile;
        TFile *ToFEfficiencyFile;
        TFile *TPCEfficiencyFileDandT;
  
        string ID;
        string Variation;

        
        //Histograms
        TH1D *QxRefA;
        TH1D *QyRefA;
        TH1D *QxRefB;
        TH1D *QyRefB;
        TH1D *QxPOI;
        TH1D *QyPOI;

        TProfile *AvgCosCentEPD;
        TProfile *AvgSinCentEPD;
        TProfile *AvgCosCentTPC[7];
        TProfile *AvgSinCentTPC[7];
        TProfile *AvgCosPt00_10TPC[7];
        TProfile *AvgSinPt00_10TPC[7];
        TProfile *AvgCosPt10_40TPC[7];
        TProfile *AvgSinPt10_40TPC[7];
        TProfile *AvgCosPt40_60TPC[7];
        TProfile *AvgSinPt40_60TPC[7];
        TProfile *AvgCosY00_10TPC[7];
        TProfile *AvgSinY00_10TPC[7];
        TProfile *AvgCosY10_40TPC[7];
        TProfile *AvgSinY10_40TPC[7];
        TProfile *AvgCosY40_60TPC[7];
        TProfile *AvgSinY40_60TPC[7];



        TH1D *TPCPhi;
        TH1D *EPDPhi;
        TH2F *HistoD12;
        TH2F *HistoD13;
        TH2F *HistoD14;
        TH2F *HistoD15;
        TH2F *HistoD16;
        TH2F *HistoD17;
        TH2F *HistoD27;
        TH2F *HistoD27A;
        TH2F *HistoD27B;
        TH2F *HistoD28;
        TH2F *HistoD29;
        TH2F *HistoD30;
        TH2F *HistoD31;

        TH2D *TPCAcceptance;
        TH2D *EPDAcceptance;

        TH2D *AllTracksToFDetected;

        TH1D *MSquaredBToF;
        TH1D *MSquaredEToF;
        
        TH1D *RunCount;

        TH1D *EventCheck;

        TH1F *OverallTrackCheckNoCuts;
        TH1F *OverallTrackCheckQACuts;
        TH1F *OverallTrackCheckIDedAsAny;


        TProfile *TwoPartRefVsCent;
        TProfile *TwoPartDiffVsCent[7];
        TProfile2D *TwoPartDiffVsCentVsPt[7];
        TProfile2D *TwoPartDiffVsCentVsY[7];

        TProfile *FourPartRefVsCent;
        TProfile *FourPartDiffVsCent[7];
        TProfile2D *FourPartDiffVsCentVsPt[7];
        TProfile2D *FourPartDiffVsCentVsY[7];

        
    
        StEpdGeom* epdGeom;

ClassDef(TreeAnalyzerCumulant,1)
};
#endif
