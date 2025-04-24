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


/*
 * Bunny Build LPC55 Sample
 *
 *
 * This code is design to run on the The LPC55S69 Xpresso board
 *
 * The EZH will toggle GPIO0-3
 *
 * It will also increment a test variable that is read in the IRQ handler.
 * The value is sent through EZH2ARM
 *
 */

uint32_t ezh_stack[16];

EZHPWM_Para ezh_parameters;

uint32_t ezh_debug_params[5];

__DATA(SRAMX) uint32_t  my_ezh_program[128];

uint32_t test_val = 0;

void Reserved46_IRQHandler()
{
	EZH_SetExternalFlag(1) ;

	test_val = LPC_EZH_ARCH_B0->EZHB_EZH2ARM;

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

    //Magic mux setting to use port 0.3 directly in EZH

    IOCON->PIO[0][3]             = PINFUNC_EZH | 2<<4 | 1<<8;

	EZH_SetExternalFlag(0) ;

	DisableIRQ(Reserved46_IRQn);
	CLOCK_EnableClock(kCLOCK_Ezhb);

    ezh_parameters.coprocessor_stack = (void *)ezh_stack;
	ezh_parameters.p_buffer =  (uint32_t *)ezh_debug_params;

	EZH_Init(&ezh_parameters);

	bunny_build(&my_ezh_program[0],
	    	    sizeof(my_ezh_program),
				ezh_app
				);



	EnableIRQ(Reserved46_IRQn);


    while (1)
    {

    }
}
