// This is needed for calling standalone classes (not needed on RACF)
//#define _VANILLA_ROOT_

// C++ headers
#include <iostream>
#include <stdio.h>

// ROOT headers
#include "TROOT.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TSystem.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TRandom.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TProfile3D.h"

// PicoDst headers
#include "StRoot/StPicoEvent/StPicoDstReader.h"
#include "StRoot/StPicoEvent/StPicoDst.h"
#include "StRoot/StPicoEvent/StPicoEvent.h"
#include "StRoot/StPicoEvent/StPicoTrack.h"

// Load libraries (for ROOT_VERSTION_CODE >= 393215)
#if ROOT_VERSION_CODE >= ROOT_VERSION(6,0,0)
R__LOAD_LIBRARY(libStPicoDst)
#endif

//const TString sourceTest = "root://xrdstar.rcf.bnl.gov:1095//home/starlib/home/starreco/reco/production_4p59GeV_fixedTarget_2019/ReversedFullField/P21id/2019/179/20179040/st_physics_adc_20179040_raw_2000002.picoDst.root";
//const TString sourceTest = "root://xrdstar.rcf.bnl.gov:1095//home/starlib/home/starreco/reco/production_7.3GeV_fixedTarget_2019/ReversedFullField/P21id/2019/107/20107029/st_physics_20107029_raw_2000001.picoDst.root";


const TString sourceTest = "/star/u/adams92/LambdaPolarizationAnalyses/3GeV/picoDsts/st_physics_19151039_raw_1000002.picoDst.root";

//const TString source3p2 = "3p2GeVFXT.files.list";
const TString source3p7 = "3p7GeVFXT.list";

const Int_t numModes = 5;

TString weightFileNames[numModes] = {"3p2GeVFXT.weight.root", "3p5GeVFXT.weight.root", "3p9GeVFXT.weight.root", "3p9GeVFXT2.weight.root", "4p5GeVFXT.weight.root"};

//////////////////////////////// Main Function /////////////////////////////////
void CentralityAnalyzer(const Char_t *inFile = sourceTest
					, TString outfilename = "picos", Int_t mode = 4
                    )
{
	
	gDirectory->pwd();
	
	//TString filename = inFile;
	
	//filename.Remove(filename.Last(' '), filename.Length() - filename.Last(' '));
	
	//cout << filename;
	

	// (0) ================== Read input files and set status =====================
	StPicoDstReader* picoReader = new StPicoDstReader(inFile);
	picoReader->Init();
	std::cout << "Explicit read status for some branches" << std::endl;
	picoReader->SetStatus("*",0);
	picoReader->SetStatus("Event",1);
	picoReader->SetStatus("Track",1);
	picoReader->SetStatus("BTofHit",1);
	picoReader->SetStatus("BTofPidTraits",1);
	picoReader->SetStatus("EpdHit",1);
	
	if( !picoReader->chain() ) {
		std::cout << "No chain has been found." << std::endl;
		return;
	}
  
    TFile *out_histos = TFile::Open(outfilename+".out.root", "RECREATE");
  
	TH2D * TOFMult_FXTMultHist = new TH2D("TOFMult_FXTMult","TOFMult v.s. FXTMult",700,-0.5,699.5,700,-0.5,699.5);
	TOFMult_FXTMultHist->GetXaxis()->SetTitle("TOFMult");
	TOFMult_FXTMultHist->GetYaxis()->SetTitle("FXTMult");
	
	TH1F* FxtMultHist = new TH1F("FxtMultHist", "FXTMult", 700,-0.5,699.5);
	FxtMultHist->GetXaxis()->SetTitle("FXTMult");
	FxtMultHist->GetYaxis()->SetTitle("# Events");
	
	TH1F* FxtMultWeightedHist = new TH1F("FxtWeightedMultHist", "FXTMult", 700,-0.5,699.5);
	FxtMultWeightedHist->GetXaxis()->SetTitle("FXTMult");
	FxtMultWeightedHist->GetYaxis()->SetTitle("# Events");
	
	TFile* mWeightFile = new TFile(weightFileNames[mode],"READ");
	TH1D * hWeightInput;
	if (mWeightFile->IsZombie()) {
		std::cout << "Error opening file with Weight information" << std::endl;
		std::cout << "No weighting in this execution." << std::endl;
		hWeightInput = 0;
	}
	else{
		hWeightInput = (TH1D*)mWeightFile->Get("hRatio");
	}

	
	


	Long64_t eventsInTree = picoReader->tree()->GetEntries();
	std::cout << "eventsInTree: "  << eventsInTree << std::endl;
	// ------------------ Get event numbers from TChain --------------------------------
	Long64_t events2read = picoReader->chain()->GetEntries();
	std::cout << "Number of events to read: " << events2read << std::endl;
	
	//3.2 Results from fitting
	
	int topbound;
	double a0, a1, a2, a3, a4;
	double b0, b1, b2, b3, b4;
	double c0, c1, c2, c3, c4;

	if (mode == 0){	
		topbound = 86;
		a0=-1.06842944939833; a1=3.32752611078231; a2=0.0120123921747088; a3=-0.00016076533134281; a4=-5.76797702596332e-07;
		b0=19.4817200401755; b1=5.42828827195504; b2=-0.00700262221266987; b3=-0.00024281819103346; b4=1.19721479492776e-07;
		c0=-13.589060580499; c1=1.51484218133914; c2=0.0281555036015621; c3=-0.000119469370842764; c4=-9.63874290972657e-07;
	}
	//3.5 Results from fitting
	else if (mode == 1){
		topbound = 100;
		a0=-0.364560805050766; a1=3.29330248293638; a2=0.031557482086097; a3=-0.000475777044156064; a4=9.95532413046347e-07;
		b0=23.2795468220185; b1=5.24722922421242; b2=0.040371364314833; b3=-0.00120587425061126; b4=5.79166009134734e-06;
		c0=-14.8185049128413; c1=1.58286469977909; c2=0.0268383378149974; c3=4.60499515023108e-05; c4=-2.41013015072081e-06;
	}
	//3.9 Results from fitting 2019
	else if (mode == 2){
		topbound = 95;
		a0=0.44476015723745; a1=3.04720994213842; a2=0.0290104648617336; a3=-0.0003518841134038; a4=5.21983361388553e-07;
		b0=22.0926171612827; b1=4.89211214161688; b2=0.0425731537540368; b3=-0.00111498150508863; b4=5.28536922228164e-06;
		c0=-13.0181769126488; c1=1.46926815930638; c2=0.0194076694792425; c3=0.000212033242346309; c4=-2.96061694656231e-06;
	}
	//3.9 Results from fitting 2020
	else if (mode == 3){
		topbound = 86;
		a0=-1.57335343527267; a1=3.57575744741028; a2=0.0229650415104031; a3=-0.00027341478742119; a4=-2.38019821513371e-07;
		b0=29.7355907032501; b1=4.42117489246211; b2=0.0913860908006649; b3=-0.0019773333892564; b4=9.4346821156139e-06;
		c0=-20.5338113617167; c1=2.55687601728073; c2=-0.0209409704149484; c3=0.000894258240078555; c4=-6.87890304862811e-06;
	}
	//4.5 Results from fitting
	else if (mode == 4){
		topbound = 95;	
		a0=-2.03057679028819; a1=3.65688726511454; a2=0.0208702196423615; a3=-0.000177099509282628; a4=-8.43358020944693e-07;
		b0=35.0161466438267; b1=3.58617385328552; b2=0.136818052986195; b3=-0.00257846572694019; b4=1.18869617325334e-05;
		c0=-24.8423974452115; c1=3.28857680182104; c2=-0.0572161664950845; c3=0.001491423531024; c4=-9.67779945054367e-06;
	}

	//5.2 Results from fitting
	/*
	topbound = 100;
	a0=-1.00655688528203; a1=3.67795546817801; a2=0.0264501415147349; a3=-0.000188439615181463; a4=-1.07988963244212e-06;
	b0=32.4648254893708; b1=4.28172174914505; b2=0.124178531275722; b3=-0.00231765594275868; b4=1.00509274960378e-05;
	c0=-22.1895433514021; c1=2.95050962492921; c2=-0.0433469379579907; c3=0.00134686525512654; c4=-9.03318884149758e-06;
	*/
	

    //6.2 Results from fitting
    /*
    int topbound = 100;
    double a0=-1.00655688528203; a1=3.67795546817801; a2=0.0264501415147349; a3=-0.000188439615181463; a4=-1.07988963244212e-06;
    double b0=32.4648254893708; b1=4.28172174914505; b2=0.124178531275722; b3=-0.00231765594275868; b4=1.00509274960378e-05;
    double c0=-22.1895433514021; c1=2.95050962492921; c2=-0.0433469379579907; c3=0.00134686525512654; c4=-9.03318884149758e-06;
    */

	//Bad runs for QA study 3.2 GeV
	//const int numBadRuns = 10;
	//int badruns[numBadRuns] = {20180005,20180006,20180019,20180025,20181016,20182034,20183001,20183013,20183014,20183019};
	
	//Bad runs for QA study	3.5 GeV 2020
	//const int numBadRuns = 8;
	//int badruns[numBadRuns] = {20355020, 20355021, 21044023, 21045024, 21045025, 21044027, 21044035, 21045004};

	//Bad runs for QA study	3.9 GeV 2019
	//const int numBadRuns = 6;
	//int badruns[numBadRuns] = {20107029, 20113042, 20113043, 20169033, 20169043, 20169051};
	
	//Bad runs for QA study	3.9 GeV 2020
	//const int numBadRuns = 4;
	//int badruns[numBadRuns] = {21035008, 21035011, 21036012, 21035014};

	//Bad runs for QA study	4.5 GeV 2020
	const int numBadRuns = 1;
	int badruns[numBadRuns] = {21032001};

	//Bad runs for QA study	5.2 GeV 2020
	//const int numBadRuns = 2;
	//int badruns[numBadRuns] = {21034002, 21034007};
	
	//Bad runs for QA study	6.2 GeV 2020
	//const int numBadRuns = 2;
	//int badruns[numBadRuns] = {21032046, 21033009};

	//Bad runs for QA study	7.2 GeV 2020
	//const int numBadRuns = 1;
	//int badruns[numBadRuns] = {0}; //No bad runs
	
	//Bad runs for QA study	7.7 GeV 2020
	//const int numBadRuns = 3;
	//int badruns[numBadRuns] = {21029002, 21029013, 21029027};

	
	
	double luminosityCorrection = 0;


	// (3) =========================== Event loop ====================================
	for(long iEvent=0; iEvent<events2read; iEvent++){
		// ---------------------- Event reading quality assurance ----------------------
		if((iEvent+1)%100 == 0) std::cout << "Working on event #[" << (iEvent+1)
		<< "/" << events2read << "]" << std::endl;
		Bool_t readEvent = picoReader->ReadPicoEvent(iEvent);
		if( !readEvent ) {
			std::cout << "Something went wrong, Master! Nothing to analyze..."
			<< std::endl;
			break;
		}
		StPicoDst     *dst = picoReader->picoDst();
		StPicoEvent *event = dst->event();
		if( !event ) {
			std::cout << "Something went wrong, Master! Event is hiding from me..."
			<< std::endl;
			break;
		}

		// (4) =================== Get event parameters ================================
		Int_t runId       = event->runId();
		Int_t nTracks     = dst->numberOfTracks();\
		
		
		bool isBadRun = false;
		
		for (int run = 0; run < numBadRuns; run++){
			if (runId == badruns[run]){
				isBadRun = true;
				break;
			}
		
		}
		
		if (isBadRun){continue;}
		
		


		const Float_t   B = event->bField(); // Magnetic field
		double d_MagField = event->bField();
		Double_t Day      = (Double_t)runId - 19151028.0; // a day bin

		Double_t primaryVertex_X    = (Double_t)event->primaryVertex().X();
		Double_t primaryVertex_Y    = (Double_t)event->primaryVertex().Y();
		Double_t primaryVertex_Z    = (Double_t)event->primaryVertex().Z();
		Double_t primaryVertex_perp = (Double_t)event->primaryVertex().Perp();

		// ---------------------- trigger selection ---------------------------------
		std::vector <unsigned int> triggerIDs;
		triggerIDs.clear();
		triggerIDs      = event->triggerIds();
		bool b_bad_trig = true;
			
		for(unsigned int i=0; i < triggerIDs.size(); i++)
		  {
			if(mode == 0 && triggerIDs[i] == 680001) b_bad_trig = false; // epde-or-bbce-or-vpde-tof1 3.2GeV
			if(mode == 1 && triggerIDs[i] == 720000) b_bad_trig = false; // epde-or-bbce-or-vpde-tof1 3.5GeV 2020
			if(mode == 2 && triggerIDs[i] == 1) b_bad_trig = false; // epde-or-bbce-tof1 3.9GeV 2019
			if(mode == 3 && triggerIDs[i] == 730000) b_bad_trig = false; // epde-or-bbce-or-vpde-tof1 3.9GeV 2020
			if(mode == 4 && triggerIDs[i] == 740010) b_bad_trig = false; // epde-or-bbce-or-vpde-tof1 4.5GeV 2020
			if(mode == 5 && triggerIDs[i] == 750000) b_bad_trig = false; // epde-or-bbce-or-vpde-tof1 5.2GeV 2020
			if(mode == 6 && triggerIDs[i] == 760000) b_bad_trig = false; // epde-or-bbce-or-vpde-tof1 6.2GeV 2020
		  }
		  

		// --------------------------- Vertex cut -----------------------------------
		double      d_zvtx  = -9999.0;
		double      d_xvtx  = -9999.0;
		double      d_yvtx  = -9999.0;
		double  d_vtx_perp  = -9999.0;
		TVector3       pVtx = event->primaryVertex();
		d_zvtx     = pVtx.z();
		d_xvtx     = pVtx.x();
		d_yvtx     = pVtx.y();
		d_vtx_perp = pVtx.Perp();
		bool b_bad_zvtx   =  ((d_zvtx < 198.0) || (d_zvtx > 202.0));
		bool b_bad_xvtx   =  ((d_xvtx < -1.0) || (d_xvtx > 1.0));
		bool b_bad_yvtx   =  ((d_yvtx < -3.0) || (d_yvtx > -0.5));
		bool b_bad_rvtx   =   sqrt(pow(d_xvtx,2)+pow(d_yvtx+2,2))> 2.0;
		bool b_bad_evt  = b_bad_zvtx || b_bad_trig /*|| b_bad_xvtx || b_bad_yvtx */|| b_bad_rvtx;
		if(b_bad_evt) continue;
		
		//cout << d_xvtx << " " << d_yvtx << " " << d_zvtx << endl;


		Int_t  refMult = event->refMult(); // refMult
		Int_t grefMult = event->grefMult();
		Int_t  tofMult =(Int_t)event->nBTOFMatch();
		// (5) =============== Track loop to determine good tracks =================
		int nGoodTracks = 0;


		
		for(Int_t iTrk=0; iTrk<nTracks; iTrk++){
		  StPicoTrack *picoTrack = dst->track(iTrk);
		  if(!picoTrack) continue;
		  if(!picoTrack->isPrimary()) continue;
		  
		  nGoodTracks++;
		} // Track loop to determine good tracks
		
		double refmultcutmin = ( c0 + c1*(tofMult) + c2*pow(tofMult,2) +
							   c3*pow(tofMult,3) + c4*pow(tofMult,4) );		
		double refmultcutmax;
		
		
		if (tofMult <= topbound){
			refmultcutmax = ( b0 + b1*(tofMult) + b2*pow(tofMult,2) +
							   b3*pow(tofMult,3) + b4*pow(tofMult,4) );
		}
		else {
			refmultcutmax = ( b0 + b1*(topbound) + b2*pow(topbound,2) +
							   b3*pow(topbound,3) + b4*pow(topbound,4) );
		}

		if ( nGoodTracks>refmultcutmax || nGoodTracks<refmultcutmin ){continue;} //Not within bounds


		
		TOFMult_FXTMultHist->Fill(tofMult,nGoodTracks);
		
		FxtMultHist->Fill(nGoodTracks);

		if (hWeightInput != 0){
			double weight = hWeightInput->GetBinContent(nGoodTracks + 1); //Add 1 to account for index shit
			
			FxtMultWeightedHist->Fill(nGoodTracks, weight);
		}


	}  // Event Loop

	out_histos->cd();
	out_histos->Write();
}

