set(headers ${headers} src/Menu/View
)
set(currsources
  src/Menu/View/IMenuViewModule.h
  src/Menu/View/MenuCLI.cpp
  src/Menu/View/MenuCLI.h
  src/Menu/View/MenuView.cpp
  src/Menu/View/MenuView.h
  src/Menu/View/MenuViewIncludes.h
  src/Menu/View/MenuViewModule.cpp
  src/Menu/View/MenuViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
 
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Menu\\View FILES ${currsources})
