LOCAL_PATH := $(call my-dir)
include $(LOCAL_PATH)/../common.mk

include $(CLEAR_VARS)

LOCAL_MODULE                  := libqdutils
LOCAL_VENDOR_MODULE           := true
LOCAL_MODULE_TAGS             := optional
LOCAL_SHARED_LIBRARIES        := $(common_libs) libbinder libqservice
LOCAL_C_INCLUDES              := $(common_includes) $(kernel_includes)
LOCAL_HEADER_LIBRARIES        := display_headers
LOCAL_HEADER_LIBRARIES        += libutils_headers

LOCAL_EXPORT_C_INCLUDE_DIRS := \
    $(LOCAL_PATH)

LOCAL_CFLAGS                  := $(common_flags) -DLOG_TAG=\"qdutils\" -Wno-sign-conversion
LOCAL_SRC_FILES               := qd_utils.cpp \
                                 display_config.cpp
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE                    := libqdMetaData
LOCAL_VENDOR_MODULE             := true
LOCAL_MODULE_TAGS               := optional

LOCAL_SHARED_LIBRARIES          := liblog libcutils
LOCAL_C_INCLUDES                := $(common_includes)
LOCAL_HEADER_LIBRARIES          := display_headers
LOCAL_HEADER_LIBRARIES          += libutils_headers
LOCAL_SRC_FILES                 := qdMetaData.cpp qd_utils.cpp
LOCAL_CFLAGS                    := $(common_flags) -Wno-sign-conversion
LOCAL_CFLAGS                    += -DLOG_TAG=\"DisplayMetaData\"

LOCAL_EXPORT_C_INCLUDE_DIRS := \
    $(LOCAL_PATH)

LOCAL_CFLAGS                    := $(common_flags) -Wno-sign-conversion
LOCAL_CFLAGS                    += -DLOG_TAG=\"DisplayMetaData\"
LOCAL_SRC_FILES                 := qdMetaData.cpp qd_utils.cpp
include $(BUILD_SHARED_LIBRARY)
