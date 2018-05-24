set(headers ${headers} ../src/Reaction/View
)
set(currsources
  ../src/Reaction/View/CMakeLists.txt
  ../src/Reaction/View/IReactionModel.h
  ../src/Reaction/View/IReactionModelModule.h
  ../src/Reaction/View/ReactionModel.cpp
  ../src/Reaction/View/ReactionModel.h
  ../src/Reaction/View/ReactionModelModule.cpp
  ../src/Reaction/View/ReactionModelModule.h

  ../src/Reaction/View/IReaction.h
  ../src/Reaction/View/ReactionHideOtherScreenControls.cpp
  ../src/Reaction/View/ReactionHideOtherScreenControls.h
  ../src/Reaction/View/ReactionPushScreenControl.cpp
  ../src/Reaction/View/ReactionPushScreenControl.h
  ../src/Reaction/View/IReactionScreenOffsetProvider.h
  ../src/Reaction/View/ReactionScreenOffsetProvider.cpp
  ../src/Reaction/View/ReactionScreenOffsetProvider.h

)
set(sources ${sources} ${currsources})
source_group(\\src\\Reaction\\View FILES ${currsources})
