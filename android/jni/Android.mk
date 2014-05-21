LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := native-activity-lib
LOCAL_SRC_FILES := ./../libs/libnative-activity-lib.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := native-activity
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -L./libs/ -lpng -lz -lm -L./libs/ -lcrypto -L./libs/ -lssl -L./libs/ -lcurl -L./libs/ -lcares -L./libs/ -lsimd -L./libs/ -lmyjpeg
LOCAL_STATIC_LIBRARIES := android_native_app_glue native-activity-lib

#android-specific sources
LOCAL_SRC_FILES += ./main.cpp
LOCAL_SRC_FILES += ./AppWindow.cpp
LOCAL_SRC_FILES += ./UiThreadToNativeThreadTaskQueue.cpp

LOCAL_SRC_FILES += ./Examples/JavaHudCrossThreadCommunication/JavaHudCrossThreadCommunicationExample.cpp
LOCAL_SRC_FILES += ./Examples/JavaHudCrossThreadCommunication/JavaHudCrossThreadCommunicationExampleFactory.cpp
LOCAL_SRC_FILES += ./Examples/ShowJavaPlaceJumpUI/ShowJavaPlaceJumpUIExample.cpp
LOCAL_SRC_FILES += ./Examples/ShowJavaPlaceJumpUI/ShowJavaPlaceJumpUIExampleFactory.cpp
LOCAL_SRC_FILES += ./Examples/ShowJavaPlaceJumpUI/ExampleCameraJumpController.cpp
LOCAL_SRC_FILES += ./Examples/PinsWithAttachedJavaUI/PinsWithAttachedJavaUIExample.cpp
LOCAL_SRC_FILES += ./Examples/PinsWithAttachedJavaUI/PinsWithAttachedJavaUIExampleFactory.cpp
LOCAL_SRC_FILES += ./Examples/PositionJavaPinButton/PositionJavaPinButtonExample.cpp
LOCAL_SRC_FILES += ./Examples/PositionJavaPinButton/PositionJavaPinButtonExampleFactory.cpp
LOCAL_SRC_FILES += ./Examples/RouteMatching/AndroidRouteMatchingExampleView.cpp
LOCAL_SRC_FILES += ./Examples/RouteMatching/AndroidRouteMatchingExampleViewFactory.cpp
LOCAL_SRC_FILES += ./Examples/RouteSimulation/AndroidRouteSimulationExampleView.cpp
LOCAL_SRC_FILES += ./Examples/RouteSimulation/AndroidRouteSimulationExampleViewFactory.cpp

#cross-platform sources
LOCAL_SRC_FILES += ./../../src/ExampleApp.cpp
LOCAL_SRC_FILES += ./../../src/Examples/ExampleController.cpp

LOCAL_SRC_FILES += ./../../src/Examples/DebugSphere/DebugSphereExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/DebugSphere/DebugSphereExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/EnvironmentFlattening/EnvironmentFlatteningExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/EnvironmentFlattening/EnvironmentFlatteningExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/EnvironmentNotifier/EnvironmentNotifierExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/EnvironmentNotifier/EnvironmentNotifierExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/FileIO/FileIOExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/FileIO/FileIOExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/LoadModel/LoadModelExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/LoadModel/LoadModelExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/ModifiedRendering/ModifiedRenderingExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/ModifiedRendering/ModifiedRenderingExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/NavigationGraph/NavigationGraphExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/NavigationGraph/NavigationGraphExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/ResourceSpatialQuery/ResourceSpatialQueryExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/ResourceSpatialQuery/ResourceSpatialQueryExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/ScreenUnproject/ScreenUnprojectExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/ScreenUnproject/ScreenUnprojectExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/Search/SearchExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/Search/SearchExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/ToggleTraffic/ToggleTrafficExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/ToggleTraffic/ToggleTrafficExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/WebRequest/WebRequestExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/WebRequest/WebRequestExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/KeyboardInput/KeyboardInputExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/KeyboardInput/KeyboardInputExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/PODAnimation/PODAnimationExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/PODAnimation/PODAnimationExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/Pick3DObject/Pick3DObjectExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/Pick3DObject/Pick3DObjectExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/ScreenPick/ScreenPickExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/ScreenPick/ScreenPickExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/DebugPrimitiveRendering/DebugPrimitiveRenderingExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/DebugPrimitiveRendering/DebugPrimitiveRenderingExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/RouteDrawing/RouteDrawingExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/RouteDrawing/RouteDrawingExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/Pins/PinsExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/Pins/PinsExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/RouteSimulationAnimation/RouteSimulationAnimationExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/RouteSimulationAnimation/RouteSimulationAnimationExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/RouteThicknessPolicy/RouteThicknessPolicyExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/RouteThicknessPolicy/RouteThicknessPolicyExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/RouteMatching/RouteMatchingExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/RouteMatching/RouteMatchingExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/RouteSimulation/RouteSimulationExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/RouteSimulation/RouteSimulationExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/DynamicText3D/DynamicText3DExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/DynamicText3D/DynamicText3DExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/SingleCity/SingleCityExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/SingleCity/SingleCityExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/PinOverModel/PinOverModelExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/PinOverModel/PinOverModelExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/TrafficCongestion/TrafficCongestionExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/TrafficCongestion/TrafficCongestionExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/ControlCityThemes/ControlCityThemeExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/ControlCityThemes/ControlCityThemeExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/CameraTransition/CameraTransitionExample.cpp
LOCAL_SRC_FILES += ./../../src/Examples/CameraTransition/CameraTransitionExampleFactory.cpp
LOCAL_SRC_FILES += ./../../src/Examples/UI/UIHelpers.cpp

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

exampleincludes := $(shell find ./libs/../../src -type d)
LOCAL_C_INCLUDES += $(exampleincludes:$(LOCAL_PATH)/%=%)

java_exampleincludes := $(shell find ./jni/Examples -type d)
LOCAL_C_INCLUDES += $(java_exampleincludes:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES += ./libs/png
LOCAL_C_INCLUDES += ./libs/curl 
LOCAL_C_INCLUDES += ./libs/jpeg  

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
