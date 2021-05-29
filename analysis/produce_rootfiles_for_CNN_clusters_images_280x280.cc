// ./bin/Reco is not required to run this code
# define Filter 1.0 // GeV
# define max_dis 0.8
# define N_fib 56 // the number of fibers along to the edge of a tower
# define N_tow 2 // we collect the information from (2N+1) x (2N+1) towers
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

int absolute(int num) {
    if (num >= 0) return num;
    else return (-1) * num;
}

double Min(double num1, double num2) {
    if (num1 > num2) return num2;
    else return num1;
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

    std::string outfilename = std::string(filename) + "_CNN_out_" + std::string(filenum);
    TFile* file = new TFile((outfilename + ".root").c_str(), "recreate");
    TTree* tree = new TTree("data", "data");

    float Energy_S_first[(2 * N_tow + 1) * N_fib][(2 * N_tow + 1) * N_fib];
    float Energy_C_first[(2 * N_tow + 1) * N_fib][(2 * N_tow + 1) * N_fib];
    float Energy_S_second[(2 * N_tow + 1) * N_fib][(2 * N_tow + 1) * N_fib];
    float Energy_C_second[(2 * N_tow + 1) * N_fib][(2 * N_tow + 1) * N_fib];

    if (N_tow != 2) std::abort();
    else if (N_fib != 56) std::abort();
    else {
        tree->Branch("Energy_S_first", &Energy_S_first, "Energy_S_first[280][280]/F");
        tree->Branch("Energy_C_first", &Energy_C_first, "Energy_C_first[280][280]/F");
        tree->Branch("Energy_S_second", &Energy_S_second, "Energy_S_second[280][280]/F");
        tree->Branch("Energy_C_second", &Energy_C_second, "Energy_C_second[280][280]/F");
    }

    HepMC3::ReaderRootTree reader(std::string(filename) + "_" + std::string(filenum) + ".root");

    unsigned int entries = drInterface->entries();
    while (drInterface->numEvt() < entries) {

        for (int i = 0; i < (2 * N_tow + 1) * N_fib; i++) {
            for (int j = 0; j < (2 * N_tow + 1) * N_fib; j++) {
                Energy_S_first[i][j] = 0;
                Energy_C_first[i][j] = 0;
                Energy_S_second[i][j] = 0;
                Energy_C_second[i][j] = 0;
            }
        }

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
        if (cluster_pair[0] == -1 || cluster_pair[1] == -1) continue; // reject the event if cluster of scin and cheren does not match
        
        /*
                auto tower_pos = segmentation->towerposition_from_cell_ID(fiber->fiberNum);
                TVector3 tower_vec(tower_pos.x(), tower_pos.y(), tower_pos.z());

                auto SiPM_pos = segmentation->position(fiber->fiberNum);
                TVector3 SiPM_vec(SiPM_pos.x(), SiPM_pos.y(), SiPM_pos.z());

                int Eta = segmentation->numEta(fiber->fiberNum);
                int Phi = segmentation->numPhi(fiber->fiberNum);

                int NumX = segmentation->numX(fiber->fiberNum);
                int NumY = segmentation->numY(fiber->fiberNum);

                int X = segmentation->x(fiber->fiberNum);
                int Y = segmentation->y(fiber->fiberNum);
                
                fprintf(fp, "tower pos: %f %f\n",tower_vec.Theta(), tower_vec.Phi());
                fprintf(fp, "SiPM pos: %f %f\n", SiPM_vec.Theta(), SiPM_vec.Phi());
                fprintf(fp, "tower eta phi: %d %d\n", Eta, Phi);
                fprintf(fp, "SiPM max x y: %d %d\n", NumX, NumY);
                fprintf(fp, "SiPM x y: %d %d\n", X, Y);

        */

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

        // save data
        for (auto tower = recoEvt->towers.begin(); tower != recoEvt->towers.end(); ++tower) {
            for (auto fiber = tower->fibers.begin(); fiber != tower->fibers.end(); ++fiber) {

                int current_Eta = segmentation->numEta(fiber->fiberNum);
                int current_Phi = segmentation->numPhi(fiber->fiberNum);
                int relative_Eta_wrt_first_cluster = current_Eta - Eta_tower_first;
                int relative_Phi_wrt_first_cluster = Del_Phi(current_Phi, Phi_tower_first);
                int relative_Eta_wrt_second_cluster = current_Eta - Eta_tower_second;
                int relative_Phi_wrt_second_cluster = Del_Phi(current_Phi, Phi_tower_second);

                int X;
                int Y;
                if (current_Eta < 0) {
                    X = (-segmentation->y(fiber->fiberNum) + N_fib - 1) + N_tow * N_fib;
                    Y = segmentation->x(fiber->fiberNum) + N_tow * N_fib;
                }
                else {
                    X = segmentation->y(fiber->fiberNum) + N_tow * N_fib;
                    Y = (-segmentation->x(fiber->fiberNum) + N_fib - 1) + N_tow * N_fib;
                }

                if ((-1) * N_tow <= relative_Eta_wrt_first_cluster && relative_Eta_wrt_first_cluster <= N_tow && (-1) * N_tow <= relative_Phi_wrt_first_cluster && relative_Phi_wrt_first_cluster <= N_tow) {
                    X = X - relative_Eta_wrt_first_cluster * N_fib;
                    Y = Y + relative_Phi_wrt_first_cluster * N_fib;
                    if (segmentation->IsCerenkov(fiber->fiberNum)) Energy_C_first[X][Y] = Energy_C_first[X][Y] + fiber->Ecorr;
                    else Energy_S_first[X][Y] = Energy_S_first[X][Y] + fiber->Ecorr;
                }
                else if ((-1) * N_tow <= relative_Eta_wrt_second_cluster && relative_Eta_wrt_second_cluster <= N_tow && (-1) * N_tow <= relative_Phi_wrt_second_cluster && relative_Phi_wrt_second_cluster <= N_tow) {
                    X = X - relative_Eta_wrt_second_cluster * N_fib;
                    Y = Y + relative_Phi_wrt_second_cluster * N_fib;
                    if (segmentation->IsCerenkov(fiber->fiberNum)) Energy_C_second[X][Y] = Energy_C_second[X][Y] + fiber->Ecorr;
                    else Energy_S_second[X][Y] = Energy_S_second[X][Y] + fiber->Ecorr;
                }
                else break;
            }
        }
        tree->Fill();

        delete recoEvt;
    } // event loop

    file->cd(); tree->Write();
    file->Close();
}
