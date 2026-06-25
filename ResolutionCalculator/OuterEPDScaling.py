import ROOT

CentralityXLabels = ["0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60"]

HistogramOuterEPDScaled = ROOT.TH1F("DataResolution", " ; ; ", 12, 0, 12)

HistogramNormalFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/R_31_Normal.root","READ")
HistogramOuterEPDUnscaledFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/R_31_OuterEPDHighUnscaled.root","READ")
CorrelationProfileFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/HistogramThirdPassNormal.root","READ")

HistogramNormal = HistogramNormalFile.Get("DataResolution")
HistogramOuterEPDUnscaled = HistogramOuterEPDUnscaledFile.Get("DataResolution")
CorrelationProfile = CorrelationProfileFile.Get("DataResolutionBottomTerm")

HistogramNormalAverage = 0.0
HistogramOuterEPDUnscaledAverage = 0.0
Entries = 0.0

for index in range(5,10):
    HistogramNormalAverage += CorrelationProfile.GetBinEntries(index) * HistogramNormal.GetBinContent(index)
    HistogramOuterEPDUnscaledAverage += CorrelationProfile.GetBinEntries(index) * HistogramOuterEPDUnscaled.GetBinContent(index)
    Entries += CorrelationProfile.GetBinEntries(index)

HistogramNormalAverage /= Entries
HistogramOuterEPDUnscaledAverage /= Entries

HistogramNormal.Scale(HistogramOuterEPDUnscaledAverage / HistogramNormalAverage)

for index in range(1, HistogramOuterEPDScaled.GetNbinsX() + 1):
    HistogramOuterEPDScaled.SetBinContent(index, HistogramNormal.GetBinContent(index))
    HistogramOuterEPDScaled.SetBinError(index, HistogramNormal.GetBinError(index))
    HistogramOuterEPDScaled.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])

HistogramNormalFile.Close()
HistogramOuterEPDUnscaledFile.Close()
CorrelationProfileFile.Close()

MyResolutionPlotFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/R_31_OuterEPDHigh.root","RECREATE")
MyResolutionPlotFile.cd()
HistogramOuterEPDScaled.Write()
MyResolutionPlotFile.Close()

print("DONE")
