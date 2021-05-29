// ./bin/Reco is not required to run this code
# define Filter 1.0 // GeV
# define max_dis 0.8
# define N_tow_Phi 283 // the number of towers at phi direction

#include "RootInterface.h"
#include "RecoInterface.h"
#include "DRsimInterface.h"
#include "fastjetInterface.h"
#include "functions.h"

#include "RecoTower.h"

#include "GeoSvc.h"
#include "GridDRcalo.h"

#include "HepMC3/ReaderRootTree.h"
#include "HepMC3/GenEvent.h"
#include "HepMC3/GenParticle.h"
#include "HepMC3/GenVertex.h"

#include "TROOT.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TF2.h"
#include "TPaveStats.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TGraph.h"

#include <iostream>
#include <string>
#include <algorithm>

double absolute(double num) {
    if (num >= 0) return num;
    else return (-1) * num;
}

double Min(double num1, double num2) {
    if (num1 > num2) return num2;
    else return num1;
}

double sigma(TLorentzVector cluster, std::vector<TLorentzVector> constituents_of_cluster) {

    double cluster_phi = cluster.Phi();
    double cluster_theta = cluster.Theta();

    double sig_sq = 0;
    double total_energy = 0;
    for (auto constituent : constituents_of_cluster) {
        double delta_phi = cluster_phi - constituent.Phi(); delta_phi = Min( absolute(delta_phi), 2 * TMath::Pi() - absolute(delta_phi) );
        double delta_theta = cluster_theta - constituent.Theta(); delta_theta = Min(absolute(delta_theta), TMath::Pi() - absolute(delta_theta));

        sig_sq = sig_sq + constituent.E() * ( delta_phi * delta_phi + delta_theta * delta_theta);
        total_energy = total_energy + constituent.E();
    }
    sig_sq = sig_sq / total_energy;
    return TMath::Sqrt(sig_sq);
}

double distance(TLorentzVector vec1, TLorentzVector vec2) {
    double delta_phi = vec1.Phi() - vec2.Phi(); delta_phi = Min(absolute(delta_phi), 2 * TMath::Pi() - absolute(delta_phi));
    double delta_theta = vec1.Theta() - vec2.Theta(); delta_theta = Min(absolute(delta_theta), TMath::Pi() - absolute(delta_theta));
    double sq_distance = delta_phi * delta_phi + delta_theta * delta_theta;
    return TMath::Sqrt(sq_distance);
}

double distance(TVector3 vec1, TVector3 vec2) {
    double delta_phi = vec1.Phi() - vec2.Phi(); delta_phi = Min(absolute(delta_phi), 2 * TMath::Pi() - absolute(delta_phi));
    double delta_theta = vec1.Theta() - vec2.Theta(); delta_theta = Min(absolute(delta_theta), TMath::Pi() - absolute(delta_theta));
    double sq_distance = delta_phi * delta_phi + delta_theta * delta_theta;
    return TMath::Sqrt(sq_distance);
}

float avg_depth(std::vector<TLorentzVector> constituents_of_cluster, std::vector<float> depth_of_constituents) {

    double depth = 0;
    double total_E = 0;
    for (int i = 0; i < constituents_of_cluster.size(); i++) {
        depth = depth + constituents_of_cluster.at(i).E() * depth_of_constituents.at(i);
        total_E = total_E + constituents_of_cluster.at(i).E();
    }
    return depth / total_E;
}

float Max(float num1, float num2) {
    if (num1 > num2) return num1;
    else return num2;
}

float Min(float num1, float num2) {
    if (num1 > num2) return num2;
    else return num1;
}

int Del_Phi(int phi1, int phi2) { // phi1 - phi2
    int del_Phi = phi1 - phi2;
    if (absolute(del_Phi) < (N_tow_Phi - absolute(del_Phi))) return del_Phi;
    else {
        if (del_Phi > 0) return del_Phi - N_tow_Phi;
        else return del_Phi + N_tow_Phi;
    }
}

int main(int, char* argv[]) {
    TString filenum = argv[1];
    TString filename = argv[2];

    RootInterface<DRsimInterface::DRsimEventData>* drInterface = new RootInterface<DRsimInterface::DRsimEventData>(std::string(filename) + "_" + std::string(filenum) + ".root");
    drInterface->set("DRsim", "DRsimEventData");

    std::string outfilename = std::string(filename) + "_out_" + std::string(filenum);
    TFile* file = new TFile((outfilename + ".root").c_str(),"recreate");
    TTree* tree = new TTree("data", "data");
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
    float S_sigma_first_cluster = 0;
    float C_sigma_first_cluster = 0;
    float S_sigma_second_cluster = 0;
    float C_sigma_second_cluster = 0;
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
    float S_of_C_first_cluster = 0;
    float S_of_C_second_cluster = 0;
    float E_33_dividedby_E_55_S_first_cluster = 0;
    float E_33_dividedby_E_55_C_first_cluster = 0;
    float E_33_dividedby_E_55_S_second_cluster = 0;
    float E_33_dividedby_E_55_C_second_cluster = 0;
    tree->Branch("num_S_cluster", &num_of_S_cluster);
    tree->Branch("num_C_cluster", &num_of_C_cluster);
    tree->Branch("num_fired_S_fibers",&num_of_fired_S_fibers);
    tree->Branch("num_fired_C_fibers",&num_of_fired_C_fibers);
    tree->Branch("E_S", &total_E_S);
    tree->Branch("E_Scorr", &total_E_Scorr);
    tree->Branch("E_C", &total_E_C);
    tree->Branch("E_DR",&total_E_DR);
    tree->Branch("E_DRcorr",&total_E_DRcorr);
    tree->Branch("E_missing",&total_missing_energy);
    tree->Branch("avg_S_sigma", &average_S_sigma);
    tree->Branch("avg_C_sigma", &average_C_sigma);
    tree->Branch("S_sigma_first_cluster", &S_sigma_first_cluster);
    tree->Branch("C_sigma_first_cluster", &C_sigma_first_cluster);
    tree->Branch("S_sigma_second_cluster", &S_sigma_second_cluster);
    tree->Branch("C_sigma_Second_cluster", &C_sigma_second_cluster);
    tree->Branch("total_signal_max_position_S", &total_signal_peak_position_S);
    tree->Branch("total_signal_max_position_C", &total_signal_peak_position_C);
    tree->Branch("time_of_total_signal_rise_threshold_S", &time_signal_rise_threshold_S);
    tree->Branch("time_of_total_signal_rise_threshold_C", &time_signal_rise_threshold_C);
    tree->Branch("time_of_total_signal_fall_threshold_S", &time_signal_fall_threshold_S);
    tree->Branch("time_of_total_signal_fall_threshold_C", &time_signal_fall_threshold_C);
    tree->Branch("signal_max_position_S_first_cluster", &signal_peak_position_S_first_cluster);
    tree->Branch("signal_max_position_C_first_cluster", &signal_peak_position_C_first_cluster);
    tree->Branch("signal_max_position_S_second_cluster", &signal_peak_position_S_second_cluster);
    tree->Branch("signal_max_position_C_second_cluster", &signal_peak_position_C_second_cluster);
    tree->Branch("rise_time_10to90_S_first_cluster", &rise_time_10to90_S_first_cluster);
    tree->Branch("rise_time_10to90_C_first_cluster", &rise_time_10to90_C_first_cluster);
    tree->Branch("rise_time_10to90_S_second_cluster", &rise_time_10to90_S_second_cluster);
    tree->Branch("rise_time_10to90_C_second_cluster", &rise_time_10to90_C_second_cluster);
    tree->Branch("middle_time_of_10to90_S_first_cluster", &middle_of_10to90_S_first_cluster);
    tree->Branch("middle_time_of_10to90_C_first_cluster", &middle_of_10to90_C_first_cluster);
    tree->Branch("middle_time_of_10to90_S_second_cluster", &middle_of_10to90_S_second_cluster);
    tree->Branch("middle_time_of_10to90_C_second_cluster", &middle_of_10to90_C_second_cluster);
    tree->Branch("E_S_dividedby_E_C_first_cluster", &S_of_C_first_cluster); //
    tree->Branch("E_S_dividedby_E_C_second_cluster", &S_of_C_second_cluster);
    tree->Branch("E_33_dividedby_E_55_S_first_cluster", &E_33_dividedby_E_55_S_first_cluster);
    tree->Branch("E_33_dividedby_E_55_C_first_cluster", &E_33_dividedby_E_55_C_first_cluster);
    tree->Branch("E_33_dividedby_E_55_S_second_cluster", &E_33_dividedby_E_55_S_second_cluster);
    tree->Branch("E_33_dividedby_E_55_C_second_cluster", &E_33_dividedby_E_55_C_second_cluster);

    new GeoSvc({ "./bin/compact/DRcalo.xml" });

    auto m_geoSvc = GeoSvc::GetInstance();
    std::string m_readoutName = "DRcaloSiPMreadout";

    auto lcdd = m_geoSvc->lcdd();
    auto allReadouts = lcdd->readouts();
    if (allReadouts.find(m_readoutName) == allReadouts.end()) {
        throw std::runtime_error("Readout " + m_readoutName + " not found! Please check tool configuration.");
    }
    else {
        std::cout << "Reading EDM from the collection " << m_readoutName << std::endl;
    }

    auto segmentation = dynamic_cast<dd4hep::DDSegmentation::GridDRcalo*>(m_geoSvc->lcdd()->readout(m_readoutName).segmentation().segmentation());

    RecoTower* recoTower = new RecoTower();
    recoTower->readCSV();

    HepMC3::ReaderRootTree reader(std::string(filename) + "_" + std::string(filenum) + ".root");

    unsigned int entries = drInterface->entries();
    while (drInterface->numEvt() < entries) {

        fastjetInterface fjFiber_S;
        fastjetInterface fjFiber_Scorr;
        fastjetInterface fjFiber_C;

        recoTower->getFiber()->clear();

        DRsimInterface::DRsimEventData evt;
        RecoInterface::RecoEventData* recoEvt = new RecoInterface::RecoEventData();
        drInterface->read(evt);

        HepMC3::GenEvent genEvt;
        reader.read_event(genEvt);

        for (auto towerItr = evt.towers.begin(); towerItr != evt.towers.end(); ++towerItr) {
            auto tower = *towerItr;
            recoTower->reconstruct(tower, *recoEvt);

            auto theTower = recoTower->getTower();
            recoEvt->E_C += theTower.E_C;
            recoEvt->E_S += theTower.E_S;
            recoEvt->E_Scorr += theTower.E_Scorr;
            recoEvt->n_C += theTower.n_C;
            recoEvt->n_S += theTower.n_S;
        } // tower loop
        recoEvt->E_DR = RecoTower::E_DR(recoEvt->E_C, recoEvt->E_S);
        recoEvt->E_DRcorr = RecoTower::E_DR(recoEvt->E_C, recoEvt->E_Scorr);

        fjFiber_S.MyrunFastjet(recoTower->getFiber()->getFjInputs_S(), recoTower->getFiber()->getFjInputs_fibernum_S());
        fjFiber_Scorr.MyrunFastjet(recoTower->getFiber()->getFjInputs_Scorr(), recoTower->getFiber()->getFjInputs_fibernum_Scorr());
        fjFiber_C.MyrunFastjet(recoTower->getFiber()->getFjInputs_C(), recoTower->getFiber()->getFjInputs_fibernum_C());

        std::vector<fastjetInterface::fastjetData> jets_S;
        std::vector<fastjetInterface::fastjetData> jets_Scorr;
        std::vector<fastjetInterface::fastjetData> jets_C;
        std::vector<fastjetInterface::fastjetData>* constituents_for_jets_S;
        std::vector<fastjetInterface::fastjetData>* constituents_for_jets_Scorr;
        std::vector<fastjetInterface::fastjetData>* constituents_for_jets_C;
        std::vector<long long int>* fibernum_for_constituents_for_jets_S;
        std::vector<long long int>* fibernum_for_constituents_for_jets_Scorr;
        std::vector<long long int>* fibernum_for_constituents_for_jets_C;
        int num_jets_S;
        int num_jets_Scorr;
        int num_jets_C;
        fjFiber_S.Myread(jets_S, &constituents_for_jets_S, &num_jets_S, &fibernum_for_constituents_for_jets_S);
        fjFiber_Scorr.Myread(jets_Scorr, &constituents_for_jets_Scorr, &num_jets_Scorr, &fibernum_for_constituents_for_jets_Scorr);
        fjFiber_C.Myread(jets_C, &constituents_for_jets_C, &num_jets_C, &fibernum_for_constituents_for_jets_C);

        std::vector<TLorentzVector> S_cluster;
        std::vector<TLorentzVector> Scorr_cluster;
        std::vector<TLorentzVector> C_cluster;
        std::vector<TLorentzVector> constituents_S_cluster[num_jets_S];
        std::vector<TLorentzVector> constituents_Scorr_cluster[num_jets_Scorr];
        std::vector<TLorentzVector> constituents_C_cluster[num_jets_C];

        for (auto cluster : jets_S) {
            TLorentzVector cluster_vec;
            cluster_vec.SetPxPyPzE(cluster.px, cluster.py, cluster.pz, cluster.E);
            S_cluster.push_back(cluster_vec);
        }
        for (auto cluster : jets_Scorr) {
            TLorentzVector cluster_vec;
            cluster_vec.SetPxPyPzE(cluster.px, cluster.py, cluster.pz, cluster.E);
            Scorr_cluster.push_back(cluster_vec);
        }
        for (auto cluster : jets_C) {
            TLorentzVector cluster_vec;
            cluster_vec.SetPxPyPzE(cluster.px, cluster.py, cluster.pz, cluster.E);
            C_cluster.push_back(cluster_vec);
        }

        for (int i = 0; i < num_jets_S; i++) {
            for (auto constituent : constituents_for_jets_S[i]) {
                TLorentzVector constituent_vec;
                constituent_vec.SetPxPyPzE(constituent.px, constituent.py, constituent.pz, constituent.E);
                constituents_S_cluster[i].push_back(constituent_vec);
            }
        }

        for (int i = 0; i < num_jets_Scorr; i++) {
            for (auto constituent : constituents_for_jets_Scorr[i]) {
                TLorentzVector constituent_vec;
                constituent_vec.SetPxPyPzE(constituent.px, constituent.py, constituent.pz, constituent.E);
                constituents_Scorr_cluster[i].push_back(constituent_vec);
            }
        }

        for (int i = 0; i < num_jets_C; i++) {
            for (auto constituent : constituents_for_jets_C[i]) {
                TLorentzVector constituent_vec;
                constituent_vec.SetPxPyPzE(constituent.px, constituent.py, constituent.pz, constituent.E);
                constituents_C_cluster[i].push_back(constituent_vec);
            }
        }

        // apply cut
        std::vector<int> entry_jets_S_after_cut;
        std::vector<int> entry_jets_Scorr_after_cut;
        std::vector<int> entry_jets_C_after_cut;

        std::vector<TLorentzVector> S_cluster_after_cut;
        std::vector<TLorentzVector> Scorr_cluster_after_cut;
        std::vector<TLorentzVector> C_cluster_after_cut;

        for (int i = 0; i < S_cluster.size(); i++) {
            if (S_cluster.at(i).E() > Filter) {
                entry_jets_S_after_cut.push_back(i);
                TLorentzVector temp_vec;
                temp_vec = S_cluster.at(i);
                S_cluster_after_cut.push_back(temp_vec);
            }
        }

        for (int i = 0; i < Scorr_cluster.size(); i++) {
            if (Scorr_cluster.at(i).E() > Filter) {
                entry_jets_Scorr_after_cut.push_back(i);
                TLorentzVector temp_vec;
                temp_vec = Scorr_cluster.at(i);
                Scorr_cluster_after_cut.push_back(temp_vec);
            }
        }

        for (int i = 0; i < C_cluster.size(); i++) {
            if (C_cluster.at(i).E() > Filter) {
                entry_jets_C_after_cut.push_back(i);
                TLorentzVector temp_vec;
                temp_vec = C_cluster.at(i);
                C_cluster_after_cut.push_back(temp_vec);
            }
        }

        std::vector<TLorentzVector> constituents_S_cluster_after_cut[entry_jets_S_after_cut.size()];
        std::vector<TLorentzVector> constituents_Scorr_cluster_after_cut[entry_jets_Scorr_after_cut.size()];
        std::vector<TLorentzVector> constituents_C_cluster_after_cut[entry_jets_C_after_cut.size()];
        std::vector<long long int> fibernum_for_constituents_for_jets_S_after_cut[entry_jets_S_after_cut.size()];
        std::vector<long long int> fibernum_for_constituents_for_jets_Scorr_after_cut[entry_jets_Scorr_after_cut.size()];
        std::vector<long long int> fibernum_for_constituents_for_jets_C_after_cut[entry_jets_C_after_cut.size()];

        {
            int index = 0;
            for (auto elem : entry_jets_S_after_cut) {
                constituents_S_cluster_after_cut[index] = constituents_S_cluster[elem];
                index++;
            }
        }

        {
            int index = 0;
            for (auto elem : entry_jets_Scorr_after_cut) {
                constituents_Scorr_cluster_after_cut[index] = constituents_Scorr_cluster[elem];
                index++;
            }
        }

        {
            int index = 0;
            for (auto elem : entry_jets_C_after_cut) {
                constituents_C_cluster_after_cut[index] = constituents_C_cluster[elem];
                index++;
            }
        }

        {
            int index = 0;
            for (auto elem : entry_jets_S_after_cut) {
                fibernum_for_constituents_for_jets_S_after_cut[index] = fibernum_for_constituents_for_jets_S[elem];
                index++;
            }
        }

        {
            int index = 0;
            for (auto elem : entry_jets_Scorr_after_cut) {
                fibernum_for_constituents_for_jets_Scorr_after_cut[index] = fibernum_for_constituents_for_jets_Scorr[elem];
                index++;
            }
        }

        {
            int index = 0;
            for (auto elem : entry_jets_C_after_cut) {
                fibernum_for_constituents_for_jets_C_after_cut[index] = fibernum_for_constituents_for_jets_C[elem];
                index++;
            }
        }

        // clustering is conducted. cut is 1 GeV for scin and cheren
        // reject events if the number of clusters is smaller than 2, at scin and cheren
        // reject events if position of clusters between scin and cheren is not matched
        if (entry_jets_S_after_cut.size() < 2 || entry_jets_C_after_cut.size() < 2) continue;

        std::map<int, int> cluster_pair; // index of scin cluster, index of cherenkov cluster
        std::vector<int> index_of_C_already_selected; // list of index of cherenkov cluster, which is already selected
        for (unsigned long int i = 0; i < entry_jets_S_after_cut.size(); i++) {

            double min_distance = std::numeric_limits<double>::max();
            int index_C = -1;

            for (unsigned long int j = 0; j < entry_jets_C_after_cut.size(); j++) {
                
                auto itr = find(index_of_C_already_selected.begin(), index_of_C_already_selected.end(), j);
                if (itr != index_of_C_already_selected.end()) continue;

                if (distance(S_cluster_after_cut.at(i), C_cluster_after_cut.at(j)) < min_distance) {
                    min_distance = distance(S_cluster_after_cut.at(i), C_cluster_after_cut.at(j));
                    index_C = j;
                }

            }

            if (min_distance > max_dis) index_C = -1;

            cluster_pair.insert(std::make_pair(i, index_C));
            if (index_C != -1) index_of_C_already_selected.push_back(index_C);
        }
        if (cluster_pair[0] == -1 || cluster_pair[1] == -1) continue;
        
        double avg_S_sigmas = 0;
        double S_sigmas[entry_jets_S_after_cut.size()];
        for (int i = 0; i < entry_jets_S_after_cut.size(); i++) {
            avg_S_sigmas = avg_S_sigmas + S_cluster_after_cut.at(i).E() * sigma(S_cluster_after_cut.at(i), constituents_S_cluster_after_cut[i]);
            S_sigmas[i] = sigma(S_cluster_after_cut.at(i), constituents_S_cluster_after_cut[i]);
        }
        {
            double temp_total_S = 0;
                for(int i = 0; i < entry_jets_S_after_cut.size(); i++){
                    temp_total_S = temp_total_S + S_cluster_after_cut.at(i).E();
                }
                if (entry_jets_S_after_cut.size() == 0 || temp_total_S == 0) {
                    avg_S_sigmas = 0;
                }
                else avg_S_sigmas = avg_S_sigmas / temp_total_S;
        }

        double avg_C_sigmas = 0;
        double C_sigmas[entry_jets_C_after_cut.size()];
        for (int i = 0; i < entry_jets_C_after_cut.size(); i++) {
            avg_C_sigmas = avg_C_sigmas + C_cluster_after_cut.at(i).E() * sigma(C_cluster_after_cut.at(i), constituents_C_cluster_after_cut[i]);
            C_sigmas[i] = sigma(C_cluster_after_cut.at(i), constituents_C_cluster_after_cut[i]);
        }
        {
            double temp_total_C = 0;
            for (int i = 0; i < entry_jets_C_after_cut.size(); i++) {
                temp_total_C = temp_total_C + C_cluster_after_cut.at(i).E();
            }
            if (entry_jets_C_after_cut.size() == 0 || temp_total_C == 0) {
                avg_C_sigmas = 0;
            }
            else avg_C_sigmas = avg_C_sigmas / temp_total_C;
        }

        double initial_total_E = 0;
        for (auto ptc : genEvt.particles()) {
                if(ptc->parents().size() == 0) initial_total_E = initial_total_E + ptc->momentum().e();
        }
        if (initial_total_E < 91.1 || initial_total_E > 91.3) { printf("unexpected initial energy.\n"); std::abort(); }

        TH1F* tT_C = new TH1F("time_C_total", "total Cerenkov time;ns;p.e.", 125, 10., 60.);
        tT_C->Sumw2(); tT_C->SetLineColor(kBlue); tT_C->SetLineWidth(2);
        TH1F* tT_S = new TH1F("time_S_total", "total Scint time;ns;p.e.", 125, 10., 60.);
        tT_S->Sumw2(); tT_S->SetLineColor(kRed); tT_S->SetLineWidth(2);
        TH1F* tT_temp_C = new TH1F("tmax_C_total", "total Cerenkov time;ns;p.e.", 550, 10., 65.);
        TH1F* tT_temp_S = new TH1F("tmax_S_total", "total Scint time;ns;p.e.", 550, 10., 65.);

        // first cluster: the cluster whose scin energy is highest
        TH1F* tT_temp_C_first_cluster = new TH1F("tmax_C_1st_cluster", "Cerenkov time of first energetic cluster;ns;p.e.", 550, 10., 65.);
        TH1F* tT_temp_S_first_cluster = new TH1F("tmax_S_1st_cluster", "Scint time of first energetic cluster;ns;p.e.", 550, 10., 65.);
        TH1F* tT_temp_C_second_cluster = new TH1F("tmax_C_2nd_cluster", "Cerenkov time of second energetic cluster;ns;p.e.", 550, 10., 65.);
        TH1F* tT_temp_S_second_cluster = new TH1F("tmax_S_2nd_cluster", "Scint time of second energetic cluster;ns;p.e.", 550, 10., 65.);

        for (auto tower = evt.towers.begin(); tower != evt.towers.end(); ++tower) {
            for (auto sipm = tower->SiPMs.begin(); sipm != tower->SiPMs.end(); ++sipm) {

                auto position = segmentation->towerposition_from_cell_ID(sipm->SiPMnum); // cm
                TVector3 temp_vec; temp_vec.SetXYZ(position.x(), position.y(), position.z());
                double towerH = segmentation->towerheight_from_cell_ID(sipm->SiPMnum); // cm

                float distance = (float)((temp_vec.Mag() - towerH / 2.0) * 0.01); // m
                float offset = (distance - 1.8) / 0.3; // ns

                // exception
                if (distance > 4.2 || distance < 1.75) {
                    printf("inappropriate distance from the origin to a tower plane\n");
                    abort();
                }

                if (segmentation->IsCerenkov(sipm->SiPMnum)) {
                    for (const auto timepair : sipm->timeStruct) {
                        tT_C->Fill(timepair.first.first + 0.05 - offset, timepair.second);
                        tT_temp_C->Fill(timepair.first.first + 0.05 - offset, timepair.second);
                    }
                }
                else {
                    for (const auto timepair : sipm->timeStruct) {
                        tT_S->Fill(timepair.first.first + 0.05 - offset, timepair.second);
                        tT_temp_S->Fill(timepair.first.first + 0.05 - offset, timepair.second);
                    }
                }

                for (int i = 0; i < entry_jets_S_after_cut.size(); i++) {
                    auto it = find(fibernum_for_constituents_for_jets_S_after_cut[i].begin(), fibernum_for_constituents_for_jets_S_after_cut[i].end(), sipm->SiPMnum);
                    if (it != fibernum_for_constituents_for_jets_S_after_cut[i].end()) {
                        if (segmentation->IsCerenkov(sipm->SiPMnum)) {
                            printf("inappropriate fiber num\n");
                            std::abort();
                        }
                        else {
                            if (i == 0) {
                                for (const auto timepair : sipm->timeStruct) {
                                    tT_temp_S_first_cluster->Fill(timepair.first.first + 0.05 - offset, timepair.second);
                                }
                            }
                            else if (i == 1) {
                                for (const auto timepair : sipm->timeStruct) {
                                    tT_temp_S_second_cluster->Fill(timepair.first.first + 0.05 - offset, timepair.second);
                                }
                            }
                        }
                    }
                }

                for (int i = 0; i < entry_jets_C_after_cut.size(); i++) {
                    auto it = find(fibernum_for_constituents_for_jets_C_after_cut[i].begin(), fibernum_for_constituents_for_jets_C_after_cut[i].end(), sipm->SiPMnum);
                    if (it != fibernum_for_constituents_for_jets_C_after_cut[i].end()) {
                        if (segmentation->IsCerenkov(sipm->SiPMnum)) {
                            if (i == cluster_pair[0]) {
                                for (const auto timepair : sipm->timeStruct) {
                                    tT_temp_C_first_cluster->Fill(timepair.first.first + 0.05 - offset, timepair.second);
                                }
                            }
                            else if (i == cluster_pair[1]) {
                                for (const auto timepair : sipm->timeStruct) {
                                    tT_temp_C_second_cluster->Fill(timepair.first.first + 0.05 - offset, timepair.second);
                                }
                            }
                        }
                        else {
                            printf("inappropriate fiber num\n");
                            std::abort();
                        }
                    }
                }

            }
        }

        float T_max_C = tT_temp_C->GetBinCenter(tT_temp_C->GetMaximumBin());
        float T_max_S = tT_temp_S->GetBinCenter(tT_temp_S->GetMaximumBin());
        float T_max_C_first = tT_temp_C_first_cluster->GetBinCenter(tT_temp_C_first_cluster->GetMaximumBin());
        float T_max_S_first = tT_temp_S_first_cluster->GetBinCenter(tT_temp_S_first_cluster->GetMaximumBin());
        float T_max_C_second = tT_temp_C_second_cluster->GetBinCenter(tT_temp_C_second_cluster->GetMaximumBin());
        float T_max_S_second = tT_temp_S_second_cluster->GetBinCenter(tT_temp_S_second_cluster->GetMaximumBin());

        float T_first_above_half_maximum_C = tT_temp_C->GetBinCenter(tT_temp_C->FindFirstBinAbove(tT_temp_C->GetMaximum() / 2.0));
        float T_last_above_half_maximum_C = tT_temp_C->GetBinCenter(tT_temp_C->FindLastBinAbove(tT_temp_C->GetMaximum() / 2.0));
        float T_first_above_half_maximum_S = tT_temp_S->GetBinCenter(tT_temp_S->FindFirstBinAbove(tT_temp_S->GetMaximum() / 2.0));
        float T_last_above_half_maximum_S = tT_temp_S->GetBinCenter(tT_temp_S->FindLastBinAbove(tT_temp_S->GetMaximum() / 2.0));

        float T_10to90_C_first = tT_temp_C_first_cluster->GetBinCenter(tT_temp_C_first_cluster->FindFirstBinAbove(tT_temp_C_first_cluster->GetMaximum() * 0.9)) - tT_temp_C_first_cluster->GetBinCenter(tT_temp_C_first_cluster->FindFirstBinAbove(tT_temp_C_first_cluster->GetMaximum() * 0.1));
        float T_10to90_S_first = tT_temp_S_first_cluster->GetBinCenter(tT_temp_S_first_cluster->FindFirstBinAbove(tT_temp_S_first_cluster->GetMaximum() * 0.9)) - tT_temp_S_first_cluster->GetBinCenter(tT_temp_S_first_cluster->FindFirstBinAbove(tT_temp_S_first_cluster->GetMaximum() * 0.1));
        float T_10to90_C_second = tT_temp_C_second_cluster->GetBinCenter(tT_temp_C_second_cluster->FindFirstBinAbove(tT_temp_C_second_cluster->GetMaximum() * 0.9)) - tT_temp_C_second_cluster->GetBinCenter(tT_temp_C_second_cluster->FindFirstBinAbove(tT_temp_C_second_cluster->GetMaximum() * 0.1));
        float T_10to90_S_second = tT_temp_S_second_cluster->GetBinCenter(tT_temp_S_second_cluster->FindFirstBinAbove(tT_temp_S_second_cluster->GetMaximum() * 0.9)) - tT_temp_S_second_cluster->GetBinCenter(tT_temp_S_second_cluster->FindFirstBinAbove(tT_temp_S_second_cluster->GetMaximum() * 0.1));

        float T_middle_of_10to90_C_first = tT_temp_C_first_cluster->GetBinCenter(tT_temp_C_first_cluster->FindFirstBinAbove(tT_temp_C_first_cluster->GetMaximum() * 0.5));
        float T_middle_of_10to90_S_first = tT_temp_S_first_cluster->GetBinCenter(tT_temp_S_first_cluster->FindFirstBinAbove(tT_temp_S_first_cluster->GetMaximum() * 0.5));
        float T_middle_of_10to90_C_second = tT_temp_C_second_cluster->GetBinCenter(tT_temp_C_second_cluster->FindFirstBinAbove(tT_temp_C_second_cluster->GetMaximum() * 0.5));
        float T_middle_of_10to90_S_second = tT_temp_S_second_cluster->GetBinCenter(tT_temp_S_second_cluster->FindFirstBinAbove(tT_temp_S_second_cluster->GetMaximum() * 0.5));

        float E_S_33_first = 0;
        float E_C_33_first = 0;
        float E_S_55_first = 0;
        float E_C_55_first = 0;
        float E_S_33_second = 0;
        float E_C_33_second = 0;
        float E_S_55_second = 0;
        float E_C_55_second = 0;

        // get the eta/phi number of towers which include scint clusters
        int Eta_tower_first = std::numeric_limits<int>::max(); // the eta number of the tower which include first cluster
        int Phi_tower_first = std::numeric_limits<int>::max();
        int Eta_tower_second = std::numeric_limits<int>::max(); // the eta number of the tower which include second cluster
        int Phi_tower_second = std::numeric_limits<int>::max();
        {
            TLorentzVector temp_vec_S = S_cluster_after_cut.at(0);
            TLorentzVector temp_vec_C = C_cluster_after_cut.at(cluster_pair[0]);
            double min_distance = std::numeric_limits<double>::max();

            for (auto tower = recoEvt->towers.begin(); tower != recoEvt->towers.end(); ++tower) {
                for (auto fiber = tower->fibers.begin(); fiber != tower->fibers.end(); ++fiber) {
                    auto global = segmentation->towerposition_from_cell_ID(fiber->fiberNum);

                    TVector3 vec(global.x(), global.y(), global.z());
                    TVector3 p = fiber->Ecorr * vec.Unit();
                    TLorentzVector temp_vec; temp_vec.SetPxPyPzE(p.x(), p.y(), p.z(), fiber->Ecorr);

                    if (min_distance > distance(temp_vec, temp_vec_S)) {
                        min_distance = distance(temp_vec, temp_vec_S);
                        Eta_tower_first = segmentation->numEta(fiber->fiberNum);
                        Phi_tower_first = segmentation->numPhi(fiber->fiberNum);
                    }
                    else break;
                }
            }
        }
        {
            TLorentzVector temp_vec_S = S_cluster_after_cut.at(1);
            TLorentzVector temp_vec_C = C_cluster_after_cut.at(cluster_pair[1]);
            double min_distance = std::numeric_limits<double>::max();

            for (auto tower = recoEvt->towers.begin(); tower != recoEvt->towers.end(); ++tower) {
                for (auto fiber = tower->fibers.begin(); fiber != tower->fibers.end(); ++fiber) {
                    auto global = segmentation->towerposition_from_cell_ID(fiber->fiberNum);

                    TVector3 vec(global.x(), global.y(), global.z());
                    TVector3 p = fiber->Ecorr * vec.Unit();
                    TLorentzVector temp_vec; temp_vec.SetPxPyPzE(p.x(), p.y(), p.z(), fiber->Ecorr);

                    if (min_distance > distance(temp_vec, temp_vec_S)) {
                        min_distance = distance(temp_vec, temp_vec_S);
                        Eta_tower_second = segmentation->numEta(fiber->fiberNum);
                        Phi_tower_second = segmentation->numPhi(fiber->fiberNum);
                    }
                    else break;
                }
            }
        }
        // exception
        if (Eta_tower_first == std::numeric_limits<int>::max()) std::abort();
        if (Phi_tower_first == std::numeric_limits<int>::max()) std::abort();
        if (Eta_tower_second == std::numeric_limits<int>::max()) std::abort();
        if (Phi_tower_second == std::numeric_limits<int>::max()) std::abort();
        if (Eta_tower_first == Eta_tower_second && Phi_tower_first == Phi_tower_second) std::abort();

        for (auto tower = recoEvt->towers.begin(); tower != recoEvt->towers.end(); ++tower) {
            for (auto fiber = tower->fibers.begin(); fiber != tower->fibers.end(); ++fiber) {

                int current_Eta = segmentation->numEta(fiber->fiberNum);
                int current_Phi = segmentation->numPhi(fiber->fiberNum);
                int relative_Eta_wrt_first_cluster = current_Eta - Eta_tower_first;
                int relative_Phi_wrt_first_cluster = Del_Phi(current_Phi, Phi_tower_first);
                int relative_Eta_wrt_second_cluster = current_Eta - Eta_tower_second;
                int relative_Phi_wrt_second_cluster = Del_Phi(current_Phi, Phi_tower_second);

                if ((-1) * 1 <= relative_Eta_wrt_first_cluster && relative_Eta_wrt_first_cluster <= 1 && (-1) * 1 <= relative_Phi_wrt_first_cluster && relative_Phi_wrt_first_cluster <= 1) {
                    if (segmentation->IsCerenkov(fiber->fiberNum)) { E_C_33_first = E_C_33_first + fiber->Ecorr; E_C_55_first = E_C_55_first + fiber->Ecorr; }
                    else { E_S_33_first = E_S_33_first + fiber->Ecorr; E_S_55_first = E_S_55_first + fiber->Ecorr; }
                } // 3x3 first
                else if ((-1) * 1 <= relative_Eta_wrt_second_cluster && relative_Eta_wrt_second_cluster <= 1 && (-1) * 1 <= relative_Phi_wrt_second_cluster && relative_Phi_wrt_second_cluster <= 1) {
                    if (segmentation->IsCerenkov(fiber->fiberNum)) { E_C_33_second = E_C_33_second + fiber->Ecorr; E_C_55_second = E_C_55_second + fiber->Ecorr; }
                    else { E_S_33_second = E_S_33_second + fiber->Ecorr; E_S_55_second = E_S_55_second + fiber->Ecorr; }
                } // 3x3 second
                else if ((-1) * 2 <= relative_Eta_wrt_first_cluster && relative_Eta_wrt_first_cluster <= 2 && (-1) * 2 <= relative_Phi_wrt_first_cluster && relative_Phi_wrt_first_cluster <= 2) {
                    if (segmentation->IsCerenkov(fiber->fiberNum)) E_C_55_first = E_C_55_first + fiber->Ecorr;
                    else E_S_55_first = E_S_55_first + fiber->Ecorr;
                } // 5x5 first
                else if ((-1) * 2 <= relative_Eta_wrt_second_cluster && relative_Eta_wrt_second_cluster <= 2 && (-1) * 2 <= relative_Phi_wrt_second_cluster && relative_Phi_wrt_second_cluster <= 2) {
                    if (segmentation->IsCerenkov(fiber->fiberNum)) E_C_55_second = E_C_55_second + fiber->Ecorr;
                    else E_S_55_second = E_S_55_second + fiber->Ecorr;
                } // 5x5 second
                else break;
            }
        }
        /*
        if (drInterface->numEvt() < 101) {
            TCanvas* c = new TCanvas("c", "", 716, 600);
            c->SetRightMargin(0.15);

            tT_S->Draw("Hist"); c->SaveAs(("./time_images/time_dis_S_" + std::to_string(drInterface->numEvt()) + ".png").c_str());
            tT_C->Draw("Hist"); c->SaveAs(("./time_images/time_dis_C_" + std::to_string(drInterface->numEvt()) + ".png").c_str());
            tT_temp_C->Draw("Hist"); c->SaveAs(("./time_images/temp_dis_C_" + std::to_string(drInterface->numEvt()) + ".png").c_str());
            tT_temp_S->Draw("Hist"); c->SaveAs(("./time_images/temp_dis_S_" + std::to_string(drInterface->numEvt()) + ".png").c_str());
            tT_temp_C_first_cluster->Draw("Hist"); c->SaveAs(("./time_images/temp_dis_C_first_cluster" + std::to_string(drInterface->numEvt()) + ".png").c_str());
            tT_temp_S_first_cluster->Draw("Hist"); c->SaveAs(("./time_images/temp_dis_S_first_cluster" + std::to_string(drInterface->numEvt()) + ".png").c_str());
            tT_temp_C_second_cluster->Draw("Hist"); c->SaveAs(("./time_images/temp_dis_C_second_cluster" + std::to_string(drInterface->numEvt()) + ".png").c_str());
            tT_temp_S_second_cluster->Draw("Hist"); c->SaveAs(("./time_images/temp_dis_S_second_cluster" + std::to_string(drInterface->numEvt()) + ".png").c_str());

            TH2F* detected_jet_scin = new TH2F("p.e.S", ";#theta;#phi; # of p.e. at Scint", 60, -0.1, 3.2, 120, -3.2, 3.2);
            TH2F* detected_jet_ceren = new TH2F("p.e.C", ";#theta;#phi; # of p.e. at Ceren", 60, -0.1, 3.2, 120, -3.2, 3.2);
            for (auto tower = evt.towers.begin(); tower != evt.towers.end(); ++tower) {
                for (auto sipm = tower->SiPMs.begin(); sipm != tower->SiPMs.end(); ++sipm) {

                    for (int i = 0; i < entry_jets_S_after_cut.size(); i++) {
                        auto it = find(fibernum_for_constituents_for_jets_S_after_cut[i].begin(), fibernum_for_constituents_for_jets_S_after_cut[i].end(), sipm->SiPMnum);
                        if (it != fibernum_for_constituents_for_jets_S_after_cut[i].end()) {
                            if (segmentation->IsCerenkov(sipm->SiPMnum)) {
                                printf("inappropriate fiber num\n");
                                std::abort();
                            }
                            else {
                                auto position = segmentation->towerposition_from_cell_ID(sipm->SiPMnum); // cm
                                TVector3 temp_vec; temp_vec.SetXYZ(position.x(), position.y(), position.z());
                                TLorentzVector tlv; tlv.SetPxPyPzE(temp_vec.x(), temp_vec.y(), temp_vec.z(), temp_vec.Mag());
                                detected_jet_scin->Fill(tlv.Theta(), tlv.Phi(), sipm->count);
                            }
                        }
                    }

                    for (int i = 0; i < entry_jets_C_after_cut.size(); i++) {
                        auto it = find(fibernum_for_constituents_for_jets_C_after_cut[i].begin(), fibernum_for_constituents_for_jets_C_after_cut[i].end(), sipm->SiPMnum);
                        if (it != fibernum_for_constituents_for_jets_C_after_cut[i].end()) {
                            if (segmentation->IsCerenkov(sipm->SiPMnum)) {
                                auto position = segmentation->towerposition_from_cell_ID(sipm->SiPMnum); // cm
                                TVector3 temp_vec; temp_vec.SetXYZ(position.x(), position.y(), position.z());
                                TLorentzVector tlv; tlv.SetPxPyPzE(temp_vec.x(), temp_vec.y(), temp_vec.z(), temp_vec.Mag());
                                detected_jet_ceren->Fill(tlv.Theta(), tlv.Phi(), sipm->count);
                            }
                            else {
                                printf("inappropriate fiber num\n");
                                std::abort();
                            }
                        }
                    }

                }
            }
            detected_jet_scin->Draw("COLZ"); c->SaveAs(("./time_images/Hit_distribution_S_" + std::to_string(drInterface->numEvt()) + ".png").c_str());
            detected_jet_ceren->Draw("COLZ"); c->SaveAs(("./time_images/Hit_distribution_C_" + std::to_string(drInterface->numEvt()) + ".png").c_str());

            delete detected_jet_scin;
            delete detected_jet_ceren;
            delete c;
        }
        */
        delete tT_C;
        delete tT_S;
        delete tT_temp_C;
        delete tT_temp_S;

        delete tT_temp_C_first_cluster;
        delete tT_temp_S_first_cluster;
        delete tT_temp_C_second_cluster;
        delete tT_temp_S_second_cluster;
        /*
        if (drInterface->numEvt() < 101) {

            TH2F* detected_jet_scin = new TH2F("E_S", ";#theta;#phi;E_S [GeV]", 60, -0.1, 3.2, 120, -3.2, 3.2);
            TH2F* detected_jet_scincorr = new TH2F("E_Scorr", ";#theta;#phi;E_Scorr [GeV]", 60, -0.1, 3.2, 120, -3.2, 3.2);
            TH2F* detected_jet_ceren = new TH2F("E_C", ";#theta;#phi;E_C [GeV]", 60, -0.1, 3.2, 120, -3.2, 3.2);

            TGraph* S_cluster_graph;
            TGraph* Scorr_cluster_graph;
            TGraph* C_cluster_graph;

            for (auto tower = recoEvt->towers.begin(); tower != recoEvt->towers.end(); ++tower) {
                for (auto fiber = tower->fibers.begin(); fiber != tower->fibers.end(); ++fiber) {
                    auto global = segmentation->position(fiber->fiberNum);

                    TVector3 vec(global.x(), global.y(), global.z());
                    TVector3 p = fiber->E * vec.Unit();

                    if (segmentation->IsCerenkov(fiber->fiberNum)) {
                        detected_jet_ceren->Fill(p.Theta(), p.Phi(), fiber->E);
                    }
                    else {
                        detected_jet_scin->Fill(p.Theta(), p.Phi(), fiber->E);
                        detected_jet_scincorr->Fill(p.Theta(), p.Phi(), fiber->Ecorr);
                    }
                }
            }

            {
                double* temp_x;
                double* temp_y;
                temp_x = new double[S_cluster_after_cut.size()];
                temp_y = new double[S_cluster_after_cut.size()];
                for (long unsigned int i = 0; i < S_cluster_after_cut.size(); i++) {
                    temp_x[i] = S_cluster_after_cut[i].Theta();
                    temp_y[i] = S_cluster_after_cut[i].Phi();
                }
                S_cluster_graph = new TGraph(S_cluster_after_cut.size(), temp_x, temp_y);
                delete[] temp_x;
                delete[] temp_y;
            }

            {
                double* temp_x;
                double* temp_y;
                temp_x = new double[Scorr_cluster_after_cut.size()];
                temp_y = new double[Scorr_cluster_after_cut.size()];
                for (long unsigned int i = 0; i < Scorr_cluster_after_cut.size(); i++) {
                    temp_x[i] = Scorr_cluster_after_cut[i].Theta();
                    temp_y[i] = Scorr_cluster_after_cut[i].Phi();
                }
                Scorr_cluster_graph = new TGraph(Scorr_cluster_after_cut.size(), temp_x, temp_y);
                delete[] temp_x;
                delete[] temp_y;
            }

            {
                double* temp_x;
                double* temp_y;
                temp_x = new double[C_cluster_after_cut.size()];
                temp_y = new double[C_cluster_after_cut.size()];
                for (long unsigned int i = 0; i < C_cluster_after_cut.size(); i++) {
                    temp_x[i] = C_cluster_after_cut[i].Theta();
                    temp_y[i] = C_cluster_after_cut[i].Phi();
                }
                C_cluster_graph = new TGraph(C_cluster_after_cut.size(), temp_x, temp_y);
                delete[] temp_x;
                delete[] temp_y;
            }

            TCanvas* c = new TCanvas("c", "", 716, 600);
            c->SetRightMargin(0.15);

            detected_jet_scin->SetStats(FALSE);
            detected_jet_ceren->SetStats(FALSE);
            detected_jet_scincorr->SetStats(FALSE);

            detected_jet_scin->Draw("COLZ");
            S_cluster_graph->SetMarkerColor(2); S_cluster_graph->SetMarkerStyle(26); S_cluster_graph->SetMarkerSize(2); S_cluster_graph->Draw("SAMEP");
            c->SaveAs(("./cluster_images/energy_dis_S" + std::to_string(drInterface->numEvt()) + ".png").c_str());

            detected_jet_scincorr->Draw("COLZ");
            Scorr_cluster_graph->SetMarkerColor(2); Scorr_cluster_graph->SetMarkerStyle(26); Scorr_cluster_graph->SetMarkerSize(2); Scorr_cluster_graph->Draw("SAMEP");
            c->SaveAs(("./cluster_images/energy_dis_Scorr" + std::to_string(drInterface->numEvt()) + ".png").c_str());

            detected_jet_ceren->Draw("COLZ");
            C_cluster_graph->SetMarkerColor(2); C_cluster_graph->SetMarkerStyle(26); C_cluster_graph->SetMarkerSize(2); C_cluster_graph->Draw("SAMEP");
            c->SaveAs(("./cluster_images/energy_dis_C" + std::to_string(drInterface->numEvt()) + ".png").c_str());

            delete c;
            delete S_cluster_graph;
            delete Scorr_cluster_graph;
            delete C_cluster_graph;
            delete detected_jet_scin;
            delete detected_jet_ceren;
            delete detected_jet_scincorr;

        } // 100 loop
        */
        num_of_S_cluster = float(entry_jets_S_after_cut.size());
        num_of_C_cluster = float(entry_jets_C_after_cut.size());
        num_of_fired_S_fibers = float(recoTower->getFiber()->getFjInputs_S().size());
        num_of_fired_C_fibers = float(recoTower->getFiber()->getFjInputs_C().size());
        total_E_S = float(recoEvt->E_S);
        total_E_Scorr = float(recoEvt->E_Scorr);
        total_E_C = float(recoEvt->E_C);
        total_E_DR = float(recoEvt->E_DR);
        total_E_DRcorr = float(recoEvt->E_DRcorr);
        total_missing_energy = float(initial_total_E - total_E_DRcorr);
        average_S_sigma = float(avg_S_sigmas);
        average_C_sigma = float(avg_C_sigmas);
        S_sigma_first_cluster = float(S_sigmas[0]);
        C_sigma_first_cluster = float(C_sigmas[cluster_pair[0]]);
        S_sigma_second_cluster = float(S_sigmas[1]);
        C_sigma_second_cluster = float(C_sigmas[cluster_pair[1]]);
        total_signal_peak_position_S = T_max_S;
        total_signal_peak_position_C = T_max_C;
        time_signal_rise_threshold_S = T_first_above_half_maximum_S;
        time_signal_rise_threshold_C = T_first_above_half_maximum_C;
        time_signal_fall_threshold_S = T_last_above_half_maximum_S;
        time_signal_fall_threshold_C = T_last_above_half_maximum_C;
        signal_peak_position_S_first_cluster = T_max_S_first;
        signal_peak_position_C_first_cluster = T_max_C_first;
        signal_peak_position_S_second_cluster = T_max_S_second;
        signal_peak_position_C_second_cluster = T_max_C_second;
        rise_time_10to90_S_first_cluster = T_10to90_S_first;
        rise_time_10to90_C_first_cluster = T_10to90_C_first;
        rise_time_10to90_S_second_cluster = T_10to90_S_second;
        rise_time_10to90_C_second_cluster = T_10to90_C_second;
        middle_of_10to90_S_first_cluster = T_middle_of_10to90_S_first;
        middle_of_10to90_C_first_cluster = T_middle_of_10to90_C_first;
        middle_of_10to90_S_second_cluster = T_middle_of_10to90_S_second;
        middle_of_10to90_C_second_cluster = T_middle_of_10to90_C_second;
        S_of_C_first_cluster = S_cluster_after_cut.at(0).E() / C_cluster_after_cut.at(cluster_pair[0]).E();
        S_of_C_second_cluster = S_cluster_after_cut.at(1).E() / C_cluster_after_cut.at(cluster_pair[1]).E();
        E_33_dividedby_E_55_S_first_cluster = E_S_33_first / E_S_55_first;
        E_33_dividedby_E_55_C_first_cluster = E_C_33_first / E_C_55_first;
        E_33_dividedby_E_55_S_second_cluster = E_S_33_second / E_S_55_second;
        E_33_dividedby_E_55_C_second_cluster = E_C_33_second / E_C_55_second;

        tree->Fill();

        delete recoEvt;
    } // event loop

    file->cd(); tree->Write();
    file->Close();
}
