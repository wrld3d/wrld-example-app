set(headers ${headers} src/ModalBackground
)
set(currsources
  src/ModalBackground/ModalBackgroundViewIncludes.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\ModalBackground FILES ${currsources})
include(src/ModalBackground/SdkModel/CMakeLists.txt)
include(src/ModalBackground/View/CMakeLists.txt)
