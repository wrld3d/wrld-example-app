set(headers ${headers} ios_src/TagSearch/View
)
set(currsources
  ios_src/TagSearch/View/CMakeLists.txt
  ios_src/TagSearch/View/TagSearchMenuOptionsFactory.cpp
)

set(sources ${sources} ${currsources})
source_group(\\ios_src\\\\TagSearch\\View FILES ${currsources})
