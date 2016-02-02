set(headers ${headers} src/Helpers
)
set(currsources
  src/Helpers/ImagePathHelpers.cpp
  src/Helpers/ReflectionHelpers.h
  src/Helpers/WindowsImagePathHelpers.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "/clr /EHa")

set(sources ${sources} ${currsources})
source_group(\\Helpers FILES ${currsources})
