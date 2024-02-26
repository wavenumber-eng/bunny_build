################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_flexcomm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_power.c \
../drivers/fsl_reset.c \
../drivers/fsl_usart.c 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_flexcomm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_power.d \
./drivers/fsl_reset.d \
./drivers/fsl_usart.d 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_flexcomm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_power.o \
./drivers/fsl_reset.o \
./drivers/fsl_usart.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DARM_MATH_CM33 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\drivers" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\device" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\CMSIS" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\uart" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\serial_manager" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\lists" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\utilities" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\board" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\source" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\drivers" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\device" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\CMSIS" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\startup" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\utilities" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\serial_manager" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\lists" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\uart" -O0 -fno-common -g3 -gdwarf-4 -Wall -mcpu=cortex-m33  -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_flexcomm.d ./drivers/fsl_flexcomm.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_power.d ./drivers/fsl_power.o ./drivers/fsl_reset.d ./drivers/fsl_reset.o ./drivers/fsl_usart.d ./drivers/fsl_usart.o

.PHONY: clean-drivers

