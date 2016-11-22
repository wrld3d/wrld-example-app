set(headers ${headers} src/SearchMenu/View
)
set(currsources_noclr
  src/SearchMenu/View/SearchMenuViewModule.cpp
  src/SearchMenu/View/SearchMenuViewModule.h
  src/SearchMenu/View/SearchMenuView.h
  src/SearchMenu/View/SearchMenuViewIncludes.h
)
set(currsources
  src/SearchMenu/View/SearchMenuViewImpl.cpp
  src/SearchMenu/View/SearchMenuViewImpl.h
  src/SearchMenu/View/SearchMenuView.cpp
  src/SearchMenu/View/SearchMenuCLI.cpp
  src/SearchMenu/View/SearchMenuCLI.h
  src/SearchMenu/View/SearchMenuViewInterop.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\SearchMenu\\View FILES ${currsources} ${currsources_noclr})
