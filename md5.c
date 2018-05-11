#include "md5.h"

static __uint64_t verify_length(__uint64_t length);

static int full_data(__uint8_t *data, __int64_t begin_index, __int64_t length);

static __uint32_t loop_left(__uint32_t x, __uint32_t y);

static __uint32_t F(__uint32_t X, __uint32_t Y, __uint32_t Z);
static __uint32_t G(__uint32_t X, __uint32_t Y, __uint32_t Z);
static __uint32_t H(__uint32_t X, __uint32_t Y, __uint32_t Z);
static __uint32_t I(__uint32_t X, __uint32_t Y, __uint32_t Z);

static __uint32_t FF(__uint32_t a, __uint32_t b, __uint32_t c, __uint32_t d, __uint32_t M, __uint32_t s, __uint32_t t);
static __uint32_t GG(__uint32_t a, __uint32_t b, __uint32_t c, __uint32_t d, __uint32_t M, __uint32_t s, __uint32_t t);
static __uint32_t HH(__uint32_t a, __uint32_t b, __uint32_t c, __uint32_t d, __uint32_t M, __uint32_t s, __uint32_t t);
static __uint32_t II(__uint32_t a, __uint32_t b, __uint32_t c, __uint32_t d, __uint32_t M, __uint32_t s, __uint32_t t);

static __uint8_t *n_add_one_loop(__uint8_t *data, __uint64_t length);

extern unsigned char *md5(__uint8_t *_data, __uint64_t length) {
    __uint64_t more_length;
    __uint8_t *data;
    __uint8_t *result;
    length *= 8;
    more_length = verify_length(length);
    data = (__uint8_t *)malloc(sizeof(__uint8_t) * (length + more_length) /8);
    memcpy(data, _data, sizeof(__uint8_t) * length / 8);
    full_data(data, length, length + more_length);
    length += more_length;
    result = n_add_one_loop(data, length);

    free(data);
    return result;
}

static __uint8_t *n_add_one_loop(__uint8_t *data, __uint64_t length) {
    __uint64_t loop_i;
    __uint32_t A = 0X67452301L, B = 0XEFCDAB89L, C = 0X98BADCFEL, D = 0X10325476L, *M;
    __uint32_t a = 0X67452301L, b = 0XEFCDAB89L, c = 0X98BADCFEL, d = 0X10325476L;
    length /= 512;
    __uint8_t *result;
    for(loop_i = 0; loop_i < length; ++loop_i) {
        a = A;b = B;c = C; d = D;
        M = (__uint32_t *)(data + loop_i * 512 / 8);
        a=FF(a,b,c,d,M[0],7,0xd76aa478);
        d=FF(d,a,b,c,M[1],12,0xe8c7b756);
        c=FF(c,d,a,b,M[2],17,0x242070db);
        b=FF(b,c,d,a,M[3],22,0xc1bdceee);
        a=FF(a,b,c,d,M[4],7,0xf57c0faf);
        d=FF(d,a,b,c,M[5],12,0x4787c62a);
        c=FF(c,d,a,b,M[6],17,0xa8304613);
        b=FF(b,c,d,a,M[7],22,0xfd469501);
        a=FF(a,b,c,d,M[8],7,0x698098d8);
        d=FF(d,a,b,c,M[9],12,0x8b44f7af);
        c=FF(c,d,a,b,M[10],17,0xffff5bb1);
        b=FF(b,c,d,a,M[11],22,0x895cd7be);
        a=FF(a,b,c,d,M[12],7,0x6b901122);
        d=FF(d,a,b,c,M[13],12,0xfd987193);
        c=FF(c,d,a,b,M[14],17,0xa679438e);
        b=FF(b,c,d,a,M[15],22,0x49b40821);
        
        a=GG(a,b,c,d,M[1],5,0xf61e2562);
        d=GG(d,a,b,c,M[6],9,0xc040b340);
        c=GG(c,d,a,b,M[11],14,0x265e5a51);
        b=GG(b,c,d,a,M[0],20,0xe9b6c7aa);
        a=GG(a,b,c,d,M[5],5,0xd62f105d);
        d=GG(d,a,b,c,M[10],9,0x02441453);
        c=GG(c,d,a,b,M[15],14,0xd8a1e681);
        b=GG(b,c,d,a,M[4],20,0xe7d3fbc8);
        a=GG(a,b,c,d,M[9],5,0x21e1cde6);
        d=GG(d,a,b,c,M[14],9,0xc33707d6);
        c=GG(c,d,a,b,M[3],14,0xf4d50d87);
        b=GG(b,c,d,a,M[8],20,0x455a14ed);
        a=GG(a,b,c,d,M[13],5,0xa9e3e905);
        d=GG(d,a,b,c,M[2],9,0xfcefa3f8);
        c=GG(c,d,a,b,M[7],14,0x676f02d9);
        b=GG(b,c,d,a,M[12],20,0x8d2a4c8a);

        a=HH(a,b,c,d,M[5],4,0xfffa3942);
        d=HH(d,a,b,c,M[8],11,0x8771f681);
        c=HH(c,d,a,b,M[11],16,0x6d9d6122);
        b=HH(b,c,d,a,M[14],23,0xfde5380c);
        a=HH(a,b,c,d,M[1],4,0xa4beea44);
        d=HH(d,a,b,c,M[4],11,0x4bdecfa9);
        c=HH(c,d,a,b,M[7],16,0xf6bb4b60);
        b=HH(b,c,d,a,M[10],23,0xbebfbc70);
        a=HH(a,b,c,d,M[13],4,0x289b7ec6);
        d=HH(d,a,b,c,M[0],11,0xeaa127fa);
        c=HH(c,d,a,b,M[3],16,0xd4ef3085);
        b=HH(b,c,d,a,M[6],23,0x04881d05);
        a=HH(a,b,c,d,M[9],4,0xd9d4d039);
        d=HH(d,a,b,c,M[12],11,0xe6db99e5);
        c=HH(c,d,a,b,M[15],16,0x1fa27cf8);
        b=HH(b,c,d,a,M[2],23,0xc4ac5665);

        a=II(a,b,c,d,M[0],6,0xf4292244);
        d=II(d,a,b,c,M[7],10,0x432aff97);
        c=II(c,d,a,b,M[14],15,0xab9423a7);
        b=II(b,c,d,a,M[5],21,0xfc93a039);
        a=II(a,b,c,d,M[12],6,0x655b59c3);
        d=II(d,a,b,c,M[3],10,0x8f0ccc92);
        c=II(c,d,a,b,M[10],15,0xffeff47d);
        b=II(b,c,d,a,M[1],21,0x85845dd1);
        a=II(a,b,c,d,M[8],6,0x6fa87e4f);
        d=II(d,a,b,c,M[15],10,0xfe2ce6e0);
        c=II(c,d,a,b,M[6],15,0xa3014314);
        b=II(b,c,d,a,M[13],21,0x4e0811a1);
        a=II(a,b,c,d,M[4],6,0xf7537e82);
        d=II(d,a,b,c,M[11],10,0xbd3af235);
        c=II(c,d,a,b,M[2],15,0x2ad7d2bb);
        b=II(b,c,d,a,M[9],21,0xeb86d391);
        A += a;B += b;C +=c;D += d;
    }
    result = (__uint8_t *)malloc(sizeof(__uint8_t) * 16);
    memcpy(result, &A, sizeof(__uint32_t));
    memcpy(result + 4, &B, sizeof(__uint32_t));
    memcpy(result + 8, &C, sizeof(__uint32_t));
    memcpy(result + 12, &D, sizeof(__uint32_t));
    return result;
}

static __uint64_t verify_length(__uint64_t length) {
    return (448 - length % 512)%512 + 64;
}
static int full_data(__uint8_t *data, __int64_t begin_index, __int64_t length) {
    data[begin_index/8] = 0x80;
    memset(data + begin_index/8 + 1, 0, length/8 -  begin_index/8 - 1);
    memcpy(data + length/8 - 8, &begin_index, 8);
}

static __uint32_t F(__uint32_t X, __uint32_t Y, __uint32_t Z) {
    return (X&Y)|((~X)&Z);
}

static __uint32_t G(__uint32_t X, __uint32_t Y, __uint32_t Z) {
    return (X&Z)|(Y&(~Z));
}

static __uint32_t H(__uint32_t X, __uint32_t Y, __uint32_t Z) {
    return X^Y^Z;
}

static __uint32_t I(__uint32_t X, __uint32_t Y, __uint32_t Z) {
    return Y^(X|(~Z));
}

static __uint32_t loop_left(__uint32_t x, __uint32_t y) {
    return (x >> (32 - y) | x << y);
}

static __uint32_t FF(__uint32_t a, __uint32_t b, __uint32_t c, __uint32_t d, __uint32_t M, __uint32_t s, __uint32_t t) {
    return b+loop_left((a+F(b,c,d)+M+t),s);
}
static __uint32_t GG(__uint32_t a, __uint32_t b, __uint32_t c, __uint32_t d, __uint32_t M, __uint32_t s, __uint32_t t) {
    return b+loop_left((a+G(b,c,d)+M+t),s);
}
static __uint32_t HH(__uint32_t a, __uint32_t b, __uint32_t c, __uint32_t d, __uint32_t M, __uint32_t s, __uint32_t t) {
    return b+loop_left((a+H(b,c,d)+M+t),s);
}
static __uint32_t II(__uint32_t a, __uint32_t b, __uint32_t c, __uint32_t d, __uint32_t M, __uint32_t s, __uint32_t t) {
    return b+loop_left((a+I(b,c,d)+M+t),s);
}