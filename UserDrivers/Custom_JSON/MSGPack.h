#ifndef __JSON__
#define __JSON__

#include <stdint-gcc.h>
#include "USB_Data.h"

void PackMSG ( const char *stringToPack, uint32_t stringSize, struct USBDataReceived *usbDataReceived );

void UnpackMSG ( struct USBData *usbData, char *textJson );

#endif
