if(${IOS})
set(headers ${headers} ios_src/Automation
)
set(currsources
  ios_src/Automation/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Automation FILES ${currsources})
include(ios_src/Automation/SdkModel/CMakeLists.txt)
endif(${IOS})
