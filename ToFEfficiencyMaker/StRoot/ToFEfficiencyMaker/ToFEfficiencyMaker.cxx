//Author: Michael Gordon
//Date: 1-7-25


#include <iostream>
#include <string>
#include <vector>

#include "TROOT.h"
#include "TObject.h"
#include "TChain.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TString.h"
#include "TKey.h"
#include "TF1.h"
#include "TMath.h"

#include "ToFEfficiencyMaker.h"
#include "FlowFunctions.h"
#include "DeuteronsAndTritons.h"
#include "TileVector.h"

#include "StBichsel/Bichsel.h"

#include "StPicoDstMaker/StPicoDstMaker.h"
#include "StPicoEvent/StPicoEvent.h"
#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoTrack.h"
#include "StPicoEvent/StPicoETofHit.h"
#include "StPicoEvent/StPicoBTofPidTraits.h"
#include "StPicoEvent/StPicoETofPidTraits.h"
#include "StPicoEvent/StPicoEpdHit.h"
#include "StEpdUtil/StEpdGeom.h"
#include "StEpdUtil/StEpdEpFinder.h"

#include <Math/Vector4D.h>

ClassImp(ToFEfficiencyMaker)

    
ToFEfficiencyMaker::ToFEfficiencyMaker(StPicoDstMaker *picoMaker, Char_t *JobID):StMaker()
{
    mPicoDstMaker = picoMaker;
    mPicoDst = 0;
    
    ID = std::string(JobID);
}



// Bichsel function
Double_t BichselZ(Double_t *p, Double_t *parameters) 
{
    Double_t POverM = p[0] / parameters[0];

    return TMath::Exp(Bichsel::Instance()->GetMostProbableZ(TMath::Log10(POverM),parameters[1]));
}



void ToFEfficiencyMaker::Clear(Option_t *opt)
{
    StMaker::Clear();
}



Int_t ToFEfficiencyMaker::Finish()
{
    //Outputting the Histograms
EventCheck->SetDirectory(0);
    ProtonTPCDetected->SetDirectory(0);
    ProtonTPCDetectedRapidity->SetDirectory(0);        
    KaonPlusTPCDetected->SetDirectory(0);
    KaonPlusTPCDetectedRapidity->SetDirectory(0);
    KaonMinusTPCDetected->SetDirectory(0);
    KaonMinusTPCDetectedRapidity->SetDirectory(0);
    PionPlusTPCDetected->SetDirectory(0);
    PionPlusTPCDetectedRapidity->SetDirectory(0);
    PionMinusTPCDetected->SetDirectory(0);
    PionMinusTPCDetectedRapidity->SetDirectory(0);
    DeuteronTPCDetected->SetDirectory(0);
    TritonTPCDetected->SetDirectory(0);
    ProtonToFDetected->SetDirectory(0);
    ProtonToFDetectedRapidity->SetDirectory(0);
    ProtonToFDetectedRapidityMSquaredCuts->SetDirectory(0);
    ProtonEToFDetected->SetDirectory(0);
    ProtonEToFDetectedRapidity->SetDirectory(0);
    KaonPlusToFDetected->SetDirectory(0);
    KaonPlusToFDetectedRapidity->SetDirectory(0);
    KaonPlusToFDetectedRapidityMSquaredCuts->SetDirectory(0);
    KaonPlusEToFDetected->SetDirectory(0);
    KaonPlusEToFDetectedRapidity->SetDirectory(0);
    KaonMinusToFDetected->SetDirectory(0);
    KaonMinusToFDetectedRapidity->SetDirectory(0);
    KaonMinusToFDetectedRapidityMSquaredCuts->SetDirectory(0);
    KaonMinusEToFDetected->SetDirectory(0);
    KaonMinusEToFDetectedRapidity->SetDirectory(0);
    PionPlusToFDetected->SetDirectory(0);
    PionPlusToFDetectedRapidity->SetDirectory(0);
    PionPlusToFDetectedRapidityMSquaredCuts->SetDirectory(0);
    PionPlusEToFDetected->SetDirectory(0);
    PionPlusEToFDetectedRapidity->SetDirectory(0);
    PionMinusToFDetected->SetDirectory(0);
    PionMinusToFDetectedRapidity->SetDirectory(0);
    PionMinusToFDetectedRapidityMSquaredCuts->SetDirectory(0);
    PionMinusEToFDetected->SetDirectory(0);
    PionMinusEToFDetectedRapidity->SetDirectory(0);
    DeuteronToFDetected->SetDirectory(0);
    DeuteronEToFDetected->SetDirectory(0);
    TritonToFDetected->SetDirectory(0);
    TritonEToFDetected->SetDirectory(0);
 

 
    std::string ToFEfficiencyFileString = "/star/data01/pwg/mcgordon/VnFromEPD/V" + std::to_string(nV) + "Histograms/ToFEfficiency" + ID +".root";
    const char *ToFEfficiencyFileChar = &ToFEfficiencyFileString[0];

    TFile *ToFEfficiencyRootFile = TFile::Open(ToFEfficiencyFileChar, "RECREATE");
    ToFEfficiencyRootFile->cd();


    ProtonTPCDetected->Write();
    ProtonTPCDetectedRapidity->Write();
    KaonPlusTPCDetected->Write();
    KaonPlusTPCDetectedRapidity->Write();
    KaonMinusTPCDetected->Write();
    KaonMinusTPCDetectedRapidity->Write();
    PionPlusTPCDetected->Write();
    PionPlusTPCDetectedRapidity->Write();
    PionMinusTPCDetected->Write();
    PionMinusTPCDetectedRapidity->Write();
    DeuteronTPCDetected->Write();
    TritonTPCDetected->Write();
    ProtonToFDetected->Write();
    ProtonToFDetectedRapidity->Write();
    ProtonToFDetectedRapidityMSquaredCuts->Write();
    ProtonEToFDetected->Write();
    ProtonEToFDetectedRapidity->Write();
    KaonPlusToFDetected->Write();
    KaonPlusToFDetectedRapidity->Write();
    KaonPlusToFDetectedRapidityMSquaredCuts->Write();
    KaonPlusEToFDetected->Write();
    KaonPlusEToFDetectedRapidity->Write();
    KaonMinusToFDetected->Write();
    KaonMinusToFDetectedRapidity->Write();
    KaonMinusToFDetectedRapidityMSquaredCuts->Write();
    KaonMinusEToFDetected->Write();
    KaonMinusEToFDetectedRapidity->Write();
    PionPlusToFDetected->Write();
    PionPlusToFDetectedRapidity->Write();
    PionPlusToFDetectedRapidityMSquaredCuts->Write();
    PionPlusEToFDetected->Write();
    PionPlusEToFDetectedRapidity->Write();
    PionMinusToFDetected->Write();
    PionMinusToFDetectedRapidity->Write();
    PionMinusToFDetectedRapidityMSquaredCuts->Write();
    PionMinusEToFDetected->Write();
    PionMinusEToFDetectedRapidity->Write();
    DeuteronToFDetected->Write();
    DeuteronEToFDetected->Write();
    TritonToFDetected->Write();
    TritonEToFDetected->Write();

    ToFEfficiencyRootFile->Close();
     


    
   
    delete EventCheck;
    delete ProtonTPCDetected;
    delete ProtonTPCDetectedRapidity;
    delete KaonPlusTPCDetected;
    delete KaonPlusTPCDetectedRapidity;
    delete KaonMinusTPCDetected;
    delete KaonMinusTPCDetectedRapidity;
    delete PionPlusTPCDetected;
    delete PionPlusTPCDetectedRapidity;
    delete PionMinusTPCDetected;
    delete PionMinusTPCDetectedRapidity;
    delete DeuteronTPCDetected;
    delete TritonTPCDetected;
    delete ProtonToFDetected;
    delete ProtonToFDetectedRapidity;
    delete ProtonToFDetectedRapidityMSquaredCuts;
    delete ProtonEToFDetected;
    delete ProtonEToFDetectedRapidity;
    delete KaonPlusToFDetected;
    delete KaonPlusToFDetectedRapidity;
    delete KaonPlusToFDetectedRapidityMSquaredCuts;
    delete KaonPlusEToFDetected;
    delete KaonPlusEToFDetectedRapidity;
    delete KaonMinusToFDetected;
    delete KaonMinusToFDetectedRapidity;
    delete KaonMinusToFDetectedRapidityMSquaredCuts;
    delete KaonMinusEToFDetected;
    delete KaonMinusEToFDetectedRapidity;
    delete PionPlusToFDetected;
    delete PionPlusToFDetectedRapidity;
    delete PionPlusToFDetectedRapidityMSquaredCuts;
    delete PionPlusEToFDetected;
    delete PionPlusEToFDetectedRapidity;
    delete PionMinusToFDetected;
    delete PionMinusToFDetectedRapidity;
    delete PionMinusToFDetectedRapidityMSquaredCuts;
    delete PionMinusEToFDetected;
    delete PionMinusEToFDetectedRapidity;
    delete DeuteronToFDetected;
    delete DeuteronEToFDetected;
    delete TritonToFDetected;
    delete TritonEToFDetected;
   

    
    return kStOK;
}



Int_t ToFEfficiencyMaker::Init()
{
    std::vector<int> RunIDs {0, 79020,79021,79022,78002,78003,78004,78005,78006,78007,78008,78009,78010,78011,78012,78013,77002,77003,77004,77005,77006,77007,77008,77012,77013,77014,76001,76002,76003,76004,76005,76006,76007,76008,76009,76011,76012,75001,75002,75003,75004,75005,75006,75007,75008,75010,75011,75013,75031,75032,74002,74003,74004,74005,74006,74007,74010,74011,74012,74013,74014,74018,74019,74046,74047,74048,74049,74050,74054,74055,74056,74057,74058,74059,74060,74061,74062,73001,73002,73003,73004,73005,73006,73009,73010,73011,73012,73013,73014,73015,73016,73017,73018,73019,73020,73023,73024,73025,73026,73027,73028,73029,73030,73031,73032,73033,73034,73035,72001,72002,72003,72004,72005,72006,72007,72008,72009,72010,72022,72024,72025,71021,71022,71023,71024,71025,71026,71027,71028,71029,71030,71031,71032,71033,70001,70002,70003,70004,70005,70006,70007,70008,70009,70014,70015,70016,70017,70018,70019,70020,70021,70022,69001,69002,69003,69004,69005,69006,69007,69008,69009,69010,69011,69018,69022,69023,68003,68004,68005,68006,68007,68008,68009,68010,68015,67001,67002,67003,67004,67005,67006,67007,67008,67009,67010,67011,67012,67016,67017,67021,67022,67023,67024,67025,67027,67028,67029,66001,66002,66003,66004,66005,66006,66009,66010,66013,66014,66015,66016,66017,66018,66019,66020,66023,66024,66026,66028,66029,66030,66031,66034,66035,66036,66037,66038,66039,65001,65002,65003,65004,65005,65006,65007,65008,65009,65010,65012,65013,65014,65015,65016,65017,65018,65019,65021,65024,65025,65026,65027,65028,65029,65031,65032,65033,65034,65035,64001,64002,64003,64004,64005,64006,64007,64008,64009,64010,64011,64012,64013,64014,64015,64016,64017,64018,64019,64022,64024,64025,64026,64027,64028,64029,64030,64031,64032,64033,63002,63003,63004,63005,63006,63007,63008,63009,63010,63011,63012,63013,63014,63015,63016,63017,63018,63019,63020,63026,63027,63028,63029,63030,63031,63032,63034,63035,63036,62001,62003,62006,62007,62008,62009,62015,62018,62019,62021,62022,62023,61001,61002,61003,61004,61005,61006,61009,61010,61012,61013,61014,61015,61016,61018,61019,61020,61023,61024,61025,61026,61027,61028,61029,61030,61031,61032,61033,60001,60002,60003,60004,60005,60006,60007,60008,60009,60010,60011,60012,60013,60014,60015,60016,60017,60018,60019,60020,60021,60022,60024,60025,60026,60027,60028,60029,60030,60031,60032,60046,60047,60048,60049,60050,60051,60052,60053,59001,59003,59008,59009,59010,59011,59012,59013,59015,59051,59052,59053,58032,58033,58036,25001,25002,25003,25004,25005,25006,25007,25008,25009,25010,25011,24002,24003,24004,24005,24006,24007,24008,24011,24012,24013,24014,24018,24027,24028,24031,23001,23002,23003,23004,23005,23006,23007,23008,23009,23010,23011,23012,23013,23014,23015,23016,23017,23018,23020,23021,23025,23026,23027,23028,23030,23031,23032,23034,23035,23037,23038,23040,23041,22001,22002,22003,22004,22005,22006,22007,22008,22009,22010,22011,22014,22016,22017,22018,22019,22020,22021,22024,22025,22026,22027,22028,22029,22031,22032,22034,22035,21033,21036,21037,21038,21039,21040,21041,21044,21045,21046,21048,21049,21050,21052,21053};



    
    EventCheck = new TH1D("EventCheck","Event number after each cut;;Events", 9, 0, 9);
    EventCheck->GetXaxis()->SetBinLabel(1,"No Cuts");
    EventCheck->GetXaxis()->SetBinLabel(2,"Bad Run Cut");
    EventCheck->GetXaxis()->SetBinLabel(3,"Minbias Cut");
    EventCheck->GetXaxis()->SetBinLabel(4,"Valid # of Primary Tracks Cut");
    EventCheck->GetXaxis()->SetBinLabel(5,"V_{Z} Cut");
    EventCheck->GetXaxis()->SetBinLabel(6,"V_{r} Cut");
    EventCheck->GetXaxis()->SetBinLabel(7,"Min # of Events/Tracks Cut");
    EventCheck->GetXaxis()->SetBinLabel(8,"No QVec = 0 Cut");
    EventCheck->GetXaxis()->SetBinLabel(9,"Centrality Cut");
    


    ProtonTPCDetected = new TH2D("ProtonTPCDetected", "Number of Proton Tracks Detected By TPC; #eta; P_{T} (GeV)", 300, -3, 0, 600, 0, 6);
    ProtonTPCDetected->Sumw2();

    ProtonTPCDetectedRapidity = new TH2D("ProtonTPCDetectedRapidity", "Number of Proton Tracks Detected By TPC; y_{cm}; P_{T} (GeV)", 500, -2.5, 2.5, 600, 0, 6);
    ProtonTPCDetectedRapidity->Sumw2();

    KaonPlusTPCDetected = new TH2D("KaonPlusTPCDetected", "Number of K^{+} Tracks Detected By TPC; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    KaonPlusTPCDetected->Sumw2();

    KaonPlusTPCDetectedRapidity = new TH2D("KaonPlusTPCDetectedRapidity", "Number of K^{+} Tracks Detected By TPC; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonPlusTPCDetectedRapidity->Sumw2();
    
    KaonMinusTPCDetected = new TH2D("KaonMinusTPCDetected", "Number of K^{-} Tracks Detected By TPC; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    KaonMinusTPCDetected->Sumw2();

    KaonMinusTPCDetectedRapidity = new TH2D("KaonMinusTPCDetectedRapidity", "Number of K^{-} Tracks Detected By TPC; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonMinusTPCDetectedRapidity->Sumw2();
    
    PionPlusTPCDetected = new TH2D("PionPlusTPCDetected", "Number of #pi^{+} Tracks Detected By TPC; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    PionPlusTPCDetected->Sumw2();

    PionPlusTPCDetectedRapidity = new TH2D("PionPlusTPCDetectedRapidity", "Number of #pi^{+} Tracks Detected By TPC; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionPlusTPCDetectedRapidity->Sumw2();
    
    PionMinusTPCDetected = new TH2D("PionMinusTPCDetected", "Number of #pi^{-} Tracks Detected By TPC; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    PionMinusTPCDetected->Sumw2();

    PionMinusTPCDetectedRapidity = new TH2D("PionMinusTPCDetectedRapidity", "Number of #pi^{-} Tracks Detected By TPC; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionMinusTPCDetectedRapidity->Sumw2();

    DeuteronTPCDetected = new TH2D("DeuteronTPCDetected", "Number of Deuteron Tracks Detected By TPC; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    DeuteronTPCDetected->Sumw2();

    TritonTPCDetected = new TH2D("TritonTPCDetected", "Number of Triton Tracks Detected By TPC; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    TritonTPCDetected->Sumw2();

    ProtonToFDetected = new TH2D("ProtonToFDetected", "Number of Proton Tracks Detected By ToF; #eta; P_{T} (GeV)", 300, -3, 0, 600, 0, 6);
    ProtonToFDetected->Sumw2();

    ProtonToFDetectedRapidity = new TH2D("ProtonToFDetectedRapidity", "Number of Proton Tracks Detected By ToF; y_{cm}; P_{T} (GeV)", 500, -2.5, 2.5, 600, 0, 6);
    ProtonToFDetectedRapidity->Sumw2();

    ProtonToFDetectedRapidityMSquaredCuts = new TH2D("ProtonToFDetectedRapidityMSquaredCuts", "Number of Proton Tracks Detected By ToF with m^{2} Cuts; y_{cm}; P_{T} (GeV)", 500, -2.5, 2.5, 600, 0, 6);
    ProtonToFDetectedRapidityMSquaredCuts->Sumw2();

    ProtonEToFDetected = new TH2D("ProtonEToFDetected", "Number of Proton Tracks Detected By EToF; #eta; P_{T} (GeV)", 300, -3, 0, 600, 0, 6);
    ProtonEToFDetected->Sumw2();

    ProtonEToFDetectedRapidity = new TH2D("ProtonEToFDetectedRapidity", "Number of Proton Tracks Detected By EToF; y_{cm}; P_{T} (GeV)", 500, -2.5, 2.5, 600, 0, 6);
    ProtonEToFDetectedRapidity->Sumw2();
    
    KaonPlusToFDetected = new TH2D("KaonPlusToFDetected", "Number of K^{+} Tracks Detected By ToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    KaonPlusToFDetected->Sumw2();

    KaonPlusToFDetectedRapidity = new TH2D("KaonPlusToFDetectedRapidity", "Number of K^{+} Tracks Detected By ToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonPlusToFDetectedRapidity->Sumw2();

    KaonPlusToFDetectedRapidityMSquaredCuts = new TH2D("KaonPlusToFDetectedRapidityMSquaredCuts", "Number of K^{+} Tracks Detected By ToF with m^{2} Cuts; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonPlusToFDetectedRapidityMSquaredCuts->Sumw2();

    KaonPlusEToFDetected = new TH2D("KaonPlusEToFDetected", "Number of K^{+} Tracks Detected By EToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    KaonPlusEToFDetected->Sumw2();

    KaonPlusEToFDetectedRapidity = new TH2D("KaonPlusEToFDetectedRapidity", "Number of K^{+} Tracks Detected By EToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonPlusEToFDetectedRapidity->Sumw2();
    
    KaonMinusToFDetected = new TH2D("KaonMinusToFDetected", "Number of K^{-} Tracks Detected By ToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    KaonMinusToFDetected->Sumw2();

    KaonMinusToFDetectedRapidity = new TH2D("KaonMinusToFDetectedRapidity", "Number of K^{-} Tracks Detected By ToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonMinusToFDetectedRapidity->Sumw2();

    KaonMinusToFDetectedRapidityMSquaredCuts = new TH2D("KaonMinusToFDetectedRapidityMSquaredCuts", "Number of K^{-} Tracks Detected By ToF with m^{2} Cuts; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonMinusToFDetectedRapidityMSquaredCuts->Sumw2();

    KaonMinusEToFDetected = new TH2D("KaonMinusEToFDetected", "Number of K^{-} Tracks Detected By EToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    KaonMinusEToFDetected->Sumw2();

    KaonMinusEToFDetectedRapidity = new TH2D("KaonMinusEToFDetectedRapidity", "Number of K^{-} Tracks Detected By EToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    KaonMinusEToFDetectedRapidity->Sumw2();
    
    PionPlusToFDetected = new TH2D("PionPlusToFDetected", "Number of #pi^{+} Tracks Detected By ToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    PionPlusToFDetected->Sumw2();

    PionPlusToFDetectedRapidity = new TH2D("PionPlusToFDetectedRapidity", "Number of #pi^{+} Tracks Detected By ToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionPlusToFDetectedRapidity->Sumw2();

    PionPlusToFDetectedRapidityMSquaredCuts = new TH2D("PionPlusToFDetectedRapidityMSquaredCuts", "Number of #pi^{+} Tracks Detected By ToF with m^{2} Cuts; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionPlusToFDetectedRapidityMSquaredCuts->Sumw2();

    PionPlusEToFDetected = new TH2D("PionPlusEToFDetected", "Number of #pi^{+} Tracks Detected By EToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    PionPlusEToFDetected->Sumw2();

    PionPlusEToFDetectedRapidity = new TH2D("PionPlusEToFDetectedRapidity", "Number of #pi^{+} Tracks Detected By EToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionPlusEToFDetectedRapidity->Sumw2();
    
    PionMinusToFDetected = new TH2D("PionMinusToFDetected", "Number of #pi^{-} Tracks Detected By ToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    PionMinusToFDetected->Sumw2();

    PionMinusToFDetectedRapidity = new TH2D("PionMinusToFDetectedRapidity", "Number of #pi^{-} Tracks Detected By ToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionMinusToFDetectedRapidity->Sumw2();

    PionMinusToFDetectedRapidityMSquaredCuts = new TH2D("PionMinusToFDetectedRapidityMSquaredCuts", "Number of #pi^{-} Tracks Detected By ToF with m^{2} Cuts; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionMinusToFDetectedRapidityMSquaredCuts->Sumw2();

    PionMinusEToFDetected = new TH2D("PionMinusEToFDetected", "Number of #pi^{-} Tracks Detected By EToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    PionMinusEToFDetected->Sumw2();

    PionMinusEToFDetectedRapidity = new TH2D("PionMinusEToFDetectedRapidity", "Number of #pi^{-} Tracks Detected By EToF; y_{cm}; P_{T} (GeV)", 50, -2.5, 2.5, 60, 0, 6);
    PionMinusEToFDetectedRapidity->Sumw2();

    DeuteronToFDetected = new TH2D("DeuteronToFDetected", "Number of Deuteron Tracks Detected By ToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    DeuteronToFDetected->Sumw2();

    DeuteronEToFDetected = new TH2D("DeuteronEToFDetected", "Number of Deuteron Tracks Detected By EToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    DeuteronEToFDetected->Sumw2();

    TritonToFDetected = new TH2D("TritonToFDetected", "Number of Triton Tracks Detected By ToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    TritonToFDetected->Sumw2();

    TritonEToFDetected = new TH2D("TritonEToFDetected", "Number of Triton Tracks Detected By EToF; #eta; P_{T} (GeV)", 30, -3, 0, 60, 0, 6);
    TritonEToFDetected->Sumw2();


    
    
    
    
    std::cout << "Setup Complete" << std::endl; 
    
    
    return kStOK;
}





Int_t ToFEfficiencyMaker::Make()
{   
    //Bichsel function setup
    Double_t log2dx = 1.0;
    Double_t xStart = 0.01;
    Double_t xStop  = 3.0;
    Int_t npx = 10000;

    const Double_t DeuteronMass = 1.875613;
    const Double_t TritonMass = 2.808921;

    Double_t parameters[2] = {1.0, log2dx};

    parameters[0] = DeuteronMass;
    TF1 *BichselZDeuteron = new TF1(Form("BichselZDeuteron_log2dx_%i",(int)log2dx),BichselZ,xStart,xStop,2);
    BichselZDeuteron->SetParameters(parameters); 
    BichselZDeuteron->SetNpx(npx);

    parameters[0] = TritonMass;
    TF1 *BichselZTriton = new TF1(Form("BichselZTriton_log2dx_%i",(int)log2dx),BichselZ,xStart,xStop,2);
    BichselZTriton->SetParameters(parameters); 
    BichselZTriton->SetNpx(npx);
    
    
    


    
    
    // Parameters
    Double_t yCMShift = -1.05;



    Double_t RVertexBound = 1.5;
    Double_t ZVertexLowerBound = 198.0;
    Double_t ZVertexUpperBound = 202.0;
    
    Double_t DCABound = 3.0;
    Int_t NHitsBound = 15;
    Int_t NHitsdEdxBound = 5;
    Double_t NHitsFitOverNHitsPossBound = 0.52;

    
    
    
    Double_t ProtonLowerMSquared = 0.6;
    Double_t ProtonUpperMSquared = 1.2;
    Double_t KaonLowerMSquared = 0.15;
    Double_t KaonUpperMSquared = 0.34;
    Double_t PionLowerMSquared = -0.1;
    Double_t PionUpperMSquared = 0.1;
    Double_t NSigmaPrBound = 2.0;
    Double_t NSigmaKaBound = 3.0;
    Double_t NSigmaPiBound = 3.0;

   


    std::vector<int> RunIDs {0, 79020,79021,79022,78002,78003,78004,78005,78006,78007,78008,78009,78010,78011,78012,78013,77002,77003,77004,77005,77006,77007,77008,77012,77013,77014,76001,76002,76003,76004,76005,76006,76007,76008,76009,76011,76012,75001,75002,75003,75004,75005,75006,75007,75008,75010,75011,75013,75031,75032,74002,74003,74004,74005,74006,74007,74010,74011,74012,74013,74014,74018,74019,74046,74047,74048,74049,74050,74054,74055,74056,74057,74058,74059,74060,74061,74062,73001,73002,73003,73004,73005,73006,73009,73010,73011,73012,73013,73014,73015,73016,73017,73018,73019,73020,73023,73024,73025,73026,73027,73028,73029,73030,73031,73032,73033,73034,73035,72001,72002,72003,72004,72005,72006,72007,72008,72009,72010,72022,72024,72025,71021,71022,71023,71024,71025,71026,71027,71028,71029,71030,71031,71032,71033,70001,70002,70003,70004,70005,70006,70007,70008,70009,70014,70015,70016,70017,70018,70019,70020,70021,70022,69001,69002,69003,69004,69005,69006,69007,69008,69009,69010,69011,69018,69022,69023,68003,68004,68005,68006,68007,68008,68009,68010,68015,67001,67002,67003,67004,67005,67006,67007,67008,67009,67010,67011,67012,67016,67017,67021,67022,67023,67024,67025,67027,67028,67029,66001,66002,66003,66004,66005,66006,66009,66010,66013,66014,66015,66016,66017,66018,66019,66020,66023,66024,66026,66028,66029,66030,66031,66034,66035,66036,66037,66038,66039,65001,65002,65003,65004,65005,65006,65007,65008,65009,65010,65012,65013,65014,65015,65016,65017,65018,65019,65021,65024,65025,65026,65027,65028,65029,65031,65032,65033,65034,65035,64001,64002,64003,64004,64005,64006,64007,64008,64009,64010,64011,64012,64013,64014,64015,64016,64017,64018,64019,64022,64024,64025,64026,64027,64028,64029,64030,64031,64032,64033,63002,63003,63004,63005,63006,63007,63008,63009,63010,63011,63012,63013,63014,63015,63016,63017,63018,63019,63020,63026,63027,63028,63029,63030,63031,63032,63034,63035,63036,62001,62003,62006,62007,62008,62009,62015,62018,62019,62021,62022,62023,61001,61002,61003,61004,61005,61006,61009,61010,61012,61013,61014,61015,61016,61018,61019,61020,61023,61024,61025,61026,61027,61028,61029,61030,61031,61032,61033,60001,60002,60003,60004,60005,60006,60007,60008,60009,60010,60011,60012,60013,60014,60015,60016,60017,60018,60019,60020,60021,60022,60024,60025,60026,60027,60028,60029,60030,60031,60032,60046,60047,60048,60049,60050,60051,60052,60053,59001,59003,59008,59009,59010,59011,59012,59013,59015,59051,59052,59053,58032,58033,58036,25001,25002,25003,25004,25005,25006,25007,25008,25009,25010,25011,24002,24003,24004,24005,24006,24007,24008,24011,24012,24013,24014,24018,24027,24028,24031,23001,23002,23003,23004,23005,23006,23007,23008,23009,23010,23011,23012,23013,23014,23015,23016,23017,23018,23020,23021,23025,23026,23027,23028,23030,23031,23032,23034,23035,23037,23038,23040,23041,22001,22002,22003,22004,22005,22006,22007,22008,22009,22010,22011,22014,22016,22017,22018,22019,22020,22021,22024,22025,22026,22027,22028,22029,22031,22032,22034,22035,21033,21036,21037,21038,21039,21040,21041,21044,21045,21046,21048,21049,21050,21052,21053};



    
    const Int_t NumBadRuns = 67;
        
    const Int_t BadRuns[NumBadRuns] = {22121046, 22122004, 22122005, 22122021, 22122034, 22123002, 22123007, 22123016, 22124011, 22158032, 22158033, 22158036, 22159001, 22159003, 22159009, 22159010, 22159012, 22159015, 22160003, 22160031, 22161016, 22162015, 22163002, 22163003, 22163007, 22163010, 22164010, 22164018, 22164025, 22163004, 22163005, 22163006, 22165012, 22165034, 22166003, 22166013, 22166026, 22166030, 22167004, 22167009, 22168009, 22169009, 22171023, 22173026, 22173035, 22174004, 22174005, 22174006, 22174007, 22174010, 22174011, 22174012, 22174013, 22174014, 22174019, 22174049, 22176007, 22177004, 22177006, 22178004, 22178013, 22179020, 22171029, 22172003, 22172007, 22173004, 22173013};
    
    const Int_t TriggerIDs[3] = {820010, 820020, 820030};


    

    const Int_t NumEToFMatchFlags = 3;

    const Int_t EToFMatchFlags[NumEToFMatchFlags] = {-52, -42, -32};

    
  

    if(!mPicoDstMaker) {
        LOG_WARN << " No PicoDstMaker! Skip! " << endm;
        return kStWarn;
    }
    mPicoDst = mPicoDstMaker->picoDst();
    if(!mPicoDst) {
        LOG_WARN << " No PicoDst! Skip! " << endm;
        return kStWarn;
    }
    picoEvent = (StPicoEvent*)mPicoDst->event();
    if( !picoEvent ){
        LOG_WARN << " No PicoEvent! Skip! " << endm;
        return kStWarn;
    }

    EventCheck->Fill(0);

    Int_t RunID = picoEvent->runId();

    Bool_t IsBadRun = false;

    for(Int_t i = 0; i < NumBadRuns; i++)
    {
        if(RunID == BadRuns[i])
        {
            IsBadRun = true;
        }
    }

    if(IsBadRun)
    {
        return 0;
    }

    EventCheck->Fill(1);

    Bool_t IsTriggered = false;
    
    for(Int_t i = 0; i < 3; i++)
    {
         if(picoEvent->isTrigger(TriggerIDs[i]))
         {
             IsTriggered = true;
         }
    }

    if(!IsTriggered)
    {
        return 0;
    }

    EventCheck->Fill(2);

    TVector3 PrimaryVertex = picoEvent->primaryVertex();

    Double_t vx = PrimaryVertex.x();
    Double_t vy = PrimaryVertex.y();
    Double_t vz = PrimaryVertex.z();

    Double_t vr = sqrt(pow(vx, 2) + pow(vy + 2, 2));
    
    Int_t TotalTracks = mPicoDst->numberOfTracks();
    Int_t NumPrimaryTracks = 0;
    
    for (Int_t TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
    {
        StPicoTrack *pTrack = (StPicoTrack*)mPicoDst->track(TrackNum);
    
        if(!pTrack->isPrimary())
        {
            continue;
        }
        
        NumPrimaryTracks++;
    }
    
    
    
    Int_t Centrality = -1;

    if     ( NumPrimaryTracks >=   5 && NumPrimaryTracks <=   6 ) Centrality =  0;  // 75% - 80% (Peripheral)
    else if( NumPrimaryTracks >=   7 && NumPrimaryTracks <=   9 ) Centrality =  1;
    else if( NumPrimaryTracks >=  10 && NumPrimaryTracks <=  12 ) Centrality =  2;
    else if( NumPrimaryTracks >=  13 && NumPrimaryTracks <=  17 ) Centrality =  3;
    else if( NumPrimaryTracks >=  18 && NumPrimaryTracks <=  23 ) Centrality =  4;
    else if( NumPrimaryTracks >=  24 && NumPrimaryTracks <=  30 ) Centrality =  5;
    else if( NumPrimaryTracks >=  31 && NumPrimaryTracks <=  38 ) Centrality =  6;
    else if( NumPrimaryTracks >=  39 && NumPrimaryTracks <=  48 ) Centrality =  7;
    else if( NumPrimaryTracks >=  49 && NumPrimaryTracks <=  59 ) Centrality =  8;
    else if( NumPrimaryTracks >=  60 && NumPrimaryTracks <=  72 ) Centrality =  9;
    else if( NumPrimaryTracks >=  73 && NumPrimaryTracks <=  88 ) Centrality = 10;
    else if( NumPrimaryTracks >=  89 && NumPrimaryTracks <= 105 ) Centrality = 11;
    else if( NumPrimaryTracks >= 106 && NumPrimaryTracks <= 126 ) Centrality = 12;
    else if( NumPrimaryTracks >= 127 && NumPrimaryTracks <= 150 ) Centrality = 13;
    else if( NumPrimaryTracks >= 151 && NumPrimaryTracks <= 179 ) Centrality = 14;
    else if( NumPrimaryTracks >= 180 && NumPrimaryTracks <= 195 ) Centrality = 15;  // 0% - 5% (Central)
    
    
    if(Centrality < 0)
    {
        return 0;
    }
    
    EventCheck->Fill(3);


    
    
    if ((vz <= ZVertexLowerBound) || (vz >= ZVertexUpperBound))
    {
        return 0;
    }

    EventCheck->Fill(4);

    if (vr >= RVertexBound)
    {
        return 0;
    }

    EventCheck->Fill(5);

    
    
    Double_t ProtonMass = 0.938;
    Double_t KaonMass = 0.493;
    Double_t PionMass = 0.13957;




    //Kinematics Track Loop
    for (Int_t TrackNum = 0; TrackNum < TotalTracks; TrackNum++)
    {
        StPicoTrack *pTrack = (StPicoTrack*)mPicoDst->track(TrackNum);

        
        if(!pTrack->isPrimary())
        {
            continue;
        } 
        
        
        Double_t px = pTrack->pMom().X();
        Double_t py = pTrack->pMom().Y();
        Double_t pz = pTrack->pMom().Z();
        Int_t q = pTrack->charge();
        Double_t tofBeta = -999.0;
        Double_t dEdx = pTrack->dEdx();
        Double_t NSigmaPr = pTrack->nSigmaProton();
        Double_t NSigmaKa = pTrack->nSigmaKaon();
        Double_t NSigmaPi = pTrack->nSigmaPion();
        Double_t DCA = pTrack->gDCA(vx,vy,vz);
        Int_t NHits = pTrack->nHits();
        Int_t NHitsdEdx = pTrack->nHitsDedx();
        Int_t NHitsFit = pTrack->nHitsFit();
        Int_t NHitsPoss = pTrack->nHitsPoss();


        Double_t BToFBeta = -999.0;
        Double_t EToFBeta = -999.0;

        Bool_t IsGoodEToFMatchFlag = false;
        
        if(pTrack->isTofTrack())
        {
            tofBeta = mPicoDst->btofPidTraits(pTrack->bTofPidTraitsIndex())->btofBeta();
            BToFBeta = mPicoDst->btofPidTraits(pTrack->bTofPidTraitsIndex())->btofBeta();
        }

        if((pTrack->isETofTrack()))
        {
            for(int i = 0; i < NumEToFMatchFlags; i++)
            {
                if((mPicoDst->etofPidTraits(pTrack->eTofPidTraitsIndex())->matchFlag()) == EToFMatchFlags[i])
                {
                    IsGoodEToFMatchFlag = true;
                }
            }
            
            if( (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag))
            {
                tofBeta = mPicoDst->etofPidTraits(pTrack->eTofPidTraitsIndex())->beta();
                EToFBeta = mPicoDst->etofPidTraits(pTrack->eTofPidTraitsIndex())->beta();
            }
        }
        



        if((pTrack->isTofTrack()) && ((pTrack->isETofTrack()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag)))
        {
            continue;
        }
        


        if (DCA >= DCABound)
        {
            continue;
        }
        if (NHits < NHitsBound)
        {
            continue;
        }
        if (NHitsdEdx <= NHitsdEdxBound)
        {
            continue;
        }
        if ((Double_t)NHitsFit / (Double_t)NHitsPoss <= NHitsFitOverNHitsPossBound)
        {
            continue;
        }



        if(q == 0)
        {
            continue;
        } 



        
        Double_t pt = FlowFunctions::Pt(px, py);

        Double_t p = FlowFunctions::P(px, py, pz);

        Double_t eta = FlowFunctions::Eta(px, py, pz);





        if(std::isnan(p))
        {
            continue;
        }
        
        




        // if((q == 1) && (pt > 0.16) && (pt < 6.0) && (eta > -2.5) && (eta < 0.0))
        // {
        //     Double_t zDeuteron = TMath::Log(dEdx / BichselZDeuteron->Eval(p));
        //     Double_t zTriton = TMath::Log(dEdx / BichselZTriton->Eval(p));
            
        //     h2_zd_vs_mom->Fill(p, zDeuteron);
        //     h2_zt_vs_mom->Fill(p, zTriton);

        //     MomentumDistributionBischel->Fill(p);
        //     ZDeuteronDistribution->Fill(zDeuteron);
        //     ZTritonDistribution->Fill(zTriton);
        // }

        //Particle Identification
        Bool_t IsKaon = false;
        Bool_t IsPion = false;
        // Bool_t IsProtonToF = false;
        Bool_t IsDeuteron = false;
        Bool_t IsTriton = false;
        Bool_t IsProtonTPC = (abs(NSigmaPr) < NSigmaPrBound) && (q == 1);

        Double_t msquared = 0;
        

        if(tofBeta > 0)
        {
            msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

            IsKaon = (abs(NSigmaKa) < NSigmaKaBound) && (msquared > KaonLowerMSquared) && (msquared < KaonUpperMSquared);
            IsPion = (abs(NSigmaPi) < NSigmaPiBound) && (msquared > PionLowerMSquared) && (msquared < PionUpperMSquared);
            // IsProtonToF = (abs(NSigmaPr) < NSigmaPrBound) && (msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared) && (q == 1);
        }

        Double_t zDeuteron = TMath::Log(dEdx / BichselZDeuteron->Eval(p));
        Double_t zTriton = TMath::Log(dEdx / BichselZTriton->Eval(p));

        DeuteronsAndTritons DAndT (p, dEdx, tofBeta, EToFBeta, zDeuteron, zTriton, false, false, false, false, false, false);


        if(!(IsKaon) && !(IsPion))
        {
            IsDeuteron = DAndT.IsDeuteron() and (q == 1);
            IsTriton = DAndT.IsTriton() and (q == 1);
        }
        



        if((IsDeuteron) && (IsTriton))
        {
            IsDeuteron = false;
            IsTriton = false;
        }

        if((IsKaon) && (IsProtonTPC))
        {
            IsProtonTPC = false;
        }

        if((IsPion) && (IsProtonTPC))
        {
            IsProtonTPC = false;
        }

        if((IsDeuteron) && (IsProtonTPC))
        {
            IsProtonTPC = false;
        }

        if((IsTriton) && (IsProtonTPC))
        {
            IsProtonTPC = false;
        }




        if(abs(NSigmaPr) < NSigmaPrBound)
        {
            Double_t mass = ProtonMass;
            
            Double_t y = FlowFunctions::Y(px, py, pz, mass);
            
            ProtonTPCDetected->Fill(eta, pt);
            ProtonTPCDetectedRapidity->Fill(y - yCMShift, pt);

            if((pTrack->isTofTrack()) && (tofBeta > 0.001))
            {   
                ProtonToFDetected->Fill(eta, pt);
                ProtonToFDetectedRapidity->Fill(y - yCMShift, pt);

                msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

                if((msquared > ProtonLowerMSquared) && (msquared < ProtonUpperMSquared))
                {
                    ProtonToFDetectedRapidityMSquaredCuts->Fill(y - yCMShift, pt);
                }
            }

            if((pTrack->isETofTrack()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag) && (EToFBeta > 0.001))
            {
                ProtonEToFDetected->Fill(eta, pt);
                ProtonEToFDetectedRapidity->Fill(y - yCMShift, pt);
            }      
        }
        

        if((abs(NSigmaKa) < NSigmaKaBound) && (q > 0))
        {
            Double_t mass = KaonMass;

            Double_t y = FlowFunctions::Y(px, py, pz, mass);
            
            KaonPlusTPCDetected->Fill(eta, pt);
            KaonPlusTPCDetectedRapidity->Fill(y - yCMShift, pt);

            if((pTrack->isTofTrack()) && (tofBeta > 0.001))
            {   
                KaonPlusToFDetected->Fill(eta, pt);
                KaonPlusToFDetectedRapidity->Fill(y - yCMShift, pt);

                msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

                if((msquared > KaonLowerMSquared) && (msquared < KaonUpperMSquared))
                {
                    KaonPlusToFDetectedRapidityMSquaredCuts->Fill(y - yCMShift, pt);
                }
            }

            if((pTrack->isETofTrack()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag) && (EToFBeta > 0.001))
            {
                KaonPlusEToFDetected->Fill(eta, pt);
                KaonPlusEToFDetectedRapidity->Fill(y - yCMShift, pt);
            }     
        }

        if((abs(NSigmaKa) < NSigmaKaBound) && (q < 0))
        {
            Double_t mass = KaonMass;

            Double_t y = FlowFunctions::Y(px, py, pz, mass);
            
            KaonMinusTPCDetected->Fill(eta, pt);
            KaonMinusTPCDetectedRapidity->Fill(y - yCMShift, pt);

            if((pTrack->isTofTrack()) && (tofBeta > 0.001))
            {
                KaonMinusToFDetected->Fill(eta, pt);
                KaonMinusToFDetectedRapidity->Fill(y - yCMShift, pt);

                msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);
            }
            
            if((pTrack->isETofTrack()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag) && (EToFBeta > 0.001))
            {
                KaonMinusEToFDetected->Fill(eta, pt);
                KaonMinusEToFDetectedRapidity->Fill(y - yCMShift, pt);
            }     
        }

        if((abs(NSigmaPi) < NSigmaPiBound) && (q > 0))
        {
            Double_t mass = PionMass;

            Double_t y = FlowFunctions::Y(px, py, pz, mass);
            
            PionPlusTPCDetected->Fill(eta, pt);
            PionPlusTPCDetectedRapidity->Fill(y - yCMShift, pt);

            if((pTrack->isTofTrack()) && (tofBeta > 0.001))
            {
                PionPlusToFDetected->Fill(eta, pt);
                PionPlusToFDetectedRapidity->Fill(y - yCMShift, pt);

                msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

                if((msquared > PionLowerMSquared) && (msquared < PionUpperMSquared))
                {
                    PionPlusToFDetectedRapidityMSquaredCuts->Fill(y - yCMShift, pt);
                }
            }

            if((pTrack->isETofTrack()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag) && (EToFBeta > 0.001))
            {
                PionPlusEToFDetected->Fill(eta, pt);
                PionPlusEToFDetectedRapidity->Fill(y - yCMShift, pt);
            }     
        }

        if((abs(NSigmaPi) < NSigmaPiBound) && (q < 0))
        {
            Double_t mass = PionMass;

            Double_t y = FlowFunctions::Y(px, py, pz, mass);
            
            PionMinusTPCDetected->Fill(eta, pt);
            PionMinusTPCDetectedRapidity->Fill(y - yCMShift, pt);

            if((pTrack->isTofTrack()) && (tofBeta > 0.001))
            {
                PionMinusToFDetected->Fill(eta, pt);
                PionMinusToFDetectedRapidity->Fill(y - yCMShift, pt);

                msquared = FlowFunctions::MSquared(px, py, pz, tofBeta);

                if((msquared > PionLowerMSquared) && (msquared < PionUpperMSquared))
                {
                    PionMinusToFDetectedRapidityMSquaredCuts->Fill(y - yCMShift, pt);
                }
            }

            if((pTrack->isETofTrack()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag) && (EToFBeta > 0.001))
            {
                PionMinusEToFDetected->Fill(eta, pt);
                PionMinusEToFDetectedRapidity->Fill(y - yCMShift, pt);
            }     
        }

        if((IsDeuteron) && (DAndT.GetFoundWithDeuteronTPC()))
        {
            DeuteronTPCDetected->Fill(eta, pt);

            if((DAndT.GetFoundWithDeuteronToF()) && (tofBeta > 0.001))
            {
                DeuteronToFDetected->Fill(eta, pt);
            }

            if((DAndT.GetFoundWithDeuteronEToF()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag) && (EToFBeta > 0.001))
            {
                DeuteronEToFDetected->Fill(eta, pt);
            }
        }

        if((IsTriton) && (DAndT.GetFoundWithTritonTPC()))
        {
            TritonTPCDetected->Fill(eta, pt);

            if((DAndT.GetFoundWithTritonToF()) && (tofBeta > 0.001))
            {
                TritonToFDetected->Fill(eta, pt);
            }

            if((DAndT.GetFoundWithTritonEToF()) && (mPicoDst->etofHit(pTrack->eTofPidTraitsIndex())->clusterSize() <= 100) && (IsGoodEToFMatchFlag) && (EToFBeta > 0.001))
            {
                TritonEToFDetected->Fill(eta, pt);
            }
        }            
    }

    delete BichselZDeuteron;
    delete BichselZTriton;

    return kStOK;   
}

