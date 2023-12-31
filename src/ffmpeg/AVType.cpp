#include "ffmpeg/AVType.hpp"

extern "C" {
#include "libavformat/avformat.h"
}

namespace av {

    int videoCodecIDToAVCodecID(VIDEO_CODEC_ID videoCodecID) {
        switch (videoCodecID) {
            case VIDEO_CODEC_ID::H264: return AV_CODEC_ID_H264;
            case VIDEO_CODEC_ID::H265: return AV_CODEC_ID_H265;
        }
        return AV_CODEC_ID_NONE;
    }

    std::string videoHWCodecIDToString(VIDEO_HW_CODEC_ID codecID) {
        switch (codecID) {
            case VIDEO_HW_CODEC_ID::H264: return "h264_nvenc";
        }
        return "";
    }

    int audioCodecIDToAVCodecID(AUDIO_CODEC_ID audioCodecId) {
        switch (audioCodecId) {
            case AUDIO_CODEC_ID::AAC: return AV_CODEC_ID_AAC;
            case AUDIO_CODEC_ID::AC3: return AV_CODEC_ID_AC3;
        }
        return AV_CODEC_ID_NONE;
    }

    int mediaTypeToAVMediaType(MEDIA_TYPE type) {
        switch (type) {
            case MEDIA_TYPE::UNKNOWN:    return AVMEDIA_TYPE_UNKNOWN;
            case MEDIA_TYPE::VIDEO:      return AVMEDIA_TYPE_VIDEO;
            case MEDIA_TYPE::AUDIO:      return AVMEDIA_TYPE_AUDIO;
            case MEDIA_TYPE::DATA:       return AVMEDIA_TYPE_DATA;
            case MEDIA_TYPE::SUBTITLE:   return AVMEDIA_TYPE_SUBTITLE;
            case MEDIA_TYPE::ATTACHMENT: return AVMEDIA_TYPE_ATTACHMENT;
            case MEDIA_TYPE::NB:         return AVMEDIA_TYPE_NB;
        }
        return AVMEDIA_TYPE_UNKNOWN;
    }

    MEDIA_TYPE AVMediaTypeToMediaType(int type) {
        switch ((AVMediaType)type) {
            case AVMEDIA_TYPE_UNKNOWN:    return MEDIA_TYPE::UNKNOWN;
            case AVMEDIA_TYPE_VIDEO:      return MEDIA_TYPE::VIDEO;
            case AVMEDIA_TYPE_AUDIO:      return MEDIA_TYPE::AUDIO;
            case AVMEDIA_TYPE_DATA:       return MEDIA_TYPE::DATA;
            case AVMEDIA_TYPE_SUBTITLE:   return MEDIA_TYPE::SUBTITLE;
            case AVMEDIA_TYPE_ATTACHMENT: return MEDIA_TYPE::ATTACHMENT;
            case AVMEDIA_TYPE_NB:         return MEDIA_TYPE::NB;
        }

        return MEDIA_TYPE::UNKNOWN;
    }

    int pixelFormatToAVPixelFormat(PIXEL_FORMAT format) {
        switch (format) {
            case PIXEL_FORMAT::NONE:    return AV_PIX_FMT_NONE;
            case PIXEL_FORMAT::YUV420P: return AV_PIX_FMT_YUV420P;
        }

        return AV_PIX_FMT_NONE;
    }

    int sampleFormatToAVSampleFormat(SAMPLE_FORMAT format) {
        switch (format) {
            case SAMPLE_FORMAT::NONE: return AV_SAMPLE_FMT_NONE;
            case SAMPLE_FORMAT::S16:  return AV_SAMPLE_FMT_S16;
            case SAMPLE_FORMAT::S16P: return AV_SAMPLE_FMT_S16P;
            case SAMPLE_FORMAT::FLTP: return AV_SAMPLE_FMT_FLTP;
        }

        return AV_SAMPLE_FMT_NONE;
    }

};