#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned int right_rotate ( unsigned int c, int shift ) {
    return  (c >> shift) | ( c << ( sizeof ( c ) * 8 - shift ) );
}

char* sha256 ( char* input ) {

    // Initializes hash values
    unsigned int h[8] = { 
        0x6a09e667, 
        0xbb67ae85, 
        0x3c6ef372, 
        0xa54ff53a, 
        0x510e527f, 
        0x9b05688c, 
        0x1f83d9ab, 
        0x5be0cd19 
    };

    // Initializes constants
    unsigned int k[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    // Padds the input (pre-processing)
    char padding[( (int) ceil ( ( (float) strlen ( input ) + 9.0 ) / 64.0 ) * 64 )];
    for ( int x = 0; x < sizeof ( padding ); x++ ) {
        padding[x] = 0x00;
    }

    strcpy ( padding, input );

    // Append a 64-bit big endian int which represents the length of the input in bits
    long long int length = strlen ( input ) * 8;
    padding[sizeof ( padding ) - 8] = ( length >> 56 ) & 0xFF;
    padding[sizeof ( padding ) - 7] = ( length >> 48 ) & 0xFF;
    padding[sizeof ( padding ) - 6] = ( length >> 40 ) & 0xFF;
    padding[sizeof ( padding ) - 5] = ( length >> 32 ) & 0xFF;
    padding[sizeof ( padding ) - 4] = ( length >> 24 ) & 0xFF;
    padding[sizeof ( padding ) - 3] = ( length >> 16 ) & 0xFF;
    padding[sizeof ( padding ) - 2] = ( length >> 8 ) & 0xFF;
    padding[sizeof ( padding ) - 1]     = length & 0xFF;
    padding[strlen ( input )] = 0x80;

    for ( int x = 0; x < sizeof ( padding ); x += 64 ) {

        // Splits the padding into 64 byte chunks
        char chunk[64] = {
            padding[x],      padding[x + 1],  padding[x + 2],  padding[x + 3],  padding[x + 4],  padding[x + 5],
            padding[x + 6],  padding[x + 7],  padding[x + 8],  padding[x + 9], padding[x + 10], padding[x + 11],
            padding[x + 12], padding[x + 13], padding[x + 14], padding[x + 15], padding[x + 16], padding[x + 17],
            padding[x + 18], padding[x + 19], padding[x + 20], padding[x + 21], padding[x + 22], padding[x + 23],
            padding[x + 24], padding[x + 25], padding[x + 26], padding[x + 27], padding[x + 28], padding[x + 29],
            padding[x + 30], padding[x + 31], padding[x + 32], padding[x + 33], padding[x + 34], padding[x + 35],
            padding[x + 36], padding[x + 37], padding[x + 38], padding[x + 39], padding[x + 40], padding[x + 41],
            padding[x + 42], padding[x + 43], padding[x + 44], padding[x + 45], padding[x + 46], padding[x + 47],
            padding[x + 48], padding[x + 49], padding[x + 50], padding[x + 51], padding[x + 52], padding[x + 53],
            padding[x + 54], padding[x + 55], padding[x + 56], padding[x + 57], padding[x + 58], padding[x + 59],
            padding[x + 60], padding[x + 61], padding[x + 62], padding[x + 63]
        };

        // Copies chunk into first 16 words of the message schedule
        unsigned int w[64] = {0};
        for ( int y = 0; y < sizeof ( chunk ); y += 4 ) {
            char word[4] = { chunk[y + 3], chunk[y + 2], chunk[y + 1], chunk[y] };
            w[y / 4] = *(int *)word;
        }

        // Main schedule extension loop
        for ( int y = 16; y < 64; y++ ) {
            
            unsigned int s0 = ( right_rotate ( w[y - 15], 7 ) ^
                                right_rotate ( w[y - 15], 18) ^
                                ( w[y - 15] >> 3 ) );

            unsigned int s1 = ( right_rotate ( w[y - 2], 17 ) ^
                                right_rotate ( w[y - 2], 19 ) ^
                                ( w[y - 2] >> 10 ) );


            w[y] = ( w[y - 16] + s0 + w[y - 7] + s1 ) % 4294967296;

        }

        unsigned int a = h[0];
        unsigned int b = h[1];
        unsigned int c = h[2];
        unsigned int d = h[3];
        unsigned int e = h[4];
        unsigned int f = h[5];
        unsigned int g = h[6];
        unsigned int _h = h[7];

        // Main compression loop
        for ( int y = 0; y < 64; y++ ) {

            unsigned int S1 = right_rotate ( e, 6  ) ^
                              right_rotate ( e, 11 ) ^
                              right_rotate ( e, 25 );
            
            unsigned int ch = ( e & f ) ^ ( ( ~e ) & g );
            unsigned int temp1 = ( _h + S1 + ch + k[y] + w[y] ) % 4294967296;

            unsigned int S0 = right_rotate ( a, 2  ) ^
                              right_rotate ( a, 13 ) ^
                              right_rotate ( a, 22 );

            unsigned int maj = ( a & b ) ^ ( a & c ) ^ ( b & c );
            unsigned int temp2 = ( S0 + maj ) % 4294967296;

            _h = g;
            g = f;
            f = e;
            e = ( d + temp1 ) % 4294967296;
            d = c;
            c = b;
            b = a;
            a = ( temp1 + temp2 ) % 4294967296;

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

    char* output = malloc ( sizeof ( char ) * 64 );
    sprintf ( output, "%X%X%X%X%X%X%X%X", h[0], h[1], h[2], h[3], h[4], h[5], h[6], h[7] );
    
    return output;

}

int main ( int argc, char* argv[] ) {

    if ( argc < 2 ) {
        printf ( "Usage: ./sha256 <data>\n" );
        exit ( EXIT_FAILURE );
    }

    for ( int x = 1; x < argc; x++ ) {
        printf ( "[%d]: %s\n", x, sha256 ( argv[x] ) );
    }

}