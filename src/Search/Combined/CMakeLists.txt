set(headers ${headers} src/Search/Combined
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\Search\\Combined FILES ${currsources})
include(src/Search/Combined/SdkModel/CMakeLists.txt)
