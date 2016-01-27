if(${IOS})
set(headers ${headers} ios/ios_src/ModalBackground/View
)
set(currsources
  ios/ios_src/ModalBackground/View/IModalBackgroundViewModule.h
  ios/ios_src/ModalBackground/View/ModalBackgroundView.h
  ios/ios_src/ModalBackground/View/ModalBackgroundView.mm
  ios/ios_src/ModalBackground/View/ModalBackgroundViewIncludes.h
  ios/ios_src/ModalBackground/View/ModalBackgroundViewInterop.h
  ios/ios_src/ModalBackground/View/ModalBackgroundViewInterop.mm
  ios/ios_src/ModalBackground/View/ModalBackgroundViewModule.h
  ios/ios_src/ModalBackground/View/ModalBackgroundViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\ModalBackground\\View FILES ${currsources})
endif(${IOS})
