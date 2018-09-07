#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <sstream>
#include <vector>
#include "Dip.h"
#include "DipSubscription.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"


class Writer 
{
  public:
    Writer(std::string cOutputPath, unsigned int cFileCloseInterval);
    ~Writer();
    void dataReceived(const char *cSubscription, DipData &cDipData);
    void Flush();

  private:
    TFile            *fCurrentFile;
    TTree            *fCurrentTree;
    unsigned int	     fFileCloseInterval;
    unsigned long int fCurrentOpenTime;
    std::string fCurrentFileName;
    std::string	fOutputPath;
    std::vector<std::string> fVecSubscriptionNames;
    double fLatestCurrent   = 0.;
    int    fLatestCurrentDQ = 2;

    std::string        br_Subscription;
    std::string        br_DetName;
    std::string        br_DetType;
    int                br_DQ;
    int                br_CurrentDQ;
    double             br_Current;
    double             br_Timestamp;
    unsigned int       br_CountsRec;
    unsigned int       br_TimestampCount;
    std::vector<unsigned long> br_TTS_LSB;
    std::vector<unsigned long> br_TTS_MSB;
    std::vector<unsigned long> br_ETS_LSB;
    std::vector<unsigned long> br_ETS_MSB;
    std::vector<unsigned int>  br_Fibres0;
    std::vector<unsigned int>  br_Fibres1;
    std::vector<unsigned int>  br_Fibres2;
    std::vector<unsigned int>  br_Fibres3;
    std::vector<unsigned int>  br_Fibres4;
    std::vector<unsigned int>  br_Fibres5;
    std::vector<unsigned int>  br_Coarse;
    std::vector<unsigned int>  br_Frac;
    std::vector<unsigned long> br_Seconds;
    
    double             getCurrent(const DipData &cDipData, const char *var);
    unsigned int       getCountsRec(const char *cSubscription, const DipData &cDipData, const char *var);
    unsigned long long getAcqTimestamp(const DipData &cDipData);
    void openFirst(double const &cAcqTimestamp);
    void reopenFile(double const &cAcqTimestamp);
    void clearTreeVars();
    void closeCurrentFile();
    void writeAcqXBPF(const char *cSubscription, const DipData &cDipData, const char *var, unsigned long long const &cAcqTimestamp, unsigned int const &cCountsRec);
    void writeAcqXBTF(const char *cSubscription, const DipData &cDipData, std::map<std::string,const char*> &map_VarsList, unsigned long long const &cTimestamp);
};

Writer::Writer(std::string cOutputPath, unsigned int cFileCloseInterval)
{
  fOutputPath        = cOutputPath;
  fFileCloseInterval = cFileCloseInterval;
  fCurrentOpenTime   = 0;
  fCurrentFile       = NULL;
  fCurrentTree       = NULL;
}

Writer::~Writer()
{
  closeCurrentFile();
}

double Writer::getCurrent(const DipData &cDipData, const char *var)
{
  DipFloat current = cDipData.extractFloat(var);
  return (double)current;
}

unsigned long long Writer::getAcqTimestamp(const DipData &cDipData)
{
  DipLong acqTimestamp = cDipData.extractDipTime().getAsNanos();
  return (unsigned long long)acqTimestamp;
}

unsigned int Writer::getCountsRec(const char *cSubscription, const DipData &cDipData, const char *var)
{
  DipLong counsRec = cDipData.extractLong(var);
  return (unsigned int)counsRec;
}

void Writer::clearTreeVars()
{
  br_Subscription = ""; br_DetName = ""; br_DetType = ""; br_DQ = 2; br_CurrentDQ = 2; br_Current = 0.; br_Timestamp = 0; br_CountsRec = 0; br_TimestampCount = 0;
  br_TTS_LSB.clear(); br_TTS_MSB.clear(); br_ETS_LSB.clear(); br_ETS_MSB.clear(); br_Fibres0.clear();
  br_Fibres1.clear(); br_Fibres2.clear(); br_Fibres3.clear(); br_Fibres4.clear(); br_Fibres5.clear();
  br_Coarse.clear();  br_Frac.clear();    br_Seconds.clear();

  return;
}
void Writer::closeCurrentFile()
{
  if(fCurrentFile!=NULL)
  {
    fCurrentTree->Write();
    fCurrentFile->Close();
    delete fCurrentFile;
    std::cout << "\nCLOSED " << fCurrentFileName << std::endl;
    std::ofstream f_FileList;
    f_FileList.open(fOutputPath+"/filesList_BI_ToHist.txt",std::ios_base::app);
    f_FileList << fCurrentFileName << " ";
    f_FileList.close();
    f_FileList.open(fOutputPath+"/filesList_BI_ToTree.txt",std::ios_base::app);
    f_FileList << fCurrentFileName << " ";
    f_FileList.close();
    f_FileList.open(fOutputPath+"/filesList_BL_ToTree.txt",std::ios_base::app);
    f_FileList << fCurrentFileName << " ";
    f_FileList.close();
    f_FileList.open(fOutputPath+"/filesList_BL_ToHist.txt",std::ios_base::app);
    f_FileList << fCurrentFileName << " ";
    f_FileList.close();
    f_FileList.open(fOutputPath+"/filesList_BIBL_ToTree.txt",std::ios_base::app);
    f_FileList << fCurrentFileName << " ";
    f_FileList.close();
    f_FileList.open(fOutputPath+"/filesList_BIBL_ToHist.txt",std::ios_base::app);
    f_FileList << fCurrentFileName << " ";
    f_FileList.close();
    f_FileList.open(fOutputPath+"/filesList_BIBL_ToHistToTree.txt",std::ios_base::app);
    f_FileList << fCurrentFileName << " ";
    f_FileList.close();
  }
  fCurrentFile = NULL;
  fCurrentTree = NULL;
}

void Writer::dataReceived(const char *cSubscription, DipData &cDipData)
{
  unsigned long long acqTimestamp = getAcqTimestamp(cDipData);
  double acqTimestamp_Seconds     = (double)acqTimestamp/1.e9; 
  //DONT NEED HIGH PRECISION ON THE ACQUISITION TIME.
  acqTimestamp = acqTimestamp_Seconds;

  std::cout.precision(13);
  std::cout << "dataReceived(), TIMESTAMP: " << acqTimestamp_Seconds << ", SUBSCRIPTION: " << cSubscription << ". DATA QUALITY FLAG: " << cDipData.extractDataQuality() << std::endl;

  if(cSubscription[24]=='B')
  {
    int nVars = 0;
    int var_CURRENT = 1;
    const char **varsList = cDipData.getTags(nVars);

    fLatestCurrent   = getCurrent(cDipData, varsList[var_CURRENT]); 
    fLatestCurrentDQ = cDipData.extractDataQuality();
  }

  if(fLatestCurrent!=0.)
  {
    if(cSubscription[24]=='P')
    {
      reopenFile(acqTimestamp_Seconds);

      int nVars             = 0;
      int var_COUNTSRECORDS = 5;
      int var_EVENTSDATA    = 11;
      const char **varsList = cDipData.getTags(nVars);

      unsigned int acqCountsRec = getCountsRec(cSubscription, cDipData, varsList[var_COUNTSRECORDS]);

      writeAcqXBPF(cSubscription, cDipData, varsList[var_EVENTSDATA], acqTimestamp, acqCountsRec);
    }
    else if(cSubscription[24]=='T' || cSubscription[24]=='O')
    {
      reopenFile(acqTimestamp_Seconds);

      int nVars       = 0;
      const char **varsList = cDipData.getTags(nVars);
      std::map<std::string,const char*> map_VarsList;
      map_VarsList["COARSE"]         = varsList[1];
      map_VarsList["FRAC"]           = varsList[4];
      map_VarsList["SECONDS"]        = varsList[5];
      map_VarsList["TIMESTAMPCOUNT"] = varsList[6];

      writeAcqXBTF(cSubscription, cDipData, map_VarsList, acqTimestamp);
    }
  }

  return;
}

void Writer::reopenFile(double const &acqTimestamp_Seconds)
{
  if(acqTimestamp_Seconds >= fCurrentOpenTime + fFileCloseInterval)
  {
    closeCurrentFile();
    fCurrentFileName = fOutputPath + "/eventsData_" + std::to_string((long)std::floor(acqTimestamp_Seconds)) + ".root";
    fCurrentFile = new TFile((TString)fCurrentFileName,"UPDATE");
    fCurrentTree = new TTree("eventsData","eventsData");
    fCurrentTree->Branch("subscription",   &br_Subscription);
    fCurrentTree->Branch("detName",        &br_DetName);
    fCurrentTree->Branch("detType",        &br_DetType);
    fCurrentTree->Branch("dq",             &br_DQ,             "dq/I");
    fCurrentTree->Branch("currentDQ",      &br_CurrentDQ,      "currentDQ/I");
    fCurrentTree->Branch("timestamp",      &br_Timestamp,      "timestamp/D");
    fCurrentTree->Branch("countsRec",      &br_CountsRec,      "countsRec/I");
    fCurrentTree->Branch("timestampCount", &br_TimestampCount, "timestampCount/I");
    fCurrentTree->Branch("current",        &br_Current,        "current/D");
    fCurrentTree->Branch("TTS_LSB", &br_TTS_LSB);
    fCurrentTree->Branch("TTS_MSB", &br_TTS_MSB);
    fCurrentTree->Branch("ETS_LSB", &br_ETS_LSB);
    fCurrentTree->Branch("ETS_MSB", &br_ETS_MSB);
    fCurrentTree->Branch("Fibres0", &br_Fibres0);
    fCurrentTree->Branch("Fibres1", &br_Fibres1);
    fCurrentTree->Branch("Fibres2", &br_Fibres2);
    fCurrentTree->Branch("Fibres3", &br_Fibres3);
    fCurrentTree->Branch("Fibres4", &br_Fibres4);
    fCurrentTree->Branch("Fibres5", &br_Fibres5);
    fCurrentTree->Branch("Coarse",  &br_Coarse);
    fCurrentTree->Branch("Frac",    &br_Frac);
    fCurrentTree->Branch("Seconds", &br_Seconds);

    if(fCurrentFile==NULL)
    {
      std::cout << "CANNOT OPEN FILE " << fCurrentFileName << std::endl;
      exit(1);
    }

    std::cout << "\nFILE " << fCurrentFileName << " IS OPENED!\n" << std::endl;
    fCurrentOpenTime = acqTimestamp_Seconds;
  }
}

void Writer::writeAcqXBPF(const char *cSubscription, const DipData &cDipData, const char *var, unsigned long long const &cTimestamp, unsigned int const &cCountsRec)
{
  int   arrayLength = 0;
  const DipLong *acqArray    = cDipData.extractLongArray(arrayLength, var);
  std::string s_Subscription = cSubscription;
  std::string s_DetName      = s_Subscription.substr(27,36);

  br_Subscription = s_Subscription; 
  br_DetName      = s_DetName;
  br_DetType      = "XBPF";
  br_Timestamp    = cTimestamp;
  br_CountsRec    = cCountsRec;
  br_Current      = fLatestCurrent;
  br_CurrentDQ    = fLatestCurrentDQ;
  br_DQ           = cDipData.extractDataQuality();

  int i = 0;
  while(i < arrayLength)
  {
    br_TTS_LSB.push_back(acqArray[i]);  
    br_TTS_MSB.push_back(acqArray[i+1]);
    br_ETS_LSB.push_back(acqArray[i+2]);
    br_ETS_MSB.push_back(acqArray[i+3]);
    br_Fibres0.push_back(acqArray[i+4]);
    br_Fibres1.push_back(acqArray[i+5]);
    br_Fibres2.push_back(acqArray[i+6]);
    br_Fibres3.push_back(acqArray[i+7]);
    br_Fibres4.push_back(acqArray[i+8]);
    br_Fibres5.push_back(acqArray[i+9]);
    i+=10;
  }
  fCurrentTree->Fill();
  clearTreeVars();
  
  return;
}

void Writer::writeAcqXBTF(const char *cSubscription, const DipData &cDipData, std::map<std::string,const char*> &map_VarsList, unsigned long long const &cTimestamp)
{
  int   arrayLength = 0;
  const DipInt  *acqArray_COARSE  = cDipData.extractIntArray(arrayLength,  map_VarsList["COARSE"]);
  const DipInt  *acqArray_FRAC    = cDipData.extractIntArray(arrayLength,  map_VarsList["FRAC"]);
  const DipLong *acqArray_SECONDS = cDipData.extractLongArray(arrayLength, map_VarsList["SECONDS"]);
  std::string s_Subscription = cSubscription;
  std::string s_DetName = s_Subscription.substr(27);

  br_Subscription   = s_Subscription; 
  br_DetName        = s_DetName; 
  br_DetType        = "XBTF";
  br_Timestamp      = cTimestamp;
  br_TimestampCount = cDipData.extractInt(map_VarsList["TIMESTAMPCOUNT"]); 
  br_DQ             = cDipData.extractDataQuality();

  int i = 0;
  while(i < arrayLength)
  {
    br_Coarse .push_back(acqArray_COARSE[i] );  
    br_Frac   .push_back(acqArray_FRAC[i]   );
    br_Seconds.push_back(acqArray_SECONDS[i]);
    i++;
  }
  fCurrentTree->Fill();
  clearTreeVars();

  return;
}

void Writer::Flush()
{
  closeCurrentFile();
  return;
}


class Client : public DipSubscriptionListener{

  private:
    unsigned int      fNSubscriptions;
    DipSubscription **fSubscription;
    DipFactory       *fDipFactory;
    Writer           *fWriter;

  public:
    Client(Writer *cWriter, unsigned int cNVars, std::vector<std::string> cVecSubscriptionNames)
    {
      fWriter         = cWriter;
      fNSubscriptions = cNVars;
      fDipFactory     = Dip::create("dipClient_BIMonitoring");
      fSubscription   = new DipSubscription*[fNSubscriptions];

      fDipFactory->setDNSNode("dipnsgpn1,dipnsgpn2");
      //fDipFactory->setDNSNode("dipnstn1,dipnstn2");

      for(unsigned int i = 0; i < fNSubscriptions; i++)
      {	
        char c_CurrentSubscription[cVecSubscriptionNames.at(i).length()+1];
        strcpy(c_CurrentSubscription, cVecSubscriptionNames.at(i).c_str());
        fSubscription[i] = fDipFactory->createDipSubscription(c_CurrentSubscription, this);
        std::cout << "SUBSCRIBED TO: " << cVecSubscriptionNames.at(i) << std::endl;
      }
    }

    ~Client()
    {
      for(unsigned int i = 0; i< fNSubscriptions; i++)
      {
        fDipFactory->destroyDipSubscription(fSubscription[i]);
      }

      delete fDipFactory;

      std::cout << "CLIENT IS DONE!" <<std::endl;
    }

    void handleMessage(DipSubscription *cSubscription, DipData &cDipData)
    {
      fWriter->dataReceived(cSubscription->getTopicName(), cDipData);
    }

    void connected(DipSubscription *cSubscription) 
    {
      std::cout << "\nPUBLICATION SOURCE " << cSubscription->getTopicName()<< " AVAILABLE" << std::endl;
    }

    void disconnected(DipSubscription *cSubscription, char *arg1) 
    {
      std::cout << "\nPUBLICATION SOURCE " << cSubscription->getTopicName() << " UNAVAILABLE" << std::endl;
    }

    void handleException(DipSubscription* subscription, DipException& ex)
    {
      std::cout << "\nPUBLICATION " << subscription->getTopicName() << " HAS ERROR: " << ex.what() << std::endl;
    }
};


int main(const int argc, const char ** argv)
{
  std::cout << std::endl;
  std::cout << "**************************************************************" << std::endl;
  std::cout << "*       WELCOME TO BEAM INSTRUMENTATION DIP EXTRACTION       *" << std::endl;
  std::cout << "**************************************************************" << std::endl;

  std::string s_Usage = "./dipClient.exe [-t <LIFETIME, (MINS)>: 2 HOURS] [-f <FILE CLOSE INTERVAL, (SECS)>: 1 SECOND] <OUTDIR> <SUBSCRIPTION VARS>";

  //MEASURED IN SECONDS.
  unsigned int lifetime          = 1438*60;
  unsigned int fileCloseInterval = 1;

  int i = 0;
  //IF THERE ARE NO ARGUMENTS THEN THIS LOOP DOES NOT GET EXECUTED AT ALL. DOES NOT PASS THE FOR LOOP LOGIC.
  for( i=1; i<argc; i++ )
  {
    const char *arg = argv[i];
    if(arg[0]=='-')
    {
      switch(arg[1])
      {
        case 't':
          lifetime = std::atoi(argv[++i])*60;
          //lifetime = std::atoi(argv[++i]);
          break;
        case 'f':
          //fileCloseInterval = std::atoi(argv[++i])*60;
          fileCloseInterval = std::atoi(argv[++i]);
          break;
      }
    }
    else if(i>argc-2)
    {
      std::cout << "\nRUN run_collector.sh -h FOR USAGE" << std::endl;
      std::cout << s_Usage << std::endl;

      return 0;
    }
    else
    {
      break;
    }
  }

  //SINCE i IS INITALISED AS ZERO, THIS LOOP GETS PRINTED IF NO OR GREATER THAN THE REQUIRED NUMBER OF ARGUMENTS ARE PROVIDED.
  if( i >= argc )
  {
    std::cout << "\nRUN run_collector.sh -h FOR USAGE" << std::endl;
    std::cout << s_Usage << std::endl;
    return 0;
  }

  std::string s_OutputPath = argv[i];
  std::vector<std::string> vec_SubscriptionNames;
  for(unsigned int j = i+1; j < (unsigned int)argc; j++)
  {
    std::string s_Subscription = *(argv+j);
    vec_SubscriptionNames.push_back(s_Subscription);
  }

  std::cout << "\nRUNNING WITH LIFETIME: "       << lifetime     
            << " SEC. DATA FILES CLOSED EVERY: " << fileCloseInterval << " SECS." << std::endl;  
  std::cout << "\nTHERE ARE "                    << vec_SubscriptionNames.size() << " SUBSCRIPTIONS." << std::endl;
  for(unsigned int j = 0; j < vec_SubscriptionNames.size(); j++)
  {
    std::cout << vec_SubscriptionNames.at(j) << std::endl;
  }
  std::cout << "\nWRITING DATA TO: " << s_OutputPath << std::endl;
  std::cout << std::endl;

  //CONSTRUCTOR TAKES THE OUTPUT FILE DIRECTORY AND THE FILE CLOSE INTERVAL.
  Writer *writer = new Writer(s_OutputPath, fileCloseInterval);

  Client *client = new Client(writer, vec_SubscriptionNames.size(), vec_SubscriptionNames);

  sleep(lifetime);

  std::cout << "\nCLIENTS LIFETIME HAS EXPIRED, LEAVING!" << std::endl;
  delete client;

  writer->Flush();
  delete writer;

  return(0);
}
