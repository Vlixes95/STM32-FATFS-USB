#include "../MSGPack/MSGPack.h"

#include "../../AppDrivers/SDCard/User_SD_Card.h"

void PackMSG ( const char *stringToPack, uint32_t stringSize, struct USBDataReceived *usbDataReceived ) {
    DWORD i = 0;
    bool init = false;
    uint8_t size = 0;
    uint8_t numOfFields = 0;

    memset(usbDataReceived->usbData.fileName, '\0', 50);
    memset(usbDataReceived->usbData.content, '\0', 1000);

    while ( i <= stringSize ) {

        if ( stringToPack[i] == '}' ) {
            break;
        }

        if ( stringToPack[i] == '{' && !init )
            init = true;

        if ( init ) {
            if ( stringToPack[i] == 'L' ) {
                ++i;
                char tmpSize[10] = "\0";

                for ( int j = 0; j < 10; ++j ) {
                    if ( stringToPack[i] == 'C' ) {
                        break;
                    }
                    tmpSize[j] = stringToPack[i];
                    ++i;
                    //TODO: control if i>10
                }
                size = atoi( tmpSize );
            }

            if ( stringToPack[i] == 'C' ) {
                ++i;
                char *buff = ( char * ) malloc( size * sizeof( char ) + 1 ); // +1 for '\0'
                for ( int j = 0; j < size; ++j ) {
                    buff[j] = stringToPack[i];
                    if (( j + 1 ) >= size ) {
                        buff[j + 1] = '\0';
                        break;
                    }
                    ++i;
                }

                if ( numOfFields == 0 ) {
                    usbDataReceived->usbData.command = buff[0];
                } else if ( numOfFields == 1 ) {
                    strncpy( usbDataReceived->usbData.fileName, buff, size );
                } else if ( numOfFields == 2 ) {
                    strncpy( usbDataReceived->usbData.content, buff, size );
                }
                ++numOfFields;
                free( buff );
            }
        }
        ++i;
    }
}

void UnpackMSG ( struct USBData *usbData, char *textJson ) {
    char json[1000];
    char tmp[1000];
    memset( json, '\0', 1000 );
    strcat( json, "{" );
    uint8_t numOfFields = 0;
    uint8_t size = 0;
    for ( int i = 0; i < 3; ++i ) {

        if ( numOfFields == 0 ) {
            tmp[0] = usbData->command;
            tmp[1] = '\0';
        } else if ( numOfFields == 1 ) {
            strcpy( tmp, usbData->fileName );
        } else if ( numOfFields == 2 ) {
            strcpy( tmp, usbData->content );
        }
        ++numOfFields;

        for ( size = 0; tmp[size] != '\0'; ++size );

        strcat( json, "L" );
        char snum[10];
        itoa( size, snum, 10 );
        strcat( json, snum );
        strcat( json, "C" );
        strcat( json, tmp );
    }
    strcat( json, "}" );
    strcpy( textJson, json );
}
