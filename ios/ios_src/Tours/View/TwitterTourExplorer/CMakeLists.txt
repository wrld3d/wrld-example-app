if(${IOS})
set(headers ${headers} ios_src/Tours/View/TwitterTourExplorer
)
set(currsources
  ios_src/Tours/View/TwitterTourExplorer/CMakeLists.txt
  ios_src/Tours/View/TwitterTourExplorer/TwitterCardView.h
  ios_src/Tours/View/TwitterTourExplorer/TwitterCardView.mm
  ios_src/Tours/View/TwitterTourExplorer/TwitterDefines.h
  ios_src/Tours/View/TwitterTourExplorer/TwitterDefines.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Tours\\View\\TwitterTourExplorer FILES ${currsources})
endif(${IOS})
