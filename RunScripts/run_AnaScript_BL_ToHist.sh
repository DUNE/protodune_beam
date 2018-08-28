#!/bin/sh

newFileList=`cat /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPRaw/filesList_BL_ToHist.txt`
detectorList=`cat /afs/cern.ch/user/a/abooth/private/BeamLine/DIPExtraction/SubscriptionLists/detectors`
#echo -n > /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPRaw/filesList_BL_ToHist.txt
/afs/cern.ch/user/a/abooth/private/BeamLine/AnaScripts/Analyse_BL_ToHist.exe true $newFileList $detectorList
cp `cat /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Histograms_BL/latestHistoFile_BL.txt` /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Histograms_BL/latestHistoFile_BL.root
