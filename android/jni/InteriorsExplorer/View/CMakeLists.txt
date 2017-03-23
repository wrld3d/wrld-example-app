if(${ANDROID})
set(headers ${headers} jni/InteriorsExplorer/View
)
set(currsources
  jni/InteriorsExplorer/View/CMakeLists.txt
  jni/InteriorsExplorer/View/IInteriorsExplorerViewModule.h
  jni/InteriorsExplorer/View/InteriorsExplorerView.h
  jni/InteriorsExplorer/View/InteriorsExplorerView.cpp
  jni/InteriorsExplorer/View/InteriorsExplorerViewIncludes.h
  jni/InteriorsExplorer/View/InteriorsExplorerViewJni.h
  jni/InteriorsExplorer/View/InteriorsExplorerViewJni.cpp
  jni/InteriorsExplorer/View/InteriorsExplorerViewModule.h
  jni/InteriorsExplorer/View/InteriorsExplorerViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\InteriorsExplorer\\View FILES ${currsources})
endif(${ANDROID})
