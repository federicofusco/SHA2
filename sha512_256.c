#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "rotate.h"
// #include "sha512.h"

char* sha512_256 ( char* input ) {

    // Initializes hash values
    unsigned long long int h[8] = { 
        0x22312194FC2BF72C, 
        0x9F555FA3C84C64C2, 
        0x2393B86B6F53B151, 
        0x963877195940EABD, 
        0x96283EE2A88EFFE3, 
        0xBE5E1E2553863992, 
        0x2B0199FC2C85B8AA, 
        0x0EB72DDC81C52CA2 
    };

    // Initializes constants
    unsigned long long int k[128] = {
        0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538, 
        0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe, 
        0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 
        0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 
        0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab, 
        0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725, 
        0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 
        0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b, 
        0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218, 
        0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 
        0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 
        0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec, 
        0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c, 
        0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6, 
        0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 
        0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
    };

    // Padds the input (pre-processing)
    unsigned char padding[( (int) ceil ( ( (float) strlen ( input ) + 17.0 ) / 128.0 ) * 128 )];
    for ( unsigned int x = 0; x < sizeof ( padding ); x++ ) {
        if ( x < strlen ( input ) ) {
            padding[x] = input[x];
        } else if ( x == strlen ( input ) ) {
            padding[x] = 0x80; 
        } else {
            padding[x] = 0x00;
        }
    }

    // Append a 64-bit big endian int which represents the length of the input in bits
    unsigned long long int length = strlen ( input ) * 8;
    padding[sizeof ( padding ) - 8] =  ( length >> 56  ) & 0xFF;
    padding[sizeof ( padding ) - 7] =  ( length >> 48  ) & 0xFF;
    padding[sizeof ( padding ) - 6] =  ( length >> 40  ) & 0xFF;
    padding[sizeof ( padding ) - 5] =  ( length >> 32  ) & 0xFF;
    padding[sizeof ( padding ) - 4] =  ( length >> 24  ) & 0xFF;
    padding[sizeof ( padding ) - 3] =  ( length >> 16  ) & 0xFF;
    padding[sizeof ( padding ) - 2] =  ( length >> 8   ) & 0xFF;
    padding[sizeof ( padding ) - 1] =  ( length >> 0   ) & 0xFF;

    for ( unsigned int x = 0; x < sizeof ( padding ); x += 128 ) {

        // Splits the padding into 64 byte chunks
        char chunk[128] = {
            padding[x],        padding[ x + 1],   padding[ x + 2],   padding[ x + 3],   padding[ x + 4],   padding[ x + 5 ],
            padding[ x + 6],   padding[ x + 7],   padding[ x + 8],   padding[ x + 9],   padding[ x + 10],  padding[ x + 11],
            padding[ x + 12],  padding[ x + 13],  padding[ x + 14],  padding[ x + 15],  padding[ x + 16],  padding[ x + 17],
            padding[ x + 18],  padding[ x + 19],  padding[ x + 20],  padding[ x + 21],  padding[ x + 22],  padding[ x + 23],
            padding[ x + 24],  padding[ x + 25],  padding[ x + 26],  padding[ x + 27],  padding[ x + 28],  padding[ x + 29],
            padding[ x + 30],  padding[ x + 31],  padding[ x + 32],  padding[ x + 33],  padding[ x + 34],  padding[ x + 35],
            padding[ x + 36],  padding[ x + 37],  padding[ x + 38],  padding[ x + 39],  padding[ x + 40],  padding[ x + 41],
            padding[ x + 42],  padding[ x + 43],  padding[ x + 44],  padding[ x + 45],  padding[ x + 46],  padding[ x + 47],
            padding[ x + 48],  padding[ x + 49],  padding[ x + 50],  padding[ x + 51],  padding[ x + 52],  padding[ x + 53],
            padding[ x + 54],  padding[ x + 55],  padding[ x + 56],  padding[ x + 57],  padding[ x + 58],  padding[ x + 59],
            padding[ x + 60],  padding[ x + 61],  padding[ x + 62],  padding[ x + 63],  padding[ x + 64],  padding[ x + 65],
            padding[ x + 66],  padding[ x + 67],  padding[ x + 68],  padding[ x + 69],  padding[ x + 70],  padding[ x + 71],
            padding[ x + 72],  padding[ x + 73],  padding[ x + 74],  padding[ x + 75],  padding[ x + 76],  padding[ x + 77],
            padding[ x + 78],  padding[ x + 79],  padding[ x + 80],  padding[ x + 81],  padding[ x + 82],  padding[ x + 83],
            padding[ x + 84],  padding[ x + 85],  padding[ x + 86],  padding[ x + 87],  padding[ x + 88],  padding[ x + 89],
            padding[ x + 90],  padding[ x + 91],  padding[ x + 92],  padding[ x + 93],  padding[ x + 94],  padding[ x + 95],
            padding[ x + 96],  padding[ x + 97],  padding[ x + 98],  padding[ x + 99],  padding[ x + 100], padding[ x + 101],
            padding[ x + 102], padding[ x + 103], padding[ x + 104], padding[ x + 105], padding[ x + 106], padding[ x + 107],
            padding[ x + 108], padding[ x + 109], padding[ x + 110], padding[ x + 111], padding[ x + 112], padding[ x + 113],
            padding[ x + 114], padding[ x + 115], padding[ x + 116], padding[ x + 117], padding[ x + 118], padding[ x + 119],
            padding[ x + 120], padding[ x + 121], padding[ x + 122], padding[ x + 123], padding[ x + 124], padding[ x + 125],
            padding[ x + 126], padding[ x + 127]
        };

        // Copies chunk into first 16 words of the message schedule
        unsigned long long int w[80] = {0};
        for ( unsigned int y = 0; y < sizeof ( chunk ); y += 8 ) {
            unsigned char word[8] = { chunk[y + 7], chunk[y + 6], chunk[y + 5], chunk[y + 4], chunk[y + 3], chunk[y + 2], chunk[y + 1], chunk[y] };
            w[y / 8] = ( ( ( ( ( ( ( w[y / 8] << 8 | word[7] ) << 8 | word[6] ) << 8 | word[5] ) << 8 | word[4] ) << 8 | word[3] ) << 8 | word[2] ) << 8 | word[1] ) << 8 | word[0];
        }

        // Main schedule extension loop
        for ( int y = 16; y < 80; y++ ) {
            
            unsigned long long int s0 = ( long_right_rotate ( w[y - 15], 1 ) ^
                                          long_right_rotate ( w[y - 15], 8) ^
                                          ( w[y - 15] >> 7 ) );

            unsigned long long int s1 = ( long_right_rotate ( w[y - 2], 19 ) ^
                                          long_right_rotate ( w[y - 2], 61 ) ^
                                          ( w[y - 2] >> 6 ) );


            w[y] = ( w[y - 16] + s0 + w[y - 7] + s1 ) % 18446744073709551615ULL;

        }

        unsigned long long int a = h[0];
        unsigned long long int b = h[1];
        unsigned long long int c = h[2];
        unsigned long long int d = h[3];
        unsigned long long int e = h[4];
        unsigned long long int f = h[5];
        unsigned long long int g = h[6];
        unsigned long long int _h = h[7];

        // Main compression loop
        for ( int y = 0; y < 80; y++ ) {

            unsigned long long int S1 = long_right_rotate ( e, 14  ) ^
                              long_right_rotate ( e, 18 ) ^
                              long_right_rotate ( e, 41 );
            
            unsigned long long int ch = ( e & f ) ^ ( ( ~e ) & g );
            unsigned long long int temp1 = ( _h + S1 + ch + k[y] + w[y] ) % 18446744073709551615ULL;

            unsigned long long int S0 = long_right_rotate ( a, 28 ) ^
                              long_right_rotate ( a, 34 ) ^
                              long_right_rotate ( a, 39 );

            unsigned long long int maj = ( a & b ) ^ ( a & c ) ^ ( b & c );
            unsigned long long int temp2 = ( S0 + maj ) % 18446744073709551615ULL;

            _h = g;
            g = f;
            f = e;
            e = ( d + temp1 ) % 18446744073709551615ULL;
            d = c;
            c = b;
            b = a;
            a = ( temp1 + temp2 ) % 18446744073709551615ULL;

        }

        // Add the compressed chunk to the current hash value
        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
        h[5] += f;
        h[6] += g;
        h[7] += _h;

    }

    char* output = malloc ( sizeof ( unsigned long long int ) * 64 );
    sprintf ( output, "%016llX%016llX%016llX%016llX", h[0], h[1], h[2], h[3] );
    
    return output;

}