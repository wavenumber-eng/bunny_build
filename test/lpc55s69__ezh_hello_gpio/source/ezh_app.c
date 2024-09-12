/*
 * @brief IOH Architecture B mnemonics
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */
#include <ezh_app.h>
#include "fsl_debug_console.h"
#include "bunny_build.h"
#include "cr_section_macros.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EZH_IP_1       19         /* PIO0_19 */
#define EZH_IP_2       20         /* PIO0_20 */
#define EZH_OP_1       3         /* PIO0_3 */

//#define ARM2EZH      (LPC_EZH_ARCH_B_CON_BASE   + 0x20)
//#define EZH2ARM      (LPC_EZH_ARCH_B_CON_BASE   + 0x24)

//#define EZHBREAKADDR (LPC_EZH_ARCH_B_CON_BASE   + 0x10)
//#define EZHBREAKVECT (LPC_EZH_ARCH_B_CON_BASE   + 0x14)
//#define LPC_EZH_ARCH_B0     ((EZH_ARCH_B_CON_Type *)     LPC_EZH_ARCH_B_CON_BASE)



volatile void ezh_app (void){
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

    E_PER_WRITE(R0, EZH2ARM);  // notify app to update next foreground buffer address and fill count
    E_HEART_RYTHM_IMM(37493);

 E_LABEL("toggle");
    E_BSET_IMM(GPO, GPO, EZH_OP_1);
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_BCLR_IMM(GPO, GPO, EZH_OP_1);
    E_WAIT_FOR_BEAT();
    E_WAIT_FOR_BEAT();
    E_PER_WRITE(R0, EZH2ARM);
    E_GOSUB("toggle");
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
//	EZH_boot(pwm_engine);
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
