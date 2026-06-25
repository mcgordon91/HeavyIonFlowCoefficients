#include <TSystem>

class StMaker;
class StChain;
class StPicoDstMaker;
StChain *chain;

void readPicoDst(const Char_t *inputFile ="test.list", const Char_t *OutputFile="Out_TestFile.root")
{  
  Int_t nEvents = 999999999;

  
  // Load all the System libraries
  cout << "Load" << endl;
  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  loadSharedLibraries();
    
  gSystem->Load("StPicoEvent");
  gSystem->Load("StPicoDstMaker");
  gSystem->Load("StRefMultCorr");
  //gSystem->Load("PicoTreeMaker");
  gSystem->Load("MyAnalysisMaker");//knayak   

  chain = new StChain();
  
  StPicoDstMaker *picoMaker = new StPicoDstMaker(2,inputFile,"picoDst");
  //StPicoDstMaker *picoMaker = new StPicoDstMaker(2,"st_physics_18153041_raw_0000002.picoDst.root","picoDst");
  //PicoTreeMaker *anaMaker = new PicoTreeMaker("ana",picoMaker,outputFile);
  MyAnalysisMaker* AnalysisCode = new MyAnalysisMaker(picoMaker);
  AnalysisCode -> SetOutputFileName(OutputFile);
  
  if(chain->Init()==kStErr)
    { 
      cout<<"chain->Init(): ERROR..."<<endl;
      return;
    }
  else {
    cout<<"chain->Init();"<<endl;
  }
  
  int neveData = picoMaker->chain()->GetEntries();
  cout << " Total entries = " << neveData << endl;
  if( neveData<nEvents ) nEvents = neveData;
  
  int total = 0;
  for (Int_t i=0; i<nEvents; i++)
    {  

      if(i%100==0) cout << "Working on eventNumber " << i << endl;
      //cout << "Working on eventNumber " << i << endl;
      
      chain->Clear();
      int iret = chain->Make(i);
      if( iret )
	{ 
	  cout << "Bad return code!" << iret << endl; 
	  break;
	}
      
      total++;
    }
  
  chain->Finish();
  
  //delete anaMaker;
  delete picoMaker;  
  delete chain;     
}

