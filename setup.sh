#!/bin/bash

export depot="/eos/uscms/store/group/lpchbb/LLDJntuples/"
export nversion="furwed"
export aversion="t3dy_cutflowDY_loose"

pushd `dirname ${BASH_SOURCE[0]}` > /dev/null
export basedir=`pwd`
popd > /dev/null

export listdir="${basedir}/lists"
export rootdir="${basedir}/roots"
export plotdir="${basedir}/plots"
export andir="${basedir}/analysis"

export subdir="${basedir}/ntuples/config"
