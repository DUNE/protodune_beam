#ifndef CLASS_DETECTORCOINCIDENCES_H
#define CLASS_DETECTORCOINCIDENCES_H

#include <vector>
#include <string>
#include <map>
#include <array>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include "class_Detector.h"
#include "class_AcquisitionXBTF.h"
#include "class_AcquisitionXBPF.h"

class Detector;
class AcquisitionXBTF;
class AcquisitionXBPF;

class TFCoincidenceRecord{

  public:
    struct TFCoincidence{
        unsigned int fDetUS;
        unsigned int fAcqUS;
        unsigned int fEventUS;
        unsigned int fDetDS;
        unsigned int fAcqDS;
        unsigned int fEventDS;
        double       fTF;
        std::pair<unsigned int,unsigned int> fMultiplicity;
        bool fUniqueness;
        void setMultiplicity(std::pair<unsigned int,unsigned int> &cMultiplicity){fMultiplicity = cMultiplicity; return;};
        void setUniqueness(bool const &cIsUnique){fUniqueness = cIsUnique; return;};
    };

    TFCoincidenceRecord(){return;};
    std::vector<TFCoincidence> getTFCoincidencesDegenerate();
    std::vector<TFCoincidence> getTFCoincidencesUnique();
    std::pair<unsigned int,unsigned int> getMultiplicity(TFCoincidence const &cTFCoincidence);
    unsigned int getMultiplicity(std::string const &cUSOrDS, unsigned int const &cDet, unsigned int const &cAcq, unsigned int const &cEvent);
    void addCoincidence(unsigned int cDetUS, unsigned int cAcqUS, unsigned int cEventUS, unsigned int cDetDS, unsigned int cAcqDS, unsigned int cEventDS, double cTF);
    void dumpDegenerate (std::map<std::string,Detector> &cMapDetectors, std::map<std::string,unsigned int> &cXBTFNameToIndex, TString const &cFilePathName);
    void dumpUnique     (std::map<std::string,Detector> &cMapDetectors, std::map<std::string,unsigned int> &cXBTFNameToIndex, TString const &cFilePathName);
    void printDegenerate(std::map<std::string,Detector> &cMapDetectors, std::map<std::string,unsigned int> &cXBTFNameToIndex);
    void printUnique    (std::map<std::string,Detector> &cMapDetectors, std::map<std::string,unsigned int> &cXBTFNameToIndex);

  private:
    std::vector<TFCoincidence> fVecTFCoincidesDegenerate;
    std::vector<TFCoincidence> fVecTFCoincidesUnique;
    std::map<std::array<unsigned int,3>,std::vector<TFCoincidence>> fMapUS;
    std::map<std::array<unsigned int,3>,std::vector<TFCoincidence>> fMapDS;
};

class PROFCoincidenceRecord{

  public:
    class PROFCoincidence{

      public:
        unsigned int fAcqPROF1;
        unsigned int fEventPROF1;
        unsigned int fAcqPROF2;
        unsigned int fEventPROF2;
        unsigned int fAcqPROF3;
        unsigned int fEventPROF3;
        std::vector<double> fCosTheta;
        std::vector<double> fTheta;
        std::vector<double> fMomentum;
        std::array<long unsigned int,3> fMultiplicity;
        bool fUniqueness;

        PROFCoincidence(unsigned int cAcqPROF1, unsigned int cEventPROF1, unsigned int cAcqPROF2, unsigned int cEventPROF2, unsigned int cAcqPROF3, unsigned int cEventPROF3)
        {
          fAcqPROF1   = cAcqPROF1;
          fEventPROF1 = cEventPROF1;
          fAcqPROF2   = cAcqPROF2;
          fEventPROF2 = cEventPROF2;
          fAcqPROF3   = cAcqPROF3;
          fEventPROF3 = cEventPROF3;

          return;
        };

        void addDeflectionInfo(std::vector<double> cCosTheta, std::vector<double> cTheta, std::vector<double> cMomentum)
        {
          fCosTheta = cCosTheta;
          fTheta    = cTheta;
          fMomentum = cMomentum;

          return;
        };

        std::vector<double> getCosTheta()
        {
          return fCosTheta;
        };
        std::vector<double> getTheta()
        {
          return fTheta;
        };
        std::vector<double> getMomentum()
        {
          return fMomentum;
        };
        unsigned int getNFibreCombinations()
        {
          return fMomentum.size();
        };
        void setMultiplicity(std::array<long unsigned int,3> &cMultiplicity){fMultiplicity = cMultiplicity; return;};
        void setUniqueness(bool const&cIsUnique){fUniqueness = cIsUnique; return;}
    };
    PROFCoincidenceRecord(){};
    std::vector<PROFCoincidence> getPROFCoincidencesDegenerate();
    std::vector<PROFCoincidence> getPROFCoincidencesUnique();
    std::array<long unsigned int,3> getMultiplicity(PROFCoincidence const &cPROFCoincidence);
    unsigned int getMultiplicity(unsigned int const &cDet, unsigned int const &cAcq, unsigned int const &cEvent);
    void addCoincidence(unsigned int cAcqPROF1, unsigned int cEventPROF1, unsigned int cAcqPROF2, unsigned int cEventPROF2, unsigned int cAcqPROF3, unsigned int cEventPROF3,
                        std::vector<double> cCosTheta, std::vector<double> cTheta, std::vector<double> cMomentum);
    void dumpDegenerate (std::map<std::string,Detector> &cMapDetectors, TString const &cFilePathName);
    void dumpUnique     (std::map<std::string,Detector> &cMapDetectors, TString const &cFilePathName);
    void printDegenerate(std::map<std::string,Detector> &cMapDetectors);
    void printUnique    (std::map<std::string,Detector> &cMapDetectors);

  private:
    std::vector<PROFCoincidence> fVecPROFCoincidesDegenerate;
    std::vector<PROFCoincidence> fVecPROFCoincidesUnique;
    std::map<std::array<unsigned int,2>,std::vector<PROFCoincidence>> fMapPROF1;
    std::map<std::array<unsigned int,2>,std::vector<PROFCoincidence>> fMapPROF2;
    std::map<std::array<unsigned int,2>,std::vector<PROFCoincidence>> fMapPROF3;
};

class CombinedCoincidenceRecord{
  public:
    class TFPROFCoincidence{
      TFPROFCoincidence(){};
    
    };
    class TOFPROFCoincidence{
      TOFPROFCoincidence(){};
    
    };
    CombinedCoincidenceRecord(){return;};
    std::vector<TFPROFCoincidence>  fTFPROFCoincidenceDegenerate;
    std::vector<TFPROFCoincidence>  fTFPROFCoincidenceUnique;
    std::vector<TOFPROFCoincidence> fTOFPROFCoincidenceDegenerate;
    std::vector<TOFPROFCoincidence> fTOFPROFCoincidenceUnique;
};

#endif
