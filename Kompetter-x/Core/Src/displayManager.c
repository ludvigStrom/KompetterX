#include "displayManager.h"

void displayInit(void) {
    SSD1306_Init (); // initialize the display
    HAL_Delay(50);
    SSD1306_GotoXY (0,0);
    SSD1306_Puts ("Kompetter-X", &Font_11x18, 1);
    SSD1306_GotoXY (0, 20);
    SSD1306_Puts ("v.02", &Font_7x10, 1);
    SSD1306_UpdateScreen();
    HAL_Delay(1500);
    SSD1306_Clear();
    SSD1306_GotoXY(0, 30);
    SSD1306_Puts("Key: ", &Font_7x10, 1);
    SSD1306_GotoXY(0, 40);
    SSD1306_Puts("--  ", &Font_11x18, 1);
    SSD1306_GotoXY(40, 30);
    SSD1306_Puts("Magnet: ", &Font_7x10, 1);
    SSD1306_GotoXY(40, 40);
    SSD1306_Puts("--  ", &Font_11x18, 1);
    SSD1306_UpdateScreen();
}

void displayUpdate(char* last_key, int16_t angle, int32_t smoothedAccumulator, uint8_t magnetPresent) {
    // Handle magnet status
    if(magnetPresent == 1){
        SSD1306_GotoXY(40, 40);
        SSD1306_Puts("ok!  ", &Font_11x18, 1);

        // Convert the angle to a string
        char angle_str[5]; // Buffer to hold the string. Make sure it's large enough to hold all digits of the angle and the null-terminating character.

        // Convert to a string with leading spaces
        sprintf(angle_str, "%4u", angle);

        // Display the angle on the OLED display
        SSD1306_GotoXY (0,0);
        SSD1306_Puts("Angle: ", &Font_7x10, 1);
        SSD1306_GotoXY (0, 12);
        SSD1306_Puts(angle_str, &Font_11x18, 1);

        // ACCUMULATOR:
        // Convert to a string with leading spaces
        sprintf(angle_str, "%5d", smoothedAccumulator);

        // Display accumulator
        SSD1306_GotoXY (80,0);
        SSD1306_Puts("Acc: ", &Font_7x10, 1);
        SSD1306_GotoXY (60, 12);
        SSD1306_Puts(angle_str, &Font_7x10, 1);

    } else {
        SSD1306_GotoXY(40, 40);
        SSD1306_Puts("No :(", &Font_11x18, 1);
    }

    // Update the OLED display with the last key pressed
    SSD1306_GotoXY(0, 40);
    SSD1306_Puts(last_key, &Font_11x18, 1);

    // Update the OLED display
    SSD1306_UpdateScreen();
}
