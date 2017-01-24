if(${IOS})
set(headers ${headers} ios_src/Helpers
)
set(currsources
  ios_src/Helpers/CMakeLists.txt
  ios_src/Helpers/DeviceHelpers.h
  ios_src/Helpers/DeviceHelpers.mm
  ios_src/Helpers/IconResources.h
  ios_src/Helpers/IconResources.mm
  ios_src/Helpers/ImageHelpers.h
  ios_src/Helpers/ImageHelpers.mm
  ios_src/Helpers/UIColors.h
  ios_src/Helpers/UIColors.mm
  ios_src/Helpers/UIHelpers.h
  ios_src/Helpers/UIHelpers.mm
  ios_src/Helpers/ImmediatePanGestureRecognizer.h
  ios_src/Helpers/ImmediatePanGestureRecognizer.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Helpers FILES ${currsources})
include(ios_src/Helpers/UIAnimation/CMakeLists.txt)
endif(${IOS})
