if(${IOS})
set(headers ${headers} ios/ios_src/Tours/View/TwitterTourExplorer
)
set(currsources
  ios/ios_src/Tours/View/TwitterTourExplorer/TwitterCardView.h
  ios/ios_src/Tours/View/TwitterTourExplorer/TwitterCardView.mm
  ios/ios_src/Tours/View/TwitterTourExplorer/TwitterDefines.h
  ios/ios_src/Tours/View/TwitterTourExplorer/TwitterDefines.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Tours\\View\\TwitterTourExplorer FILES ${currsources})
endif(${IOS})
