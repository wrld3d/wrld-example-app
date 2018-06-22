if(${ANDROID})
set(headers ${headers} jni/InteriorsPosition/SdkModel/IndoorAtlas
)
set(currsources
  jni/InteriorsPosition/SdkModel/IndoorAtlas/CMakeLists.txt
  jni/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationInterop.h
  jni/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationInterop.cpp
  jni/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationInteropJni.h
  jni/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationInteropJni.cpp
  jni/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationModule.h
  jni/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\InteriorsPosition\\SdkModel\\IndoorAtlas FILES ${currsources})
endif(${ANDROID})
