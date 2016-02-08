set(headers ${headers} ../src/MyPinDetails/SdkModel
)
set(currsources
  ../src/MyPinDetails/SdkModel/CMakeLists.txt
  ../src/MyPinDetails/SdkModel/IMyPinDetailsModule.h
  ../src/MyPinDetails/SdkModel/MyPinDetailsModule.cpp
  ../src/MyPinDetails/SdkModel/MyPinDetailsModule.h
  ../src/MyPinDetails/SdkModel/MyPinDetailsViewRemovePinHandler.cpp
  ../src/MyPinDetails/SdkModel/MyPinDetailsViewRemovePinHandler.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\MyPinDetails\\SdkModel FILES ${currsources})
