#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Typedef for unsigned integer
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Typedef for signed integer
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// Typedef for floating point number
typedef float f32;
typedef double f64;
typedef long double f128;

namespace athena::data::meteor {

enum meteor_telemetry_type { NONE = 0, ANALOG = 16, DIGITAL = 26 };

struct meteor_telemetry {
    /* @brief APID
     * 64 -> 69: image
     * 70: telemetry
     */
    std::string APID;
    double ccsds_time = 0.0;
    std::string msu_mr_id;
    std::string msu_mr_set;
    std::string type_name;
    meteor_telemetry_type type = NONE;
    std::vector<std::pair<std::string, std::string>> telemetry;
};

} // namespace athena::data::meteor

namespace athena::session {

enum athena_status { ATHENA_ERROR_CODE = 0, ATHENA_SUCCESS_CODE = 1 };
enum athena_mode { OFFLINE_MODE, LIVE_MODE };

/// One SDR frontend the mock (later: real) backend can open.
struct Device {
    int index = 0;
    std::string name;
    bool supportsOffsetTuning = false;
    std::vector<double> gainsDb;
};

/// Live lock / queue diagnostics pushed through SDRListener::onStatus.
struct Status {
    bool carrierLocked = false;
    bool symbolLocked = false;
    double queueHealth = 0.0;
    int iqCallbacks = 0;
    int fftFrames = 0;
};

struct DopplerPoint {
    double t = 0.0;
    double hz = 0.0;
};

/// Offline decode products delivered through DecodeListener::onResponse.
struct DecodeResult {
    std::shared_ptr<std::vector<athena::data::meteor::meteor_telemetry>>
        telemetry;
    std::vector<DopplerPoint> doppler;
    std::string dopplerLog;
};

/**
 * Live capture callbacks. Spectrum bins are the FFT row; waterfall is the
 * same data drawn as a history of rows (GUI-side), not a second payload.
 */
class SDRListener {
  public:
    virtual ~SDRListener() = default;

    virtual void onSpectrum(const std::vector<float> &bins) = 0;
    virtual void onStatus(const Status &status) = 0;
    virtual void onError(const std::string &message) = 0;
};

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

extern SDRListener* g_sdr_listener;
extern DecodeListener* g_decode_listener;

} // namespace athena::session
