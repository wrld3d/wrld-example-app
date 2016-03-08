set(headers ${headers} src/ModalBackground/View
)
set(currsources
  src/ModalBackground/View/IModalBackgroundViewModule.h
  src/ModalBackground/View/ModalBackgroundAggregateView.cpp
  src/ModalBackground/View/ModalBackgroundAggregateView.h
  src/ModalBackground/View/ModalBackgroundViewModule.cpp
  src/ModalBackground/View/ModalBackgroundViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\ModalBackground\\View FILES ${currsources})
