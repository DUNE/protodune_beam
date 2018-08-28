#!/bin/sh

newFileList=`cat /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPRaw/filesList_BI_ToTree.txt`
detectorList=`cat /afs/cern.ch/user/a/abooth/private/BeamLine/DIPExtraction/SubscriptionLists/detectors`
#echo -n > /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPRaw/filesList_BI_ToTree.txt
/afs/cern.ch/user/a/abooth/private/BeamLine/AnaScripts/Analyse_BI_ToTree.exe true $newFileList $detectorList
cp `cat /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPProcessed/latestTreeFile_BI.txt` /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPProcessed/latestTreeFile_BI.root
