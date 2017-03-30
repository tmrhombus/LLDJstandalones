// for deleting a histogram from a root file

void rmhisto(TString filename){

TString hname = "h_NoPair_FourthJet_STUPAKR;1";

TFile* file = new TFile(filename, "update");
gDirectory->Delete(hname);
file->Close();


}
