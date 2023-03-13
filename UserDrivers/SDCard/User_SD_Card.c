#include "string.h"
#include "stdlib.h"
#include "User_SD_Card.h"

// TOOD: store the messages in sdCard.message
// first memset(sdcard.messsage, '\0', 100);

FRESULT Mount_SD ( FATFS *fs, char *path ) {
    char *message = malloc( 50 * sizeof( char ));
    FRESULT result = f_mount( fs, path, 1 );

    if ( result == FR_OK ) {
        strncpy( message, "Successfully mounted SD card...\n", 33 ); // 33 + 1
    } else {
        strncpy( message, "Error mounting SD card...\n", 28 ); // 27 + 1
    }

    free( message );
    return result;
}

FRESULT Unmount_SD ( char *path ) {
    char *message = malloc( 50 * sizeof( char ));

    FRESULT result = f_unmount( path );
    if ( result == FR_OK ) {
        strncpy( message, "Successfully unmounted SD card...\n", 35 );
    } else {
        strncpy( message, "Error unmounting SD card...\n", 29 );
    }

    free( message );
    return result;
}

FRESULT OpenFile ( FIL *file, char *pathName ) {
    char *message = malloc( 50 * sizeof( char ));

    FRESULT result = f_open( file, pathName, FA_CREATE_ALWAYS | FA_WRITE );
    if ( result == FR_OK ) {
        strncpy( message, "Successfully opened the file...\n", 31 ); // +1 ?
    } else {
        strncpy( message, "Error opening the file...\n", 25 );
    }

    free( message );
    return result;
}

FRESULT CreateFileOnly_SD ( FIL *file, char *pathName ) {
    char *message = malloc( 50 * sizeof( char ));

    FRESULT result = OpenFile ( file, pathName);

    if ( result == FR_OK ) {
        result = f_close( file );
        if ( result == FR_OK ) {
            strncpy( message, "Successfully closed the file...\n", 31 );
        } else {
            strncpy( message, "Error closing the file...\n", 25 );
        }
    }

    free( message );
    return result;
}

FRESULT CreateAndWriteFile_SD ( FIL *file, char *pathName, char *buff ) {
    FILINFO info;
    UINT bw;
    char *message = malloc( 80 * sizeof( char ));

    FRESULT result = OpenFile ( file, pathName);

    if ( result == FR_OK ) {
        result = f_write( file, buff, strlen( buff ), &bw );
        if ( result == FR_OK ) {
            sprintf( message, "Successfully written the file. %d number of bytes written...\n", bw );
        } else {
            strncpy( message, "Error writing the file...\n", 27 );
        }

        if ( result == FR_OK ) {
            result = f_close( file );
            if ( result == FR_OK ) {
                strncpy( message, "Successfully closed the file...\n", 33 );
            } else {
                strncpy( message, "Error closing the file...\n", 27 );
            }

        }
    }

    free( message );
    return result;
}

FRESULT UpdateFile_SD ( FIL *file, char *pathName, char *buff ) {
    UINT bw;
    char *message = malloc( 80 * sizeof( char ));

    FRESULT result = OpenFile ( file, pathName);

    if ( result == FR_OK ) {
        result = f_write( file, buff, strlen( buff ), &bw );
        if ( result == FR_OK ) {
            sprintf( message, "Successfully written the file. %d number of bytes written...\n", bw );
            strncpy( message, "Error opening the file...\n", 25 );
        } else {
            strncpy( message, "Error writing the file...\n", 27 );
        }

        if ( result == FR_OK ) {
            result = f_close( file );
            if ( result == FR_OK ) {
                strncpy( message, "Successfully closed the file...\n", 33 );
            } else {
                strncpy( message, "Error closing the file...\n", 27 );
            }

        }
    }

    free( message );
    return result;
}

FRESULT WriteFile_SD ( FIL *file, char *pathName, char *buff ) {
    UINT bw;
    char *message = malloc( 50 * sizeof( char ));

    FRESULT result = OpenFile ( file, pathName);

    if ( result == FR_OK ) {
        result = f_write( file, buff, strlen( buff ), &bw );
        if ( result == FR_OK ) {
            strncpy( message, "Successfully written the file...\n", 34 );
        } else {
            strncpy( message, "Error opening the file...\n", 27 );
        }
    }

    free( message );
    return result;
}

FRESULT EraseFile_SD ( char *pathName ) {
    char *message = malloc( 50 * sizeof( char ));

    FRESULT result = f_unlink( pathName );
    if ( result == FR_OK ) {
        strncpy( message, "Successfully deleted the file...\n", 34 );
    } else {
        strncpy( message, "Error deleting the file...\n", 28 );
    }

    free( message );
    return result;
}

FRESULT ReadFile_SD ( FIL *file, char *pathName, char *buff, UINT *bytesRead ) {
    UINT br = 0;
    char *message = malloc( 50 * sizeof( char ));
    BYTE buffer[1000]; //4096
    memset( buffer, '\0', 1000 );
    FRESULT result = f_open( file, pathName, FA_READ );

    if ( result == FR_OK ) {
        strncpy( message, "Successfully opened the file...\n", 33 );
    } else {
        strncpy( message, "Error opening the file...\n", 27 );
    }

    if ( result == FR_OK ) {
        for ( ;; ) {
            result = f_read( file, buffer, sizeof buffer, &br );
            if ( br == 0 ) {
                break; /* error or eof */
            } else {
                *bytesRead = br;
            }
        }

        strncpy( buff, buffer, *bytesRead );

        if ( result == FR_OK ) {
            strncpy( message, "Successfully readed the file...\n", 25 );
        } else {
            strncpy( message, "Error reading the file...\n", 25 );
        }


        if ( result == FR_OK ) {
            result = f_close( file );
            if ( result == FR_OK ) {
                strncpy( message, "Successfully closed the file...\n", 33 );
            } else {
                strncpy( message, "Error closing the file...\n", 27 );
            }

        }
    }

    free( message );
    return result;
}

/* TODO: Add RTOS to check if sd card is connected*/
FRESULT FileStatus_SD ( const char *fileName, FILINFO *fileInfo ) {
    char *message = malloc( 50 * sizeof( char ));

    FRESULT result = f_stat( fileName, fileInfo );
    if ( result == FR_OK ) {
        strncpy( message, "Successfully got the file status...\n", 37 );
    } else {
        strncpy( message, "Error getting file status...\n", 30 );
    }


    free( message );
    return result;
}

FRESULT MKDIR_SD ( char *folder ) {
    char *message = malloc( 50 * sizeof( char ));

    FRESULT fresult = f_mkdir( folder );
    if ( fresult == FR_OK ) {
        strncpy( message, "Succsessfully creating a folder", 32 );
    } else {
        strncpy( message, "Error creating a folder...\n", 28 );
    }

    free( message );
    return fresult;
}

FRESULT scan_files (
        char *path,        /* Start node to be scanned (***also used as work area***) */
        struct USBData *usbData
) {
    FRESULT res;
    DIR dir;
    UINT i;
    static FILINFO fno;
    char fullPath[50];
    res = f_opendir( &dir, path );                              /* Open the directory */
    if ( res == FR_OK ) {
        char fileName[50];
        memset( fileName, '\0', 50 );
        for ( ;; ) {
            res = f_readdir( &dir, &fno );                      /* Read a directory item */
            if ( res != FR_OK || fno.fname[0] == 0 ) break;         /* Break on error or end of dir */
            if ( fno.fattrib & AM_DIR ) {                           /* It is a directory */
                i = strlen( path );
                sprintf( &path[i], "/%s", fno.fname );
                res = scan_files( path, usbData );                   /* Enter the directory */
                if ( res != FR_OK ) break;

                path[i] = 0;
            } else {                                                 /* It is a file. */
                i = strlen( path );
                sprintf( &fileName[0], "/%s", fno.fname );
            }
            i = strlen( path );
            char copyPath[50];
            strcpy( copyPath, path );
            strcat( copyPath, fileName );
            strcat( usbData->content, copyPath );
            strcat( usbData->content, ";" );
        }

        f_closedir( &dir );
    }
    return res;
}
