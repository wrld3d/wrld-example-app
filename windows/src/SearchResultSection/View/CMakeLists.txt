set(headers ${headers} src/SearchResultSection/View
)
set(currsources
  src/SearchResultSection/View/ISearchResultSectionViewModule.h
  src/SearchResultSection/View/SearchResultSectionViewModule.cpp
  src/SearchResultSection/View/SearchResultSectionViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\SearchResultSection\\View FILES ${currsources})
