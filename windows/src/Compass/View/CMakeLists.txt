set(headers ${headers} src/Compass/View
)
set(currsources_noclr
  src/Compass/View/CompassViewIncludes.h
  src/Compass/View/CompassViewModule.cpp
  src/Compass/View/CompassViewModule.h
  src/Compass/View/CompassView.h
)
set(currsources
  src/Compass/View/CompassCLI.cpp
  src/Compass/View/CompassCLI.h
  src/Compass/View/CompassView.cpp
  src/Compass/View/CompassViewImpl.h
  src/Compass/View/CompassViewImpl.cpp
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\Compass\\View FILES ${currsources} ${currsources_noclr})
