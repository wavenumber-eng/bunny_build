#include "bunny_build.h"
#include "ezh_init.h"

void EZH_cfgHandshake(bool _enable_handshake, bool _enable_event){
	int enable_handshake;
	int enable_event;
	enable_handshake = (_enable_handshake) ? 1 : 0;
	enable_event     = (_enable_event)     ? 1 : 0;
	LPC_EZH_ARCH_B0->EZHB_ARM2EZH |= (enable_handshake<<EZHB_HANDSHAKE_ENABLE) + (enable_event<<EZHB_HANDSHAKE_EVENT);
}

void EZH_Init(void *pPara){
	LPC_EZH_ARCH_B0->EZHB_CTRL |= (0xC0DE0000 | (1<<EZHB_ENABLE_GPISYNCH));
    LPC_EZH_ARCH_B0->EZHB_ARM2EZH = (uint32_t)pPara;
	EZH_cfgHandshake(true,false);
}

void EZH_boot(void * pProgram) {
	LPC_EZH_ARCH_B0->EZHB_BOOT = (uint32_t) pProgram;
	LPC_EZH_ARCH_B0->EZHB_CTRL = 0xC0DE0011 | (0<<EZHB_MASK_RESP) |(0<<EZHB_ENABLE_AHBBUF) ; // BOOT
}

void EZH_init_and_boot(void * program, void * param_struct)
{
	LPC_EZH_ARCH_B0->EZHB_CTRL |= (0xC0DE0000 | (1<<EZHB_ENABLE_GPISYNCH));
	LPC_EZH_ARCH_B0->EZHB_ARM2EZH = (uint32_t)param_struct;
	EZH_cfgHandshake(true,false);

	LPC_EZH_ARCH_B0->EZHB_BOOT = (uint32_t) program;
	LPC_EZH_ARCH_B0->EZHB_CTRL = 0xC0DE0011 | (0<<EZHB_MASK_RESP) |(0<<EZHB_ENABLE_AHBBUF) ; // BOOT
}


void EZH_stop()
{
	LPC_EZH_ARCH_B0->EZHB_CTRL = (0xC0DE0000 | (1<<EZHB_ENABLE_GPISYNCH));
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
