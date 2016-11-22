set(headers ${headers} src/AboutPage/View
)
set(currsources_noclr
  src/AboutPage/View/AboutPageViewIncludes.h
  src/AboutPage/View/AboutPageViewModule.cpp
  src/AboutPage/View/AboutPageViewModule.h
)
set(currsources
  src/AboutPage/View/AboutPageCLI.cpp
  src/AboutPage/View/AboutPageCLI.h
  src/AboutPage/View/AboutPageView.cpp
  src/AboutPage/View/AboutPageView.h
  src/AboutPage/View/AboutPageViewImpl.h
  src/AboutPage/View/AboutPageViewImpl.cpp
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\AboutPage\\View FILES ${currsources} ${currsources_noclr})
