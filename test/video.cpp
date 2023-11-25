#include "gtest/gtest.h"

#include "TEST_DEFINE.hpp"

#include "AVType.hpp"
#include "AVResult.hpp"
#include "Demuxer.hpp"
#include "CodecContext.hpp"
#include "Decoder.hpp"
#include "Packet.hpp"
#include "Frame.hpp"
#include "Muxer.hpp"
#include "EncodeParameter.hpp"

TEST(Demuxer, Demuxer_Open) {
    av::AVResult result;

    av::Demuxer demuxer;
    demuxer.open(TEST::MP4_FILE, &result);
    ASSERT_TRUE(result.isSuccess());

    demuxer.printDump();

    demuxer.close();
}

TEST(Demuxer, Demuxer_ReadPacket) {
    av::AVResult result;

    av::Demuxer demuxer;
    demuxer.open(TEST::MP4_FILE, &result);
    ASSERT_TRUE(result.isSuccess());

    av::Packet packet;
    while (demuxer.read(&packet, &result)) {
        //std::cout << packet.getPTS() << " "
        //          << packet.getDTS() << " "
        //          << packet.getSize() << std::endl;
        packet.unref();
    }

    demuxer.close();
}

static void save_gray_frame(unsigned char *buf, int wrap, int xsize, int ysize, const char *filename)
{
    FILE *f;
    int i;
    f = fopen(filename,"w");
    // writing the minimal required header for a pgm file format
    // portable graymap format -> https://en.wikipedia.org/wiki/Netpbm_format#PGM_example
    fprintf(f, "P5\n%d %d\n%d\n", xsize, ysize, 255);

    // writing line by line
    for (i = 0; i < ysize; i++)
        fwrite(buf + i * wrap, 1, xsize, f);
    fclose(f);
}

TEST(Decoder, Decoder_Decode) {
    av::AVResult result;

    av::Demuxer demuxer;
    demuxer.open(TEST::MP4_FILE, &result);
    ASSERT_TRUE(result.isSuccess());

    auto decodeVideoCodecContext = av::createVideoDecodeContext(demuxer, &result);
    ASSERT_TRUE(result.isSuccess());
    auto decodeAudioCodecContext = av::createAudioDecodeContext(demuxer, &result);
    ASSERT_TRUE(result.isSuccess());

    av::Decoder decoder(decodeVideoCodecContext, decodeAudioCodecContext);
    decoder.decode(demuxer, [&](av::MEDIA_TYPE type, av::Frame& frame) {
        if (type == av::MEDIA_TYPE::VIDEO) {
            //AVFrame* avframe = frame.getRawFrame();
            //save_gray_frame(avframe->data[0], avframe->linesize[0], avframe->width, avframe->height, "test.pgm");
            //frame.printDump();
        } else if (type == av::MEDIA_TYPE::AUDIO) {
            //std::cout << "Audio frame!!" << std::endl;
        }
    }, &result);
    ASSERT_TRUE(result.isSuccess());
}

TEST(Muxer, Muxer_Mux) {
    av::AVResult result;

    av::Demuxer demuxer;
    demuxer.open(TEST::MP4_FILE, &result);
    ASSERT_TRUE(result.isSuccess());

    av::Muxer muxer;
    muxer.mux(demuxer, TEST::MKV_FILE, &result);
    ASSERT_TRUE(result.isSuccess());
}

TEST(Encoder, Encoder_encode) {
    av::AVResult result;

    av::EncodeParameter encodeParameter;
    encodeParameter.setBitrate(400000);
    encodeParameter.setWidth(1900);
    encodeParameter.setHeight(1680);
    encodeParameter.setTimeBase(av::Rational(1, 25));
    encodeParameter.setFrameRate(av::Rational(25, 1));
    encodeParameter.setGOPSize(10);
    encodeParameter.setMaxBFrames(0);
    encodeParameter.setPixelFormat(av::PIXEL_FORMAT::YUV420P);

    auto codecContext = av::createEncodeContext(av::CODEC_ID::H264, encodeParameter, &result);
    ASSERT_TRUE(result.isSuccess());

    av::Muxer muxer;
    muxer.open(TEST::OUTPUT_MP4_FILE, &result);
    ASSERT_TRUE(result.isSuccess());

    muxer.createNewStream(codecContext, &result);
    ASSERT_TRUE(result.isSuccess());

    muxer.writeHeader(&result);
    ASSERT_TRUE(result.isSuccess());
}