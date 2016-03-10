set(headers ${headers} src/Compass/View
)
set(currsources
  src/Compass/View/CompassCLI.cpp
  src/Compass/View/CompassCLI.h
  src/Compass/View/CompassView.cpp
  src/Compass/View/CompassView.h
  src/Compass/View/CompassViewIncludes.h
  src/Compass/View/CompassViewModule.cpp
  src/Compass/View/CompassViewModule.h
  src/Compass/View/ICompassViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Compass\\View FILES ${currsources})
