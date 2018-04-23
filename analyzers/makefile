
ROOTFLAGS=`root-config --cflags --libs` 
CXXDEPFLAGS = -MMD -MP

all: main

#main:  analyzer_base.o analyzer_signal.o analyzer_AODjets.o main.C 
#main:  analyzer_base.o analyzer_signal.o main.C 
main:  analyzer_base.o \
       analyzer_globalvalues.o \
       analyzer_config.o \
       analyzer_createobjects.o \
       analyzer_selections.o \
       analyzer_scalefactors.o \
       analyzer_histograms.o \
       analyzer_tree.o \
       analyzer_signal.o \
       main.C 
	g++ --std=c++11 $^ -o runanalyzer.exe ${ROOTFLAGS} ${CXXDEPFLAGS}

%.o: %.C  
	g++ --std=c++11 -c $^ -o $@ ${ROOTFLAGS} ${CXXDEPFLAGS} 

#-include *.d

#g++ -Wno-deprecated main.C -o theplot.exe -I$ROOTSYS/include -L$ROOTSYS/lib -I$CMS_PATH/$SCRAM_ARCH/lcg/roofit/5.32.03-cms9/include -L$CMS_PATH/$SCRAM_ARCH/lcg/roofit/5.32.03-cms9/lib -lRooFit -lRooFitCore `root-config --cflags` `root-config --libs`
