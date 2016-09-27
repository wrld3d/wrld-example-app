set(headers ${headers} ../src/DirectionResultSection
)
set(currsources
  ../src/DirectionResultSection/CMakeLists.txt
  ../src/DirectionResultSection/DirectionResultSection.h
  ../src/DirectionResultSection/DirectionQueryResponseReceivedMessage.cpp
  ../src/DirectionResultSection/DirectionQueryResponseReceivedMessage.h
  ../src/DirectionResultSection/DirectionResultSectionItemSelectedMessage.cpp
  ../src/DirectionResultSection/DirectionResultSectionItemSelectedMessage.h

)
set(sources ${sources} ${currsources})
source_group(\\src\\DirectionResultSection FILES ${currsources})
include(../src/DirectionResultSection/View/CMakeLists.txt)
include(../src/DirectionResultSection/SdkModel/CMakeLists.txt)