set(headers ${headers} src/InteriorsExplorer
)
set(currsources
  src/InteriorsExplorer/IInteriorsExplorerViewModule.h
  src/InteriorsExplorer/InteriorsExplorerCLI.cpp
  src/InteriorsExplorer/InteriorsExplorerCLI.h
  src/InteriorsExplorer/InteriorsExplorerView.cpp
  src/InteriorsExplorer/InteriorsExplorerView.h
  src/InteriorsExplorer/InteriorsExplorerViewIncludes.h
  src/InteriorsExplorer/InteriorsExplorerViewModule.cpp
  src/InteriorsExplorer/InteriorsExplorerViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\InteriorsExplorer FILES ${currsources})
