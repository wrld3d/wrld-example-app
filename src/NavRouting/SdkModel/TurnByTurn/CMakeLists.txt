set(headers ${headers} ../src/NavRouting/SdkModel/TurnByTurn
)
set(currsources
  ../src/NavRouting/SdkModel/TurnByTurn/CMakeLists.txt
  ../src/NavRouting/SdkModel/TurnByTurn/INavTurnByTurnModel.h
  ../src/NavRouting/SdkModel/TurnByTurn/NavTurnByTurnModel.h
  ../src/NavRouting/SdkModel/TurnByTurn/NavTurnByTurnModel.cpp
  ../src/NavRouting/SdkModel/TurnByTurn/NavTurnByTurnController.h
  ../src/NavRouting/SdkModel/TurnByTurn/NavTurnByTurnController.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\NavRouting\\SdkModel\\TurnByTurn FILES ${currsources})