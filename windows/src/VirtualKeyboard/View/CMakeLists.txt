set(headers ${headers} src/VirtualKeyboard/View
)
set(currsources
  src/VirtualKeyboard/View/CMakeLists.txt
  src/VirtualKeyboard/View/VirtualKeyboardView.cpp
  src/VirtualKeyboard/View/VirtualKeyboardView.h
  src/VirtualKeyboard/View/VirtualKeyboardCLI.cpp
  src/VirtualKeyboard/View/VirtualKeyboardCLI.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\VirtualKeyboard\\View FILES ${currsources})
