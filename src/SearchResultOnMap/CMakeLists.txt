set(headers ${headers} src/SearchResultOnMap
)
set(currsources
  src/SearchResultOnMap/SearchResultOnMap.h
  src/SearchResultOnMap/SearchResultOnMapItemModelSelectedMessage.cpp
  src/SearchResultOnMap/SearchResultOnMapItemModelSelectedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\SearchResultOnMap FILES ${currsources})
include(src/SearchResultOnMap/SdkModel/CMakeLists.txt)
include(src/SearchResultOnMap/View/CMakeLists.txt)
