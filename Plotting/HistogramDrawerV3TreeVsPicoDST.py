#!/usr/bin/env python
# coding: utf-8



import ROOT
import os
import sys

Canvasas = []

Date = '9-15-24'





FirstResolutionPlotFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/R_31_NormalWithTrees.root","READ")
SecondResolutionPlotFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/R_31_Normal.root","READ")

MyFileFirst = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/9-15-24-V3-HistogramNormalNewDataset20000FilesFromTrees.root","READ")
MyFileSecond = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/9-29-24-V3-HistogramNormal.root","READ")
# MyFileSecond = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/1-27-25-V3-HistogramNormalNewDataset20000FilesPicoDST.root","READ")

# SystematicErrorRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/systematicErrors.root","READ")
# CameronSystematicErrorRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/LiteratureFiles/HEPData-ins2702151-SystematicErrors-root.root", "READ")


CentralityXLabels = ["0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60"]


 







Canvas0 = ROOT.TCanvas("Canvas0", "", 800, 800)
Canvas0.cd()

HistogramA = FirstResolutionPlotFile.Get("DataResolution")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetTitle("R_{31}")
HistogramA.GetYaxis().SetTitleOffset(1.5)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.Draw("PE 1 X0")

HistogramB = SecondResolutionPlotFile.Get("DataResolution")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetTitle("R_{31}")
HistogramB.GetYaxis().SetTitleOffset(1.5)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas0.Draw()

Legend0 = ROOT.TLegend(0.7, 0.8, 0.9, 0.9)
Legend0.AddEntry(HistogramA, "With Trees")
Legend0.AddEntry(HistogramB, "With PicoDSTs")
Legend0.Draw()

Canvasas.append(Canvas0)



FirstResolutionPlotFile.Close()
SecondResolutionPlotFile.Close()



'''
Canvas_h_eventCheck = ROOT.TCanvas("Canvas_h_eventCheck", "", 800, 800)
# Change the scope to be within the file
Canvas_h_eventCheck.cd()

HistogramA = MyFileFirst.Get("EventCheck")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramA.SetDirectory(0)

# Build the canvas

# Delete the stats box
HistogramA.SetStats(0)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.Draw("HIST")

HistogramB = MyFileSecond.Get("EventCheck")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramB.SetDirectory(0)

# Delete the stats box
HistogramB.SetStats(0)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("HIST SAME")

# Draw the histogram
Canvas_h_eventCheck.Draw()

LegendEv = ROOT.TLegend(0.6, 0.8, 0.9, 0.9)
LegendEv.AddEntry(HistogramA, "From Trees")
LegendEv.AddEntry(HistogramB, "From PicoDSTs")
LegendEv.Draw()

# Add the histogram to the list of histograms
Canvasas.append(Canvas_h_eventCheck)
'''
####################################################################################################### V3 vs Centrality



Canvas4 = ROOT.TCanvas("Canvas4", "", 800, 800)
Canvas4.cd()

HistogramA = MyFileFirst.Get("DataVnVsCentralityProtonCorrected")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsCentralityProtonCorrected")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas4.Draw()

Legend4 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend4.AddEntry(HistogramA, "New Data")
Legend4.AddEntry(HistogramB, "Old Data")
Legend4.Draw()

Canvasas.append(Canvas4)



Canvas5 = ROOT.TCanvas("Canvas5", "", 800, 800)
Canvas5.cd()

HistogramA = MyFileFirst.Get("DataVnVsCentralityKaonPlusCorrected")

# HistogramA.SetDirectory(0)

# HistogramA.SetStats(0)

# HistogramA.SetLineWidth(10)
# HistogramA.SetMarkerStyle(ROOT.kFullCircle)
# HistogramA.SetMarkerSize(3)
# HistogramA.SetMarkerColor(ROOT.kBlue)

# HistogramA.SetLineColor(ROOT.kBlue)

# HistogramA.GetYaxis().SetTitleOffset(1.5)

# HistogramA.SetAxisRange(-0.02, 0.02, "Y")

NewHistogram1 = ROOT.TH1F("RescaledK+", "V3 vs Centrality for Kaon+; Centrality; V3", 12, 0, 12)

for index in range(1, HistogramA.GetNbinsX() + 1):
    NewHistogram1.SetBinContent(index, HistogramA.GetBinContent(index))
    NewHistogram1.SetBinError(index, HistogramA.GetBinError(index) / 2)
    NewHistogram1.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])

NewHistogram1.SetDirectory(0)

NewHistogram1.SetStats(0)

NewHistogram1.SetLineWidth(10)
NewHistogram1.SetMarkerStyle(ROOT.kFullCircle)
NewHistogram1.SetMarkerSize(3)
NewHistogram1.SetMarkerColor(ROOT.kBlue)

NewHistogram1.SetLineColor(ROOT.kBlue)

NewHistogram1.SetAxisRange(-0.06, 0.04, "Y")

NewHistogram1.Draw("PE 1 X0")

# HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsCentralityKaonPlusCorrected")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas5.Draw()

Legend5 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend5.AddEntry(NewHistogram1, "New Data")
Legend5.AddEntry(HistogramB, "Old Data")
Legend5.Draw()

Canvasas.append(Canvas5)






Canvas6 = ROOT.TCanvas("Canvas6", "", 800, 800)
Canvas6.cd()

HistogramA = MyFileFirst.Get("DataVnVsCentralityKaonMinusCorrected")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsCentralityKaonMinusCorrected")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas6.Draw()

Legend6 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend6.AddEntry(HistogramA, "New Data")
Legend6.AddEntry(HistogramB, "Old Data")
Legend6.Draw()

Canvasas.append(Canvas6)





Canvas7 = ROOT.TCanvas("Canvas7", "", 800, 800)
Canvas7.cd()

HistogramA = MyFileFirst.Get("DataVnVsCentralityPionPlusCorrected")

# HistogramA.SetDirectory(0)

# HistogramA.SetStats(0)

# HistogramA.SetLineWidth(10)
# HistogramA.SetMarkerStyle(ROOT.kFullCircle)
# HistogramA.SetMarkerSize(3)
# HistogramA.SetMarkerColor(ROOT.kBlue)

# HistogramA.SetLineColor(ROOT.kBlue)

# HistogramA.Draw("PE 1 X0")

NewHistogram2 = ROOT.TH1F("RescaledPi+", "V3 vs Centrality for Pion+; Centrality; V3", 12, 0, 12)

for index in range(1, HistogramA.GetNbinsX() + 1):
    NewHistogram2.SetBinContent(index, HistogramA.GetBinContent(index))
    NewHistogram2.SetBinError(index, HistogramA.GetBinError(index) / 2)
    NewHistogram2.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])

NewHistogram2.SetDirectory(0)

NewHistogram2.SetStats(0)

NewHistogram2.SetLineWidth(10)
NewHistogram2.SetMarkerStyle(ROOT.kFullCircle)
NewHistogram2.SetMarkerSize(3)
NewHistogram2.SetMarkerColor(ROOT.kBlue)

NewHistogram2.SetLineColor(ROOT.kBlue)

NewHistogram2.SetAxisRange(-0.02, 0.01, "Y")

NewHistogram2.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsCentralityPionPlusCorrected")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas7.Draw()

Legend7 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend7.AddEntry(HistogramA, "New Data")
Legend7.AddEntry(HistogramA, "Old Data")
Legend7.Draw()

Canvasas.append(Canvas7)




Canvas8 = ROOT.TCanvas("Canvas8", "", 800, 800)
Canvas8.cd()

HistogramA = MyFileFirst.Get("DataVnVsCentralityPionMinusCorrected")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsCentralityPionMinusCorrected")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas8.Draw()

Legend8 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend8.AddEntry(HistogramA, "New Data")
Legend8.AddEntry(HistogramB, "Old Data")
Legend8.Draw()

Canvasas.append(Canvas8)



Canvas9 = ROOT.TCanvas("Canvas9", "", 800, 800)
Canvas9.cd()

HistogramA = MyFileFirst.Get("DataVnVsCentralityDeuteronCorrected")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsCentralityDeuteronCorrected")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

# Legend9 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend9.AddEntry(HistogramA, "New Data")
# Legend9.AddEntry(HistogramB, "Old Data")
# Legend9.Draw()

Canvasas.append(Canvas9)



Canvas10 = ROOT.TCanvas("Canvas10", "", 800, 800)
Canvas10.cd()

HistogramA = MyFileFirst.Get("DataVnVsCentralityTritonCorrected")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsCentralityTritonCorrected")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas10.Draw()

# Legend10 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend10.AddEntry(HistogramA, "New Data")
# Legend10.AddEntry(HistogramB, "Old Data")
# Legend10.Draw()

Canvasas.append(Canvas10)

####################################################################################################### V3 vs Pt


Canvas14 = ROOT.TCanvas("Canvas14", "", 800, 800)
Canvas14.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForProtonsCentrality0-10")

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.Rebin()

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Protons, 0-10% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.07, 0.02, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForProtonsCentrality0-10")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas14.Draw()

Legend14 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend14.AddEntry(HistogramA, "New Data")
Legend14.AddEntry(HistogramB, "Old Data")
Legend14.Draw()

Canvasas.append(Canvas14)







Canvas15 = ROOT.TCanvas("Canvas15", "", 800, 800)
Canvas15.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForProtonsCentrality10-40")

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.Rebin()

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Protons, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.07, 0.02, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForProtonsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas15.Draw()

Legend15 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend15.AddEntry(HistogramA, "New Data")
Legend15.AddEntry(HistogramB, "Old Data")
Legend15.Draw()

Canvasas.append(Canvas15)






Canvas16 = ROOT.TCanvas("Canvas16", "", 800, 800)
Canvas16.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForProtonsCentrality40-60")

HistogramA.Rebin()

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Protons, 0-10% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.07, 0.0, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForProtonsCentrality40-60")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas16.Draw()

Legend16 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend16.AddEntry(HistogramA, "New Data")
Legend16.AddEntry(HistogramB, "Old Data")
Legend16.Draw()

Canvasas.append(Canvas16)






Canvas18 = ROOT.TCanvas("Canvas18", "", 800, 800)
Canvas18.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForKaonsPlusCentrality0-10")

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.Rebin()

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for K+, 0-10% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.04, 0.04, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForKaonsPlusCentrality0-10")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas18.Draw()

Legend18 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend18.AddEntry(HistogramA, "New Data")
Legend18.AddEntry(HistogramB, "Old Data")
Legend18.Draw()

Canvasas.append(Canvas18)







Canvas19 = ROOT.TCanvas("Canvas19", "", 800, 800)
Canvas19.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForKaonsPlusCentrality10-40")

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.Rebin()

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for K+, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.04, 0.04, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForKaonsPlusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas19.Draw()

Legend19 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend19.AddEntry(HistogramA, "New Data")
Legend19.AddEntry(HistogramB, "Old Data")
Legend19.Draw()

Canvasas.append(Canvas19)






Canvas20 = ROOT.TCanvas("Canvas20", "", 800, 800)
Canvas20.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForKaonsPlusCentrality40-60")

HistogramA.Rebin()

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for K+, 40-60% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.04, 0.04, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForKaonsPlusCentrality40-60")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas20.Draw()

Legend20 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend20.AddEntry(HistogramA, "New Data")
Legend20.AddEntry(HistogramB, "Old Data")
Legend20.Draw()

Canvasas.append(Canvas20)





Canvas21 = ROOT.TCanvas("Canvas21", "", 800, 800)
Canvas21.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForKaonsMinusCentrality0-10")

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.Rebin()

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for K-, 0-10% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.2, 0.3, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForKaonsMinusCentrality0-10")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas21.Draw()

Legend21 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend21.AddEntry(HistogramA, "New Data")
Legend21.AddEntry(HistogramB, "Old Data")
Legend21.Draw()

Canvasas.append(Canvas21)







Canvas22 = ROOT.TCanvas("Canvas22", "", 800, 800)
Canvas22.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForKaonsMinusCentrality10-40")

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.Rebin()

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for K-, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.2, 0.3, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForKaonsMinusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas22.Draw()

Legend22 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend22.AddEntry(HistogramA, "New Data")
Legend22.AddEntry(HistogramB, "Old Data")
Legend22.Draw()

Canvasas.append(Canvas22)






Canvas23 = ROOT.TCanvas("Canvas23", "", 800, 800)
Canvas23.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForKaonsMinusCentrality40-60")

HistogramA.Rebin()

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for K-, 40-60% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.2, 0.3, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForKaonsMinusCentrality40-60")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas23.Draw()

Legend23 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend23.AddEntry(HistogramA, "New Data")
Legend23.AddEntry(HistogramB, "Old Data")
Legend23.Draw()

Canvasas.append(Canvas23)




Canvas24 = ROOT.TCanvas("Canvas24", "", 800, 800)
Canvas24.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForPionsPlusCentrality0-10")

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.Rebin()

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Pi+, 0-10% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.05, 0.02, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForPionsPlusCentrality0-10")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas24.Draw()

Legend24 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend24.AddEntry(HistogramA, "New Data")
Legend24.AddEntry(HistogramB, "Old Data")
Legend24.Draw()

Canvasas.append(Canvas24)







Canvas25 = ROOT.TCanvas("Canvas25", "", 800, 800)
Canvas25.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForPionsPlusCentrality10-40")

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.Rebin()

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Pi+, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.05, 0.02, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForPionsPlusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas25.Draw()

Legend25 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend25.AddEntry(HistogramA, "New Data")
Legend25.AddEntry(HistogramB, "Old Data")
Legend25.Draw()

Canvasas.append(Canvas25)






Canvas26 = ROOT.TCanvas("Canvas26", "", 800, 800)
Canvas26.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForPionsPlusCentrality40-60")

HistogramA.Rebin()

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Pi+, 40-60% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.05, 0.02, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForPionsPlusCentrality40-60")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas26.Draw()

Legend26 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend26.AddEntry(HistogramA, "New Data")
Legend26.AddEntry(HistogramB, "Old Data")
Legend26.Draw()

Canvasas.append(Canvas26)





Canvas27 = ROOT.TCanvas("Canvas27", "", 800, 800)
Canvas27.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForPionsMinusCentrality0-10")

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.Rebin()

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Pi-, 0-10% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.02, 0.02, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForPionsMinusCentrality0-10")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas27.Draw()

Legend27 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend27.AddEntry(HistogramA, "New Data")
Legend27.AddEntry(HistogramB, "Old Data")
Legend27.Draw()

Canvasas.append(Canvas27)







Canvas28 = ROOT.TCanvas("Canvas28", "", 800, 800)
Canvas28.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForPionsMinusCentrality10-40")

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.Rebin()

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Pi-, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.02, 0.02, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForPionsMinusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas28.Draw()

Legend28 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend28.AddEntry(HistogramA, "New Data")
Legend28.AddEntry(HistogramB, "Old Data")
Legend28.Draw()

Canvasas.append(Canvas28)






Canvas29 = ROOT.TCanvas("Canvas29", "", 800, 800)
Canvas29.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForPionsMinusCentrality40-60")

HistogramA.Rebin()

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Pi-, 40-60% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.02, 0.02, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForPionsMinusCentrality40-60")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas29.Draw()

Legend29 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend29.AddEntry(HistogramA, "New Data")
Legend29.AddEntry(HistogramB, "Old Data")
Legend29.Draw()

Canvasas.append(Canvas29)




Canvas30 = ROOT.TCanvas("Canvas30", "", 800, 800)
Canvas30.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForDeuteronsCentrality0-10")

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.Rebin()

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Deuterons, 0-10% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.08, 0.01, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForDeuteronsCentrality0-10")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas30.Draw()

Legend30 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend30.AddEntry(HistogramA, "New Data")
Legend30.AddEntry(HistogramB, "Old Data")
Legend30.Draw()

Canvasas.append(Canvas30)







Canvas31 = ROOT.TCanvas("Canvas31", "", 800, 800)
Canvas31.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForDeuteronsCentrality10-40")

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.Rebin()

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Deuterons, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.08, 0.01, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForDeuteronsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas31.Draw()

Legend31 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend31.AddEntry(HistogramA, "New Data")
Legend31.AddEntry(HistogramB, "Old Data")
Legend31.Draw()

Canvasas.append(Canvas31)






Canvas32 = ROOT.TCanvas("Canvas32", "", 800, 800)
Canvas32.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForDeuteronsCentrality40-60")

HistogramA.Rebin()

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Deuterons, 40-60% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.08, 0.01, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForDeuteronsCentrality40-60")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas32.Draw()

Legend32 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend32.AddEntry(HistogramA, "New Data")
Legend32.AddEntry(HistogramB, "Old Data")
Legend32.Draw()

Canvasas.append(Canvas32)




Canvas33 = ROOT.TCanvas("Canvas33", "", 800, 800)
Canvas33.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForTritonsCentrality0-10")

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.Rebin()

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Tritons, 0-10% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.1, 0.1, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForTritonsCentrality0-10")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas33.Draw()

Legend33 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend33.AddEntry(HistogramA, "New Data")
Legend33.AddEntry(HistogramB, "Old Data")
Legend33.Draw()

Canvasas.append(Canvas33)







Canvas34 = ROOT.TCanvas("Canvas34", "", 800, 800)
Canvas34.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForTritonsCentrality10-40")

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.Rebin()

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Tritons, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.1, 0.1, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForTritonsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas34.Draw()

Legend34 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend34.AddEntry(HistogramA, "New Data")
Legend34.AddEntry(HistogramB, "Old Data")
Legend34.Draw()

Canvasas.append(Canvas34)






Canvas35 = ROOT.TCanvas("Canvas35", "", 800, 800)
Canvas35.cd()

HistogramA = MyFileFirst.Get("DataVnVsPtForTritonsCentrality40-60")

HistogramA.Rebin()

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Tritons, 40-60% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.1, 0.1, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsPtForTritonsCentrality40-60")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.Rebin()

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas35.Draw()

Legend35 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend35.AddEntry(HistogramA, "New Data")
Legend35.AddEntry(HistogramB, "Old Data")
Legend35.Draw()

Canvasas.append(Canvas35)



####################################################################################################### V3 vs Rapidity



Canvas1 = ROOT.TCanvas("Canvas1", "", 800, 800)
Canvas1.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForProtonsCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Protons, 0-10% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.01, 0.01, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForProtonsCentrality0-10")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas1.Draw()

Legend1 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend1.AddEntry(HistogramA, "New Data")
Legend1.AddEntry(HistogramB, "Old Data")
Legend1.Draw()

Canvasas.append(Canvas1)



Canvas2 = ROOT.TCanvas("Canvas2", "", 800, 800)
Canvas2.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForProtonsCentrality10-40")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Protons, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.05, 0.0, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForProtonsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas2.Draw()

Legend2 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend2.AddEntry(HistogramA, "New Data")
Legend2.AddEntry(HistogramB, "Old Data")
Legend2.Draw()

Canvasas.append(Canvas2)






Canvas3 = ROOT.TCanvas("Canvas3", "", 800, 800)
Canvas3.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForProtonsCentrality40-60")
#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Protons, 40-60% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.05, 0.0, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForProtonsCentrality40-60")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas3.Draw()

Legend3 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend3.AddEntry(HistogramA, "New Data")
Legend3.AddEntry(HistogramB, "Old Data")
Legend3.Draw()

Canvasas.append(Canvas3)





Canvas1A = ROOT.TCanvas("Canvas1A", "", 800, 800)
Canvas1A.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForKaonsPlusCentrality0-10")
#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Kaons Plus, 0-10% Centrality")

HistogramA.SetAxisRange(-0.03, 0.03, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForKaonsPlusCentrality0-10")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas1A.Draw()

Legend1A = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend1A.AddEntry(HistogramA, "New Data")
Legend1A.AddEntry(HistogramB, "Old Data")
Legend1A.Draw()

Canvasas.append(Canvas1A)









Canvas2A = ROOT.TCanvas("Canvas2A", "", 800, 800)
Canvas2A.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForKaonsPlusCentrality10-40")
#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Kaons Plus, 10-40% Centrality")

HistogramA.SetAxisRange(-0.03, 0.03, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForKaonsPlusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas2A.Draw()

Legend2A = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend2A.AddEntry(HistogramA, "New Data")
Legend2A.AddEntry(HistogramB, "Old Data")
Legend2A.Draw()

Canvasas.append(Canvas2A)






Canvas3A = ROOT.TCanvas("Canvas3A", "", 800, 800)
Canvas3A.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForKaonsPlusCentrality40-60")
#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Kaons Plus, 40-60% Centrality")

HistogramA.SetAxisRange(-0.03, 0.03, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForKaonsPlusCentrality40-60")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas3A.Draw()

Legend3A = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend3A.AddEntry(HistogramA, "New Data")
Legend3A.AddEntry(HistogramB, "Old Data")
Legend3A.Draw()

Canvasas.append(Canvas3A)




Canvas1B = ROOT.TCanvas("Canvas1B", "", 800, 800)
Canvas1B.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForKaonsMinusCentrality0-10")
#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Kaons Minus, 0-10% Centrality")

HistogramA.SetAxisRange(-0.1, 0.1, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForKaonsMinusCentrality0-10")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas1B.Draw()

Legend1B = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend1B.AddEntry(HistogramA, "New Data")
Legend1B.AddEntry(HistogramB, "Old Data")
Legend1B.Draw()

Canvasas.append(Canvas1B)









Canvas2B = ROOT.TCanvas("Canvas2B", "", 800, 800)
Canvas2B.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForKaonsMinusCentrality10-40")
#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Kaons Minus, 10-40% Centrality")

HistogramA.SetAxisRange(-0.1, 0.1, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForKaonsMinusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas2B.Draw()

Legend2B = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend2B.AddEntry(HistogramA, "New Data")
Legend2B.AddEntry(HistogramB, "Old Data")
Legend2B.Draw()

Canvasas.append(Canvas2B)






Canvas3B = ROOT.TCanvas("Canvas3B", "", 800, 800)
Canvas3B.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForKaonsMinusCentrality40-60")
#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Kaons Minus, 40-60% Centrality")

HistogramA.SetAxisRange(-0.1, 0.1, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForKaonsMinusCentrality40-60")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas3B.Draw()

Legend3B = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend3B.AddEntry(HistogramA, "New Data")
Legend3B.AddEntry(HistogramB, "Old Data")
Legend3B.Draw()

Canvasas.append(Canvas3B)




Canvas1C = ROOT.TCanvas("Canvas1C", "", 800, 800)
Canvas1C.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForPionsPlusCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Pions Plus, 0-10% Centrality")

HistogramA.SetAxisRange(-0.01, 0.01, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForPionsPlusCentrality0-10")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas1C.Draw()

Legend1C = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend1C.AddEntry(HistogramA, "New Data")
Legend1C.AddEntry(HistogramB, "Old Data")
Legend1C.Draw()

Canvasas.append(Canvas1C)









Canvas2C = ROOT.TCanvas("Canvas2C", "", 800, 800)
Canvas2C.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForPionsPlusCentrality10-40")
#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Pions Plus, 10-40% Centrality")

HistogramA.SetAxisRange(-0.01, 0.01, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForPionsPlusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas2C.Draw()

Legend2C = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend2C.AddEntry(HistogramA, "New Data")
Legend2C.AddEntry(HistogramB, "Old Data")
Legend2C.Draw()

Canvasas.append(Canvas2C)






Canvas3C = ROOT.TCanvas("Canvas3C", "", 800, 800)
Canvas3C.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForPionsPlusCentrality40-60")
#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Pions Plus, 40-60% Centrality")

HistogramA.SetAxisRange(-0.01, 0.01, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForPionsPlusCentrality40-60")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas3C.Draw()

Legend3C = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend3C.AddEntry(HistogramA, "New Data")
Legend3C.AddEntry(HistogramB, "Old Data")
Legend3C.Draw()

Canvasas.append(Canvas3C)




Canvas1D = ROOT.TCanvas("Canvas1D", "", 800, 800)
Canvas1D.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForPionsMinusCentrality0-10")
#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Pions Minus, 0-10% Centrality")

HistogramA.SetAxisRange(-0.01, 0.003, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForPionsMinusCentrality0-10")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas1D.Draw()

Legend1D = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend1D.AddEntry(HistogramA, "New Data")
Legend1D.AddEntry(HistogramB, "Old Data")
Legend1D.Draw()

Canvasas.append(Canvas1D)









Canvas2D = ROOT.TCanvas("Canvas2D", "", 800, 800)
Canvas2D.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForPionsMinusCentrality10-40")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Pions Minus, 10-40% Centrality")

HistogramA.SetAxisRange(-0.01, 0.003, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForPionsMinusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas2D.Draw()

Legend2D = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend2D.AddEntry(HistogramA, "New Data")
Legend2D.AddEntry(HistogramB, "Old Data")
Legend2D.Draw()

Canvasas.append(Canvas2D)






Canvas3D = ROOT.TCanvas("Canvas3D", "", 800, 800)
Canvas3D.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForPionsMinusCentrality40-60")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Pions Minus, 40-60% Centrality")

HistogramA.SetAxisRange(-0.01, 0.003, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForPionsMinusCentrality40-60")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas3D.Draw()

Legend3D = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend3D.AddEntry(HistogramA, "New Data")
Legend3D.AddEntry(HistogramB, "Old Data")
Legend3D.Draw()

Canvasas.append(Canvas3D)





Canvas1E = ROOT.TCanvas("Canvas1E", "", 800, 800)
Canvas1E.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForDeuteronsCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Deuterons, 0-10% Centrality")

HistogramA.SetAxisRange(-0.1, 0.003, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForDeuteronsCentrality0-10")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas1E.Draw()

Legend1E = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend1E.AddEntry(HistogramA, "New Data")
Legend1E.AddEntry(HistogramB, "Old Data")
Legend1E.Draw()

Canvasas.append(Canvas1E)




Canvas2E = ROOT.TCanvas("Canvas2E", "", 800, 800)
Canvas2E.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForDeuteronsCentrality10-40")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Deuterons, 10-40% Centrality")

HistogramA.SetAxisRange(-0.1, 0.003, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForDeuteronsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas2E.Draw()

Legend2E = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend2E.AddEntry(HistogramA, "New Data")
Legend2E.AddEntry(HistogramB, "Old Data")
Legend2E.Draw()

Canvasas.append(Canvas2E)






Canvas3E = ROOT.TCanvas("Canvas3E", "", 800, 800)
Canvas3E.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForDeuteronsCentrality40-60")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Deuterons, 40-60% Centrality")

HistogramA.SetAxisRange(-0.1, 0.003, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForDeuteronsCentrality40-60")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas3E.Draw()

Legend3E = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend3E.AddEntry(HistogramA, "New Data")
Legend3E.AddEntry(HistogramB, "Old Data")
Legend3E.Draw()

Canvasas.append(Canvas3E)






Canvas1F = ROOT.TCanvas("Canvas1F", "", 800, 800)
Canvas1F.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForTritonsCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetAxisRange(-0.1, 0.05, "Y")

HistogramA.SetTitle("V3 vs Y for Tritons, 0-10% Centrality")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForTritonsCentrality0-10")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas1F.Draw()

Legend1F = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend1F.AddEntry(HistogramA, "New Data")
Legend1F.AddEntry(HistogramB, "Old Data")
Legend1F.Draw()

Canvasas.append(Canvas1F)









Canvas2F = ROOT.TCanvas("Canvas2F", "", 800, 800)
Canvas2F.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForTritonsCentrality10-40")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Tritons, 10-40% Centrality")

HistogramA.SetAxisRange(-0.1, 0.05, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForTritonsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas2F.Draw()

Legend2F = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend2F.AddEntry(HistogramA, "New Data")
Legend2F.AddEntry(HistogramB, "Old Data")
Legend2F.Draw()

Canvasas.append(Canvas2F)






Canvas3F = ROOT.TCanvas("Canvas3F", "", 800, 800)
Canvas3F.cd()

HistogramA = MyFileFirst.Get("DataVnVsYForTritonsCentrality40-60")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Tritons, 40-60% Centrality")

HistogramA.SetAxisRange(-0.1, 0.05, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYForTritonsCentrality40-60")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas3F.Draw()

Legend3F = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend3F.AddEntry(HistogramA, "New Data")
Legend3F.AddEntry(HistogramB, "Old Data")
Legend3F.Draw()

Canvasas.append(Canvas3F)






####################################################################################################### Vn vs Y Symmetric Plots


Canvas11 = ROOT.TCanvas("Canvas11", "", 800, 800)
Canvas11.cd()

HistogramA = MyFileFirst.Get("DataVnVsYSymmetricForProtonsCentrality0-10")
#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y Symmetric for Protons, 0-10% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYSymmetricForProtonsCentrality0-10")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas11.Draw()

Legend11 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend11.AddEntry(HistogramA, "New Data")
Legend11.AddEntry(HistogramB, "Old Data")
Legend11.Draw()

Canvasas.append(Canvas11)







Canvas12 = ROOT.TCanvas("Canvas12", "", 800, 800)
Canvas12.cd()

HistogramA = MyFileFirst.Get("DataVnVsYSymmetricForProtonsCentrality10-40")
#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y Symmetric for Protons, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYSymmetricForProtonsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas12.Draw()

Legend12 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend12.AddEntry(HistogramA, "New Data")
Legend12.AddEntry(HistogramB, "Old Data")
Legend12.Draw()

Canvasas.append(Canvas12)






Canvas13 = ROOT.TCanvas("Canvas13", "", 800, 800)
Canvas13.cd()

HistogramA = MyFileFirst.Get("DataVnVsYSymmetricForProtonsCentrality40-60")
#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y Symmetric for Protons, 40-60% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.Draw("PE 1 X0")

HistogramB = MyFileSecond.Get("DataVnVsYSymmetricForProtonsCentrality40-60")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas13.Draw()

Legend13 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend13.AddEntry(HistogramA, "New Data")
Legend13.AddEntry(HistogramB, "Old Data")
Legend13.Draw()

Canvasas.append(Canvas13)


####################################################################################################### Scaling Plots
'''

CanvasScalingCentrality = ROOT.TCanvas("CanvasScalingCentrality", "", 800, 800)
CanvasScalingCentrality.cd()

HistogramProton1 = MyFile.Get("DataVnVsCentralityProtonCorrected")

HistogramProton1.SetDirectory(0)

HistogramProton1.SetStats(0)

HistogramProton1.SetTitle("Scaling Plot of p, d and t (V3 vs Centrality)")

HistogramProton1.GetYaxis().SetTitle("V3 / A")

HistogramProton1.GetYaxis().SetTitleOffset(1.5)

HistogramProton1.SetLineWidth(15)
HistogramProton1.SetMarkerStyle(ROOT.kFullSquare)
HistogramProton1.SetMarkerSize(3)
HistogramProton1.SetMarkerColor(ROOT.kRed)

HistogramProton1.SetLineColor(ROOT.kRed)

HistogramProton1.SetAxisRange(-0.02, 0.01, "Y")

HistogramProton1.Draw("PE 1 X0")

Histogram = MyFile.Get("DataVnVsCentralityDeuteronCorrected")

NewHistogramScaled1 = ROOT.TH1D("DataVnVsCentralityDeuteronCorrectedScaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 12, 0, 12)

NewHistogramScaled1.SetDirectory(0)

NewHistogramScaled1.SetStats(0)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled1.SetBinContent(index, Histogram.GetBinContent(index) / 2)
    NewHistogramScaled1.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled1.SetLineWidth(10)
NewHistogramScaled1.SetMarkerStyle(ROOT.kFullCircle)
NewHistogramScaled1.SetMarkerSize(3)
NewHistogramScaled1.SetMarkerColor(ROOT.kBlue)

NewHistogramScaled1.SetLineColor(ROOT.kBlue)

NewHistogramScaled1.SetAxisRange(-0.02, 0.01, "Y")

NewHistogramScaled1.Draw("PE 1 X0 SAME")

Histogram = MyFile.Get("DataVnVsCentralityTritonCorrected")

NewHistogramScaled2 = ROOT.TH1D("DataVnVsCentralityTritonCorrectedScaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 12, 0, 12)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled2.SetBinContent(index, Histogram.GetBinContent(index) / 3)
    NewHistogramScaled2.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled2.SetDirectory(0)

NewHistogramScaled2.SetStats(0)
    
NewHistogramScaled2.SetLineWidth(5)
NewHistogramScaled2.SetMarkerStyle(ROOT.kFullTriangleDown)
NewHistogramScaled2.SetMarkerSize(3)
NewHistogramScaled2.SetMarkerColor(ROOT.kGreen)

NewHistogramScaled2.SetLineColor(ROOT.kGreen)

NewHistogramScaled2.SetAxisRange(-0.02, 0.01, "Y")

NewHistogramScaled2.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityTritonCorrected_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityTritonCorrected_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

CanvasScalingCentrality.Draw()

LegendScalingCentrality = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
LegendScalingCentrality.AddEntry(HistogramProton1, "Protons")
LegendScalingCentrality.AddEntry(NewHistogramScaled1, "Deuterons")
LegendScalingCentrality.AddEntry(NewHistogramScaled2, "Tritons")
LegendScalingCentrality.Draw()

Canvasas.append(CanvasScalingCentrality)







CanvasScalingPt0_10 = ROOT.TCanvas("CanvasScalingPt0_10", "", 800, 800)
CanvasScalingPt0_10.cd()

HistogramProton2 = MyFile.Get("DataVnVsPtForProtonsCentrality0-10")

HistogramProton2.SetDirectory(0)

HistogramProton2.SetStats(0)

HistogramProton2.SetTitle("Scaling Plot of p, d and t (V3 vs Pt, 0-10% Centrality)")

HistogramProton2.GetYaxis().SetTitle("V3 / A")

HistogramProton2.GetYaxis().SetTitleOffset(1.5)

HistogramProton2.SetLineWidth(15)
HistogramProton2.SetMarkerStyle(ROOT.kFullSquare)
HistogramProton2.SetMarkerSize(3)
HistogramProton2.SetMarkerColor(ROOT.kRed)

HistogramProton2.SetLineColor(ROOT.kRed)

# HistogramProton2.SetAxisRange(-0.02, 0.01, "Y")

HistogramProton2.Draw("PE 1 X0")

Histogram = MyFile.Get("DataVnVsPtForDeuteronsCentrality0-10")

NewHistogramScaled3 = ROOT.TH1D("DataVnVsPtForDeuteronsCentrality0-10Scaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 12, 0, 12)

NewHistogramScaled3.SetDirectory(0)

NewHistogramScaled3.SetStats(0)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled3.SetBinContent(index, Histogram.GetBinContent(index) / 2)
    NewHistogramScaled3.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled3.SetLineWidth(10)
NewHistogramScaled3.SetMarkerStyle(ROOT.kFullCircle)
NewHistogramScaled3.SetMarkerSize(3)
NewHistogramScaled3.SetMarkerColor(ROOT.kBlue)

NewHistogramScaled3.SetLineColor(ROOT.kBlue)

NewHistogramScaled3.Draw("PE 1 X0 SAME")

Histogram = MyFile.Get("DataVnVsPtForTritonsCentrality0-10")

NewHistogramScaled4 = ROOT.TH1D("DataVnVsPtForTritonsCentrality0-10Scaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 12, 0, 12)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled4.SetBinContent(index, Histogram.GetBinContent(index) / 3)
    NewHistogramScaled4.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled4.SetDirectory(0)

NewHistogramScaled4.SetStats(0)
    
NewHistogramScaled4.SetLineWidth(5)
NewHistogramScaled4.SetMarkerStyle(ROOT.kFullTriangleDown)
NewHistogramScaled4.SetMarkerSize(3)
NewHistogramScaled4.SetMarkerColor(ROOT.kGreen)

NewHistogramScaled4.SetLineColor(ROOT.kGreen)

NewHistogramScaled4.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityTritonCorrected_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityTritonCorrected_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

CanvasScalingPt0_10.Draw()

LegendScalingPt0_10 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
LegendScalingPt0_10.AddEntry(HistogramProton2, "Protons")
LegendScalingPt0_10.AddEntry(NewHistogramScaled3, "Deuterons")
LegendScalingPt0_10.AddEntry(NewHistogramScaled4, "Tritons")
LegendScalingPt0_10.Draw()

Canvasas.append(CanvasScalingPt0_10)






CanvasScalingPt10_40 = ROOT.TCanvas("CanvasScalingPt10_40", "", 800, 800)
CanvasScalingPt10_40.cd()

HistogramProton3 = MyFile.Get("DataVnVsPtForProtonsCentrality10-40")

HistogramProton3.SetDirectory(0)

HistogramProton3.SetStats(0)

HistogramProton3.SetTitle("Scaling Plot of p, d and t (V3 vs Pt, 10-40% Centrality)")

HistogramProton3.GetYaxis().SetTitle("V3 / A")

HistogramProton3.GetYaxis().SetTitleOffset(1.5)

HistogramProton3.SetLineWidth(15)
HistogramProton3.SetMarkerStyle(ROOT.kFullSquare)
HistogramProton3.SetMarkerSize(3)
HistogramProton3.SetMarkerColor(ROOT.kRed)

HistogramProton3.SetLineColor(ROOT.kRed)

HistogramProton3.SetAxisRange(-0.02, 0.01, "Y")

HistogramProton3.Draw("PE 1 X0")

Histogram = MyFile.Get("DataVnVsPtForDeuteronsCentrality10-40")

NewHistogramScaled5 = ROOT.TH1D("DataVnVsPtForDeuteronsCentrality10-40Scaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 12, 0, 12)

NewHistogramScaled5.SetDirectory(0)

NewHistogramScaled5.SetStats(0)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled5.SetBinContent(index, Histogram.GetBinContent(index) / 2)
    NewHistogramScaled5.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled5.SetLineWidth(10)
NewHistogramScaled5.SetMarkerStyle(ROOT.kFullCircle)
NewHistogramScaled5.SetMarkerSize(3)
NewHistogramScaled5.SetMarkerColor(ROOT.kBlue)

NewHistogramScaled5.SetLineColor(ROOT.kBlue)

NewHistogramScaled5.Draw("PE 1 X0 SAME")

Histogram = MyFile.Get("DataVnVsPtForTritonsCentrality10-40")

NewHistogramScaled6 = ROOT.TH1D("DataVnVsPtForTritonsCentrality10-40Scaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 12, 0, 12)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled6.SetBinContent(index, Histogram.GetBinContent(index) / 3)
    NewHistogramScaled6.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled6.SetDirectory(0)

NewHistogramScaled6.SetStats(0)
    
NewHistogramScaled6.SetLineWidth(5)
NewHistogramScaled6.SetMarkerStyle(ROOT.kFullTriangleDown)
NewHistogramScaled6.SetMarkerSize(3)
NewHistogramScaled6.SetMarkerColor(ROOT.kGreen)

NewHistogramScaled6.SetLineColor(ROOT.kGreen)

NewHistogramScaled6.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityTritonCorrected_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityTritonCorrected_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

CanvasScalingPt10_40.Draw()

LegendScalingPt10_40 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
LegendScalingPt10_40.AddEntry(HistogramProton3, "Protons")
LegendScalingPt10_40.AddEntry(NewHistogramScaled5, "Deuterons")
LegendScalingPt10_40.AddEntry(NewHistogramScaled6, "Tritons")
LegendScalingPt10_40.Draw()

Canvasas.append(CanvasScalingPt10_40)






CanvasScalingPt40_60 = ROOT.TCanvas("CanvasScalingPt40_60", "", 800, 800)
CanvasScalingPt40_60.cd()

HistogramProton4 = MyFile.Get("DataVnVsPtForProtonsCentrality40-60")

HistogramProton4.SetDirectory(0)

HistogramProton4.SetStats(0)

HistogramProton4.SetTitle("Scaling Plot of p, d and t (V3 vs Pt, 40-60% Centrality)")

HistogramProton4.GetYaxis().SetTitle("V3 / A")

HistogramProton4.GetYaxis().SetTitleOffset(1.5)

HistogramProton4.SetLineWidth(15)
HistogramProton4.SetMarkerStyle(ROOT.kFullSquare)
HistogramProton4.SetMarkerSize(3)
HistogramProton4.SetMarkerColor(ROOT.kRed)

HistogramProton4.SetLineColor(ROOT.kRed)

HistogramProton4.SetAxisRange(-0.02, 0.01, "Y")

HistogramProton4.Draw("PE 1 X0")

Histogram = MyFile.Get("DataVnVsPtForDeuteronsCentrality40-60")

NewHistogramScaled7 = ROOT.TH1D("DataVnVsPtForDeuteronsCentrality40-60Scaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 12, 0, 12)

NewHistogramScaled7.SetDirectory(0)

NewHistogramScaled7.SetStats(0)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled7.SetBinContent(index, Histogram.GetBinContent(index) / 2)
    NewHistogramScaled7.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled7.SetLineWidth(10)
NewHistogramScaled7.SetMarkerStyle(ROOT.kFullCircle)
NewHistogramScaled7.SetMarkerSize(3)
NewHistogramScaled7.SetMarkerColor(ROOT.kBlue)

NewHistogramScaled7.SetLineColor(ROOT.kBlue)

NewHistogramScaled7.Draw("PE 1 X0 SAME")

Histogram = MyFile.Get("DataVnVsPtForTritonsCentrality40-60")

NewHistogramScaled8 = ROOT.TH1D("DataVnVsPtForTritonsCentrality40-60Scaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 12, 0, 12)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled8.SetBinContent(index, Histogram.GetBinContent(index) / 3)
    NewHistogramScaled8.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled8.SetDirectory(0)

NewHistogramScaled8.SetStats(0)
    
NewHistogramScaled8.SetLineWidth(5)
NewHistogramScaled8.SetMarkerStyle(ROOT.kFullTriangleDown)
NewHistogramScaled8.SetMarkerSize(3)
NewHistogramScaled8.SetMarkerColor(ROOT.kGreen)

NewHistogramScaled8.SetLineColor(ROOT.kGreen)

NewHistogramScaled8.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityTritonCorrected_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityTritonCorrected_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

CanvasScalingPt40_60.Draw()

LegendScalingPt40_60 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
LegendScalingPt40_60.AddEntry(HistogramProton4, "Protons")
LegendScalingPt40_60.AddEntry(NewHistogramScaled7, "Deuterons")
LegendScalingPt40_60.AddEntry(NewHistogramScaled8, "Tritons")
LegendScalingPt40_60.Draw()

Canvasas.append(CanvasScalingPt40_60)






CanvasScalingY0_10 = ROOT.TCanvas("CanvasScalingY0_10", "", 800, 800)
CanvasScalingY0_10.cd()

HistogramProton5 = MyFile.Get("DataVnVsYForProtonsCentrality0-10")

HistogramProton5.SetDirectory(0)

HistogramProton5.SetStats(0)

HistogramProton5.SetTitle("Scaling Plot of p, d and t (V3 vs Y, 0-10% Centrality)")

HistogramProton5.GetYaxis().SetTitle("V3 / A")

HistogramProton5.GetYaxis().SetTitleOffset(1.5)

HistogramProton5.SetLineWidth(15)
HistogramProton5.SetMarkerStyle(ROOT.kFullSquare)
HistogramProton5.SetMarkerSize(3)
HistogramProton5.SetMarkerColor(ROOT.kRed)

HistogramProton5.SetLineColor(ROOT.kRed)

HistogramProton5.SetAxisRange(-0.05, 0.01, "Y")

HistogramProton5.Draw("PE 1 X0")

Histogram = MyFile.Get("DataVnVsYForDeuteronsCentrality0-10")

NewHistogramScaled9 = ROOT.TH1D("DataVnVsYForDeuteronsCentrality0-10Scaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 10, 0, 1)

NewHistogramScaled9.SetDirectory(0)

NewHistogramScaled9.SetStats(0)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled9.SetBinContent(index, Histogram.GetBinContent(index) / 2)
    NewHistogramScaled9.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled9.SetLineWidth(10)
NewHistogramScaled9.SetMarkerStyle(ROOT.kFullCircle)
NewHistogramScaled9.SetMarkerSize(3)
NewHistogramScaled9.SetMarkerColor(ROOT.kBlue)

NewHistogramScaled9.SetLineColor(ROOT.kBlue)

NewHistogramScaled9.Draw("PE 1 X0 SAME")

Histogram = MyFile.Get("DataVnVsYForTritonsCentrality0-10")

NewHistogramScaled10 = ROOT.TH1D("DataVnVsYForTritonsCentrality0-10Scaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 10, 0, 1)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled10.SetBinContent(index, Histogram.GetBinContent(index) / 3)
    NewHistogramScaled10.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled10.SetDirectory(0)

NewHistogramScaled10.SetStats(0)
    
NewHistogramScaled10.SetLineWidth(5)
NewHistogramScaled10.SetMarkerStyle(ROOT.kFullTriangleDown)
NewHistogramScaled10.SetMarkerSize(3)
NewHistogramScaled10.SetMarkerColor(ROOT.kGreen)

NewHistogramScaled10.SetLineColor(ROOT.kGreen)

NewHistogramScaled10.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityTritonCorrected_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityTritonCorrected_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

CanvasScalingY0_10.Draw()

LegendScalingY0_10 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
LegendScalingY0_10.AddEntry(HistogramProton5, "Protons")
LegendScalingY0_10.AddEntry(NewHistogramScaled9, "Deuterons")
LegendScalingY0_10.AddEntry(NewHistogramScaled10, "Tritons")
LegendScalingY0_10.Draw()

Canvasas.append(CanvasScalingY0_10)






CanvasScalingY10_40 = ROOT.TCanvas("CanvasScalingY10_40", "", 800, 800)
CanvasScalingY10_40.cd()

HistogramProton6 = MyFile.Get("DataVnVsYForProtonsCentrality10-40")

HistogramProton6.SetDirectory(0)

HistogramProton6.SetStats(0)

HistogramProton6.SetTitle("Scaling Plot of p, d and t (V3 vs Y, 10-40% Centrality)")

HistogramProton6.GetYaxis().SetTitle("V3 / A")

HistogramProton6.GetYaxis().SetTitleOffset(1.5)

HistogramProton6.SetLineWidth(15)
HistogramProton6.SetMarkerStyle(ROOT.kFullSquare)
HistogramProton6.SetMarkerSize(3)
HistogramProton6.SetMarkerColor(ROOT.kRed)

HistogramProton6.SetLineColor(ROOT.kRed)

HistogramProton6.SetAxisRange(-0.05, 0.01, "Y")

HistogramProton6.Draw("PE 1 X0")

Histogram = MyFile.Get("DataVnVsYForDeuteronsCentrality10-40")

NewHistogramScaled11 = ROOT.TH1D("DataVnVsYForDeuteronsCentrality10-40Scaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 10, 0, 1)

NewHistogramScaled11.SetDirectory(0)

NewHistogramScaled11.SetStats(0)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled11.SetBinContent(index, Histogram.GetBinContent(index) / 2)
    NewHistogramScaled11.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled11.SetLineWidth(10)
NewHistogramScaled11.SetMarkerStyle(ROOT.kFullCircle)
NewHistogramScaled11.SetMarkerSize(3)
NewHistogramScaled11.SetMarkerColor(ROOT.kBlue)

NewHistogramScaled11.SetLineColor(ROOT.kBlue)

NewHistogramScaled11.Draw("PE 1 X0 SAME")

Histogram = MyFile.Get("DataVnVsYForTritonsCentrality10-40")

NewHistogramScaled12 = ROOT.TH1D("DataVnVsYForTritonsCentrality10-40Scaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 10, 0, 1)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled12.SetBinContent(index, Histogram.GetBinContent(index) / 3)
    NewHistogramScaled12.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled12.SetDirectory(0)

NewHistogramScaled12.SetStats(0)
    
NewHistogramScaled12.SetLineWidth(5)
NewHistogramScaled12.SetMarkerStyle(ROOT.kFullTriangleDown)
NewHistogramScaled12.SetMarkerSize(3)
NewHistogramScaled12.SetMarkerColor(ROOT.kGreen)

NewHistogramScaled12.SetLineColor(ROOT.kGreen)

NewHistogramScaled12.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityTritonCorrected_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityTritonCorrected_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

CanvasScalingY10_40.Draw()

LegendScalingY10_40 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
LegendScalingY10_40.AddEntry(HistogramProton6, "Protons")
LegendScalingY10_40.AddEntry(NewHistogramScaled11, "Deuterons")
LegendScalingY10_40.AddEntry(NewHistogramScaled12, "Tritons")
LegendScalingY10_40.Draw()

Canvasas.append(CanvasScalingY10_40)






CanvasScalingY40_60 = ROOT.TCanvas("CanvasScalingY40_60", "", 800, 800)
CanvasScalingY40_60.cd()

HistogramProton7 = MyFile.Get("DataVnVsYForProtonsCentrality40-60")

HistogramProton7.SetDirectory(0)

HistogramProton7.SetStats(0)

HistogramProton7.SetTitle("Scaling Plot of p, d and t (V3 vs Y, 40-60% Centrality)")

HistogramProton7.GetYaxis().SetTitle("V3 / A")

HistogramProton7.GetYaxis().SetTitleOffset(1.5)

HistogramProton7.SetLineWidth(15)
HistogramProton7.SetMarkerStyle(ROOT.kFullSquare)
HistogramProton7.SetMarkerSize(3)
HistogramProton7.SetMarkerColor(ROOT.kRed)

HistogramProton7.SetLineColor(ROOT.kRed)

HistogramProton7.SetAxisRange(-0.05, 0.01, "Y")

HistogramProton7.Draw("PE 1 X0")

Histogram = MyFile.Get("DataVnVsYForDeuteronsCentrality40-60")

NewHistogramScaled13 = ROOT.TH1D("DataVnVsYForDeuteronsCentrality40-60Scaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 10, 0, 1)

NewHistogramScaled13.SetDirectory(0)

NewHistogramScaled13.SetStats(0)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled13.SetBinContent(index, Histogram.GetBinContent(index) / 2)
    NewHistogramScaled13.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled13.SetLineWidth(10)
NewHistogramScaled13.SetMarkerStyle(ROOT.kFullCircle)
NewHistogramScaled13.SetMarkerSize(3)
NewHistogramScaled13.SetMarkerColor(ROOT.kBlue)

NewHistogramScaled13.SetLineColor(ROOT.kBlue)

NewHistogramScaled13.Draw("PE 1 X0 SAME")

Histogram = MyFile.Get("DataVnVsYForTritonsCentrality40-60")

NewHistogramScaled14 = ROOT.TH1D("DataVnVsYForTritonsCentrality40-60Scaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 10, 0, 1)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled14.SetBinContent(index, Histogram.GetBinContent(index) / 3)
    NewHistogramScaled14.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled14.SetDirectory(0)

NewHistogramScaled14.SetStats(0)
    
NewHistogramScaled14.SetLineWidth(5)
NewHistogramScaled14.SetMarkerStyle(ROOT.kFullTriangleDown)
NewHistogramScaled14.SetMarkerSize(3)
NewHistogramScaled14.SetMarkerColor(ROOT.kGreen)

NewHistogramScaled14.SetLineColor(ROOT.kGreen)

NewHistogramScaled14.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityTritonCorrected_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityTritonCorrected_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

CanvasScalingY40_60.Draw()

LegendScalingY40_60 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
LegendScalingY40_60.AddEntry(HistogramProton7, "Protons")
LegendScalingY40_60.AddEntry(NewHistogramScaled13, "Deuterons")
LegendScalingY40_60.AddEntry(NewHistogramScaled14, "Tritons")
LegendScalingY40_60.Draw()

Canvasas.append(CanvasScalingY40_60)

'''
####################################################################################################### Other Plots
'''
Canvas17 = ROOT.TCanvas("Canvas17", "", 800, 800)
Canvas17.cd()

Histogram = MyFile.Get("DataVnVsCentralityProtonCorrected")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

for index in range(1, Histogram.GetNbinsX() + 1):
    Histogram.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])

Histogram.Draw("PE 1 X0")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityProtonCorrected_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)

NewGraph10 = ROOT.TGraphAsymmErrors()
NewGraph10.SetMarkerSize(3)
NewGraph10.SetMarkerColor(ROOT.kBlue)
NewGraph10.SetLineWidth(3)
NewGraph10.SetLineColor(ROOT.kBlue)

NewGraph10.SetFillColorAlpha(ROOT.kBlue, 0.3)

for index in range(0, 8):
    NewGraph10.SetPoint(index, index + 0.5, Graph.GetY()[index])
    NewGraph10.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index) * 1.5, Graph.GetErrorY(index) * 1.5)
    
for index in range(8, 12):
    NewGraph10.SetPoint(index, index + 0.5, Graph.GetY()[index])
    NewGraph10.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index) / 2, Graph.GetErrorY(index) / 2)

NewGraph10.Draw("E2 SAME")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth)

# Graph.Draw("E2 SAME")

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityProtonCorrected_px")

Graph.SetFillColorAlpha(ROOT.kRed, 0.3)

NewGraph11 = ROOT.TGraphAsymmErrors()
NewGraph11.SetMarkerSize(3)
NewGraph11.SetMarkerColor(ROOT.kRed)
NewGraph11.SetLineWidth(3)
NewGraph11.SetLineColor(ROOT.kRed)

NewGraph11.SetFillColorAlpha(ROOT.kRed, 0.3)

for index in range(0, 8):
    NewGraph11.SetPoint(index, index + 0.5, Graph.GetY()[index])
    NewGraph11.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index) * 1.5, Graph.GetErrorY(index) * 1.5)
    
for index in range(8, 12):
    NewGraph11.SetPoint(index, index + 0.5, Graph.GetY()[index])
    NewGraph11.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index) / 2, Graph.GetErrorY(index) / 2)
    
NewGraph11.Draw("E2 SAME")

RescaledHistogram17 = ROOT.TH1F("CameronRescaled", " ; ; ", 12, 0, 12)

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

# NewGraph6 = ROOT.TGraphAsymmErrors()
# NewGraph6.SetMarkerSize(3)
# NewGraph6.SetMarkerColor(ROOT.kRed)
# NewGraph6.SetLineWidth(3)
# NewGraph6.SetLineColor(ROOT.kRed)
print(Histogram.GetNbinsX())
for index in range(1, Histogram.GetNbinsX() + 1):
    RescaledHistogram17.SetBinContent(index, Histogram.GetBinContent(index))
    RescaledHistogram17.SetBinError(index, Histogram.GetBinError(index))
    
RescaledHistogram17.SetDirectory(0)

RescaledHistogram17.SetStats(0)

RescaledHistogram17.SetLineWidth(3)
RescaledHistogram17.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogram17.SetMarkerSize(1.5)
RescaledHistogram17.SetMarkerColor(ROOT.kRed)

RescaledHistogram17.SetLineColor(ROOT.kRed)

RescaledHistogram17.Draw("P E0 X0 SAME")

Canvas17.Draw()

Canvasas.append(Canvas17)
'''
############################################################################################################################################################

MyFileFirst.Close()
MyFileSecond.Close()



for index in range(0, len(Canvasas)):
    if len(Canvasas) == 1:
        Canvasas[index].SaveAs(Date + '_V3_Comparison_Plots.pdf)')
        break
    
    if index == 0:
        print("Opening PDF")
        Canvasas[index].SaveAs(Date + '_V3_Comparison_Plots.pdf(')
    
    elif index == len(Canvasas) - 1:
        print("Closing PDF")
        Canvasas[index].SaveAs(Date + '_V3_Comparison_Plots.pdf)')
    
    else:
        Canvasas[index].SaveAs(Date + '_V3_Comparison_Plots.pdf')
