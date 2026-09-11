#pragma once

#include "station.h"
#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace athena::session {
/**
 * Callbacks for one decode() run. Progress is 0–100.
 * onResponse and onError are mutually exclusive for a given call.
 */
class DecodeListener {
  public:
    virtual ~DecodeListener() = default;

    virtual void onUpdate(int progress) = 0;
    virtual void onResponse(const DecodeResult &result) = 0;
    virtual void onError(const std::string &message) = 0;
};

/// Live (0) or Offline (1). Matches the SessionParameter decode-mode toggle.
enum Mode { Live = 0, Offline = 1 };

void open();
void close();

/// Request/return: enumerate RTL-SDR (and stand-in) frontends.
std::vector<Device> listDevices();

void setMode(int mode);
void setDevice(int index);
void setFrequencyHz(std::int64_t hz);
void setSampleRateHz(int hz);
void setSampleType(int type);
void setGainMode(int mode);
void setGainIndex(int index);
void setOffsetTuning(bool enabled);
void setStopLevel(int level);
void setDopplerLogging(bool enabled);
void setFftSize(int size);
void setFftRateHz(int rate);
void setWaterfallRateHz(int rate);
void setAvgNum(int n);
void setOutputDirectory(const std::string &path);
void setPipeline(int index);
void setBasebandFormat(int format);
void setInputFile(const std::string &path);

/// Blocking live loop. Returns after stopCapture().
void capture(SDRListener &listener);
void stopCapture();

/// Store the session record directory. The mock does not write files.
void record(const std::string &path);
void stopRecord();

/// Blocking decode. Returns after finish or cancelDecode().
void decode(DecodeListener &listener);
void cancelDecode();

extern SDRListener *g_sdr_listener;
extern DecodeListener *g_decode_listener;

} // namespace athena::session
