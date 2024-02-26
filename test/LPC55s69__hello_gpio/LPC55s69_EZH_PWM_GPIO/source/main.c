/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <ezh_app.h>
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"



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
	PRINTF("GPI::%x \r\n",EZH_DEBUGREG[0]);
	PRINTF("R5:%x \r\n",EZH_DEBUGREG[1]);
	EZH_SetExternalFlag(0) ;
};
 



/*!
 * @brief Main function
 */
int main(void)
{
    /* Init board hardware. */
    /* attach main clock divide to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    BOARD_InitPins();
    BOARD_BootClockPLL150M();
    BOARD_InitDebugConsole();

	PRINTF("EZH 1KH GPIO Toggle Demo demo.\r\n");
	
	EZH_SetExternalFlag(0) ;

	 DisableIRQ(Reserved46_IRQn);            // EZH irq NUMBER 30
	 CLOCK_EnableClock( kCLOCK_Ezhb);        // enable EZH clock
		
     para.coprocessor_stack = (void *)stack;
	 para.p_buffer =  (uint32_t *)EZH_DEBUGREG;
		
	EZH_Init(&para);					       //EZH initialisation
	EZH_Start();				  			   //start EZH
    EnableIRQ(Reserved46_IRQn);                //EZH irq number 30
		
    while (1)
    {
    }
}
