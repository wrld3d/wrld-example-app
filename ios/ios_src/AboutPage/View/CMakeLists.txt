if(${IOS})
set(headers ${headers} ios/ios_src/AboutPage/View
)
set(currsources
  ios/ios_src/AboutPage/View/AboutPageView.h
  ios/ios_src/AboutPage/View/AboutPageView.mm
  ios/ios_src/AboutPage/View/AboutPageViewIncludes.h
  ios/ios_src/AboutPage/View/AboutPageViewInterop.h
  ios/ios_src/AboutPage/View/AboutPageViewInterop.mm
  ios/ios_src/AboutPage/View/AboutPageViewModule.h
  ios/ios_src/AboutPage/View/AboutPageViewModule.mm
  ios/ios_src/AboutPage/View/IAboutPageViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\_src\\AboutPage\\View FILES ${currsources})
endif(${IOS})
