set(headers ${headers} ../src/Search/Swallow/View
)
set(currsources
  ../src/Search/Swallow/View/SwallowCategoryMenuOption.cpp
  ../src/Search/Swallow/View/SwallowCategoryMenuOption.h
  ../src/Search/Swallow/View/SwallowOfficeResultMenuOption.cpp
  ../src/Search/Swallow/View/SwallowOfficeResultMenuOption.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Swallow\\View FILES ${currsources})
