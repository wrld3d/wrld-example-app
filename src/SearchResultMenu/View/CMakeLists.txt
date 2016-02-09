set(headers ${headers} ../src/SearchResultMenu/View
)
set(currsources
  ../src/SearchResultMenu/View/CMakeLists.txt
  ../src/SearchResultMenu/View/ISearchResultMenuOrder.h
  ../src/SearchResultMenu/View/ISearchResultMenuView.h
  ../src/SearchResultMenu/View/ISearchResultMenuViewModel.h
  ../src/SearchResultMenu/View/SearchResultItemModel.cpp
  ../src/SearchResultMenu/View/SearchResultItemModel.h
  ../src/SearchResultMenu/View/SearchResultMenuAppModeMessageHandler.cpp
  ../src/SearchResultMenu/View/SearchResultMenuAppModeMessageHandler.h
  ../src/SearchResultMenu/View/SearchResultMenuController.cpp
  ../src/SearchResultMenu/View/SearchResultMenuController.h
  ../src/SearchResultMenu/View/SearchResultMenuOrder.cpp
  ../src/SearchResultMenu/View/SearchResultMenuOrder.h
  ../src/SearchResultMenu/View/SearchResultMenuSearchQueryPerformedMessageHandler.cpp
  ../src/SearchResultMenu/View/SearchResultMenuSearchQueryPerformedMessageHandler.h
  ../src/SearchResultMenu/View/SearchResultMenuSearchQueryRemovedMessageHandler.cpp
  ../src/SearchResultMenu/View/SearchResultMenuSearchQueryRemovedMessageHandler.h
  ../src/SearchResultMenu/View/SearchResultMenuViewModel.cpp
  ../src/SearchResultMenu/View/SearchResultMenuViewModel.h
  ../src/SearchResultMenu/View/SearchResultRepositoryObserver.cpp
  ../src/SearchResultMenu/View/SearchResultRepositoryObserver.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchResultMenu\\View FILES ${currsources})
include(../src/SearchResultMenu/View/Swallow/CMakeLists.txt)
