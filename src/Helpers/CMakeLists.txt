set(headers ${headers} ../src/Helpers
)
set(currsources
  ../src/Helpers/AppColorHelpers.h
  ../src/Helpers/CMakeLists.txt
  ../src/Helpers/ImagePathHelpers.h
  ../src/Helpers/InteriorHeightHelpers.cpp
  ../src/Helpers/InteriorHeightHelpers.h
  ../src/Helpers/IStateMachineState.h
  ../src/Helpers/SizeHelpers.cpp
  ../src/Helpers/SizeHelpers.h
  ../src/Helpers/StateMachine.cpp
  ../src/Helpers/StateMachine.h
  ../src/Helpers/IpAddressHelpers.cpp
  ../src/Helpers/IpAddressHelpers.h
  ../src/Helpers/JsonPrintHelper.cpp
  ../src/Helpers/JsonPrintHelper.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Helpers FILES ${currsources})
