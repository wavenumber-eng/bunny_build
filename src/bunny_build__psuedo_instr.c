#include "bunny_build.h"


void E_LABEL(const char* label)
{
	uint32_t resolved_address;

	bunny_build_label__result_t r;

	if (bunny_build__pass_num == 0)
	{
		if (label == NULL)
		{
			BUNNY_BUILD_PRINTF(BUNNY_BUILD_ERROR_FLAG"Label on ezh program index %d was invalid\r\n", bunny_build__idx);
		}
		else
		{
			r = bunny_build__add_label(label, &resolved_address);

			if (r == bunny_build_label__ok)
			{
				BUNNY_BUILD_PRINTF(BUNNY_BUILD_INFO_FLAG "Added label " VT100_CYAN "%s" VT100_DEFAULT " at index %d which will resolve to " VT100_CYAN "0x%08x" VT100_DEFAULT " \r\n", label, bunny_build__idx, resolved_address);
			}
			else if (r == bunny_build_label__out_of_mem)
			{
				BUNNY_BUILD_PRINTF(BUNNY_BUILD_ERROR_FLAG "Cannot add another label. BUNNY_BUILD_MAX_LABELS set to %d\r\n", BUNNY_BUILD_MAX_LABELS);
			}
		}
	}

}

//This one is prbably no longer needed since we can resolve lables
void E_DCD(uint32_t loc) { bunny_build__add_instruction(0); if (bunny_build__pass_num) { BUNNY_BUILD_PRINTF(BUNNY_BUILD_ERROR_FLAG"E_DCD NOT YET IMPLEMENTED\r\n"); } }    // __asm(".word "#loc)

void E_DCD_VAL(uint32_t val) { bunny_build__add_instruction(val); }


void E__END()
{
    E_LABEL("END_LOOP");
        E_LOAD_IMM(CFS, 0);
        E_LOAD_SIMM(R0, 0xDB, 24);
        E_LOAD_SIMM(R1, 0x6D, 16);
        E_LOAD_SIMM(R2, 0xB6, 8);
        E_XOR(R0, R0, R1);
        E_XOR(CFM, R0, R2);
        E_HOLD();
        E_GOTO("END_LOOP");
}



void E_LOAD_32IMM(uint32_t rx, uint32_t imm)
{
	if(rx>R7)
	{
		BUNNY_BUILD_PRINTF(BUNNY_BUILD_ERROR_FLAG "E_LOAD_32IMM >> illegal register of %d\r\n", rx);
	}

    E_PUSH(R5);
    E_LOAD_SIMM(rx, (uint8_t)(imm >> 24), 24);
    E_LOAD_SIMM(R5, (uint8_t)(imm >> 16), 16);
    E_OR(rx, rx, R5);
    E_LOAD_SIMM(R5, (uint8_t)(imm >> 8), 8);
    E_OR(rx, rx, R5);
    E_LOAD_IMM(R5, (uint8_t)(imm));
    E_OR(rx, rx, R5);
    E_POP(R5);
}

