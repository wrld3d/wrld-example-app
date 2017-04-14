cmake_minimum_required(VERSION 3.1)

set(CMAKE_TOOLCHAIN_FILE "../cmake/toolchain/ios/iOS.cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/templates/ios)

macro (unset_xcode_property TARGET XCODE_PROPERTY)
  set_property (TARGET ${TARGET} PROPERTY XCODE_ATTRIBUTE_${XCODE_PROPERTY})
endmacro (unset_xcode_property)

if(NOT ${IOS}) 
	message(FATAL_ERROR "Incorrect toolchain set: ${CMAKE_TOOLCHAIN_FILE}")
endif(NOT ${IOS})

if(NOT TARGET_NAME)
  set(TARGET_NAME "ExampleApp")
  message("Using default target: ${TARGET_NAME}")
endif(NOT TARGET_NAME)


project(${TARGET_NAME})
set(executable_name ${TARGET_NAME})

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Include/eegeo/CMakeLists.txt")
  include("${CMAKE_CURRENT_SOURCE_DIR}/Include/eegeo/CMakeLists.txt")
else(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Include/eegeo/CMakeLists.txt")
  message(FATAL_ERROR "Couldn't detect platform headers. Have you run update.platform.sh?")
endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Include/eegeo/CMakeLists.txt")

include(../src/CMakeLists.txt)
include(Include/CMakeLists.txt)
include(ios_src/CMakeLists.txt)
include(Resources/CMakeLists.txt)

set(storyboards
    ExampleApp/en.lproj/MainStoryboard_iPad.storyboard
    ExampleApp/en.lproj/MainStoryboard_iPhone.storyboard)

# plist settings
set(EEGEO_PLIST_BUNDLE_EXECUTABLE "\${EXECUTABLE_NAME}")
set(EEGEO_PLIST_BUNDLE_IDENTIFIER "com.eegeo.\${PRODUCT_NAME:rfc1034identifier}")
set(EEGEO_PLIST_BUNDLE_SHORT_VERSION_STRING "\${PRODUCT_VERSION}")
set(EEGEO_PLIST_BUNDLE_DISPLAY_NAME "WRLD")

# compiler/linker settings
set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
set(CMAKE_)
set(CMAKE_OSX_ARCHITECTURES "armv7;arm64;i386")
set(IOS_WARNING_FLAGS "-Wmost -Werror -Wno-four-char-constants -Wno-unknown-pragmas -Wno-reorder")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++ ${IOS_WARNING_FLAGS}")
set(eegeo_sdk_libs "-lapps-on-maps-cpp11 -lapps-on-maps-cpp11-sim -lsdk-extensions-sqlite-cpp11 -lsdk-extensions-sqlite-cpp11-sim")

set(ios_frameworks 
  "-framework CoreLocation
  -framework CoreFoundation 
  -framework MobileCoreServices 
  -framework SystemConfiguration 
  -framework CFNetwork 
  -framework GLKit 
  -framework OpenGLES 
  -framework UIKit 
  -framework Foundation 
  -framework QuartzCore 
  -framework AVFoundation 
  -framework CoreGraphics 
  -framework CoreData
  -framework Security
  -framework CoreMotion
  -framework CoreBluetooth
  -framework IndoorAtlas
  -framework SLIndoorLocation
  -framework HockeySDK")

set(linker_search_paths "-LInclude/eegeo -LInclude")
set(framework_search_paths "${CMAKE_CURRENT_SOURCE_DIR}/Include/IndoorAtlas ${CMAKE_CURRENT_SOURCE_DIR}/Include/SenionLab ${CMAKE_CURRENT_SOURCE_DIR}/Include/HockeySDK-iOS/HockeySDK.embeddedframework")
set(libs "${eegeo_sdk_libs} -lturbojpeg -lz -lcurl -luv -lFlurry_6.0.0")
set(CMAKE_EXE_LINKER_FLAGS "${ios_frameworks} ${linker_search_paths} ${libs}")

include_directories(${headers})

add_executable(${executable_name} MACOSX_BUNDLE ${sources} ${resources} ${storyboards})

set(
allresources
${resources}
${storyboards}
)

set_target_properties(
${executable_name} 
PROPERTIES 
RESOURCE "${allresources}"
)
  
option(AUTOMATED_SCREENSHOTS "Build for screenshot automation." OFF)
if(AUTOMATED_SCREENSHOTS)
  add_definitions(-DAUTOMATED_SCREENSHOTS)
endif(AUTOMATED_SCREENSHOTS)

# project settings
set_xcode_property (${executable_name} DEBUG_INFORMATION_FORMAT[variant=Debug] "dwarf")
set_xcode_property (${executable_name} DEBUG_INFORMATION_FORMAT[variant=MinSizeRel] "dwarf-with-dsym")
set_xcode_property (${executable_name} DEBUG_INFORMATION_FORMAT[variant=RelWithDebInfo] "dwarf-with-dsym")
set_xcode_property (${executable_name} DEBUG_INFORMATION_FORMAT[variant=Release] "dwarf-with-dsym")

set_xcode_property (${executable_name} GCC_TREAT_WARNINGS_AS_ERRORS "YES")
set_xcode_property (${executable_name} CODE_SIGN_IDENTITY "iPhone Developer")
set_xcode_property (${executable_name} DEVELOPMENT_TEAM "")
set_xcode_property (${executable_name} IPHONEOS_DEPLOYMENT_TARGET "8.0")
set_xcode_property (${executable_name} TARGETED_DEVICE_FAMILY "1,2")
set_xcode_property (${executable_name} ENABLE_BITCODE "No")
set_xcode_property (${executable_name} INSTALL_PATH "/Applications")

set_xcode_property (${executable_name} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
set_xcode_property (${executable_name} ASSETCATALOG_COMPILER_LAUNCHIMAGE_NAME "LaunchImage")
set_xcode_property (${executable_name} COMBINE_HIDPI_IMAGES "No")

set_xcode_property(${executable_name} GCC_PRECOMPILE_PREFIX_HEADER "YES")
set_xcode_property(${executable_name} GCC_PREFIX_HEADER "ExampleApp/ExampleApp-Prefix.pch")
set_xcode_property(${executable_name} FRAMEWORK_SEARCH_PATHS "${framework_search_paths}")

set_xcode_property(${executable_name} CLANG_CXX_LANGUAGE_STANDARD "c++11")
set_xcode_property(${executable_name} CLANG_CXX_LIBRARY "libc++")

set_xcode_property(${executable_name} LD_RUNPATH_SEARCH_PATHS "@executable_path/Frameworks")

# Test Project Settings
if (BUILD_SNAPSHOT_TEST)
  set(CMAKE_Swift_COMPILER_FORCED 1)
  enable_language(Swift)

  # CMakeDetermineCompilerId appears to currently hard-code the version at certain points in the pbxproj.
  set_xcode_property(${executable_name} SWIFT_VERSION "2.3")
  unset_xcode_property(${executable_name} OTHER_SWIFT_FLAGS)

  find_package(XCTest REQUIRED)
  # CMake adds the xctest framework path to the compiler's include path which is forcibly injected into
  # OTHER_SWIFT_FLAGS.  This causes the header to be found twice by swift, resulting in the error 
  # "non-modular header inside framework module".  Clearing the framework include path solves the problem
  # and doesn't appear to have any adverse effect on the Obj-C side.
  set(XCTest_INCLUDE_DIRS "")
  
  xctest_add_bundle(FastlaneUITest ${TARGET_NAME}
    fastlane_uitest/UITests.mm
    fastlane_uitest/SnapshotHelper2-3.swift
    fastlane_uitest/Info.plist)
  set_target_properties(FastlaneUITest
    PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/fastlane_uitest/Info.plist)
  xctest_add_test(XCTest.FastlaneUITest FastlaneUITest)

  set_xcode_property(FastlaneUITest LD_RUNPATH_SEARCH_PATHS "$(inherited) @executable_path/Frameworks @loader_path/Frameworks")
  set_xcode_property(FastlaneUITest ONLY_ACTIVE_ARCH "YES")
  set_xcode_property(FastlaneUITest PRODUCT_BUNDLE_IDENTIFIER "com.eegeo.FastlaneUITest")
  unset_xcode_property(FastlaneUITest TEST_HOST)
  unset_xcode_property(FastlaneUITest BUNDLE_LOADER)
  set_xcode_property(FastlaneUITest USES_XCTRUNNER "YES")
  set_xcode_property(FastlaneUITest TEST_TARGET_NAME "${executable_name}")
  set_xcode_property(FastlaneUITest FRAMEWORK_SEARCH_PATHS "${framework_search_paths}")
  set_target_properties(FastlaneUITest PROPERTIES XCODE_PRODUCT_TYPE "com.apple.product-type.bundle.ui-testing")
endif (BUILD_SNAPSHOT_TEST)

set_target_properties(${PROJECT_NAME} PROPERTIES XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "YES")
set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/build/Debug-iphoneos/
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/build/Release-iphoneos/)

