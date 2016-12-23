set(headers ${headers} ../src/InteriorsPosition
)
set(currsources
  ../src/InteriorsPosition/CMakeLists.txt
  ../src/InteriorsPosition/InteriorsPosition.h
  ../src/InteriorsPosition/IPSConfigurationParser.cpp
  ../src/InteriorsPosition/IPSConfigurationParser.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsPosition FILES ${currsources})
include(../src/InteriorsPosition/SdkModel/CMakeLists.txt)
