set(headers ${headers} ../src/MyPins/View
)
set(currsources
  ../src/MyPins/View/CMakeLists.txt
  ../src/MyPins/View/MyPinAddedToMenuObserver.cpp
  ../src/MyPins/View/MyPinAddedToMenuObserver.h
  ../src/MyPins/View/MyPinMenuOption.h
  ../src/MyPins/View/MyPinMenuOptionFactory.h
  ../src/MyPins/View/MyPinRemovedFromMenuObserver.cpp
  ../src/MyPins/View/MyPinRemovedFromMenuObserver.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\MyPins\\View FILES ${currsources})
