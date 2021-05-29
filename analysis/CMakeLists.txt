project(analysis)
cmake_minimum_required(VERSION 3.17)

find_package(ROOT REQUIRED)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${FASTJET_DIR}/include
  ${HEPMC_DIR}/include
)
file(GLOB sources
  ${PROJECT_SOURCE_DIR}/src/*.cc
)
file(GLOB headers
  ${PROJECT_SOURCE_DIR}/include/*.h
)

include(${ROOT_USE_FILE})
add_executable(produce_rootfiles_for_TMVA produce_rootfiles_for_TMVA.cc ${sources} ${headers})
add_executable(produce_rootfiles_for_CNN_4pi_images_224x224 produce_rootfiles_for_CNN_4pi_images_224x224.cc ${sources} ${headers})
add_executable(produce_rootfiles_for_CNN_clusters_images_280x280 produce_rootfiles_for_CNN_clusters_images_280x280.cc ${sources} ${headers})
add_executable(produce_rootfiles_for_CNN_clusters_images_256x256 produce_rootfiles_for_CNN_clusters_images_256x256.cc ${sources} ${headers})
#add_executable(JER JER.cc ${sources} ${headers})
#add_executable(calib calib.cc ${sources} ${headers})
target_link_libraries(
  produce_rootfiles_for_TMVA
  ${HEPMC_DIR}/lib64/libHepMC3.so
  ${HEPMC_DIR}/lib64/libHepMC3rootIO.so
  rootIO
  ${ROOT_LIBRARIES}
  ${CMAKE_DL_LIBS}
  DetComponents
  ddDRsegmentation
)
target_link_libraries(
  produce_rootfiles_for_CNN_4pi_images_224x224
  ${HEPMC_DIR}/lib64/libHepMC3.so
  ${HEPMC_DIR}/lib64/libHepMC3rootIO.so
  rootIO
  ${ROOT_LIBRARIES}
  ${CMAKE_DL_LIBS}
  DetComponents
  ddDRsegmentation
)
target_link_libraries(
  produce_rootfiles_for_CNN_clusters_images_280x280
  ${HEPMC_DIR}/lib64/libHepMC3.so
  ${HEPMC_DIR}/lib64/libHepMC3rootIO.so
  rootIO
  ${ROOT_LIBRARIES}
  ${CMAKE_DL_LIBS}
  DetComponents
  ddDRsegmentation
)
target_link_libraries(
  produce_rootfiles_for_CNN_clusters_images_256x256
  ${HEPMC_DIR}/lib64/libHepMC3.so
  ${HEPMC_DIR}/lib64/libHepMC3rootIO.so
  rootIO
  ${ROOT_LIBRARIES}
  ${CMAKE_DL_LIBS}
  DetComponents
  ddDRsegmentation
)
#target_link_libraries(
#  JER
#  ${HEPMC_DIR}/lib64/libHepMC3.so
#  ${HEPMC_DIR}/lib64/libHepMC3rootIO.so
#  rootIO
#  ${ROOT_LIBRARIES}
#  ${CMAKE_DL_LIBS}
#)
#target_link_libraries(
#  calib
#  ${HEPMC_DIR}/lib64/libHepMC3.so
#  ${HEPMC_DIR}/lib64/libHepMC3rootIO.so
#  rootIO
#  ${ROOT_LIBRARIES}
#  ${CMAKE_DL_LIBS}
#)

set(
  analysis_SCRIPTS
)

foreach(_script ${analysis_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
  )
endforeach()

install(TARGETS produce_rootfiles_for_TMVA produce_rootfiles_for_CNN_4pi_images_224x224 produce_rootfiles_for_CNN_clusters_images_280x280 produce_rootfiles_for_CNN_clusters_images_256x256 DESTINATION bin) # JER calib
