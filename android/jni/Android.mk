LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := native-activity-lib
LOCAL_SRC_FILES := ./../libs/libnative-activity-lib.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := native-activity
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -L./libs/ -lpng -lz -lm -L./libs/ -lcrypto -L./libs/ -lssl -L./libs/ -lcurl -L./libs/ -lcares -L./libs/ -lsimd -L./libs/ -lmyjpeg -L./libs/ -lhttpxx-lib
LOCAL_STATIC_LIBRARIES := android_native_app_glue native-activity-lib 

LOCAL_CFLAGS += -march=armv6 -marm -mfloat-abi=softfp -mfpu=vfp
LOCAL_CFLAGS += -Wall -Wno-unknown-pragmas -Wno-sign-compare -Wno-format-security -Wno-reorder
#LOCAL_CFLAGS += -Werror

ifdef COMPILE_CPP_11
  LOCAL_LDLIBS += -fuse-ld=bfd
  LOCAL_CPPFLAGS += -DCOMPILE_CPP_11=1 -std=c++11
endif

os_name:=$(shell uname -s)

ifeq ($(os_name),Darwin)
	android_specific_cpp_files := $(shell cd jni; find ./ -type f  -iname "*.cpp")
	LOCAL_SRC_FILES := $(android_specific_cpp_files:$(LOCAL_PATH)/%=%)
	android_specific_includes := $(shell find ./jni -type d)
	LOCAL_C_INCLUDES := $(android_specific_includes:$(LOCAL_PATH)/%=%)

	shared_example_cpp_files := $(shell cd jni; find ./../../src/ -type f  -iname "*.cpp")
	LOCAL_SRC_FILES += $(shared_example_cpp_files:$(LOCAL_PATH)/%=%)

	platformincludes := $(shell find ./libs/platform -type d ! -path "*/OSX/*" ! -path "*/iOS/*")
	LOCAL_C_INCLUDES += $(platformincludes:$(LOCAL_PATH)/%=%)

	exampleincludes := $(shell find ./libs/../../src -type d)
	LOCAL_C_INCLUDES += $(exampleincludes:$(LOCAL_PATH)/%=%)

else
	# assume windows if not specified for now (due to no uname)
	
	android_specific_includes := $(shell dir jni /ad-h /s /b)
	LOCAL_C_INCLUDES := $(android_specific_includes:$(LOCAL_PATH)/%=%)
	
	android_specific_cpp_files := $(shell cd jni && dir /a-d /b /s *.cpp)
	LOCAL_SRC_FILES := $(android_specific_cpp_files:$(LOCAL_PATH)/%=%)
    
    shared_example_cpp_files := $(shell cd jni\..\..\src\ && dir /a-d /b /s *.cpp)
	LOCAL_SRC_FILES += $(shared_example_cpp_files:$(LOCAL_PATH)/%=%)
	
	platformincludes := $(shell dir .\libs\platform /ad-h /s /b)
	LOCAL_C_INCLUDES += $(platformincludes:$(LOCAL_PATH)/%=%)
	LOCAL_C_INCLUDES += ./libs/platform 

	exampleincludes := $(shell dir .\libs\..\..\src /ad-h /s /b)
	LOCAL_C_INCLUDES += $(exampleincludes:$(LOCAL_PATH)/%=%)
	LOCAL_C_INCLUDES += .\libs\..\..\src
endif 

LOCAL_C_INCLUDES += ./libs/png
LOCAL_C_INCLUDES += ./libs/curl 
LOCAL_C_INCLUDES += ./libs/jpeg  
LOCAL_C_INCLUDES += ./libs/httpxx/code
LOCAL_C_INCLUDES += ./../external/rapidjson/
LOCAL_C_INCLUDES += ./../external/rapidjson/internal
LOCAL_C_INCLUDES += ./libs/httpxx/libs/http-parser

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
