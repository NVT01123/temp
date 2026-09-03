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

class result {
  public:
    std::shared_ptr<std::vector<data::meteor::meteor_telemetry>> telemetry;
    athena_status status;
};

class listener {
  public:
    class result result;

  public:
    virtual void on_progress(double progress) = 0;
    virtual void on_finished() = 0;
    virtual void on_error(std::string error) = 0;
};

/* @brief Call this function to initialize decoder system
 */
athena_status init_decoder();

/* @brief Call this function to demodulate and decode baseband file
 */
void decode(std::shared_ptr<listener> listener);

/* @brief Call this function to set decoder mode
 */
void set_mode(athena_mode mode);

/* @brief Call this function to set pipeline
 */
athena_status set_pipeline(std::string pipeline_id);

/* @brief Call this function to set input_file
 */
void set_input_file(std::string input_file);

/* @brief Call this function to set output_directory
 */
void set_output_directory(std::string output_directory);

/* @brief Call this function to set until
 */
athena_status set_until(until_t until);

/* @brief Call this function to set samplerate
 */
void set_samplerate(uint64_t samplerate);

/* @brief Call this function to set baseband format
 */
void set_baseband_format(baseband_t baseband_format);

/* @brief Call this function to set iq_swap
 */
void set_iq_swap(bool iq_swap);

/* @brief Call this function to set buffer size
 */
void set_buffer_size(uint32_t buffer_size);

/* @brief Call this function to enable doppler logging
 */
void enable_doppler_logging();

} // namespace athena::decoder

#endif
