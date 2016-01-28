if(${IOS})
set(headers ${headers} ios_src/AboutPage/View
)
set(currsources
  ios_src/AboutPage/View/AboutPageView.h
  ios_src/AboutPage/View/AboutPageView.mm
  ios_src/AboutPage/View/AboutPageViewIncludes.h
  ios_src/AboutPage/View/AboutPageViewInterop.h
  ios_src/AboutPage/View/AboutPageViewInterop.mm
  ios_src/AboutPage/View/AboutPageViewModule.h
  ios_src/AboutPage/View/AboutPageViewModule.mm
  ios_src/AboutPage/View/CMakeLists.txt
  ios_src/AboutPage/View/IAboutPageViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\AboutPage\\View FILES ${currsources})
endif(${IOS})
