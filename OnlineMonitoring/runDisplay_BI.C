#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "runDisplay.h"
#include "colors.h"


int runDisplay_BI()
{
  long startTime = std::time(0);
  std::string lastFile = "";

  std::vector<int> vec_Colors = getColors(2);

  TCanvas *c_XBPF_0 = new TCanvas("c_XBPF_0","XBPF Display 0",1300,550);
  c_XBPF_0->Divide(3,2);
  TCanvas *c_XBPF_1 = new TCanvas("c_XBPF_1","XBPF Display 1",1300,550);
  c_XBPF_1->Divide(3,2);
  TCanvas *c_XBTF_0 = new TCanvas("c_XBTF_0","XBTF Display 0",1300,550);
  c_XBTF_0->Divide(3,1);
  TCanvas *c_XBTF_1 = new TCanvas("c_XBTF_1","XBTF Display 1",1300,550);
  c_XBTF_1->Divide(3,2);
  std::map<TString,std::pair<TCanvas*,int>> map_StkToPad;
  map_StkToPad["stk_XBPF_dTAcq"]                   = {c_XBPF_1, 1};
  map_StkToPad["stk_XBPF_NEventsPerAcq"]           = {c_XBPF_0, 1};
  map_StkToPad["stk_XBPF_FracBuffer"]              = {c_XBPF_0, 2};
  map_StkToPad["stk_XBPF_NFibresPerEvent"]         = {c_XBPF_0, 3};
  map_StkToPad["stk_XBPF_Span"]                    = {c_XBPF_0, 4};
  map_StkToPad["stk_XBPF_EventTS"]                 = {c_XBPF_1, 2};
  map_StkToPad["stk_XBPF_EventTimeSinceFirst"]     = {c_XBPF_1, 3};
  map_StkToPad["stk_XBPF_TriggerTS"]               = {c_XBPF_1, 4};
  map_StkToPad["stk_XBPF_TriggerTimeSinceFirst"]   = {c_XBPF_1, 5};
  map_StkToPad["stk_XBPF_NHitsPerFibre"]           = {c_XBPF_0, 5};
  map_StkToPad["stk_XBTF_dTAcq"]                   = {c_XBTF_1, 1};
  map_StkToPad["stk_XBTF_NEventsPerAcq"]           = {c_XBTF_0, 1};
  map_StkToPad["stk_XBTF_FracBuffer"]              = {c_XBTF_0, 2};
  map_StkToPad["stk_XBTF_EventTS_SecondsPart"]     = {c_XBTF_1, 2};
  map_StkToPad["stk_XBTF_EventTS_NanosecondsPart"] = {c_XBTF_1, 3};
  map_StkToPad["stk_XBTF_EventTS"]                 = {c_XBTF_1, 4};
  map_StkToPad["stk_XBTF_EventTimeSinceFirst"]     = {c_XBTF_1, 5};

  std::map<TString,std::vector<TString>> map_StkToTitles;
  map_StkToTitles["stk_XBPF_dTAcq"]                   = {"Time Between DIP Data Acquisitions", "Time, (s)", "Acquisition Pairs"};
  map_StkToTitles["stk_XBPF_NEventsPerAcq"]           = {"Number of Events / Acqusition", "No. Events", "Acquisitions"};
  map_StkToTitles["stk_XBPF_FracBuffer"]              = {"Fraction of EventsData Array Filled", "Fraction", "Acquisitions"};
  map_StkToTitles["stk_XBPF_NFibresPerEvent"]         = {"Number of Fibres Hit / Event", "No. Fibres", "Events"};
  map_StkToTitles["stk_XBPF_Span"]                    = {"Hit Fibre Span", "Difference in Fibre No.", "Events"};
  map_StkToTitles["stk_XBPF_EventTS"]                 = {"Event Timestamp", "Unix Time", "Events"};
  map_StkToTitles["stk_XBPF_EventTimeSinceFirst"]     = {"Event Time Elapsed Since First Event", "Time Elapsed, (ns)", "Events"};
  map_StkToTitles["stk_XBPF_TriggerTS"]               = {"Trigger Timestamp", "Unix Time", "Triggers"};
  map_StkToTitles["stk_XBPF_TriggerTimeSinceFirst"]   = {"Trigger Time Elapsed Since First Trigger", "Time Elapsed, (ns)", "Triggers"};
  map_StkToTitles["stk_XBPF_NHitsPerFibre"]           = {"Number of Hits / Fibre", "Fibre No.", "Hits"};
  map_StkToTitles["stk_XBTF_dTAcq"]                   = {"Time Between DIP Data Acquisitions", "Time, (s)", "Acquisition Pairs"};
  map_StkToTitles["stk_XBTF_NEventsPerAcq"]           = {"Number of Events / Acqusition", "No. Events", "Acquisitions"};
  map_StkToTitles["stk_XBTF_FracBuffer"]              = {"Fraction of EventsData Array Filled", "Fraction", "Acquisitions"};
  map_StkToTitles["stk_XBTF_EventTS_SecondsPart"]     = {"Event Timestamp Seconds Part", "Unix Time", "Events"};
  map_StkToTitles["stk_XBTF_EventTS_NanosecondsPart"] = {"Event Timestamp Nanoseconds Part", "Time, (ns)", "Events"};
  map_StkToTitles["stk_XBTF_EventTS"]                 = {"Event Timestamp", "Time, (s)", "Events"};
  map_StkToTitles["stk_XBTF_EventTimeSinceFirst"]     = {"Event Time Elapsed Since First Event", "Time Elapsed, (ns)", "Events"};

  std::vector<TH1*> vec;
  std::map<TString,std::vector<TH1*>> map_Hist_XBPF;
  map_Hist_XBPF["dTAcq"]                   = vec;
  map_Hist_XBPF["NEventsPerAcq"]           = vec;
  map_Hist_XBPF["FracBuffer"]              = vec;
  map_Hist_XBPF["NFibresPerEvent"]         = vec;
  map_Hist_XBPF["Span"]                    = vec;
  map_Hist_XBPF["EventTS"]                 = vec;
  map_Hist_XBPF["EventTimeSinceFirst"]     = vec;
  map_Hist_XBPF["TriggerTS"]               = vec;
  map_Hist_XBPF["TriggerTimeSinceFirst"]   = vec;
  map_Hist_XBPF["NHitsPerFibre"]           = vec;

  std::map<TString,std::vector<TH1*>> map_Hist_XBTF;
  map_Hist_XBTF["dTAcq"]                   = vec;
  map_Hist_XBTF["NEventsPerAcq"]           = vec;
  map_Hist_XBTF["FracBuffer"]              = vec;
  map_Hist_XBTF["EventTS_SecondsPart"]     = vec;
  map_Hist_XBTF["EventTS_NanosecondsPart"] = vec;
  map_Hist_XBTF["EventTS"]                 = vec;
  map_Hist_XBTF["EventTimeSinceFirst"]     = vec;

  while(std::time(0) < startTime + monitorTime)
  {
    std::ifstream latestFile;
    latestFile.open("/scratch/BeamInstOutput/Histograms_BI/latestHistFile.txt");
    std::string latestFilePath = "";
    latestFile >> latestFilePath;
    latestFile.close();

    std::cout << "LATEST FILE PATH: " << latestFilePath << std::endl;
    if(latestFilePath!=lastFile)
    {
      time_t now = std::time(0);
      std::string s_Time = std::ctime(&now);

      map_Hist_XBPF["dTAcq"]                  .clear();
      map_Hist_XBPF["NEventsPerAcq"]          .clear();
      map_Hist_XBPF["FracBuffer"]             .clear();
      map_Hist_XBPF["NFibresPerEvent"]        .clear();
      map_Hist_XBPF["Span"]                   .clear();
      map_Hist_XBPF["EventTS"]                .clear();
      map_Hist_XBPF["EventTimeSinceFirst"]    .clear();
      map_Hist_XBPF["TriggerTS"]              .clear();
      map_Hist_XBPF["TriggerTimeSinceFirst"]  .clear();
      map_Hist_XBPF["NHitsPerFibre"]          .clear();

      map_Hist_XBTF["dTAcq"]                  .clear();
      map_Hist_XBTF["NEventsPerAcq"]          .clear();
      map_Hist_XBTF["FracBuffer"]             .clear();
      map_Hist_XBTF["EventTS_SecondsPart"]    .clear();
      map_Hist_XBTF["EventTS_NanosecondsPart"].clear();
      map_Hist_XBTF["EventTS"]                .clear();
      map_Hist_XBTF["EventTimeSinceFirst"]    .clear();

      TFile *f_Latest = new TFile((TString)latestFilePath,"OPEN");
      TIter  iter(f_Latest->GetListOfKeys());
      TKey  *key;

      while((key=(TKey*)iter()))
      {
        TDirectory *dir = (TDirectory*)key->ReadObj();
        dir->cd();
        TIter iter_hist(dir->GetListOfKeys());
        TKey *key_hist;
        int plotCount = 0;
        while((key_hist=(TKey*)iter_hist()))
        {
          if(((std::string)dir->GetName()).find("XBPF")!=std::string::npos)
          {
            TH1 *h = (TH1*)key_hist->ReadObj();
            if(plotCount==0)     {map_Hist_XBPF["dTAcq"].push_back(h);}
            else if(plotCount==1){map_Hist_XBPF["NEventsPerAcq"].push_back(h);}
            else if(plotCount==2){map_Hist_XBPF["FracBuffer"].push_back(h);}
            else if(plotCount==3){map_Hist_XBPF["NFibresPerEvent"].push_back(h);}
            else if(plotCount==4){map_Hist_XBPF["Span"].push_back(h);}
            else if(plotCount==5){map_Hist_XBPF["TriggerTS"].push_back(h);}
            else if(plotCount==6){map_Hist_XBPF["EventTS"].push_back(h);}
            else if(plotCount==7){map_Hist_XBPF["TriggerTimeSinceFirst"].push_back(h);}
            else if(plotCount==8){map_Hist_XBPF["EventTimeSinceFirst"].push_back(h);}
            else if(plotCount==9){map_Hist_XBPF["NHitsPerFibre"].push_back(h);}
            plotCount++;
          }
          else
          {
            TH1 *h = (TH1*)key_hist->ReadObj();
            if(plotCount==0)     {map_Hist_XBTF["dTAcq"].push_back(h);}
            else if(plotCount==1){map_Hist_XBTF["NEventsPerAcq"].push_back(h);}
            else if(plotCount==2){map_Hist_XBTF["FracBuffer"].push_back(h);}
            else if(plotCount==3){map_Hist_XBTF["EventTS_SecondsPart"].push_back(h);}
            else if(plotCount==4){map_Hist_XBTF["EventTS_NanosecondsPart"].push_back(h);}
            else if(plotCount==5){map_Hist_XBTF["EventTS"].push_back(h);}
            else if(plotCount==6){map_Hist_XBTF["EventTimeSinceFirst"].push_back(h);}
            plotCount++;
          }
        }
      }

      TLegend *leg_XBPF = new TLegend(0.1,0.1,0.9,0.9);
      TLegend *leg_XBTF = new TLegend(0.1,0.1,0.9,0.9);
      bool firstLoop_XBPF = true;
      bool firstLoop_XBTF = true;
      for(auto hist : map_Hist_XBPF)
      {
        if(hist.second.size()!=0)
        {
          TString stk = "stk_XBPF_"+hist.first;
          map_StkToPad[stk].first->cd(map_StkToPad[stk].second);
          double maxY = hist.second.at(0)->GetBinContent(hist.second.at(0)->GetMaximumBin());
          hist.second.at(0)->SetLineColor(vec_Colors.at(0));
          hist.second.at(0)->SetTitle(map_StkToTitles[stk].at(0));
          hist.second.at(0)->GetXaxis()->SetTitle(map_StkToTitles[stk].at(1));
          hist.second.at(0)->GetYaxis()->SetTitle(map_StkToTitles[stk].at(2));
          TString histName = hist.second.at(0)->GetName();
          if(firstLoop_XBPF){leg_XBPF->AddEntry(hist.second.at(0), (TString)histName(histName.Length()-10,10), "L");}
          hist.second.at(0)->Draw();
          for(unsigned int i = 1; i < hist.second.size(); i++)
          {
            if(hist.second.at(i)->GetBinContent(hist.second.at(i)->GetMaximumBin())>maxY){maxY = hist.second.at(1)->GetBinContent(hist.second.at(1)->GetMaximumBin());}
            hist.second.at(i)->SetLineColor(vec_Colors.at(i));
            TString histName = hist.second.at(i)->GetName();
            if(firstLoop_XBPF){leg_XBPF->AddEntry(hist.second.at(i), (TString)histName(histName.Length()-10,10), "L");}
            hist.second.at(i)->Draw("SAME");
          }
          hist.second.at(0)->GetYaxis()->SetRangeUser(0, maxY+maxY*0.1);
          map_StkToPad[stk].first->Update();
          map_StkToPad[stk].first->Modified();
          firstLoop_XBPF = false;
        }
      }
      c_XBPF_0->cd(6);
      c_XBPF_0->SetTitle("XBPF Display 0, LAST UPDATED "+(TString)s_Time);
      leg_XBPF->Draw();
      c_XBPF_0->Update();
      c_XBPF_0->Modified();
      c_XBPF_1->cd(6);
      c_XBPF_1->SetTitle("XBPF Display 1, LAST UPDATED "+(TString)s_Time);
      leg_XBPF->Draw();
      c_XBPF_1->Update();
      c_XBPF_1->Modified();
      for(auto hist : map_Hist_XBTF)
      {
        if(hist.second.size()!=0)
        {
          TString stk = "stk_XBTF_"+hist.first;
          map_StkToPad[stk].first->cd(map_StkToPad[stk].second);
          double maxY = hist.second.at(0)->GetBinContent(hist.second.at(0)->GetMaximumBin());
          hist.second.at(0)->SetLineColor(vec_Colors.at(0));
          hist.second.at(0)->SetTitle(map_StkToTitles[stk].at(0));
          hist.second.at(0)->GetXaxis()->SetTitle(map_StkToTitles[stk].at(1));
          hist.second.at(0)->GetYaxis()->SetTitle(map_StkToTitles[stk].at(2));
          hist.second.at(0)->SetLineColor(vec_Colors.at(0));
          TString histName = hist.second.at(0)->GetName();
          if(firstLoop_XBTF){leg_XBTF->AddEntry(hist.second.at(0), (TString)histName(histName.Length()-10,10), "L");}
          hist.second.at(0)->Draw();
          for(unsigned int i = 1; i < hist.second.size(); i++)
          {
            if(hist.second.at(i)->GetBinContent(hist.second.at(i)->GetMaximumBin())>maxY){maxY = hist.second.at(1)->GetBinContent(hist.second.at(1)->GetMaximumBin());}
            hist.second.at(i)->SetLineColor(vec_Colors.at(i));
            TString histName = hist.second.at(i)->GetName();
            if(firstLoop_XBTF){leg_XBTF->AddEntry(hist.second.at(i), (TString)histName(histName.Length()-10,10), "L");}
            hist.second.at(i)->Draw("SAME");
          }
          hist.second.at(0)->GetYaxis()->SetRangeUser(0, maxY+maxY*0.1);
          map_StkToPad[stk].first->Update();
          map_StkToPad[stk].first->Modified();
          firstLoop_XBTF = false;
        }
      }
      c_XBTF_0->cd(3);
      c_XBTF_0->SetTitle("XBTF Display 0, LAST UPDATED "+(TString)s_Time);
      leg_XBTF->Draw();
      c_XBTF_0->Update();
      c_XBTF_0->Modified();
      c_XBTF_1->cd(6);
      c_XBTF_1->SetTitle("XBTF Display 1, LAST UPDATED "+(TString)s_Time);
      leg_XBTF->Draw();
      c_XBPF_1->Update();
      c_XBPF_1->Modified();

      lastFile = latestFilePath;
      delete f_Latest;
      delete leg_XBPF;
      delete leg_XBTF;
    }

    gSystem->Sleep(1000*updateEvery);
  }

  std::cout << "MONITORING TIME FINISHED" << std::endl;

  return 0;
}
