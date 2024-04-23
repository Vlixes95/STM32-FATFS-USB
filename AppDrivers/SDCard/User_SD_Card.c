#include "user_sd_card.h"

#include "string.h"
#include "stdlib.h"

// TOOD: store the sdcard->messages in sdCard.sdcard->message
// first memset(sdcard.messsage, '\0', 100);

void Mount_SD(SDcardTypeDef *sdcard, char *path) {

	sdcard->f_result = f_mount(&sdcard->fs, path, 1);
	if (sdcard->f_result == FR_OK) {
		strncpy(sdcard->message, "Successfully mounted SD card...",
		MAX_MESSAGE_SIZE); // MAX_MESSAGE_SIZE + 1
	} else {
		strncpy(sdcard->message, "Error mounting SD card...", MAX_MESSAGE_SIZE);
	}

}

void Unmount_SD(SDcardTypeDef *sdcard, const char *path) {

	sdcard->f_result = f_unmount(path);
	if (sdcard->f_result == FR_OK) {
		strncpy(sdcard->message, "Successfully unmounted SD card...",
		MAX_MESSAGE_SIZE);
	} else {
		strncpy(sdcard->message, "Error unmounting SD card...", MAX_MESSAGE_SIZE);
	}

}

void OpenFile(SDcardTypeDef *sdcard, char *pathName) {

	sdcard->f_result = f_open(&sdcard->file, pathName,
	FA_CREATE_ALWAYS | FA_WRITE);
	if (sdcard->f_result == FR_OK) {
		strncpy(sdcard->message, "Successfully opened the file...",
		MAX_MESSAGE_SIZE);
	} else {
		strncpy(sdcard->message, "Error opening the file...", MAX_MESSAGE_SIZE);
	}

}

void CreateFileOnly_SD(SDcardTypeDef *sdcard, char *pathName) {

	OpenFile(sdcard, pathName);

	if (sdcard->f_result == FR_OK) {
		sdcard->f_result = f_close(&sdcard->file);
		if (sdcard->f_result == FR_OK) {
			strncpy(sdcard->message, "Successfully closed the file...",
			MAX_MESSAGE_SIZE);
		} else {
			strncpy(sdcard->message, "Error closing the file...",
			MAX_MESSAGE_SIZE);
		}
	}

}

void CreateAndWriteFile_SD(SDcardTypeDef *sdcard, char *pathName, char *buff) {

	OpenFile(sdcard, pathName);

	if (sdcard->f_result == FR_OK) {
		UINT bw;
		sdcard->f_result = f_write(&sdcard->file, buff, strlen(buff), &bw);

		if (sdcard->f_result == FR_OK) {
			sprintf(sdcard->message,
					"Successfully written the file. %d number of bytes written...",
					bw);
		} else {
			strncpy(sdcard->message, "Error writing the file...",
			MAX_MESSAGE_SIZE);
		}

		if (sdcard->f_result == FR_OK) {
			sdcard->f_result = f_close(&sdcard->file);
			if (sdcard->f_result == FR_OK) {
				strncpy(sdcard->message, "Successfully closed the file...",
				MAX_MESSAGE_SIZE);
			} else {
				strncpy(sdcard->message, "Error closing the file...",
				MAX_MESSAGE_SIZE);
			}

		}
	}

}

void UpdateFile_SD(SDcardTypeDef *sdcard, char *pathName, char *buff) {

	OpenFile(sdcard, pathName);

	if (sdcard->f_result == FR_OK) {
		UINT bw;
		sdcard->f_result = f_write(&sdcard->file, buff, strlen(buff), &bw);
		if (sdcard->f_result == FR_OK) {
			sprintf(sdcard->message,
					"Successfully written the file. %d number of bytes written...",
					bw);
			strncpy(sdcard->message, "Error opening the file...",
			MAX_MESSAGE_SIZE);
		} else {
			strncpy(sdcard->message, "Error writing the file...",
			MAX_MESSAGE_SIZE);
		}

		if (sdcard->f_result == FR_OK) {
			sdcard->f_result = f_close(&sdcard->file);
			if (sdcard->f_result == FR_OK) {
				strncpy(sdcard->message, "Successfully closed the file...",
				MAX_MESSAGE_SIZE);
			} else {
				strncpy(sdcard->message, "Error closing the file...",
				MAX_MESSAGE_SIZE);
			}

		}
	}

}

void WriteFile_SD(SDcardTypeDef *sdcard, char *pathName, char *buff) {

	OpenFile(sdcard, pathName);

	if (sdcard->f_result == FR_OK) {
		UINT bw;
		sdcard->f_result = f_write(&sdcard->file, buff, strlen(buff), &bw);
		if (sdcard->f_result == FR_OK) {
			strncpy(sdcard->message, "Successfully written the file...",
			MAX_MESSAGE_SIZE);
		} else {
			strncpy(sdcard->message, "Error opening the file...",
			MAX_MESSAGE_SIZE);
		}
	}

}

void EraseFile_SD(SDcardTypeDef *sdcard, char *pathName) {

	sdcard->f_result = f_unlink(pathName);
	if (sdcard->f_result == FR_OK) {
		strncpy(sdcard->message, "Successfully deleted the file...",
		MAX_MESSAGE_SIZE);
	} else {
		strncpy(sdcard->message, "Error deleting the file...", 28);
	}

}

void ReadFile_SD(SDcardTypeDef *sdcard, char *pathName, char *buff,
		UINT *bytesRead) {

	BYTE buffer[1000] = { '0' };
	sdcard->f_result = f_open(&sdcard->file, pathName, FA_READ);

	if (sdcard->f_result == FR_OK) {
		strncpy(sdcard->message, "Successfully opened the file...",
		MAX_MESSAGE_SIZE);
	} else {
		strncpy(sdcard->message, "Error opening the file...", MAX_MESSAGE_SIZE);
	}

	if (sdcard->f_result == FR_OK) {
		UINT br;
		for (;;) {
			sdcard->f_result = f_read(&sdcard->file, buffer, sizeof buffer,
					&br);
			if (br == 0) {
				break; /* error or eof */
			} else {
				*bytesRead = br;
			}
		}

		strncpy(buff, buffer, *bytesRead);

		if (sdcard->f_result == FR_OK) {
			strncpy(sdcard->message, "Successfully readed the file...",
			MAX_MESSAGE_SIZE);
		} else {
			strncpy(sdcard->message, "Error reading the file...",
			MAX_MESSAGE_SIZE);
		}

		if (sdcard->f_result == FR_OK) {
			sdcard->f_result = f_close(&sdcard->file);
			if (sdcard->f_result == FR_OK) {
				strncpy(sdcard->message, "Successfully closed the file...",
				MAX_MESSAGE_SIZE);
			} else {
				strncpy(sdcard->message, "Error closing the file...",
				MAX_MESSAGE_SIZE);
			}

		}
	}

}

/* TODO: Add RTOS to check if sd card is connected*/
void FileStatus_SD(SDcardTypeDef *sdcard, const char *fileName,
		FILINFO *fileInfo) {

	sdcard->f_result = f_stat(fileName, fileInfo);
	if (sdcard->f_result == FR_OK) {
		strncpy(sdcard->message, "Successfully got the file status...",
		MAX_MESSAGE_SIZE);
	} else {
		strncpy(sdcard->message, "Error getting file status...",
		MAX_MESSAGE_SIZE);
	}

}

void MKDIR_SD(SDcardTypeDef *sdcard, char *folder) {

	sdcard->f_result = f_mkdir(folder);
	if (sdcard->f_result == FR_OK) {
		strncpy(sdcard->message, "Successfully creating a folder...",
		MAX_MESSAGE_SIZE);
	}

	if (sdcard->f_result != FR_EXIST) {
		strncpy(sdcard->message, "Error creating a folder...", MAX_MESSAGE_SIZE);
	}

	sdcard->f_result = FR_OK;

}

void scan_files(SDcardTypeDef *sdcard, char *path, struct USBData *usb_data) {

	DIR dir;
	UINT i;
	static FILINFO fno;

	sdcard->f_result = f_opendir(&dir, path); /* Open the directory */
	if (sdcard->f_result == FR_OK) {
		char fileName[50];
		memset(fileName, '\0', 50);
		for (;;) {
			sdcard->f_result = f_readdir(&dir, &fno); /* Read a directory item */
			if (sdcard->f_result != FR_OK || fno.fname[0] == 0)
				break; /* Break on error or end of dir */
			if (fno.fattrib & AM_DIR) { /* It is a directory */
				i = strlen(path);
				sprintf(&path[i], "/%s", fno.fname);
				scan_files(sdcard, path, usb_data); /* Enter the directory */
				if (sdcard->f_result != FR_OK)
					break;

				path[i] = 0;
			} else { /* It is a file. */
				sprintf(&fileName[0], "/%s", fno.fname);
			}
			char copyPath[50];
			strcpy(copyPath, path);
			strcat(copyPath, fileName);
			strcat(usb_data->content, copyPath);
			strcat(usb_data->content, ";");
		}

		f_closedir(&dir);
	}

}
