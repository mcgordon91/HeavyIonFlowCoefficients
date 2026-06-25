
//###################################################################################################//
//~~~~~~~~~~~~~~~~~~~~~~Sample code for making input file for QA package~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~Please edit the code and define the TProfiles as per your requirment~~~~~~~~~~~~~~~// 
//~~~~~~~~~~~~~~~~~Prepared for the QA group for FXT data by Sharangrav Sharma~~~~~~~~~~~~~~~~~~~~~~~//
//###################################################################################################//

#include "MyAnalysisMaker.h"
#include <iostream>
#include "StRoot/StPicoEvent/StPicoDst.h"
#include "StRoot/StPicoEvent/StPicoEvent.h"
#include "StRoot/StPicoEvent/StPicoTrack.h"
#include "StRoot/StPicoDstMaker/StPicoDstMaker.h"
#include "StRoot/StPicoEvent/StPicoBTofPidTraits.h"
#include "StRoot/StRefMultCorr/StRefMultCorr.h"
#include "StBichsel/Bichsel.h"
#include "StRefMultCorr/CentralityMaker.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include "TMath.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TProfile.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TProfile2D.h"
#include "TProfile.h"
#include "TLorentzVector.h"
#include "StThreeVectorF.hh"
#include "TObjArray.h"
#include "TComplex.h"
#include "para_pileup.h"

using namespace std;
ClassImp(MyAnalysisMaker)                       // Macro for CINT compatibility
MyAnalysisMaker::MyAnalysisMaker(StPicoDstMaker* maker ) : StMaker("MyAnalysisMaker")
{                                               // Initialize data members here.            
  mPicoDstMaker    = maker ;                  
  mPicoDst = 0;
  histogram_output = NULL  ;                    
  mEventsProcessed = 0     ;                   
  OutputFileName = "" ;                        
}

MyAnalysisMaker::~MyAnalysisMaker()
{/* */}

Int_t MyAnalysisMaker::Init()
{
  dMass = 1.8756;
  Pi    =  3.14159;
  twoPi =   2.0*Pi;  

  runnumber_flag   =   1214;    
  runnumber        =   -15100001;
  runnumberPointer =   0;
  directionPointer =   0;
  centrality       =   0;
  cent_flag        =  10;
 

  CurrentEvent_vz = 999.;
  CurrentEvent_vx = 999.;
  CurrentEvent_vy = 999.;
  Qx = 0.;
  Qy = 0.;
  weight = 1.;

  //====Run Number File===
  f_rn.open("/star/u/sharangrav/RunbyRunQA/run_qa_code/p24iy_runnumber_3p0.dat");
    for(int i = 0; i < runnumber_flag; i++){
        f_rn>>numbers[i];
    }
  f_rn.close();



  //--------------------------------------------------------------------------------- 
  histogram_output = new TFile(OutputFileName,"RECREATE") ;  

//define the profile here
 runidvsrefmult = new TProfile("runidvsrefmult","", 3978, 22121033, 22125011);

  
  return kStOK ;
}



Bool_t MyAnalysisMaker::IsBadEvent(StPicoEvent *mPicoEvent)
{
  if(!mPicoEvent)
    return kTRUE;

  double vx = mPicoEvent->primaryVertex().X();
  double vy = mPicoEvent->primaryVertex().Y();
  double vz = mPicoEvent->primaryVertex().Z();
  double vzVPD  = mPicoEvent->vzVpd();
  

  if( (vx < 1.e-5 && vx > -1.e-5) &&
      (vy < 1.e-5 && vy > -1.e-5) &&
      (vz < 1.e-5 && vz > -1.e-5)  )
    return kTRUE;
 
 
   if(vz < 198 || vz > 202)
   return kTRUE;

   if(sqrt((vx+0.4)*(vx+0.4)+(vy+0.4)*(vy+0.4)) > 2.0)
    return kTRUE;
  return kFALSE;
}



Int_t MyAnalysisMaker::Make()
{
  if(!mPicoDstMaker) {
    LOG_WARN << " No PicoDstMaker! Skip! " << endm;
    return kStWarn;
  }

  mPicoDst = mPicoDstMaker->picoDst();
  if(!mPicoDst)
    {
      LOG_WARN << " No PicoDst! Skip! " << endm;
      return kStWarn;
    }

  mPicoEvent = (StPicoEvent*)mPicoDst->event();
  if(!mPicoEvent)
    {
      LOG_WARN << " No PicoEvent! Skip! " << endm;
      return kStWarn;
    }

  Int_t runid = mPicoEvent->runId();


  Vx     = mPicoEvent->primaryVertex().X();
  Vy     = mPicoEvent->primaryVertex().Y();
  Vz     = mPicoEvent->primaryVertex().Z();


 
  Float_t vrad = TMath::Sqrt(Vx*Vx + Vy*Vy);
  gRefMult = mPicoEvent->fxtMult();
 
  //Event Cuts
  if(IsBadEvent(mPicoEvent))
    return kStOK;  

 runidvsrefmult  -> Fill(runid, gRefMult);

 const Int_t nTracks = mPicoDst->numberOfTracks();


  for(Int_t i = 0; i < nTracks; i++) // track loop                         
    {

      StPicoTrack *track = (StPicoTrack*)mPicoDst->track(i);
    
      if (!track) continue;
      if(!track->isPrimary()) continue;
      trackId = track->id();
      

      TVector3 p = track->gMom();
      pp = p.Mag();
      eta=p.Eta();
      pt=p.Pt();
      q=track->charge();
      phi=p.Phi();
      dEdx = track->dEdx();
      nHits  =  track->nHitsFit();
      nHitsFit =  TMath::Abs(nHits)+1;
      Float_t FitRatio   =    (float) nHitsFit / (float) track->nHitsMax();
      nHitsdEdx = track->nHitsDedx(); 
      gdca = track->gDCA(Vx,Vy,Vz);

      //.............Track Cuts...................
      if(pt <  0.06 || pt > 2.0)                continue;
      if(TMath::Abs(gdca) >= 3.0)         continue; 
      if(TMath::Abs(eta) > 1.5)          continue;
      if(nHitsFit < 10)            continue;
      //.........................................
      

} //Track loop
  return         kStOK ;
   
} //Event loop
  


Int_t MyAnalysisMaker::Finish()
{
  cout<<"Finish writing histograms..."<<endl;
  histogram_output->Write();
  return kStOk ;

}


int MyAnalysisMaker::Centrality(int gRefMult )
{
  int centrality;
  int centFull[9]={16,29,48,73,106,149,206,284,338};   
  if      (gRefMult>=centFull[8]) centrality=8; //0-5%
  else if (gRefMult>=centFull[7]) centrality=7; //5-10%
  else if (gRefMult>=centFull[6]) centrality=6; //10-20%
  else if (gRefMult>=centFull[5]) centrality=5; //20-30%
  else if (gRefMult>=centFull[4]) centrality=4; //30-40%
  else if (gRefMult>=centFull[3]) centrality=3; //40-50%
  else if (gRefMult>=centFull[2]) centrality=2; //50-60%
  else if (gRefMult>=centFull[1]) centrality=1; //60-70%
  else if (gRefMult>=centFull[0]) centrality=0; //70-80%
  else centrality = 9;

  return centrality;
}


class Bichsel;
static Bichsel *m_Bichsel = 0;

double ZValue(double mom, double dedx_truncated, char *name, double mass)
{
  double dedx_expected;
  double momentum;
  double q = 1.;
  double z = -999.;
  
  momentum = mom; //passes from main program                                                                
  double dedx_trunc= dedx_truncated; //passed from main program                                             
  if(!m_Bichsel) m_Bichsel = Bichsel::Instance();
  if(strcmp(name, "He3")==0 || strcmp(name, "He4")==0){
    q = 2.;
    dedx_expected = q*q*1.e-6*m_Bichsel->GetI70M(log10(momentum*q/mass),2.322);
									  }
  else{
    q = 1.;
    dedx_expected = q*q*1.e-6*m_Bichsel->GetI70M(log10(momentum*q/mass),1.0);
    
  }
  
  z = log(dedx_trunc/dedx_expected);
  return z ;

}

