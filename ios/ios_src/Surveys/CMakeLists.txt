if(${IOS})
set(headers ${headers} ios_src/Surveys
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Surveys FILES ${currsources})
include(ios_src/Surveys/View/CMakeLists.txt)
endif(${IOS})
