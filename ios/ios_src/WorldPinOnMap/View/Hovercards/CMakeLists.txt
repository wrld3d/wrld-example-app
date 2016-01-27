if(${IOS})
set(headers ${headers} ios/ios_src/WorldPinOnMap/View/Hovercards
)
set(currsources
  ios/ios_src/WorldPinOnMap/View/Hovercards/InteriorsHovercard.h
  ios/ios_src/WorldPinOnMap/View/Hovercards/InteriorsHovercard.mm
  ios/ios_src/WorldPinOnMap/View/Hovercards/TwitterTourHovercard.h
  ios/ios_src/WorldPinOnMap/View/Hovercards/TwitterTourHovercard.mm
  ios/ios_src/WorldPinOnMap/View/Hovercards/TwitterWorldHovercard.h
  ios/ios_src/WorldPinOnMap/View/Hovercards/TwitterWorldHovercard.mm
  ios/ios_src/WorldPinOnMap/View/Hovercards/YelpHovercardView.h
  ios/ios_src/WorldPinOnMap/View/Hovercards/YelpHovercardView.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\WorldPinOnMap\\View\\Hovercards FILES ${currsources})
endif(${IOS})
