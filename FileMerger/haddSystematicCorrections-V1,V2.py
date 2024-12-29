import subprocess
import os.path
import glob


nV = 2
PassNumber = 5
PassOrdinalNumber = "Fifth"
Date = "11-19-24"


Variations = [
              "DCA1",
              "DCA2",
              "NHits1",
              "NHits2",
              "NSigmaProton1",
              "NSigmaProton2",
              "NSigmaKaon1",
              "NSigmaKaon2",
              "NSigmaPion1",
              "NSigmaPion2",
              "MSquaredProton",
              "MSquaredKaon",
              "MSquaredPion",
              "OuterEPDLow",
              "OuterEPDHigh"
            ]


if (PassNumber <= 4):
    for variation in Variations:
        Files = ""
        Files = glob.glob("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/Histogram" + PassOrdinalNumber + "Pass" + variation + "*.root")

        FileNameString = ""

        for file in Files:
            FileNameString = FileNameString + file + " "

        os.environ["FileNameString"] = FileNameString

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
