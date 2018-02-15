#include "vp8decoderproxy.h"

#include <iostream>
#include <stdio.h>
using namespace std;

#include "webrtc/base/file.h"
#define LIMIT_BYTE_SIZE 1024*1024

std::map<std::string, std::function<void(const webrtc::EncodedImage&, std::string label)> > encodedImageCallbacks;

static void VP8DecoderProxy::RegisterProxyCallback(std::string label,
                                                   std::function<void(const webrtc::EncodedImage&,
                                                                      std::string label)> encodedImageCallback) {
  encodedImageCallbacks[label] = encodedImageCallback;
}
static VP8DecoderProxy* VP8DecoderProxy::Create(std::string label) {

  return new VP8DecoderProxy(label);
}

VP8DecoderProxy::VP8DecoderProxy(std::string label) : label(label) {
  writer = webrtc::IvfFileWriter::Wrap(rtc::File::Create("out.ivf"), LIMIT_BYTE_SIZE);

  decoder = webrtc::VP8Decoder::Create();

}
VP8DecoderProxy::~VP8DecoderProxy() {
  delete decoder;
}
int32_t VP8DecoderProxy::InitDecode(const webrtc::VideoCodec* codec_settings,
                           int32_t number_of_cores) {
  return decoder->InitDecode(codec_settings, number_of_cores);
}

int32_t VP8DecoderProxy::Decode(const webrtc::EncodedImage& input_image,
                       bool missing_frames,
                       const webrtc::RTPFragmentationHeader* fragmentation,
                       const webrtc::CodecSpecificInfo* codec_specific_info = NULL,
                       int64_t render_time_ms = -1) {
  if(encodedImageCallbacks.find(label) != encodedImageCallbacks.end()) {
    encodedImageCallbacks[label](input_image, label);
  }
  writer->WriteFrame(input_image, webrtc::kVideoCodecVP8);
  return decoder->Decode(input_image, missing_frames, fragmentation, codec_specific_info, render_time_ms);
}

int32_t VP8DecoderProxy::RegisterDecodeCompleteCallback(
    webrtc::DecodedImageCallback* callback) {
  return decoder->RegisterDecodeCompleteCallback(callback);
}

int32_t VP8DecoderProxy::Release() {
  return decoder->Release();
}