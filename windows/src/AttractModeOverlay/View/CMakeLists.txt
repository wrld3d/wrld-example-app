set(headers ${headers} src/AttractModeOverlay/View
)
set(currsources
  src/AttractModeOverlay/View/CMakeLists.txt
  src/AttractModeOverlay/View/AttractModeOverlayView.cpp
  src/AttractModeOverlay/View/AttractModeOverlayView.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\AttractModeOverlay\\View FILES ${currsources})
