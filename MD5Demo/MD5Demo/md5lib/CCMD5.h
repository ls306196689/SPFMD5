//
//  CCMD5.h
//  MD5Demo
//
//  Created by pengfei sun on 5/29/13.
//  Copyright (c) 2013 pengfei sun. All rights reserved.
//

#ifndef __MD5Demo__CCMD5__
#define __MD5Demo__CCMD5__

#include <iostream>
//循环左移
#define CROL(value, bits) ((value << bits) | (value >> (0x20 - bits)))
//循环右移:
#define CROR(value, bits) ((value >> bits) | (value << (0x20 - bits)))

typedef unsigned char uchar;
//typedef unsigned int uint;
/* Constants for MD5Transform routine. */
/*md5转换用到的常量，算法本身规定的*/
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

typedef bool BYTE;

class CCMD5 {
    
    const uint m_A = 0x67452301;
    const uint m_B = 0xefcdab89;
    const uint m_C = 0x98badcfe;
    const uint m_D = 0x10325476;
    inline uint F(uint X, uint Y, uint Z)
    {
        return (X & Y)|((~X)&Z);
    };
    inline uint G(uint X, uint Y, uint Z)
    {
        return (X & Z)|((Y)&(~Z));
    };
    inline uint H(uint X, uint Y, uint Z)
    {
        return (X ^ Y ^Z);
    };
    inline uint I(uint X, uint Y, uint Z)
    {
        return (Y ^ (X | (~Z)));
    };
    inline void FF(uint &a, uint b, uint c,uint d, uint Mj, uint s,uint ti)
    {
        a += (F(b,c,d) + Mj) + ti;
        a = b + CROL( a,s);
    };
    inline void GG(uint &a, uint b, uint c,uint d, uint Mj, uint s,uint ti)
    {
        a += (G(b,c,d) + Mj) + ti;
        a = b + CROL( a,s);
    };
    inline void HH(uint &a, uint b, uint c,uint d, uint Mj, uint s,uint ti)
    {
        a += (H(b,c,d) + Mj) + ti;
        a = b + CROL( a,s);
    };
    inline void II(uint &a, uint b, uint c,uint d, uint Mj, uint s,uint ti)
    {
        a += (I(b,c,d) + Mj) + ti;
        a = b + CROL( a,s);
    };
public:
    std::string getMD5String(const uchar* text, int64_t length);
    
private:
    void MD5(uint state[4],const  uchar block[64]);
    void chars_2_int4(const uchar*datain,uint dataout[], int countercs);
    void int4_2_chars(const uint datain[], uchar dataout[], int countercs);
    void int8_2_chars(const int64_t datain[], uchar dataout[], int countercs);
//    static void chars_2_byte(const char *cdata, BYTE *byte, int counterbits);
//    static void byte_2_chars(const BYTE *byte, char *cdata, int counterbits);
};

#endif /* defined(__MD5Demo__CCMD5__) */
