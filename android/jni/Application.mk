APP_OPTIM := debug
APP_PLATFORM := android-10
APP_STL := c++_static
APP_ABI := armeabi-v7a

ifneq ($(os_name),Darwin)    
	APP_SHORT_COMMANDS := true 
endif
 
