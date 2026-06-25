#include <iostream>
#include <string>

#include "TROOT.h"
#include "TString.h"

void FinalPlotting()
{
    Int_t NumPtBins[7] = {20, 20, 20, 20, 20, 40, 60};
    Double_t LowerPt[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    Double_t UpperPt[7] = {2.0, 2.0, 2.0, 2.0, 2.0, 4.0, 4.0};
    
    TFile *InputFile = new TFile("/star/u/mcgordon/CorrelationsTest.root", "READ");
    TProfile* TwoPartRefVsCentProfile = (TProfile*)InputFile->Get("TwoPartRefVsCent");
    TProfile* FourPartRefVsCentProfile = (TProfile*)InputFile->Get("FourPartRefVsCent");

    // TProfile* AvgCosCentEPDProfile = (TProfile*)InputFile->Get("AvgCosCentEPD");
    // TProfile* AvgSinCentEPDProfile = (TProfile*)InputFile->Get("AvgSinCentEPD");    

    TH1D *TwoPartVnVsCent[7];
    TH2D *TwoPartVnVsCentVsPt[7];
    TH2D *TwoPartVnVsCentVsY[7];

    TH1D *FourPartVnVsCent[7];
    TH2D *FourPartVnVsCentVsPt[7];
    TH2D *FourPartVnVsCentVsY[7];

    const Int_t nV = 1;

    const char* CentralityXLabels[16] = {"0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60"};
    std::string ParticleNames[7] = {"Protons", "K^{+}", "K^{-}", "#pi^{+}", "#pi^{-}", "Deuterons", "Tritons"};
   
    for(int i = 0; i < 7; i++)
    {        
        TwoPartVnVsCent[i] = new TH1D(Form("TwoPartVnVsCent%s", ParticleNames[i].c_str()), Form("V_{%i} vs Centrality for %s from Two-Particle Correlations; Centrality; V_{%i}", nV, ParticleNames[i].c_str(), nV), 12, 0, 12);
        TwoPartVnVsCent[i]->Sumw2();
        
        TwoPartVnVsCentVsPt[i] = new TH2D(Form("TwoPartVnVsCentVsPt%s", ParticleNames[i].c_str()), Form("V_{%i} vs Centrality vs Pt for %s from Two-Particle Correlations; Centrality; Pt; V_{%i}", nV, ParticleNames[i].c_str(), nV), 12, 0, 12, NumPtBins[i], LowerPt[i], UpperPt[i]);
        TwoPartVnVsCentVsPt[i]->Sumw2();
        
        TwoPartVnVsCentVsY[i] = new TH2D(Form("TwoPartVnVsCentVsY%s", ParticleNames[i].c_str()), Form("V_{%i} vs Centrality vs Y for %s from Two-Particle Correlations; Centrality; Y; V_{%i}", nV, ParticleNames[i].c_str(), nV), 12, 0, 12, 10, 0, 1);
        TwoPartVnVsCentVsY[i]->Sumw2();




        FourPartVnVsCent[i] = new TH1D(Form("FourPartVnVsCent%s", ParticleNames[i].c_str()), Form("V_{%i} vs Centrality for %s from Four-Particle Correlations; Centrality; V_{%i}", nV, ParticleNames[i].c_str(), nV), 12, 0, 12);
        FourPartVnVsCent[i]->Sumw2();
        
        FourPartVnVsCentVsPt[i] = new TH2D(Form("FourPartVnVsCentVsPt%s", ParticleNames[i].c_str()), Form("V_{%i} vs Centrality vs Pt for %s from Four-Particle Correlations; Centrality; Pt; V_{%i}", nV, ParticleNames[i].c_str(), nV), 12, 0, 12, NumPtBins[i], LowerPt[i], UpperPt[i]);
        FourPartVnVsCentVsPt[i]->Sumw2();
        
        FourPartVnVsCentVsY[i] = new TH2D(Form("FourPartVnVsCentVsY%s", ParticleNames[i].c_str()), Form("V_{%i} vs Centrality vs Y for %s from Four-Particle Correlations; Centrality; Y; V_{%i}", nV, ParticleNames[i].c_str(), nV), 12, 0, 12, 10, 0, 1);
        FourPartVnVsCentVsY[i]->Sumw2();
    }

    Double_t AvgAvgRefTwoVnVsCent = 0;
    Double_t AvgAvgDiffTwoVnVsCent = 0;
    Double_t AvgAvgRefTwoVnVsCentErr = 0;
    Double_t AvgAvgDiffTwoVnVsCentErr = 0;
    Double_t TwoPartVnVsCentFinalErr = 0;

    Double_t AvgAvgDiffTwoVnVsCentVsPt = 0;
    Double_t AvgAvgDiffTwoVnVsCentVsPtErr = 0;
    Double_t TwoPartVnVsCentVsPtFinalErr = 0;

    Double_t AvgAvgDiffTwoVnVsCentVsY = 0;
    Double_t AvgAvgDiffTwoVnVsCentVsYErr = 0;
    Double_t TwoPartVnVsCentVsYFinalErr = 0;

    Double_t AvgAvgRefFourVnVsCent = 0;
    Double_t AvgAvgDiffFourVnVsCent = 0;
    Double_t AvgAvgRefFourVnVsCentErr = 0;
    Double_t AvgAvgDiffFourVnVsCentErr = 0;
    Double_t FourPartVnVsCentFinalErr = 0;

    Double_t AvgAvgDiffFourVnVsCentVsPt = 0;
    Double_t AvgAvgDiffFourVnVsCentVsPtErr = 0;
    Double_t FourPartVnVsCentVsPtFinalErr = 0;

    Double_t AvgAvgDiffFourVnVsCentVsY = 0;
    Double_t AvgAvgDiffFourVnVsCentVsYErr = 0;
    Double_t FourPartVnVsCentVsYFinalErr = 0;

    // Double_t AvgCosCentEPD;
    // Double_t AvgCosCentEPDErr;
    // Double_t AvgSinCentEPD;
    // Double_t AvgSinCentEPDErr;
    // Double_t AvgCosCentTPC;
    // Double_t AvgCosCentTPCErr;
    // Double_t AvgSinCentTPC;
    // Double_t AvgSinCentTPCErr;



    for(int i = 0; i < 7; i++)
    {
        TProfile* TwoPartDiffVsCentProfile = (TProfile*)InputFile->Get(Form("TwoPartDiffVsCent%s", ParticleNames[i].c_str()));
        TProfile2D* TwoPartDiffVsCentVsPtProfile = (TProfile2D*)InputFile->Get(Form("TwoPartDiffVsCentVsPt%s", ParticleNames[i].c_str()));
        TProfile2D* TwoPartDiffVsCentVsYProfile = (TProfile2D*)InputFile->Get(Form("TwoPartDiffVsCentVsY%s", ParticleNames[i].c_str()));

        TProfile* FourPartDiffVsCentProfile = (TProfile*)InputFile->Get(Form("FourPartDiffVsCent%s", ParticleNames[i].c_str()));
        TProfile2D* FourPartDiffVsCentVsPtProfile = (TProfile2D*)InputFile->Get(Form("FourPartDiffVsCentVsPt%s", ParticleNames[i].c_str()));
        TProfile2D* FourPartDiffVsCentVsYProfile = (TProfile2D*)InputFile->Get(Form("FourPartDiffVsCentVsY%s", ParticleNames[i].c_str()));

        // TProfile* AvgCosCentTPCProfile = (TProfile*)InputFile->Get(Form("AvgCosCent%sTPC", ParticleNames[i].c_str()));
        // TProfile* AvgSinCentTPCProfile = (TProfile*)InputFile->Get(Form("AvgSinCent%sTPC", ParticleNames[i].c_str()));


            for(int j = 1; j < TwoPartRefVsCentProfile->GetNbinsX() + 1; j++)
            {
                TwoPartVnVsCent[i]->GetXaxis()->SetBinLabel(j, CentralityXLabels[j - 1]);
                FourPartVnVsCent[i]->GetXaxis()->SetBinLabel(j, CentralityXLabels[j - 1]);
                
                AvgAvgRefTwoVnVsCent = TwoPartRefVsCentProfile->GetBinContent(j);
                AvgAvgDiffTwoVnVsCent = TwoPartDiffVsCentProfile->GetBinContent(j);

               AvgAvgRefFourVnVsCent = FourPartRefVsCentProfile->GetBinContent(j) - 2 * pow(AvgAvgRefTwoVnVsCent,2);
                AvgAvgDiffFourVnVsCent = FourPartDiffVsCentProfile->GetBinContent(j) - 2 * AvgAvgDiffTwoVnVsCent * AvgAvgRefTwoVnVsCent;

                if((AvgAvgRefTwoVnVsCent == 0) || (AvgAvgRefFourVnVsCent == 0))
                {
                    continue;
                }

                AvgAvgRefTwoVnVsCentErr = TwoPartRefVsCentProfile->GetBinError(j);
                AvgAvgDiffTwoVnVsCentErr = TwoPartDiffVsCentProfile->GetBinError(j);

//                AvgAvgRefFourVnVsCentErr = TMath::Sqrt(pow(FourPartRefVsCentProfile->GetBinError(j),2) + 16 * pow(AvgAvgRefTwoVnVsCent,2) * pow(AvgAvgRefTwoVnVsCentErr,2));
                AvgAvgDiffFourVnVsCentErr = TMath::Sqrt(pow(FourPartDiffVsCentProfile->GetBinError(j),2) + 4 * pow(AvgAvgRefTwoVnVsCent,2) * pow(AvgAvgRefTwoVnVsCentErr,2) + 4 * pow(AvgAvgRefTwoVnVsCent,2) * pow(AvgAvgDiffTwoVnVsCentErr,2));

                // AvgCosCentEPD = AvgCosCentEPDProfile->GetBinContent(j);
                // AvgSinCentEPD = AvgSinCentEPDProfile->GetBinContent(j);
                // AvgCosCentTPC = AvgCosCentTPCProfile->GetBinContent(j);
                // AvgSinCentTPC = AvgSinCentTPCProfile->GetBinContent(j);
                // AvgCosCentEPDErr = AvgCosCentEPDProfile->GetBinError(j);
                // AvgSinCentEPDErr = AvgSinCentEPDProfile->GetBinError(j);
                // AvgCosCentTPCErr = AvgCosCentTPCProfile->GetBinError(j);
                // AvgSinCentTPCErr = AvgSinCentTPCProfile->GetBinError(j);

                // AvgAvgRefTwoVnVsCent = AvgAvgRefTwoVnVsCent - pow(AvgCosCentEPD, 2) - pow(AvgSinCentEPD, 2);
                // AvgAvgDiffTwoVnVsCent = AvgAvgDiffTwoVnVsCent - (AvgCosCentEPD * AvgCosCentTPC) - (AvgSinCentEPD * AvgSinCentTPC);

                // AvgAvgRefTwoVnVsCentErr = TMath::Sqrt(pow(AvgAvgRefTwoVnVsCentErr, 2) + pow(2 * AvgCosCentEPD * AvgCosCentEPDErr, 2) + pow(2 * AvgSinCentEPD * AvgSinCentEPDErr, 2));
                // AvgAvgDiffTwoVnVsCentErr = TMath::Sqrt(pow(AvgAvgDiffTwoVnVsCentErr, 2) + pow(AvgCosCentTPC * AvgCosCentEPDErr, 2) + pow(AvgCosCentEPD * AvgCosCentTPCErr, 2) + pow(AvgSinCentTPC * AvgSinCentEPDErr, 2) + pow(AvgSinCentEPD * AvgSinCentTPCErr, 2)); 
        
                TwoPartVnVsCentFinalErr = (TMath::Sqrt(pow((1/TMath::Sqrt(AvgAvgRefTwoVnVsCent)), 2)*pow(AvgAvgDiffTwoVnVsCentErr, 2) + pow((-1 * AvgAvgDiffTwoVnVsCent) / (2 * pow(AvgAvgRefTwoVnVsCent, 1.5)), 2) * pow(AvgAvgRefTwoVnVsCentErr, 2)));

                // FourPartVnVsCentFinalErr = TMath::Sqrt((1/pow(-1*AvgAvgRefFourVnVsCent,1.5))*pow(AvgAvgDiffFourVnVsCentErr,2) + (9.0/16.0)*((pow(AvgAvgDiffFourVnVsCent,2)/pow(-1*AvgAvgRefFourVnVsCent,3.5))*pow(AvgAvgRefFourVnVsCentErr,2)));

                FourPartVnVsCentFinalErr = TMath::Sqrt((1.0 / pow(TMath::Abs(AvgAvgRefTwoVnVsCent), 3.0)) * pow(AvgAvgDiffFourVnVsCentErr, 2) + (9.0 / 4.0) * (pow(AvgAvgDiffFourVnVsCent, 2) / pow(TMath::Abs(AvgAvgRefTwoVnVsCent), 5.0)) * pow(AvgAvgRefTwoVnVsCentErr, 2));

                TwoPartVnVsCent[i]->SetBinContent(j, AvgAvgDiffTwoVnVsCent / TMath::Sqrt(AvgAvgRefTwoVnVsCent));
                TwoPartVnVsCent[i]->SetBinError(j, TwoPartVnVsCentFinalErr);

//                FourPartVnVsCent[i]->SetBinContent(j, (-1)*(AvgAvgDiffFourVnVsCent / pow(-1*AvgAvgRefFourVnVsCent,0.75)));
                FourPartVnVsCent[i]->SetBinContent(j, (-1)*(AvgAvgDiffFourVnVsCent / pow(AvgAvgRefTwoVnVsCent,1.5)));
                FourPartVnVsCent[i]->SetBinError(j, FourPartVnVsCentFinalErr);

                for(int k = 1; k < TwoPartDiffVsCentVsPtProfile->GetNbinsY() + 1; k++)
                {
                    AvgAvgDiffTwoVnVsCentVsPt = TwoPartDiffVsCentVsPtProfile->GetBinContent(j, k);
                    
                    AvgAvgDiffTwoVnVsCentVsPtErr = TwoPartDiffVsCentVsPtProfile->GetBinError(j, k);

                    AvgAvgDiffFourVnVsCentVsPt = FourPartDiffVsCentVsPtProfile->GetBinContent(j, k);
                    
                    AvgAvgDiffFourVnVsCentVsPtErr = FourPartDiffVsCentVsPtProfile->GetBinError(j, k);
            
                    TwoPartVnVsCentVsPtFinalErr = TMath::Sqrt(pow((1/TMath::Sqrt(AvgAvgRefTwoVnVsCent)), 2)*pow(AvgAvgDiffTwoVnVsCentVsPtErr, 2) + pow((-1 * AvgAvgDiffTwoVnVsCentVsPt) / (2 * pow(AvgAvgRefTwoVnVsCent, 1.5)), 2) * pow(AvgAvgRefTwoVnVsCentErr, 2));

                    // FourPartVnVsCentVsPtFinalErr = TMath::Sqrt((1/pow(-1*AvgAvgRefFourVnVsCent,1.5))*pow(AvgAvgDiffFourVnVsCentVsPtErr,2) + (9.0/16.0)*((pow(AvgAvgDiffFourVnVsCentVsPt,2)/pow(-1*AvgAvgRefFourVnVsCent,3.5))*pow(AvgAvgRefFourVnVsCentErr,2)));

                    FourPartVnVsCentVsPtFinalErr = TMath::Sqrt((1.0 / pow(TMath::Abs(AvgAvgRefTwoVnVsCent), 3.0)) * pow(AvgAvgDiffFourVnVsCentVsPtErr, 2) + (9.0 / 4.0) * (pow(AvgAvgDiffFourVnVsCentVsPt, 2) / pow(TMath::Abs(AvgAvgRefTwoVnVsCent), 5.0)) * pow(AvgAvgRefTwoVnVsCentErr, 2));
            
                    TwoPartVnVsCentVsPt[i]->SetBinContent(j, k, AvgAvgDiffTwoVnVsCentVsPt / TMath::Sqrt(AvgAvgRefTwoVnVsCent));
                    TwoPartVnVsCentVsPt[i]->SetBinError(j, k, TwoPartVnVsCentVsPtFinalErr);

//                    FourPartVnVsCentVsPt[i]->SetBinContent(j, k, (-1)*(AvgAvgDiffFourVnVsCentVsPt / pow(-1*AvgAvgRefFourVnVsCent,0.75)));
                    FourPartVnVsCentVsPt[i]->SetBinContent(j, k, (-1)*(AvgAvgDiffFourVnVsCentVsPt / pow(AvgAvgRefTwoVnVsCent,1.5)));
                    FourPartVnVsCentVsPt[i]->SetBinError(j, k, FourPartVnVsCentVsPtFinalErr);
                }
        
        
                for(int k = 1; k < TwoPartDiffVsCentVsYProfile->GetNbinsY() + 1; k++)
                {
                    AvgAvgDiffTwoVnVsCentVsY = TwoPartDiffVsCentVsYProfile->GetBinContent(j, k);
                    
                    AvgAvgDiffTwoVnVsCentVsYErr = TwoPartDiffVsCentVsYProfile->GetBinError(j, k);

                    AvgAvgDiffFourVnVsCentVsY = FourPartDiffVsCentVsYProfile->GetBinContent(j, k);
                    
                    AvgAvgDiffFourVnVsCentVsYErr = FourPartDiffVsCentVsYProfile->GetBinError(j, k);
            
                    TwoPartVnVsCentVsYFinalErr = TMath::Sqrt(pow((1/TMath::Sqrt(AvgAvgRefTwoVnVsCent)), 2)*pow(AvgAvgDiffTwoVnVsCentVsYErr, 2) + pow((-1 * AvgAvgDiffTwoVnVsCentVsY) / (2 * pow(AvgAvgRefTwoVnVsCent, 1.5)), 2) * pow(AvgAvgRefTwoVnVsCentErr, 2));

                    // FourPartVnVsCentVsYFinalErr = TMath::Sqrt((1/pow(-1*AvgAvgRefFourVnVsCent,1.5))*pow(AvgAvgDiffFourVnVsCentVsYErr,2) + (9.0/16.0)*((pow(AvgAvgDiffFourVnVsCentVsY,2)/pow(-1*AvgAvgRefFourVnVsCent,3.5))*pow(AvgAvgRefFourVnVsCentErr,2)));

                    FourPartVnVsCentVsYFinalErr = TMath::Sqrt((1.0 / pow(TMath::Abs(AvgAvgRefTwoVnVsCent), 3.0)) * pow(AvgAvgDiffFourVnVsCentVsYErr, 2) + (9.0 / 4.0) * (pow(AvgAvgDiffFourVnVsCentVsY, 2) / pow(TMath::Abs(AvgAvgRefTwoVnVsCent), 5.0)) * pow(AvgAvgRefTwoVnVsCentErr, 2));
            
                    TwoPartVnVsCentVsY[i]->SetBinContent(j, k, AvgAvgDiffTwoVnVsCentVsY / TMath::Sqrt(AvgAvgRefTwoVnVsCent));
                    TwoPartVnVsCentVsY[i]->SetBinError(j, k, TwoPartVnVsCentVsYFinalErr);

                    // FourPartVnVsCentVsY[i]->SetBinContent(j, k, (-1)*(AvgAvgDiffFourVnVsCentVsY / pow(-1*AvgAvgRefFourVnVsCent,0.75)));
                    FourPartVnVsCentVsY[i]->SetBinContent(j, k, (-1)*(AvgAvgDiffFourVnVsCentVsY / pow(AvgAvgRefTwoVnVsCent,1.5)));
                    FourPartVnVsCentVsY[i]->SetBinError(j, k, FourPartVnVsCentVsYFinalErr);
                }
            }
    }







    
    
    
    
    

//Two-Particle
    
    // Proton
    TH1D *HistoD89 = new TH1D("TwoPartVnVsPtForProtonsCentrality0-10", "V_{1} vs Pt for Protons using Two-Particle Correlations, 0-10% Centrality; Pt; V_{1}", NumPtBins[0], LowerPt[0], UpperPt[0]);
    
    for(int y = 1; y <= NumPtBins[0]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += TwoPartVnVsCentVsPt[0]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[0]->GetBinError(x, y), 2);
        }
    
        HistoD89->SetBinContent(y, Sum / 2);
        HistoD89->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD90 = new TH1D("TwoPartVnVsPtForProtonsCentrality10-40", "V_{1} vs Pt for Protons using Two-Particle Correlations, 10-40% Centrality; Pt; V_{1}", NumPtBins[0], LowerPt[0], UpperPt[0]);
    
    for(int y = 1; y <= NumPtBins[0]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += TwoPartVnVsCentVsPt[0]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[0]->GetBinError(x, y), 2);
        }
    
        HistoD90->SetBinContent(y, Sum / 6);
        HistoD90->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD91 = new TH1D("TwoPartVnVsPtForProtonsCentrality40-60", "V_{1} vs Pt for Protons using Two-Particle Correlations, 40-60% Centrality; Pt; V_{1}", NumPtBins[0], LowerPt[0], UpperPt[0]);
    
    for(int y = 1; y <= NumPtBins[0]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += TwoPartVnVsCentVsPt[0]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[0]->GetBinError(x, y), 2);
        }
    
        HistoD91->SetBinContent(y, Sum / 4);
        HistoD91->SetBinError(y, sqrt(SumErrSq) / 4);
    }

    TH1D *HistoD92 = new TH1D("TwoPartVnVsYForProtonsCentrality0-10", "V_{1} vs y_{CM} for Protons using Two-Particle Correlations, 0-10% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += TwoPartVnVsCentVsY[0]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[0]->GetBinError(x, y), 2);
        }
    
        HistoD92->SetBinContent(y, Sum / 2);
        HistoD92->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD93 = new TH1D("TwoPartVnVsYForProtonsCentrality10-40", "V_{1} vs y_{CM} for Protons using Two-Particle Correlations, 10-40% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += TwoPartVnVsCentVsY[0]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[0]->GetBinError(x, y), 2);
        }
    
        HistoD93->SetBinContent(y, Sum / 6);
        HistoD93->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD94 = new TH1D("TwoPartVnVsYForProtonsCentrality40-60", "V_{1} vs y_{CM} for Protons using Two-Particle Correlations, 40-60% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += TwoPartVnVsCentVsY[0]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[0]->GetBinError(x, y), 2);
        }
    
        HistoD94->SetBinContent(y, Sum / 4);
        HistoD94->SetBinError(y, sqrt(SumErrSq) / 4);
    }







    //K-Plus
    TH1D *HistoD95 = new TH1D("TwoPartVnVsPtForKaonsPlusCentrality0-10", "V_{1} vs Pt for K^{+} using Two-Particle Correlations, 0-10% Centrality; Pt; V_{1}", NumPtBins[1], LowerPt[1], UpperPt[1]);
    
    for(int y = 1; y <= NumPtBins[1]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += TwoPartVnVsCentVsPt[1]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[1]->GetBinError(x, y), 2);
        }
    
        HistoD95->SetBinContent(y, Sum / 2);
        HistoD95->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD96 = new TH1D("TwoPartVnVsPtForKaonsPlusCentrality10-40", "V_{1} vs Pt for K^{+} using Two-Particle Correlations, 10-40% Centrality; Pt; V_{1}", NumPtBins[1], LowerPt[1], UpperPt[1]);
    
    for(int y = 1; y <= NumPtBins[1]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += TwoPartVnVsCentVsPt[1]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[1]->GetBinError(x, y), 2);
        }
    
        HistoD96->SetBinContent(y, Sum / 6);
        HistoD96->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD97 = new TH1D("TwoPartVnVsPtForKaonsPlusCentrality40-60", "V_{1} vs Pt for K^{+} using Two-Particle Correlations, 40-60% Centrality; Pt; V_{1}", NumPtBins[1], LowerPt[1], UpperPt[1]);
    
    for(int y = 1; y <= NumPtBins[1]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += TwoPartVnVsCentVsPt[1]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[1]->GetBinError(x, y), 2);
        }
    
        HistoD97->SetBinContent(y, Sum / 4);
        HistoD97->SetBinError(y, sqrt(SumErrSq) / 4);
    }

    TH1D *HistoD98 = new TH1D("TwoPartVnVsYForKaonsPlusCentrality0-10", "V_{1} vs y_{CM} for K^{+} using Two-Particle Correlations, 0-10% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += TwoPartVnVsCentVsY[1]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[1]->GetBinError(x, y), 2);
        }
    
        HistoD98->SetBinContent(y, Sum / 2);
        HistoD98->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD99 = new TH1D("TwoPartVnVsYForKaonsPlusCentrality10-40", "V_{1} vs y_{CM} for K^{+} using Two-Particle Correlations, 10-40% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += TwoPartVnVsCentVsY[1]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[1]->GetBinError(x, y), 2);
        }
    
        HistoD99->SetBinContent(y, Sum / 6);
        HistoD99->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD100 = new TH1D("TwoPartVnVsYForKaonsPlusCentrality40-60", "V_{1} vs y_{CM} for K^{+} using Two-Particle Correlations, 40-60% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += TwoPartVnVsCentVsY[1]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[1]->GetBinError(x, y), 2);
        }
    
        HistoD100->SetBinContent(y, Sum / 4);
        HistoD100->SetBinError(y, sqrt(SumErrSq) / 4);
    }




    

    //K-Minus
    TH1D *HistoD101 = new TH1D("TwoPartVnVsPtForKaonsMinusCentrality0-10", "V_{1} vs Pt for K^{-} using Two-Particle Correlations, 0-10% Centrality; Pt; V_{1}", NumPtBins[2], LowerPt[2], UpperPt[2]);
    
    for(int y = 1; y <= NumPtBins[2]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += TwoPartVnVsCentVsPt[2]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[2]->GetBinError(x, y), 2);
        }
    
        HistoD101->SetBinContent(y, Sum / 2);
        HistoD101->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD102 = new TH1D("TwoPartVnVsPtForKaonsMinusCentrality10-40", "V_{1} vs Pt for K^{-} using Two-Particle Correlations, 10-40% Centrality; Pt; V_{1}", NumPtBins[2], LowerPt[2], UpperPt[2]);
    
    for(int y = 1; y <= NumPtBins[2]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += TwoPartVnVsCentVsPt[2]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[2]->GetBinError(x, y), 2);
        }
    
        HistoD102->SetBinContent(y, Sum / 6);
        HistoD102->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD103 = new TH1D("TwoPartVnVsPtForKaonsMinusCentrality40-60", "V_{1} vs Pt for K^{-} using Two-Particle Correlations, 40-60% Centrality; Pt; V_{1}", NumPtBins[2], LowerPt[2], UpperPt[2]);
    
    for(int y = 1; y <= NumPtBins[2]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += TwoPartVnVsCentVsPt[2]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[2]->GetBinError(x, y), 2);
        }
    
        HistoD103->SetBinContent(y, Sum / 4);
        HistoD103->SetBinError(y, sqrt(SumErrSq) / 4);
    }

    TH1D *HistoD104 = new TH1D("TwoPartVnVsYForKaonsMinusCentrality0-10", "V_{1} vs y_{CM} for K^{-} using Two-Particle Correlations, 0-10% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += TwoPartVnVsCentVsY[2]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[2]->GetBinError(x, y), 2);
        }
    
        HistoD104->SetBinContent(y, Sum / 2);
        HistoD104->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD105 = new TH1D("TwoPartVnVsYForKaonsMinusCentrality10-40", "V_{1} vs y_{CM} for K^{-} using Two-Particle Correlations, 10-40% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += TwoPartVnVsCentVsY[2]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[2]->GetBinError(x, y), 2);
        }
    
        HistoD105->SetBinContent(y, Sum / 6);
        HistoD105->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD106 = new TH1D("TwoPartVnVsYForKaonsMinusCentrality40-60", "V_{1} vs y_{CM} for K^{-} using Two-Particle Correlations, 40-60% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += TwoPartVnVsCentVsY[2]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[2]->GetBinError(x, y), 2);
        }
    
        HistoD106->SetBinContent(y, Sum / 4);
        HistoD106->SetBinError(y, sqrt(SumErrSq) / 4);
    }
    






    //Pi-Plus
    TH1D *HistoD107 = new TH1D("TwoPartVnVsPtForPionsPlusCentrality0-10", "V_{1} vs Pt for #pi^{+} using Two-Particle Correlations, 0-10% Centrality; Pt; V_{1}", NumPtBins[3], LowerPt[3], UpperPt[3]);
    
    for(int y = 1; y <= NumPtBins[3]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += TwoPartVnVsCentVsPt[3]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[3]->GetBinError(x, y), 2);
        }
    
        HistoD107->SetBinContent(y, Sum / 2);
        HistoD107->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD108 = new TH1D("TwoPartVnVsPtForPionsPlusCentrality10-40", "V_{1} vs Pt for #pi^{+} using Two-Particle Correlations, 10-40% Centrality; Pt; V_{1}", NumPtBins[3], LowerPt[3], UpperPt[3]);
    
    for(int y = 1; y <= NumPtBins[3]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += TwoPartVnVsCentVsPt[3]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[3]->GetBinError(x, y), 2);
        }
    
        HistoD108->SetBinContent(y, Sum / 6);
        HistoD108->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD109 = new TH1D("TwoPartVnVsPtForPionsPlusCentrality40-60", "V_{1} vs Pt for #pi^{+} using Two-Particle Correlations, 40-60% Centrality; Pt; V_{1}", NumPtBins[3], LowerPt[3], UpperPt[3]);
    
    for(int y = 1; y <= NumPtBins[3]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += TwoPartVnVsCentVsPt[3]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[3]->GetBinError(x, y), 2);
        }
    
        HistoD109->SetBinContent(y, Sum / 4);
        HistoD109->SetBinError(y, sqrt(SumErrSq) / 4);
    }

    TH1D *HistoD110 = new TH1D("TwoPartVnVsYForPionsPlusCentrality0-10", "V_{1} vs y_{CM} for #pi^{+} using Two-Particle Correlations, 0-10% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += TwoPartVnVsCentVsY[3]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[3]->GetBinError(x, y), 2);
        }
    
        HistoD110->SetBinContent(y, Sum / 2);
        HistoD110->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD111 = new TH1D("TwoPartVnVsYForPionsPlusCentrality10-40", "V_{1} vs y_{CM} for #pi^{+} using Two-Particle Correlations, 10-40% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += TwoPartVnVsCentVsY[3]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[3]->GetBinError(x, y), 2);
        }
    
        HistoD111->SetBinContent(y, Sum / 6);
        HistoD111->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD112 = new TH1D("TwoPartVnVsYForPionsPlusCentrality40-60", "V_{1} vs y_{CM} for #pi^{+} using Two-Particle Correlations, 40-60% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += TwoPartVnVsCentVsY[3]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[3]->GetBinError(x, y), 2);
        }
    
        HistoD112->SetBinContent(y, Sum / 4);
        HistoD112->SetBinError(y, sqrt(SumErrSq) / 4);
    }




    

    //Pi-Minus
    TH1D *HistoD113 = new TH1D("TwoPartVnVsPtForPionsMinusCentrality0-10", "V_{1} vs Pt for #pi^{-} using Two-Particle Correlations, 0-10% Centrality; Pt; V_{1}", NumPtBins[4], LowerPt[4], UpperPt[4]);
    
    for(int y = 1; y <= NumPtBins[4]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += TwoPartVnVsCentVsPt[4]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[4]->GetBinError(x, y), 2);
        }
    
        HistoD113->SetBinContent(y, Sum / 2);
        HistoD113->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD114 = new TH1D("TwoPartVnVsPtForPionsMinusCentrality10-40", "V_{1} vs Pt for #pi^{-} using Two-Particle Correlations, 10-40% Centrality; Pt; V_{1}", NumPtBins[4], LowerPt[4], UpperPt[4]);
    
    for(int y = 1; y <= NumPtBins[4]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += TwoPartVnVsCentVsPt[4]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[4]->GetBinError(x, y), 2);
        }
    
        HistoD114->SetBinContent(y, Sum / 6);
        HistoD114->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD115 = new TH1D("TwoPartVnVsPtForPionsMinusCentrality40-60", "V_{1} vs Pt for #pi^{-} using Two-Particle Correlations, 40-60% Centrality; Pt; V_{1}", NumPtBins[4], LowerPt[4], UpperPt[4]);
    
    for(int y = 1; y <= NumPtBins[4]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += TwoPartVnVsCentVsPt[4]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[4]->GetBinError(x, y), 2);
        }
    
        HistoD115->SetBinContent(y, Sum / 4);
        HistoD115->SetBinError(y, sqrt(SumErrSq) / 4);
    }

    TH1D *HistoD116 = new TH1D("TwoPartVnVsYForPionsMinusCentrality0-10", "V_{1} vs y_{CM} for #pi^{-} using Two-Particle Correlations, 0-10% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += TwoPartVnVsCentVsY[4]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[4]->GetBinError(x, y), 2);
        }
    
        HistoD116->SetBinContent(y, Sum / 2);
        HistoD116->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD117 = new TH1D("TwoPartVnVsYForPionsMinusCentrality10-40", "V_{1} vs y_{CM} for #pi^{-} using Two-Particle Correlations, 10-40% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += TwoPartVnVsCentVsY[4]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[4]->GetBinError(x, y), 2);
        }
    
        HistoD117->SetBinContent(y, Sum / 6);
        HistoD117->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD118 = new TH1D("TwoPartVnVsYForPionsMinusCentrality40-60", "V_{1} vs y_{CM} for #pi^{-} using Two-Particle Correlations, 40-60% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += TwoPartVnVsCentVsY[4]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[4]->GetBinError(x, y), 2);
        }
    
        HistoD118->SetBinContent(y, Sum / 4);
        HistoD118->SetBinError(y, sqrt(SumErrSq) / 4);
    }
    
    
    
    
    
    
    
    
    // Deuteron
    TH1D *HistoD119 = new TH1D("TwoPartVnVsPtForDeuteronsCentrality0-10", "V_{1} vs Pt for Deuterons using Two-Particle Correlations, 0-10% Centrality; Pt; V_{1}", NumPtBins[5], LowerPt[5], UpperPt[5]);
    
    for(int y = 1; y <= NumPtBins[5]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += TwoPartVnVsCentVsPt[5]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[5]->GetBinError(x, y), 2);
        }
    
        HistoD119->SetBinContent(y, Sum / 2);
        HistoD119->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD120 = new TH1D("TwoPartVnVsPtForDeuteronsCentrality10-40", "V_{1} vs Pt for Deuterons using Two-Particle Correlations, 10-40% Centrality; Pt; V_{1}", NumPtBins[5], LowerPt[5], UpperPt[5]);
    
    for(int y = 1; y <= NumPtBins[5]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += TwoPartVnVsCentVsPt[5]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[5]->GetBinError(x, y), 2);
        }
    
        HistoD120->SetBinContent(y, Sum / 6);
        HistoD120->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD121 = new TH1D("TwoPartVnVsPtForDeuteronsCentrality40-60", "V_{1} vs Pt for Deuterons using Two-Particle Correlations, 40-60% Centrality; Pt; V_{1}", NumPtBins[5], LowerPt[5], UpperPt[5]);
    
    for(int y = 1; y <= NumPtBins[5]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += TwoPartVnVsCentVsPt[5]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[5]->GetBinError(x, y), 2);
        }
    
        HistoD121->SetBinContent(y, Sum / 4);
        HistoD121->SetBinError(y, sqrt(SumErrSq) / 4);
    }

    TH1D *HistoD122 = new TH1D("TwoPartVnVsYForDeuteronsCentrality0-10", "V_{1} vs y_{CM} for Deuterons using Two-Particle Correlations, 0-10% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += TwoPartVnVsCentVsY[5]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[5]->GetBinError(x, y), 2);
        }
    
        HistoD122->SetBinContent(y, Sum / 2);
        HistoD122->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD123 = new TH1D("TwoPartVnVsYForDeuteronsCentrality10-40", "V_{1} vs y_{CM} for Deuterons using Two-Particle Correlations, 10-40% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += TwoPartVnVsCentVsY[5]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[5]->GetBinError(x, y), 2);
        }
    
        HistoD123->SetBinContent(y, Sum / 6);
        HistoD123->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD124 = new TH1D("TwoPartVnVsYForDeuteronsCentrality40-60", "V_{1} vs y_{CM} for Deuterons using Two-Particle Correlations, 40-60% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += TwoPartVnVsCentVsY[5]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[5]->GetBinError(x, y), 2);
        }
    
        HistoD124->SetBinContent(y, Sum / 4);
        HistoD124->SetBinError(y, sqrt(SumErrSq) / 4);
    }




    // Triton
    TH1D *HistoD125 = new TH1D("TwoPartVnVsPtForTritonsCentrality0-10", "V_{1} vs Pt for Tritons using Two-Particle Correlations, 0-10% Centrality; Pt; V_{1}", NumPtBins[6], LowerPt[6], UpperPt[6]);
    
    for(int y = 1; y <= NumPtBins[6]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += TwoPartVnVsCentVsPt[6]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[6]->GetBinError(x, y), 2);
        }
    
        HistoD125->SetBinContent(y, Sum / 2);
        HistoD125->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD126 = new TH1D("TwoPartVnVsPtForTritonsCentrality10-40", "V_{1} vs Pt for Tritons using Two-Particle Correlations, 10-40% Centrality; Pt; V_{1}", NumPtBins[6], LowerPt[6], UpperPt[6]);
    
    for(int y = 1; y <= NumPtBins[6]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += TwoPartVnVsCentVsPt[6]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[6]->GetBinError(x, y), 2);
        }
    
        HistoD126->SetBinContent(y, Sum / 6);
        HistoD126->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD127 = new TH1D("TwoPartVnVsPtForTritonsCentrality40-60", "V_{1} vs Pt for Tritons using Two-Particle Correlations, 40-60% Centrality; Pt; V_{1}", NumPtBins[6], LowerPt[6], UpperPt[6]);
    
    for(int y = 1; y <= NumPtBins[6]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += TwoPartVnVsCentVsPt[6]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsPt[6]->GetBinError(x, y), 2);
        }
    
        HistoD127->SetBinContent(y, Sum / 4);
        HistoD127->SetBinError(y, sqrt(SumErrSq) / 4);
    }

    TH1D *HistoD128 = new TH1D("TwoPartVnVsYForTritonsCentrality0-10", "V_{1} vs y_{CM} for Tritons using Two-Particle Correlations, 0-10% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += TwoPartVnVsCentVsY[6]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[6]->GetBinError(x, y), 2);
        }
    
        HistoD128->SetBinContent(y, Sum / 2);
        HistoD128->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD129 = new TH1D("TwoPartVnVsYForTritonsCentrality10-40", "V_{1} vs y_{CM} for Tritons using Two-Particle Correlations, 10-40% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += TwoPartVnVsCentVsY[6]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[6]->GetBinError(x, y), 2);
        }
    
        HistoD129->SetBinContent(y, Sum / 6);
        HistoD129->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD130 = new TH1D("TwoPartVnVsYForTritonsCentrality40-60", "V_{1} vs y_{CM} for Tritons using Two-Particle Correlations, 40-60% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += TwoPartVnVsCentVsY[6]->GetBinContent(x, y);
            SumErrSq += pow(TwoPartVnVsCentVsY[6]->GetBinError(x, y), 2);
        }
    
        HistoD130->SetBinContent(y, Sum / 4);
        HistoD130->SetBinError(y, sqrt(SumErrSq) / 4);
    }
    
    
    
    







//Four-Particle
    
    // Proton
    TH1D *HistoD131 = new TH1D("FourPartVnVsPtForProtonsCentrality0-10", "V_{1} vs Pt for Protons using Four-Particle Correlations, 0-10% Centrality; Pt; V_{1}", NumPtBins[0], LowerPt[0], UpperPt[0]);
    
    for(int y = 1; y <= NumPtBins[0]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += FourPartVnVsCentVsPt[0]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[0]->GetBinError(x, y), 2);
        }
    
        HistoD131->SetBinContent(y, Sum / 2);
        HistoD131->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD132 = new TH1D("FourPartVnVsPtForProtonsCentrality10-40", "V_{1} vs Pt for Protons using Four-Particle Correlations, 10-40% Centrality; Pt; V_{1}", NumPtBins[0], LowerPt[0], UpperPt[0]);
    
    for(int y = 1; y <= NumPtBins[0]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += FourPartVnVsCentVsPt[0]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[0]->GetBinError(x, y), 2);
        }
    
        HistoD132->SetBinContent(y, Sum / 6);
        HistoD132->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD133 = new TH1D("FourPartVnVsPtForProtonsCentrality40-60", "V_{1} vs Pt for Protons using Four-Particle Correlations, 40-60% Centrality; Pt; V_{1}", NumPtBins[0], LowerPt[0], UpperPt[0]);
    
    for(int y = 1; y <= NumPtBins[0]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += FourPartVnVsCentVsPt[0]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[0]->GetBinError(x, y), 2);
        }
    
        HistoD133->SetBinContent(y, Sum / 4);
        HistoD133->SetBinError(y, sqrt(SumErrSq) / 4);
    }

    TH1D *HistoD134 = new TH1D("FourPartVnVsYForProtonsCentrality0-10", "V_{1} vs y_{CM} for Protons using Four-Particle Correlations, 0-10% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += FourPartVnVsCentVsY[0]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[0]->GetBinError(x, y), 2);
        }
    
        HistoD134->SetBinContent(y, Sum / 2);
        HistoD134->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD135 = new TH1D("FourPartVnVsYForProtonsCentrality10-40", "V_{1} vs y_{CM} for Protons using  Four-Particle Correlations, 10-40% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += FourPartVnVsCentVsY[0]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[0]->GetBinError(x, y), 2);
        }
    
        HistoD135->SetBinContent(y, Sum / 6);
        HistoD135->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD136 = new TH1D("FourPartVnVsYForProtonsCentrality40-60", "V_{1} vs y_{CM} for Protons using Four-Particle Correlations, 40-60% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += FourPartVnVsCentVsY[0]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[0]->GetBinError(x, y), 2);
        }
    
        HistoD136->SetBinContent(y, Sum / 4);
        HistoD136->SetBinError(y, sqrt(SumErrSq) / 4);
    }







    //K-Plus
    TH1D *HistoD137 = new TH1D("FourPartVnVsPtForKaonsPlusCentrality0-10", "V_{1} vs Pt for K^{+} using Four-Particle Correlations, 0-10% Centrality; Pt; V_{1}", NumPtBins[1], LowerPt[1], UpperPt[1]);
    
    for(int y = 1; y <= NumPtBins[1]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += FourPartVnVsCentVsPt[1]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[1]->GetBinError(x, y), 2);
        }
    
        HistoD137->SetBinContent(y, Sum / 2);
        HistoD137->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD138 = new TH1D("FourPartVnVsPtForKaonsPlusCentrality10-40", "V_{1} vs Pt for K^{+} using Four-Particle Correlations, 10-40% Centrality; Pt; V_{1}", NumPtBins[1], LowerPt[1], UpperPt[1]);
    
    for(int y = 1; y <= NumPtBins[1]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += FourPartVnVsCentVsPt[1]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[1]->GetBinError(x, y), 2);
        }
    
        HistoD138->SetBinContent(y, Sum / 6);
        HistoD138->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD139 = new TH1D("FourPartVnVsPtForKaonsPlusCentrality40-60", "V_{1} vs Pt for K^{+} using Four-Particle Correlations, 40-60% Centrality; Pt; V_{1}", NumPtBins[1], LowerPt[1], UpperPt[1]);
    
    for(int y = 1; y <= NumPtBins[1]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += FourPartVnVsCentVsPt[1]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[1]->GetBinError(x, y), 2);
        }
    
        HistoD139->SetBinContent(y, Sum / 4);
        HistoD139->SetBinError(y, sqrt(SumErrSq) / 4);
    }

    TH1D *HistoD140 = new TH1D("FourPartVnVsYForKaonsPlusCentrality0-10", "V_{1} vs y_{CM} for K^{+} using Four-Particle Correlations, 0-10% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += FourPartVnVsCentVsY[1]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[1]->GetBinError(x, y), 2);
        }
    
        HistoD140->SetBinContent(y, Sum / 2);
        HistoD140->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD141 = new TH1D("FourPartVnVsYForKaonsPlusCentrality10-40", "V_{1} vs y_{CM} for K^{+} using Four-Particle Correlations, 10-40% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += FourPartVnVsCentVsY[1]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[1]->GetBinError(x, y), 2);
        }
    
        HistoD141->SetBinContent(y, Sum / 6);
        HistoD141->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD142 = new TH1D("FourPartVnVsYForKaonsPlusCentrality40-60", "V_{1} vs y_{CM} for K^{+} using Four-Particle Correlations, 40-60% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += FourPartVnVsCentVsY[1]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[1]->GetBinError(x, y), 2);
        }
    
        HistoD142->SetBinContent(y, Sum / 4);
        HistoD142->SetBinError(y, sqrt(SumErrSq) / 4);
    }




    

    //K-Minus
    TH1D *HistoD143 = new TH1D("FourPartVnVsPtForKaonsMinusCentrality0-10", "V_{1} vs Pt for K^{-} using Four-Particle Correlations, 0-10% Centrality; Pt; V_{1}", NumPtBins[2], LowerPt[2], UpperPt[2]);
    
    for(int y = 1; y <= NumPtBins[2]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += FourPartVnVsCentVsPt[2]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[2]->GetBinError(x, y), 2);
        }
    
        HistoD143->SetBinContent(y, Sum / 2);
        HistoD143->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD144 = new TH1D("FourPartVnVsPtForKaonsMinusCentrality10-40", "V_{1} vs Pt for K^{-} using Four-Particle Correlations, 10-40% Centrality; Pt; V_{1}", NumPtBins[2], LowerPt[2], UpperPt[2]);
    
    for(int y = 1; y <= NumPtBins[2]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += FourPartVnVsCentVsPt[2]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[2]->GetBinError(x, y), 2);
        }
    
        HistoD144->SetBinContent(y, Sum / 6);
        HistoD144->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD145 = new TH1D("FourPartVnVsPtForKaonsMinusCentrality40-60", "V_{1} vs Pt for K^{-} using Four-Particle Correlations, 40-60% Centrality; Pt; V_{1}", NumPtBins[2], LowerPt[2], UpperPt[2]);
    
    for(int y = 1; y <= NumPtBins[2]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += FourPartVnVsCentVsPt[2]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[2]->GetBinError(x, y), 2);
        }
    
        HistoD145->SetBinContent(y, Sum / 4);
        HistoD145->SetBinError(y, sqrt(SumErrSq) / 4);
    }

    TH1D *HistoD146 = new TH1D("FourPartVnVsYForKaonsMinusCentrality0-10", "V_{1} vs y_{CM} for K^{-} using Four-Particle Correlations, 0-10% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += FourPartVnVsCentVsY[2]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[2]->GetBinError(x, y), 2);
        }
    
        HistoD146->SetBinContent(y, Sum / 2);
        HistoD146->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD147 = new TH1D("FourPartVnVsYForKaonsMinusCentrality10-40", "V_{1} vs y_{CM} for K^{-} using Four-Particle Correlations, 10-40% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += FourPartVnVsCentVsY[2]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[2]->GetBinError(x, y), 2);
        }
    
        HistoD147->SetBinContent(y, Sum / 6);
        HistoD147->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD148 = new TH1D("FourPartVnVsYForKaonsMinusCentrality40-60", "V_{1} vs y_{CM} for K^{-} using Four-Particle Correlations, 40-60% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += FourPartVnVsCentVsY[2]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[2]->GetBinError(x, y), 2);
        }
    
        HistoD148->SetBinContent(y, Sum / 4);
        HistoD148->SetBinError(y, sqrt(SumErrSq) / 4);
    }
    






    //Pi-Plus
    TH1D *HistoD149 = new TH1D("FourPartVnVsPtForPionsPlusCentrality0-10", "V_{1} vs Pt for #pi^{+} using Four-Particle Correlations, 0-10% Centrality; Pt; V_{1}", NumPtBins[3], LowerPt[3], UpperPt[3]);
    
    for(int y = 1; y <= NumPtBins[3]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += FourPartVnVsCentVsPt[3]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[3]->GetBinError(x, y), 2);
        }
    
        HistoD149->SetBinContent(y, Sum / 2);
        HistoD149->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD150 = new TH1D("FourPartVnVsPtForPionsPlusCentrality10-40", "V_{1} vs Pt for #pi^{+} using Four-Particle Correlations, 10-40% Centrality; Pt; V_{1}", NumPtBins[3], LowerPt[3], UpperPt[3]);
    
    for(int y = 1; y <= NumPtBins[3]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += FourPartVnVsCentVsPt[3]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[3]->GetBinError(x, y), 2);
        }
    
        HistoD150->SetBinContent(y, Sum / 6);
        HistoD150->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD151 = new TH1D("FourPartVnVsPtForPionsPlusCentrality40-60", "V_{1} vs Pt for #pi^{+} using Four-Particle Correlations, 40-60% Centrality; Pt; V_{1}", NumPtBins[3], LowerPt[3], UpperPt[3]);
    
    for(int y = 1; y <= NumPtBins[3]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += FourPartVnVsCentVsPt[3]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[3]->GetBinError(x, y), 2);
        }
    
        HistoD151->SetBinContent(y, Sum / 4);
        HistoD151->SetBinError(y, sqrt(SumErrSq) / 4);
    }

    TH1D *HistoD152 = new TH1D("FourPartVnVsYForPionsPlusCentrality0-10", "V_{1} vs y_{CM} for #pi^{+} using Four-Particle Correlations, 0-10% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += FourPartVnVsCentVsY[3]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[3]->GetBinError(x, y), 2);
        }
    
        HistoD152->SetBinContent(y, Sum / 2);
        HistoD152->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD153 = new TH1D("FourPartVnVsYForPionsPlusCentrality10-40", "V_{1} vs y_{CM} for #pi^{+} using Four-Particle Correlations, 10-40% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += FourPartVnVsCentVsY[3]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[3]->GetBinError(x, y), 2);
        }
    
        HistoD153->SetBinContent(y, Sum / 6);
        HistoD153->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD154 = new TH1D("FourPartVnVsYForPionsPlusCentrality40-60", "V_{1} vs y_{CM} for #pi^{+} using Four-Particle Correlations, 40-60% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += FourPartVnVsCentVsY[3]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[3]->GetBinError(x, y), 2);
        }
    
        HistoD154->SetBinContent(y, Sum / 4);
        HistoD154->SetBinError(y, sqrt(SumErrSq) / 4);
    }




    

    //Pi-Minus
    TH1D *HistoD155 = new TH1D("FourPartVnVsPtForPionsMinusCentrality0-10", "V_{1} vs Pt for #pi^{-} using Four-Particle Correlations, 0-10% Centrality; Pt; V_{1}", NumPtBins[4], LowerPt[4], UpperPt[4]);
    
    for(int y = 1; y <= NumPtBins[4]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += FourPartVnVsCentVsPt[4]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[4]->GetBinError(x, y), 2);
        }
    
        HistoD155->SetBinContent(y, Sum / 2);
        HistoD155->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD156 = new TH1D("FourPartVnVsPtForPionsMinusCentrality10-40", "V_{1} vs Pt for #pi^{-} using Four-Particle Correlations, 10-40% Centrality; Pt; V_{1}", NumPtBins[4], LowerPt[4], UpperPt[4]);
    
    for(int y = 1; y <= NumPtBins[4]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += FourPartVnVsCentVsPt[4]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[4]->GetBinError(x, y), 2);
        }
    
        HistoD156->SetBinContent(y, Sum / 6);
        HistoD156->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD157 = new TH1D("FourPartVnVsPtForPionsMinusCentrality40-60", "V_{1} vs Pt for #pi^{-} using Four-Particle Correlations, 40-60% Centrality; Pt; V_{1}", NumPtBins[4], LowerPt[4], UpperPt[4]);
    
    for(int y = 1; y <= NumPtBins[4]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += FourPartVnVsCentVsPt[4]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[4]->GetBinError(x, y), 2);
        }
    
        HistoD157->SetBinContent(y, Sum / 4);
        HistoD157->SetBinError(y, sqrt(SumErrSq) / 4);
    }

    TH1D *HistoD158 = new TH1D("FourPartVnVsYForPionsMinusCentrality0-10", "V_{1} vs y_{CM} for #pi^{-} using Four-Particle Correlations, 0-10% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += FourPartVnVsCentVsY[4]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[4]->GetBinError(x, y), 2);
        }
    
        HistoD158->SetBinContent(y, Sum / 2);
        HistoD158->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD159 = new TH1D("FourPartVnVsYForPionsMinusCentrality10-40", "V_{1} vs y_{CM} for #pi^{-} using Four-Particle Correlations, 10-40% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += FourPartVnVsCentVsY[4]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[4]->GetBinError(x, y), 2);
        }
    
        HistoD159->SetBinContent(y, Sum / 6);
        HistoD159->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD160 = new TH1D("FourPartVnVsYForPionsMinusCentrality40-60", "V_{1} vs y_{CM} for #pi^{-} using Four-Particle Correlations, 40-60% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += FourPartVnVsCentVsY[4]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[4]->GetBinError(x, y), 2);
        }
    
        HistoD160->SetBinContent(y, Sum / 4);
        HistoD160->SetBinError(y, sqrt(SumErrSq) / 4);
    }
    
    
    
    
    
    
    
    
    // Deuteron
    TH1D *HistoD161 = new TH1D("FourPartVnVsPtForDeuteronsCentrality0-10", "V_{1} vs Pt for Deuterons using Four-Particle Correlations, 0-10% Centrality; Pt; V_{1}", NumPtBins[5], LowerPt[5], UpperPt[5]);
    
    for(int y = 1; y <= NumPtBins[5]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += FourPartVnVsCentVsPt[5]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[5]->GetBinError(x, y), 2);
        }
    
        HistoD161->SetBinContent(y, Sum / 2);
        HistoD161->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD162 = new TH1D("FourPartVnVsPtForDeuteronsCentrality10-40", "V_{1} vs Pt for Deuterons using Four-Particle Correlations, 10-40% Centrality; Pt; V_{1}", NumPtBins[5], LowerPt[5], UpperPt[5]);
    
    for(int y = 1; y <= NumPtBins[5]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += FourPartVnVsCentVsPt[5]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[5]->GetBinError(x, y), 2);
        }
    
        HistoD162->SetBinContent(y, Sum / 6);
        HistoD162->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD163 = new TH1D("FourPartVnVsPtForDeuteronsCentrality40-60", "V_{1} vs Pt for Deuterons using Four-Particle Correlations, 40-60% Centrality; Pt; V_{1}", NumPtBins[5], LowerPt[5], UpperPt[5]);
    
    for(int y = 1; y <= NumPtBins[5]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += FourPartVnVsCentVsPt[5]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[5]->GetBinError(x, y), 2);
        }
    
        HistoD163->SetBinContent(y, Sum / 4);
        HistoD163->SetBinError(y, sqrt(SumErrSq) / 4);
    }

    TH1D *HistoD164 = new TH1D("FourPartVnVsYForDeuteronsCentrality0-10", "V_{1} vs y_{CM} for Deuterons using Four-Particle Correlations, 0-10% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += FourPartVnVsCentVsY[5]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[5]->GetBinError(x, y), 2);
        }
    
        HistoD164->SetBinContent(y, Sum / 2);
        HistoD164->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD165 = new TH1D("FourPartVnVsYForDeuteronsCentrality10-40", "V_{1} vs y_{CM} for Deuterons using Four-Particle Correlations, 10-40% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += FourPartVnVsCentVsY[5]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[5]->GetBinError(x, y), 2);
        }
    
        HistoD165->SetBinContent(y, Sum / 6);
        HistoD165->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD166 = new TH1D("FourPartVnVsYForDeuteronsCentrality40-60", "V_{1} vs y_{CM} for Deuterons using Four-Particle Correlations, 40-60% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += FourPartVnVsCentVsY[5]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[5]->GetBinError(x, y), 2);
        }
    
        HistoD166->SetBinContent(y, Sum / 4);
        HistoD166->SetBinError(y, sqrt(SumErrSq) / 4);
    }




    // Triton
    TH1D *HistoD167 = new TH1D("FourPartVnVsPtForTritonsCentrality0-10", "V_{1} vs Pt for Tritons using Four-Particle Correlations, 0-10% Centrality; Pt; V_{1}", NumPtBins[6], LowerPt[6], UpperPt[6]);
    
    for(int y = 1; y <= NumPtBins[6]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += FourPartVnVsCentVsPt[6]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[6]->GetBinError(x, y), 2);
        }
    
        HistoD167->SetBinContent(y, Sum / 2);
        HistoD167->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD168 = new TH1D("FourPartVnVsPtForTritonsCentrality10-40", "V_{1} vs Pt for Tritons using Four-Particle Correlations, 10-40% Centrality; Pt; V_{1}", NumPtBins[6], LowerPt[6], UpperPt[6]);
    
    for(int y = 1; y <= NumPtBins[6]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += FourPartVnVsCentVsPt[6]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[6]->GetBinError(x, y), 2);
        }
    
        HistoD168->SetBinContent(y, Sum / 6);
        HistoD168->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD169 = new TH1D("FourPartVnVsPtForTritonsCentrality40-60", "V_{1} vs Pt for Tritons using Four-Particle Correlations, 40-60% Centrality; Pt; V_{1}", NumPtBins[6], LowerPt[6], UpperPt[6]);
    
    for(int y = 1; y <= NumPtBins[6]; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += FourPartVnVsCentVsPt[6]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsPt[6]->GetBinError(x, y), 2);
        }
    
        HistoD169->SetBinContent(y, Sum / 4);
        HistoD169->SetBinError(y, sqrt(SumErrSq) / 4);
    }

    TH1D *HistoD170 = new TH1D("FourPartVnVsYForTritonsCentrality0-10", "V_{1} vs y_{CM} for Tritons using Four-Particle Correlations, 0-10% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 1; x <= 2; x++) {
            Sum += FourPartVnVsCentVsY[6]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[6]->GetBinError(x, y), 2);
        }
    
        HistoD170->SetBinContent(y, Sum / 2);
        HistoD170->SetBinError(y, sqrt(SumErrSq) / 2);
    }

        
    TH1D *HistoD171 = new TH1D("FourPartVnVsYForTritonsCentrality10-40", "V_{1} vs y_{CM} for Tritons using Four-Particle Correlations, 10-40% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 3; x <= 8; x++) {
            Sum += FourPartVnVsCentVsY[6]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[6]->GetBinError(x, y), 2);
        }
    
        HistoD171->SetBinContent(y, Sum / 6);
        HistoD171->SetBinError(y, sqrt(SumErrSq) / 6);
    }

    TH1D *HistoD172 = new TH1D("FourPartVnVsYForTritonsCentrality40-60", "V_{1} vs y_{CM} for Tritons using Four-Particle Correlations, 40-60% Centrality; y_{CM}; V_{1}", 10, 0.0, 1.0);
    
    for(int y = 1; y <= 10; y++)
    {
        Double_t Sum = 0;
        Double_t SumErrSq = 0;
    
        for (int x = 9; x <= 12; x++) {
            Sum += FourPartVnVsCentVsY[6]->GetBinContent(x, y);
            SumErrSq += pow(FourPartVnVsCentVsY[6]->GetBinError(x, y), 2);
        }
    
        HistoD172->SetBinContent(y, Sum / 4);
        HistoD172->SetBinError(y, sqrt(SumErrSq) / 4);
    }




      





    HistoD89->SetDirectory(0);
    HistoD90->SetDirectory(0);
    HistoD91->SetDirectory(0);
    HistoD92->SetDirectory(0);
    HistoD93->SetDirectory(0);
    HistoD94->SetDirectory(0);
    HistoD95->SetDirectory(0);
    HistoD96->SetDirectory(0);
    HistoD97->SetDirectory(0);
    HistoD98->SetDirectory(0);
    HistoD99->SetDirectory(0);
    HistoD100->SetDirectory(0);
    HistoD101->SetDirectory(0);
    HistoD102->SetDirectory(0);
    HistoD103->SetDirectory(0);
    HistoD104->SetDirectory(0);
    HistoD105->SetDirectory(0);
    HistoD106->SetDirectory(0);
    HistoD107->SetDirectory(0);
    HistoD108->SetDirectory(0);
    HistoD109->SetDirectory(0);
    HistoD110->SetDirectory(0);
    HistoD111->SetDirectory(0);
    HistoD112->SetDirectory(0);
    HistoD113->SetDirectory(0);
    HistoD114->SetDirectory(0);
    HistoD115->SetDirectory(0);
    HistoD116->SetDirectory(0);
    HistoD117->SetDirectory(0);
    HistoD118->SetDirectory(0);
    HistoD119->SetDirectory(0);
    HistoD120->SetDirectory(0);
    HistoD121->SetDirectory(0);
    HistoD122->SetDirectory(0);
    HistoD123->SetDirectory(0);
    HistoD124->SetDirectory(0);
    HistoD125->SetDirectory(0);
    HistoD126->SetDirectory(0);
    HistoD127->SetDirectory(0);
    HistoD128->SetDirectory(0);
    HistoD129->SetDirectory(0);
    HistoD130->SetDirectory(0);
    HistoD131->SetDirectory(0);
    HistoD132->SetDirectory(0);
    HistoD133->SetDirectory(0);
    HistoD134->SetDirectory(0);
    HistoD135->SetDirectory(0);
    HistoD136->SetDirectory(0);
    HistoD137->SetDirectory(0);
    HistoD138->SetDirectory(0);
    HistoD139->SetDirectory(0);
    HistoD140->SetDirectory(0);
    HistoD141->SetDirectory(0);
    HistoD142->SetDirectory(0);
    HistoD143->SetDirectory(0);
    HistoD144->SetDirectory(0);
    HistoD145->SetDirectory(0);
    HistoD146->SetDirectory(0);
    HistoD147->SetDirectory(0);
    HistoD148->SetDirectory(0);
    HistoD149->SetDirectory(0);
    HistoD150->SetDirectory(0);
    HistoD151->SetDirectory(0);
    HistoD152->SetDirectory(0);
    HistoD153->SetDirectory(0);
    HistoD154->SetDirectory(0);
    HistoD155->SetDirectory(0);
    HistoD156->SetDirectory(0);
    HistoD157->SetDirectory(0);
    HistoD158->SetDirectory(0);
    HistoD159->SetDirectory(0);
    HistoD160->SetDirectory(0);
    HistoD161->SetDirectory(0);
    HistoD162->SetDirectory(0);
    HistoD163->SetDirectory(0);
    HistoD164->SetDirectory(0);
    HistoD165->SetDirectory(0);
    HistoD166->SetDirectory(0);
    HistoD167->SetDirectory(0);
    HistoD168->SetDirectory(0);
    HistoD169->SetDirectory(0);
    HistoD170->SetDirectory(0);
    HistoD171->SetDirectory(0);
    HistoD172->SetDirectory(0);
    for(int i = 0; i < 7; i++)
    {
        TwoPartVnVsCent[i]->SetDirectory(0);
        TwoPartVnVsCentVsPt[i]->SetDirectory(0);
        TwoPartVnVsCentVsY[i]->SetDirectory(0);
        FourPartVnVsCent[i]->SetDirectory(0);
        FourPartVnVsCentVsPt[i]->SetDirectory(0);
        FourPartVnVsCentVsY[i]->SetDirectory(0);
    }





    //TString OutputFileString = TString::Format("/star/data01/pwg/mcgordon/VnFromEPD/V%iHistograms/CumulantNormalFinal.root", nV);
    TString OutputFileString = TString::Format("/star/u/mcgordon/CumulantFinal.root");
    
    TFile *OutputFile = TFile::Open(OutputFileString, "RECREATE");
    OutputFile->cd();




    HistoD89->Write();
    HistoD90->Write();
    HistoD91->Write();
    HistoD92->Write();
    HistoD93->Write();
    HistoD94->Write();
    HistoD95->Write();
    HistoD96->Write();
    HistoD97->Write();
    HistoD98->Write();
    HistoD99->Write();
    HistoD100->Write();
    HistoD101->Write();
    HistoD102->Write();
    HistoD103->Write();
    HistoD104->Write();
    HistoD105->Write();
    HistoD106->Write();
    HistoD107->Write();
    HistoD108->Write();
    HistoD109->Write();
    HistoD110->Write();
    HistoD111->Write();
    HistoD112->Write();
    HistoD113->Write();
    HistoD114->Write();
    HistoD115->Write();
    HistoD116->Write();
    HistoD117->Write();
    HistoD118->Write();
    HistoD119->Write();
    HistoD120->Write();
    HistoD121->Write();
    HistoD122->Write();
    HistoD123->Write();
    HistoD124->Write();
    HistoD125->Write();
    HistoD126->Write();
    HistoD127->Write();
    HistoD128->Write();
    HistoD129->Write();
    HistoD130->Write();
    HistoD131->Write();
    HistoD132->Write();
    HistoD133->Write();
    HistoD134->Write();
    HistoD135->Write();
    HistoD136->Write();
    HistoD137->Write();
    HistoD138->Write();
    HistoD139->Write();
    HistoD140->Write();
    HistoD141->Write();
    HistoD142->Write();
    HistoD143->Write();
    HistoD144->Write();
    HistoD145->Write();
    HistoD146->Write();
    HistoD147->Write();
    HistoD148->Write();
    HistoD149->Write();
    HistoD150->Write();
    HistoD151->Write();
    HistoD152->Write();
    HistoD153->Write();
    HistoD154->Write();
    HistoD155->Write();
    HistoD156->Write();
    HistoD157->Write();
    HistoD158->Write();
    HistoD159->Write();
    HistoD160->Write();
    HistoD161->Write();
    HistoD162->Write();
    HistoD163->Write();
    HistoD164->Write();
    HistoD165->Write();
    HistoD166->Write();
    HistoD167->Write();
    HistoD168->Write();
    HistoD169->Write();
    HistoD170->Write();
    HistoD171->Write();
    HistoD172->Write();
    for(int i = 0; i < 7; i++)
    {
        TwoPartVnVsCent[i]->Write();
        TwoPartVnVsCentVsPt[i]->Write();
        TwoPartVnVsCentVsY[i]->Write();
        FourPartVnVsCent[i]->Write();
        FourPartVnVsCentVsPt[i]->Write();
        FourPartVnVsCentVsY[i]->Write();
    }



    


    InputFile->Close();
    OutputFile->Close();



    delete HistoD89;
    delete HistoD90;
    delete HistoD91;
    delete HistoD92;
    delete HistoD93;
    delete HistoD94;
    delete HistoD95;
    delete HistoD96;
    delete HistoD97;
    delete HistoD98;
    delete HistoD99;
    delete HistoD100;
    delete HistoD101;
    delete HistoD102;
    delete HistoD103;
    delete HistoD104;
    delete HistoD105;
    delete HistoD106;
    delete HistoD107;
    delete HistoD108;
    delete HistoD109;
    delete HistoD110;
    delete HistoD111;
    delete HistoD112;
    delete HistoD113;
    delete HistoD114;
    delete HistoD115;
    delete HistoD116;
    delete HistoD117;
    delete HistoD118;
    delete HistoD119;
    delete HistoD120;
    delete HistoD121;
    delete HistoD122;
    delete HistoD123;
    delete HistoD124;
    delete HistoD125;
    delete HistoD126;
    delete HistoD127;
    delete HistoD128;
    delete HistoD129;
    delete HistoD130;
    delete HistoD131;
    delete HistoD132;
    delete HistoD133;
    delete HistoD134;
    delete HistoD135;
    delete HistoD136;
    delete HistoD137;
    delete HistoD138;
    delete HistoD139;
    delete HistoD140;
    delete HistoD141;
    delete HistoD142;
    delete HistoD143;
    delete HistoD144;
    delete HistoD145;
    delete HistoD146;
    delete HistoD147;
    delete HistoD148;
    delete HistoD149;
    delete HistoD150;
    delete HistoD151;
    delete HistoD152;
    delete HistoD153;
    delete HistoD154;
    delete HistoD155;
    delete HistoD156;
    delete HistoD157;
    delete HistoD158;
    delete HistoD159;
    delete HistoD160;
    delete HistoD161;
    delete HistoD162;
    delete HistoD163;
    delete HistoD164;
    delete HistoD165;
    delete HistoD166;
    delete HistoD167;
    delete HistoD168;
    delete HistoD169;
    delete HistoD170;
    delete HistoD171;
    delete HistoD172;
    for(int i = 0; i < 7; i++)
    {
        delete TwoPartVnVsCent[i];
        delete TwoPartVnVsCentVsPt[i];
        delete TwoPartVnVsCentVsY[i];
        delete FourPartVnVsCent[i];
        delete FourPartVnVsCentVsPt[i];
        delete FourPartVnVsCentVsY[i];
    }
}

