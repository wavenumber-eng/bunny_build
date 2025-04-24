
#include <stdbool.h>
#include <stdint.h>

#include "bunny_build.h"



#define EZH_CTR_b0      		 22         	/* GPIO22  us PIO2_2 on MCX */
#define EZH_CTR_b1      		 23         	/* GPIO23  us PIO2_3 on MCX */
#define EZH_CTR_b2      		 24         	/* GPIO24  us PIO2_4 on MCX */
#define EZH_CTR_b3      		 25         	/* GPIO25  us PIO2_5 on MCX */
#define EZH_FRQ_SEL              27             /* GPIO27  us PIO2_7 on MCX */



/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

// This application tests GOTOL, GOTOL and GOTO_REG instructions
// Counter up from 0 to 0xF
void ezh_4_bit_counter_up_app (void){
    E_NOP;
    E_PER_READ(R6, ARM2EZH); //Peripheral Read
    E_LSR(R6, R6, 2);        //remove bit 0:1
    E_LSL(R6, R6, 2);        //bit 0:1 now = 0
    E_LDR(SP, R6, 0);        //load stack pointer para.coprocessor_stack
	E_LDR(R7, R6, 1);        //R7 -> para.p_buffer

E_LABEL("INIT_CU");
	E_BSET_IMM(GPD, GPD, EZH_CTR_b0);   //counter pins direction
	E_BSET_IMM(GPD, GPD, EZH_CTR_b1);
    E_BSET_IMM(GPD, GPD, EZH_CTR_b2);
	E_BSET_IMM(GPD, GPD, EZH_CTR_b3);
    E_BCLR_IMM(GPD, GPD, EZH_FRQ_SEL);

    E_LOAD_IMM(R0, 0);  // R0 has the counter value

E_LABEL("LOOP_CU");
    E_GOTOL("COUNTER_INC_LOOP");
    E_GOTOL("UPDATE_OUTPUT");
    E_WAIT_FOR_BEAT();
    E_GOTO("LOOP_CU");


E_LABEL("COUNTER_INC_LOOP");
    E_ADD_IMM(R0, R0, 1);               // R0 = R0 + 1
    E_AND_IMM(R0, R0, 0XF);             // R0 = R0 % 0b1111
    E_GOTO_REG(RA);

E_LABEL("UPDATE_OUTPUT");
    E_LSL(GPO, R0, 22);                 // Set output bits of counter
    E_BTST_IMMS(R1, GPI, EZH_FRQ_SEL);  //if(FRQ_SEL == 1) ctr_freq = 8000, else ctr_freq = 4000
    E_COND_ADD(PO, PC, PC, 4);
    E_HEART_RYTHM_IMM(37500);           // ctr_freq = 8000
    E_HEART_RYTHM_IMM(18750);           // ctr_freq = 4000
    E_GOTO_REG(RA);
}

// This application tests E_GOTO(), E_GOTOL(), E_COND_GOTO_REG() and E_COND_GOTO
// Counter down from 0xF to 1, when the counter restarts it shows 0xf during 3 counter periods.
void ezh_4_bit_counter_down_app (void){
    E_NOP;
    E_PER_READ(R6, ARM2EZH);            //Peripheral Read
    E_LSR(R6, R6, 2);                   //remove bit 0:1
    E_LSL(R6, R6, 2);                   //bit 0:1 now = 0
    E_LDR(SP, R6, 0);                   //load stack pointer para.coprocessor_stack
	E_LDR(R7, R6, 1);                   //R7 -> para.p_buffer

	E_BSET_IMM(GPD, GPD, EZH_CTR_b0);   //counter pins direction
	E_BSET_IMM(GPD, GPD, EZH_CTR_b1);
    E_BSET_IMM(GPD, GPD, EZH_CTR_b2);
	E_BSET_IMM(GPD, GPD, EZH_CTR_b3);
    E_HEART_RYTHM_IMM(37500);           // ctr_freq = 8000

E_LABEL("INIT_CD");
    E_LOAD_IMM(R0, 0XF);                // R0 has the counter value
    E_LSL(GPO, R0, 22);                 // Set output bits of counter
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();

E_LABEL("LOOP_CD");
    E_GOTOL("COUNTER_DEC_LOOP");
    E_WAIT_FOR_BEAT();
    E_GOTO("LOOP_CD");

E_LABEL("COUNTER_DEC_LOOP");
    E_SUB_IMMS(R0, R0, 1);              // R0 = R0 - 1
    E_COND_GOTO(ZE, "INIT_CD");         // if r0 == 0, reinit counter
    E_LSL(GPO, R0, 22);                 // else show counter value

    E_ADD_IMMS(R0, R0, 0);              // to rise flags
    E_COND_GOTO_REG(PO, RA);            // Just for testing purpose
}


// This application test E_GOTO_REGL
// Calculates the value of 2*N1 + 1, and stores it on the shared buffer
#define N1  2
void ezh_fun1_app(){
    E_NOP;
    E_PER_READ(R6, ARM2EZH);            // Peripheral Read
    E_LSR(R6, R6, 2);                   // remove bit 0:1
    E_LSL(R6, R6, 2);                   // bit 0:1 now = 0
    E_LDR(SP, R6, 0);                   // load stack pointer para.coprocessor_stack
	E_LDR(R7, R6, 1);                   // R7 -> para.p_buffer

    E_LOAD_IMM(R0, N1);                 // R0 has the result value

    E_ADD_IMM(R5, PC, 8);
    E_GOTO_REGL(R5);
    E_ADD_IMM(R0, R0, 1);               // R0 = R0 + 1 
    E_GOTO("RESULT");                   

E_LABEL("X2");                         
    E_LSL(R0, R0, 1);                   // R0 = R0 << 1 
    E_GOTO_REG(RA);

E_LABEL("RESULT");
    E_STR(R7, R0, 0);                   // Store output
    E_INT_TRIGGER(1);

}


// This application test E_COND_GOTOL
// If the input number is odd write the word "odd" in the shared buffer, else write the word "even"
#define N2  7
void ezh_even_or_odd_app(){
    E_NOP;
    E_PER_READ(R6, ARM2EZH);            // Peripheral Read
    E_LSR(R6, R6, 2);                   // remove bit 0:1
    E_LSL(R6, R6, 2);                   // bit 0:1 now = 0
    E_LDR(SP, R6, 0);                   // load stack pointer para.coprocessor_stack
	E_LDR(R7, R6, 1);                   // R7 -> para.p_buffer

    E_LOAD_IMM(R0, N2);                 // R0 has the result value

    E_BTST_IMMS(R1, R0, 0);             // bit0 determines if the number is even or odd
    E_COND_GOTOL(PO, "ODD");
    E_COND_GOTOL(ZE, "EVEN");
    E_INT_TRIGGER(1);                   // Trigger interrupt
    E_GOTO("END");

E_LABEL("ODD");                         // Write odd in the shared buffer
    E_LOAD_IMM(R2, 'O');
    E_STR(R7, R2, 0);             
    E_LOAD_IMM(R2, 'D');
    E_STR(R7, R2, 1);   
    E_LOAD_IMM(R2, 'D');
    E_STR(R7, R2, 2);     
    E_GOTO_REG(RA);

E_LABEL("EVEN");                        // Write even in the shared buffer
    E_LOAD_IMM(R2, 'E');
    E_STR(R7, R2, 0);             
    E_LOAD_IMM(R2, 'V');
    E_STR(R7, R2, 1);   
    E_LOAD_IMM(R2, 'E');
    E_STR(R7, R2, 2);   
    E_LOAD_IMM(R2, 'N');
    E_STR(R7, R2, 3);  
    E_GOTO_REG(RA);

E_LABEL("END");
}

// This application test E_COND_GOTO_REGL
// If the input number is odd write the word "odd" in the shared buffer, else write the word "even"
#define N3  25
void ezh_even_or_odd_app2(){
    E_NOP;
    E_PER_READ(R6, ARM2EZH);            // Peripheral Read
    E_LSR(R6, R6, 2);                   // remove bit 0:1
    E_LSL(R6, R6, 2);                   // bit 0:1 now = 0
    E_LDR(SP, R6, 0);                   // load stack pointer para.coprocessor_stack
	E_LDR(R7, R6, 1);                   // R7 -> para.p_buffer

    E_LOAD_IMM(R0, N3);                 // R0 has the result value

    E_BTST_IMMS(R1, R0, 0);             // bit0 determines if the number is even or odd
    E_ADD_IMM(R3, PC, 16);
    E_COND_GOTO_REGL(PO, R3);           // Jump to odd

    E_ADD_IMM(R3, PC, 40);
    E_COND_GOTOL(ZE, "EVEN");           // Jump to even
    E_INT_TRIGGER(1);                   // Trigger interrupt
    E_GOTO("END");

E_LABEL("ODD");                         // Write odd in the shared buffer
    E_LOAD_IMM(R2, 'O');
    E_STR(R7, R2, 0);             
    E_LOAD_IMM(R2, 'D');
    E_STR(R7, R2, 1);   
    E_LOAD_IMM(R2, 'D');
    E_STR(R7, R2, 2);     
    E_GOTO_REG(RA);

E_LABEL("EVEN");                        // Write even in the shared buffer
    E_LOAD_IMM(R2, 'E');
    E_STR(R7, R2, 0);             
    E_LOAD_IMM(R2, 'V');
    E_STR(R7, R2, 1);   
    E_LOAD_IMM(R2, 'E');
    E_STR(R7, R2, 2);   
    E_LOAD_IMM(R2, 'N');
    E_STR(R7, R2, 3);  
    E_GOTO_REG(RA);

E_LABEL("END");
}
