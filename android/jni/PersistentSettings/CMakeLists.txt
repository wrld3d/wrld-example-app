if(${ANDROID})
set(headers ${headers} jni/PersistentSettings
)
set(currsources
  jni/PersistentSettings/CMakeLists.txt
  jni/PersistentSettings/AndroidPersistentSettingsModel.h
  jni/PersistentSettings/AndroidPersistentSettingsModel.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\PersistentSettings FILES ${currsources})
endif(${ANDROID})
