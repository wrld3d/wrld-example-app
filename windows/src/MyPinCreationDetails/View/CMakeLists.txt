set(headers ${headers} src/MyPinCreationDetails/View
)
set(currsources_noclr
  src/MyPinCreationDetails/View/MyPinCreationDetailsViewIncludes.h
  src/MyPinCreationDetails/View/MyPinCreationDetailsViewModule.cpp
  src/MyPinCreationDetails/View/MyPinCreationDetailsViewModule.h
  src/MyPinCreationDetails/View/MyPinCreationDetailsView.h
)
set(currsources
  src/MyPinCreationDetails/View/MyPinCreationDetailsViewImpl.cpp
  src/MyPinCreationDetails/View/MyPinCreationDetailsViewImpl.h
  src/MyPinCreationDetails/View/MyPinCreationDetailsView.cpp
  src/MyPinCreationDetails/View/MyPinCreationDetailsViewCLI.cpp
  src/MyPinCreationDetails/View/MyPinCreationDetailsViewCLI.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\MyPinCreationDetails\\View FILES ${currsources} ${currsources_noclr})
