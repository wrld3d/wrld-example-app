set(headers ${headers} src/AppCamera/Helpers
)
set(currsources
  src/AppCamera/Helpers/AppCameraHelpers.cpp
  src/AppCamera/Helpers/AppCameraHelpers.h
)
set(sources ${sources} ${currsources})
source_group(\\AppCamera\\Helpers FILES ${currsources})
