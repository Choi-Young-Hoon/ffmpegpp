#pragma once

#include <memory>
#include <functional>

#include "AVResult.hpp"
#include "Demuxer.hpp"
#include "Packet.hpp"
#include "Frame.hpp"
#include "CodecContext.hpp"

namespace av {
    typedef std::function<void(Packet&, Frame&)> DecoderCallbackFunc;

    class Decoder {
    public:
        explicit Decoder(CodecContextPtr videoContext, CodecContextPtr audioContext);
        virtual ~Decoder();

    public: // 이동 생성자 제거
        Decoder(const Decoder&) = delete;
        Decoder& operator=(const Decoder&) = delete;

    public:
        bool decode(Demuxer& demuxer, DecoderCallbackFunc func, AVResult* result);

    private:
        bool decodePacket(AVCodecContext* avCodecContext, AVPacket* avPacket, DecoderCallbackFunc func, AVResult* result);

    private:
        CodecContextPtr videoContext;
        CodecContextPtr audioContext;
    };
};