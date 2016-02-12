set(headers ${headers} ../src/SearchResultSection
)
set(currsources
  ../src/SearchResultSection/CMakeLists.txt
  ../src/SearchResultSection/SearchResultAddedMessage.cpp
  ../src/SearchResultSection/SearchResultAddedMessage.h
  ../src/SearchResultSection/SearchResultRemovedMessage.cpp
  ../src/SearchResultSection/SearchResultRemovedMessage.h
  ../src/SearchResultSection/SearchResultSection.h
  ../src/SearchResultSection/SearchResultSectionItemSelectedMessage.cpp
  ../src/SearchResultSection/SearchResultSectionItemSelectedMessage.h
  ../src/SearchResultSection/SearchResultViewClearedMessage.cpp
  ../src/SearchResultSection/SearchResultViewClearedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchResultSection FILES ${currsources})
include(../src/SearchResultSection/SdkModel/CMakeLists.txt)
include(../src/SearchResultSection/View/CMakeLists.txt)
