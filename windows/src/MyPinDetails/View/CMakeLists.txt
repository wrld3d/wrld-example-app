set(headers ${headers} src/MyPinDetails/View
)
set(currsources_noclr
  src/MyPinDetails/View/MyPinDetailsViewIncludes.h
  src/MyPinDetails/View/MyPinDetailsViewModule.cpp
  src/MyPinDetails/View/MyPinDetailsViewModule.h
  src/MyPinDetails/View/MyPinDetailsView.h
)

set(currsources
  src/MyPinDetails/View/MyPinDetailsViewImpl.cpp
  src/MyPinDetails/View/MyPinDetailsViewImpl.h
  src/MyPinDetails/View/MyPinDetailsView.cpp
  src/MyPinDetails/View/MyPinDetailsViewCLI.cpp
  src/MyPinDetails/View/MyPinDetailsViewCLI.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\MyPinDetails\\View FILES ${currsources} ${currsources_noclr})
