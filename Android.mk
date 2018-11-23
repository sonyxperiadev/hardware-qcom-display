ifneq ($(TARGET_DISABLE_DISPLAY),true)
sdm-libs := sdm/libs
display-hals := include libdebug libqservice libqdutils $(sdm-libs)/utils $(sdm-libs)/core

ifneq ($(TARGET_IS_HEADLESS), true)
    display-hals += libcopybit libmemtrack hdmi_cec \
                    $(sdm-libs)/hwc2 gpu_tonemapper libdrmutils libdisplayconfig
endif

ifeq ($(TARGET_USES_GRALLOC1), true)
display-hals += gralloc1
else
display-hals += gralloc
endif

ifeq ($(call is-vendor-board-platform,QCOM),true)
    include $(call all-named-subdir-makefiles,$(display-hals))
else
ifneq ($(filter msm% apq%,$(TARGET_BOARD_PLATFORM)),)
    include $(call all-named-subdir-makefiles,$(display-hals))
endif
endif
endif #TARGET_DISABLE_DISPLAY
