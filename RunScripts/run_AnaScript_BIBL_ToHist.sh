#!/bin/sh


newFileList=`cat ${DATAHOME}/Trees_DIPRaw/filesList_BIBL_ToHist.txt`
detectorList=`cat ${THISHOME}/DIPExtraction/SubscriptionLists/detectors`
echo -n > ${DATAHOME}/Trees_DIPRaw/filesList_BIBL_ToHist.txt
${THISHOME}/AnaScripts/Analyse_BIBL_ToHist.exe true $newFileList $detectorList
cp `cat ${DATAHOME}/Histograms_BIBL/latestHistFile.txt` ${DATAHOME}/Histograms_BIBL/latestHistFile.root
