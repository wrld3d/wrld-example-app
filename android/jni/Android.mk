LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(info TARGET_ARCH_ABI is $(TARGET_ARCH_ABI))

PREBUILT_LIBS := ./libs/eegeo/prebuilt/android-$(TARGET_ARCH_ABI)

LOCAL_MODULE := native-activity-lib
LOCAL_SRC_FILES := ../$(PREBUILT_LIBS)/libnative-activity-lib.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

ifneq ($(os_name),Darwin)    
    LOCAL_SHORT_COMMANDS := true    
endif

LOCAL_MODULE := native-activity
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2 -lz -lm -L${PREBUILT_LIBS} -lpng -lcurl -lssl -lcrypto -lhttp-parser -ljpeg -lturbojpeg
LOCAL_LDLIBS += -fuse-ld=bfd
LOCAL_STATIC_LIBRARIES := native-activity-lib 

LOCAL_CFLAGS += -Wall -Wno-unknown-pragmas -Wno-sign-compare -Wno-format-security -Wno-reorder
#LOCAL_CFLAGS += -Werror

ifdef COMPILE_CPP_11
  LOCAL_CPPFLAGS += -DCOMPILE_CPP_11=1 -std=c++11
endif

os_name:=$(shell uname -s)

get_android_cpp_files_cmd := cd jni; find ./ -type f  -iname "*.cpp"
get_android_includes_cmd  := find ./jni -type d
get_shared_cpp_files_cmd  := cd jni; find ./../../src/ -type f  -iname "*.cpp"
get_shared_includes_cmd   := find ./libs/../../src -type d
get_platform_includes_cmd := find ./libs/eegeo/platform -type d ! -path "*/OSX/*" ! -path "*/iOS/*"


ifeq ($(os_name),Darwin)
	cppfiles := ${shell ${get_android_cpp_files_cmd}}
	cppfiles += ${shell ${get_shared_cpp_files_cmd}}
	
	includes := ${shell ${get_android_includes_cmd}}
	includes += ${shell ${get_shared_includes_cmd}}
	includes += ${shell ${get_platform_includes_cmd}}
else
	# assume windows if not specified for now (due to no uname)
	cppfiles := ${shell sh -c '${get_android_cpp_files_cmd}'}
	cppfiles += ${shell sh -c '${get_shared_cpp_files_cmd}'}
	
	includes := ${shell sh -c '${get_android_includes_cmd}'}
	includes += ${shell sh -c '${get_shared_includes_cmd}'}
	includes += ${shell sh -c '${get_platform_includes_cmd}'}
endif 

LOCAL_SRC_FILES := $(cppfiles:$(LOCAL_PATH)/%=%)
LOCAL_C_INCLUDES := $(includes:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES += ./libs/eegeo/curl/android-$(TARGET_ARCH_ABI) 
LOCAL_C_INCLUDES += ./libs/eegeo/http-parser
LOCAL_C_INCLUDES += ./libs/eegeo/httpxx
LOCAL_C_INCLUDES += ./libs/eegeo/jpeg-turbo
LOCAL_C_INCLUDES += ./libs/eegeo/png
LOCAL_C_INCLUDES += ./libs/eegeo/rapidjson
LOCAL_C_INCLUDES += ./libs/eegeo/rapidjson/internal



include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
