if(${ANDROID})
set(headers ${headers} jni/SettingsMenu
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\jni\\SettingsMenu FILES ${currsources})
include(jni/SettingsMenu/View/CMakeLists.txt)
endif(${ANDROID})
