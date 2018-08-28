#!/bin/sh

newFileList=`cat /scratch/BeamInstOutput/Trees_DIPRaw/filesList_BIBL_ToTree.txt`
detectorList=`cat /nfs/sw/BeamLineMonitoring/DIPExtraction/SubscriptionLists/detectors`
echo -n > /scratch/BeamInstOutput/Trees_DIPRaw/filesList_BIBL_ToTree.txt
/nfs/sw/BeamLineMonitoring/AnaScripts/Analyse_BIBL_ToTree.exe true $newFileList $detectorList
cp `cat /scratch/BeamInstOutput/Trees_DIPProcessed/latestTreeFile_BIBL.txt` /scratch/BeamInstOutput/Trees_DIPProcessed/latestTreeFile_BIBL.root
