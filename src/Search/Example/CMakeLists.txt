set(headers ${headers} ../src/Search/Example
)
set(currsources
  ../src/Search/Example/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Example FILES ${currsources})
include(../src/Search/Example/SdkModel/CMakeLists.txt)
