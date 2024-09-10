// usb_hid.c

#include "usbHidReport.h"

static KeyboardHID keyboardhid;
static uint8_t hid_report[NUM_KEYS];
static uint8_t hid_report_prev[NUM_KEYS];
static MouseHID mousehid;
static USBD_HandleTypeDef *usbDeviceHandle;

void usbHidInit(USBD_HandleTypeDef *handle) {
    usbDeviceHandle = handle;
    memset(hid_report, 0, NUM_KEYS);
    memset(hid_report_prev, 0, NUM_KEYS);

    memset(&keyboardhid, 0, sizeof(KeyboardHID));
    keyboardhid.REPORT_ID = 0x01;

    memset(&mousehid, 0, sizeof(MouseHID));
    mousehid.REPORT_ID = 0x02;
}

void usbHidAddKey(uint8_t keycode) {
    for (int i = 0; i < NUM_KEYS; i++) {
        if (hid_report[i] == 0) {
            hid_report[i] = keycode;
            break;
        }
    }
}

void usbHidRemoveKey(uint8_t keycode) {
    for (int i = 0; i < NUM_KEYS; i++) {
        if (hid_report[i] == keycode) {
            hid_report[i] = 0;
            break;
        }
    }
}

void usbHidHandleMacro(USBD_HandleTypeDef *usbDeviceHandle, uint8_t* macro, uint8_t macro_length) {
    // Clean out key report
    memset(hid_report, 0, NUM_KEYS);

    // Send char[] of macro to usbHidAddkey
    for (int i = 0; i < macro_length; i++) {
        usbHidAddKey(macro[i]);
    }

    // Send key report
    usbHidSendKeyboardReport();

    // Clean out key report
    memset(hid_report, 0, NUM_KEYS);

    // Send empty key report
    usbHidSendKeyboardReport();
}

void usbHidSendKeyboardReport() {
	// Copy keycodes from hid_report to keyboardhid
	keyboardhid.KEYCODE1 = hid_report[0];
	keyboardhid.KEYCODE2 = hid_report[1];
	keyboardhid.KEYCODE3 = hid_report[2];
	keyboardhid.KEYCODE4 = hid_report[3];
	keyboardhid.KEYCODE5 = hid_report[4];
	keyboardhid.KEYCODE6 = hid_report[5];

	//send current key report
	USBD_HID_SendReport(usbDeviceHandle, (uint8_t*)&keyboardhid, sizeof(keyboardhid));
	//save it to previous report
	memcpy(hid_report_prev, hid_report, NUM_KEYS);
}

uint8_t usbHidkeyReportChanged(){
	uint8_t report_changed = 0;

	for (int i = 0; i < NUM_KEYS; i++) {
		if (hid_report[i] != hid_report_prev[i]) {
			report_changed = 1;
			break;
		}
	}
	return report_changed;
}

void usbHidUpdateMouseReport(int8_t x, int8_t y, int8_t wheel, uint8_t buttons) {
    mousehid.X = x;
    mousehid.Y = y;
    mousehid.WHEEL = wheel;
    mousehid.BUTTONS = buttons;
}

void usbHidSendMouseReport(void) {
    USBD_HID_SendReport(usbDeviceHandle, (uint8_t*)&mousehid, sizeof(mousehid));
}
