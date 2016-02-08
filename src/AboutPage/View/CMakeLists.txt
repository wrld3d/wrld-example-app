set(headers ${headers} ../src/AboutPage/View
)
set(currsources
  ../src/AboutPage/View/AboutPage.h
  ../src/AboutPage/View/AboutPageController.cpp
  ../src/AboutPage/View/AboutPageController.h
  ../src/AboutPage/View/AboutPageModule.cpp
  ../src/AboutPage/View/AboutPageModule.h
  ../src/AboutPage/View/AboutPageOpenableControl.cpp
  ../src/AboutPage/View/AboutPageOpenableControl.h
  ../src/AboutPage/View/AboutPageViewModel.cpp
  ../src/AboutPage/View/AboutPageViewModel.h
  ../src/AboutPage/View/CMakeLists.txt
  ../src/AboutPage/View/IAboutPageModule.h
  ../src/AboutPage/View/IAboutPageView.h
  ../src/AboutPage/View/IAboutPageViewModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\AboutPage\\View FILES ${currsources})
