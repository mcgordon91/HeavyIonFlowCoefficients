import ROOT
import sys
from math import sqrt

nV = "1"

#HistogramFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/HistogramThirdPassTest.root", "UPDATE")
HistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + nV + "Histograms/HistogramThirdPass.root", "UPDATE")

HistoD51 = HistogramFile.Get("DataResolutionTopLeftTerm")
HistoD52 = HistogramFile.Get("DataResolutionTopRightTerm")
HistoD53 = HistogramFile.Get("DataResolutionBottomTerm")

HistoD54 = ROOT.TH1F("DataResolution", "Resolution (R" + str(nV) + "1) (Data); Centrality; Resolution", 12, 0, 12)
HistoD54.Sumw2()




CentralityXLabels = ["0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60"]

R11 = 0
R11Error = 0

for index in range(1, HistoD51.GetNbinsX() + 1):
    TopLeftTerm = HistoD51.GetBinContent(index)
    TopRightTerm = HistoD52.GetBinContent(index)
    BottomTerm = HistoD53.GetBinContent(index)
    
    if((TopLeftTerm * TopRightTerm)/BottomTerm <= 0):
        continue
    
    R11 = sqrt((TopLeftTerm * TopRightTerm)/BottomTerm)

    TopLeftTermError = HistoD51.GetBinError(index)
    TopRightTermError = HistoD52.GetBinError(index)
    BottomTermError = HistoD53.GetBinError(index)
    
    R11Error = R11*sqrt(pow((TopLeftTermError/TopLeftTerm),2) + pow((TopRightTermError/TopRightTerm),2) + pow((BottomTermError/BottomTerm),2))

    HistoD54.SetBinContent(index, R11)
    HistoD54.SetBinError(index, R11Error)

    HistoD54.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])
    
    
    
    

# HistoD54.SetDirectory(0)

# CanvasD54 = ROOT.TCanvas("CanvasD54", "", 800, 800)
# CanvasD54.cd()

# HistoD54.SetStats(0)

# HistoD54.Draw("P E1")

# CanvasD54.Draw()




# CanvasD54.SaveAs('ResolutionPlot.pdf)')

# sys.exit(0)








HistoD54.SetDirectory(0)

HistogramFile.cd()


HistoD54.Write()

HistogramFile.Close()

print("DONE")