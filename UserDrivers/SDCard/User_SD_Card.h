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

#define MESSAGE_SIZE    200

typedef struct {
    FATFS fs;
    FIL file;
    FRESULT fResult;
    char message[MESSAGE_SIZE];
    UINT br, bw;
} SDcardTypeDef;

void Mount_SD ( SDcardTypeDef *sdcard, char *path );

void Unmount_SD ( SDcardTypeDef *sdcard, const char *path );

void CreateFileOnly_SD ( SDcardTypeDef *sdcard, char *pathName );

void CreateAndWriteFile_SD ( SDcardTypeDef *sdcard, char *pathName, char *buff );

void UpdateFile_SD ( SDcardTypeDef *sdcard, char *pathName, char *buff );

void FileStatus_SD ( SDcardTypeDef *sdcard, const char *fileName, FILINFO *fileInfo );

void EraseFile_SD ( SDcardTypeDef *sdcard, char *pathName );

void WriteFile_SD ( SDcardTypeDef *sdcard, char *pathName, char *buff );

void ReadFile_SD ( SDcardTypeDef *sdcard, char *pathName, char *buff, UINT *bytesRead );

void MKDIR_SD ( SDcardTypeDef *sdcard, char *folder );

void scan_files ( SDcardTypeDef *sdcard, char *path, struct USBData *usbData );

void restartSDCard ( SDcardTypeDef *sdcard );

#ifdef __cplusplus
}
#endif

#endif