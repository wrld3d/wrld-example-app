if(${ANDROID})
set(headers ${headers} jni/Compass/View
)
set(currsources
  jni/Compass/View/CMakeLists.txt
  jni/Compass/View/CompassView.h
  jni/Compass/View/CompassView.cpp
  jni/Compass/View/CompassViewIncludes.h
  jni/Compass/View/CompassJni.h
  jni/Compass/View/CompassJni.cpp
  jni/Compass/View/CompassViewModule.h
  jni/Compass/View/CompassViewModule.cpp
  jni/Compass/View/ICompassViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Compass\\View FILES ${currsources})
endif(${ANDROID})
