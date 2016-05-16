set(headers ${headers} ../src/CategorySearch/View
)
set(currsources
  ../src/CategorySearch/View/DesktopCategorySearchMenuOption.cpp
  ../src/CategorySearch/View/DesktopCategorySearchMenuOption.h
  ../src/CategorySearch/View/CategorySearchMenuOption.cpp
  ../src/CategorySearch/View/CategorySearchMenuOption.h
  ../src/CategorySearch/View/CategorySearchMenuOptionFactory.h
  ../src/CategorySearch/View/CategorySearchModel.cpp
  ../src/CategorySearch/View/CategorySearchModel.h
  ../src/CategorySearch/View/CategorySearchRepository.cpp
  ../src/CategorySearch/View/CategorySearchRepository.h
  ../src/CategorySearch/View/CMakeLists.txt
  ../src/CategorySearch/View/ICategorySearchRepository.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\CategorySearch\\View FILES ${currsources})
