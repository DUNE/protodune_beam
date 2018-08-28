#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "runDisplay.h"
#include "colors.h"


int runDisplay_BL()
{
  long startTime = std::time(0);
  std::string lastFile = "";

  std::vector<int> vec_Colors = getColors(2);

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
  map_HistToTitles["h_TF_UNIQ"]          = {"Time of Flight from XBPFs","Time, (ns)","Events"};
  map_HistToTitles["h_TF_DEGEN"]         = {"Time of Flight from XBPFs","Time, (ns)","Events"};
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
    latestFile.open("/scratch/BeamInstOutput/Histograms_BL/latestHistFile.txt");
    std::string latestFilePath = "";
    latestFile >> latestFilePath;
    latestFile.close();

    std::cout << "LATEST FILE PATH: " << latestFilePath << std::endl;

    if(latestFilePath!=lastFile)
    {
      time_t now = std::time(0);
      std::string s_Time = std::ctime(&now);

      TFile *f_Latest = new TFile((TString)latestFilePath,"OPEN");
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
      delete legTF;
      delete legPROF;
    }

    gSystem->Sleep(1000*updateEvery);
  }

  std::cout << "MONITORING TIME FINISHED" << std::endl;

  return 0;
}
