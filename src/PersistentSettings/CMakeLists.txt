set(headers ${headers} ../src/PersistentSettings
)
set(currsources
  ../src/PersistentSettings/CMakeLists.txt
  ../src/PersistentSettings/IPersistentSettingsModel.h
  ../src/PersistentSettings/PersistentSettings.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\PersistentSettings FILES ${currsources})
