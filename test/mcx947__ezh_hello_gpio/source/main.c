
#include "pin_mux.h"
#include "peripherals.h"
#include "board.h"
#include "ezh_app.h"
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"

#define PCR_IBE_ibe1 0x01u /*!<@brief Input Buffer Enable: Enables */

uint32_t stack[1];
EZHPWM_Para para;
uint32_t EZH_DEBUGREG[5];

void SMARTDMA_DriverIRQHandler()
{
	EZH_SetExternalFlag(1) ;
	//PRINTF("GPI::%x \r\n",EZH_DEBUGREG[0]);
	//PRINTF("R5:%x \r\n",EZH_DEBUGREG[1]);
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

    PORT_SetPinMux(PORT2, 4U, kPORT_MuxAlt7);

    PORT2->PCR[4] = ((PORT2->PCR[4] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_IBE_MASK)))

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

	EZH_SetExternalFlag(0) ;


    RESET_PeripheralReset(kSMART_DMA_RST_SHIFT_RSTn);

    CLOCK_EnableClock(kCLOCK_Smartdma);


	DisableIRQ(SMARTDMA_IRQn);


    para.coprocessor_stack = (void *)stack;
	para.p_buffer =  (uint32_t *)EZH_DEBUGREG;

	EZH_Init(&para);					       //EZH initialisation
	EZH_Start();				  			   //start EZH

    EnableIRQ(SMARTDMA_IRQn);


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
