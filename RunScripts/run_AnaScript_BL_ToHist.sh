#!/bin/sh

newFileList=`cat /scratch/BeamInstOutput/Trees_DIPRaw/filesList_BL_ToHist.txt`
detectorList=`cat /nfs/sw/BeamLineMonitoring/DIPExtraction/SubscriptionLists/detectors`
echo -n > /scratch/BeamInstOutput/Trees_DIPRaw/filesList_BL_ToHist.txt
/nfs/sw/BeamLineMonitoring/AnaScripts/Analyse_BL_ToHist.exe true $newFileList $detectorList
cp `cat /scratch/BeamInstOutput/Histograms_BL/latestHistFile.txt` /scratch/BeamInstOutput/Histograms_BL/latestHistFile.root
