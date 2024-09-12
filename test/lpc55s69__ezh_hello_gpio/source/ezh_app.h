#include "stdint.h"

#ifndef _EZH_APP_H
#define _EZH_APP_H


typedef struct _EZHPWM_Para
{
    void  *coprocessor_stack;
    uint32_t *p_buffer;
} EZHPWM_Para;


void ezh_app(void);


#endif

