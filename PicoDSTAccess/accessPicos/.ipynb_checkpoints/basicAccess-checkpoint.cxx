// C++ headers
#include <iostream>
#include <vector>

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
#include "StRoot/StPicoEvent/StPicoBTofPidTraits.h"

// EPD Util headers
#include "StRoot/StEpdUtil/StEpdEpFinder.h"
#include "StRoot/StEpdUtil/StEpdGeom.h"



//void basicAccess(TString inFile, TString jobID)
int main(int argc, char *argv[])
{
  std::cout << "Initializing..." << std::endl;

  TString inFile = "root://xrdstar.rcf.bnl.gov:1095//home/starlib/home/starreco/reco/production_3p85GeV_fixedTarget_2018/ReversedFullField/P19ie.SL20d/2018/153/19153016/st_physics_19153016_raw_5500011.picoDst.root";//argv[1];
  TString jobID = "TEST";//argv[2];

  if (gSystem->AccessPathName(inFile)) { std::cout << "Error reading input file!" << std::endl; return 1;}

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

  if(events2read == 0)
  {
      std::cout << "File Contains Zero Events.  Exiting program." << std::endl;
      
      exit(0);
  }
    
  std::cout << "Number of events to read: " << events2read << std::endl;

  TClonesArray *epdHits = new TClonesArray("StPicoEpdHit");
  unsigned int found;

  TChain *picoChain = picoReader->chain();
  picoChain->SetBranchStatus("EpdHit*",1,&found);   // note you need the asterisk                                                                                
  std::cout << "EpdHit Branch returned found = " << found << std::endl;
  picoChain->SetBranchAddress("EpdHit",&epdHits);


  // MAIN OUTPUT FILE
  TString outFile = "/star/u/mcgordon/ParticleIdentification/Histograms/Histogram" + jobID + ".root";
  TFile *outputFile = new TFile(outFile,"RECREATE");
  outputFile->cd();
  //=========================================================
  //          END file setup
  //=========================================================




  // HISTOGRAMS
  // TH1D *h_pT = new TH1D("h_pT", "p_{T};p_{T} (GeV);", 100, 0, 5);
  TH1F* Histo0 = new TH1F("EventCounter", "Event Multiplicities; Number of Events; Event Multiplicity", 3, 0, 2);
  TH1F* Histo1 = new TH1F("PtProton", "Pt for Protons; Pt (GeV); Events", 500, 0, 2);
  TH1F* Histo2 = new TH1F("PtKaonPlus", "Pt for Kaons+; Pt (GeV); Events", 500, 0, 2);
  TH1F* Histo3 = new TH1F("PtKaonMinus", "Pt for Kaons-; Pt (GeV); Events", 500, 0, 2);
  TH1F* Histo4 = new TH1F("PtPionPlus", "Pt for Pions+; Pt (GeV); Events", 500, 0, 2);
  TH1F* Histo5 = new TH1F("PtPionMinus", "Pt for Pions-; Pt (GeV); Events", 500, 0, 2);
  TH1F* Histo6 = new TH1F("YProton", "Y for Protons; Y - Y_Mid; Events", 500, -1, 1);
  TH1F* Histo7 = new TH1F("YKaonPlus", "Y for Kaons+; Y - Y_Mid; Events", 500, -1, 1);
  TH1F* Histo8 = new TH1F("YKaonMinus", "Y for Kaons-; Y - Y_Mid; Events", 500, -1, 1);
  TH1F* Histo9 = new TH1F("YPionPlus", "Y for Pions+; Y - Y_Mid; Events", 500, -1, 1);
  TH1F* Histo10 = new TH1F("YPionMinus", "Y for Pions-; Y - Y_Mid; Events", 500, -1, 1);
  TH2F* Histo11 = new TH2F("PtVsYProton", "Pt vs Y for Protons; Y - Y_Mid; Pt (GeV)", 500, -1, 1, 1000, 0, 2.5);
  TH2F* Histo12 = new TH2F("PtVsYKaonPlus", "Pt vs Y for Kaons+; Y - Y_Mid; Pt (GeV)", 500, -1, 1, 1000, 0, 2.5);
  TH2F* Histo13 = new TH2F("PtVsYKaonMinus", "Pt vs Y for Kaons-; Y - Y_Mid; Pt (GeV)", 500, -1, 1, 1000, 0, 2.5);
  TH2F* Histo14 = new TH2F("PtVsYPionPlus", "Pt vs Y for Pions+; Y - Y_Mid; Pt (GeV)", 500, -1, 1, 1000, 0, 2.5);
  TH2F* Histo15 = new TH2F("PtVsYPionMinus", "Pt vs Y for Pion-; Y - Y_Mid; Pt (GeV)", 500, -1, 1, 1000, 0, 2.5);
  TH2F* Histo16 = new TH2F("DataMSquaredVsQP", "m^2 vs q|p| (Data); q|p| (GeV); m^2 (GeV^2)", 1000, -4, 4, 1000, -0.1, 1.5);
  TH2F* Histo17 = new TH2F("DatadEdxVsP", "dE/dx vs p (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10);
  TH2F* Histo18 = new TH2F("DatadEdxVsPProton", "dE/dx vs p for Protons (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10);
  TH2F* Histo19 = new TH2F("DatadEdxVsPKaon", "dE/dx vs p for Kaons (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10);
  TH2F* Histo20 = new TH2F("DatadEdxVsPPion", "dE/dx vs p for Pions (Data); p (GeV); dE/dx (Gev/fm)", 1000, 0, 2, 1000, 0, 10);



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
      Histo0->Fill(1);

      Int_t nTracks = dst->numberOfTracks();

      // TRACK LOOP OVER PRIMARY TRACKS
      for(Int_t iTrk = 0; iTrk < nTracks; iTrk++)
	{
	  StPicoTrack *picoTrack = dst->track(iTrk);
	  if(picoTrack == NULL) continue;
	  if(!picoTrack->isPrimary()) continue;  // Require primary tracks
          
      StPicoBTofPidTraits* trait;
      Bool_t tofTrack = picoTrack->isTofTrack();


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

      const Double_t yCMShift = -1.045;
      const Double_t ProtonMass = 0.938;
      const Double_t KaonMass = 0.494;
      const Double_t PionMass = 0.140;
          
      Double_t qp = d_charge * d_mom;
	  ////
	  // TPC track level code here
	  //h_pT->Fill(d_pT);
	  ////

      if(tofTrack)
      { 
          trait = dst->btofPidTraits(picoTrack->bTofPidTraitsIndex());

          Double_t d_tofBeta = trait->btofBeta();

          Double_t msquared = pow(d_mom,2) * ((1/pow(d_tofBeta,2)) - 1);

          Histo16->Fill(qp, msquared);
          Histo17->Fill(d_mom, d_dEdx);

          if((abs(d_TPCnSigmaProton) < 3) and (msquared > 0.45) and (msquared < 2.0))
          {
              Double_t mass = ProtonMass;
              
              Double_t energy = sqrt(pow(d_px,2) + pow(d_py,2) + pow(d_pz,2) + pow(mass,2));
              
              Double_t y = atanh(d_pz/energy);
              
              Histo1->Fill(d_pT);
              Histo6->Fill(y - yCMShift);
              Histo11->Fill(y - yCMShift, d_pT);
              
              Histo18->Fill(d_mom, d_dEdx);
          }

          else if((abs(d_TPCnSigmaKaon) < 3) and (msquared > 0.15) and (msquared < 0.45))
          {
              Double_t mass = KaonMass;
              
              Double_t energy = sqrt(pow(d_px,2) + pow(d_py,2) + pow(d_pz,2) + pow(mass,2));
              
              Double_t y = atanh(d_pz/energy);
                  
              Histo19->Fill(d_mom, d_dEdx);
              
              if(d_charge > 0)
              {
                 Histo2->Fill(d_pT);
                 Histo7->Fill(y - yCMShift);
                 Histo12->Fill(y - yCMShift, d_pT);
              }

              else if(d_charge < 0)
              {
                 Histo3->Fill(d_pT);
                 Histo8->Fill(y - yCMShift);
                 Histo13->Fill(y - yCMShift, d_pT);
              }
          }

          else if((abs(d_TPCnSigmaPion) < 3) and (msquared < 0.15))
          {
              Double_t mass = PionMass;
              
              Double_t energy = sqrt(pow(d_px,2) + pow(d_py,2) + pow(d_pz,2) + pow(mass,2));
              
              Double_t y = atanh(d_pz/energy);
              
              Histo20->Fill(d_mom, d_dEdx);
              
              if(d_charge > 0)
              {
                 Histo4->Fill(d_pT);
                 Histo9->Fill(y - yCMShift);
                 Histo14->Fill(y - yCMShift, d_pT);
              }

              else if(d_charge < 0)
              {
                 Histo5->Fill(d_pT);
                 Histo10->Fill(y - yCMShift);
                 Histo15->Fill(y - yCMShift, d_pT);
              }
          }
      }
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
  Histo0->Write();
  Histo1->Write();
  Histo2->Write();
  Histo3->Write();
  Histo4->Write();
  Histo5->Write();
  Histo6->Write();
  Histo7->Write();
  Histo8->Write();
  Histo9->Write();
  Histo10->Write();
  Histo11->Write();
  Histo12->Write();
  Histo13->Write();
  Histo14->Write();
  Histo15->Write();
  Histo16->Write();
  Histo17->Write();
  Histo18->Write();
  Histo19->Write();
  Histo20->Write();
  //outputFile->Write();

  gROOT->GetListOfFiles()->Remove(outputFile);
  outputFile->Close();

  picoReader->Finish();
  delete picoReader;

  std::cout << "Done!" << std::endl;
}//End FlowAnalyzer()
