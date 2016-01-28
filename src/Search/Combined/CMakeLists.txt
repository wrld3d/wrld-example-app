set(headers ${headers} ../src/Search/Combined
)
set(currsources
  ../src/Search/Combined/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Combined FILES ${currsources})
include(../src/Search/Combined/SdkModel/CMakeLists.txt)
