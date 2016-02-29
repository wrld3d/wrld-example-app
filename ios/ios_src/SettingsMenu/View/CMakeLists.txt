if(${IOS})
set(headers ${headers} ios_src/SettingsMenu/View
)
set(currsources
  ios_src/SettingsMenu/View/ISettingsMenuViewModule.h
  ios_src/SettingsMenu/View/SettingsMenuView.h
  ios_src/SettingsMenu/View/SettingsMenuView.mm
  ios_src/SettingsMenu/View/SettingsMenuViewIncludes.h
  ios_src/SettingsMenu/View/SettingsMenuViewInterop.h
  ios_src/SettingsMenu/View/SettingsMenuViewModule.h
  ios_src/SettingsMenu/View/SettingsMenuViewModule.mm
  ios_src/SettingsMenu/View/SettingsTableDataProvider.h
  ios_src/SettingsMenu/View/SettingsTableDataProvider.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SettingsMenu\\View FILES ${currsources})
endif(${IOS})
