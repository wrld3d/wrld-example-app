set(headers ${headers} src/SearchMenu/View
)
set(currsources
  src/SearchMenu/View/ISearchMenuViewModule.h
  src/SearchMenu/View/SearchMenuView.cpp
  src/SearchMenu/View/SearchMenuView.h
  src/SearchMenu/View/SearchMenuCLI.cpp
  src/SearchMenu/View/SearchMenuCLI.h
  src/SearchMenu/View/SearchMenuViewIncludes.h
  src/SearchMenu/View/SearchMenuViewInterop.h
  src/SearchMenu/View/SearchMenuViewModule.cpp
  src/SearchMenu/View/SearchMenuViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\SearchMenu\\View FILES ${currsources})
