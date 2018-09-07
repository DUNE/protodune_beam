#!/bin/sh

newFileList=`cat /scratch/BeamInstOutput/HistogramsAndTrees_DIPProcessed/lxplus_HistFiles.txt`
currentTS=`date '+%Y%m%d_%H%M%S'`
echo -n > /scratch/BeamInstOutput/HistogramsAndTrees_DIPProcessed/lxplus_HistFiles.txt
hadd /data0/BeamInstOutput/HistogramsAndTrees_DIPProcessed_4Hrs/Analyse_BIBL_Hist_4HrsEnding_$currentTS.root $newFileList 
#~/krb5/np04daq_abooth-scp.sh /data0/BeamInstOutput/HistogramsAndTrees_DIPProcessed_4Hrs/Analyse_BIBL_Hist_4HrsEnding_$currentTS.root abooth@lxplus.cern.ch:/afs/cern.ch/user/a/abooth/public/BeamLineMonitoringOutput/
#rm -f /scratch/BeamInstOutput/HistogramsAndTrees_DIPProcessed/Analyse_BIBL_Hist_4HrsEnding_$currentTS.root

