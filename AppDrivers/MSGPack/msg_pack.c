#include "msg_pack.h"

#include "../SDCard/user_sd_card.h"

void packMSG(const char *stringToPack, uint32_t stringSize, struct UsbDataReceived *usb_data_received) {

	DWORD i = 0;
	bool init = false;
	uint8_t size = 0;
	uint8_t numOfFields = 0;

	memset(usb_data_received->usb_data.fileName, '\0', FILE_NAME_MAX_LENGHT);
	memset(usb_data_received->usb_data.content, '\0', CONTENT_MAX_LENGHT);

	while (i <= stringSize) {

		if (stringToPack[i] == '}') {
			break;
		}

		if (stringToPack[i] == '{' && !init)
			init = true;

		if (init) {
			if (stringToPack[i] == 'L') {
				++i;
				char tmpSize[10] = "\0";

				for (int j = 0; j < 10; ++j) {
					if (stringToPack[i] == 'C') {
						break;
					}
					tmpSize[j] = stringToPack[i];
					++i;
					//TODO: control if i>10
				}
				size = atoi(tmpSize);
			}

			if (stringToPack[i] == 'C') {
				++i;
				char *buff = (char*) malloc(size * sizeof(char) + 1); // +1 for '\0'
				for (int j = 0; j < size; ++j) {
					buff[j] = stringToPack[i];
					if ((j + 1) >= size) {
						buff[j + 1] = '\0';
						break;
					}
					++i;
				}

				if (numOfFields == 0) {
					usb_data_received->usb_data.command = buff[0];
				} else if (numOfFields == 1) {
					strncpy(usb_data_received->usb_data.fileName, buff, size);
				} else if (numOfFields == 2) {
					strncpy(usb_data_received->usb_data.content, buff, size);
				}
				++numOfFields;
				free(buff);
			}
		}
		++i;
	}
}

void UnpackMSG(struct USBData *usb_data, char *textJson) {

	uint8_t size = 0;
	uint8_t numOfFields = 0;
	char json[1000] = {'\0'};
	char tmp[1000] = {'\0'};

	strncat(json, "{", 2);

	for (int i = 0; i < 3; ++i) {

		if (numOfFields == 0) {
			tmp[0] = usb_data->command;
			tmp[1] = '\0';
		} else if (numOfFields == 1) {
			strncpy(tmp, usb_data->fileName, FILE_NAME_MAX_LENGHT);
		} else if (numOfFields == 2) {
			strncpy(tmp, usb_data->content, CONTENT_MAX_LENGHT);
		}
		++numOfFields;

		for (size = 0; tmp[size] != '\0'; ++size)
			;

		strncat(json, "L", 2);
		
		char snum[10];
		itoa(size, snum, 10);

		strcat(json, snum);
		strncat(json, "C", 2);
		strncat(json, tmp, 1000);
	}

	strncat(json, "}", 2);
	strncpy(textJson, json, 1000);

}
