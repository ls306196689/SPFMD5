//
//  CCMD5.cpp
//  MD5Demo
//
//  Created by pengfei sun on 5/29/13.
//  Copyright (c) 2013 pengfei sun. All rights reserved.
//

#include "CCMD5.h"
static uchar PADDING[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
//std::string CCMD5::getMD5String(const uchar* text, int64_t length)
//{
//    uint data[4] = {0};
//    data[0] = m_A;
//    data[1] = m_B;
//    data[2] = m_C;
//    data[3] = m_D;
//    uchar    cdata[65]={0};
//    int i = 0;
//    int lengthtofill = length%64;
//    int64_t counter = length /64;
//    if (lengthtofill > 56) {
//        lengthtofill = 120 - lengthtofill;
//        counter += 2;
//    }
//    else
//    {
//        counter ++;
//        lengthtofill = 56 - lengthtofill;
//    }
//    for (i = 0; i < counter; i ++) {
//        if (i < counter-1) {
//            memcpy(cdata, text + (i << 6), sizeof(uchar)*64);
//            MD5(data, cdata);
//        }
//        else
//        {
//            memcpy(cdata, text + (i << 6), sizeof(uchar)*(56 - lengthtofill));
//            memcpy(cdata + (56 - lengthtofill), PADDING, lengthtofill);
//            uchar dddd[64] = {0};
//            length <<= 3;
//            int8_2_chars(&length, dddd, 8);
//            memcpy(cdata + 56, dddd, 8);
//            MD5(data, cdata);
//        }
//    }
//    int4_2_chars(data, cdata, 16);
//    char md5[33] = {0};
////    sprintf(md5, "")
//    for (int j = 0; j < 16; j ++) {
//        sprintf(&(md5[j *2]), "%02x",cdata[j]);
//    }
//    std::string datastr(md5);
//    return datastr;
//}
std::string CCMD5::getMD5String(const uchar* text, int64_t length)
{
    uint data[4] = {0};
    data[0] = m_A;
    data[1] = m_B;
    data[2] = m_C;
    data[3] = m_D;
    uchar    cdata[65]={0};
    int i = 0;
    int lengthtofill = length%64;
    int64_t counter = length /64;
    int counter0 = 1;
    int lengthtofill0 = 0;
    if (lengthtofill > 56) {
        lengthtofill0 = 120 - lengthtofill;
        counter0 = 2;
    }
    else
    {
        lengthtofill0 = 56 - lengthtofill;
    }
    for (i = 0; i < counter; i ++) {
        memcpy(cdata, text + (i << 6), sizeof(uchar)*64);
        MD5(data, cdata);
        
    }
    if (counter0 == 1) {
        memcpy(cdata, text + (i << 6), sizeof(uchar)*(lengthtofill));
        memcpy(cdata + (lengthtofill), PADDING, (56 - lengthtofill));
        uchar dddd[64] = {0};
        length <<= 3;
        int8_2_chars(&length, dddd, 8);
        memcpy(cdata + 56, dddd, 8);
        MD5(data, cdata);
    }
    else
    {
        memcpy(cdata, text + (i << 6), sizeof(uchar)*( lengthtofill));
        memcpy(cdata + (lengthtofill), PADDING, (64 - lengthtofill));
        MD5(data, cdata);
        
        
        memcpy(cdata, PADDING, 56);
        
        uchar dddd[64] = {0};
        length <<= 3;
        int8_2_chars(&length, dddd, 8);
        memcpy(cdata + 56, dddd, 8);
        MD5(data, cdata);
    }
    int4_2_chars(data, cdata, 16);
    char md5[33] = {0};
//    sprintf(md5, "")
    for (int j = 0; j < 16; j ++) {
        sprintf(&(md5[j *2]), "%02x",cdata[j]);
    }
    std::string datastr(md5);
    return datastr;
}

void CCMD5::chars_2_int4(const uchar *datain,uint dataout[], int counterincs )
{
    unsigned int i, j;
    
    for(i = 0, j = 0; j < counterincs; i++, j += 4)
    {
        dataout[i] = ((uint)datain[j]) | (((uint)datain[j+1]) << 8) |(((uint)datain[j+2]) << 16) | (((uint)datain[j+3]) << 24);
    }
    
}
void CCMD5::int4_2_chars(const uint datain[], uchar dataout[], int countercs)
{
    unsigned int i, j;
    
    for(i = 0, j = 0; j < countercs; i++, j += 4) {
        dataout[j] = (uchar)(datain[i] & 0xff);
        dataout[j+1] = (uchar)((datain[i] >> 8) & 0xff);
        dataout[j+2] = (uchar)((datain[i] >> 16) & 0xff);
        dataout[j+3] = (uchar)((datain[i] >> 24) & 0xff);
    }
}
void CCMD5::int8_2_chars(const int64_t datain[], uchar dataout[], int countercs)
{
    unsigned int i, j;
    
    for(i = 0, j = 0; j < countercs; i++, j += 8) {
        dataout[j] = (uchar)(datain[i] & 0xff);
        dataout[j+1] = (uchar)((datain[i] >> 8) & 0xff);
        dataout[j+2] = (uchar)((datain[i] >> 16) & 0xff);
        dataout[j+3] = (uchar)((datain[i] >> 24) & 0xff);
        dataout[j+4] = (uchar)((datain[i] >> 32) & 0xff);
        dataout[j+5] = (uchar)((datain[i] >> 40) & 0xff);
        dataout[j+6] = (uchar)((datain[i] >> 48) & 0xff);
        dataout[j+7] = (uchar)((datain[i] >> 56) & 0xff);
    }
}
void CCMD5::MD5(uint state[4],const uchar block[64])
{
    uint a = state[0], b = state[1], c = state[2], d = state[3], x[16];
    
    chars_2_int4( block, x,64);
    
    /* Round 1 */
    FF(a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
    FF(d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
    FF(c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
    FF(b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
    FF(a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
    FF(d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
    FF(c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
    FF(b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
    FF(a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
    FF(d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
    FF(c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
    FF(b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
    FF(a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
    FF(d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
    FF(c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
    FF(b, c, d, a, x[15], S14, 0x49b40821); /* 16 */
    
    /* Round 2 */
    GG(a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
    GG(d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
    GG(c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
    GG(b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
    GG(a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
    GG(d, a, b, c, x[10], S22,  0x2441453); /* 22 */
    GG(c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
    GG(b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
    GG(a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
    GG(d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
    GG(c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
    GG(b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
    GG(a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
    GG(d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
    GG(c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
    GG(b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */
    
    /* Round 3 */
    HH(a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
    HH(d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
    HH(c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
    HH(b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
    HH(a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
    HH(d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
    HH(c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
    HH(b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
    HH(a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
    HH(d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
    HH(c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
    HH(b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
    HH(a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
    HH(d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
    HH(c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
    HH(b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */
    
    /* Round 4 */
    II(a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
    II(d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
    II(c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
    II(b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
    II(a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
    II(d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
    II(c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
    II(b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
    II(a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
    II(d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
    II(c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
    II(b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
    II(a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
    II(d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
    II(c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
    II(b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */
    
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}