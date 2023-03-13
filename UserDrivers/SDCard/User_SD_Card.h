#ifndef __USER_SD_CARD_H_
#define __USER_SD_CARD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "fatfs.h"
#include <string.h>
#include <stdio.h>
#include "USB_Data.h"

#define f_unmount( path ) f_mount(NULL, path, 0)

typedef struct {
    FATFS fs;
    FIL file;
    FRESULT fresult;
    char message[100];
    UINT br, bw;
} SDcardTypeDef;

FRESULT Mount_SD ( FATFS *fs, char *path );

FRESULT Unmount_SD ( char *path );

FRESULT CreateFileOnly_SD ( FIL *file, char *pathName );

FRESULT CreateAndWriteFile_SD ( FIL *file, char *pathName, char *buff );

FRESULT UpdateFile_SD ( FIL *file, char *pathName, char *buff );

FRESULT FileStatus_SD ( const char *fileName, FILINFO *fileInfo );

FRESULT EraseFile_SD ( char *pathName );

FRESULT WriteFile_SD ( FIL *file, char *pathName, char *buff );

FRESULT ReadFile_SD ( FIL *file, char *pathName, char *buff, UINT *bytesRead );

FRESULT MKDIR_SD ( char *folder );

FRESULT scan_files ( char *path, struct USBData *usbData );

#ifdef __cplusplus
}
#endif

#endif