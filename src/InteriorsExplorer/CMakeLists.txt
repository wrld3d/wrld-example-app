set(headers ${headers} ../src/InteriorsExplorer
)
set(currsources
  ../src/InteriorsExplorer/CMakeLists.txt
  ../src/InteriorsExplorer/InteriorsExplorer.h
  ../src/InteriorsExplorer/InteriorsExplorerExitMessage.h
  ../src/InteriorsExplorer/InteriorsExplorerFloorSelectedMessage.h
  ../src/InteriorsExplorer/InteriorsExplorerSelectFloorMessage.h
  ../src/InteriorsExplorer/InteriorsExplorerStateChangedMessage.h
  ../src/InteriorsExplorer/InteriorsExplorerUINotifyMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsExplorer FILES ${currsources})
include(../src/InteriorsExplorer/SdkModel/CMakeLists.txt)
include(../src/InteriorsExplorer/View/CMakeLists.txt)
