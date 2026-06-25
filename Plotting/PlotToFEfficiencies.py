#!/usr/bin/env python
# coding: utf-8



import ROOT
import os
import sys

Canvasas = []





ToFFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V6Histograms/ToFEfficiency.root","READ")
# OverallPtVsEtaFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V6Histograms/HistogramFirstPassNormal.root","READ")


Histogram = ToFFile.Get("ProtonToFDetected")

Histogram.SetDirectory(0)

Histogram.SetTitle("Proton ToF Tracks Detected")

CanvasPrToF = ROOT.TCanvas("CanvasPrToF", "", 800, 800)
CanvasPrToF.cd()

CanvasPrToF.SetLogz()

CanvasPrToF.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPrToF.Draw()

Canvasas.append(CanvasPrToF)



Histogram = ToFFile.Get("ProtonTPCDetected")

Histogram.SetDirectory(0)

Histogram.SetTitle("Proton TPC Tracks Detected")

Histogram.SetDirectory(0)

CanvasPrTPC = ROOT.TCanvas("CanvasPrTPC", "", 800, 800)
CanvasPrTPC.cd()

CanvasPrTPC.SetLogz()

CanvasPrTPC.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPrTPC.Draw()

Canvasas.append(CanvasPrTPC)



Histogram1 = ToFFile.Get("ProtonToFDetected")
Histogram2 = ToFFile.Get("ProtonTPCDetected")
HistogramPr = ROOT.TH2D("ProtonToFEfficiency", "Proton ToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramPr = Histogram1.Clone()

HistogramPr.SetTitle("Proton ToF Efficiencies")

HistogramPr.Divide(Histogram2)

HistogramPr.SetDirectory(0)

CanvasPr = ROOT.TCanvas("CanvasPr", "", 800, 800)
CanvasPr.cd()

CanvasPr.SetLogz()

CanvasPr.SetRightMargin(0.15)

HistogramPr.SetStats(0)
# Change the countour gradient
HistogramPr.SetContour(1000)

HistogramPr.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
HistogramPr.Draw("colz")

CanvasPr.Draw()

Canvasas.append(CanvasPr)




Histogram1 = ToFFile.Get("ProtonToFDetectedRapidity")
Histogram2 = ToFFile.Get("ProtonTPCDetectedRapidity")
HistogramPrRap = ROOT.TH2D("ProtonToFEfficiencyRapidity", "Proton ToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramPrRap = Histogram1.Clone()

HistogramPrRap.SetTitle("Proton ToF Efficiencies")

HistogramPrRap.Divide(Histogram2)

HistogramPrRap.SetDirectory(0)

CanvasPrRap = ROOT.TCanvas("CanvasPrRap", "", 800, 800)
CanvasPrRap.cd()

CanvasPrRap.SetLogz()

CanvasPrRap.SetRightMargin(0.15)

HistogramPrRap.SetStats(0)
# Change the countour gradient
HistogramPrRap.SetContour(1000)

HistogramPrRap.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
HistogramPrRap.Draw("colz")

CanvasPrRap.Draw()

Canvasas.append(CanvasPrRap)



Histogram1 = ToFFile.Get("ProtonToFDetectedRapidityMSquaredCuts")
Histogram2 = ToFFile.Get("ProtonTPCDetectedRapidity")
HistogramPrRapM2 = ROOT.TH2D("ProtonToFEfficiencyRapidityMSquaredCuts", "Proton ToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramPrRapM2 = Histogram1.Clone()

HistogramPrRapM2.SetTitle("Proton ToF Efficiencies With m^{2} Cuts")

HistogramPrRapM2.Divide(Histogram2)

HistogramPrRapM2.SetDirectory(0)

CanvasPrRapM2 = ROOT.TCanvas("CanvasPrRapM2", "", 800, 800)
CanvasPrRapM2.cd()

CanvasPrRapM2.SetLogz()

CanvasPrRapM2.SetRightMargin(0.15)

HistogramPrRapM2.SetStats(0)
# Change the countour gradient
HistogramPrRapM2.SetContour(1000)

HistogramPrRapM2.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
HistogramPrRapM2.Draw("colz")

CanvasPrRapM2.Draw()

Canvasas.append(CanvasPrRapM2)





Histogram = ToFFile.Get("KaonPlusToFDetected")

Histogram.SetDirectory(0)

Histogram.SetTitle("K^{+} ToF Tracks Detected")

CanvasKpToF = ROOT.TCanvas("CanvasKpToF", "", 800, 800)
CanvasKpToF.cd()

CanvasKpToF.SetLogz()

CanvasKpToF.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasKpToF.Draw()

Canvasas.append(CanvasKpToF)



Histogram = ToFFile.Get("KaonPlusTPCDetected")

Histogram.SetDirectory(0)

Histogram.SetTitle("K^{+} TPC Tracks Detected")

Histogram.SetDirectory(0)

CanvasKpTPC = ROOT.TCanvas("CanvasKpTPC", "", 800, 800)
CanvasKpTPC.cd()

CanvasKpTPC.SetLogz()

CanvasKpTPC.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasKpTPC.Draw()

Canvasas.append(CanvasKpTPC)



Histogram1 = ToFFile.Get("KaonPlusToFDetected")
Histogram2 = ToFFile.Get("KaonPlusTPCDetected")
HistogramKp = ROOT.TH2D("KaonPlusToFEfficiency", "K^{+} ToF Efficiencies; #eta; P_{t} (GeV)", 30, -3, 0, 60, 0, 6)

HistogramKp = Histogram1.Clone()

HistogramKp.SetTitle("K^{+} ToF Efficiencies")

HistogramKp.Divide(Histogram2)

HistogramKp.SetDirectory(0)

CanvasKp = ROOT.TCanvas("CanvasKp", "", 800, 800)
CanvasKp.cd()

CanvasKp.SetLogz()

CanvasKp.SetRightMargin(0.15)

HistogramKp.SetStats(0)
# Change the countour gradient
HistogramKp.SetContour(1000)

HistogramKp.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
HistogramKp.Draw("colz")

CanvasKp.Draw()

Canvasas.append(CanvasKp)



Histogram1 = ToFFile.Get("KaonPlusToFDetectedRapidity")
Histogram2 = ToFFile.Get("KaonPlusTPCDetectedRapidity")
HistogramKpRap = ROOT.TH2D("KaonPlusToFEfficiencyRapidity", "K^{+} ToF Efficiencies; #eta; P_{t} (GeV)", 30, -3, 0, 60, 0, 6)

HistogramKpRap = Histogram1.Clone()

HistogramKpRap.SetTitle("K^{+} ToF Efficiencies")

HistogramKpRap.Divide(Histogram2)

HistogramKpRap.SetDirectory(0)

CanvasKpRap = ROOT.TCanvas("CanvasKpRap", "", 800, 800)
CanvasKpRap.cd()

CanvasKpRap.SetLogz()

CanvasKpRap.SetRightMargin(0.15)

HistogramKpRap.SetStats(0)
# Change the countour gradient
HistogramKpRap.SetContour(1000)

HistogramKpRap.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
HistogramKpRap.Draw("colz")

CanvasKpRap.Draw()

Canvasas.append(CanvasKpRap)



Histogram1 = ToFFile.Get("KaonPlusToFDetectedRapidityMSquaredCuts")
Histogram2 = ToFFile.Get("KaonPlusTPCDetectedRapidity")
HistogramKpRapM2 = ROOT.TH2D("KaonPlusToFEfficiencyRapidityMSquaredCuts", "K^{+} ToF Efficiencies; #eta; P_{t} (GeV)", 30, -3, 0, 60, 0, 6)

HistogramKpRapM2 = Histogram1.Clone()

HistogramKpRapM2.SetTitle("K^{+} ToF Efficiencies With m^{2} Cuts")

HistogramKpRapM2.Divide(Histogram2)

HistogramKpRapM2.SetDirectory(0)

CanvasKpRapM2 = ROOT.TCanvas("CanvasKpRapM2", "", 800, 800)
CanvasKpRapM2.cd()

CanvasKpRapM2.SetLogz()

CanvasKpRapM2.SetRightMargin(0.15)

HistogramKpRapM2.SetStats(0)
# Change the countour gradient
HistogramKpRapM2.SetContour(1000)

HistogramKpRapM2.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
HistogramKpRapM2.Draw("colz")

CanvasKpRapM2.Draw()

Canvasas.append(CanvasKpRapM2)








Histogram = ToFFile.Get("KaonMinusToFDetected")

Histogram.SetDirectory(0)

Histogram.SetTitle("K^{-} ToF Tracks Detected")

CanvasKmToF = ROOT.TCanvas("CanvasKmToF", "", 800, 800)
CanvasKmToF.cd()

CanvasKmToF.SetLogz()

CanvasKmToF.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasKmToF.Draw()

Canvasas.append(CanvasKmToF)



Histogram = ToFFile.Get("KaonMinusTPCDetected")

Histogram.SetDirectory(0)

Histogram.SetTitle("K^{-} TPC Tracks Detected")

Histogram.SetDirectory(0)

CanvasKmTPC = ROOT.TCanvas("CanvasKmTPC", "", 800, 800)
CanvasKmTPC.cd()

CanvasKmTPC.SetLogz()

CanvasKmTPC.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasKmTPC.Draw()

Canvasas.append(CanvasKmTPC)


Histogram1 = ToFFile.Get("KaonMinusToFDetected")
Histogram2 = ToFFile.Get("KaonMinusTPCDetected")
HistogramKm = ROOT.TH2D("KaonMinusToFEfficiency", "K^{-} ToF Efficiencies; #eta; P_{t} (GeV)", 30, -3, 0, 60, 0, 6)

HistogramKm = Histogram1.Clone()

HistogramKm.SetTitle("K^{-} ToF Efficiencies")

HistogramKm.Divide(Histogram2)

HistogramKm.SetDirectory(0)

CanvasKm = ROOT.TCanvas("CanvasKm", "", 800, 800)
CanvasKm.cd()

CanvasKm.SetLogz()

CanvasKm.SetRightMargin(0.15)

HistogramKm.SetStats(0)
# Change the countour gradient
HistogramKm.SetContour(1000)

HistogramKm.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
HistogramKm.Draw("colz")

CanvasKm.Draw()

Canvasas.append(CanvasKm)



Histogram1 = ToFFile.Get("KaonMinusToFDetectedRapidity")
Histogram2 = ToFFile.Get("KaonMinusTPCDetectedRapidity")
HistogramKmRap = ROOT.TH2D("KaonMinusToFEfficiencyRapidity", "K^{-} ToF Efficiencies; #eta; P_{t} (GeV)", 30, -3, 0, 60, 0, 6)

HistogramKmRap = Histogram1.Clone()

HistogramKmRap.SetTitle("K^{-} ToF Efficiencies")

HistogramKmRap.Divide(Histogram2)

HistogramKmRap.SetDirectory(0)

CanvasKmRap = ROOT.TCanvas("CanvasKmRap", "", 800, 800)
CanvasKmRap.cd()

CanvasKmRap.SetLogz()

CanvasKmRap.SetRightMargin(0.15)

HistogramKmRap.SetStats(0)
# Change the countour gradient
HistogramKmRap.SetContour(1000)

HistogramKmRap.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
HistogramKmRap.Draw("colz")

CanvasKmRap.Draw()

Canvasas.append(CanvasKmRap)



Histogram1 = ToFFile.Get("KaonMinusToFDetectedRapidityMSquaredCuts")
Histogram2 = ToFFile.Get("KaonMinusTPCDetectedRapidity")
HistogramKmRapM2 = ROOT.TH2D("KaonMinusToFEfficiencyRapidityMSquaredCuts", "K^{-} ToF Efficiencies; #eta; P_{t} (GeV)", 30, -3, 0, 60, 0, 6)

HistogramKmRapM2 = Histogram1.Clone()

HistogramKmRapM2.SetTitle("K^{-} ToF Efficiencies With m^{2} Cuts")

HistogramKmRapM2.Divide(Histogram2)

HistogramKmRapM2.SetDirectory(0)

CanvasKmRapM2 = ROOT.TCanvas("CanvasKmRapM2", "", 800, 800)
CanvasKmRapM2.cd()

CanvasKmRapM2.SetLogz()

CanvasKmRapM2.SetRightMargin(0.15)

HistogramKmRapM2.SetStats(0)
# Change the countour gradient
HistogramKmRapM2.SetContour(1000)

HistogramKmRapM2.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
HistogramKmRapM2.Draw("colz")

CanvasKmRapM2.Draw()

Canvasas.append(CanvasKmRapM2)







Histogram = ToFFile.Get("PionPlusToFDetected")

Histogram.SetDirectory(0)

Histogram.SetTitle("#pi^{+} ToF Tracks Detected")

CanvasPpToF = ROOT.TCanvas("CanvasPpToF", "", 800, 800)
CanvasPpToF.cd()

CanvasPpToF.SetLogz()

CanvasPpToF.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPpToF.Draw()

Canvasas.append(CanvasPpToF)



Histogram = ToFFile.Get("PionPlusTPCDetected")

Histogram.SetDirectory(0)

Histogram.SetTitle("#pi^{+} TPC Tracks Detected")

Histogram.SetDirectory(0)

CanvasPpTPC = ROOT.TCanvas("CanvasPpTPC", "", 800, 800)
CanvasPpTPC.cd()

CanvasPpTPC.SetLogz()

CanvasPpTPC.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPpTPC.Draw()

Canvasas.append(CanvasPpTPC)



Histogram1 = ToFFile.Get("PionPlusToFDetected")
Histogram2 = ToFFile.Get("PionPlusTPCDetected")
HistogramPp = ROOT.TH2D("PionPlusToFEfficiency", "#pi^{+} ToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramPp = Histogram1.Clone()

HistogramPp.SetTitle("#pi^{+} ToF Efficiencies")

HistogramPp.Divide(Histogram2)

HistogramPp.SetDirectory(0)

CanvasPp = ROOT.TCanvas("CanvasPp", "", 800, 800)
CanvasPp.cd()

CanvasPp.SetLogz()

CanvasPp.SetRightMargin(0.15)

HistogramPp.SetStats(0)
# Change the countour gradient
HistogramPp.SetContour(1000)

HistogramPp.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
HistogramPp.Draw("colz")

CanvasPp.Draw()

Canvasas.append(CanvasPp)


Histogram1 = ToFFile.Get("PionPlusToFDetectedRapidity")
Histogram2 = ToFFile.Get("PionPlusTPCDetectedRapidity")
HistogramPpRap = ROOT.TH2D("PionPlusToFEfficiencyRapidity", "#pi^{+} ToF Efficiencies; #eta; P_{t} (GeV)", 30, -3, 0, 60, 0, 6)

HistogramPpRap = Histogram1.Clone()

HistogramPpRap.SetTitle("#pi^{+} ToF Efficiencies")

HistogramPpRap.Divide(Histogram2)

HistogramPpRap.SetDirectory(0)

CanvasPpRap = ROOT.TCanvas("CanvasPpRap", "", 800, 800)
CanvasPpRap.cd()

CanvasPpRap.SetLogz()

CanvasPpRap.SetRightMargin(0.15)

HistogramPpRap.SetStats(0)
# Change the countour gradient
HistogramPpRap.SetContour(1000)

HistogramPpRap.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
HistogramPpRap.Draw("colz")

CanvasPpRap.Draw()

Canvasas.append(CanvasPpRap)



Histogram1 = ToFFile.Get("PionPlusToFDetectedRapidityMSquaredCuts")
Histogram2 = ToFFile.Get("PionPlusTPCDetectedRapidity")
HistogramPpRapM2 = ROOT.TH2D("PionPlusToFEfficiencyRapidityMSquaredCuts", "#pi^{+} ToF Efficiencies; #eta; P_{t} (GeV)", 30, -3, 0, 60, 0, 6)

HistogramPpRapM2 = Histogram1.Clone()

HistogramPpRapM2.SetTitle("#pi^{+} ToF Efficiencies With m^{2} Cuts")

HistogramPpRapM2.Divide(Histogram2)

HistogramPpRapM2.SetDirectory(0)

CanvasPpRapM2 = ROOT.TCanvas("CanvasPpRapM2", "", 800, 800)
CanvasPpRapM2.cd()

CanvasPpRapM2.SetLogz()

CanvasPpRapM2.SetRightMargin(0.15)

HistogramPpRapM2.SetStats(0)
# Change the countour gradient
HistogramPpRapM2.SetContour(1000)

HistogramPpRapM2.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
HistogramPpRapM2.Draw("colz")

CanvasPpRapM2.Draw()

Canvasas.append(CanvasPpRapM2)







Histogram = ToFFile.Get("PionMinusToFDetected")

Histogram.SetDirectory(0)

Histogram.SetTitle("#pi^{-} ToF Tracks Detected")

CanvasPmToF = ROOT.TCanvas("CanvasPmToF", "", 800, 800)
CanvasPmToF.cd()

CanvasPmToF.SetLogz()

CanvasPmToF.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPmToF.Draw()

Canvasas.append(CanvasPmToF)



Histogram = ToFFile.Get("PionMinusTPCDetected")

Histogram.SetDirectory(0)

Histogram.SetTitle("#pi^{-} TPC Tracks Detected")

Histogram.SetDirectory(0)

CanvasPmTPC = ROOT.TCanvas("CanvasPmTPC", "", 800, 800)
CanvasPmTPC.cd()

CanvasPmTPC.SetLogz()

CanvasPmTPC.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPmTPC.Draw()

Canvasas.append(CanvasPmTPC)



Histogram1 = ToFFile.Get("PionMinusToFDetected")
Histogram2 = ToFFile.Get("PionMinusTPCDetected")
HistogramPm = ROOT.TH2D("PionMinusToFEfficiency", "#pi^{-} ToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramPm = Histogram1.Clone()

HistogramPm.SetTitle("#pi^{-} ToF Efficiencies")

HistogramPm.Divide(Histogram2)

HistogramPm.SetDirectory(0)

CanvasPm = ROOT.TCanvas("CanvasPm", "", 800, 800)
CanvasPm.cd()

CanvasPm.SetLogz()

CanvasPm.SetRightMargin(0.15)

HistogramPm.SetStats(0)
# Change the countour gradient
HistogramPm.SetContour(1000)

HistogramPm.SetMaximum(1)
# HistogramPm.SetMinimum(0.1)

# Set the histogram with the colors corresponding to the z-values
HistogramPm.Draw("colz")

CanvasPm.Draw()

Canvasas.append(CanvasPm)



Histogram1 = ToFFile.Get("PionMinusToFDetectedRapidity")
Histogram2 = ToFFile.Get("PionMinusTPCDetectedRapidity")
HistogramPmRap = ROOT.TH2D("PionMinusToFEfficiencyRapidity", "#pi^{-} ToF Efficiencies; #eta; P_{t} (GeV)", 30, -3, 0, 60, 0, 6)

HistogramPmRap = Histogram1.Clone()

HistogramPmRap.SetTitle("#pi^{-} ToF Efficiencies")

HistogramPmRap.Divide(Histogram2)

HistogramPmRap.SetDirectory(0)

CanvasPmRap = ROOT.TCanvas("CanvasPmRap", "", 800, 800)
CanvasPmRap.cd()

CanvasPmRap.SetLogz()

CanvasPmRap.SetRightMargin(0.15)

HistogramPmRap.SetStats(0)
# Change the countour gradient
HistogramPmRap.SetContour(1000)

HistogramPmRap.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
HistogramPmRap.Draw("colz")

CanvasPmRap.Draw()

Canvasas.append(CanvasPmRap)



Histogram1 = ToFFile.Get("PionMinusToFDetectedRapidityMSquaredCuts")
Histogram2 = ToFFile.Get("PionMinusTPCDetectedRapidity")
HistogramPmRapM2 = ROOT.TH2D("PionMinusToFEfficiencyRapidityMSquaredCuts", "#pi^{-} ToF Efficiencies; #eta; P_{t} (GeV)", 30, -3, 0, 60, 0, 6)

HistogramPmRapM2 = Histogram1.Clone()

HistogramPmRapM2.SetTitle("#pi^{-} ToF Efficiencies With m^{2} Cuts")

HistogramPmRapM2.Divide(Histogram2)

HistogramPmRapM2.SetDirectory(0)

CanvasPmRapM2 = ROOT.TCanvas("CanvasPmRapM2", "", 800, 800)
CanvasPmRapM2.cd()

CanvasPmRapM2.SetLogz()

CanvasPmRapM2.SetRightMargin(0.15)

HistogramPmRapM2.SetStats(0)
# Change the countour gradient
HistogramPmRapM2.SetContour(1000)

HistogramPmRapM2.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
HistogramPmRapM2.Draw("colz")

CanvasPmRapM2.Draw()

Canvasas.append(CanvasPmRapM2)






Histogram = ToFFile.Get("DeuteronToFDetected")

Histogram.SetDirectory(0)

Histogram.SetTitle("d ToF Tracks Detected")

CanvasDeToF = ROOT.TCanvas("CanvasDeToF", "", 800, 800)
CanvasDeToF.cd()

CanvasDeToF.SetLogz()

CanvasDeToF.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasDeToF.Draw()

Canvasas.append(CanvasDeToF)



Histogram = ToFFile.Get("DeuteronTPCDetected")

Histogram.SetDirectory(0)

Histogram.SetTitle("d TPC Tracks Detected")

Histogram.SetDirectory(0)

CanvasDeTPC = ROOT.TCanvas("CanvasDeTPC", "", 800, 800)
CanvasDeTPC.cd()

CanvasDeTPC.SetLogz()

CanvasDeTPC.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasDeTPC.Draw()

Canvasas.append(CanvasDeTPC)


Histogram1 = ToFFile.Get("DeuteronToFDetected")
Histogram2 = ToFFile.Get("DeuteronTPCDetected")
HistogramDe = ROOT.TH2D("DeuteronToFEfficiency", "d ToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramDe = Histogram1.Clone()

HistogramDe.SetTitle("d ToF Efficiencies")

HistogramDe.Divide(Histogram2)

HistogramDe.SetDirectory(0)

CanvasDe = ROOT.TCanvas("CanvasDe", "", 800, 800)
CanvasDe.cd()

CanvasDe.SetLogz()

CanvasDe.SetRightMargin(0.15)

HistogramDe.SetStats(0)
# Change the countour gradient
HistogramDe.SetContour(1000)

HistogramDe.SetMaximum(1)
# HistogramDe.SetMinimum(0.1)

# Set the histogram with the colors corresponding to the z-values
HistogramDe.Draw("colz")

CanvasDe.Draw()

Canvasas.append(CanvasDe)





Histogram = ToFFile.Get("TritonToFDetected")

Histogram.SetDirectory(0)

Histogram.SetTitle("t ToF Tracks Detected")

CanvasTrToF = ROOT.TCanvas("CanvasTrToF", "", 800, 800)
CanvasTrToF.cd()

CanvasTrToF.SetLogz()

CanvasTrToF.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasTrToF.Draw()

Canvasas.append(CanvasTrToF)



Histogram = ToFFile.Get("TritonTPCDetected")

Histogram.SetDirectory(0)

Histogram.SetTitle("t TPC Tracks Detected")

Histogram.SetDirectory(0)

CanvasTrTPC = ROOT.TCanvas("CanvasTrTPC", "", 800, 800)
CanvasTrTPC.cd()

CanvasTrTPC.SetLogz()

CanvasTrTPC.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasTrTPC.Draw()

Canvasas.append(CanvasTrTPC)



Histogram1 = ToFFile.Get("TritonToFDetected")
Histogram2 = ToFFile.Get("TritonTPCDetected")
HistogramTr = ROOT.TH2D("TritonToFEfficiency", "t ToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramTr = Histogram1.Clone()

HistogramTr.SetTitle("t ToF Efficiencies")

HistogramTr.Divide(Histogram2)

HistogramTr.SetDirectory(0)

CanvasTr = ROOT.TCanvas("CanvasTr", "", 800, 800)
CanvasTr.cd()

CanvasTr.SetLogz()

CanvasTr.SetRightMargin(0.15)

HistogramTr.SetStats(0)
# Change the countour gradient
HistogramTr.SetContour(1000)

HistogramTr.SetMaximum(1)
# HistogramTr.SetMinimum(0.1)

# Set the histogram with the colors corresponding to the z-values
HistogramTr.Draw("colz")

CanvasTr.Draw()

Canvasas.append(CanvasTr)



# Histogram1 = OverallPtVsEtaFile.Get("AllTracksToFDetected")
# Histogram2 = OverallPtVsEtaFile.Get("DataPtVsEta")
# HistogramAll = ROOT.TH2D("AllTracksToFEfficiency", "All Track ToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

# HistogramAll = Histogram1.Clone()

# HistogramAll.SetTitle("All Track ToF Efficiencies")

# HistogramAll.Divide(Histogram2)

# HistogramAll.SetDirectory(0)

# CanvasAll = ROOT.TCanvas("CanvasAll", "", 800, 800)
# CanvasAll.cd()

# CanvasAll.SetLogz()

# HistogramAll.SetStats(0)
# # Change the countour gradient
# HistogramAll.SetContour(1000)

# # Set the histogram with the colors corresponding to the z-values
# HistogramAll.Draw("colz")

# CanvasAll.Draw()

# Canvasas.append(CanvasAll)




ToFFile.Close()
# OverallPtVsEtaFile.Close()



for index in range(0, len(Canvasas)):
    if len(Canvasas) == 1:
        Canvasas[index].SaveAs('ToFEfficiencies.pdf)')
        break
    
    if index == 0:
        print("Opening PDF")
        Canvasas[index].SaveAs('ToFEfficiencies.pdf(')
    
    elif index == len(Canvasas) - 1:
        print("Closing PDF")
        Canvasas[index].SaveAs('ToFEfficiencies.pdf)')
    
    else:
        Canvasas[index].SaveAs('ToFEfficiencies.pdf')
