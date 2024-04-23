#include "../../AppDrivers/USB/USB_Data.h"
#include "string.h"

// TODO: strcpy to strcpy_s, strncpy to strncpy_s

char getCommand(const struct UsbDataReceived *usb_data) {
	return usb_data->usb_data.command;
}

void setCommand(struct UsbDataReceived *usb_data, char command) {
	usb_data->usb_data.command = command;
}

char* getFileName(const struct UsbDataReceived *usb_data) {
	return (char*) usb_data->usb_data.fileName;
}

void setFileName(const struct UsbDataReceived *usb_data, const char *name) {
	strcpy((char*) usb_data->usb_data.fileName, name);
}

char* getContent(const struct UsbDataReceived *usb_data) {
	return (char*) usb_data->usb_data.content;
}

void setContent(const struct UsbDataReceived *usb_data, const char *content) {
	strcpy((char*) usb_data->usb_data.content, content);
}

bool isNewData(const struct UsbDataReceived *usb_data) {
	return usb_data->is_new_data;
}

void setNewData(struct UsbDataReceived *usb_data, bool newData) {
	usb_data->is_new_data = newData;
}
