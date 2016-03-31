set(headers ${headers} src/ApplicationConfig/SdkModel
)
set(currsources
  src/ApplicationConfig/SdkModel/WindowsApplicationConfigurationVersionProvider.h
  src/ApplicationConfig/SdkModel/WindowsApplicationConfigurationVersionProvider.cpp
)


set(sources ${sources} ${currsources})
source_group(\\windows_src\\ApplicationConfig\\SdkModel FILES ${currsources})