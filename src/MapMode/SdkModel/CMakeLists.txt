set(headers ${headers} ../src/MapMode/SdkModel
)
set(currsources
  ../src/MapMode/SdkModel/CMakeLists.txt
  ../src/MapMode/SdkModel/IMapModeModel.h
  ../src/MapMode/SdkModel/IMapModeModule.h
  ../src/MapMode/SdkModel/MapModeController.cpp
  ../src/MapMode/SdkModel/MapModeController.h
  ../src/MapMode/SdkModel/MapModeModel.cpp
  ../src/MapMode/SdkModel/MapModeModel.h
  ../src/MapMode/SdkModel/MapModeModule.cpp
  ../src/MapMode/SdkModel/MapModeModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\MapMode\\SdkModel FILES ${currsources})
