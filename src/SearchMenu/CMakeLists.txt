set(headers ${headers} ../src/SearchMenu
)
set(currsources
  ../src/SearchMenu/CMakeLists.txt
  ../src/SearchMenu/SearchMenu.h
  ../src/SearchMenu/SearchMenuPerformedSearchMessage.cpp
  ../src/SearchMenu/SearchMenuPerformedSearchMessage.h
  ../src/SearchMenu/OpenSearchMenuMessage.cpp
  ../src/SearchMenu/OpenSearchMenuMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchMenu FILES ${currsources})
include(../src/SearchMenu/SdkModel/CMakeLists.txt)
include(../src/SearchMenu/View/CMakeLists.txt)
