set(headers ${headers} src/MyPinCreationDetails/View
)
set(currsources
  src/MyPinCreationDetails/View/IMyPinCreationDetailsViewModule.h
  src/MyPinCreationDetails/View/MyPinCreationDetailsView.cpp
  src/MyPinCreationDetails/View/MyPinCreationDetailsView.h
  src/MyPinCreationDetails/View/MyPinCreationDetailsViewCLI.cpp
  src/MyPinCreationDetails/View/MyPinCreationDetailsViewCLI.h
  src/MyPinCreationDetails/View/MyPinCreationDetailsViewIncludes.h
  src/MyPinCreationDetails/View/MyPinCreationDetailsViewModule.cpp
  src/MyPinCreationDetails/View/MyPinCreationDetailsViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\MyPinCreationDetails\\View FILES ${currsources})
