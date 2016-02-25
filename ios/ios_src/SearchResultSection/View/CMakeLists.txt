if(${IOS})
set(headers ${headers} ios_src/SearchResultSection/View
)
set(currsources
  ios_src/SearchResultSection/View/ISearchResultSectionViewModule.h
  ios_src/SearchResultSection/View/SearchResultSectionViewIncludes.h
  ios_src/SearchResultSection/View/SearchResultSectionViewModule.h
  ios_src/SearchResultSection/View/SearchResultSectionViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SearchResultSection\\View FILES ${currsources})
endif(${IOS})
