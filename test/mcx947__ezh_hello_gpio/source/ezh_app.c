#include <ezh_app.h>
#include "fsl_debug_console.h"
#include "fsl_ezh_armclang.h"
#include <cr_section_macros.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define EZH_OP_1      		 24         	/* GPIO24  us PIO2_4 on MCX */

#define LPC_EZH_ARCH_B_CON_BASE 0x40033020
#define ARM2EZH      		(LPC_EZH_ARCH_B_CON_BASE   + 0x20)
#define EZH2ARM    			(LPC_EZH_ARCH_B_CON_BASE   + 0x24)

#define EZHBREAKADDR 		(LPC_EZH_ARCH_B_CON_BASE   + 0x10)
#define EZHBREAKVECT 		(LPC_EZH_ARCH_B_CON_BASE   + 0x14)
#define LPC_EZH_ARCH_B0     ((EZH_ARCH_B_CON_Type *)     LPC_EZH_ARCH_B_CON_BASE)  

/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

/*
 * Main EZH code to generate PWM signal on EZH_OP1
 * EZH_OP1 creates a defined square wave depending on the 2 input switch settings EZH_IP1 and EZH_IP2
 * IP1 = L, IP2 = L then 10kHz
 * IP1 = H, IP2 = L then 5kHz
 * IP1 = L, IP2 = H then 1kHz
 * IP1 = H, IP2 = H then Set output low
 * Heart Beat timer value is based on AHB clock of 150mHz
 */
/*
 * 04000000 <gpio_toggle>:
 4000000:	b480      	push	{r7}
 4000002:	af00      	add	r7, sp, #0
 4000004:	00000012 	.word	0x00000012
 4000008:	33041804 	.word	0x33041804
 400000c:	02681810 	.word	0x02681810
 4000010:	02601810 	.word	0x02601810
 4000014:	0005b001 	.word	0x0005b001
 4000018:	01059c01 	.word	0x01059c01
 400001c:	d8022018 	.word	0xd8022018
 4000020:	d8026418 	.word	0xd8026418
 4000024:	33004405 	.word	0x33004405
 4000028:	92750032 	.word	0x92750032

 0400002c <toggle>:
 400002c:	d8022018 	.word	0xd8022018
 4000030:	00000072 	.word	0x00000072
 4000034:	00000072 	.word	0x00000072
 4000038:	38022018 	.word	0x38022018
 400003c:	00000072 	.word	0x00000072
 4000040:	00000072 	.word	0x00000072
 4000044:	0400002f 	.word	0x0400002f
 4000048:	bf00      	nop
 400004a:	46bd      	mov	sp, r7
 400004c:	f85d 7b04 	ldr.w	r7, [sp], #4
 4000050:	4770      	bx	lr
 4000052:	Address 0x4000052 is out of bounds.
 *
 *
 *
 *
 */

void __attribute__ ((section("for_ezh_ram"))) gpio_toggle (void){
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

    /* IP1 = L, IP2 = L then R5 = b1100 & b0000 = 0*/
    /* IP1 = H, IP2 = L then R5 = b1100 & b0100 = 4*/
    /* IP1 = L, IP2 = H then R5 = b1100 & b1000 = 8*/
    /* IP1 = H, IP2 = H then R5 = b1100 & b1100 = 12*/
    E_PER_WRITE(R0, EZH2ARM);  // notify app to update next foreground buffer address and fill count
    E_HEART_RYTHM_IMM(37493);

 E_LABEL("toggle");
    E_BSET_IMM(GPO, GPO, EZH_OP_1);
    E_WAIT_FOR_BEAT;
    E_WAIT_FOR_BEAT;
    E_BCLR_IMM(GPO, GPO, EZH_OP_1);
    E_WAIT_FOR_BEAT;
    E_WAIT_FOR_BEAT;
    E_GOSUB(toggle);

}
void EZH_cfgHandshake(bool _enable_handshake, bool _enable_event){
	int enable_handshake;
	int enable_event;
	enable_handshake = (_enable_handshake) ? 1 : 0;
	enable_event     = (_enable_event)     ? 1 : 0;
	LPC_EZH_ARCH_B0->EZHB_ARM2EZH |= (enable_handshake<<EZHB_HANDSHAKE_ENABLE) + (enable_event<<EZHB_HANDSHAKE_EVENT);
};

void EZH_Init(void *pPara){
	LPC_EZH_ARCH_B0->EZHB_CTRL |= (0xC0DE0000 | (1<<EZHB_ENABLE_GPISYNCH));
    LPC_EZH_ARCH_B0->EZHB_ARM2EZH = (uint32_t)pPara;
	EZH_cfgHandshake(true,false);
}

void EZH_boot(void * pProgram) {
	LPC_EZH_ARCH_B0->EZHB_BOOT = (uint32_t) pProgram;
	LPC_EZH_ARCH_B0->EZHB_CTRL = 0xC0DE0011 | (0<<EZHB_MASK_RESP) |(0<<EZHB_ENABLE_AHBBUF) ; // BOOT
};

void EZH_Start(void){
	EZH_boot(gpio_toggle);
}


void EZH_SetExternalFlag(uint8_t flag)
{
    volatile uint32_t ezh_ctrl = (LPC_EZH_ARCH_B0->EZHB_CTRL & 0x0000FFFF);
    if (flag == 0) {
        ezh_ctrl &= ~(1 << EZHB_EXTERNAL_FLAG);
    } else {
        ezh_ctrl |= (1 << EZHB_EXTERNAL_FLAG);
    }
    LPC_EZH_ARCH_B0->EZHB_CTRL = (0xC0DE0000 | ezh_ctrl);
}
