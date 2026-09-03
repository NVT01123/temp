#include "decoder.h"
#include <stdio.h>
#include <vector>

class m_listener : public athena::decoder::listener {
  public:
    void on_progress(double progress) {
        printf("----> progress %lf\n", progress);
    }
    void on_finished() {
        if (result.status == athena::decoder::ATHENA_ERROR_CODE) {
            printf("Decoding Error");
            return;
        }

        printf("size of telemetry = %d\n", (int)result.telemetry->size());

        athena::data::meteor::meteor_telemetry el = (*result.telemetry)[0];

        int cnt = 0;
        while (cnt < 10) {
            el = (*result.telemetry)[cnt++];
            if (el.type == athena::data::meteor::NONE) {
                printf("{\n");
                printf("    APID = %s\n", el.APID);
                printf("    timestamp = %lf\n", el.ccsds_time);
                printf("    {\n");
                printf("        msu_mr_id = %s\n", el.msu_mr_id);
                printf("        msu_mr_set = %s\n", el.msu_mr_set);
                printf("    }\n");
                printf("},\n");
            } else {
                printf("{\n");
                printf("    APID = %s\n", el.APID);
                printf("    timestamp = %lf\n", el.ccsds_time);
                printf("    {\n");
                printf("        msu_mr_id = %s\n", el.msu_mr_id);
                printf("        msu_mr_set = %s\n", el.msu_mr_set);
                printf("    }\n");
                printf("    {\n");
                printf("    %s: {\n", el.type_name);
                for (int i = 0; i < el.type; ++i)
                    printf("        %s = %s\n", el.telemetry[0][i],
                           el.telemetry[1][i]);
                printf("    }\n");
                printf("},\n");
            }
        }

        printf("Decoding finished");

        printf("on finished!\n");
    }
    void on_error(std::string error) { printf("error: %s\n", error.c_str()); }
};

int main() {
    // athena::decoder::cmd cmd;
    // cmd.pipeline = "meteor_m2-x_lrpt";
    // cmd.input_file = "/home/nvt/Documents/Satdump-input/test2.wav";
    // // cmd.input_file = "/home/nvt/Documents/Satdump-input/"
    // //                  "2026-08-17_07-28-50_1024000SPS_137900000Hz.cf32";
    // cmd.output_directory = "outputtest2";
    // cmd.baseband_format = athena::decoder::CF_32;
    // cmd.samplerate = 1024e3;
    // cmd.live = true;

    athena::decoder::init_decoder();

    athena::decoder::set_pipeline("meteor_m2-x_lrpt");
    athena::decoder::set_mode(athena::decoder::LIVE_MODE);
    // athena::decoder::set_input_file(
    // "/home/nvt/Documents/Satdump-input/test.wav");
    athena::decoder::set_input_file(
        "/home/nvt/Documents/Satdump-input/"
        "2026-08-17_07-28-50_1024000SPS_137900000Hz.cf32");
    athena::decoder::set_output_directory("outputtest3");
    athena::decoder::set_baseband_format(athena::decoder::CF_32);
    athena::decoder::set_samplerate(1024e3);
    athena::decoder::enable_doppler_logging();

    std::shared_ptr<athena::decoder::listener> listener =
        std::make_shared<m_listener>();
    listener->result.telemetry =
        std::make_shared<std::vector<athena::data::meteor::meteor_telemetry>>();

    athena::decoder::decode(listener);
    return 0;
}
