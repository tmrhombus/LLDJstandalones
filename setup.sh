#!/bin/bash

export depot="/eos/uscms/store/group/lpchbb/LLDJntuples"
export nversion="addpuAOD_eled0dz_trig"
export aversion="NMinus1TaggingPlots"
#"Elesort_PhoPt175_OPTLight" #"addpuAODPassSingle"
#export aversion="CRHeavyOPT" #"addpuAODPassSingle"
#export aversion="CRLightOPT" #"addpuAODPassSingle"

pushd `dirname ${BASH_SOURCE[0]}` > /dev/null
export basedir=`pwd`
popd > /dev/null

export listdir="${basedir}/lists"
export rootdir="${basedir}/roots"
export plotdir="${basedir}/plots"
export andir="${basedir}/analysis"

export subdir="${basedir}/ntuples/config"
export asubdir="${basedir}/submitters"
