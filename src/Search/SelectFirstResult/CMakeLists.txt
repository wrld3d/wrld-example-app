set(headers ${headers} ../src/Search/SelectFirstResult
)
set(currsources
  ../src/Search/SelectFirstResult/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\SelectFirstResult FILES ${currsources})
include(../src/Search/SelectFirstResult/SdkModel/CMakeLists.txt)
