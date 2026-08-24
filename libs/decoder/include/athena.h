#pragma once
#ifndef ATHENA_CORE
#define ATHENA_CORE

#include <stdint.h>
#include <string>

namespace athena {
constexpr int8_t ATHENA_ERROR_CODE = -1;
constexpr int8_t ATHENA_SUCCESS_CODE = 1;

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
    until_t until = PRODUCTS;
    uint64_t samplerate = 0;
    baseband_t baseband_format = CF_32;
    bool iq_swap{false};
    uint32_t buffer_size = 0;
    bool live{false};
};

/* @brief Call this function to demodulate and decode baseband file
 */
int8_t decode(cmd cmd);

} // namespace athena

#endif
