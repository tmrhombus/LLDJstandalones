#!/bin/bash

export depot="/eos/uscms/store/group/lpchbb/LLDJntuples"
export nversion="topRWT"
export aversion="PhoPT170_k1p26"
#export aversion="PhoPT170"
#export aversion="PhoPT350"
#export aversion="addTrigFlav"

pushd `dirname ${BASH_SOURCE[0]}` > /dev/null
export basedir=`pwd`
popd > /dev/null

export listdir="${basedir}/lists"
export rootdir="${basedir}/roots"
export plotdir="${basedir}/plots"
export andir="${basedir}/analysis"

export subdir="${basedir}/ntuples/config"
export asubdir="${basedir}/submitters"
