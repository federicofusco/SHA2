#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sha224.h"
#include "sha256.h"
#include "sha384.h"
#include "sha512.h"

/**
 * All these tests come from the algorithm examples specified by the FIPS 180-4 
 * specification in the implementation notes (https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/<algorithm>.pdf)
 */

int main ( int argc, char* argv[] ) {

    int error = 0;

    // Tests SHA224
    printf ( ":======== SHA-224 ========:\n" );
    if ( strcmp ( sha224 ( "abc" ), "23097D223405D8228642A477BDA255B32AADBCE4BDA0B3F7E36C9DA7" ) != 0 ) {
        printf ( "SHA224              FAILED!\n" );
        error = 1;
    } else 
        printf ( "SHA224              PASSED!\n" );

    if ( strcmp ( sha224 ( "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq" ), "75388B16512776CC5DBA5DA1FD890150B0C6455CB4F58B1952522525" ) != 0 ) {
        printf ( "SHA224 (Multiblock) FAILED!\n" );
        error = 1; 
    } else
        printf ( "SHA224 (Multiblock) PASSED!\n" );

    // Tests SHA256
    printf ( "\n:======== SHA-256 ========:\n" );
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

    // Tests SHA384
    printf ( "\n:======== SHA-384 ========:\n" );
    if ( strcmp ( sha384 ( "abc" ), "CB00753F45A35E8BB5A03D699AC65007272C32AB0EDED1631A8B605A43FF5BED8086072BA1E7CC2358BAECA134C825A7" ) != 0 ) {
        printf ( "SHA384              FAILED!\n" );
        error = 1;
    } else 
        printf ( "SHA384              PASSED!\n" );

    if ( strcmp ( sha384 ( "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu" ), "09330C33F71147E83D192FC782CD1B4753111B173B3B05D22FA08086E3B0F712FCC7C71A557E2DB966C3E9FA91746039" ) != 0 ) {
        printf ( "SHA384 (Multiblock) FAILED!\n" );
        error = 1;
    } else
        printf ( "SHA384 (Multiblock) PASSED!\n" );

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