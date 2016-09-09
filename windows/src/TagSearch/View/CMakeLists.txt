set(headers ${headers} src/TagSearch/View
)
set(currsources
  src/TagSearch/View/CMakeLists.txt
  src/TagSearch/View/ITagSearchViewModule.h
  src/TagSearch/View/TagSearchMenuOptionsFactory.cpp
  src/TagSearch/View/TagSearchViewIncludes.h  
  src/TagSearch/View/TagSearchViewModule.cpp
  src/TagSearch/View/TagSearchViewModule.h  
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\TagSearch\\View FILES ${currsources})
