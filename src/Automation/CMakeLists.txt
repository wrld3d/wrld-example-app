set(headers ${headers} ../src/Automation
)
set(currsources
  ../src/Automation/CMakeLists.txt
  ../src/Automation/AutomatedScreenshotController.cpp
  ../src/Automation/AutomatedScreenshotController.h
  ../src/Automation/NullScreenshotService.cpp
  ../src/Automation/NullScreenshotService.h
  ../src/Automation/IScreenshotService.h
  ../src/Automation/SurfaceScreenshotService.cpp
  ../src/Automation/SurfaceScreenshotService.h
  ../src/Automation/ClosePoiMessage.cpp
  ../src/Automation/ClosePoiMessage.h
  ../src/Automation/SelectMenuItemMessage.cpp
  ../src/Automation/SelectMenuItemMessage.h
  ../src/Automation/OpenSearchMenuSectionMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Automation FILES ${currsources})
