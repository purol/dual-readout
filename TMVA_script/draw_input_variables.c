#define N1 9999 // pipipi
#define N2 8841 // pinu
#define N3 10000 // qqbar
#define N4 9999 // pipizero
#define N5 10000 // pipizeropizero
#define N6 10000 // pipipipizero

std::vector<TH1F*> pipipi_TH1Fs;
std::vector<TH1F*> pi_TH1Fs;
std::vector<TH1F*> qqbar_TH1Fs;
std::vector<TH1F*> pipizero_TH1Fs;
std::vector<TH1F*> pipizeropizero_TH1Fs;
std::vector<TH1F*> pipipipizero_TH1Fs;

std::vector<std::string> paths =
{
    "./images/num_S_cluster.png", "./images/E_Scorr.png", "./images/E_C.png", "./images/avg_S_sigma.png", "./images/avg_C_sigma.png",
    "./images/num_fired_S_fibers.png", "./images/num_fired_C_fibers.png", "./images/E_missing.png", "./images/total_signal_max_position_S.png",
    "./images/total_signal_max_position_C.png", "./images/time_of_total_signal_rise_threshold_S.png", "./images/time_of_total_signal_rise_threshold_C.png",
    "./images/time_of_total_signal_half_width_S.png", "./images/time_of_total_signal_half_width_C.png", "./images/signal_max_position_S_first_cluster.png",
    "./images/signal_max_position_C_first_cluster.png", "./images/signal_max_position_S_second_cluster.png", "./images/signal_max_position_C_second_cluster.png",
    "./images/rise_time_10to90_S_first_cluster.png", "./images/rise_time_10to90_C_first_cluster.png", "./images/rise_time_10to90_S_second_cluster.png",
    "./images/rise_time_10to90_C_second_cluster.png", "./images/middle_time_of_10to90_S_first_cluster.png", "./images/middle_time_of_10to90_C_first_cluster.png",
    "./images/middle_time_of_10to90_S_second_cluster.png", "./images/middle_time_of_10to90_C_second_cluster.png"
};

void TH1F_pipipi(TH1F* pointer){
  pointer->SetStats(false);
  pointer->SetLineColor(kBlue);
  pointer->SetLineWidth(2);
  pointer->SetFillColor(kBlue);
  pointer->SetFillStyle(3004);
  pipipi_TH1Fs.push_back(pointer);
}

void TH1F_pi(TH1F* pointer){
  pointer->SetStats(false);
  pointer->SetLineColor(kRed);
  pointer->SetLineWidth(2);
  pointer->SetFillColor(kRed);
  pointer->SetFillStyle(3005);
  pi_TH1Fs.push_back(pointer);
}

void TH1F_qqbar(TH1F* pointer) {
    pointer->SetStats(false);
    pointer->SetLineColor(kGreen);
    pointer->SetLineWidth(2);
    pointer->SetFillColor(kGreen);
    pointer->SetFillStyle(3006);
    qqbar_TH1Fs.push_back(pointer);
}

void TH1F_pipizero(TH1F* pointer) {
    pointer->SetStats(false);
    //    pointer->SetLineColor(kMagenta+2);
    pointer->SetLineColor(kRed);
    pointer->SetLineWidth(2);
    //    pointer->SetFillColor(kMagenta + 2);
    pointer->SetFillColor(kRed);
    pointer->SetFillStyle(3007);
    pipizero_TH1Fs.push_back(pointer);
}

void TH1F_pipizeropizero(TH1F* pointer) {
    pointer->SetStats(false);
    pointer->SetLineColor(kYellow + 1);
    pointer->SetLineWidth(2);
    pointer->SetFillColor(kYellow + 1);
    pointer->SetFillStyle(3013);
    pipizeropizero_TH1Fs.push_back(pointer);
}

void TH1F_pipipipizero(TH1F* pointer) {
    pointer->SetStats(false);
    //   pointer->SetLineColor(kCyan + 1);
    pointer->SetLineColor(kBlue);
    pointer->SetLineWidth(2);
    //   pointer->SetFillColor(kCyan + 1);
    pointer->SetFillColor(kBlue);
    pointer->SetFillStyle(3017);
    pipipipizero_TH1Fs.push_back(pointer);
}

void TH1F_norm(TH1F* pointer) {
    pointer->Scale(1. / pointer->Integral());
}

void draw_input_variables(){
    // pipipi
  TH1F *num_S_cluster_pipipi = new TH1F("num_S_cluster_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});the number of clusters at scint;arbitrary unit",60,0,7); TH1F_pipipi(num_S_cluster_pipipi);
  TH1F *E_Scorr_pipipi = new TH1F("E_Scorr_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});total enegry of scintillation channel [GeV];arbitrary unit",60,0,95); TH1F_pipipi(E_Scorr_pipipi);
  TH1F *E_C_pipipi = new TH1F("E_C_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});total enegry of Cherenkov channel [GeV];arbitrary unit",60,0,95); TH1F_pipipi(E_C_pipipi);
  TH1F *avg_S_sigma_pipipi = new TH1F("avg_S_sigma_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});average distance from center of clusters at scint;arbitrary unit",60,0,0.4); TH1F_pipipi(avg_S_sigma_pipipi);
  TH1F* avg_C_sigma_pipipi = new TH1F("avg_C_sigma_pipipi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});average distance from center of clusters at Cherenkov;arbitrary unit", 60, 0, 0.4); TH1F_pipipi(avg_C_sigma_pipipi);
  TH1F *num_fired_S_fibers_pipipi = new TH1F("num_fired_S_fibers_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});the number of fired scintillation fibers;arbitrary unit",60,0,7000); TH1F_pipipi(num_fired_S_fibers_pipipi);
  TH1F *num_fired_C_fibers_pipipi = new TH1F("num_fired_C_fibers_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});the number of fired Cherenkov fibers;arbitrary unit",60,0,3000); TH1F_pipipi(num_fired_C_fibers_pipipi);
  TH1F *E_missing_pipipi = new TH1F("E_missing_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});missing energy [GeV];arbitrary unit",60,-15,95); TH1F_pipipi(E_missing_pipipi);
  TH1F *total_signal_max_position_S_pipipi = new TH1F("total_signal_max_position_S_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});peak position of total signal at scint [ns];arbitrary unit",50,15,20); TH1F_pipipi(total_signal_max_position_S_pipipi);
  TH1F *total_signal_max_position_C_pipipi = new TH1F("total_signal_max_position_C_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});peak position of total signal at Cherenkov [ns];arbitrary unit",60,12,18); TH1F_pipipi(total_signal_max_position_C_pipipi);
  TH1F *time_of_total_signal_rise_threshold_S_pipipi = new TH1F("time_of_total_signal_rise_threshold_S_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});time of crossing half maximum of total signal at scint [ns];arbitrary unit",60,12,18); TH1F_pipipi(time_of_total_signal_rise_threshold_S_pipipi);
  TH1F *time_of_total_signal_rise_threshold_C_pipipi = new TH1F("time_of_total_signal_rise_threshold_C_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});time of crossing half maximum of total signal at Cherenkov [ns];arbitrary unit",50,12,17); TH1F_pipipi(time_of_total_signal_rise_threshold_C_pipipi);
  TH1F *time_of_total_signal_half_width_S_pipipi = new TH1F("time_of_total_signal_half_width_S_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});FWHM of total signal at scint [ns];arbitrary unit",60,1.95,7.95); TH1F_pipipi(time_of_total_signal_half_width_S_pipipi);
  TH1F *time_of_total_signal_half_width_C_pipipi = new TH1F("time_of_total_signal_half_width_C_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});FWHM of total signal at Cherenkov [ns];arbitrary unit",50,-0.05,4.95); TH1F_pipipi(time_of_total_signal_half_width_C_pipipi);
  TH1F *signal_max_position_S_first_cluster_pipipi = new TH1F("signal_max_position_S_first_cluster_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});peak position of first cluster at scint [ns];arbitrary unit", 50, 15, 20); TH1F_pipipi(signal_max_position_S_first_cluster_pipipi);
  TH1F *signal_max_position_C_first_cluster_pipipi = new TH1F("signal_max_position_C_first_cluster_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});peak position of first cluster at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_pipipi(signal_max_position_C_first_cluster_pipipi);
  TH1F *signal_max_position_S_second_cluster_pipipi = new TH1F("signal_max_position_S_second_cluster_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});peak position of second cluster at scint [ns];arbitrary unit", 50, 15, 20); TH1F_pipipi(signal_max_position_S_second_cluster_pipipi);
  TH1F *signal_max_position_C_second_cluster_pipipi = new TH1F("signal_max_position_C_second_cluster_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});peak position of second cluster at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_pipipi(signal_max_position_C_second_cluster_pipipi);
  TH1F *rise_time_10to90_S_first_cluster_pipipi = new TH1F("rise_time_10to90_S_first_cluster_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});risetime(10 to 90%) of first cluster at scint [ns];arbitrary unit", 60,-0.05,5.95); TH1F_pipipi(rise_time_10to90_S_first_cluster_pipipi);
  TH1F *rise_time_10to90_C_first_cluster_pipipi = new TH1F("rise_time_10to90_C_first_cluster_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});risetime(10 to 90%) of first cluster at Cherenkov [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pipipi(rise_time_10to90_C_first_cluster_pipipi);
  TH1F *rise_time_10to90_S_second_cluster_pipipi = new TH1F("rise_time_10to90_S_second_cluster_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});risetime(10 to 90%) of second cluster at scint [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pipipi(rise_time_10to90_S_second_cluster_pipipi);
  TH1F *rise_time_10to90_C_second_cluster_pipipi = new TH1F("rise_time_10to90_C_second_cluster_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});risetime(10 to 90%) of second cluster at Cherenkov [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pipipi(rise_time_10to90_C_second_cluster_pipipi);
  TH1F *middle_time_of_10to90_S_first_cluster_pipipi = new TH1F("middle_time_of_10to90_S_first_cluster_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});time of crossing half maximum of first cluster at scint [ns];arbitrary unit", 60, 12, 18); TH1F_pipipi(middle_time_of_10to90_S_first_cluster_pipipi);
  TH1F *middle_time_of_10to90_C_first_cluster_pipipi = new TH1F("middle_time_of_10to90_C_first_cluster_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});time of crossing half maximum of first cluster at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_pipipi(middle_time_of_10to90_C_first_cluster_pipipi);
  TH1F *middle_time_of_10to90_S_second_cluster_pipipi = new TH1F("middle_time_of_10to90_S_second_cluster_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});time of crossing half maximum of second cluster at scint [ns];arbitrary unit", 60, 12, 18); TH1F_pipipi(middle_time_of_10to90_S_second_cluster_pipipi);
  TH1F *middle_time_of_10to90_C_second_cluster_pipipi = new TH1F("middle_time_of_10to90_C_second_cluster_pipipi","Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#pi^{+}#pi^{-}#nu_{#tau});time of crossing half maximum of second cluster at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_pipipi(middle_time_of_10to90_C_second_cluster_pipipi);
    
    TFile *input = new TFile("20210301_Z2tau2pipipi_total_out.root","read");
    TTree *input_tree = (TTree *) input -> Get("data");
    float num_of_S_cluster = 0;
    float num_of_C_cluster = 0;
    float num_of_fired_S_fibers = 0;
    float num_of_fired_C_fibers = 0;
    float total_E_S = 0;
    float total_E_Scorr = 0;
    float total_E_C = 0;
    float total_E_DR = 0;
    float total_E_DRcorr = 0;
    float total_missing_energy = 0;
    float average_S_sigma = 0;
    float average_C_sigma = 0;
    float total_signal_peak_position_S = 0;
    float total_signal_peak_position_C = 0;
    float time_signal_rise_threshold_S = 0;
    float time_signal_rise_threshold_C = 0;
    float time_signal_fall_threshold_S = 0;
    float time_signal_fall_threshold_C = 0;
    float signal_peak_position_S_first_cluster = 0;
    float signal_peak_position_C_first_cluster = 0;
    float signal_peak_position_S_second_cluster = 0;
    float signal_peak_position_C_second_cluster = 0;
    float rise_time_10to90_S_first_cluster = 0;
    float rise_time_10to90_C_first_cluster = 0;
    float rise_time_10to90_S_second_cluster = 0;
    float rise_time_10to90_C_second_cluster = 0;
    float middle_of_10to90_S_first_cluster = 0;
    float middle_of_10to90_C_first_cluster = 0;
    float middle_of_10to90_S_second_cluster = 0;
    float middle_of_10to90_C_second_cluster = 0;
    input_tree->SetBranchAddress("num_S_cluster", &num_of_S_cluster);
    input_tree->SetBranchAddress("num_C_cluster", &num_of_C_cluster);
    input_tree->SetBranchAddress("num_fired_S_fibers",&num_of_fired_S_fibers);
    input_tree->SetBranchAddress("num_fired_C_fibers",&num_of_fired_C_fibers);
    input_tree->SetBranchAddress("E_S", &total_E_S);
    input_tree->SetBranchAddress("E_Scorr", &total_E_Scorr);
    input_tree->SetBranchAddress("E_C", &total_E_C);
    input_tree->SetBranchAddress("E_DR",&total_E_DR);
    input_tree->SetBranchAddress("E_DRcorr",&total_E_DRcorr);
    input_tree->SetBranchAddress("E_missing",&total_missing_energy);
    input_tree->SetBranchAddress("avg_S_sigma", &average_S_sigma);
    input_tree->SetBranchAddress("avg_C_sigma", &average_C_sigma);
    input_tree->SetBranchAddress("total_signal_max_position_S", &total_signal_peak_position_S);
    input_tree->SetBranchAddress("total_signal_max_position_C", &total_signal_peak_position_C);
    input_tree->SetBranchAddress("time_of_total_signal_rise_threshold_S", &time_signal_rise_threshold_S);
    input_tree->SetBranchAddress("time_of_total_signal_rise_threshold_C", &time_signal_rise_threshold_C);
    input_tree->SetBranchAddress("time_of_total_signal_fall_threshold_S", &time_signal_fall_threshold_S);
    input_tree->SetBranchAddress("time_of_total_signal_fall_threshold_C", &time_signal_fall_threshold_C);
    input_tree->SetBranchAddress("signal_max_position_S_first_cluster", &signal_peak_position_S_first_cluster);
    input_tree->SetBranchAddress("signal_max_position_C_first_cluster", &signal_peak_position_C_first_cluster);
    input_tree->SetBranchAddress("signal_max_position_S_second_cluster", &signal_peak_position_S_second_cluster);
    input_tree->SetBranchAddress("signal_max_position_C_second_cluster", &signal_peak_position_C_second_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_S_first_cluster", &rise_time_10to90_S_first_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_C_first_cluster", &rise_time_10to90_C_first_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_S_second_cluster", &rise_time_10to90_S_second_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_C_second_cluster", &rise_time_10to90_C_second_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_S_first_cluster", &middle_of_10to90_S_first_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_C_first_cluster", &middle_of_10to90_C_first_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_S_second_cluster", &middle_of_10to90_S_second_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_C_second_cluster", &middle_of_10to90_C_second_cluster);
    
    for(int i=0;i<N1;i++){
        input_tree->GetEntry(i);
        num_S_cluster_pipipi->Fill(num_of_S_cluster);
        E_Scorr_pipipi->Fill(total_E_Scorr);
        E_C_pipipi->Fill(total_E_C);
        avg_S_sigma_pipipi->Fill(average_S_sigma);
        avg_C_sigma_pipipi->Fill(average_C_sigma);
        num_fired_S_fibers_pipipi->Fill(num_of_fired_S_fibers);
        num_fired_C_fibers_pipipi->Fill(num_of_fired_C_fibers);
        E_missing_pipipi->Fill(total_missing_energy);
        total_signal_max_position_S_pipipi->Fill(total_signal_peak_position_S);
        total_signal_max_position_C_pipipi->Fill(total_signal_peak_position_C);
        time_of_total_signal_rise_threshold_S_pipipi->Fill(time_signal_rise_threshold_S);
        time_of_total_signal_rise_threshold_C_pipipi->Fill(time_signal_rise_threshold_C);
        time_of_total_signal_half_width_S_pipipi->Fill(time_signal_fall_threshold_S - time_signal_rise_threshold_S);
        time_of_total_signal_half_width_C_pipipi->Fill(time_signal_fall_threshold_C - time_signal_rise_threshold_C);
        signal_max_position_S_first_cluster_pipipi->Fill(signal_peak_position_S_first_cluster);
        signal_max_position_C_first_cluster_pipipi->Fill(signal_peak_position_C_first_cluster);
        signal_max_position_S_second_cluster_pipipi->Fill(signal_peak_position_S_second_cluster);
        signal_max_position_C_second_cluster_pipipi->Fill(signal_peak_position_C_second_cluster);
        rise_time_10to90_S_first_cluster_pipipi->Fill(rise_time_10to90_S_first_cluster);
        rise_time_10to90_C_first_cluster_pipipi->Fill(rise_time_10to90_C_first_cluster);
        rise_time_10to90_S_second_cluster_pipipi->Fill(rise_time_10to90_S_second_cluster);
        rise_time_10to90_C_second_cluster_pipipi->Fill(rise_time_10to90_C_second_cluster);
        middle_time_of_10to90_S_first_cluster_pipipi->Fill(middle_of_10to90_S_first_cluster);
        middle_time_of_10to90_C_first_cluster_pipipi->Fill(middle_of_10to90_C_first_cluster);
        middle_time_of_10to90_S_second_cluster_pipipi->Fill(middle_of_10to90_S_second_cluster);
        middle_time_of_10to90_C_second_cluster_pipipi->Fill(middle_of_10to90_C_second_cluster);
    }
    input->Close();
    
    // pi
    TH1F* num_S_cluster_pi = new TH1F("num_S_cluster_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});the number of clusters at scint;arbitrary unit", 60, 0, 7); TH1F_pi(num_S_cluster_pi);
    TH1F* E_Scorr_pi = new TH1F("E_Scorr_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});total enegry of scintillation channel [GeV];arbitrary unit", 60, 0, 95); TH1F_pi(E_Scorr_pi);
    TH1F* E_C_pi = new TH1F("E_C_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});total enegry of Cherenkov channel [GeV];arbitrary unit", 60, 0, 95); TH1F_pi(E_C_pi);
    TH1F* avg_S_sigma_pi = new TH1F("avg_S_sigma_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});average distance from center of clusters at scint;arbitrary unit", 60, 0, 0.4); TH1F_pi(avg_S_sigma_pi);
    TH1F* avg_C_sigma_pi = new TH1F("avg_C_sigma_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});average distance from center of clusters at Cherenkov;arbitrary unit", 60, 0, 0.4); TH1F_pi(avg_C_sigma_pi);
    TH1F* num_fired_S_fibers_pi = new TH1F("num_fired_S_fibers_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});the number of fired scintillation fibers;arbitrary unit", 60, 0, 7000); TH1F_pi(num_fired_S_fibers_pi);
    TH1F* num_fired_C_fibers_pi = new TH1F("num_fired_C_fibers_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});the number of fired Cherenkov fibers;arbitrary unit", 60, 0, 3000); TH1F_pi(num_fired_C_fibers_pi);
    TH1F* E_missing_pi = new TH1F("E_missing_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});missing energy [GeV];arbitrary unit", 60, -15, 95); TH1F_pi(E_missing_pi);
    TH1F* total_signal_max_position_S_pi = new TH1F("total_signal_max_position_S_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});peak position of total signal at scint [ns];arbitrary unit", 50, 15, 20); TH1F_pi(total_signal_max_position_S_pi);
    TH1F* total_signal_max_position_C_pi = new TH1F("total_signal_max_position_C_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});peak position of total signal at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_pi(total_signal_max_position_C_pi);
    TH1F* time_of_total_signal_rise_threshold_S_pi = new TH1F("time_of_total_signal_rise_threshold_S_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});time of crossing half maximum of total signal at scint [ns];arbitrary unit", 60, 12, 18); TH1F_pi(time_of_total_signal_rise_threshold_S_pi);
    TH1F* time_of_total_signal_rise_threshold_C_pi = new TH1F("time_of_total_signal_rise_threshold_C_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});time of crossing half maximum of total signal at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_pi(time_of_total_signal_rise_threshold_C_pi);
    TH1F* time_of_total_signal_half_width_S_pi = new TH1F("time_of_total_signal_half_width_S_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});FWHM of total signal at scint [ns];arbitrary unit", 60, 1.95, 7.95); TH1F_pi(time_of_total_signal_half_width_S_pi);
    TH1F* time_of_total_signal_half_width_C_pi = new TH1F("time_of_total_signal_half_width_C_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});FWHM of total signal at Cherenkov [ns];arbitrary unit", 50, -0.05, 4.95); TH1F_pi(time_of_total_signal_half_width_C_pi);
    TH1F* signal_max_position_S_first_cluster_pi = new TH1F("signal_max_position_S_first_cluster_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});peak position of first cluster at scint [ns];arbitrary unit", 50, 15, 20); TH1F_pi(signal_max_position_S_first_cluster_pi);
    TH1F* signal_max_position_C_first_cluster_pi = new TH1F("signal_max_position_C_first_cluster_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});peak position of first cluster at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_pi(signal_max_position_C_first_cluster_pi);
    TH1F* signal_max_position_S_second_cluster_pi = new TH1F("signal_max_position_S_second_cluster_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});peak position of second cluster at scint [ns];arbitrary unit", 50, 15, 20); TH1F_pi(signal_max_position_S_second_cluster_pi);
    TH1F* signal_max_position_C_second_cluster_pi = new TH1F("signal_max_position_C_second_cluster_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});peak position of second cluster at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_pi(signal_max_position_C_second_cluster_pi);
    TH1F* rise_time_10to90_S_first_cluster_pi = new TH1F("rise_time_10to90_S_first_cluster_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});risetime(10 to 90%) of first cluster at scint [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pi(rise_time_10to90_S_first_cluster_pi);
    TH1F* rise_time_10to90_C_first_cluster_pi = new TH1F("rise_time_10to90_C_first_cluster_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});risetime(10 to 90%) of first cluster at Cherenkov [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pi(rise_time_10to90_C_first_cluster_pi);
    TH1F* rise_time_10to90_S_second_cluster_pi = new TH1F("rise_time_10to90_S_second_cluster_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});risetime(10 to 90%) of second cluster at scint [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pi(rise_time_10to90_S_second_cluster_pi);
    TH1F* rise_time_10to90_C_second_cluster_pi = new TH1F("rise_time_10to90_C_second_cluster_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});risetime(10 to 90%) of second cluster at Cherenkov [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pi(rise_time_10to90_C_second_cluster_pi);
    TH1F* middle_time_of_10to90_S_first_cluster_pi = new TH1F("middle_time_of_10to90_S_first_cluster_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});time of crossing half maximum of first cluster at scint [ns];arbitrary unit", 60, 12, 18); TH1F_pi(middle_time_of_10to90_S_first_cluster_pi);
    TH1F* middle_time_of_10to90_C_first_cluster_pi = new TH1F("middle_time_of_10to90_C_first_cluster_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});time of crossing half maximum of first cluster at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_pi(middle_time_of_10to90_C_first_cluster_pi);
    TH1F* middle_time_of_10to90_S_second_cluster_pi = new TH1F("middle_time_of_10to90_S_second_cluster_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});time of crossing half maximum of second cluster at scint [ns];arbitrary unit", 60, 12, 18); TH1F_pi(middle_time_of_10to90_S_second_cluster_pi);
    TH1F* middle_time_of_10to90_C_second_cluster_pi = new TH1F("middle_time_of_10to90_C_second_cluster_pi", "Z#rightarrow#tau#tau(#tau^{-}#rightarrow#pi^{-}#nu_{#tau});time of crossing half maximum of second cluster at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_pi(middle_time_of_10to90_C_second_cluster_pi);

    input = new TFile("20210331_Z2tau2pinu_total_out.root","read");
    input_tree = (TTree *) input -> Get("data");
    input_tree->SetBranchAddress("num_S_cluster", &num_of_S_cluster);
    input_tree->SetBranchAddress("num_C_cluster", &num_of_C_cluster);
    input_tree->SetBranchAddress("num_fired_S_fibers",&num_of_fired_S_fibers);
    input_tree->SetBranchAddress("num_fired_C_fibers",&num_of_fired_C_fibers);
    input_tree->SetBranchAddress("E_S", &total_E_S);
    input_tree->SetBranchAddress("E_Scorr", &total_E_Scorr);
    input_tree->SetBranchAddress("E_C", &total_E_C);
    input_tree->SetBranchAddress("E_DR",&total_E_DR);
    input_tree->SetBranchAddress("E_DRcorr",&total_E_DRcorr);
    input_tree->SetBranchAddress("E_missing",&total_missing_energy);
    input_tree->SetBranchAddress("avg_S_sigma", &average_S_sigma);
    input_tree->SetBranchAddress("avg_C_sigma", &average_C_sigma);
    input_tree->SetBranchAddress("total_signal_max_position_S", &total_signal_peak_position_S);
    input_tree->SetBranchAddress("total_signal_max_position_C", &total_signal_peak_position_C);
    input_tree->SetBranchAddress("time_of_total_signal_rise_threshold_S", &time_signal_rise_threshold_S);
    input_tree->SetBranchAddress("time_of_total_signal_rise_threshold_C", &time_signal_rise_threshold_C);
    input_tree->SetBranchAddress("time_of_total_signal_fall_threshold_S", &time_signal_fall_threshold_S);
    input_tree->SetBranchAddress("time_of_total_signal_fall_threshold_C", &time_signal_fall_threshold_C);
    input_tree->SetBranchAddress("signal_max_position_S_first_cluster", &signal_peak_position_S_first_cluster);
    input_tree->SetBranchAddress("signal_max_position_C_first_cluster", &signal_peak_position_C_first_cluster);
    input_tree->SetBranchAddress("signal_max_position_S_second_cluster", &signal_peak_position_S_second_cluster);
    input_tree->SetBranchAddress("signal_max_position_C_second_cluster", &signal_peak_position_C_second_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_S_first_cluster", &rise_time_10to90_S_first_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_C_first_cluster", &rise_time_10to90_C_first_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_S_second_cluster", &rise_time_10to90_S_second_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_C_second_cluster", &rise_time_10to90_C_second_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_S_first_cluster", &middle_of_10to90_S_first_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_C_first_cluster", &middle_of_10to90_C_first_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_S_second_cluster", &middle_of_10to90_S_second_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_C_second_cluster", &middle_of_10to90_C_second_cluster);

    for(int i=0;i<N2;i++){
        input_tree->GetEntry(i);
        num_S_cluster_pi->Fill(num_of_S_cluster);
        E_Scorr_pi->Fill(total_E_Scorr);
        E_C_pi->Fill(total_E_C);
        avg_S_sigma_pi->Fill(average_S_sigma);
        avg_C_sigma_pi->Fill(average_C_sigma);
        num_fired_S_fibers_pi->Fill(num_of_fired_S_fibers);
        num_fired_C_fibers_pi->Fill(num_of_fired_C_fibers);
        E_missing_pi->Fill(total_missing_energy);
        total_signal_max_position_S_pi->Fill(total_signal_peak_position_S);
        total_signal_max_position_C_pi->Fill(total_signal_peak_position_C);
        time_of_total_signal_rise_threshold_S_pi->Fill(time_signal_rise_threshold_S);
        time_of_total_signal_rise_threshold_C_pi->Fill(time_signal_rise_threshold_C);
        time_of_total_signal_half_width_S_pi->Fill(time_signal_fall_threshold_S - time_signal_rise_threshold_S);
        time_of_total_signal_half_width_C_pi->Fill(time_signal_fall_threshold_C - time_signal_rise_threshold_C);
        signal_max_position_S_first_cluster_pi->Fill(signal_peak_position_S_first_cluster);
        signal_max_position_C_first_cluster_pi->Fill(signal_peak_position_C_first_cluster);
        signal_max_position_S_second_cluster_pi->Fill(signal_peak_position_S_second_cluster);
        signal_max_position_C_second_cluster_pi->Fill(signal_peak_position_C_second_cluster);
        rise_time_10to90_S_first_cluster_pi->Fill(rise_time_10to90_S_first_cluster);
        rise_time_10to90_C_first_cluster_pi->Fill(rise_time_10to90_C_first_cluster);
        rise_time_10to90_S_second_cluster_pi->Fill(rise_time_10to90_S_second_cluster);
        rise_time_10to90_C_second_cluster_pi->Fill(rise_time_10to90_C_second_cluster);
        middle_time_of_10to90_S_first_cluster_pi->Fill(middle_of_10to90_S_first_cluster);
        middle_time_of_10to90_C_first_cluster_pi->Fill(middle_of_10to90_C_first_cluster);
        middle_time_of_10to90_S_second_cluster_pi->Fill(middle_of_10to90_S_second_cluster);
        middle_time_of_10to90_C_second_cluster_pi->Fill(middle_of_10to90_C_second_cluster);
    }
    input->Close();

    // qqbar
    TH1F* num_S_cluster_qqbar = new TH1F("num_S_cluster_qqbar", "Z#rightarrowq#bar{q};the number of clusters at scint;arbitrary unit", 60, 0, 7); TH1F_qqbar(num_S_cluster_qqbar);
    TH1F* E_Scorr_qqbar = new TH1F("E_Scorr_qqbar", "Z#rightarrowq#bar{q};total enegry of scintillation channel [GeV];arbitrary unit", 60, 0, 95); TH1F_qqbar(E_Scorr_qqbar);
    TH1F* E_C_qqbar = new TH1F("E_C_qqbar", "Z#rightarrowq#bar{q};total enegry of Cherenkov channel [GeV];arbitrary unit", 60, 0, 95); TH1F_qqbar(E_C_qqbar);
    TH1F* avg_S_sigma_qqbar = new TH1F("avg_S_sigma_qqbar", "Z#rightarrowq#bar{q};average distance from center of clusters at scint;arbitrary unit", 60, 0, 0.4); TH1F_qqbar(avg_S_sigma_qqbar);
    TH1F* avg_C_sigma_qqbar = new TH1F("avg_C_sigma_qqbar", "Z#rightarrowq#bar{q};average distance from center of clusters at Cherenkov;arbitrary unit", 60, 0, 0.4); TH1F_qqbar(avg_C_sigma_qqbar);
    TH1F* num_fired_S_fibers_qqbar = new TH1F("num_fired_S_fibers_qqbar", "Z#rightarrowq#bar{q};the number of fired scintillation fibers;arbitrary unit", 60, 0, 7000); TH1F_qqbar(num_fired_S_fibers_qqbar);
    TH1F* num_fired_C_fibers_qqbar = new TH1F("num_fired_C_fibers_qqbar", "Z#rightarrowq#bar{q};the number of fired Cherenkov fibers;arbitrary unit", 60, 0, 3000); TH1F_qqbar(num_fired_C_fibers_qqbar);
    TH1F* E_missing_qqbar = new TH1F("E_missing_qqbar", "Z#rightarrowq#bar{q};missing energy [GeV];arbitrary unit", 60, -15, 95); TH1F_qqbar(E_missing_qqbar);
    TH1F* total_signal_max_position_S_qqbar = new TH1F("total_signal_max_position_S_qqbar", "Z#rightarrowq#bar{q};peak position of total signal at scint [ns];arbitrary unit", 50, 15, 20); TH1F_qqbar(total_signal_max_position_S_qqbar);
    TH1F* total_signal_max_position_C_qqbar = new TH1F("total_signal_max_position_C_qqbar", "Z#rightarrowq#bar{q};peak position of total signal at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_qqbar(total_signal_max_position_C_qqbar);
    TH1F* time_of_total_signal_rise_threshold_S_qqbar = new TH1F("time_of_total_signal_rise_threshold_S_qqbar", "Z#rightarrowq#bar{q};time of crossing half maximum of total signal at scint [ns];arbitrary unit", 60, 12, 18); TH1F_qqbar(time_of_total_signal_rise_threshold_S_qqbar);
    TH1F* time_of_total_signal_rise_threshold_C_qqbar = new TH1F("time_of_total_signal_rise_threshold_C_qqbar", "Z#rightarrowq#bar{q};time of crossing half maximum of total signal at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_qqbar(time_of_total_signal_rise_threshold_C_qqbar);
    TH1F* time_of_total_signal_half_width_S_qqbar = new TH1F("time_of_total_signal_half_width_S_qqbar", "Z#rightarrowq#bar{q};FWHM of total signal at scint [ns];arbitrary unit", 60, 1.95, 7.95); TH1F_qqbar(time_of_total_signal_half_width_S_qqbar);
    TH1F* time_of_total_signal_half_width_C_qqbar = new TH1F("time_of_total_signal_half_width_C_qqbar", "Z#rightarrowq#bar{q};FWHM of total signal at Cherenkov [ns];arbitrary unit", 50, -0.05, 4.95); TH1F_qqbar(time_of_total_signal_half_width_C_qqbar);
    TH1F* signal_max_position_S_first_cluster_qqbar = new TH1F("signal_max_position_S_first_cluster_qqbar", "Z#rightarrowq#bar{q};peak position of first cluster at scint [ns];arbitrary unit", 50, 15, 20); TH1F_qqbar(signal_max_position_S_first_cluster_qqbar);
    TH1F* signal_max_position_C_first_cluster_qqbar = new TH1F("signal_max_position_C_first_cluster_qqbar", "Z#rightarrowq#bar{q};peak position of first cluster at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_qqbar(signal_max_position_C_first_cluster_qqbar);
    TH1F* signal_max_position_S_second_cluster_qqbar = new TH1F("signal_max_position_S_second_cluster_qqbar", "Z#rightarrowq#bar{q};peak position of second cluster at scint [ns];arbitrary unit", 50, 15, 20); TH1F_qqbar(signal_max_position_S_second_cluster_qqbar);
    TH1F* signal_max_position_C_second_cluster_qqbar = new TH1F("signal_max_position_C_second_cluster_qqbar", "Z#rightarrowq#bar{q};peak position of second cluster at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_qqbar(signal_max_position_C_second_cluster_qqbar);
    TH1F* rise_time_10to90_S_first_cluster_qqbar = new TH1F("rise_time_10to90_S_first_cluster_qqbar", "Z#rightarrowq#bar{q};risetime(10 to 90%) of first cluster at scint [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_qqbar(rise_time_10to90_S_first_cluster_qqbar);
    TH1F* rise_time_10to90_C_first_cluster_qqbar = new TH1F("rise_time_10to90_C_first_cluster_qqbar", "Z#rightarrowq#bar{q};risetime(10 to 90%) of first cluster at Cherenkov [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_qqbar(rise_time_10to90_C_first_cluster_qqbar);
    TH1F* rise_time_10to90_S_second_cluster_qqbar = new TH1F("rise_time_10to90_S_second_cluster_qqbar", "Z#rightarrowq#bar{q};risetime(10 to 90%) of second cluster at scint [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_qqbar(rise_time_10to90_S_second_cluster_qqbar);
    TH1F* rise_time_10to90_C_second_cluster_qqbar = new TH1F("rise_time_10to90_C_second_cluster_qqbar", "Z#rightarrowq#bar{q};risetime(10 to 90%) of second cluster at Cherenkov [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_qqbar(rise_time_10to90_C_second_cluster_qqbar);
    TH1F* middle_time_of_10to90_S_first_cluster_qqbar = new TH1F("middle_time_of_10to90_S_first_cluster_qqbar", "Z#rightarrowq#bar{q};time of crossing half maximum of first cluster at scint [ns];arbitrary unit", 60, 12, 18); TH1F_qqbar(middle_time_of_10to90_S_first_cluster_qqbar);
    TH1F* middle_time_of_10to90_C_first_cluster_qqbar = new TH1F("middle_time_of_10to90_C_first_cluster_qqbar", "Z#rightarrowq#bar{q};time of crossing half maximum of first cluster at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_qqbar(middle_time_of_10to90_C_first_cluster_qqbar);
    TH1F* middle_time_of_10to90_S_second_cluster_qqbar = new TH1F("middle_time_of_10to90_S_second_cluster_qqbar", "Z#rightarrowq#bar{q};time of crossing half maximum of second cluster at scint [ns];arbitrary unit", 60, 12, 18); TH1F_qqbar(middle_time_of_10to90_S_second_cluster_qqbar);
    TH1F* middle_time_of_10to90_C_second_cluster_qqbar = new TH1F("middle_time_of_10to90_C_second_cluster_qqbar", "Z#rightarrowq#bar{q};time of crossing half maximum of second cluster at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_qqbar(middle_time_of_10to90_C_second_cluster_qqbar);

    input = new TFile("20210313_Z2qqbar_total_out.root", "read");
    input_tree = (TTree*)input->Get("data");
    input_tree->SetBranchAddress("num_S_cluster", &num_of_S_cluster);
    input_tree->SetBranchAddress("num_C_cluster", &num_of_C_cluster);
    input_tree->SetBranchAddress("num_fired_S_fibers", &num_of_fired_S_fibers);
    input_tree->SetBranchAddress("num_fired_C_fibers", &num_of_fired_C_fibers);
    input_tree->SetBranchAddress("E_S", &total_E_S);
    input_tree->SetBranchAddress("E_Scorr", &total_E_Scorr);
    input_tree->SetBranchAddress("E_C", &total_E_C);
    input_tree->SetBranchAddress("E_DR", &total_E_DR);
    input_tree->SetBranchAddress("E_DRcorr", &total_E_DRcorr);
    input_tree->SetBranchAddress("E_missing", &total_missing_energy);
    input_tree->SetBranchAddress("avg_S_sigma", &average_S_sigma);
    input_tree->SetBranchAddress("avg_C_sigma", &average_C_sigma);
    input_tree->SetBranchAddress("total_signal_max_position_S", &total_signal_peak_position_S);
    input_tree->SetBranchAddress("total_signal_max_position_C", &total_signal_peak_position_C);
    input_tree->SetBranchAddress("time_of_total_signal_rise_threshold_S", &time_signal_rise_threshold_S);
    input_tree->SetBranchAddress("time_of_total_signal_rise_threshold_C", &time_signal_rise_threshold_C);
    input_tree->SetBranchAddress("time_of_total_signal_fall_threshold_S", &time_signal_fall_threshold_S);
    input_tree->SetBranchAddress("time_of_total_signal_fall_threshold_C", &time_signal_fall_threshold_C);
    input_tree->SetBranchAddress("signal_max_position_S_first_cluster", &signal_peak_position_S_first_cluster);
    input_tree->SetBranchAddress("signal_max_position_C_first_cluster", &signal_peak_position_C_first_cluster);
    input_tree->SetBranchAddress("signal_max_position_S_second_cluster", &signal_peak_position_S_second_cluster);
    input_tree->SetBranchAddress("signal_max_position_C_second_cluster", &signal_peak_position_C_second_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_S_first_cluster", &rise_time_10to90_S_first_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_C_first_cluster", &rise_time_10to90_C_first_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_S_second_cluster", &rise_time_10to90_S_second_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_C_second_cluster", &rise_time_10to90_C_second_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_S_first_cluster", &middle_of_10to90_S_first_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_C_first_cluster", &middle_of_10to90_C_first_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_S_second_cluster", &middle_of_10to90_S_second_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_C_second_cluster", &middle_of_10to90_C_second_cluster);

    for (int i = 0; i < N3; i++) {
        input_tree->GetEntry(i);
        num_S_cluster_qqbar->Fill(num_of_S_cluster);
        E_Scorr_qqbar->Fill(total_E_Scorr);
        E_C_qqbar->Fill(total_E_C);
        avg_S_sigma_qqbar->Fill(average_S_sigma);
        avg_C_sigma_qqbar->Fill(average_C_sigma);
        num_fired_S_fibers_qqbar->Fill(num_of_fired_S_fibers);
        num_fired_C_fibers_qqbar->Fill(num_of_fired_C_fibers);
        E_missing_qqbar->Fill(total_missing_energy);
        total_signal_max_position_S_qqbar->Fill(total_signal_peak_position_S);
        total_signal_max_position_C_qqbar->Fill(total_signal_peak_position_C);
        time_of_total_signal_rise_threshold_S_qqbar->Fill(time_signal_rise_threshold_S);
        time_of_total_signal_rise_threshold_C_qqbar->Fill(time_signal_rise_threshold_C);
        time_of_total_signal_half_width_S_qqbar->Fill(time_signal_fall_threshold_S - time_signal_rise_threshold_S);
        time_of_total_signal_half_width_C_qqbar->Fill(time_signal_fall_threshold_C - time_signal_rise_threshold_C);
        signal_max_position_S_first_cluster_qqbar->Fill(signal_peak_position_S_first_cluster);
        signal_max_position_C_first_cluster_qqbar->Fill(signal_peak_position_C_first_cluster);
        signal_max_position_S_second_cluster_qqbar->Fill(signal_peak_position_S_second_cluster);
        signal_max_position_C_second_cluster_qqbar->Fill(signal_peak_position_C_second_cluster);
        rise_time_10to90_S_first_cluster_qqbar->Fill(rise_time_10to90_S_first_cluster);
        rise_time_10to90_C_first_cluster_qqbar->Fill(rise_time_10to90_C_first_cluster);
        rise_time_10to90_S_second_cluster_qqbar->Fill(rise_time_10to90_S_second_cluster);
        rise_time_10to90_C_second_cluster_qqbar->Fill(rise_time_10to90_C_second_cluster);
        middle_time_of_10to90_S_first_cluster_qqbar->Fill(middle_of_10to90_S_first_cluster);
        middle_time_of_10to90_C_first_cluster_qqbar->Fill(middle_of_10to90_C_first_cluster);
        middle_time_of_10to90_S_second_cluster_qqbar->Fill(middle_of_10to90_S_second_cluster);
        middle_time_of_10to90_C_second_cluster_qqbar->Fill(middle_of_10to90_C_second_cluster);
    }
    input->Close();

    // pipizero
    TH1F* num_S_cluster_pipizero = new TH1F("num_S_cluster_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);the number of clusters at scint;arbitrary unit", 60, 0, 7); TH1F_pipizero(num_S_cluster_pipizero);
    TH1F* E_Scorr_pipizero = new TH1F("E_Scorr_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);total enegry of scintillation channel [GeV];arbitrary unit", 60, 0, 95); TH1F_pipizero(E_Scorr_pipizero);
    TH1F* E_C_pipizero = new TH1F("E_C_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);total enegry of Cherenkov channel [GeV];arbitrary unit", 60, 0, 95); TH1F_pipizero(E_C_pipizero);
    TH1F* avg_S_sigma_pipizero = new TH1F("avg_S_sigma_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);average distance from center of clusters at scint;arbitrary unit", 60, 0, 0.4); TH1F_pipizero(avg_S_sigma_pipizero);
    TH1F* avg_C_sigma_pipizero = new TH1F("avg_C_sigma_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);average distance from center of clusters at Cherenkov;arbitrary unit", 60, 0, 0.4); TH1F_pipizero(avg_C_sigma_pipizero);
    TH1F* num_fired_S_fibers_pipizero = new TH1F("num_fired_S_fibers_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);the number of fired scintillation fibers;arbitrary unit", 60, 0, 7000); TH1F_pipizero(num_fired_S_fibers_pipizero);
    TH1F* num_fired_C_fibers_pipizero = new TH1F("num_fired_C_fibers_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);the number of fired Cherenkov fibers;arbitrary unit", 60, 0, 3000); TH1F_pipizero(num_fired_C_fibers_pipizero);
    TH1F* E_missing_pipizero = new TH1F("E_missing_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);missing energy [GeV];arbitrary unit", 60, -15, 95); TH1F_pipizero(E_missing_pipizero);
    TH1F* total_signal_max_position_S_pipizero = new TH1F("total_signal_max_position_S_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);peak position of total signal at scint [ns];arbitrary unit", 50, 15, 20); TH1F_pipizero(total_signal_max_position_S_pipizero);
    TH1F* total_signal_max_position_C_pipizero = new TH1F("total_signal_max_position_C_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);peak position of total signal at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_pipizero(total_signal_max_position_C_pipizero);
    TH1F* time_of_total_signal_rise_threshold_S_pipizero = new TH1F("time_of_total_signal_rise_threshold_S_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);time of crossing half maximum of total signal at scint [ns];arbitrary unit", 60, 12, 18); TH1F_pipizero(time_of_total_signal_rise_threshold_S_pipizero);
    TH1F* time_of_total_signal_rise_threshold_C_pipizero = new TH1F("time_of_total_signal_rise_threshold_C_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);time of crossing half maximum of total signal at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_pipizero(time_of_total_signal_rise_threshold_C_pipizero);
    TH1F* time_of_total_signal_half_width_S_pipizero = new TH1F("time_of_total_signal_half_width_S_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);FWHM of total signal at scint [ns];arbitrary unit", 60, 1.95, 7.95); TH1F_pipizero(time_of_total_signal_half_width_S_pipizero);
    TH1F* time_of_total_signal_half_width_C_pipizero = new TH1F("time_of_total_signal_half_width_C_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);FWHM of total signal at Cherenkov [ns];arbitrary unit", 50, -0.05, 4.95); TH1F_pipizero(time_of_total_signal_half_width_C_pipizero);
    TH1F* signal_max_position_S_first_cluster_pipizero = new TH1F("signal_max_position_S_first_cluster_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);peak position of first cluster at scint [ns];arbitrary unit", 50, 15, 20); TH1F_pipizero(signal_max_position_S_first_cluster_pipizero);
    TH1F* signal_max_position_C_first_cluster_pipizero = new TH1F("signal_max_position_C_first_cluster_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);peak position of first cluster at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_pipizero(signal_max_position_C_first_cluster_pipizero);
    TH1F* signal_max_position_S_second_cluster_pipizero = new TH1F("signal_max_position_S_second_cluster_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);peak position of second cluster at scint [ns];arbitrary unit", 50, 15, 20); TH1F_pipizero(signal_max_position_S_second_cluster_pipizero);
    TH1F* signal_max_position_C_second_cluster_pipizero = new TH1F("signal_max_position_C_second_cluster_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);peak position of second cluster at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_pipizero(signal_max_position_C_second_cluster_pipizero);
    TH1F* rise_time_10to90_S_first_cluster_pipizero = new TH1F("rise_time_10to90_S_first_cluster_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);risetime(10 to 90%) of first cluster at scint [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pipizero(rise_time_10to90_S_first_cluster_pipizero);
    TH1F* rise_time_10to90_C_first_cluster_pipizero = new TH1F("rise_time_10to90_C_first_cluster_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);risetime(10 to 90%) of first cluster at Cherenkov [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pipizero(rise_time_10to90_C_first_cluster_pipizero);
    TH1F* rise_time_10to90_S_second_cluster_pipizero = new TH1F("rise_time_10to90_S_second_cluster_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);risetime(10 to 90%) of second cluster at scint [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pipizero(rise_time_10to90_S_second_cluster_pipizero);
    TH1F* rise_time_10to90_C_second_cluster_pipizero = new TH1F("rise_time_10to90_C_second_cluster_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);risetime(10 to 90%) of second cluster at Cherenkov [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pipizero(rise_time_10to90_C_second_cluster_pipizero);
    TH1F* middle_time_of_10to90_S_first_cluster_pipizero = new TH1F("middle_time_of_10to90_S_first_cluster_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);time of crossing half maximum of first cluster at scint [ns];arbitrary unit", 60, 12, 18); TH1F_pipizero(middle_time_of_10to90_S_first_cluster_pipizero);
    TH1F* middle_time_of_10to90_C_first_cluster_pipizero = new TH1F("middle_time_of_10to90_C_first_cluster_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);time of crossing half maximum of first cluster at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_pipizero(middle_time_of_10to90_C_first_cluster_pipizero);
    TH1F* middle_time_of_10to90_S_second_cluster_pipizero = new TH1F("middle_time_of_10to90_S_second_cluster_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);time of crossing half maximum of second cluster at scint [ns];arbitrary unit", 60, 12, 18); TH1F_pipizero(middle_time_of_10to90_S_second_cluster_pipizero);
    TH1F* middle_time_of_10to90_C_second_cluster_pipizero = new TH1F("middle_time_of_10to90_C_second_cluster_pipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{0}#nu);time of crossing half maximum of second cluster at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_pipizero(middle_time_of_10to90_C_second_cluster_pipizero);

    input = new TFile("20210413_Z2tau2pipizeronu_total_out.root", "read");
    input_tree = (TTree*)input->Get("data");
    input_tree->SetBranchAddress("num_S_cluster", &num_of_S_cluster);
    input_tree->SetBranchAddress("num_C_cluster", &num_of_C_cluster);
    input_tree->SetBranchAddress("num_fired_S_fibers", &num_of_fired_S_fibers);
    input_tree->SetBranchAddress("num_fired_C_fibers", &num_of_fired_C_fibers);
    input_tree->SetBranchAddress("E_S", &total_E_S);
    input_tree->SetBranchAddress("E_Scorr", &total_E_Scorr);
    input_tree->SetBranchAddress("E_C", &total_E_C);
    input_tree->SetBranchAddress("E_DR", &total_E_DR);
    input_tree->SetBranchAddress("E_DRcorr", &total_E_DRcorr);
    input_tree->SetBranchAddress("E_missing", &total_missing_energy);
    input_tree->SetBranchAddress("avg_S_sigma", &average_S_sigma);
    input_tree->SetBranchAddress("avg_C_sigma", &average_C_sigma);
    input_tree->SetBranchAddress("total_signal_max_position_S", &total_signal_peak_position_S);
    input_tree->SetBranchAddress("total_signal_max_position_C", &total_signal_peak_position_C);
    input_tree->SetBranchAddress("time_of_total_signal_rise_threshold_S", &time_signal_rise_threshold_S);
    input_tree->SetBranchAddress("time_of_total_signal_rise_threshold_C", &time_signal_rise_threshold_C);
    input_tree->SetBranchAddress("time_of_total_signal_fall_threshold_S", &time_signal_fall_threshold_S);
    input_tree->SetBranchAddress("time_of_total_signal_fall_threshold_C", &time_signal_fall_threshold_C);
    input_tree->SetBranchAddress("signal_max_position_S_first_cluster", &signal_peak_position_S_first_cluster);
    input_tree->SetBranchAddress("signal_max_position_C_first_cluster", &signal_peak_position_C_first_cluster);
    input_tree->SetBranchAddress("signal_max_position_S_second_cluster", &signal_peak_position_S_second_cluster);
    input_tree->SetBranchAddress("signal_max_position_C_second_cluster", &signal_peak_position_C_second_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_S_first_cluster", &rise_time_10to90_S_first_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_C_first_cluster", &rise_time_10to90_C_first_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_S_second_cluster", &rise_time_10to90_S_second_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_C_second_cluster", &rise_time_10to90_C_second_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_S_first_cluster", &middle_of_10to90_S_first_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_C_first_cluster", &middle_of_10to90_C_first_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_S_second_cluster", &middle_of_10to90_S_second_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_C_second_cluster", &middle_of_10to90_C_second_cluster);

    for (int i = 0; i < N4; i++) {
        input_tree->GetEntry(i);
        num_S_cluster_pipizero->Fill(num_of_S_cluster);
        E_Scorr_pipizero->Fill(total_E_Scorr);
        E_C_pipizero->Fill(total_E_C);
        avg_S_sigma_pipizero->Fill(average_S_sigma);
        avg_C_sigma_pipizero->Fill(average_C_sigma);
        num_fired_S_fibers_pipizero->Fill(num_of_fired_S_fibers);
        num_fired_C_fibers_pipizero->Fill(num_of_fired_C_fibers);
        E_missing_pipizero->Fill(total_missing_energy);
        total_signal_max_position_S_pipizero->Fill(total_signal_peak_position_S);
        total_signal_max_position_C_pipizero->Fill(total_signal_peak_position_C);
        time_of_total_signal_rise_threshold_S_pipizero->Fill(time_signal_rise_threshold_S);
        time_of_total_signal_rise_threshold_C_pipizero->Fill(time_signal_rise_threshold_C);
        time_of_total_signal_half_width_S_pipizero->Fill(time_signal_fall_threshold_S - time_signal_rise_threshold_S);
        time_of_total_signal_half_width_C_pipizero->Fill(time_signal_fall_threshold_C - time_signal_rise_threshold_C);
        signal_max_position_S_first_cluster_pipizero->Fill(signal_peak_position_S_first_cluster);
        signal_max_position_C_first_cluster_pipizero->Fill(signal_peak_position_C_first_cluster);
        signal_max_position_S_second_cluster_pipizero->Fill(signal_peak_position_S_second_cluster);
        signal_max_position_C_second_cluster_pipizero->Fill(signal_peak_position_C_second_cluster);
        rise_time_10to90_S_first_cluster_pipizero->Fill(rise_time_10to90_S_first_cluster);
        rise_time_10to90_C_first_cluster_pipizero->Fill(rise_time_10to90_C_first_cluster);
        rise_time_10to90_S_second_cluster_pipizero->Fill(rise_time_10to90_S_second_cluster);
        rise_time_10to90_C_second_cluster_pipizero->Fill(rise_time_10to90_C_second_cluster);
        middle_time_of_10to90_S_first_cluster_pipizero->Fill(middle_of_10to90_S_first_cluster);
        middle_time_of_10to90_C_first_cluster_pipizero->Fill(middle_of_10to90_C_first_cluster);
        middle_time_of_10to90_S_second_cluster_pipizero->Fill(middle_of_10to90_S_second_cluster);
        middle_time_of_10to90_C_second_cluster_pipizero->Fill(middle_of_10to90_C_second_cluster);
    }
    input->Close();
    
    // pipizeropizero
    TH1F* num_S_cluster_pipizeropizero = new TH1F("num_S_cluster_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);the number of clusters at scint;arbitrary unit", 60, 0, 7); TH1F_pipizeropizero(num_S_cluster_pipizeropizero);
    TH1F* E_Scorr_pipizeropizero = new TH1F("E_Scorr_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);total enegry of scintillation channel [GeV];arbitrary unit", 60, 0, 95); TH1F_pipizeropizero(E_Scorr_pipizeropizero);
    TH1F* E_C_pipizeropizero = new TH1F("E_C_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);total enegry of Cherenkov channel [GeV];arbitrary unit", 60, 0, 95); TH1F_pipizeropizero(E_C_pipizeropizero);
    TH1F* avg_S_sigma_pipizeropizero = new TH1F("avg_S_sigma_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);average distance from center of clusters at scint;arbitrary unit", 60, 0, 0.4); TH1F_pipizeropizero(avg_S_sigma_pipizeropizero);
    TH1F* avg_C_sigma_pipizeropizero = new TH1F("avg_C_sigma_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);average distance from center of clusters at Cherenkov;arbitrary unit", 60, 0, 0.4); TH1F_pipizeropizero(avg_C_sigma_pipizeropizero);
    TH1F* num_fired_S_fibers_pipizeropizero = new TH1F("num_fired_S_fibers_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);the number of fired scintillation fibers;arbitrary unit", 60, 0, 7000); TH1F_pipizeropizero(num_fired_S_fibers_pipizeropizero);
    TH1F* num_fired_C_fibers_pipizeropizero = new TH1F("num_fired_C_fibers_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);the number of fired Cherenkov fibers;arbitrary unit", 60, 0, 3000); TH1F_pipizeropizero(num_fired_C_fibers_pipizeropizero);
    TH1F* E_missing_pipizeropizero = new TH1F("E_missing_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);missing energy [GeV];arbitrary unit", 60, -15, 95); TH1F_pipizeropizero(E_missing_pipizeropizero);
    TH1F* total_signal_max_position_S_pipizeropizero = new TH1F("total_signal_max_position_S_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);peak position of total signal at scint [ns];arbitrary unit", 50, 15, 20); TH1F_pipizeropizero(total_signal_max_position_S_pipizeropizero);
    TH1F* total_signal_max_position_C_pipizeropizero = new TH1F("total_signal_max_position_C_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);peak position of total signal at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_pipizeropizero(total_signal_max_position_C_pipizeropizero);
    TH1F* time_of_total_signal_rise_threshold_S_pipizeropizero = new TH1F("time_of_total_signal_rise_threshold_S_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);time of crossing half maximum of total signal at scint [ns];arbitrary unit", 60, 12, 18); TH1F_pipizeropizero(time_of_total_signal_rise_threshold_S_pipizeropizero);
    TH1F* time_of_total_signal_rise_threshold_C_pipizeropizero = new TH1F("time_of_total_signal_rise_threshold_C_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);time of crossing half maximum of total signal at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_pipizeropizero(time_of_total_signal_rise_threshold_C_pipizeropizero);
    TH1F* time_of_total_signal_half_width_S_pipizeropizero = new TH1F("time_of_total_signal_half_width_S_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);FWHM of total signal at scint [ns];arbitrary unit", 60, 1.95, 7.95); TH1F_pipizeropizero(time_of_total_signal_half_width_S_pipizeropizero);
    TH1F* time_of_total_signal_half_width_C_pipizeropizero = new TH1F("time_of_total_signal_half_width_C_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);FWHM of total signal at Cherenkov [ns];arbitrary unit", 50, -0.05, 4.95); TH1F_pipizeropizero(time_of_total_signal_half_width_C_pipizeropizero);
    TH1F* signal_max_position_S_first_cluster_pipizeropizero = new TH1F("signal_max_position_S_first_cluster_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);peak position of first cluster at scint [ns];arbitrary unit", 50, 15, 20); TH1F_pipizeropizero(signal_max_position_S_first_cluster_pipizeropizero);
    TH1F* signal_max_position_C_first_cluster_pipizeropizero = new TH1F("signal_max_position_C_first_cluster_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);peak position of first cluster at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_pipizeropizero(signal_max_position_C_first_cluster_pipizeropizero);
    TH1F* signal_max_position_S_second_cluster_pipizeropizero = new TH1F("signal_max_position_S_second_cluster_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);peak position of second cluster at scint [ns];arbitrary unit", 50, 15, 20); TH1F_pipizeropizero(signal_max_position_S_second_cluster_pipizeropizero);
    TH1F* signal_max_position_C_second_cluster_pipizeropizero = new TH1F("signal_max_position_C_second_cluster_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);peak position of second cluster at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_pipizeropizero(signal_max_position_C_second_cluster_pipizeropizero);
    TH1F* rise_time_10to90_S_first_cluster_pipizeropizero = new TH1F("rise_time_10to90_S_first_cluster_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);risetime(10 to 90%) of first cluster at scint [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pipizeropizero(rise_time_10to90_S_first_cluster_pipizeropizero);
    TH1F* rise_time_10to90_C_first_cluster_pipizeropizero = new TH1F("rise_time_10to90_C_first_cluster_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);risetime(10 to 90%) of first cluster at Cherenkov [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pipizeropizero(rise_time_10to90_C_first_cluster_pipizeropizero);
    TH1F* rise_time_10to90_S_second_cluster_pipizeropizero = new TH1F("rise_time_10to90_S_second_cluster_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);risetime(10 to 90%) of second cluster at scint [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pipizeropizero(rise_time_10to90_S_second_cluster_pipizeropizero);
    TH1F* rise_time_10to90_C_second_cluster_pipizeropizero = new TH1F("rise_time_10to90_C_second_cluster_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);risetime(10 to 90%) of second cluster at Cherenkov [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pipizeropizero(rise_time_10to90_C_second_cluster_pipizeropizero);
    TH1F* middle_time_of_10to90_S_first_cluster_pipizeropizero = new TH1F("middle_time_of_10to90_S_first_cluster_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);time of crossing half maximum of first cluster at scint [ns];arbitrary unit", 60, 12, 18); TH1F_pipizeropizero(middle_time_of_10to90_S_first_cluster_pipizeropizero);
    TH1F* middle_time_of_10to90_C_first_cluster_pipizeropizero = new TH1F("middle_time_of_10to90_C_first_cluster_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);time of crossing half maximum of first cluster at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_pipizeropizero(middle_time_of_10to90_C_first_cluster_pipizeropizero);
    TH1F* middle_time_of_10to90_S_second_cluster_pipizeropizero = new TH1F("middle_time_of_10to90_S_second_cluster_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);time of crossing half maximum of second cluster at scint [ns];arbitrary unit", 60, 12, 18); TH1F_pipizeropizero(middle_time_of_10to90_S_second_cluster_pipizeropizero);
    TH1F* middle_time_of_10to90_C_second_cluster_pipizeropizero = new TH1F("middle_time_of_10to90_C_second_cluster_pipizeropizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}2#pi^{0}#nu);time of crossing half maximum of second cluster at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_pipizeropizero(middle_time_of_10to90_C_second_cluster_pipizeropizero);

    input = new TFile("20210414_Z2tau2pipizeropizeronu_total_out.root", "read");
    input_tree = (TTree*)input->Get("data");
    input_tree->SetBranchAddress("num_S_cluster", &num_of_S_cluster);
    input_tree->SetBranchAddress("num_C_cluster", &num_of_C_cluster);
    input_tree->SetBranchAddress("num_fired_S_fibers", &num_of_fired_S_fibers);
    input_tree->SetBranchAddress("num_fired_C_fibers", &num_of_fired_C_fibers);
    input_tree->SetBranchAddress("E_S", &total_E_S);
    input_tree->SetBranchAddress("E_Scorr", &total_E_Scorr);
    input_tree->SetBranchAddress("E_C", &total_E_C);
    input_tree->SetBranchAddress("E_DR", &total_E_DR);
    input_tree->SetBranchAddress("E_DRcorr", &total_E_DRcorr);
    input_tree->SetBranchAddress("E_missing", &total_missing_energy);
    input_tree->SetBranchAddress("avg_S_sigma", &average_S_sigma);
    input_tree->SetBranchAddress("avg_C_sigma", &average_C_sigma);
    input_tree->SetBranchAddress("total_signal_max_position_S", &total_signal_peak_position_S);
    input_tree->SetBranchAddress("total_signal_max_position_C", &total_signal_peak_position_C);
    input_tree->SetBranchAddress("time_of_total_signal_rise_threshold_S", &time_signal_rise_threshold_S);
    input_tree->SetBranchAddress("time_of_total_signal_rise_threshold_C", &time_signal_rise_threshold_C);
    input_tree->SetBranchAddress("time_of_total_signal_fall_threshold_S", &time_signal_fall_threshold_S);
    input_tree->SetBranchAddress("time_of_total_signal_fall_threshold_C", &time_signal_fall_threshold_C);
    input_tree->SetBranchAddress("signal_max_position_S_first_cluster", &signal_peak_position_S_first_cluster);
    input_tree->SetBranchAddress("signal_max_position_C_first_cluster", &signal_peak_position_C_first_cluster);
    input_tree->SetBranchAddress("signal_max_position_S_second_cluster", &signal_peak_position_S_second_cluster);
    input_tree->SetBranchAddress("signal_max_position_C_second_cluster", &signal_peak_position_C_second_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_S_first_cluster", &rise_time_10to90_S_first_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_C_first_cluster", &rise_time_10to90_C_first_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_S_second_cluster", &rise_time_10to90_S_second_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_C_second_cluster", &rise_time_10to90_C_second_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_S_first_cluster", &middle_of_10to90_S_first_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_C_first_cluster", &middle_of_10to90_C_first_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_S_second_cluster", &middle_of_10to90_S_second_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_C_second_cluster", &middle_of_10to90_C_second_cluster);

    for (int i = 0; i < N5; i++) {
        input_tree->GetEntry(i);
        num_S_cluster_pipizeropizero->Fill(num_of_S_cluster);
        E_Scorr_pipizeropizero->Fill(total_E_Scorr);
        E_C_pipizeropizero->Fill(total_E_C);
        avg_S_sigma_pipizeropizero->Fill(average_S_sigma);
        avg_C_sigma_pipizeropizero->Fill(average_C_sigma);
        num_fired_S_fibers_pipizeropizero->Fill(num_of_fired_S_fibers);
        num_fired_C_fibers_pipizeropizero->Fill(num_of_fired_C_fibers);
        E_missing_pipizeropizero->Fill(total_missing_energy);
        total_signal_max_position_S_pipizeropizero->Fill(total_signal_peak_position_S);
        total_signal_max_position_C_pipizeropizero->Fill(total_signal_peak_position_C);
        time_of_total_signal_rise_threshold_S_pipizeropizero->Fill(time_signal_rise_threshold_S);
        time_of_total_signal_rise_threshold_C_pipizeropizero->Fill(time_signal_rise_threshold_C);
        time_of_total_signal_half_width_S_pipizeropizero->Fill(time_signal_fall_threshold_S - time_signal_rise_threshold_S);
        time_of_total_signal_half_width_C_pipizeropizero->Fill(time_signal_fall_threshold_C - time_signal_rise_threshold_C);
        signal_max_position_S_first_cluster_pipizeropizero->Fill(signal_peak_position_S_first_cluster);
        signal_max_position_C_first_cluster_pipizeropizero->Fill(signal_peak_position_C_first_cluster);
        signal_max_position_S_second_cluster_pipizeropizero->Fill(signal_peak_position_S_second_cluster);
        signal_max_position_C_second_cluster_pipizeropizero->Fill(signal_peak_position_C_second_cluster);
        rise_time_10to90_S_first_cluster_pipizeropizero->Fill(rise_time_10to90_S_first_cluster);
        rise_time_10to90_C_first_cluster_pipizeropizero->Fill(rise_time_10to90_C_first_cluster);
        rise_time_10to90_S_second_cluster_pipizeropizero->Fill(rise_time_10to90_S_second_cluster);
        rise_time_10to90_C_second_cluster_pipizeropizero->Fill(rise_time_10to90_C_second_cluster);
        middle_time_of_10to90_S_first_cluster_pipizeropizero->Fill(middle_of_10to90_S_first_cluster);
        middle_time_of_10to90_C_first_cluster_pipizeropizero->Fill(middle_of_10to90_C_first_cluster);
        middle_time_of_10to90_S_second_cluster_pipizeropizero->Fill(middle_of_10to90_S_second_cluster);
        middle_time_of_10to90_C_second_cluster_pipizeropizero->Fill(middle_of_10to90_C_second_cluster);
    }
    input->Close();

    // pipipipizero
    TH1F* num_S_cluster_pipipipizero = new TH1F("num_S_cluster_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);the number of clusters at scint;arbitrary unit", 60, 0, 7); TH1F_pipipipizero(num_S_cluster_pipipipizero);
    TH1F* E_Scorr_pipipipizero = new TH1F("E_Scorr_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);total enegry of scintillation channel [GeV];arbitrary unit", 60, 0, 95); TH1F_pipipipizero(E_Scorr_pipipipizero);
    TH1F* E_C_pipipipizero = new TH1F("E_C_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);total enegry of Cherenkov channel [GeV];arbitrary unit", 60, 0, 95); TH1F_pipipipizero(E_C_pipipipizero);
    TH1F* avg_S_sigma_pipipipizero = new TH1F("avg_S_sigma_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);average distance from center of clusters at scint;arbitrary unit", 60, 0, 0.4); TH1F_pipipipizero(avg_S_sigma_pipipipizero);
    TH1F* avg_C_sigma_pipipipizero = new TH1F("avg_C_sigma_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);average distance from center of clusters at Cherenkov;arbitrary unit", 60, 0, 0.4); TH1F_pipipipizero(avg_C_sigma_pipipipizero);
    TH1F* num_fired_S_fibers_pipipipizero = new TH1F("num_fired_S_fibers_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);the number of fired scintillation fibers;arbitrary unit", 60, 0, 7000); TH1F_pipipipizero(num_fired_S_fibers_pipipipizero);
    TH1F* num_fired_C_fibers_pipipipizero = new TH1F("num_fired_C_fibers_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);the number of fired Cherenkov fibers;arbitrary unit", 60, 0, 3000); TH1F_pipipipizero(num_fired_C_fibers_pipipipizero);
    TH1F* E_missing_pipipipizero = new TH1F("E_missing_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);missing energy [GeV];arbitrary unit", 60, -15, 95); TH1F_pipipipizero(E_missing_pipipipizero);
    TH1F* total_signal_max_position_S_pipipipizero = new TH1F("total_signal_max_position_S_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);peak position of total signal at scint [ns];arbitrary unit", 50, 15, 20); TH1F_pipipipizero(total_signal_max_position_S_pipipipizero);
    TH1F* total_signal_max_position_C_pipipipizero = new TH1F("total_signal_max_position_C_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);peak position of total signal at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_pipipipizero(total_signal_max_position_C_pipipipizero);
    TH1F* time_of_total_signal_rise_threshold_S_pipipipizero = new TH1F("time_of_total_signal_rise_threshold_S_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);time of crossing half maximum of total signal at scint [ns];arbitrary unit", 60, 12, 18); TH1F_pipipipizero(time_of_total_signal_rise_threshold_S_pipipipizero);
    TH1F* time_of_total_signal_rise_threshold_C_pipipipizero = new TH1F("time_of_total_signal_rise_threshold_C_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);time of crossing half maximum of total signal at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_pipipipizero(time_of_total_signal_rise_threshold_C_pipipipizero);
    TH1F* time_of_total_signal_half_width_S_pipipipizero = new TH1F("time_of_total_signal_half_width_S_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);FWHM of total signal at scint [ns];arbitrary unit", 60, 1.95, 7.95); TH1F_pipipipizero(time_of_total_signal_half_width_S_pipipipizero);
    TH1F* time_of_total_signal_half_width_C_pipipipizero = new TH1F("time_of_total_signal_half_width_C_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);FWHM of total signal at Cherenkov [ns];arbitrary unit", 50, -0.05, 4.95); TH1F_pipipipizero(time_of_total_signal_half_width_C_pipipipizero);
    TH1F* signal_max_position_S_first_cluster_pipipipizero = new TH1F("signal_max_position_S_first_cluster_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);peak position of first cluster at scint [ns];arbitrary unit", 50, 15, 20); TH1F_pipipipizero(signal_max_position_S_first_cluster_pipipipizero);
    TH1F* signal_max_position_C_first_cluster_pipipipizero = new TH1F("signal_max_position_C_first_cluster_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);peak position of first cluster at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_pipipipizero(signal_max_position_C_first_cluster_pipipipizero);
    TH1F* signal_max_position_S_second_cluster_pipipipizero = new TH1F("signal_max_position_S_second_cluster_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);peak position of second cluster at scint [ns];arbitrary unit", 50, 15, 20); TH1F_pipipipizero(signal_max_position_S_second_cluster_pipipipizero);
    TH1F* signal_max_position_C_second_cluster_pipipipizero = new TH1F("signal_max_position_C_second_cluster_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);peak position of second cluster at Cherenkov [ns];arbitrary unit", 60, 12, 18); TH1F_pipipipizero(signal_max_position_C_second_cluster_pipipipizero);
    TH1F* rise_time_10to90_S_first_cluster_pipipipizero = new TH1F("rise_time_10to90_S_first_cluster_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);risetime(10 to 90%) of first cluster at scint [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pipipipizero(rise_time_10to90_S_first_cluster_pipipipizero);
    TH1F* rise_time_10to90_C_first_cluster_pipipipizero = new TH1F("rise_time_10to90_C_first_cluster_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);risetime(10 to 90%) of first cluster at Cherenkov [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pipipipizero(rise_time_10to90_C_first_cluster_pipipipizero);
    TH1F* rise_time_10to90_S_second_cluster_pipipipizero = new TH1F("rise_time_10to90_S_second_cluster_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);risetime(10 to 90%) of second cluster at scint [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pipipipizero(rise_time_10to90_S_second_cluster_pipipipizero);
    TH1F* rise_time_10to90_C_second_cluster_pipipipizero = new TH1F("rise_time_10to90_C_second_cluster_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);risetime(10 to 90%) of second cluster at Cherenkov [ns];arbitrary unit", 60, -0.05, 5.95); TH1F_pipipipizero(rise_time_10to90_C_second_cluster_pipipipizero);
    TH1F* middle_time_of_10to90_S_first_cluster_pipipipizero = new TH1F("middle_time_of_10to90_S_first_cluster_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);time of crossing half maximum of first cluster at scint [ns];arbitrary unit", 60, 12, 18); TH1F_pipipipizero(middle_time_of_10to90_S_first_cluster_pipipipizero);
    TH1F* middle_time_of_10to90_C_first_cluster_pipipipizero = new TH1F("middle_time_of_10to90_C_first_cluster_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);time of crossing half maximum of first cluster at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_pipipipizero(middle_time_of_10to90_C_first_cluster_pipipipizero);
    TH1F* middle_time_of_10to90_S_second_cluster_pipipipizero = new TH1F("middle_time_of_10to90_S_second_cluster_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);time of crossing half maximum of second cluster at scint [ns];arbitrary unit", 60, 12, 18); TH1F_pipipipizero(middle_time_of_10to90_S_second_cluster_pipipipizero);
    TH1F* middle_time_of_10to90_C_second_cluster_pipipipizero = new TH1F("middle_time_of_10to90_C_second_cluster_pipipipizero", "Z#rightarrow#tau#tau(#tau#rightarrow#pi^{-}#pi^{+}#pi^{-}#pi^{0}#nu);time of crossing half maximum of second cluster at Cherenkov [ns];arbitrary unit", 50, 12, 17); TH1F_pipipipizero(middle_time_of_10to90_C_second_cluster_pipipipizero);

    input = new TFile("20210418_Z2tau2pipipipizero_total_out.root", "read");
    input_tree = (TTree*)input->Get("data");
    input_tree->SetBranchAddress("num_S_cluster", &num_of_S_cluster);
    input_tree->SetBranchAddress("num_C_cluster", &num_of_C_cluster);
    input_tree->SetBranchAddress("num_fired_S_fibers", &num_of_fired_S_fibers);
    input_tree->SetBranchAddress("num_fired_C_fibers", &num_of_fired_C_fibers);
    input_tree->SetBranchAddress("E_S", &total_E_S);
    input_tree->SetBranchAddress("E_Scorr", &total_E_Scorr);
    input_tree->SetBranchAddress("E_C", &total_E_C);
    input_tree->SetBranchAddress("E_DR", &total_E_DR);
    input_tree->SetBranchAddress("E_DRcorr", &total_E_DRcorr);
    input_tree->SetBranchAddress("E_missing", &total_missing_energy);
    input_tree->SetBranchAddress("avg_S_sigma", &average_S_sigma);
    input_tree->SetBranchAddress("avg_C_sigma", &average_C_sigma);
    input_tree->SetBranchAddress("total_signal_max_position_S", &total_signal_peak_position_S);
    input_tree->SetBranchAddress("total_signal_max_position_C", &total_signal_peak_position_C);
    input_tree->SetBranchAddress("time_of_total_signal_rise_threshold_S", &time_signal_rise_threshold_S);
    input_tree->SetBranchAddress("time_of_total_signal_rise_threshold_C", &time_signal_rise_threshold_C);
    input_tree->SetBranchAddress("time_of_total_signal_fall_threshold_S", &time_signal_fall_threshold_S);
    input_tree->SetBranchAddress("time_of_total_signal_fall_threshold_C", &time_signal_fall_threshold_C);
    input_tree->SetBranchAddress("signal_max_position_S_first_cluster", &signal_peak_position_S_first_cluster);
    input_tree->SetBranchAddress("signal_max_position_C_first_cluster", &signal_peak_position_C_first_cluster);
    input_tree->SetBranchAddress("signal_max_position_S_second_cluster", &signal_peak_position_S_second_cluster);
    input_tree->SetBranchAddress("signal_max_position_C_second_cluster", &signal_peak_position_C_second_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_S_first_cluster", &rise_time_10to90_S_first_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_C_first_cluster", &rise_time_10to90_C_first_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_S_second_cluster", &rise_time_10to90_S_second_cluster);
    input_tree->SetBranchAddress("rise_time_10to90_C_second_cluster", &rise_time_10to90_C_second_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_S_first_cluster", &middle_of_10to90_S_first_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_C_first_cluster", &middle_of_10to90_C_first_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_S_second_cluster", &middle_of_10to90_S_second_cluster);
    input_tree->SetBranchAddress("middle_time_of_10to90_C_second_cluster", &middle_of_10to90_C_second_cluster);

    for (int i = 0; i < N6; i++) {
        input_tree->GetEntry(i);
        num_S_cluster_pipipipizero->Fill(num_of_S_cluster);
        E_Scorr_pipipipizero->Fill(total_E_Scorr);
        E_C_pipipipizero->Fill(total_E_C);
        avg_S_sigma_pipipipizero->Fill(average_S_sigma);
        avg_C_sigma_pipipipizero->Fill(average_C_sigma);
        num_fired_S_fibers_pipipipizero->Fill(num_of_fired_S_fibers);
        num_fired_C_fibers_pipipipizero->Fill(num_of_fired_C_fibers);
        E_missing_pipipipizero->Fill(total_missing_energy);
        total_signal_max_position_S_pipipipizero->Fill(total_signal_peak_position_S);
        total_signal_max_position_C_pipipipizero->Fill(total_signal_peak_position_C);
        time_of_total_signal_rise_threshold_S_pipipipizero->Fill(time_signal_rise_threshold_S);
        time_of_total_signal_rise_threshold_C_pipipipizero->Fill(time_signal_rise_threshold_C);
        time_of_total_signal_half_width_S_pipipipizero->Fill(time_signal_fall_threshold_S - time_signal_rise_threshold_S);
        time_of_total_signal_half_width_C_pipipipizero->Fill(time_signal_fall_threshold_C - time_signal_rise_threshold_C);
        signal_max_position_S_first_cluster_pipipipizero->Fill(signal_peak_position_S_first_cluster);
        signal_max_position_C_first_cluster_pipipipizero->Fill(signal_peak_position_C_first_cluster);
        signal_max_position_S_second_cluster_pipipipizero->Fill(signal_peak_position_S_second_cluster);
        signal_max_position_C_second_cluster_pipipipizero->Fill(signal_peak_position_C_second_cluster);
        rise_time_10to90_S_first_cluster_pipipipizero->Fill(rise_time_10to90_S_first_cluster);
        rise_time_10to90_C_first_cluster_pipipipizero->Fill(rise_time_10to90_C_first_cluster);
        rise_time_10to90_S_second_cluster_pipipipizero->Fill(rise_time_10to90_S_second_cluster);
        rise_time_10to90_C_second_cluster_pipipipizero->Fill(rise_time_10to90_C_second_cluster);
        middle_time_of_10to90_S_first_cluster_pipipipizero->Fill(middle_of_10to90_S_first_cluster);
        middle_time_of_10to90_C_first_cluster_pipipipizero->Fill(middle_of_10to90_C_first_cluster);
        middle_time_of_10to90_S_second_cluster_pipipipizero->Fill(middle_of_10to90_S_second_cluster);
        middle_time_of_10to90_C_second_cluster_pipipipizero->Fill(middle_of_10to90_C_second_cluster);
    }
    input->Close();

    for (int i = 0; i < paths.size(); i++) {
        TH1F_norm(pipipi_TH1Fs.at(i));
        TH1F_norm(pi_TH1Fs.at(i));
        TH1F_norm(qqbar_TH1Fs.at(i));
        TH1F_norm(pipizero_TH1Fs.at(i));
        TH1F_norm(pipizeropizero_TH1Fs.at(i));
        TH1F_norm(pipipipizero_TH1Fs.at(i));
    }

    TCanvas* c = new TCanvas("c", "", 1500, 1200);

    for (int i = 0; i < paths.size(); i++) {

        float temp_max_y = -1;
        if (qqbar_TH1Fs.at(i)->GetMaximum() > temp_max_y) temp_max_y = qqbar_TH1Fs.at(i)->GetMaximum();
        if (pi_TH1Fs.at(i)->GetMaximum() > temp_max_y) temp_max_y = pi_TH1Fs.at(i)->GetMaximum();
        if (pipipi_TH1Fs.at(i)->GetMaximum() > temp_max_y) temp_max_y = pipipi_TH1Fs.at(i)->GetMaximum();
        if (pipizero_TH1Fs.at(i)->GetMaximum() > temp_max_y) temp_max_y = pipizero_TH1Fs.at(i)->GetMaximum();
        if (pipizeropizero_TH1Fs.at(i)->GetMaximum() > temp_max_y) temp_max_y = pipizeropizero_TH1Fs.at(i)->GetMaximum();
        if (pipipipizero_TH1Fs.at(i)->GetMaximum() > temp_max_y) temp_max_y = pipipipizero_TH1Fs.at(i)->GetMaximum();
        qqbar_TH1Fs.at(i)->GetYaxis()->SetRangeUser(0., temp_max_y*1.1);

        qqbar_TH1Fs.at(i)->Draw("Hist");
	//        pi_TH1Fs.at(i)->Draw("HistSAME");
	//       pipipi_TH1Fs.at(i)->Draw("HistSAME");
        pipizero_TH1Fs.at(i)->Draw("HistSAME");
        pipizeropizero_TH1Fs.at(i)->Draw("HistSAME");
        pipipipizero_TH1Fs.at(i)->Draw("HistSAME");
	//	gPad->BuildLegend();
        gStyle->SetOptTitle(0);
        c->SaveAs(paths.at(i).c_str());
    }
}
