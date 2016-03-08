set(headers ${headers} src/CLI
)
set(currsources
  src/CLI/MapImage.cpp
  src/CLI/MapImage.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\CLI FILES ${currsources})
