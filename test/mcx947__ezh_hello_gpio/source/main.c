
#include "pin_mux.h"
#include "peripherals.h"
#include "board.h"
#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"

#include "bunny_build.h"
#include "ezh_init.h"
#include "ezh_app.h"

#include "cr_section_macros.h"


uint32_t ezh_stack[16];
EZHPWM_Para ezh_parameters;
uint32_t ezh_debug_params[5];
__DATA(SRAMX) uint32_t  my_ezh_program[128];

uint32_t test_val;

void SMARTDMA_DriverIRQHandler()
{
	EZH_SetExternalFlag(1) ;

	test_val = LPC_EZH_ARCH_B0->EZHB_EZH2ARM;

	EZH_SetExternalFlag(0) ;
}

int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Hello World\r\n");

    CLOCK_EnableClock(kCLOCK_Port2);

    PORT_SetPinMux(PORT2, 4U, kPORT_MuxAlt7);   // counter b2

    RESET_PeripheralReset(kSMART_DMA_RST_SHIFT_RSTn);
    CLOCK_EnableClock(kCLOCK_Smartdma);

	bunny_build(&my_ezh_program[0],
	    	    sizeof(my_ezh_program),
				ezh_app
				);

	//EZH_SetExternalFlag(0) ;
	DisableIRQ(SMARTDMA_IRQn);            // EZH irq NUMBER 30

	ezh_parameters.coprocessor_stack = (void *)ezh_stack;
	ezh_parameters.p_buffer =  (uint32_t *)ezh_debug_params;

    EZH_Init(&ezh_parameters);		 //EZH initialization



    EZH_boot(my_ezh_program);	    //start EZH

	EnableIRQ(SMARTDMA_IRQn);          // EZH irq NUMBER 30


    while(1) {
    }
    return 0 ;
}
