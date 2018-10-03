#include "unpack.h"

void unpackDIPROOT(std::map<std::string,Detector> &cMapDetector, std::string const &cDatapath, bool const &cZeroSuppress)
{
  TFile *f_In = new TFile((TString)cDatapath,"OPEN");
  TTree *t = (TTree*)f_In->Get("eventsData");

  std::string *br_Subscription = 0;
  std::string *br_DetName      = 0;
  std::string *br_DetType      = 0;
  double       br_Timestamp;
  double       br_Current;
  int          br_CountsRec;
  int          br_TimestampCount;
  std::vector<unsigned long> *br_TTS_LSB = 0;
  std::vector<unsigned long> *br_TTS_MSB = 0;
  std::vector<unsigned long> *br_ETS_LSB = 0;
  std::vector<unsigned long> *br_ETS_MSB = 0;
  std::vector<unsigned int>  *br_Fibres0 = 0;
  std::vector<unsigned int>  *br_Fibres1 = 0;
  std::vector<unsigned int>  *br_Fibres2 = 0;
  std::vector<unsigned int>  *br_Fibres3 = 0;
  std::vector<unsigned int>  *br_Fibres4 = 0;
  std::vector<unsigned int>  *br_Fibres5 = 0;
  std::vector<unsigned int>  *br_Coarse  = 0;
  std::vector<unsigned int>  *br_Frac    = 0;
  std::vector<unsigned long> *br_Seconds = 0;

  t->SetBranchAddress("subscription",   &br_Subscription  );
  t->SetBranchAddress("detName",        &br_DetName       );
  t->SetBranchAddress("detType",        &br_DetType       );
  t->SetBranchAddress("timestamp",      &br_Timestamp     );
  t->SetBranchAddress("current",        &br_Current       );
  t->SetBranchAddress("countsRec",      &br_CountsRec     );
  t->SetBranchAddress("timestampCount", &br_TimestampCount);
  t->SetBranchAddress("TTS_LSB", &br_TTS_LSB);
  t->SetBranchAddress("TTS_MSB", &br_TTS_MSB);
  t->SetBranchAddress("ETS_LSB", &br_ETS_LSB);
  t->SetBranchAddress("ETS_MSB", &br_ETS_MSB);
  t->SetBranchAddress("Fibres0", &br_Fibres0);
  t->SetBranchAddress("Fibres1", &br_Fibres1);
  t->SetBranchAddress("Fibres2", &br_Fibres2);
  t->SetBranchAddress("Fibres3", &br_Fibres3);
  t->SetBranchAddress("Fibres4", &br_Fibres4);
  t->SetBranchAddress("Fibres5", &br_Fibres5);
  t->SetBranchAddress("Coarse",  &br_Coarse );
  t->SetBranchAddress("Frac",    &br_Frac   );
  t->SetBranchAddress("Seconds", &br_Seconds);

  for(unsigned int i = 0; i < t->GetEntries(); i++)
  {
    t->GetEntry(i);
    if(*br_DetType=="XBPF" && cMapDetector.count(*br_DetName)>0)
    {
      AcquisitionXBPF acq;
      acq.addAcqDetails(br_Timestamp, br_CountsRec);
      unsigned int nEvents = 0;
      if(br_CountsRec>=0)
      {
        nEvents = cZeroSuppress ? br_CountsRec : br_TTS_LSB->size();
      }
      unsigned int nNonZeroCount = 0;
      for(unsigned int j = 0; j < nEvents; j++)
      {
        std::array<unsigned int, 6> arr_Fibre;
        acq.addEventRecord({br_TTS_LSB->at(j), br_TTS_MSB->at(j), br_ETS_LSB->at(j), br_ETS_MSB->at(j), {br_Fibres0->at(j), br_Fibres1->at(j), br_Fibres2->at(j), 
                                                                                                         br_Fibres3->at(j), br_Fibres4->at(j), br_Fibres5->at(j)}});
        if(br_TTS_MSB->at(j)>0.)
        {
          nNonZeroCount++;
          acq.setEmpty(false);
        }
      }
      acq.setNNonZeroEvents(nNonZeroCount);
      acq.setCurrent(br_Current);
      cMapDetector[*br_DetName].addAcquisition(acq);
    }
    else if(*br_DetType=="XBTF" && cMapDetector.count(*br_DetName)>0)
    {
      AcquisitionXBTF acq;
      acq.addAcqDetails(br_Timestamp, br_TimestampCount);
      for(unsigned int j = 0; j < br_TimestampCount; j++)
      {
        acq.addEventRecord({br_Frac->at(j), br_Coarse->at(j), br_Seconds->at(j)});      
      }
      cMapDetector[*br_DetName].addAcquisition(acq);
    }
  }

  return;
}

void SetHistTitles(TH1I* &h, TString const &title, TString const &xTitle, TString const &yTitle)
{
  h->SetTitle(title);
  h->GetXaxis()->SetTitle(xTitle);
  h->GetYaxis()->SetTitle(yTitle);

  return;
}

void SetHistTitles(TH1D* &h, TString const &title, TString const &xTitle, TString const &yTitle)
{
  h->SetTitle(title);
  h->GetXaxis()->SetTitle(xTitle);
  h->GetYaxis()->SetTitle(yTitle);

  return;
}

void SetHistTitles(TH2D* &h, TString const &title, TString const &xTitle, TString const &yTitle)
{
  h->SetTitle(title);
  h->GetXaxis()->SetTitle(xTitle);
  h->GetYaxis()->SetTitle(yTitle);

  return;
}
