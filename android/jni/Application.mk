APP_OPTIM := debug
APP_PLATFORM := android-10
APP_STL := gnustl_static

ifdef COMPILE_CPP_11
  NDK_TOOLCHAIN_VERSION:=4.8
endif
