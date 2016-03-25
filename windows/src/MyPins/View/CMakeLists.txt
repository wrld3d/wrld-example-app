set(headers ${headers} src/MyPins/View
)
set(currsources
  src/MyPins/View/MyPinsMenuOptionFactory.cpp
)

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\MyPins\\View FILES ${currsources})
