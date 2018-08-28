#!/bin/sh

newFileList=`cat /scratch/BeamInstOutput/Trees_DIPRaw/filesList_BI_ToTree.txt`
detectorList=`cat /nfs/sw/BeamLineMonitoring/DIPExtraction/SubscriptionLists/detectors`
echo -n > /scratch/BeamInstOutput/Trees_DIPRaw/filesList_BI_ToTree.txt
/nfs/sw/BeamLineMonitoring/AnaScripts/Analyse_BI_ToTree.exe true $newFileList $detectorList
cp `cat /scratch/BeamInstOutput/Trees_DIPProcessed/latestTreeFile_BI.txt` /scratch/BeamInstOutput/Trees_DIPProcessed/latestTreeFile_BI.root
