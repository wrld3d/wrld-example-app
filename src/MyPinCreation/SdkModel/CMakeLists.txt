set(headers ${headers} ../src/MyPinCreation/SdkModel
)
set(currsources
  ../src/MyPinCreation/SdkModel/CMakeLists.txt
  ../src/MyPinCreation/SdkModel/IMyPinCreationModel.h
  ../src/MyPinCreation/SdkModel/IMyPinCreationModule.h
  ../src/MyPinCreation/SdkModel/MyPinCreationModel.cpp
  ../src/MyPinCreation/SdkModel/MyPinCreationModel.h
  ../src/MyPinCreation/SdkModel/MyPinCreationModelObserver.cpp
  ../src/MyPinCreation/SdkModel/MyPinCreationModelObserver.h
  ../src/MyPinCreation/SdkModel/MyPinCreationModule.cpp
  ../src/MyPinCreation/SdkModel/MyPinCreationModule.h
  ../src/MyPinCreation/SdkModel/MyPinCreationViewSavePinHandler.cpp
  ../src/MyPinCreation/SdkModel/MyPinCreationViewSavePinHandler.h
  ../src/MyPinCreation/SdkModel/MyPinCreationViewStateChangedHandler.cpp
  ../src/MyPinCreation/SdkModel/MyPinCreationViewStateChangedHandler.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\MyPinCreation\\SdkModel FILES ${currsources})
