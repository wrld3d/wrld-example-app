if(${IOS})
  set(headers ${headers} ios_src/Automation/SdkModel
)
set(currsources
  ios_src/Automation/SdkModel/CMakeLists.txt
  ios_src/Automation/SdkModel/SnapshotScreenshotService.h
  ios_src/Automation/SdkModel/SnapshotScreenshotService.cpp
  ios_src/Automation/SdkModel/iOSScreenshotService.h
  ios_src/Automation/SdkModel/iOSAutomatedScreenshotController.h
  ios_src/Automation/SdkModel/iOSAutomatedScreenshotController.mm
  ios_src/Automation/SdkModel/SnapshotMessageConstants.h
  ios_src/Automation/SdkModel/AlbumScreenshotService.h
  ios_src/Automation/SdkModel/AlbumScreenshotService.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Automation\\SdkModel FILES ${currsources})
endif(${IOS})
