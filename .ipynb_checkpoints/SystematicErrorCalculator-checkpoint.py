#!/usr/bin/env python
# coding: utf-8



import ROOT
import os
import sys
import numpy as np

from math import sqrt, pow

nV = 3
DateNormal = "8-5-23"
DateSystematics = "9-17-2023"




HistogramsNeedingFixing = ["DataVnVsCentralityDeuteronCorrected"]
AllTGraphErrors = []





NormalHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateNormal + "-V" + str(nV) + "-Histograms.root","READ")






RVertex20LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsRVertex20Low.root","READ")

RVertex30LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsRVertex30Low.root","READ")

RVertex20HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsRVertex20High.root","READ")

RVertex30HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsRVertex30High.root","READ")

# ZVertex20LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsZVertex20Low.root","READ")

# ZVertex30LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsZVertex30Low.root","READ")

# ZVertex20HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsZVertex20High.root","READ")

# ZVertex30HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsZVertex30High.root","READ")

DCA20LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsDCA20Low.root","READ")

DCA30LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsDCA30Low.root","READ")

DCA20HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsDCA20High.root","READ")

DCA30HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsDCA30High.root","READ")

NHits20LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNHits20Low.root","READ")

NHits30LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNHits30Low.root","READ")

NHits20HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNHits20High.root","READ")

NHits30HighHistogramFile =  ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNHits30High.root","READ")

NHitsdEdx20HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNHitsdEdx20High.root","READ")

NHitsdEdx30HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNHitsdEdx30High.root","READ")

NHitsFitOverNHitsPoss20LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNHitsFitOverNHitsPoss20Low.root","READ")

NHitsFitOverNHitsPoss30LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNHitsFitOverNHitsPoss30Low.root","READ")

NHitsFitOverNHitsPoss20HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNHitsFitOverNHitsPoss20High.root","READ")

NHitsFitOverNHitsPoss30HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNHitsFitOverNHitsPoss30High.root","READ")

NSigmaPion20LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNSigmaPion20Low.root","READ")

NSigmaPion30LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNSigmaPion30Low.root","READ")

NSigmaPion20HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNSigmaPion20High.root","READ")

NSigmaPion30HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNSigmaPion30High.root","READ")

NSigmaKaon20LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNSigmaKaon20Low.root","READ")

NSigmaKaon30LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNSigmaKaon30Low.root","READ")

NSigmaKaon20HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNSigmaKaon20High.root","READ")

NSigmaKaon30HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNSigmaKaon30High.root","READ")

NSigmaProton20LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNSigmaProton20Low.root","READ")

NSigmaProton30LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNSigmaProton30Low.root","READ")

NSigmaProton20HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNSigmaProton20High.root","READ")

NSigmaProton30HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsNSigmaProton30High.root","READ")

MSquaredPion20LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsMSquaredPion20Low.root","READ")

MSquaredPion30LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsMSquaredPion30Low.root","READ")

MSquaredPion20HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsMSquaredPion20High.root","READ")

MSquaredPion30HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsMSquaredPion30High.root","READ")

MSquaredKaon20LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsMSquaredKaon20Low.root","READ")

MSquaredKaon30LowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsMSquaredKaon30Low.root","READ")

MSquaredKaon20HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsMSquaredKaon20High.root","READ")

MSquaredKaon30HighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsMSquaredKaon30High.root","READ")

OuterEPDLowHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsOuterEPDLow.root","READ")

OuterEPDHighHistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + DateSystematics + "-V" + str(nV) + "-HistogramsOuterEPDHigh.root","READ")




for Histogram in HistogramsNeedingFixing:
    
    NormalHistogram = NormalHistogramFile.Get(Histogram)
    
    
    
    
    
    RVertexHistograms = []
    ZVertexHistograms = []
    DCAHistograms = []
    NHitsHistograms = []
    NHitsdEdxHistograms = []
    NHitsFitOverNHitsPossHistograms = []
    NSigmaPionHistograms = []
    NSigmaKaonHistograms = []
    NSigmaProtonHistograms = []
    MSquaredPionHistograms = []
    MSquaredKaonHistograms = []
    OuterEPDHistograms = []
    

    
    
    
    
    RVertex20LowHistogram = RVertex20LowHistogramFile.Get(Histogram)
    RVertexHistograms.append(RVertex20LowHistogram)
    
    RVertex30LowHistogram = RVertex30LowHistogramFile.Get(Histogram)
    RVertexHistograms.append(RVertex30LowHistogram)
    
    RVertex20HighHistogram = RVertex20HighHistogramFile.Get(Histogram)
    RVertexHistograms.append(RVertex20HighHistogram)
    
    RVertex30HighHistogram = RVertex30HighHistogramFile.Get(Histogram)
    RVertexHistograms.append(RVertex30HighHistogram)
    
    
    
    
    # ZVertex20LowHistogram = ZVertex20LowHistogramFile.Get(Histogram)
    # ZVertexHistograms.append(ZVertex20LowHistogram)
    
    # ZVertex30LowHistogram = ZVertex30LowHistogramFile.Get(Histogram)
    # ZVertexHistograms.append(ZVertex30LowHistogram)
    
    # ZVertex20HighHistogram = ZVertex20HighHistogramFile.Get(Histogram)
    # ZVertexHistograms.append(ZVertex20HighHistogram)
    
    # ZVertex30HighHistogram = ZVertex30HighHistogramFile.Get(Histogram)
    # ZVertexHistograms.append(ZVertex30HighHistogram)
    
    
    
    
    DCA20LowHistogram = DCA20LowHistogramFile.Get(Histogram)
    DCAHistograms.append(DCA20LowHistogram)
    
    DCA30LowHistogram = DCA30LowHistogramFile.Get(Histogram)
    DCAHistograms.append(DCA30LowHistogram)
    
    DCA20HighHistogram = DCA20HighHistogramFile.Get(Histogram)
    DCAHistograms.append(DCA20HighHistogram)
    
    DCA30HighHistogram = DCA30HighHistogramFile.Get(Histogram)
    DCAHistograms.append(DCA30HighHistogram)
    
    
    
    
    NHits20LowHistogram = NHits20LowHistogramFile.Get(Histogram)
    NHitsHistograms.append(NHits20LowHistogram)
    
    NHits30LowHistogram = NHits30LowHistogramFile.Get(Histogram)
    NHitsHistograms.append(NHits30LowHistogram)
    
    NHits20HighHistogram = NHits20HighHistogramFile.Get(Histogram)
    NHitsHistograms.append(NHits20HighHistogram)
    
    NHits30HighHistogram = NHits30HighHistogramFile.Get(Histogram)
    NHitsHistograms.append(NHits30HighHistogram)
    
    
    
    
    NHitsdEdx20HighHistogram = NHitsdEdx20HighHistogramFile.Get(Histogram)
    NHitsdEdxHistograms.append(NHitsdEdx20HighHistogram)
    
    NHitsdEdx30HighHistogram = NHitsdEdx30HighHistogramFile.Get(Histogram)
    NHitsdEdxHistograms.append(NHitsdEdx30HighHistogram)
    
    
    
    
    NHitsFitOverNHitsPoss20LowHistogram =NHitsFitOverNHitsPoss20LowHistogramFile.Get(Histogram)
    NHitsFitOverNHitsPossHistograms.append(NHitsFitOverNHitsPoss20LowHistogram)
    
    NHitsFitOverNHitsPoss30LowHistogram = NHitsFitOverNHitsPoss30LowHistogramFile.Get(Histogram)
    NHitsFitOverNHitsPossHistograms.append(NHitsFitOverNHitsPoss30LowHistogram)
    
    NHitsFitOverNHitsPoss20HighHistogram = NHitsFitOverNHitsPoss20HighHistogramFile.Get(Histogram)
    NHitsFitOverNHitsPossHistograms.append(NHitsFitOverNHitsPoss20HighHistogram)
    
    NHitsFitOverNHitsPoss30HighHistogram = NHitsFitOverNHitsPoss30HighHistogramFile.Get(Histogram)
    NHitsFitOverNHitsPossHistograms.append(NHitsFitOverNHitsPoss30HighHistogram)
    
    
    
    
    NSigmaPion20LowHistogram = NSigmaPion20LowHistogramFile.Get(Histogram)
    NSigmaPionHistograms.append(NSigmaPion20LowHistogram)
    
    NSigmaPion30LowHistogram = NSigmaPion30LowHistogramFile.Get(Histogram)
    NSigmaPionHistograms.append(NSigmaPion30LowHistogram)
    
    NSigmaPion20HighHistogram = NSigmaPion20HighHistogramFile.Get(Histogram)
    NSigmaPionHistograms.append(NSigmaPion20HighHistogram)
    
    NSigmaPion30HighHistogram = NSigmaPion30HighHistogramFile.Get(Histogram)
    NSigmaPionHistograms.append(NSigmaPion30HighHistogram)
    
    
    
    
    NSigmaKaon20LowHistogram = NSigmaKaon20LowHistogramFile.Get(Histogram)
    NSigmaKaonHistograms.append(NSigmaKaon20LowHistogram)
    
    NSigmaKaon30LowHistogram = NSigmaKaon30LowHistogramFile.Get(Histogram)
    NSigmaKaonHistograms.append(NSigmaKaon30LowHistogram)
    
    NSigmaKaon20HighHistogram = NSigmaKaon20HighHistogramFile.Get(Histogram)
    NSigmaKaonHistograms.append(NSigmaKaon20HighHistogram)
    
    NSigmaKaon30HighHistogram = NSigmaKaon30HighHistogramFile.Get(Histogram)
    NSigmaKaonHistograms.append(NSigmaKaon30HighHistogram)
    
    
    
    
    NSigmaProton20LowHistogram = NSigmaProton20LowHistogramFile.Get(Histogram)
    NSigmaProtonHistograms.append(NSigmaProton20LowHistogram)
    
    NSigmaProton30LowHistogram = NSigmaProton30LowHistogramFile.Get(Histogram)
    NSigmaProtonHistograms.append(NSigmaProton30LowHistogram)
    
    NSigmaProton20HighHistogram = NSigmaProton20HighHistogramFile.Get(Histogram)
    NSigmaProtonHistograms.append(NSigmaProton20HighHistogram)
    
    NSigmaProton30HighHistogram = NSigmaProton30HighHistogramFile.Get(Histogram)
    NSigmaProtonHistograms.append(NSigmaProton30HighHistogram)
    
    
    
    
    MSquaredPion20LowHistogram = MSquaredPion20LowHistogramFile.Get(Histogram)
    MSquaredPionHistograms.append(MSquaredPion20LowHistogram)
    
    MSquaredPion30LowHistogram = MSquaredPion30LowHistogramFile.Get(Histogram)
    MSquaredPionHistograms.append(MSquaredPion30LowHistogram)
    
    MSquaredPion20HighHistogram = MSquaredPion20HighHistogramFile.Get(Histogram)
    MSquaredPionHistograms.append(MSquaredPion20HighHistogram)
    
    MSquaredPion30HighHistogram = MSquaredPion30HighHistogramFile.Get(Histogram)
    MSquaredPionHistograms.append(MSquaredPion30HighHistogram)
    
    
    
    
    MSquaredKaon20LowHistogram = MSquaredKaon20LowHistogramFile.Get(Histogram)
    MSquaredKaonHistograms.append(MSquaredKaon20LowHistogram)
    
    MSquaredKaon30LowHistogram = MSquaredKaon30LowHistogramFile.Get(Histogram)
    MSquaredKaonHistograms.append(MSquaredKaon30LowHistogram)
    
    MSquaredKaon20HighHistogram = MSquaredKaon20HighHistogramFile.Get(Histogram)
    MSquaredKaonHistograms.append(MSquaredKaon20HighHistogram)
    
    MSquaredKaon30HighHistogram = MSquaredKaon30HighHistogramFile.Get(Histogram)
    MSquaredKaonHistograms.append(MSquaredKaon30HighHistogram)
    
    
    
    
    OuterEPDLowHistogram = OuterEPDLowHistogramFile.Get(Histogram)
    OuterEPDHistograms.append(OuterEPDLowHistogram)
    
    OuterEPDHighHistogram = OuterEPDHighHistogramFile.Get(Histogram)
    OuterEPDHistograms.append(OuterEPDHighHistogram)
    
    
    
    
    
    SystematicErrorHistograms = [RVertexHistograms, DCAHistograms, NHitsHistograms, NHitsdEdxHistograms, NHitsFitOverNHitsPossHistograms, NSigmaPionHistograms, NSigmaKaonHistograms, NSigmaProtonHistograms, MSquaredPionHistograms, MSquaredKaonHistograms]
    
    
    
    NormalHistogramXValues = []
    NormalHistogramYValues = []

    for index in range(1, NormalHistogram.GetNbinsX() + 1):
        
        NormalHistogramXValue = NormalHistogram.GetBinCenter(index)
        NormalHistogramXValues.append(NormalHistogramXValue)
    
        NormalHistogramYValue = NormalHistogram.GetBinContent(index)
        NormalHistogramYValues.append(NormalHistogramYValue)
    
    print(NormalHistogramXValues)
    print(NormalHistogramYValues)

    
    CurrentTGraphErrorSystematic = ROOT.TGraphErrors(NormalHistogram.GetNbinsX(), np.array(NormalHistogramXValues), np.array(NormalHistogramYValues))
    CurrentTGraphErrorStatistical = ROOT.TGraphErrors(NormalHistogram.GetNbinsX(), np.array(NormalHistogramXValues), np.array(NormalHistogramYValues))

    
    
    
    
    for index in range(1, NormalHistogram.GetNbinsX() + 1):
        
        StatisticalError = NormalHistogram.GetBinError(index)
        
        SignificantVariances = []
        
        for SystematicErrorHistogramGroup in SystematicErrorHistograms:
            
            N = len(SystematicErrorHistogramGroup)
            
            Values = []
            Errors = []
            

            
            
            
            
            for IndividualSystematicErrorHistogram in SystematicErrorHistogramGroup:
                
                Values.append(IndividualSystematicErrorHistogram.GetBinContent(index))
                Errors.append(IndividualSystematicErrorHistogram.GetBinError(index) + StatisticalError)
            
            IndexOfMaximum = Values.index(max(Values))
            IndexOfMinimum = Values.index(min(Values))

            X1 = Values[IndexOfMinimum]
            X2 = Values[IndexOfMaximum]
            DeltaX1 = Errors[IndexOfMinimum]
            DeltaX2 = Errors[IndexOfMaximum]
            if (sqrt(abs(pow(DeltaX2, 2) - pow(DeltaX1, 2)))) == 0:
                continue
            if ((X2 - X1)/sqrt(abs(pow(DeltaX2, 2) - pow(DeltaX1, 2)))) <= 1:
#                 print("Failed")
                continue
            
            
            
            
            
            SumOfValues = 0
            
            for IndividualSystematicErrorHistogram in SystematicErrorHistogramGroup:
                
                SumOfValues += IndividualSystematicErrorHistogram.GetBinContent(index)
                
            Mean = SumOfValues / N

            SumOfVarianceTerms = 0
            
            for IndividualSystematicErrorHistogram in SystematicErrorHistogramGroup:
                
                SumOfVarianceTerms += pow(IndividualSystematicErrorHistogram.GetBinContent(index) - Mean, 2)
                
            SignificantVariances.append(SumOfVarianceTerms / N)
            
            
        SystematicError = sqrt(sum(SignificantVariances))
        print(SystematicError, StatisticalError)
        
        CurrentTGraphErrorSystematic.SetPointError(index, 0, SystematicError)
        CurrentTGraphErrorStatistical.SetPointError(index, 0, StatisticalError)
    
    AllTGraphErrors.append(CurrentTGraphErrorSystematic)
    AllTGraphErrors.append(CurrentTGraphErrorStatistical)
        

        

SystematicErrorCorrectedFile = ROOT.TFile.Open("/star/u/mcgordon/Test.root", "RECREATE")
SystematicErrorCorrectedFile.cd()

for index in range(0,len(AllTGraphErrors)):
    AllTGraphErrors[index].Write()
    
SystematicErrorCorrectedFile.Close()








Canvas = ROOT.TCanvas("Canvas", "", 800, 800)

AllTGraphErrors[1].SetLineColor(ROOT.kBlue)

AllTGraphErrors[1].Draw("AP")

AllTGraphErrors[0].SetLineColor(ROOT.kRed)

AllTGraphErrors[0].Draw("AP SAME")

Canvas.Draw()

Canvas.SaveAs("Test.pdf)")