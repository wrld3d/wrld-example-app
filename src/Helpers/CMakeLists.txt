set(headers ${headers} ../src/Helpers
)
set(currsources
  ../src/Helpers/CMakeLists.txt
  ../src/Helpers/AppColorHelpers.h
  ../src/Helpers/FileHelpers.h
  ../src/Helpers/FileHelpers.cpp
  ../src/Helpers/ImagePathHelpers.h
  ../src/Helpers/InteriorHeightHelpers.cpp
  ../src/Helpers/InteriorHeightHelpers.h
  ../src/Helpers/InteriorNavigationHelpers.cpp
  ../src/Helpers/InteriorNavigationHelpers.h
  ../src/Helpers/IStateMachineState.h
  ../src/Helpers/PinHelpers.h
  ../src/Helpers/SizeHelpers.cpp
  ../src/Helpers/SizeHelpers.h
  ../src/Helpers/StateMachine.cpp
  ../src/Helpers/StateMachine.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Helpers FILES ${currsources})
