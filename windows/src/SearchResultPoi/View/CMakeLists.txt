set(headers ${headers} src/SearchResultPoi/View
)
set(currsources
  src/SearchResultPoi/View/ISearchResultPoiViewModule.h
  src/SearchResultPoi/View/SearchResultModelCLI.cpp
  src/SearchResultPoi/View/SearchResultModelCLI.h
  src/SearchResultPoi/View/SearchResultPoiView.cpp
  src/SearchResultPoi/View/SearchResultPoiView.h
  src/SearchResultPoi/View/SearchResultPoiViewCLI.cpp
  src/SearchResultPoi/View/SearchResultPoiViewCLI.h
  src/SearchResultPoi/View/SearchResultPoiViewIncludes.h
  src/SearchResultPoi/View/SearchResultPoiViewModule.cpp
  src/SearchResultPoi/View/SearchResultPoiViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\SearchResultPoi\\View FILES ${currsources})
