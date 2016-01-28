if(${IOS})
set(headers ${headers} ios_src/ModalBackground/View
)
set(currsources
  ios_src/ModalBackground/View/CMakeLists.txt
  ios_src/ModalBackground/View/IModalBackgroundViewModule.h
  ios_src/ModalBackground/View/ModalBackgroundView.h
  ios_src/ModalBackground/View/ModalBackgroundView.mm
  ios_src/ModalBackground/View/ModalBackgroundViewIncludes.h
  ios_src/ModalBackground/View/ModalBackgroundViewInterop.h
  ios_src/ModalBackground/View/ModalBackgroundViewInterop.mm
  ios_src/ModalBackground/View/ModalBackgroundViewModule.h
  ios_src/ModalBackground/View/ModalBackgroundViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\ModalBackground\\View FILES ${currsources})
endif(${IOS})
