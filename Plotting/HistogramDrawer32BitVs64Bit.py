#!/usr/bin/env python
# coding: utf-8



import ROOT
import os
import sys

Canvasas = []

nV = 2
Date = '7-19-24'




FirstQVectorFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/32Bit/QVectorSecondPassNormal.root","READ")
SecondQVectorFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/64Bit/QVectorSecondPassNormal.root","READ")



CanvasEPDAQxRecentered = ROOT.TCanvas("CanvasEPDAQxRecentered", "", 800, 800)
# Change the scope to be within the file
CanvasEPDAQxRecentered.cd()

HistogramA = FirstQVectorFile.Get("InnerEPDQxRecentered")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramA.SetDirectory(0)

# Build the canvas

# Delete the stats box
HistogramA.SetStats(0)

HistogramA.SetLineColor(ROOT.kBlue)
HistogramA.SetLineWidth(3)

HistogramA.Draw("HIST")

HistogramB = SecondQVectorFile.Get("InnerEPDQxRecentered")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramB.SetDirectory(0)

# Delete the stats box
HistogramB.SetStats(0)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetLineWidth(3)
HistogramB.SetLineStyle(2)

HistogramB.Draw("HIST SAME")

# Draw the histogram
CanvasEPDAQxRecentered.Draw()

LegendEPDAQx = ROOT.TLegend(0.6, 0.8, 0.9, 0.9)
LegendEPDAQx.AddEntry(HistogramA, "32 Bit")
LegendEPDAQx.AddEntry(HistogramB, "64 Bit")
LegendEPDAQx.Draw()

# Add the histogram to the list of histograms
Canvasas.append(CanvasEPDAQxRecentered)



CanvasEPDAQxRecenteredComp = ROOT.TCanvas("CanvasEPDAQxRecenteredComp", "", 800, 800)
CanvasEPDAQxRecenteredComp.cd()

HistogramCompA = FirstQVectorFile.Get("InnerEPDQxRecentered")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit for Inner EPD Qx Vectors")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.Divide(SecondQVectorFile.Get("InnerEPDQxRecentered"))

HistogramCompA.Draw("E")

CanvasEPDAQxRecenteredComp.Draw()

Canvasas.append(CanvasEPDAQxRecenteredComp)



CanvasEPDAQyRecentered = ROOT.TCanvas("CanvasEPDAQyRecentered", "", 800, 800)
# Change the scope to be within the file
CanvasEPDAQyRecentered.cd()

HistogramA = FirstQVectorFile.Get("InnerEPDQyRecentered")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramA.SetDirectory(0)

# Build the canvas

# Delete the stats box
HistogramA.SetStats(0)

HistogramA.SetLineColor(ROOT.kBlue)
HistogramA.SetLineWidth(3)

HistogramA.Draw("HIST")

HistogramB = SecondQVectorFile.Get("InnerEPDQyRecentered")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramB.SetDirectory(0)

# Delete the stats box
HistogramB.SetStats(0)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetLineWidth(3)
HistogramB.SetLineStyle(2)

HistogramB.Draw("HIST SAME")

# Draw the histogram
CanvasEPDAQyRecentered.Draw()

LegendEPDAQy = ROOT.TLegend(0.6, 0.8, 0.9, 0.9)
LegendEPDAQy.AddEntry(HistogramA, "32 Bit")
LegendEPDAQy.AddEntry(HistogramB, "64 Bit")
LegendEPDAQy.Draw()

# Add the histogram to the list of histograms
Canvasas.append(CanvasEPDAQyRecentered)



CanvasEPDAQyRecenteredComp = ROOT.TCanvas("CanvasEPDAQyRecenteredComp", "", 800, 800)
CanvasEPDAQyRecenteredComp.cd()

HistogramCompA = FirstQVectorFile.Get("InnerEPDQyRecentered")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit for Inner EPD Qy Vectors")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.Divide(SecondQVectorFile.Get("InnerEPDQyRecentered"))

HistogramCompA.Draw("E")

CanvasEPDAQyRecenteredComp.Draw()

Canvasas.append(CanvasEPDAQyRecenteredComp)



CanvasEPDBQxRecentered = ROOT.TCanvas("CanvasEPDBQxRecentered", "", 800, 800)
# Change the scope to be within the file
CanvasEPDBQxRecentered.cd()

HistogramA = FirstQVectorFile.Get("OuterEPDQxRecentered")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramA.SetDirectory(0)

# Build the canvas

# Delete the stats box
HistogramA.SetStats(0)

HistogramA.SetLineColor(ROOT.kBlue)
HistogramA.SetLineWidth(3)

HistogramA.Draw("HIST")

HistogramB = SecondQVectorFile.Get("OuterEPDQxRecentered")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramB.SetDirectory(0)

# Delete the stats box
HistogramB.SetStats(0)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetLineWidth(3)
HistogramB.SetLineStyle(2)

HistogramB.Draw("HIST SAME")

# Draw the histogram
CanvasEPDBQxRecentered.Draw()

LegendEPDBQx = ROOT.TLegend(0.6, 0.8, 0.9, 0.9)
LegendEPDBQx.AddEntry(HistogramA, "32 Bit")
LegendEPDBQx.AddEntry(HistogramB, "64 Bit")
LegendEPDBQx.Draw()

# Add the histogram to the list of histograms
Canvasas.append(CanvasEPDBQxRecentered)



CanvasEPDBQxRecenteredComp = ROOT.TCanvas("CanvasEPDBQxRecenteredComp", "", 800, 800)
CanvasEPDBQxRecenteredComp.cd()

HistogramCompA = FirstQVectorFile.Get("OuterEPDQxRecentered")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit for Outer EPD Qx Vectors")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.Divide(SecondQVectorFile.Get("OuterEPDQxRecentered"))

HistogramCompA.Draw("E")

CanvasEPDBQxRecenteredComp.Draw()

Canvasas.append(CanvasEPDBQxRecenteredComp)



CanvasEPDBQyRecentered = ROOT.TCanvas("CanvasEPDBQyRecentered", "", 800, 800)
# Change the scope to be within the file
CanvasEPDBQyRecentered.cd()

HistogramA = FirstQVectorFile.Get("OuterEPDQyRecentered")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramA.SetDirectory(0)

# Build the canvas

# Delete the stats box
HistogramA.SetStats(0)

HistogramA.SetLineColor(ROOT.kBlue)
HistogramA.SetLineWidth(3)

HistogramA.Draw("HIST")

HistogramB = SecondQVectorFile.Get("OuterEPDQyRecentered")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramB.SetDirectory(0)

# Delete the stats box
HistogramB.SetStats(0)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetLineWidth(3)
HistogramB.SetLineStyle(2)

HistogramB.Draw("HIST SAME")

# Draw the histogram
CanvasEPDBQyRecentered.Draw()

LegendEPDBQy = ROOT.TLegend(0.6, 0.8, 0.9, 0.9)
LegendEPDBQy.AddEntry(HistogramA, "32 Bit")
LegendEPDBQy.AddEntry(HistogramB, "64 Bit")
LegendEPDBQy.Draw()

# Add the histogram to the list of histograms
Canvasas.append(CanvasEPDBQyRecentered)



CanvasEPDBQyRecenteredComp = ROOT.TCanvas("CanvasEPDBQyRecenteredComp", "", 800, 800)
CanvasEPDBQyRecenteredComp.cd()

HistogramCompA = FirstQVectorFile.Get("OuterEPDQyRecentered")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit for Outer EPD Qy Vectors")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.Divide(SecondQVectorFile.Get("OuterEPDQyRecentered"))

HistogramCompA.Draw("E")

CanvasEPDBQyRecenteredComp.Draw()

Canvasas.append(CanvasEPDBQyRecenteredComp)





CanvasTPCBQxRecentered = ROOT.TCanvas("CanvasTPCBQxRecentered", "", 800, 800)
# Change the scope to be within the file
CanvasTPCBQxRecentered.cd()

HistogramA = FirstQVectorFile.Get("OuterTPCQxRecentered")

HistogramA.SetTitle("Qx Recentered for Outer TPC")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramA.SetDirectory(0)

# Build the canvas

# Delete the stats box
HistogramA.SetStats(0)

HistogramA.SetLineColor(ROOT.kBlue)
HistogramA.SetLineWidth(3)

HistogramA.Draw("HIST")

HistogramB = SecondQVectorFile.Get("OuterTPCQxRecentered")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramB.SetDirectory(0)

# Delete the stats box
HistogramB.SetStats(0)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetLineWidth(3)
HistogramB.SetLineStyle(2)

HistogramB.Draw("HIST SAME")

# Draw the histogram
CanvasTPCBQxRecentered.Draw()

LegendTPCBQx = ROOT.TLegend(0.6, 0.8, 0.9, 0.9)
LegendTPCBQx.AddEntry(HistogramA, "32 Bit")
LegendTPCBQx.AddEntry(HistogramB, "64 Bit")
LegendTPCBQx.Draw()

# Add the histogram to the list of histograms
Canvasas.append(CanvasTPCBQxRecentered)



CanvasTPCBQxRecenteredComp = ROOT.TCanvas("CanvasTPCBQxRecenteredComp", "", 800, 800)
CanvasTPCBQxRecenteredComp.cd()

HistogramCompA = FirstQVectorFile.Get("OuterTPCQxRecentered")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit for Outer TPC Qx Vectors")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.Divide(SecondQVectorFile.Get("OuterTPCQxRecentered"))

HistogramCompA.Draw("E")

CanvasTPCBQxRecenteredComp.Draw()

Canvasas.append(CanvasTPCBQxRecenteredComp)





CanvasTPCBQyRecentered = ROOT.TCanvas("CanvasTPCBQyRecentered", "", 800, 800)
# Change the scope to be within the file
CanvasTPCBQyRecentered.cd()

HistogramA = FirstQVectorFile.Get("OuterTPCQyRecentered")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramA.SetDirectory(0)

HistogramA.SetTitle("Qy Recentered for Outer TPC")

# Build the canvas

# Delete the stats box
HistogramA.SetStats(0)

HistogramA.SetLineColor(ROOT.kBlue)
HistogramA.SetLineWidth(3)

HistogramA.Draw("HIST")

HistogramB = SecondQVectorFile.Get("OuterTPCQyRecentered")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramB.SetDirectory(0)

# Delete the stats box
HistogramB.SetStats(0)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetLineWidth(3)
HistogramB.SetLineStyle(2)

HistogramB.Draw("HIST SAME")

# Draw the histogram
CanvasTPCBQyRecentered.Draw()

LegendTPCBQy = ROOT.TLegend(0.6, 0.8, 0.9, 0.9)
LegendTPCBQy.AddEntry(HistogramA, "32 Bit")
LegendTPCBQy.AddEntry(HistogramB, "64 Bit")
LegendTPCBQy.Draw()

# Add the histogram to the list of histograms
Canvasas.append(CanvasTPCBQyRecentered)



CanvasTPCBQyRecenteredComp = ROOT.TCanvas("CanvasTPCBQyRecenteredComp", "", 800, 800)
CanvasTPCBQyRecenteredComp.cd()

HistogramCompA = FirstQVectorFile.Get("OuterTPCQyRecentered")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit for Outer TPC Qy Vectors")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.Divide(SecondQVectorFile.Get("OuterTPCQyRecentered"))

HistogramCompA.Draw("E")

CanvasTPCBQyRecenteredComp.Draw()

Canvasas.append(CanvasTPCBQyRecenteredComp)





FirstQVectorFile.Close()
SecondQVectorFile.Close()


##################################################################################### Kinematics



FirstResolutionPlotFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/32Bit/R_11_Normal.root","READ")
SecondResolutionPlotFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/64Bit/R_11_Normal.root","READ")

MyFileFirst = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/32Bit/7-19-25-V1-32Bit.root","READ")
MyFileSecond = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/64Bit/7-19-25-V1-64Bit.root","READ")

# SystematicErrorRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/systematicErrors.root","READ")
# CameronSystematicErrorRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/LiteratureFiles/HEPData-ins2702151-SystematicErrors-root.root", "READ")




Histogram = MyFileFirst.Get("DatadEdxVsP")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetTitle("dE/dx vs p (32 Bit)")

CanvasDeDxP32 = ROOT.TCanvas("DeDxP32", "", 800, 800)
CanvasDeDxP32.cd()

CanvasDeDxP32.SetLogz()

#Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasDeDxP32.Draw()

Canvasas.append(CanvasDeDxP32)




Histogram = MyFileSecond.Get("DatadEdxVsP")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetTitle("dE/dx vs p (64 Bit)")

CanvasDeDxP64 = ROOT.TCanvas("DeDxP64", "", 800, 800)
CanvasDeDxP64.cd()

CanvasDeDxP64.SetLogz()

#Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasDeDxP64.Draw()

Canvasas.append(CanvasDeDxP64)




CanvasDeDxComp = ROOT.TCanvas("CanvasDeDxComp", "", 800, 800)
CanvasDeDxComp.cd()

HistogramCompA = MyFileFirst.Get("DatadEdxVsP")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

# HistogramCompA.SetAxisRange(0.95, 1.05, "Y")

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit (Scaled) For dE/dx vs p")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.Rebin2D(10, 10)

HistogramCompB = MyFileSecond.Get("DatadEdxVsP")

HistogramCompB.Rebin2D(10, 10)

HistogramCompA.Scale(136442570 / 136134776)
HistogramCompA.Divide(HistogramCompB)

HistogramCompA.SetMinimum(0.8)
HistogramCompA.SetMaximum(1.2)

HistogramCompA.Draw("colz")

CanvasDeDxComp.Draw()

Canvasas.append(CanvasDeDxComp)





Histogram = MyFileFirst.Get("DataPtVsYProton")

Histogram.SetDirectory(0)

Histogram.SetTitle("Pt vs Y for Protons (32 Bit)")

Histogram.SetAxisRange(0.0, 2.0, "Y")

CanvasPrPtY32 = ROOT.TCanvas("CanvasPrPtY32", "", 800, 800)
CanvasPrPtY32.cd()

CanvasPrPtY32.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPrPtY32.Draw()

Canvasas.append(CanvasPrPtY32)




Histogram = MyFileSecond.Get("DataPtVsYProton")

Histogram.SetDirectory(0)

Histogram.SetTitle("Pt vs Y for Protons (64 Bit)")

Histogram.SetAxisRange(0.0, 2.0, "Y")

CanvasPrPtY64 = ROOT.TCanvas("CanvasPrPtY64", "", 800, 800)
CanvasPrPtY64.cd()

CanvasPrPtY64.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPrPtY64.Draw()

Canvasas.append(CanvasPrPtY64)



CanvasPrPtYComp = ROOT.TCanvas("CanvasPrPtYComp", "", 800, 800)
CanvasPrPtYComp.cd()

HistogramCompA = MyFileFirst.Get("DataPtVsYProton")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit (Scaled) For Pt vs Y for Protons")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.Rebin2D(10, 10)

HistogramCompB = MyFileSecond.Get("DataPtVsYProton")

HistogramCompB.Rebin2D(10, 10)

HistogramCompA.Scale(136442570 / 136134776)
HistogramCompA.Divide(HistogramCompB)

HistogramCompA.SetMinimum(0.8)
HistogramCompA.SetMaximum(1.2)

HistogramCompA.SetAxisRange(0.0, 2.0, "Y")

HistogramCompA.Draw("colz")

CanvasPrPtYComp.Draw()

Canvasas.append(CanvasPrPtYComp)





Histogram = MyFileFirst.Get("DataPtVsYKaonPlus")

Histogram.SetDirectory(0)

Histogram.SetTitle("Pt vs Y for K^{+} (32 Bit)")

CanvasKpPtY32 = ROOT.TCanvas("CanvasKpPtY32", "", 800, 800)
CanvasKpPtY32.cd()

CanvasKpPtY32.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasKpPtY32.Draw()

Canvasas.append(CanvasKpPtY32)




Histogram = MyFileSecond.Get("DataPtVsYKaonPlus")

Histogram.SetDirectory(0)

Histogram.SetTitle("Pt vs Y for K^{+} (64 Bit)")

CanvasKpPtY64 = ROOT.TCanvas("CanvasKpPtY64", "", 800, 800)
CanvasKpPtY64.cd()

CanvasKpPtY64.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasKpPtY64.Draw()

Canvasas.append(CanvasKpPtY64)



CanvasKpPtYComp = ROOT.TCanvas("CanvasKpPtYComp", "", 800, 800)
CanvasKpPtYComp.cd()

HistogramCompA = MyFileFirst.Get("DataPtVsYKaonPlus")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

# HistogramCompA.SetAxisRange(0.95, 1.05, "Y")

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit (Scaled) For Pt vs Y for K^{+}")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.Rebin2D(10, 10)

HistogramCompB = MyFileSecond.Get("DataPtVsYKaonPlus")

HistogramCompB.Rebin2D(10, 10)

HistogramCompA.Scale(136442570 / 136134776)
HistogramCompA.Divide(HistogramCompB)

HistogramCompA.SetMinimum(0.8)
HistogramCompA.SetMaximum(1.2)

HistogramCompA.Draw("colz")

CanvasKpPtYComp.Draw()

Canvasas.append(CanvasKpPtYComp)





Histogram = MyFileFirst.Get("DataPtVsYKaonMinus")

Histogram.SetDirectory(0)

Histogram.SetTitle("Pt vs Y for K^{-} (32 Bit)")

CanvasKmPtY32 = ROOT.TCanvas("CanvasKmPtY32", "", 800, 800)
CanvasKmPtY32.cd()

CanvasKmPtY32.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasKmPtY32.Draw()

Canvasas.append(CanvasKmPtY32)




Histogram = MyFileSecond.Get("DataPtVsYKaonMinus")

Histogram.SetDirectory(0)

Histogram.SetTitle("Pt vs Y for K^{-} (64 Bit)")

CanvasKmPtY64 = ROOT.TCanvas("CanvasKmPtY64", "", 800, 800)
CanvasKmPtY64.cd()

CanvasKmPtY64.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasKmPtY64.Draw()

Canvasas.append(CanvasKmPtY64)



CanvasKmPtYComp = ROOT.TCanvas("CanvasKmPtYComp", "", 800, 800)
CanvasKmPtYComp.cd()

HistogramCompA = MyFileFirst.Get("DataPtVsYKaonMinus")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

# HistogramCompA.SetAxisRange(0.95, 1.05, "Y")

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit (Scaled) For Pt vs Y for K^{-}")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.Rebin2D(10, 10)

HistogramCompB = MyFileSecond.Get("DataPtVsYKaonMinus")

HistogramCompB.Rebin2D(10, 10)

HistogramCompA.Scale(136442570 / 136134776)
HistogramCompA.Divide(HistogramCompB)

HistogramCompA.SetMinimum(0.8)
HistogramCompA.SetMaximum(1.2)

HistogramCompA.Draw("colz")

CanvasKmPtYComp.Draw()

Canvasas.append(CanvasKmPtYComp)





Histogram = MyFileFirst.Get("DataPtVsYPionPlus")

Histogram.SetDirectory(0)

Histogram.SetTitle("Pt vs Y for #pi^{+} (32 Bit)")

CanvasPpPtY32 = ROOT.TCanvas("CanvasPpPtY32", "", 800, 800)
CanvasPpPtY32.cd()

CanvasPpPtY32.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPpPtY32.Draw()

Canvasas.append(CanvasPpPtY32)




Histogram = MyFileSecond.Get("DataPtVsYPionPlus")

Histogram.SetDirectory(0)

Histogram.SetTitle("Pt vs Y for #pi^{+} (64 Bit)")

CanvasPpPtY64 = ROOT.TCanvas("CanvasPpPtY64", "", 800, 800)
CanvasPpPtY64.cd()

CanvasPpPtY64.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPpPtY64.Draw()

Canvasas.append(CanvasPpPtY64)




CanvasPpPtYComp = ROOT.TCanvas("CanvasPpPtYComp", "", 800, 800)
CanvasPpPtYComp.cd()

HistogramCompA = MyFileFirst.Get("DataPtVsYPionPlus")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

# HistogramCompA.SetAxisRange(0.95, 1.05, "Y")

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit (Scaled) For Pt vs Y for #pi^{+}")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.Rebin2D(10, 10)

HistogramCompB = MyFileSecond.Get("DataPtVsYPionPlus")

HistogramCompB.Rebin2D(10, 10)

HistogramCompA.Scale(136442570 / 136134776)
HistogramCompA.Divide(HistogramCompB)

HistogramCompA.SetMinimum(0.8)
HistogramCompA.SetMaximum(1.2)

HistogramCompA.Draw("colz")

CanvasPpPtYComp.Draw()

Canvasas.append(CanvasPpPtYComp)





Histogram = MyFileFirst.Get("DataPtVsYPionMinus")

Histogram.SetDirectory(0)

Histogram.SetTitle("Pt vs Y for #pi^{-} (32 Bit)")

CanvasPmPtY32 = ROOT.TCanvas("CanvasPmPtY32", "", 800, 800)
CanvasPmPtY32.cd()

CanvasPmPtY32.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPmPtY32.Draw()

Canvasas.append(CanvasPmPtY32)




Histogram = MyFileSecond.Get("DataPtVsYPionMinus")

Histogram.SetDirectory(0)

Histogram.SetTitle("Pt vs Y for #pi^{-} (64 Bit)")

CanvasPmPtY64 = ROOT.TCanvas("CanvasPmPtY64", "", 800, 800)
CanvasPmPtY64.cd()

CanvasPmPtY64.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPmPtY64.Draw()

Canvasas.append(CanvasPmPtY64)



CanvasPmPtYComp = ROOT.TCanvas("CanvasPmPtYComp", "", 800, 800)
CanvasPmPtYComp.cd()

HistogramCompA = MyFileFirst.Get("DataPtVsYPionMinus")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

# HistogramCompA.SetAxisRange(0.95, 1.05, "Y")

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit (Scaled) For Pt vs Y for #pi^{-}")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.Rebin2D(10, 10)

HistogramCompB = MyFileSecond.Get("DataPtVsYPionMinus")

HistogramCompB.Rebin2D(10, 10)

HistogramCompA.Scale(136442570 / 136134776)
HistogramCompA.Divide(HistogramCompB)

HistogramCompA.SetMinimum(0.8)
HistogramCompA.SetMaximum(1.2)

HistogramCompA.Draw("colz")

CanvasPmPtYComp.Draw()

Canvasas.append(CanvasPmPtYComp)





Histogram = MyFileFirst.Get("DataPtVsYDeuteron")

Histogram.SetDirectory(0)

Histogram.SetTitle("Pt vs Y for Deuterons (32 Bit)")

CanvasDePtY32 = ROOT.TCanvas("CanvasDePtY32", "", 800, 800)
CanvasDePtY32.cd()

CanvasDePtY32.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasDePtY32.Draw()

Canvasas.append(CanvasDePtY32)




Histogram = MyFileSecond.Get("DataPtVsYDeuteron")

Histogram.SetDirectory(0)

Histogram.SetTitle("Pt vs Y for Deuterons (64 Bit)")

CanvasDePtY64 = ROOT.TCanvas("CanvasDePtY64", "", 800, 800)
CanvasDePtY64.cd()

CanvasDePtY64.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasDePtY64.Draw()

Canvasas.append(CanvasDePtY64)



CanvasDePtYComp = ROOT.TCanvas("CanvasDePtYComp", "", 800, 800)
CanvasDePtYComp.cd()

HistogramCompA = MyFileFirst.Get("DataPtVsYDeuteron")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

# HistogramCompA.SetAxisRange(0.95, 1.05, "Y")

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit (Scaled) For Pt vs Y for Deuterons")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.Rebin2D(10, 10)

HistogramCompB = MyFileSecond.Get("DataPtVsYDeuteron")

HistogramCompB.Rebin2D(10, 10)

HistogramCompA.Scale(136442570 / 136134776)
HistogramCompA.Divide(HistogramCompB)

HistogramCompA.SetMinimum(0.8)
HistogramCompA.SetMaximum(1.2)

HistogramCompA.Draw("colz")

CanvasDePtYComp.Draw()

Canvasas.append(CanvasDePtYComp)





Histogram = MyFileFirst.Get("DataPtVsYTriton")

Histogram.SetDirectory(0)

Histogram.SetTitle("Pt vs Y for Tritons (32 Bit)")

CanvasTrPtY32 = ROOT.TCanvas("CanvasTrPtY32", "", 800, 800)
CanvasTrPtY32.cd()

CanvasTrPtY32.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasTrPtY32.Draw()

Canvasas.append(CanvasTrPtY32)



Histogram = MyFileSecond.Get("DataPtVsYTriton")

Histogram.SetDirectory(0)

Histogram.SetTitle("Pt vs Y for Tritons (64 Bit)")

CanvasTrPtY64 = ROOT.TCanvas("CanvasTrPtY64", "", 800, 800)
CanvasTrPtY64.cd()

CanvasTrPtY64.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasTrPtY64.Draw()

Canvasas.append(CanvasTrPtY64)



CanvasTrPtYComp = ROOT.TCanvas("CanvasTrPtYComp", "", 800, 800)
CanvasTrPtYComp.cd()

HistogramCompA = MyFileFirst.Get("DataPtVsYTriton")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

# HistogramCompA.SetAxisRange(0.95, 1.05, "Y")

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit (Scaled) For Pt vs Y for Tritons")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.Rebin2D(10, 10)

HistogramCompB = MyFileSecond.Get("DataPtVsYTriton")

HistogramCompB.Rebin2D(10, 10)

HistogramCompA.Scale(136442570 / 136134776)
HistogramCompA.Divide(HistogramCompB)

HistogramCompA.SetMinimum(0.8)
HistogramCompA.SetMaximum(1.2)

HistogramCompA.Draw("colz")

CanvasTrPtYComp.Draw()

Canvasas.append(CanvasTrPtYComp)


######################################################################################################### Resolution and Psi1



Canvas0 = ROOT.TCanvas("Canvas0", "", 800, 800)
Canvas0.cd()

HistogramA = FirstResolutionPlotFile.Get("DataResolutionR11")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetTitle("R_{11}")
HistogramA.GetYaxis().SetTitleOffset(1.5)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetAxisRange(0, 11, "X")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondResolutionPlotFile.Get("DataResolutionR11")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.GetYaxis().SetTitleOffset(1.5)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas0.Draw()

Legend0 = ROOT.TLegend(0.7, 0.8, 0.9, 0.9)
Legend0.AddEntry(HistogramA, "32 Bit")
Legend0.AddEntry(HistogramB, "64 Bit")
Legend0.Draw()

Canvasas.append(Canvas0)



Canvas0Comp = ROOT.TCanvas("Canvas0Comp", "", 800, 800)
Canvas0Comp.cd()

HistogramA = FirstResolutionPlotFile.Get("DataResolutionR11")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetTitle("Ratio of 32 to 64 Bit R_{11}")
HistogramA.GetYaxis().SetTitle("Ratio")

HistogramA.SetLineWidth(10)
HistogramA.SetLineColor(ROOT.kBlue)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetAxisRange(0, 11, "X")

HistogramB = SecondResolutionPlotFile.Get("DataResolutionR11")

HistogramA.Divide(HistogramB)

HistogramA.Draw("HIST P E X0")

Canvas0Comp.Draw()

Canvasas.append(Canvas0Comp)



FirstResolutionPlotFile.Close()
SecondResolutionPlotFile.Close()



Canvas_h_eventCheck = ROOT.TCanvas("Canvas_h_eventCheck", "", 800, 800)
# Change the scope to be within the file
Canvas_h_eventCheck.cd()

HistogramA = MyFileFirst.Get("EventCheck")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramA.SetDirectory(0)

# Delete the stats box
HistogramA.SetStats(0)

HistogramA.SetLineColor(ROOT.kBlue)
HistogramA.SetLineWidth(3)

HistogramA.Draw("HIST")

HistogramB = MyFileSecond.Get("EventCheck")

# Change the histogram scope so that it doesn't close when the last file closes
HistogramB.SetDirectory(0)

# Delete the stats box
HistogramB.SetStats(0)

HistogramB.Scale(136134776.0 / 136442570.0)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.SetLineWidth(3)
HistogramB.SetLineStyle(2)

HistogramB.Draw("HIST SAME")

# Draw the histogram
Canvas_h_eventCheck.Draw()

LegendEv = ROOT.TLegend(0.6, 0.8, 0.9, 0.9)
LegendEv.AddEntry(HistogramA, "32 Bit")
LegendEv.AddEntry(HistogramB, "64 Bit (Scaled)")
LegendEv.Draw()

# Add the histogram to the list of histograms
Canvasas.append(Canvas_h_eventCheck)



CanvasEventCheckComp = ROOT.TCanvas("CanvasEventCheckComp", "", 800, 800)
CanvasEventCheckComp.cd()

HistogramCompA = MyFileFirst.Get("EventCheck")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit Events (Scaled) After Each Cut")
HistogramCompA.GetYaxis().SetTitle("Ratio")
HistogramCompA.GetYaxis().SetLabelSize(0.02)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompB = MyFileSecond.Get("EventCheck")

HistogramCompB.Scale(136134776.0 / 136442570.0)

HistogramCompA.Divide(HistogramCompB)

HistogramCompA.Draw("HIST P E X0")

CanvasEventCheckComp.Draw()

Canvasas.append(CanvasEventCheckComp)




CanvasPsi1Raw32 = ROOT.TCanvas("CanvasPsi1Raw32", "", 800, 800)
CanvasPsi1Raw32.cd()

Histogram = MyFileFirst.Get("DataPsi1RawInnerEPD")

Histogram.SetTitle("#Psi_{1}, EPD-A (32 Bit)")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("HIST")

Histogram = MyFileFirst.Get("DataPsi1RecenteredInnerEPD")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("HIST SAME")

Histogram = MyFileFirst.Get("DataPsi1RecenteredAndShiftedInnerEPD")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kGreen)

Histogram.Draw("HIST SAME")

CanvasPsi1Raw32.Draw()

Canvasas.append(CanvasPsi1Raw32)



CanvasPsi1Raw64 = ROOT.TCanvas("CanvasPsi1Raw64", "", 800, 800)
CanvasPsi1Raw64.cd()

Histogram = MyFileSecond.Get("DataPsi1RawInnerEPD")

Histogram.SetTitle("#Psi_{1}, EPD-A (64 Bit)")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("HIST")

Histogram = MyFileSecond.Get("DataPsi1RecenteredInnerEPD")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("HIST SAME")

Histogram = MyFileSecond.Get("DataPsi1RecenteredAndShiftedInnerEPD")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kGreen)

Histogram.Draw("HIST SAME")

CanvasPsi1Raw64.Draw()

Canvasas.append(CanvasPsi1Raw64)





CanvasPsi1Recentered32 = ROOT.TCanvas("CanvasPsi1Recentered32", "", 800, 800)
CanvasPsi1Recentered32.cd()

Histogram = MyFileFirst.Get("DataPsi1RawOuterEPD")

Histogram.SetTitle("#Psi_{1}, EPD-B (32 Bit)")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("HIST")

Histogram = MyFileFirst.Get("DataPsi1RecenteredOuterEPD")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("HIST SAME")

Histogram = MyFileFirst.Get("DataPsi1RecenteredAndShiftedOuterEPD")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kGreen)

Histogram.Draw("HIST SAME")

CanvasPsi1Recentered32.Draw()

Canvasas.append(CanvasPsi1Recentered32)



CanvasPsi1Recentered64 = ROOT.TCanvas("CanvasPsi1Recentered64", "", 800, 800)
CanvasPsi1Recentered64.cd()

Histogram = MyFileSecond.Get("DataPsi1RawOuterEPD")

Histogram.SetTitle("#Psi_{1}, EPD-B (64 Bit)")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("HIST")

Histogram = MyFileSecond.Get("DataPsi1RecenteredOuterEPD")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("HIST SAME")

Histogram = MyFileSecond.Get("DataPsi1RecenteredAndShiftedOuterEPD")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kGreen)

Histogram.Draw("HIST SAME")

CanvasPsi1Recentered64.Draw()

Canvasas.append(CanvasPsi1Recentered64)







CanvasPsi1Shifted32 = ROOT.TCanvas("CanvasPsi1Shifted32", "", 800, 800)
CanvasPsi1Shifted32.cd()

Histogram = MyFileFirst.Get("DataPsi1RawOuterTPC")

Histogram.SetTitle("#Psi_{1}, TPC-B (32 Bit)")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("HIST")

Histogram = MyFileFirst.Get("DataPsi1RecenteredOuterTPC")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("HIST SAME")

Histogram = MyFileFirst.Get("DataPsi1RecenteredAndShiftedOuterTPC")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kGreen)

Histogram.Draw("HIST SAME")

CanvasPsi1Shifted32.Draw()

Canvasas.append(CanvasPsi1Shifted32)



CanvasPsi1Shifted64 = ROOT.TCanvas("CanvasPsi1Shifted64", "", 800, 800)
CanvasPsi1Shifted64.cd()

Histogram = MyFileSecond.Get("DataPsi1RawOuterTPC")

Histogram.SetTitle("#Psi_{1}, TPC-B (64 Bit)")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("HIST")

Histogram = MyFileSecond.Get("DataPsi1RecenteredOuterTPC")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("HIST SAME")

Histogram = MyFileSecond.Get("DataPsi1RecenteredAndShiftedOuterTPC")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kGreen)

Histogram.Draw("HIST SAME")

CanvasPsi1Shifted64.Draw()

Canvasas.append(CanvasPsi1Shifted64)



MyFileFirst.Close()
MyFileSecond.Close()
####################################################################################################### V3 vs Centrality
MyFileFirst = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V2Histograms/32Bit/7-19-25-V2-32Bit.root","READ")
MyFileSecond = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V2Histograms/64Bit/7-19-25-V2-64Bit.root","READ")





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
Legend4.AddEntry(HistogramA, "32 Bit")
Legend4.AddEntry(HistogramB, "64 Bit")
Legend4.Draw()

Canvasas.append(Canvas4)




Canvas5 = ROOT.TCanvas("Canvas5", "", 800, 800)
Canvas5.cd()

HistogramA = MyFileFirst.Get("DataVnVsCentralityKaonPlusCorrected")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.Draw("PE 1 X0")

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
Legend5.AddEntry(HistogramA, "32 Bit")
Legend5.AddEntry(HistogramB, "64 Bit")
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
Legend6.AddEntry(HistogramA, "32 Bit")
Legend6.AddEntry(HistogramB, "64 Bit")
Legend6.Draw()

Canvasas.append(Canvas6)





Canvas7 = ROOT.TCanvas("Canvas7", "", 800, 800)
Canvas7.cd()

HistogramA = MyFileFirst.Get("DataVnVsCentralityPionPlusCorrected")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.Draw("PE 1 X0")

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
Legend7.AddEntry(HistogramA, "32 Bit")
Legend7.AddEntry(HistogramB, "64 Bit")
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
Legend8.AddEntry(HistogramA, "32 Bit")
Legend8.AddEntry(HistogramB, "64 Bit")
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

Legend9 = ROOT.TLegend(0.7, 0.8, 0.9, 0.9)
Legend9.AddEntry(HistogramA, "32 Bit")
Legend9.AddEntry(HistogramB, "64 Bit")
Legend9.Draw()

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

Legend10 = ROOT.TLegend(0.7, 0.8, 0.9, 0.9)
Legend10.AddEntry(HistogramA, "32 Bit")
Legend10.AddEntry(HistogramB, "64 Bit")
Legend10.Draw()

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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend14 = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend14.AddEntry(HistogramA, "32 Bit")
Legend14.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend15 = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend15.AddEntry(HistogramA, "32 Bit")
Legend15.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend16 = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend16.AddEntry(HistogramA, "32 Bit")
Legend16.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend18 = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend18.AddEntry(HistogramA, "32 Bit")
Legend18.AddEntry(HistogramB, "64 Bit")
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

if (nV == 2):
    HistogramA.SetAxisRange(-0.02, 0.13, "Y")

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

Legend19 = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend19.AddEntry(HistogramA, "32 Bit")
Legend19.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend20 = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
Legend20.AddEntry(HistogramA, "32 Bit")
Legend20.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend21 = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend21.AddEntry(HistogramA, "32 Bit")
Legend21.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend22 = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend22.AddEntry(HistogramA, "32 Bit")
Legend22.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend23 = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend23.AddEntry(HistogramA, "32 Bit")
Legend23.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend24 = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend24.AddEntry(HistogramA, "32 Bit")
Legend24.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend25 = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend25.AddEntry(HistogramA, "32 Bit")
Legend25.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend26 = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend26.AddEntry(HistogramA, "32 Bit")
Legend26.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend27 = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend27.AddEntry(HistogramA, "32 Bit")
Legend27.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend28 = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend28.AddEntry(HistogramA, "32 Bit")
Legend28.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend29 = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend29.AddEntry(HistogramA, "32 Bit")
Legend29.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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
Legend30.AddEntry(HistogramA, "32 Bit")
Legend30.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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
Legend31.AddEntry(HistogramA, "32 Bit")
Legend31.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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
Legend32.AddEntry(HistogramA, "32 Bit")
Legend32.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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
Legend33.AddEntry(HistogramA, "32 Bit")
Legend33.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend34 = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend34.AddEntry(HistogramA, "32 Bit")
Legend34.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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
Legend35.AddEntry(HistogramA, "32 Bit")
Legend35.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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
Legend1.AddEntry(HistogramA, "32 Bit")
Legend1.AddEntry(HistogramB, "64 Bit")
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

if (nV == 2):
    HistogramA.SetAxisRange(-0.01, 0.038, "Y")

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

Legend2 = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend2.AddEntry(HistogramA, "32 Bit")
Legend2.AddEntry(HistogramB, "64 Bit")
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

HistogramA.GetYaxis().SetTitleOffset(1)

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

Legend3 = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend3.AddEntry(HistogramA, "32 Bit")
Legend3.AddEntry(HistogramB, "64 Bit")
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

Legend1A = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend1A.AddEntry(HistogramA, "32 Bit")
Legend1A.AddEntry(HistogramB, "64 Bit")
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

Legend2A = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend2A.AddEntry(HistogramA, "32 Bit")
Legend2A.AddEntry(HistogramB, "64 Bit")
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

Legend3A = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend3A.AddEntry(HistogramA, "32 Bit")
Legend3A.AddEntry(HistogramB, "64 Bit")
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

Legend1B = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend1B.AddEntry(HistogramA, "32 Bit")
Legend1B.AddEntry(HistogramB, "64 Bit")
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

if (nV == 2):
    HistogramA.SetAxisRange(-0.12, 0.075, "Y")

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

Legend2B = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend2B.AddEntry(HistogramA, "32 Bit")
Legend2B.AddEntry(HistogramB, "64 Bit")
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
Legend3B.AddEntry(HistogramA, "32 Bit")
Legend3B.AddEntry(HistogramB, "64 Bit")
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
Legend1C.AddEntry(HistogramA, "32 Bit")
Legend1C.AddEntry(HistogramB, "64 Bit")
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

if (nV == 2):
    HistogramA.SetAxisRange(-0.045, 0.014, "Y")

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
Legend2C.AddEntry(HistogramA, "32 Bit")
Legend2C.AddEntry(HistogramB, "64 Bit")
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
Legend3C.AddEntry(HistogramA, "32 Bit")
Legend3C.AddEntry(HistogramB, "64 Bit")
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
Legend1D.AddEntry(HistogramA, "32 Bit")
Legend1D.AddEntry(HistogramB, "64 Bit")
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
Legend2D.AddEntry(HistogramA, "32 Bit")
Legend2D.AddEntry(HistogramB, "64 Bit")
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
Legend3D.AddEntry(HistogramA, "32 Bit")
Legend3D.AddEntry(HistogramB, "64 Bit")
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

Legend1E = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend1E.AddEntry(HistogramA, "32 Bit")
Legend1E.AddEntry(HistogramB, "64 Bit")
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

Legend2E = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend2E.AddEntry(HistogramA, "32 Bit")
Legend2E.AddEntry(HistogramB, "64 Bit")
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

Legend3E = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend3E.AddEntry(HistogramA, "32 Bit")
Legend3E.AddEntry(HistogramB, "64 Bit")
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

Legend1F = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend1F.AddEntry(HistogramA, "32 Bit")
Legend1F.AddEntry(HistogramB, "64 Bit")
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

if (nV == 2):
    HistogramA.SetAxisRange(0.0, 0.32, "Y")

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

Legend2F = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend2F.AddEntry(HistogramA, "32 Bit")
Legend2F.AddEntry(HistogramB, "64 Bit")
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

Legend3F = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend3F.AddEntry(HistogramA, "32 Bit")
Legend3F.AddEntry(HistogramB, "64 Bit")
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

Legend11 = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend11.AddEntry(HistogramA, "32 Bit")
Legend11.AddEntry(HistogramB, "64 Bit")
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

Legend12 = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend12.AddEntry(HistogramA, "32 Bit")
Legend12.AddEntry(HistogramB, "64 Bit")
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

Legend13 = ROOT.TLegend(0.1, 0.8, 0.3, 0.9)
Legend13.AddEntry(HistogramA, "32 Bit")
Legend13.AddEntry(HistogramB, "64 Bit")
Legend13.Draw()

Canvasas.append(Canvas13)


#################################################################################################### Comparison Plots

CanvasPrCentComp = ROOT.TCanvas("CanvasPrCentComp", "", 800, 800)
CanvasPrCentComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsCentralityProtonCorrected")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Centrality Values for Protons")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsCentralityProtonCorrected"))

HistogramCompA.Draw("HIST P E X0")

CanvasPrCentComp.Draw()

Canvasas.append(CanvasPrCentComp)



CanvasKpCentComp = ROOT.TCanvas("CanvasKpCentComp", "", 800, 800)
CanvasKpCentComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsCentralityKaonPlusCorrected")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Centrality Values for K^{+}")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsCentralityKaonPlusCorrected"))

if (nV == 2):
    HistogramCompA.SetAxisRange(0.0, 2.0, "Y")

HistogramCompA.Draw("HIST P E X0")

CanvasKpCentComp.Draw()

Canvasas.append(CanvasKpCentComp)



CanvasKmCentComp = ROOT.TCanvas("CanvasKmCentComp", "", 800, 800)
CanvasKmCentComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsCentralityKaonMinusCorrected")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Centrality Values for K^{-}")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsCentralityKaonMinusCorrected"))

if (nV == 2):
    HistogramCompA.SetAxisRange(-2.0, 4.0, "Y")

HistogramCompA.Draw("HIST P E X0")

CanvasKmCentComp.Draw()

Canvasas.append(CanvasKmCentComp)



CanvasPpCentComp = ROOT.TCanvas("CanvasPpCentComp", "", 800, 800)
CanvasPpCentComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsCentralityPionPlusCorrected")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Centrality Values for #pi^{+}")
HistogramCompA.GetYaxis().SetTitle("Ratio")

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsCentralityPionPlusCorrected"))

HistogramCompA.Draw("HIST P E X0")

CanvasPpCentComp.Draw()

Canvasas.append(CanvasPpCentComp)



CanvasPmCentComp = ROOT.TCanvas("CanvasPmCentComp", "", 800, 800)
CanvasPmCentComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsCentralityPionMinusCorrected")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Centrality Values for #pi^{-}")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsCentralityPionMinusCorrected"))

HistogramCompA.Draw("HIST P E X0")

CanvasPmCentComp.Draw()

Canvasas.append(CanvasPmCentComp)



CanvasDeCentComp = ROOT.TCanvas("CanvasDeCentComp", "", 800, 800)
CanvasDeCentComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsCentralityDeuteronCorrected")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Centrality Values for Deuterons")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsCentralityDeuteronCorrected"))

HistogramCompA.Draw("HIST P E X0")

CanvasDeCentComp.Draw()

Canvasas.append(CanvasDeCentComp)


CanvasTrCentComp = ROOT.TCanvas("CanvasTrCentComp", "", 800, 800)
CanvasTrCentComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsCentralityTritonCorrected")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Centrality Values for Tritons")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.1)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsCentralityTritonCorrected"))

HistogramCompA.Draw("HIST P E X0")

CanvasTrCentComp.Draw()

Canvasas.append(CanvasTrCentComp)



CanvasPrPtComp = ROOT.TCanvas("CanvasPrPtComp", "", 800, 800)
CanvasPrPtComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsPtForProtonsCentrality10-40")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Pt Values for Protons, 10-40% Centrality")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsPtForProtonsCentrality10-40"))

HistogramCompA.Rebin()

HistogramCompA.Draw("HIST P E X0")

CanvasPrPtComp.Draw()

Canvasas.append(CanvasPrPtComp)


CanvasKpPtComp = ROOT.TCanvas("CanvasKpPtComp", "", 800, 800)
CanvasKpPtComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsPtForKaonsPlusCentrality10-40")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Pt Values for K^{+}, 10-40% Centrality")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsPtForKaonsPlusCentrality10-40"))

HistogramCompA.Rebin()

if (nV == 2):
    HistogramCompA.SetAxisRange(0.0, 2.0, "Y")

HistogramCompA.Draw("HIST P E X0")

CanvasKpPtComp.Draw()

Canvasas.append(CanvasKpPtComp)



CanvasKmPtComp = ROOT.TCanvas("CanvasKmPtComp", "", 800, 800)
CanvasKmPtComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsPtForKaonsMinusCentrality10-40")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Pt Values for K^{-}, 10-40% Centrality")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsPtForKaonsMinusCentrality10-40"))

HistogramCompA.Rebin()

if (nV == 2):
    HistogramCompA.SetAxisRange(-1.0, 3.0, "Y")

HistogramCompA.Draw("HIST P E X0")

CanvasKmPtComp.Draw()

Canvasas.append(CanvasKmPtComp)



CanvasPpPtComp = ROOT.TCanvas("CanvasPpPtComp", "", 800, 800)
CanvasPpPtComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsPtForPionsPlusCentrality10-40")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Pt Values for #pi^{+}, 10-40% Centrality")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsPtForPionsPlusCentrality10-40"))

HistogramCompA.Rebin()

HistogramCompA.Draw("HIST P E X0")

CanvasPpPtComp.Draw()

Canvasas.append(CanvasPpPtComp)



CanvasPmPtComp = ROOT.TCanvas("CanvasPmPtComp", "", 800, 800)
CanvasPmPtComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsPtForPionsMinusCentrality10-40")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Pt Values for #pi^{-}, 10-40% Centrality")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsPtForPionsMinusCentrality10-40"))

HistogramCompA.Rebin()

HistogramCompA.Draw("HIST P E X0")

CanvasPmPtComp.Draw()

Canvasas.append(CanvasPmPtComp)



CanvasDePtComp = ROOT.TCanvas("CanvasDePtComp", "", 800, 800)
CanvasDePtComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsPtForDeuteronsCentrality10-40")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Pt Values for Deuterons, 10-40% Centrality")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsPtForDeuteronsCentrality10-40"))

HistogramCompA.Rebin()

if (nV == 2):
    HistogramCompA.SetAxisRange(0.0, 2.0, "Y")

HistogramCompA.Draw("HIST P E X0")

CanvasDePtComp.Draw()

Canvasas.append(CanvasDePtComp)



CanvasTrPtComp = ROOT.TCanvas("CanvasTrPtComp", "", 800, 800)
CanvasTrPtComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsPtForTritonsCentrality10-40")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Pt Values for Tritons, 10-40% Centrality")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsPtForTritonsCentrality10-40"))

HistogramCompA.Rebin()

if (nV == 2):
    HistogramCompA.SetAxisRange(0.0, 2.0, "Y")

HistogramCompA.Draw("HIST P E X0")

CanvasTrPtComp.Draw()

Canvasas.append(CanvasTrPtComp)



CanvasPrYComp = ROOT.TCanvas("CanvasPrYComp", "", 800, 800)
CanvasPrYComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsYForProtonsCentrality10-40")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Y Values for Protons, 10-40% Centrality")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsYForProtonsCentrality10-40"))

HistogramCompA.Draw("HIST P E X0")

CanvasPrYComp.Draw()

Canvasas.append(CanvasPrYComp)


CanvasKpYComp = ROOT.TCanvas("CanvasKpYComp", "", 800, 800)
CanvasKpYComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsYForKaonsPlusCentrality10-40")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Y Values for K^{+}, 10-40% Centrality")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsYForKaonsPlusCentrality10-40"))

if (nV == 2):
    HistogramCompA.SetAxisRange(-3.0, 5.0, "Y")

HistogramCompA.Draw("HIST P E X0")

CanvasKpYComp.Draw()

Canvasas.append(CanvasKpYComp)



CanvasKmYComp = ROOT.TCanvas("CanvasKmYComp", "", 800, 800)
CanvasKmYComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsYForKaonsMinusCentrality10-40")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Y Values for K^{-}, 10-40% Centrality")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsYForKaonsMinusCentrality10-40"))

if (nV == 2):
    HistogramCompA.SetAxisRange(-1.0, 3.0, "Y")

HistogramCompA.Draw("HIST P E X0")

CanvasKmYComp.Draw()

Canvasas.append(CanvasKmYComp)



CanvasPpYComp = ROOT.TCanvas("CanvasPpYComp", "", 800, 800)
CanvasPpYComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsYForPionsPlusCentrality10-40")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Y Values for #pi^{+}, 10-40% Centrality")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsYForPionsPlusCentrality10-40"))

HistogramCompA.Draw("HIST P E X0")

CanvasPpYComp.Draw()

Canvasas.append(CanvasPpYComp)



CanvasPmYComp = ROOT.TCanvas("CanvasPmYComp", "", 800, 800)
CanvasPmYComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsYForPionsMinusCentrality10-40")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Y Values for #pi^{-}, 10-40% Centrality")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsYForPionsMinusCentrality10-40"))

HistogramCompA.Draw("HIST P E X0")

CanvasPmYComp.Draw()

Canvasas.append(CanvasPmYComp)



CanvasDeYComp = ROOT.TCanvas("CanvasDeYComp", "", 800, 800)
CanvasDeYComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsYForDeuteronsCentrality10-40")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Y Values for Deuterons, 10-40% Centrality")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsYForDeuteronsCentrality10-40"))

HistogramCompA.Draw("HIST P E X0")

CanvasDeYComp.Draw()

Canvasas.append(CanvasDeYComp)



CanvasTrYComp = ROOT.TCanvas("CanvasTrYComp", "", 800, 800)
CanvasTrYComp.cd()

HistogramCompA = MyFileFirst.Get("DataVnVsYForTritonsCentrality10-40")

HistogramCompA.SetDirectory(0)

HistogramCompA.SetStats(0)

HistogramCompA.SetTitle("Ratio of 32 Bit to 64 Bit V_{" + str(nV) + "} vs Y Values for Tritons, 10-40% Centrality")
HistogramCompA.GetYaxis().SetTitle("Ratio")

if (nV == 2):
    HistogramCompA.GetYaxis().SetTitleOffset(1.5)

HistogramCompA.SetLineWidth(10)
HistogramCompA.SetLineColor(ROOT.kBlue)
HistogramCompA.SetMarkerSize(3)
HistogramCompA.SetMarkerStyle(ROOT.kFullCircle)
HistogramCompA.SetMarkerColor(ROOT.kBlue)

HistogramCompA.Divide(MyFileSecond.Get("DataVnVsYForTritonsCentrality10-40"))

HistogramCompA.Draw("HIST P E X0")

CanvasTrYComp.Draw()

Canvasas.append(CanvasTrYComp)





MyFileFirst.Close()
MyFileSecond.Close()



for index in range(0, len(Canvasas)):
    if len(Canvasas) == 1:
        Canvasas[index].SaveAs(Date + '_32BitVs64BitComparison_Plots.pdf)')
        break
    
    if index == 0:
        print("Opening PDF")
        Canvasas[index].SaveAs(Date + '_32BitVs64BitComparison_Plots.pdf(')
    
    elif index == len(Canvasas) - 1:
        print("Closing PDF")
        Canvasas[index].SaveAs(Date + '_32BitVs64BitComparison_Plots.pdf)')
    
    else:
        Canvasas[index].SaveAs(Date + '_32BitVs64BitComparison_Plots.pdf')

