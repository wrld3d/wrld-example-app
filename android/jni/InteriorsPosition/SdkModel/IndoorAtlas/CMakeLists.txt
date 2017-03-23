if(${ANDROID})
set(headers ${headers} jni/InteriorsPosition/SdkModel/IndoorAtlas
)
set(currsources
  jni/InteriorsPosition/SdkModel/IndoorAtlas/CMakeLists.txt
  jni/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationManager.h
  jni/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationManager.cpp
  jni/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationManagerJni.h
  jni/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationManagerJni.cpp
  jni/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationModule.h
  jni/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\InteriorsPosition\\SdkModel\\IndoorAtlas FILES ${currsources})
endif(${ANDROID})
