set(headers ${headers} src/ModalBackground/SdkModel
)
set(currsources
  src/ModalBackground/SdkModel/IModalBackgroundNativeViewModule.h
  src/ModalBackground/SdkModel/ModalBackgroundNativeModalityObserver.h
  src/ModalBackground/SdkModel/ModalBackgroundNativeView.cpp
  src/ModalBackground/SdkModel/ModalBackgroundNativeView.h
  src/ModalBackground/SdkModel/ModalBackgroundNativeViewModule.cpp
  src/ModalBackground/SdkModel/ModalBackgroundNativeViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\ModalBackground\\SdkModel FILES ${currsources})
