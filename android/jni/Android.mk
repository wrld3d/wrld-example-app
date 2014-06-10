LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := native-activity-lib
LOCAL_SRC_FILES := ./../libs/libnative-activity-lib.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := native-activity
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -L./libs/ -lpng -lz -lm -L./libs/ -lcrypto -L./libs/ -lssl -L./libs/ -lcurl -L./libs/ -lcares -L./libs/ -lsimd -L./libs/ -lmyjpeg
LOCAL_STATIC_LIBRARIES := android_native_app_glue native-activity-lib

os_name:=$(shell uname -s)

ifeq ($(os_name),Darwin)
	android_specific_cpp_files := $(shell cd jni; find ./ -type f  -iname "*.cpp")
	LOCAL_SRC_FILES := $(android_specific_cpp_files:$(LOCAL_PATH)/%=%)

	shared_example_cpp_files := $(shell cd jni; find ./../../src/ -type f  -iname "*.cpp")
	LOCAL_SRC_FILES += $(shared_example_cpp_files:$(LOCAL_PATH)/%=%)

	platformincludes := $(shell find ./libs/platform -type d ! -path "*/OSX/*" ! -path "*/iOS/*")
	LOCAL_C_INCLUDES := $(platformincludes:$(LOCAL_PATH)/%=%)

	exampleincludes := $(shell find ./libs/../../src -type d)
	LOCAL_C_INCLUDES += $(exampleincludes:$(LOCAL_PATH)/%=%)
	
	java_exampleincludes := $(shell find ./jni/Examples -type d)
	LOCAL_C_INCLUDES += $(java_exampleincludes:$(LOCAL_PATH)/%=%)
else
	# assume windows if not specified for now (due to no uname)
	
	android_specific_cpp_files := $(shell cd jni && dir /a-d /b /s *.cpp)
	LOCAL_SRC_FILES := $(android_specific_cpp_files:$(LOCAL_PATH)/%=%)
    
    shared_example_cpp_files := $(shell cd jni\..\..\src\ && dir /a-d /b /s *.cpp)
	LOCAL_SRC_FILES += $(shared_example_cpp_files:$(LOCAL_PATH)/%=%)
	
	platformincludes := $(shell dir .\libs\platform /ad-h /s /b)
	LOCAL_C_INCLUDES := $(platformincludes:$(LOCAL_PATH)/%=%)
	LOCAL_C_INCLUDES += ./libs/platform 

	exampleincludes := $(shell dir .\libs\..\..\src /ad-h /s /b)
	LOCAL_C_INCLUDES += $(exampleincludes:$(LOCAL_PATH)/%=%)
	LOCAL_C_INCLUDES += .\libs\..\..\src
	
	java_exampleincludes := $(shell dir .\jni\Examples /ad-h /s /b)
	LOCAL_C_INCLUDES += $(java_exampleincludes:$(LOCAL_PATH)/%=%)
	LOCAL_C_INCLUDES += .\jni\Examples
endif 

LOCAL_C_INCLUDES += ./libs/png
LOCAL_C_INCLUDES += ./libs/curl 
LOCAL_C_INCLUDES += ./libs/jpeg  

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
