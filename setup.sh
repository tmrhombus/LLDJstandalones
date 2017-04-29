#!/bin/bash

export nversion="splash"
export aversion="frere"

pushd `dirname ${BASH_SOURCE[0]}` > /dev/null
export basedir=`pwd`
popd > /dev/null

export listdir="${basedir}/lists"
export rootdir="${basedir}/roots"
export andir="${basedir}/analysis"

export subdir="${basedir}/ntuples/config"
