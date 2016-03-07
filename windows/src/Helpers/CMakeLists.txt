set(headers ${headers} src/Helpers
)
set(currsources
  src/Helpers/ImagePathHelpers.cpp
  src/Helpers/ReflectionHelpers.h
  src/Helpers/WindowsImagePathHelpers.h
)

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Helpers FILES ${currsources})
