set(headers ${headers} src/FlattenButton/View
)
set(currsources_noclr
  src/FlattenButton/View/FlattenButtonViewIncludes.h
  src/FlattenButton/View/FlattenButtonViewModule.cpp
  src/FlattenButton/View/FlattenButtonViewModule.h
  src/FlattenButton/View/FlattenButtonView.h
)

set(currsources
  src/FlattenButton/View/FlattenButtonCLI.cpp
  src/FlattenButton/View/FlattenButtonCLI.h
  src/FlattenButton/View/FlattenButtonView.cpp
  src/FlattenButton/View/FlattenButtonViewImpl.h
  src/FlattenButton/View/FlattenButtonViewImpl.cpp
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\FlattenButton\\View FILES ${currsources} ${currsources_noclr})
