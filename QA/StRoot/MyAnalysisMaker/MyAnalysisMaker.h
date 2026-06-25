#ifndef MyAnalysisMaker_def
#define MyAnalysisMaker_def

#include "StMaker.h"
#include "TString.h"
#include "TH1.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TProfile.h"
#include "TLorentzVector.h"
#include "Riostream.h"


class StPicoDst;  
class StPicoDstMaker;
class StPicoEvent;
class StPicoTrack;
class StRefMultCorr ;

class TFile         ;
class TH1F          ;
class TH2F          ;
class TH3F          ;
class TString       ;
class TVector2      ;
class TProfile      ;
class TProfile2D    ;
class TLorentzVector;


class MyAnalysisMaker : public StMaker
{
 public:
  MyAnalysisMaker(StPicoDstMaker* maker) ;           //  Constructor               

  virtual          ~MyAnalysisMaker( ) ;           //  Destructor                  
                                                           
  
  Int_t Init    ( ) ;                              //  Initiliaze the analysis tools ... done once                
  Int_t Make    ( ) ;                              //  The main analysis that is done on each event    
  Int_t Finish  ( ) ;       


  Bool_t IsBadEvent(StPicoEvent *mPicoEvent);
  Bool_t IsBadTrack(StPicoTrack * track, StPicoEvent *mPicoEvent);
  Bool_t isPileUp(UShort_t refMult, UShort_t btofMatched, int VzBin); 
  Int_t Centrality(Int_t gRefMult);
  double ZValue(double mom, double dedx_truncated, char *name, double mass);
  
  void SetOutputFileName(TString name)
  {OutputFileName = name;}                     // Make name available to member functions 
  
 private:
  StPicoDstMaker  *mPicoDstMaker;                   //  Make PicoDst pointer available to member functions               
  StPicoDst       *mPicoDst;
  StPicoEvent    *mPicoEvent;

  StRefMultCorr* refmultCorrUtil;  
  TFile*        histogram_output;                   //  Histograms outputfile pointer                    

  UInt_t        mEventsProcessed;                   //  Number of Events read and processed
  TString         OutputFileName;


  //-------- constants  --------//                                                                                                                                    

  Float_t Pi ;
  Float_t twoPi ;

  Float_t c_light = 29.9792458; //speed of light in [cm/ns]                                                                                                            
  Float_t piMass = 0.13957;
  Float_t kaMass = 0.493677;
  Float_t prMass = 0.938272;
  Float_t elMass = 0.0005109990;


  Int_t   mycentcut = 8;
  Float_t vzcut = 30.0;
  Float_t rapcut = 0.1;


  float      dMass;  
  float      weight;
  double     reweight;


  int        runnumber;
  int runnumberPointer;
  int directionPointer;
  int       centrality;
  int   runnumber_flag;
  int        cent_flag;
  int numbers[1214];

  float  CurrentEvent_Psi;
  int CurrentEvent_centrality; 
  float  CurrentEvent_vz;
  float  CurrentEvent_vy;
  float  CurrentEvent_vx;

  float               Qx;
  float               Qy;
  float       Qx_eta_pos;
  float       Qy_eta_pos;
  float       Qx_eta_neg;
  float       Qy_eta_neg;

  Double_t                 Qxsum;
  Double_t                 Qysum;

  float           cos_part;
  float           sin_part;
  float   cos_part_etawest;
  float   sin_part_etawest;
  float   cos_part_etaeast;
  float   sin_part_etaeast;

  float             sinsum;
  float             cossum;
  float     sinsum_etaeast;
  float     cossum_etaeast;
  float     sinsum_etawest;
  float     cossum_etawest;
  float     res_weight_eta;
  float     resFull;

  float         coscorrect;
  float         sincorrect;
  float coscorrect_etawest;
  float sincorrect_etawest;
  float coscorrect_etaeast;
  float sincorrect_etaeast;
  float  dedx_He_th[12000];
  char  name[60], title[60];

  ifstream       f_dedx_th; 
  float             temp_1;
  float         VertexZPos;
  ifstream      f_rn;

  float           psi_Shift;
  float      psi_Shift_east;
  float      psi_Shift_west;


  Float_t         Vx;
  Float_t         Vy;
  Float_t         Vz;
  Float_t         VzVPD;

  //Int_t           gRefMult;
  unsigned short            gRefMult;
  Int_t           refMult;
  Int_t           TOFMult;

  Int_t nPrimVtx;
  Double_t zdc_cons;
  Double_t bbc_cons;
  Int_t    cent;
  Double_t Corr_refMult;


  Int_t trackId;
  Float_t pp;
  Float_t pt;
  Int_t q;
  Float_t gdca;
  Float_t eta;
  Int_t nHits;
  Int_t nHitsFit;
  UShort_t nHitsPoss;
  Int_t nHitsdEdx;
  Float_t phi;
  Float_t dEdx;

  Float_t nSigmaPi;
  Float_t nSigmaKa;  
  Float_t nSigmaPr;

  Double_t Zpi;
  Double_t Zka;
  Double_t Zpr;

  short   flag;
  float   pathLength;
  short   matchFlag;
  double beta = -999;
  float tof = -999;

  TLorentzVector LVpi;
  TLorentzVector LVka;
  TLorentzVector LVpr;


  //------histograms pointer------------                                                                                                       
  TH1F *EventCount;
  TH1F *CentCount;

//Before Cuts
  TH1* hrefmult_all;
  TH1* hvx_all;
  TH1* hvy_all;
  TH1* hvz_all;
  TH2* hvxvy_all;
  TH1* hvz_VPD_all;
  TH1* hvrad_all;
//After cuts
  TH1* hvx;
  TH1* hvy;
  TH1* hvz;
  TH2* hvxvy;
  TH1* hvrad;
  TH1* hvz_VPD;
  TH1* hrefmult;

//Before cuts
  TH1* hpt_all;
  TH1* heta_all;
  TH1* hdca_all;
  TH1* hnHitsFit_all;
  TH1* hphi_all;

  TH2F *hdEdxvsp_all;
  TH2F *hbeta_all;

//After cuts
  TH1* hpt;
  TH1* heta;
  TH1* hdca;
  TH1* hnHitsFit;
  TH1* hphi;

  TH2F *hdEdxvsp;
  TH2F *hbeta;
  TH2F *hMass2;

  TH2F                           *hQxQy;
  TH1F                      *EventPlane;
  TH1F                   *EventPlane_rc;
  TH1F                *EventPlane_shift;
  
  TH1F *EventP_east_rec;
  TH1F *EventP_west_rec;
  TH1F *EventPlane_east;
  TH1F *EventPlane_west;


  //track loop hists:
  TH2F                *hetaphi;
  TH2F                *dEdxvsp;          
  TH2F               *dEdxvspt;        
  TH2F             *dEdxvspHe3;        
  TH2F         *dEdxvspantiHe3;  
  TProfile          *He3CosRes_eta;   
TH1D* hPhiAll;
TH1D* hphi_farwest[10];
TH1D* hphi_west[10];
TH1D* hphi_east[10];
TH1D* hphi_fareast[10];
      
TH1D* hphi_farwest_eta[10];
TH1D* hphi_west_eta[10];
TH1D* hphi_east_eta[10];
TH1D* hphi_fareast_eta[10];
  TH3F      *He3dedxZPhiPt[10]; 
  TH3F     *He3dedxZPhiPt2[10];  
  TH3F  *antiHe3dedxZPhiPt[10];
  TH3F *antiHe3dedxZPhiPt2[10];
  TH3F       *He3gDcaPhiPt[10];     
  TH3F   *antiHe3gDcaPhiPt[10]; 
TProfile *runidvsavgsdcaxy;
TProfile *runidvsavgvz;
TProfile *runidvstofmult;
TProfile *runidvsrefmult; 
TProfile *runidvsavgeta;
TProfile *runidvsavgphi;
TProfile *runidvsavgdca;

TProfile *runidvsavgdcaxy;
TProfile *runidvsavgdedx;
  TProfile2D     *cosfarwest_correction;
  TProfile2D     *sinfarwest_correction;
  TProfile2D        *coswest_correction;
  TProfile2D        *sinwest_correction;
  TProfile2D        *coseast_correction;
  TProfile2D        *sineast_correction;
  TProfile2D     *cosfareast_correction;
  TProfile2D     *sinfareast_correction;
  TProfile2D    *coswest_correction_eta;
  TProfile2D    *sinwest_correction_eta;
  TProfile2D    *coseast_correction_eta;
  TProfile2D    *sineast_correction_eta;
  TProfile2D *cosfarwest_correction_eta; 
  TProfile2D *sinfarwest_correction_eta;
  TProfile2D *cosfareast_correction_eta;
  TProfile2D *sinfareast_correction_eta;

  float            FTPCshift_sinAvg[30];
  float            FTPCshift_cosAvg[30];
  float       FTPCshift_sinAvg_west[30];
  float       FTPCshift_cosAvg_west[30];
  float       FTPCshift_sinAvg_east[30];
  float       FTPCshift_cosAvg_east[30];

	TProfile2D*  mcoscorrect_farwest;
	TProfile2D*  msincorrect_farwest;
	TProfile2D*  mcoscorrect_west;
	TProfile2D*  msincorrect_west;
	TProfile2D*  mcoscorrect_east;
	TProfile2D*  msincorrect_east;
	TProfile2D*  mcoscorrect_fareast;
	TProfile2D*  msincorrect_fareast;


	TProfile2D*  mcoscorrect_farwest_eta;
	TProfile2D*  msincorrect_farwest_eta;
	TProfile2D*  mcoscorrect_west_eta;
	TProfile2D*  msincorrect_west_eta;
	TProfile2D*  mcoscorrect_east_eta;
	TProfile2D*  msincorrect_east_eta;
	TProfile2D*  mcoscorrect_fareast_eta;
	TProfile2D*  msincorrect_fareast_eta;

Float_t  v_mcoscorrect_farwest2;
Float_t  v_msincorrect_farwest2;
Float_t  v_mcoscorrect_west2;
Float_t  v_msincorrect_west2;
Float_t  v_mcoscorrect_east2;
Float_t  v_msincorrect_east2;
Float_t  v_mcoscorrect_fareast2;
Float_t  v_msincorrect_fareast2;

Float_t  v_mcoscorrect_farwest_eta2;
Float_t  v_msincorrect_farwest_eta2;
Float_t  v_mcoscorrect_west_eta2;
Float_t  v_msincorrect_west_eta2;
Float_t  v_mcoscorrect_east_eta2;
Float_t  v_msincorrect_east_eta2;
Float_t  v_mcoscorrect_fareast_eta2;
Float_t  v_msincorrect_fareast_eta2;


  /*
  Float_t         Vx;
  Float_t         Vy;
  Float_t         Vz;
  Float_t         VzVPD;

  Int_t           gRefMult;
  Int_t           RefMult;
  Int_t           TOFMult;

  Int_t                runnumber;
  Int_t                cent_flag;
  Int_t           runnumber_flag;
  Int_t         runnumberPointer;


  //---------------nTuple pointers------------
  TTree                       *t1;

  Float_t   Kapt[500000];
  Float_t   Prpt[500000];


  //-------------------------------------------------------------------New initilization ----------------------------
  Double_t Zpi;
  Double_t Zka;
  Double_t Zpr;
  Int_t cent;
 
  TH1F *func1;
  TH1F *fucn2;





  Int_t trackId;
  Float_t p;
  Float_t pt;
  Int_t q;
  Float_t gdca;
  Float_t eta;
  Int_t nHits;
  Int_t nHitsFit;
  UShort_t nHitsPoss;
  Int_t nHitsdEdx;
  Float_t phi;
  Float_t dEdx;

  Float_t nSigmaPi;
  Float_t nSigmaKa;  
  Float_t nSigmaPr;

  TLorentzVector LVpi;
  TLorentzVector LVka;
  TLorentzVector LVpr;


  Char_t                name[60];

  //-------- constants  --------//                                                                          
  
  Float_t Pi ;
  Float_t twoPi ;

  Float_t c_light = 29.9792458; //speed of light in [cm/ns]                                                         
  Float_t piMass = 0.13957;
  Float_t kaMass = 0.493677;
  Float_t prMass = 0.938272;
  Float_t elMass = 0.0005109990;

  
  Int_t   mycentcut = 8;
  Float_t vzcut = 30.0;
  Float_t rapcut = 0.1;

  //------histograms pointer------------                                                                                                       
 
  TH1D *test;
  TH1D *test1;
  TH2D *ptCent;
  TH1F *Cent_value;


  TH1F *Cent0_5;
  TH1F *Cent5_10;
  TH1F *Cent10_20;
  TH1F *Cent20_30;
  TH1F *Cent30_40;
  TH1F *Cent40_50;
  TH1F *Cent50_60;
  TH1F *Cent60_70;
  TH1F *Cent70_80;

  TH1* pt_pion;
  TH1* pt_kaon;
  TH1* pt_proton;
  TH1F *hP_rap;


  TH1F *EventCount;
  TH1F *CentCount;

  TH1* hgrefmult;
  TH1* hrefmult;
  TH1* hvx_all;
  TH1* hvy_all;
  TH1* hvz_all;
  TH2* hvxvy_all;
  TH1* hnprim;
  TH1* hvz;
  TH2* hvxvy;
  TH1* hvrad;
  TH1* hvz_VPD;
  
  TH1* hpt;
  TH1* heta;
  TH1* hdca;
  TH1* hnHitsFit;
  TH1* hphi;



  TH1D*  hnhits_pre;
  TH1D* hnfit_nfitposs_pre;
  TH1D*  hndedx_pre;
  TH1D*  hdca_pre;
  TH1D*  heta_pre;
  TH1D*  hrapidity_pre;


 TH1D* hnfit_nfitposs_main;
 TH1D* hndedx_main;










  TH2F *hdEdxvsp;
  TH2F *betaHis ;
  TH2F *hMass2 ;
  
  TH2* hnsigmapipos ;
  TH2* hnsigmapineg ;
  TH2* hnsigmakapos ;
  TH2* hnsigmakaneg ;
  TH2* hnsigmaprpos ;
  TH2* hnsigmaprneg ;

  //----------------------------for test without cut----------

 TH2*  hzpipos_wcut;
 TH2*  hzkapos_wcut;
 TH2*  hzprpos_wcut;
 TH2*  hzpineg_wcut;
 TH2*  hzkaneg_wcut;
 TH2*  hzprneg_wcut;

 TH3D *hZpipos;
 TH3D *hZpineg;
 TH3D *hZkapos;
 TH3D *hZkaneg;
 TH3D *hZprpos;
 TH3D *hZprneg;
  
 ifstream inp;
 ofstream myfile;
 ofstream myfile2;

 TProfile *hptdiff1;
 TProfile *hptdiff2;


 //---------------------
 TH2D *hZkpos9;
 TH2D *hZkpos8;
 TH2D *hZkpos7;
 TH2D *hZkpos6;
 TH2D *hZkpos5;
 TH2D *hZkpos4;
 TH2D *hZkpos3;
 TH2D *hZkpos2;
 TH2D *hZkpos1;

 TH2D *hZkneg9;
 TH2D *hZkneg8;
 TH2D *hZkneg7;
 TH2D *hZkneg6;
 TH2D *hZkneg5;
 TH2D *hZkneg4;
 TH2D *hZkneg3;
 TH2D *hZkneg2;
 TH2D *hZkneg1;
 //--------------------------
 //--------------------------
 TH2D *hZprpos9;
 TH2D *hZprpos8;
 TH2D *hZprpos7;
 TH2D *hZprpos6;
 TH2D *hZprpos5;
 TH2D *hZprpos4;
 TH2D *hZprpos3;
 TH2D *hZprpos2;
 TH2D *hZprpos1;

 TH2D *hZprneg9;
 TH2D *hZprneg8;
 TH2D *hZprneg7;
 TH2D *hZprneg6;
 TH2D *hZprneg5;
 TH2D *hZprneg4;
 TH2D *hZprneg3;
 TH2D *hZprneg2;
 TH2D *hZprneg1;

 TH3D* hptdcaPr;
 TH3D* hptdcaAntiPr;
 TH1F *pt_kaon_withoutcorr;
 TH1F *pt_proton_withoutcorr;

  */
 protected:
  
  ClassDef(MyAnalysisMaker,1)                       //Macro for CINT compatability 
    
    };

#endif

