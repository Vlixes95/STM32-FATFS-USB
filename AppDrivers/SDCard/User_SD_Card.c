#include "string.h"
#include "stdlib.h"
#include "../../AppDrivers/SDCard/User_SD_Card.h"

// TOOD: store the sdcard->messages in sdCard.sdcard->message
// first memset(sdcard.messsage, '\0', 100);

void Mount_SD ( SDcardTypeDef *sdcard, char *path ) {

    sdcard->fResult = f_mount( &sdcard->fs, path, 1 );
    if ( sdcard->fResult == FR_OK ) {
        strncpy( sdcard->message, "Successfully mounted SD card...\0", MESSAGE_SIZE ); // MESSAGE_SIZE + 1
    } else {
        strncpy( sdcard->message, "Error mounting SD card...\0", MESSAGE_SIZE ); // MESSAGE_SIZE + 1
    }

}

void Unmount_SD ( SDcardTypeDef *sdcard, const char *path ) {

    sdcard->fResult = f_unmount( path );
    if ( sdcard->fResult == FR_OK ) {
        strncpy( sdcard->message, "Successfully unmounted SD card...\0", MESSAGE_SIZE );
    } else {
        strncpy( sdcard->message, "Error unmounting SD card...\0", MESSAGE_SIZE );
    }

}

void OpenFile ( SDcardTypeDef *sdcard, char *pathName ) {

    sdcard->fResult = f_open( &sdcard->file, pathName, FA_CREATE_ALWAYS | FA_WRITE );
    if ( sdcard->fResult == FR_OK ) {
        strncpy( sdcard->message, "Successfully opened the file...\0", MESSAGE_SIZE ); // +1 ?
    } else {
        strncpy( sdcard->message, "Error opening the file...\0", MESSAGE_SIZE );
    }

}

void CreateFileOnly_SD ( SDcardTypeDef *sdcard, char *pathName ) {

    OpenFile( sdcard, pathName );

    if ( sdcard->fResult == FR_OK ) {
        sdcard->fResult = f_close( &sdcard->file );
        if ( sdcard->fResult == FR_OK ) {
            strncpy( sdcard->message, "Successfully closed the file...\0", MESSAGE_SIZE );
        } else {
            strncpy( sdcard->message, "Error closing the file...\0", MESSAGE_SIZE );
        }
    }

}

void CreateAndWriteFile_SD ( SDcardTypeDef *sdcard, char *pathName, char *buff ) {

    OpenFile( sdcard, pathName );

    if ( sdcard->fResult == FR_OK ) {
        UINT bw;
        sdcard->fResult = f_write( &sdcard->file, buff, strlen( buff ), &bw );

        if ( sdcard->fResult == FR_OK ) {
            sprintf( sdcard->message, "Successfully written the file. %d number of bytes written...", bw );
        } else {
            strncpy( sdcard->message, "Error writing the file...\0", MESSAGE_SIZE );
        }

        if ( sdcard->fResult == FR_OK ) {
            sdcard->fResult = f_close( &sdcard->file );
            if ( sdcard->fResult == FR_OK ) {
                strncpy( sdcard->message, "Successfully closed the file...\0", MESSAGE_SIZE );
            } else {
                strncpy( sdcard->message, "Error closing the file...\0", MESSAGE_SIZE );
            }

        }
    }

}

void UpdateFile_SD ( SDcardTypeDef *sdcard, char *pathName, char *buff ) {


    OpenFile( sdcard, pathName );

    if ( sdcard->fResult == FR_OK ) {
        UINT bw;
        sdcard->fResult = f_write( &sdcard->file, buff, strlen( buff ), &bw );
        if ( sdcard->fResult == FR_OK ) {
            sprintf( sdcard->message, "Successfully written the file. %d number of bytes written...", bw );
            strncpy( sdcard->message, "Error opening the file...\0", MESSAGE_SIZE );
        } else {
            strncpy( sdcard->message, "Error writing the file...\0", MESSAGE_SIZE );
        }

        if ( sdcard->fResult == FR_OK ) {
            sdcard->fResult = f_close( &sdcard->file );
            if ( sdcard->fResult == FR_OK ) {
                strncpy( sdcard->message, "Successfully closed the file...\0", MESSAGE_SIZE );
            } else {
                strncpy( sdcard->message, "Error closing the file...\0", MESSAGE_SIZE );
            }

        }
    }

}

void WriteFile_SD ( SDcardTypeDef *sdcard, char *pathName, char *buff ) {

    OpenFile( sdcard, pathName );

    if ( sdcard->fResult == FR_OK ) {
        UINT bw;
        sdcard->fResult = f_write( &sdcard->file, buff, strlen( buff ), &bw );
        if ( sdcard->fResult == FR_OK ) {
            strncpy( sdcard->message, "Successfully written the file...\0", MESSAGE_SIZE );
        } else {
            strncpy( sdcard->message, "Error opening the file...\0", MESSAGE_SIZE );
        }
    }

}

void EraseFile_SD ( SDcardTypeDef *sdcard, char *pathName ) {

    sdcard->fResult = f_unlink( pathName );
    if ( sdcard->fResult == FR_OK ) {
        strncpy( sdcard->message, "Successfully deleted the file...\0", MESSAGE_SIZE );
    } else {
        strncpy( sdcard->message, "Error deleting the file...\0", 28 );
    }

}

void ReadFile_SD ( SDcardTypeDef *sdcard, char *pathName, char *buff, UINT *bytesRead ) {

    BYTE buffer[1000]; //4096
    memset( buffer, '\0', 1000 );
    sdcard->fResult = f_open( &sdcard->file, pathName, FA_READ );

    if ( sdcard->fResult == FR_OK ) {
        strncpy( sdcard->message, "Successfully opened the file...\0", MESSAGE_SIZE );
    } else {
        strncpy( sdcard->message, "Error opening the file...\0", MESSAGE_SIZE );
    }

    if ( sdcard->fResult == FR_OK ) {
        UINT br;
        for ( ;; ) {
            sdcard->fResult = f_read( &sdcard->file, buffer, sizeof buffer, &br );
            if ( br == 0 ) {
                break; /* error or eof */
            } else {
                *bytesRead = br;
            }
        }

        strncpy( buff, buffer, *bytesRead );

        if ( sdcard->fResult == FR_OK ) {
            strncpy( sdcard->message, "Successfully readed the file...\0", MESSAGE_SIZE );
        } else {
            strncpy( sdcard->message, "Error reading the file...\0", MESSAGE_SIZE );
        }


        if ( sdcard->fResult == FR_OK ) {
            sdcard->fResult = f_close( &sdcard->file );
            if ( sdcard->fResult == FR_OK ) {
                strncpy( sdcard->message, "Successfully closed the file...\0", MESSAGE_SIZE );
            } else {
                strncpy( sdcard->message, "Error closing the file...\0", MESSAGE_SIZE );
            }

        }
    }

}

/* TODO: Add RTOS to check if sd card is connected*/
void FileStatus_SD ( SDcardTypeDef *sdcard, const char *fileName, FILINFO *fileInfo ) {

    sdcard->fResult = f_stat( fileName, fileInfo );
    if ( sdcard->fResult == FR_OK ) {
        strncpy( sdcard->message, "Successfully got the file status...\0", MESSAGE_SIZE );
    } else {
        strncpy( sdcard->message, "Error getting file status...\0", MESSAGE_SIZE );
    }

}

void MKDIR_SD ( SDcardTypeDef *sdcard, char *folder ) {

    sdcard->fResult = f_mkdir( folder );
    if ( sdcard->fResult == FR_OK ) {
        strncpy( sdcard->message, "Succsessfully creating a folder", MESSAGE_SIZE );
    }


    if(sdcard->fResult != FR_EXIST){
        strncpy( sdcard->message, "Error creating a folder...\0", MESSAGE_SIZE );
    }

    sdcard->fResult = FR_OK;

}

void scan_files ( SDcardTypeDef *sdcard, char *path, struct USBData *usb_data ) {

    DIR dir;
    UINT i;
    static FILINFO fno;

    sdcard->fResult = f_opendir( &dir, path );                              /* Open the directory */
    if ( sdcard->fResult == FR_OK ) {
        char fileName[50];
        memset( fileName, '\0', 50 );
        for ( ;; ) {
            sdcard->fResult = f_readdir( &dir, &fno );                      /* Read a directory item */
            if ( sdcard->fResult != FR_OK || fno.fname[0] == 0 ) break;         /* Break on error or end of dir */
            if ( fno.fattrib & AM_DIR ) {                           /* It is a directory */
                i = strlen( path );
                sprintf( &path[i], "/%s", fno.fname );
                scan_files( sdcard, path, usb_data );                   /* Enter the directory */
                if ( sdcard->fResult != FR_OK ) break;

                path[i] = 0;
            } else {                                                 /* It is a file. */
                sprintf( &fileName[0], "/%s", fno.fname );
            }
            char copyPath[50];
            strcpy( copyPath, path );
            strcat( copyPath, fileName );
            strcat( usb_data->content, copyPath );
            strcat( usb_data->content, ";" );
        }

        f_closedir( &dir );
    }

}
