set(headers ${headers} src/Options/View
)
set(currsources_noclr
  src/Options/View/OptionsViewIncludes.h
  src/Options/View/OptionsViewModule.cpp
  src/Options/View/OptionsViewModule.h
  src/Options/View/OptionsView.h
)

set(currsources
  src/Options/View/OptionsCLI.cpp
  src/Options/View/OptionsCLI.h
  src/Options/View/OptionsViewImpl.cpp
  src/Options/View/OptionsViewImpl.h
  src/Options/View/OptionsView.cpp
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\Options\\View FILES ${currsources} ${currsources_noclr})
