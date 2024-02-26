################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_assert.c \
../utilities/fsl_debug_console.c \
../utilities/fsl_str.c 

C_DEPS += \
./utilities/fsl_assert.d \
./utilities/fsl_debug_console.d \
./utilities/fsl_str.d 

OBJS += \
./utilities/fsl_assert.o \
./utilities/fsl_debug_console.o \
./utilities/fsl_str.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DARM_MATH_CM33 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\drivers" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\device" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\CMSIS" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\uart" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\serial_manager" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\lists" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\utilities" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\board" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\source" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\drivers" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\device" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\CMSIS" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\startup" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\utilities" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\serial_manager" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\lists" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\uart" -O0 -fno-common -g3 -gdwarf-4 -Wall -mcpu=cortex-m33  -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities

clean-utilities:
	-$(RM) ./utilities/fsl_assert.d ./utilities/fsl_assert.o ./utilities/fsl_debug_console.d ./utilities/fsl_debug_console.o ./utilities/fsl_str.d ./utilities/fsl_str.o

.PHONY: clean-utilities

