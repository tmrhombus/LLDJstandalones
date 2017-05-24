#!/bin/bash

export nversion="raindaydata"
export aversion="sipmshape"

pushd `dirname ${BASH_SOURCE[0]}` > /dev/null
export basedir=`pwd`
popd > /dev/null

export listdir="${basedir}/lists"
export rootdir="${basedir}/roots"
export andir="${basedir}/analysis"

export subdir="${basedir}/ntuples/config"
