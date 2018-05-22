if(${ANDROID})
set(headers ${headers} jni/SearchProviders
)
set(currsources
  jni/SearchProviders/CMakeLists.txt
  jni/SearchProviders/MyTestSearchProvider.cpp
  jni/SearchProviders/MyTestSearchProvider.h
  jni/SearchProviders/SearchProvidersJni.cpp
  jni/SearchProviders/SearchProvidersJni.h
)
set(sources ${sources} ${currsources})
source_group(\\jni\\SearchProviders FILES ${currsources})
endif(${ANDROID})
