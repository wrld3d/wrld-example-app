set(headers ${headers} ../src/Search/Swallow
)
set(currsources
  ../src/Search/Swallow/SwallowOfficeResultMenuOptionSelectedMessage.cpp
  ../src/Search/Swallow/SwallowOfficeResultMenuOptionSelectedMessage.h
  ../src/Search/Swallow/SwallowSearch.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Swallow FILES ${currsources})
include(../src/Search/Swallow/SdkModel/CMakeLists.txt)
include(../src/Search/Swallow/SearchConstants/CMakeLists.txt)
include(../src/Search/Swallow/View/CMakeLists.txt)
