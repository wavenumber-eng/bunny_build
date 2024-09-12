################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/system_MCXN947_cm33_core0.c 

C_DEPS += \
./device/system_MCXN947_cm33_core0.d 

OBJS += \
./device/system_MCXN947_cm33_core0.o 


# Each subdirectory must supply rules for building sources it contributes
device/%.o: ../device/%.c device/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MCXN947VDF -DCPU_MCXN947VDF_cm33 -DCPU_MCXN947VDF_cm33_core0 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\ELI\projects\wavenumber\bunny_build\test\mcx947__ezh_hello_gpio\board" -I"C:\ELI\projects\wavenumber\bunny_build\test\mcx947__ezh_hello_gpio\source" -I"C:\ELI\projects\wavenumber\bunny_build\test\mcx947__ezh_hello_gpio\drivers" -I"C:\ELI\projects\wavenumber\bunny_build\test\mcx947__ezh_hello_gpio\device" -I"C:\ELI\projects\wavenumber\bunny_build\test\mcx947__ezh_hello_gpio\utilities" -I"C:\ELI\projects\wavenumber\bunny_build\test\mcx947__ezh_hello_gpio\component\uart" -I"C:\ELI\projects\wavenumber\bunny_build\test\mcx947__ezh_hello_gpio\component\serial_manager" -I"C:\ELI\projects\wavenumber\bunny_build\test\mcx947__ezh_hello_gpio\component\lists" -I"C:\ELI\projects\wavenumber\bunny_build\test\mcx947__ezh_hello_gpio\CMSIS" -I"C:\ELI\projects\wavenumber\bunny_build\test\mcx947__ezh_hello_gpio\startup" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-device

clean-device:
	-$(RM) ./device/system_MCXN947_cm33_core0.d ./device/system_MCXN947_cm33_core0.o

.PHONY: clean-device

