set(headers ${headers} ../src/AttractMode/SdkModel/States
)
set(currsources
  ../src/AttractMode/SdkModel/States/CMakeLists.txt
  ../src/AttractMode/SdkModel/States/AttractModeEnteringState.cpp
  ../src/AttractMode/SdkModel/States/AttractModeEnteringState.h
  ../src/AttractMode/SdkModel/States/AttractModeViewingState.cpp
  ../src/AttractMode/SdkModel/States/AttractModeViewingState.h
  ../src/AttractMode/SdkModel/States/AttractModeExitingState.cpp
  ../src/AttractMode/SdkModel/States/AttractModeExitingState.h
  ../src/AttractMode/SdkModel/States/AttractModeStates.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\AttractMode\\SdkModel\\States FILES ${currsources})
