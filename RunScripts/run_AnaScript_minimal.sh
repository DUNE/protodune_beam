#!/bin/sh

#newFileList=`cat ${DATAHOME}/Trees_DIPRaw/filesList_BIBL_ToHistToTree.txt`
newFileList=`cat ${DATAHOME}/Trees_DIPRaw/temp_files.txt`
echo "new file list $newFileList"
detectorList=`cat ${THISHOME}/DIPExtraction/SubscriptionLists/detectors`
#detectorList=`cat ${THISHOME}/DIPExtraction/SubscriptionLists/detectorSubscriptions`
echo -n > ${DATAHOME}/Trees_DIPRaw/filesList_BIBL_ToHistToTree.txt
${THISHOME}/AnaScripts/Analyse_BIBL_ToHistToTree.exe true $newFileList $detectorList
cp `cat ${DATAHOME}/HistogramsAndTrees_DIPProcessed/latestHistFile.txt` ${DATAHOME}/HistogramsAndTrees_DIPProcessed/latestHistFile.root
cp `cat ${DATAHOME}/HistogramsAndTrees_DIPProcessed/latestTreeFile.txt` ${DATAHOME}/HistogramsAndTrees_DIPProcessed/latestTreeFile.root
#cp ${DATAHOME}/HistogramsAndTrees_DIPProcessed/latestHistFile.root /data0/BeamInstOutput/
#cp ${DATAHOME}/HistogramsAndTrees_DIPProcessed/latestHistFile.root /nfs/rscratch/BeamInstOutput/
