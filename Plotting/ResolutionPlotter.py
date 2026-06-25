import ROOT
import os
import sys

Canvasas = []

# ResolutionFileR11 = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/R_11_Normal.root","READ")
# ResolutionFileR21 = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V2Histograms/R_21_Normal.root","READ")
# ResolutionFileR31 = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/R_31_Normal.root","READ")
# ResolutionFileR41 = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V4Histograms/R_41_Normal.root","READ")
# ResolutionFileR51 = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V5Histograms/R_51_Normal.root","READ")

HistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V2Histograms/HistogramThirdPassNormal.root","READ")


# Histogram = ResolutionFileR11.Get("DataResolutionR11")

# Histogram.SetDirectory(0)

# Histogram.GetYaxis().SetTitleOffset(1.5)

# CanvasR11 = ROOT.TCanvas("CanvasR11", "", 800, 800)
# CanvasR11.cd()

# Histogram.SetStats(0)

# Histogram.SetLineWidth(10)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(3)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.Draw("PE 1 X0")

# CanvasR11.Draw()

# Canvasas.append(CanvasR11)




# Histogram = ResolutionFileR21.Get("DataResolutionR21")

# Histogram.SetDirectory(0)

# Histogram.GetYaxis().SetTitleOffset(1.5)

# CanvasR21 = ROOT.TCanvas("CanvasR21", "", 800, 800)
# CanvasR21.cd()

# Histogram.SetStats(0)

# Histogram.SetLineWidth(10)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(3)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.Draw("PE 1 X0")

# CanvasR21.Draw()

# Canvasas.append(CanvasR21)



# Histogram = ResolutionFileR41.Get("DataResolutionR31")

# Histogram.SetDirectory(0)

# Histogram.GetYaxis().SetTitleOffset(1.5)

# CanvasR31 = ROOT.TCanvas("CanvasR31", "", 800, 800)
# CanvasR31.cd()

# Histogram.SetStats(0)

# Histogram.SetLineWidth(10)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(3)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.Draw("PE 1 X0")

# CanvasR31.Draw()

# Canvasas.append(CanvasR31)



# Histogram = ResolutionFileR41.Get("DataResolutionR41")

# Histogram.SetDirectory(0)

# Histogram.GetYaxis().SetTitleOffset(1.5)

# CanvasR41 = ROOT.TCanvas("CanvasR41", "", 800, 800)
# CanvasR41.cd()

# Histogram.SetStats(0)

# Histogram.SetLineWidth(10)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(3)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.Draw("PE 1 X0")

# CanvasR41.Draw()

# Canvasas.append(CanvasR41)



# Histogram = ResolutionFileR51.Get("DataResolutionR51")

# Histogram.SetDirectory(0)

# Histogram.GetYaxis().SetTitleOffset(1.5)

# CanvasR51 = ROOT.TCanvas("CanvasR51", "", 800, 800)
# CanvasR51.cd()

# Histogram.SetStats(0)

# Histogram.SetLineWidth(10)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(3)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.Draw("PE 1 X0")

# CanvasR51.Draw()

# Canvasas.append(CanvasR51)



Histogram = HistogramFile.Get("DataResolutionTopLeftTerm")

Histogram.SetDirectory(0)

Histogram.GetYaxis().SetTitleOffset(1.5)

CanvasTLT = ROOT.TCanvas("CanvasTLT", "", 800, 800)
CanvasTLT.cd()

Histogram.SetTitle('<cos[2*(#Psi_{EPD-A} - #Psi_{EPD-B})]> vs Centrality')
Histogram.GetXaxis().SetTitle("Centrality")
Histogram.GetYaxis().SetTitle("<cos[2*(#Psi_{EPD-A} - #Psi_{EPD-B})]>")

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.Draw("PE 1 X0")

CanvasTLT.Draw()

Canvasas.append(CanvasTLT)



Histogram = HistogramFile.Get("DataResolutionTopRightTerm")

Histogram.SetDirectory(0)

Histogram.GetYaxis().SetTitleOffset(1.5)

CanvasTRT = ROOT.TCanvas("CanvasTRT", "", 800, 800)
CanvasTRT.cd()

Histogram.SetTitle('<cos[2*(#Psi_{EPD-A} - #Psi_{TPC-B})]> vs Centrality')
Histogram.GetXaxis().SetTitle("Centrality")
Histogram.GetYaxis().SetTitle("<cos[2*(#Psi_{EPD-A} - #Psi_{TPC-B})]>")

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.Draw("PE 1 X0")

CanvasTRT.Draw()

Canvasas.append(CanvasTRT)




Histogram = HistogramFile.Get("DataResolutionBottomTerm")

Histogram.SetDirectory(0)

Histogram.GetYaxis().SetTitleOffset(1.5)

CanvasB = ROOT.TCanvas("CanvasB", "", 800, 800)
CanvasB.cd()

Histogram.SetTitle('<cos[2*(#Psi_{EPD-A} - #Psi_{TPC-B})]> vs Centrality')
Histogram.GetXaxis().SetTitle("Centrality")
Histogram.GetYaxis().SetTitle("<cos[2*(#Psi_{EPD-B} - #Psi_{TPC-B})]>")

Histogram.SetStats(0)

Histogram.SetLineWidth(3)
Histogram.SetLineColor(ROOT.kBlue)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.Draw("PE 1 X0")

CanvasB.Draw()

Canvasas.append(CanvasB)




# ResolutionFileR11.Close()
# ResolutionFileR21.Close()
# ResolutionFileR31.Close()
# ResolutionFileR41.Close()
# ResolutionFileR51.Close()

HistogramFile.Close()



for index in range(0, len(Canvasas)):
    if len(Canvasas) == 1:
        Canvasas[index].SaveAs('Resolutions.pdf)')
        break
    
    if index == 0:
        print("Opening PDF")
        Canvasas[index].SaveAs('Resolutions.pdf(')
    
    elif index == len(Canvasas) - 1:
        print("Closing PDF")
        Canvasas[index].SaveAs('Resolutions.pdf)')
    
    else:
        Canvasas[index].SaveAs('Resolutions.pdf')
