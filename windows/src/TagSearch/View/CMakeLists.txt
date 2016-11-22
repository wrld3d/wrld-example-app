set(headers ${headers} src/TagSearch/View
)
set(currsources
  src/TagSearch/View/CMakeLists.txt
  src/TagSearch/View/TagSearchMenuOptionsFactory.cpp
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\TagSearch\\View FILES ${currsources})
