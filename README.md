# dual-readout
Modified dual-readout simulation of v0.0.1 for TMVA and CNN

## How to use
### Complile
After fetching the repository, go to the main directory.
for a convenience, make `build` and `install` directories.

    mkdir build
    mkdir install

Then, go to the build directory

    cd ./build

and do

    source setenv-cc7-gcc8.sh
    cmake -DCMAKE_INSTALL_PREFIX=/fcc/jwpark/dual-readout-master/install /fcc/jwpark/dual-readout-master
    make install
    make -j4
    
Here, `/fcc/jwpark/dual-readout-master` is the path of this program. You need to modify it.
You can check the change in the `install` directory.

### Generating events
There is `pipipi_generic.cmnd` file in the `pipipi_example directory` of the main directory. It is for Pythia8 to produce e^{-}e^{+}→Z→\tau^{-}\tau^{+} (\tau^{-}→\pi^{-}\pi^{+}\pi^{-}\nu).
Go to the install directory and copy that cmnd file into the install directory.

    cd ../install
    cp ../pipipi_example directory/pipipi_generic.cmnd ./
    
Then, produce events using Pythia8,

    ./bin/P8generic pipipi_generic.cmnd 42 test_Z2tau2pipipi
    
, which would produce `test_Z2tau2pipipi_42.root` file. Condor can make this process to be parallel.

### Running GEANT4
You get `test_Z2tau2pipipi_42.root` file at the above step. There is `run_hepmc_pipipi.mac` file in the `pipipi_example directory` of the main directory. It is macro file to run GEANT4. Copy it into the install directory.

    cp ../pipipi_example directory/run_hepmc_pipipi.mac ./
    
Then do

    ./bin/DRsim run_hepmc_pipipi.mac 42 test_Z2tau2pipipi

, which run GEANT4 simulation with `test_Z2tau2pipipi_42.root` file. You can check the volume of the `test_Z2tau2pipipi_42.root` file is larger than before.

### Reconstruction
    Because of technical issue, I did not use Reco. It is also possible to produce root files to run TMVA and CNN without this step (reconstruction is conducted after).
    So, you can just skip this step.
This requires the ROOT file generated from `DRsim`. Assuming the name of the file `<filename>_<filenumber>.root`, in build/Reco,

    #./Reco <filenumber> <filename>
    ./Reco 0 ../eltest

### Produce root files to run TMVA or CNN
#### produce_rootfiles_for_TMVA.cc
You can find `./bin/produce_rootfiles_for_TMVA.cc` in the install directory. It is for TMVA. Do

    ./bin/produce_rootfiles_for_TMVA.c 42 test_Z2tau2pipipi

, which would produce `test_Z2tau2pipipi_out_42.root` file. In this root file, there are 40 variables. 

    num_of_S_cluster: the number of clusters in scintillation channel
    num_of_C_cluster: the number of clusters in Cherenkov channel
    num_of_fired_S_fibers: the number of fired fibers in scintillation channel
    num_of_fired_C_fibers: the number of fired fibers in Cherenkov channel
    total_E_S: total energy of scintillation channel
    total_E_Scorr: total energy of scintillation channel (corrected energy)
    total_E_C: total energy of Cherenkov channel
    total_E_DR: total DR corrected energy (using non-corrected scintillation energy)
    total_E_DRcorr: total DR corrected energy (using corrected scintillation energy)
    total_missing_energy: total missing energy
    average_S_sigma: spreadness of clusters in scintillation channel
    average_C_sigma: spreadness of clusters in Cherenkov channel
    S_sigma_first_cluster
    C_sigma_first_cluster
    S_sigma_second_cluster
    C_sigma_second_cluster
    total_signal_peak_position_S
    total_signal_peak_position_C
    time_signal_rise_threshold_S
    time_signal_rise_threshold_C
    time_signal_fall_threshold_S
    time_signal_fall_threshold_C
    signal_peak_position_S_first_cluster
    signal_peak_position_C_first_cluster
    signal_peak_position_S_second_cluster
    signal_peak_position_C_second_cluster
    rise_time_10to90_S_first_cluster
    rise_time_10to90_C_first_cluster
    rise_time_10to90_S_second_cluster
    rise_time_10to90_C_second_cluster
    middle_of_10to90_S_first_cluster
    middle_of_10to90_C_first_cluster
    middle_of_10to90_S_second_cluster
    middle_of_10to90_C_second_cluster
    S_of_C_first_cluster
    S_of_C_second_cluster
    E_33_dividedby_E_55_S_first_cluster
    E_33_dividedby_E_55_C_first_cluster
    E_33_dividedby_E_55_S_second_cluster
    E_33_dividedby_E_55_C_second_cluster
    
