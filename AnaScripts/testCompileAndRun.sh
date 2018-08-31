#!/bin/sh

g++ -std=c++11 -o AnaTest.exe AnaTest.C BeamLineClasses/class_AcquisitionXBPF.C BeamLineClasses/class_AcquisitionXBTF.C BeamLineClasses/class_Detector.C BeamLineClasses/class_BeamLine.C BeamLineClasses/class_DetectorCoincidences.C BeamLineClasses/unpack.C BeamLineClasses/plotting.C `root-config --cflags --glibs`
#cd /afs/cern.ch/user/a/abooth/public/BeamLineMonitoring/RunScripts/
#source run_AnaTest.sh
#cd /afs/cern.ch/user/a/abooth/public/BeamLineMonitoring/AnaScripts/

cd /nfs/sw/BeamLineMonitoring/RunScripts/
source /nfs/sw/BeamLineMonitoring/RunScripts/run_AnaTest.sh
cd /nfs/sw/BeamLineMonitoring/AnaScripts/
