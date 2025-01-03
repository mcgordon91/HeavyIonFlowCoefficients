#!/usr/bin/env python
# coding: utf-8



import ROOT
import os
import sys

Canvasas = []

Date = '9-4-24'





MyResolutionPlotFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/R_31_Normal.root","READ")
#ResolutionPlotFileCameron = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/resolutionInfo_INPUT_epd_high.root","READ")
ResolutionPlotFileCameron = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/LiteratureFiles/resolutionPlot.root","READ")

MyFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/" + Date + "-V3-HistogramNormalNewDataset20000FilesWithCuts.root","READ")
#MyFile = ROOT.TFile.Open("/star/u/mcgordon/SystematicsCameronResolution/HistogramFourthPassOuterEPDLow.root","READ")

#CameronFile = ROOT.TFile.Open("/star/u/mcgordon/30percentVariations/epd_low.picoDst.result.combined.root", "READ")
#CameronFile = ROOT.TFile.Open("/star/u/mcgordon/30percentVariations/epd_low.picoDst.result.combined.root", "READ")
#CameronFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/CameronResults.root","READ")
CameronFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/1-3-24-V3-HistogramsNormal.root","OPEN")

SystematicErrorRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/systematicErrors.root","READ")
#CameronSystematicErrorRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/LiteratureFiles/HEPData-ins2702151-SystematicErrors-root.root", "READ")



# Histogram = MyFile.Get("OverallTrackCheckNoCuts")

# print(Histogram.GetEntries())




 







CentralityXLabels = ["0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60", "60-65", "65-70", "70-75", "75-80"]


Canvas0 = ROOT.TCanvas("Canvas0", "", 800, 800)
Canvas0.cd()

HistogramA = MyResolutionPlotFile.Get("DataResolution")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetTitle("R_{31}")
HistogramA.GetYaxis().SetTitleOffset(1.5)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

for index in range(1, HistogramA.GetNbinsX() + 1):
    HistogramA.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])
    
HistogramA.Draw("PE 1 X0")

# HistogramB = ResolutionPlotFileCameron.Get("h_resVar1")

# RescaledHistogram1 = ROOT.TH1F("CameronResolutionRescaledVersion1", " ; ; ", 12, 0, 12)

# RescaledHistogram1.SetDirectory(0)

# RescaledHistogram1.SetStats(0)

# RescaledHistogram1.SetLineWidth(3)

# for index in range(1, HistogramB.GetNbinsX() + 1):
#     RescaledHistogram1.SetBinContent(17 - index, HistogramB.GetBinContent(index))
#     RescaledHistogram1.SetBinError(17 - index, HistogramB.GetBinError(index))
    
# for index in range(1, RescaledHistogram1.GetNbinsX() + 1):
#     RescaledHistogram1.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])

# # for index in range(1, Histogram.GetNbinsX() + 1):
# #     RescaledHistogram1.SetBinContent(index, Histogram.GetBinContent(index))
# #     RescaledHistogram1.SetBinError(index, Histogram.GetBinError(index))
# #     RescaledHistogram1.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])

# RescaledHistogram1.SetLineWidth(3)
# RescaledHistogram1.SetMarkerStyle(ROOT.kFullSquare)
# RescaledHistogram1.SetMarkerSize(1.5)
# RescaledHistogram1.SetMarkerColor(ROOT.kRed)

# RescaledHistogram1.SetLineColor(ROOT.kRed)

# RescaledHistogram1.Draw("PE 1 X0 SAME")

# # for index in range(1, 13):
# #     print(HistogramA.GetBinContent(index) - RescaledHistogram1.GetBinContent(index), HistogramA.GetBinError(index) - RescaledHistogram1.GetBinError(index))

# HistogramB = ResolutionPlotFileCameron.Get("h_resVar2")

# RescaledHistogram2 = ROOT.TH1F("CameronResolutionRescaledVersion2", " ; ; ", 12, 0, 12)

# RescaledHistogram2.SetDirectory(0)

# RescaledHistogram2.SetStats(0)

# RescaledHistogram2.SetLineWidth(3)

# for index in range(1, HistogramB.GetNbinsX() + 1):
#     RescaledHistogram2.SetBinContent(17 - index, HistogramB.GetBinContent(index))
#     RescaledHistogram2.SetBinError(17 - index, HistogramB.GetBinError(index))
    
# for index in range(1, RescaledHistogram2.GetNbinsX() + 1):
#     RescaledHistogram2.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])

# # for index in range(1, Histogram.GetNbinsX() + 1):
# #     RescaledHistogram1.SetBinContent(index, Histogram.GetBinContent(index))
# #     RescaledHistogram1.SetBinError(index, Histogram.GetBinError(index))
# #     RescaledHistogram1.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])

# RescaledHistogram2.SetLineWidth(3)
# RescaledHistogram2.SetMarkerStyle(ROOT.kFullSquare)
# RescaledHistogram2.SetMarkerSize(1.5)
# RescaledHistogram2.SetMarkerColor(ROOT.kGreen)

# RescaledHistogram2.SetLineColor(ROOT.kGreen)

# RescaledHistogram2.Draw("PE 1 X0 SAME")

# HistogramB = ResolutionPlotFileCameron.Get("h_resVar3")

# RescaledHistogram3 = ROOT.TH1F("CameronResolutionRescaledVersion3", " ; ; ", 12, 0, 12)

# RescaledHistogram3.SetDirectory(0)

# RescaledHistogram3.SetStats(0)

# RescaledHistogram3.SetLineWidth(3)

# for index in range(1, HistogramB.GetNbinsX() + 1):
#     RescaledHistogram3.SetBinContent(17 - index, HistogramB.GetBinContent(index))
#     RescaledHistogram3.SetBinError(17 - index, HistogramB.GetBinError(index))
    
# for index in range(1, RescaledHistogram3.GetNbinsX() + 1):
#     RescaledHistogram3.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])

# # for index in range(1, Histogram.GetNbinsX() + 1):
# #     RescaledHistogram1.SetBinContent(index, Histogram.GetBinContent(index))
# #     RescaledHistogram1.SetBinError(index, Histogram.GetBinError(index))
# #     RescaledHistogram1.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])

# RescaledHistogram3.SetLineWidth(3)
# RescaledHistogram3.SetMarkerStyle(ROOT.kFullSquare)
# RescaledHistogram3.SetMarkerSize(1.5)
# RescaledHistogram3.SetMarkerColor(ROOT.kOrange)

# RescaledHistogram3.SetLineColor(ROOT.kOrange)

# RescaledHistogram3.Draw("PE 1 X0 SAME")

HistogramB = ResolutionPlotFileCameron.Get("h_resolutions")

RescaledHistogramAverage = ROOT.TH1F("CameronResolutionRescaledAverage", " ; ; ", 12, 0, 12)

RescaledHistogramAverage.SetDirectory(0)

RescaledHistogramAverage.SetStats(0)

RescaledHistogramAverage.SetLineWidth(3)

for index in range(1, HistogramB.GetNbinsX() + 1):
    RescaledHistogramAverage.SetBinContent(index, HistogramB.GetBinContent(index))
    RescaledHistogramAverage.SetBinError(index, HistogramB.GetBinError(index))

# for index in range(1, HistogramB.GetNbinsX() + 1):
#     RescaledHistogramAverage.SetBinContent(17 - index, HistogramB.GetBinContent(index))
#     RescaledHistogramAverage.SetBinError(17 - index, HistogramB.GetBinError(index))

for index in range(1, RescaledHistogramAverage.GetNbinsX() + 1):
    RescaledHistogramAverage.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])

RescaledHistogramAverage.SetLineWidth(3)
RescaledHistogramAverage.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogramAverage.SetMarkerSize(1.5)
RescaledHistogramAverage.SetMarkerColor(ROOT.kMagenta)

RescaledHistogramAverage.SetLineColor(ROOT.kMagenta)

RescaledHistogramAverage.Draw("PE 1 X0 SAME")

Canvas0.Draw()

Legend0 = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend0.AddEntry(HistogramA, "New Dataset")
# Legend0.AddEntry(RescaledHistogram1, "STAR 2023, Variant 1")
# Legend0.AddEntry(RescaledHistogram2, "STAR 2023, Variant 2")
# Legend0.AddEntry(RescaledHistogram3, "STAR 2023, Variant 3")
Legend0.AddEntry(RescaledHistogramAverage, "STAR 2023")#, Average")
Legend0.Draw()

Canvasas.append(Canvas0)



MyResolutionPlotFile.Close()
#ResolutionPlotFileCameron.Close()



'''
Canvas1 = ROOT.TCanvas("Canvas1", "", 800, 800)
Canvas1.cd()

HistogramA = MyFile.Get("DataVnVsYForProtonsCentrality0-10")
#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Protons, 0-10% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.Draw("PE 1 X0")

HistogramB = CameronFile.Get("p2_vn_yCM_cent_pr").ProfileY("p_vn_yCM_00to10_pr", 15, 16)
#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForProtonsCentrality0-10_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForProtonsCentrality0-10_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

# Graph = CameronSystematicErrorRootFile.Get("/Figure 7/Graph1D_y1")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth, Graph.GetErrorY(i), Graph.GetErrorY(i))
    
# Graph.SetMarkerSize(3)
# Graph.SetMarkerColor(ROOT.kRed)
# Graph.SetLineWidth(3)
# Graph.SetLineColor(ROOT.kRed)
# Graph.SetFillColorAlpha(ROOT.kRed, 0.3)

# Graph.Draw("P* E2 SAME")

Canvas1.Draw()

# Legend1 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend1.AddEntry(HistogramA, "My Work")
# #Legend1.AddEntry(HistogramB, "STAR 2023")
# Legend1.AddEntry(Graph, "STAR 2023")
# Legend1.Draw()

Canvasas.append(Canvas1)







Canvas2 = ROOT.TCanvas("Canvas2", "", 800, 800)
Canvas2.cd()

HistogramA = MyFile.Get("DataVnVsYForProtonsCentrality10-40")
#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Protons, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.Draw("PE 1 X0")

HistogramB = CameronFile.Get("p2_vn_yCM_cent_pr").ProfileY("p_vn_yCM_10to40_pr", 9, 14)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForProtonsCentrality10-40_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForProtonsCentrality10-40_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)

# Graph.Draw("E2 SAME")

# Graph = CameronSystematicErrorRootFile.Get("/Figure 7/Graph1D_y2")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth, Graph.GetErrorY(i), Graph.GetErrorY(i))

# Graph.SetMarkerSize(3)
# Graph.SetMarkerColor(ROOT.kRed)
# Graph.SetLineWidth(3)
# Graph.SetLineColor(ROOT.kRed)
# Graph.SetFillColorAlpha(ROOT.kRed, 0.3)

# Graph.Draw("P* E2 SAME")

Canvas2.Draw()

# Legend2 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend2.AddEntry(HistogramA, "My Work")
# #Legend2.AddEntry(HistogramB, "STAR 2023")
# Legend2.AddEntry(Graph, "STAR 2023")
# Legend2.Draw()

Canvasas.append(Canvas2)






Canvas3 = ROOT.TCanvas("Canvas3", "", 800, 800)
Canvas3.cd()

HistogramA = MyFile.Get("DataVnVsYForProtonsCentrality40-60")
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

HistogramA.Draw("PE 1 X0")

HistogramB = CameronFile.Get("p2_vn_yCM_cent_pr").ProfileY("p_vn_yCM_40to60_pr", 5, 8)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForProtonsCentrality40-60_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForProtonsCentrality40-60_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)

# # for i in range(0, Graph.GetN()):
# #     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth)

# Graph.Draw("E2 SAME")

# Graph = CameronSystematicErrorRootFile.Get("/Figure 7/Graph1D_y3")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth, Graph.GetErrorY(i), Graph.GetErrorY(i))

# Graph.SetMarkerSize(3)
# Graph.SetMarkerColor(ROOT.kRed)
# Graph.SetLineWidth(3)
# Graph.SetLineColor(ROOT.kRed)
# Graph.SetFillColorAlpha(ROOT.kRed, 0.3)

# Graph.Draw("P* E2 SAME")

Canvas3.Draw()

# Legend3 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend3.AddEntry(HistogramA, "My Work")
# #Legend3.AddEntry(HistogramB, "STAR 2023")
# Legend3.AddEntry(Graph, "STAR 2023")
# Legend3.Draw()

Canvasas.append(Canvas3)





Canvas1A = ROOT.TCanvas("Canvas1A", "", 800, 800)
Canvas1A.cd()

Histogram = MyFile.Get("DataVnVsYForKaonsPlusCentrality0-10")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Kaons Plus, 0-10% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p2_vn_yCM_cent_kp").ProfileY("p_vn_yCM_0to10_kp", 15, 16)
# HistogramB = CameronFile.Get("p_vn_yCM_00to10_kp_px")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForKaonsPlusCentrality0-10_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForKaonsPlusCentrality0-10_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas1A.Draw()

Canvasas.append(Canvas1A)









Canvas2A = ROOT.TCanvas("Canvas2A", "", 800, 800)
Canvas2A.cd()

Histogram = MyFile.Get("DataVnVsYForKaonsPlusCentrality10-40")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Kaons Plus, 10-40% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p2_vn_yCM_cent_kp").ProfileY("p_vn_yCM_10to40_kp", 9, 14)

#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForKaonsPlusCentrality10-40_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForKaonsPlusCentrality10-40_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas2A.Draw()

Canvasas.append(Canvas2A)






Canvas3A = ROOT.TCanvas("Canvas3A", "", 800, 800)
Canvas3A.cd()

Histogram = MyFile.Get("DataVnVsYForKaonsPlusCentrality40-60")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Kaons Plus, 40-60% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p2_vn_yCM_cent_kp").ProfileY("p_vn_yCM_40to60_kp", 5, 8)

#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForKaonsPlusCentrality40-60_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForKaonsPlusCentrality40-60_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas3A.Draw()

Canvasas.append(Canvas3A)




Canvas1B = ROOT.TCanvas("Canvas1B", "", 800, 800)
Canvas1B.cd()

Histogram = MyFile.Get("DataVnVsYForKaonsMinusCentrality0-10")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Kaons Minus, 0-10% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p2_vn_yCM_cent_km").ProfileY("p_vn_yCM_0to10_km", 15, 16)

#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForKaonsMinusCentrality0-10_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForKaonsMinusCentrality0-10_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas1B.Draw()

Canvasas.append(Canvas1B)









Canvas2B = ROOT.TCanvas("Canvas2B", "", 800, 800)
Canvas2B.cd()

Histogram = MyFile.Get("DataVnVsYForKaonsMinusCentrality10-40")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Kaons Minus, 10-40% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p2_vn_yCM_cent_km").ProfileY("p_vn_yCM_10to40_km", 9, 14)

#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForKaonsMinusCentrality10-40_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForKaonsMinusCentrality10-40_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas2B.Draw()

Canvasas.append(Canvas2B)






Canvas3B = ROOT.TCanvas("Canvas3B", "", 800, 800)
Canvas3B.cd()

Histogram = MyFile.Get("DataVnVsYForKaonsMinusCentrality40-60")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Kaons Minus, 40-60% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p2_vn_yCM_cent_km").ProfileY("p_vn_yCM_40to60_km", 5, 8)

#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForKaonsMinusCentrality40-60_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForKaonsMinusCentrality40-60_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas3B.Draw()

Canvasas.append(Canvas3B)




Canvas1C = ROOT.TCanvas("Canvas1C", "", 800, 800)
Canvas1C.cd()

Histogram = MyFile.Get("DataVnVsYForPionsPlusCentrality0-10")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Pions Plus, 0-10% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p2_vn_yCM_cent_pp").ProfileY("p_vn_yCM_0to10_pp", 15, 16)

#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForPionsPlusCentrality0-10_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForPionsPlusCentrality0-10_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas1C.Draw()

Canvasas.append(Canvas1C)









Canvas2C = ROOT.TCanvas("Canvas2C", "", 800, 800)
Canvas2C.cd()

Histogram = MyFile.Get("DataVnVsYForPionsPlusCentrality10-40")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Pions Plus, 10-40% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p2_vn_yCM_cent_pp").ProfileY("p_vn_yCM_10to40_pp", 9, 14)

#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForPionsPlusCentrality10-40_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForPionsPlusCentrality10-40_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas2C.Draw()

Canvasas.append(Canvas2C)






Canvas3C = ROOT.TCanvas("Canvas3C", "", 800, 800)
Canvas3C.cd()

Histogram = MyFile.Get("DataVnVsYForPionsPlusCentrality40-60")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Pions Plus, 40-60% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p2_vn_yCM_cent_pp").ProfileY("p_vn_yCM_40to60_pp", 5, 8)

#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForPionsPlusCentrality40-60_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForPionsPlusCentrality40-60_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas3C.Draw()

Canvasas.append(Canvas3C)




Canvas1D = ROOT.TCanvas("Canvas1D", "", 800, 800)
Canvas1D.cd()

Histogram = MyFile.Get("DataVnVsYForPionsMinusCentrality0-10")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Pions Minus, 0-10% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p2_vn_yCM_cent_pm").ProfileY("p_vn_yCM_0to10_pm", 15, 16)

#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForPionsMinusCentrality0-10_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForPionsMinusCentrality0-10_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas1D.Draw()

Canvasas.append(Canvas1D)









Canvas2D = ROOT.TCanvas("Canvas2D", "", 800, 800)
Canvas2D.cd()

Histogram = MyFile.Get("DataVnVsYForPionsMinusCentrality10-40")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Pions Minus, 10-40% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p2_vn_yCM_cent_pm").ProfileY("p_vn_yCM_10to40_pm", 9, 14)

#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForPionsMinusCentrality10-40_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForPionsMinusCentrality10-40_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas2D.Draw()

Canvasas.append(Canvas2D)






Canvas3D = ROOT.TCanvas("Canvas3D", "", 800, 800)
Canvas3D.cd()

Histogram = MyFile.Get("DataVnVsYForPionsMinusCentrality40-60")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Pions Minus, 40-60% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p2_vn_yCM_cent_pm").ProfileY("p_vn_yCM_40to60_pm", 5, 8)

#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForPionsMinusCentrality40-60_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForPionsMinusCentrality40-60_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas3D.Draw()

Canvasas.append(Canvas3D)





Canvas1E = ROOT.TCanvas("Canvas1E", "", 800, 800)
Canvas1E.cd()

Histogram = MyFile.Get("DataVnVsYForDeuteronsCentrality0-10")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Deuterons, 0-10% Centrality")

Histogram.Draw("PE 1 X0")

# Histogram = CameronFile.Get("p2_vn_yCM_cent_de").ProfileY("p_vn_yCM_0to10_de", 15, 16)
# #print(Histogram.GetEntries())
# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(3)
# Histogram.SetMarkerStyle(ROOT.kFullSquare)
# Histogram.SetMarkerSize(1.5)
# Histogram.SetMarkerColor(ROOT.kRed)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForDeuteronsCentrality0-10_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForDeuteronsCentrality0-10_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas1E.Draw()

Canvasas.append(Canvas1E)









Canvas2E = ROOT.TCanvas("Canvas2E", "", 800, 800)
Canvas2E.cd()

Histogram = MyFile.Get("DataVnVsYForDeuteronsCentrality10-40")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Deuterons, 10-40% Centrality")

Histogram.Draw("PE 1 X0")

# Histogram = CameronFile.Get("p2_vn_yCM_cent_de").ProfileY("p_vn_yCM_10to40_pm", 9, 14)
# #print(Histogram.GetEntries())
# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(3)
# Histogram.SetMarkerStyle(ROOT.kFullSquare)
# Histogram.SetMarkerSize(1.5)
# Histogram.SetMarkerColor(ROOT.kRed)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForDeuteronsCentrality10-40_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForDeuteronsCentrality10-40_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas2E.Draw()

Canvasas.append(Canvas2E)






Canvas3E = ROOT.TCanvas("Canvas3E", "", 800, 800)
Canvas3E.cd()

Histogram = MyFile.Get("DataVnVsYForDeuteronsCentrality40-60")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Deuterons, 40-60% Centrality")

Histogram.Draw("PE 1 X0")

# Histogram = CameronFile.Get("p2_vn_yCM_cent_de").ProfileY("p_vn_yCM_40to60_de", 5, 8)
# #print(Histogram.GetEntries())
# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(3)
# Histogram.SetMarkerStyle(ROOT.kFullSquare)
# Histogram.SetMarkerSize(1.5)
# Histogram.SetMarkerColor(ROOT.kRed)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForDeuteronsCentrality40-60_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForDeuteronsCentrality40-60_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas3E.Draw()

Canvasas.append(Canvas3E)






Canvas1F = ROOT.TCanvas("Canvas1F", "", 800, 800)
Canvas1F.cd()

Histogram = MyFile.Get("DataVnVsYForTritonsCentrality0-10")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Tritons, 0-10% Centrality")

Histogram.Draw("PE 1 X0")

# Histogram = CameronFile.Get("p2_vn_yCM_cent_tr").ProfileY("p_vn_yCM_0to10_tr", 15, 16)
# #print(Histogram.GetEntries())
# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(3)
# Histogram.SetMarkerStyle(ROOT.kFullSquare)
# Histogram.SetMarkerSize(1.5)
# Histogram.SetMarkerColor(ROOT.kRed)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForTritonsCentrality0-10_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForTritonsCentrality0-10_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas1F.Draw()

Canvasas.append(Canvas1F)









Canvas2F = ROOT.TCanvas("Canvas2F", "", 800, 800)
Canvas2F.cd()

Histogram = MyFile.Get("DataVnVsYForTritonsCentrality10-40")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Tritons, 10-40% Centrality")

Histogram.Draw("PE 1 X0")

# Histogram = CameronFile.Get("p2_vn_yCM_cent_tr").ProfileY("p_vn_yCM_10to40_tr", 9, 14)
# #print(Histogram.GetEntries())
# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(3)
# Histogram.SetMarkerStyle(ROOT.kFullSquare)
# Histogram.SetMarkerSize(1.5)
# Histogram.SetMarkerColor(ROOT.kRed)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForTritonsCentrality10-40_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForTritonsCentrality10-40_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas2F.Draw()

Canvasas.append(Canvas2F)






Canvas3F = ROOT.TCanvas("Canvas3F", "", 800, 800)
Canvas3F.cd()

Histogram = MyFile.Get("DataVnVsYForTritonsCentrality40-60")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Tritons, 40-60% Centrality")

Histogram.Draw("PE 1 X0")

# Histogram = CameronFile.Get("p2_vn_yCM_cent_tr").ProfileY("p_vn_yCM_40to60_tr", 5, 8)
# #print(Histogram.GetEntries())
# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(3)
# Histogram.SetMarkerStyle(ROOT.kFullSquare)
# Histogram.SetMarkerSize(1.5)
# Histogram.SetMarkerColor(ROOT.kRed)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForTritonsCentrality40-60_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForTritonsCentrality40-60_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Canvas3F.Draw()

Canvasas.append(Canvas3F)







Canvas4 = ROOT.TCanvas("Canvas4", "", 800, 800)
Canvas4.cd()

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

RescaledHistogram4 = CameronFile.Get("DataVnVsCentralityProtonCorrected")#("p_vn_pr")

# RescaledHistogram4 = ROOT.TH1F("CameronV3VsCentralityProtonRescaled", "V3 vs Centrality for Protons; Centrality; V3", 12, 0, 12)

RescaledHistogram4.SetDirectory(0)

RescaledHistogram4.SetStats(0)

    
RescaledHistogram4.SetLineWidth(3)
RescaledHistogram4.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogram4.SetMarkerSize(1.5)
RescaledHistogram4.SetMarkerColor(ROOT.kRed)
RescaledHistogram4.SetLineColor(ROOT.kRed)

RescaledHistogram4.Draw("PE 1 X0 SAME")

# SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityProtonCorrected_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)

# NewGraph = ROOT.TGraphAsymmErrors()
# NewGraph.SetMarkerSize(3)
# NewGraph.SetMarkerColor(ROOT.kBlue)
# NewGraph.SetLineWidth(3)
# NewGraph.SetLineColor(ROOT.kBlue)

# NewGraph.SetFillColorAlpha(ROOT.kBlue, 0.3)

# for index in range(0, Graph.GetN()):
#     NewGraph.SetPoint(index, index + 0.5, Graph.GetY()[index])
#     NewGraph.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))


# NewGraph.Draw("E2 SAME")

# Graph = CameronSystematicErrorRootFile.Get("/Figure 4/Graph1D_y3")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth, Graph.GetErrorY(i), Graph.GetErrorY(i))
    
# NewGraph1 = ROOT.TGraphAsymmErrors()
# NewGraph1.SetMarkerSize(3)
# NewGraph1.SetMarkerColor(ROOT.kRed)
# NewGraph1.SetLineWidth(3)
# NewGraph1.SetLineColor(ROOT.kRed)
    
# NewGraph1.SetFillColorAlpha(ROOT.kRed, 0.3)

# for index in range(0, Graph.GetN()):
#     NewGraph1.SetPoint(index, index + 0.5, Graph.GetY()[index])
#     NewGraph1.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))

# NewGraph1.Draw("P* E2 SAME")

Canvas4.Draw()

Canvasas.append(Canvas4)



Canvas5 = ROOT.TCanvas("Canvas5", "", 800, 800)
Canvas5.cd()

Histogram = MyFile.Get("DataVnVsCentralityKaonPlusCorrected")
#print(Histogram.GetEntries())

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.GetYaxis().SetTitleOffset(1.5)

for index in range(1, Histogram.GetNbinsX() + 1):
    Histogram.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])


Histogram.Draw("PE 1 X0")

RescaledHistogram5 = CameronFile.Get("DataVnVsCentralityKaonPlusCorrected")#("p_vn_kp")
#print(Histogram.GetEntries())

# RescaledHistogram5 = ROOT.TH1F("CameronV3VsCentralityKaonPlusRescaled", "V3 vs Centrality for K+; Centrality; V3", 12, 0, 12)

# for index in range(1, Histogram.GetNbinsX() + 1):
#     RescaledHistogram5.SetBinContent(17 - index, Histogram.GetBinContent(index))
#     RescaledHistogram5.SetBinError(17 - index, Histogram.GetBinError(index))

RescaledHistogram5.SetDirectory(0)

RescaledHistogram5.SetStats(0)

RescaledHistogram5.SetLineWidth(3)
RescaledHistogram5.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogram5.SetMarkerSize(1.5)
RescaledHistogram5.SetMarkerColor(ROOT.kRed)
RescaledHistogram5.SetLineColor(ROOT.kRed)

RescaledHistogram5.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityKaonPlusCorrected_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityKaonPlusCorrected_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

# Graph = CameronSystematicErrorRootFile.Get("/Figure 5/Graph1D_y1")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth, Graph.GetErrorY(i), Graph.GetErrorY(i))
    
# NewGraph2 = ROOT.TGraphAsymmErrors()
# NewGraph2.SetMarkerSize(3)
# NewGraph2.SetMarkerColor(ROOT.kRed)
# NewGraph2.SetLineWidth(3)
# NewGraph2.SetLineColor(ROOT.kRed)

# for index in range(0, Graph.GetN()):
#     NewGraph2.SetPoint(index, index + 0.5, Graph.GetY()[index])
#     NewGraph2.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))
    
# NewGraph2.SetFillColorAlpha(ROOT.kRed, 0.3)

# NewGraph2.Draw("P* E2 SAME")

Canvas5.Draw()

Canvasas.append(Canvas5)






Canvas6 = ROOT.TCanvas("Canvas6", "", 800, 800)
Canvas6.cd()

Histogram = MyFile.Get("DataVnVsCentralityKaonMinusCorrected")
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

RescaledHistogram6 = CameronFile.Get("DataVnVsCentralityKaonMinusCorrected")#("p_vn_km")
# # print(Histogram.GetEntries())
# RescaledHistogram6 = ROOT.TH1F("CameronV3VsCentralityKaonMinusRescaled", "V3 vs Centrality for K-; Centrality; V3", 12, 0, 12)

# for index in range(1, Histogram.GetNbinsX() + 1):
#     RescaledHistogram6.SetBinContent(17 - index, Histogram.GetBinContent(index))
#     RescaledHistogram6.SetBinError(17 - index, Histogram.GetBinError(index))

RescaledHistogram6.SetDirectory(0)

RescaledHistogram6.SetStats(0)

RescaledHistogram6.SetLineWidth(3)
RescaledHistogram6.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogram6.SetMarkerSize(1.5)
RescaledHistogram6.SetMarkerColor(ROOT.kRed)
RescaledHistogram6.SetLineColor(ROOT.kRed)

RescaledHistogram6.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityKaonMinusCorrected_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityKaonMinusCorrected_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

# Graph = CameronSystematicErrorRootFile.Get("/Figure 5/Graph1D_y2")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth, Graph.GetErrorY(i), Graph.GetErrorY(i))
    
# NewGraph3 = ROOT.TGraphAsymmErrors()
# NewGraph3.SetMarkerSize(3)
# NewGraph3.SetMarkerColor(ROOT.kRed)
# NewGraph3.SetLineWidth(3)
# NewGraph3.SetLineColor(ROOT.kRed)

# for index in range(0, Graph.GetN()):
#     NewGraph3.SetPoint(index, index + 0.5, Graph.GetY()[index])
#     NewGraph3.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))
    
# NewGraph3.SetFillColorAlpha(ROOT.kRed, 0.3)

# NewGraph3.Draw("P* E2 SAME")

Canvas6.Draw()

Canvasas.append(Canvas6)





Canvas7 = ROOT.TCanvas("Canvas7", "", 800, 800)
Canvas7.cd()

Histogram = MyFile.Get("DataVnVsCentralityPionPlusCorrected")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("DataVnVsCentralityPionPlusCorrected")#("p_vn_pp")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)
Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityPionPlusCorrected_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityPionPlusCorrected_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

# Graph = CameronSystematicErrorRootFile.Get("/Figure 4/Graph1D_y1")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth, Graph.GetErrorY(i), Graph.GetErrorY(i))
    
# NewGraph4 = ROOT.TGraphAsymmErrors()
# NewGraph4.SetMarkerSize(3)
# NewGraph4.SetMarkerColor(ROOT.kRed)
# NewGraph4.SetLineWidth(3)
# NewGraph4.SetLineColor(ROOT.kRed)

# for index in range(0, Graph.GetN()):
#     NewGraph4.SetPoint(index, index + 0.5, Graph.GetY()[index])
#     NewGraph4.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))
    
# NewGraph4.SetFillColorAlpha(ROOT.kRed, 0.3)

# NewGraph4.Draw("P* E2 SAME")

Canvas7.Draw()

Canvasas.append(Canvas7)




Canvas8 = ROOT.TCanvas("Canvas8", "", 800, 800)
Canvas8.cd()

Histogram = MyFile.Get("DataVnVsCentralityPionMinusCorrected")
#print(Histogram.GetEntries())
Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("DataVnVsCentralityPionMinusCorrected")#("p_vn_pm")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)
Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityPionMinusCorrected_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityPionMinusCorrected_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

# Graph = CameronSystematicErrorRootFile.Get("/Figure 4/Graph1D_y2")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth, Graph.GetErrorY(i), Graph.GetErrorY(i))
    
# NewGraph5 = ROOT.TGraphAsymmErrors()
# NewGraph5.SetMarkerSize(3)
# NewGraph5.SetMarkerColor(ROOT.kRed)
# NewGraph5.SetLineWidth(3)
# NewGraph5.SetLineColor(ROOT.kRed)

# for index in range(0, Graph.GetN()):
#     NewGraph5.SetPoint(index, index + 0.5, Graph.GetY()[index])
#     NewGraph5.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))
    
# NewGraph5.SetFillColorAlpha(ROOT.kRed, 0.3)

# NewGraph5.Draw("P* E2 SAME")

Canvas8.Draw()

Canvasas.append(Canvas8)



Canvas9 = ROOT.TCanvas("Canvas9", "", 800, 800)
Canvas9.cd()

Histogram = MyFile.Get("DataVnVsCentralityDeuteronCorrected")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityDeuteronCorrected_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityDeuteronCorrected_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

# Canvas9.Draw()

Canvasas.append(Canvas9)



Canvas10 = ROOT.TCanvas("Canvas10", "", 800, 800)
Canvas10.cd()

Histogram = MyFile.Get("DataVnVsCentralityTritonCorrected")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityTritonCorrected_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityTritonCorrected_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas10.Draw()

Canvasas.append(Canvas10)





Canvas11 = ROOT.TCanvas("Canvas11", "", 800, 800)
Canvas11.cd()

HistogramA = MyFile.Get("DataVnVsYSymmetricForProtonsCentrality0-10")
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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_pr_symmetry").ProfileY("p_vn_yCM_00to10_pr_symmetry", 15, 16)
#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYSymmetricForProtonsCentrality0-10_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYSymmetricForProtonsCentrality0-10_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)

# Graph.Draw("E2 SAME")

# Graph = CameronSystematicErrorRootFile.Get("/Figure 6/Graph1D_y1")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth, Graph.GetErrorY(i) / 2, Graph.GetErrorY(i) / 2)
    
# Graph.SetMarkerSize(3)
# Graph.SetMarkerColor(ROOT.kRed)
# Graph.SetLineWidth(3)
# Graph.SetLineColor(ROOT.kRed)
# Graph.SetFillColorAlpha(ROOT.kRed, 0.3)

# Graph.Draw("P* E2 SAME")

Canvas1.Draw()

# Legend1 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend1.AddEntry(HistogramA, "My Work")
# #Legend1.AddEntry(HistogramB, "STAR 2023")
# Legend1.AddEntry(Graph, "STAR 2023")
# Legend1.Draw()

Canvasas.append(Canvas11)







Canvas12 = ROOT.TCanvas("Canvas12", "", 800, 800)
Canvas12.cd()

HistogramA = MyFile.Get("DataVnVsYSymmetricForProtonsCentrality10-40")
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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_pr_symmetry").ProfileY("p_vn_yCM_10to40_pr_symmetry", 9, 14)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYSymmetricForProtonsCentrality10-40_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYSymmetricForProtonsCentrality10-40_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)

# Graph.Draw("E2 SAME")

# Graph = CameronSystematicErrorRootFile.Get("/Figure 6/Graph1D_y2")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth, Graph.GetErrorY(i) / 2, Graph.GetErrorY(i) / 2)

# Graph.SetMarkerSize(3)
# Graph.SetMarkerColor(ROOT.kRed)
# Graph.SetLineWidth(3)
# Graph.SetLineColor(ROOT.kRed)
# Graph.SetFillColorAlpha(ROOT.kRed, 0.3)

# Graph.Draw("P* E2 SAME")

Canvas2.Draw()

# Legend2 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend2.AddEntry(HistogramA, "My Work")
# #Legend2.AddEntry(HistogramB, "STAR 2023")
# Legend2.AddEntry(Graph, "STAR 2023")
# Legend2.Draw()

Canvasas.append(Canvas12)






Canvas13 = ROOT.TCanvas("Canvas13", "", 800, 800)
Canvas13.cd()

HistogramA = MyFile.Get("DataVnVsYSymmetricForProtonsCentrality40-60")
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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_pr_symmetry").ProfileY("p_vn_yCM_40to60_pr_symmetry", 5, 8)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsYSymmetricForProtonsCentrality40-60_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYSymmetricForProtonsCentrality40-60_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)

# # for i in range(0, Graph.GetN()):
# #     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth)

# Graph.Draw("E2 SAME")

# Graph = CameronSystematicErrorRootFile.Get("/Figure 6/Graph1D_y3")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth, Graph.GetErrorY(i) / 2, Graph.GetErrorY(i) / 2)

# Graph.SetMarkerSize(3)
# Graph.SetMarkerColor(ROOT.kRed)
# Graph.SetLineWidth(3)
# Graph.SetLineColor(ROOT.kRed)
# Graph.SetFillColorAlpha(ROOT.kRed, 0.3)

# Graph.Draw("P* E2 SAME")

Canvas13.Draw()

# Legend3 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend3.AddEntry(HistogramA, "My Work")
# #Legend3.AddEntry(HistogramB, "STAR 2023")
# Legend3.AddEntry(Graph, "STAR 2023")
# Legend3.Draw()

Canvasas.append(Canvas13)




Canvas14 = ROOT.TCanvas("Canvas14", "", 800, 800)
Canvas14.cd()

HistogramA = MyFile.Get("DataVnVsPtForProtonsCentrality0-10")

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

HistogramA.Draw("PE 1 X0")

HistogramB = CameronFile.Get("p2_vn_pT_cent_pr").ProfileY("p_vn_pT_00to10_pr", 15, 16)
#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsPtForProtonsCentrality0-10_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsPtForProtonsCentrality0-10_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)

# Graph.Draw("E2 SAME")

# Graph = CameronSystematicErrorRootFile.Get("/Figure 8/Graph1D_y1")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth, Graph.GetErrorY(i), Graph.GetErrorY(i))
    
# Graph.SetMarkerSize(3)
# Graph.SetMarkerColor(ROOT.kRed)
# Graph.SetLineWidth(3)
# Graph.SetLineColor(ROOT.kRed)
# Graph.SetFillColorAlpha(ROOT.kRed, 0.3)

# Graph.Draw("P* E2 SAME")

Canvas14.Draw()

# Legend1 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend1.AddEntry(HistogramA, "My Work")
# #Legend1.AddEntry(HistogramB, "STAR 2023")
# Legend1.AddEntry(Graph, "STAR 2023")
# Legend1.Draw()

Canvasas.append(Canvas14)







Canvas15 = ROOT.TCanvas("Canvas15", "", 800, 800)
Canvas15.cd()

HistogramA = MyFile.Get("DataVnVsPtForProtonsCentrality10-40")

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Protons, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.Draw("PE 1 X0")

HistogramB = CameronFile.Get("p2_vn_pT_cent_pr").ProfileY("p_vn_pT_10to40_pr", 9, 14)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsPtForProtonsCentrality10-40_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsPtForProtonsCentrality10-40_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)

# Graph.Draw("E2 SAME")

# Graph = CameronSystematicErrorRootFile.Get("/Figure 8/Graph1D_y2")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth, Graph.GetErrorY(i), Graph.GetErrorY(i))

# Graph.SetMarkerSize(3)
# Graph.SetMarkerColor(ROOT.kRed)
# Graph.SetLineWidth(3)
# Graph.SetLineColor(ROOT.kRed)
# Graph.SetFillColorAlpha(ROOT.kRed, 0.3)

# Graph.Draw("P* E2 SAME")

Canvas15.Draw()

# Legend2 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend2.AddEntry(HistogramA, "My Work")
# #Legend2.AddEntry(HistogramB, "STAR 2023")
# Legend2.AddEntry(Graph, "STAR 2023")
# Legend2.Draw()

Canvasas.append(Canvas15)






Canvas16 = ROOT.TCanvas("Canvas16", "", 800, 800)
Canvas16.cd()

HistogramA = MyFile.Get("DataVnVsPtForProtonsCentrality40-60")

HistogramA.Rebin()

#print(Histogram.GetEntries())
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Pt for Protons, 40-60% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.Draw("PE 1 X0")

HistogramB = CameronFile.Get("p2_vn_pT_cent_pr").ProfileY("p_vn_pT_40to60_pr", 5, 8)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

# Histogram = SystematicErrorRootFile.Get("DataVnVsPtForProtonsCentrality40-60_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsPtForProtonsCentrality40-60_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)

# Graph.Draw("E2 SAME")

# Graph = CameronSystematicErrorRootFile.Get("/Figure 8/Graph1D_y3")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth, Graph.GetErrorY(i), Graph.GetErrorY(i))

# Graph.SetMarkerSize(3)
# Graph.SetMarkerColor(ROOT.kRed)
# Graph.SetLineWidth(3)
# Graph.SetLineColor(ROOT.kRed)
# Graph.SetFillColorAlpha(ROOT.kRed, 0.3)

# Graph.Draw("P* E2 SAME")

Canvas16.Draw()

# Legend3 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend3.AddEntry(HistogramA, "My Work")
# #Legend3.AddEntry(HistogramB, "STAR 2023")
# Legend3.AddEntry(Graph, "STAR 2023")
# Legend3.Draw()

Canvasas.append(Canvas16)





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











CanvasScaling = ROOT.TCanvas("CanvasScaling", "", 800, 800)
CanvasScaling.cd()

HistogramProton = MyFile.Get("DataVnVsCentralityProtonCorrected")

HistogramProton.SetDirectory(0)

HistogramProton.SetStats(0)

HistogramProton.SetTitle("Scaling Plot of p, d and t")

HistogramProton.GetYaxis().SetTitle("V3 / A")

HistogramProton.SetAxisRange(-0.024, 0.03, "Y")
HistogramProton.GetYaxis().SetTitleOffset(1.5)

HistogramProton.SetLineWidth(3)
HistogramProton.SetMarkerStyle(ROOT.kFullSquare)
HistogramProton.SetMarkerSize(3)
HistogramProton.SetMarkerColor(ROOT.kRed)

HistogramProton.SetLineColor(ROOT.kRed)

HistogramProton.Draw("PE 1 X0")

Histogram = MyFile.Get("DataVnVsCentralityDeuteronCorrected")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

NewHistogramScaled1 = ROOT.TH1D("DataVnVsCentralityDeuteronCorrectedScaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 12, 0, 12)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled1.SetBinContent(index, Histogram.GetBinContent(index) / 2)
    NewHistogramScaled1.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled1.SetLineWidth(3)
NewHistogramScaled1.SetMarkerStyle(ROOT.kFullCircle)
NewHistogramScaled1.SetMarkerSize(3)
NewHistogramScaled1.SetMarkerColor(ROOT.kBlue)

NewHistogramScaled1.Draw("PE 1 X0 SAME")

Histogram = MyFile.Get("DataVnVsCentralityTritonCorrected")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullTriangleDown)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kGreen)

Histogram.SetLineColor(ROOT.kGreen)

NewHistogramScaled2 = ROOT.TH1D("DataVnVsCentralityTritonCorrectedScaled", "Scaling Plot of p, d and t; Centrality; V3 / A", 12, 0, 12)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled2.SetBinContent(index, Histogram.GetBinContent(index) / 3)
    NewHistogramScaled2.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled2.SetLineWidth(3)
NewHistogramScaled2.SetMarkerStyle(ROOT.kFullTriangleDown)
NewHistogramScaled2.SetMarkerSize(3)
NewHistogramScaled2.SetMarkerColor(ROOT.kGreen)

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

CanvasScaling.Draw()

LegendScaling = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
LegendScaling.AddEntry(HistogramProton, "Protons")
LegendScaling.AddEntry(NewHistogramScaled1, "Deuterons")
LegendScaling.AddEntry(NewHistogramScaled2, "Tritons")
LegendScaling.Draw()

Canvasas.append(CanvasScaling)
'''





MyFile.Close()
#CameronFile.Close()
#SystematicErrorRootFile.Close()
#CameronSystematicErrorRootFile.Close()



for index in range(0, len(Canvasas)):
    if len(Canvasas) == 1:
        Canvasas[index].SaveAs(Date + '_V3_Literature_Plots.pdf)')
        break
    
    if index == 0:
        print("Opening PDF")
        Canvasas[index].SaveAs(Date + '_V3_Literature_Plots.pdf(')
    
    elif index == len(Canvasas) - 1:
        print("Closing PDF")
        Canvasas[index].SaveAs(Date + '_V3_Literature_Plots.pdf)')
    
    else:
        Canvasas[index].SaveAs(Date + '_V3_Literature_Plots.pdf')
