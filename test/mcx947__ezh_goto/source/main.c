
#include "pin_mux.h"
#include "peripherals.h"
#include "board.h"
#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"
#include "ezh_app.h"


uint32_t stack[1];
EZHPWM_Para para;
uint32_t EZH_DEBUGREG[5];



void SMARTDMA_DriverIRQHandler()
{
	EZH_SetExternalFlag(1) ;
	PRINTF("R5:%x \r\n",EZH_DEBUGREG[0]);
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

    PORT_SetPinMux(PORT2, 2U, kPORT_MuxAlt7);   // counter b0
    PORT_SetPinMux(PORT2, 3U, kPORT_MuxAlt7);   // counter b1
    PORT_SetPinMux(PORT2, 4U, kPORT_MuxAlt7);   // counter b2
    PORT_SetPinMux(PORT2, 5U, kPORT_MuxAlt7);   // counter b3

	EZH_SetExternalFlag(0) ;

    RESET_PeripheralReset(kSMART_DMA_RST_SHIFT_RSTn);
    CLOCK_EnableClock(kCLOCK_Smartdma);


	//DisableIRQ(SMARTDMA_IRQn);            // EZH irq NUMBER 30
	EnableIRQ(SMARTDMA_IRQn);            // EZH irq NUMBER 30

    para.coprocessor_stack = (void *)stack;
	para.p_buffer =  (uint32_t *)EZH_DEBUGREG;

    EZH_Init(&para);					       //EZH initialisation
	EZH_Start();				  			   //start EZH


    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
