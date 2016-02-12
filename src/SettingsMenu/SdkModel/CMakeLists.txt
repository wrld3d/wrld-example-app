set(headers ${headers} ../src/SettingsMenu/SdkModel
)
set(currsources
  ../src/SettingsMenu/SdkModel/CMakeLists.txt
  ../src/SettingsMenu/SdkModel/ISettingsMenuModule.h
  ../src/SettingsMenu/SdkModel/SettingsMenuModule.cpp
  ../src/SettingsMenu/SdkModel/SettingsMenuModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SettingsMenu\\SdkModel FILES ${currsources})
