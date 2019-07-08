from array import array
import os, sys, re
from string import *
from glob import glob
from array import array
from ROOT import *

#-------------------------------------------------------------------------------
gStyle.SetOptStat(0)
filename = 'EleLeg2.txt'
errname = 'ErrorEleLeg2.txt'
title = filename[:-4]
if filename[:3] == 'Ele':
	determ = 0
else:
	determ = 1
if determ == 0:	
	xbins = array('f',[-2.5,-2.2,-1.8,-1.6,-1.45,-.8,0,.8,1.45,1.6,1.8,2.2,2.5])
	ybins = array('f',[15,22,25,30,35,40,50,60,70,80,100,120,200])
else:	
	ybins = array('f',[12,25,30,40,50,60,120])
	xbins = array('f',[-2.4,-2.1,-1.2,-0.9,.9,1.2,2.1,2.4])
records = map(lambda x: map(atof, x),
                  map(split, open(filename).readlines()[:]))
print(records)
errecords=map(lambda x: map(atof, x),
                  map(split, open(errname).readlines()[:])) 
xloop = len(xbins)-1
yloop = len(ybins)-1
_file0 = TFile.Open('rootfiles/%s.root' %title, "recreate")
TrigHist = TH2F("TrigEffi","Trigger Efficiency with error for %s"%filename,xloop,xbins,yloop,ybins)

for j in range(yloop):
	for i in range(xloop):
		if determ == 0:
	
			TrigHist.SetBinContent(i+1,j+1,records[j][i])
			TrigHist.SetBinError(i+1,j+1,errecords[j][i])
		else:
			TrigHist.SetBinContent(i+1,j+1,records[i][j])
			TrigHist.SetBinError(i+1,j+1,errecords[i][j])
TrigHist.SetEntries(1)
TrigHist.Draw("hist")
TrigHist.GetYaxis().SetTitle("pt (GeV)")
TrigHist.GetXaxis().SetTitle("#eta")
TrigHist.Write()
_file0.Close() 

