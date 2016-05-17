
include $(CLEAR_VARS)

LOCAL_MODULE := recce-common-lib
LOCAL_SRC_FILES := $(shared_cpp_files:$(LOCAL_PATH)/%=%)
LOCAL_C_INCLUDES := $(includes:$(LOCAL_PATH)/%=%)
LOCAL_CFLAGS += ${cflags}
LOCAL_CPPFLAGS += ${cppflags}

include $(BUILD_STATIC_LIBRARY)
