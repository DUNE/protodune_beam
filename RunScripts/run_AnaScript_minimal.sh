#!/bin/sh

newFileList=`cat ${1}`
echo "new file list $newFileList"
detectorList=`cat ${THISHOME}/DIPExtraction/SubscriptionLists/detectors`

echo -n > ${DATAHOME}/Trees_DIPRaw/filesList_BIBL_ToHistToTree.txt

${THISHOME}/AnaScripts/Analyse_BIBL_ToHistToTree.exe true "/afs/cern.ch/user/j/jcalcutt/scratch/BeamInstOutput/HistogramsAndTrees_DIPProcessed/" $newFileList $detectorList
cp `cat ${DATAHOME}/HistogramsAndTrees_DIPProcessed/latestHistFile.txt` ${DATAHOME}/HistogramsAndTrees_DIPProcessed/${2}/latestHistFile.root
cp `cat ${DATAHOME}/HistogramsAndTrees_DIPProcessed/latestTreeFile.txt` ${DATAHOME}/HistogramsAndTrees_DIPProcessed/${2}/latestTreeFile.root
