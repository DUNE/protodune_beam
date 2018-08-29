#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "runDisplay.h"
#include "colors.h"


int runDisplay_BIBL()
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

  TCanvas *c_TF  = new TCanvas("c_TF","TF Display", 1300,550);
  c_TF->Divide(2,2);
  TCanvas *c_PROF = new TCanvas("c_PROF","PROF Display",1300,550);
  c_PROF->Divide(3,2);
  std::map<TString,std::pair<TCanvas*,int>> map_HistToPad_TF;
  map_HistToPad_TF["h_TF_UNIQ"]            = {c_TF,  1};
  map_HistToPad_TF["h_TF_DEGEN"]           = {c_TF,  2};
  map_HistToPad_TF["h_MultiUS_DEGEN"]      = {c_TF,  3};
  map_HistToPad_TF["h_MultiDS_DEGEN"]      = {c_TF,  3};
  std::map<TString,std::pair<TCanvas*,int>> map_HistToPad_PROF;
  map_HistToPad_PROF["h_Theta_UNIQ"]       = {c_PROF, 1};
  map_HistToPad_PROF["h_Momentum_UNIQ"]    = {c_PROF, 2};
  map_HistToPad_PROF["h_Theta_DEGEN"]      = {c_PROF, 4};
  map_HistToPad_PROF["h_Momentum_DEGEN"]   = {c_PROF, 5};
  map_HistToPad_PROF["h_FibComb_DEGEN"]    = {c_PROF, 3};
  map_HistToPad_PROF["h_MultiPROF1_DEGEN"] = {c_PROF, 6};
  map_HistToPad_PROF["h_MultiPROF2_DEGEN"] = {c_PROF, 6};
  map_HistToPad_PROF["h_MultiPROF3_DEGEN"] = {c_PROF, 6};

  std::map<TString,std::vector<TString>> map_HistToTitles;
  map_HistToTitles["h_TF_UNIQ"]          = {"Time of Flight from XBTFs","Time, (ns)","Events"};
  map_HistToTitles["h_TF_DEGEN"]         = {"Time of Flight from XBTFs","Time, (ns)","Events"};
  map_HistToTitles["h_MultiUS_DEGEN"]    = {"Event Coincidence Degeneracy","Combinations","Events"};
  map_HistToTitles["h_MultiDS_DEGEN"]    = {"Event Coincidence Degeneracy","Combinations","Events"};
  map_HistToTitles["h_Theta_UNIQ"]       = {"Deflection Angle, Unique Events","Deflection, (Deg)","Events"};
  map_HistToTitles["h_Momentum_UNIQ"]    = {"Momentum, Unique Events","Momentum, (GeV)","Events"};
  map_HistToTitles["h_Theta_DEGEN"]      = {"Deflection Angle, Degenerate Events","Deflection,(Deg)","Events"};
  map_HistToTitles["h_Momentum_DEGEN"]   = {"Momentum, Degenerate Events","Momentum, (GeV)","Events"};
  map_HistToTitles["h_FibComb_DEGEN"]    = {"Number of Possible Fibre Combinations / Degenerate Event","Combinations","Events"};
  map_HistToTitles["h_MultiPROF1_DEGEN"] = {"Event Coincidence Degeneracy","Combinations","Events"};
  map_HistToTitles["h_MultiPROF2_DEGEN"] = {"Event Coincidence Degeneracy","Combinations","Events"};
  map_HistToTitles["h_MultiPROF3_DEGEN"] = {"Event Coincidence Degeneracy","Combinations","Events"};

  std::map<TString,std::vector<TH1*>> map_StkToHists_PROF;
  std::map<TString,std::vector<TH1*>> map_StkToHists_TF;

  while(std::time(0) < startTime + monitorTime)
  {
    std::ifstream latestFile;
    latestFile.open("/scratch/BeamInstOutput/Histograms_BIBL/latestHistFile.txt");
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
        if((std::string)dir->GetName()!="PROF" && (std::string)dir->GetName()!="TF")
        {
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

      TDirectory *dir_PROF = (TDirectory*)f_Latest->Get("PROF");
      TDirectory *dir_TF   = (TDirectory*)f_Latest->Get("TF");

      dir_PROF->cd();
      bool isFirst_MultiPROF = true;
      double maxY = 0.;
      std::vector<TH1*> vec_StkPROF1;
      TLegend *legPROF = new TLegend(0.7,0.7,0.9,0.9);
      for(auto histName : map_HistToPad_PROF)
      {
        if(histName.first=="h_MultiPROF1_DEGEN" || histName.first=="h_MultiPROF2_DEGEN" || histName.first=="h_MultiPROF3_DEGEN")
        {
          TH1 *temp = (TH1*)dir_PROF->Get(histName.first);
          if(maxY<temp->GetBinContent(temp->GetMaximumBin())){maxY = temp->GetBinContent(temp->GetMaximumBin());} 
          vec_StkPROF1.push_back(temp);
        }
        else
        {
          map_HistToPad_PROF[histName.first].first->cd(map_HistToPad_PROF[histName.first].second);
          TH1 *temp = (TH1*)dir_PROF->Get(histName.first);
          temp->SetTitle(map_HistToTitles[histName.first][0]);
          temp->GetXaxis()->SetTitle(map_HistToTitles[histName.first][1]);
          temp->GetYaxis()->SetTitle(map_HistToTitles[histName.first][2]);
          temp->Draw();
          map_HistToPad_PROF[histName.first].first->Update();
          map_HistToPad_PROF[histName.first].first->Modified();
        }
      }
      for(unsigned int i = 0; i < vec_StkPROF1.size(); i++)
      {
        if(i==0)
        {
          map_HistToPad_PROF[vec_StkPROF1[i]->GetName()].first->cd(map_HistToPad_PROF[vec_StkPROF1[i]->GetName()].second);
          vec_StkPROF1[i]->SetTitle(map_HistToTitles[vec_StkPROF1[i]->GetName()][0]);
          vec_StkPROF1[i]->GetXaxis()->SetTitle(map_HistToTitles[vec_StkPROF1[i]->GetName()][1]);
          vec_StkPROF1[i]->GetYaxis()->SetTitle(map_HistToTitles[vec_StkPROF1[i]->GetName()][2]);
          vec_StkPROF1[i]->SetLineColor(vec_Colors[i]);
          legPROF->AddEntry(vec_StkPROF1[i],"PROF1","L");
          vec_StkPROF1[i]->Draw();
        }
        else
        {
          vec_StkPROF1[i]->SetLineColor(vec_Colors[i]);
          if(i==1)
          {
            legPROF->AddEntry(vec_StkPROF1[i],"PROF2","L");
          }
          else if(i==2)
          {
            legPROF->AddEntry(vec_StkPROF1[i],"PROF3", "L");
          }
          vec_StkPROF1[i]->Draw("SAME");
        }
      }
      vec_StkPROF1[0]->GetYaxis()->SetRangeUser(0, maxY+maxY*0.1);
      c_PROF->SetTitle("PROF Display, LAST UPDATED "+(TString)s_Time);
      legPROF->Draw();
      map_HistToPad_PROF[vec_StkPROF1[0]->GetName()].first->Update();
      map_HistToPad_PROF[vec_StkPROF1[0]->GetName()].first->Modified();

      dir_TF->cd();
      bool isFirst_MultiTF   = true;
      maxY = 0.;
      std::vector<TH1*> vec_StkTF1;
      TLegend *legTF = new TLegend(0.1,0.1,0.9,0.9);
      for(auto histName : map_HistToPad_TF)
      {
        if(histName.first=="h_MultiUS_DEGEN" || histName.first=="h_MultiDS_DEGEN")
        {
          TH1 *temp = (TH1*)dir_TF->Get(histName.first);
          if(maxY<temp->GetBinContent(temp->GetMaximumBin())){maxY = temp->GetBinContent(temp->GetMaximumBin());} 
          vec_StkTF1.push_back(temp);
        }
        else
        {
          map_HistToPad_TF[histName.first].first->cd(map_HistToPad_TF[histName.first].second);
          TH1 *temp = (TH1*)dir_TF->Get(histName.first);
          temp->SetTitle(map_HistToTitles[histName.first][0]);
          temp->GetXaxis()->SetTitle(map_HistToTitles[histName.first][1]);
          temp->GetYaxis()->SetTitle(map_HistToTitles[histName.first][2]);
          temp->Draw();
          map_HistToPad_TF[histName.first].first->Update();
          map_HistToPad_TF[histName.first].first->Modified();
        }
      }
      for(unsigned int i = 0; i < vec_StkTF1.size(); i++)
      {
        if(i==0)
        {
          map_HistToPad_TF[vec_StkTF1[i]->GetName()].first->cd(map_HistToPad_TF[vec_StkTF1[i]->GetName()].second);
          vec_StkTF1[i]->SetTitle(map_HistToTitles[vec_StkTF1[i]->GetName()][0]);
          vec_StkTF1[i]->GetXaxis()->SetTitle(map_HistToTitles[vec_StkTF1[i]->GetName()][1]);
          vec_StkTF1[i]->GetYaxis()->SetTitle(map_HistToTitles[vec_StkTF1[i]->GetName()][2]);
          vec_StkTF1[i]->SetLineColor(vec_Colors[i]);
          legTF->AddEntry(vec_StkTF1[i],"TFUS","L");
          vec_StkTF1[i]->Draw();
        }
        else
        {
          vec_StkTF1[i]->SetLineColor(vec_Colors[i]);
          legTF->AddEntry(vec_StkTF1[i],"TFDS","L");
          vec_StkTF1[i]->Draw("SAME");
        }
      }
      vec_StkTF1[0]->GetYaxis()->SetRangeUser(0, maxY+maxY*0.1);
      map_HistToPad_TF[vec_StkTF1[0]->GetName()].first->Update();
      map_HistToPad_TF[vec_StkTF1[0]->GetName()].first->Modified();

      c_TF->cd(4);
      c_TF->SetTitle("TF Display, LAST UPDATED "+(TString)s_Time);
      legTF->Draw();
      c_TF->Update();
      c_TF->Modified();

      lastFile = latestFilePath;
      delete f_Latest;
      delete leg_XBPF;
      delete leg_XBTF;
      delete legTF;
      delete legPROF;
    }

    gSystem->Sleep(1000*updateEvery);
  }

  std::cout << "MONITORING TIME FINISHED" << std::endl;

  return 0;
}
