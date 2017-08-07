#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/mincoin.png
ICON_DST=../../src/qt/res/icons/mincoin.ico
convert ${ICON_SRC} -resize 16x16 mincoin-16.png
convert ${ICON_SRC} -resize 32x32 mincoin-32.png
convert ${ICON_SRC} -resize 48x48 mincoin-48.png
convert mincoin-16.png mincoin-32.png mincoin-48.png ${ICON_DST}

