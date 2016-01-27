if(${IOS})
set(headers ${headers} ios/ios_src/Options/View
)
set(currsources
  ios/ios_src/Options/View/IOptionsViewModule.h
  ios/ios_src/Options/View/OptionsCacheClearSubView.h
  ios/ios_src/Options/View/OptionsCacheClearSubView.mm
  ios/ios_src/Options/View/OptionsView.h
  ios/ios_src/Options/View/OptionsView.mm
  ios/ios_src/Options/View/OptionsViewIncludes.h
  ios/ios_src/Options/View/OptionsViewInterop.h
  ios/ios_src/Options/View/OptionsViewInterop.mm
  ios/ios_src/Options/View/OptionsViewModule.h
  ios/ios_src/Options/View/OptionsViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Options\\View FILES ${currsources})
endif(${IOS})
