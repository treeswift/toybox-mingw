#!/bin/sh

OBJDUMP=${OBJDUMP:-${PREFIX}/bin/${TARGET}-objdump}
OUTFILE=${OUTFILE:-toybox.exe}
DEBFILE=${OUTFILE:-generated/unstripped/toybox.exe}

INSTALL=${INSTALL:-install}
INSTDIR=${PREFIX}/${TARGET}/bin

"${INSTALL}" "${OUTFILE}" "${INSTDIR}"

for cmd in `"${OBJDUMP}" -t "${DEBFILE}" | grep -v '0xffc' | grep '.weak..*_main' | grep -o '\\w*_main' | sed s/_main// | grep -v toybox | uniq`
do
    CMDFILE=${INSTDIR}/${cmd}.cmd
    echo "@echo off" > "${CMDFILE}"
    echo "toybox ${cmd} %*" >> "${CMDFILE}"
done
