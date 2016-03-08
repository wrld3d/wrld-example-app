set(headers ${headers} src/Options/View
)
set(currsources
  src/Options/View/IOptionsViewModule.h
  src/Options/View/OptionsCLI.cpp
  src/Options/View/OptionsCLI.h
  src/Options/View/OptionsView.cpp
  src/Options/View/OptionsView.h
  src/Options/View/OptionsViewIncludes.h
  src/Options/View/OptionsViewModule.cpp
  src/Options/View/OptionsViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Options\\View FILES ${currsources})
