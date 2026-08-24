#include "athena.h"
#include <stdio.h>

int main() {
    athena::cmd cmd;
    cmd.pipeline = "meteor_m2-x_lrpt";
    cmd.input_file = "/home/nvt/Documents/Satdump-input/test.wav";
    cmd.output_directory = "outputtest";
    cmd.baseband_format = athena::CF_32;
    cmd.live = false;
    athena::decode(cmd);
    printf("Decode success!");
    return 0;
}
