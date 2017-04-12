set(headers ${headers} Include/HockeySDK-iOS/HockeySDK.embeddedframework
)
set(currsources
Include/HockeySDK-iOS/CMakeLists.txt
Include/HockeySDK-iOS/HockeySDK.embeddedframework/HockeySDK.framework
Include/HockeySDK-iOS/HockeySDK.embeddedframework/HockeySDKResources.bundle
)
set(sources ${sources} ${currsources})
source_group(\\HockeySDK-iOS FILES ${currsources})
