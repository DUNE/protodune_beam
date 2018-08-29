#include "BeamLineClasses/class_BeamLine.h"
#include "BeamLineClasses/unpack.h"
#include <fstream>
#include <sstream>
#include <inttypes.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TROOT.h>


void plotPROF(std::vector<PROFCoincidenceRecord::PROFCoincidence> &vec_PROFCO, std::vector<TH1D*> &vec_PROFHist1D, std::vector<TH2D*> &vec_PROFHist2D, TString const &sType) 
{
  TH1D *h_CosTheta   = new TH1D("h_CosTheta_"  +sType, "h_CosTheta_"  +sType,  50, -1.1,  1.1);
  TH1D *h_Momentum   = new TH1D("h_Momentum_"  +sType, "h_Momentum_"  +sType,  50,    0,    8);
  TH1D *h_Theta      = new TH1D("h_Theta_"     +sType, "h_Theta_"     +sType,  50,   -10,  10);
  TH1D *h_FibComb    = new TH1D("h_FibComb_"   +sType, "h_FibComb_"   +sType,  21, -0.5, 20.5);
  TH1D *h_MultiPROF1 = new TH1D("h_MultiPROF1_"+sType, "h_MultiPROF1_"+sType,   7, -0.5,  6.5);
  TH1D *h_MultiPROF2 = new TH1D("h_MultiPROF2_"+sType, "h_MultiPROF2_"+sType,   7, -0.5,  6.5);
  TH1D *h_MultiPROF3 = new TH1D("h_MultiPROF3_"+sType, "h_MultiPROF3_"+sType,   7, -0.5,  6.5);

  if(sType=="UNIQ")
  {
    SetHistTitles(h_CosTheta  , "Cosine of Deflection Angle, Unique Events",            "CosTheta",          "Events");
    SetHistTitles(h_Momentum  , "Momentum, Unique Events",                              "Momentum, (GeV)",   "Events");
    SetHistTitles(h_Theta     , "Deflection Angle, Unique Events",                      "Deflection, (Deg)", "Events");
    SetHistTitles(h_FibComb   , "Number of Possible Fibre Combinations / Unique Event", "Combinations",      "Events");
    SetHistTitles(h_MultiPROF1, "Event Coincidence Degeneracy", "Combinations","Events");
    SetHistTitles(h_MultiPROF2, "Event Coincidence Degeneracy", "Combinations","Events");
    SetHistTitles(h_MultiPROF3, "Event Coincidence Degeneracy", "Combinations","Events");
  }
  else
  {
    SetHistTitles(h_CosTheta  , "Cosine of Deflection Angle, Degenerate Events",            "CosTheta",          "Events");
    SetHistTitles(h_Momentum  , "Momentum, Degenerate Events",                              "Momentum, (GeV)",   "Events");
    SetHistTitles(h_Theta     , "Deflection Angle, Degenerate Events",                      "Deflection, (Deg)", "Events");
    SetHistTitles(h_FibComb   , "Number of Possible Fibre Combinations / Degenerate Event", "Combinations",      "Events");
    SetHistTitles(h_MultiPROF1, "Event Coincidence Degeneracy", "Combinations","Events");
    SetHistTitles(h_MultiPROF2, "Event Coincidence Degeneracy", "Combinations","Events");
    SetHistTitles(h_MultiPROF3, "Event Coincidence Degeneracy", "Combinations","Events");
  }

  for(unsigned int i = 0; i < vec_PROFCO.size(); i++)
  {
    for(unsigned int j = 0; j < vec_PROFCO[i].getMomentum().size(); j++)
    {
      h_CosTheta->Fill(vec_PROFCO[i].getCosTheta()[j]);  
      h_Momentum->Fill(vec_PROFCO[i].getMomentum()[j]);  
      h_Theta   ->Fill(vec_PROFCO[i].getTheta()[j]);
    }
    h_FibComb   ->Fill((vec_PROFCO[i].getNFibreCombinations()<=19 ? vec_PROFCO[i].getNFibreCombinations() : 20));
    h_MultiPROF1->Fill((vec_PROFCO[i].fMultiplicity[0]<=5 ? vec_PROFCO[i].fMultiplicity[0] : 6));
    h_MultiPROF2->Fill((vec_PROFCO[i].fMultiplicity[1]<=5 ? vec_PROFCO[i].fMultiplicity[1] : 6));
    h_MultiPROF3->Fill((vec_PROFCO[i].fMultiplicity[2]<=5 ? vec_PROFCO[i].fMultiplicity[2] : 6));
  }

  vec_PROFHist1D.push_back(h_CosTheta  );
  vec_PROFHist1D.push_back(h_Momentum  );
  vec_PROFHist1D.push_back(h_Theta     );
  vec_PROFHist1D.push_back(h_FibComb   );
  vec_PROFHist1D.push_back(h_MultiPROF1);
  vec_PROFHist1D.push_back(h_MultiPROF2);
  vec_PROFHist1D.push_back(h_MultiPROF3);

  return;
}

void plotTF(std::vector<TFCoincidenceRecord::TFCoincidence> &vec_TFCO, std::vector<TH1D*> &vec_TFHist1D, std::vector<TH2D*> &vec_TFHist2D, TString const &sType) 
{
  TH1D *h_TF      = new TH1D("h_TF_"     +sType,"h_TF_"      +sType, 50,    0,  500);
  TH1D *h_MultiUS = new TH1D("h_MultiUS_"+sType, "h_MultiUS_"+sType,  7, -0.5,  6.5); 
  TH1D *h_MultiDS = new TH1D("h_MultiDS_"+sType, "h_MultiDS_"+sType,  7, -0.5,  6.5); 

  if(sType=="UNIQ")
  {
    SetHistTitles(h_TF,      "Time of Flight from XBTFs, Unique Events", "Time, (ns)",   "Events");
    SetHistTitles(h_MultiUS, "Event Coincidence Degeneracy, US",         "Combinations", "Events");
    SetHistTitles(h_MultiDS, "Event Coincidence Degeneracy, DS",         "Combinations", "Events");
  }
  else
  {
    SetHistTitles(h_TF,      "Time of Flight from XBTFs, Degenerate Events", "Time, (ns)",   "Events");
    SetHistTitles(h_MultiUS, "Event Coincidence Degeneracy, US",             "Combinations", "Events");
    SetHistTitles(h_MultiDS, "Event Coincidence Degeneracy, DS",             "Combinations", "Events");
  }

  for(unsigned int i = 0; i < vec_TFCO.size(); i++)
  {
    h_TF->Fill(vec_TFCO[i].fTF);
    h_MultiUS->Fill((vec_TFCO[i].fMultiplicity.first <=5 ? vec_TFCO[i].fMultiplicity.first  : 6));
    h_MultiDS->Fill((vec_TFCO[i].fMultiplicity.second<=5 ? vec_TFCO[i].fMultiplicity.second : 6));
  }

  vec_TFHist1D.push_back(h_TF);
  vec_TFHist1D.push_back(h_MultiUS);
  vec_TFHist1D.push_back(h_MultiDS);

  return;
}

int main(int argc, char *argv[])
{
  gROOT->ProcessLine("#include <vector>");
  std::string s_OutDir = "/scratch/BeamInstOutput/Histograms_BL/";

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

    BeamLine beamline;
    //FINDS AND FILLS THE TF COINCIDENCE RECORD VARIABLE IN OUR INSTANCE OF BEAMLINE.
    std::cout << "\nDATA UNPACKED, FINDING COINCIDENCES IN TF" << std::endl;
    beamline.findTFCoincidences  (map_Detector);
    //FINDS AND FILLS THE PROF COINCIDENCE RECORD VARIABLE IN OUR INSTANCE OF BEAMLINE.
    std::cout << "\nFINDING COINCIDENCES IN PROF" << std::endl;
    beamline.findPROFCoincidences(map_Detector);

    //beamline.printTFCoincidencesDegenerate(map_Detector);
    //beamline.printTFCoincidencesUnique(map_Detector);
    //beamline.printPROFCoincidencesDegenerate(map_Detector);
    //beamline.printPROFCoincidencesUnique(map_Detector);

    std::vector<PROFCoincidenceRecord::PROFCoincidence> vec_PROFCO_Degen = beamline.getPROFCoincidencesDegenerate();
    std::vector<PROFCoincidenceRecord::PROFCoincidence> vec_PROFCO_Uniq  = beamline.getPROFCoincidencesUnique();
    std::vector<TFCoincidenceRecord::TFCoincidence>     vec_TFCO_Degen   = beamline.getTFCoincidencesDegenerate();
    std::vector<TFCoincidenceRecord::TFCoincidence>     vec_TFCO_Uniq    = beamline.getTFCoincidencesUnique();

    std::vector<TH1D*> vec_PROFHist1D;
    std::vector<TH2D*> vec_PROFHist2D;
    std::vector<TH1D*> vec_TFHist1D;
    std::vector<TH2D*> vec_TFHist2D;

    std::cout << "\nFINDING DONE, MAKING PLOTS" << std::endl;
    plotPROF(vec_PROFCO_Degen, vec_PROFHist1D, vec_PROFHist2D, "DEGEN"); 
    plotPROF(vec_PROFCO_Uniq,  vec_PROFHist1D, vec_PROFHist2D, "UNIQ" ); 
    plotTF  (vec_TFCO_Degen,     vec_TFHist1D,   vec_TFHist2D, "DEGEN");
    plotTF  (vec_TFCO_Uniq,      vec_TFHist1D,   vec_TFHist2D, "UNIQ" );

    std::string s_FirstFile = vec_DataPath.at(0);
    std::string s_LastFile  = vec_DataPath.at(vec_DataPath.size()-1);
    std::string s_FirstTime = s_FirstFile.substr(s_FirstFile.length()-15,10);
    std::string s_LastTime  = s_LastFile .substr(s_LastFile .length()-15,10);

    TFile *f_Out = new TFile((TString)s_OutDir+"Analyse_BL_ToHist_"+(TString)s_FirstTime+"_"+(TString)s_LastTime+".root","RECREATE");
    TDirectory *dir_PROF = f_Out->mkdir("PROF");
    dir_PROF->cd();
    for(auto hist : vec_PROFHist1D){hist->Write();}
    for(auto hist : vec_PROFHist2D){hist->Write();}
    TDirectory *dir_TF = f_Out->mkdir("TF");
    dir_TF->cd();
    for(auto hist : vec_TFHist1D){hist->Write();}
    for(auto hist : vec_TFHist2D){hist->Write();}

    f_Out->Close();
    delete f_Out;

    std::ofstream latestFile;
    latestFile.open(s_OutDir+"latestHistFile.txt");
    latestFile << s_OutDir+"Analyse_BL_ToHist_"+s_FirstTime+"_"+s_LastTime+".root" << std::endl;
    latestFile.close();

    std::cout << "\nHISTOGRAMS DONE!\n" << std::endl;
  }
  else
  {
    std::cout << "BEAMLINE: NO NEW DATA FILES!" << std::endl;
  }

  return 0;
}
