export LD_LIBRARY_PATH=/afs/cern.ch/user/j/jcalcutt/dip-5.6.3/lib64:$LD_LIBRARY_PATH
THISHOME=/afs/cern.ch/user/j/jcalcutt/BeamlineMonitoring/BeamLineMonitoring
DATAHOME=/afs/cern.ch/user/j/jcalcutt/scratch/BeamInstOutput
DIPHOME=/${THISHOME}/dip-5.6.3

source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
#setup root v6_28_12 -q e26:p3915:prof
setup root v6_06_04b -q e10:nu:prof
