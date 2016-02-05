set(headers ${headers} src/SearchResultMenu/View
)
set(currsources
  src/SearchResultMenu/View/SearchMenuCLI.cpp
  src/SearchResultMenu/View/SearchMenuCLI.h
  src/SearchResultMenu/View/SearchMenuView.cpp
  src/SearchResultMenu/View/SearchMenuView.h
  src/SearchResultMenu/View/SearchMenuViewModule.cpp
  src/SearchResultMenu/View/SearchMenuViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "/clr /EHa /Y-")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\SearchResultMenu\\View FILES ${currsources})
