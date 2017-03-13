set(headers ${headers} ../src/InteriorsPosition/SdkModel/SenionLab
)
set(currsources
  ../src/InteriorsPosition/SdkModel/SenionLab/CMakeLists.txt
  ../src/InteriorsPosition/SdkModel/SenionLab/ISenionLabLocationManager.h
  ../src/InteriorsPosition/SdkModel/SenionLab/SenionLabLocationController.cpp
  ../src/InteriorsPosition/SdkModel/SenionLab/SenionLabLocationController.h
  ../src/InteriorsPosition/SdkModel/SenionLab/SenionLabLocationService.cpp
  ../src/InteriorsPosition/SdkModel/SenionLab/SenionLabLocationService.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsPosition\\SdkModel\\SenionLab FILES ${currsources})
