set(headers ${headers} ../src/PlaceJumps/SdkModel
)
set(currsources
  ../src/PlaceJumps/SdkModel/CMakeLists.txt
  ../src/PlaceJumps/SdkModel/IPlaceJumpController.h
  ../src/PlaceJumps/SdkModel/IPlaceJumpsModule.h
  ../src/PlaceJumps/SdkModel/PlaceJumpController.cpp
  ../src/PlaceJumps/SdkModel/PlaceJumpController.h
  ../src/PlaceJumps/SdkModel/PlaceJumpSelectedMessageHandler.cpp
  ../src/PlaceJumps/SdkModel/PlaceJumpSelectedMessageHandler.h
  ../src/PlaceJumps/SdkModel/PlaceJumpsModule.cpp
  ../src/PlaceJumps/SdkModel/PlaceJumpsModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\PlaceJumps\\SdkModel FILES ${currsources})
