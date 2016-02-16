LOCAL_PATH := $(call my-dir)

PREBUILT_LIBS := ./libs/eegeo/prebuilt/android-$(TARGET_ARCH_ABI)

include $(CLEAR_VARS)
LOCAL_MODULE := eegeo-sdk-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libeegeo-sdk.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := png-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libpng.a
LOCAL_EXPORT_C_INCLUDES := ./libs/eegeo/png
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := curl-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libcurl.a
LOCAL_EXPORT_C_INCLUDES := ./libs/eegeo/curl/android-$(TARGET_ARCH_ABI) 
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := uv-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libuv.a
LOCAL_EXPORT_C_INCLUDES := ./libs/eegeo/curl/android-$(TARGET_ARCH_ABI) 
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := ssl-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := crypto-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := http-parser-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libhttp-parser.a
LOCAL_EXPORT_C_INCLUDES := ./libs/eegeo/http-parser 
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := jpeg-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libjpeg.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := turbojpeg-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libturbojpeg.a
LOCAL_EXPORT_C_INCLUDES := ./libs/eegeo/jpeg-turbo 
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := eegeo-mobile-example-app
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2 -lz -lm
LOCAL_LDLIBS += -fuse-ld=bfd -Wl,--stub-group-size=2085000
LOCAL_STATIC_LIBRARIES := recce-common-lib eegeo-sdk-lib png-lib curl-lib uv-lib ssl-lib crypto-lib http-parser-lib jpeg-lib turbojpeg-lib

cflags := -Wall -Wno-unknown-pragmas -Wno-sign-compare -Wno-format-security -Wno-reorder

#LOCAL_CFLAGS += -Werror

ifdef COMPILE_CPP_11  
  cppflags := -DCOMPILE_CPP_11=1 -std=c++11
else  
  cppflags := -std=c++0x
endif


LOCAL_CFLAGS += ${cflags}
LOCAL_CPPFLAGS += ${cppflags}

os_name:=$(shell uname -s)

get_android_cpp_files_cmd := cd jni; find ./ -type f  -iname "*.cpp"
get_android_includes_cmd  := find ./jni -type d
get_shared_cpp_files_cmd  := cd jni; find ./../../src/ -type f  -iname "*.cpp"
get_shared_includes_cmd   := find ./libs/../../src -type d
get_platform_includes_cmd := find ./libs/eegeo/platform -type d ! -path "*/OSX/*" ! -path "*/iOS/*"


ifeq ($(os_name),Darwin)
	android_cpp_files := ${shell ${get_android_cpp_files_cmd}}
	shared_cpp_files := ${shell ${get_shared_cpp_files_cmd}}
	
	includes := ${shell ${get_android_includes_cmd}}
	includes += ${shell ${get_shared_includes_cmd}}
	includes += ${shell ${get_platform_includes_cmd}}
else
	# assume windows if not specified for now (due to no uname)
	android_cpp_files := ${shell sh -c '${get_android_cpp_files_cmd}'}
	shared_cpp_files := ${shell sh -c '${get_shared_cpp_files_cmd}'}
	
	includes := ${shell sh -c '${get_android_includes_cmd}'}
	includes += ${shell sh -c '${get_shared_includes_cmd}'}
	includes += ${shell sh -c '${get_platform_includes_cmd}'}
endif 

includes += ./libs/eegeo/rapidjson
includes += ./libs/eegeo/rapidjson/internal

LOCAL_SRC_FILES := $(android_cpp_files:$(LOCAL_PATH)/%=%)
LOCAL_C_INCLUDES := $(includes:$(LOCAL_PATH)/%=%)



include $(BUILD_SHARED_LIBRARY)

include $(LOCAL_PATH)/Common.mk

$(call import-module,android/native_app_glue)
