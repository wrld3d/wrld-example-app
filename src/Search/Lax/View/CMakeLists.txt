set(headers ${headers} ../src/Search/Lax/View
)
set(currsources
  ../src/Search/Lax/View/LaxCategoryMenuOption.cpp
  ../src/Search/Lax/View/LaxCategoryMenuOption.h
  ../src/Search/Lax/View/LaxOfficeResultMenuOption.cpp
  ../src/Search/Lax/View/LaxOfficeResultMenuOption.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Lax\\View FILES ${currsources})
