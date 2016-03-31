set(headers ${headers} src/ApplicationConfig
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\ApplicationConfig FILES ${currsources})
include(src/ApplicationConfig/SdkModel/CMakeLists.txt)