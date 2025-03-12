import os
import glob

nV = 3
OrdinalPassNumber = "Fourth"
Date = "1-27-25"

#Files = glob.glob("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/QVector" + OrdinalPassNumber + "PassNormal*.root")
#Files = glob.glob("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/Histogram" + OrdinalPassNumber + "PassNormal*_*.root")
Files = glob.glob("/star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/Histogram*PassNormal.root")
#Files = glob.glob("/star/u/mcgordon/VnFromEPD/Histogram*PassTest.root")

FileNameString = ""

for file in Files:
	FileNameString = FileNameString + file + " "

os.environ["FileNameString"] = FileNameString

#command = "hadd -f /star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/QVector" + OrdinalPassNumber + "PassNormal.root $FileNameString"
#command = "hadd -f /star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/Histogram" + OrdinalPassNumber + "PassNormal.root $FileNameString"
command = "hadd -f /star/data01/pwg/mcgordon/VnFromEPD/V" + str(nV) + "Histograms/" + Date + "-V" + str(nV) + "-HistogramNormal.root $FileNameString"
#command = "hadd -f /star/u/mcgordon/VnFromEPD/HistogramTest.root $FileNameString"

os.system(command)
