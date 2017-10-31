#!/bin/bash

#export nversion="ealb10000"
export nversion="ealb5000"
#export nversion="bloomy50"
#export nversion="bilumi200"
#export nversion="bylumi350"
#export nversion="furmon"
export aversion="gmapa"

pushd `dirname ${BASH_SOURCE[0]}` > /dev/null
export basedir=`pwd`
popd > /dev/null

export listdir="${basedir}/lists"
export rootdir="${basedir}/roots"
export plotdir="${basedir}/plots"
export andir="${basedir}/analysis"

export subdir="${basedir}/ntuples/config"
export asubdir="${basedir}/submitters"
