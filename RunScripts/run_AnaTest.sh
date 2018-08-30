#!/bin/sh

newFileList=`cat /scratch/BeamInstOutput/Trees_DIPRaw/fileList_Test.txt`
detectorList=`cat /nfs/sw/BeamLineMonitoring/DIPExtraction/SubscriptionLists/detectors`
/nfs/sw/BeamLineMonitoring/AnaScripts/AnaTest.exe true $newFileList $detectorList
