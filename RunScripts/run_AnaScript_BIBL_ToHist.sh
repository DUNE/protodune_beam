#!/bin/sh

newFileList=`cat /scratch/BeamInstOutput/Trees_DIPRaw/filesList_BIBL_ToHist.txt`
detectorList=`cat /nfs/sw/BeamLineMonitoring/DIPExtraction/SubscriptionLists/detectors`
echo -n > /scratch/BeamInstOutput/Trees_DIPRaw/filesList_BIBL_ToHist.txt
/nfs/sw/BeamLineMonitoring/AnaScripts/Analyse_BIBL_ToHist.exe true $newFileList $detectorList
cp `cat /scratch/BeamInstOutput/Histograms_BIBL/latestHistFile.txt` /scratch/BeamInstOutput/Histograms_BIBL/latestHistFile.root
