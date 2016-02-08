set(headers ${headers} ../src/Tours/SdkModel/Camera
)
set(currsources
  ../src/Tours/SdkModel/Camera/CMakeLists.txt
  ../src/Tours/SdkModel/Camera/DroneLookatCameraMode.h
  ../src/Tours/SdkModel/Camera/InterestPointTransitionCameraMode.cpp
  ../src/Tours/SdkModel/Camera/InterestPointTransitionCameraMode.h
  ../src/Tours/SdkModel/Camera/IToursCameraController.h
  ../src/Tours/SdkModel/Camera/IToursCameraMode.h
  ../src/Tours/SdkModel/Camera/IToursCameraModule.h
  ../src/Tours/SdkModel/Camera/IToursCameraTransitionController.h
  ../src/Tours/SdkModel/Camera/IToursCameraTransitionMode.h
  ../src/Tours/SdkModel/Camera/MapCameraMode.cpp
  ../src/Tours/SdkModel/Camera/MapCameraMode.h
  ../src/Tours/SdkModel/Camera/OrbitCameraMode.h
  ../src/Tours/SdkModel/Camera/SplineCameraMode.cpp
  ../src/Tours/SdkModel/Camera/SplineCameraMode.h
  ../src/Tours/SdkModel/Camera/SplineTransitionCameraMode.cpp
  ../src/Tours/SdkModel/Camera/SplineTransitionCameraMode.h
  ../src/Tours/SdkModel/Camera/StaticCameraMode.cpp
  ../src/Tours/SdkModel/Camera/StaticCameraMode.h
  ../src/Tours/SdkModel/Camera/TourCameraModule.cpp
  ../src/Tours/SdkModel/Camera/TourCameraModule.h
  ../src/Tours/SdkModel/Camera/ToursCameraController.cpp
  ../src/Tours/SdkModel/Camera/ToursCameraController.h
  ../src/Tours/SdkModel/Camera/ToursCameraFadeTransitionMode.cpp
  ../src/Tours/SdkModel/Camera/ToursCameraFadeTransitionMode.h
  ../src/Tours/SdkModel/Camera/ToursCameraState.h
  ../src/Tours/SdkModel/Camera/ToursCameraTransitionController.cpp
  ../src/Tours/SdkModel/Camera/ToursCameraTransitionController.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Tours\\SdkModel\\Camera FILES ${currsources})
