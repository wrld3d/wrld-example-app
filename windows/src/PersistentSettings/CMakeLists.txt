set(headers ${headers} src/PersistentSettings
)
set(currsources
  src/PersistentSettings/WindowsPersistentSettings.h
  src/PersistentSettings/WindowsPersistentSettingsModel.cpp
  src/PersistentSettings/WindowsPersistentSettingsModel.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "/clr /EHa")

set(sources ${sources} ${currsources})
source_group(\\PersistentSettings FILES ${currsources})
