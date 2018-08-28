DIPHOME=/nfs/sw/BeamLineMonitoring/dip-5.6.3

CC = g++
CFLAGS = -Wall -ansi -I $(DIPHOME)/include -std=c++11

DLIB = $(DIPHOME)/lib64/libdip.so -lpthread -ldl -llog4cplus

all:	dip-client

dip-client:	dipClient_ToROOTFile.C
	$(CC) $(CFLAGS) dipClient_ToROOTFile.C -L$(DIPHOME)/lib64 $(DLIB) -o dipClient.exe $(LIBS) `root-config --cflags --glibs` 
