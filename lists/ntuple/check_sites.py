import sys,os

listfile = open("dasmapAOD.list", "r")
    
for line in listfile:
    values = line.split()

    for value in values:
        if "/AOD" in value:
            output = os.popen('dasgoclient -query="site dataset='+value+'"').read()
            if "T2_" not in output and "T3_" not in output:
                print value
