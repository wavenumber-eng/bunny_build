/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <ezh_app.h>
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "bunny_build.h"
#include "fsl_gpio.h"

#include "fsl_power.h"
#include "cr_section_macros.h"

#define PINFUNC_EZH        15

/*******************************************************************************
 * Definitions
 ******************************************************************************/
uint32_t stack[1];
EZHPWM_Para para;
uint32_t EZH_DEBUGREG[5];


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/**
 * @brief	 EZH block initialisation
 * @return	Nothing
 */
extern void EZH_Init(void *pPara);
/**
 * @brief	 EZH application start
 * @return	Nothing
 */
extern void EZH_Start(void);

/*******************************************************************************
 * Code
 ******************************************************************************/
void Reserved46_IRQHandler(){
	EZH_SetExternalFlag(1) ;
	//PRINTF("GPI::%x \r\n",EZH_DEBUGREG[0]);
	//PRINTF("R5:%x \r\n",EZH_DEBUGREG[1]);
	EZH_SetExternalFlag(0) ;
};


__DATA(SRAMX) uint32_t  my_ezh_program[1024];


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

    /* Enables the clock for the I/O controller.: Enable Clock. */
    CLOCK_EnableClock(kCLOCK_Iocon);
    IOCON->PIO[0][3]             = PINFUNC_EZH | 2<<4 | 1<<8;
   // IOCON->PIO[0][2]             = PINFUNC_EZH | 2<<4 | 1<<8;
	EZH_SetExternalFlag(0) ;

	 DisableIRQ(Reserved46_IRQn);            // EZH irq NUMBER 30
	 CLOCK_EnableClock( kCLOCK_Ezhb);        // enable EZH clock

     para.coprocessor_stack = (void *)stack;
	 para.p_buffer =  (uint32_t *)EZH_DEBUGREG;

	EZH_Init(&para);					       //EZH initialisation

	bunny_build(&my_ezh_program[0],
	    	    sizeof(my_ezh_program),
				ezh_app
				);

	EZH_boot(my_ezh_program);				     //start EZH
    EnableIRQ(Reserved46_IRQn);                //EZH irq number 30


    PRINTF("hello world.\r\n");

    while (1)
    {
    	//GPIO->NOT[0] = 1<<3;
        //ch = GETCHAR();	GPIO->NOT[0] = 1<<3;z
       // PUTCHAR(ch);
    }
}
