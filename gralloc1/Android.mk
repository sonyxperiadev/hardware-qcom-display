# Gralloc module
LOCAL_PATH := $(call my-dir)
include $(LOCAL_PATH)/../common.mk
include $(CLEAR_VARS)

LOCAL_MODULE                  := gralloc.$(TARGET_BOARD_PLATFORM)
LOCAL_VENDOR_MODULE           := true
LOCAL_MODULE_RELATIVE_PATH    := hw
LOCAL_MODULE_TAGS             := optional
LOCAL_C_INCLUDES              := $(common_includes)

LOCAL_HEADER_LIBRARIES        := display_headers
LOCAL_SHARED_LIBRARIES        := $(common_libs) libqdMetaData libsync libgrallocutils
LOCAL_CFLAGS                  := $(common_flags) -DLOG_TAG=\"qdgralloc\" -Wall -Werror
LOCAL_CLANG                   := true
LOCAL_SRC_FILES               := gr_ion_alloc.cpp \
                                 gr_allocator.cpp \
                                 gr_buf_mgr.cpp \
                                 gr_device_impl.cpp

ifeq ($(call is-board-platform-in-list, msm8909), true)
    LOCAL_CFLAGS += -DUSE_SECURE_HEAP
endif

include $(BUILD_SHARED_LIBRARY)

#libgrallocutils
include $(CLEAR_VARS)
LOCAL_MODULE                  := libgrallocutils
LOCAL_VENDOR_MODULE           := true
LOCAL_MODULE_TAGS             := optional
LOCAL_C_INCLUDES              := $(common_includes) $(kernel_includes)
LOCAL_HEADER_LIBRARIES        := display_headers
LOCAL_SHARED_LIBRARIES        := $(common_libs) libqdMetaData libdl
LOCAL_CFLAGS                  := $(common_flags) -DLOG_TAG=\"grallocutils\" -Wno-sign-conversion
LOCAL_SRC_FILES               := gr_utils.cpp gr_adreno_info.cpp
include $(BUILD_SHARED_LIBRARY)
