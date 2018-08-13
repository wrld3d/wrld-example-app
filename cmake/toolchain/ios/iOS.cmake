# This file is based off of the Platform/Darwin.cmake and Platform/UnixPaths.cmake
# files which are included with CMake 2.8.4
# It has been altered for iOS development

# Options:
#
# [Optional] IOS_PLATFORM = OS | SIMULATOR
#   OS - build for iPhone and iPad physical devices, which have an arm arch.
#   SIMULATOR - build for Simulator platforms, i386 / x86_64 arch.
#	If this option is not supplied, IOS_PLATFORM is automaticallly derived from CMAKE_OSX_ARCHITECTURES if defined, else defaults to OS.
#
# [Optional] IOS_SDK_NAME = <SDK NAME>
# 	Specify an iOS SDK explicitly by name e.g. iphoneos11.0
#   If not supplied, IOS_SDK_NAME is automatically set to the most recent SDK version found under the selected iOS platform. 
#
# The iOS platform toolchain dir is chosen automatically based on the IOS_PLATFORM value and the currently
# active Xcode version. For example:
#	/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform
# If multiple Xcode apps are installed, xcode-select can be used to set the active Xcode version, eg:
#		sudo xcode-select --switch /Applications/Xcode-beta.app
#
# Macros supplied by this cmake toolchain for external use in CMakeLists:
#
# set_xcode_property (TARGET XCODE_PROPERTY XCODE_VALUE)
#  A convenience macro for setting xcode specific properties on targets
#  example: set_xcode_property (myioslib IPHONEOS_DEPLOYMENT_TARGET "3.1")
#
# find_host_package (PROGRAM ARGS)
#  A macro used to find executable programs on the host system, not within the iOS environment.
#  Thanks to the android-cmake project for providing the command


# 3.12 required for legacy build system support with Xcode 10:
# https://gitlab.kitware.com/cmake/cmake/issues/18099
cmake_minimum_required(VERSION 3.12)

# Informational Xcode version
message(STATUS "Xcode version:" )
execute_process(COMMAND xcodebuild -version )


# Determine value of IOS_PLATFORM
if (NOT DEFINED IOS_PLATFORM)
  if (CMAKE_OSX_ARCHITECTURES)
    if (CMAKE_OSX_ARCHITECTURES MATCHES ".*arm.*")
      set(IOS_PLATFORM "OS")
    elseif (CMAKE_OSX_ARCHITECTURES MATCHES "i386")
      set(IOS_PLATFORM "SIMULATOR")
    elseif (CMAKE_OSX_ARCHITECTURES MATCHES "x86_64")
      set(IOS_PLATFORM "SIMULATOR")
    endif()
  endif()
  if (NOT IOS_PLATFORM)
    set(IOS_PLATFORM "OS")
  endif ()
endif ()


message (STATUS "Using IOS_PLATFORM: ${IOS_PLATFORM}")
set (IOS_PLATFORM ${IOS_PLATFORM} CACHE STRING "iOS Platform")


# Determine xcodebuild platform name and build architecture from IOS_PLATFORM
if (IOS_PLATFORM STREQUAL "OS")
  set(__xcode_ios_platform iphoneos)
elseif (IOS_PLATFORM STREQUAL "SIMULATOR")
  set(__xcode_ios_platform iphonesimulator)
else()
  message(FATAL_ERROR "Unsupported IOS_PLATFORM value: ${IOS_PLATFORM}")
endif()

set(__xcode_ios_arch "$(ARCHS_STANDARD)")

message(STATUS "Using Xcode iOS platform: ${__xcode_ios_platform}")
message(STATUS "Using Xcode iOS architecture: ${__xcode_ios_arch}")


if (NOT DEFINED IOS_SDK_NAME)

	# get most recent installed sdk version for platform
	execute_process(
		COMMAND xcrun --sdk ${__xcode_ios_platform} --show-sdk-version
	  	OUTPUT_VARIABLE __ios_sdk_version
	  	ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
	)

  	set (IOS_SDK_NAME ${__xcode_ios_platform}${__ios_sdk_version})
  	message (STATUS "IOS_SDK_NAME not specified, defaulting to: ${IOS_SDK_NAME}")
endif ()

message (STATUS "Using IOS_SDK_NAME: ${IOS_SDK_NAME}")

# get sdk path
execute_process(
	COMMAND xcrun --sdk ${IOS_SDK_NAME} --show-sdk-path
	OUTPUT_VARIABLE __xcode_ios_sdk_root
	RESULT_VARIABLE __xcode_ios_sdk_root_error
	ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
)

if (__xcode_ios_sdk_root_error)

	execute_process(
		COMMAND xcodebuild -showsdks
		OUTPUT_VARIABLE __available_sdk_list
		ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
	)


  	message (STATUS "Could not find sdk for IOS_SDK_NAME=${IOS_SDK_NAME}")
  	message (STATUS "Available installed sdks are: \n${__available_sdk_list}")
  	message (FATAL_ERROR "Aborting due")
endif()

#get_filename_component(__xcode_ios_sdk_toolchain ${__xcode_ios_sdk_root} NAME)

if (NOT EXISTS ${__xcode_ios_sdk_root})
  message(FATAL_ERROR "__xcode_ios_sdk_root: '${__xcode_ios_sdk_root}' path does not exist.")
endif()

# get sdk version
execute_process(
	COMMAND xcrun --sdk ${__xcode_ios_sdk_root} --show-sdk-version
  	OUTPUT_VARIABLE __ios_sdk_version
  	ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "Using iOS SDK version: ${__ios_sdk_version}")





# (osx) cmake toolchain sets SDKROOT from CMAKE_OSX_SYSROOT. In Xcode, this populates 'Base SDK' field in build settings. 
# Setting CMAKE_OSX_SYSROOT to lowercase sdk name rather than full path appears to fix xcode "missing SDK" errors in Xcode IDE.
# Querying build settings via xcodebuild continues to return path, eg
# xcodebuild -project <Project>.xcodeproj -target <targetAppName> -showBuildSettings | grep SDKROOT
# -> SDKROOT = /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS11.0.sdk
set (CMAKE_OSX_SYSROOT ${IOS_SDK_NAME} CACHE PATH "Sysroot used for iOS support" FORCE)
message (STATUS "Using CMAKE_OSX_SYSROOT: ${CMAKE_OSX_SYSROOT}")



# Determine __xcode_ios_sdk_platform_path
execute_process(
    COMMAND xcrun --sdk ${__xcode_ios_sdk_root} --show-sdk-platform-path
    OUTPUT_VARIABLE __xcode_ios_sdk_platform_path
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
)

if (NOT EXISTS ${__xcode_ios_sdk_platform_path})
  message(FATAL_ERROR "iOS SDK Platform path: ${__xcode_ios_sdk_platform_path} path does not exist.")
endif()


# Configure compiler and lib tools
if (NOT CMAKE_C_COMPILER)
  execute_process(COMMAND xcrun --sdk ${__xcode_ios_sdk_root} -find clang
    OUTPUT_VARIABLE CMAKE_C_COMPILER
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
  )
endif()

if (NOT CMAKE_CXX_COMPILER)
  execute_process(COMMAND xcrun --sdk ${__xcode_ios_sdk_root} -find clang++
    OUTPUT_VARIABLE CMAKE_CXX_COMPILER
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
  )
endif()

if (NOT CMAKE_LIBTOOL)
	execute_process(COMMAND xcrun --sdk ${__xcode_ios_sdk_root} -find libtool
	  OUTPUT_VARIABLE CMAKE_LIBTOOL
	  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	set(CMAKE_LIBTOOL ${CMAKE_LIBTOOL} CACHE FILEPATH "Libtool")
endif()

if (NOT CMAKE_CODESIGN)
	execute_process(COMMAND xcrun -sdk ${CMAKE_OSX_SYSROOT} -find codesign
   		OUTPUT_VARIABLE CMAKE_CODESIGN
   		ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
   	)
  	set(CMAKE_CODESIGN ${CMAKE_CODESIGN} CACHE FILEPATH "Codesign")
endif()

if (NOT CMAKE_CODESIGN_ALLOCATE)
	execute_process(COMMAND xcrun -sdk ${CMAKE_OSX_SYSROOT} -find codesign_allocate
   		OUTPUT_VARIABLE CMAKE_CODESIGN_ALLOCATE
   		ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
   	)
  	set(CMAKE_CODESIGN_ALLOCATE ${CMAKE_CODESIGN_ALLOCATE} CACHE FILEPATH "codesign_allocate")
endif()


message(STATUS "Using C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Using CXX compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Using libtool: ${CMAKE_LIBTOOL}")
message(STATUS "Using codesign: ${CMAKE_CODESIGN}")
message(STATUS "Using codesign_allocate: ${CMAKE_CODESIGN_ALLOCATE}")



# Get macOS version of host
execute_process(COMMAND uname -r
  OUTPUT_VARIABLE CMAKE_HOST_SYSTEM_VERSION
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "Using host macOS version: ${CMAKE_HOST_SYSTEM_VERSION}")




# Standard settings
set (CMAKE_SYSTEM_NAME Darwin CACHE INTERNAL "")
set (CMAKE_SYSTEM_VERSION ${__ios_sdk_version} CACHE INTERNAL "")
set (UNIX True CACHE BOOL "")
set (APPLE True CACHE BOOL "")
set (IOS True CACHE BOOL "")
set (CMAKE_RANLIB ranlib CACHE FILEPATH "" FORCE)
set (CMAKE_AR ar CACHE FILEPATH "" FORCE)
set (CMAKE_OSX_DEPLOYMENT_TARGET "" CACHE STRING "Force unset of the OSX-specific deployment target for iOS" FORCE)
set (CMAKE_OSX_ARCHITECTURES ${__xcode_ios_arch} CACHE string  "iOS build architectures" FORCE)
message (STATUS "Using CMAKE_OSX_ARCHITECTURES: ${CMAKE_OSX_ARCHITECTURES}")



# Skip platform compiler checks for cross compiling
set (CMAKE_CXX_COMPILER_FORCED TRUE)
set (CMAKE_C_COMPILER_FORCED TRUE)
set (CMAKE_CXX_COMPILER_WORKS TRUE)
set (CMAKE_C_COMPILER_WORKS TRUE)



# All iOS/Darwin specific settings - some may be redundant
set (CMAKE_SHARED_LIBRARY_PREFIX "lib")
set (CMAKE_SHARED_LIBRARY_SUFFIX ".dylib")
set (CMAKE_SHARED_MODULE_PREFIX "lib")
set (CMAKE_SHARED_MODULE_SUFFIX ".so")
set (CMAKE_MODULE_EXISTS 1)
set (CMAKE_DL_LIBS "")
set (CMAKE_C_OSX_COMPATIBILITY_VERSION_FLAG "-compatibility_version ")
set (CMAKE_C_OSX_CURRENT_VERSION_FLAG "-current_version ")
set (CMAKE_CXX_OSX_COMPATIBILITY_VERSION_FLAG "${CMAKE_C_OSX_COMPATIBILITY_VERSION_FLAG}")
set (CMAKE_CXX_OSX_CURRENT_VERSION_FLAG "${CMAKE_C_OSX_CURRENT_VERSION_FLAG}")

set (CMAKE_C_FLAGS_INIT "")
# Hidden visibilty is required for cxx on iOS 
set (CMAKE_CXX_FLAGS_INIT "-fvisibility=hidden -fvisibility-inlines-hidden")



set (CMAKE_C_LINK_FLAGS "-Wl,-search_paths_first ${CMAKE_C_LINK_FLAGS}")
set (CMAKE_CXX_LINK_FLAGS "-Wl,-search_paths_first ${CMAKE_CXX_LINK_FLAGS}")

set (CMAKE_PLATFORM_HAS_INSTALLNAME 1)
set (CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS "-dynamiclib -headerpad_max_install_names")
set (CMAKE_SHARED_MODULE_CREATE_C_FLAGS "-bundle -headerpad_max_install_names")
set (CMAKE_SHARED_MODULE_LOADER_C_FLAG "-Wl,-bundle_loader,")
set (CMAKE_SHARED_MODULE_LOADER_CXX_FLAG "-Wl,-bundle_loader,")
set (CMAKE_FIND_LIBRARY_SUFFIXES ".dylib" ".so" ".a")

# hack: if a new cmake (which uses CMAKE_INSTALL_NAME_TOOL) runs on an old build tree
# (where install_name_tool was hardcoded) and where CMAKE_INSTALL_NAME_TOOL isn't in the cache
# and still cmake didn't fail in CMakeFindBinUtils.cmake (because it isn't rerun)
# hardcode CMAKE_INSTALL_NAME_TOOL here to install_name_tool, so it behaves as it did before, Alex
if (NOT DEFINED CMAKE_INSTALL_NAME_TOOL)
	find_program(CMAKE_INSTALL_NAME_TOOL install_name_tool)
endif (NOT DEFINED CMAKE_INSTALL_NAME_TOOL)



set (CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Set the find root to the iOS developer roots and to user defined paths
set (CMAKE_FIND_ROOT_PATH ${__xcode_ios_sdk_platform_path}/Developer ${CMAKE_OSX_SYSROOT} ${CMAKE_PREFIX_PATH} CACHE string "iOS find search path root" FORCE)

# default to searching for frameworks first
set (CMAKE_FIND_FRAMEWORK FIRST)

# set up the default search directories for frameworks
set (CMAKE_SYSTEM_FRAMEWORK_PATH
	${__xcode_ios_sdk_root}/System/Library/Frameworks
	${__xcode_ios_sdk_root}/System/Library/PrivateFrameworks
	${__xcode_ios_sdk_root}/Developer/Library/Frameworks
)

# only search the iOS sdks, not the remainder of the host filesystem
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)



# This little macro lets you set any XCode specific property
macro (set_xcode_property TARGET XCODE_PROPERTY XCODE_VALUE)
	set_property (TARGET ${TARGET} PROPERTY XCODE_ATTRIBUTE_${XCODE_PROPERTY} ${XCODE_VALUE})
endmacro (set_xcode_property)


# This macro lets you find executable programs on the host system
macro (find_host_package)
	set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
	set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
	set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)
	set (IOS FALSE)

	find_package(${ARGN})

	set (IOS TRUE)
	set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
	set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
	set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endmacro (find_host_package)