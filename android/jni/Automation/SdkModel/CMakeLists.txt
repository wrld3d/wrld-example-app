if(${ANDROID})
  set(headers ${headers} jni/Automation/SdkModel
)
set(currsources
  jni/Automation/SdkModel/AndroidAutomatedScreenshotController.cpp
  jni/Automation/SdkModel/AndroidAutomatedScreenshotController.h
  jni/Automation/SdkModel/ScreengrabScreenshotService.cpp
  jni/Automation/SdkModel/ScreengrabScreenshotService.h
  jni/Automation/SdkModel/AndroidScreenshotService.h
  jni/Automation/SdkModel/AlbumScreenshotService.cpp
  jni/Automation/SdkModel/AlbumScreenshotService.h
  jni/Automation/SdkModel/AlbumScreenshotServiceJni.cpp
  jni/Automation/SdkModel/AlbumScreenshotServiceJni.h
  jni/Automation/SdkModel/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Automation\\SdkModel FILES ${currsources})
endif(${ANDROID})
