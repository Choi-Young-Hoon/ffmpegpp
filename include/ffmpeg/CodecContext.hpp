#pragma once

#include <memory>

#include "ffmpeg/AVType.hpp"
#include "ffmpeg/AVResult.hpp"
#include "ffmpeg/Demuxer.hpp"
#include "ffmpeg/VideoEncodeParameters.hpp"
#include "ffmpeg/AudioEncodeParameters.hpp"
#include "ffmpeg/Rational.hpp"

namespace av {
    class CodecContext {
    public:
        explicit CodecContext();
        explicit CodecContext(AVCodecContext* codecContext);
        virtual ~CodecContext();

    public:
        CodecContext(const CodecContext&) = delete;
        CodecContext& operator=(const CodecContext&) = delete;

    public: // getter setter
        int64_t    getBitrate();
        MEDIA_TYPE getMediaType();

        void setAVCodecContext(AVCodecContext* codecContext);

        bool isVaildContext();
        bool isCUDAContext();

    public: // Raw pointer
        void setRawCodeContext(AVCodecContext* codecContext);

        AVCodecContext* getRawCodecContext();
        int             getRawHWFormat();

    private:
        AVCodecContext* codecContext;

        Rational timebase;
        Rational framerate;

        // 쿠다를 사용할경우
        int cudaDecodeHWFormat;
    };
    typedef std::shared_ptr<CodecContext> CodecContextPtr;


    // Decode AVCodecContext
    CodecContextPtr createVideoDecodeContext(Demuxer& demuxer, AVResult* result);
    CodecContextPtr createAudioDecodeContext(Demuxer& demuxer, AVResult* result);

    // Video Encode AVCodecContext
    CodecContextPtr createVideoEncodeContext(const std::string&& codecName, VideoEncodeParameters& encodeParameter, AVResult* result);
    CodecContextPtr createVideoEncodeContext(VIDEO_CODEC_ID codecID, VideoEncodeParameters& encodeParameter, AVResult* result);

    // Audio Encode AVCodecContext
    CodecContextPtr createAudioEncodeContext(const std::string&& codecName, AudioEncodeParameters& encodeParameter, AVResult* result);
    CodecContextPtr createAudioEncodeContext(AUDIO_CODEC_ID codecID, AudioEncodeParameters& encodeParameters, AVResult* result);


    // Video HW Decoder Encoder
    // Decoder
    CodecContextPtr createVideoCUDADecodeContext(Demuxer& demuxer, AVResult* result);
    CodecContextPtr createVideoCUDAEncoderContext(VIDEO_HW_CODEC_ID codecID, VideoEncodeParameters& encodeParameters, AVResult* result);
};