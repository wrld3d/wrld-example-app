set(headers ${headers} src/AboutPage/View
)
set(currsources
  src/AboutPage/View/AboutPageCLI.cpp
  src/AboutPage/View/AboutPageCLI.h
  src/AboutPage/View/AboutPageView.cpp
  src/AboutPage/View/AboutPageView.h
  src/AboutPage/View/AboutPageViewIncludes.h
  src/AboutPage/View/AboutPageViewModule.cpp
  src/AboutPage/View/AboutPageViewModule.h
  src/AboutPage/View/IAboutPageViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\AboutPage\\View FILES ${currsources})
