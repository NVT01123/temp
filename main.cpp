#include "decoder.h"
#include <stdio.h>
#include <vector>

int main() {
    athena::decoder::cmd cmd;
    cmd.pipeline = "meteor_m2-x_lrpt";
    cmd.input_file = "/home/nvt/Documents/Satdump-input/test.wav";
    // cmd.input_file = "/home/nvt/Documents/Satdump-input/"
    //                  "2026-08-17_07-28-50_1024000SPS_137900000Hz.cf32";
    cmd.output_directory = "outputtest";
    cmd.baseband_format = athena::decoder::CF_32;
    cmd.samplerate = 1024e3;
    cmd.live = true;

    std::shared_ptr<std::vector<athena::data::meteor::meteor_telemetry>>
        telemetry = std::make_shared<
            std::vector<athena::data::meteor::meteor_telemetry>>();

    athena::decoder::athena_status success =
        athena::decoder::decode(cmd, &telemetry);

    printf("size of telemetry = %d\n", (int)telemetry->size());

    athena::data::meteor::meteor_telemetry el = (*telemetry)[0];

    int cnt = 0;
    while (cnt < 10) {
        el = (*telemetry)[cnt++];
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
            for (int i = 0; i < 26; ++i)
                printf("        %s = %s\n", el.telemetry[0][i],
                       el.telemetry[1][i]);
            printf("    }\n");
            printf("},\n");
        }
    }

    if (success == athena::decoder::ATHENA_ERROR_CODE) {
        printf("Decoding Error");
        return 0;
    }
    printf("Successfully Decoded");
    return 0;
}
