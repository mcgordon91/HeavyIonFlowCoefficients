#!/usr/bin/env python
# coding: utf-8



import ROOT
import os
import sys






ToFFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/ToFEfficiency.root","UPDATE")





Histogram1 = ToFFile.Get("ProtonToFDetected")
Histogram2 = ToFFile.Get("ProtonTPCDetected")
HistogramPr = ROOT.TH2D("ProtonToFEfficiency", "Proton ToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramPr = Histogram1.Clone()

HistogramPr.Divide(Histogram2)

HistogramPr.SetName("ProtonToFEfficiency")
HistogramPr.SetTitle("Proton ToF Efficiencies")
HistogramPr.GetXaxis().SetTitle("#eta")
HistogramPr.GetYaxis().SetTitle("P_{t} (GeV)")

HistogramPr.SetDirectory(0)








Histogram1 = ToFFile.Get("KaonPlusToFDetected")
Histogram2 = ToFFile.Get("KaonPlusTPCDetected")
HistogramKp = ROOT.TH2D("KaonPlusToFEfficiency", "K^{+} ToF Efficiencies; #eta; P_{t} (GeV)", 30, -3, 0, 60, 0, 6)

HistogramKp = Histogram1.Clone()

HistogramKp.Divide(Histogram2)

HistogramKp.SetName("KaonPlusToFEfficiency")
HistogramKp.SetTitle("K^{+} ToF Efficiencies")
HistogramKp.GetXaxis().SetTitle("#eta")
HistogramKp.GetYaxis().SetTitle("P_{t} (GeV)")

HistogramKp.SetDirectory(0)






Histogram1 = ToFFile.Get("KaonMinusToFDetected")
Histogram2 = ToFFile.Get("KaonMinusTPCDetected")
HistogramKm = ROOT.TH2D("KaonMinusToFEfficiency", "K^{-} ToF Efficiencies; #eta; P_{t} (GeV)", 30, -3, 0, 60, 0, 6)

HistogramKm = Histogram1.Clone()

HistogramKm.Divide(Histogram2)

HistogramKm.SetName("KaonMinusToFEfficiency")
HistogramKm.SetTitle("K^{-} ToF Efficiencies")
HistogramKm.GetXaxis().SetTitle("#eta")
HistogramKm.GetYaxis().SetTitle("P_{t} (GeV)")

HistogramKm.SetDirectory(0)






Histogram1 = ToFFile.Get("PionPlusToFDetected")
Histogram2 = ToFFile.Get("PionPlusTPCDetected")
HistogramPp = ROOT.TH2D("PionPlusToFEfficiency", "#pi^{+} ToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramPp = Histogram1.Clone()

HistogramPp.Divide(Histogram2)

HistogramPp.SetName("PionPlusToFEfficiency")
HistogramPp.SetTitle("#pi^{+} ToF Efficiencies")
HistogramPp.GetXaxis().SetTitle("#eta")
HistogramPp.GetYaxis().SetTitle("P_{t} (GeV)")

HistogramPp.SetDirectory(0)








Histogram1 = ToFFile.Get("PionMinusToFDetected")
Histogram2 = ToFFile.Get("PionMinusTPCDetected")
HistogramPm = ROOT.TH2D("PionMinusToFEfficiency", "#pi^{-} ToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramPm = Histogram1.Clone()

HistogramPm.Divide(Histogram2)

HistogramPm.SetName("PionMinusToFEfficiency")
HistogramPm.SetTitle("#pi^{-} ToF Efficiencies")
HistogramPm.GetXaxis().SetTitle("#eta")
HistogramPm.GetYaxis().SetTitle("P_{t} (GeV)")

HistogramPm.SetDirectory(0)







Histogram1 = ToFFile.Get("DeuteronToFDetected")
Histogram2 = ToFFile.Get("DeuteronTPCDetected")
HistogramDe = ROOT.TH2D("DeuteronToFEfficiency", "d ToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramDe = Histogram1.Clone()

HistogramDe.Divide(Histogram2)

HistogramDe.SetName("DeuteronToFEfficiency")
HistogramDe.SetTitle("d ToF Efficiencies")
HistogramDe.GetXaxis().SetTitle("#eta")
HistogramDe.GetYaxis().SetTitle("P_{t} (GeV)")

HistogramDe.SetDirectory(0)






Histogram1 = ToFFile.Get("TritonToFDetected")
Histogram2 = ToFFile.Get("TritonTPCDetected")
HistogramTr = ROOT.TH2D("TritonToFEfficiency", "t ToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramTr = Histogram1.Clone()

HistogramTr.Divide(Histogram2)

HistogramTr.SetName("TritonToFEfficiency")
HistogramTr.SetTitle("t ToF Efficiencies")
HistogramTr.GetXaxis().SetTitle("#eta")
HistogramTr.GetYaxis().SetTitle("P_{t} (GeV)")

HistogramTr.SetDirectory(0)








Histogram1 = ToFFile.Get("ProtonEToFDetected")
Histogram2 = ToFFile.Get("ProtonTPCDetected")
HistogramPrEToF = ROOT.TH2D("ProtonEToFEfficiency", "Proton EToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramPrEToF = Histogram1.Clone()

HistogramPrEToF.Divide(Histogram2)

HistogramPrEToF.SetName("ProtonEToFEfficiency")
HistogramPrEToF.SetTitle("Proton EToF Efficiencies")
HistogramPrEToF.GetXaxis().SetTitle("#eta")
HistogramPrEToF.GetYaxis().SetTitle("P_{t} (GeV)")

HistogramPrEToF.SetDirectory(0)








Histogram1 = ToFFile.Get("KaonPlusEToFDetected")
Histogram2 = ToFFile.Get("KaonPlusTPCDetected")
HistogramKpEToF = ROOT.TH2D("KaonPlusEToFEfficiency", "K^{+} EToF Efficiencies; #eta; P_{t} (GeV)", 30, -3, 0, 60, 0, 6)

HistogramKpEToF = Histogram1.Clone()

HistogramKpEToF.Divide(Histogram2)

HistogramKpEToF.SetName("KaonPlusEToFEfficiency")
HistogramKpEToF.SetTitle("K^{+} EToF Efficiencies")
HistogramKpEToF.GetXaxis().SetTitle("#eta")
HistogramKpEToF.GetYaxis().SetTitle("P_{t} (GeV)")

HistogramKpEToF.SetDirectory(0)






Histogram1 = ToFFile.Get("KaonMinusEToFDetected")
Histogram2 = ToFFile.Get("KaonMinusTPCDetected")
HistogramKmEToF = ROOT.TH2D("KaonMinusEToFEfficiency", "K^{-} EToF Efficiencies; #eta; P_{t} (GeV)", 30, -3, 0, 60, 0, 6)

HistogramKmEToF = Histogram1.Clone()

HistogramKmEToF.Divide(Histogram2)

HistogramKmEToF.SetName("KaonMinusEToFEfficiency")
HistogramKmEToF.SetTitle("K^{-} EToF Efficiencies")
HistogramKmEToF.GetXaxis().SetTitle("#eta")
HistogramKmEToF.GetYaxis().SetTitle("P_{t} (GeV)")

HistogramKmEToF.SetDirectory(0)






Histogram1 = ToFFile.Get("PionPlusEToFDetected")
Histogram2 = ToFFile.Get("PionPlusTPCDetected")
HistogramPpEToF = ROOT.TH2D("PionPlusEToFEfficiency", "#pi^{+} EToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramPpEToF = Histogram1.Clone()

HistogramPpEToF.Divide(Histogram2)

HistogramPpEToF.SetName("PionPlusEToFEfficiency")
HistogramPpEToF.SetTitle("#pi^{+} EToF Efficiencies")
HistogramPpEToF.GetXaxis().SetTitle("#eta")
HistogramPpEToF.GetYaxis().SetTitle("P_{t} (GeV)")

HistogramPpEToF.SetDirectory(0)








Histogram1 = ToFFile.Get("PionMinusEToFDetected")
Histogram2 = ToFFile.Get("PionMinusTPCDetected")
HistogramPmEToF = ROOT.TH2D("PionMinusEToFEfficiency", "#pi^{-} EToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramPmEToF = Histogram1.Clone()

HistogramPmEToF.Divide(Histogram2)

HistogramPmEToF.SetName("PionMinusEToFEfficiency")
HistogramPmEToF.SetTitle("#pi^{-} EToF Efficiencies")
HistogramPmEToF.GetXaxis().SetTitle("#eta")
HistogramPmEToF.GetYaxis().SetTitle("P_{t} (GeV)")

HistogramPmEToF.SetDirectory(0)







Histogram1 = ToFFile.Get("DeuteronEToFDetected")
Histogram2 = ToFFile.Get("DeuteronTPCDetected")
HistogramDeEToF = ROOT.TH2D("DeuteronEToFEfficiency", "d EToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramDeEToF = Histogram1.Clone()

HistogramDeEToF.Divide(Histogram2)

HistogramDeEToF.SetName("DeuteronEToFEfficiency")
HistogramDeEToF.SetTitle("d EToF Efficiencies")
HistogramDeEToF.GetXaxis().SetTitle("#eta")
HistogramDeEToF.GetYaxis().SetTitle("P_{t} (GeV)")

HistogramDeEToF.SetDirectory(0)






Histogram1 = ToFFile.Get("TritonEToFDetected")
Histogram2 = ToFFile.Get("TritonTPCDetected")
HistogramTrEToF = ROOT.TH2D("TritonEToFEfficiency", "t EToF Efficiencies; #eta; P_{t} (GeV)", 300, -3, 0, 600, 0, 6)

HistogramTrEToF = Histogram1.Clone()

HistogramTrEToF.Divide(Histogram2)

HistogramTrEToF.SetName("TritonEToFEfficiency")
HistogramTrEToF.SetTitle("t EToF Efficiencies")
HistogramTrEToF.GetXaxis().SetTitle("#eta")
HistogramTrEToF.GetYaxis().SetTitle("P_{t} (GeV)")

HistogramTrEToF.SetDirectory(0)







HistogramPr.Write()
HistogramKp.Write()
HistogramKm.Write()
HistogramPp.Write()
HistogramPm.Write()
HistogramDe.Write()
HistogramTr.Write()
HistogramPrEToF.Write()
HistogramKpEToF.Write()
HistogramKmEToF.Write()
HistogramPpEToF.Write()
HistogramPmEToF.Write()
HistogramDeEToF.Write()
HistogramTrEToF.Write()




ToFFile.Close()

print("DONE")
