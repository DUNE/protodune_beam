#!/bin/sh

#newFileList=`cat /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPRaw/filesList_BIBL_ToHistToTree.txt`
newFileList=`cat /afs/cern.ch/user/a/abooth/private/Testing/BIDataOutput/Trials/filesList_temp.txt`
detectorList=`cat /afs/cern.ch/user/a/abooth/private/BeamLine/DIPExtraction/SubscriptionLists/detectors`
#echo -n > /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPRaw/filesList_BIBL_ToHistToTree.txt
/afs/cern.ch/user/a/abooth/private/BeamLine/AnaScripts/Analyse_BIBL_ToHistToTree.exe true $newFileList $detectorList
cp `cat /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/HistogramsAndTrees_DIPProcessed/latestHistFile.txt` /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPProcessed/latestHistFile.root
cp `cat /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/HistogramsAndTrees_DIPProcessed/latestTreeFile.txt` /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPProcessed/latestTreeFile.root
