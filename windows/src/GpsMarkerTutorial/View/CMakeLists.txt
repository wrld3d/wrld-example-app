set(headers ${headers} src/GpsMarkerTutorial/View
)
set(currsources
  src/GpsMarkerTutorial/View/GpsMarkerTutorialController.cpp
  src/GpsMarkerTutorial/View/GpsMarkerTutorialController.h
  src/GpsMarkerTutorial/View/GpsMarkerTutorialView.cpp
  src/GpsMarkerTutorial/View/GpsMarkerTutorialView.h
  src/GpsMarkerTutorial/View/GpsMarkerTutorialViewIncludes.h
  src/GpsMarkerTutorial/View/GpsMarkerTutorialViewModule.cpp
  src/GpsMarkerTutorial/View/GpsMarkerTutorialViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\GpsMarkerTutorial\\View FILES ${currsources})
