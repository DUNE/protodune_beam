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
                                                                           +(TString)it_Detector.second.getDetName(),1000,    0,   5e9); 
      TH1I *h_TriggerTimeSinceFirst  = new TH1I("h_TriggerTimeSinceFirst_" +(TString)it_Detector.second.getDetName(),"h_TriggerTimeSinceFirst_" 
                                                                           +(TString)it_Detector.second.getDetName(),1000,    0,   5e9); 
      TH1D *h_NHitsPerFibre          = new TH1D("h_NHitsPerFibre_"         +(TString)it_Detector.second.getDetName(),"h_NHitsPerFibre_"
                                                                           +(TString)it_Detector.second.getDetName(), 193, -0.5, 192.5);

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

      TH1I *h_EventTS_SecondsPart     = new TH1I("h_EventTS_SecondsPart_"    +(TString)it_Detector.second.getDetName(),"h_EventTS_SecondsPart_"             
                                                                             +(TString)it_Detector.second.getDetName(),1000, tLow, upperbin);
      TH1I *h_EventTS_NanosecondsPart = new TH1I("h_EventTS_NanosecondsPart_"+(TString)it_Detector.second.getDetName(),"h_EventTS_NanosecondsPart_"             
                                                                             +(TString)it_Detector.second.getDetName(),1000, 0, 1e9);
      TH1I *h_EventTS                 = new TH1I("h_EventTS_"                +(TString)it_Detector.second.getDetName(),"h_EventTS_"               
                                                                             +(TString)it_Detector.second.getDetName(),1000, tLow, upperbin); 
      TH1I *h_EventTimeSinceFirst     = new TH1I("h_EventTimeSinceFirst_"    +(TString)it_Detector.second.getDetName(),"h_EventTimeSinceFirst_"   
                                                                             +(TString)it_Detector.second.getDetName(),1000,    0,   5e9); 
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

int main(int argc, char *argv[])
{
  gROOT->ProcessLine("#include <vector>");
  std::string s_OutDir = "/scratch/BeamInstOutput/Histograms_BI/";

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
      std::string s_DetType = s_DetName.substr(0,4);

      Detector detector(s_DetName, s_DetType, "XBH4_"+s_DetType+"_022_"+s_DetName.substr(7,9));
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

    std::string s_FirstFile = vec_DataPath.at(0);
    std::string s_LastFile  = vec_DataPath.at(vec_DataPath.size()-1);
    std::string s_FirstTime = s_FirstFile.substr(s_FirstFile.length()-15,10);
    std::string s_LastTime  = s_LastFile .substr(s_LastFile .length()-15,10);

    TFile *f_Out = new TFile((TString)s_OutDir+"Analyse_BI_ToHist_"+(TString)s_FirstTime+"_"+(TString)s_LastTime+".root","RECREATE");
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

    f_Out->Close();
    delete f_Out;

    std::ofstream latestFile;
    latestFile.open(s_OutDir+"latestHistFile.txt");
    latestFile << s_OutDir+"Analyse_BI_ToHist_"+s_FirstTime+"_"+s_LastTime+".root" << std::endl;
    latestFile.close();

    std::cout << "\nHISTOGRAMS DONE!\n" << std::endl;
  }
  else
  {
    std::cout << "DETECTORS: NO NEW DATA FILES!" << std::endl;
  }

  return 0;
}
