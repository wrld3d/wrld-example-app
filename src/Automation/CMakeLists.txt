set(headers ${headers} ../src/Automation
)
set(currsources
  ../src/Automation/CMakeLists.txt
  ../src/Automation/AutomatedScreenshotController.cpp
  ../src/Automation/AutomatedScreenshotController.h
  ../src/Automation/NullScreenshotService.cpp
  ../src/Automation/NullScreenshotService.h
  ../src/Automation/IScreenshotService.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Automation FILES ${currsources})
