#include "angleSensor.h"
#include "main.h" // Include this if necessary for GPIO functions
#include "utils.h"
#include <stdlib.h>

#define ALPHA_SMOOTHING 0.2

int16_t currentEncoderVal = 0;
int16_t lastEncoderVal = 0;
int32_t encoderAccumulator = 0;
int32_t smoothedAccumulator = 0;
int32_t lastSmoothedAccumulator = 0;

void angleSensorInit(I2C_HandleTypeDef *hi2c)
{
	lastEncoderVal = AS5600_ReadAngle(hi2c);
}

uint16_t AS5600_ReadAngle(I2C_HandleTypeDef *hi2c)
{
    uint8_t buffer[2];
    uint16_t angle;

    // Read the angle from the AS5600 chip
    HAL_I2C_Mem_Read(hi2c, AS5600_ADDRESS<<1, 0x0E, I2C_MEMADD_SIZE_8BIT, buffer, 2, 100);

    // Combine the two bytes to get the angle
    angle = (buffer[0] << 8) | buffer[1];

    return angle;
}

uint8_t AS5600_ReadStatus(I2C_HandleTypeDef *hi2c)
{
    uint8_t status;

    // Read the status from the AS5600 chip
    HAL_I2C_Mem_Read(hi2c, AS5600_ADDRESS<<1, 0x0B, I2C_MEMADD_SIZE_8BIT, &status, 1, 100);

    return status;
}

uint8_t AS5600_IsMagnetPresent(I2C_HandleTypeDef *hi2c)
{
    uint8_t status = AS5600_ReadStatus(hi2c);

    // Check if the magnet is too high or too low
    if((status & 0x08) || (status & 0x10)) {
        // Magnet is not present or not properly placed
        return 0; // returning 0 for false
    } else {
        // Magnet is present and properly placed
        return 1; // returning 1 for true
    }
}

int32_t encoderValueFunction(int16_t currentValue, int16_t previousValue, int32_t accumulator) {
	int16_t difference = (int16_t)currentValue - (int16_t)previousValue;

	// Handle wraparound from 0 to 4095 and from 4095 to 0
	if (abs(difference) > 2048) {
		if (difference > 0) {
			difference -= 4096;
		} else {
			difference += 4096;
		}
	}

	if (abs(difference) > 10) {
		accumulator += difference;
	}

	// Exponential smoothing
	float alpha = ALPHA_SMOOTHING; // Smoothing factor, adjust as needed
	smoothedAccumulator = alpha * accumulator + (1 - alpha) * smoothedAccumulator;

	// Limit smoothedAccumulator to the range -127 to 127
	smoothedAccumulator = max(-127, min(127, smoothedAccumulator));

	return smoothedAccumulator;
}

void angleSensorScrollScan(I2C_HandleTypeDef *hi2c){
	//ANGLE SENSOR
	uint16_t angle = AS5600_ReadAngle(hi2c);

	smoothedAccumulator = encoderValueFunction(angle, lastEncoderVal, encoderAccumulator);
	lastEncoderVal = angle; // Update lastEncoderVal after calling encoderValueFunction

	//Handle magnet status
	if( AS5600_IsMagnetPresent(hi2c) == 1){

		SSD1306_GotoXY(40, 40);
		SSD1306_Puts("ok!  ", &Font_11x18, 1);

		//Convert the angle to a string
		char angle_str[5]; // Buffer to hold the string. Make sure it's large enough to hold all digits of the angle and the null-terminating character.

		//Convert to a string with leading spaces
		sprintf(angle_str, "%4u", angle);

		// Display the angle on the OLED display
		SSD1306_GotoXY (0,0);
		SSD1306_Puts("Angle: ", &Font_7x10, 1);
		SSD1306_GotoXY (0, 12);
		SSD1306_Puts(angle_str, &Font_11x18, 1);


		//ACCUMULATOR:
		//Convert to a string with leading spaces
		sprintf(angle_str, "%5d", (int8_t)smoothedAccumulator);

		//display accumulator
		SSD1306_GotoXY (80,0);
		SSD1306_Puts("Acc: ", &Font_7x10, 1);
		SSD1306_GotoXY (60, 12);
		SSD1306_Puts(angle_str, &Font_7x10, 1);

	} else {
		SSD1306_GotoXY(40, 40);
		SSD1306_Puts("No :(", &Font_11x18, 1);
	}
}
