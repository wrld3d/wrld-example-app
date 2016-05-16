set(headers ${headers} src/CategorySearch/View
)
set(currsources
  src/CategorySearch/View/CategorySearchMenuOptionsFactory.cpp
)

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\CategorySearch\\View FILES ${currsources})
