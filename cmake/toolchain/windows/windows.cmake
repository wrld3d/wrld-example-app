# Options:
#

# Macros:
#
# remove_visual_studio_compiler_flag_debug (FLAG_TO_REMOVE)
#  A convenience macro for removing visual studio debug compiler flags
#  example: remove_visual_studio_compiler_flag_debug("/RTC1")

# Standard settings
set (WINDOWS True)
set (APPLE False)
set (IOS False)
set (OSX False)

macro (remove_visual_studio_compiler_flag_debug FLAG_TO_REMOVE)
	string(REPLACE ${FLAG_TO_REMOVE} "" TEMP_CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
	set(CMAKE_CXX_FLAGS_DEBUG ${TEMP_CMAKE_CXX_FLAGS_DEBUG})
endmacro (remove_visual_studio_compiler_flag_debug)