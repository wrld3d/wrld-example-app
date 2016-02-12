set(headers ${headers} ../src/SearchResultSection/View
)
set(currsources
  ../src/SearchResultSection/View/CMakeLists.txt
  ../src/SearchResultSection/View/ISearchResultSectionOrder.h
  ../src/SearchResultSection/View/SearchResultItemModel.cpp
  ../src/SearchResultSection/View/SearchResultItemModel.h
  ../src/SearchResultSection/View/SearchResultRepositoryObserver.cpp
  ../src/SearchResultSection/View/SearchResultRepositoryObserver.h
  ../src/SearchResultSection/View/SearchResultSectionController.cpp
  ../src/SearchResultSection/View/SearchResultSectionController.h
  ../src/SearchResultSection/View/SearchResultSectionOrder.cpp
  ../src/SearchResultSection/View/SearchResultSectionOrder.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchResultSection\\View FILES ${currsources})
