#pragma once

#include <string>
#include <vector>

#include "AVType.hpp"
#include "AVResult.hpp"
#include "Demuxer.hpp"
#include "CodecContext.hpp"
#include "Packet.hpp"

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
    bool createNewStream(CodecContextPtr codecContext, AVResult* result);
    
    bool writeHeader(AVResult* result);
    bool writePacket(Packet& packet, AVResult* result);
    
public: // Raw pointer
    AVFormatContext* getRawFormatContext();
    AVStream* getRawStream(MEDIA_TYPE type);
    
private:
    bool copyPacketsFrom(Demuxer& demuxer, AVResult* result);
    
private:
    AVFormatContext* formatContext;    

    std::vector<int> streamsMapper;
};

};