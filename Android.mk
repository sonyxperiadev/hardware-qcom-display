ifneq ($(TARGET_DISABLE_DISPLAY),true)

display-hals := \
    include \
    libdebug \
    libqservice \
    libqdutils \
    sdm/libs/utils \
    sdm/libs/core \
    libcopybit \
    libmemtrack \
    hdmi_cec \
    sdm/libs/hwc2 \
    gpu_tonemapper \
    libdrmutils \
    libdisplayconfig

# All currently supported "legacy" devices use gralloc1
display-hals += gralloc1

include $(call all-named-subdir-makefiles,$(display-hals))

endif #TARGET_DISABLE_DISPLAY
