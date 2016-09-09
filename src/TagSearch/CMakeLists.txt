set(headers ${headers} ../src/TagSearch
)
set(currsources
  ../src/TagSearch/TagSearch.h
  ../src/TagSearch/TagSearchAddedMessage.h
  ../src/TagSearch/TagSearchRemovedMessage.h
  ../src/TagSearch/TagSearchSelectedMessage.cpp
  ../src/TagSearch/TagSearchSelectedMessage.h
  ../src/TagSearch/CMakeLists.txt
  ../src/TagSearch/ISearchResultIconKeyMapper.h
  ../src/TagSearch/SearchResultIconKeyMapper.cpp
  ../src/TagSearch/SearchResultIconKeyMapper.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\TagSearch FILES ${currsources})
include(../src/TagSearch/SdkModel/CMakeLists.txt)
include(../src/TagSearch/View/CMakeLists.txt)
