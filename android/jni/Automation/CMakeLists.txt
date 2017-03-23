if(${ANDROID})
set(headers ${headers} jni/Automation
)
set(currsources
  jni/Automation/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Automation FILES ${currsources})
include(jni/Automation/SdkModel/CMakeLists.txt)
endif(${ANDROID})
