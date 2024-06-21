#!/bin/sh
THISHOME=/afs/cern.ch/user/j/jcalcutt/BeamlineMonitoring/BeamLineMonitoring
DIPHOME=/${THISHOME}/dip-5.6.3
export LD_LIBRARY_PATH=$DIPHOME/lib64:$LD_LIBRARY_PATH
detectors=${THISHOME}/DIPExtraction/SubscriptionLists/detectorSubscriptions

lifetime=0
if [ $1 = "-h" ]; then
  echo ""
  echo "./run_DIPClient_newdir.sh <LIFETIME, (MINS)> <OUTDIR>"
  echo ""
else
  echo "hw"

  echo "Attempting to mkdir $2"
  outdir=$2
  mkdir $2
  
  if [ $? -ne 0 ]; then
    echo "Could not make $outdir -- does it already exist? Choose a new directory"
    return 1
  fi

  echo "Made new directory"

  exec $THISHOME/DIPExtraction/dipClient.exe -t $1 $outdir `cat $detectors` &
fi
