#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bunny_build.h"



#ifndef NULL
	#define NULL 0
#endif // !NULL


uint32_t   *bunny_build__out;
uint32_t   bunny_build__idx;
bunny_build__label_t bunny_build__labels[BUNNY_BUILD_MAX_LABELS];
uint32_t   bunny_build__num_labels;
uint32_t   bunny_build__base_address;
uint32_t   bunny_build__pass_num = 0;
uint32_t   bunny_build__out_len = 0;

/*
	Adds a label to the bunny_build storage.  Also checks if already exists
*/

bunny_build_label__result_t bunny_build__add_label(char* label,uint32_t *resolved_address)
{
	bunny_build_label__result_t r = bunny_build_label__ok;
	uint32_t Address = 0;

	if (bunny_build__num_labels >= BUNNY_BUILD_MAX_LABELS)
	{

		r = bunny_build_label__out_of_mem;
	}
	else
	{
		if (bunny_build__label_get_address(label, &Address) == false)
		{

			bunny_build__labels[bunny_build__num_labels].address = bunny_build__base_address + (bunny_build__idx * 4);
			bunny_build__labels[bunny_build__num_labels].label = label;

			if (resolved_address != NULL)
			{
				*resolved_address = bunny_build__labels[bunny_build__num_labels].address;
			}

			bunny_build__num_labels++;

			r = bunny_build_label__ok;
		}
		else
		{
			r = bunny_build_label__exists;
		}
	}

	return r;
}


bool bunny_build__label_get_address(char* label, uint32_t *Address)
{
	for (uint32_t i = 0; i < bunny_build__num_labels; i++)
	{
		if (bunny_build__labels[i].label != NULL)
		{
			if (strcmp(label, bunny_build__labels[i].label) == 0)
			{
				*Address = bunny_build__labels[i].address;

				return true;
			}
		}
	}

	return false;
}


uint32_t bunny_build__relocate(uint32_t* ezh_prog_mem_array,
			 uint32_t ezh_prog_mem_length, 
	         uint32_t ezh_prog_mem_base_address,
			 void(*ezh_program)(void))
{

	if (ezh_program == NULL)
	{
		BUNNY_BUILD_PRINTF(BUNNY_BUILD_ERROR_FLAG"pointer to EZH program is null.  Please pass valid ezh builder function\r\n");
		return 0;
	}

	bunny_build__out = ezh_prog_mem_array;
	bunny_build__idx = 0;
	bunny_build__pass_num = 0;
	bunny_build__num_labels = 0;
	bunny_build__base_address = ezh_prog_mem_base_address;
	bunny_build__out_len = ezh_prog_mem_length;

	BUNNY_BUILD_PRINTF("\r\nbunny_build pass 1\r\n");
	BUNNY_BUILD_PRINTF("----------------------------\r\n");

	ezh_program();


	bunny_build__pass_num++;
	bunny_build__idx = 0;

	BUNNY_BUILD_PRINTF("\r\nbunny_build pass 2\r\n");
	BUNNY_BUILD_PRINTF("----------------------------\r\n");

	ezh_program();

	BUNNY_BUILD_PRINTF("\r\nAll done\r\n");
	BUNNY_BUILD_PRINTF("----------------------------\r\n");

	return bunny_build__idx;

}

uint32_t bunny_build(uint32_t* ezh_prog_mem_array,
			 uint32_t ezh_prog_mem_length, 
			 void(*ezh_program)(void))
{
	return bunny_build__relocate(ezh_prog_mem_array,
		ezh_prog_mem_length,
		(uint32_t)(ezh_prog_mem_array), 
		ezh_program
	);

}

void bunny_build__add_instruction(uint32_t instruction_encoding)
{
	if (bunny_build__pass_num == 1)
	{
		if (bunny_build__idx < bunny_build__out_len)
		{
			bunny_build__out[bunny_build__idx] = instruction_encoding;
			bunny_build__idx++;
		}
		else
		{
			BUNNY_BUILD_PRINTF(BUNNY_BUILD_ERROR_FLAG"out of program memory @ index %d\r\n", bunny_build__idx++);
		}
	}
	else
	{
		bunny_build__idx++;
	}
}
