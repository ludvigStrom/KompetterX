#ifndef USB_HID_REPORT_H
#define USB_HID_REPORT_H

#include "usbd_hid.h"

#define NUM_KEYS 16

extern USBD_HandleTypeDef hUsbDeviceFS;

typedef struct
{
    uint8_t REPORT_ID;
    uint8_t MODIFIER;
    uint8_t RESERVED;
    uint8_t KEYCODE1;
    uint8_t KEYCODE2;
    uint8_t KEYCODE3;
    uint8_t KEYCODE4;
    uint8_t KEYCODE5;
    uint8_t KEYCODE6;
} KeyboardHID;

typedef struct {
    uint8_t REPORT_ID;    		// REPORT_ID
    uint8_t BUTTONS;     		// Button states - bitmapped
    int8_t  X;           		// X-axis movement
    int8_t  Y;           		// Y-axis movement
    int8_t  WHEEL;       		// Wheel movement
    uint8_t VENDOR_DEFINED[2];  // Vendor-defined usage
} MouseHID;

void usbHidInit(USBD_HandleTypeDef *usbDeviceHandle);
void usbHidAddKey(uint8_t keycode);
void usbHidRemoveKey(uint8_t keycode);
void usbHidSendKeyboardReport(void);
void usbHidHandleMacro(USBD_HandleTypeDef *usbDeviceHandle, uint8_t* macro, uint8_t macro_length);
uint8_t usbHidkeyReportChanged(void);
void usbHidUpdateMouseReport(int8_t x, int8_t y, int8_t wheel, uint8_t buttons);
void usbHidSendMouseReport(void);

#endif
