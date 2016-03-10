set(headers ${headers} src/FlattenButton/View
)
set(currsources
  src/FlattenButton/View/FlattenButtonCLI.cpp
  src/FlattenButton/View/FlattenButtonCLI.h
  src/FlattenButton/View/FlattenButtonView.cpp
  src/FlattenButton/View/FlattenButtonView.h
  src/FlattenButton/View/FlattenButtonViewIncludes.h
  src/FlattenButton/View/FlattenButtonViewModule.cpp
  src/FlattenButton/View/FlattenButtonViewModule.h
  src/FlattenButton/View/IFlattenButtonViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\FlattenButton\\View FILES ${currsources})
