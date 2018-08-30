#ifndef PLOTTING_H
#define PLOTTING_H

#include "class_BeamLine.h"
#include "unpack.h"
#include "class_Detector.h"
#include <string>
#include <map>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TTree.h>

void plot_dTAcq(std::map<std::string,Detector> &map_Detector, std::map<std::string,std::vector<TH1I*>> &map_NameToVecHist_I);
void plot_AcqLevel(std::map<std::string,Detector> &map_Detector, std::map<std::string,std::vector<TH1I*>> &map_NameToVecHist_I);
void plot_EventLevel(std::map<std::string,Detector> &map_Detector, std::map<std::string,std::vector<TH1I*>> &map_NameToVecHist_I, std::map<std::string,std::vector<TH1D*>> &map_NameToVecHist_D);
void plotPROF(std::vector<PROFCoincidenceRecord::PROFCoincidence> &vec_PROFCO, std::vector<TH1D*> &vec_PROFHist1D, std::vector<TH2D*> &vec_PROFHist2D, TString const &sType);
void plotTF(std::vector<TFCoincidenceRecord::TFCoincidence> &vec_TFCO, std::vector<TH1D*> &vec_TFHist1D, std::vector<TH2D*> &vec_TFHist2D, TString const &sType); 

#endif
