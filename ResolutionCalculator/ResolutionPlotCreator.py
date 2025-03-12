import ROOT
import sys
import numpy as np
from math import sqrt
from array import array


def Resolution11(x_val):
    chi = x_val[0]
    arg = chi*chi/4.0
    norm = ROOT.TMath.Sqrt(ROOT.TMath.Pi()/2.0)/2.0

    y = norm*chi*ROOT.TMath.Exp(-1.0*arg)*(ROOT.TMath.BesselI0(arg)+ROOT.TMath.BesselI1(arg))

    return y

def Resolution21(x_val):
    chi = x_val[0]
    arg = chi*chi/4.0
    norm = ROOT.TMath.Sqrt(ROOT.TMath.Pi())/(2.0*ROOT.TMath.Sqrt(2.0))
    besselOneHalf = ROOT.TMath.Sqrt(2.0*arg/ROOT.TMath.Pi()) * ROOT.TMath.SinH(arg)/arg
    besselThreeHalf = ROOT.TMath.Sqrt(2.0*arg/ROOT.TMath.Pi()) * (ROOT.TMath.CosH(arg)/arg - ROOT.TMath.SinH(arg)/(arg*arg) )

    y = norm * chi * ROOT.TMath.Exp(-1.0*arg) * (besselOneHalf + besselThreeHalf)

    return y

def Resolution21Err(x_val, x_err):
    chi = x_val
    chierr = x_err
    arg = chi*chi/4.0

    yerr = ROOT.TMath.Abs(-1*2*pow(2,3/4)*ROOT.TMath.Exp(-1.0*arg)*((pow(chi,2)*ROOT.TMath.CosH(arg)-((pow(chi,2)+4)*ROOT.TMath.SinH(arg)))/pow(chi,3))) * chierr

    return yerr

def Resolution31(x_val):
    chi = x_val[0]
    arg = chi*chi/4.0
    norm = ROOT.TMath.Sqrt(ROOT.TMath.Pi())/(2.0*ROOT.TMath.Sqrt(2.0))

    y = norm * chi * ROOT.TMath.Exp(-1.0*arg) * (ROOT.TMath.BesselI(1, arg) + ROOT.TMath.BesselI(2, arg))

    return y

def Resolution31Err(x_val, x_err):
    chi = x_val
    chierr = x_err
    arg = chi*chi/4.0
    norm = ROOT.TMath.Sqrt(ROOT.TMath.Pi())/(2.0*ROOT.TMath.Sqrt(2.0))

    yerr = ROOT.TMath.Abs(ROOT.TMath.Sqrt(ROOT.TMath.Pi())*ROOT.TMath.Exp(-1.0*arg)*(pow(chi,2)*ROOT.TMath.BesselI(0,arg)-pow(chi,2)*ROOT.TMath.BesselI(2,arg)+pow(chi,2)*ROOT.TMath.BesselI(3,arg)-(pow(chi,2)-4)*ROOT.TMath.BesselI(1,arg)+4*ROOT.TMath.BesselI(2,arg)/pow(2,11/4))) * chierr

    return yerr

def Resolution41(x_val):
    chi = x_val[0]
    arg = chi*chi/4.0
    norm = ROOT.TMath.Sqrt(ROOT.TMath.Pi())/(2.0*ROOT.TMath.Sqrt(2.0))
    besselThreeHalf = ROOT.TMath.Sqrt(2.0*arg/ROOT.TMath.Pi()) * (ROOT.TMath.CosH(arg)/arg - ROOT.TMath.SinH(arg)/(arg*arg) )
    besselFiveHalf = ROOT.TMath.Sqrt(1.0/(2.0*ROOT.TMath.Pi()*arg)) * (((6.0/pow(arg,2)) + 2.0) * ROOT.TMath.SinH(arg) - 6.0 * ROOT.TMath.CosH(arg)/(arg) )

    y = norm * chi * ROOT.TMath.Exp(-1.0*arg) * (besselThreeHalf + besselFiveHalf)

    return y

def Resolution41Err(x_val, x_err):
    chi = x_val
    chierr = x_err
    arg = chi*chi/4.0
    norm = ROOT.TMath.Sqrt(ROOT.TMath.Pi())/(2.0*ROOT.TMath.Sqrt(2.0))

    yerr = ROOT.TMath.Abs(4*pow(2,3/4)*ROOT.TMath.Exp(-1.0*arg)*(((pow(chi,4)+12*pow(chi,2))*ROOT.TMath.CosH(arg)-((pow(chi,4)+4*pow(chi,2)+48)*ROOT.TMath.SinH(arg)))/pow(chi,9/2))) * chierr

    return yerr

def Resolution51(x_val):
    chi = x_val[0]
    arg = chi*chi/4.0
    norm = ROOT.TMath.Sqrt(ROOT.TMath.Pi())/(2.0*ROOT.TMath.Sqrt(2.0))

    y = norm * chi * ROOT.TMath.Exp(-1.0*arg) * (ROOT.TMath.BesselI(2, arg) + ROOT.TMath.BesselI(3, arg))

    return y
                          
def Resolution51Err(x_val, x_err):
    chi = x_val
    chierr = x_err
    arg = chi*chi/4.0
    norm = ROOT.TMath.Sqrt(ROOT.TMath.Pi())/(2.0*ROOT.TMath.Sqrt(2.0))

    yerr = ROOT.TMath.Abs(ROOT.TMath.Sqrt(ROOT.TMath.Pi())*ROOT.TMath.Exp(-1.0*arg)*(pow(chi,2)*ROOT.TMath.BesselI(1,arg)-pow(chi,2)*ROOT.TMath.BesselI(3,arg)+pow(chi,2)*ROOT.TMath.BesselI(4,arg)-(pow(chi,2)-4)*ROOT.TMath.BesselI(2,arg)+4*ROOT.TMath.BesselI(3,arg)/pow(2,11/4))) * chierr

    return yerr


HistogramFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/HistogramThirdPass" + sys.argv[1] + ".root", "UPDATE")

ResolutionFile1 = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V1Histograms/R_11_" + sys.argv[1] + ".root", "RECREATE")
ResolutionFile2 = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V2Histograms/R_21_" + sys.argv[1] + ".root", "RECREATE")
ResolutionFile3 = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V3Histograms/R_31_" + sys.argv[1] + ".root", "RECREATE")
ResolutionFile4 = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V4Histograms/R_41_" + sys.argv[1] + ".root", "RECREATE")
ResolutionFile5 = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V5Histograms/R_51_" + sys.argv[1] + ".root", "RECREATE")

HistoD51 = HistogramFile.Get("DataResolutionTopLeftTerm")
HistoD52 = HistogramFile.Get("DataResolutionTopRightTerm")
HistoD53 = HistogramFile.Get("DataResolutionBottomTerm")




HistoD54A = ROOT.TH1F("DataResolutionR11", "R_{11}; Centrality; Resolution", 12, 0, 12)
HistoD54A.Sumw2()

HistoD54B = ROOT.TH1F("DataResolutionR21", "R_{21}; Centrality; Resolution", 12, 0, 12)
HistoD54B.Sumw2()

HistoD54C = ROOT.TH1F("DataResolutionR31", "R_{31}; Centrality; Resolution", 12, 0, 12)
HistoD54C.Sumw2()

HistoD54D = ROOT.TH1F("DataResolutionR41", "R_{41}; Centrality; Resolution", 12, 0, 12)
HistoD54D.Sumw2()

HistoD54E = ROOT.TH1F("DataResolutionR51", "R_{51}; Centrality; Resolution", 12, 0, 12)
HistoD54E.Sumw2()




CentralityXLabels = ["0-5", "5-10", "10-15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "45-50", "50-55", "55-60", "60-65", "65-70", "70-75", "75-80"]

for index in range(1, HistoD51.GetNbinsX() + 1):
    HistoD54A.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])
    HistoD54B.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])
    HistoD54C.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])
    HistoD54D.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])
    HistoD54E.GetXaxis().SetBinLabel(index, CentralityXLabels[index - 1])
        
    TopLeftTerm = HistoD51.GetBinContent(index)
    TopRightTerm = HistoD52.GetBinContent(index)
    BottomTerm = HistoD53.GetBinContent(index)
    
    if((TopLeftTerm * TopRightTerm)/BottomTerm <= 0):
        continue
    
    R11 = sqrt((TopLeftTerm * TopRightTerm)/BottomTerm)

    TopLeftTermError = HistoD51.GetBinError(index)
    TopRightTermError = HistoD52.GetBinError(index)
    BottomTermError = HistoD53.GetBinError(index)

    R11Error = R11*sqrt(pow((TopLeftTermError/(2*TopLeftTerm)),2) + pow((TopRightTermError/(2*TopRightTerm)),2) + pow((BottomTermError/(2*BottomTerm)),2))

    HistoD54A.SetBinContent(index, R11)
    HistoD54A.SetBinError(index, R11Error)
    
    R11Bessel = ROOT.TF1("R11Bessel",Resolution11,0,10,0)
    chi1 = R11Bessel.GetX(R11)
    chi1err = R11Bessel.GetX(R11Error)

    R21Bessel = ROOT.TF1("R21Bessel",Resolution21,0,10,0)
    R21 = R21Bessel.Eval(chi1)
    R21Err = Resolution21Err(chi1, chi1err)
    
    HistoD54B.SetBinContent(index, R21)
    HistoD54B.SetBinError(index, R21Err)
    
    R31Bessel = ROOT.TF1("R31Bessel",Resolution31,0,10,0)
    R31 = R31Bessel.Eval(chi1)
    R31Err = Resolution31Err(chi1, chi1err)
    
    HistoD54C.SetBinContent(index, R31)
    HistoD54C.SetBinError(index, R31Err)
    
    R41Bessel = ROOT.TF1("R41Bessel",Resolution41,0,10,0)
    R41 = R41Bessel.Eval(chi1)
    R41Err = Resolution41Err(chi1, chi1err)
    
    HistoD54D.SetBinContent(index, R41)
    HistoD54D.SetBinError(index, R41Err)
    
    R51Bessel = ROOT.TF1("R51Bessel",Resolution51,0,10,0)
    R51 = R51Bessel.Eval(chi1)
    R51Err = Resolution51Err(chi1, chi1err)
    
    HistoD54E.SetBinContent(index, R51)
    HistoD54E.SetBinError(index, R51Err)



HistoD54A.SetDirectory(0)
HistoD54B.SetDirectory(0)
HistoD54C.SetDirectory(0)
HistoD54D.SetDirectory(0)
HistoD54E.SetDirectory(0)



ResolutionFile1.cd()

HistoD54A.Write()

ResolutionFile1.Close()



ResolutionFile2.cd()

HistoD54B.Write()

ResolutionFile2.Close()



ResolutionFile3.cd()

HistoD54C.Write()

ResolutionFile3.Close()



ResolutionFile4.cd()

HistoD54D.Write()

ResolutionFile4.Close()



ResolutionFile5.cd()

HistoD54E.Write()

ResolutionFile5.Close()


HistogramFile.Close()

print("DONE")