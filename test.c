#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sha256.h"
#include "sha512.h"

/**
 * All these tests come from the algorithm examples specified by the FIPS 180-2
 * specification (https://csrc.nist.gov/csrc/media/publications/fips/180/2/archive/2002-08-01/documents/fips180-2.pdf)
 */

int main ( int argc, char* argv[] ) {

    int error = 0;

    // Tests SHA256
    printf ( ":======== SHA-256 ========:\n" );
    if ( strcmp ( sha256 ( "abc" ), "BA7816BF8F01CFEA414140DE5DAE2223B00361A396177A9CB410FF61F20015AD" ) != 0 ) {
        printf ( "SHA256              FAILED!\n" );
        error = 1;
    } else
        printf ( "SHA256              PASSED!\n" );

    if ( strcmp ( sha256 ( "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq" ), "248D6A61D20638B8E5C026930C3E6039A33CE45964FF2167F6ECEDD419DB06C1" ) != 0 ) {
        printf ( "SHA256 (Multiblock) FAILED!\n" );
        error = 1;
    } else
        printf ( "SHA256 (Multiblock) PASSED!\n" );

    // Tests SHA512
    printf ( "\n:======== SHA-512 ========:\n" );
    if ( strcmp ( sha512 ( "abc" ), "DDAF35A193617ABACC417349AE20413112E6FA4E89A97EA20A9EEEE64B55D39A2192992A274FC1A836BA3C23A3FEEBBD454D4423643CE80E2A9AC94FA54CA49F" ) != 0 ) {
        printf ( "SHA512(             FAILED!\n" );
        error = 1;
    } else
        printf ( "SHA512              PASSED!\n" );


    if ( strcmp ( sha512 ( "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu" ), "8E959B75DAE313DA8CF4F72814FC143F8F7779C6EB9F7FA17299AEADB6889018501D289E4900F7E4331B99DEC4B5433AC7D329EEB6DD26545E96E55B874BE909" ) != 0 ) {
        printf ( "SHA512 (Multiblock) FAILED!\n" );
        error = 1;
    } else 
        printf ( "SHA512 (Multiblock) PASSED!\n" );

    if ( error == 0 ) {
        printf ( "\n###########################\n" );
        printf ( "#    ALL TESTS PASSED!    #\n" );
        printf ( "###########################\n" );
    } else {
        printf ( "\n###########################\n" );
        printf ( "#      TESTS FAILED!      #\n" );
        printf ( "###########################\n" );
    }

    return 0;

}