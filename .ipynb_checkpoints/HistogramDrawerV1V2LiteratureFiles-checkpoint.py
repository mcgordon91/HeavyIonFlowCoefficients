#!/usr/bin/env python
# coding: utf-8



import ROOT
import os
import sys

Canvasas = []

nV = 1
Date = '8-17-24'





GraphRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/LiteratureFiles/HEPData-ins1897294-v1-fig2.root","READ")
HistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/" + Date + "-V1-HistogramNormal.root","READ")
ResolutionFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/R_11_Normal.root","READ")


Graph = GraphRootFile.Get("/fig2/Graph1D_y1")
Resolution = ResolutionFile.Get("DataResolution")

Resolution.SetDirectory(0)
Resolution.SetLineWidth(3)
Resolution.SetLineColor(ROOT.kBlue)
Resolution.SetMarkerStyle(ROOT.kFullCircle)
Resolution.SetMarkerSize(1.5)
Resolution.SetMarkerColor(ROOT.kBlue)

Canvas1 = ROOT.TCanvas("Canvas1", "", 800, 800)

for index in range(1, Resolution.GetNbinsX()):
    print(Resolution.GetBinContent(index))

Canvas1.cd()

Resolution.SetStats(0)
Resolution.SetLineWidth(3)

Resolution.GetYaxis().SetTitleOffset(1.5)

Resolution.Draw("P* E1 X0")

NewGraph1 = ROOT.TGraphAsymmErrors()
NewGraph1.SetMarkerSize(3)
NewGraph1.SetMarkerColor(ROOT.kRed)
NewGraph1.SetLineWidth(3)
NewGraph1.SetLineColor(ROOT.kRed)

for index in range(0, 8):
    NewGraph1.SetPoint(index, Graph.GetX()[index] / 5, Graph.GetY()[index])
    NewGraph1.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))

NewGraph1.Draw("* SAME")

#Graph.Draw("AP*")

Canvas1.Draw()

Legend1 = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend1.AddEntry(Resolution, "My Work")
Legend1.AddEntry(NewGraph1, "STAR 2021")
Legend1.Draw()

Canvasas.append(Canvas1)



GraphRootFile.Close()
ResolutionFile.Close()







GraphRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/LiteratureFiles/HEPData-ins1897294-v1-fig3_top.root","READ")
SystematicErrorRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/systematicErrorsV1.root","READ")



Graph = GraphRootFile.Get("/fig3 top/Graph1D_y1")

Histogram = HistogramRootFile.Get("DataVnVsYForProtonsCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V1 vs Y for Protons, 10-40% Centrality")

Canvas2 = ROOT.TCanvas("Canvas2", "", 800, 800)

Canvas2.cd()

Histogram.SetStats(0)

Histogram.GetYaxis().SetTitleOffset(1.5)

Histogram.Draw("PE 1 X0")

NewGraph2 = ROOT.TGraphAsymmErrors()
NewGraph2.SetMarkerSize(3)
NewGraph2.SetMarkerColor(ROOT.kRed)
NewGraph2.SetLineWidth(3)
NewGraph2.SetLineColor(ROOT.kRed)

for index in range(0, Graph.GetN()):
    NewGraph2.SetPoint(index, -1 * Graph.GetX()[index], -1 * Graph.GetY()[index])
    NewGraph2.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))

NewGraph2.Draw("* SAME")

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

# Graph = CameronSystematicErrorRootFile.Get("/Figure 7/Graph1D_y1")

# for i in range(0, Graph.GetN()):
#     Graph.SetPointError(i, SystematicErrorWidth, SystematicErrorWidth, Graph.GetErrorY(i), Graph.GetErrorY(i))
    
# Graph.SetMarkerSize(3)
# Graph.SetMarkerColor(ROOT.kRed)
# Graph.SetLineWidth(3)
# Graph.SetLineColor(ROOT.kRed)
# Graph.SetFillColorAlpha(ROOT.kRed, 0.3)

# Graph.Draw("P* E2 SAME")

Canvas2.Draw()

Legend2 = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend2.AddEntry(Histogram, "My Work")
Legend2.AddEntry(NewGraph2, "STAR 2021")
Legend2.Draw()

Canvasas.append(Canvas2)




'''
Graph = GraphRootFile.Get("/fig3 top/Graph1D_y5")

Histogram = HistogramRootFile.Get("DataVnVsYForKaonsPlusCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V1 vs Y for Kaons Plus, 10-40% Centrality")

Canvas3 = ROOT.TCanvas("Canvas3", "", 800, 800)

Canvas3.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

NewGraph3 = ROOT.TGraphAsymmErrors()
NewGraph3.SetMarkerSize(3)
NewGraph3.SetMarkerColor(ROOT.kRed)
NewGraph3.SetLineWidth(3)
NewGraph3.SetLineColor(ROOT.kRed)

for index in range(0, Graph.GetN()):
    NewGraph3.SetPoint(index, -1 * Graph.GetX()[index], -1 * Graph.GetY()[index])
    NewGraph3.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))

NewGraph3.Draw("* SAME")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForKaonsPlusCentrality10-40_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForKaonsPlusCentrality10-40_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas3.Draw()

Legend3 = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend3.AddEntry(Histogram, "My Work")
Legend3.AddEntry(NewGraph2, "STAR 2021")
Legend3.Draw()

Canvasas.append(Canvas3)




Graph = GraphRootFile.Get("/fig3 top/Graph1D_y6")

Histogram = HistogramRootFile.Get("DataVnVsYForKaonsMinusCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V1 vs Y for Kaons Minus, 10-40% Centrality")

Canvas4 = ROOT.TCanvas("Canvas4", "", 800, 800)

Canvas4.cd()

Histogram.SetStats(0)

Histogram.Draw("P* E1 X0")

NewGraph4 = ROOT.TGraphAsymmErrors()
NewGraph4.SetMarkerSize(3)
NewGraph4.SetMarkerColor(ROOT.kRed)
NewGraph4.SetLineWidth(3)
NewGraph4.SetLineColor(ROOT.kRed)

for index in range(0, Graph.GetN()):
    NewGraph4.SetPoint(index, -1 * Graph.GetX()[index], -1 * Graph.GetY()[index])
    NewGraph4.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))

NewGraph4.Draw("* SAME")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForKaonsMinusCentrality10-40_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForKaonsMinusCentrality10-40_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas4.Draw()

Legend4 = ROOT.TLegend(0.5, 0.1, 0.7, 0.2)
Legend4.AddEntry(Histogram, "My Work")
Legend4.AddEntry(NewGraph4, "STAR 2021")
Legend4.Draw()

Canvasas.append(Canvas4)




Graph = GraphRootFile.Get("/fig3 top/Graph1D_y3")

Histogram = HistogramRootFile.Get("DataVnVsYForPionsPlusCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V1 vs Y for Pions Plus, 10-40% Centrality")

Canvas5 = ROOT.TCanvas("Canvas5", "", 800, 800)

Canvas5.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

NewGraph5 = ROOT.TGraphAsymmErrors()
NewGraph5.SetMarkerSize(3)
NewGraph5.SetMarkerColor(ROOT.kRed)
NewGraph5.SetLineWidth(3)
NewGraph5.SetLineColor(ROOT.kRed)

for index in range(0, Graph.GetN()):
    NewGraph5.SetPoint(index, -1 * Graph.GetX()[index], -1 * Graph.GetY()[index])
    NewGraph5.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))

NewGraph5.Draw("* SAME")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForPionsPlusCentrality10-40_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForPionsPlusCentrality10-40_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas5.Draw()

Legend5 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend5.AddEntry(Resolution, "My Work")
Legend5.AddEntry(NewGraph5, "STAR 2021")
Legend5.Draw()

Canvasas.append(Canvas5)





Graph = GraphRootFile.Get("/fig3 top/Graph1D_y4")

Histogram = HistogramRootFile.Get("DataVnVsYForPionsMinusCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V1 vs Y for Pions Minus, 10-40% Centrality")

Canvas6 = ROOT.TCanvas("Canvas6", "", 800, 800)

Canvas6.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

NewGraph6 = ROOT.TGraphAsymmErrors()
NewGraph6.SetMarkerSize(3)
NewGraph6.SetMarkerColor(ROOT.kRed)
NewGraph6.SetLineWidth(3)
NewGraph6.SetLineColor(ROOT.kRed)

for index in range(0, Graph.GetN()):
    NewGraph6.SetPoint(index, -1 * Graph.GetX()[index], -1 * Graph.GetY()[index])
    NewGraph6.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))

NewGraph6.Draw("* SAME")

Canvas6.Draw()

Histogram = SystematicErrorRootFile.Get("DataVnVsYForPionsMinusCentrality10-40_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForPionsMinusCentrality10-40_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Legend6 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend6.AddEntry(Resolution, "My Work")
Legend6.AddEntry(NewGraph2, "STAR 2021")
Legend6.Draw()

Canvasas.append(Canvas6)




GraphRootFile.Close()
'''



GraphRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/HEPData-ins1986611-v1-Figure_5a_proton,_deuteron,_and_^{3}He.root","READ")

Graph = GraphRootFile.Get("/Figure 5a proton, deuteron, and ^{3}He/Graph1D_y2")

Histogram = HistogramRootFile.Get("DataVnVsYForDeuteronsCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V1 vs Y for Deuterons, 10-40% Centrality")

Canvas6A = ROOT.TCanvas("Canvas6A", "", 800, 800)

Canvas6A.cd()

Histogram.SetStats(0)


for index in range(1, Histogram.GetNbinsX() + 1):
    print(Histogram.GetBinContent(index), Histogram.GetBinError(index))
print()

Histogram.Draw("PE 1 X0")

NewGraph6A = ROOT.TGraphErrors()#AsymmErrors()
NewGraph6A.SetMarkerSize(3)
NewGraph6A.SetMarkerColor(ROOT.kRed)
NewGraph6A.SetLineWidth(3)
NewGraph6A.SetLineColor(ROOT.kRed)

for index in range(0, Graph.GetN()):
    NewGraph6A.SetPoint(index, -1 * Graph.GetX()[index], -1 * Graph.GetY()[index])
    NewGraph6A.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorY(index))#, Graph.GetErrorY(index), Graph.GetErrorY(index))
    print(-1 * Graph.GetY()[index], Graph.GetErrorY(index))

NewGraph6A.Draw("* SAME")

Canvas6A.Draw()

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForDeuteronsCentrality10-40_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForDeuteronsCentrality10-40_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)

# Graph.Draw("E2 SAME")

Legend6A = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend6A.AddEntry(Histogram, "My Work")
Legend6A.AddEntry(NewGraph6A, "STAR 2022")
Legend6A.Draw()

Canvasas.append(Canvas6A)






GraphRootFile.Close()




GraphRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/HEPData-ins1986611-v1-Figure_5a_triton_and_^{4}He.root","READ")

Graph = GraphRootFile.Get("/Figure 5a triton and ^{4}He/Graph1D_y1")

Histogram = HistogramRootFile.Get("DataVnVsYForTritonsCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V1 vs Y for Tritons, 10-40% Centrality")

Histogram.GetYaxis().SetTitleOffset(1.5)

Canvas6B = ROOT.TCanvas("Canvas6B", "", 800, 800)

Canvas6B.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

NewGraph6B = ROOT.TGraphAsymmErrors()
NewGraph6B.SetMarkerSize(3)
NewGraph6B.SetMarkerColor(ROOT.kRed)
NewGraph6B.SetLineWidth(3)
NewGraph6B.SetLineColor(ROOT.kRed)

for index in range(0, Graph.GetN()):
    NewGraph6B.SetPoint(index, -1 * Graph.GetX()[index], -1 * Graph.GetY()[index])
    NewGraph6B.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))

NewGraph6B.Draw("* SAME")

Canvas6B.Draw()

# Histogram = SystematicErrorRootFile.Get("DataVnVsYForTritonsCentrality10-40_px")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineWidth(0)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(0)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetLineColor(ROOT.kWhite)

# Histogram.Draw("PE 1 X0 SAME")

# SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

# Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForTritonsCentrality10-40_px")

# Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
# Graph.Draw("E2 SAME")

Legend6B = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend6B.AddEntry(Histogram, "My Work")
Legend6B.AddEntry(NewGraph6B, "STAR 2022")
Legend6B.Draw()

Canvasas.append(Canvas6B)



GraphRootFile.Close()
HistogramRootFile.Close()

'''


Date = "4-30-24"


GraphRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/HEPData-ins1897294-v1-fig2.root","READ")
HistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V2Histograms/" + Date + "-V2-HistogramNormal.root","READ")
ResolutionFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V2Histograms/R_21_Normal.root","READ")




Graph = GraphRootFile.Get("/fig2/Graph1D_y2")
Histogram = ResolutionFile.Get("DataResolution")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Canvas1A = ROOT.TCanvas("Canvas1A", "", 800, 800)

Canvas1A.cd()

Histogram.SetStats(0)
Histogram.SetLineWidth(3)

Histogram.GetYaxis().SetTitleOffset(1.5)

Histogram.Draw("P* E1 X0")

NewGraph1A = ROOT.TGraphAsymmErrors()
NewGraph1A.SetMarkerSize(3)
NewGraph1A.SetMarkerColor(ROOT.kRed)
NewGraph1A.SetLineWidth(3)
NewGraph1A.SetLineColor(ROOT.kRed)

for index in range(0, 8):
    NewGraph1A.SetPoint(index, Graph.GetX()[index] / 5, Graph.GetY()[index])
    NewGraph1A.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))

NewGraph1A.Draw("* SAME")

#Graph.Draw("AP*")

Canvas1A.Draw()

Legend1A = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend1A.AddEntry(Resolution, "My Work")
Legend1A.AddEntry(NewGraph1, "STAR 2021")
Legend1A.Draw()

Canvasas.append(Canvas1A)



# GraphRootFile.Close()



nV = 2



SystematicErrorRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/systematicErrorsV2.root","READ")


Histogram = HistogramRootFile.Get("DataVnVsYForProtonsCentrality0-10")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Protons, 0-10% Centrality")

Canvas7A = ROOT.TCanvas("Canvas7A", "", 800, 800)

Canvas7A.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForProtonsCentrality0-10_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForProtonsCentrality0-10_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")


Canvas7A.Draw()

Canvasas.append(Canvas7A)




Histogram = HistogramRootFile.Get("DataVnVsYForProtonsCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Protons, 10-40% Centrality")

Canvas7 = ROOT.TCanvas("Canvas7", "", 800, 800)

Canvas7.cd()

Histogram.SetStats(0)

Histogram.SetAxisRange(-0.022,0.045,"Y")

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForProtonsCentrality10-40_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForProtonsCentrality10-40_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Y = [-0.05, -0.15, -0.25, -0.35, -0.45, -0.55, -0.65, -0.75, -0.85, -0.95]
V2 = [-0.0215476, -0.0205711, -0.0191894, -0.017581, -0.0143508, -0.00948898, -0.00231553, 0.00720103, 0.0196095, 0.03739]
Error = [0.001233453, 0.000834859, 0.000746282, 0.000690578, 0.000577578, 0.000472735, 0.000502811, 0.001008005, 0.00119795, 0.001460709]

NewGraph7 = ROOT.TGraphAsymmErrors()
NewGraph7.SetMarkerSize(3)
NewGraph7.SetMarkerColor(ROOT.kRed)
NewGraph7.SetLineWidth(3)
NewGraph7.SetLineColor(ROOT.kRed)

for index in range(0, 10):
    NewGraph7.SetPoint(index, -1 * Y[index], V2[index])
    NewGraph7.SetPointError(index, 0, 0, Error[index], Error[index])

NewGraph7.Draw("* SAME")

Canvas7.Draw()

Legend7 = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend7.AddEntry(Resolution, "My Work")
Legend7.AddEntry(NewGraph1, "STAR 2021")
Legend7.Draw()

Canvasas.append(Canvas7)





Histogram = HistogramRootFile.Get("DataVnVsYForProtonsCentrality40-60")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Protons, 40-60% Centrality")

Canvas7B = ROOT.TCanvas("Canvas7B", "", 800, 800)

Canvas7B.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForProtonsCentrality40-60_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForProtonsCentrality40-60_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")


Canvas7B.Draw()

Canvasas.append(Canvas7B)





Histogram = HistogramRootFile.Get("DataVnVsYForKaonsPlusCentrality0-10")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Kaons Plus, 0-10% Centrality")

Canvas8A = ROOT.TCanvas("Canvas8A", "", 800, 800)

Canvas8A.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForKaonsPlusCentrality0-10_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForKaonsPlusCentrality0-10_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas8A.Draw()

Canvasas.append(Canvas8A)






Histogram8 = HistogramRootFile.Get("DataVnVsYForKaonsPlusCentrality10-40")

Histogram8.SetDirectory(0)
Histogram8.SetLineWidth(3)
Histogram8.SetLineColor(ROOT.kBlue)
Histogram8.SetMarkerStyle(ROOT.kFullCircle)
Histogram8.SetMarkerSize(1.5)
Histogram8.SetMarkerColor(ROOT.kBlue)

Histogram8.SetTitle("V2 vs Y for Kaons Plus, 10-40% Centrality")

Canvas8 = ROOT.TCanvas("Canvas8", "", 800, 800)

Canvas8.cd()

Histogram8.SetStats(0)

Histogram8.GetYaxis().SetTitleOffset(1.5)

Histogram8.Draw("PE 1 X0")

Y = [-0.05, -0.15, -0.25, -0.35, -0.45, -0.55, -0.65, -0.75, -0.85, -0.95]
V2 = [-0.0170269, -0.0171611, -0.0166637, -0.0167134, -0.0208151, -0.0255965, -0.0270674, -0.0285182, -0.0308948, -0.0352446]
Error = [0.002539327, 0.00292259, 0.0030261, 0.00357202, 0.00351784, 0.00482663, 0.00454482, 0.00441607, 0.00633096, 0.00959497]

NewGraph8 = ROOT.TGraphAsymmErrors()
NewGraph8.SetMarkerSize(3)
NewGraph8.SetMarkerColor(ROOT.kRed)
NewGraph8.SetLineWidth(3)
NewGraph8.SetLineColor(ROOT.kRed)

for index in range(0, 10):
    NewGraph8.SetPoint(index, -1 * Y[index], V2[index])
    NewGraph8.SetPointError(index, 0, 0, Error[index], Error[index])

NewGraph8.Draw("* SAME")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForKaonsPlusCentrality10-40_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForKaonsPlusCentrality10-40_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas8.Draw()

Legend8 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend8.AddEntry(Histogram8, "My Work")
Legend8.AddEntry(NewGraph8, "STAR 2021")
Legend8.Draw()

Canvasas.append(Canvas8)




Histogram = HistogramRootFile.Get("DataVnVsYForKaonsPlusCentrality40-60")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Kaons Plus, 40-60% Centrality")

Canvas8B = ROOT.TCanvas("Canvas8B", "", 800, 800)

Canvas8B.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForKaonsPlusCentrality40-60_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForKaonsPlusCentrality40-60_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas8B.Draw()

Canvasas.append(Canvas8B)






Histogram = HistogramRootFile.Get("DataVnVsYForKaonsMinusCentrality0-10")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Kaons Minus, 0-10% Centrality")

Canvas9A = ROOT.TCanvas("Canvas9A", "", 800, 800)

Canvas9A.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForKaonsMinusCentrality0-10_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForKaonsMinusCentrality0-10_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas9A.Draw()

Canvasas.append(Canvas9A)






Histogram = HistogramRootFile.Get("DataVnVsYForKaonsMinusCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Kaons Minus, 10-40% Centrality")

Canvas9 = ROOT.TCanvas("Canvas9", "", 800, 800)

Canvas9.cd()

Histogram.SetStats(0)

Histogram.GetYaxis().SetTitleOffset(1.5)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForKaonsMinusCentrality10-40_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForKaonsMinusCentrality10-40_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas9.Draw()

Canvasas.append(Canvas9)






Histogram = HistogramRootFile.Get("DataVnVsYForKaonsMinusCentrality40-60")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Kaons Minus, 40-60% Centrality")

Canvas9B = ROOT.TCanvas("Canvas9B", "", 800, 800)

Canvas9B.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForKaonsMinusCentrality40-60_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForKaonsMinusCentrality40-60_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas9B.Draw()

Canvasas.append(Canvas9B)





Histogram = HistogramRootFile.Get("DataVnVsYForPionsPlusCentrality0-10")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Pions Plus, 0-40% Centrality")

Canvas10A = ROOT.TCanvas("Canvas10A", "", 800, 800)

Canvas10A.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForPionsPlusCentrality0-10_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForPionsPlusCentrality0-10_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas10A.Draw()

Canvasas.append(Canvas10A)






Histogram = HistogramRootFile.Get("DataVnVsYForPionsPlusCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Pions Plus, 10-40% Centrality")

Canvas10 = ROOT.TCanvas("Canvas10", "", 800, 800)

Canvas10.cd()

Histogram.SetStats(0)

Histogram.SetAxisRange(-0.052,-0.022,"Y")

Histogram.Draw("PE 1 X0")

Y = [-0.05, -0.15, -0.25, -0.35, -0.45, -0.55, -0.65, -0.75, -0.85, -0.95]
V2 = [-0.0270011, -0.0262154, -0.0267038, -0.0272488, -0.0276927, -0.0281598, -0.028663, -0.0300568, -0.031139, -0.0311928]
Error = [0.001231992, 0.001223544, 0.001533661, 0.001166541, 0.001163305, 0.001230219, 0.001269799, 0.001432818, 0.001408639, 0.001472702]

NewGraph10 = ROOT.TGraphAsymmErrors()
NewGraph10.SetMarkerSize(3)
NewGraph10.SetMarkerColor(ROOT.kRed)
NewGraph10.SetLineWidth(3)
NewGraph10.SetLineColor(ROOT.kRed)

for index in range(0, 10):
    NewGraph10.SetPoint(index, -1 * Y[index], V2[index])
    NewGraph10.SetPointError(index, 0, 0, Error[index], Error[index])

NewGraph10.Draw("* SAME")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForPionsPlusCentrality10-40_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForPionsPlusCentrality10-40_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas10.Draw()

Legend8 = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend8.AddEntry(Resolution, "My Work")
Legend8.AddEntry(NewGraph1, "STAR 2021")
Legend8.Draw()

Canvasas.append(Canvas10)




Histogram = HistogramRootFile.Get("DataVnVsYForPionsPlusCentrality40-60")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Pions Plus, 40-60% Centrality")

Canvas10B = ROOT.TCanvas("Canvas10B", "", 800, 800)

Canvas10B.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForPionsPlusCentrality40-60_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForPionsPlusCentrality40-60_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas10B.Draw()

Canvasas.append(Canvas10B)






Histogram = HistogramRootFile.Get("DataVnVsYForPionsMinusCentrality0-10")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Pions Minus, 0-10% Centrality")

Canvas11A = ROOT.TCanvas("Canvas11A", "", 800, 800)

Canvas11A.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForPionsMinusCentrality0-10_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForPionsMinusCentrality0-10_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas11A.Draw()

Canvasas.append(Canvas11A)






Histogram11 = HistogramRootFile.Get("DataVnVsYForPionsMinusCentrality10-40")

Histogram11.SetDirectory(0)
Histogram11.SetLineWidth(3)
Histogram11.SetLineColor(ROOT.kBlue)
Histogram11.SetMarkerStyle(ROOT.kFullCircle)
Histogram11.SetMarkerSize(1.5)
Histogram11.SetMarkerColor(ROOT.kBlue)

Histogram11.SetTitle("V2 vs Y for Pions Minus, 10-40% Centrality")

Canvas11 = ROOT.TCanvas("Canvas11", "", 800, 800)

Canvas11.cd()

Histogram11.SetStats(0)

Histogram11.SetAxisRange(-0.037,-0.013,"Y")

Histogram11.Draw("PE 1 X0")

Y = [-0.05, -0.15, -0.25, -0.35, -0.45, -0.55, -0.65, -0.75, -0.85, -0.95]
V2 = [-0.0165181, -0.0160634, -0.0160957, -0.0170284, -0.0168865, -0.017647, -0.0185628, -0.0186106, -0.0213052, -0.0204974]
Error = [0.000819211, 0.000789957, 0.000794043, 0.000869556, 0.000844145, 0.000933527, 0.000949753, 0.001111686, 0.001055486, 0.001401783]

NewGraph11 = ROOT.TGraphAsymmErrors()
NewGraph11.SetMarkerSize(3)
NewGraph11.SetMarkerColor(ROOT.kRed)
NewGraph11.SetLineWidth(3)
NewGraph11.SetLineColor(ROOT.kRed)

for index in range(0, 10):
    NewGraph11.SetPoint(index, -1 * Y[index], V2[index])
    NewGraph11.SetPointError(index, 0, 0, Error[index], Error[index])

NewGraph11.Draw("* SAME")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForPionsMinusCentrality10-40_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForPionsMinusCentrality10-40_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas11.Draw()

Legend11 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend11.AddEntry(Histogram11, "My Work")
Legend11.AddEntry(NewGraph11, "STAR 2021")
Legend11.Draw()


Canvasas.append(Canvas11)




Histogram = HistogramRootFile.Get("DataVnVsYForPionsMinusCentrality40-60")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Pions Minus, 40-60% Centrality")

Canvas11B = ROOT.TCanvas("Canvas11B", "", 800, 800)

Canvas11B.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForPionsMinusCentrality40-60_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForPionsMinusCentrality40-60_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas11B.Draw()

Canvasas.append(Canvas11B)




GraphRootFile.Close()




GraphRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/LiteratureFiles/HEPData-ins1986611-v1-Figure_5b_proton,_deuteron,_and_^{3}He.root","READ")


Histogram = HistogramRootFile.Get("DataVnVsYForDeuteronsCentrality0-10")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Deuterons, 0-10% Centrality")

Canvas12A = ROOT.TCanvas("Canvas12A", "", 800, 800)

Canvas12A.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForDeuteronsCentrality0-10_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForDeuteronsCentrality0-10_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas12A.Draw()

Canvasas.append(Canvas12A)







Graph = GraphRootFile.Get("/Figure 5b proton, deuteron, and ^{3}He/Graph1D_y2")

Histogram12 = HistogramRootFile.Get("DataVnVsYForDeuteronsCentrality10-40")

Histogram12.SetDirectory(0)
Histogram12.SetLineWidth(3)
Histogram12.SetLineColor(ROOT.kBlue)
Histogram12.SetMarkerStyle(ROOT.kFullCircle)
Histogram12.SetMarkerSize(1.5)
Histogram12.SetMarkerColor(ROOT.kBlue)

Histogram12.SetTitle("V2 vs Y for Deuterons, 10-40% Centrality")

Canvas12 = ROOT.TCanvas("Canvas12", "", 800, 800)

Canvas12.cd()

Histogram12.SetStats(0)

Histogram12.Draw("PE 1 X0")

NewGraph12 = ROOT.TGraphAsymmErrors()
NewGraph12.SetMarkerSize(3)
NewGraph12.SetMarkerColor(ROOT.kRed)
NewGraph12.SetLineWidth(3)
NewGraph12.SetLineColor(ROOT.kRed)

for index in range(0, Graph.GetN()):
    NewGraph12.SetPoint(index, -1 * Graph.GetX()[index], Graph.GetY()[index])
    NewGraph12.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))

NewGraph12.Draw("* SAME")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForDeuteronsCentrality10-40_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForDeuteronsCentrality10-40_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas12.Draw()

Legend12 = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend12.AddEntry(Histogram12, "My Work")
Legend12.AddEntry(NewGraph12, "STAR 2021")
Legend12.Draw()

Canvasas.append(Canvas12)






Histogram = HistogramRootFile.Get("DataVnVsYForDeuteronsCentrality40-60")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Deuterons, 40-60% Centrality")

Canvas12B = ROOT.TCanvas("Canvas12B", "", 800, 800)

Canvas12B.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForDeuteronsCentrality40-60_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForDeuteronsCentrality40-60_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas12B.Draw()

Canvasas.append(Canvas12B)




GraphRootFile.Close()




GraphRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/HEPData-ins1986611-v1-Figure_5b_triton_and_^{4}He.root","READ")







Histogram = HistogramRootFile.Get("DataVnVsYForTritonsCentrality0-10")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Tritons, 0-10% Centrality")

Canvas13A = ROOT.TCanvas("Canvas13A", "", 800, 800)

Canvas13A.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForTritonsCentrality0-10_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForTritonsCentrality0-10_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas13A.Draw()

Canvasas.append(Canvas13A)





Graph = GraphRootFile.Get("/Figure 5b triton and ^{4}He/Graph1D_y2")

Histogram13 = HistogramRootFile.Get("DataVnVsYForTritonsCentrality10-40")

Histogram13.SetDirectory(0)
Histogram13.SetLineWidth(3)
Histogram13.SetLineColor(ROOT.kBlue)
Histogram13.SetMarkerStyle(ROOT.kFullCircle)
Histogram13.SetMarkerSize(1.5)
Histogram13.SetMarkerColor(ROOT.kBlue)

Histogram13.SetTitle("V2 vs Y for Tritons, 10-40% Centrality")

Canvas13 = ROOT.TCanvas("Canvas13", "", 800, 800)

Canvas13.cd()

Histogram13.SetStats(0)

Histogram13.Draw("PE 1 X0")

NewGraph13 = ROOT.TGraphAsymmErrors()
NewGraph13.SetMarkerSize(3)
NewGraph13.SetMarkerColor(ROOT.kRed)
NewGraph13.SetLineWidth(3)
NewGraph13.SetLineColor(ROOT.kRed)

for index in range(0, Graph.GetN()):
    NewGraph13.SetPoint(index, -1 * Graph.GetX()[index], Graph.GetY()[index])
    NewGraph13.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))

NewGraph13.Draw("* SAME")

Canvas13.Draw()

Histogram = SystematicErrorRootFile.Get("DataVnVsYForTritonsCentrality10-40_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForTritonsCentrality10-40_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Legend13 = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend13.AddEntry(Histogram13, "My Work")
Legend13.AddEntry(NewGraph13, "STAR 2021")
Legend13.Draw()

Canvasas.append(Canvas13)




Histogram = HistogramRootFile.Get("DataVnVsYForTritonsCentrality40-60")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Tritons, 40-60% Centrality")

Canvas13B = ROOT.TCanvas("Canvas13B", "", 800, 800)

Canvas13B.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsYForTritonsCentrality40-60_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsYForTritonsCentrality40-60_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas13B.Draw()

Canvasas.append(Canvas13B)




Histogram = HistogramRootFile.Get("DataVnVsCentralityProtonCorrected")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Centrality for Protons")

Canvas14 = ROOT.TCanvas("Canvas14", "", 800, 800)

Canvas14.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityProtonCorrected_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityProtonCorrected_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas14.Draw()

Canvasas.append(Canvas14)




Histogram = HistogramRootFile.Get("DataVnVsCentralityKaonPlusCorrected")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Centrality for Kaons Plus")
Histogram.Rebin()

Canvas15 = ROOT.TCanvas("Canvas15", "", 800, 800)

Canvas15.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityKaonPlusCorrected_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityKaonPlusCorrected_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas15.Draw()

Canvasas.append(Canvas15)





Histogram = HistogramRootFile.Get("DataVnVsCentralityKaonMinusCorrected")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Centrality for Kaons Minus")
Histogram.Rebin()

Canvas16 = ROOT.TCanvas("Canvas16", "", 800, 800)

Canvas16.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityKaonMinusCorrected_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityKaonMinusCorrected_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas16.Draw()

Canvasas.append(Canvas16)





Histogram = HistogramRootFile.Get("DataVnVsCentralityPionPlusCorrected")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Centrality for Pions Plus")

Canvas17 = ROOT.TCanvas("Canvas17", "", 800, 800)

Canvas17.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityPionPlusCorrected_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityPionPlusCorrected_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas17.Draw()

Canvasas.append(Canvas17)





Histogram = HistogramRootFile.Get("DataVnVsCentralityPionMinusCorrected")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Centrality for Pions Minus")

Canvas18 = ROOT.TCanvas("Canvas18", "", 800, 800)

Canvas18.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Histogram = SystematicErrorRootFile.Get("DataVnVsCentralityPionMinusCorrected_px")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineWidth(0)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(0)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetLineColor(ROOT.kWhite)

Histogram.Draw("PE 1 X0 SAME")

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityPionMinusCorrected_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas18.Draw()

Canvasas.append(Canvas18)




Histogram = HistogramRootFile.Get("DataVnVsCentralityDeuteronCorrected")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Centrality for Deuterons")

Canvas19 = ROOT.TCanvas("Canvas19", "", 800, 800)

Canvas19.cd()

Histogram.SetStats(0)

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

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityDeuteronCorrected_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas19.Draw()

Canvasas.append(Canvas19)




Histogram = HistogramRootFile.Get("DataVnVsCentralityTritonCorrected")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Centrality for Tritons")

Canvas20 = ROOT.TCanvas("Canvas20", "", 800, 800)

Canvas20.cd()

Histogram.SetStats(0)

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

SystematicErrorWidth = Histogram.GetXaxis().GetBinWidth(1) / 2

Graph = SystematicErrorRootFile.Get("Graph_from_DataVnVsCentralityTritonCorrected_px")

Graph.SetFillColorAlpha(ROOT.kBlue, 0.3)
Graph.Draw("E2 SAME")

Canvas20.Draw()

Canvasas.append(Canvas20)
'''



GraphRootFile.Close()
HistogramRootFile.Close()


for index in range(0, len(Canvasas)):
    if len(Canvasas) == 1:
        Canvasas[index].SaveAs(Date + '_V1_V2_Literature_Plots.pdf)')
        break
    
    if index == 0:
        print("Opening PDF")
        Canvasas[index].SaveAs(Date + '_V1_V2_Literature_Plots.pdf(')
    
    elif index == len(Canvasas) - 1:
        print("Closing PDF")
        Canvasas[index].SaveAs(Date + '_V1_V2_Literature_Plots.pdf)')
    
    else:
        Canvasas[index].SaveAs(Date + '_V1_V2_Literature_Plots.pdf')
