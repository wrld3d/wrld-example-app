set(headers ${headers} src/MyPinDetails/View
)
set(currsources
  src/MyPinDetails/View/IMyPinDetailsViewModule.h
  src/MyPinDetails/View/MyPinDetailsView.cpp
  src/MyPinDetails/View/MyPinDetailsView.h
  src/MyPinDetails/View/MyPinDetailsViewCLI.cpp
  src/MyPinDetails/View/MyPinDetailsViewCLI.h
  src/MyPinDetails/View/MyPinDetailsViewIncludes.h
  src/MyPinDetails/View/MyPinDetailsViewModule.cpp
  src/MyPinDetails/View/MyPinDetailsViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\MyPinDetails\\View FILES ${currsources})
