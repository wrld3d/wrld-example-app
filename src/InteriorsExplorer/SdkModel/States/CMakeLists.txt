set(headers ${headers} ../src/InteriorsExplorer/SdkModel/States
)
set(currsources
  ../src/InteriorsExplorer/SdkModel/States/CMakeLists.txt
  ../src/InteriorsExplorer/SdkModel/States/InteriorExplorerExitingState.cpp
  ../src/InteriorsExplorer/SdkModel/States/InteriorExplorerExitingState.h
  ../src/InteriorsExplorer/SdkModel/States/InteriorExplorerSetupState.cpp
  ../src/InteriorsExplorer/SdkModel/States/InteriorExplorerSetupState.h
  ../src/InteriorsExplorer/SdkModel/States/InteriorExplorerStreamState.cpp
  ../src/InteriorsExplorer/SdkModel/States/InteriorExplorerStreamState.h
  ../src/InteriorsExplorer/SdkModel/States/InteriorExplorerViewingState.cpp
  ../src/InteriorsExplorer/SdkModel/States/InteriorExplorerViewingState.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsExplorer\\SdkModel\\States FILES ${currsources})
