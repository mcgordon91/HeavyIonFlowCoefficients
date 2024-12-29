#!/usr/bin/env python
# coding: utf-8




# This box draws the histograms
import ROOT
from math import sin, sqrt, log, atanh, exp

# List of canvasas
Canvasas = []

nV = 1
Date = "11-12-24"

# Open the output Root file
ResolutionRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/R_" + str(nV) + "1_Normal.root","READ")
HistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + Date + "-V" + str(nV) + "-HistogramNormal.root","READ")
# HistogramRootFile = ROOT.TFile.Open("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + Date + "-V" + str(nV) + "-HistogramNormal.root","READ")
#SystematicErrorRootFile = ROOT.TFile.Open("/star/u/mcgordon/VnFromEPD/systematicErrors.root","READ")



# Histogram = HistogramRootFile.Get("pVx")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvaspVx = ROOT.TCanvas("CanvaspVx", "", 800, 800)
# # Change the scope to be within the file
# CanvaspVx.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.SetAxisRange(-0.65, -0.25, "Y")

# Sum = 0.0
# Count = 0.0
# StdSum = 0.0

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         Sum = Sum + Histogram.GetBinContent(index)
#         Count = Count + 1
        
# Mean = Sum / Count

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         StdSum = StdSum + pow(Histogram.GetBinContent(index) - Mean, 2)
    
# StdDev = sqrt(StdSum / Count)

# print("pVx")    
# print("Mean:", Mean)
# print("Standard Deviation:", StdDev)

# print(Mean - 5 * StdDev, Mean + 5 * StdDev)

# for index in range(1, Histogram.GetNbinsX()):
#     if((Histogram.GetBinContent(index) > (Mean + 5 * StdDev)) or (Histogram.GetBinContent(index) < (Mean - 5 * StdDev))):
#         if(Histogram.GetBinContent(index) != 0):
#             print(index, Histogram.GetBinContent(index))

# Histogram.Draw("P* E1 X0")

# # Draw the histogram
# CanvaspVx.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvaspVx)




# Histogram = HistogramRootFile.Get("pVy")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvaspVy = ROOT.TCanvas("CanvaspVy", "", 800, 800)
# # Change the scope to be within the file
# CanvaspVy.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.SetAxisRange(-2.1, -1.8, "Y")

# Sum = 0.0
# Count = 0.0
# StdSum = 0.0

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         Sum = Sum + Histogram.GetBinContent(index)
#         Count = Count + 1
        
# Mean = Sum / Count

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         StdSum = StdSum + pow(Histogram.GetBinContent(index) - Mean, 2)
    
# StdDev = sqrt(StdSum / Count)

# print("pVy")    
# print("Mean:", Mean)
# print("Standard Deviation:", StdDev)


# print(Mean - 5 * StdDev, Mean + 5 * StdDev)

# for index in range(1, Histogram.GetNbinsX()):
#     if((Histogram.GetBinContent(index) > (Mean + 5 * StdDev)) or (Histogram.GetBinContent(index) < (Mean - 5 * StdDev))):
#         if(Histogram.GetBinContent(index) != 0):
#             print(index, Histogram.GetBinContent(index))

# Histogram.Draw("P* E1 X0")

# # Draw the histogram
# CanvaspVy.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvaspVy)



# Histogram = HistogramRootFile.Get("pVz")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvaspVz = ROOT.TCanvas("CanvaspVz", "", 800, 800)
# # Change the scope to be within the file
# CanvaspVz.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.SetAxisRange(200.0, 200.3, "Y")

# Sum = 0.0
# Count = 0.0
# StdSum = 0.0

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         Sum = Sum + Histogram.GetBinContent(index)
#         Count = Count + 1
        
# Mean = Sum / Count

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         StdSum = StdSum + pow(Histogram.GetBinContent(index) - Mean, 2)
    
# StdDev = sqrt(StdSum / Count)


# print("pVz")
# print("Mean:", Mean)
# print("Standard Deviation:", StdDev)

# print(Mean - 5 * StdDev, Mean + 5 * StdDev)

# for index in range(1, Histogram.GetNbinsX()):
#     if((Histogram.GetBinContent(index) > (Mean + 5 * StdDev)) or (Histogram.GetBinContent(index) < (Mean - 5 * StdDev))):
#         if(Histogram.GetBinContent(index) != 0):
#             print(index, Histogram.GetBinContent(index))

# Histogram.Draw("P* E1 X0")

# # Draw the histogram
# CanvaspVz.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvaspVz)



# Histogram = HistogramRootFile.Get("pPt")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvaspPt = ROOT.TCanvas("CanvaspPt", "", 800, 800)
# # Change the scope to be within the file
# CanvaspPt.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.SetAxisRange(0.45, 0.65, "Y")

# Sum = 0.0
# Count = 0.0
# StdSum = 0.0

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         Sum = Sum + Histogram.GetBinContent(index)
#         Count = Count + 1
        
# Mean = Sum / Count

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         StdSum = StdSum + pow(Histogram.GetBinContent(index) - Mean, 2)
    
# StdDev = sqrt(StdSum / Count)


# print("pPt")
# print("Mean:", Mean)
# print("Standard Deviation:", StdDev)

# print(Mean - 5 * StdDev, Mean + 5 * StdDev)

# for index in range(1, Histogram.GetNbinsX()):
#     if((Histogram.GetBinContent(index) > (Mean + 5 * StdDev)) or (Histogram.GetBinContent(index) < (Mean - 5 * StdDev))):
#         if(Histogram.GetBinContent(index) != 0):
#             print(index, Histogram.GetBinContent(index))

# Histogram.Draw("P* E1 X0")

# # Draw the histogram
# CanvaspPt.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvaspPt)




# Histogram = HistogramRootFile.Get("pEta")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvaspEta = ROOT.TCanvas("CanvaspEta", "", 800, 800)
# # Change the scope to be within the file
# CanvaspEta.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.SetAxisRange(-1.45, -1.00, "Y")

# Sum = 0.0
# Count = 0.0
# StdSum = 0.0

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         Sum = Sum + Histogram.GetBinContent(index)
#         Count = Count + 1
        
# Mean = Sum / Count

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         StdSum = StdSum + pow(Histogram.GetBinContent(index) - Mean, 2)
    
# StdDev = sqrt(StdSum / Count)

# print("pPEta")    
# print("Mean:", Mean)
# print("Standard Deviation:", StdDev)

# print(Mean - 5 * StdDev, Mean + 5 * StdDev)

# for index in range(1, Histogram.GetNbinsX()):
#     if((Histogram.GetBinContent(index) > (Mean + 5 * StdDev)) or (Histogram.GetBinContent(index) < (Mean - 5 * StdDev))):
#         if(Histogram.GetBinContent(index) != 0):
#             print(index, Histogram.GetBinContent(index))

# Histogram.Draw("P* E1 X0")

# # Draw the histogram
# CanvaspEta.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvaspEta)





# Histogram = HistogramRootFile.Get("pQxEPDA")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvaspQxEPDA = ROOT.TCanvas("CanvaspQxEPDA", "", 800, 800)
# # Change the scope to be within the file
# CanvaspQxEPDA.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.SetAxisRange(-1.15, -0.20, "Y")

# Sum = 0.0
# Count = 0.0
# StdSum = 0.0

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         Sum = Sum + Histogram.GetBinContent(index)
#         Count = Count + 1
        
# Mean = Sum / Count

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         StdSum = StdSum + pow(Histogram.GetBinContent(index) - Mean, 2)
    
# StdDev = sqrt(StdSum / Count)


# print("pQxEPDA")
# print("Mean:", Mean)
# print("Standard Deviation:", StdDev)

# print(Mean - 5 * StdDev, Mean + 5 * StdDev)

# for index in range(1, Histogram.GetNbinsX()):
#     if((Histogram.GetBinContent(index) > (Mean + 5 * StdDev)) or (Histogram.GetBinContent(index) < (Mean - 5 * StdDev))):
#         if(Histogram.GetBinContent(index) != 0):
#             print(index, Histogram.GetBinContent(index))

# Histogram.Draw("P* E1 X0")

# # Draw the histogram
# CanvaspQxEPDA.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvaspQxEPDA)






# Histogram = HistogramRootFile.Get("pQyEPDA")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvaspQyEPDA = ROOT.TCanvas("CanvaspQyEPDA", "", 800, 800)
# # Change the scope to be within the file
# CanvaspQyEPDA.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.SetAxisRange(0.40, 3.50, "Y")

# Sum = 0.0
# Count = 0.0
# StdSum = 0.0

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         Sum = Sum + Histogram.GetBinContent(index)
#         Count = Count + 1
        
# Mean = Sum / Count

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         StdSum = StdSum + pow(Histogram.GetBinContent(index) - Mean, 2)
    
# StdDev = sqrt(StdSum / Count)


# print("pQyEPDA")
# print("Mean:", Mean)
# print("Standard Deviation:", StdDev)

# print(Mean - 5 * StdDev, Mean + 5 * StdDev)

# for index in range(1, Histogram.GetNbinsX()):
#     if((Histogram.GetBinContent(index) > (Mean + 5 * StdDev)) or (Histogram.GetBinContent(index) < (Mean - 5 * StdDev))):
#         if(Histogram.GetBinContent(index) != 0):
#             print(index, Histogram.GetBinContent(index))

# Histogram.Draw("P* E1 X0")

# # Draw the histogram
# CanvaspQyEPDA.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvaspQyEPDA)






# Histogram = HistogramRootFile.Get("pQxEPDB")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvaspQxEPDB = ROOT.TCanvas("CanvaspQxEPDB", "", 800, 800)
# # Change the scope to be within the file
# CanvaspQxEPDB.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.SetAxisRange(-0.5, 0.05, "Y")

# Sum = 0.0
# Count = 0.0
# StdSum = 0.0

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         Sum = Sum + Histogram.GetBinContent(index)
#         Count = Count + 1
        
# Mean = Sum / Count

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         StdSum = StdSum + pow(Histogram.GetBinContent(index) - Mean, 2)
    
# StdDev = sqrt(StdSum / Count)


# print("pQxEPDB")
# print("Mean:", Mean)
# print("Standard Deviation:", StdDev)

# print(Mean - 5 * StdDev, Mean + 5 * StdDev)

# for index in range(1, Histogram.GetNbinsX()):
#     if((Histogram.GetBinContent(index) > (Mean + 5 * StdDev)) or (Histogram.GetBinContent(index) < (Mean - 5 * StdDev))):
#         if(Histogram.GetBinContent(index) != 0):
#             print(index, Histogram.GetBinContent(index))

# Histogram.Draw("P* E1 X0")

# # Draw the histogram
# CanvaspQxEPDB.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvaspQxEPDB)






# Histogram = HistogramRootFile.Get("pQyEPDB")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvaspQyEPDB = ROOT.TCanvas("CanvaspQyEPDB", "", 800, 800)
# # Change the scope to be within the file
# CanvaspQyEPDB.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.SetAxisRange(-0.2, 0.45, "Y")

# Sum = 0.0
# Count = 0.0
# StdSum = 0.0

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         Sum = Sum + Histogram.GetBinContent(index)
#         Count = Count + 1
        
# Mean = Sum / Count

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         StdSum = StdSum + pow(Histogram.GetBinContent(index) - Mean, 2)
    
# StdDev = sqrt(StdSum / Count)


# print("pQyEPDB")
# print("Mean:", Mean)
# print("Standard Deviation:", StdDev)

# print(Mean - 5 * StdDev, Mean + 5 * StdDev)

# for index in range(1, Histogram.GetNbinsX()):
#     if((Histogram.GetBinContent(index) > (Mean + 5 * StdDev)) or (Histogram.GetBinContent(index) < (Mean - 5 * StdDev))):
#         if(Histogram.GetBinContent(index) != 0):
#             print(index, Histogram.GetBinContent(index))

# Histogram.Draw("P* E1 X0")

# # Draw the histogram
# CanvaspQyEPDB.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvaspQyEPDB)




# Histogram = HistogramRootFile.Get("pQxTPCA")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvaspQxTPCA = ROOT.TCanvas("CanvaspQxTPCA", "", 800, 800)
# # Change the scope to be within the file
# CanvaspQxTPCA.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.SetAxisRange(-0.5, 1.3, "Y")

# Sum = 0.0
# Count = 0.0
# StdSum = 0.0

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         Sum = Sum + Histogram.GetBinContent(index)
#         Count = Count + 1
        
# Mean = Sum / Count

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         StdSum = StdSum + pow(Histogram.GetBinContent(index) - Mean, 2)
    
# StdDev = sqrt(StdSum / Count)

# print("pQxTPCA")    
# print("Mean:", Mean)
# print("Standard Deviation:", StdDev)

# print(Mean - 5 * StdDev, Mean + 5 * StdDev)

# for index in range(1, Histogram.GetNbinsX()):
#     if((Histogram.GetBinContent(index) > (Mean + 5 * StdDev)) or (Histogram.GetBinContent(index) < (Mean - 5 * StdDev))):
#         if(Histogram.GetBinContent(index) != 0):
#             print(index, Histogram.GetBinContent(index))

# Histogram.Draw("P* E1 X0")

# # Draw the histogram
# CanvaspQxTPCA.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvaspQxTPCA)






# Histogram = HistogramRootFile.Get("pQyTPCA")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvaspQyTPCA = ROOT.TCanvas("CanvaspQyTPCA", "", 800, 800)
# # Change the scope to be within the file
# CanvaspQyTPCA.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.SetAxisRange(-0.75, 1.25, "Y")

# Sum = 0.0
# Count = 0.0
# StdSum = 0.0

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         Sum = Sum + Histogram.GetBinContent(index)
#         Count = Count + 1
        
# Mean = Sum / Count

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         StdSum = StdSum + pow(Histogram.GetBinContent(index) - Mean, 2)
    
# StdDev = sqrt(StdSum / Count)


# print("pQyTPCA")
# print("Mean:", Mean)
# print("Standard Deviation:", StdDev)

# print(Mean - 5 * StdDev, Mean + 5 * StdDev)

# for index in range(1, Histogram.GetNbinsX()):
#     if((Histogram.GetBinContent(index) > (Mean + 5 * StdDev)) or (Histogram.GetBinContent(index) < (Mean - 5 * StdDev))):
#         if(Histogram.GetBinContent(index) != 0):
#             print(index, Histogram.GetBinContent(index))

# Histogram.Draw("P* E1 X0")

# # Draw the histogram
# CanvaspQyTPCA.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvaspQyTPCA)






# Histogram = HistogramRootFile.Get("pQxTPCB")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvaspQxTPCB = ROOT.TCanvas("CanvaspQxTPCB", "", 800, 800)
# # Change the scope to be within the file
# CanvaspQxTPCB.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.SetAxisRange(-0.15, 0.3, "Y")

# Sum = 0.0
# Count = 0.0
# StdSum = 0.0

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         Sum = Sum + Histogram.GetBinContent(index)
#         Count = Count + 1
        
# Mean = Sum / Count

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         StdSum = StdSum + pow(Histogram.GetBinContent(index) - Mean, 2)
    
# StdDev = sqrt(StdSum / Count)


# print("pQxTPCB")
# print("Mean:", Mean)
# print("Standard Deviation:", StdDev)

# print(Mean - 5 * StdDev, Mean + 5 * StdDev)

# for index in range(1, Histogram.GetNbinsX()):
#     if((Histogram.GetBinContent(index) > (Mean + 5 * StdDev)) or (Histogram.GetBinContent(index) < (Mean - 5 * StdDev))):
#         if(Histogram.GetBinContent(index) != 0):
#             print(index, Histogram.GetBinContent(index))

# Histogram.Draw("P* E1 X0")

# # Draw the histogram
# CanvaspQxTPCB.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvaspQxTPCB)






# Histogram = HistogramRootFile.Get("pQyTPCB")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvaspQyTPCB = ROOT.TCanvas("CanvaspQyTPCB", "", 800, 800)
# # Change the scope to be within the file
# CanvaspQyTPCB.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.SetAxisRange(-0.5, 0.4, "Y")

# Sum = 0.0
# Count = 0.0
# StdSum = 0.0

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         Sum = Sum + Histogram.GetBinContent(index)
#         Count = Count + 1
        
# Mean = Sum / Count

# for index in range(1, Histogram.GetNbinsX()):
#     if(Histogram.GetBinContent(index) != 0):
#         StdSum = StdSum + pow(Histogram.GetBinContent(index) - Mean, 2)
    
# StdDev = sqrt(StdSum / Count)


# print("pQyTPCB")
# print("Mean:", Mean)
# print("Standard Deviation:", StdDev)

# print(Mean - 5 * StdDev, Mean + 5 * StdDev)

# for index in range(1, Histogram.GetNbinsX()):
#     if((Histogram.GetBinContent(index) > (Mean + 5 * StdDev)) or (Histogram.GetBinContent(index) < (Mean - 5 * StdDev))):
#         if(Histogram.GetBinContent(index) != 0):
#             print(index, Histogram.GetBinContent(index))

# Histogram.Draw("P* E1 X0")

# # Draw the histogram
# CanvaspQyTPCB.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvaspQyTPCB)








# Histogram = HistogramRootFile.Get("ZVertexValues")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasZVertexValues = ROOT.TCanvas("CanvasZVertexValues", "", 800, 800)
# # Change the scope to be within the file
# CanvasZVertexValues.cd()

# CanvasZVertexValues.SetLogy()

# # Delete the stats box
# #Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # Draw the histogram
# CanvasZVertexValues.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasZVertexValues)




# Histogram = HistogramRootFile.Get("RVertexValues")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasRVertexValues = ROOT.TCanvas("CanvasRVertexValues", "", 800, 800)
# # Change the scope to be within the file
# CanvasRVertexValues.cd()

# CanvasRVertexValues.SetLogy()

# # Delete the stats box
# #Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # Draw the histogram
# CanvasRVertexValues.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasRVertexValues)




# Histogram = HistogramRootFile.Get("DCAValues")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasDCAValues = ROOT.TCanvas("CanvasDCAValues", "", 800, 800)
# # Change the scope to be within the file
# CanvasDCAValues.cd()

# CanvasDCAValues.SetLogy()

# # Delete the stats box
# #Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # Draw the histogram
# CanvasDCAValues.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasDCAValues)






# Histogram = HistogramRootFile.Get("NHitsValues")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasNHitsValues = ROOT.TCanvas("CanvasNHitsValues", "", 800, 800)
# # Change the scope to be within the file
# CanvasNHitsValues.cd()

# CanvasNHitsValues.SetLogy()

# # Delete the stats box
# #Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # Draw the histogram
# CanvasNHitsValues.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasNHitsValues)





# Histogram = HistogramRootFile.Get("NHitsdEdxValues")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasNHitsdEdxValues = ROOT.TCanvas("CanvasNHitsdEdxValues", "", 800, 800)
# # Change the scope to be within the file
# CanvasNHitsdEdxValues.cd()

# CanvasNHitsdEdxValues.SetLogy()

# # Delete the stats box
# #Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # Draw the histogram
# CanvasNHitsdEdxValues.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasNHitsdEdxValues)





# Histogram = HistogramRootFile.Get("NHitsFitOverNHitsPossValues")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasNHitsFitOverNHitsPossValues = ROOT.TCanvas("CanvasNHitsFitOverNHitsPossValues", "", 800, 800)
# # Change the scope to be within the file
# CanvasNHitsFitOverNHitsPossValues.cd()

# CanvasNHitsFitOverNHitsPossValues.SetLogy()

# # Delete the stats box
# #Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # Draw the histogram
# CanvasNHitsFitOverNHitsPossValues.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasNHitsFitOverNHitsPossValues)






# Histogram = HistogramRootFile.Get("HitCountOuterEPD")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasHitCountOuterEPD = ROOT.TCanvas("CanvasHitCountOuterEPD", "", 800, 800)
# # Change the scope to be within the file
# CanvasHitCountOuterEPD.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # Draw the histogram
# CanvasHitCountOuterEPD.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasHitCountOuterEPD)







# Histogram = HistogramRootFile.Get("Centralities")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasCentralities = ROOT.TCanvas("CanvasCentralities", "", 800, 800)
# # Change the scope to be within the file
# CanvasCentralities.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # Draw the histogram
# CanvasCentralities.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasCentralities)




# Histogram = HistogramRootFile.Get("CentralitiesNineToFifteenOuterEPDHitsOnly")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasCentralitiesNineToFifteenOuterEPDHitsOnly = ROOT.TCanvas("CanvasCentralitiesNineToFifteenOuterEPDHitsOnly", "", 800, 800)
# # Change the scope to be within the file
# CanvasCentralitiesNineToFifteenOuterEPDHitsOnly.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # Draw the histogram
# CanvasCentralities.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasCentralitiesNineToFifteenOuterEPDHitsOnly)




# Histogram = HistogramRootFile.Get("EPDPhiVsEta")

# Histogram.SetDirectory(0)

# CanvasEPDPhiVsEta = ROOT.TCanvas("CanvasEPDPhiVsEta", "", 800, 800)
# CanvasEPDPhiVsEta.cd()

# CanvasEPDPhiVsEta.SetLogz()

# Histogram.SetStats(0)
# Histogram.SetContour(1000)

# Histogram.Draw("colz")

# CanvasEPDPhiVsEta.Draw()

# Canvasas.append(CanvasEPDPhiVsEta)




# Histogram = HistogramRootFile.Get("EtaVsRingNumberVsTruncatednMIP")

# Histogram.SetDirectory(0)

# CanvasEtaVsRingNumberVsTruncatednMIP = ROOT.TCanvas("EtaVsRingNumberVsTruncatednMIP", "", 800, 800)
# CanvasEtaVsRingNumberVsTruncatednMIP.cd()

# CanvasEtaVsRingNumberVsTruncatednMIP.SetLogz()

# Histogram.SetStats(0)
# Histogram.SetContour(1000)

# Histogram.Draw("colz")

# CanvasEtaVsRingNumberVsTruncatednMIP.Draw()

# Canvasas.append(CanvasEtaVsRingNumberVsTruncatednMIP)



# # Get the histogram we want
# Histogram = HistogramRootFile.Get("nMIPVsPhi")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasnMIPVsPhi = ROOT.TCanvas("CanvasnMIPVsPhi", "", 800, 800)
# # Change the scope to be within the file
# CanvasnMIPVsPhi.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # Draw the histogram
# CanvasnMIPVsPhi.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasnMIPVsPhi)






# Histogram = HistogramRootFile.Get("h_eventCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# Canvas_h_eventCheck = ROOT.TCanvas("Canvas_h_eventCheck", "", 800, 800)
# # Change the scope to be within the file
# Canvas_h_eventCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# for index in range (1, Histogram.GetNbinsX() + 1):
#     print(Histogram.GetBinContent(index))

# # Draw the histogram
# Canvas_h_eventCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(Canvas_h_eventCheck)





# Histogram = HistogramRootFile.Get("OverallTrackCheckNoCuts")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasOverallTrackCheckNoCuts = ROOT.TCanvas("OverallTrackCheckNoCuts", "", 800, 800)
# # Change the scope to be within the file
# CanvasOverallTrackCheckNoCuts.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# print(Histogram.GetEntries())

# # for index in range (1, Histogram.GetNbinsX() + 1):
# #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasOverallTrackCheckNoCuts.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasOverallTrackCheckNoCuts)




# Histogram = HistogramRootFile.Get("OverallTrackCheckQACuts")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasOverallTrackCheckQACuts = ROOT.TCanvas("OverallTrackCheckQACuts", "", 800, 800)
# # Change the scope to be within the file
# CanvasOverallTrackCheckQACuts.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# print(Histogram.GetEntries())

# # for index in range (1, Histogram.GetNbinsX() + 1):
# #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasOverallTrackCheckQACuts.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasOverallTrackCheckQACuts)



# Histogram = HistogramRootFile.Get("OverallTrackCheckIDedAsAny")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasOverallTrackCheckIDedAsAny = ROOT.TCanvas("OverallTrackCheckIDedAsAny", "", 800, 800)
# # Change the scope to be within the file
# CanvasOverallTrackCheckIDedAsAny.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# print(Histogram.GetEntries())

# # for index in range (1, Histogram.GetNbinsX() + 1):
# #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasOverallTrackCheckIDedAsAny.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasOverallTrackCheckIDedAsAny)




# Histogram = HistogramRootFile.Get("ProtonTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasProtonTrackCheck = ROOT.TCanvas("ProtonTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasProtonTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# #print(Histogram.GetEntries())

# # for index in range (1, Histogram.GetNbinsX() + 1):
# #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasProtonTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasProtonTrackCheck)




# Histogram = HistogramRootFile.Get("MostlyGoodProtonTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasMostlyGoodProtonTrackCheck = ROOT.TCanvas("MostlyGoodProtonTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasMostlyGoodProtonTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# #print(Histogram.GetEntries())

# # for index in range (1, Histogram.GetNbinsX() + 1):
# #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasMostlyGoodProtonTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasMostlyGoodProtonTrackCheck)





# Histogram = HistogramRootFile.Get("GoodProtonTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasGoodProtonTrackCheck = ROOT.TCanvas("GoodProtonTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasGoodProtonTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # print(Histogram.GetEntries())

# # # for index in range (1, Histogram.GetNbinsX() + 1):
# # #     print(Histogram.GetBinContent(index))

# # # Draw the histogram
# CanvasGoodProtonTrackCheck.Draw()

# # # Add the histogram to the list of histograms
# Canvasas.append(CanvasGoodProtonTrackCheck)




# Histogram = HistogramRootFile.Get("KaonPlusTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasKaonPlusTrackCheck = ROOT.TCanvas("KaonPlusTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasKaonPlusTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# #print(Histogram.GetEntries())

# # for index in range (1, Histogram.GetNbinsX() + 1):
# #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasKaonPlusTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasKaonPlusTrackCheck)




# Histogram = HistogramRootFile.Get("MostlyGoodKaonPlusTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasMostlyGoodKaonPlusTrackCheck = ROOT.TCanvas("GoodMostlyKaonPlusTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasMostlyGoodKaonPlusTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# #print(Histogram.GetEntries())

# # for index in range (1, Histogram.GetNbinsX() + 1):
# #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasMostlyGoodKaonPlusTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasMostlyGoodKaonPlusTrackCheck)





# Histogram = HistogramRootFile.Get("GoodKaonPlusTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasGoodKaonPlusTrackCheck = ROOT.TCanvas("GoodKaonPlusTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasGoodKaonPlusTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # print(Histogram.GetEntries())

# # # for index in range (1, Histogram.GetNbinsX() + 1):
# # #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasGoodKaonPlusTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasGoodKaonPlusTrackCheck)




# Histogram = HistogramRootFile.Get("KaonMinusTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasKaonMinusTrackCheck = ROOT.TCanvas("KaonMinusTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasKaonMinusTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# #print(Histogram.GetEntries())

# # for index in range (1, Histogram.GetNbinsX() + 1):
# #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasKaonMinusTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasKaonMinusTrackCheck)




# Histogram = HistogramRootFile.Get("MostlyGoodKaonMinusTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasMostlyGoodKaonMinusTrackCheck = ROOT.TCanvas("MostlyGoodKaonMinusTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasMostlyGoodKaonMinusTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# #print(Histogram.GetEntries())

# # for index in range (1, Histogram.GetNbinsX() + 1):
# #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasMostlyGoodKaonMinusTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasMostlyGoodKaonMinusTrackCheck)





# Histogram = HistogramRootFile.Get("GoodKaonMinusTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasGoodKaonMinusTrackCheck = ROOT.TCanvas("GoodKaonMinusTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasGoodKaonMinusTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # print(Histogram.GetEntries())

# # # for index in range (1, Histogram.GetNbinsX() + 1):
# # #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasGoodKaonMinusTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasGoodKaonMinusTrackCheck)





# Histogram = HistogramRootFile.Get("PionPlusTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasPionPlusTrackCheck = ROOT.TCanvas("PionPlusTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasPionPlusTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# #print(Histogram.GetEntries())

# # for index in range (1, Histogram.GetNbinsX() + 1):
# #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasPionPlusTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasPionPlusTrackCheck)




# Histogram = HistogramRootFile.Get("MostlyGoodPionPlusTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasMostlyGoodPionPlusTrackCheck = ROOT.TCanvas("MostlyGoodPionPlusTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasMostlyGoodPionPlusTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# #print(Histogram.GetEntries())

# # for index in range (1, Histogram.GetNbinsX() + 1):
# #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasMostlyGoodPionPlusTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasMostlyGoodPionPlusTrackCheck)




# Histogram = HistogramRootFile.Get("GoodPionPlusTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasGoodPionPlusTrackCheck = ROOT.TCanvas("GoodPionPlusTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasGoodPionPlusTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # print(Histogram.GetEntries())

# # # for index in range (1, Histogram.GetNbinsX() + 1):
# # #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasGoodPionPlusTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasGoodPionPlusTrackCheck)





# Histogram = HistogramRootFile.Get("PionMinusTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasPionMinusTrackCheck = ROOT.TCanvas("PionMinusTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasPionMinusTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# #print(Histogram.GetEntries())

# # for index in range (1, Histogram.GetNbinsX() + 1):
# #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasPionMinusTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasPionMinusTrackCheck)



# Histogram = HistogramRootFile.Get("MostlyGoodPionMinusTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasMostlyGoodPionMinusTrackCheck = ROOT.TCanvas("MostlyGoodPionMinusTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasMostlyGoodPionMinusTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# #print(Histogram.GetEntries())

# # for index in range (1, Histogram.GetNbinsX() + 1):
# #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasMostlyGoodPionMinusTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasMostlyGoodPionMinusTrackCheck)



# Histogram = HistogramRootFile.Get("GoodPionMinusTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasGoodPionMinusTrackCheck = ROOT.TCanvas("GoodPionMinusTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasGoodPionMinusTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # print(Histogram.GetEntries())

# # # for index in range (1, Histogram.GetNbinsX() + 1):
# # #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasGoodPionMinusTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasGoodPionMinusTrackCheck)




# Histogram = HistogramRootFile.Get("DeuteronTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasDeuteronTrackCheck = ROOT.TCanvas("DeuteronTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasDeuteronTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # print(Histogram.GetEntries())

# # # for index in range (1, Histogram.GetNbinsX() + 1):
# # #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasDeuteronTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasDeuteronTrackCheck)



# Histogram = HistogramRootFile.Get("MostlyGoodDeuteronTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasMostlyGoodDeuteronTrackCheck = ROOT.TCanvas("MostlyGoodDeuteronTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasMostlyGoodDeuteronTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # print(Histogram.GetEntries())

# # # for index in range (1, Histogram.GetNbinsX() + 1):
# # #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasMostlyGoodDeuteronTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasMostlyGoodDeuteronTrackCheck)




# Histogram = HistogramRootFile.Get("GoodDeuteronTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasGoodDeuteronTrackCheck = ROOT.TCanvas("GoodDeuteronTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasGoodDeuteronTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # print(Histogram.GetEntries())

# # # for index in range (1, Histogram.GetNbinsX() + 1):
# # #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasGoodDeuteronTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasGoodDeuteronTrackCheck)




# Histogram = HistogramRootFile.Get("TritonTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasTritonTrackCheck = ROOT.TCanvas("TritonTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasTritonTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # print(Histogram.GetEntries())

# # # for index in range (1, Histogram.GetNbinsX() + 1):
# # #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasTritonTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasTritonTrackCheck)



# Histogram = HistogramRootFile.Get("MostlyGoodTritonTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasMostlyGoodTritonTrackCheck = ROOT.TCanvas("MostlyGoodTritonTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasMostlyGoodTritonTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # print(Histogram.GetEntries())

# # # for index in range (1, Histogram.GetNbinsX() + 1):
# # #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasMostlyGoodTritonTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasMostlyGoodTritonTrackCheck)



# Histogram = HistogramRootFile.Get("GoodTritonTrackCheck")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasGoodTritonTrackCheck = ROOT.TCanvas("GoodTritonTrackCheck", "", 800, 800)
# # Change the scope to be within the file
# CanvasGoodTritonTrackCheck.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # print(Histogram.GetEntries())

# # # for index in range (1, Histogram.GetNbinsX() + 1):
# # #     print(Histogram.GetBinContent(index))

# # Draw the histogram
# CanvasGoodTritonTrackCheck.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasGoodTritonTrackCheck)






# Histogram = HistogramRootFile.Get("DataNSigmaProtonAll")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasDA = ROOT.TCanvas("CanvasDA", "", 800, 800)
# # Change the scope to be within the file
# CanvasDA.cd()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # Draw the histogram
# CanvasDA.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasDA)







# Histogram = HistogramRootFile.Get("DataNSigmaProtonUsed")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasDB = ROOT.TCanvas("CanvasDB", "", 800, 800)
# # Change the scope to be within the file
# CanvasDB.cd()

# CanvasDB.SetLogy()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # Draw the histogram
# CanvasDB.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasDB)






# # Get the histogram we want
# Histogram = HistogramRootFile.Get("Cos(3(Phi-Psi_1)) for Protons, No Weighting or Resolution Correction")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasDC = ROOT.TCanvas("CanvasDC", "", 800, 800)
# # Change the scope to be within the file
# CanvasDC.cd()

# CanvasDC.SetLogy()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# Histogram = CheckFile.Get("h_35to40_pr_noEff_noRes")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("HIST SAME")

# # Draw the histogram
# CanvasDC.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasDC)





# # Get the histogram we want
# Histogram = HistogramRootFile.Get("Cos(3(Phi-Psi_1)) for Protons, Resolution Corrected but no Weighting")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasDD = ROOT.TCanvas("CanvasDD", "", 800, 800)
# # Change the scope to be within the file
# CanvasDD.cd()

# CanvasDD.SetLogy()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# Histogram = CheckFile.Get("h_35to40_pr_noEff")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("HIST SAME")

# # Draw the histogram
# CanvasDD.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasDD)




# # Get the histogram we want
# Histogram = HistogramRootFile.Get("Cos(3(Phi-Psi_1)) for Protons, Weighted and Resolution Corrected")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasDE = ROOT.TCanvas("CanvasDE", "", 800, 800)
# # Change the scope to be within the file
# CanvasDE.cd()

# CanvasDE.SetLogy()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# Histogram = CheckFile.Get("h_35to40_pr")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("HIST SAME")

# # Draw the histogram
# CanvasDE.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasDE)






# Histogram = HistogramRootFile.Get("DataVxVy")

# Histogram.SetDirectory(0)

# CanvasD0 = ROOT.TCanvas("CanvasD0", "", 800, 800)
# CanvasD0.cd()

# CanvasD0.SetLogz()

# Histogram.SetStats(0)
# Histogram.SetContour(1000)

# Histogram.Draw("colz")

# CanvasD0.Draw()

# Canvasas.append(CanvasD0)






# # Get the histogram we want
# Histogram = HistogramRootFile.Get("DataPt")

# # Change the histogram scope so that it doesn't close when the last file closes
# Histogram.SetDirectory(0)

# # Build the canvas
# CanvasD1 = ROOT.TCanvas("CanvasD1", "", 800, 800)
# # Change the scope to be within the file
# CanvasD1.cd()

# CanvasD1.SetLogy()

# # Delete the stats box
# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# # Draw the histogram
# CanvasD1.Draw()

# # Add the histogram to the list of histograms
# Canvasas.append(CanvasD1)





# Histogram = HistogramRootFile.Get("DataEta")

# Histogram.SetDirectory(0)

# CanvasD2 = ROOT.TCanvas("CanvasD2", "", 800, 800)
# CanvasD2.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD2.Draw()

# Canvasas.append(CanvasD2)





# Histogram = HistogramRootFile.Get("DataPtVsEta")

# Histogram.SetDirectory(0)

# CanvasD3 = ROOT.TCanvas("CanvasD3", "", 800, 800)
# CanvasD3.cd()

# CanvasD3.SetLogz()

# Histogram.SetStats(0)
# # Change the countour gradient
# Histogram.SetContour(1000)

# # Set the histogram with the colors corresponding to the z-values
# Histogram.Draw("colz")

# CanvasD3.Draw()

# Canvasas.append(CanvasD3)





Histogram = HistogramRootFile.Get("DataMSquaredVsQP")

Histogram.SetDirectory(0)

CanvasD4 = ROOT.TCanvas("CanvasD4", "", 800, 800)
CanvasD4.cd()

CanvasD4.SetLogz()

Histogram.SetStats(0)
Histogram.SetContour(1000)

Histogram.Draw("colz")

CanvasD4.Draw()

Canvasas.append(CanvasD4)





# Histogram = HistogramRootFile.Get("DataMSquaredVsQPZoomed")

# Histogram.SetDirectory(0)

# CanvasD4A = ROOT.TCanvas("CanvasD4A", "", 800, 800)
# CanvasD4A.cd()

# CanvasD4A.SetLogz()

# Histogram.SetStats(0)
# Histogram.SetContour(1000)

# Histogram.Draw("colz")

# CanvasD4A.Draw()

# Canvasas.append(CanvasD4A)





# Histogram = HistogramRootFile.Get("DataYProton")

# Histogram.SetDirectory(0)

# CanvasD5 = ROOT.TCanvas("CanvasD5", "", 800, 800)
# CanvasD5.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD5.Draw()

# Canvasas.append(CanvasD5)





# Histogram = HistogramRootFile.Get("DataYKaon")

# Histogram.SetDirectory(0)

# CanvasD6 = ROOT.TCanvas("CanvasD6", "", 800, 800)
# CanvasD6.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD6.Draw()

# Canvasas.append(CanvasD6)





# Histogram = HistogramRootFile.Get("DataYPion")

# Histogram.SetDirectory(0)

# CanvasD7 = ROOT.TCanvas("CanvasD7", "", 800, 800)
# CanvasD7.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD7.Draw()

# Canvasas.append(CanvasD7)





# Histogram = HistogramRootFile.Get("DataPtProton")

# Histogram.SetDirectory(0)

# CanvasD8 = ROOT.TCanvas("CanvasD8", "", 800, 800)
# CanvasD8.cd()

# CanvasD8.SetLogy()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD8.Draw()

# Canvasas.append(CanvasD8)





# Histogram = HistogramRootFile.Get("DataPtKaon")

# Histogram.SetDirectory(0)

# CanvasD9 = ROOT.TCanvas("CanvasD9", "", 800, 800)
# CanvasD9.cd()

# CanvasD9.SetLogy()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD9.Draw()

# Canvasas.append(CanvasD9)





# Histogram = HistogramRootFile.Get("DataPtPion")

# Histogram.SetDirectory(0)

# CanvasD10 = ROOT.TCanvas("CanvasD10", "", 800, 800)
# CanvasD10.cd()

# CanvasD10.SetLogy()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD10.Draw()

# Canvasas.append(CanvasD10)





Histogram = HistogramRootFile.Get("DataMultiplicity")

Histogram.SetDirectory(0)

CanvasD11 = ROOT.TCanvas("CanvasD11", "", 800, 800)
CanvasD11.cd()

Histogram.SetStats(0)

Histogram.Draw("HIST")

CanvasD11.Draw()

Canvasas.append(CanvasD11)





# Histogram = HistogramRootFile.Get("DatadEdxVsP")

# Histogram.SetDirectory(0)

# CanvasD12 = ROOT.TCanvas("CanvasD12", "", 800, 800)
# CanvasD12.cd()

# CanvasD12.SetLogz()

# #Histogram.SetStats(0)
# # Change the countour gradient
# Histogram.SetContour(1000)

# # Set the histogram with the colors corresponding to the z-values
# Histogram.Draw("colz")

# CanvasD12.Draw()

# Canvasas.append(CanvasD12)





# Histogram = HistogramRootFile.Get("DatadEdxVsPPion")

# Histogram.SetDirectory(0)

# CanvasD13 = ROOT.TCanvas("CanvasD13", "", 800, 800)
# CanvasD13.cd()

# CanvasD13.SetLogz()

# Histogram.SetStats(0)
# # Change the countour gradient
# Histogram.SetContour(1000)

# # Set the histogram with the colors corresponding to the z-values
# Histogram.Draw("colz")

# CanvasD13.Draw()

# Canvasas.append(CanvasD13)





# Histogram = HistogramRootFile.Get("DatadEdxVsPKaon")

# Histogram.SetDirectory(0)

# CanvasD14 = ROOT.TCanvas("CanvasD14", "", 800, 800)
# CanvasD14.cd()

# CanvasD14.SetLogz()

# Histogram.SetStats(0)
# # Change the countour gradient
# Histogram.SetContour(1000)

# # Set the histogram with the colors corresponding to the z-values
# Histogram.Draw("colz")

# CanvasD14.Draw()

# Canvasas.append(CanvasD14)





# Histogram = HistogramRootFile.Get("DatadEdxVsPProton")

# Histogram.SetDirectory(0)

# CanvasD15 = ROOT.TCanvas("CanvasD15", "", 800, 800)
# CanvasD15.cd()

# CanvasD15.SetLogz()

# Histogram.SetStats(0)
# # Change the countour gradient
# Histogram.SetContour(1000)

# # Set the histogram with the colors corresponding to the z-values
# Histogram.Draw("colz")

# CanvasD15.Draw()

# Canvasas.append(CanvasD15)





# Histogram = HistogramRootFile.Get("DatadEdxVsPDeuteron")

# Histogram.SetDirectory(0)

# CanvasD16 = ROOT.TCanvas("CanvasD16", "", 800, 800)
# CanvasD16.cd()

# CanvasD16.SetLogz()

# Histogram.SetStats(0)
# # Change the countour gradient
# Histogram.SetContour(1000)

# # Set the histogram with the colors corresponding to the z-values
# Histogram.Draw("colz")

# CanvasD16.Draw()

# Canvasas.append(CanvasD16)





# Histogram = HistogramRootFile.Get("DatadEdxVsPTriton")

# Histogram.SetDirectory(0)

# CanvasD17 = ROOT.TCanvas("CanvasD17", "", 800, 800)
# CanvasD17.cd()

# CanvasD17.SetLogz()

# Histogram.SetStats(0)
# # Change the countour gradient
# Histogram.SetContour(1000)

# # Set the histogram with the colors corresponding to the z-values
# Histogram.Draw("colz")

# CanvasD17.Draw()

# Canvasas.append(CanvasD17)





# Histogram = HistogramRootFile.Get("DataMSquaredVsQPProton")

# Histogram.SetDirectory(0)

# CanvasD18 = ROOT.TCanvas("CanvasD18", "", 800, 800)
# CanvasD18.cd()

# CanvasD18.SetLogz()

# Histogram.SetStats(0)
# Histogram.SetContour(1000)

# Histogram.Draw("colz")

# CanvasD18.Draw()

# Canvasas.append(CanvasD18)





# Histogram = HistogramRootFile.Get("DataMSquaredVsQPKaon")

# Histogram.SetDirectory(0)

# CanvasD19 = ROOT.TCanvas("CanvasD19", "", 800, 800)
# CanvasD19.cd()

# CanvasD19.SetLogz()

# Histogram.SetStats(0)
# Histogram.SetContour(1000)

# Histogram.Draw("colz")

# CanvasD19.Draw()

# Canvasas.append(CanvasD19)





# Histogram = HistogramRootFile.Get("DataMSquaredVsQPPion")

# Histogram.SetDirectory(0)

# CanvasD20 = ROOT.TCanvas("CanvasD20", "", 800, 800)
# CanvasD20.cd()

# CanvasD20.SetLogz()

# Histogram.SetStats(0)
# Histogram.SetContour(1000)

# Histogram.Draw("colz")

# CanvasD20.Draw()

# Canvasas.append(CanvasD20)





# Histogram = HistogramRootFile.Get("DataPtProtonBothCuts")

# Histogram.SetDirectory(0)

# CanvasD21 = ROOT.TCanvas("CanvasD21", "", 800, 800)
# CanvasD21.cd()

# CanvasD21.SetLogy()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD21.Draw()

# Canvasas.append(CanvasD21)





# Histogram = HistogramRootFile.Get("DataPtKaonBothCuts")

# Histogram.SetDirectory(0)

# CanvasD22 = ROOT.TCanvas("CanvasD22", "", 800, 800)
# CanvasD22.cd()

# CanvasD22.SetLogy()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD22.Draw()

# Canvasas.append(CanvasD22)





# Histogram = HistogramRootFile.Get("DataPtPionBothCuts")

# Histogram.SetDirectory(0)

# CanvasD23 = ROOT.TCanvas("CanvasD23", "", 800, 800)
# CanvasD23.cd()

# CanvasD23.SetLogy()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD23.Draw()

# Canvasas.append(CanvasD23)





# Histogram = HistogramRootFile.Get("DataNSigmaPrVsQPProton")

# Histogram.SetDirectory(0)

# CanvasD24 = ROOT.TCanvas("CanvasD24", "", 800, 800)
# CanvasD24.cd()

# CanvasD24.SetLogz()

# Histogram.SetStats(0)
# # Change the countour gradient
# Histogram.SetContour(1000)

# # Set the histogram with the colors corresponding to the z-values
# Histogram.Draw("colz")

# CanvasD24.Draw()

# Canvasas.append(CanvasD24)





# Histogram = HistogramRootFile.Get("DataNSigmaKaVsQPKaon")

# Histogram.SetDirectory(0)

# CanvasD25 = ROOT.TCanvas("CanvasD25", "", 800, 800)
# CanvasD25.cd()

# CanvasD25.SetLogz()

# Histogram.SetStats(0)
# # Change the countour gradient
# Histogram.SetContour(1000)

# # Set the histogram with the colors corresponding to the z-values
# Histogram.Draw("colz")

# CanvasD25.Draw()

# Canvasas.append(CanvasD25)





# Histogram = HistogramRootFile.Get("DataNSigmaPiVsQPPion")

# Histogram.SetDirectory(0)

# CanvasD26 = ROOT.TCanvas("CanvasD26", "", 800, 800)
# CanvasD26.cd()

# CanvasD26.SetLogz()

# Histogram.SetStats(0)
# # Change the countour gradient
# Histogram.SetContour(1000)

# # Set the histogram with the colors corresponding to the z-values
# Histogram.Draw("colz")

# CanvasD26.Draw()

# Canvasas.append(CanvasD26)





Histogram = HistogramRootFile.Get("DataPtVsYProton")

Histogram.SetDirectory(0)

CanvasD27 = ROOT.TCanvas("CanvasD27", "", 800, 800)
CanvasD27.cd()

CanvasD27.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasD27.Draw()

BoxD27 = ROOT.TBox(0, 0.4, 1, 2.0)
BoxD27.SetLineColor(ROOT.kRed)
BoxD27.SetLineWidth(2)
BoxD27.SetFillStyle(0)

BoxD27.Draw()

Canvasas.append(CanvasD27)





Histogram = HistogramRootFile.Get("DataPtVsYKaonPlus")

Histogram.SetDirectory(0)

CanvasD28 = ROOT.TCanvas("CanvasD28", "", 800, 800)
CanvasD28.cd()

CanvasD28.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasD28.Draw()

BoxD28 = ROOT.TBox(0, 0.4, 1, 1.6)
BoxD28.SetLineColor(ROOT.kRed)
BoxD28.SetLineWidth(2)
BoxD28.SetFillStyle(0)

BoxD28.Draw()

Canvasas.append(CanvasD28)





Histogram = HistogramRootFile.Get("DataPtVsYKaonMinus")

Histogram.SetDirectory(0)

CanvasD29 = ROOT.TCanvas("CanvasD29", "", 800, 800)
CanvasD29.cd()

CanvasD29.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasD29.Draw()

BoxD29 = ROOT.TBox(0, 0.4, 1, 1.6)
BoxD29.SetLineColor(ROOT.kRed)
BoxD29.SetLineWidth(2)
BoxD29.SetFillStyle(0)

BoxD29.Draw()

Canvasas.append(CanvasD29)





Histogram = HistogramRootFile.Get("DataPtVsYPionPlus")

Histogram.SetDirectory(0)

CanvasD30 = ROOT.TCanvas("CanvasD30", "", 800, 800)
CanvasD30.cd()

CanvasD30.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasD30.Draw()

BoxD30 = ROOT.TBox(0, 0.2, 1, 1.6)
BoxD30.SetLineColor(ROOT.kRed)
BoxD30.SetLineWidth(2)
BoxD30.SetFillStyle(0)

BoxD30.Draw()

Canvasas.append(CanvasD30)





Histogram = HistogramRootFile.Get("DataPtVsYPionMinus")

Histogram.SetDirectory(0)

CanvasD31 = ROOT.TCanvas("CanvasD31", "", 800, 800)
CanvasD31.cd()

CanvasD31.SetLogz()

Histogram.SetStats(0)
# Change the countour gradient
Histogram.SetContour(1000)

# Set the histogram with the colors corresponding to the z-values
Histogram.Draw("colz")

CanvasD31.Draw()

BoxD31 = ROOT.TBox(0, 0.2, 1, 1.6)
BoxD31.SetLineColor(ROOT.kRed)
BoxD31.SetLineWidth(2)
BoxD31.SetFillStyle(0)

BoxD31.Draw()

Canvasas.append(CanvasD31)





# Histogram = HistogramRootFile.Get("DataPtVsYDeuteron")

# Histogram.SetDirectory(0)

# CanvasD31A = ROOT.TCanvas("CanvasD31A", "", 800, 800)
# CanvasD31A.cd()

# CanvasD31A.SetLogz()

# Histogram.SetStats(0)
# # Change the countour gradient
# Histogram.SetContour(1000)

# Histogram.SetAxisRange(0, 4.0, "Y")

# # Set the histogram with the colors corresponding to the z-values
# Histogram.Draw("colz")

# CanvasD31A.Draw()

# BoxD32 = ROOT.TBox(0, 0.8, 1, 4.0)
# BoxD32.SetLineColor(ROOT.kRed)
# BoxD32.SetLineWidth(2)
# BoxD32.SetFillStyle(0)

# BoxD32.Draw()

# Canvasas.append(CanvasD31A)





# Histogram = HistogramRootFile.Get("DataPtVsYTriton")

# Histogram.SetDirectory(0)

# CanvasD31B = ROOT.TCanvas("CanvasD31B", "", 800, 800)
# CanvasD31B.cd()

# CanvasD31B.SetLogz()

# Histogram.SetStats(0)
# # Change the countour gradient
# Histogram.SetContour(1000)

# Histogram.SetAxisRange(0, 6.0, "Y")

# # Set the histogram with the colors corresponding to the z-values
# Histogram.Draw("colz")

# CanvasD31B.Draw()

# BoxD33 = ROOT.TBox(0, 1.2, 1, 6.0)
# BoxD33.SetLineColor(ROOT.kRed)
# BoxD33.SetLineWidth(2)
# BoxD33.SetFillStyle(0)

# BoxD33.Draw()

# Canvasas.append(CanvasD31B)





# Histogram = HistogramRootFile.Get("DataPhiTPC")

# Histogram.SetDirectory(0)

# CanvasD32 = ROOT.TCanvas("CanvasD32", "", 800, 800)
# CanvasD32.cd()

# CanvasD32.SetLogy()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD32.Draw()

# Canvasas.append(CanvasD32)





Histogram = HistogramRootFile.Get("DataPhiEPD")

Histogram.SetDirectory(0)

CanvasD32A = ROOT.TCanvas("CanvasD32A", "", 800, 800)
CanvasD32A.cd()

# CanvasD32A.SetLogy()

Histogram.SetStats(0)

Histogram.Draw("HIST")

CanvasD32A.Draw()

Canvasas.append(CanvasD32A)





# Histogram = HistogramRootFile.Get("DataEPDEastRingVsEta")

# Histogram.SetDirectory(0)

# CanvasD32B = ROOT.TCanvas("CanvasD32B", "", 800, 800)
# CanvasD32B.cd()

# CanvasD32B.SetLogz()

# Histogram.SetStats(0)
# # Change the countour gradient
# Histogram.SetContour(1000)

# # Set the histogram with the colors corresponding to the z-values
# Histogram.Draw("colz")

# CanvasD32B.Draw()

# Canvasas.append(CanvasD32B)






CanvasD33_34_35 = ROOT.TCanvas("CanvasD33_34_35", "", 800, 800)
CanvasD33_34_35.cd()

Histogram = HistogramRootFile.Get("DataPsi1RawInnerEPD")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("HIST")

Histogram = HistogramRootFile.Get("DataPsi1RecenteredInnerEPD")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("HIST SAME")

Histogram = HistogramRootFile.Get("DataPsi1RecenteredAndShiftedInnerEPD")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kGreen)

Histogram.Draw("HIST SAME")

CanvasD33_34_35.Draw()

Canvasas.append(CanvasD33_34_35)





CanvasD36_37_38 = ROOT.TCanvas("CanvasD36_37_38", "", 800, 800)
CanvasD36_37_38.cd()

Histogram = HistogramRootFile.Get("DataPsi1RawOuterEPD")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("HIST")

Histogram = HistogramRootFile.Get("DataPsi1RecenteredOuterEPD")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("HIST SAME")

Histogram = HistogramRootFile.Get("DataPsi1RecenteredAndShiftedOuterEPD")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kGreen)

Histogram.Draw("HIST SAME")

CanvasD36_37_38.Draw()

Canvasas.append(CanvasD36_37_38)






CanvasD39_40_41 = ROOT.TCanvas("CanvasD39_40_41", "", 800, 800)
CanvasD39_40_41.cd()

Histogram = HistogramRootFile.Get("DataPsi1RawOuterTPC")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kRed)

Histogram.Draw("HIST")

Histogram = HistogramRootFile.Get("DataPsi1RecenteredOuterTPC")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kBlue)

Histogram.Draw("HIST SAME")

Histogram = HistogramRootFile.Get("DataPsi1RecenteredAndShiftedOuterTPC")

Histogram.SetDirectory(0)

Histogram.SetStats(0)

Histogram.SetLineColor(ROOT.kGreen)

Histogram.Draw("HIST SAME")

CanvasD39_40_41.Draw()

Canvasas.append(CanvasD39_40_41)






# CanvasD42_43_44 = ROOT.TCanvas("CanvasD42_43_44", "", 800, 800)
# CanvasD42_43_44.cd()

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RawInnerEPDProton")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("HIST")

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RecenteredInnerEPDProton")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kBlue)

# Histogram.Draw("HIST SAME")

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RecenteredAndShiftedInnerEPDProton")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kGreen)

# Histogram.Draw("HIST SAME")

# CanvasD42_43_44.Draw()

# Canvasas.append(CanvasD42_43_44)





# CanvasD44A = ROOT.TCanvas("CanvasD44A", "", 800, 800)
# CanvasD44A.cd()

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1ResolutionCorrectedProton")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD44A.Draw()

# Canvasas.append(CanvasD44A)





# CanvasD45_46_47 = ROOT.TCanvas("CanvasD45_46_47", "", 800, 800)
# CanvasD45_46_47.cd()

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RawInnerEPDKaonPlus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("HIST")

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RecenteredInnerEPDKaonPlus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kBlue)

# Histogram.Draw("HIST SAME")

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RecenteredAndShiftedInnerEPDKaonPlus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kGreen)

# Histogram.Draw("HIST SAME")

# CanvasD45_46_47.Draw()

# Canvasas.append(CanvasD45_46_47)





# CanvasD47B = ROOT.TCanvas("CanvasD47B", "", 800, 800)
# CanvasD47B.cd()

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1ResolutionCorrectedKaonPlus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD47B.Draw()

# Canvasas.append(CanvasD47B)






# CanvasD45A_46A_47A = ROOT.TCanvas("CanvasD45A_46A_47A", "", 800, 800)
# CanvasD45A_46A_47A.cd()

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RawInnerEPDKaonMinus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("HIST")

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RecenteredInnerEPDKaonMinus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kBlue)

# Histogram.Draw("HIST SAME")

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RecenteredAndShiftedInnerEPDKaonMinus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kGreen)

# Histogram.Draw("HIST SAME")

# CanvasD45A_46A_47A.Draw()

# Canvasas.append(CanvasD45A_46A_47A)





# CanvasD47C = ROOT.TCanvas("CanvasD47C", "", 800, 800)
# CanvasD47C.cd()

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1ResolutionCorrectedKaonMinus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD47C.Draw()

# Canvasas.append(CanvasD47C)







# CanvasD48_49_50 = ROOT.TCanvas("CanvasD48_49_50", "", 800, 800)
# CanvasD48_49_50.cd()

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RawInnerEPDPionPlus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("HIST")

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RecenteredInnerEPDPionPlus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kBlue)

# Histogram.Draw("HIST SAME")

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RecenteredAndShiftedInnerEPDPionPlus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kGreen)

# Histogram.Draw("HIST SAME")

# CanvasD48_49_50.Draw()

# Canvasas.append(CanvasD48_49_50)





# CanvasD50B = ROOT.TCanvas("CanvasD50B", "", 800, 800)
# CanvasD50B.cd()

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1ResolutionCorrectedPionPlus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD50B.Draw()

# Canvasas.append(CanvasD50B)







# CanvasD48A_49A_50A = ROOT.TCanvas("CanvasD48A_49A_50A", "", 800, 800)
# CanvasD48A_49A_50A.cd()

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RawInnerEPDPionMinus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("HIST")

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RecenteredInnerEPDPionMinus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kBlue)

# Histogram.Draw("HIST SAME")

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RecenteredAndShiftedInnerEPDPionMinus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kGreen)

# Histogram.Draw("HIST SAME")

# CanvasD48A_49A_50A.Draw()

# Canvasas.append(CanvasD48A_49A_50A)





# CanvasD50C = ROOT.TCanvas("CanvasD50C", "", 800, 800)
# CanvasD50C.cd()

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1ResolutionCorrectedPionMinus")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD50C.Draw()

# Canvasas.append(CanvasD50C)






# CanvasD48B_49B_50B = ROOT.TCanvas("CanvasD48B_49B_50B", "", 800, 800)
# CanvasD48B_49B_50B.cd()

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RawInnerEPDDeuteron")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("HIST")

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RecenteredInnerEPDDeuteron")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kBlue)

# Histogram.Draw("HIST SAME")

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RecenteredAndShiftedInnerEPDDeuteron")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kGreen)

# Histogram.Draw("HIST SAME")

# CanvasD48B_49B_50B.Draw()

# Canvasas.append(CanvasD48B_49B_50B)





# CanvasD50D = ROOT.TCanvas("CanvasD50D", "", 800, 800)
# CanvasD50D.cd()

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1ResolutionCorrectedDeuteron")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD50D.Draw()

# Canvasas.append(CanvasD50D)






# CanvasD48C_49C_50C = ROOT.TCanvas("CanvasD48C_49C_50C", "", 800, 800)
# CanvasD48C_49C_50C.cd()

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RawInnerEPDTriton")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kRed)

# Histogram.Draw("HIST")

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RecenteredInnerEPDTriton")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kBlue)

# Histogram.Draw("HIST SAME")

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1RecenteredAndShiftedInnerEPDTriton")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.SetLineColor(ROOT.kGreen)

# Histogram.Draw("HIST SAME")

# CanvasD48C_49C_50C.Draw()

# Canvasas.append(CanvasD48C_49C_50C)





# CanvasD50E = ROOT.TCanvas("CanvasD50E", "", 800, 800)
# CanvasD50E.cd()

# Histogram = HistogramRootFile.Get("DataVnVsYPsi1ResolutionCorrectedTriton")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD50E.Draw()

# Canvasas.append(CanvasD50E)






# Histogram = HistogramRootFile.Get("DataResolutionTopLeftTerm")

# Histogram.SetDirectory(0)

# CanvasD51 = ROOT.TCanvas("CanvasD51", "", 800, 800)
# CanvasD51.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD51.Draw()

# Canvasas.append(CanvasD51)






# Histogram = HistogramRootFile.Get("DataResolutionTopRightTerm")

# Histogram.SetDirectory(0)

# CanvasD52 = ROOT.TCanvas("CanvasD52", "", 800, 800)
# CanvasD52.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD52.Draw()

# Canvasas.append(CanvasD52)






# Histogram = HistogramRootFile.Get("DataResolutionBottomTerm")

# Histogram.SetDirectory(0)

# CanvasD53 = ROOT.TCanvas("CanvasD53", "", 800, 800)
# CanvasD53.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD53.Draw()

# Canvasas.append(CanvasD53)





# Histogram = ResolutionRootFile.Get("DataResolution")

# Histogram.SetDirectory(0)

# CanvasD54 = ROOT.TCanvas("CanvasD54", "", 800, 800)
# CanvasD54.cd()

# Histogram.SetStats(0)

# Histogram.SetLineWidth(3)
# Histogram.SetMarkerStyle(ROOT.kFullCircle)
# Histogram.SetMarkerSize(1.5)
# Histogram.SetMarkerColor(ROOT.kBlue)

# Histogram.SetTitle("R_{" + str(nV) + "1}")

# Histogram.Draw("PE 1 X0")

# CanvasD54.Draw()

# Canvasas.append(CanvasD54)






Histogram = HistogramRootFile.Get("DataVnVsCentralityProtonCorrected")

Histogram.SetDirectory(0)

CanvasD54A = ROOT.TCanvas("CanvasD54A", "", 800, 800)
CanvasD54A.cd()

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetStats(0)

if nV == 4:
    Histogram.SetAxisRange(-0.004, 0.004, "Y")
elif nV == 5:
    Histogram.SetAxisRange(-0.01, 0.01, "Y")

Histogram.Draw("PE 1 X0")

CanvasD54A.Draw()

Canvasas.append(CanvasD54A)






Histogram = HistogramRootFile.Get("DataVnVsCentralityKaonPlusCorrected")

Histogram.SetDirectory(0)

CanvasD54B = ROOT.TCanvas("CanvasD54B", "", 800, 800)
CanvasD54B.cd()

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetStats(0)

if nV == 3:
    Histogram.SetAxisRange(-0.02, 0.02, "Y")
elif nV == 4:
    Histogram.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 5:
    Histogram.SetAxisRange(-0.1, 0.1, "Y")

Histogram.Draw("PE 1 X0")

CanvasD54B.Draw()

Canvasas.append(CanvasD54B)





Histogram = HistogramRootFile.Get("DataVnVsCentralityKaonMinusCorrected")

Histogram.SetDirectory(0)

CanvasD54C = ROOT.TCanvas("CanvasD54C", "", 800, 800)
CanvasD54C.cd()

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetStats(0)

if nV == 3:
    Histogram.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 4:
    Histogram.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 5:
    Histogram.SetAxisRange(-0.3, 0.3, "Y")

Histogram.Draw("PE 1 X0")
CanvasD54C.Draw()

Canvasas.append(CanvasD54C)





Histogram = HistogramRootFile.Get("DataVnVsCentralityPionPlusCorrected")

Histogram.SetDirectory(0)

CanvasD54D = ROOT.TCanvas("CanvasD54D", "", 800, 800)
CanvasD54D.cd()

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetStats(0)

if nV == 3:
    Histogram.SetAxisRange(-0.01, 0.005, "Y")
elif nV == 4:
    Histogram.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    Histogram.SetAxisRange(-0.05, 0.05,"Y")

Histogram.Draw("PE 1 X0")
CanvasD54D.Draw()

Canvasas.append(CanvasD54D)





Histogram = HistogramRootFile.Get("DataVnVsCentralityPionMinusCorrected")

Histogram.SetDirectory(0)

CanvasD54E = ROOT.TCanvas("CanvasD54E", "", 800, 800)
CanvasD54E.cd()

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetStats(0)

if nV == 3:
    Histogram.SetAxisRange(-0.005, 0.002, "Y")
elif nV == 4:
    Histogram.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    Histogram.SetAxisRange(-0.05, 0.05, "Y")

Histogram.Draw("PE 1 X0")
CanvasD54E.Draw()

Canvasas.append(CanvasD54E)





Histogram = HistogramRootFile.Get("DataVnVsCentralityDeuteronCorrected")

Histogram.SetDirectory(0)

CanvasD54F = ROOT.TCanvas("CanvasD54F", "", 800, 800)
CanvasD54F.cd()

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetStats(0)

if nV == 4:
    Histogram.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    Histogram.SetAxisRange(-0.02, 0.02, "Y")

Histogram.Draw("PE 1 X0")
CanvasD54F.Draw()

Canvasas.append(CanvasD54F)




Histogram = HistogramRootFile.Get("DataVnVsCentralityTritonCorrected")

Histogram.SetDirectory(0)

CanvasD54G = ROOT.TCanvas("CanvasD54G", "", 800, 800)
CanvasD54G.cd()

Histogram.SetLineWidth(3)
Histogram.SetMarkerStyle(ROOT.kFullCircle)
Histogram.SetMarkerSize(1.5)
Histogram.SetMarkerColor(ROOT.kBlue)

Histogram.SetStats(0)

if nV == 3:
    Histogram.SetAxisRange(-0.05, 0.02, "Y")
elif nV == 4:
    Histogram.SetAxisRange(-0.03, 0.02, "Y")
elif nV == 5:
    Histogram.SetAxisRange(-0.1, 0.1, "Y")

Histogram.Draw("PE 1 X0")

CanvasD54G.Draw()

Canvasas.append(CanvasD54G)






# Histogram = HistogramRootFile.Get("DataVnCorrectedVsPtDifferentCentralitiesProton")

# Histogram.SetDirectory(0)

# CanvasD79 = ROOT.TCanvas("CanvasD79", "", 800, 800)
# CanvasD79.cd()

# Histogram.SetStats(0)

# Histogram.Draw("PE 1")

# CanvasD79.Draw()

# Canvasas.append(CanvasD79)





# Histogram = HistogramRootFile.Get("DataVnCorrectedVsYDifferentCentralitiesProton")

# Histogram.SetDirectory(0)

# CanvasD80 = ROOT.TCanvas("CanvasD80", "", 800, 800)
# CanvasD80.cd()

# Histogram.SetStats(0)

# Histogram.Draw("PE 1")

# CanvasD80.Draw()

# Canvasas.append(CanvasD80)





# Histogram = HistogramRootFile.Get("DataVnCorrectedVsPtDifferentCentralitiesKaonPlus")

# Histogram.SetDirectory(0)

# CanvasD81 = ROOT.TCanvas("CanvasD81", "", 800, 800)
# CanvasD81.cd()

# Histogram.SetStats(0)

# Histogram.Draw("PE 1")

# CanvasD81.Draw()

# Canvasas.append(CanvasD81)





# Histogram = HistogramRootFile.Get("DataVnCorrectedVsYDifferentCentralitiesKaonPlus")

# Histogram.SetDirectory(0)

# CanvasD82 = ROOT.TCanvas("CanvasD82", "", 800, 800)
# CanvasD82.cd()

# Histogram.SetStats(0)

# Histogram.Draw("PE 1")

# CanvasD82.Draw()

# Canvasas.append(CanvasD82)






# Histogram = HistogramRootFile.Get("DataVnCorrectedVsPtDifferentCentralitiesKaonMinus")

# Histogram.SetDirectory(0)

# CanvasD83 = ROOT.TCanvas("CanvasD83", "", 800, 800)
# CanvasD83.cd()

# Histogram.SetStats(0)

# Histogram.Draw("PE 1")

# CanvasD83.Draw()

# Canvasas.append(CanvasD83)





# Histogram = HistogramRootFile.Get("DataVnCorrectedVsYDifferentCentralitiesKaonMinus")

# Histogram.SetDirectory(0)

# CanvasD84 = ROOT.TCanvas("CanvasD84", "", 800, 800)
# CanvasD84.cd()

# Histogram.SetStats(0)

# Histogram.Draw("PE 1")

# CanvasD84.Draw()

# Canvasas.append(CanvasD84)





# Histogram = HistogramRootFile.Get("DataVnCorrectedVsPtDifferentCentralitiesPionPlus")

# Histogram.SetDirectory(0)

# CanvasD85 = ROOT.TCanvas("CanvasD85", "", 800, 800)
# CanvasD85.cd()

# Histogram.SetStats(0)

# Histogram.Draw("PE 1")

# CanvasD85.Draw()

# Canvasas.append(CanvasD85)





# Histogram = HistogramRootFile.Get("DataVnCorrectedVsYDifferentCentralitiesPionPlus")

# Histogram.SetDirectory(0)

# CanvasD86 = ROOT.TCanvas("CanvasD86", "", 800, 800)
# CanvasD86.cd()

# Histogram.SetStats(0)

# Histogram.Draw("PE 1")

# CanvasD86.Draw()

# Canvasas.append(CanvasD86)





# Histogram = HistogramRootFile.Get("DataVnCorrectedVsPtDifferentCentralitiesPionMinus")

# Histogram.SetDirectory(0)

# CanvasD87 = ROOT.TCanvas("CanvasD87", "", 800, 800)
# CanvasD87.cd()

# Histogram.SetStats(0)

# Histogram.Draw("PE 1")

# CanvasD87.Draw()

# Canvasas.append(CanvasD87)





# Histogram = HistogramRootFile.Get("DataVnCorrectedVsYDifferentCentralitiesPionMinus")

# Histogram.SetDirectory(0)

# CanvasD88 = ROOT.TCanvas("CanvasD88", "", 800, 800)
# CanvasD88.cd()

# Histogram.SetStats(0)

# Histogram.Draw("PE 1")

# CanvasD88.Draw()

# Canvasas.append(CanvasD88)





CanvasD89_90_91 = ROOT.TCanvas("CanvasD89_90_91", "", 800, 800)
CanvasD89_90_91.cd()

HistogramA = HistogramRootFile.Get("DataVnVsPtForProtonsCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(3)
HistogramA.SetMarkerStyle(ROOT.kFullSquare)
HistogramA.SetMarkerSize(1.5)
HistogramA.SetMarkerColor(ROOT.kRed)

HistogramA.SetLineColor(ROOT.kRed)

if nV == 1:
    HistogramA.SetAxisRange(0.0, 0.20, "Y")
elif nV == 4:
    HistogramA.SetAxisRange(-0.004, 0.004, "Y")
elif nV == 5:
    HistogramA.SetAxisRange(-0.01, 0.01, "Y")

HistogramA.Draw("P* E1 X0")

HistogramC = HistogramRootFile.Get("DataVnVsPtForProtonsCentrality40-60")

HistogramC.SetDirectory(0)

HistogramC.SetStats(0)

HistogramC.SetLineWidth(3)
HistogramC.SetMarkerStyle(ROOT.kFullTriangleDown)
HistogramC.SetMarkerSize(1.5)
HistogramC.SetMarkerColor(ROOT.kGreen)

HistogramC.SetLineColor(ROOT.kGreen)

if nV == 1:
    HistogramA.SetAxisRange(0.0, 0.20, "Y")
elif nV == 4:
    HistogramC.SetAxisRange(-0.004, 0.004, "Y")
elif nV == 5:
    HistogramC.SetAxisRange(-0.01, 0.01, "Y")

HistogramC.Draw("P* E1 X0 SAME")

HistogramB = HistogramRootFile.Get("DataVnVsPtForProtonsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullCircle)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kBlue)

HistogramB.SetLineColor(ROOT.kBlue)

if nV == 1:
    HistogramA.SetAxisRange(0.0, 0.20, "Y")
elif nV == 4:
    HistogramB.SetAxisRange(-0.004, 0.004, "Y")
elif nV == 5:
    HistogramB.SetAxisRange(-0.01, 0.01, "Y")

HistogramB.Draw("P* E1 X0 SAME")

CanvasD89_90_91.Draw()

Legend89_90_91 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend89_90_91.AddEntry(HistogramA, "0-10% Centrality")
Legend89_90_91.AddEntry(HistogramB, "10-40% Centrality")
Legend89_90_91.AddEntry(HistogramC, "40-60% Centrality")
Legend89_90_91.Draw()

Canvasas.append(CanvasD89_90_91)





CanvasD92_93_94 = ROOT.TCanvas("CanvasD92_93_94", "", 800, 800)
CanvasD92_93_94.cd()

HistogramA = HistogramRootFile.Get("DataVnVsYForProtonsCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(3)
HistogramA.SetMarkerStyle(ROOT.kFullSquare)
HistogramA.SetMarkerSize(1.5)
HistogramA.SetMarkerColor(ROOT.kRed)

HistogramA.SetLineColor(ROOT.kRed)

# if nV == 2:
#     Histogram.SetAxisRange(-0.1, 0.05, "Y")
if nV == 3:
    HistogramA.SetAxisRange(-0.02, 0.001, "Y")
elif nV == 4:
    HistogramA.SetAxisRange(-0.004, 0.004, "Y")
elif nV == 5:
    HistogramA.SetAxisRange(-0.01, 0.01, "Y")

HistogramA.Draw("PE 1 X0")

HistogramC = HistogramRootFile.Get("DataVnVsYForProtonsCentrality40-60")

HistogramC.SetDirectory(0)

HistogramC.SetStats(0)

HistogramC.SetLineWidth(3)
HistogramC.SetMarkerStyle(ROOT.kFullTriangleDown)
HistogramC.SetMarkerSize(1.5)
HistogramC.SetMarkerColor(ROOT.kGreen)

HistogramC.SetLineColor(ROOT.kGreen)

# if nV == 2:
#     Histogram.SetAxisRange(-0.1, 0.05, "Y")
if nV == 3:
    HistogramC.SetAxisRange(-0.02, 0.001, "Y")
elif nV == 4:
    HistogramC.SetAxisRange(-0.004, 0.004, "Y")
elif nV == 5:
    HistogramC.SetAxisRange(-0.01, 0.01, "Y")

HistogramC.Draw("PE 1 X0 SAME")

HistogramB = HistogramRootFile.Get("DataVnVsYForProtonsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullCircle)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kBlue)

HistogramB.SetLineColor(ROOT.kBlue)

# if nV == 2:
#     Histogram.SetAxisRange(-0.1, 0.05, "Y")
if nV == 3:
    HistogramB.SetAxisRange(-0.02, 0.001, "Y")
elif nV == 4:
    HistogramB.SetAxisRange(-0.004, 0.004, "Y")
elif nV == 5:
    HistogramB.SetAxisRange(-0.01, 0.01, "Y")

HistogramB.Draw("PE 1 X0 SAME")

CanvasD92_93_94.Draw()

Legend92_93_94 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend92_93_94.AddEntry(HistogramA, "0-10% Centrality")
Legend92_93_94.AddEntry(HistogramB, "10-40% Centrality")
Legend92_93_94.AddEntry(HistogramC, "40-60% Centrality")
Legend92_93_94.Draw()

Canvasas.append(CanvasD92_93_94)





CanvasD95_96_97 = ROOT.TCanvas("CanvasD95_96_97", "", 800, 800)
CanvasD95_96_97.cd()

HistogramA = HistogramRootFile.Get("DataVnVsPtForKaonsPlusCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(3)
HistogramA.SetMarkerStyle(ROOT.kFullSquare)
HistogramA.SetMarkerSize(1.5)
HistogramA.SetMarkerColor(ROOT.kRed)

HistogramA.SetLineColor(ROOT.kRed)

if nV == 3:
    HistogramA.SetAxisRange(-0.05, 0.05, "Y")
elif nV == 4:
    HistogramA.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 5:
    HistogramA.SetAxisRange(-0.1, 0.1, "Y")

HistogramA.Draw("PE 1 X0")

HistogramC = HistogramRootFile.Get("DataVnVsPtForKaonsPlusCentrality40-60")

HistogramC.SetDirectory(0)

HistogramC.SetStats(0)

HistogramC.SetLineWidth(3)
HistogramC.SetMarkerStyle(ROOT.kFullTriangleDown)
HistogramC.SetMarkerSize(1.5)
HistogramC.SetMarkerColor(ROOT.kGreen)

HistogramC.SetLineColor(ROOT.kGreen)

if nV == 3:
    HistogramC.SetAxisRange(-0.05, 0.05, "Y")
elif nV == 4:
    HistogramC.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 5:
    HistogramC.SetAxisRange(-0.1, 0.1, "Y")

HistogramC.Draw("PE 1 X0 SAME")

HistogramB = HistogramRootFile.Get("DataVnVsPtForKaonsPlusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullCircle)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kBlue)

HistogramB.SetLineColor(ROOT.kBlue)

if nV == 3:
    HistogramB.SetAxisRange(-0.05, 0.05, "Y")
elif nV == 4:
    HistogramB.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 5:
    HistogramB.SetAxisRange(-0.1, 0.1, "Y")

HistogramB.Draw("PE 1 X0 SAME")

CanvasD95_96_97.Draw()

Legend95_96_97 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend95_96_97.AddEntry(HistogramA, "0-10% Centrality")
Legend95_96_97.AddEntry(HistogramB, "10-40% Centrality")
Legend95_96_97.AddEntry(HistogramC, "40-60% Centrality")
Legend95_96_97.Draw()

Canvasas.append(CanvasD95_96_97)





CanvasD98_99_100 = ROOT.TCanvas("CanvasD98_99_100", "", 800, 800)
CanvasD98_99_100.cd()

HistogramA = HistogramRootFile.Get("DataVnVsYForKaonsPlusCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(3)
HistogramA.SetMarkerStyle(ROOT.kFullSquare)
HistogramA.SetMarkerSize(1.5)
HistogramA.SetMarkerColor(ROOT.kRed)

HistogramA.SetLineColor(ROOT.kRed)

if nV == 3:
    HistogramA.SetAxisRange(-0.03, 0.03, "Y")
elif nV == 4:
    HistogramA.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 5:
    HistogramA.SetAxisRange(-0.1, 0.1, "Y")

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Red", Histogram.GetBinContent(i))

HistogramA.Draw("PE 1 X0")

HistogramC = HistogramRootFile.Get("DataVnVsYForKaonsPlusCentrality40-60")

HistogramC.SetDirectory(0)

HistogramC.SetStats(0)

HistogramC.SetLineWidth(3)
HistogramC.SetMarkerStyle(ROOT.kFullTriangleDown)
HistogramC.SetMarkerSize(1.5)
HistogramC.SetMarkerColor(ROOT.kGreen)

HistogramC.SetLineColor(ROOT.kGreen)

if nV == 3:
    HistogramC.SetAxisRange(-0.03, 0.03, "Y")
elif nV == 4:
    HistogramC.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 5:
    HistogramC.SetAxisRange(-0.1, 0.1, "Y")

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Green", Histogram.GetBinContent(i))

HistogramC.Draw("P* E1 X0 SAME")

HistogramB = HistogramRootFile.Get("DataVnVsYForKaonsPlusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullCircle)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kBlue)

HistogramB.SetLineColor(ROOT.kBlue)

if nV == 3:
    HistogramB.SetAxisRange(-0.03, 0.03, "Y")
elif nV == 4:
    HistogramB.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 5:
    HistogramB.SetAxisRange(-0.1, 0.1, "Y")

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Blue", Histogram.GetBinContent(i))

HistogramB.Draw("PE 1 X0 SAME")

CanvasD98_99_100.Draw()

Legend98_99_100 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend98_99_100.AddEntry(HistogramA, "0-10% Centrality")
Legend98_99_100.AddEntry(HistogramB, "10-40% Centrality")
Legend98_99_100.AddEntry(HistogramC, "40-60% Centrality")
Legend98_99_100.Draw()

Canvasas.append(CanvasD98_99_100)






CanvasD101_102_103 = ROOT.TCanvas("CanvasD101_102_103", "", 800, 800)
CanvasD101_102_103.cd()

HistogramA = HistogramRootFile.Get("DataVnVsPtForKaonsMinusCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(3)
HistogramA.SetMarkerStyle(ROOT.kFullSquare)
HistogramA.SetMarkerSize(1.5)
HistogramA.SetMarkerColor(ROOT.kRed)

HistogramA.SetLineColor(ROOT.kRed)

if nV == 3:
    HistogramA.SetAxisRange(-0.1, 0.2, "Y")
elif nV == 4:
    HistogramA.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 5:
    HistogramA.SetAxisRange(-0.3, 0.3, "Y")

HistogramA.Draw("PE 1 X0")

HistogramC = HistogramRootFile.Get("DataVnVsPtForKaonsMinusCentrality40-60")

HistogramC.SetDirectory(0)

HistogramC.SetStats(0)

HistogramC.SetLineWidth(3)
HistogramC.SetMarkerStyle(ROOT.kFullTriangleDown)
HistogramC.SetMarkerSize(1.5)
HistogramC.SetMarkerColor(ROOT.kGreen)

HistogramC.SetLineColor(ROOT.kGreen)

if nV == 3:
    HistogramC.SetAxisRange(-0.1, 0.2, "Y")
elif nV == 4:
    HistogramC.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 5:
    HistogramC.SetAxisRange(-0.3, 0.3, "Y")

HistogramC.Draw("PE 1 X0 SAME")

HistogramB = HistogramRootFile.Get("DataVnVsPtForKaonsMinusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullCircle)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kBlue)

HistogramB.SetLineColor(ROOT.kBlue)

if nV == 3:
    HistogramB.SetAxisRange(-0.1, 0.2, "Y")
elif nV == 4:
    HistogramB.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 5:
    HistogramB.SetAxisRange(-0.3, 0.3, "Y")

HistogramB.Draw("PE 1 X0 SAME")

CanvasD101_102_103.Draw()

Legend101_102_103 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend101_102_103.AddEntry(HistogramA, "0-10% Centrality")
Legend101_102_103.AddEntry(HistogramB, "10-40% Centrality")
Legend101_102_103.AddEntry(HistogramC, "40-60% Centrality")
Legend101_102_103.Draw()

Canvasas.append(CanvasD101_102_103)





CanvasD104_105_106 = ROOT.TCanvas("CanvasD104_105_106", "", 800, 800)
CanvasD104_105_106.cd()

HistogramA = HistogramRootFile.Get("DataVnVsYForKaonsMinusCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(3)
HistogramA.SetMarkerStyle(ROOT.kFullSquare)
HistogramA.SetMarkerSize(1.5)
HistogramA.SetMarkerColor(ROOT.kRed)

HistogramA.SetLineColor(ROOT.kRed)

if nV == 3:
    HistogramA.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 4:
    HistogramA.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 5:
    HistogramA.SetAxisRange(-0.3, 0.3, "Y")

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Red", Histogram.GetBinContent(i))

HistogramA.Draw("PE 1 X0")

HistogramC = HistogramRootFile.Get("DataVnVsYForKaonsMinusCentrality40-60")

HistogramC.SetDirectory(0)

HistogramC.SetStats(0)

HistogramC.SetLineWidth(3)
HistogramC.SetMarkerStyle(ROOT.kFullTriangleDown)
HistogramC.SetMarkerSize(1.5)
HistogramC.SetMarkerColor(ROOT.kGreen)

HistogramC.SetLineColor(ROOT.kGreen)

if nV == 3:
    HistogramC.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 4:
    HistogramC.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 5:
    HistogramC.SetAxisRange(-0.3, 0.3, "Y")

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Green", Histogram.GetBinContent(i))

HistogramC.Draw("PE 1 X0 SAME")

HistogramB = HistogramRootFile.Get("DataVnVsYForKaonsMinusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullCircle)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kBlue)

HistogramB.SetLineColor(ROOT.kBlue)

if nV == 3:
    HistogramB.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 4:
    HistogramB.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 5:
    HistogramB.SetAxisRange(-0.3, 0.3, "Y")

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Blue", Histogram.GetBinContent(i))

HistogramB.Draw("PE 1 X0 SAME")

CanvasD104_105_106.Draw()

Legend104_105_106 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend104_105_106.AddEntry(HistogramA, "0-10% Centrality")
Legend104_105_106.AddEntry(HistogramB, "10-40% Centrality")
Legend104_105_106.AddEntry(HistogramC, "40-60% Centrality")
Legend104_105_106.Draw()

Canvasas.append(CanvasD104_105_106)





CanvasD107_108_109 = ROOT.TCanvas("CanvasD107_108_109", "", 800, 800)
CanvasD107_108_109.cd()

HistogramA = HistogramRootFile.Get("DataVnVsPtForPionsPlusCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(3)
HistogramA.SetMarkerStyle(ROOT.kFullSquare)
HistogramA.SetMarkerSize(1.5)
HistogramA.SetMarkerColor(ROOT.kRed)

HistogramA.SetLineColor(ROOT.kRed)

if nV == 3:
    HistogramA.SetAxisRange(-0.05, 0.02, "Y")
elif nV == 4:
    HistogramA.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramA.SetAxisRange(-0.05, 0.05, "Y")

HistogramA.Draw("PE 1 X0")

HistogramC = HistogramRootFile.Get("DataVnVsPtForPionsPlusCentrality40-60")

HistogramC.SetDirectory(0)

HistogramC.SetStats(0)

HistogramC.SetLineWidth(3)
HistogramC.SetMarkerStyle(ROOT.kFullTriangleDown)
HistogramC.SetMarkerSize(1.5)
HistogramC.SetMarkerColor(ROOT.kGreen)

HistogramC.SetLineColor(ROOT.kGreen)

if nV == 3:
    HistogramC.SetAxisRange(-0.05, 0.02, "Y")
elif nV == 4:
    HistogramC.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramC.SetAxisRange(-0.05, 0.05, "Y")

HistogramC.Draw("PE 1 X0 SAME")

HistogramB = HistogramRootFile.Get("DataVnVsPtForPionsPlusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullCircle)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kBlue)

HistogramB.SetLineColor(ROOT.kBlue)

if nV == 3:
    HistogramB.SetAxisRange(-0.05, 0.02, "Y")
elif nV == 4:
    HistogramB.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramB.SetAxisRange(-0.05, 0.05, "Y")

HistogramB.Draw("PE 1 X0 SAME")

CanvasD107_108_109.Draw()

Legend107_108_109 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend107_108_109.AddEntry(HistogramA, "0-10% Centrality")
Legend107_108_109.AddEntry(HistogramB, "10-40% Centrality")
Legend107_108_109.AddEntry(HistogramC, "40-60% Centrality")
Legend107_108_109.Draw()

Canvasas.append(CanvasD107_108_109)





CanvasD110_111_112 = ROOT.TCanvas("CanvasD110_111_112", "", 800, 800)
CanvasD110_111_112.cd()

HistogramA = HistogramRootFile.Get("DataVnVsYForPionsPlusCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(3)
HistogramA.SetMarkerStyle(ROOT.kFullSquare)
HistogramA.SetMarkerSize(1.5)
HistogramA.SetMarkerColor(ROOT.kRed)

HistogramA.SetLineColor(ROOT.kRed)

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Red", Histogram.GetBinContent(i))

if nV == 3:
    HistogramA.SetAxisRange(-0.005, 0.002, "Y")
elif nV == 4:
    HistogramA.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramA.SetAxisRange(-0.05, 0.05, "Y")

HistogramA.Draw("PE 1 X0")

HistogramC = HistogramRootFile.Get("DataVnVsYForPionsPlusCentrality40-60")

HistogramC.SetDirectory(0)

HistogramC.SetStats(0)

HistogramC.SetLineWidth(3)
HistogramC.SetMarkerStyle(ROOT.kFullTriangleDown)
HistogramC.SetMarkerSize(1.5)
HistogramC.SetMarkerColor(ROOT.kGreen)

HistogramC.SetLineColor(ROOT.kGreen)

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Green", Histogram.GetBinContent(i))

if nV == 3:
    HistogramC.SetAxisRange(-0.005, 0.002, "Y")
elif nV == 4:
    HistogramC.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramC.SetAxisRange(-0.05, 0.05, "Y")

HistogramC.Draw("PE 1 X0 SAME")

HistogramB = HistogramRootFile.Get("DataVnVsYForPionsPlusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullCircle)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kBlue)

HistogramB.SetLineColor(ROOT.kBlue)

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Blue", Histogram.GetBinContent(i))

if nV == 3:
    HistogramB.SetAxisRange(-0.005, 0.002, "Y")
elif nV == 4:
    HistogramB.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramB.SetAxisRange(-0.05, 0.05, "Y")

HistogramB.Draw("PE 1 X0 SAME")

CanvasD110_111_112.Draw()

Legend110_111_112 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend110_111_112.AddEntry(HistogramA, "0-10% Centrality")
Legend110_111_112.AddEntry(HistogramB, "10-40% Centrality")
Legend110_111_112.AddEntry(HistogramC, "40-60% Centrality")
Legend110_111_112.Draw()

Canvasas.append(CanvasD110_111_112)





CanvasD113_114_115 = ROOT.TCanvas("CanvasD113_114_115", "", 800, 800)
CanvasD113_114_115.cd()

HistogramA = HistogramRootFile.Get("DataVnVsPtForPionsMinusCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(3)
HistogramA.SetMarkerStyle(ROOT.kFullSquare)
HistogramA.SetMarkerSize(1.5)
HistogramA.SetMarkerColor(ROOT.kRed)

HistogramA.SetLineColor(ROOT.kRed)

if nV == 3:
    HistogramA.SetAxisRange(-0.03, 0.03, "Y")
elif nV == 4:
    HistogramA.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramA.SetAxisRange(-0.05, 0.05, "Y")

HistogramA.Draw("PE 1 X0")

HistogramC = HistogramRootFile.Get("DataVnVsPtForPionsMinusCentrality40-60")

HistogramC.SetDirectory(0)

HistogramC.SetStats(0)

HistogramC.SetLineWidth(3)
HistogramC.SetMarkerStyle(ROOT.kFullTriangleDown)
HistogramC.SetMarkerSize(1.5)
HistogramC.SetMarkerColor(ROOT.kGreen)

HistogramC.SetLineColor(ROOT.kGreen)

if nV == 3:
    HistogramC.SetAxisRange(-0.03, 0.03, "Y")
elif nV == 4:
    HistogramC.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramC.SetAxisRange(-0.05, 0.05, "Y")

HistogramC.Draw("PE 1 X0 SAME")

HistogramB = HistogramRootFile.Get("DataVnVsPtForPionsMinusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullCircle)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kBlue)

HistogramB.SetLineColor(ROOT.kBlue)

if nV == 3:
    HistogramB.SetAxisRange(-0.03, 0.03, "Y")
elif nV == 4:
    HistogramB.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramB.SetAxisRange(-0.05, 0.05, "Y")

HistogramB.Draw("PE 1 X0 SAME")

CanvasD113_114_115.Draw()

Legend113_114_115 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend113_114_115.AddEntry(HistogramA, "0-10% Centrality")
Legend113_114_115.AddEntry(HistogramB, "10-40% Centrality")
Legend113_114_115.AddEntry(HistogramC, "40-60% Centrality")
Legend113_114_115.Draw()

Canvasas.append(CanvasD113_114_115)





CanvasD116_117_118 = ROOT.TCanvas("CanvasD116_117_118", "", 800, 800)
CanvasD116_117_118.cd()

HistogramA = HistogramRootFile.Get("DataVnVsYForPionsMinusCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(3)
HistogramA.SetMarkerStyle(ROOT.kFullSquare)
HistogramA.SetMarkerSize(1.5)
HistogramA.SetMarkerColor(ROOT.kRed)

HistogramA.SetLineColor(ROOT.kRed)

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Red", Histogram.GetBinContent(i))

if nV == 3:
    HistogramA.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 4:
    HistogramA.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramA.SetAxisRange(-0.05, 0.05, "Y")

HistogramA.Draw("PE 1 X0")

HistogramC = HistogramRootFile.Get("DataVnVsYForPionsMinusCentrality40-60")

HistogramC.SetDirectory(0)

HistogramC.SetStats(0)

HistogramC.SetLineWidth(3)
HistogramC.SetMarkerStyle(ROOT.kFullTriangleDown)
HistogramC.SetMarkerSize(1.5)
HistogramC.SetMarkerColor(ROOT.kGreen)

HistogramC.SetLineColor(ROOT.kGreen)

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Green", Histogram.GetBinContent(i))

if nV == 3:
    HistogramC.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 4:
    HistogramC.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramC.SetAxisRange(-0.05, 0.05, "Y")

HistogramC.Draw("PE 1 X0 SAME")

HistogramB = HistogramRootFile.Get("DataVnVsYForPionsMinusCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullCircle)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kBlue)

HistogramB.SetLineColor(ROOT.kBlue)

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Blue", Histogram.GetBinContent(i))

if nV == 3:
    HistogramB.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 4:
    HistogramB.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramB.SetAxisRange(-0.05, 0.05, "Y")

HistogramB.Draw("PE 1 X0 SAME")

CanvasD116_117_118.Draw()

Legend116_117_118 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend116_117_118.AddEntry(HistogramA, "0-10% Centrality")
Legend116_117_118.AddEntry(HistogramB, "10-40% Centrality")
Legend116_117_118.AddEntry(HistogramC, "40-60% Centrality")
Legend116_117_118.Draw()

Canvasas.append(CanvasD116_117_118)








CanvasD119_120_121 = ROOT.TCanvas("CanvasD119_120_121", "", 800, 800)
CanvasD119_120_121.cd()

HistogramA = HistogramRootFile.Get("DataVnVsPtForDeuteronsCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(3)
HistogramA.SetMarkerStyle(ROOT.kFullSquare)
HistogramA.SetMarkerSize(1.5)
HistogramA.SetMarkerColor(ROOT.kRed)

HistogramA.SetLineColor(ROOT.kRed)

if nV == 3:
    HistogramA.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 4:
    HistogramA.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramA.SetAxisRange(-0.02, 0.02, "Y")

HistogramA.Draw("PE 1 X0")

HistogramC = HistogramRootFile.Get("DataVnVsPtForDeuteronsCentrality40-60")

HistogramC.SetDirectory(0)

HistogramC.SetStats(0)

HistogramC.SetLineWidth(3)
HistogramC.SetMarkerStyle(ROOT.kFullTriangleDown)
HistogramC.SetMarkerSize(1.5)
HistogramC.SetMarkerColor(ROOT.kGreen)

HistogramC.SetLineColor(ROOT.kGreen)

if nV == 3:
    HistogramC.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 4:
    HistogramC.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramC.SetAxisRange(-0.02, 0.02, "Y")

HistogramC.Draw("PE 1 X0 SAME")

HistogramB = HistogramRootFile.Get("DataVnVsPtForDeuteronsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullCircle)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kBlue)

HistogramB.SetLineColor(ROOT.kBlue)

if nV == 3:
    HistogramB.SetAxisRange(-0.1, 0.1, "Y")
elif nV == 4:
    HistogramB.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramB.SetAxisRange(-0.02, 0.02, "Y")

HistogramB.Draw("PE 1 X0 SAME")


CanvasD119_120_121.Draw()

Legend119_120_121 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend119_120_121.AddEntry(HistogramA, "0-10% Centrality")
Legend119_120_121.AddEntry(HistogramB, "10-40% Centrality")
Legend119_120_121.AddEntry(HistogramC, "40-60% Centrality")
Legend119_120_121.Draw()

Canvasas.append(CanvasD119_120_121)





CanvasD122_123_124 = ROOT.TCanvas("CanvasD122_123_124", "", 800, 800)
CanvasD122_123_124.cd()

HistogramA = HistogramRootFile.Get("DataVnVsYForDeuteronsCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(3)
HistogramA.SetMarkerStyle(ROOT.kFullSquare)
HistogramA.SetMarkerSize(1.5)
HistogramA.SetMarkerColor(ROOT.kRed)

HistogramA.SetLineColor(ROOT.kRed)

# if nV == 2:
#     Histogram.SetAxisRange(-0.1, 0.2, "Y")
if nV == 3:
    HistogramA.SetAxisRange(-0.025, 0.005, "Y")
elif nV == 4:
    HistogramA.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramA.SetAxisRange(-0.02, 0.02, "Y")

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Red", Histogram.GetBinContent(i))

HistogramA.Draw("PE 1 X0")

HistogramC = HistogramRootFile.Get("DataVnVsYForDeuteronsCentrality40-60")

HistogramC.SetDirectory(0)

HistogramC.SetStats(0)

HistogramC.SetLineWidth(3)
HistogramC.SetMarkerStyle(ROOT.kFullTriangleDown)
HistogramC.SetMarkerSize(1.5)
HistogramC.SetMarkerColor(ROOT.kGreen)

HistogramC.SetLineColor(ROOT.kGreen)

# if nV == 2:
#     Histogram.SetAxisRange(-0.1, 0.2, "Y")
if nV == 3:
    HistogramC.SetAxisRange(-0.025, 0.005, "Y")
elif nV == 4:
    HistogramC.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramC.SetAxisRange(-0.02, 0.02, "Y")

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Green", Histogram.GetBinContent(i))

HistogramC.Draw("PE 1 X0 SAME")

HistogramB = HistogramRootFile.Get("DataVnVsYForDeuteronsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullCircle)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kBlue)

HistogramB.SetLineColor(ROOT.kBlue)

# if nV == 2:
#     Histogram.SetAxisRange(-0.1, 0.2, "Y")
if nV == 3:
    HistogramB.SetAxisRange(-0.025, 0.005, "Y")
elif nV == 4:
    HistogramB.SetAxisRange(-0.01, 0.01, "Y")
elif nV == 5:
    HistogramB.SetAxisRange(-0.02, 0.02, "Y")

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Blue", Histogram.GetBinContent(i))

HistogramB.Draw("PE 1 X0 SAME")

CanvasD122_123_124.Draw()

Legend122_123_124 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend122_123_124.AddEntry(HistogramA, "0-10% Centrality")
Legend122_123_124.AddEntry(HistogramB, "10-40% Centrality")
Legend122_123_124.AddEntry(HistogramC, "40-60% Centrality")
Legend122_123_124.Draw()

Canvasas.append(CanvasD122_123_124)






CanvasD125_126_127 = ROOT.TCanvas("CanvasD125_126_127", "", 800, 800)
CanvasD125_126_127.cd()

HistogramA = HistogramRootFile.Get("DataVnVsPtForTritonsCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(3)
HistogramA.SetMarkerStyle(ROOT.kFullSquare)
HistogramA.SetMarkerSize(1.5)
HistogramA.SetMarkerColor(ROOT.kRed)

HistogramA.SetLineColor(ROOT.kRed)

HistogramA.Draw("PE 1 X0")

if nV == 3:
    HistogramA.SetAxisRange(-0.05, 0.05, "Y")
elif nV == 4:
    HistogramA.SetAxisRange(-0.03, 0.02, "Y")
elif nV == 5:
    HistogramA.SetAxisRange(-0.1, 0.1, "Y")

HistogramC = HistogramRootFile.Get("DataVnVsPtForTritonsCentrality40-60")

HistogramC.SetDirectory(0)

HistogramC.SetStats(0)

HistogramC.SetLineWidth(3)
HistogramC.SetMarkerStyle(ROOT.kFullTriangleDown)
HistogramC.SetMarkerSize(1.5)
HistogramC.SetMarkerColor(ROOT.kGreen)

HistogramC.SetLineColor(ROOT.kGreen)

if nV == 3:
    HistogramC.SetAxisRange(-0.05, 0.05, "Y")
elif nV == 4:
    HistogramC.SetAxisRange(-0.03, 0.02, "Y")
elif nV == 5:
    HistogramC.SetAxisRange(-0.1, 0.1, "Y")

HistogramC.Draw("PE 1 X0 SAME")

HistogramB = HistogramRootFile.Get("DataVnVsPtForTritonsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullCircle)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kBlue)

HistogramB.SetLineColor(ROOT.kBlue)

if nV == 3:
    HistogramB.SetAxisRange(-0.05, 0.05, "Y")
elif nV == 4:
    HistogramB.SetAxisRange(-0.03, 0.02, "Y")
elif nV == 5:
    HistogramB.SetAxisRange(-0.1, 0.1, "Y")

HistogramB.Draw("PE 1 X0 SAME")

CanvasD125_126_127.Draw()

Legend125_126_127 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend125_126_127.AddEntry(HistogramA, "0-10% Centrality")
Legend125_126_127.AddEntry(HistogramB, "10-40% Centrality")
Legend125_126_127.AddEntry(HistogramC, "40-60% Centrality")
Legend125_126_127.Draw()

Canvasas.append(CanvasD125_126_127)





CanvasD128_129_130 = ROOT.TCanvas("CanvasD128_129_130", "", 800, 800)
CanvasD128_129_130.cd()

HistogramA = HistogramRootFile.Get("DataVnVsYForTritonsCentrality0-10")

HistogramA.SetDirectory(0)

HistogramA.SetStats(0)

HistogramA.SetLineWidth(3)
HistogramA.SetMarkerStyle(ROOT.kFullSquare)
HistogramA.SetMarkerSize(1.5)
HistogramA.SetMarkerColor(ROOT.kRed)

HistogramA.SetLineColor(ROOT.kRed)

# if nV == 2:
#     Histogram.SetAxisRange(-0.1, 0.4, "Y")
if nV == 3:
    HistogramA.SetAxisRange(-0.02, 0.04, "Y")
elif nV == 4:
    HistogramA.SetAxisRange(-0.03, 0.02, "Y")
elif nV == 5:
    HistogramA.SetAxisRange(-0.1, 0.1, "Y")

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Red", Histogram.GetBinContent(i))

HistogramA.Draw("PE 1 X0")

HistogramC = HistogramRootFile.Get("DataVnVsYForTritonsCentrality40-60")

HistogramC.SetDirectory(0)

HistogramC.SetStats(0)

HistogramC.SetLineWidth(3)
HistogramC.SetMarkerStyle(ROOT.kFullTriangleDown)
HistogramC.SetMarkerSize(1.5)
HistogramC.SetMarkerColor(ROOT.kGreen)

HistogramC.SetLineColor(ROOT.kGreen)

# if nV == 2:
#     Histogram.SetAxisRange(-0.1, 0.4, "Y")
if nV == 3:
    HistogramC.SetAxisRange(-0.02, 0.04, "Y")
elif nV == 4:
    HistogramC.SetAxisRange(-0.03, 0.02, "Y")
elif nV == 5:
    HistogramC.SetAxisRange(-0.1, 0.1, "Y")

# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Green", Histogram.GetBinContent(i))

HistogramC.Draw("PE 1 X0 SAME")

HistogramB = HistogramRootFile.Get("DataVnVsYForTritonsCentrality10-40")

HistogramB.SetDirectory(0)

HistogramB.SetStats(0)

HistogramB.SetLineWidth(3)
HistogramB.SetMarkerStyle(ROOT.kFullCircle)
HistogramB.SetMarkerSize(1.5)
HistogramB.SetMarkerColor(ROOT.kBlue)

HistogramB.SetLineColor(ROOT.kBlue)

# if nV == 2:
#     Histogram.SetAxisRange(-0.1, 0.4, "Y")
# elif nV == 3:
#     Histogram.SetAxisRange(-0.15, 0.1, "Y")
if nV == 3:
    HistogramB.SetAxisRange(-0.02, 0.04, "Y")
elif nV == 4:
    HistogramB.SetAxisRange(-0.03, 0.02, "Y")
elif nV == 5:
    HistogramB.SetAxisRange(-0.1, 0.1, "Y")
    
# for i in range(1, Histogram.GetNbinsX() + 1):
#     print("Blue", Histogram.GetBinContent(i))

HistogramB.Draw("PE 1 X0 SAME")

CanvasD128_129_130.Draw()

Legend128_129_130 = ROOT.TLegend(0.1, 0.1, 0.3, 0.2)
Legend128_129_130.AddEntry(HistogramA, "0-10% Centrality")
Legend128_129_130.AddEntry(HistogramB, "10-40% Centrality")
Legend128_129_130.AddEntry(HistogramC, "40-60% Centrality")
Legend128_129_130.Draw()

Canvasas.append(CanvasD128_129_130)
#####################################################################################################
# CanvasD27Through31 = ROOT.TCanvas("CanvasD27Through31")
# CanvasD27Through31.cd()

# CanvasD27Through31.Divide(3,2,0,0)


# CanvasD27Through31.cd(1)

# Histogram = HistogramRootFile.Get("DataPtVsYPionPlus")

# Histogram.SetDirectory(0)

# CanvasD27Through31.cd(1).SetLogz()

# Histogram.SetStats(0)
# Histogram.SetContour(1000)

# Histogram.SetTitle("")
# Histogram.SetXTitle("")
# Histogram.SetYTitle("")

# Histogram.Draw("colz")

# BoxA = ROOT.TBox(0, 0.18, 0.5, 1.6)
# BoxA.SetLineColor(ROOT.kRed)
# BoxA.SetLineWidth(2)
# BoxA.SetFillStyle(0)

# BoxA.Draw()

# CanvasD27Through31.cd(2)

# Histogram = HistogramRootFile.Get("DataPtVsYKaonPlus")

# Histogram.SetDirectory(0)

# CanvasD27Through31.cd(2).SetLogz()

# Histogram.SetStats(0)
# Histogram.SetContour(1000)

# Histogram.SetTitle("")
# Histogram.SetXTitle("")
# Histogram.SetYTitle("")

# Histogram.Draw("colz")

# BoxB = ROOT.TBox(0, 0.4, 0.5, 1.6)
# BoxB.SetLineColor(ROOT.kRed)
# BoxB.SetLineWidth(2)
# BoxB.SetFillStyle(0)

# BoxB.Draw()

# CanvasD27Through31.cd(4)

# Histogram = HistogramRootFile.Get("DataPtVsYPionMinus")

# Histogram.SetDirectory(0)

# CanvasD27Through31.cd(4).SetLogz()

# Histogram.SetStats(0)
# Histogram.SetContour(1000)

# Histogram.SetTitle("")
# Histogram.SetXTitle("")
# Histogram.SetYTitle("")

# Histogram.Draw("colz")

# BoxC = ROOT.TBox(0, 0.18, 0.5, 1.6)
# BoxC.SetLineColor(ROOT.kRed)
# BoxC.SetLineWidth(2)
# BoxC.SetFillStyle(0)

# BoxC.Draw()

# CanvasD27Through31.cd(5)

# Histogram = HistogramRootFile.Get("DataPtVsYKaonMinus")

# Histogram.SetDirectory(0)

# CanvasD27Through31.cd(5).SetLogz()

# Histogram.SetStats(0)
# Histogram.SetContour(1000)

# Histogram.SetTitle("")
# Histogram.SetXTitle("")
# Histogram.SetYTitle("")

# Histogram.Draw("colz")

# BoxD = ROOT.TBox(0, 0.4, 0.5, 1.6)
# BoxD.SetLineColor(ROOT.kRed)
# BoxD.SetLineWidth(2)
# BoxD.SetFillStyle(0)

# BoxD.Draw()

# CanvasD27Through31.cd(6)

# Histogram = HistogramRootFile.Get("DataPtVsYProton")

# Histogram.SetDirectory(0)

# CanvasD27Through31.cd(6).SetLogz()

# Histogram.SetStats(0)
# Histogram.SetContour(1000)

# Histogram.SetTitle("")
# Histogram.SetXTitle("")
# Histogram.SetYTitle("")

# Histogram.Draw("colz")

# BoxE = ROOT.TBox(0, 0.4, 0.5, 2.0)
# BoxE.SetLineColor(ROOT.kRed)
# BoxE.SetLineWidth(2)
# BoxE.SetFillStyle(0)

# BoxE.Draw()

# CanvasD27Through31.Draw()

# Canvasas.append(CanvasD27Through31)

# #####################################################################################################
# Histogram = HistogramRootFile.Get("MonteCarloPtVsEta")

# Histogram.SetDirectory(0)

# CanvasMC1 = ROOT.TCanvas("CanvasMC1", "", 800, 800)
# CanvasMC1.cd()

# CanvasMC1.SetLogz()

# Histogram.SetStats(0)
# Histogram.SetContour(1000)

# Histogram.Draw("colz")

# CanvasMC1.Draw()

# Canvasas.append(CanvasMC1)





# Histogram = HistogramRootFile.Get("MonteCarloYProton")

# Histogram.SetDirectory(0)

# CanvasMC2 = ROOT.TCanvas("CanvasMC2", "", 800, 800)
# CanvasMC2.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC2.Draw()

# Canvasas.append(CanvasMC2)





# Histogram = HistogramRootFile.Get("MonteCarloYKaon")

# Histogram.SetDirectory(0)

# CanvasMC3 = ROOT.TCanvas("CanvasMC3", "", 800, 800)
# CanvasMC3.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC3.Draw()

# Canvasas.append(CanvasMC3)





# Histogram = HistogramRootFile.Get("MonteCarloYPion")

# Histogram.SetDirectory(0)

# CanvasMC4 = ROOT.TCanvas("CanvasMC4", "", 800, 800)
# CanvasMC4.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC4.Draw()

# Canvasas.append(CanvasMC4)





# Histogram = HistogramRootFile.Get("MonteCarloPtProton")

# Histogram.SetDirectory(0)

# CanvasMC5 = ROOT.TCanvas("CanvasMC5", "", 800, 800)
# CanvasMC5.cd()

# CanvasMC5.SetLogy()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC5.Draw()

# Canvasas.append(CanvasMC5)





# Histogram = HistogramRootFile.Get("MonteCarloPtKaon")

# Histogram.SetDirectory(0)

# CanvasMC6 = ROOT.TCanvas("CanvasMC6", "", 800, 800)
# CanvasMC6.cd()

# CanvasMC6.SetLogy()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC6.Draw()

# Canvasas.append(CanvasMC6)




# Histogram = HistogramRootFile.Get("MonteCarloPtPion")

# Histogram.SetDirectory(0)

# CanvasMC7 = ROOT.TCanvas("CanvasMC7", "", 800, 800)
# CanvasMC7.cd()

# CanvasMC7.SetLogy()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC7.Draw()

# Canvasas.append(CanvasMC7)





# Histogram = HistogramRootFile.Get("MonteCarloImpactParameter")

# Histogram.SetDirectory(0)

# CanvasMC8 = ROOT.TCanvas("CanvasMC8", "", 800, 800)
# CanvasMC8.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC8.Draw()

# Canvasas.append(CanvasMC8)





# Histogram = HistogramRootFile.Get("MonteCarloImpactParameterFlattened")

# Histogram.SetDirectory(0)

# CanvasMC8A = ROOT.TCanvas("CanvasMC8A", "", 800, 800)
# CanvasMC8A.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC8A.Draw()

# Canvasas.append(CanvasMC8A)





# Histogram = HistogramRootFile.Get("MonteCarloMultiplicityVsImpactParameter")

# Histogram.SetDirectory(0)

# CanvasMC9 = ROOT.TCanvas("CanvasMC9", "", 800, 800)
# CanvasMC9.cd()

# CanvasMC9.SetLogz()

# Histogram.SetStats(0)
# Histogram.SetContour(1000)

# Histogram.Draw("colz")

# CanvasMC9.Draw()

# Canvasas.append(CanvasMC9)





# Histogram = HistogramRootFile.Get("MonteCarloPhi")

# Histogram.SetDirectory(0)

# CanvasMC10 = ROOT.TCanvas("CanvasMC10", "", 800, 800)
# CanvasMC10.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC10.Draw()

# Canvasas.append(CanvasMC10)





# Histogram = HistogramRootFile.Get("MonteCarloReactionPlanePsi1Angle")

# Histogram.SetDirectory(0)

# CanvasMC11 = ROOT.TCanvas("CanvasMC11", "", 800, 800)
# CanvasMC11.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC11.Draw()

# Canvasas.append(CanvasMC11)





# Histogram = HistogramRootFile.Get("MonteCarloReactionPlanePsi2Angle")

# Histogram.SetDirectory(0)

# CanvasMC12 = ROOT.TCanvas("CanvasMC12", "", 800, 800)
# CanvasMC12.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC12.Draw()

# Canvasas.append(CanvasMC12)





# Histogram = HistogramRootFile.Get("MonteCarloReactionPlanePsi3Angle")

# Histogram.SetDirectory(0)

# CanvasMC13 = ROOT.TCanvas("CanvasMC13", "", 800, 800)
# CanvasMC13.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC13.Draw()

# Canvasas.append(CanvasMC13)





# Histogram = HistogramRootFile.Get("MonteCarloV1VsYProtonNoPsi")

# Histogram.SetDirectory(0)

# CanvasMC14 = ROOT.TCanvas("CanvasMC14", "", 800, 800)
# CanvasMC14.cd()

# Histogram.SetAxisRange(-0.1, 0.1, "Y")

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC14.Draw()

# Canvasas.append(CanvasMC14)





# Histogram = HistogramRootFile.Get("MonteCarloV1VsYKaonPlusNoPsi")

# Histogram.SetDirectory(0)

# CanvasMC15 = ROOT.TCanvas("CanvasMC15", "", 800, 800)
# CanvasMC15.cd()

# Histogram.SetAxisRange(-0.1, 0.1, "Y")

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC15.Draw()

# Canvasas.append(CanvasMC15)





# Histogram = HistogramRootFile.Get("MonteCarloV1VsYPionPlusNoPsi")

# Histogram.SetDirectory(0)

# CanvasMC16 = ROOT.TCanvas("CanvasMC16", "", 800, 800)
# CanvasMC16.cd()

# Histogram.SetAxisRange(-0.1, 0.1, "Y")

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC16.Draw()

# Canvasas.append(CanvasMC16)





# Histogram = HistogramRootFile.Get("MonteCarloV1VsYAllNoPsi")

# Histogram.SetDirectory(0)

# CanvasMC17 = ROOT.TCanvas("CanvasMC17", "", 800, 800)
# CanvasMC17.cd()

# Histogram.SetAxisRange(-0.1, 0.1, "Y")

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC17.Draw()

# Canvasas.append(CanvasMC17)





# Histogram = HistogramRootFile.Get("MonteCarloV1VsYProton")

# Histogram.SetDirectory(0)

# CanvasMC18 = ROOT.TCanvas("CanvasMC18", "", 800, 800)
# CanvasMC18.cd()

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC18.Draw()

# Canvasas.append(CanvasMC18)





# Histogram = HistogramRootFile.Get("MonteCarloV1VsYKaonPlus")

# Histogram.SetDirectory(0)

# CanvasMC19 = ROOT.TCanvas("CanvasMC19", "", 800, 800)
# CanvasMC19.cd()

# Histogram.SetAxisRange(-0.1, 0.1, "Y")

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC19.Draw()

# Canvasas.append(CanvasMC19)





# Histogram = HistogramRootFile.Get("MonteCarloV1VsYPionPlus")

# Histogram.SetDirectory(0)

# CanvasMC20 = ROOT.TCanvas("CanvasMC20", "", 800, 800)
# CanvasMC20.cd()

# Histogram.SetAxisRange(-0.1, 0.1, "Y")

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC20.Draw()

# Canvasas.append(CanvasMC20)





# Histogram = HistogramRootFile.Get("MonteCarloV1VsYAll")

# Histogram.SetDirectory(0)

# CanvasMC21 = ROOT.TCanvas("CanvasMC21", "", 800, 800)
# CanvasMC21.cd()

# Histogram.SetAxisRange(-0.1, 0.1, "Y")

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasMC21.Draw()

# Canvasas.append(CanvasMC21)
# ############################################################################################################################################
# CanvasD5_6_7_HC_2_3_4 = ROOT.TCanvas("CanvasD5_6_7_HC_2_3_4")
# CanvasD5_6_7_HC_2_3_4.cd()

# CanvasD5_6_7_HC_2_3_4.Divide(3,2,0,0)


# CanvasD5_6_7_HC_2_3_4.cd(1)

# Histogram = HistogramRootFile.Get("DataYProton")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD5_6_7_HC_2_3_4.cd(2)

# Histogram = HistogramRootFile.Get("DataYKaon")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD5_6_7_HC_2_3_4.cd(3)

# Histogram = HistogramRootFile.Get("DataYPion")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD5_6_7_HC_2_3_4.cd(4)

# Histogram = HistogramRootFile.Get("MonteCarloYProton")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD5_6_7_HC_2_3_4.cd(5)

# Histogram = HistogramRootFile.Get("MonteCarloYKaon")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD5_6_7_HC_2_3_4.cd(6)

# Histogram = HistogramRootFile.Get("MonteCarloYPion")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD5_6_7_HC_2_3_4.Draw()

# Canvasas.append(CanvasD5_6_7_HC_2_3_4)





# CanvasD8_9_10_HC_5_6_7 = ROOT.TCanvas("CanvasD8_9_10_HC_5_6_7")
# CanvasD8_9_10_HC_5_6_7.cd()

# CanvasD8_9_10_HC_5_6_7.Divide(3,2,0,0)


# CanvasD8_9_10_HC_5_6_7.cd(1)

# CanvasD8_9_10_HC_5_6_7.SetLogy(1)

# Histogram = HistogramRootFile.Get("DataPtProton")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD8_9_10_HC_5_6_7.cd(2)

# CanvasD8_9_10_HC_5_6_7.SetLogy()

# Histogram = HistogramRootFile.Get("DataPtKaon")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD8_9_10_HC_5_6_7.cd(3)

# CanvasD8_9_10_HC_5_6_7.SetLogy()

# Histogram = HistogramRootFile.Get("DataPtPion")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD8_9_10_HC_5_6_7.cd(4)

# CanvasD8_9_10_HC_5_6_7.SetLogy()

# Histogram = HistogramRootFile.Get("MonteCarloPtProton")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD8_9_10_HC_5_6_7.cd(5)

# CanvasD8_9_10_HC_5_6_7.SetLogy()

# Histogram = HistogramRootFile.Get("MonteCarloPtKaon")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD8_9_10_HC_5_6_7.cd(6)

# CanvasD8_9_10_HC_5_6_7.SetLogy()

# Histogram = HistogramRootFile.Get("MonteCarloPtPion")

# Histogram.SetDirectory(0)

# Histogram.SetStats(0)

# Histogram.Draw("HIST")

# CanvasD8_9_10_HC_5_6_7.Draw()

# Canvasas.append(CanvasD8_9_10_HC_5_6_7)
# ##################################################################################

# ProtonMass = 0.938
# KaonMass = 0.494
# PionMass = 0.140


# CanvasG1 = ROOT.TCanvas("CanvasG1", "", 800, 800)
# CanvasG1.cd()

# CanvasG1.Divide(4,2,0,0)

# Mass = ProtonMass

# CanvasG1.cd(1)

# Graph1 = ROOT.TGraph()

# pt = 0.2

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph1.AddPoint(eta, Y)

# Graph1.SetTitle("Y vs Eta for Protons (Pt = 0.2); Eta; Y")

# Graph1.Draw()

# CanvasG1.cd(2)

# Graph2 = ROOT.TGraph()

# pt = 0.5

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph2.AddPoint(eta, Y)

# Graph2.SetTitle("Y vs Eta for Protons (Pt = 0.5); Eta; Y")

# Graph2.Draw()

# CanvasG1.cd(3)

# Graph3 = ROOT.TGraph()

# pt = 1.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph3.AddPoint(eta, Y)

# Graph3.SetTitle("Y vs Eta for Protons (Pt = 1.0); Eta; Y")

# Graph3.Draw()

# CanvasG1.cd(4)

# Graph4 = ROOT.TGraph()

# pt = 1.5

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph4.AddPoint(eta, Y)

# Graph4.SetTitle("Y vs Eta for Protons (Pt = 1.5); Eta; Y")

# Graph4.Draw()

# CanvasG1.cd(5)

# Graph5 = ROOT.TGraph()

# pt = 2.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph5.AddPoint(eta, Y)

# Graph5.SetTitle("Y vs Eta for Protons (Pt = 2.0); Eta; Y")

# Graph5.Draw()

# CanvasG1.cd(6)

# Graph6 = ROOT.TGraph()

# pt = 3.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph6.AddPoint(eta, Y)

# Graph6.SetTitle("Y vs Eta for Protons (Pt = 3.0); Eta; Y")

# Graph6.Draw()

# CanvasG1.cd(7)

# Graph7 = ROOT.TGraph()

# pt = 5.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph7.AddPoint(eta, Y)

# Graph7.SetTitle("Y vs Eta for Protons (Pt = 5.0); Eta; Y")

# Graph7.Draw()

# CanvasG1.Draw()

# Canvasas.append(CanvasG1)





# CanvasG2 = ROOT.TCanvas("CanvasG2", "", 800, 800)
# CanvasG2.cd()

# CanvasG2.Divide(4,2,0,0)

# Mass = KaonMass

# CanvasG2.cd(1)

# Graph8 = ROOT.TGraph()

# pt = 0.2

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph8.AddPoint(eta, Y)

# Graph8.SetTitle("Y vs Eta for Kaons (Pt = 0.2); Eta; Y")

# Graph8.Draw()

# CanvasG2.cd(2)

# Graph9 = ROOT.TGraph()

# pt = 0.5

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph9.AddPoint(eta, Y)

# Graph9.SetTitle("Y vs Eta for Kaons (Pt = 0.5); Eta; Y")

# Graph9.Draw()

# CanvasG2.cd(3)

# Graph10 = ROOT.TGraph()

# pt = 1.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph10.AddPoint(eta, Y)

# Graph10.SetTitle("Y vs Eta for Kaons (Pt = 1.0); Eta; Y")

# Graph10.Draw()

# CanvasG2.cd(4)

# Graph11 = ROOT.TGraph()

# pt = 1.5

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph11.AddPoint(eta, Y)

# Graph11.SetTitle("Y vs Eta for Kaons (Pt = 1.5); Eta; Y")

# Graph11.Draw()

# CanvasG2.cd(5)

# Graph12 = ROOT.TGraph()

# pt = 2.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph12.AddPoint(eta, Y)

# Graph12.SetTitle("Y vs Eta for Kaons (Pt = 2.0); Eta; Y")

# Graph12.Draw()

# CanvasG2.cd(6)

# Graph13 = ROOT.TGraph()

# pt = 3.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph13.AddPoint(eta, Y)

# Graph13.SetTitle("Y vs Eta for Kaons (Pt = 3.0); Eta; Y")

# Graph13.Draw()

# CanvasG2.cd(7)

# Graph14 = ROOT.TGraph()

# pt = 5.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph14.AddPoint(eta, Y)

# Graph14.SetTitle("Y vs Eta for Kaons (Pt = 5.0); Eta; Y")

# Graph14.Draw()

# CanvasG2.Draw()

# Canvasas.append(CanvasG2)






# CanvasG3 = ROOT.TCanvas("CanvasG3", "", 800, 800)
# CanvasG3.cd()

# CanvasG3.Divide(4,2,0,0)

# Mass = PionMass

# CanvasG3.cd(1)

# Graph15 = ROOT.TGraph()

# pt = 0.2

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph15.AddPoint(eta, Y)

# Graph15.SetTitle("Y vs Eta for Pions (Pt = 0.2); Eta; Y")

# Graph15.Draw()

# CanvasG3.cd(2)

# Graph16 = ROOT.TGraph()

# pt = 0.5

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph16.AddPoint(eta, Y)

# Graph16.SetTitle("Y vs Eta for Pions (Pt = 0.5); Eta; Y")

# Graph16.Draw()

# CanvasG3.cd(3)

# Graph17 = ROOT.TGraph()

# pt = 1.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph17.AddPoint(eta, Y)

# Graph17.SetTitle("Y vs Eta for Pions (Pt = 1.0); Eta; Y")

# Graph17.Draw()

# CanvasG3.cd(4)

# Graph18 = ROOT.TGraph()

# pt = 1.5

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph18.AddPoint(eta, Y)

# Graph18.SetTitle("Y vs Eta for Pions (Pt = 1.5); Eta; Y")

# Graph18.Draw()

# CanvasG3.cd(5)

# Graph19 = ROOT.TGraph()

# pt = 2.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph19.AddPoint(eta, Y)

# Graph19.SetTitle("Y vs Eta for Pions (Pt = 2.0); Eta; Y")

# Graph19.Draw()

# CanvasG3.cd(6)

# Graph20 = ROOT.TGraph()

# pt = 3.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph20.AddPoint(eta, Y)

# Graph20.SetTitle("Y vs Eta for Pions (Pt = 3.0); Eta; Y")

# Graph20.Draw()

# CanvasG3.cd(7)

# Graph21 = ROOT.TGraph()

# pt = 5.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(pt,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph21.AddPoint(eta, Y)

# Graph21.SetTitle("Y vs Eta for Pions (Pt = 5.0); Eta; Y")

# Graph21.Draw()

# CanvasG3.Draw()

# Canvasas.append(CanvasG3)






# CanvasG4 = ROOT.TCanvas("CanvasG4", "", 800, 800)
# CanvasG4.cd()

# CanvasG4.Divide(4,2,0,0)

# Mass = ProtonMass

# CanvasG4.cd(1)

# Graph22 = ROOT.TGraph()

# mt = 1.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph22.AddPoint(eta, Y)

# Graph22.SetTitle("Y vs Eta for Protons (mt = 1.0); Eta; Y")

# Graph22.Draw()

# CanvasG4.cd(2)

# Graph23 = ROOT.TGraph()

# mt = 1.5

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph23.AddPoint(eta, Y)

# Graph23.SetTitle("Y vs Eta for Protons (mt = 1.5); Eta; Y")

# Graph23.Draw()

# CanvasG4.cd(3)

# Graph24 = ROOT.TGraph()

# mt = 2.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph24.AddPoint(eta, Y)

# Graph24.SetTitle("Y vs Eta for Protons (mt = 2.0); Eta; Y")

# Graph24.Draw()

# CanvasG4.cd(4)

# Graph25 = ROOT.TGraph()

# mt = 2.5

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph25.AddPoint(eta, Y)

# Graph25.SetTitle("Y vs Eta for Protons (mt = 2.5); Eta; Y")

# Graph25.Draw()

# CanvasG4.cd(5)

# Graph26 = ROOT.TGraph()

# mt = 3.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph26.AddPoint(eta, Y)

# Graph26.SetTitle("Y vs Eta for Protons (mt = 3.0); Eta; Y")

# Graph26.Draw()

# CanvasG4.cd(6)

# Graph27 = ROOT.TGraph()

# mt = 4.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph27.AddPoint(eta, Y)

# Graph27.SetTitle("Y vs Eta for Protons (mt = 4.0); Eta; Y")

# Graph27.Draw()

# CanvasG4.cd(7)

# Graph28 = ROOT.TGraph()

# mt = 5.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph28.AddPoint(eta, Y)

# Graph28.SetTitle("Y vs Eta for Protons (mt = 5.0); Eta; Y")

# Graph28.Draw()

# CanvasG4.Draw()

# Canvasas.append(CanvasG4)





# CanvasG5 = ROOT.TCanvas("CanvasG5", "", 800, 800)
# CanvasG5.cd()

# CanvasG5.Divide(4,2,0,0)

# Mass = KaonMass

# CanvasG5.cd(1)

# Graph29 = ROOT.TGraph()

# mt = 1.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph29.AddPoint(eta, Y)

# Graph29.SetTitle("Y vs Eta for Kaons (mt = 1.0); Eta; Y")

# Graph29.Draw()

# CanvasG5.cd(2)

# Graph30 = ROOT.TGraph()

# mt = 1.5

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph30.AddPoint(eta, Y)

# Graph30.SetTitle("Y vs Eta for Kaons (mt = 1.5); Eta; Y")

# Graph30.Draw()

# CanvasG5.cd(3)

# Graph31 = ROOT.TGraph()

# mt = 2.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph31.AddPoint(eta, Y)

# Graph31.SetTitle("Y vs Eta for Kaons (mt = 2.0); Eta; Y")

# Graph31.Draw()

# CanvasG5.cd(4)

# Graph32 = ROOT.TGraph()

# mt = 2.5

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph32.AddPoint(eta, Y)

# Graph32.SetTitle("Y vs Eta for Kaons (mt = 2.5); Eta; Y")

# Graph32.Draw()

# CanvasG5.cd(5)

# Graph33 = ROOT.TGraph()

# mt = 3.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph33.AddPoint(eta, Y)

# Graph33.SetTitle("Y vs Eta for Kaons (mt = 3.0); Eta; Y")

# Graph33.Draw()

# CanvasG5.cd(6)

# Graph34 = ROOT.TGraph()

# mt = 4.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph34.AddPoint(eta, Y)

# Graph34.SetTitle("Y vs Eta for Kaons (mt = 4.0); Eta; Y")

# Graph34.Draw()

# CanvasG5.cd(7)

# Graph35 = ROOT.TGraph()

# mt = 5.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph35.AddPoint(eta, Y)

# Graph35.SetTitle("Y vs Eta for Kaons (mt = 5.0); Eta; Y")

# Graph35.Draw()

# CanvasG5.Draw()

# Canvasas.append(CanvasG5)





# CanvasG6 = ROOT.TCanvas("CanvasG6", "", 800, 800)
# CanvasG6.cd()

# CanvasG6.Divide(4,2,0,0)

# Mass = PionMass

# CanvasG6.cd(1)

# Graph36 = ROOT.TGraph()

# mt = 1.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph36.AddPoint(eta, Y)

# Graph36.SetTitle("Y vs Eta for Pions (mt = 1.0); Eta; Y")

# Graph36.Draw()

# CanvasG6.cd(2)

# Graph37 = ROOT.TGraph()

# mt = 1.5

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph37.AddPoint(eta, Y)

# Graph37.SetTitle("Y vs Eta for Pions (mt = 1.5); Eta; Y")

# Graph37.Draw()

# CanvasG6.cd(3)

# Graph38 = ROOT.TGraph()

# mt = 2.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph38.AddPoint(eta, Y)

# Graph38.SetTitle("Y vs Eta for Pions (mt = 2.0); Eta; Y")

# Graph38.Draw()

# CanvasG6.cd(4)

# Graph39 = ROOT.TGraph()

# mt = 1.5

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph39.AddPoint(eta, Y)

# Graph39.SetTitle("Y vs Eta for Pions (mt = 2.5); Eta; Y")

# Graph39.Draw()

# CanvasG6.cd(5)

# Graph40 = ROOT.TGraph()

# mt = 3.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph40.AddPoint(eta, Y)

# Graph40.SetTitle("Y vs Eta for Pions (mt = 3.0); Eta; Y")

# Graph40.Draw()

# CanvasG6.cd(6)

# Graph41 = ROOT.TGraph()

# mt = 4.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph41.AddPoint(eta, Y)

# Graph41.SetTitle("Y vs Eta for Pions (mt = 4.0); Eta; Y")

# Graph41.Draw()

# CanvasG6.cd(7)

# Graph42 = ROOT.TGraph()

# mt = 5.0

# for pzTimesTen in range(0,50,1):

#     pz = pzTimesTen / 10

#     p = sqrt(pow(mt,2) - pow(Mass,2) + pow(pz,2))

#     eta = 0.5*log((p + pz)/(p - pz))

#     Energy = sqrt(pow(p,2) + pow(Mass, 2))

#     Y = atanh(pz/Energy)

#     Graph42.AddPoint(eta, Y)

# Graph42.SetTitle("Y vs Eta for Pions (mt = 5.0); Eta; Y")

# Graph42.Draw()

# CanvasG6.Draw()

# Canvasas.append(CanvasG6)



# Close the output Root file
# ResolutionRootFile.Close()
HistogramRootFile.Close()
# SystematicErrorRootFile.Close()





# This box prints the histograms to a pdf file

for index in range(0, len(Canvasas)):
    if len(Canvasas) == 1:
        Canvasas[index].SaveAs(Date + '_V' + str(nV) + '_Plots.pdf)')
        #Canvasas[index].SaveAs("HistogramTest.pdf)")
        break
    
    if index == 0:
        print("Opening PDF")
        Canvasas[index].SaveAs(Date + '_V' + str(nV) + '_Plots.pdf(')
        #Canvasas[index].SaveAs("HistogramTest.pdf(")
    
    elif index == len(Canvasas) - 1:
        print("Closing PDF")
        Canvasas[index].SaveAs(Date + '_V' + str(nV) + '_Plots.pdf)')
        #Canvasas[index].SaveAs("HistogramTest.pdf)")
    
    else:
        Canvasas[index].SaveAs(Date + '_V' + str(nV) + '_Plots.pdf')
        #Canvasas[index].SaveAs("HistogramTest.pdf")


# In[ ]:




