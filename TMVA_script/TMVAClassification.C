#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

int TMVAClassification( )
{

   TMVA::Tools::Instance();
   // TMVA::Config::Instance().fVariablePlotting.fNbinsMVAoutput = 20;
   // TMVA::Config::Instance().fVariablePlotting.fNbins1D = 20;

   TFile *input_signal(0);
   TFile* input_background(0);

   input_signal = TFile::Open( "Z2tau2pipipi_outfile_TMVA.root" );
   input_background = TFile::Open("Z2tau2pi_outfile_TMVA.root");

   if (!input_signal && !input_background) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }

   TTree *signalTree     = (TTree*)input_signal->Get("data");
   TTree *background     = (TTree*)input_background->Get("data");

   TString outfileName( "TMVA_output.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:!DrawProgressBar:Transformations=I;D;P;G,D;P,N;N:AnalysisType=Classification" );

   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");

   dataloader->AddVariable("num_S_cluster", "the number of clusters at scint", "", 'F');
   dataloader->AddVariable("E_Scorr", "total energy of scintillation channel", "GeV", 'F');
   dataloader->AddVariable("E_C","total energy of cerenkov channel","GeV",'F');
   dataloader->AddVariable("avg_S_sigma", "average distance from center of clusters at scint", "", 'F');
   dataloader->AddVariable("avg_C_sigma", "average distance from center of clusters at Cherenkov", "", 'F');
   dataloader->AddVariable("num_fired_S_fibers", "the number of fired scintillation fibers", "", 'F');
   dataloader->AddVariable("num_fired_C_fibers", "the number of fired Cherenkov fibers", "", 'F');
   dataloader->AddVariable("E_missing", "missing energy", "GeV", 'F');
   dataloader->AddVariable("total_signal_max_position_S","peak position of total signal at scint","ns",'F');
   dataloader->AddVariable("total_signal_max_position_C","peak position of total signal at Cherenkov","ns",'F');
   dataloader->AddVariable("time_of_total_signal_rise_threshold_S","time of crossing half maximum of total signal at scint","ns",'F');
   dataloader->AddVariable("time_of_total_signal_rise_threshold_C","time of crossing half maximum of total signal at Cherenkov","ns",'F');
   dataloader->AddVariable("var1 := time_of_total_signal_fall_threshold_S - time_of_total_signal_rise_threshold_S","FWHM of total signal at scint","ns",'F');
   dataloader->AddVariable("var2 := time_of_total_signal_fall_threshold_C - time_of_total_signal_rise_threshold_C","FWHM of total signal at Cherenkov","ns",'F');
   dataloader->AddVariable("signal_max_position_S_first_cluster","peak position of first cluster at scint","ns",'F');
   dataloader->AddVariable("signal_max_position_C_first_cluster","peak position first cluster at Cherenkov","ns",'F');
   dataloader->AddVariable("signal_max_position_S_second_cluster","peak position of second cluster at scint","ns",'F');
   dataloader->AddVariable("signal_max_position_C_second_cluster","peak position of second cluster at Cherenkov","ns",'F');
   dataloader->AddVariable("rise_time_10to90_S_first_cluster","risetime(10 to 90%) of first cluster at scint","ns",'F');
   dataloader->AddVariable("rise_time_10to90_C_first_cluster","risetime(10 to 90%) of first cluster at Cherenkov","ns",'F');
   dataloader->AddVariable("rise_time_10to90_S_second_cluster","risetime(10 to 90%) of second cluster at scint","ns",'F');
   dataloader->AddVariable("rise_time_10to90_C_second_cluster","risetime(10 to 90%) of second cluster at Cherenkov","ns",'F');
   dataloader->AddVariable("middle_time_of_10to90_S_first_cluster","time of crossing half maximum of first cluster at scint","ns",'F');
   dataloader->AddVariable("middle_time_of_10to90_C_first_cluster","time of crossing half maximum of first cluster at Cherenkov","ns",'F');
   dataloader->AddVariable("middle_time_of_10to90_S_second_cluster","time of crossing half maximum of second cluster at scint","ns",'F');
   dataloader->AddVariable("middle_time_of_10to90_C_second_cluster","time of crossing half maximum of second cluster at Cherenkov","ns",'F');
   dataloader->AddVariable("E_S_dividedby_E_C_first_cluster", "E_{S}/E_{C} of first cluster", "", 'F');
   dataloader->AddVariable("E_S_dividedby_E_C_second_cluster", "E_{S}/E_{C} of second cluster", "", 'F');
   //dataloader->AddVariable("E_33_dividedby_E_55_S_first_cluster", "E_{3x3 tower}/E_{5x5 tower} of first cluster at scint", "", 'F');
   //dataloader->AddVariable("E_33_dividedby_E_55_C_first_cluster", "E_{3x3 tower}/E_{5x5 tower} of first cluster at Cherenkov", "", 'F');
   //dataloader->AddVariable("E_33_dividedby_E_55_S_second_cluster", "E_{3x3 tower}/E_{5x5 tower} of second cluster at scint", "", 'F');
   //dataloader->AddVariable("E_33_dividedby_E_55_C_second_cluster", "E_{3x3 tower}/E_{5x5 tower} of second cluster at Cherenkov", "", 'F');

   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;

   dataloader->AddSignalTree    ( signalTree,     signalWeight );
   dataloader->AddBackgroundTree( background, backgroundWeight );

   TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";

   //   dataloader->PrepareTrainingAndTestTree( mycuts, mycutb,"nTrain_Signal=5000:nTrain_Background=5000:SplitMode=Alternate:NormMode=NumEvents:!V" );
   dataloader->PrepareTrainingAndTestTree( mycuts, mycutb,"SplitMode=Random:SplitSeed=42:nTrain_Signal=40000:nTrain_Background=40000:NormMode=NumEvents:!V" );

   factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT", "!H:!V:VarTransform=N" );
   factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "H:!V:VarTransform=N");
   // factory->BookMethod(dataloader, TMVA::Types::kSVM, "SVM", "VarTransform=N");
      //      factory->BookMethod(dataloader, TMVA::Types::kLikelihood, "Likelihood",
      //          "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50");
      //factory->BookMethod(dataloader, TMVA::Types::kKNN, "KNN","VarTransform=N");

   factory->TrainAllMethods();

   factory->TestAllMethods();

   factory->EvaluateAllMethods();

   outputFile->Close();

   delete factory;
   delete dataloader;

   if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );

   return 0;
}

int main( int argc, char** argv )
{

   return TMVAClassification();
}
