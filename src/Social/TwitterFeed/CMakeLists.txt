set(headers ${headers} ../src/Social/TwitterFeed
)
set(currsources
  ../src/Social/TwitterFeed/CMakeLists.txt
  ../src/Social/TwitterFeed/ITwitterFeedModule.h
  ../src/Social/TwitterFeed/ITwitterFeedService.h
  ../src/Social/TwitterFeed/TweetModel.cpp
  ../src/Social/TwitterFeed/TweetModel.h
  ../src/Social/TwitterFeed/TweetRepository.h
  ../src/Social/TwitterFeed/TwitterFeed.h
  ../src/Social/TwitterFeed/TwitterFeedModule.cpp
  ../src/Social/TwitterFeed/TwitterFeedModule.h
  ../src/Social/TwitterFeed/TwitterFeedService.cpp
  ../src/Social/TwitterFeed/TwitterFeedService.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Social\\TwitterFeed FILES ${currsources})
