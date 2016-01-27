set(headers ${headers} src/CategorySearch
)
set(currsources
  src/CategorySearch/CategorySearch.h
  src/CategorySearch/CategorySearchSelectedMessage.cpp
  src/CategorySearch/CategorySearchSelectedMessage.h
  src/CategorySearch/ISearchResultIconCategoryMapper.h
  src/CategorySearch/SearchResultIconCategoryMapper.cpp
  src/CategorySearch/SearchResultIconCategoryMapper.h
)
set(sources ${sources} ${currsources})
source_group(\\CategorySearch FILES ${currsources})
include(src/CategorySearch/SdkModel/CMakeLists.txt)
include(src/CategorySearch/View/CMakeLists.txt)
