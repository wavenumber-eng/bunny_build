#include <ezh_app.h>
#include "bunny_build.h"

#define EZH_OP_1      		 24         	/* GPIO24  us PIO2_4 on MCX */

void ezh_app (void)
{
    E_NOP;
    E_NOP;
    E_PER_READ(R6, ARM2EZH); //Peripheral Read
    E_LSR(R6, R6, 2);        //remove bit 0:1
    E_LSL(R6, R6, 2);        //bit 0:1 now = 0
    E_LDR(SP, R6, 0);        //load stack pointer para.coprocessor_stack
	E_LDR(R7, R6, 1);        //R7 -> para.p_buffer

	/* Set output high */
    E_BSET_IMM(GPO, GPO, EZH_OP_1);
    /* Set EZH_OP_1  as output , Direction bit = 1 */
    E_BSET_IMM(GPD, GPD, EZH_OP_1);

    /* set the heartbeat counter period to 250uS assuming 150MHz Clock*/
    E_HEART_RYTHM_IMM(37493);

 E_LABEL("toggle");

 	E_BSET_IMM(GPO, GPO, EZH_OP_1); //Set PIO0_3

	E_WAIT_FOR_BEAT();
	E_WAIT_FOR_BEAT();

    E_BCLR_IMM(GPO, GPO, EZH_OP_1); //Clear PIO0_3

    //Increment our counter and interrupt the ARM
    E_ADD_IMM(R0, R0, 1);
    E_PER_WRITE(R0, EZH2ARM);

    E_STR(R7,R0,0); //store the counter in the 1st parameter

    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();

    E_GOSUB("toggle");
}


