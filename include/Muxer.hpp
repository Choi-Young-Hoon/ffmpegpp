#pragma once

#include <string>
#include <vector>

extern "C" {
    #include "libavformat/avformat.h"
}

#include "AVResult.hpp"
#include "Demuxer.hpp"

namespace av {

class Muxer {
public:
    explicit Muxer();
    virtual ~Muxer();

public:
    bool mux(Demuxer& demuxer, const std::string& saveFileName, AVResult* result);

    bool open(const std::string& fileName, AVResult* result);
    void close();

    bool copyStreamsFrom(Demuxer& demuxer, AVResult* result);
    bool writeHeader(AVResult* result);

public: // Raw pointer
    AVFormatContext* getRawFormatContext();

private:
    bool copyPacketsFrom(Demuxer& demuxer, AVResult* result);

private:
    AVFormatContext* formatContext;    

    std::vector<int> streamsMapper;
};

};