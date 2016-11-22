set(headers ${headers} src/Menu/View
)
set(currsources_noclr
  src/Menu/View/MenuViewIncludes.h
)
set(currsources
  src/Menu/View/MenuCLI.cpp
  src/Menu/View/MenuCLI.h
  src/Menu/View/MenuViewImpl.h
  src/Menu/View/MenuViewImpl.cpp
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\Menu\\View FILES ${currsources} ${currsources_noclr})
