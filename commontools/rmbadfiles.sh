#!/bin/bash

# remove bad files by hand
sed '/161018_170954_1705.root/d' ${listdir}/DY50.list > temp && mv temp ${listdir}/DY50.list

sed '/161018_171029_1326.root/d' ${listdir}/TTbar.list > temp && mv temp ${listdir}/TTbar.list
