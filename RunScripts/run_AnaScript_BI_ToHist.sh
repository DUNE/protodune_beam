#!/bin/sh

newFileList=`cat /scratch/BeamInstOutput/Trees_DIPRaw/filesList_BI_ToHist.txt`
detectorList=`cat /nfs/sw/BeamLineMonitoring/DIPExtraction/SubscriptionLists/detectors`
echo -n > /scratch/BeamInstOutput/Trees_DIPRaw/filesList_BI_ToHist.txt
/nfs/sw/BeamLineMonitoring/AnaScripts/Analyse_BI_ToHist.exe true $newFileList $detectorList
cp `cat /scratch/BeamInstOutput/Histograms_BI/latestHistFile.txt` /scratch/BeamInstOutput/Histograms_BI/latestHistFile.root
