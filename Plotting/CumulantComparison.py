import ROOT
import os
import sys
import math

Canvasas = []

nV = 1

EventPlaneFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/4-10-25-V1-HistogramNormalFullDataset.root","OPEN")
CumulantFile = ROOT.TFile.Open("/star/u/mcgordon/CumulantFinal.root", "OPEN")





######## Vn vs Centrality
CanvasPr = ROOT.TCanvas("CanvasPr", "", 800, 800)
CanvasPr.cd()



EPPrCent = EventPlaneFile.Get("DataVnVsCentralityProtonCorrected")

EPPrCent.SetDirectory(0)

EPPrCent.SetStats(0)

EPPrCent.SetLineWidth(10)
EPPrCent.SetMarkerStyle(ROOT.kFullCircle)
EPPrCent.SetMarkerSize(3)
EPPrCent.SetMarkerColor(ROOT.kBlue)

EPPrCent.SetLineColor(ROOT.kBlue)

EPPrCent.SetTitle("V_{" + str(nV) + "} vs Centrality for Protons")

EPPrCent.SetAxisRange(-0.1, 0.11, "Y")

EPPrCent.Draw("PE 1 X0")

CumTwoPlotPrCent = CumulantFile.Get("TwoPartVnVsCentProtons")

CumTwoPlotPrCentFlipped = ROOT.TH1D("TwoPartVnVsCentProtonsFlipped", ";;", 12, 0, 12)

for index in range (1, CumTwoPlotPrCentFlipped.GetNbinsX() + 1):
    CumTwoPlotPrCentFlipped.SetBinContent(index, -1 * CumTwoPlotPrCent.GetBinContent(index))
    CumTwoPlotPrCentFlipped.SetBinError(index, CumTwoPlotPrCent.GetBinError(index))

CumTwoPlotPrCentFlipped.SetDirectory(0)

CumTwoPlotPrCentFlipped.SetStats(0)

CumTwoPlotPrCentFlipped.SetLineWidth(7)
CumTwoPlotPrCentFlipped.SetMarkerStyle(ROOT.kFullSquare)
CumTwoPlotPrCentFlipped.SetMarkerSize(2.5)
CumTwoPlotPrCentFlipped.SetMarkerColor(ROOT.kRed)
CumTwoPlotPrCentFlipped.SetLineColor(ROOT.kRed)

CumTwoPlotPrCentFlipped.Draw("PE 1 X0 SAME")

CumFourPlotPrCent = CumulantFile.Get("FourPartVnVsCentProtons")

CumFourPlotPrCentFlipped = ROOT.TH1D("FourPartVnVsCentProtonsFlipped", ";;", 12, 0, 12)

for index in range (1, CumFourPlotPrCentFlipped.GetNbinsX() + 1):
    CumFourPlotPrCentFlipped.SetBinContent(index, -1 * CumFourPlotPrCent.GetBinContent(index))
    CumFourPlotPrCentFlipped.SetBinError(index, CumFourPlotPrCent.GetBinError(index))

CumFourPlotPrCentFlipped.SetDirectory(0)

CumFourPlotPrCentFlipped.SetStats(0)

CumFourPlotPrCentFlipped.SetLineWidth(5)
CumFourPlotPrCentFlipped.SetMarkerStyle(ROOT.kFullTriangleDown)
CumFourPlotPrCentFlipped.SetMarkerSize(2)
CumFourPlotPrCentFlipped.SetMarkerColor(ROOT.kGreen)
CumFourPlotPrCentFlipped.SetLineColor(ROOT.kGreen)

CumFourPlotPrCentFlipped.Draw("PE 1 X0 SAME")

CanvasPrCent.Draw()

LegendPrCent = ROOT.TLegend(0.25, 0.1, 0.75, 0.3)
LegendPrCent.AddEntry(EPPrCent, "Event Plane")
LegendPrCent.AddEntry(CumTwoPlotPrCentFlipped, "Two-Particle Cumulant")
LegendPrCent.AddEntry(CumFourPlotPrCentFlipped, "Four-Particle Cumulant")
LegendPrCent.Draw()

Canvasas.append(CanvasPrCent)




CanvasKpCent = ROOT.TCanvas("KpCent", "", 800, 800)
CanvasKpCent.cd()

EPKpCent = EventPlaneFile.Get("DataVnVsCentralityKaonPlusCorrected")

EPKpCent.SetDirectory(0)

EPKpCent.SetStats(0)

EPKpCent.SetLineWidth(10)
EPKpCent.SetMarkerStyle(ROOT.kFullCircle)
EPKpCent.SetMarkerSize(3)
EPKpCent.SetMarkerColor(ROOT.kBlue)

EPKpCent.SetLineColor(ROOT.kBlue)

EPKpCent.SetTitle("V_{" + str(nV) + "} vs Centrality for K^{+}")

EPKpCent.Draw("PE 1 X0")

CumPlotKpCent = CumulantFile.Get("TwoPartVnVsCentK^{+}")

CumPlotKpCent.SetDirectory(0)

CumPlotKpCent.SetStats(0)

CumPlotKpCent.SetLineWidth(3)
CumPlotKpCent.SetMarkerStyle(ROOT.kFullSquare)
CumPlotKpCent.SetMarkerSize(1.5)
CumPlotKpCent.SetMarkerColor(ROOT.kRed)
CumPlotKpCent.SetLineColor(ROOT.kRed)

CumPlotKpCent.Draw("PE 1 X0 SAME")

CanvasKpCent.Draw()

LegendKpCent = ROOT.TLegend(0.1, 0.1, 0.4, 0.3)
LegendKpCent.AddEntry(EPKpCent, "Event Plane")
LegendKpCent.AddEntry(CumPlotKpCent, "Two-Particle Cumulant")
LegendKpCent.Draw()

Canvasas.append(CanvasKpCent)





CanvasKmCent = ROOT.TCanvas("KmCent", "", 800, 800)
CanvasKmCent.cd()

EPKmCent = EventPlaneFile.Get("DataVnVsCentralityKaonMinusCorrected")

EPKmCent.SetDirectory(0)

EPKmCent.SetStats(0)

EPKmCent.SetLineWidth(10)
EPKmCent.SetMarkerStyle(ROOT.kFullCircle)
EPKmCent.SetMarkerSize(3)
EPKmCent.SetMarkerColor(ROOT.kBlue)

EPKmCent.SetLineColor(ROOT.kBlue)

EPKmCent.SetTitle("V_{" + str(nV) + "} vs Centrality for K^{-}")

EPKmCent.Draw("PE 1 X0")

CumPlotKmCent = CumulantFile.Get("TwoPartVnVsCentK^{-}")

CumPlotKmCent.SetDirectory(0)

CumPlotKmCent.SetStats(0)

CumPlotKmCent.SetLineWidth(3)
CumPlotKmCent.SetMarkerStyle(ROOT.kFullSquare)
CumPlotKmCent.SetMarkerSize(1.5)
CumPlotKmCent.SetMarkerColor(ROOT.kRed)
CumPlotKmCent.SetLineColor(ROOT.kRed)

CumPlotKmCent.Draw("PE 1 X0 SAME")

CanvasKmCent.Draw()

LegendKmCent = ROOT.TLegend(0.1, 0.1, 0.4, 0.3)
LegendKmCent.AddEntry(EPKmCent, "Event Plane")
LegendKmCent.AddEntry(CumPlotKmCent, "Two-Particle Cumulant")
LegendKmCent.Draw()

Canvasas.append(CanvasKmCent)





CanvasPpCent = ROOT.TCanvas("PpCent", "", 800, 800)
CanvasPpCent.cd()

EPPpCent = EventPlaneFile.Get("DataVnVsCentralityPionPlusCorrected")

EPPpCent.SetDirectory(0)

EPPpCent.SetStats(0)

EPPpCent.SetLineWidth(10)
EPPpCent.SetMarkerStyle(ROOT.kFullCircle)
EPPpCent.SetMarkerSize(3)
EPPpCent.SetMarkerColor(ROOT.kBlue)

EPPpCent.SetLineColor(ROOT.kBlue)

EPPpCent.SetTitle("V_{" + str(nV) + "} vs Centrality for #pi^{+}")

EPPpCent.Draw("PE 1 X0")

CumPlotPpCent = CumulantFile.Get("TwoPartVnVsCent#pi^{+}")

CumPlotPpCent.SetDirectory(0)

CumPlotPpCent.SetStats(0)

CumPlotPpCent.SetLineWidth(3)
CumPlotPpCent.SetMarkerStyle(ROOT.kFullSquare)
CumPlotPpCent.SetMarkerSize(1.5)
CumPlotPpCent.SetMarkerColor(ROOT.kRed)
CumPlotPpCent.SetLineColor(ROOT.kRed)

CumPlotPpCent.Draw("PE 1 X0 SAME")

CanvasPpCent.Draw()

LegendPpCent = ROOT.TLegend(0.1, 0.1, 0.4, 0.3)
LegendPpCent.AddEntry(EPPpCent, "Event Plane")
LegendPpCent.AddEntry(CumPlotPpCent, "Two-Particle Cumulant")
LegendPpCent.Draw()

Canvasas.append(CanvasPpCent)




CanvasPmCent = ROOT.TCanvas("PmCent", "", 800, 800)
CanvasPmCent.cd()

EPPmCent = EventPlaneFile.Get("DataVnVsCentralityPionMinusCorrected")

EPPmCent.SetDirectory(0)

EPPmCent.SetStats(0)

EPPmCent.SetLineWidth(10)
EPPmCent.SetMarkerStyle(ROOT.kFullCircle)
EPPmCent.SetMarkerSize(3)
EPPmCent.SetMarkerColor(ROOT.kBlue)

EPPmCent.SetLineColor(ROOT.kBlue)

EPPmCent.SetTitle("V_{" + str(nV) + "} vs Centrality for #pi^{-}")

EPPmCent.Draw("PE 1 X0")

CumPlotPmCent = CumulantFile.Get("TwoPartVnVsCent#pi^{-}")

CumPlotPmCent.SetDirectory(0)

CumPlotPmCent.SetStats(0)

CumPlotPmCent.SetLineWidth(3)
CumPlotPmCent.SetMarkerStyle(ROOT.kFullSquare)
CumPlotPmCent.SetMarkerSize(1.5)
CumPlotPmCent.SetMarkerColor(ROOT.kRed)
CumPlotPmCent.SetLineColor(ROOT.kRed)

CumPlotPmCent.Draw("PE 1 X0 SAME")

CanvasPmCent.Draw()

LegendPmCent = ROOT.TLegend(0.1, 0.1, 0.4, 0.3)
LegendPmCent.AddEntry(EPPmCent, "Event Plane")
LegendPmCent.AddEntry(CumPlotPmCent, "Two-Particle Cumulant")
LegendPmCent.Draw()

Canvasas.append(CanvasPmCent)




CanvasDeCent = ROOT.TCanvas("DeCent", "", 800, 800)
CanvasDeCent.cd()

EPDeCent = EventPlaneFile.Get("DataVnVsCentralityDeuteronCorrected")

EPDeCent.SetDirectory(0)

EPDeCent.SetStats(0)

EPDeCent.SetLineWidth(10)
EPDeCent.SetMarkerStyle(ROOT.kFullCircle)
EPDeCent.SetMarkerSize(3)
EPDeCent.SetMarkerColor(ROOT.kBlue)

EPDeCent.SetLineColor(ROOT.kBlue)

EPDeCent.SetTitle("V_{" + str(nV) + "} vs Centrality for Deuterons")

EPDeCent.SetAxisRange(0.00, 0.30, "Y")

EPDeCent.Draw("PE 1 X0")

CumPlotDeCent = CumulantFile.Get("TwoPartVnVsCentDeuterons")

CumPlotDeCent.SetDirectory(0)

CumPlotDeCent.SetStats(0)

CumPlotDeCent.SetLineWidth(3)
CumPlotDeCent.SetMarkerStyle(ROOT.kFullSquare)
CumPlotDeCent.SetMarkerSize(1.5)
CumPlotDeCent.SetMarkerColor(ROOT.kRed)
CumPlotDeCent.SetLineColor(ROOT.kRed)

CumPlotDeCent.Draw("PE 1 X0 SAME")

CanvasDeCent.Draw()

LegendDeCent = ROOT.TLegend(0.1, 0.1, 0.4, 0.3)
LegendDeCent.AddEntry(EPDeCent, "Event Plane")
LegendDeCent.AddEntry(CumPlotDeCent, "Two-Particle Cumulant")
LegendDeCent.Draw()

Canvasas.append(CanvasDeCent)




CanvasTrCent = ROOT.TCanvas("TrCent", "", 800, 800)
CanvasTrCent.cd()

EPTrCent = EventPlaneFile.Get("DataVnVsCentralityTritonCorrected")

EPTrCent.SetDirectory(0)

EPTrCent.SetStats(0)

EPTrCent.SetLineWidth(10)
EPTrCent.SetMarkerStyle(ROOT.kFullCircle)
EPTrCent.SetMarkerSize(3)
EPTrCent.SetMarkerColor(ROOT.kBlue)

EPTrCent.SetLineColor(ROOT.kBlue)

EPTrCent.SetTitle("V_{" + str(nV) + "} vs Centrality for Tritons")

EPTrCent.SetAxisRange(0.00, 0.50, "Y")

EPTrCent.Draw("PE 1 X0")

CumPlotTrCent = CumulantFile.Get("TwoPartVnVsCentTritons")

CumPlotTrCent.SetDirectory(0)

CumPlotTrCent.SetStats(0)

CumPlotTrCent.SetLineWidth(3)
CumPlotTrCent.SetMarkerStyle(ROOT.kFullSquare)
CumPlotTrCent.SetMarkerSize(1.5)
CumPlotTrCent.SetMarkerColor(ROOT.kRed)
CumPlotTrCent.SetLineColor(ROOT.kRed)

CumPlotTrCent.Draw("PE 1 X0 SAME")

CanvasTrCent.Draw()

LegendTrCent = ROOT.TLegend(0.1, 0.1, 0.4, 0.3)
LegendTrCent.AddEntry(EPTrCent, "Event Plane")
LegendTrCent.AddEntry(CumPlotTrCent, "Two-Particle Cumulant")
LegendTrCent.Draw()

Canvasas.append(CanvasTrCent)




'''
############ Vn vs Pt
EPPrMidPt = ROOT.TCanvas("CanvasPrMidPt", "", 800, 800)
EPPrMidPt.cd()

EPPrMidPt = EventPlaneFirst.Get("DataVnVsPtForProtonsCentrality10-40")

EPPrMidPt.SetDirectory(0)

EPPrMidPt.SetStats(0)

EPPrMidPt.SetLineWidth(10)
EPPrMidPt.SetMarkerStyle(ROOT.kFullCircle)
EPPrMidPt.SetMarkerSize(3)
EPPrMidPt.SetMarkerColor(ROOT.kBlue)

EPPrMidPt.SetLineColor(ROOT.kBlue)

EPPrMidPt.SetTitle("V_{" + str(nV) + "} vs Pt for Protons, 10-40% Centrality")

EPPrMidPt.Draw("PE 1 X0")

CumPlotPrMidPt = CumulantFile.Get("DataVnVsPtForProtonsCentrality10-40")

CumPlotPrMidPt.SetDirectory(0)

CumPlotPrMidPt.SetStats(0)

CumPlotPrMidPt.Rebin()

CumPlotPrMidPt.SetLineWidth(3)
CumPlotPrMidPt.SetMarkerStyle(ROOT.kFullSquare)
CumPlotPrMidPt.SetMarkerSize(1.5)
CumPlotPrMidPt.SetMarkerColor(ROOT.kRed)

CumPlotPrMidPt.SetLineColor(ROOT.kRed)

CumPlotPrMidPt.Draw("PE 1 X0 SAME")

CumPlotPrMidPt.Draw()

CumPlotPrMidPt = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
CumPlotPrMidPt.AddEntry(EPPrMidPt, "Event Plane")
CumPlotPrMidPt.AddEntry(CumPlotPrMidPt, "Two-Particle Cumulant")
CumPlotPrMidPt.Draw()

Canvasas.append(CumPlotPrMidPt)



EPKpMidPt = ROOT.TCanvas("CanvasKpMidPt", "", 800, 800)
EPKpMidPt.cd()

EPKpMidPt = EventPlaneFirst.Get("DataVnVsPtForKaonsPlusCentrality10-40")

EPKpMidPt.SetDirectory(0)

EPKpMidPt.SetStats(0)

EPKpMidPt.SetLineWidth(10)
EPKpMidPt.SetMarkerStyle(ROOT.kFullCircle)
EPKpMidPt.SetMarkerSize(3)
EPKpMidPt.SetMarkerColor(ROOT.kBlue)

EPKpMidPt.SetLineColor(ROOT.kBlue)

EPKpMidPt.SetTitle("V_{" + str(nV) + "} vs Pt for K^{+}, 10-40% Centrality")

EPKpMidPt.Draw("PE 1 X0")

CumPlotKpMidPt = CumulantFile.Get("DataVnVsPtForKaonsPlusCentrality10-40")

CumPlotKpMidPt.SetDirectory(0)

CumPlotKpMidPt.SetStats(0)

CumPlotKpMidPt.Rebin()

CumPlotKpMidPt.SetLineWidth(3)
CumPlotKpMidPt.SetMarkerStyle(ROOT.kFullSquare)
CumPlotKpMidPt.SetMarkerSize(1.5)
CumPlotKpMidPt.SetMarkerColor(ROOT.kRed)

CumPlotKpMidPt.SetLineColor(ROOT.kRed)

CumPlotKpMidPt.Draw("PE 1 X0 SAME")

CumPlotKpMidPt.Draw()

CumPlotKpMidPt = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
CumPlotKpMidPt.AddEntry(EPKpMidPt, "Event Plane")
CumPlotKpMidPt.AddEntry(CumPlotKpMidPt, "Two-Particle Cumulant")
CumPlotKpMidPt.Draw()

Canvasas.append(CumPlotKpMidPt)




EPKmMidPt = ROOT.TCanvas("CanvasKmMidPt", "", 800, 800)
EPKmMidPt.cd()

EPKmMidPt = EventPlaneFirst.Get("DataVnVsPtForKaonsMinusCentrality10-40")

EPKmMidPt.SetDirectory(0)

EPKmMidPt.SetStats(0)

EPKmMidPt.SetLineWidth(10)
EPKmMidPt.SetMarkerStyle(ROOT.kFullCircle)
EPKmMidPt.SetMarkerSize(3)
EPKmMidPt.SetMarkerColor(ROOT.kBlue)

EPKmMidPt.SetLineColor(ROOT.kBlue)

EPKmMidPt.SetTitle("V_{" + str(nV) + "} vs Pt for K^{-}, 10-40% Centrality")

EPKmMidPt.Draw("PE 1 X0")

CumPlotKmMidPt = CumulantFile.Get("DataVnVsPtForKaonsMinusCentrality10-40")

CumPlotKmMidPt.SetDirectory(0)

CumPlotKmMidPt.SetStats(0)

CumPlotKmMidPt.Rebin()

CumPlotKmMidPt.SetLineWidth(3)
CumPlotKmMidPt.SetMarkerStyle(ROOT.kFullSquare)
CumPlotKmMidPt.SetMarkerSize(1.5)
CumPlotKmMidPt.SetMarkerColor(ROOT.kRed)

CumPlotKmMidPt.SetLineColor(ROOT.kRed)

CumPlotKmMidPt.Draw("PE 1 X0 SAME")

CumPlotKmMidPt.Draw()

CumPlotKmMidPt = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
CumPlotKmMidPt.AddEntry(EPKmMidPt, "Event Plane")
CumPlotKmMidPt.AddEntry(CumPlotKmMidPt, "Two-Particle Cumulant")
CumPlotKmMidPt.Draw()

Canvasas.append(CumPlotKmMidPt)




EPPpMidPt = ROOT.TCanvas("CanvasPpMidPt", "", 800, 800)
EPPpMidPt.cd()

EPPpMidPt = EventPlaneFirst.Get("DataVnVsPtForPionsPlusCentrality10-40")

EPPpMidPt.SetDirectory(0)

EPPpMidPt.SetStats(0)

EPPpMidPt.SetLineWidth(10)
EPPpMidPt.SetMarkerStyle(ROOT.kFullCircle)
EPPpMidPt.SetMarkerSize(3)
EPPpMidPt.SetMarkerColor(ROOT.kBlue)

EPPpMidPt.SetLineColor(ROOT.kBlue)

EPPpMidPt.SetTitle("V_{" + str(nV) + "} vs Pt for #pi^{+}, 10-40% Centrality")

EPPpMidPt.Draw("PE 1 X0")

CumPlotPpMidPt = CumulantFile.Get("DataVnVsPtForPionsPlusCentrality10-40")

CumPlotPpMidPt.SetDirectory(0)

CumPlotPpMidPt.SetStats(0)

CumPlotPpMidPt.Rebin()

CumPlotPpMidPt.SetLineWidth(3)
CumPlotPpMidPt.SetMarkerStyle(ROOT.kFullSquare)
CumPlotPpMidPt.SetMarkerSize(1.5)
CumPlotPpMidPt.SetMarkerColor(ROOT.kRed)

CumPlotPpMidPt.SetLineColor(ROOT.kRed)

CumPlotPpMidPt.Draw("PE 1 X0 SAME")

CumPlotPpMidPt.Draw()

CumPlotPpMidPt = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
CumPlotPpMidPt.AddEntry(EPPpMidPt, "Event Plane")
CumPlotPpMidPt.AddEntry(CumPlotPpMidPt, "Two-Particle Cumulant")
CumPlotPpMidPt.Draw()

Canvasas.append(CumPlotPpMidPt)




EPPmMidPt = ROOT.TCanvas("CanvasPmMidPt", "", 800, 800)
EPPmMidPt.cd()

EPPmMidPt = EventPlaneFirst.Get("DataVnVsPtForPionsMinusCentrality10-40")

EPPmMidPt.SetDirectory(0)

EPPmMidPt.SetStats(0)

EPPmMidPt.SetLineWidth(10)
EPPmMidPt.SetMarkerStyle(ROOT.kFullCircle)
EPPmMidPt.SetMarkerSize(3)
EPPmMidPt.SetMarkerColor(ROOT.kBlue)

EPPmMidPt.SetLineColor(ROOT.kBlue)

EPPmMidPt.SetTitle("V_{" + str(nV) + "} vs Pt for #pi^{-}, 10-40% Centrality")

EPPmMidPt.Draw("PE 1 X0")

CumPlotPmMidPt = CumulantFile.Get("DataVnVsPtForPionsMinusCentrality10-40")

CumPlotPmMidPt.SetDirectory(0)

CumPlotPmMidPt.SetStats(0)

CumPlotPmMidPt.Rebin()

CumPlotPmMidPt.SetLineWidth(3)
CumPlotPmMidPt.SetMarkerStyle(ROOT.kFullSquare)
CumPlotPmMidPt.SetMarkerSize(1.5)
CumPlotPmMidPt.SetMarkerColor(ROOT.kRed)

CumPlotPmMidPt.SetLineColor(ROOT.kRed)

CumPlotPmMidPt.Draw("PE 1 X0 SAME")

CumPlotPmMidPt.Draw()

CumPlotPmMidPt = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
CumPlotPmMidPt.AddEntry(EPPmMidPt, "Event Plane")
CumPlotPmMidPt.AddEntry(CumPlotPmMidPt, "Two-Particle Cumulant")
CumPlotPmMidPt.Draw()

Canvasas.append(CumPlotPmMidPt)



EPDeMidPt = ROOT.TCanvas("CanvasDeMidPt", "", 800, 800)
EPDeMidPt.cd()

EPDeMidPt = EventPlaneFirst.Get("DataVnVsPtForDeuteronssCentrality10-40")

EPDeMidPt.SetDirectory(0)

EPDeMidPt.SetStats(0)

EPDeMidPt.SetLineWidth(10)
EPDeMidPt.SetMarkerStyle(ROOT.kFullCircle)
EPDeMidPt.SetMarkerSize(3)
EPDeMidPt.SetMarkerColor(ROOT.kBlue)

EPDeMidPt.SetLineColor(ROOT.kBlue)

EPDeMidPt.SetTitle("V_{" + str(nV) + "} vs Pt for Deuterons, 10-40% Centrality")

EPDeMidPt.Draw("PE 1 X0")

CumPlotDeMidPt = CumulantFile.Get("DataVnVsPtForDeuteronsCentrality10-40")

CumPlotDeMidPt.SetDirectory(0)

CumPlotDeMidPt.SetStats(0)

CumPlotDeMidPt.Rebin()

CumPlotDeMidPt.SetLineWidth(3)
CumPlotDeMidPt.SetMarkerStyle(ROOT.kFullSquare)
CumPlotDeMidPt.SetMarkerSize(1.5)
CumPlotDeMidPt.SetMarkerColor(ROOT.kRed)

CumPlotDeMidPt.SetLineColor(ROOT.kRed)

CumPlotDeMidPt.Draw("PE 1 X0 SAME")

CumPlotDeMidPt.Draw()

CumPlotDeMidPt = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
CumPlotDeMidPt.AddEntry(EPDeMidPt, "Event Plane")
CumPlotDeMidPt.AddEntry(CumPlotDeMidPt, "Two-Particle Cumulant")
CumPlotDeMidPt.Draw()

Canvasas.append(CumPlotDeMidPt)





EPTrMidPt = ROOT.TCanvas("CanvasTrMidPt", "", 800, 800)
EPTrMidPt.cd()

EPTrMidPt = EventPlaneFirst.Get("DataVnVsPtForTritonsCentrality10-40")

EPTrMidPt.SetDirectory(0)

EPTrMidPt.SetStats(0)

EPTrMidPt.SetLineWidth(10)
EPTrMidPt.SetMarkerStyle(ROOT.kFullCircle)
EPTrMidPt.SetMarkerSize(3)
EPTrMidPt.SetMarkerColor(ROOT.kBlue)

EPTrMidPt.SetLineColor(ROOT.kBlue)

EPTrMidPt.SetTitle("V_{" + str(nV) + "} vs Pt for Tritons, 10-40% Centrality")

EPTrMidPt.Draw("PE 1 X0")

CumPlotTrMidPt = CumulantFile.Get("DataVnVsPtForTritonsCentrality10-40")

CumPlotTrrMidPt.SetDirectory(0)

CumPlotTrMidPt.SetStats(0)

CumPlotTrMidPt.Rebin()

CumPlotTrMidPt.SetLineWidth(3)
CumPlotTrMidPt.SetMarkerStyle(ROOT.kFullSquare)
CumPlotTrMidPt.SetMarkerSize(1.5)
CumPlotTrMidPt.SetMarkerColor(ROOT.kRed)

CumPlotTrMidPt.SetLineColor(ROOT.kRed)

CumPlotTrMidPt.Draw("PE 1 X0 SAME")

CumPlotTrMidPt.Draw()

CumPlotTrMidPt = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
CumPlotTrMidPt.AddEntry(EPTrMidPt, "Event Plane")
CumPlotTrMidPt.AddEntry(CumPlotTrMidPt, "Two-Particle Cumulant")
CumPlotTrMidPt.Draw()

Canvasas.append(CumPlotTrMidPt)


'''
############ Vn vs Rapidity
CanvasPrMidY = ROOT.TCanvas("CanvasPrMidY", "", 800, 800)
CanvasPrMidY.cd()

EPPrMidY = EventPlaneFile.Get("DataVnVsYForProtonsCentrality10-40")

EPPrMidY.SetDirectory(0)

EPPrMidY.SetStats(0)

EPPrMidY.SetLineWidth(10)
EPPrMidY.SetMarkerStyle(ROOT.kFullCircle)
EPPrMidY.SetMarkerSize(3)
EPPrMidY.SetMarkerColor(ROOT.kBlue)

EPPrMidY.SetLineColor(ROOT.kBlue)

EPPrMidY.SetTitle("V_{" + str(nV) + "} vs Y for Protons, 10-40% Centrality")

EPPrMidY.SetAxisRange(0.0, 0.39, "Y")

EPPrMidY.Draw("PE 1 X0")

CumPlotPrMidY = CumulantFile.Get("TwoPartVnVsYForProtonsCentrality10-40")

CumPlotPrMidY.SetDirectory(0)

CumPlotPrMidY.SetStats(0)

CumPlotPrMidY.SetLineWidth(3)
CumPlotPrMidY.SetMarkerStyle(ROOT.kFullSquare)
CumPlotPrMidY.SetMarkerSize(1.5)
CumPlotPrMidY.SetMarkerColor(ROOT.kRed)

CumPlotPrMidY.SetLineColor(ROOT.kRed)

CumPlotPrMidY.Draw("PE 1 X0 SAME")

LegendPrMidY = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
LegendPrMidY.AddEntry(EPPrMidY, "Event Plane")
LegendPrMidY.AddEntry(CumPlotPrMidY, "Two-Particle Cumulant")
LegendPrMidY.Draw()

CanvasPrMidY.Draw()

Canvasas.append(CanvasPrMidY)



CanvasKpMidY = ROOT.TCanvas("CanvasKpMidY", "", 800, 800)
CanvasKpMidY.cd()

EPKpMidY = EventPlaneFile.Get("DataVnVsYForKaonsPlusCentrality10-40")

EPKpMidY.SetDirectory(0)

EPKpMidY.SetStats(0)

EPKpMidY.SetLineWidth(10)
EPKpMidY.SetMarkerStyle(ROOT.kFullCircle)
EPKpMidY.SetMarkerSize(3)
EPKpMidY.SetMarkerColor(ROOT.kBlue)

EPKpMidY.SetLineColor(ROOT.kBlue)

EPKpMidY.SetTitle("V_{" + str(nV) + "} vs Y for K^{+}, 10-40% Centrality")

EPKpMidY.Draw("PE 1 X0")

CumPlotKpMidY = CumulantFile.Get("TwoPartVnVsYForKaonsPlusCentrality10-40")

CumPlotKpMidY.SetDirectory(0)

CumPlotKpMidY.SetStats(0)

CumPlotKpMidY.SetLineWidth(3)
CumPlotKpMidY.SetMarkerStyle(ROOT.kFullSquare)
CumPlotKpMidY.SetMarkerSize(1.5)
CumPlotKpMidY.SetMarkerColor(ROOT.kRed)

CumPlotKpMidY.SetLineColor(ROOT.kRed)

CumPlotKpMidY.Draw("PE 1 X0 SAME")

LegendKpMidY = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
LegendKpMidY.AddEntry(EPKpMidY, "Event Plane")
LegendKpMidY.AddEntry(CumPlotKpMidY, "Two-Particle Cumulant")
LegendKpMidY.Draw()

CanvasKpMidY.Draw()

Canvasas.append(CanvasKpMidY)




CanvasKmMidY = ROOT.TCanvas("CanvasKmMidY", "", 800, 800)
CanvasKmMidY.cd()

EPKmMidY = EventPlaneFile.Get("DataVnVsYForKaonsMinusCentrality10-40")

EPKmMidY.SetDirectory(0)

EPKmMidY.SetStats(0)

EPKmMidY.SetLineWidth(10)
EPKmMidY.SetMarkerStyle(ROOT.kFullCircle)
EPKmMidY.SetMarkerSize(3)
EPKmMidY.SetMarkerColor(ROOT.kBlue)

EPKmMidY.SetLineColor(ROOT.kBlue)

EPKmMidY.SetTitle("V_{" + str(nV) + "} vs Y for K^{-}, 10-40% Centrality")

EPKmMidY.Draw("PE 1 X0")

CumPlotKmMidY = CumulantFile.Get("TwoPartVnVsYForKaonsMinusCentrality10-40")

CumPlotKmMidY.SetDirectory(0)

CumPlotKmMidY.SetStats(0)

CumPlotKmMidY.SetLineWidth(3)
CumPlotKmMidY.SetMarkerStyle(ROOT.kFullSquare)
CumPlotKmMidY.SetMarkerSize(1.5)
CumPlotKmMidY.SetMarkerColor(ROOT.kRed)

CumPlotKmMidY.SetLineColor(ROOT.kRed)

CumPlotKmMidY.Draw("PE 1 X0 SAME")

LegendKmMidY = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
LegendKmMidY.AddEntry(EPKmMidY, "Event Plane")
LegendKmMidY.AddEntry(CumPlotKmMidY, "Two-Particle Cumulant")
LegendKmMidY.Draw()

CanvasKmMidY.Draw()

Canvasas.append(CanvasKmMidY)




CanvasPpMidY = ROOT.TCanvas("CanvasPpMidY", "", 800, 800)
CanvasPpMidY.cd()

EPPpMidY = EventPlaneFile.Get("DataVnVsYForPionsPlusCentrality10-40")

EPPpMidY.SetDirectory(0)

EPPpMidY.SetStats(0)

EPPpMidY.SetLineWidth(10)
EPPpMidY.SetMarkerStyle(ROOT.kFullCircle)
EPPpMidY.SetMarkerSize(3)
EPPpMidY.SetMarkerColor(ROOT.kBlue)

EPPpMidY.SetLineColor(ROOT.kBlue)

EPPpMidY.SetTitle("V_{" + str(nV) + "} vs Y for #pi^{+}, 10-40% Centrality")

EPPpMidY.Draw("PE 1 X0")

CumPlotPpMidY = CumulantFile.Get("TwoPartVnVsYForPionsPlusCentrality10-40")

CumPlotPpMidY.SetDirectory(0)

CumPlotPpMidY.SetStats(0)

CumPlotPpMidY.SetLineWidth(3)
CumPlotPpMidY.SetMarkerStyle(ROOT.kFullSquare)
CumPlotPpMidY.SetMarkerSize(1.5)
CumPlotPpMidY.SetMarkerColor(ROOT.kRed)

CumPlotPpMidY.SetLineColor(ROOT.kRed)

CumPlotPpMidY.Draw("PE 1 X0 SAME")

LegendPpMidY = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
LegendPpMidY.AddEntry(EPPpMidY, "Event Plane")
LegendPpMidY.AddEntry(CumPlotPpMidY, "Two-Particle Cumulant")
LegendPpMidY.Draw()

CanvasPpMidY.Draw()

Canvasas.append(CanvasPpMidY)




CanvasPmMidY = ROOT.TCanvas("CanvasPmMidY", "", 800, 800)
CanvasPmMidY.cd()

EPPmMidY = EventPlaneFile.Get("DataVnVsYForPionsMinusCentrality10-40")

EPPmMidY.SetDirectory(0)

EPPmMidY.SetStats(0)

EPPmMidY.SetLineWidth(10)
EPPmMidY.SetMarkerStyle(ROOT.kFullCircle)
EPPmMidY.SetMarkerSize(3)
EPPmMidY.SetMarkerColor(ROOT.kBlue)

EPPmMidY.SetLineColor(ROOT.kBlue)

EPPmMidY.SetTitle("V_{" + str(nV) + "} vs Y for #pi^{-}, 10-40% Centrality")

EPPmMidY.Draw("PE 1 X0")

CumPlotPmMidY = CumulantFile.Get("TwoPartVnVsYForPionsMinusCentrality10-40")

CumPlotPmMidY.SetDirectory(0)

CumPlotPmMidY.SetStats(0)

CumPlotPmMidY.SetLineWidth(3)
CumPlotPmMidY.SetMarkerStyle(ROOT.kFullSquare)
CumPlotPmMidY.SetMarkerSize(1.5)
CumPlotPmMidY.SetMarkerColor(ROOT.kRed)

CumPlotPmMidY.SetLineColor(ROOT.kRed)

CumPlotPmMidY.Draw("PE 1 X0 SAME")

LegendPmMidY = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
LegendPmMidY.AddEntry(EPPmMidY, "Event Plane")
LegendPmMidY.AddEntry(CumPlotPmMidY, "Two-Particle Cumulant")
LegendPmMidY.Draw()

CanvasPmMidY.Draw()

Canvasas.append(CanvasPmMidY)



CanvasDeMidY = ROOT.TCanvas("CanvasDeMidY", "", 800, 800)
CanvasDeMidY.cd()

EPDeMidY = EventPlaneFile.Get("DataVnVsYForDeuteronsCentrality10-40")

EPDeMidY.SetDirectory(0)

EPDeMidY.SetStats(0)

EPDeMidY.SetLineWidth(10)
EPDeMidY.SetMarkerStyle(ROOT.kFullCircle)
EPDeMidY.SetMarkerSize(3)
EPDeMidY.SetMarkerColor(ROOT.kBlue)

EPDeMidY.SetLineColor(ROOT.kBlue)

EPDeMidY.SetTitle("V_{" + str(nV) + "} vs Y for Deuterons, 10-40% Centrality")

EPDeMidY.SetAxisRange(0.0, 0.64, "Y")

EPDeMidY.Draw("PE 1 X0")

CumPlotDeMidY = CumulantFile.Get("TwoPartVnVsYForDeuteronsCentrality10-40")

CumPlotDeMidY.SetDirectory(0)

CumPlotDeMidY.SetStats(0)

CumPlotDeMidY.SetLineWidth(3)
CumPlotDeMidY.SetMarkerStyle(ROOT.kFullSquare)
CumPlotDeMidY.SetMarkerSize(1.5)
CumPlotDeMidY.SetMarkerColor(ROOT.kRed)

CumPlotDeMidY.SetLineColor(ROOT.kRed)

CumPlotDeMidY.Draw("PE 1 X0 SAME")

LegendDeMidY = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
LegendDeMidY.AddEntry(EPDeMidY, "Event Plane")
LegendDeMidY.AddEntry(CumPlotDeMidY, "Two-Particle Cumulant")
LegendDeMidY.Draw()

CanvasDeMidY.Draw()

Canvasas.append(CanvasDeMidY)





CanvasTrMidY = ROOT.TCanvas("CanvasTrMidY", "", 800, 800)
CanvasTrMidY.cd()

EPTrMidY = EventPlaneFile.Get("DataVnVsYForTritonsCentrality10-40")

EPTrMidY.SetDirectory(0)

EPTrMidY.SetStats(0)

EPTrMidY.SetLineWidth(10)
EPTrMidY.SetMarkerStyle(ROOT.kFullCircle)
EPTrMidY.SetMarkerSize(3)
EPTrMidY.SetMarkerColor(ROOT.kBlue)

EPPrMidY.SetLineColor(ROOT.kBlue)

EPTrMidY.SetTitle("V_{" + str(nV) + "} vs Y for Tritons, 10-40% Centrality")

EPTrMidY.SetAxisRange(0.0, 0.77, "Y")

EPTrMidY.Draw("PE 1 X0")

CumPlotTrMidY = CumulantFile.Get("TwoPartVnVsYForTritonsCentrality10-40")

CumPlotTrMidY.SetDirectory(0)

CumPlotTrMidY.SetStats(0)

CumPlotTrMidY.SetLineWidth(3)
CumPlotTrMidY.SetMarkerStyle(ROOT.kFullSquare)
CumPlotTrMidY.SetMarkerSize(1.5)
CumPlotTrMidY.SetMarkerColor(ROOT.kRed)

CumPlotTrMidY.SetLineColor(ROOT.kRed)

CumPlotTrMidY.Draw("PE 1 X0 SAME")

LegendTrMidY = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
LegendTrMidY.AddEntry(EPPrMidY, "Event Plane")
LegendTrMidY.AddEntry(CumPlotPrMidY, "Two-Particle Cumulant")
LegendTrMidY.Draw()

CanvasTrMidY.Draw()

Canvasas.append(CanvasTrMidY)




EventPlaneFile.Close()
CumulantFile.Close()



for index in range(0, len(Canvasas)):
    if len(Canvasas) == 1:
        Canvasas[index].SaveAs('CumulantComparisonAllTPC.pdf)')
        break
    
    if index == 0:
        print("Opening PDF")
        Canvasas[index].SaveAs('CumulantComparisonAllTPC.pdf(')
    
    elif index == len(Canvasas) - 1:
        print("Closing PDF")
        Canvasas[index].SaveAs('CumulantComparisonAllTPC.pdf)')
    
    else:
        Canvasas[index].SaveAs('CumulantComparisonAllTPC.pdf')

