set(headers ${headers} ../src/AppCamera/SdkModel
)
set(currsources
  ../src/AppCamera/SdkModel/AppCameraController.cpp
  ../src/AppCamera/SdkModel/AppCameraController.h
  ../src/AppCamera/SdkModel/AppCameraModule.cpp
  ../src/AppCamera/SdkModel/AppCameraModule.h
  ../src/AppCamera/SdkModel/AppInteriorCameraWrapper.cpp
  ../src/AppCamera/SdkModel/AppInteriorCameraWrapper.h
  ../src/AppCamera/SdkModel/AppGlobeCameraWrapper.cpp
  ../src/AppCamera/SdkModel/AppGlobeCameraWrapper.h
  ../src/AppCamera/SdkModel/CMakeLists.txt
  ../src/AppCamera/SdkModel/IAppCameraController.h
  ../src/AppCamera/SdkModel/IAppCameraModule.h
  ../src/AppCamera/SdkModel/AppCameraSplinePlaybackWrapper.h
  ../src/AppCamera/SdkModel/AppCameraSplinePlaybackWrapper.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\AppCamera\\SdkModel FILES ${currsources})
