APP_OPTIM := debug
APP_PLATFORM := android-10
APP_STL := gnustl_static
APP_ABI := armeabi,armeabi-v7a,arm64-v8a

ifneq ($(os_name),Darwin)    
	APP_SHORT_COMMANDS := true 
endif
 