#ifndef __JSON__
#define __JSON__

#include <stdint-gcc.h>

#include "../USB/usb_data.h"

void PackMSG(const char *stringToPack, uint32_t stringSize,	struct UsbDataReceived *usb_data_received);
void UnpackMSG(struct USBData *usb_data, char *textJson);

#endif
