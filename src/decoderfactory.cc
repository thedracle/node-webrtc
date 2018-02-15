#include <vector>


#include "webrtc/modules/video_coding/codecs/h264/include/h264.h"  // nogncheck
#include "webrtc/modules/video_coding/codecs/vp8/include/vp8.h"  // nogncheck
#include "webrtc/modules/video_coding/codecs/vp9/include/vp9.h"  // nogncheck

#include "decoderfactory.h"
#include "vp8decoderproxy.h"
#include <iostream>
using namespace std;

webrtc::VideoDecoder* NodeDecoderFactory::CreateVideoDecoder(webrtc::VideoCodecType type) {
  cricket::VideoDecoderParams params;
  params.receive_stream_id = "UNKNOWN";
  return CreateVideoDecoder(type, params);
}
webrtc::VideoDecoder* NodeDecoderFactory::CreateVideoDecoder(
    webrtc::VideoCodecType type, cricket::VideoDecoderParams params) {
  switch(type) {
    case webrtc::kVideoCodecVP8:
      return VP8DecoderProxy::Create(params.receive_stream_id);
    case webrtc::kVideoCodecVP9:
      return webrtc::VP9Decoder::Create();
    case webrtc::kVideoCodecH264:
      return webrtc::H264Decoder::Create();
  }
  return nullptr;
}

void NodeDecoderFactory::DestroyVideoDecoder(webrtc::VideoDecoder* decoder) {
  decoder->Release();
}
