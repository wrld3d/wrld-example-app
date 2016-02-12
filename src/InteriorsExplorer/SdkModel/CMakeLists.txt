set(headers ${headers} ../src/InteriorsExplorer/SdkModel
)
set(currsources
  ../src/InteriorsExplorer/SdkModel/CMakeLists.txt
  ../src/InteriorsExplorer/SdkModel/IInteriorsExplorerModule.h
  ../src/InteriorsExplorer/SdkModel/InteriorExplorerUserInteractionModel.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorExplorerUserInteractionModel.h
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerCameraController.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerCameraController.h
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerModel.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerModel.h
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerModule.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerModule.h
  ../src/InteriorsExplorer/SdkModel/InteriorVisibilityUpdater.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorVisibilityUpdater.h
  ../src/InteriorsExplorer/SdkModel/InteriorWorldPinController.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorWorldPinController.h
  ../src/InteriorsExplorer/SdkModel/InteriorWorldPinSelectionHandler.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsExplorer\\SdkModel FILES ${currsources})
include(../src/InteriorsExplorer/SdkModel/States/CMakeLists.txt)
