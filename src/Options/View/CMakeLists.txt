set(headers ${headers} ../src/Options/View
)
set(currsources
  ../src/Options/View/CMakeLists.txt
  ../src/Options/View/CompletedCacheClearMessageHandler.cpp
  ../src/Options/View/CompletedCacheClearMessageHandler.h
  ../src/Options/View/IOptionsView.h
  ../src/Options/View/IOptionsViewModel.h
  ../src/Options/View/Options.h
  ../src/Options/View/OptionsController.cpp
  ../src/Options/View/OptionsController.h
  ../src/Options/View/OptionsOpenableControl.cpp
  ../src/Options/View/OptionsOpenableControl.h
  ../src/Options/View/OptionsViewModel.cpp
  ../src/Options/View/OptionsViewModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Options\\View FILES ${currsources})
