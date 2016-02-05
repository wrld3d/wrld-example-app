set(headers ${headers} src/AboutPage
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\AboutPage FILES ${currsources})
include(src/AboutPage/View/CMakeLists.txt)
