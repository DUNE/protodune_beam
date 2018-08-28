#ifndef UNPACK_H
#define UNPACK_H

#include "class_Detector.h"
#include <string>
#include <map>
#include <TFile.h>
#include <TTree.h>

void unpackDIPROOT(std::map<std::string,Detector> &cMapDetector, std::string const &cDataPath, bool const &cZeroSuppress);

#endif
