unsigned int right_rotate ( unsigned int c, int shift ) {
    return  (c >> shift) | ( c << ( sizeof ( c ) * 8 - shift ) );
}

unsigned long long int long_right_rotate ( unsigned long long int c, int shift ) {
    return  (c >> shift) | ( c << ( sizeof ( c ) * 8 - shift ) );
}