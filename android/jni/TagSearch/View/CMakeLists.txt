set(headers ${headers} jni/TagSearch/View
)
set(currsources
  jni/TagSearch/View/CMakeLists.txt
  jni/TagSearch/View/ITagSearchViewModule.h
  jni/TagSearch/View/TagSearchMenuOptionsFactory.cpp
  jni/TagSearch/View/TagSearchViewIncludes.h  
  jni/TagSearch/View/TagSearchViewModule.h
  jni/TagSearch/View/TagSearchViewModule.cpp
)

set(sources ${sources} ${currsources})
source_group(\\jni\\\\TagSearch\\View FILES ${currsources})
