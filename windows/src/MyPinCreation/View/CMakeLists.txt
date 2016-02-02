set(headers ${headers} src/MyPinCreation/View
)
set(currsources
  src/MyPinCreation/View/IMyPinCreationViewModule.h
  src/MyPinCreation/View/MyPinCreationConfirmationView.cpp
  src/MyPinCreation/View/MyPinCreationConfirmationView.h
  src/MyPinCreation/View/MyPinCreationInitiationView.cpp
  src/MyPinCreation/View/MyPinCreationInitiationView.h
  src/MyPinCreation/View/MyPinCreationViewCLI.cpp
  src/MyPinCreation/View/MyPinCreationViewCLI.h
  src/MyPinCreation/View/MyPinCreationViewIncludes.h
  src/MyPinCreation/View/MyPinCreationViewModule.cpp
  src/MyPinCreation/View/MyPinCreationViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "/clr /EHa")

set(sources ${sources} ${currsources})
source_group(\\MyPinCreation\\View FILES ${currsources})
