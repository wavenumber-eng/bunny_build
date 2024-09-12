/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_gpio.h"

#include "fsl_power.h"
#include "cr_section_macros.h"

#include "bunny_build.h"
#include "ezh_init.h"
#include "ezh_app.h"


uint32_t ezh_stack[16];
EZHPWM_Para ezh_parameters;
uint32_t ezh_debug_params[5];
__DATA(SRAMX) uint32_t  my_ezh_program[128];

uint32_t test_val = 0;

void Reserved46_IRQHandler()
{
	EZH_SetExternalFlag(1) ;

	test_val = LPC_EZH_ARCH_B0->EZHB_EZH2ARM;
	//PRINTF("GPI::%x \r\n",EZH_DEBUGREG[0]);
	//PRINTF("R5:%x \r\n",EZH_DEBUGREG[1]);
	EZH_SetExternalFlag(0) ;
};

int main(void)
{
    char ch;

    /* Init board hardware. */
    /* set BOD VBAT level to 1.65V */
    POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
    /* attach main clock divide to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

#if !defined(DONT_ENABLE_FLASH_PREFETCH)
    /* enable flash prefetch for better performance */
    SYSCON->FMCCR |= SYSCON_FMCCR_PREFEN_MASK;
#endif



    //Magic mux setting to to use port 0.3 directly in EZH
    IOCON->PIO[0][3]             = PINFUNC_EZH | 2<<4 | 1<<8;

	EZH_SetExternalFlag(0) ;

	DisableIRQ(Reserved46_IRQn);            // EZH irq NUMBER 30

	CLOCK_EnableClock( kCLOCK_Ezhb);        // enable EZH clock

    ezh_parameters.coprocessor_stack = (void *)ezh_stack;
	ezh_parameters.p_buffer =  (uint32_t *)ezh_debug_params;

	EZH_Init(&ezh_parameters);					       //EZH initialisation

	bunny_build(&my_ezh_program[0],
	    	    sizeof(my_ezh_program),
				ezh_app
				);

	EZH_boot(my_ezh_program);				     //start EZH

	EnableIRQ(Reserved46_IRQn);                //EZH irq number 30


    PRINTF("hello world.\r\n");

    while (1)
    {

    }
}
