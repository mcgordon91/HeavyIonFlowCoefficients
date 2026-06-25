#!/usr/bin/env python
# coding: utf-8



import ROOT
import os
import sys

Canvasas = []


V2RootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V2Histograms/HistogramFourthPassNormalTwice.root","READ")
V4RootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V4Histograms/HistogramFourthPassNormal.root","READ")



####### Vn vs Centrality
CanvasPrCent = ROOT.TCanvas("PrCent", "", 800, 800)
CanvasPrCent.cd()

V2PrCent = V2RootFile.Get("DataVnVsCentralityProtonHighRapidityCorrected")
V4PrCent = V4RootFile.Get("DataVnVsCentralityProtonHighRapidityCorrected")

V2PrCentTH = V2PrCent.ProjectionX("V2PrCentProj")

V4PrCentTH = V4PrCent.ProjectionX("V4PrCentProj")

V2PrCentTHSq = V2PrCentTH.Clone("V2PrCentProjSq")
V2PrCentTHSq.Multiply(V2PrCentTHSq)

FlowRatioPrCent = V4PrCentTH.Clone("FlowRatioPrCent")
FlowRatioPrCent.Divide(V2PrCentTHSq)

FlowRatioPrCent.SetDirectory(0)

FlowRatioPrCent.SetStats(0)

FlowRatioPrCent.SetLineWidth(3)
FlowRatioPrCent.SetMarkerStyle(ROOT.kFullCircle)
FlowRatioPrCent.SetMarkerSize(1.5)
FlowRatioPrCent.SetMarkerColor(ROOT.kBlue)

FlowRatioPrCent.SetLineColor(ROOT.kBlue)

FlowRatioPrCent.SetTitle("V_{4}/V_{2}^{2} vs Centrality for Protons")
FlowRatioPrCent.GetYaxis().SetTitle("V_{4}/V_{2}^{2}")
FlowRatioPrCent.SetAxisRange(-60.0, 0.0, "Y")

for i in range(1, FlowRatioPrCent.GetNbinsX() + 1):
    print(FlowRatioPrCent.GetBinContent(i))

FlowRatioPrCent.Draw("PE 1 X0")

Canvasas.append(CanvasPrCent)





# CanvasKpCent = ROOT.TCanvas("KpCent", "", 800, 800)
# CanvasKpCent.cd()

# V2KpCent = V2RootFile.Get("DataVnVsCentralityKaonPlusCorrected")
# V4KpCent = V4RootFile.Get("DataVnVsCentralityKaonPlusCorrected")

# V2KpCentTH = V2KpCent.ProjectionX("V2KpProj")

# V4KpCentTH = V4KpCent.ProjectionX("V4KpProj")

# V2KpCentTHSq = V2KpCentTH.Clone("V2KpProjSq")
# V2KpCentTHSq.Multiply(V2KpCentTHSq)

# FlowRatioKp = V4KpCentTH.Clone("FlowRatioKp")
# FlowRatioKp.Divide(V2KpCentTHSq)

# FlowRatioKp.SetDirectory(0)

# FlowRatioKp.SetStats(0)

# FlowRatioKp.SetLineWidth(10)
# FlowRatioKp.SetMarkerStyle(ROOT.kFullCircle)
# FlowRatioKp.SetMarkerSize(3)
# FlowRatioKp.SetMarkerColor(ROOT.kBlue)

# FlowRatioKp.SetLineColor(ROOT.kBlue)

# FlowRatioKp.SetTitle("V_{4}/V_{2}^{2} vs Centrality for K^{+}")
# FlowRatioKp.GetYaxis().SetTitle("V4/V2^{2}")
# # FlowRatioKp.SetAxisRange(0.0, 2.0, "Y")

# FlowRatioKp.Draw("PE 1 X0")

# Canvasas.append(CanvasKpCent)





# CanvasKmCent = ROOT.TCanvas("KmCent", "", 800, 800)
# CanvasKmCent.cd()

# V2KmCent = V2RootFile.Get("DataVnVsCentralityKaonMinusCorrected")
# V4KmCent = V4RootFile.Get("DataVnVsCentralityKaonMinusCorrected")

# V2KmCentTH = V2KmCent.ProjectionX("V2KmProj")

# V4KmCentTH = V4KmCent.ProjectionX("V4KmProj")

# V2KmCentTHSq = V2KmCentTH.Clone("V2KmProjSq")
# V2KmCentTHSq.Multiply(V2KmCentTHSq)

# FlowRatioKm = V4KmCentTH.Clone("FlowRatioKm")
# FlowRatioKm.Divide(V2KmCentTHSq)

# FlowRatioKm.SetDirectory(0)

# FlowRatioKm.SetStats(0)

# FlowRatioKm.SetLineWidth(10)
# FlowRatioKm.SetMarkerStyle(ROOT.kFullCircle)
# FlowRatioKm.SetMarkerSize(3)
# FlowRatioKm.SetMarkerColor(ROOT.kBlue)

# FlowRatioKm.SetLineColor(ROOT.kBlue)

# FlowRatioKm.SetTitle("V_{4}/V_{2}^{2} vs Centrality for K^{-}")
# FlowRatioKm.GetYaxis().SetTitle("V4/V2^{2}")
# # FlowRatioKm.SetAxisRange(0.0, 2.0, "Y")

# FlowRatioKm.Draw("PE 1 X0")

# Canvasas.append(CanvasKmCent)






# CanvasPpCent = ROOT.TCanvas("PpCent", "", 800, 800)
# CanvasPpCent.cd()

# V2PpCent = V2RootFile.Get("DataVnVsCentralityPionPlusCorrected")
# V4PpCent = V4RootFile.Get("DataVnVsCentralityPionPlusCorrected")

# V2PpCentTH = V2PpCent.ProjectionX("V2PpProj")

# V4PpCentTH = V4PpCent.ProjectionX("V4PpProj")

# V2PpCentTHSq = V2PpCentTH.Clone("V2PpProjSq")
# V2PpCentTHSq.Multiply(V2PpCentTHSq)

# FlowRatioPp = V4PpCentTH.Clone("FlowRatioPp")
# FlowRatioPp.Divide(V2PpCentTH)

# FlowRatioPp.SetDirectory(0)

# FlowRatioPp.SetStats(0)

# FlowRatioPp.SetLineWidth(10)
# FlowRatioPp.SetMarkerStyle(ROOT.kFullCircle)
# FlowRatioPp.SetMarkerSize(3)
# FlowRatioPp.SetMarkerColor(ROOT.kBlue)

# FlowRatioPp.SetLineColor(ROOT.kBlue)

# FlowRatioPp.SetTitle("V_{4}/V_{2}^{2} vs Centrality for #pi^{+}")
# FlowRatioPp.GetYaxis().SetTitle("V4/V2^{2}")
# # FlowRatioPp.SetAxisRange(0.0, 2.0, "Y")

# FlowRatioPp.Draw("PE 1 X0")

# Canvasas.append(CanvasPpCent)





# CanvasPmCent = ROOT.TCanvas("PmCent", "", 800, 800)
# CanvasPmCent.cd()

# V2PmCent = V2RootFile.Get("DataVnVsCentralityPionMinusCorrected")
# V4PmCent = V4RootFile.Get("DataVnVsCentralityPionMinusCorrected")

# V2PmCentTH = V2PmCent.ProjectionX("V2PmProj")

# V4PmCentTH = V4PmCent.ProjectionX("V4PmProj")

# V2PmCentTHSq = V2PmCentTH.Clone("V2PmProjSq")
# V2PmCentTHSq.Multiply(V2PmCentTHSq)

# FlowRatioPm = V4PmCentTH.Clone("FlowRatioPm")
# FlowRatioPm.Divide(V2PmCentTHSq)

# FlowRatioPm.SetDirectory(0)

# FlowRatioPm.SetStats(0)

# FlowRatioPm.SetLineWidth(10)
# FlowRatioPm.SetMarkerStyle(ROOT.kFullCircle)
# FlowRatioPm.SetMarkerSize(3)
# FlowRatioPm.SetMarkerColor(ROOT.kBlue)

# FlowRatioPm.SetLineColor(ROOT.kBlue)

# FlowRatioPm.SetTitle("V_{4}/V_{2}^{2} vs Centrality for #pi^{-}")
# FlowRatioPm.GetYaxis().SetTitle("V4/V2^{2}")

# # FlowRatioPm.SetAxisRange(-1.0, 1.0, "Y")

# FlowRatioPm.Draw("PE 1 X0")

# Canvasas.append(CanvasPmCent)






# CanvasDeCent = ROOT.TCanvas("DeCent", "", 800, 800)
# CanvasDeCent.cd()

# V2DeCent = V2RootFile.Get("DataVnVsCentralityDeuteronHighRapidityCorrected")
# V4DeCent = V4RootFile.Get("DataVnVsCentralityDeuteronHighRapidityCorrected")

# V2DeCentTH = V2DeCent.ProjectionX("V2DeProj")

# V4DeCentTH = V4DeCent.ProjectionX("V4DeProj")

# V2DeCentTHSq = V2DeCentTH.Clone("V2DeProjSq")
# V2DeCentTHSq.Multiply(V2DeCentTHSq)

# FlowRatioDe = V4PmCentTH.Clone("FlowRatioDe")
# FlowRatioDe.Divide(V2DeCentTHSq)

# FlowRatioDe.SetDirectory(0)

# FlowRatioDe.SetStats(0)

# FlowRatioDe.SetLineWidth(10)
# FlowRatioDe.SetMarkerStyle(ROOT.kFullCircle)
# FlowRatioDe.SetMarkerSize(3)
# FlowRatioDe.SetMarkerColor(ROOT.kBlue)

# FlowRatioDe.SetLineColor(ROOT.kBlue)

# FlowRatioDe.SetTitle("V_{4}/V_{2}^{2} vs Centrality for Deuterons")
# FlowRatioDe.GetYaxis().SetTitle("V4/V2^{2}")
# # FlowRatioDe.SetAxisRange(-2.0, 1.0, "Y")

# FlowRatioDe.Draw("PE 1 X0")

# Canvasas.append(CanvasDeCent)





# CanvasTrCent = ROOT.TCanvas("TrCent", "", 800, 800)
# CanvasTrCent.cd()

# V2TrCent = V2RootFile.Get("DataVnVsCentralityTritonHighRapidityCorrected")
# V4TrCent = V4RootFile.Get("DataVnVsCentralityTritonHighRapidityCorrected")

# V2TrCentTH = V2TrCent.ProjectionX("V2TrProj")

# V4TrCentTH = V4DeCent.ProjectionX("V4TrProj")

# V2TrCentTHSq = V2DeCentTH.Clone("V2TrProjSq")
# V2TrCentTHSq.Multiply(V2TrCentTHSq)

# FlowRatioTr = V4PmCentTH.Clone("FlowRatioTr")
# FlowRatioTr.Divide(V2TrCentTHSq)

# FlowRatioTr.SetDirectory(0)

# FlowRatioTr.SetStats(0)

# FlowRatioTr.SetLineWidth(10)
# FlowRatioTr.SetMarkerStyle(ROOT.kFullCircle)
# FlowRatioTr.SetMarkerSize(3)
# FlowRatioTr.SetMarkerColor(ROOT.kBlue)

# FlowRatioTr.SetLineColor(ROOT.kBlue)

# FlowRatioTr.SetTitle("V_{4}/V_{2}^{2} vs Centrality for Tritons")
# FlowRatioTr.GetYaxis().SetTitle("V4/V2^{2}")
# # FlowRatioTr.SetAxisRange(0.0, 2.0, "Y")

# FlowRatioTr.Draw("PE 1 X0")

# Canvasas.append(CanvasTrCent)




CanvasPrPt = ROOT.TCanvas("PrPt", "", 800, 800)
CanvasPrPt.cd()

V2PrPt = V2RootFile.Get("VnVsPtProtonHighRapidityCentrality10-40")
V4PrPt = V4RootFile.Get("VnVsPtProtonHighRapidityCentrality10-40")

V2PrPtTH = V2PrPt.ProjectionX("V2PrPtProj")

V4PrPtTH = V4PrPt.ProjectionX("V4PrPtProj")

V2PrPtTHSq = V2PrPtTH.Clone("V2PrPtProjSq")
V2PrPtTHSq.Multiply(V2PrPtTHSq)

FlowRatioPrPt = V4PrPtTH.Clone("FlowRatioPrPt")
FlowRatioPrPt.Divide(V2PrPtTHSq)

FlowRatioPrPt.SetDirectory(0)

FlowRatioPrPt.SetStats(0)

FlowRatioPrPt.SetLineWidth(3)
FlowRatioPrPt.SetMarkerStyle(ROOT.kFullCircle)
FlowRatioPrPt.SetMarkerSize(1.5)
FlowRatioPrPt.SetMarkerColor(ROOT.kBlue)

FlowRatioPrPt.SetLineColor(ROOT.kBlue)

FlowRatioPrPt.SetTitle("V_{4}/V_{2}^{2} vs Pt for Protons, 10-40% Centrality, Y > 0.5")
FlowRatioPrPt.GetYaxis().SetTitle("V_{4}/V_{2}^{2}")
# FlowRatioPrPt.SetAxisRange(0.0, 2.0, "Y")

FlowRatioPrPt.Draw("PE 1 X0")

Canvasas.append(CanvasPrPt)




CanvasPrY = ROOT.TCanvas("PrY", "", 800, 800)
CanvasPrY.cd()

V2PrY = V2RootFile.Get("DataVnVsYForProtonsCentrality10-40")
V4PrY = V4RootFile.Get("DataVnVsYForProtonsCentrality10-40")

V2PrYTH = V2PrY.ProjectionX("V2PrYProj")

V4PrYTH = V4PrY.ProjectionX("V4PrYProj")

V2PrYTHSq = V2PrYTH.Clone("V2PrYProjSq")
V2PrYTHSq.Multiply(V2PrYTHSq)

FlowRatioPrY = V4PrYTH.Clone("FlowRatioPrY")
FlowRatioPrY.Divide(V2PrYTHSq)

FlowRatioPrY.SetDirectory(0)

FlowRatioPrY.SetStats(0)

FlowRatioPrY.SetLineWidth(3)
FlowRatioPrY.SetMarkerStyle(ROOT.kFullCircle)
FlowRatioPrY.SetMarkerSize(1.5)
FlowRatioPrY.SetMarkerColor(ROOT.kBlue)

FlowRatioPrY.SetLineColor(ROOT.kBlue)

FlowRatioPrY.SetTitle("V_{4}/V_{2}^{2} vs Y for Protons, 10-40% Centrality,")
FlowRatioPrY.GetYaxis().SetTitle("V_{4}/V_{2}^{2}")
FlowRatioPrY.SetAxisRange(0.0, 0.9, "X")
# FlowRatioPrY.GetXaxis().SetNdivisions(505, ROOT.kFALSE)
FlowRatioPrY.SetAxisRange(-20.0, 10.0, "Y")

FlowRatioPrY.Draw("PE 1 X0")

Canvasas.append(CanvasPrY)





V2RootFile.Close()
V4RootFile.Close()




for index in range(0, len(Canvasas)):
    if len(Canvasas) == 1:
        Canvasas[index].SaveAs('ViscosityPlots.pdf)')
        break
    
    if index == 0:
        print("Opening PDF")
        Canvasas[index].SaveAs('ViscosityPlots.pdf(')
    
    elif index == len(Canvasas) - 1:
        print("Closing PDF")
        Canvasas[index].SaveAs('ViscosityPlots.pdf)')
    
    else:
        Canvasas[index].SaveAs('ViscosityPlots.pdf')
