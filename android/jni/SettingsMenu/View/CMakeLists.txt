if(${ANDROID})
set(headers ${headers} jni/SettingsMenu/View
)
set(currsources
  jni/SettingsMenu/View/SettingsMenuView.h
  jni/SettingsMenu/View/SettingsMenuView.cpp
  jni/SettingsMenu/View/SettingsMenuViewModule.h
  jni/SettingsMenu/View/SettingsMenuViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\SettingsMenu\\View FILES ${currsources})
endif(${ANDROID})
