set(headers ${headers} ios_src/TagSearch/View
)
set(currsources
  ios_src/TagSearch/View/CMakeLists.txt
  ios_src/TagSearch/View/ITagSearchViewModule.h
  ios_src/TagSearch/View/TagSearchMenuOptionsFactory.cpp
  ios_src/TagSearch/View/TagSearchViewIncludes.h  
  ios_src/TagSearch/View/TagSearchViewModule.h
  ios_src/TagSearch/View/TagSearchViewModule.mm
)

set(sources ${sources} ${currsources})
source_group(\\ios_src\\\\TagSearch\\View FILES ${currsources})
