DY_0="DY"
DY='"'$DY_0'"'
ZH_0="ZH"
ZH='"'$ZH_0'"'
NoSel_0="NoSel"
NoSel='"'$NoSel_0'"'
NoPair_0="NoPair"
NoPair='"'$NoPair_0'"'
OffZ_0="OffZ"
OffZ='"'$OffZ_0'"'
CRHeavy_0="CRHeavy"
CRHeavy='"'$CRHeavy_0'"'
CRLight_0="CRLight"
CRLight='"'$CRLight_0'"'

root -l -b -q  "plotter_stackedRegion.C($DY, kTRUE, kTRUE)"
root -l -b -q  "plotter_stackedRegion.C($DY, kTRUE, kFALSE)"
root -l -b -q  "plotter_stackedRegion.C($DY, kFALSE, kTRUE)"
root -l -b -q  "plotter_stackedRegion.C($DY, kFALSE, kFALSE)"

root -l -b -q  "plotter_stackedRegion.C($ZH, kTRUE, kTRUE)"
root -l -b -q  "plotter_stackedRegion.C($ZH, kTRUE, kFALSE)"
root -l -b -q  "plotter_stackedRegion.C($ZH, kFALSE, kTRUE)"
root -l -b -q  "plotter_stackedRegion.C($ZH, kFALSE, kFALSE)"

root -l -b -q  "plotter_stackedRegion.C($NoSel, kTRUE, kTRUE)"
root -l -b -q  "plotter_stackedRegion.C($NoSel, kTRUE, kFALSE)"
root -l -b -q  "plotter_stackedRegion.C($NoSel, kFALSE, kTRUE)"
root -l -b -q  "plotter_stackedRegion.C($NoSel, kFALSE, kFALSE)"

root -l -b -q  "plotter_stackedRegion.C($NoPair, kTRUE, kTRUE)"
root -l -b -q  "plotter_stackedRegion.C($NoPair, kTRUE, kFALSE)"
root -l -b -q  "plotter_stackedRegion.C($NoPair, kFALSE, kTRUE)"
root -l -b -q  "plotter_stackedRegion.C($NoPair, kFALSE, kFALSE)"

root -l -b -q  "plotter_stackedRegion.C($OffZ, kTRUE, kTRUE)"
root -l -b -q  "plotter_stackedRegion.C($OffZ, kTRUE, kFALSE)"
root -l -b -q  "plotter_stackedRegion.C($OffZ, kFALSE, kTRUE)"
root -l -b -q  "plotter_stackedRegion.C($OffZ, kFALSE, kFALSE)"

root -l -b -q  "plotter_stackedRegion.C($CRHeavy, kTRUE, kTRUE)"
root -l -b -q  "plotter_stackedRegion.C($CRHeavy, kTRUE, kFALSE)"
root -l -b -q  "plotter_stackedRegion.C($CRHeavy, kFALSE, kTRUE)"
root -l -b -q  "plotter_stackedRegion.C($CRHeavy, kFALSE, kFALSE)"

root -l -b -q  "plotter_stackedRegion.C($CRLight, kTRUE, kTRUE)"
root -l -b -q  "plotter_stackedRegion.C($CRLight, kTRUE, kFALSE)"
root -l -b -q  "plotter_stackedRegion.C($CRLight, kFALSE, kTRUE)"
root -l -b -q  "plotter_stackedRegion.C($CRLight, kFALSE, kFALSE)"
