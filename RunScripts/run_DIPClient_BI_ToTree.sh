#!/bin/sh

HOME=/nfs/sw/BeamLineMonitoring
DATAHOME=/scratch/BeamInstOutput
DIPHOME=/nfs/sw/BeamLineMonitoring/dip-5.6.3
export LD_LIBRARY_PATH=$DIPHOME/lib64:$LD_LIBRARY_PATH

lifetime=0

if [ $1 = "-h" ]; then
  echo ""
  echo "./run_DIPClient.sh [-t <LIFETIME, (MINS)>] [-f <FILE CLOSE INTERVAL, (SECONDS)>] <OUTDIR> <SUBSCRIPTION VARS>"
  echo "OR"
  echo "./run_DIPClient.sh -d"
  echo ""
#THERE IS NO NEED TO PROVIDE -f AND -t ARGUMENTS, DO REQUIRE AND OUTPUT DIR AND A LIST OF VARIABLES TO QUERY IN A SIMPLE TEXT FILE.
elif [ $1 = "-d" ]; then
  echo "RUNNING DEFAULT"
  lifetime=86400
  exec $HOME/DIPExtraction/dipClient.exe $DATAHOME/Trees_DIPRaw `cat $HOME/DIPExtraction/SubscriptionLists/detectorSubscriptions` &
else
  lifetime=$(($1 * 60))
  exec $HOME/DIPExtraction/dipClient.exe -t $1 -f $2 $DATAHOME/Trees_DIPRaw `cat $3` &
fi

timestamp=$(date +%s)

while [ `date +%s` -lt $((timestamp+lifetime)) ]
do
  source $HOME/RunScripts/run_AnaScript_BI_ToTree.sh &
  sleep 60
done

echo "ANALYSIS SCRIPT FINISHED"
