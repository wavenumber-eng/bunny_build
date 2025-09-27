#include "bunny_build.h"


//#define E_GOSUB(a30)                    __asm(".word %c0" : : "i" (0x03 + a30))
void  E_GOSUB(const char* a30)
{
	uint32_t resolved_address;
	if (bunny_build__pass_num == 1)
	{

		if (bunny_build__label_get_address(a30, &resolved_address))
		{
			bunny_build__add_instruction(0x3 + resolved_address);
			BUNNY_BUILD_PRINTF(BUNNY_BUILD_INFO_FLAG "E_GOSUB to label " VT100_CYAN "%s" VT100_DEFAULT " will resolve to address " VT100_CYAN "0x%08x" VT100_DEFAULT " at index %d\r\n", a30, resolved_address, bunny_build__idx);
		}
		else
		{
			BUNNY_BUILD_PRINTF(BUNNY_BUILD_ERROR_FLAG "E_GOSUB Error at index %d. label %s was not defined \r\n", bunny_build__idx, a30);
			bunny_build__add_instruction(0);
		}
	}
	else
	{
		//make sure to always add something in pass 0 so address get resolved in pass 1
		bunny_build__add_instruction(0);
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                       E_GOTO
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#define E_GOTO(a21)			__asm(".word 0x15 + (1<<9) + " #a21 "<<9")

void  E_GOTO(const char* a21)
{
	uint32_t resolved_address;
	uint32_t masked_address;
	if (bunny_build__pass_num == 1)
	{

		if (bunny_build__label_get_address(a21, &resolved_address))
		{
			masked_address = resolved_address & 0x1FFFFF;					// Using absoulte address
			bunny_build__add_instruction(0x15 + (1 << 9) + (masked_address << 9));
		}
		else
		{
			BUNNY_BUILD_PRINTF(BUNNY_BUILD_ERROR_FLAG "E_GOTO Error at index %d. label %s was not defined \r\n", bunny_build__idx, a21);
			bunny_build__add_instruction(0);
		}
	}
	else
	{
		//make sure to always add something in pass 0 so address get resolved in pass 1
		bunny_build__add_instruction(0);
	}
}


//#define E_GOTO_REG(raddr)			__asm(".word %c0" : : "i" (0x15  + (raddr<<14)))
void  E_GOTO_REG(uint32_t raddr)
{
	if (bunny_build__pass_num == 1)
	{
		bunny_build__add_instruction(0x15 + (raddr << 14));
		BUNNY_BUILD_PRINTF(BUNNY_BUILD_INFO_FLAG "E_GOTO to address in register " VT100_CYAN "%02d" VT100_DEFAULT " at index %d\r\n", raddr, bunny_build__idx);
	}
	else
	{
		//make sure to always add something in pass 0 so address get resolved in pass 1
		bunny_build__add_instruction(0);
	}
}


//#define E_GOTOL(a21)			__asm(".word 0x15  + (1<<10) + (1<<9)  + " #a21 "<<9") , GOTO and Link
void  E_GOTOL(const char* a21)
{
	uint32_t resolved_address;
	int32_t masked_address;
	if (bunny_build__pass_num == 1)
	{

		if (bunny_build__label_get_address(a21, &resolved_address))
		{
			masked_address = resolved_address & 0x1FFFFF;
			bunny_build__add_instruction(0x15 + (1 << 10) + (1 << 9) + (masked_address << 9));		// Using absoulte address
		}
		else
		{
			BUNNY_BUILD_PRINTF(BUNNY_BUILD_ERROR_FLAG"E_GOTOL Error at index %d. label %s was not defined \r\n", bunny_build__idx, a21);
			bunny_build__add_instruction(0);
		}
	}
	else
	{
		//make sure to always add something in pass 0 so address get resolved in pass 1
		bunny_build__add_instruction(0);
	}
}


//#define E_GOTO_REGL(raddr)			__asm(".word %c0" : : "i" (0x15  + (raddr<<14)+ (1<<10)))
void  E_GOTO_REGL(uint32_t raddr)
{
	if (bunny_build__pass_num == 1)
	{
		bunny_build__add_instruction(0x15 + (raddr << 14) + (1 << 10));
		BUNNY_BUILD_PRINTF(BUNNY_BUILD_INFO_FLAG "E_GOTO to address in register " VT100_CYAN "%02d" VT100_DEFAULT " at index %d\r\n", raddr, bunny_build__idx);
	}
	else
	{
		//make sure to always add something in pass 0 so address get resolved in pass 1
		bunny_build__add_instruction(0);
	}
}


//#define E_COND_GOTO(cond,a21)			__asm(".word 0x15  +(cond<<5) + (1<<9) + " #a21 "<<9")
void  E_COND_GOTO(uint32_t cond, const char* a21)
{
	uint32_t resolved_address;
	int32_t masked_address;
	if (bunny_build__pass_num == 1)
	{

		if (bunny_build__label_get_address(a21, &resolved_address))
		{
			masked_address = resolved_address & 0x1FFFFF;
			bunny_build__add_instruction(0x15 + (cond << 5) + (1 << 9) + (masked_address << 9));		// Using absoulte address
		}
		else
		{
			BUNNY_BUILD_PRINTF(BUNNY_BUILD_ERROR_FLAG "E_GOTOL Error at index %d. label %s was not defined \r\n", bunny_build__idx, a21);
			bunny_build__add_instruction(0);
		}
	}
	else
	{
		//make sure to always add something in pass 0 so address get resolved in pass 1
		bunny_build__add_instruction(0);
	}
}


//#define E_COND_GOTO_REG(cond,raddr)			__asm(".word %c0" : : "i" (0x15  + (raddr<<14) +(cond<<5)))
void  E_COND_GOTO_REG(uint32_t cond, uint32_t raddr)
{
	if (bunny_build__pass_num == 1)
	{
		bunny_build__add_instruction(0x15 + (raddr << 14) + (cond << 5));
		BUNNY_BUILD_PRINTF(BUNNY_BUILD_INFO_FLAG "E_GOTO to address in register " VT100_CYAN "%02d" VT100_DEFAULT" at index %d\r\n", raddr, bunny_build__idx);
	}
	else
	{
		//make sure to always add something in pass 0 so address get resolved in pass 1
		bunny_build__add_instruction(0);
	}
}


//#define E_COND_GOTOL(cond,a21)			__asm(".word 0x15  + (1<<10)  +(cond<<5)  + (1<<9) + " #a21 "<<9")
void  E_COND_GOTOL(uint32_t cond, const char* a21)
{
	uint32_t resolved_address;
	int32_t masked_address;
	if (bunny_build__pass_num == 1)
	{

		if (bunny_build__label_get_address(a21, &resolved_address))
		{
			masked_address = resolved_address & 0x1FFFFF;		// Using absoulte address
			bunny_build__add_instruction(0x15 + (1 << 10) + (cond << 5) + (1 << 9) + (masked_address << 9));
		}
		else
		{
			BUNNY_BUILD_PRINTF(BUNNY_BUILD_ERROR_FLAG "E_GOTOL Error at index %d. label %s was not defined \r\n", bunny_build__idx, a21);
			bunny_build__add_instruction(0);
		}
	}
	else
	{
		//make sure to always add something in pass 0 so address get resolved in pass 1
		bunny_build__add_instruction(0);
	}
}


//#define E_COND_GOTO_REGL(cond,raddr)			__asm(".word %c0" : : "i" (0x15  + (raddr<<14)+ (1<<10) +(cond<<5)))
void E_COND_GOTO_REGL(uint32_t cond, uint32_t raddr)
{
	if (bunny_build__pass_num == 1)
	{
		bunny_build__add_instruction(0x15 + (raddr << 14) + (1 << 10) + (cond << 5));
		BUNNY_BUILD_PRINTF(BUNNY_BUILD_INFO_FLAG "E_GOTO to address in register " VT100_CYAN "%02d" VT100_DEFAULT " at index %d\r\n", raddr, bunny_build__idx);
	}
	else
	{
		//make sure to always add something in pass 0 so address get resolved in pass 1
		bunny_build__add_instruction(0);
	}
}
