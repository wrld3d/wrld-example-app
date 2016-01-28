if(${IOS})
set(headers ${headers} ios_src/Options/View
)
set(currsources
  ios_src/Options/View/CMakeLists.txt
  ios_src/Options/View/IOptionsViewModule.h
  ios_src/Options/View/OptionsCacheClearSubView.h
  ios_src/Options/View/OptionsCacheClearSubView.mm
  ios_src/Options/View/OptionsView.h
  ios_src/Options/View/OptionsView.mm
  ios_src/Options/View/OptionsViewIncludes.h
  ios_src/Options/View/OptionsViewInterop.h
  ios_src/Options/View/OptionsViewInterop.mm
  ios_src/Options/View/OptionsViewModule.h
  ios_src/Options/View/OptionsViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Options\\View FILES ${currsources})
endif(${IOS})
