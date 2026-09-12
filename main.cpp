#include "live_session.h"
#include "replay_session.h"
#include <chrono>
#include <iostream>
#include <string>

class MyReplayListener : public SDRListener {
    int spectrum_count = 0;
    int status_count = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

  public:
    MyReplayListener() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void onSpectrum(const std::vector<float> &bins) override {
        spectrum_count++;
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                            now - start_time)
                            .count();
        if (spectrum_count % 10 == 0) { // Log occasionally to avoid spam
            std::cout << "[" << duration
                      << " ms] onSpectrum called! (total: " << spectrum_count
                      << ") - bins size: " << bins.size() << "\n";
        }
    }
    void onStatus(const Status &status) override {
        status_count++;
        if (status_count % 10 == 0) {
            std::cout << "[Status] fftFrames = " << status.fftFrames
                      << " | queueHealth = " << status.queueHealth << "\n";
        }
    }
    void onError(const std::string &message) override {
        std::cout << "[Error] " << message << std::endl;
    }
};

class MyDecodeListener : public athena::session::DecodeListener {
  public:
    void onUpdate(int progress) override {
        std::cout << "[Decode] progress: " << progress << "%\n";
    }
    void onResponse(const DecodeResult &result) override {
        std::cout << "[Decode] success!" << std::endl;
    }
    void onError(const std::string &message) override {
        std::cout << "[Decode Error] " << message << std::endl;
    }
};

int main(int argc, char **argv) {
    std::cout << "--- Testing athena::replay_session API ---" << std::endl;
    athena::session::open();

    // Use test baseband file if provided, otherwise default
    std::string input_file = "/home/nvt/Documents/Satdump-input/"
                             "2026-08-17_07-28-50_1024000SPS_137900000Hz.cf32";
    if (argc > 1) {
        input_file = argv[1];
    }

    std::cout << "Testing Replay Session with file: " << input_file
              << std::endl;

    // Configure pipeline first
    athena::session::setOutputDirectory("outputdir");

    MyReplayListener listener;
    MyDecodeListener decode_listener;
    std::cout << "Starting replay..." << std::endl;

    // Test the replay session (this will block and simulate time)
    try {
        athena::replay_session::open(input_file, listener, decode_listener);
    } catch (const std::exception &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "Replay test completed." << std::endl;
    athena::session::close();
    return 0;
}

