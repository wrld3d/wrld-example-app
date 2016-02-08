if(${IOS})
set(headers ${headers} ios_src/PersistentSettings
)
set(currsources
  ios_src/PersistentSettings/CMakeLists.txt
  ios_src/PersistentSettings/iOSPersistentSettingsModel.h
  ios_src/PersistentSettings/iOSPersistentSettingsModel.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\PersistentSettings FILES ${currsources})
endif(${IOS})
