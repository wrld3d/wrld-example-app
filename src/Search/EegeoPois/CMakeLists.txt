set(headers ${headers} ../src/Search/EegeoPois
)
set(currsources
  ../src/Search/EegeoPois/CMakeLists.txt
  ../src/Search/EegeoPois/EegeoPois.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\EegeoPois FILES ${currsources})
include(../src/Search/EegeoPois/SdkModel/CMakeLists.txt)
