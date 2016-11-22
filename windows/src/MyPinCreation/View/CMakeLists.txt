set(headers ${headers} src/MyPinCreation/View
)
set(currsources_noclr
  src/MyPinCreation/View/MyPinCreationViewIncludes.h
  src/MyPinCreation/View/MyPinCreationViewModule.cpp
  src/MyPinCreation/View/MyPinCreationViewModule.h
  src/MyPinCreation/View/MyPinCreationInitiationView.h
  src/MyPinCreation/View/MyPinCreationConfirmationView.h
)
set(currsources
  src/MyPinCreation/View/MyPinCreationConfirmationViewImpl.h
  src/MyPinCreation/View/MyPinCreationInitiationViewImpl.h
  src/MyPinCreation/View/MyPinCreationConfirmationViewImpl.cpp
  src/MyPinCreation/View/MyPinCreationInitiationViewImpl.cpp
  src/MyPinCreation/View/MyPinCreationConfirmationView.cpp
  src/MyPinCreation/View/MyPinCreationInitiationView.cpp
  src/MyPinCreation/View/MyPinCreationViewCLI.cpp
  src/MyPinCreation/View/MyPinCreationViewCLI.h
  src/MyPinCreation/View/MyPinCreationViewIncludes.h
  src/MyPinCreation/View/MyPinCreationViewModule.cpp
  src/MyPinCreation/View/MyPinCreationViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\MyPinCreation\\View FILES ${currsources} ${currsources_noclr})
