#ifndef __USB_DATA__
#define __USB_DATA__

#include "stdbool.h"

#define FILE_NAME_MAX_LENGHT 50
#define CONTENT_MAX_LENGHT 1000

enum COMMANDS {
	WRITE = 'w',
	READ = 'r',
	UPDATE = 'u',
	DELETE = 'd',
	PRINT = 'p',
	C_ERROR = 'e',
};

// TODO: struct with value and size?

/* TODO: Use un union struct to add error message and error source
 * if command: e
 *    errorSource -> previous command
 */

struct USBData {
	char command;
	char fileName[FILE_NAME_MAX_LENGHT];
	char content[CONTENT_MAX_LENGHT];
};

struct UsbDataReceived {
	bool is_new_data;
	struct USBData usb_data;
};

void setCommand(struct UsbDataReceived *usb_data, char command);

char getCommand(const struct UsbDataReceived *usb_data);

void setFileName(const struct UsbDataReceived *usb_data, const char *name);

char* getFileName(const struct UsbDataReceived *usb_data);

void setContent(const struct UsbDataReceived *usb_data, const char *content);

char* getContent(const struct UsbDataReceived *usb_data);

bool is_new_data(const struct UsbDataReceived *usb_data);

void setNewData(struct UsbDataReceived *usb_data, bool data);

#endif
