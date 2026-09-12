#pragma once

#include <cstdint>
#include <memory>
#include <string>
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
/// Live lock / queue diagnostics pushed through SDRListener::onStatus.
struct Status {
    bool carrierLocked = false;
    bool symbolLocked = false;
    double queueHealth = 0.0;
    int iqCallbacks = 0;
    int fftFrames = 0;
};

enum athena_status { ATHENA_ERROR_CODE = 0, ATHENA_SUCCESS_CODE = 1 };
enum athena_mode { OFFLINE_MODE, LIVE_MODE };

/// One SDR frontend the mock (later: real) backend can open.
struct Device {
    int index = 0;
    std::string name;
    bool supportsOffsetTuning = false;
    std::vector<double> gainsDb;
};

struct DopplerPoint {
    double t = 0.0;
    double hz = 0.0;
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
/// Offline decode products delivered through DecodeListener::onResponse.
struct DecodeResult {
    std::shared_ptr<std::vector<athena::data::meteor::meteor_telemetry>>
        telemetry;
    std::vector<DopplerPoint> doppler;
    std::string dopplerLog;
};
