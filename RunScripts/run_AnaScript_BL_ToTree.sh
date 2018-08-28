#!/bin/sh

newFileList=`cat /scratch/BeamInstOutput/Trees_DIPRaw/filesList_BL_ToTree.txt`
detectorList=`cat /nfs/sw/BeamLineMonitoring/DIPExtraction/SubscriptionLists/detectors`
echo -n > /scratch/BeamInstOutput/Trees_DIPRaw/filesList_BL_ToTree.txt
/nfs/sw/BeamLineMonitoring/AnaScripts/Analyse_BL_ToTree.exe true $newFileList $detectorList
cp `cat /scratch/BeamInstOutput/Trees_DIPProcessed/latestTreeFile_BL.txt` /scratch/BeamInstOutput/Trees_DIPProcessed/latestTreeFile_BL.root
