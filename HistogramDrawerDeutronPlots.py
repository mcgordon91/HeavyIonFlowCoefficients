#!/usr/bin/env python
# coding: utf-8



import ROOT
import os
import sys

Canvasas = []





HistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V2Histograms/HistogramFirstPass.root","READ")





Histogram = HistogramRootFile.Get("DatadEdxVsP")

Histogram.SetDirectory(0)

Canvas1 = ROOT.TCanvas("Canvas1", "", 800, 800)

Canvas1.cd()

Histogram.SetStats(0)
Histogram.SetContour(1000)

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

Canvas3.SetLogz()

Histogram.Draw("colz")

Canvas3.Draw()

Canvasas.append(Canvas3)






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








HistogramRootFile.Close()







for index in range(0, len(Canvasas)):
    if len(Canvasas) == 1:
        Canvasas[index].SaveAs('7-9-23_V2_Deuterons_Tritons.pdf)')
        break
    
    if index == 0:
        print("Opening PDF")
        Canvasas[index].SaveAs('7-9-23_V2_Deuterons_Tritons.pdf(')
    
    elif index == len(Canvasas) - 1:
        print("Closing PDF")
        Canvasas[index].SaveAs('7-9-23_V2_Deuterons_Tritons.pdf)')
    
    else:
        Canvasas[index].SaveAs('7-9-23_V2_Deuterons_Tritons.pdf')
