set(headers ${headers} ../src/CameraTransitions/SdkModel
)
set(currsources
  ../src/CameraTransitions/SdkModel/CameraTransitionController.cpp
  ../src/CameraTransitions/SdkModel/CameraTransitionController.h
  ../src/CameraTransitions/SdkModel/CameraTransitions.h
  ../src/CameraTransitions/SdkModel/CameraTransitionService.cpp
  ../src/CameraTransitions/SdkModel/CameraTransitionService.h
  ../src/CameraTransitions/SdkModel/CMakeLists.txt
  ../src/CameraTransitions/SdkModel/ExitCurrentInteriorStage.cpp
  ../src/CameraTransitions/SdkModel/ExitCurrentInteriorStage.h
  ../src/CameraTransitions/SdkModel/ICameraTransitionController.h
  ../src/CameraTransitions/SdkModel/ICameraTransitionStage.h
  ../src/CameraTransitions/SdkModel/TransitionToInteriorPointStage.cpp
  ../src/CameraTransitions/SdkModel/TransitionToInteriorPointStage.h
  ../src/CameraTransitions/SdkModel/TransitionToInteriorStage.cpp
  ../src/CameraTransitions/SdkModel/TransitionToInteriorStage.h
  ../src/CameraTransitions/SdkModel/TransitionToWorldPointStage.cpp
  ../src/CameraTransitions/SdkModel/TransitionToWorldPointStage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\CameraTransitions\\SdkModel FILES ${currsources})
