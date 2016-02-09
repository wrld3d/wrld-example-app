set(headers ${headers} ../src/ReportPinsVisibilityMasking
)
set(currsources
  ../src/ReportPinsVisibilityMasking/ReportPinsVisibilityMasking.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\ReportPinsVisibilityMasking FILES ${currsources})
include(../src/ReportPinsVisibilityMasking/SdkModel/CMakeLists.txt)
