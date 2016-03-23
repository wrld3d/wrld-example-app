set(headers ${headers} src/Options/SdkModel
)
set(currsources
  src/Options/SdkModel/ClearCacheMessageHandler.cpp
  src/Options/SdkModel/ClearCacheMessageHandler.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Options\\SdkModel FILES ${currsources})
