#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"

int main() {
    char *data = "D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A62714A6614694B32FC7B11A44E43D69A6271";
    unsigned char *md5_data = md5(data, sizeof(char) * strlen(data));
    for(int loop_i = 0; loop_i < 16; ++loop_i) {
        printf("%02X", md5_data[loop_i]);
    }
    printf("\n");
}