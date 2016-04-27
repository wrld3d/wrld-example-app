set(headers ${headers} ../src/Search/Lax
)
set(currsources
  ../src/Search/Lax/LaxOfficeResultMenuOptionSelectedMessage.cpp
  ../src/Search/Lax/LaxOfficeResultMenuOptionSelectedMessage.h
  ../src/Search/Lax/LaxSearch.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Lax FILES ${currsources})
include(../src/Search/Lax/SdkModel/CMakeLists.txt)
include(../src/Search/Lax/SearchConstants/CMakeLists.txt)
include(../src/Search/Lax/View/CMakeLists.txt)
