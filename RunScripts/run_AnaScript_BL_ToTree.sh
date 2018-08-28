#!/bin/sh

newFileList=`cat /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPRaw/filesList_BL_ToTree.txt`
detectorList=`cat /afs/cern.ch/user/a/abooth/private/BeamLine/DIPExtraction/SubscriptionLists/detectors`
#echo -n > /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPRaw/filesList_BL_ToTree.txt
/afs/cern.ch/user/a/abooth/private/BeamLine/AnaScripts/Analyse_BL_ToTree.exe true $newFileList $detectorList
cp `cat /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPProcessed/latestTreeFile_BL.txt` /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPProcessed/latestTreeFile_BL.root
