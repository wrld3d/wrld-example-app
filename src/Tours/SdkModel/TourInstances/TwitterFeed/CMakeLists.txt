set(headers ${headers} ../src/Tours/SdkModel/TourInstances/TwitterFeed
)
set(currsources
  ../src/Tours/SdkModel/TourInstances/TwitterFeed/CMakeLists.txt
  ../src/Tours/SdkModel/TourInstances/TwitterFeed/ITwitterFeedTourModule.h
  ../src/Tours/SdkModel/TourInstances/TwitterFeed/TweetStateData.h
  ../src/Tours/SdkModel/TourInstances/TwitterFeed/TwitterFeedPinSelectionHandler.cpp
  ../src/Tours/SdkModel/TourInstances/TwitterFeed/TwitterFeedPinSelectionHandler.h
  ../src/Tours/SdkModel/TourInstances/TwitterFeed/TwitterFeedShowTweetState.cpp
  ../src/Tours/SdkModel/TourInstances/TwitterFeed/TwitterFeedShowTweetState.h
  ../src/Tours/SdkModel/TourInstances/TwitterFeed/TwitterFeedTour.h
  ../src/Tours/SdkModel/TourInstances/TwitterFeed/TwitterFeedTourModule.cpp
  ../src/Tours/SdkModel/TourInstances/TwitterFeed/TwitterFeedTourModule.h
  ../src/Tours/SdkModel/TourInstances/TwitterFeed/TwitterFeedTourObserver.cpp
  ../src/Tours/SdkModel/TourInstances/TwitterFeed/TwitterFeedTourObserver.h
  ../src/Tours/SdkModel/TourInstances/TwitterFeed/TwitterFeedTourStateMachineFactory.cpp
  ../src/Tours/SdkModel/TourInstances/TwitterFeed/TwitterFeedTourStateMachineFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Tours\\SdkModel\\TourInstances\\TwitterFeed FILES ${currsources})
