set(headers ${headers} ../src/IndoorLocation/SdkModel
)
set(currsources
  ../src/IndoorLocation/SdkModel/IndoorLocationDeviceModel.h
  ../src/IndoorLocation/SdkModel/IndoorLocationDeviceModel.cpp
  ../src/IndoorLocation/SdkModel/DeviceLocation.h
  ../src/IndoorLocation/SdkModel/IndoorLocationModule.cpp
  ../src/IndoorLocation/SdkModel/IndoorLocationModule.h
  ../src/IndoorLocation/SdkModel/IIndoorLocationDeviceModel.h
  ../src/IndoorLocation/SdkModel/IIndoorLocationModule.h
  ../src/IndoorLocation/SdkModel/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\IndoorLocation\\SdkModel FILES ${currsources})