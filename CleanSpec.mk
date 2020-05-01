# Clean old composer
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/bin/hw/android.hardware.graphics.composer@2.1-service)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/etc/init/android.hardware.graphics.composer@2.1-service.rc)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib64/hw/android.hardware.graphics.composer@2.1-impl.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/bin/hw/android.hardware.graphics.composer@2.2-service)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/etc/init/android.hardware.graphics.composer@2.2-service.rc)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib64/hw/android.hardware.graphics.composer@2.2-impl.so)


# Clean old target objs
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib64/hw/hwcomposer.msmnile.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib/hw/hwcomposer.msmnile.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib64/hw/gralloc.msmnile.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib/hw/gralloc.msmnile.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib64/hw/lights.msmnile.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib/hw/lights.msmnile.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib64/hw/memtrack.msmnile.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib/hw/memtrack.msmnile.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib64/hw/hwcomposer.trinket.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib/hw/hwcomposer.trinket.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib64/hw/gralloc.trinket.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib/hw/gralloc.trinket.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib64/hw/lights.trinket.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib/hw/lights.trinket.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib64/hw/memtrack.trinket.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib/hw/memtrack.trinket.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib64/hw/hwcomposer.talos.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib/hw/hwcomposer.talos.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib64/hw/gralloc.talos.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib/hw/gralloc.talos.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib64/hw/lights.talos.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib/hw/lights.talos.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib64/hw/memtrack.talos.so)
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/lib/hw/memtrack.talos.so)

# Clean display includes
$(call add-clean-step, rm -rf $(TARGET_OUT_HEADERS)/qcom/display)

# Clean old allocator rc file
$(call add-clean-step, rm -rf $(PRODUCT_OUT)/$(TARGET_COPY_OUT_VENDOR)/vendor/etc/init/vendor.qti.hardware.display.allocator@1.0-service.rc)
