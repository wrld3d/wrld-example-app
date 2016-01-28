set(headers ${headers} ../src/Reaction/View
)
set(currsources
  ../src/Reaction/View/CMakeLists.txt
  ../src/Reaction/View/IReactionControllerModel.h
  ../src/Reaction/View/IReactionControllerModule.h
  ../src/Reaction/View/IReactionModel.h
  ../src/Reaction/View/IReactionModelModule.h
  ../src/Reaction/View/ReactionControllerModel.cpp
  ../src/Reaction/View/ReactionControllerModel.h
  ../src/Reaction/View/ReactionControllerModule.cpp
  ../src/Reaction/View/ReactionControllerModule.h
  ../src/Reaction/View/ReactionModel.cpp
  ../src/Reaction/View/ReactionModel.h
  ../src/Reaction/View/ReactionModelModule.cpp
  ../src/Reaction/View/ReactionModelModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Reaction\\View FILES ${currsources})
