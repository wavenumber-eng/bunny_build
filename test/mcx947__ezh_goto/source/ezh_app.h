#include "stdint.h"

#ifndef _EZH_APP_H
#define _EZH_APP_H


typedef struct _EZHPWM_Para
{
    void  *coprocessor_stack;
    uint32_t *p_buffer;
} EZHPWM_Para;


void ezh_4_bit_counter_up_app (void);

void ezh_4_bit_counter_down_app (void);

void ezh_fun1_app();

void ezh_even_or_odd_app();

void ezh_even_or_odd_app2();

#endif


