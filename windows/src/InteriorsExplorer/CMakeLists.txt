set(headers ${headers} src/InteriorsExplorer
)
set(currsources_noclr
  src/InteriorsExplorer/InteriorsExplorerViewIncludes.h
  src/InteriorsExplorer/InteriorsExplorerViewModule.cpp
  src/InteriorsExplorer/InteriorsExplorerViewModule.h
  src/InteriorsExplorer/InteriorsExplorerView.h
)
set(currsources
  src/InteriorsExplorer/InteriorsExplorerCLI.cpp
  src/InteriorsExplorer/InteriorsExplorerCLI.h
  src/InteriorsExplorer/InteriorsExplorerView.cpp
  src/InteriorsExplorer/InteriorsExplorerViewImpl.h
  src/InteriorsExplorer/InteriorsExplorerViewImpl.cpp
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\InteriorsExplorer FILES ${currsources} ${currsources_noclr})
