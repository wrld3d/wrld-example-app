if(${IOS})
set(headers ${headers} ios/ios_src/PersistentSettings
)
set(currsources
  ios/ios_src/PersistentSettings/iOSPersistentSettingsModel.h
  ios/ios_src/PersistentSettings/iOSPersistentSettingsModel.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\PersistentSettings FILES ${currsources})
endif(${IOS})
