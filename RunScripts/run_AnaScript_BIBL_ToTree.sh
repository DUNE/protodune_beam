#!/bin/sh

newFileList=`cat /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPRaw/filesList_BIBL_ToTree.txt`
detectorList=`cat /afs/cern.ch/user/a/abooth/private/BeamLine/DIPExtraction/SubscriptionLists/detectors`
echo -n > /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPRaw/filesList_BIBL_ToTree.txt
/afs/cern.ch/user/a/abooth/private/BeamLine/AnaScripts/Analyse_BIBL_ToTree.exe true $newFileList $detectorList
cp `cat /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPProcessed/latestTreeFile_BIBL.txt` /afs/cern.ch/user/a/abooth/public/BeamLineDataOutput/Trees_DIPProcessed/latestTreeFile_BIBL.root
