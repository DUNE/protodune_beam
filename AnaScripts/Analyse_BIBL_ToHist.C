#include "BeamLineClasses/class_BeamLine.h"
#include "BeamLineClasses/unpack.h"
#include <fstream>
#include <sstream>
#include <inttypes.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TROOT.h>


void plot_dTAcq(std::map<std::string,Detector> &map_Detector, std::map<std::string,std::vector<TH1I*>> &map_NameToVecHist_I)
{
  for(auto it_Detector : map_Detector)
  {
    if(it_Detector.second.getType()=="XBPF")
    {
      TH1I *h_dTAcq = new TH1I("h_dTAcq_"+(TString)it_Detector.second.getDetName(),"h_dTAcq_"+(TString)it_Detector.second.getDetName(), 71, -0.5, 70.5);

      SetHistTitles(h_dTAcq, "Time Between DIP Data Acquisitions", "Time, (s)", "Acquisition Pairs");

      std::vector<AcquisitionXBPF> vec_DetAcq;
      it_Detector.second.getAcquisitions(vec_DetAcq);
      if(vec_DetAcq.size()!=0)
      {
        for(unsigned int j = 0; j < vec_DetAcq.size()-1; j++)
        {
          double dTAcq = vec_DetAcq.at(j+1).getTimestamp() - vec_DetAcq.at(j).getTimestamp();
          h_dTAcq->Fill(dTAcq);
        }
      }
      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_dTAcq);
    }
    else if(it_Detector.second.getType()=="XBTF")
    {
      TH1I *h_dTAcq = new TH1I("h_dTAcq_"+(TString)it_Detector.second.getDetName(),"h_dTAcq_"+(TString)it_Detector.second.getDetName(), 71, -0.5, 70.5);

      SetHistTitles(h_dTAcq, "Time Between DIP Data Acquisitions", "Time, (s)", "Acquisition Pairs");

      std::vector<AcquisitionXBTF> vec_DetAcq;
      it_Detector.second.getAcquisitions(vec_DetAcq);
      if(vec_DetAcq.size()!=0)
      {
        for(unsigned int j = 0; j < vec_DetAcq.size()-1; j++)
        {
          double dTAcq = vec_DetAcq.at(j+1).getTimestamp() - vec_DetAcq.at(j).getTimestamp();
          h_dTAcq->Fill(dTAcq);
        }
      }
      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_dTAcq);
    }
  }

  return;
}

void plot_AcqLevel(std::map<std::string,Detector> &map_Detector, std::map<std::string,std::vector<TH1I*>> &map_NameToVecHist_I)
{
  for(auto it_Detector : map_Detector)
  {
    if(it_Detector.second.getType()=="XBPF")
    {
      TH1I *h_NEventsPerAcq = new TH1I("h_NEventsPerAcq_"+(TString)it_Detector.second.getDetName(),"h_NEventsPerAcq_"+(TString)it_Detector.second.getDetName(), 3001, -0.5, 3000.5);
      TH1I *h_FracBuffer    = new TH1I("h_FracBuffer_"   +(TString)it_Detector.second.getDetName(),"h_FracBuffer_"   +(TString)it_Detector.second.getDetName(), 11,  -0.05,   1.05);

      SetHistTitles(h_NEventsPerAcq, "Number of Events / Acqusition",       "No. Events", "Acquisitions");
      SetHistTitles(h_FracBuffer,    "Fraction of EventsData Array Filled", "Fraction",   "Acquisitions");

      std::vector<AcquisitionXBPF> vec_DetAcq;
      it_Detector.second.getAcquisitions(vec_DetAcq);
      for(unsigned int j = 0; j < vec_DetAcq.size(); j++)
      {
        h_NEventsPerAcq->Fill(vec_DetAcq.at(j).getNEventRec());
        h_FracBuffer->Fill(vec_DetAcq.at(j).getNEventRec()/(double)3000);
      }
      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_NEventsPerAcq);
      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_FracBuffer);
    }
    else if(it_Detector.second.getType()=="XBTF")
    {
      TH1I *h_NEventsPerAcq = new TH1I("h_NEventsPerAcq_"+(TString)it_Detector.second.getDetName(),"h_NEventsPerAcq_"+(TString)it_Detector.second.getDetName(), 30001, -0.5, 30000.5);
      TH1I *h_FracBuffer    = new TH1I("h_FracBuffer_"   +(TString)it_Detector.second.getDetName(),"h_FracBuffer_"   +(TString)it_Detector.second.getDetName(), 11,  -0.05,   1.05);

      SetHistTitles(h_NEventsPerAcq, "Number of Events / Acqusition",       "No. Events", "Acquisitions");
      SetHistTitles(h_FracBuffer,    "Fraction of EventsData Array Filled", "Fraction",   "Acquisitions");

      std::vector<AcquisitionXBTF> vec_DetAcq;
      it_Detector.second.getAcquisitions(vec_DetAcq);
      for(unsigned int j = 0; j < vec_DetAcq.size(); j++)
      {
        h_NEventsPerAcq->Fill(vec_DetAcq.at(j).getTimestampCount());
        h_FracBuffer->Fill(vec_DetAcq.at(j).getTimestampCount()/(double)30000);
      }
      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_NEventsPerAcq);
      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_FracBuffer);
    }
  }

  return;
}

void plot_EventLevel(std::map<std::string,Detector> &map_Detector, std::map<std::string,std::vector<TH1I*>> &map_NameToVecHist_I, std::map<std::string,std::vector<TH1D*>> &map_NameToVecHist_D)
{
  for(auto it_Detector : map_Detector)
  {
    if(it_Detector.second.getType()=="XBPF")
    {
      double tLow        = it_Detector.second.getFirstTriggerTimestamp();   
      double tHigh       = it_Detector.second.getLastTriggerTimestamp();   
      double timeElapsed = tHigh - tLow;
      double sensitivity = 1.e-3;
      long   nBins       = std::ceil(timeElapsed/sensitivity);
      double upperbin    = tLow + (double)nBins*(double)sensitivity;
      if(tLow==2.e9)
      {
        nBins = 1;
        tLow  = it_Detector.second.getFirstTimestamp();
        upperbin = tLow + sensitivity;
      }

      TH1I *h_NFibresPerEvent        = new TH1I("h_NFibresPerEvent_"       +(TString)it_Detector.second.getDetName(),"h_NFibresPerEvent_"       
                                                                           +(TString)it_Detector.second.getDetName(),  11, -0.5,  10.5);
      TH1I *h_Span                   = new TH1I("h_Span_"                  +(TString)it_Detector.second.getDetName(),"h_Span_"                  
                                                                           +(TString)it_Detector.second.getDetName(),   7, -0.5,   6.5);
      TH1I *h_TriggerTS              = new TH1I("h_TriggerTS_"             +(TString)it_Detector.second.getDetName(),"h_TriggerTS_"             
                                                                           +(TString)it_Detector.second.getDetName(),nBins, tLow, upperbin);
      TH1I *h_EventTS                = new TH1I("h_EventTS_"               +(TString)it_Detector.second.getDetName(),"h_EventTS_"               
                                                                           +(TString)it_Detector.second.getDetName(),nBins, tLow, upperbin); 
      TH1I *h_EventTimeSinceFirst    = new TH1I("h_EventTimeSinceFirst_"   +(TString)it_Detector.second.getDetName(),"h_EventTimeSinceFirst_"   
                                                                           +(TString)it_Detector.second.getDetName(),100,    0,   5e9); 
      TH1I *h_TriggerTimeSinceFirst  = new TH1I("h_TriggerTimeSinceFirst_" +(TString)it_Detector.second.getDetName(),"h_TriggerTimeSinceFirst_" 
                                                                           +(TString)it_Detector.second.getDetName(),100,    0,   5e9); 
      TH1D *h_NHitsPerFibre          = new TH1D("h_NHitsPerFibre_"         +(TString)it_Detector.second.getDetName(),"h_NHitsPerFibre_"
                                                                           +(TString)it_Detector.second.getDetName(), 193, -0.5, 192.5);

      SetHistTitles(h_NFibresPerEvent      , "Number of Fibres Hit / Event",             "No. Fibres",              "Events"  ); 
      SetHistTitles(h_Span                 , "Hit Fibre Span",                           "Difference in Fibre No.", "Events"  ); 
      SetHistTitles(h_TriggerTS            , "Trigger Timestamp",                        "Unix Time",               "Triggers"); 
      SetHistTitles(h_EventTS              , "Event Timestamp",                          "Unix Time",               "Events"  ); 
      SetHistTitles(h_EventTimeSinceFirst  , "Event Time Elapsed Since First Event",     "Time Elapsed, (ns)",      "Events"  ); 
      SetHistTitles(h_TriggerTimeSinceFirst, "Trigger Time Elapsed Since First Trigger", "Time Elapsed, (ns)",      "Triggers"); 
      SetHistTitles(h_NHitsPerFibre        , "Number of Hits / Fibre",                   "Fibre No.",               "Hits"    ); 

      std::vector<AcquisitionXBPF> vec_DetAcq;
      it_Detector.second.getAcquisitions(vec_DetAcq);
      unsigned int eventCount = 0;
      for(unsigned int j = 0; j < vec_DetAcq.size(); j++)
      {
        bool b_IsFirstRecord = true;
        AcquisitionXBPF::EventRecordHR firstRecord;
        unsigned int nEvents = vec_DetAcq.at(j).getDataHR().size();
        for(unsigned int k = 0; k < nEvents; k++)
        {
          if(b_IsFirstRecord)
          {
            firstRecord = vec_DetAcq.at(j).getDataHR().at(0);
            b_IsFirstRecord = false;
          }
          AcquisitionXBPF::EventRecordHR currentRecord = vec_DetAcq.at(j).getDataHR().at(k);

          h_NFibresPerEvent->Fill(currentRecord.fNFibresHit < 10 ? currentRecord.fNFibresHit : 10);
          h_Span     ->Fill((currentRecord.fSpan < 6) ? currentRecord.fSpan : 6);
          h_TriggerTS->Fill(currentRecord.fTriggerTimestamp/1.e9);
          h_EventTS  ->Fill(currentRecord.fEventTimestamp/1.e9);
          h_TriggerTimeSinceFirst->Fill(currentRecord.fTriggerTimestamp - firstRecord.fTriggerTimestamp);
          h_EventTimeSinceFirst  ->Fill(currentRecord.fEventTimestamp   - firstRecord.fEventTimestamp);
          for(unsigned int l = 0; l < currentRecord.fFibresList.size(); l++)
          {
            h_NHitsPerFibre->Fill(currentRecord.fFibresList[l]);
          }
        }
        eventCount+=nEvents;
      }
      /*
      if(eventCount!=0)
      {
        h_NHitsPerFibre->Scale(1./(double)eventCount);
      }*/

      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_NFibresPerEvent);
      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_Span);
      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_TriggerTS);
      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_EventTS);
      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_TriggerTimeSinceFirst);
      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_EventTimeSinceFirst);
      map_NameToVecHist_D[it_Detector.second.getDetName()].push_back(h_NHitsPerFibre);
    }
    else if(it_Detector.second.getType()=="XBTF")
    {
      double tLow  = it_Detector.second.getFirstTriggerTimestamp();   
      double tHigh = it_Detector.second.getLastTriggerTimestamp();   
      double timeElapsed = tHigh - tLow;
      double sensitivity = 1.e-3;
      int    nBins       = std::ceil(timeElapsed/sensitivity);
      double upperbin    = tLow + (double)nBins*(double)sensitivity;
      if(tLow==2.e9)
      {
        nBins = 1;
        tLow  = it_Detector.second.getFirstTimestamp();
        upperbin = tLow + sensitivity;
      }

      TH1I *h_EventTS_SecondsPart     = new TH1I("h_EventTS_SecondsPart_"    +(TString)it_Detector.second.getDetName(), "h_EventTS_SecondsPart_"             
                                                                             +(TString)it_Detector.second.getDetName(), 100, tLow, upperbin);
      TH1I *h_EventTS_NanosecondsPart = new TH1I("h_EventTS_NanosecondsPart_"+(TString)it_Detector.second.getDetName(), "h_EventTS_NanosecondsPart_"             
                                                                             +(TString)it_Detector.second.getDetName(), 100, 0, 1e9);
      TH1I *h_EventTS                 = new TH1I("h_EventTS_"                +(TString)it_Detector.second.getDetName(), "h_EventTS_"               
                                                                             +(TString)it_Detector.second.getDetName(), 100, tLow, upperbin); 
      TH1I *h_EventTimeSinceFirst     = new TH1I("h_EventTimeSinceFirst_"    +(TString)it_Detector.second.getDetName(), "h_EventTimeSinceFirst_"   
                                                                             +(TString)it_Detector.second.getDetName(), 100, 0, 5e9); 

      SetHistTitles(h_EventTS_SecondsPart,     "Event Timestamp Seconds Part",         "Unix Time",          "Events");
      SetHistTitles(h_EventTS_NanosecondsPart, "Event Timestamp Nanoseconds Part",     "Time, (ns)",         "Events");
      SetHistTitles(h_EventTS,                 "Event Timestamp",                      "Time, (s)",          "Events");
      SetHistTitles(h_EventTimeSinceFirst,     "Event Time Elapsed Since First Event", "Time Elapsed, (ns)", "Events");

      std::vector<AcquisitionXBTF> vec_DetAcq;
      it_Detector.second.getAcquisitions(vec_DetAcq);
      for(unsigned int j = 0; j < vec_DetAcq.size(); j++)
      {
        bool b_IsFirstRecord = true;
        AcquisitionXBTF::EventRecordHR firstRecord;
        for(unsigned int k = 0; k < vec_DetAcq.at(j).getDataHR().size(); k++)
        {
          if(b_IsFirstRecord)
          {
            firstRecord = vec_DetAcq.at(j).getDataHR().at(0);
            b_IsFirstRecord = false;
          }
          AcquisitionXBTF::EventRecordHR currentRecord = vec_DetAcq.at(j).getDataHR().at(k);

          h_EventTS_SecondsPart    ->Fill(currentRecord.fSeconds);
          h_EventTS_NanosecondsPart->Fill(currentRecord.fSubSeconds);
          h_EventTS                ->Fill(currentRecord.fSeconds_FullTime);
          h_EventTimeSinceFirst    ->Fill((((double)currentRecord.fSeconds-(double)firstRecord.fSeconds)+(currentRecord.fSubSeconds - firstRecord.fSubSeconds)/1.e9)*1.e9);
        }
      }

      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_EventTS_SecondsPart);
      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_EventTS_NanosecondsPart);
      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_EventTS);
      map_NameToVecHist_I[it_Detector.second.getDetName()].push_back(h_EventTimeSinceFirst);
    }
  }

  return;
}

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
  std::string s_OutDir = "/scratch/BeamInstOutput/Histograms_BIBL/";

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

    std::map<std::string,std::vector<TH1I*>> map_NameToVecHist_I;
    std::map<std::string,std::vector<TH1D*>> map_NameToVecHist_D;
    std::map<std::string,std::vector<TH1D*>> map_NameToVecHistBeamLine_D;

    std::cout << "\nUNPACKING DONE! MAKING SINGLE DETECTOR PLOTS..." << std::endl;
    plot_dTAcq     (map_Detector, map_NameToVecHist_I);
    plot_AcqLevel  (map_Detector, map_NameToVecHist_I);
    plot_EventLevel(map_Detector, map_NameToVecHist_I, map_NameToVecHist_D);

    BeamLine beamline;
    //FINDS AND FILLS THE TF COINCIDENCE RECORD VARIABLE IN OUR INSTANCE OF BEAMLINE.
    std::cout << "\nSINGLE DETECTOR PLOTS DONE, FINDING COINCIDENCES IN TF" << std::endl;
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

    TFile *f_Out = new TFile((TString)s_OutDir+"Analyse_BIBL_ToHist_"+(TString)s_FirstTime+"_"+(TString)s_LastTime+".root","RECREATE");
    for(auto detector : map_NameToVecHist_I)
    {
      TDirectory *dir = f_Out->mkdir((TString)detector.first);
      dir->cd();
      for(auto vec_Hist_I : detector.second)
      {
        vec_Hist_I->Write();
      }
    }

    for(auto detector : map_NameToVecHist_D)
    {
      TDirectory *dir = (TDirectory*)f_Out->Get((TString)detector.first);
      dir->cd();
      for(auto vec_Hist_D : detector.second)
      {
        vec_Hist_D->Write();
      }
    }

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
    latestFile << s_OutDir+"Analyse_BIBL_ToHist_"+s_FirstTime+"_"+s_LastTime+".root" << std::endl;
    latestFile.close();

    std::cout << "\nHISTOGRAMS DONE!\n" << std::endl;
  }
  else
  {
    std::cout << "DETECTORS AND BEAMLINE: NO NEW DATA FILES!" << std::endl;
  }

  return 0;
}
