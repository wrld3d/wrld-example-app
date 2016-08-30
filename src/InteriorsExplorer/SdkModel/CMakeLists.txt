set(headers ${headers} ../src/InteriorsExplorer/SdkModel
)
set(currsources
  ../src/InteriorsExplorer/SdkModel/CMakeLists.txt
  ../src/InteriorsExplorer/SdkModel/IInteriorCameraController.h
  ../src/InteriorsExplorer/SdkModel/InteriorCameraController.h
  ../src/InteriorsExplorer/SdkModel/InteriorCameraController.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorExplorerUserInteractionModel.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorExplorerUserInteractionModel.h
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerModel.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerModel.h
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerModule.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerModule.h
  ../src/InteriorsExplorer/SdkModel/InteriorVisibilityUpdater.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorVisibilityUpdater.h
  ../src/InteriorsExplorer/SdkModel/InteriorWorldPinController.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorWorldPinController.h
  ../src/InteriorsExplorer/SdkModel/InteriorWorldPinSelectionHandler.h
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerFloorDraggedObserver.cpp
  ../src/InteriorsExplorer/SdkModel/InteriorsExplorerFloorDraggedObserver.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsExplorer\\SdkModel FILES ${currsources})
include(../src/InteriorsExplorer/SdkModel/Highlights/CMakeLists.txt)
include(../src/InteriorsExplorer/SdkModel/States/CMakeLists.txt)
