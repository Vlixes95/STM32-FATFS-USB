#ifndef __USER_SD_CARD_H_
#define __USER_SD_CARD_H_

#include "fatfs.h"
#include <string.h>
#include <stdio.h>
#include "../USB/usb_data.h"

#define f_unmount( path ) f_mount(NULL, path, 0)
#define MAX_MESSAGE_SIZE        200
#define NUMBER_ERROR_MESSAGES   20

// TODO: ErrorCode
typedef struct {
	FATFS fs;
	FIL file;
	FRESULT f_result;
	char message[MAX_MESSAGE_SIZE];
	UINT br, bw;
} SDcardTypeDef;

/* (0) Succeeded */
/* (1) A hard error occurred in the low level disk I/O layer */
/* (2) Assertion failed */
/* (3) The physical drive cannot work */
/* (4) Could not find the file */
/* (5) Could not find the path */
/* (6) The path name format is invalid */
/* (7) Access denied due to prohibited access or directory full */
/* (8) Access denied due to prohibited access */
/* (9) The file/directory object is invalid */
/* (10) The physical drive is write protected */
/* (11) The logical drive number is invalid */
/* (12) The volume has no work area */
/* (13) There is no valid FAT volume */
/* (14) The f_mkfs() aborted due to any problem */
/* (15) Could not get a grant to access the volume within defined period */
/* (16) The operation is rejected according to the file sharing policy */
/* (17) LFN working buffer could not be allocated */
/* (18) Number of open files > _FS_LOCK */
/* (19) Given parameter is invalid */
// TODO: Implement
//const char SDCardResultMessages[NUMBER_ERROR_MESSAGES][MESSAGE_SIZE] = {
//        { "Succeeded" },
//        { "A hard error occurred in the low level disk I/O layer" },
//        { "Assertion failed" },
//        { "The physical drive cannot work" },
//        { "Could not find the file" },
//        { "Could not find the path" },
//        { "The path name format is invalid" },
//        { "Access denied due to prohibited access or directory full" },
//        { "Access denied due to prohibited access" },
//        { "The file/directory object is invalid" },
//        { "The physical drive is write protected" },
//        { " The logical drive number is invalid" },
//        { "The volume has no work area" },
//        { "There is no valid FAT volume" },
//        { "The f_mkfs() aborted due to any problem" },
//        { "Could not get a grant to access the volume within defined period" },
//        { "The operation is rejected according to the file sharing policy" },
//        { "LFN working buffer could not be allocated" },
//        { "Number of open files > _FS_LOCK" },
//        { "Given parameter is invalid" }
//};

void Mount_SD(SDcardTypeDef *sdcard, char *path);

void Unmount_SD(SDcardTypeDef *sdcard, const char *path);

void CreateFileOnly_SD(SDcardTypeDef *sdcard, char *pathName);

void CreateAndWriteFile_SD(SDcardTypeDef *sdcard, char *pathName, char *buff);

void UpdateFile_SD(SDcardTypeDef *sdcard, char *pathName, char *buff);

void FileStatus_SD(SDcardTypeDef *sdcard, const char *fileName, FILINFO *fileInfo);

void EraseFile_SD(SDcardTypeDef *sdcard, char *pathName);

void WriteFile_SD(SDcardTypeDef *sdcard, char *pathName, char *buff);

void ReadFile_SD(SDcardTypeDef *sdcard, char *pathName, char *buff,	UINT *bytesRead);

void MKDIR_SD(SDcardTypeDef *sdcard, char *folder);

void scan_files(SDcardTypeDef *sdcard, char *path, struct USBData *usb_data);

void restartSDCard(SDcardTypeDef *sdcard);

#endif
