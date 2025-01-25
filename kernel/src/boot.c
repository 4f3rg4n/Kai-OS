#include "../include/boot.h"

bios_parameter_block* get_bpb() {
    return (bios_parameter_block*)(START_OF_BPB);
}