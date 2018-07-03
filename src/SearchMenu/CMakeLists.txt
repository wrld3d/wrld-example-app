set(headers ${headers} ../src/SearchMenu
)
set(currsources
  ../src/SearchMenu/AutocompleteSuggestionsCancelledMessage.cpp
  ../src/SearchMenu/AutocompleteSuggestionsCancelledMessage.h
  ../src/SearchMenu/AutocompleteSuggestionsMessage.cpp
  ../src/SearchMenu/AutocompleteSuggestionsMessage.h
  ../src/SearchMenu/CMakeLists.txt
  ../src/SearchMenu/SearchMenu.h
  ../src/SearchMenu/SearchMenuPerformedSearchMessage.cpp
  ../src/SearchMenu/SearchMenuPerformedSearchMessage.h
  ../src/SearchMenu/SearchMenuSearchWithContextMessage.cpp
  ../src/SearchMenu/SearchMenuSearchWithContextMessage.h
  ../src/SearchMenu/OpenSearchMenuMessage.cpp
  ../src/SearchMenu/OpenSearchMenuMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchMenu FILES ${currsources})
include(../src/SearchMenu/SdkModel/CMakeLists.txt)
include(../src/SearchMenu/View/CMakeLists.txt)
