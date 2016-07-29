set(headers ${headers} ../src/DoubleTapIndoorInteraction/SdkModel
)
set(currsources
  ../src/DoubleTapIndoorInteraction/SdkModel/DoubleTapIndoorInteractionController.cpp
  ../src/DoubleTapIndoorInteraction/SdkModel/DoubleTapIndoorInteractionController.h
  ../src/DoubleTapIndoorInteraction/SdkModel/IDoubleTapIndoorInteractionController.h



)
set(sources ${sources} ${currsources})
source_group(\\src\\DoubleTapIndoorInteraction\\SdkModel FILES ${currsources})
