set(headers ${headers} ../src/AppModes/States/SdkModel
)
set(currsources
  ../src/AppModes/States/SdkModel/AppModeStatesFactory.cpp
  ../src/AppModes/States/SdkModel/AppModeStatesFactory.h
  ../src/AppModes/States/SdkModel/CMakeLists.txt
  ../src/AppModes/States/SdkModel/InteriorExplorerState.cpp
  ../src/AppModes/States/SdkModel/InteriorExplorerState.h
  ../src/AppModes/States/SdkModel/WorldState.cpp
  ../src/AppModes/States/SdkModel/WorldState.h
  ../src/AppModes/States/SdkModel/AttractState.cpp
  ../src/AppModes/States/SdkModel/AttractState.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\AppModes\\States\\SdkModel FILES ${currsources})
