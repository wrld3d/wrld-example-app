set(headers ${headers} src/PersistentSettings
)
set(currsources
  src/PersistentSettings/IPersistentSettingsModel.h
  src/PersistentSettings/PersistentSettings.h
)
set(sources ${sources} ${currsources})
source_group(\\PersistentSettings FILES ${currsources})
