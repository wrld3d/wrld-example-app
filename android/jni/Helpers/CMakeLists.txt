if(${ANDROID})
set(headers ${headers} jni/Helpers 
)
set(currsources
  jni/Helpers/AndroidImagePathHelpers.h
  jni/Helpers/ImagePathHelpers.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Helpers FILES ${currsources})
endif(${ANDROID})
