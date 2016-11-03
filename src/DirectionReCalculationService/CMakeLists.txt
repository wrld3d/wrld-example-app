set(headers ${headers} ../src/DirectionReCalculationService
)
set(currsources
  ../src/DirectionReCalculationService/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\DirectionReCalculationService FILES ${currsources})
include(../src/DirectionReCalculationService/SdkModel/CMakeLists.txt)