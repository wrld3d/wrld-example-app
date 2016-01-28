set(headers ${headers} ../src/SearchResultOnMap/View
)
set(currsources
  ../src/SearchResultOnMap/View/CMakeLists.txt
  ../src/SearchResultOnMap/View/ISearchResultOnMapFactory.h
  ../src/SearchResultOnMap/View/SearchResultOnMapFactory.cpp
  ../src/SearchResultOnMap/View/SearchResultOnMapFactory.h
  ../src/SearchResultOnMap/View/SearchResultOnMapItemModel.cpp
  ../src/SearchResultOnMap/View/SearchResultOnMapItemModel.h
  ../src/SearchResultOnMap/View/SearchResultOnMapItemModelSelectedObserver.cpp
  ../src/SearchResultOnMap/View/SearchResultOnMapItemModelSelectedObserver.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchResultOnMap\\View FILES ${currsources})
