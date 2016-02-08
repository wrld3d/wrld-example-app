set(headers ${headers} src/SecondaryMenu
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\SecondaryMenu FILES ${currsources})
include(src/SecondaryMenu/View/CMakeLists.txt)
