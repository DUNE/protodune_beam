#include "BeamLineClasses/class_BeamLine.h"
#include "BeamLineClasses/unpack.h"
#include <fstream>
#include <sstream>
#include <inttypes.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TROOT.h>


int main(int argc, char *argv[])
{
  gROOT->ProcessLine("#include <vector>");
  std::string s_OutDir = "/scratch/BeamInstOutput/Trees_DIPProcessed/";

  bool zeroSuppress = argv[1];
  std::vector<std::string> vec_DataPath;
  std::vector<std::string> vec_Detectors;

  for(unsigned int i = 2; i < argc; i++)
  {
    std::string s_Arg = argv[i];
    if(s_Arg.find("/") != std::string::npos)
    {
      vec_DataPath.push_back(s_Arg);
    }
    else
    {
      vec_Detectors.push_back(s_Arg);
    }
  }

  if(vec_DataPath.size()!=0)
  {
    std::cout << "\nDETECTORS: ANALYSING THE FOLLOWING DETECTORS:\n" << std::endl;

    std::map<std::string,Detector> map_Detector;
    for(unsigned int det = 0; det < vec_Detectors.size(); det++)
    {
      std::string s_DetName = vec_Detectors.at(det);
      std::string s_DetType;
      
      if(s_DetName[0]=='G')
      {
        s_DetType = "XBTF"; 
      }
      else
      {
        s_DetType = s_DetName.substr(0,4);
      }

      Detector detector(s_DetName, s_DetType, (s_DetName[0]=='G' ? "XBH4_"+s_DetType+"_"+s_DetName : "XBH4_"+s_DetType+"_022_"+s_DetName.substr(7)));
      map_Detector[s_DetName] = detector;
      detector.printDescription();
    }

    std::cout << "\nLOOKING AT DIP ROOT FILES IN: " << std::endl;
    for(unsigned int data = 0; data < vec_DataPath.size(); data++)
    {
      std::string s_DataPath = vec_DataPath.at(data);
      std::cout << s_DataPath << std::endl;
      unpackDIPROOT(map_Detector, s_DataPath, zeroSuppress);
    }

    std::cout << "\nUNPACKING DONE! DUMPING TO TREES..." << std::endl;

    std::string s_FirstFile = vec_DataPath.at(0);
    std::string s_LastFile  = vec_DataPath.at(vec_DataPath.size()-1);
    std::string s_FirstTime = s_FirstFile.substr(s_FirstFile.length()-15,10);
    std::string s_LastTime  = s_LastFile .substr(s_LastFile .length()-15,10);

    BeamLine beamline;
    beamline.dumpBIData(map_Detector,(TString)s_OutDir+"Analyse_BI_ToTree_"+(TString)s_FirstTime+"_"+(TString)s_LastTime+".root");

    std::ofstream latestFile;
    latestFile.open(s_OutDir+"latestTreeFile_BI.txt");
    latestFile << s_OutDir+"Analyse_BI_ToTree_"+s_FirstTime+"_"+s_LastTime+".root" << std::endl;
    latestFile.close();

    std::cout << "\nTREES DONE!\n" << std::endl;
  }
  else
  {
    std::cout << "DETECTORS, NO NEW DATA FILES!" << std::endl;
  }

  return 0;
}
