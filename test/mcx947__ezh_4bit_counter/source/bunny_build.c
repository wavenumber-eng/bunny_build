#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bunny_build.h"



#ifndef NULL
	#define NULL 0
#endif // !NULL



uint32_t   *ez_out;
uint32_t   ez_idx;
ez_label_t ez_labels[BUNNY_BUILD_MAX_LABELS];
uint32_t   ez_num_labels;
uint32_t   ez_base_address;
uint32_t   ez_pass_num = 0;
uint32_t   ez_out_len = 0;

/*
	Adds a label to the ezbuild storage.  Also checks if already exists
*/

ezbuild_label_result_t ezbuild__add_label(char* label,uint32_t *resolved_address)
{
	ezbuild_label_result_t r = ezbuild_label__ok;
	uint32_t Address = 0;

	if (ez_num_labels >= BUNNY_BUILD_MAX_LABELS)
	{

		r = ezbuild_label__out_of_mem;
	}
	else
	{
		if (ezbuild__label_get_address(label, &Address) == false)
		{

			ez_labels[ez_num_labels].address = ez_base_address + (ez_idx * 4);
			ez_labels[ez_num_labels].label = label;

			if (resolved_address != NULL)
			{
				*resolved_address = ez_labels[ez_num_labels].address;
			}

			ez_num_labels++;

			r = ezbuild_label__ok;
		}
		else
		{
			r = ezbuild_label__exists;
		}
	}

	return r;
}


bool ezbuild__label_get_address(char* label, uint32_t *Address)
{
	for (uint32_t i = 0; i < ez_num_labels; i++)
	{
		if (ez_labels[i].label != NULL)
		{
			if (strcmp(label, ez_labels[i].label) == 0)
			{
				*Address = ez_labels[i].address;

				return true;
			}
		}
	}

	return false;
}




void ezbuild(uint32_t* ezh_prog_mem_array,
			 uint32_t ezh_prog_mem_length, 
	         uint32_t ezh_prog_mem_base_address,
			 void(*ezh_program)(void))
{

	if (ezh_program == NULL)
	{
		BUNNY_BUILD_PRINTF(BUNNY_BUILD_ERROR_FLAG"pointer to EZH program is null.  Please pass valid ezh builder function\r\n");
		return;
	}

	ez_out = ezh_prog_mem_array;
	ez_idx = 0;
	ez_pass_num = 0;
	ez_num_labels = 0;
	ez_base_address = ezh_prog_mem_base_address;
	ez_out_len = ezh_prog_mem_length;

	BUNNY_BUILD_PRINTF("\r\nbunny_build pass 1\r\n");
	BUNNY_BUILD_PRINTF("----------------------------\r\n");

	ezh_program();


	ez_pass_num++;
	ez_idx = 0;

	BUNNY_BUILD_PRINTF("\r\nbunny_build pass 2\r\n");
	BUNNY_BUILD_PRINTF("----------------------------\r\n\r");

	ezh_program();

	BUNNY_BUILD_PRINTF("\r\nAll done\r\n");
	BUNNY_BUILD_PRINTF("----------------------------\r\n\r");



}

void ezbuild_add_instruction(uint32_t instruction_encoding)
{
	if (ez_pass_num == 1)
	{
		if (ez_idx < ez_out_len)
		{
			ez_out[ez_idx] = instruction_encoding;
			ez_idx++;
		}
		else
		{
			BUNNY_BUILD_PRINTF(BUNNY_BUILD_ERROR_FLAG"out of program memory @ index %d\r\n", ez_idx++);
		}
	}
	else
	{
		ez_idx++;
	}
}
