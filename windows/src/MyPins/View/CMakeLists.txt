set(headers ${headers} src/MyPins/View
)
set(currsources_noclr
  src/MyPins/View/MyPinsMenuOptionFactory.cpp
)
set(currsources
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\MyPins\\View FILES ${currsources} ${currsources_noclr})
