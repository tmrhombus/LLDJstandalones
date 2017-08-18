#!/bin/bash

export nversion="sosou"
#export aversion="coulou"
#export aversion="coulou_tight"
#export aversion="coulou_med"
#export aversion="coulou_loose"
#export aversion="coulou_tight_noelsf" 
#export aversion="coulou_tight_noelsf_nopusf" 
#export aversion="coulou_tight_sleptrg" 
export aversion="coulou_tight" 


pushd `dirname ${BASH_SOURCE[0]}` > /dev/null
export basedir=`pwd`
popd > /dev/null

export listdir="${basedir}/lists"
export rootdir="${basedir}/roots"
export plotdir="${basedir}/plots"
export andir="${basedir}/analysis"

export subdir="${basedir}/ntuples/config"
