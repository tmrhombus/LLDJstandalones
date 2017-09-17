
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"

// (local) variables associated with tree branches


void lldjNtuple::branchesTrigger(TTree* tree){

 printf(" making trigger branches\n");

}

void lldjNtuple::fillTrigger(const edm::Event &e, const edm::EventSetup &es){

    printf(" filling trigger brnahces\n");

    edm::Handle<edm::TriggerResults>                     triggerBits;
    edm::Handle<edm::View<pat::TriggerObjectStandAlone>> triggerObjects;
    edm::Handle<pat::PackedTriggerPrescales>             triggerPrescales;

    e.getByToken(triggerBits_, triggerBits);
    e.getByToken(triggerObjects_, triggerObjects);
    e.getByToken(triggerPrescales_, triggerPrescales);


    const edm::TriggerNames &names = e.triggerNames(*triggerBits);
    std::cout << "\n == TRIGGER PATHS= " << std::endl;
    for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
        std::cout << "Trigger " << names.triggerName(i) <<
                ", prescale " << triggerPrescales->getPrescaleForIndex(i) <<
                ": " << (triggerBits->accept(i) ? "PASS" : "fail (or not run)")
                << std::endl;
    }
    std::cout << "\n TRIGGER OBJECTS " << std::endl;
    for (pat::TriggerObjectStandAlone obj : *triggerObjects) { // note: not "const &" since we want to call unpackPathNames
        obj.unpackPathNames(names);
        std::cout << "\tTrigger object:  pt " << obj.pt() << ", eta " << obj.eta() << ", phi " << obj.phi() << std::endl;
        // Print trigger object collection and type
        std::cout << "\t   Collection: " << obj.collection() << std::endl;
        std::cout << "\t   Type IDs:   ";
        for (unsigned h = 0; h < obj.filterIds().size(); ++h) std::cout << " " << obj.filterIds()[h] ;
        std::cout << std::endl;
        // Print associated trigger filters
        std::cout << "\t   Filters:    ";
        for (unsigned h = 0; h < obj.filterLabels().size(); ++h) std::cout << " " << obj.filterLabels()[h];
        std::cout << std::endl;
        std::vector<std::basic_string<char>> pathNamesAll  = obj.pathNames(false);
        std::vector<std::basic_string<char>> pathNamesLast = obj.pathNames(true);
        // Print all trigger paths, for each one record also if the object is associated to a 'l3' filter (always true for the
        // definition used in the PAT trigger producer) and if it's associated to the last filter of a successfull path (which
        // means that this object did cause this trigger to succeed; however, it doesn't work on some multi-object triggers)
        std::cout << "\t   Paths (" << pathNamesAll.size()<<"/"<<pathNamesLast.size()<<"):    ";
        for (unsigned h = 0, n = pathNamesAll.size(); h < n; ++h) {
            bool isBoth = obj.hasPathName( pathNamesAll[h], true, true );
            bool isL3   = obj.hasPathName( pathNamesAll[h], false, true );
            bool isLF   = obj.hasPathName( pathNamesAll[h], true, false );
            bool isNone = obj.hasPathName( pathNamesAll[h], false, false );
            std::cout << "   " << pathNamesAll[h];
            if (isBoth) std::cout << "(L,3)";
            if (isL3 && !isBoth) std::cout << "(*,3)";
            if (isLF && !isBoth) std::cout << "(L,*)";
            if (isNone && !isBoth && !isL3 && !isLF) std::cout << "(*,*)";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;


}

//class lldjNtuple_trigger : public edm::EDAnalyzer {
//   public:
//      explicit lldjNtuple_trigger (const edm::ParameterSet&);
//      ~lldjNtuple_trigger() {}
//
//   private:
//      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
//
//      edm::EDGetTokenT triggerBits_;
//      edm::EDGetTokenT triggerObjects_;
//      edm::EDGetTokenT triggerPrescales_;
//};
//
//lldjNtuple_trigger::lldjNtuple_trigger(const edm::ParameterSet& iConfig):
//    triggerBits_(consumes(iConfig.getParameter("bits"))),
//    triggerObjects_(consumes(iConfig.getParameter("objects"))),
//    triggerPrescales_(consumes(iConfig.getParameter("prescales")))
//{
//}
//
//void lldjNtuple_trigger::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
//{
//
//
//}


////define this as a plug-in
//DEFINE_FWK_MODULE(lldjNtuple_trigger);
