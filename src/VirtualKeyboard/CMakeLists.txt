set(headers ${headers} ../src/VirtualKeyboard
)
set(currsources
  ../src/VirtualKeyboard/CMakeLists.txt
  ../src/VirtualKeyboard/VirtualKeyboard.h
  ../src/VirtualKeyboard/VirtualKeyboardStateChangedMessage.h
  ../src/VirtualKeyboard/VirtualKeyboardStateChangedMessage.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\VirtualKeyboard FILES ${currsources})
