set(headers ${headers} src/SearchResultPoi/View
)
set(currsources_noclr
  src/SearchResultPoi/View/SearchResultPoiViewIncludes.h
  src/SearchResultPoi/View/SearchResultPoiViewModule.cpp
  src/SearchResultPoi/View/SearchResultPoiViewModule.h
  src/SearchResultPoi/View/SearchResultPoiView.h
)
set(currsources
  src/SearchResultPoi/View/SearchResultModelCLI.cpp
  src/SearchResultPoi/View/SearchResultModelCLI.h
  src/SearchResultPoi/View/SearchResultPoiViewImpl.cpp
  src/SearchResultPoi/View/SearchResultPoiViewImpl.h
  src/SearchResultPoi/View/SearchResultPoiView.cpp
  src/SearchResultPoi/View/SearchResultPoiViewCLI.cpp
  src/SearchResultPoi/View/SearchResultPoiViewCLI.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\SearchResultPoi\\View FILES ${currsources} ${currsources_noclr})
