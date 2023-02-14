//
// Created by liyang on 2023/2/13.
//

#ifndef AURORE_RTMP_H
#define AURORE_RTMP_H

#include <cstring>
#include <cstdint>
#include <string>

using namespace std;

class Rtmp {

    uint16_t port_ = 1935;
    std::string url_;
    std::string tc_url_, swf_url_;
    std::string ip_;
    std::string app_;
    std::string stream_name_;
    std::string stream_path_;

    uint32_t peer_bandwidth_ = 5000000;
    uint32_t acknowledgement_size_ = 5000000;
    uint32_t max_chunk_size_ = 128;
    uint32_t max_gop_cache_len_ = 0;


    void SetChunkSize(uint32_t size) {
        if (size > 0 && size <= 60000) {
            max_chunk_size_ = size;
        }
    }

    void SetGopCache(uint32_t len = 5000) { max_gop_cache_len_ = len; }

    void SetPeerBandwidth(uint32_t size) { peer_bandwidth_ = size; }

    uint32_t GetChunkSize() const { return max_chunk_size_; }

    uint32_t GetGopCacheLen() const { return max_gop_cache_len_; }

    uint32_t GetAcknowledgementSize() const { return acknowledgement_size_; }

    uint32_t GetPeerBandwidth() const { return peer_bandwidth_; }

    std::string GetUrl() const { return url_; }

    std::string GetStreamPath() const { return stream_path_; }

    std::string GetApp() const { return app_; }

    std::string GetStreamName() const { return stream_name_; }

    std::string GetSwfUrl() const { return swf_url_; }

    std::string GetTcUrl() const { return tc_url_; }


    virtual int ParseRtmpUrl(std::string url) {
        char ip[100] = {0};
        char streamPath[500] = {0};
        char app[100] = {0};
        char streamName[400] = {0};
        uint16_t port = 0;

        if (strstr(url.c_str(), "rtmp://") == nullptr) {
            return -1;
        }

#if defined(__linux) || defined(__linux__)
        if (sscanf(url.c_str() + 7, "%[^:]:%hu/%s", ip, &port, streamPath) == 3)
#elif defined(WIN32) || defined(_WIN32)
            if (sscanf_s(url.c_str() + 7, "%[^:]:%hu/%s", ip, 100, &port, streamPath, 500) == 3)
#endif
        {
            port_ = port;
        }
#if defined(__linux) || defined(__linux__)
        else if (sscanf(url.c_str() + 7, "%[^/]/%s", ip, streamPath) == 2)
#elif defined(WIN32) || defined(_WIN32)
            else if (sscanf_s(url.c_str() + 7, "%[^/]/%s", ip, 100, streamPath, 500) == 2)
#endif
        {
            port_ = 1935;
        } else {
            return -1;
        }

        ip_ = ip;
        stream_path_ += "/";
        stream_path_ += streamPath;
        url_ = url;

#if defined(__linux) || defined(__linux__)
        if (sscanf(stream_path_.c_str(), "/%[^/]/%s", app, streamName) != 2)
#elif defined(WIN32) || defined(_WIN32)
            if (sscanf_s(stream_path_.c_str(), "/%[^/]/%s", app, 100, streamName, 400) != 2)
#endif
        {
            return -1;
        }

        app_ = app;
        stream_name_ = streamName;
        swf_url_ = tc_url_ = std::string("rtmp://") + ip_ + ":" + std::to_string(port_) + "/" + app_;
        return 0;
    }

};

#endif //AURORE_RTMP_H
