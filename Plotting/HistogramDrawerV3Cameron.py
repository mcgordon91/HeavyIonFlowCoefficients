#!/usr/bin/env python
# coding: utf-8



import ROOT
import os
import sys

Canvasas = []

Date = '9-29-24'





MyResolutionPlotFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/R_31_Normal.root","READ")
ResolutionPlotFileCameron = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/LiteratureFiles/resolutionPlot.root","READ")
# ResolutionPlotFileCameron = ROOT.TFile.Open("/star/u/mcgordon/SystematicsCameronResolution/resolutionInfo_INPUT_epd_high.root","READ")

MyFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/" + Date + "-V3-HistogramNormal.root","READ")
CameronFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/LiteratureFiles/CameronResults.root","READ")

# SystematicErrorRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/systematicErrors.root","READ")
# CameronSystematicErrorRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/LiteratureFiles/HEPData-ins2702151-SystematicErrors-root.root", "READ")





 







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

# for index in range(1, HistogramB.GetNbinsX() + 1):
#     RescaledHistogramAverage.SetBinContent(index, HistogramB.GetBinContent(index))
#     RescaledHistogramAverage.SetBinError(index, HistogramB.GetBinError(index))

for index in range(1, HistogramB.GetNbinsX() + 1):
    RescaledHistogramAverage.SetBinContent(17 - index, HistogramB.GetBinContent(index))
    RescaledHistogramAverage.SetBinError(17 - index, HistogramB.GetBinError(index))

RescaledHistogramAverage.SetLineWidth(3)
RescaledHistogramAverage.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogramAverage.SetMarkerSize(1.5)
RescaledHistogramAverage.SetMarkerColor(ROOT.kMagenta)

RescaledHistogramAverage.SetLineColor(ROOT.kMagenta)

RescaledHistogramAverage.Draw("PE 1 X0 SAME")

Canvas0.Draw()

# Legend0 = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
# Legend0.AddEntry(HistogramA, "New Dataset")
# # Legend0.AddEntry(RescaledHistogram1, "STAR 2023, Variant 1")
# # Legend0.AddEntry(RescaledHistogram2, "STAR 2023, Variant 2")
# # Legend0.AddEntry(RescaledHistogram3, "STAR 2023, Variant 3")
# Legend0.AddEntry(RescaledHistogramAverage, "STAR 2023")#, Average")
# Legend0.Draw()

Canvasas.append(Canvas0)



MyResolutionPlotFile.Close()
ResolutionPlotFileCameron.Close()



####################################################################################################### V3 vs Centrality



Canvas4 = ROOT.TCanvas("Canvas4", "", 800, 800)
Canvas4.cd()

Histogram = MyFile.Get("DataVnVsCentralityProtonCorrected")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("PE 1 X0")

HistogramTemp = CameronFile.Get("p_vn_pr")

RescaledHistogram4 = ROOT.TH1F("CameronVnVsCentralityProtonRescaled", "V3 vs Centrality for Protons; Centrality; V3", 12, 0, 12)

for index in range(1, HistogramTemp.GetNbinsX() + 1):
    RescaledHistogram4.SetBinContent(17 - index, HistogramTemp.GetBinContent(index))
    RescaledHistogram4.SetBinError(17 - index, HistogramTemp.GetBinError(index))

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

Legend4 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend4.AddEntry(Histogram, "My Work")
Legend4.AddEntry(RescaledHistogram4, "STAR 2023")
Legend4.Draw()

Canvasas.append(Canvas4)



Canvas5 = ROOT.TCanvas("Canvas5", "", 800, 800)
Canvas5.cd()

Histogram = MyFile.Get("DataVnVsCentralityKaonPlusCorrected")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.GetYaxis().SetTitleOffset(1.5)

Histogram.SetAxisRange(-0.02, 0.02, "Y")

Histogram.Draw("PE 1 X0")

HistogramTemp = CameronFile.Get("p_vn_kp")

RescaledHistogram5 = ROOT.TH1F("CameronVnVsCentralityKaonPlusRescaled", "V3 vs Centrality for K+; Centrality; V3", 12, 0, 12)

for index in range(1, HistogramTemp.GetNbinsX() + 1):
    RescaledHistogram5.SetBinContent(17 - index, HistogramTemp.GetBinContent(index))
    RescaledHistogram5.SetBinError(17 - index, HistogramTemp.GetBinError(index))

RescaledHistogram5.SetDirectory(0)

RescaledHistogram5.SetStats(0)

RescaledHistogram5.SetLineWidth(3)
RescaledHistogram5.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogram5.SetMarkerSize(1.5)
RescaledHistogram5.SetMarkerColor(ROOT.kRed)
RescaledHistogram5.SetLineColor(ROOT.kRed)

RescaledHistogram5.SetAxisRange(-0.02, 0.02, "Y")

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

Legend5 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend5.AddEntry(Histogram, "My Work")
Legend5.AddEntry(RescaledHistogram5, "STAR 2023")
Legend5.Draw()

Canvasas.append(Canvas5)






Canvas6 = ROOT.TCanvas("Canvas6", "", 800, 800)
Canvas6.cd()

Histogram = MyFile.Get("DataVnVsCentralityKaonMinusCorrected")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetAxisRange(-0.1, 0.1, "Y")

Histogram.Draw("PE 1 X0")

HistogramTemp = CameronFile.Get("p_vn_km")

RescaledHistogram6 = ROOT.TH1F("CameronVnVsCentralityKaonMinusRescaled", "V3 vs Centrality for K-; Centrality; V3", 12, 0, 12)

for index in range(1, HistogramTemp.GetNbinsX() + 1):
    RescaledHistogram6.SetBinContent(17 - index, HistogramTemp.GetBinContent(index))
    RescaledHistogram6.SetBinError(17 - index, HistogramTemp.GetBinError(index))

RescaledHistogram6.SetDirectory(0)

RescaledHistogram6.SetStats(0)

RescaledHistogram6.SetLineWidth(3)
RescaledHistogram6.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogram6.SetMarkerSize(1.5)
RescaledHistogram6.SetMarkerColor(ROOT.kRed)
RescaledHistogram6.SetLineColor(ROOT.kRed)

Histogram.SetAxisRange(-0.1, 0.1, "Y")

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

Legend6 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend6.AddEntry(Histogram, "My Work")
Legend6.AddEntry(RescaledHistogram6, "STAR 2023")
Legend6.Draw()

Canvasas.append(Canvas6)





Canvas7 = ROOT.TCanvas("Canvas7", "", 800, 800)
Canvas7.cd()

Histogram = MyFile.Get("DataVnVsCentralityPionPlusCorrected")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetAxisRange(-0.01, 0.005, "Y")

Histogram.Draw("PE 1 X0")

HistogramTemp = CameronFile.Get("p_vn_pp")

RescaledHistogram7 = ROOT.TH1F("CameronVnVsCentralityPionPlusRescaled", "V3 vs Centrality for Pi+; Centrality; V3", 12, 0, 12)

for index in range(1, HistogramTemp.GetNbinsX() + 1):
    RescaledHistogram7.SetBinContent(17 - index, HistogramTemp.GetBinContent(index))
    RescaledHistogram7.SetBinError(17 - index, HistogramTemp.GetBinError(index))

RescaledHistogram7.SetDirectory(0)

RescaledHistogram7.SetStats(0)

RescaledHistogram7.SetLineWidth(3)
RescaledHistogram7.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogram7.SetMarkerSize(1.5)
RescaledHistogram7.SetMarkerColor(ROOT.kRed)
RescaledHistogram7.SetLineColor(ROOT.kRed)

RescaledHistogram7.SetAxisRange(-0.01, 0.005, "Y")

RescaledHistogram7.Draw("PE 1 X0 SAME")

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

Legend7 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend7.AddEntry(Histogram, "My Work")
Legend7.AddEntry(RescaledHistogram7, "STAR 2023")
Legend7.Draw()

Canvasas.append(Canvas7)




Canvas8 = ROOT.TCanvas("Canvas8", "", 800, 800)
Canvas8.cd()

Histogram = MyFile.Get("DataVnVsCentralityPionMinusCorrected")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(10)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(3)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("PE 1 X0")

HistogramTemp = CameronFile.Get("p_vn_pm")

RescaledHistogram8 = ROOT.TH1F("CameronVnVsCentralityPionMinusRescaled", "V3 vs Centrality for Pi-; Centrality; V3", 12, 0, 12)

for index in range(1, HistogramTemp.GetNbinsX() + 1):
    RescaledHistogram8.SetBinContent(17 - index, HistogramTemp.GetBinContent(index))
    RescaledHistogram8.SetBinError(17 - index, HistogramTemp.GetBinError(index))

RescaledHistogram8.SetDirectory(0)

RescaledHistogram8.SetStats(0)

RescaledHistogram8.SetLineWidth(3)
RescaledHistogram8.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogram8.SetMarkerSize(1.5)
RescaledHistogram8.SetMarkerColor(ROOT.kRed)
RescaledHistogram8.SetLineColor(ROOT.kRed)

RescaledHistogram8.Draw("PE 1 X0 SAME")

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

Legend8 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend8.AddEntry(Histogram, "My Work")
Legend8.AddEntry(RescaledHistogram8, "STAR 2023")
Legend8.Draw()

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

# Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityDeuteronCorrected_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityDeuteronCorrected_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

# Canvas9.Draw()

# Legend9 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend9.AddEntry(Histogram, "My Work")
# Legend9.AddEntry(RescaledHistogram9, "STAR 2023")
# Legend9.Draw()

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

Histogram.SetAxisRange(-0.5, 0.5, "Y")

Histogram.Draw("PE 1 X0")

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

Canvas10.Draw()

# Legend10 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend10.AddEntry(Histogram, "My Work")
# Legend10.AddEntry(RescaledHistogram10, "STAR 2023")
# Legend10.Draw()

Canvasas.append(Canvas10)





####################################################################################################### V3 vs Pt


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

HistogramA.SetAxisRange(-0.07, 0.0, "Y")

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

HistogramB.SetAxisRange(-0.07, 0.0, "Y")

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

Legend14 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend14.AddEntry(HistogramA, "My Work")
Legend14.AddEntry(HistogramB, "STAR 2023")
Legend14.Draw()

Canvasas.append(Canvas14)







Canvas15 = ROOT.TCanvas("Canvas15", "", 800, 800)
Canvas15.cd()

HistogramA = MyFile.Get("DataVnVsPtForProtonsCentrality10-40")

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

HistogramA.SetAxisRange(-0.07, 0.0, "Y")

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

HistogramB.SetAxisRange(-0.07, 0.0, "Y")

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

Legend15 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend15.AddEntry(HistogramA, "My Work")
Legend15.AddEntry(HistogramB, "STAR 2023")
Legend15.Draw()

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

HistogramA.SetAxisRange(-0.07, 0.0, "Y")

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

HistogramB.SetAxisRange(-0.07, 0.0, "Y")

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

Legend16 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend16.AddEntry(HistogramA, "My Work")
Legend16.AddEntry(HistogramB, "STAR 2023")
Legend16.Draw()

Canvasas.append(Canvas16)






Canvas18 = ROOT.TCanvas("Canvas18", "", 800, 800)
Canvas18.cd()

HistogramA = MyFile.Get("DataVnVsPtForKaonsPlusCentrality0-10")

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

HistogramB = CameronFile.Get("p2_vn_pT_cent_kp").ProfileY("p_vn_pT_00to10_kp", 15, 16)
#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.04, 0.04, "Y")

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

Canvas18.Draw()

Legend18 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend18.AddEntry(HistogramA, "My Work")
Legend18.AddEntry(HistogramB, "STAR 2023")
Legend18.Draw()

Canvasas.append(Canvas18)







Canvas19 = ROOT.TCanvas("Canvas19", "", 800, 800)
Canvas19.cd()

HistogramA = MyFile.Get("DataVnVsPtForKaonsPlusCentrality10-40")

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

HistogramB = CameronFile.Get("p2_vn_pT_cent_kp").ProfileY("p_vn_pT_10to40_kp", 9, 14)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.04, 0.04, "Y")

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

Canvas19.Draw()

Legend19 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend19.AddEntry(HistogramA, "My Work")
Legend19.AddEntry(HistogramB, "STAR 2023")
Legend19.Draw()

Canvasas.append(Canvas19)






Canvas20 = ROOT.TCanvas("Canvas20", "", 800, 800)
Canvas20.cd()

HistogramA = MyFile.Get("DataVnVsPtForKaonsPlusCentrality40-60")

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

HistogramB = CameronFile.Get("p2_vn_pT_cent_kp").ProfileY("p_vn_pT_40to60_kp", 5, 8)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.04, 0.04, "Y")

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

Canvas20.Draw()

Legend20 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend20.AddEntry(HistogramA, "My Work")
Legend20.AddEntry(HistogramB, "STAR 2023")
Legend20.Draw()

Canvasas.append(Canvas20)





Canvas21 = ROOT.TCanvas("Canvas21", "", 800, 800)
Canvas21.cd()

HistogramA = MyFile.Get("DataVnVsPtForKaonsMinusCentrality0-10")

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

HistogramA.SetAxisRange(-0.1, 0.1, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = CameronFile.Get("p2_vn_pT_cent_km").ProfileY("p_vn_pT_00to10_km", 15, 16)
#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.1, 0.1, "Y")

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

Canvas21.Draw()

Legend21 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend21.AddEntry(HistogramA, "My Work")
Legend21.AddEntry(HistogramB, "STAR 2023")
Legend21.Draw()

Canvasas.append(Canvas21)







Canvas22 = ROOT.TCanvas("Canvas22", "", 800, 800)
Canvas22.cd()

HistogramA = MyFile.Get("DataVnVsPtForKaonsMinusCentrality10-40")

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

HistogramA.SetAxisRange(-0.1, 0.1, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = CameronFile.Get("p2_vn_pT_cent_km").ProfileY("p_vn_pT_10to40_km", 9, 14)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.1, 0.1, "Y")

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

Canvas22.Draw()

Legend22 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend22.AddEntry(HistogramA, "My Work")
Legend22.AddEntry(HistogramB, "STAR 2023")
Legend22.Draw()

Canvasas.append(Canvas22)






Canvas23 = ROOT.TCanvas("Canvas23", "", 800, 800)
Canvas23.cd()

HistogramA = MyFile.Get("DataVnVsPtForKaonsMinusCentrality40-60")

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

HistogramA.SetAxisRange(-0.1, 0.1, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = CameronFile.Get("p2_vn_pT_cent_km").ProfileY("p_vn_pT_40to60_km", 5, 8)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.1, 0.1, "Y")

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

Canvas23.Draw()

Legend23 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend23.AddEntry(HistogramA, "My Work")
Legend23.AddEntry(HistogramB, "STAR 2023")
Legend23.Draw()

Canvasas.append(Canvas23)




Canvas24 = ROOT.TCanvas("Canvas24", "", 800, 800)
Canvas24.cd()

HistogramA = MyFile.Get("DataVnVsPtForPionsPlusCentrality0-10")

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

HistogramB = CameronFile.Get("p2_vn_pT_cent_pp").ProfileY("p_vn_pT_00to10_pp", 15, 16)
#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.05, 0.02, "Y")

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

Canvas24.Draw()

Legend24 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend24.AddEntry(HistogramA, "My Work")
Legend24.AddEntry(HistogramB, "STAR 2023")
Legend24.Draw()

Canvasas.append(Canvas24)







Canvas25 = ROOT.TCanvas("Canvas25", "", 800, 800)
Canvas25.cd()

HistogramA = MyFile.Get("DataVnVsPtForPionsPlusCentrality10-40")

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

HistogramB = CameronFile.Get("p2_vn_pT_cent_pp").ProfileY("p_vn_pT_10to40_pp", 9, 14)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.05, 0.02, "Y")

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

Canvas25.Draw()

Legend25 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend25.AddEntry(HistogramA, "My Work")
Legend25.AddEntry(HistogramB, "STAR 2023")
Legend25.Draw()

Canvasas.append(Canvas25)






Canvas26 = ROOT.TCanvas("Canvas26", "", 800, 800)
Canvas26.cd()

HistogramA = MyFile.Get("DataVnVsPtForPionsPlusCentrality40-60")

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

HistogramB = CameronFile.Get("p2_vn_pT_cent_pp").ProfileY("p_vn_pT_40to60_pp", 5, 8)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.05, 0.02, "Y")

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

Canvas26.Draw()

Legend26 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend26.AddEntry(HistogramA, "My Work")
Legend26.AddEntry(HistogramB, "STAR 2023")
Legend26.Draw()

Canvasas.append(Canvas26)





Canvas27 = ROOT.TCanvas("Canvas27", "", 800, 800)
Canvas27.cd()

HistogramA = MyFile.Get("DataVnVsPtForPionsMinusCentrality0-10")

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

HistogramB = CameronFile.Get("p2_vn_pT_cent_pm").ProfileY("p_vn_pT_00to10_pm", 15, 16)
#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.02, 0.02, "Y")

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

Canvas27.Draw()

Legend27 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend27.AddEntry(HistogramA, "My Work")
Legend27.AddEntry(HistogramB, "STAR 2023")
Legend27.Draw()

Canvasas.append(Canvas27)







Canvas28 = ROOT.TCanvas("Canvas28", "", 800, 800)
Canvas28.cd()

HistogramA = MyFile.Get("DataVnVsPtForPionsMinusCentrality10-40")

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

HistogramB = CameronFile.Get("p2_vn_pT_cent_pm").ProfileY("p_vn_pT_10to40_pm", 9, 14)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.02, 0.02, "Y")

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

Canvas28.Draw()

Legend28 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend28.AddEntry(HistogramA, "My Work")
Legend28.AddEntry(HistogramB, "STAR 2023")
Legend28.Draw()

Canvasas.append(Canvas28)






Canvas29 = ROOT.TCanvas("Canvas29", "", 800, 800)
Canvas29.cd()

HistogramA = MyFile.Get("DataVnVsPtForPionsMinusCentrality40-60")

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

HistogramB = CameronFile.Get("p2_vn_pT_cent_pm").ProfileY("p_vn_pT_40to60_pm", 5, 8)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.02, 0.02, "Y")

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

Canvas29.Draw()

Legend29 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend29.AddEntry(HistogramA, "My Work")
Legend29.AddEntry(HistogramB, "STAR 2023")
Legend29.Draw()

Canvasas.append(Canvas29)




Canvas30 = ROOT.TCanvas("Canvas30", "", 800, 800)
Canvas30.cd()

HistogramA = MyFile.Get("DataVnVsPtForDeuteronsCentrality0-10")

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

Canvas30.Draw()

# Legend30 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend30.AddEntry(HistogramA, "My Work")
# Legend30.AddEntry(HistogramB, "STAR 2023")
# Legend30.Draw()

Canvasas.append(Canvas30)







Canvas31 = ROOT.TCanvas("Canvas31", "", 800, 800)
Canvas31.cd()

HistogramA = MyFile.Get("DataVnVsPtForDeuteronsCentrality10-40")

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

Canvas31.Draw()

# Legend31 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend31.AddEntry(HistogramA, "My Work")
# Legend31.AddEntry(HistogramB, "STAR 2023")
# Legend31.Draw()

Canvasas.append(Canvas31)






Canvas32 = ROOT.TCanvas("Canvas32", "", 800, 800)
Canvas32.cd()

HistogramA = MyFile.Get("DataVnVsPtForDeuteronsCentrality40-60")

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

Canvas32.Draw()

# Legend32 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend32.AddEntry(HistogramA, "My Work")
# Legend32.AddEntry(HistogramB, "STAR 2023")
# Legend32.Draw()

Canvasas.append(Canvas32)




Canvas33 = ROOT.TCanvas("Canvas33", "", 800, 800)
Canvas33.cd()

HistogramA = MyFile.Get("DataVnVsPtForTritonsCentrality0-10")

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

Canvas33.Draw()

# Legend33 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend33.AddEntry(HistogramA, "My Work")
# Legend33.AddEntry(HistogramB, "STAR 2023")
# Legend33.Draw()

Canvasas.append(Canvas33)







Canvas34 = ROOT.TCanvas("Canvas34", "", 800, 800)
Canvas34.cd()

HistogramA = MyFile.Get("DataVnVsPtForTritonsCentrality10-40")

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

Canvas34.Draw()

# Legend34 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend34.AddEntry(HistogramA, "My Work")
# Legend34.AddEntry(HistogramB, "STAR 2023")
# Legend34.Draw()

Canvasas.append(Canvas34)






Canvas35 = ROOT.TCanvas("Canvas35", "", 800, 800)
Canvas35.cd()

HistogramA = MyFile.Get("DataVnVsPtForTritonsCentrality40-60")

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

Canvas35.Draw()

# Legend35 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend35.AddEntry(HistogramA, "My Work")
# Legend35.AddEntry(HistogramB, "STAR 2023")
# Legend35.Draw()

Canvasas.append(Canvas35)



####################################################################################################### V3 vs Rapidity



Canvas1 = ROOT.TCanvas("Canvas1", "", 800, 800)
Canvas1.cd()

HistogramA = MyFile.Get("DataVnVsYForProtonsCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Protons, 0-10% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.SetAxisRange(-0.05, 0.0, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = CameronFile.Get("p2_vn_yCM_cent_pr").ProfileY("p_vn_yCM_00to10_pr", 15, 16)
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.05, 0.0, "Y")

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

Legend1 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend1.AddEntry(HistogramA, "My Work")
Legend1.AddEntry(HistogramB, "STAR 2023")
Legend1.Draw()

Canvasas.append(Canvas1)



Canvas2 = ROOT.TCanvas("Canvas2", "", 800, 800)
Canvas2.cd()

HistogramA = MyFile.Get("DataVnVsYForProtonsCentrality10-40")

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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_pr").ProfileY("p_vn_yCM_10to40_pr", 9, 14)

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.05, 0.0, "Y")

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

Legend2 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend2.AddEntry(HistogramA, "My Work")
Legend2.AddEntry(HistogramB, "STAR 2023")
Legend2.Draw()

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

HistogramA.SetAxisRange(-0.05, 0.0, "Y")

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

HistogramB.SetAxisRange(-0.05, 0.0, "Y")

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

Legend3 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend3.AddEntry(HistogramA, "My Work")
Legend3.AddEntry(HistogramB, "STAR 2023")
Legend3.Draw()

Canvasas.append(Canvas3)





Canvas1A = ROOT.TCanvas("Canvas1A", "", 800, 800)
Canvas1A.cd()

HistogramA = MyFile.Get("DataVnVsYForKaonsPlusCentrality0-10")
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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_kp").ProfileY("p_vn_yCM_0to10_kp", 15, 16)

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.03, 0.03, "Y")

HistogramB.Draw("PE 1 X0 SAME")

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

Legend1A = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend1A.AddEntry(HistogramA, "My Work")
Legend1A.AddEntry(HistogramB, "STAR 2023")
Legend1A.Draw()

Canvasas.append(Canvas1A)









Canvas2A = ROOT.TCanvas("Canvas2A", "", 800, 800)
Canvas2A.cd()

HistogramA = MyFile.Get("DataVnVsYForKaonsPlusCentrality10-40")
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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_kp").ProfileY("p_vn_yCM_10to40_kp", 9, 14)

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.03, 0.03, "Y")

HistogramB.Draw("PE 1 X0 SAME")

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

Legend2A = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend2A.AddEntry(HistogramA, "My Work")
Legend2A.AddEntry(HistogramB, "STAR 2023")
Legend2A.Draw()

Canvasas.append(Canvas2A)






Canvas3A = ROOT.TCanvas("Canvas3A", "", 800, 800)
Canvas3A.cd()

HistogramA = MyFile.Get("DataVnVsYForKaonsPlusCentrality40-60")
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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_kp").ProfileY("p_vn_yCM_40to60_kp", 5, 8)

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.03, 0.03, "Y")

HistogramB.Draw("PE 1 X0 SAME")

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

Legend3A = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend3A.AddEntry(HistogramA, "My Work")
Legend3A.AddEntry(HistogramB, "STAR 2023")
Legend3A.Draw()

Canvasas.append(Canvas3A)




Canvas1B = ROOT.TCanvas("Canvas1B", "", 800, 800)
Canvas1B.cd()

HistogramA = MyFile.Get("DataVnVsYForKaonsMinusCentrality0-10")
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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_km").ProfileY("p_vn_yCM_0to10_km", 15, 16)

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.1, 0.1, "Y")

HistogramB.Draw("PE 1 X0 SAME")

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

Legend1B = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend1B.AddEntry(HistogramA, "My Work")
Legend1B.AddEntry(HistogramB, "STAR 2023")
Legend1B.Draw()

Canvasas.append(Canvas1B)









Canvas2B = ROOT.TCanvas("Canvas2B", "", 800, 800)
Canvas2B.cd()

HistogramA = MyFile.Get("DataVnVsYForKaonsMinusCentrality10-40")
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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_km").ProfileY("p_vn_yCM_10to40_km", 9, 14)

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.1, 0.1, "Y")

HistogramB.Draw("PE 1 X0 SAME")

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

Legend2B = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend2B.AddEntry(HistogramA, "My Work")
Legend2B.AddEntry(HistogramB, "STAR 2023")
Legend2B.Draw()

Canvasas.append(Canvas2B)






Canvas3B = ROOT.TCanvas("Canvas3B", "", 800, 800)
Canvas3B.cd()

HistogramA = MyFile.Get("DataVnVsYForKaonsMinusCentrality40-60")
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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_km").ProfileY("p_vn_yCM_40to60_km", 5, 8)

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.1, 0.1, "Y")

HistogramB.Draw("PE 1 X0 SAME")

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

Legend3B = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend3B.AddEntry(HistogramA, "My Work")
Legend3B.AddEntry(HistogramB, "STAR 2023")
Legend3B.Draw()

Canvasas.append(Canvas3B)




Canvas1C = ROOT.TCanvas("Canvas1C", "", 800, 800)
Canvas1C.cd()

HistogramA = MyFile.Get("DataVnVsYForPionsPlusCentrality0-10")

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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_pp").ProfileY("p_vn_yCM_0to10_pp", 15, 16)

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.01, 0.01, "Y")

HistogramB.Draw("PE 1 X0 SAME")

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

Legend1C = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend1C.AddEntry(HistogramA, "My Work")
Legend1C.AddEntry(HistogramB, "STAR 2023")
Legend1C.Draw()

Canvasas.append(Canvas1C)









Canvas2C = ROOT.TCanvas("Canvas2C", "", 800, 800)
Canvas2C.cd()

HistogramA = MyFile.Get("DataVnVsYForPionsPlusCentrality10-40")
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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_pp").ProfileY("p_vn_yCM_10to40_pp", 9, 14)

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.01, 0.01, "Y")

HistogramB.Draw("PE 1 X0 SAME")

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

Legend2C = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend2C.AddEntry(HistogramA, "My Work")
Legend2C.AddEntry(HistogramB, "STAR 2023")
Legend2C.Draw()

Canvasas.append(Canvas2C)






Canvas3C = ROOT.TCanvas("Canvas3C", "", 800, 800)
Canvas3C.cd()

HistogramA = MyFile.Get("DataVnVsYForPionsPlusCentrality40-60")
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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_pp").ProfileY("p_vn_yCM_40to60_pp", 5, 8)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.01, 0.01, "Y")

HistogramB.Draw("PE 1 X0 SAME")

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

Legend3C = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend3C.AddEntry(HistogramA, "My Work")
Legend3C.AddEntry(HistogramB, "STAR 2023")
Legend3C.Draw()

Canvasas.append(Canvas3C)




Canvas1D = ROOT.TCanvas("Canvas1D", "", 800, 800)
Canvas1D.cd()

HistogramA = MyFile.Get("DataVnVsYForPionsMinusCentrality0-10")
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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_pm").ProfileY("p_vn_yCM_0to10_pm", 15, 16)

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.01, 0.003, "Y")

HistogramB.Draw("PE 1 X0 SAME")

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

Legend1D = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend1D.AddEntry(HistogramA, "My Work")
Legend1D.AddEntry(HistogramB, "STAR 2023")
Legend1D.Draw()

Canvasas.append(Canvas1D)









Canvas2D = ROOT.TCanvas("Canvas2D", "", 800, 800)
Canvas2D.cd()

HistogramA = MyFile.Get("DataVnVsYForPionsMinusCentrality10-40")

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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_pm").ProfileY("p_vn_yCM_10to40_pm", 9, 14)

#print(Histogram.GetEntries())
HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.01, 0.003, "Y")

HistogramB.Draw("PE 1 X0 SAME")

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

Legend2D = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend2D.AddEntry(HistogramA, "My Work")
Legend2D.AddEntry(HistogramB, "STAR 2023")
Legend2D.Draw()

Canvasas.append(Canvas2D)






Canvas3D = ROOT.TCanvas("Canvas3D", "", 800, 800)
Canvas3D.cd()

HistogramA = MyFile.Get("DataVnVsYForPionsMinusCentrality40-60")

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

HistogramB = CameronFile.Get("p2_vn_yCM_cent_pm").ProfileY("p_vn_yCM_40to60_pm", 5, 8)

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetAxisRange(-0.01, 0.003, "Y")

HistogramB.Draw("PE 1 X0 SAME")

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

Legend3D = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend3D.AddEntry(HistogramA, "My Work")
Legend3D.AddEntry(HistogramB, "STAR 2023")
Legend3D.Draw()

Canvasas.append(Canvas3D)





Canvas1E = ROOT.TCanvas("Canvas1E", "", 800, 800)
Canvas1E.cd()

HistogramA = MyFile.Get("DataVnVsYForDeuteronsCentrality0-10")

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

# Legend1E = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend1E.AddEntry(HistogramA, "My Work")
# Legend1E.AddEntry(HistogramB, "STAR 2023")
# Legend1E.Draw()

Canvasas.append(Canvas1E)




Canvas2E = ROOT.TCanvas("Canvas2E", "", 800, 800)
Canvas2E.cd()

HistogramA = MyFile.Get("DataVnVsYForDeuteronsCentrality10-40")

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

# Legend2E = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend2E.AddEntry(HistogramA, "My Work")
# Legend2E.AddEntry(HistogramB, "STAR 2023")
# Legend2E.Draw()

Canvasas.append(Canvas2E)






Canvas3E = ROOT.TCanvas("Canvas3E", "", 800, 800)
Canvas3E.cd()

HistogramA = MyFile.Get("DataVnVsYForDeuteronsCentrality40-60")

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

# Legend3E = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend3E.AddEntry(HistogramA, "My Work")
# Legend3E.AddEntry(HistogramB, "STAR 2023")
# Legend3E.Draw()

Canvasas.append(Canvas3E)






Canvas1F = ROOT.TCanvas("Canvas1F", "", 800, 800)
Canvas1F.cd()

HistogramA = MyFile.Get("DataVnVsYForTritonsCentrality0-10")

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

# Legend1F = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend1F.AddEntry(HistogramA, "My Work")
# Legend1F.AddEntry(HistogramB, "STAR 2023")
# Legend1F.Draw()

Canvasas.append(Canvas1F)









Canvas2F = ROOT.TCanvas("Canvas2F", "", 800, 800)
Canvas2F.cd()

HistogramA = MyFile.Get("DataVnVsYForTritonsCentrality10-40")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V3 vs Y for Tritons, 10-40% Centrality")

HistogramA.Draw("PE 1 X0")

HistogramA.SetAxisRange(-0.1, 0.05, "Y")

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

# Legend2F = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend2F.AddEntry(HistogramA, "My Work")
# Legend2F.AddEntry(HistogramB, "STAR 2023")
# Legend2F.Draw()

Canvasas.append(Canvas2F)






Canvas3F = ROOT.TCanvas("Canvas3F", "", 800, 800)
Canvas3F.cd()

HistogramA = MyFile.Get("DataVnVsYForTritonsCentrality40-60")

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

# Legend3F = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
# Legend3F.AddEntry(HistogramA, "My Work")
# Legend3F.AddEntry(HistogramB, "STAR 2023")
# Legend3F.Draw()

Canvasas.append(Canvas3F)






####################################################################################################### Vn vs Y Symmetric Plots


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

Canvas11.Draw()

Legend11 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend11.AddEntry(HistogramA, "My Work")
Legend11.AddEntry(HistogramB, "STAR 2023")
Legend11.Draw()

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

Canvas12.Draw()

Legend12 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend12.AddEntry(HistogramA, "My Work")
Legend12.AddEntry(HistogramB, "STAR 2023")
Legend12.Draw()

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

Legend13 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend13.AddEntry(HistogramA, "My Work")
Legend13.AddEntry(HistogramB, "STAR 2023")
Legend13.Draw()

Canvasas.append(Canvas13)


####################################################################################################### Scaling Plots


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

MyFile.Close()
CameronFile.Close()
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
