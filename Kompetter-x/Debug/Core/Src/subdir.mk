################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/OledDisplayManager.c \
../Core/Src/SceneCreator.c \
../Core/Src/angleSensor.c \
../Core/Src/displayManager.c \
../Core/Src/fonts.c \
../Core/Src/keyboardScanner.c \
../Core/Src/main.c \
../Core/Src/queue.c \
../Core/Src/ssd1306.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/test.c \
../Core/Src/usbHidReport.c \
../Core/Src/utils.c 

OBJS += \
./Core/Src/OledDisplayManager.o \
./Core/Src/SceneCreator.o \
./Core/Src/angleSensor.o \
./Core/Src/displayManager.o \
./Core/Src/fonts.o \
./Core/Src/keyboardScanner.o \
./Core/Src/main.o \
./Core/Src/queue.o \
./Core/Src/ssd1306.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/test.o \
./Core/Src/usbHidReport.o \
./Core/Src/utils.o 

C_DEPS += \
./Core/Src/OledDisplayManager.d \
./Core/Src/SceneCreator.d \
./Core/Src/angleSensor.d \
./Core/Src/displayManager.d \
./Core/Src/fonts.d \
./Core/Src/keyboardScanner.d \
./Core/Src/main.d \
./Core/Src/queue.d \
./Core/Src/ssd1306.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/test.d \
./Core/Src/usbHidReport.d \
./Core/Src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/OledDisplayManager.cyclo ./Core/Src/OledDisplayManager.d ./Core/Src/OledDisplayManager.o ./Core/Src/OledDisplayManager.su ./Core/Src/SceneCreator.cyclo ./Core/Src/SceneCreator.d ./Core/Src/SceneCreator.o ./Core/Src/SceneCreator.su ./Core/Src/angleSensor.cyclo ./Core/Src/angleSensor.d ./Core/Src/angleSensor.o ./Core/Src/angleSensor.su ./Core/Src/displayManager.cyclo ./Core/Src/displayManager.d ./Core/Src/displayManager.o ./Core/Src/displayManager.su ./Core/Src/fonts.cyclo ./Core/Src/fonts.d ./Core/Src/fonts.o ./Core/Src/fonts.su ./Core/Src/keyboardScanner.cyclo ./Core/Src/keyboardScanner.d ./Core/Src/keyboardScanner.o ./Core/Src/keyboardScanner.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/queue.cyclo ./Core/Src/queue.d ./Core/Src/queue.o ./Core/Src/queue.su ./Core/Src/ssd1306.cyclo ./Core/Src/ssd1306.d ./Core/Src/ssd1306.o ./Core/Src/ssd1306.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/test.cyclo ./Core/Src/test.d ./Core/Src/test.o ./Core/Src/test.su ./Core/Src/usbHidReport.cyclo ./Core/Src/usbHidReport.d ./Core/Src/usbHidReport.o ./Core/Src/usbHidReport.su ./Core/Src/utils.cyclo ./Core/Src/utils.d ./Core/Src/utils.o ./Core/Src/utils.su

.PHONY: clean-Core-2f-Src

