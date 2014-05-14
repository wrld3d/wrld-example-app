LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := native-activity-lib
LOCAL_SRC_FILES := ./../libs/libnative-activity-lib.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := native-activity
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -L./libs/ -lpng -lz -lm -L./libs/ -lcrypto -L./libs/ -lssl -L./libs/ -lcurl -L./libs/ -lcares -L./libs/ -lsimd -L./libs/ -lmyjpeg
LOCAL_STATIC_LIBRARIES := android_native_app_glue native-activity-lib

#shared_include := $(shell find ./libs/../../share/ -type f)
#(warning $(shared_include))
#cdc

LOCAL_SRC_FILES += ./main.cpp
LOCAL_SRC_FILES += ./AppWindow.cpp
LOCAL_SRC_FILES += ./AppOnMap.cpp
LOCAL_SRC_FILES += ./ExampleCameraJumpController.cpp
LOCAL_SRC_FILES += ./UiThreadToNativeThreadTaskQueue.cpp

LOCAL_SRC_FILES += ./Examples/JavaHudCrossThreadCommunicationExample.cpp
LOCAL_SRC_FILES += ./Examples/RouteMatchingExample.cpp
LOCAL_SRC_FILES += ./Examples/RouteSimulationExample.cpp
LOCAL_SRC_FILES += ./Examples/ShowJavaPlaceJumpUIExample.cpp
LOCAL_SRC_FILES += ./Examples/PinsWithAttachedJavaUIExample.cpp
LOCAL_SRC_FILES += ./Examples/PositionJavaPinButtonExample.cpp

LOCAL_SRC_FILES += ./../../src/DebugSphereExample.cpp
LOCAL_SRC_FILES += ./../../src/EnvironmentFlatteningExample.cpp
LOCAL_SRC_FILES += ./../../src/EnvironmentNotifierExample.cpp
LOCAL_SRC_FILES += ./../../src/FileIOExample.cpp
LOCAL_SRC_FILES += ./../../src/LoadModelExample.cpp
LOCAL_SRC_FILES += ./../../src/ModifiedRenderingExample.cpp
LOCAL_SRC_FILES += ./../../src/NavigationGraphExample.cpp
LOCAL_SRC_FILES += ./../../src/ResourceSpatialQueryExample.cpp
LOCAL_SRC_FILES += ./../../src/ScreenUnprojectExample.cpp
LOCAL_SRC_FILES += ./../../src/SearchExample.cpp
LOCAL_SRC_FILES += ./../../src/ToggleTrafficExample.cpp
LOCAL_SRC_FILES += ./../../src/WebRequestExample.cpp
LOCAL_SRC_FILES += ./../../src/KeyboardInputExample.cpp
LOCAL_SRC_FILES += ./../../src/PODAnimationExample.cpp
LOCAL_SRC_FILES += ./../../src/Pick3DObjectExample.cpp
LOCAL_SRC_FILES += ./../../src/ScreenPickExample.cpp
LOCAL_SRC_FILES += ./../../src/DebugPrimitiveRenderingExample.cpp
LOCAL_SRC_FILES += ./../../src/RouteDrawingExample.cpp
LOCAL_SRC_FILES += ./../../src/PinsExample.cpp
LOCAL_SRC_FILES += ./../../src/RouteSimulationAnimationExample.cpp
LOCAL_SRC_FILES += ./../../src/RouteThicknessPolicyExample.cpp
LOCAL_SRC_FILES += ./../../src/DynamicText3DExample.cpp
LOCAL_SRC_FILES += ./../../src/SingleCityExample.cpp
LOCAL_SRC_FILES += ./../../src/PinOverModelExample.cpp
LOCAL_SRC_FILES += ./../../src/TrafficCongestionExample.cpp
LOCAL_SRC_FILES += ./../../src/ControlCityThemeExample.cpp
LOCAL_SRC_FILES += ./../../src/CameraTransitionExample.cpp

os_name:=$(shell uname -s)

ifeq ($(os_name),Darwin)
	platformincludes := $(shell find ./libs/platform -type d ! -path "*/OSX/*" ! -path "*/iOS/*")
	LOCAL_C_INCLUDES := $(platformincludes:$(LOCAL_PATH)/%=%)
else
	# assume windows if not specified for now (due to no uname)
	platformincludes := $(shell dir .\libs\platform /ad-h /s /b)
	LOCAL_C_INCLUDES := $(platformincludes:$(LOCAL_PATH)/%=%)
	LOCAL_C_INCLUDES += ./libs/platform 
endif 

LOCAL_C_INCLUDES += ./libs/../../src/

LOCAL_C_INCLUDES += ./jni/Examples 

LOCAL_C_INCLUDES += ./libs/png
LOCAL_C_INCLUDES += ./libs/curl 
LOCAL_C_INCLUDES += ./libs/jpeg  

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
