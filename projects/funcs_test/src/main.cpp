
#include <iostream>

typedef unsigned char uint8_t;
#define CMD_LEN 64

short str2int( const char * stri )
{
    uint8_t ind = 0;
    uint8_t neg = ( stri[ind] == '-' ) ? 1 : 0;
    if ( neg )
        ind++;
    short res = 0;
    char val = stri[ ind ];
    while ( ( val >= '0' ) && ( val <= '9' ) && ( ind < CMD_LEN ) )
    {
        res *= 10;
        res += (short)( val-'0' );
        ind++;
        val = stri[ind];
    }
    if ( neg )
        res = -res;
    return res;
}

void main()
{
    std::cout << str2int( "-0023" );
}