#include "Decoder.hpp"

extern "C" {
    #include "libavformat/avformat.h"
    #include "libavcodec/avcodec.h"
}

namespace av {

Decoder::Decoder(CodecContextPtr videoContext, CodecContextPtr audioContext) 
: videoContext(videoContext)
, audioContext(audioContext) {

}

Decoder::~Decoder() {

}

bool Decoder::decode(Demuxer& demuxer, DecoderCallbackFunc func, AVResult* result) {
    if (result == nullptr) {
        return false;
    }

    Packet packet;
    while (demuxer.read(&packet, result)) {
        bool decodeResult;
        if (packet.getStreamIndex() == demuxer.getVideoStreamIndex()) {
            packet.setMediaType(this->videoContext->getMediaType());
            decodeResult = this->decodePacket(this->videoContext->getRawCodecContext(), packet.getRawPacket(), func, result);
        } else if (packet.getStreamIndex() == demuxer.getAudioStreamIndex()) {
            packet.setMediaType(this->audioContext->getMediaType());
            decodeResult = this->decodePacket(this->audioContext->getRawCodecContext(), packet.getRawPacket(), func, result);
        }
        packet.unref();

        if (result->isSuccess() == false) {
            return result->isSuccess();
        }

        if (decodeResult == false) {
            break;
        }
    }

    // flush AVCodecContext
    if (this->videoContext->isVaildContext()) { // AVCodecContext not nullptr
        this->decodePacket(this->videoContext->getRawCodecContext(), nullptr, func, result);
    } else if (this->audioContext->isVaildContext()) { // AVCodecContext not nullptr
        this->decodePacket(this->audioContext->getRawCodecContext(), nullptr, func, result);
    }

    return result->success();
}

bool Decoder::decodePacket(AVCodecContext* avCodecContext, AVPacket* avPacket, DecoderCallbackFunc func, AVResult* result) {
    if (avCodecContext == nullptr) {
        return true;
    }
    
    int ret = 0;

    ret = avcodec_send_packet(avCodecContext, avPacket);
    if (ret < 0) {
        return result->avFailed(ret);
    }

    Frame frame;
    while (ret >= 0) {
        ret = avcodec_receive_frame(avCodecContext, frame.getRawFrame());
        if (ret < 0) {
            if (ret == AVERROR_EOF ||
                ret == AVERROR(EAGAIN)) {
                return result->success();
            }
            return result->avFailed(ret);
        }

        Packet packet(avPacket);
        func(packet, frame);
        // callback에 Packet을 넘겨줘야해서 Packet 생성자를 이용했으나 소멸자에서 해제가 되는것을 막기위함임... 
        // 어떻게하지
        packet.setRawPacket(nullptr); 


        frame.unref();
    }
    return result->success();
}
};