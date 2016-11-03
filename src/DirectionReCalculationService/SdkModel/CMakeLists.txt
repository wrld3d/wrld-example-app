set(headers ${headers} ../src/DirectionReCalculationService/SdkModel
)
set(currsources
  ../src/DirectionReCalculationService/SdkModel/CMakeLists.txt
  ../src/DirectionReCalculationService/SdkModel/DirectionReCalculationService.h
  ../src/DirectionReCalculationService/SdkModel/DirectionReCalculationService.cpp

)
set(sources ${sources} ${currsources})
source_group(\\src\\DirectionReCalculationService\\SdkModel FILES ${currsources})