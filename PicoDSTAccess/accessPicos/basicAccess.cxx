// C++ headers
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

// ROOT headers
#include "TROOT.h"
#include "TObject.h"
#include "TChain.h"
#include "TH1.h"
#include "TF1.h"
#include "TSystem.h"
#include "TKey.h"

// PicoDst headers
#include "StRoot/StPicoEvent/StPicoDstReader.h"
#include "StRoot/StPicoEvent/StPicoDst.h"
#include "StRoot/StPicoEvent/StPicoEpdHit.h"
#include "StRoot/StPicoEvent/StPicoEvent.h"
#include "StRoot/StPicoEvent/StPicoTrack.h"
//#include "StRoot/StPicoEvent/StPicoBTofHit.h"
#include "StRoot/StPicoEvent/StPicoBTofPidTraits.h"

// EPD Util headers
#include "StRoot/StEpdUtil/StEpdEpFinder.h"
#include "StRoot/StEpdUtil/StEpdGeom.h"





//void basicAccess(TString inFile, TString jobID)
int main(int argc, char *argv[])
{
  std::cout << "Initializing..." << std::endl;

  TString inFile = argv[1];
  TString jobID  = argv[2];

  TString FailString = "/star/data01/pwg/mcgordon/PicoDSTs/" + jobID + ".fail";

  if (gSystem->AccessPathName(inFile)) { ofstream FailFile; std::cout << "Error reading input file!" << std::endl;  FailFile.open (FailString); FailFile.close(); return 1;}

  //=========================================================
  //          Set up various files
  //=========================================================
    
  //=== INITIALIZE PICOREADER
  StPicoDstReader* picoReader = new StPicoDstReader(inFile);
  picoReader->Init();
  picoReader->SetStatus("*",0);
  picoReader->SetStatus("Event",1);
  picoReader->SetStatus("Track",1);
  picoReader->SetStatus("EpdHit",1);
  picoReader->SetStatus("BTofHit",1);
  picoReader->SetStatus("BTofPidTraits",1);
  if (!picoReader->chain()) { std::cout << "No chain found." << std::endl; return 1; }
  
  //Long64_t eventsInTree = picoReader->tree()->GetEntries();
  Long64_t events2read  = picoReader->chain()->GetEntries();
    
  std::cout << "Number of events to read: " << events2read << std::endl;

  TClonesArray *epdHits = new TClonesArray("StPicoEpdHit");
  unsigned int found;

  TChain *picoChain = picoReader->chain();
  picoChain->SetBranchStatus("EpdHit*",1,&found);   // note you need the asterisk                                                                                
  std::cout << "EpdHit Branch returned found = " << found << std::endl;
  picoChain->SetBranchAddress("EpdHit",&epdHits);


  // MAIN OUTPUT FILE
  TString outFile = "/star/data01/pwg/mcgordon/PicoDSTs/"+jobID+".picoDst.result.root";
  TFile *outputFile = new TFile(outFile,"RECREATE");
  outputFile->cd();
  //=========================================================
  //          END file setup
  //=========================================================



  // HISTOGRAMS

  TH1F *EventCounter = new TH1F("EventCounter", "Event Counter; Counter; Counts", 3, 0, 3); 
    
  TH2D *dEdxVsP = new TH2D("dEdxVsP", "dEdx Vs p; p (Gev); dEdx (Gev/fm)", 1000, 0, 2, 1000, 0, 10);
    

  std::cout << "Setup complete, beginning analysis..." << std::endl;

  StEpdGeom *epdGeom = new StEpdGeom();

  // EVENT LOOP
  for (Long64_t ievent = 0; ievent < events2read; ievent++)
    {
      Bool_t readEvent = picoReader->readPicoEvent(ievent);
      if( !readEvent ) { std::cout << "Event could not be read; aborting analysis." << std::endl; break; }
 
      StPicoDst *dst = picoReader->picoDst();
      StPicoEvent *event = dst->event();
      if( !event ) { std::cout << "No event found; aborting analysis." << std::endl; break; }

      TVector3 pVtx = event->primaryVertex();

      Double_t d_xvtx = pVtx.x();
      Double_t d_yvtx = pVtx.y();
      Double_t d_zvtx = pVtx.z();

      ////
      // Event level code here
      ////
      EventCounter->Fill(1);
          
      Int_t nTracks = dst->numberOfTracks();

      // TRACK LOOP OVER PRIMARY TRACKS
      for(Int_t iTrk = 0; iTrk < nTracks; iTrk++)
	{
	  StPicoTrack *picoTrack = dst->track(iTrk);            
	  if(picoTrack == NULL) continue;
	  if(!picoTrack->isPrimary()) continue;  // Require primary tracks


	  TVector3 mom_vec  = picoTrack->pMom();
	  Double_t d_dEdx   = picoTrack->dEdx();
	  Double_t d_charge = picoTrack->charge();
	  Double_t d_mom    = picoTrack->pPtot();
	  Double_t d_pT     = picoTrack->pPt();
	  Double_t d_px     = picoTrack->pMom().x();
	  Double_t d_py     = picoTrack->pMom().y();
	  Double_t d_pz     = picoTrack->pMom().z();
	  Double_t d_phi    = mom_vec.Phi();
	  Double_t d_eta    = mom_vec.Eta();
	  Double_t d_TPCnSigmaPion   = picoTrack->nSigmaPion();
	  Double_t d_TPCnSigmaKaon   = picoTrack->nSigmaKaon();
	  Double_t d_TPCnSigmaProton = picoTrack->nSigmaProton();

	  //=========================================================
	  //          TOF Beta Cuts
	  //=========================================================
	  StPicoBTofPidTraits *trait;
	  Double_t d_tofBeta;
	  Double_t d_m2;
	  Bool_t tofTrack = picoTrack->isTofTrack();

	  if (tofTrack)
	    {
	      trait = dst->btofPidTraits(picoTrack->bTofPidTraitsIndex());
	      d_tofBeta = trait->btofBeta();
	      d_m2 = d_mom*d_mom*( (1 / (d_tofBeta*d_tofBeta)) - 1);		  
	    }
	  //=========================================================
	  //          End TOF Beta Cuts
	  //=========================================================


	  ////
	  // TPC track level code here
	  dEdxVsP->Fill(d_mom, d_dEdx);
	  ////

	}//End TPC track loop

      //=========================================================
      //                EPD STUFF
      //=========================================================
      StPicoEpdHit *epdHit;
      int tileID;
      TVector3 tileVector;     // Vector from vertex to center of tile that was hit
      int tileSector;
      int tileRow;
      double tileWeight;
      double tileEta;
      double tilePhi;

      for (int iEpdHit = 0; iEpdHit < epdHits->GetEntries(); iEpdHit++)
	{
	  epdHit = (StPicoEpdHit*)(epdHits->At(iEpdHit));

	  tileID = epdHit->id();
	  tileVector = epdGeom->TileCenter(tileID) - pVtx;
	  tileSector = epdHit->position();
	  tileRow = epdHit->row();
	  tileEta = tileVector.Eta();
	  tilePhi = tileVector.Phi();
	  //tileWeight = (epdHit->nMIP() > configs.epd_threshold) ? ( (epdHit->nMIP() > configs.epd_max_weight)?configs.epd_max_weight:epdHit->nMIP() ) : 0;







	}// End EPD hit loop
      //=========================================================
      //            END EPD STUFF
      //=========================================================
    }// END EVENT LOOP
    
  outputFile->cd();
    
  EventCounter->Write();
  dEdxVsP->Write();
  //outputFile->Write();

  delete EventCounter;
  delete dEdxVsP;

  gROOT->GetListOfFiles()->Remove(outputFile);
  outputFile->Close();

  picoReader->Finish();
  delete picoReader;

  std::cout << "Done!" << std::endl;
}//End FlowAnalyzer()
