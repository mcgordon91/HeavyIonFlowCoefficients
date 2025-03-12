#include <TSystem>

class StMaker;
class StChain;
class StPicoDstMaker;
class StPicoEvent;


void RunTreeAnalyzer(const Char_t *InputFile,  Char_t *JobID, const Char_t *Systematic)
{
    Long64_t TotalEvents = 999999999;

    gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
    loadSharedLibraries();

    gSystem->Load("StPicoEvent");
    gSystem->Load("StPicoDstMaker");
    gSystem->Load("StEpdUtil");
    gSystem->Load("TreeAnalyzer.so");
    std::cout << "Shared Libraries Loaded" << std::endl;


    
    // List of member links in the chain
    StChain* chain = new StChain;
    std::cout << "Chain Created" << std::endl;
    
    StPicoDstMaker* picoMaker = new StPicoDstMaker(2, InputFile, "picoDst");
    std::cout << "picoMaker Created" << std::endl;

    TreeAnalyzer *Analyzer = new TreeAnalyzer(picoMaker, JobID, Systematic);
    std::cout << "Analyzer Created" << std::endl;

    if(chain->Init() == kStErr)
    {
      cout << "Init() Error!" << endl;
      return;
    }
    
    int total = picoMaker->chain()->GetEntries();
    cout << " Total entries = " << total << endl;

    if (TotalEvents > total) TotalEvents = total;
    for (Int_t EventNum = 0; EventNum < TotalEvents; EventNum++)
    {
        if(EventNum % 5000 == 0) cout << "Working on eventNumber " << EventNum << endl;
        
        chain->Clear();
        int iret = chain->Make(EventNum);

        if (iret)
        {
            cout << "Bad return code!" << iret << endl;
            break;
        }
    }

    cout << "****************************************** " << endl;
    cout << "Work done... now its time to close up shop!" << endl;
    cout << "****************************************** " << endl;
    chain->Finish();

    delete picoMaker;
    delete Analyzer;
    delete chain;

}