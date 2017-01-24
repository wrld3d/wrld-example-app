set(headers ${headers} src/AdminLogin
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\AdminLogin FILES ${currsources})
include(src/AdminLogin/View/CMakeLists.txt)
