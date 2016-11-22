set(headers ${headers} src/PersistentSettings
)
set(currsources_noclr
  src/PersistentSettings/WindowsPersistentSettingsModel.h
)

set(currsources
  src/PersistentSettings/WindowsPersistentSettings.h
  src/PersistentSettings/WindowsPersistentSettingsModelImpl.cpp
  src/PersistentSettings/WindowsPersistentSettingsModelImpl.h
  src/PersistentSettings/WindowsPersistentSettingsModel.cpp
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\PersistentSettings FILES ${currsources} ${currsources_noclr})
