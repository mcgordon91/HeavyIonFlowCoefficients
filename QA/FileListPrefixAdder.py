infile = open('QAPicoDST32BitFileList.txt', 'r')
outfile = open('QAPicoDST32BitFileListModified.txt', 'w')

for line in infile:
    line = line.rstrip()

    outfile.write('root://xrdstar.rcf.bnl.gov:1095/' + line + '\n')

infile.close()
outfile.close()

