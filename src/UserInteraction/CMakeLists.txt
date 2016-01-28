set(headers ${headers} ../src/UserInteraction
)
set(currsources
  ../src/UserInteraction/CMakeLists.txt
  ../src/UserInteraction/UserInteraction.h
  ../src/UserInteraction/UserInteractionEnabledChangedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\UserInteraction FILES ${currsources})
include(../src/UserInteraction/SdkModel/CMakeLists.txt)
