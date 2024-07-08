#!/bin/sh

newFileList=`cat ${1}`
#newFileList=`head -n ${2} ${1} | tail -n 1`
#newFileList=${1}
echo "new file list $newFileList"
detectorList=`cat ${THISHOME}/DIPExtraction/SubscriptionLists/detectors`

echo -n > ${DATAHOME}/Trees_DIPRaw/filesList_BIBL_ToHistToTree.txt

${THISHOME}/AnaScripts/Analyse_BIBL_ToHistToTree.exe true "/afs/cern.ch/user/j/jcalcutt/scratch/BeamInstOutput/HistogramsAndTrees_DIPProcessed/${2}/" $newFileList $detectorList
