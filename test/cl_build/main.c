#include "bunny_build.h"
#include "stdio.h"
#include "camera_reference_test.h"

uint32_t my_ezh_program[1024];


#define WRITE_OUTPUT_TO_TERMINAL		(0)

#if WRITE_OUTPUT_TO_TERMINAL > 0
	#define TERMINAL_OUTPUT(...) 	BUNNY_BUILD_PRINTF(__VA_ARGS__)
#else
	#define TERMINAL_OUTPUT(...) 	
#endif

#define FILE_OUTPUT(x,...)		fprintf(x, __VA_ARGS__);
#define OUTPUT(x,...)  	        FILE_OUTPUT(x,__VA_ARGS__);TERMINAL_OUTPUT(__VA_ARGS__)

#define WORDS_PER_LINE  8


void main()
{

	BUNNY_BUILD_PRINTF("\033[2J");
	BUNNY_BUILD_PRINTF("\033[?25l");
	BUNNY_BUILD_PRINTF("\033[H");

	BUNNY_BUILD_PRINTF("\r\n");

	BUNNY_BUILD_PRINTF(VT100_WHITE"    *----------------------------*\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	     / \\                 |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	    / _ \\                |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	   | / \\ |               |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	   ||   || _______       |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	   ||   || |\\     \\      |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	   ||   || ||\\     \\     |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	   ||   || || \\    |     | \r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	   ||   || ||  \\__/      |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	   ||   || ||   ||       |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	    \\\\_/ \\_/ \\_//        |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	   /   _     _   \\       |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	  /               \\      |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	  |    "VT100_CYAN"O     "VT100_CYAN"O"VT100_WHITE"    |      |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	  |   \\  ___  /   |      |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	 /     \\ \\_/ /     \\     |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	/  -----  |  -----  \\    |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	|     \\__/|\\__/     |    |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	\\       |_|_|       /    |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	 \\_____       _____/     |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	       \\     /           |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	       |     |           |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	       |     |           |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |----------------------------|\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |        Bunny Build         |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    |	EZH Validation Test 0.1  |\r\n");
	BUNNY_BUILD_PRINTF(VT100_WHITE"    *----------------------------*\r\n\r\n\r\n");


	BUNNY_BUILD_PRINTF(VT100_YELLOW"Testing bunny_build against the MCX 320x240 full frame camera interface....\r\n"VT100_DEFAULT);

	/*
		Note: We are using the EZH_Camera_320240_Whole_Buf from from  NXP AN14191SW.

		This software has several ezh programs packed into 1 array called s_smartdmaCameraFirmware .The 1st 8 32-bit words (32bytes) represents an ezh progam/api table.
		The EZH_Camera_320240_Whole_Buf  program is the 1st option and starts directly after the table
	*/

	#define REF_BIN_OFFSET_BYTES	32

	uint32_t* reference_binary = (uint32_t *)(&s_smartdmaCameraFirmware[REF_BIN_OFFSET_BYTES]);

	uint32_t ezh_target_memory_base_address = 0x4000000 + REF_BIN_OFFSET_BYTES;
	

	/*
		build camera generator example
	*/


	uint32_t ez_idx = bunny_build__relocate(&my_ezh_program[0],
											sizeof(my_ezh_program), 
											ezh_target_memory_base_address,  //location of the camera interface code on the target
											EZH_Camera_320240_Whole_Buf
											);

	BUNNY_BUILD_PRINTF(VT100_YELLOW"%d "VT100_DEFAULT" 32bit words assembled (%d bytes) \r\n"VT100_DEFAULT,ez_idx, ez_idx<<2);

	/*
		Check the output against a known reference
	*/

	if(memcmp(my_ezh_program, reference_binary, ez_idx) != 0)
	{
		for (uint32_t i = 0; i < ez_idx; i++)
		{
			BUNNY_BUILD_PRINTF("0x%08x : 0x%08x , 0x%08x",ezh_target_memory_base_address + (4 * i),
											  my_ezh_program[i],
											  reference_binary[i]
			       );

			if (my_ezh_program[i] != reference_binary[i])
			{
				BUNNY_BUILD_PRINTF(VT100_RED"   <<<   error here @ index %d\r\n"VT100_DEFAULT, i);
			}
			else
			{
				BUNNY_BUILD_PRINTF("\r\n");
			}
		}
	}
	else
	{
		BUNNY_BUILD_PRINTF("\r\n");
		BUNNY_BUILD_PRINTF(VT100_GREEN"bunny_build output matches the keil built reference code \r\n"VT100_DEFAULT);
	}

	BUNNY_BUILD_PRINTF("\r\n");
	BUNNY_BUILD_PRINTF("\r\n");
	
	/*
		write the output files
	*/

	FILE* f;

	BUNNY_BUILD_PRINTF("Writing binary data to ezh_binary.h and ezh_binary.c\r\n");


	f = fopen("ezh_binary.h", "w+");

	OUTPUT(f, "#include \"stdint.h\"\n");

	OUTPUT(f, "\n");

	OUTPUT(f, "#ifndef __EZH_BIN_H_\n");
	OUTPUT(f, "#define __EZH_BIN_H_\n");

	OUTPUT(f, "\n");

	OUTPUT(f, "#define EZH_BIN_LEN           %d\n\n", ez_idx);
	OUTPUT(f, "#define EZH_BIN_SIZE_BYTES    %d\n\n", ez_idx<<2);

	OUTPUT(f, "extern uint32_t ezh_bin[EZH_BIN_LEN];");


	OUTPUT(f, "\n\n");

	OUTPUT(f, "#endif\n");

	fclose(f);


	BUNNY_BUILD_PRINTF("\r\n");
	BUNNY_BUILD_PRINTF("\r\n");

	f = fopen("ezh_binary.c", "w+");

	OUTPUT(f, "#include \"ezh_binary.h\"\n\n");
	
	OUTPUT(f, "uint32_t ezh_bin[EZH_BIN_LEN] =\n{\n    ");



	for (uint32_t i = 0; i < ez_idx; i++)
	{
		OUTPUT(f, " 0x%08x " , my_ezh_program[i]);

		if (i < (ez_idx - 1))
		{
			if (i % WORDS_PER_LINE == (WORDS_PER_LINE - 1))
			{
				OUTPUT(f, ", \n    ");
			}
			else
			{
				OUTPUT(f, ",");
			}
		}
		else
		{
			OUTPUT(f, "\n");
		}
	}

	OUTPUT(f, "};");

	fclose(f);

	BUNNY_BUILD_PRINTF("\r\n");
	BUNNY_BUILD_PRINTF("\r\n");


	BUNNY_BUILD_PRINTF("All done.\r\n");

	BUNNY_BUILD_PRINTF("\r\n");
	BUNNY_BUILD_PRINTF("\r\n");


}