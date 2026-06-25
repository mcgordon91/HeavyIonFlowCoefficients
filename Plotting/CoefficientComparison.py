import ROOT
import os
import sys

Canvasas = []

nV = 1
Date = '6-20-25'

FirstCoefficientFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/5-30-25-V1-HistogramNormalFullDataset.root","READ")
SecondCoefficientFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/5-30-25-V3-HistogramNormalFullDataset.root","READ")






Canvas1 = ROOT.TCanvas("Canvas1", "", 800, 800)
Canvas1.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsCentralityProtonCorrected")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Centrality for Protons")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.08, 0.02, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsCentralityProtonCorrected")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas1.Draw()

Legend1 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend1.AddEntry(HistogramA, "V2")
Legend1.AddEntry(HistogramB, "V4")
Legend1.Draw()

Canvasas.append(Canvas1)





Canvas2 = ROOT.TCanvas("Canvas2", "", 800, 800)
Canvas2.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsPtForProtonsCentrality10-40")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Pt for Protons, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.08, 0.02, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsPtForProtonsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas2.Draw()

Legend2 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend2.AddEntry(HistogramA, "V2")
Legend2.AddEntry(HistogramB, "V4")
Legend2.Draw()

Canvasas.append(Canvas2)






Canvas3 = ROOT.TCanvas("Canvas3", "", 800, 800)
Canvas3.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsYForProtonsCentrality10-40")

RescaledHistogram = ROOT.TH1F("VnVsYForProtonsCentrality10-40Rescaled", "; y_{cm}; V_{n}", 10, 0, 1)

for index in range(1, HistogramA.GetNbinsX() + 1):
    RescaledHistogram.SetBinContent(index, HistogramA.GetBinContent(index) / 10)
    RescaledHistogram.SetBinError(index, HistogramA.GetBinError(index) / 10)
    
RescaledHistogram.SetDirectory(0)

RescaledHistogram.SetStats(0)

RescaledHistogram.SetLineWidth(10)
RescaledHistogram.SetMarkerStyle(ROOT.kFullCircle)
RescaledHistogram.SetMarkerSize(3)
RescaledHistogram.SetMarkerColor(ROOT.kBlue)

RescaledHistogram.SetLineColor(ROOT.kBlue)

RescaledHistogram.SetTitle("V1 and V3 vs Y for Protons, 10-40% Centrality")
RescaledHistogram.GetYaxis().SetTitleOffset(1)

RescaledHistogram.GetYaxis().SetTitle("V_{n}")

RescaledHistogram.SetAxisRange(-0.05, 0.2, "Y")

RescaledHistogram.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsYForProtonsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas3.Draw()

Legend3 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend3.AddEntry(RescaledHistogram, "V1 / 10")
Legend3.AddEntry(HistogramB, "V3")
Legend3.Draw()

Canvasas.append(Canvas3)




Canvas4 = ROOT.TCanvas("Canvas4", "", 800, 800)
Canvas4.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsCentralityKaonPlusCorrected")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Centrality for K+")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.08, 0.02, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsCentralityKaonPlusCorrected")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas4.Draw()

Legend4 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend4.AddEntry(HistogramA, "V2")
Legend4.AddEntry(HistogramB, "V4")
Legend4.Draw()

Canvasas.append(Canvas4)





Canvas5 = ROOT.TCanvas("Canvas5", "", 800, 800)
Canvas5.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsPtForKaonsPlusCentrality10-40")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Pt for K+, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.08, 0.02, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsPtForKaonsPlusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas5.Draw()

Legend5 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend5.AddEntry(HistogramA, "V2")
Legend5.AddEntry(HistogramB, "V4")
Legend5.Draw()

Canvasas.append(Canvas5)






Canvas6 = ROOT.TCanvas("Canvas6", "", 800, 800)
Canvas6.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsYForKaonsPlusCentrality10-40")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Y for K+, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.08, 0.02, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsYForKaonsPlusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas6.Draw()

Legend6 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend6.AddEntry(HistogramA, "V2")
Legend6.AddEntry(HistogramB, "V4")
Legend6.Draw()

Canvasas.append(Canvas6)



Canvas7 = ROOT.TCanvas("Canvas7", "", 800, 800)
Canvas7.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsCentralityKaonMinusCorrected")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Centrality for K-")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.05, 0.05, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsCentralityKaonMinusCorrected")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas7.Draw()

Legend7 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend7.AddEntry(HistogramA, "V2")
Legend7.AddEntry(HistogramB, "V4")
Legend7.Draw()

Canvasas.append(Canvas7)





Canvas8 = ROOT.TCanvas("Canvas8", "", 800, 800)
Canvas8.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsPtForKaonsMinusCentrality10-40")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Pt for K-, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.05, 0.05, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsPtForKaonsMinusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas8.Draw()

Legend8 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend8.AddEntry(HistogramA, "V2")
Legend8.AddEntry(HistogramB, "V4")
Legend8.Draw()

Canvasas.append(Canvas8)




Canvas9 = ROOT.TCanvas("Canvas9", "", 800, 800)
Canvas9.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsYForKaonsMinusCentrality10-40")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Y for K-, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.05, 0.05, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsYForKaonsMinusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas9.Draw()

Legend9 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend9.AddEntry(HistogramA, "V2")
Legend9.AddEntry(HistogramB, "V4")
Legend9.Draw()

Canvasas.append(Canvas9)




Canvas10 = ROOT.TCanvas("Canvas10", "", 800, 800)
Canvas10.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsCentralityPionPlusCorrected")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Centrality for Pi+")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.08, 0.01, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsCentralityPionPlusCorrected")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas10.Draw()

Legend10 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend10.AddEntry(HistogramA, "V2")
Legend10.AddEntry(HistogramB, "V4")
Legend10.Draw()

Canvasas.append(Canvas10)





Canvas11 = ROOT.TCanvas("Canvas11", "", 800, 800)
Canvas11.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsPtForPionsPlusCentrality10-40")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Pt for Pi+, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.08, 0.01, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsPtForPionsPlusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas11.Draw()

Legend11 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend11.AddEntry(HistogramA, "V2")
Legend11.AddEntry(HistogramB, "V4")
Legend11.Draw()

Canvasas.append(Canvas11)






Canvas12 = ROOT.TCanvas("Canvas12", "", 800, 800)
Canvas12.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsYForPionsPlusCentrality10-40")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Y for Pi+, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.08, 0.01, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsYForPionsPlusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas12.Draw()

Legend12 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend12.AddEntry(HistogramA, "V2")
Legend12.AddEntry(HistogramB, "V4")
Legend12.Draw()

Canvasas.append(Canvas12)



Canvas13 = ROOT.TCanvas("Canvas13", "", 800, 800)
Canvas13.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsCentralityPionMinusCorrected")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Centrality for Pi-")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.02, 0.03, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsCentralityPionMinusCorrected")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas13.Draw()

Legend13 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend13.AddEntry(HistogramA, "V2")
Legend13.AddEntry(HistogramB, "V4")
Legend13.Draw()

Canvasas.append(Canvas13)





Canvas14 = ROOT.TCanvas("Canvas14", "", 800, 800)
Canvas14.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsPtForPionsMinusCentrality10-40")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Pt for Pi-, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.02, 0.03, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsPtForPionsMinusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas14.Draw()

Legend14 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend14.AddEntry(HistogramA, "V2")
Legend14.AddEntry(HistogramB, "V4")
Legend14.Draw()

Canvasas.append(Canvas14)




Canvas15 = ROOT.TCanvas("Canvas15", "", 800, 800)
Canvas15.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsYForPionsMinusCentrality10-40")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Y for Pi-, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.02, 0.03, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsYForPionsMinusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas15.Draw()

Legend15 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend15.AddEntry(HistogramA, "V2")
Legend15.AddEntry(HistogramB, "V4")
Legend15.Draw()

Canvasas.append(Canvas15)




Canvas16 = ROOT.TCanvas("Canvas16", "", 800, 800)
Canvas16.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsCentralityDeuteronCorrected")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Centrality for Deuterons")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.1, 0.05, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsCentralityDeuteronCorrected")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas16.Draw()

Legend16 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend16.AddEntry(HistogramA, "V2")
Legend16.AddEntry(HistogramB, "V4")
Legend16.Draw()

Canvasas.append(Canvas16)





Canvas17 = ROOT.TCanvas("Canvas17", "", 800, 800)
Canvas17.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsPtForDeuteronsCentrality10-40")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V1 and V3 vs Pt for Deuterons, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.Rebin()

HistogramA.SetAxisRange(-0.1, 0.05, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsPtForDeuteronsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Rebin()

HistogramB.Draw("PE 1 X0 SAME")

Canvas17.Draw()

Legend17 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend17.AddEntry(HistogramA, "V2")
Legend17.AddEntry(HistogramB, "V4")
Legend17.Draw()

Canvasas.append(Canvas17)






Canvas18 = ROOT.TCanvas("Canvas18", "", 800, 800)
Canvas18.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsYForDeuteronsCentrality10-40")

RescaledHistogram1 = ROOT.TH1F("VnVsYForDeuteronsCentrality10-40Rescaled", "; y_{cm}; V_{n}", 10, 0, 1)

for index in range(1, HistogramA.GetNbinsX() + 1):
    RescaledHistogram1.SetBinContent(index, HistogramA.GetBinContent(index) / 20)
    RescaledHistogram1.SetBinError(index, HistogramA.GetBinError(index) / 20)
    
RescaledHistogram1.SetDirectory(0)

RescaledHistogram1.SetStats(0)

RescaledHistogram1.SetLineWidth(10)
RescaledHistogram1.SetMarkerStyle(ROOT.kFullCircle)
RescaledHistogram1.SetMarkerSize(3)
RescaledHistogram1.SetMarkerColor(ROOT.kBlue)

RescaledHistogram1.SetLineColor(ROOT.kBlue)

RescaledHistogram1.SetTitle("V1 and V3 vs Y for Deuterons, 10-40% Centrality")
RescaledHistogram1.GetYaxis().SetTitleOffset(1)

RescaledHistogram1.GetYaxis().SetTitle("V_{n}")

RescaledHistogram1.SetAxisRange(-0.1, 0.3, "Y")

RescaledHistogram1.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsYForDeuteronsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas18.Draw()

Legend18 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend18.AddEntry(RescaledHistogram1, "V1 / 20")
Legend18.AddEntry(HistogramB, "V3")
Legend18.Draw()

Canvasas.append(Canvas18)




Canvas19 = ROOT.TCanvas("Canvas19", "", 800, 800)
Canvas19.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsCentralityTritonCorrected")
    
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Centrality for Tritons")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.SetAxisRange(-0.1, 0.1, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsCentralityTritonCorrected")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas19.Draw()

Legend19 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend19.AddEntry(HistogramA, "V2")
Legend19.AddEntry(HistogramB, "V4")
Legend19.Draw()

Canvasas.append(Canvas19)





Canvas20 = ROOT.TCanvas("Canvas20", "", 800, 800)
Canvas20.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsPtForTritonsCentrality10-40")
HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(10)
HistogramA.SetMarkerStyle(ROOT.kFullCircle)
HistogramA.SetMarkerSize(3)
HistogramA.SetMarkerColor(ROOT.kBlue)

HistogramA.SetLineColor(ROOT.kBlue)

HistogramA.SetTitle("V2 and V4 vs Pt for Tritons, 10-40% Centrality")
HistogramA.GetYaxis().SetTitleOffset(1)

HistogramA.GetYaxis().SetTitle("V_{n}")

HistogramA.Rebin(3)

HistogramA.SetAxisRange(-0.1, 0.1, "Y")

HistogramA.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsPtForTritonsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Rebin(3)

HistogramB.Draw("PE 1 X0 SAME")

Canvas20.Draw()

Legend20 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend20.AddEntry(HistogramA, "V2")
Legend20.AddEntry(HistogramB, "V4")
Legend20.Draw()

Canvasas.append(Canvas20)






Canvas21 = ROOT.TCanvas("Canvas21", "", 800, 800)
Canvas21.cd()

HistogramA = FirstCoefficientFile.Get("DataVnVsYForTritonsCentrality10-40")

RescaledHistogram2 = ROOT.TH1F("VnVsYForTritonsCentrality10-40Rescaled", "; y_{cm}; V_{n}", 10, 0, 1)

for index in range(1, HistogramA.GetNbinsX() + 1):
    RescaledHistogram2.SetBinContent(index, HistogramA.GetBinContent(index) / 15)
    RescaledHistogram2.SetBinError(index, HistogramA.GetBinError(index) / 15)
    
RescaledHistogram2.SetDirectory(0)

RescaledHistogram2.SetStats(0)

RescaledHistogram2.SetLineWidth(10)
RescaledHistogram2.SetMarkerStyle(ROOT.kFullCircle)
RescaledHistogram2.SetMarkerSize(3)
RescaledHistogram2.SetMarkerColor(ROOT.kBlue)

RescaledHistogram2.SetLineColor(ROOT.kBlue)

RescaledHistogram2.SetTitle("V2 and V4 vs Y for Tritons, 10-40% Centrality")
RescaledHistogram2.GetYaxis().SetTitleOffset(1)

RescaledHistogram2.GetYaxis().SetTitle("V_{n}")

RescaledHistogram2.SetAxisRange(-0.1, 0.1, "Y")

RescaledHistogram2.Draw("PE 1 X0")

HistogramB = SecondCoefficientFile.Get("DataVnVsYForTritonsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullSquare)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kRed)

HistogramB.SetLineColor(ROOT.kRed)

HistogramB.Draw("PE 1 X0 SAME")

Canvas21.Draw()

Legend21 = ROOT.TLegend(0.1, 0.8, 0.25, 0.9)
Legend21.AddEntry(RescaledHistogram2, "V1 / 15")
Legend21.AddEntry(HistogramB, "V3")
Legend21.Draw()

Canvasas.append(Canvas21)





CanvasScalingY10_40First = ROOT.TCanvas("CanvasScalingY10_40First", "", 800, 800)
CanvasScalingY10_40First.cd()

HistogramProton1 = FirstCoefficientFile.Get("DataVnVsYForProtonsCentrality10-40")

HistogramProton1.SetDirectory(0)

HistogramProton1.SetStats(0)

HistogramProton1.SetTitle("Scaling Plot of p, d and t (V2 vs Y, 10-40% Centrality)")

HistogramProton1.GetYaxis().SetTitle("V2 / A")

HistogramProton1.GetYaxis().SetTitleOffset(1.5)

HistogramProton1.SetLineWidth(15)
HistogramProton1.SetMarkerStyle(ROOT.kFullSquare)
HistogramProton1.SetMarkerSize(3)
HistogramProton1.SetMarkerColor(ROOT.kRed)

HistogramProton1.SetLineColor(ROOT.kRed)

# HistogramProton6.SetAxisRange(-0.05, 0.01, "Y")

HistogramProton1.Draw("PE 1 X0")

Histogram = FirstCoefficientFile.Get("DataVnVsYForDeuteronsCentrality10-40")

NewHistogramScaled1 = ROOT.TH1D("DataVnVsYForDeuteronsCentrality10-40Scaled", "Scaling Plot of p, d and t; Centrality; V2 / A", 10, 0, 1)

NewHistogramScaled1.SetDirectory(0)

NewHistogramScaled1.SetStats(0)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled1.SetBinContent(index, Histogram.GetBinContent(index) / 2)
    NewHistogramScaled1.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled1.SetLineWidth(10)
NewHistogramScaled1.SetMarkerStyle(ROOT.kFullCircle)
NewHistogramScaled1.SetMarkerSize(3)
NewHistogramScaled1.SetMarkerColor(ROOT.kBlue)

NewHistogramScaled1.SetLineColor(ROOT.kBlue)

NewHistogramScaled1.Draw("PE 1 X0 SAME")

Histogram = FirstCoefficientFile.Get("DataVnVsYForTritonsCentrality10-40")

NewHistogramScaled2 = ROOT.TH1D("DataVnVsYForTritonsCentrality10-40Scaled", "Scaling Plot of p, d and t; Centrality; V12/ A", 10, 0, 1)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled2.SetBinContent(index, Histogram.GetBinContent(index) / 3)
    NewHistogramScaled2.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled2.SetDirectory(0)

NewHistogramScaled2.SetStats(0)
    
NewHistogramScaled2.SetLineWidth(5)
NewHistogramScaled2.SetMarkerStyle(ROOT.kFullTriangleDown)
NewHistogramScaled2.SetMarkerSize(3)
NewHistogramScaled2.SetMarkerColor(ROOT.kGreen)

NewHistogramScaled2.SetLineColor(ROOT.kGreen)

NewHistogramScaled2.Draw("PE 1 X0 SAME")

CanvasScalingY10_40First.Draw()

LegendScalingY10_40First = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)
LegendScalingY10_40First.AddEntry(HistogramProton1, "Protons")
LegendScalingY10_40First.AddEntry(NewHistogramScaled1, "Deuterons")
LegendScalingY10_40First.AddEntry(NewHistogramScaled2, "Tritons")
LegendScalingY10_40First.Draw()

Canvasas.append(CanvasScalingY10_40First)






CanvasScalingY10_40Second = ROOT.TCanvas("CanvasScalingY10_40Second", "", 800, 800)
CanvasScalingY10_40Second.cd()

HistogramProton2 = SecondCoefficientFile.Get("DataVnVsYForProtonsCentrality10-40")

HistogramProton2.SetDirectory(0)

HistogramProton2.SetStats(0)

HistogramProton2.SetTitle("Scaling Plot of p, d and t (V4 vs Y, 10-40% Centrality)")

HistogramProton2.GetYaxis().SetTitle("V4 / A")

HistogramProton2.GetYaxis().SetTitleOffset(1.5)

HistogramProton2.SetLineWidth(15)
HistogramProton2.SetMarkerStyle(ROOT.kFullSquare)
HistogramProton2.SetMarkerSize(3)
HistogramProton2.SetMarkerColor(ROOT.kRed)

HistogramProton2.SetLineColor(ROOT.kRed)

# HistogramProton6.SetAxisRange(-0.05, 0.01, "Y")

HistogramProton2.Draw("PE 1 X0")

Histogram = SecondCoefficientFile.Get("DataVnVsYForDeuteronsCentrality10-40")

NewHistogramScaled3 = ROOT.TH1D("DataVnVsYForDeuteronsCentrality10-40Scaled", "Scaling Plot of p, d and t; Centrality; V4 / A", 10, 0, 1)

NewHistogramScaled3.SetDirectory(0)

NewHistogramScaled3.SetStats(0)

for index in range(1, Histogram.GetNbinsX() + 1):
    NewHistogramScaled3.SetBinContent(index, Histogram.GetBinContent(index) / 2)
    NewHistogramScaled3.SetBinError(index, Histogram.GetBinError(index))
    
NewHistogramScaled3.SetLineWidth(10)
NewHistogramScaled3.SetMarkerStyle(ROOT.kFullCircle)
NewHistogramScaled3.SetMarkerSize(3)
NewHistogramScaled3.SetMarkerColor(ROOT.kBlue)

NewHistogramScaled3.SetLineColor(ROOT.kBlue)

NewHistogramScaled3.Draw("PE 1 X0 SAME")

# Histogram = SecondCoefficientFile.Get("DataVnVsYForTritonsCentrality10-40")

# NewHistogramScaled4 = ROOT.TH1D("DataVnVsYForTritonsCentrality10-40Scaled", "Scaling Plot of p, d and t; Centrality; V4 / A", 10, 0, 1)

# for index in range(1, Histogram.GetNbinsX() + 1):
#     NewHistogramScaled4.SetBinContent(index, Histogram.GetBinContent(index) / 3)
#     NewHistogramScaled4.SetBinError(index, Histogram.GetBinError(index))
    
# NewHistogramScaled4.SetDirectory(0)

# NewHistogramScaled4.SetStats(0)
    
# NewHistogramScaled4.SetLineWidth(5)
# NewHistogramScaled4.SetMarkerStyle(ROOT.kFullTriangleDown)
# NewHistogramScaled4.SetMarkerSize(3)
# NewHistogramScaled4.SetMarkerColor(ROOT.kGreen)

# NewHistogramScaled4.SetLineColor(ROOT.kGreen)

# NewHistogramScaled4.Draw("PE 1 X0 SAME")

CanvasScalingY10_40Second.Draw()

LegendScalingY10_40Second = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
LegendScalingY10_40Second.AddEntry(HistogramProton2, "Protons")
LegendScalingY10_40Second.AddEntry(NewHistogramScaled3, "Deuterons")
# LegendScalingY10_40Second.AddEntry(NewHistogramScaled4, "Tritons")
LegendScalingY10_40Second.Draw()

Canvasas.append(CanvasScalingY10_40Second)




FirstCoefficientFile.Close()
SecondCoefficientFile.Close()




for index in range(0, len(Canvasas)):
    if len(Canvasas) == 1:
        Canvasas[index].SaveAs(Date + '_Coefficient_Comparison_Plots.pdf)')
        break
    
    if index == 0:
        print("Opening PDF")
        Canvasas[index].SaveAs(Date + '_Coefficient_Comparison_Plots.pdf(')
    
    elif index == len(Canvasas) - 1:
        print("Closing PDF")
        Canvasas[index].SaveAs(Date + '_Coefficient_Comparison_Plots.pdf)')
    
    else:
        Canvasas[index].SaveAs(Date + '_Coefficient_Comparison_Plots.pdf')
