#include "../MSGPack/MSGPack.h"

#include "../../AppDrivers/SDCard/User_SD_Card.h"

void PackMSG(const char *stringToPack, uint32_t stringSize, struct UsbDataReceived *usb_data_received) {
	DWORD i = 0;
	bool init = false;
	uint8_t size = 0;
	uint8_t numOfFields = 0;

	memset(usb_data_received->usb_data.fileName, '\0', 50);
	memset(usb_data_received->usb_data.content, '\0', 1000);

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
	char json[1000];
	char tmp[1000];
	memset(json, '\0', 1000);
	strcat(json, "{");
	uint8_t numOfFields = 0;
	uint8_t size = 0;
	for (int i = 0; i < 3; ++i) {

		if (numOfFields == 0) {
			tmp[0] = usb_data->command;
			tmp[1] = '\0';
		} else if (numOfFields == 1) {
			strcpy(tmp, usb_data->fileName);
		} else if (numOfFields == 2) {
			strcpy(tmp, usb_data->content);
		}
		++numOfFields;

		for (size = 0; tmp[size] != '\0'; ++size)
			;

		strcat(json, "L");
		char snum[10];
		itoa(size, snum, 10);
		strcat(json, snum);
		strcat(json, "C");
		strcat(json, tmp);
	}
	strcat(json, "}");
	strcpy(textJson, json);
}
