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
You can check the change in the `install` .

### Generating events
There is `pipipi_generic.cmnd` file in the `pipipi_example` directory of the main directory.

It is for Pythia8 to produce e^{-}e^{+}→Z→\tau^{-}\tau^{+} (\tau^{-}→\pi^{-}\pi^{+}\pi^{-}\nu).
Go to the install directory and copy that cmnd file into the install directory.

    cd ../install
    cp ../pipipi_example directory/pipipi_generic.cmnd ./
    
Then, produce events using Pythia8,

    ./bin/P8generic pipipi_generic.cmnd 42 test_Z2tau2pipipi
    
, which would produce `test_Z2tau2pipipi_42.root` file. Condor can make this process to be parallel.

### Running GEANT4
You get `test_Z2tau2pipipi_42.root` file at the above step. There is `run_hepmc_pipipi.mac` file in the `pipipi_example` directory of the main directory. It is macro file to run GEANT4. Copy it into the install directory.

    cp ../pipipi_example directory/run_hepmc_pipipi.mac ./
    
Then do

    ./bin/DRsim run_hepmc_pipipi.mac 42 test_Z2tau2pipipi

, which run GEANT4 simulation with `test_Z2tau2pipipi_42.root` file. You can check the volume of the `test_Z2tau2pipipi_42.root` file is larger than before.

### Reconstruction
> Because of technical issue, I did not use Reco. It is also possible to produce root files to run TMVA and CNN without this step (reconstruction is conducted after). So, you can just skip this step.

This requires the ROOT file generated from `DRsim`. Assuming the name of the file `<filename>_<filenumber>.root`, in build/Reco,

    #./Reco <filenumber> <filename>
    ./Reco 0 ../eltest

### Produce root files to run TMVA or CNN
#### produce_rootfiles_for_TMVA.cc
You can find `./bin/produce_rootfiles_for_TMVA` in the install directory. It is for TMVA. Do

    ./bin/produce_rootfiles_for_TMVA 42 test_Z2tau2pipipi

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
    S_sigma_first_cluster: spreadness of most energetic cluster in scintillation channel
    C_sigma_first_cluster: spreadness of the cluster in Cherenkov channel. The cluster is most energetic cluster in scintillation channel
    S_sigma_second_cluster: spreadness of secondarily energetic cluster in scintillation channel
    C_sigma_second_cluster: spreadness of the cluster in Cherenkov channel. The cluster is secondarily energetic cluster in scintillation channel
    total_signal_peak_position_S: peak position of total signal in scintillation channel (unit: ns)
    total_signal_peak_position_C: peak position of total signal in Cherenkov channel (unit: ns)
    time_signal_rise_threshold_S: first time when total signal cross a threshold in scintillation channel (default threshold: half of peak height)
    time_signal_rise_threshold_C: first time when total signal cross a threshold in Cherenkov channel (default threshold: half of peak height)
    time_signal_fall_threshold_S: last time when total signal cross a threshold in scintillation channel (default threshold: half of peak height)
    time_signal_fall_threshold_C: last time when total signal cross a threshold in Cherenkov channel (default threshold: half of peak height)
    signal_peak_position_S_first_cluster: peak position of signal of most energetic cluster in scintillation channel (unit: ns)
    signal_peak_position_C_first_cluster: peak position of signal of the cluster in Cherenkov channel. The cluster is most energetic cluster in scintillation channel. (unit: ns)
    signal_peak_position_S_second_cluster: peak position of signal of secondarily energetic cluster in scintillation channel (unit: ns)
    signal_peak_position_C_second_cluster: peak position of signal of the cluster in Cherenkov channel. The cluster is secondarily energetic cluster in scintillation channel. (unit: ns)
    rise_time_10to90_S_first_cluster: rise time(10to90) of signal of most energetic cluster in scintillation channel (unit: ns)
    rise_time_10to90_C_first_cluster: rise time(10to90) of signal of the cluster in Cherenkov channel. The cluster is most energetic cluster in scintillation channel. (unit: ns)
    rise_time_10to90_S_second_cluster: rise time(10to90) of signal of secondarily energetic cluster in scintillation channel (unit: ns)
    rise_time_10to90_C_second_cluster: rise time(10to90) of signal of the cluster in Cherenkov channel. The cluster is secondarily energetic cluster in scintillation channel. (unit: ns)
    middle_of_10to90_S_first_cluster: first time of crossing half height of signal of most energetic cluster in scintillation channel (unit: ns)
    middle_of_10to90_C_first_cluster: first time of crossing half height of signal of the cluster in Cherenkov channel. The cluster is most energetic cluster in scintillation channel. (unit: ns)
    middle_of_10to90_S_second_cluster: first time of crossing half height of signal of secondarily energetic cluster in scintillation channel (unit: ns)
    middle_of_10to90_C_second_cluster: first time of crossing half height of signal of the cluster in Cherenkov channel. The cluster is secondarily energetic cluster in scintillation channel. (unit: ns)
    S_of_C_first_cluster: Scintillation energy divided by Cherenkov energy of the cluster. The cluster is most energetic cluster in scintillation channel
    S_of_C_second_cluster: Scintillation energy divided by Cherenkov energy of the cluster. The cluster is secondarily energetic cluster in scintillation channel
    E_33_dividedby_E_55_S_first_cluster: energy inside 3x3 towers/energy inside 5x5 towers of the cluster in scintillation channel. Center of 3x3 and 5x5 is the tower which is most closest from the position of the cluster. The cluster is most energetic cluster in scintillation channel. 
    E_33_dividedby_E_55_C_first_cluster: energy inside 3x3 towers/energy inside 5x5 towers of the cluster in Cherenkov channel. Center of 3x3 and 5x5 is the tower which is most closest from the position of the cluster. The cluster is most energetic cluster in scintillation channel. 
    E_33_dividedby_E_55_S_second_cluster: energy inside 3x3 towers/energy inside 5x5 towers of the cluster in scintillation channel. Center of 3x3 and 5x5 is the tower which is most closest from the position of the cluster. The cluster is secondarily energetic cluster in scintillation channel. 
    E_33_dividedby_E_55_C_second_cluster: energy inside 3x3 towers/energy inside 5x5 towers of the cluster in Cherenkov channel. Center of 3x3 and 5x5 is the tower which is most closest from the position of the cluster. The cluster is secondarily energetic cluster in scintillation channel. 
    
sample TMVA code is in `TMVA_script` directory of the main directory. You can see `TMVAClassification.C` and `draw_input_variables.c`.
`TMVAClassification.C` is the code for TMVA. `draw_input_variables.c` is the code to plot the input variables. You need to modify them to use.

#### produce_rootfiles_for_CNN_4pi_images_224x224.cc
You can find `./bin/produce_rootfiles_for_CNN_4pi_images_224x224` in the install directory. It is for CNN. Do

    ./bin/produce_rootfiles_for_CNN_4pi_images_224x224 42 test_Z2tau2pipipi
    
, which would produce `test_Z2tau2pipipi_CNN_out_42.root` file. In this root file, energy distribution of 4pi calorimeter is saved.

It save energy distribution of scintillation channel and Cherenkov channel. The example of saved data is the below plot:
![Alt text](/img/S_224.png "S_224")

The size of single images is 224x224. Therefore, the size of image is 2x224x224 (channel x height x width)

#### produce_rootfiles_for_CNN_clusters_images_280x280.cc
> This code has a potential error. You need to revise it!

You can find `./bin/produce_rootfiles_for_CNN_clusters_images_280x280` in the install directory. It is for CNN. Do

    ./bin/produce_rootfiles_for_CNN_clusters_images_280x280 42 test_Z2tau2pipipi
    
, which would produce `test_Z2tau2pipipi_CNN_out_42.root` file. In this root file, energy distribution of 5x5 towers is saved.
The center of 5x5 tower is the tower, which is most closest from the position of cluster.

It save energy distribution of scintillation channel and Cherenkov channel. Also, it save the images with respect to two clusters. The first one is the most energetic cluster in scintillation channel. The other one is the secondarily energetic cluster in scintillation channel.

The example of saved data is the below plot:
![Alt text](/img/S_280.png "S_280")

The size of single images is 280x280. Therefore, the size of image is 4x280x280 (channel x height x width)

> I assumed that towers consisted of 56x56 fibers. So, I made the size of image to be 280x280. However, the number of fibers inside towers depend on the eta and phi position of towers. You need to fix it.
    
    
#### produce_rootfiles_for_CNN_clusters_images_256x256.cc
You can find `./bin/produce_rootfiles_for_CNN_clusters_images_256x256` in the install directory. It is for CNN. Do

    ./bin/produce_rootfiles_for_CNN_clusters_images_256x256 42 test_Z2tau2pipipi
    
, which would produce `test_Z2tau2pipipi_CNN_out_42.root` file. In this root file, energy distributions near the clusters are saved. The center is the position of cluster. Size is 0.5 rad x 0.5 rad. It save energy distribution of scintillation channel and Cherenkov channel. Also, it save the images with respect to two clusters. The first one is the most energetic cluster in scintillation channel. The other one is the secondarily energetic cluster in scintillation channel.

The example of saved data is the below plot:
![Alt text](/img/S_256.png "S_256")

The size of single images is 256x256. Therefore, the size of image is 4x256x256 (channel x height x width)

### How to run CNN
https://github.com/purol/HEP-CNN

### Note
This code is based on v0.0.1

### More information
https://github.com/SanghyunKo/dual-readout
