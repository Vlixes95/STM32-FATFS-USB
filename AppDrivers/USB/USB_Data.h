#ifndef __USB_DATA__
#define __USB_DATA__

#include "stdbool.h"

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
    char fileName[50];
    char content[1000];
};

struct USBDataReceived {
    bool isNewData;
    struct USBData usbData;
};

void setCommand ( struct USBDataReceived *usbData, char command );

char getCommand ( const struct USBDataReceived *usbData );

void setFileName ( const struct USBDataReceived *usbData, const char *name );

char *getFileName ( const struct USBDataReceived *usbData );

void setContent ( const struct USBDataReceived *usbData, const char *content );

char *getContent ( const struct USBDataReceived *usbData );

bool IsNewData ( const struct USBDataReceived *usbData );

void setNewData ( struct USBDataReceived *usbData, bool data );

#endif