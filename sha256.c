#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void sha256 ( char* input ) {

    // Initializes hash values
    unsigned int h0 = 0x6a09e667;
    unsigned int h1 = 0xbb67ae85;
    unsigned int h2 = 0x3c6ef372;
    unsigned int h3 = 0xa54ff53a;
    unsigned int h4 = 0x510e527f;
    unsigned int h5 = 0x9b05688c;
    unsigned int h6 = 0x1f83d9ab;
    unsigned int h7 = 0x5be0cd19;

    // Initializes contants
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
    char padding[(int) ceil ( (float) strlen ( input ) / 64.0 ) * 64];
    strcpy ( padding, input );

    padding[strlen ( input )] = 0x01;
    for ( int x = strlen ( input ) + 1; x < sizeof ( padding ); x++ ) {
        padding[x] = 0x00;
    }

}

int main ( int argc, char* argv[] ) {

    if ( argc != 2 ) {
        fprintf ( stderr, "Usage: %s\n", "./a.out <message>" );
        exit ( EXIT_FAILURE );
    }

    sha256 ( argv[1] );

    exit ( EXIT_SUCCESS );

}

// Converts the input into a binary string
    // char bin_input[strlen ( input ) * 8];
    // for ( int x = 0; x < strlen ( input ); x++ ) {
    //     char y[8];
        // for( int z = 7; z >= 0; z-- ) {
        //     bin_input[x * 8 + 7 - z] = ( input[x] >> z ) & 1 ? '1' : '0';
        // }
    // }

    // // Terminates char array to prevent reading into random memory
    // bin_input[strlen ( input ) * 8] = 0;

    // // Pads the input (pre-processing)
    // char padded_input[(int) ceil ( (float) strlen ( input ) * 8.0 / 512.0 ) * 512];
    
    // strcat ( padded_input, bin_input );
    // strcat ( padded_input, "1" );

    // for ( int x = 0; x < sizeof ( padded_input ) - strlen ( padded_input ); x++ ) {
    //     padded_input[strlen ( padded_input) + x] = '0';
    //     printf ( "%c\n", padded_input[strlen ( padded_input) + x]);
    //     // printf ( "%d\t", x );
    // }

    // // // printf ( "%d\n", sizeof ( padded_input ) - strlen ( padded_input ) );
    // printf ( "%s\n", padded_input );