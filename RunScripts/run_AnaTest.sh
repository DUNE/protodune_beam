#!/bin/sh

newFileList=`cat /scratch/BeamInstOutput/Trees_DIPRaw/180830_Testing/files.list`
detectorList=`cat /nfs/sw/BeamLineMonitoring/DIPExtraction/SubscriptionLists/detectors`
/nfs/sw/BeamLineMonitoring/AnaScripts/AnaTest.exe true /scratch/BeamInstOutput/Trees_DIPRaw/180901-180902_Testing/eventsData_1535871342.root /scratch/BeamInstOutput/Trees_DIPRaw/180901-180902_Testing/eventsData_1535867764.root $detectorList
