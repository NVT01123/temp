#include "athena.h"
#include <stdio.h>

int main() {
    athena::decoder::cmd cmd;
    cmd.pipeline = "meteor_m2-x_lrpt";
    cmd.input_file = "/home/nvt/Documents/Satdump-input/test.wav";
    cmd.output_directory = "outputtest";
    cmd.until = athena::decoder::CADU;
    cmd.baseband_format = athena::decoder::CF_32;
    cmd.live = true;
    int8_t success = athena::decoder::decode(cmd);
    if (success == athena::decoder::ATHENA_ERROR_CODE) {
        printf("Decoding Error!");
        return 0;
    }
    printf("Decode success!");
    return 0;
}
