#!/usr/bin/env python
# coding: utf-8



import ROOT
import os
import sys

Canvasas = []

Date = '2-31-23'





MyFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/" + Date +"-V3-Histograms.root","READ")
ResolutionPlotFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/resolutionPlot.root","READ")
CameronFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/v3_results.root","READ")




CentralityXLabels = ["0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60"]




Canvas0 = ROOT.TCanvas("Canvas0", "", 800, 800)
Canvas0.cd()

Histogram = MyFile.Get("DataResolution")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

for index in range(1, Histogram.GetNbinsX() + 1):
    Histogram.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])

Histogram.Draw("PE 1 X0")

Histogram = ResolutionPlotFile.Get("h_resolutions")

RescaledHistogram1 = ROOT.TH1F("CameronResolutionRescaled", " ; ; ", 12, 0, 12)

RescaledHistogram1.SetDirectory(0)

RescaledHistogram1.SetStats(0)

RescaledHistogram1.SetLineWidth(3)

for index in range(1, Histogram.GetNbinsX() + 1):
    RescaledHistogram1.SetBinContent(index, Histogram.GetBinContent(index))
    RescaledHistogram1.SetBinError(index, Histogram.GetBinError(index))
    RescaledHistogram1.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])

RescaledHistogram1.SetLineWidth(3)
RescaledHistogram1.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogram1.SetMarkerSize(1.5)
RescaledHistogram1.SetMarkerColor(ROOT.kRed)

RescaledHistogram1.SetLineColor(ROOT.kRed)

RescaledHistogram1.Draw("PE 1 X0 SAME")

Canvas0.Draw()

Canvasas.append(Canvas0)



ResolutionPlotFile.Close()




Canvas1 = ROOT.TCanvas("Canvas1", "", 800, 800)
Canvas1.cd()

Histogram = MyFile.Get("DataV3VsYForProtonsCentrality0-10")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Protons, 0-10% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_yCM_00to10_pr_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

Canvas1.Draw()

Canvasas.append(Canvas1)









Canvas2 = ROOT.TCanvas("Canvas2", "", 800, 800)
Canvas2.cd()

Histogram = MyFile.Get("DataV3VsYForProtonsCentrality10-40")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Protons, 10-40% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_yCM_10to40_pr_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

Canvas2.Draw()

Canvasas.append(Canvas2)






Canvas3 = ROOT.TCanvas("Canvas3", "", 800, 800)
Canvas3.cd()

Histogram = MyFile.Get("DataV3VsYForProtonsCentrality40-60")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Protons, 40-60% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_yCM_40to60_pr_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

Canvas3.Draw()

Canvasas.append(Canvas3)





Canvas1A = ROOT.TCanvas("Canvas1A", "", 800, 800)
Canvas1A.cd()

Histogram = MyFile.Get("DataV3VsYForKaonsPlusCentrality0-10")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Kaons Plus, 0-10% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_yCM_00to10_kp_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

Canvas1A.Draw()

Canvasas.append(Canvas1A)









Canvas2A = ROOT.TCanvas("Canvas2A", "", 800, 800)
Canvas2A.cd()

Histogram = MyFile.Get("DataV3VsYForKaonsPlusCentrality10-40")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Kaons Plus, 10-40% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_yCM_10to40_kp_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

Canvas2A.Draw()

Canvasas.append(Canvas2A)






Canvas3A = ROOT.TCanvas("Canvas3A", "", 800, 800)
Canvas3A.cd()

Histogram = MyFile.Get("DataV3VsYForKaonsPlusCentrality40-60")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Kaons Plus, 40-60% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_yCM_40to60_kp_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

Canvas3A.Draw()

Canvasas.append(Canvas3A)




Canvas1B = ROOT.TCanvas("Canvas1B", "", 800, 800)
Canvas1B.cd()

Histogram = MyFile.Get("DataV3VsYForKaonsMinusCentrality0-10")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Kaons Minus, 0-10% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_yCM_00to10_km_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

Canvas1B.Draw()

Canvasas.append(Canvas1B)









Canvas2B = ROOT.TCanvas("Canvas2B", "", 800, 800)
Canvas2B.cd()

Histogram = MyFile.Get("DataV3VsYForKaonsMinusCentrality10-40")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Kaons Minus, 10-40% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_yCM_10to40_km_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

Canvas2B.Draw()

Canvasas.append(Canvas2B)






Canvas3B = ROOT.TCanvas("Canvas3B", "", 800, 800)
Canvas3B.cd()

Histogram = MyFile.Get("DataV3VsYForKaonsMinusCentrality40-60")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Kaons Minus, 40-60% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_yCM_40to60_km_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

Canvas3B.Draw()

Canvasas.append(Canvas3B)




Canvas1C = ROOT.TCanvas("Canvas1C", "", 800, 800)
Canvas1C.cd()

Histogram = MyFile.Get("DataV3VsYForPionsPlusCentrality0-10")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Pions Plus, 0-10% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_yCM_00to10_pp_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

Canvas1C.Draw()

Canvasas.append(Canvas1C)









Canvas2C = ROOT.TCanvas("Canvas2C", "", 800, 800)
Canvas2C.cd()

Histogram = MyFile.Get("DataV3VsYForPionsPlusCentrality10-40")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Pions Plus, 10-40% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_yCM_10to40_pp_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

Canvas2C.Draw()

Canvasas.append(Canvas2C)






Canvas3C = ROOT.TCanvas("Canvas3C", "", 800, 800)
Canvas3C.cd()

Histogram = MyFile.Get("DataV3VsYForPionsPlusCentrality40-60")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Pions Plus, 40-60% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_yCM_40to60_pp_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

Canvas3C.Draw()

Canvasas.append(Canvas3C)




Canvas1D = ROOT.TCanvas("Canvas1D", "", 800, 800)
Canvas1D.cd()

Histogram = MyFile.Get("DataV3VsYForPionsMinusCentrality0-10")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Pions Minus, 0-10% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_yCM_00to10_pm_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

Canvas1D.Draw()

Canvasas.append(Canvas1D)









Canvas2D = ROOT.TCanvas("Canvas2D", "", 800, 800)
Canvas2D.cd()

Histogram = MyFile.Get("DataV3VsYForPionsMinusCentrality10-40")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Pions Minus, 10-40% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_yCM_10to40_pm_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

Canvas2D.Draw()

Canvasas.append(Canvas2D)






Canvas3D = ROOT.TCanvas("Canvas3D", "", 800, 800)
Canvas3D.cd()

Histogram = MyFile.Get("DataV3VsYForPionsMinusCentrality40-60")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.SetTitle("V3 vs Y for Pions Minus, 40-60% Centrality")

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_yCM_40to60_pm_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullSquare)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kRed)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("PE 1 X0 SAME")

Canvas3D.Draw()

Canvasas.append(Canvas3D)





Canvas4 = ROOT.TCanvas("Canvas4", "", 800, 800)
Canvas4.cd()

Histogram = MyFile.Get("DataVnVsCentralityProtonCorrected")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

for index in range(1, Histogram.GetNbinsX() + 1):
    Histogram.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_pr_px_flip")

RescaledHistogram4 = ROOT.TH1F("CameronV3VsCentralityProtonRescaled", "V3 vs Centrality for Protons; Centrality; V3", 12, 0, 12)

RescaledHistogram4.SetDirectory(0)

RescaledHistogram4.SetStats(0)

for index in range(1, Histogram.GetNbinsX() + 1):
    RescaledHistogram4.SetBinContent(index, Histogram.GetBinContent(index))
    RescaledHistogram4.SetBinError(index, Histogram.GetBinError(index))
    RescaledHistogram4.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])

    
RescaledHistogram4.SetLineWidth(3)
RescaledHistogram4.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogram4.SetMarkerSize(1.5)
RescaledHistogram4.SetMarkerColor(ROOT.kRed)
RescaledHistogram4.SetLineColor(ROOT.kRed)

RescaledHistogram4.Draw("PE 1 X0 SAME")

Canvas4.Draw()

Canvasas.append(Canvas4)





Canvas5 = ROOT.TCanvas("Canvas5", "", 800, 800)
Canvas5.cd()

Histogram = MyFile.Get("DataVnVsCentralityKaonPlusCorrected")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_kp_px_flip")

RescaledHistogram5 = ROOT.TH1F("CameronV3VsCentralityKaonPlusRescaled", "V3 vs Centrality for K+; Centrality; V3", 12, 0, 12)

for index in range(1, Histogram.GetNbinsX() + 1):
    RescaledHistogram5.SetBinContent(index, Histogram.GetBinContent(index))
    RescaledHistogram5.SetBinError(index, Histogram.GetBinError(index))

RescaledHistogram5.SetDirectory(0)

RescaledHistogram5.SetStats(0)

RescaledHistogram5.SetLineWidth(3)
RescaledHistogram5.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogram5.SetMarkerSize(1.5)
RescaledHistogram5.SetMarkerColor(ROOT.kRed)
RescaledHistogram5.SetLineColor(ROOT.kRed)

RescaledHistogram5.Draw("PE 1 X0 SAME")

Canvas5.Draw()

Canvasas.append(Canvas5)






Canvas6 = ROOT.TCanvas("Canvas6", "", 800, 800)
Canvas6.cd()

Histogram = MyFile.Get("DataVnVsCentralityKaonMinusCorrected")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_km_px_flip")

RescaledHistogram6 = ROOT.TH1F("CameronV3VsCentralityKaonMinusRescaled", "V3 vs Centrality for K-; Centrality; V3", 12, 0, 12)

for index in range(1, Histogram.GetNbinsX() + 1):
    RescaledHistogram6.SetBinContent(index, Histogram.GetBinContent(index))
    RescaledHistogram6.SetBinError(index, Histogram.GetBinError(index))

RescaledHistogram6.SetDirectory(0)

RescaledHistogram6.SetStats(0)

RescaledHistogram6.SetLineWidth(3)
RescaledHistogram6.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogram6.SetMarkerSize(1.5)
RescaledHistogram6.SetMarkerColor(ROOT.kRed)
RescaledHistogram6.SetLineColor(ROOT.kRed)

RescaledHistogram6.Draw("PE 1 X0 SAME")

Canvas6.Draw()

Canvasas.append(Canvas6)





Canvas7 = ROOT.TCanvas("Canvas7", "", 800, 800)
Canvas7.cd()

Histogram = MyFile.Get("DataVnVsCentralityPionPlusCorrected")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_pp_px_flip")

RescaledHistogram7 = ROOT.TH1F("CameronV3VsCentralityPionPlusRescaled", "V3 vs Centrality for Pi+; Centrality; V3", 12, 0, 12)

for index in range(1, Histogram.GetNbinsX() + 1):
    RescaledHistogram7.SetBinContent(index, Histogram.GetBinContent(index))
    RescaledHistogram7.SetBinError(index, Histogram.GetBinError(index))

RescaledHistogram7.SetDirectory(0)

RescaledHistogram7.SetStats(0)

RescaledHistogram7.SetLineWidth(3)
RescaledHistogram7.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogram7.SetMarkerSize(1.5)
RescaledHistogram7.SetMarkerColor(ROOT.kRed)
RescaledHistogram7.SetLineColor(ROOT.kRed)

RescaledHistogram7.Draw("PE 1 X0 SAME")

Canvas7.Draw()

Canvasas.append(Canvas7)




Canvas8 = ROOT.TCanvas("Canvas8", "", 800, 800)
Canvas8.cd()

Histogram = MyFile.Get("DataVnVsCentralityPionMinusCorrected")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("PE 1 X0")

Histogram = CameronFile.Get("p_vn_pm_px_flip")

RescaledHistogram8 = ROOT.TH1F("CameronV3VsCentralityPionMinusRescaled", "V3 vs Centrality for Pi-; Centrality; V3", 12, 0, 12)

for index in range(1, Histogram.GetNbinsX() + 1):
    RescaledHistogram8.SetBinContent(index, Histogram.GetBinContent(index))
    RescaledHistogram8.SetBinError(index, Histogram.GetBinError(index))

RescaledHistogram8.SetDirectory(0)

RescaledHistogram8.SetStats(0)

RescaledHistogram8.SetLineWidth(3)
RescaledHistogram8.SetMarkerStyle(ROOT.kFullSquare)
RescaledHistogram8.SetMarkerSize(1.5)
RescaledHistogram8.SetMarkerColor(ROOT.kRed)
RescaledHistogram8.SetLineColor(ROOT.kRed)

RescaledHistogram8.Draw("PE 1 X0 SAME")

Canvas8.Draw()

Canvasas.append(Canvas8)



MyFile.Close()
CameronFile.Close()



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
