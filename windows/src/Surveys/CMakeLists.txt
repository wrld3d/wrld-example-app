set(headers ${headers} src/Surveys
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Surveys FILES ${currsources})
include(src/Surveys/View/CMakeLists.txt)
