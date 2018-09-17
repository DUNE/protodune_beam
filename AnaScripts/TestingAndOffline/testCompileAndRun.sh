#!/bin/sh

g++ -std=c++11 -o AnaTest.exe AnaTest.C ../BeamLineClasses/class_AcquisitionXBPF.C ../BeamLineClasses/class_AcquisitionXBTF.C ../BeamLineClasses/class_Detector.C ../BeamLineClasses/class_BeamLine.C ../BeamLineClasses/class_DetectorCoincidences.C ../BeamLineClasses/unpack.C ../BeamLineClasses/plotting.C `root-config --cflags --glibs`

detectorList=`cat /nfs/sw/BeamLineMonitoring/DIPExtraction/SubscriptionLists/detectors`
filesList=`cat `

#./AnaTest.exe true $fileList $detectorList
#./AnaTest.exe true `cat firstFiles.txt` $detectorList
#./AnaTest.exe true `cat secondFiles.txt` $detectorList
#./AnaTest.exe true `cat thirdFiles.txt` $detectorList
#./AnaTest.exe true `cat fourthFiles.txt` $detectorList
./AnaTest.exe true `cat filesList_180911_0000_0400.txt` $detectorList
