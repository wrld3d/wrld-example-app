if(${IOS})
set(headers ${headers} ios_src/WorldPinOnMap/View/Hovercards
)
set(currsources
  ios_src/WorldPinOnMap/View/Hovercards/CMakeLists.txt
  ios_src/WorldPinOnMap/View/Hovercards/InteriorsHovercard.h
  ios_src/WorldPinOnMap/View/Hovercards/InteriorsHovercard.mm
  ios_src/WorldPinOnMap/View/Hovercards/TwitterTourHovercard.h
  ios_src/WorldPinOnMap/View/Hovercards/TwitterTourHovercard.mm
  ios_src/WorldPinOnMap/View/Hovercards/TwitterWorldHovercard.h
  ios_src/WorldPinOnMap/View/Hovercards/TwitterWorldHovercard.mm
  ios_src/WorldPinOnMap/View/Hovercards/YelpHovercardView.h
  ios_src/WorldPinOnMap/View/Hovercards/YelpHovercardView.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\WorldPinOnMap\\View\\Hovercards FILES ${currsources})
endif(${IOS})
