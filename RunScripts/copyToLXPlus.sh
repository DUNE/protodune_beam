#!/bin/sh

newFileList=`cat /scratch/BeamInstOutput/HistogramsAndTrees_DIPProcessed/filesList_ForLXPlus.txt`
dateAndTime=`date '+%Y%m%d_%H%M%S'`
echo -n >| /scratch/BeamInstOutput/HistogramsAndTrees_DIPProcessed/filesList_ForLXPlus.txt
hadd /scratch/BeamInstOutput/HistogramsAndTrees_DIPProcessed/Analyse_BIBL_Hist_4hrs_Ending_$dateAndTime.root $newFileList
scp /scratch/BeamInstOutput/HistogramsAndTrees_DIPProcessed/Analyse_BIBL_Hist_4hrs_Ending_$dateAndTime.root abooth@lxplus.cern.ch:/afs/cern.ch/user/a/abooth/BeamLineMonitoringOutput/
rm -f /scratch/BeamInstOutput/HistogramsAndTrees_DIPProcessed/Analyse_BIBL_Hist_4hrs_Ending_$dateAndTime.root
