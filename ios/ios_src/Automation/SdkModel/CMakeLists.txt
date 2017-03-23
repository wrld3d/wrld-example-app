if(${IOS})
  set(headers ${headers} ios_src/Automation/SdkModel
)
set(currsources
  ios_src/Automation/SdkModel/CMakeLists.txt
  ios_src/Automation/SdkModel/SnapshotScreenshotService.h
  ios_src/Automation/SdkModel/SnapshotScreenshotService.cpp
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Automation\\SdkModel FILES ${currsources})
endif(${IOS})
