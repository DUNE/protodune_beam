#!/bin/sh

newFileList=`cat ~/public/WC_180827/Testing/BIDataOutput/Trials/filesList_temp2.txt`
detectorList=`cat /afs/cern.ch/user/a/abooth/public/BeamLineMonitoring/DIPExtraction/SubscriptionLists/detectors`
/afs/cern.ch/user/a/abooth/public/BeamLineMonitoring/AnaScripts/AnaTest.exe true $newFileList $detectorList
