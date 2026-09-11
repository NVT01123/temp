#include "session.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class MyDecodeListener : public athena::session::DecodeListener {
  public:
    void onUpdate(int progress) override {
        std::cout << "\r->> Progress: " << progress << "%" << std::flush
                  << std::endl;
    }

    void onResponse(const athena::session::DecodeResult &result) override {
        std::cout << "\n\nDecode finished!" << std::endl;
        if (!result.telemetry) {
            std::cout << "No telemetry data found." << std::endl;
            return;
        }

        std::cout << "Size of telemetry = " << result.telemetry->size()
                  << std::endl;

        int cnt = 0;
        for (const auto &el : *result.telemetry) {
            if (cnt++ >= 10)
                break;

            std::cout << "{\n";
            std::cout << "    APID = " << (el.APID.empty() ? "null" : el.APID)
                      << "\n";
            std::cout << "    timestamp = " << el.ccsds_time << "\n";
            std::cout << "    {\n";
            std::cout << "        msu_mr_id = "
                      << (el.msu_mr_id.empty() ? "null" : el.msu_mr_id) << "\n";
            std::cout << "        msu_mr_set = "
                      << (el.msu_mr_set.empty() ? "null" : el.msu_mr_set)
                      << "\n";
            std::cout << "    }\n";

            if (el.type != athena::data::meteor::NONE &&
                !el.type_name.empty()) {
                std::cout << "    {\n";
                std::cout << "    " << el.type_name << ": {\n";
                for (const auto &pair : el.telemetry) {
                    std::cout << "        " << pair.first << " = "
                              << pair.second << "\n";
                }
                std::cout << "    }\n";
            }
            std::cout << "},\n";
        }
    }

    void onError(const std::string &message) override {
        std::cout << "\nError: " << message << std::endl;
    }
};

class MySdrListener : public athena::session::SDRListener {
  public:
    void onSpectrum(const std::vector<float> &bins) override {}
    void onStatus(const athena::session::Status &status) override {
        std::cout << "\r[SDR] Carrier Locked: " << status.carrierLocked
                  << " | Symbol Locked: " << status.symbolLocked << std::flush;
    }
    void onError(const std::string &message) override {
        std::cout << "\nSDR Error: " << message << std::endl;
    }
};

int main(int argc, char *argv[]) {
    // 1. Init session
    athena::session::open();

    // 2. Configure pipeline matching commented code
    athena::session::setPipeline(0); // 0 = meteor_m2-x_lrpt
    athena::session::setMode(athena::session::LIVE_MODE);
    athena::session::setInputFile(
        "/home/nvt/Documents/Satdump-input/"
        "2026-08-17_07-28-50_1024000SPS_137900000Hz.cf32");
    athena::session::setOutputDirectory("outputtest3");
    athena::session::setBasebandFormat(0); // 0 = CF_32
    athena::session::setSampleRateHz(1024e3);
    athena::session::setDopplerLogging(true);

    // 3. Setup listeners
    MyDecodeListener decode_listener;
    MySdrListener sdr_listener;

    athena::session::capture(
        sdr_listener); // Set global SDR listener for metrics

    std::cout << "Bắt đầu tiến trình decode..." << std::endl;
    athena::session::decode(decode_listener);
    std::cout << "\nTiến trình decode kết thúc." << std::endl;

    athena::session::close();
    return 0;
}
