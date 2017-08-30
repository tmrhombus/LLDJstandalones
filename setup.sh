#!/bin/bash

export nversion="Levine"
#export nversion="sosou"
#export aversion="laug"

#export aversion="tw9_loose"
#export aversion="tw9_tight"
export aversion="tw9_cutflowDY_loose"

#export aversion="agl_tight"
#export aversion="laug_med"
#export aversion="laug_loose"
#export aversion="laug_tight_noelsf" 
#export aversion="laug_tight_noelsf_nopusf" 
#export aversion="laug_tight_sleptrg" 
#export aversion="laug_tight" 
#export aversion="laug_tight_sigonly" 


pushd `dirname ${BASH_SOURCE[0]}` > /dev/null
export basedir=`pwd`
popd > /dev/null

export listdir="${basedir}/lists"
export rootdir="${basedir}/roots"
export plotdir="${basedir}/plots"
export andir="${basedir}/analysis"

export subdir="${basedir}/ntuples/config"
