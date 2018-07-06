

 # region, lepname, varname, dolog, HIP

root -l -b -q  'plotter_singleMerged.C("ZH", "ele", "AllJets_AODCaloJetPt", kFALSE, kFALSE)'
root -l -b -q  'plotter_singleMerged.C("ZH", "mu", "AllJets_AODCaloJetPt", kFALSE, kFALSE)'

root -l -b -q  'plotter_singleMerged.C("OffZ", "ele", "AllJets_AODCaloJetPt", kFALSE, kFALSE)'
root -l -b -q  'plotter_singleMerged.C("OffZ", "mu", "AllJets_AODCaloJetPt", kFALSE, kFALSE)'

root -l -b -q  'plotter_singleMerged.C("DY", "ele", "AllJets_AODCaloJetPt", kFALSE, kFALSE)'
root -l -b -q  'plotter_singleMerged.C("DY", "mu", "AllJets_AODCaloJetPt", kFALSE, kFALSE)'

#root -l -b -q  'plotter_singleMerged.C("ZH", kTRUE, kTRUE)'
#root -l -b -q  'plotter_singleMerged.C("ZH", kTRUE, kFALSE)'
#root -l -b -q  'plotter_singleMerged.C("ZH", kFALSE, kTRUE)'
#root -l -b -q  'plotter_singleMerged.C("ZH", kFALSE, kFALSE)'
#
#root -l -b -q  'plotter_singleMerged.C("NoSel", kTRUE, kTRUE)'
#root -l -b -q  'plotter_singleMerged.C("NoSel", kTRUE, kFALSE)'
#root -l -b -q  'plotter_singleMerged.C("NoSel", kFALSE, kTRUE)'
#root -l -b -q  'plotter_singleMerged.C("NoSel", kFALSE, kFALSE)'
#
#root -l -b -q  'plotter_singleMerged.C("NoPair", kTRUE, kTRUE)'
#root -l -b -q  'plotter_singleMerged.C("NoPair", kTRUE, kFALSE)'
#root -l -b -q  'plotter_singleMerged.C("NoPair", kFALSE, kTRUE)'
#root -l -b -q  'plotter_singleMerged.C("NoPair", kFALSE, kFALSE)'
#
#root -l -b -q  'plotter_singleMerged.C("OffZ", kTRUE, kTRUE)'
#root -l -b -q  'plotter_singleMerged.C("OffZ", kTRUE, kFALSE)'
#root -l -b -q  'plotter_singleMerged.C("OffZ", kFALSE, kTRUE)'
#root -l -b -q  'plotter_singleMerged.C("OffZ", kFALSE, kFALSE)'
#
#root -l -b -q  'plotter_singleMerged.C("CRHeavy", kTRUE, kTRUE)'
#root -l -b -q  'plotter_singleMerged.C("CRHeavy", kTRUE, kFALSE)'
#root -l -b -q  'plotter_singleMerged.C("CRHeavy", kFALSE, kTRUE)'
#root -l -b -q  'plotter_singleMerged.C("CRHeavy", kFALSE, kFALSE)'
#
#root -l -b -q  'plotter_singleMerged.C("CRLight", kTRUE, kTRUE)'
#root -l -b -q  'plotter_singleMerged.C("CRLight", kTRUE, kFALSE)'
#root -l -b -q  'plotter_singleMerged.C("CRLight", kFALSE, kTRUE)'
#root -l -b -q  'plotter_singleMerged.C("CRLight", kFALSE, kFALSE)'
