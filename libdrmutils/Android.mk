LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE                  := libdrmutils
LOCAL_VENDOR_MODULE           := true
LOCAL_MODULE_TAGS             := optional
LOCAL_C_INCLUDES              := external/libdrm
LOCAL_HEADER_LIBRARIES        := display_headers
LOCAL_SHARED_LIBRARIES        := libdrm libdl libdisplaydebug
ifeq ($(TARGET_COMPILE_WITH_MSM_KERNEL),true)
LOCAL_C_INCLUDES          += $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
LOCAL_ADDITIONAL_DEPENDENCIES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr
endif
LOCAL_CFLAGS                  := -DLOG_TAG=\"DRMUTILS\" -Wall -std=c++11 -Werror -fno-operator-names
LOCAL_CLANG                   := true
LOCAL_SRC_FILES               := drm_master.cpp drm_res_mgr.cpp drm_lib_loader.cpp
LOCAL_COPY_HEADERS_TO         := qcom/display
LOCAL_COPY_HEADERS            := drm_master.h drm_res_mgr.h drm_lib_loader.h drm_logger.h drm_interface.h

include $(BUILD_SHARED_LIBRARY)
