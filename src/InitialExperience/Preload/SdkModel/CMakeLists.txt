set(headers ${headers} ../src/InitialExperience/Preload/SdkModel
)
set(currsources
  ../src/InitialExperience/Preload/SdkModel/CMakeLists.txt
  ../src/InitialExperience/Preload/SdkModel/IInitialExperiencePreLoadModel.h
  ../src/InitialExperience/Preload/SdkModel/InitialExperiencePreLoadModel.cpp
  ../src/InitialExperience/Preload/SdkModel/InitialExperiencePreLoadModelBase.h
  ../src/InitialExperience/Preload/SdkModel/PreloadSphereVolume.cpp
  ../src/InitialExperience/Preload/SdkModel/PreloadSphereVolume.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InitialExperience\\Preload\\SdkModel FILES ${currsources})
