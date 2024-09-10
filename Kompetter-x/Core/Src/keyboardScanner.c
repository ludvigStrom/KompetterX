#include "keyboardScanner.h"
#include "main.h" // Include this if necessary for GPIO functions
#include "ImprovedKeylayouts.h"
#include <stdio.h>
#include "usbHidReport.h"


#define DEBOUNCE_DELAY 10 // Debounce delay in milliseconds

uint8_t keycode_map[NUM_ROWS][NUM_COLS] = {
    {KEY_1, KEY_2, KEY_3, KEY_4}, // HID keycodes for '1', '2', '3', '4'
    {KEY_5, KEY_6, KEY_7, KEY_8}, // HID keycodes for '5', '6', '7', '8'
    {KEY_9, KEY_A, KEY_B, KEY_C}, // HID keycodes for '9', 'A', 'B', 'C'
    {KEY_D, KEY_E, KEY_F, KEY_G}  // HID keycodes for 'D', 'E', 'F', 'G'
};

uint32_t last_key_time[NUM_ROWS][NUM_COLS] = {0};
uint8_t hid_report[NUM_KEYS] = {0};
uint8_t hid_report_prev[NUM_KEYS] = {0};
char last_key[3] = {0};
enum KeyState key_state[NUM_ROWS][NUM_COLS];

void keyboardScannerInit(void)
{
  // Initialize each state to IDLE
  for(int i = 0; i < NUM_ROWS; i++) {
    for(int j = 0; j < NUM_COLS; j++) {
      key_state[i][j] = IDLE;
    }
  }
}

void keyboardScan(void)
{
    //Keyboard Scan!
    for(int i = 0; i < NUM_ROWS; i++) {
        uint32_t current_tick = HAL_GetTick();
        HAL_GPIO_WritePin(row_ports[i], row_pins[i], GPIO_PIN_SET);
        HAL_Delay(1); // delay after setting row high

        for(int j = 0; j < NUM_COLS; j++) {
            uint8_t is_pressed = HAL_GPIO_ReadPin(col_ports[j], col_pins[j]) == GPIO_PIN_SET;

            if (is_pressed && key_state[i][j] == IDLE) {
                // Key has been pressed from an idle state
                usbHidAddKey(keycode_map[i][j]); // Add the key to the HID report
                key_state[i][j] = PRESSED;
                last_key_time[i][j] = current_tick;

                sprintf(last_key, "%d%d", i+1, j+1);  // Save the last key pressed

            } else if (!is_pressed && key_state[i][j] == PRESSED && current_tick - last_key_time[i][j] > DEBOUNCE_DELAY) {
                // Key has been released
                usbHidRemoveKey(keycode_map[i][j]); // Remove the key from the HID report
                key_state[i][j] = IDLE;
            }
        }

        HAL_GPIO_WritePin(row_ports[i], row_pins[i], GPIO_PIN_RESET);
        HAL_Delay(1); // delay after setting row low
    }
}
