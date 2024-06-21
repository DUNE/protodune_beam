DIPHOME=/afs/cern.ch/user/j/jcalcutt/dip-5.6.3

CC = g++
CFLAGS = -Wall -ansi -I $(DIPHOME)/include -std=c++14

#DLIB = $(DIPHOME)/lib64/libdip.so -lpthread -ldl -llog4cplus
DLIB = -ldip -lpthread -ldl -llog4cplus

#LIBS = -llog4cplus

all:	dip-client


dip-client:	dipClient_ToROOTFile.C
	$(CC) $(CFLAGS) dipClient_ToROOTFile.C -L$(DIPHOME)/lib64 $(LIBS) $(DLIB) -o dipClient.exe `root-config --cflags --glibs` 
