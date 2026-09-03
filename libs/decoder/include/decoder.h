#pragma once

#ifndef ATHENA_CORE
#define ATHENA_CORE

#include "telemetry.h"
#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

namespace athena::decoder {
enum athena_status { ATHENA_ERROR_CODE = 0, ATHENA_SUCCESS_CODE = 1 };
enum athena_mode { OFFLINE_MODE, LIVE_MODE };

/* @brief Baseband typy
 */
enum baseband_t {
    CF_32,
    CS_32,
    CS_16,
    CS_8,
    CU_8,
    WAV_16,
};

/* @brief Until type code
 */
enum until_t { SOFT, CADU, PRODUCTS };

/* @brief Command structure
 */
class cmd {
  public:
    /* @brief Pipelines support list: meteor_m2-x_lrpt, gk2a_lrit.
     * @params string pipeline (mandatory): meteor_m2-x_lrpt or gk2a_lrit.
     * @params string input_file (mandatory): input baseband file.
     * @params string output_directory (mandatory): output folder.
     * @params until_t until (optional): default PRODUCTS level.
     * @params u64 samplerate:
     *      - Mandatory: .cf32, .cs32, .cs16, .cs8, .cu8
     *      - Optional: .wav
     * @params baseband_t baseband_format (mandatory): baseband type, default
     * cf32.
     * @params bool iq_swap:
     *      - True: I/Q phase swap.
     * @params buffer_size (optional): override default buffer size - default =
     * 8192 bytes.
     * @params bool live (optional):
     *      - True: Enable live mode.
     *      - False: Offline mode.
     */
    std::string pipeline = "";
    std::string input_file = "";
    std::string output_directory = "";
    decoder::until_t until = decoder::PRODUCTS;
    uint64_t samplerate = 0;
    decoder::baseband_t baseband_format = decoder::CF_32;
    bool iq_swap{false};
    uint32_t buffer_size = 0;
    bool doppler_logging{false};
    athena_mode mode = OFFLINE_MODE;
};

class result {
  public:
    std::shared_ptr<std::vector<data::meteor::meteor_telemetry>> telemetry;
    athena_status status;
};

class listener {
  public:
    virtual void on_progress(double progress) = 0;
    virtual void on_finished(std::shared_ptr<class result> result) = 0;
    virtual void on_error(std::string error) = 0;
};

/* @brief Call this function to demodulate and decode baseband file
 */
void decode(cmd cmd, std::shared_ptr<listener> listener);

} // namespace athena::decoder

#endif
