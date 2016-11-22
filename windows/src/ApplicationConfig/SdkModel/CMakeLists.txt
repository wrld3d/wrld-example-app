set(headers ${headers} src/ApplicationConfig/SdkModel
)
set(currsources
  src/ApplicationConfig/SdkModel/WindowsApplicationConfigurationVersionProvider.h
  src/ApplicationConfig/SdkModel/WindowsApplicationConfigurationVersionProvider.cpp
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\ApplicationConfig\\SdkModel FILES ${currsources})