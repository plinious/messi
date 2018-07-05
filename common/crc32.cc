#include "src32.h"

namespace messi {

    unsigned int CRC32::checksum(const void *src, size_t len) {
        static bool needInitTableb = true;
        static u32 CRCTable[256];

        if (bCalcTable) {
            Init_CRC32_Table( CRCTable );
            bCalcTable = false;
        }

        if ( dwLength == 0 )
        {
            return 0;
        }

        unsigned int CRC = 0xFFFFFFFF;
        const u8 *pD = (const u8*)chData;

        for (size_t i = 0; i < dwLength; i++)
        {
            CRC = CRCTable[( CRC^( *( pD+i ) ) )&0xff] ^ ( CRC >> 8 );
        }

        return ~CRC;
#else
        return 0;
#endif
    }
    //----------------------------------------------
    u32 CRC32::Reflect( u32 ref, char ch )
    {
        u32 i, value = 0;

        // swap bit0 and bit7, bit1 and bit6, and so on
        for ( i = 1; i < u32( ch + 1 ); i++ )
        {
            if ( ref & 1 )
            {
                value |= 1 << ( ch - i );
            }

            ref >>= 1;
        }

        return value;
    }
    //----------------------------------------------
    void CRC32::Init_CRC32_Table( u32* table )
    {
        u32 i, j;
        u32 crc, temp;
        (void)crc;

        // 256 values
        for ( i = 0; i < 256; i++ )
        {
            temp = Reflect( i, 8 );
            table[i] = temp << 24;

            for ( j = 0; j < 8; j++ )
            {
                u32 t1, t2;
                u32 flag = table[i] & 0x80000000;
                t1 = ( table[i] << 1 );

                if ( flag == 0 )
                {
                    t2 = 0;
                }
                else
                {
                    t2 = 0x04c11db7;
                }

                table[i] = t1 ^ t2 ;
            }

            crc = table[i];
            table[i] = Reflect( table[i], 32 );
        }
    }
}
