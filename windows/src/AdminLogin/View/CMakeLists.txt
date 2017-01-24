set(headers ${headers} src/AdminLogin/View
)
set(currsources
  src/AdminLogin/View/CMakeLists.txt
  src/AdminLogin/View/AdminLoginView.cpp
  src/AdminLogin/View/AdminLoginView.h
  src/AdminLogin/View/AdminLoginCLI.cpp
  src/AdminLogin/View/AdminLoginCLI.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\AdminLogin\\View FILES ${currsources})
