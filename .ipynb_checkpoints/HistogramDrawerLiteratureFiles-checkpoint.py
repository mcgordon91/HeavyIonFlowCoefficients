#!/usr/bin/env python
# coding: utf-8



import ROOT
import os
import sys

Canvasas = []

Date = '2-31-23'





GraphRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/HEPData-ins1897294-v1-fig2.root","READ")
HistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/" + Date + "-V1-Histograms.root","READ")


Graph = GraphRootFile.Get("/fig2/Graph1D_y1")
Histogram = HistogramRootFile.Get("DataResolution")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Canvas1 = ROOT.TCanvas("Canvas1", "", 800, 800)

Canvas1.cd()

Histogram.SetStats(0)
Histogram.SetLineWidth(3)

Histogram.Draw("P* E1 X0")

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

Canvasas.append(Canvas1)



GraphRootFile.Close()







GraphRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/HEPData-ins1897294-v1-fig3_top.root","READ")




Graph = GraphRootFile.Get("/fig3 top/Graph1D_y1")

Histogram = HistogramRootFile.Get("DataV" + str(nV) +"VsYForProtonsCentrality10-40")

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

Canvas2.Draw()

Canvasas.append(Canvas2)





Graph = GraphRootFile.Get("/fig3 top/Graph1D_y5")

Histogram = HistogramRootFile.Get("DataV" + str(nV) +"VsYForKaonsPlusCentrality10-40")

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

Canvas3.Draw()

Canvasas.append(Canvas3)




Graph = GraphRootFile.Get("/fig3 top/Graph1D_y6")

Histogram = HistogramRootFile.Get("DataV" + str(nV) +"VsYForKaonsMinusCentrality10-40")

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

Canvas4.Draw()

Canvasas.append(Canvas4)




Graph = GraphRootFile.Get("/fig3 top/Graph1D_y3")

Histogram = HistogramRootFile.Get("DataV" + str(nV) +"VsYForPionsPlusCentrality10-40")

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

Canvas5.Draw()

Canvasas.append(Canvas5)





Graph = GraphRootFile.Get("/fig3 top/Graph1D_y4")

Histogram = HistogramRootFile.Get("DataV" + str(nV) +"VsYForPionsMinusCentrality10-40")

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

Canvasas.append(Canvas6)




GraphRootFile.Close()




GraphRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/HEPData-ins1986611-v1-Figure_5a_proton,_deuteron,_and_^{3}He.root","READ")

Graph = GraphRootFile.Get("/Figure 5a proton, deuteron, and ^{3}He/Graph1D_y2")

Histogram = HistogramRootFile.Get("DataV" + str(nV) +"VsYForDeuteronsCentrality10-40")

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

Histogram.Draw("PE 1 X0")

NewGraph6A = ROOT.TGraphAsymmErrors()
NewGraph6A.SetMarkerSize(3)
NewGraph6A.SetMarkerColor(ROOT.kRed)
NewGraph6A.SetLineWidth(3)
NewGraph6A.SetLineColor(ROOT.kRed)

for index in range(0, Graph.GetN()):
    NewGraph6A.SetPoint(index, -1 * Graph.GetX()[index], -1 * Graph.GetY()[index])
    NewGraph6A.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))

NewGraph6A.Draw("* SAME")

Canvas6A.Draw()

Canvasas.append(Canvas6A)






GraphRootFile.Close()




GraphRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/HEPData-ins1986611-v1-Figure_5a_triton_and_^{4}He.root","READ")

Graph = GraphRootFile.Get("/Figure 5a triton and ^{4}He/Graph1D_y1")

Histogram = HistogramRootFile.Get("DataV" + str(nV) +"VsYForTritonsCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V1 vs Y for Tritons, 10-40% Centrality")

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

Canvasas.append(Canvas6B)



GraphRootFile.Close()
HistogramRootFile.Close()







GraphRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/HEPData-ins1897294-v1-fig2.root","READ")
HistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V2Histograms/" + Date + "-V2-Histograms.root","READ")



Graph = GraphRootFile.Get("/fig2/Graph1D_y1")
Histogram = HistogramRootFile.Get("DataResolution")

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

Canvasas.append(Canvas1)



GraphRootFile.Close()



Histogram = HistogramRootFile.Get("DataV" + str(nV) +"VsYForProtonsCentrality10-40")

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

Histogram.Draw("PE 1 X0")

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

Canvasas.append(Canvas7)






Histogram = HistogramRootFile.Get("DataV" + str(nV) +"VsYForKaonsPlusCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Kaons Plus, 10-40% Centrality")

Canvas8 = ROOT.TCanvas("Canvas8", "", 800, 800)

Canvas8.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

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

Canvas8.Draw()

Canvasas.append(Canvas8)




Histogram = HistogramRootFile.Get("DataV" + str(nV) +"VsYForKaonsMinusCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Canvas9 = ROOT.TCanvas("Canvas9", "", 800, 800)

Canvas9.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

Canvas9.Draw()

Canvasas.append(Canvas9)






Histogram = HistogramRootFile.Get("DataV" + str(nV) +"VsYForPionsPlusCentrality10-40")

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

Canvas10.Draw()

Canvasas.append(Canvas10)







Histogram = HistogramRootFile.Get("DataV" + str(nV) +"VsYForPionsMinusCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Pions Minus, 10-40% Centrality")

Canvas11 = ROOT.TCanvas("Canvas11", "", 800, 800)

Canvas11.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

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

Canvas11.Draw()

Canvasas.append(Canvas11)




GraphRootFile.Close()




GraphRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/HEPData-ins1986611-v1-Figure_5b_proton,_deuteron,_and_^{3}He.root","READ")

Graph = GraphRootFile.Get("/Figure 5b proton, deuteron, and ^{3}He/Graph1D_y2")

Histogram = HistogramRootFile.Get("DataV" + str(nV) +"VsYForDeuteronsCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Deuterons, 10-40% Centrality")

Canvas12 = ROOT.TCanvas("Canvas12", "", 800, 800)

Canvas12.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

NewGraph12 = ROOT.TGraphAsymmErrors()
NewGraph12.SetMarkerSize(3)
NewGraph12.SetMarkerColor(ROOT.kRed)
NewGraph12.SetLineWidth(3)
NewGraph12.SetLineColor(ROOT.kRed)

for index in range(0, Graph.GetN()):
    NewGraph12.SetPoint(index, -1 * Graph.GetX()[index], Graph.GetY()[index])
    NewGraph12.SetPointError(index, Graph.GetErrorX(index), Graph.GetErrorX(index), Graph.GetErrorY(index), Graph.GetErrorY(index))

NewGraph12.Draw("* SAME")

Canvas12.Draw()

Canvasas.append(Canvas12)






GraphRootFile.Close()




GraphRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/HEPData-ins1986611-v1-Figure_5b_triton_and_^{4}He.root","READ")

Graph = GraphRootFile.Get("/Figure 5b triton and ^{4}He/Graph1D_y2")

Histogram = HistogramRootFile.Get("DataV" + str(nV) +"VsYForTritonsCentrality10-40")

Histogram.SetDirectory(0)
Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetTitle("V2 vs Y for Tritons, 10-40% Centrality")

Canvas13 = ROOT.TCanvas("Canvas13", "", 800, 800)

Canvas13.cd()

Histogram.SetStats(0)

Histogram.Draw("PE 1 X0")

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

Canvasas.append(Canvas13)



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
