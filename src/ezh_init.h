#include "stdint.h"
#include "stdbool.h"

#ifndef _EZH_INIT_H
#define _EZH_INIT_H

void EZH_SetExternalFlag(uint8_t flag);

void EZH_cfgHandshake(bool _enable_handshake, bool _enable_event);

void EZH_Init(void *pPara);

void EZH_boot(void * pProgram);

#define PINFUNC_EZH        0xF

#endif