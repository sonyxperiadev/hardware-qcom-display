/*
* Copyright (c) 2015-2019, The Linux Foundation. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted
* provided that the following conditions are met:
*    * Redistributions of source code must retain the above copyright notice, this list of
*      conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above copyright notice, this list of
*      conditions and the following disclaimer in the documentation and/or other materials provided
*      with the distribution.
*    * Neither the name of The Linux Foundation nor the names of its contributors may be used to
*      endorse or promote products derived from this software without specific prior written
*      permission.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utils/constants.h>
#include <utils/debug.h>
#include <utils/sys.h>
#include <dlfcn.h>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "hw_info.h"

#define __CLASS__ "HWInfo"

using std::vector;
using std::map;
using std::string;
using std::fstream;
using std::to_string;

namespace sdm {

// kDefaultFormatSupport contains the bit map of supported formats for each hw blocks.
// For eg: if Cursor supports MDP_RGBA_8888[bit-13] and MDP_RGB_565[bit-0], then cursor pipe array
// contains { 0x01[0-3], 0x00[4-7], 0x00[8-12], 0x01[13-16], 0x00[17-20], 0x00[21-24], 0x00[24-28] }
const std::bitset<8> HWInfo::kDefaultFormatSupport[kHWSubBlockMax][
                                                      BITS_TO_BYTES(MDP_IMGTYPE_LIMIT1)] = {
  { 0xFF, 0xF5, 0x1C, 0x1E, 0x20, 0xFF, 0x01, 0x00, 0xFE, 0x1F },  // kHWVIGPipe
  { 0x33, 0xE0, 0x00, 0x16, 0x00, 0xBF, 0x00, 0x00, 0xFE, 0x07 },  // kHWRGBPipe
  { 0x33, 0xE0, 0x00, 0x16, 0x00, 0xBF, 0x00, 0x00, 0xFE, 0x07 },  // kHWDMAPipe
  { 0x12, 0x60, 0x0C, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00 },  // kHWCursorPipe
  { 0xFF, 0xF5, 0x1C, 0x1E, 0x20, 0xFF, 0x01, 0x00, 0xFE, 0x1F },  // kHWRotatorInput
  { 0xFF, 0xF5, 0x1C, 0x1E, 0x20, 0xFF, 0x01, 0x00, 0xFE, 0x1F },  // kHWRotatorOutput
  { 0x3F, 0xF4, 0x10, 0x1E, 0x20, 0xFF, 0x01, 0x00, 0xAA, 0x16 },  // kHWWBIntfOutput
};

int HWInfo::ParseString(const char *input, char *tokens[], const uint32_t max_token,
                        const char *delim, uint32_t *count) {
  char *tmp_token = NULL;
  char *temp_ptr;
  uint32_t index = 0;
  if (!input) {
    return -1;
  }
  tmp_token = strtok_r(const_cast<char *>(input), delim, &temp_ptr);
  while (tmp_token && index < max_token) {
    tokens[index++] = tmp_token;
    tmp_token = strtok_r(NULL, delim, &temp_ptr);
  }
  *count = index;

  return 0;
}

DisplayError HWInfo::GetHWResourceInfo(HWResourceInfo *hw_resource) {
  if (hw_resource_) {
    *hw_resource = *hw_resource_;
    return kErrorNone;
  }
  string fb_path = "/sys/devices/virtual/graphics/fb"
                      + to_string(kHWCapabilitiesNode) + "/mdp/caps";

  Sys::fstream fs(fb_path, fstream::in);
  if (!fs.is_open()) {
    DLOGE("File '%s' not found", fb_path.c_str());
    return kErrorHardware;
  }

  hw_resource_ = new HWResourceInfo;

  InitSupportedFormatMap(hw_resource_);
  hw_resource_->hw_version = kHWMdssVersion5;

  uint32_t token_count = 0;
  const uint32_t max_count = 256;
  char *tokens[max_count] = { NULL };
  string line;
  while (Sys::getline_(fs, line)) {
    // parse the line and update information accordingly
    if (!ParseString(line.c_str(), tokens, max_count, ":, =\n", &token_count)) {
      if (!strncmp(tokens[0], "hw_rev", strlen("hw_rev"))) {
        hw_resource_->hw_version = UINT32(atoi(tokens[1]));  // HW Rev, v1/v2

      } else if (!strncmp(tokens[0], "pipe_count", strlen("pipe_count"))) {
        uint32_t pipe_count = UINT8(atoi(tokens[1]));
        for (uint32_t i = 0; i < pipe_count; i++) {
          Sys::getline_(fs, line);
          if (!ParseString(line.c_str(), tokens, max_count, ": =\n", &token_count)) {
            HWPipeCaps pipe_caps;
            pipe_caps.type = kPipeTypeUnused;
            for (uint32_t j = 0; j < token_count; j += 2) {
              if (!strncmp(tokens[j], "fmts_supported", strlen("fmts_supported"))) {
                char *tokens_fmt[max_count] = { NULL };
                // uint32_t token_fmt_count = 0;
                if (&tokens_fmt[0] == NULL) {}
              }
            }
            hw_resource_->hw_pipes.push_back(pipe_caps);
          }
        }
      }
    }
  }

  return kErrorNone;
}

LayerBufferFormat HWInfo::GetSDMFormat(int mdp_format) {
  switch (mdp_format) {
  default:                         return kFormatInvalid;
  }
}

void HWInfo::InitSupportedFormatMap(HWResourceInfo *hw_resource) {
}

void HWInfo::ParseFormats(char *tokens[], uint32_t token_count, HWSubBlockType sub_blk_type,
                          HWResourceInfo *hw_resource) {
  if (token_count > BITS_TO_BYTES(MDP_IMGTYPE_LIMIT1)) {
    return;
  }

  std::unique_ptr<std::bitset<8>[]> format_supported(new std::bitset<8>[token_count]);
  for (uint32_t i = 0; i < token_count; i++) {
    format_supported[i] = UINT8(atoi(tokens[i]));
  }

  PopulateSupportedFormatMap(format_supported.get(), (token_count << 3), sub_blk_type, hw_resource);
}

void HWInfo::PopulateSupportedFormatMap(const std::bitset<8> *format_supported,
                                        uint32_t format_count, HWSubBlockType sub_blk_type,
                                        HWResourceInfo *hw_resource) {
  vector <LayerBufferFormat> supported_sdm_formats;
  for (uint32_t mdp_format = 0; mdp_format < format_count; mdp_format++) {
    if (format_supported[mdp_format >> 3][mdp_format & 7]) {
      LayerBufferFormat sdm_format = GetSDMFormat(INT(mdp_format));
      if (sdm_format != kFormatInvalid) {
        supported_sdm_formats.push_back(sdm_format);
      }
    }
  }

  hw_resource->supported_formats_map.erase(sub_blk_type);
  hw_resource->supported_formats_map.insert(make_pair(sub_blk_type, supported_sdm_formats));
}

DisplayError HWInfo::GetFirstDisplayInterfaceType(HWDisplayInterfaceInfo *hw_disp_info) {
  Sys::fstream fs("/sys/devices/virtual/graphics/fb0/msm_fb_type", fstream::in);
  if (!fs.is_open()) {
    return kErrorHardware;
  }

  string line;
  if (!Sys::getline_(fs, line)) {
    return kErrorHardware;
  }

  if (!strncmp(line.c_str(), "dtv panel", strlen("dtv panel")) ||
      !strncmp(line.c_str(), "dp panel", strlen("dp panel"))) {
    hw_disp_info->type = kPluggable;
    DLOGI("First display is HDMI/pluggable");
  } else {
    hw_disp_info->type = kBuiltIn;
    DLOGI("First display is internal display");
  }

  fs.close();
  fs.open("/sys/devices/virtual/graphics/fb0/connected", fstream::in);
  if (!fs.is_open()) {
    // If fb0 is for a DSI/connected panel, then connected node will not exist.
    hw_disp_info->is_connected = true;
  } else {
    if (!Sys::getline_(fs, line)) {
      return kErrorHardware;
    }

    hw_disp_info->is_connected =  (!strncmp(line.c_str(), "1", strlen("1")));
  }

  return kErrorNone;
}

DisplayError HWInfo::GetDisplaysStatus(HWDisplaysInfo *hw_displays_info) {
  if (!hw_displays_info) {
    DLOGE("No output parameter provided!");
    return kErrorParameters;
  }
  hw_displays_info->clear();

  HWDisplayInterfaceInfo hw_disp_info = {};
  DisplayError ret = HWInfo::GetFirstDisplayInterfaceType(&hw_disp_info);
  if (ret != kErrorNone) {
    return ret;
  }

  HWDisplayInfo hw_info = {};
  hw_info.display_id = 0;
  hw_info.display_type = hw_disp_info.type;
  hw_info.is_connected = hw_disp_info.is_connected;
  hw_info.is_primary = hw_info.display_type == kPrimary;
  (*hw_displays_info)[hw_info.display_id] = hw_info;
  return kErrorNone;
}

DisplayError HWInfo::GetMaxDisplaysSupported(DisplayType type, int32_t *max_displays) {
  static DebugTag log_once = kTagNone;

  if (!max_displays) {
    DLOGE("No output parameter provided!");
    return kErrorParameters;
  }

  switch (type) {
    case kBuiltIn:
    case kPluggable:
    case kVirtual:
      *max_displays = 1;
      break;
    case kDisplayTypeMax:
      *max_displays = 3;
      break;
    default:
      *max_displays = 0;
      DLOGE("Unknown display type %d.", type);
      return kErrorParameters;
  }

  DLOGI_IF(log_once, "Max 3 concurrent displays.");
  DLOGI_IF(log_once, "Max 1 concurrent display of type %d (BuiltIn).", kBuiltIn);
  DLOGI_IF(log_once, "Max 1 concurrent display of type %d (Pluggable).", kPluggable);
  DLOGI_IF(log_once, "Max 1 concurrent display of type %d (Virtual).", kVirtual);

  log_once = kTagDisplay;

  return kErrorNone;
}

}  // namespace sdm

