set(headers ${headers} ../src/Compass/SdkModel
)
set(currsources
  ../src/Compass/SdkModel/CMakeLists.txt
  ../src/Compass/SdkModel/CompassModel.cpp
  ../src/Compass/SdkModel/CompassModel.h
  ../src/Compass/SdkModel/CompassModeObserver.cpp
  ../src/Compass/SdkModel/CompassModeObserver.h
  ../src/Compass/SdkModel/CompassModule.cpp
  ../src/Compass/SdkModel/CompassModule.h
  ../src/Compass/SdkModel/CompassUpdateController.cpp
  ../src/Compass/SdkModel/CompassUpdateController.h
  ../src/Compass/SdkModel/CompassViewCycledObserver.cpp
  ../src/Compass/SdkModel/CompassViewCycledObserver.h
  ../src/Compass/SdkModel/ICompassModel.h
  ../src/Compass/SdkModel/ICompassModule.h
  ../src/Compass/SdkModel/ICompassUpdateController.h
  ../src/Compass/SdkModel/ICompassTouchController.h
  ../src/Compass/SdkModel/CompassTouchController.cpp
  ../src/Compass/SdkModel/CompassTouchController.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Compass\\SdkModel FILES ${currsources})
