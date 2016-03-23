if(${WINDOWS})
set(headers ${headers} src/WindowsAppThreadAssertions
)
set(currsources
  src/WindowsAppThreadAssertions/WindowsAppThreadAssertionMacros.h
  src/WindowsAppThreadAssertions/WindowsAppThreadAssertions.cpp
  src/WindowsAppThreadAssertions/WindowsAppThreadAssertions.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\WindowsAppThreadAssertions FILES ${currsources})
endif(${WINDOWS})
