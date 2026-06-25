import ROOT
import os
import sys

Canvasas = []

PrFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/EmbeddingAnalysis/Proton/Efficiency/eff_tpc_pr.root","READ")
KpFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/EmbeddingAnalysis/Kplus/Efficiency/eff_tpc_kp.root","READ")
KmFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/EmbeddingAnalysis/Kminus/Efficiency/eff_tpc_km.root","READ")
PpFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/EmbeddingAnalysis/Piplus/Efficiency/eff_tpc_pp.root","READ")
PmFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/EmbeddingAnalysis/Piminus/Efficiency/eff_tpc_pm.root","READ")
DeFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/EmbeddingAnalysis/Deuteron/Efficiency/eff_tpc_de.root","READ")
TrFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/EmbeddingAnalysis/Triton/Efficiency/eff_tpc_tr.root","READ")

PrFileLit = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/EmbeddingAnalysis/eff_tpc_pr_20202801.root","READ")
KpFileLit = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/EmbeddingAnalysis/Kplus/Efficiency/eff_tpc_kp_Cameron.root","READ")
KmFileLit = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/EmbeddingAnalysis/Kminus/Efficiency/eff_tpc_km_Cameron.root","READ")
PpFileLit = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/EmbeddingAnalysis/Piplus/Efficiency/eff_tpc_pp_Cameron.root","READ")
PmFileLit = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/EmbeddingAnalysis/Piminus/Efficiency/eff_tpc_pm_Cameron.root","READ")
DeFileLit = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/EmbeddingAnalysis/Deuteron/Efficiency/eff_tpc_de_Cameron.root","READ")
TrFileLit = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/EmbeddingAnalysis/Triton/Efficiency/eff_tpc_tr_Cameron.root","READ")




Histogram = PrFile.Get("h2_ratio_pr")

Histogram.SetDirectory(0)

CanvasPr = ROOT.TCanvas("CanvasPr", "", 800, 800)
CanvasPr.cd()

# CanvasPr.SetLogz()

CanvasPr.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

Histogram.SetMaximum(1)

print(Histogram.GetEntries())

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPr.Draw()

Canvasas.append(CanvasPr)



Histogram = PrFileLit.Get("h2_ratio_pr")

Histogram.SetDirectory(0)

Histogram.SetTitle("RC/MC Proton Literature")

CanvasPrLit = ROOT.TCanvas("CanvasPrLit", "", 800, 800)
CanvasPrLit.cd()

# CanvasPrLit.SetLogz()

CanvasPrLit.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

Histogram.SetMaximum(1)

print(Histogram.GetEntries())

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPrLit.Draw()

Canvasas.append(CanvasPrLit)



Histogram = KpFile.Get("h2_ratio_kp")

Histogram.SetDirectory(0)

CanvasKp = ROOT.TCanvas("CanvasKp", "", 800, 800)
CanvasKp.cd()

# CanvasKp.SetLogz()

CanvasKp.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

Histogram.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasKp.Draw()

Canvasas.append(CanvasKp)



Histogram = KpFileLit.Get("h2_ratio_kp")

Histogram.SetDirectory(0)

Histogram.SetTitle("RC/MC K^{+} Literature")

CanvasKpLit = ROOT.TCanvas("CanvasKpLit", "", 800, 800)
CanvasKpLit.cd()

# CanvasKpLit.SetLogz()

CanvasKpLit.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

Histogram.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasKpLit.Draw()

Canvasas.append(CanvasKpLit)



Histogram = KmFile.Get("h2_ratio_km")

Histogram.SetDirectory(0)

CanvasKm = ROOT.TCanvas("CanvasKm", "", 800, 800)
CanvasKm.cd()

# CanvasKm.SetLogz()

CanvasKm.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

Histogram.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasKm.Draw()

Canvasas.append(CanvasKm)



Histogram = KmFileLit.Get("h2_ratio_km")

Histogram.SetDirectory(0)

Histogram.SetTitle("RC/MC K^{-} Literature")

CanvasKmLit = ROOT.TCanvas("CanvasKmLit", "", 800, 800)
CanvasKmLit.cd()

# CanvasKmLit.SetLogz()

CanvasKmLit.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

Histogram.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasKmLit.Draw()

Canvasas.append(CanvasKmLit)



Histogram = PpFile.Get("h2_ratio_pp")

Histogram.SetDirectory(0)

CanvasPp = ROOT.TCanvas("CanvasPp", "", 800, 800)
CanvasPp.cd()

# CanvasPp.SetLogz()

CanvasPp.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

Histogram.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPp.Draw()

Canvasas.append(CanvasPp)



Histogram = PpFileLit.Get("h2_ratio_pp")

Histogram.SetDirectory(0)

Histogram.SetTitle("RC/MC #pi^{+} Literature")

CanvasPpLit = ROOT.TCanvas("CanvasPpLit", "", 800, 800)
CanvasPpLit.cd()

# CanvasPpLit.SetLogz()

CanvasPpLit.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

Histogram.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPpLit.Draw()

Canvasas.append(CanvasPpLit)




Histogram = PmFile.Get("h2_ratio_pm")

Histogram.SetDirectory(0)

CanvasPm = ROOT.TCanvas("CanvasPm", "", 800, 800)
CanvasPm.cd()

# CanvasPm.SetLogz()

CanvasPm.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

Histogram.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPm.Draw()

Canvasas.append(CanvasPm)



Histogram = PmFileLit.Get("h2_ratio_pm")

Histogram.SetDirectory(0)

Histogram.SetTitle("RC/MC #pi^{-} Literature")

CanvasPmLit = ROOT.TCanvas("CanvasPmLit", "", 800, 800)
CanvasPmLit.cd()

# CanvasPmLit.SetLogz()

CanvasPmLit.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

Histogram.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasPmLit.Draw()

Canvasas.append(CanvasPmLit)



Histogram = DeFile.Get("h2_ratio_de")

Histogram.SetDirectory(0)

CanvasDe = ROOT.TCanvas("CanvasDe", "", 800, 800)
CanvasDe.cd()

# CanvasDe.SetLogz()

CanvasDe.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

Histogram.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasDe.Draw()

Canvasas.append(CanvasDe)



Histogram = DeFileLit.Get("h2_ratio_de")

Histogram.SetDirectory(0)

Histogram.SetTitle("RC/MC Deuteron Literature")

CanvasDeLit = ROOT.TCanvas("CanvasDeLit", "", 800, 800)
CanvasDeLit.cd()

# CanvasDeLit.SetLogz()

CanvasDeLit.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

Histogram.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasDeLit.Draw()

Canvasas.append(CanvasDeLit)



Histogram = TrFile.Get("h2_ratio_tr")

Histogram.SetDirectory(0)

CanvasTr = ROOT.TCanvas("CanvasTr", "", 800, 800)
CanvasTr.cd()

# CanvasTr.SetLogz()

CanvasTr.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

Histogram.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasTr.Draw()

Canvasas.append(CanvasTr)



Histogram = TrFileLit.Get("h2_ratio_tr")

Histogram.SetDirectory(0)

Histogram.SetTitle("RC/MC Triton Literature")

CanvasTrLit = ROOT.TCanvas("CanvasTrLit", "", 800, 800)
CanvasTrLit.cd()

# CanvasTrLit.SetLogz()

CanvasTrLit.SetRightMargin(0.15)

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

Histogram.SetMaximum(1)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasTrLit.Draw()

Canvasas.append(CanvasTrLit)



PrFile.Close()
KpFile.Close()
KmFile.Close()
PpFile.Close()
PmFile.Close()
DeFile.Close()
TrFile.Close()

PrFileLit.Close()
KpFileLit.Close()
KmFileLit.Close()
PpFileLit.Close()
PmFileLit.Close()
DeFileLit.Close()
TrFileLit.Close()




for index in range(0, len(Canvasas)):
    if len(Canvasas) == 1:
        Canvasas[index].SaveAs('TPCEfficiencies.pdf)')
        break
    
    if index == 0:
        print("Opening PDF")
        Canvasas[index].SaveAs('TPCEfficiencies.pdf(')
    
    elif index == len(Canvasas) - 1:
        print("Closing PDF")
        Canvasas[index].SaveAs('TPCEfficiencies.pdf)')
    
    else:
        Canvasas[index].SaveAs('TPCEfficiencies.pdf')
