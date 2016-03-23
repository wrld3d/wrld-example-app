set(headers ${headers} src/PersistentSettings
)
set(currsources
  src/PersistentSettings/WindowsPersistentSettings.h
  src/PersistentSettings/WindowsPersistentSettingsModel.cpp
  src/PersistentSettings/WindowsPersistentSettingsModel.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\PersistentSettings FILES ${currsources})
