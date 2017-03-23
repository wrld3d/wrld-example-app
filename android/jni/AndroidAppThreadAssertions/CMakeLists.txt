if(${ANDROID})
set(headers ${headers} jni/AndroidAppThreadAssertions
)
set(currsources
  jni/AndroidAppThreadAssertions/AndroidAppThreadAssertionMacros.h
  jni/AndroidAppThreadAssertions/AndroidAppThreadAssertions.cpp
  jni/AndroidAppThreadAssertions/AndroidAppThreadAssertions.h
)
set(sources ${sources} ${currsources})
source_group(\\jni\\AndroidAppThreadAssertions FILES ${currsources})
endif(${ANDROID})
