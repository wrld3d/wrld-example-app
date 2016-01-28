set(headers ${headers} ../src/SearchResultMenu
)
set(currsources
  ../src/SearchResultMenu/CMakeLists.txt
  ../src/SearchResultMenu/SearchResultAddedMessage.cpp
  ../src/SearchResultMenu/SearchResultAddedMessage.h
  ../src/SearchResultMenu/SearchResultMenu.h
  ../src/SearchResultMenu/SearchResultMenuItemSelectedMessage.cpp
  ../src/SearchResultMenu/SearchResultMenuItemSelectedMessage.h
  ../src/SearchResultMenu/SearchResultRemovedMessage.cpp
  ../src/SearchResultMenu/SearchResultRemovedMessage.h
  ../src/SearchResultMenu/SearchResultViewClearedMessage.cpp
  ../src/SearchResultMenu/SearchResultViewClearedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchResultMenu FILES ${currsources})
include(../src/SearchResultMenu/SdkModel/CMakeLists.txt)
include(../src/SearchResultMenu/View/CMakeLists.txt)
