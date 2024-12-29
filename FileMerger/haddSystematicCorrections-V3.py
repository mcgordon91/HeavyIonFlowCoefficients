import subprocess
import os.path
import glob


nV = 3
PassNumber = 4
PassOrdinalNumber = "Fourth"
Date = "12-16-24"


Variations = [
#               "RVertex20Low",
#               "RVertex20High",
#               "ZVertex20Low",
#               "ZVertex20High",
#               "DCA20Low",
#               "DCA20High",
#               "NHits20Low",
#               "NHits20High",
#               "NHitsFitOverNHitsPoss20Low",
#               "NHitsFitOverNHitsPoss20High",
#               "NHitsdEdx20High",
#               "NSigmaProton20Low",
#               "NSigmaProton20High",
#               "NSigmaKaon20Low",
#               "NSigmaKaon20High",
#               "NSigmaPion20Low",
#               "NSigmaPion20High",
#               "MSquaredKaon20Low",
#               "MSquaredKaon20High",
#               "MSquaredPion20Low",
#               "MSquaredPion20High",
#               "RVertex30Low",
#               "RVertex30High",
#               "ZVertex30Low",
#               "ZVertex30High",
#               "DCA30Low",
#               "DCA30High",
#               "NHits30Low",
#               "NHits30High",
#               "NHitsFitOverNHitsPoss30Low",
#               "NHitsFitOverNHitsPoss30High",
#               "NHitsdEdx30High",
#               "NSigmaProton30Low",
#               "NSigmaProton30High",
#               "NSigmaKaon30Low",
#               "NSigmaKaon30High",
#               "NSigmaPion30Low",
#               "NSigmaPion30High",
#               "MSquaredKaon30Low",
#               "MSquaredKaon30High",
#               "MSquaredPion30Low",
#               "MSquaredPion30High",
              "OuterEPDLow",
              "OuterEPDHigh"
            ]


if (PassNumber <= 4):
    for variation in Variations:
        Files = ""
        Files = glob.glob("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/Histogram" + PassOrdinalNumber + "Pass" + variation + "*_*.root")

        FileNameString = ""

        for file in Files:
            FileNameString = FileNameString + file + " "

        os.environ["FileNameString"] = FileNameString

        #command = "hadd -f /star/u/mcgordon/SystematicsCameronResolution/Histogram" + PassOrdinalNumber + "Pass" + variation + ".root $FileNameString"
        command = "hadd -f /star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/Histogram" + PassOrdinalNumber + "Pass" + variation + ".root $FileNameString"

        sp = subprocess.Popen(command, shell=True)
        sp.communicate()
            
            
            
if (PassNumber <= 2):
    for variation in Variations:
        Files = ""
        Files = glob.glob("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/QVector" + PassOrdinalNumber + "Pass" + variation + "*.root")

        FileNameString = ""

        for file in Files:
            FileNameString = FileNameString + file + " "

        os.environ["FileNameString"] = FileNameString
        
        cmd = "hadd -f /star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/QVector" + PassOrdinalNumber + "Pass" + variation + ".root $FileNameString"
    
        sp = subprocess.Popen(cmd, shell=True)
        sp.communicate()
            
            
            
if (PassNumber == 5):
    for variation in Variations:
#         if os.path.isfile("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/HistogramFourthPass" + variation + ".root"):
        cmd = "hadd -f /star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + Date + "-V" + str(nV) +"-Histogram" + variation +".root /star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/Histogram*Pass" + variation + ".root"
        sp = subprocess.Popen(cmd, shell=True)
        sp.communicate()

print("Done!")
