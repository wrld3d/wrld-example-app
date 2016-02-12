set(headers ${headers} ../src/FlattenButton/SdkModel
)
set(currsources
  ../src/FlattenButton/SdkModel/CMakeLists.txt
  ../src/FlattenButton/SdkModel/FlattenButtonModel.cpp
  ../src/FlattenButton/SdkModel/FlattenButtonModel.h
  ../src/FlattenButton/SdkModel/FlattenButtonModelStateChangedObserver.cpp
  ../src/FlattenButton/SdkModel/FlattenButtonModelStateChangedObserver.h
  ../src/FlattenButton/SdkModel/FlattenButtonModule.cpp
  ../src/FlattenButton/SdkModel/FlattenButtonModule.h
  ../src/FlattenButton/SdkModel/FlattenButtonViewStateChangedObserver.cpp
  ../src/FlattenButton/SdkModel/FlattenButtonViewStateChangedObserver.h
  ../src/FlattenButton/SdkModel/IFlattenButtonModel.h
  ../src/FlattenButton/SdkModel/IFlattenButtonModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\FlattenButton\\SdkModel FILES ${currsources})
