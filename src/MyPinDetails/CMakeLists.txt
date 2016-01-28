set(headers ${headers} ../src/MyPinDetails
)
set(currsources
  ../src/MyPinDetails/CMakeLists.txt
  ../src/MyPinDetails/MyPinDetails.h
  ../src/MyPinDetails/MyPinDetailsViewRemovePinMessage.cpp
  ../src/MyPinDetails/MyPinDetailsViewRemovePinMessage.h
  ../src/MyPinDetails/SearchResultMyPinDetailsModelSelectedMessage.cpp
  ../src/MyPinDetails/SearchResultMyPinDetailsModelSelectedMessage.h
  ../src/MyPinDetails/UserCreatedMyPinDetailsModelSelectedMessage.cpp
  ../src/MyPinDetails/UserCreatedMyPinDetailsModelSelectedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\MyPinDetails FILES ${currsources})
include(../src/MyPinDetails/SdkModel/CMakeLists.txt)
include(../src/MyPinDetails/View/CMakeLists.txt)
