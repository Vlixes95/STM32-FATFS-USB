#include "USB_Data.h"
#include "string.h"

char getCommand ( const struct USBDataReceived *usbData ) {
    return usbData->usbData.command;
}

void setCommand ( struct USBDataReceived *usbData, char command ) {
    usbData->usbData.command = command;
}

char *getFileName ( const struct USBDataReceived *usbData ) { return ( char * ) usbData->usbData.fileName; }

void setFileName ( const struct USBDataReceived *usbData, const char *name ) {
    strcpy(( char * ) usbData->usbData.fileName, name );
}

char *getContent ( const struct USBDataReceived *usbData ) { return ( char * ) usbData->usbData.content; }

void setContent ( const struct USBDataReceived *usbData, const char *content ) {
    strcpy(( char * ) usbData->usbData.content, content );
}

bool IsNewData ( const struct USBDataReceived *usbData ) { return usbData->isNewData; }

void setNewData ( struct USBDataReceived *usbData, bool newData ) { usbData->isNewData = newData; }
