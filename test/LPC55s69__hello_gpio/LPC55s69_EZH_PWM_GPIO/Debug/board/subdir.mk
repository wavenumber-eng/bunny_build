################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/pin_mux.c 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/pin_mux.d 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/pin_mux.o 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c board/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DARM_MATH_CM33 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\drivers" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\device" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\CMSIS" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\uart" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\serial_manager" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\lists" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\utilities" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\board" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\source" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\drivers" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\device" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\CMSIS" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\startup" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\utilities" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\serial_manager" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\lists" -I"C:\ELI\ezh\LPC55\LPC55s69_hello_gpio\LPC55s69_EZH_PWM_GPIO\component\uart" -O0 -fno-common -g3 -gdwarf-4 -Wall -mcpu=cortex-m33  -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-board

clean-board:
	-$(RM) ./board/board.d ./board/board.o ./board/clock_config.d ./board/clock_config.o ./board/pin_mux.d ./board/pin_mux.o

.PHONY: clean-board
