#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "main.h"
#include "fonts.h"
#include "ssd1306.h"
#include <string.h>

void displayInit(void);
void displayUpdate(char* last_key, int16_t angle, int32_t smoothedAccumulator, uint8_t magnetPresent);

#endif // DISPLAY_MANAGER_H
