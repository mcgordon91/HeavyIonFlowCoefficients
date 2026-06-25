#!/usr/bin/env python
# coding: utf-8



import ROOT
import os
import sys

Canvasas = []





HistogramRootFile = ROOT.TFile.Open("/star/u/mcgordon/HistogramFirstPassNormal.root")#("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/7-28-25-V1-HistogramNormal.root","READ")




# Histogram = HistogramRootFile.Get("TritonBadRunCheck")

# Histogram.SetDirectory(0)

# Canvas0 = ROOT.TCanvas("Canvas0", "", 800, 800)

# Canvas0.cd()

# Histogram.SetStats(0)
# Histogram.SetContour(1000)

# Histogram.Draw()

# Canvas0.Draw("colz")

# Canvasas.append(Canvas0)




Histogram = HistogramRootFile.Get("DatadEdxVsP")

Histogram.SetDirectory(0)

Canvas1 = ROOT.TCanvas("Canvas1", "", 800, 800)

Canvas1.cd()

Histogram.SetStats(0)
Histogram.SetContour(1000)

Histogram.SetMaximum(Histogram.GetMaximum())

Canvas1.SetLogz()

Histogram.Draw("colz")

Canvas1.Draw()

Canvasas.append(Canvas1)




Histogram = HistogramRootFile.Get("DatadEdxVsPDeuteron")

Histogram.SetDirectory(0)

Canvas2 = ROOT.TCanvas("Canvas2", "", 800, 800)

Canvas2.cd()

Histogram.SetStats(0)
Histogram.SetContour(1000)

Histogram.SetMaximum(Histogram.GetMaximum())

Canvas2.SetLogz()

Histogram.Draw("colz")

Canvas2.Draw()

Canvasas.append(Canvas2)




Histogram = HistogramRootFile.Get("DatadEdxVsPTriton")

Histogram.SetDirectory(0)

Canvas3 = ROOT.TCanvas("Canvas3", "", 800, 800)

Canvas3.cd()

Histogram.SetStats(0)
Histogram.SetContour(1000)

Histogram.SetMaximum(Histogram.GetMaximum())

Canvas3.SetLogz()

Histogram.Draw("colz")

Canvas3.Draw()

Canvasas.append(Canvas3)





'''
Histogram = HistogramRootFile.Get("DataPtVsYProton")

Histogram.SetDirectory(0)

Canvas4 = ROOT.TCanvas("Canvas4", "", 800, 800)

Canvas4.cd()

Histogram.SetStats(0)
Histogram.SetContour(1000)

Canvas4.SetLogz()

Histogram.Draw("colz")

Canvas4.Draw()

Canvasas.append(Canvas4)




Histogram = HistogramRootFile.Get("DataPtVsYDeuteron")

Histogram.SetDirectory(0)

Canvas5 = ROOT.TCanvas("Canvas5", "", 800, 800)

Canvas5.cd()

Histogram.SetStats(0)
Histogram.SetContour(1000)

Canvas5.SetLogz()

Histogram.Draw("colz")

Canvas5.Draw()

Canvasas.append(Canvas5)




Histogram = HistogramRootFile.Get("DataPtVsYTriton")

Histogram.SetDirectory(0)

Canvas6 = ROOT.TCanvas("Canvas6", "", 800, 800)

Canvas6.cd()

Histogram.SetStats(0)
Histogram.SetContour(1000)

Canvas6.SetLogz()

Histogram.Draw("colz")

Canvas6.Draw()

Canvasas.append(Canvas6)



Histogram = HistogramRootFile.Get("h2_zd_vs_mom")

Histogram.SetDirectory(0)

Histogram.SetTitle("Z_{d} vs Momentum")

CanvasZdVsP1 = ROOT.TCanvas("CanvasZdVsP1", "", 800, 800)
CanvasZdVsP1.cd()

CanvasZdVsP1.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasZdVsP1.Draw()

Canvasas.append(CanvasZdVsP1)



Histogram = HistogramRootFile.Get("h2_zt_vs_mom")

Histogram.SetDirectory(0)

Histogram.SetTitle("Z_{t} vs Momentum")

CanvasZtVsP1 = ROOT.TCanvas("CanvasZtVsP1", "", 800, 800)
CanvasZtVsP1.cd()

CanvasZtVsP1.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasZtVsP1.Draw()

Canvasas.append(CanvasZtVsP1)
'''




HistogramRootFile.Close()





'''
HistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V6Histograms/BischelPlotsNewDataset.root","READ")





Histogram = HistogramRootFile.Get("DatadEdxVsP")

Histogram.SetDirectory(0)

Canvas7 = ROOT.TCanvas("Canvas7", "", 800, 800)

Canvas7.cd()

Histogram.SetStats(0)
Histogram.SetContour(1000)

Canvas7.SetLogz()

Histogram.Draw("colz")

Canvas7.Draw()

Canvasas.append(Canvas7)




Histogram = HistogramRootFile.Get("DatadEdxVsPDeuteron")

Histogram.SetDirectory(0)

Canvas8 = ROOT.TCanvas("Canvas8", "", 800, 800)

Canvas8.cd()

Histogram.SetStats(0)
Histogram.SetContour(1000)

Canvas8.SetLogz()

Histogram.Draw("colz")

Canvas8.Draw()

Canvasas.append(Canvas8)




Histogram = HistogramRootFile.Get("DatadEdxVsPTriton")

Histogram.SetDirectory(0)

Canvas9 = ROOT.TCanvas("Canvas9", "", 800, 800)

Canvas9.cd()

Histogram.SetStats(0)
Histogram.SetContour(1000)

Canvas9.SetLogz()

Histogram.Draw("colz")

Canvas9.Draw()

Canvasas.append(Canvas9)






Histogram = HistogramRootFile.Get("DataPtVsYProton")

Histogram.SetDirectory(0)

Canvas10 = ROOT.TCanvas("Canvas10", "", 800, 800)

Canvas10.cd()

Histogram.SetStats(0)
Histogram.SetContour(1000)

Canvas10.SetLogz()

Histogram.Draw("colz")

Canvas10.Draw()

Canvasas.append(Canvas10)




Histogram = HistogramRootFile.Get("DataPtVsYDeuteron")

Histogram.SetDirectory(0)

Canvas11 = ROOT.TCanvas("Canvas11", "", 800, 800)

Canvas11.cd()

Histogram.SetStats(0)
Histogram.SetContour(1000)

Canvas11.SetLogz()

Histogram.Draw("colz")

Canvas11.Draw()

Canvasas.append(Canvas11)




Histogram = HistogramRootFile.Get("DataPtVsYTriton")

Histogram.SetDirectory(0)

Canvas12 = ROOT.TCanvas("Canvas12", "", 800, 800)

Canvas12.cd()

Histogram.SetStats(0)
Histogram.SetContour(1000)

Canvas12.SetLogz()

Histogram.Draw("colz")

Canvas12.Draw()

Canvasas.append(Canvas12)



Histogram = HistogramRootFile.Get("h2_zd_vs_mom")

Histogram.SetDirectory(0)

CanvasZdVsP2 = ROOT.TCanvas("CanvasZdVsP2", "", 800, 800)
CanvasZdVsP2.cd()

CanvasZdVsP2.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasZdVsP2.Draw()

Canvasas.append(CanvasZdVsP2)



Histogram = HistogramRootFile.Get("h2_zt_vs_mom")

Histogram.SetDirectory(0)

CanvasZtVsP2 = ROOT.TCanvas("CanvasZtVsP2", "", 800, 800)
CanvasZtVsP2.cd()

CanvasZtVsP2.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasZtVsP2.Draw()

Canvasas.append(CanvasZtVsP2)






HistogramRootFile.Close()







FirstHistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V6Histograms/BischelPlotsNewDataset.root", "READ")
SecondHistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V6Histograms/BischelPlotsOldDataset.root", "READ")




CanvasP = ROOT.TCanvas("CanvasP", "", 800, 800)
CanvasP.cd()

FirstHistogram = FirstHistogramRootFile.Get("MomDistBischel")

FirstHistogram.SetDirectory(0)

FirstHistogram.SetStats(0)

FirstHistogram.SetLineColor(ROOT.kBlue)

FirstHistogram.Scale(1.0 / 7.0)

FirstHistogram.Draw("HIST")

SecondHistogram = SecondHistogramRootFile.Get("MomDistBischel")

SecondHistogram.SetDirectory(0)

SecondHistogram.SetLineColor(ROOT.kRed)

SecondHistogram.Draw("HIST SAME")

CanvasP.Draw()

LegendP = ROOT.TLegend(0.4, 0.8, 0.9, 0.9)
LegendP.AddEntry(FirstHistogram, "3.0 GeV Au-Au 2021 Data / 7")
LegendP.AddEntry(SecondHistogram, "3.0 GeV Au-Au 2018 Data")
LegendP.Draw()

Canvasas.append(CanvasP)





CanvasZd = ROOT.TCanvas("CanvasZd", "", 800, 800)
CanvasZd.cd()

FirstHistogram = FirstHistogramRootFile.Get("ZDeuteronDist")

FirstHistogram.SetDirectory(0)

FirstHistogram.SetStats(0)

FirstHistogram.SetLineColor(ROOT.kBlue)

FirstHistogram.Scale(1.0 / 10.0)

FirstHistogram.Draw("HIST")

SecondHistogram = SecondHistogramRootFile.Get("ZDeuteronDist")

SecondHistogram.SetDirectory(0)

SecondHistogram.SetLineColor(ROOT.kRed)

SecondHistogram.Draw("HIST SAME")

CanvasZd.Draw()

LegendZd = ROOT.TLegend(0.1, 0.1, 0.6, 0.2)
LegendZd.AddEntry(FirstHistogram, "3.0 GeV Au-Au 2021 Data / 10")
LegendZd.AddEntry(SecondHistogram, "3.0 GeV Au-Au 2018 Data")
LegendZd.Draw()

Canvasas.append(CanvasZd)






CanvasZt = ROOT.TCanvas("CanvasZt", "", 800, 800)
CanvasZt.cd()

FirstHistogram = FirstHistogramRootFile.Get("ZTritonDist")

FirstHistogram.SetDirectory(0)

FirstHistogram.SetStats(0)

FirstHistogram.SetLineColor(ROOT.kBlue)

FirstHistogram.Scale(1.0 / 9.0)

FirstHistogram.Draw("HIST")

SecondHistogram = SecondHistogramRootFile.Get("ZTritonDist")

SecondHistogram.SetDirectory(0)

SecondHistogram.SetLineColor(ROOT.kRed)

SecondHistogram.Draw("HIST SAME")

CanvasZt.Draw()

LegendZt = ROOT.TLegend(0.4, 0.8, 0.9, 0.9)
LegendZt.AddEntry(FirstHistogram, "3.0 GeV Au-Au 2021 Data / 9")
LegendZt.AddEntry(SecondHistogram, "3.0 GeV Au-Au 2018 Data")
LegendZt.Draw()

Canvasas.append(CanvasZt)



FirstHistogramRootFile.Close()
SecondHistogramRootFile.Close()
'''


for index in range(0, len(Canvasas)):
    if len(Canvasas) == 1:
        Canvasas[index].SaveAs('7-28-25_Deuterons_Tritons.pdf)')
        break
    
    if index == 0:
        print("Opening PDF")
        Canvasas[index].SaveAs('7-28-25_Deuterons_Tritons.pdf(')
    
    elif index == len(Canvasas) - 1:
        print("Closing PDF")
        Canvasas[index].SaveAs('7-28-25_Deuterons_Tritons.pdf)')
    
    else:
        Canvasas[index].SaveAs('7-28-25_Deuterons_Tritons.pdf')

