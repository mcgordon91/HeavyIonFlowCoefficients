#include <TSystem>


class StMaker;
class StChain;
class StPicoDstMaker;
class StPicoDst;
class StPicoEvent;


Int_t RunTreeAnalyzer(TString InputFileList, TString JobIdName, TString SystematicName)
{
  Int_t nEvents = 999999999;
    
  // Load libraries
  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  loadSharedLibraries();

  gSystem->Load("StPicoEvent");
  gSystem->Load("StPicoDstMaker");
  gSystem->Load("StEpdUtil");
  gSystem->Load("TreeAnalyzer.so");

  std::cout << "Loaded" << std::endl;
  // List of member links in the chain
  StChain* chain = new StChain;
  std::cout << "chain" << std::endl;
  StPicoDstMaker* picoMaker = new StPicoDstMaker(2,InputFileList,"picoDst");
  std::cout << "picoMaker" << std::endl;
  TreeAnalyzer* doAnalysis = new TreeAnalyzer(picoMaker,JobIdName,SystematicName);
  std::cout << "doAnalysis" << std::endl;
    
  // Loop over the links in the chain
  if(chain->Init() == kStErr)
    {
      cout << "Init() Error!" << endl;
      return;
    }
    
  int total = picoMaker->chain()->GetEntries();
  cout << " Total entries = " << total << endl;
  if(nEvents > total) nEvents = total;
    
  for (Int_t i = 0; i < nEvents; i++)
    {

      // if(i % 10000 == 0) cout << "Working on eventNumber " << i << endl;
      
      chain->Clear();
      int iret = chain->Make(i);      
      if (iret) { cout << "Bad return code!" << iret << endl; break;}

      total++;
    }
    
  cout << "****************************************** " << endl;
  cout << "Work done... now its time to close up shop!" << endl;
  cout << "****************************************** " << endl;
  chain->Finish();
  cout << "****************************************** " << endl;
  cout << "total number of events  " << nEvents << endl;
  cout << "****************************************** " << endl;
    
  // Cleanup
  delete doAnalysis;
  delete picoMaker;
  delete chain;
  return 0;
}
