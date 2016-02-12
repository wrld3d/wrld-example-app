set(headers ${headers} ../src/PlaceJumps/View
)
set(currsources
  ../src/PlaceJumps/View/CMakeLists.txt
  ../src/PlaceJumps/View/IPlaceJumpsModel.h
  ../src/PlaceJumps/View/PlaceJumpMenuOption.cpp
  ../src/PlaceJumps/View/PlaceJumpMenuOption.h
  ../src/PlaceJumps/View/PlaceJumpsDataParser.cpp
  ../src/PlaceJumps/View/PlaceJumpsDataParser.h
  ../src/PlaceJumps/View/PlaceJumpsModel.cpp
  ../src/PlaceJumps/View/PlaceJumpsModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\PlaceJumps\\View FILES ${currsources})
