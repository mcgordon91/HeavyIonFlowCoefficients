import ROOT
import sys
from math import sqrt
from array import array

nPsi = 1
nV = 3

#HistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/HistogramThirdPass" + sys.argv[1] + ".root", "UPDATE")
HistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/HistogramThirdPassNormal.root", "READ")

ResolutionFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/R_" + str(nV) + str(nPsi) + "_" + sys.argv[1] + ".root", "RECREATE")

HistoD51 = HistogramFile.Get("DataResolutionTopLeftTerm")
HistoD52 = HistogramFile.Get("DataResolutionTopRightTerm")
HistoD53 = HistogramFile.Get("DataResolutionBottomTerm")

HistoD54 = ROOT.TH1F("DataResolution", "Resolution (R" + str(nV) + "1) (Data); Centrality; Resolution", 12, 0, 12)
# NumberOfBinsDandT = 7;
# BinEdgesDandT = [0.0, 1.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0]
# HistoD54 = ROOT.TH1F("DataResolution", "Resolution (R" + str(nV) + "1) (Data); Centrality; Resolution", NumberOfBinsDandT, array('d', BinEdgesDandT))
HistoD54.Sumw2()




CentralityXLabels = ["0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60"]

Rnm = 0
RnmError = 0

for index in range(1, HistoD51.GetNbinsX() + 1):
    #HistoD54.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])
        
    TopLeftTerm = HistoD51.GetBinContent(index)
    TopRightTerm = HistoD52.GetBinContent(index)
    BottomTerm = HistoD53.GetBinContent(index)
    
    if((TopLeftTerm * TopRightTerm)/BottomTerm <= 0):
        continue
    
    Rnm = sqrt((TopLeftTerm * TopRightTerm)/BottomTerm)

    TopLeftTermError = HistoD51.GetBinError(index)
    TopRightTermError = HistoD52.GetBinError(index)
    BottomTermError = HistoD53.GetBinError(index)

    RnmError = Rnm*sqrt(pow((TopLeftTermError/(2*TopLeftTerm)),2) + pow((TopRightTermError/(2*TopRightTerm)),2) + pow((BottomTermError/(2*BottomTerm)),2))

    HistoD54.SetBinContent(index, Rnm)
    HistoD54.SetBinError(index, RnmError)


    

# HistoD54.SetDirectory(0)

# CanvasD54 = ROOT.TCanvas("CanvasD54", "", 800, 800)
# CanvasD54.cd()

# HistoD54.SetStats(0)

# HistoD54.Draw("P E1")

# CanvasD54.Draw()




# CanvasD54.SaveAs('ResolutionPlot.pdf)')

# sys.exit(0)








HistoD54.SetDirectory(0)

ResolutionFile.cd()

HistoD54.Write()

HistogramFile.Close()
ResolutionFile.Close()

print("DONE")