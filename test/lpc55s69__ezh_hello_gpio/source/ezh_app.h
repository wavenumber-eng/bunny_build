

#include "fsl_common.h"

typedef struct _EZHPWM_Para{
    void  *coprocessor_stack;
		uint32_t *p_buffer;
} EZHPWM_Para;

void EZH_Pin_Init(void);
void EZH_SetExternalFlag(uint8_t flag);
void EZH_boot(void * pProgram);

void ezh_app (void);
