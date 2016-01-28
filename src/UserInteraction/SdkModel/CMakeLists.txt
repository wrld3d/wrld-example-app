set(headers ${headers} ../src/UserInteraction/SdkModel
)
set(currsources
  ../src/UserInteraction/SdkModel/CMakeLists.txt
  ../src/UserInteraction/SdkModel/UserInteractionController.cpp
  ../src/UserInteraction/SdkModel/UserInteractionController.h
  ../src/UserInteraction/SdkModel/UserInteractionEnabledObserver.cpp
  ../src/UserInteraction/SdkModel/UserInteractionEnabledObserver.h
  ../src/UserInteraction/SdkModel/UserInteractionModel.cpp
  ../src/UserInteraction/SdkModel/UserInteractionModel.h
  ../src/UserInteraction/SdkModel/UserInteractionModule.cpp
  ../src/UserInteraction/SdkModel/UserInteractionModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\UserInteraction\\SdkModel FILES ${currsources})
