#ifndef ToFEfficiencyMaker_def
#define ToFEfficiencyMaker_def


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
class ToFEfficiencyMaker : public StMaker 
{

    public:
        ToFEfficiencyMaker(StPicoDstMaker *picoMaker, Char_t *JobID);   // constructor
        virtual ~ToFEfficiencyMaker(){}                                 // destructor

        virtual void Clear(Option_t *option=""); // called after every event to cleanup
        virtual Int_t  Init();                   // called once at the beginning of your job
        virtual Int_t  Make();                   // invoked for every event
        virtual Int_t  Finish();                 // called once at the end



    private:
        StPicoDstMaker *mPicoDstMaker;
        StPicoDst   *mPicoDst;
        StPicoEvent *picoEvent;

        const Int_t nV = 6;

        string ID;
        
        
        
        
        
        //Histograms
        TH1D *EventCheck;

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


ClassDef(ToFEfficiencyMaker,1)
};
#endif
