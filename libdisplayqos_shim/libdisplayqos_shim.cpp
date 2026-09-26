/*
 * LD_PRELOAD shim for vendor.qti.hardware.display.composer-service.
 * Intercepts QOSParserImpl::DetermineXML and overrides the XML path
 * for specific known HW versions. Any other version falls through
 * to the original implementation unchanged.
 */

#include <cstdint>
#include <cstdlib>
#include <string>
#include <dlfcn.h>
#include <debug_handler.h>

#define __CLASS__ "QOSParserImpl_shim"

/*
 * Mangled symbol for QOSParserImpl::DetermineXML(uint32_t, std::string*)
 * llvm-nm -D --defined-only libdisplayqos.so | grep 'DetermineXML'
 */
#define QOS_DETERMINE_XML_SYMBOL \
    "_ZN13QOSParserImpl12DetermineXMLEjPNSt3__112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE"

constexpr uint32_t kDpuVersionWaipio = 0x80010000;
constexpr uint32_t kDpuVersionParrot = 0x80030000;

/* Declaration: binds this name to the real mangled symbol. */
extern "C" __attribute__((visibility("default")))
int DetermineXML_shim(void* thiz, uint32_t hw_version, std::string* xml_path)
    __asm__(QOS_DETERMINE_XML_SYMBOL);

int DetermineXML_shim(void* instance, uint32_t hw_version, std::string* xml_path) {
    switch (hw_version) {
        case kDpuVersionWaipio:
            *xml_path = "/vendor/etc/display/DPU8__.xml";
            return 0;
        case kDpuVersionParrot:
            *xml_path = "/vendor/etc/display/DPU830.xml";
            return 0;
        default:
            break;
    }

    /* No override for this version: resolve and call the original. */
    void *resolved = dlsym(RTLD_NEXT, QOS_DETERMINE_XML_SYMBOL);
    if (!resolved) {
        /*
         * dlsym failed to find the original symbol (e.g. ABI mismatch,
         * renamed function in a newer ODM lib). We cannot safely continue
         * without the real implementation, so crash loudly instead of
         * silently misbehaving
         */
        DLOGE("dlsym failed to find original DetermineXML: %s", dlerror());
        abort();
    }

    DLOGI("Shimmed DetermineXML has no override for hw version %x; "
      "this library likely should not be built for this hw version",
      hw_version);

    using orig_fn_t = int(*)(void*, uint32_t, std::string*);
    auto orig_fn = reinterpret_cast<orig_fn_t>(resolved);
    return orig_fn(instance, hw_version, xml_path);
}
