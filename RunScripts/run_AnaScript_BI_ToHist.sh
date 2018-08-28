#!/bin/sh

newFileList=`cat /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPRaw/filesList_BI_ToHist.txt`
detectorList=`cat /afs/cern.ch/user/a/abooth/private/BeamLine/DIPExtraction/SubscriptionLists/detectors`
echo -n > /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPRaw/filesList_BI_ToHist.txt
/afs/cern.ch/user/a/abooth/private/BeamLine/AnaScripts/Analyse_BI_ToHist.exe true $newFileList $detectorList
cp `cat /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Histograms_BI/latestHistoFile_BI.txt` /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Histograms_BI/latestHistoFile_BI.root
