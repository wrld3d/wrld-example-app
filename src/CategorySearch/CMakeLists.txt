set(headers ${headers} ../src/CategorySearch
)
set(currsources
  ../src/CategorySearch/CategorySearch.h
  ../src/CategorySearch/CategorySearchSelectedMessage.cpp
  ../src/CategorySearch/CategorySearchSelectedMessage.h
  ../src/CategorySearch/CMakeLists.txt
  ../src/CategorySearch/ISearchResultIconCategoryMapper.h
  ../src/CategorySearch/SearchResultIconCategoryMapper.cpp
  ../src/CategorySearch/SearchResultIconCategoryMapper.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\CategorySearch FILES ${currsources})
include(../src/CategorySearch/SdkModel/CMakeLists.txt)
include(../src/CategorySearch/View/CMakeLists.txt)
