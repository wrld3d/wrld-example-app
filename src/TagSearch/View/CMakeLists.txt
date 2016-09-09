set(headers ${headers} ../src/TagSearch/View
)
set(currsources
  ../src/TagSearch/View/DesktopTagSearchMenuOption.cpp
  ../src/TagSearch/View/DesktopTagSearchMenuOption.h
  ../src/TagSearch/View/TagSearchMenuOption.cpp
  ../src/TagSearch/View/TagSearchMenuOption.h
  ../src/TagSearch/View/TagSearchMenuOptionFactory.h
  ../src/TagSearch/View/TagSearchModel.cpp
  ../src/TagSearch/View/TagSearchModel.h
  ../src/TagSearch/View/TagSearchModelFactory.h
  ../src/TagSearch/View/TagSearchModelFactory.cpp
  ../src/TagSearch/View/TagSearchRepository.cpp
  ../src/TagSearch/View/TagSearchRepository.h
  ../src/TagSearch/View/TagSearchSectionController.h
  ../src/TagSearch/View/TagSearchSectionController.cpp
  ../src/TagSearch/View/CMakeLists.txt
  ../src/TagSearch/View/ITagSearchRepository.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\TagSearch\\View FILES ${currsources})
