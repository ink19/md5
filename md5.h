#ifndef __MD5_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define __MD5_H 1

extern unsigned char *md5(__uint8_t *data, __uint64_t length);

#endif