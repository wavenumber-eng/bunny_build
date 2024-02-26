#include "bunny_build.h"
#include "stdio.h"

uint32_t my_ezh_program[1024];

/* LPC5500 EZH register address*/
#define LPC_EZH_ARCH_B_CON_BASE		0x40033020
#define ARM2EZH						(LPC_EZH_ARCH_B_CON_BASE   + 0x20)
#define EZH2ARM						(LPC_EZH_ARCH_B_CON_BASE   + 0x24)
#define EZHBREAKADDR				(LPC_EZH_ARCH_B_CON_BASE   + 0x10)
#define EZHBREAKVECT				(LPC_EZH_ARCH_B_CON_BASE   + 0x14)
#define LPC_EZH_ARCH_B0             ((EZH_ARCH_B_CON_Type *)     LPC_EZH_ARCH_B_CON_BASE)


/*
	Camera code generator example
	Was placed at 0x20067000 in the keil project
*/

uint32_t ezh_camera_keil_reference_code[512] = 
{
0x00000012, 0x00000012, 0x33041804, 0x02681810, 0x02601810, 0x0005B001, 0x01058C01, 0x01076801, 0x01076C01, 0x00477406, 0x00008800, 0xDB6C9201, 0x20026418, 0x21026418, 0x22026418, 0x23026418,
0x24026418, 0x25026418, 0x26026418, 0x27026418, 0xD2026418, 0x00140800, 0x00041400, 0x04D0361C, 0x0FF7800D, 0xC202EC18, 0x20067083, 0x200670A3, 0x0C054608, 0x0108C462, 0x00155406, 0x2006705F,
0xC002EC18, 0x00140800, 0x00041400, 0xC102EC18, 0xC202EC18, 0x01058C01, 0xF2022018, 0x2006705F, 0x2000CC18, 0x2100CC18, 0x0C04CC08, 0x00041400, 0x1FF4880D, 0x03059001, 0x00E4820E, 0x00140420,
0x00150022, 0x33004425, 0x01C4820E, 0x00240420, 0x00150022, 0x01058C21, 0x33004425, 0x02A4820E, 0x00340420, 0x00150022, 0x33004425, 0x0384820E, 0x00440420, 0x00150022, 0x01058C21, 0x33004425,
0x0464820E, 0x00540420, 0x00150022, 0x33004425, 0x0544820E, 0x00640420, 0x00150022, 0x01058C21, 0x33004425, 0x0624820E, 0x00740420, 0x00150022, 0x33004425, 0x0704820E, 0x00840420, 0x00150022,
0x01058C21, 0x33004425, 0x07E4820E, 0x00940420, 0x00150022, 0x33004425, 0x08C4820E, 0x00A40420, 0x00150022, 0x01058C21, 0x33004425, 0x09A4820E, 0x00B40420, 0x00150022, 0x33004425, 0x0A84820E,
0x00C40420, 0x00150022, 0x01058C21, 0x33004425, 0x0B64820E, 0x00D40420, 0x00150022, 0x33004425, 0x0C44820E, 0x00E40420, 0x00150022, 0x01058C21, 0x33004425, 0x0D24820E, 0x00F40420, 0x00150022,
0x33004425, 0x0E04820E, 0x01040420, 0x00150022, 0x01058C21, 0x33004425, 0x0EE4820E, 0x01140420, 0x00150022, 0x33004425, 0x0FC4820E, 0x01240420, 0x00150022, 0x01058C21, 0x33004425, 0x10A4820E,
0x01340420, 0x00150022, 0x33004425, 0x1184820E, 0x01440420, 0x00150022, 0x01058C21, 0x33004425, 0x1264820E, 0x01540420, 0x00150022, 0x33004425, 0x1344820E, 0x01640420, 0x00150022, 0x01058C21,
0x33004425, 0x1424820E, 0x01740420, 0x00150022, 0x33004425, 0x1504820E, 0x01840420, 0x00150022, 0x01058C21, 0x33004425, 0x15E4820E, 0x01940420, 0x00150022, 0x33004425, 0x16C4820E, 0x01A40420,
0x00150022, 0x01058C21, 0x33004425, 0x17A4820E, 0x01B40420, 0x00150022, 0x33004425, 0x1884820E, 0x01C40420, 0x00150022, 0x01058C21, 0x33004425, 0x1964820E, 0x01D40420, 0x00150022, 0x33004425,
0x1A44820E, 0x01E40420, 0x00150022, 0x01058C21, 0x33004425, 0x1B24820E, 0x01F40420, 0x00150022, 0x33004425, 0xC102EC18, 0xC202EC18, 0x1C04820E, 0x02040420, 0x00150022, 0x01058C21, 0x33004425,
0x2102EC38, 0x2202EC38, 0x00148806, 0xF2022018, 0x2006705F, 0x00004770
};


void ezh_camera_interface_builder(void)
{
	E_NOP();
	E_NOP();
	E_PER_READ(R6, ARM2EZH);
	//Align the value of R6 to word
	E_LSR(R6, R6, 2);
	E_LSL(R6, R6, 2);
	E_LDR(SP, R6, 0);//EZH stack initial
	E_LDR(R3, R6, 1);//R3 point to the store buffer in the RAM	

	E_LABEL("init");
	E_LDR(CFS, PC, 1); // Load CFS
	E_LDR(CFM, PC, 1); // Load CFM
	E_ADD_IMM(PC, PC, 1 * 4); //E_goto
	E_DCD_VAL(BS7(0) | BS6(0) | BS5(0) | BS4(0) | BS3(0) | BS2(2) | BS1(1) | BS0(0));   // Config source (C^D + C^D-)  where C^ is Clock rise, D- is Data inverted
	E_DCD_VAL(BS7(6) | BS6(6) | BS5(6) | BS4(6) | BS3(6) | BS2(BS_FALL) | BS1(BS_FALL) | BS0(BS_FALL) | (1 << 0)); // Config MUX    (C^D + C^D-)  where C^ is Clock rise, D- is Data inverted, enable OR 

	E_BCLR_IMM(GPD, GPD, 0);
	E_BCLR_IMM(GPD, GPD, 1);
	E_BCLR_IMM(GPD, GPD, 2);
	E_BCLR_IMM(GPD, GPD, 3);
	E_BCLR_IMM(GPD, GPD, 4);
	E_BCLR_IMM(GPD, GPD, 5);
	E_BCLR_IMM(GPD, GPD, 6);
	E_BCLR_IMM(GPD, GPD, 7);
	E_BSET_IMM(GPD, GPD, 18);

	//	E_LABEL("teset");
	//		E_BTOG_IMM(GPO, GPO, 18); 
	//	E_GOSUB(teset); 


	E_LOAD_IMM(R2, 1);
	E_LOAD_IMM(R5, 0);

	E_LABEL("PCLK");
	E_ACC_VECTORED_HOLD(PC, (1 << 2));
	E_AND_IMM(R0, GPI, 0xff);
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
	E_GOSUB("VSYNC");//BS0
	E_GOSUB("HSYNC");//BS1
	E_SUB_IMMS(R1, R5, 192);
	E_COND_STRB_POST(PO, R3, R0, 1);  // data will be stored from GPI bottom byte to RAM
	E_ADD_IMM(R5, R5, 1);

	E_GOSUB("PCLK");

	E_LABEL("VSYNC");
	E_BSET_IMM(CFM, CFM, 0); 			//clear the vector flag	
	E_LOAD_IMM(R2, 1);
	E_LOAD_IMM(R5, 0);

	E_BSET_IMM(CFM, CFM, 1); 			//enable HSYNC interrupt
	E_BSET_IMM(CFM, CFM, 2); 			//enable PCLK  interrupt	
	E_LDR(R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_BTOG_IMM(GPO, GPO, 18);				//toggle the P0_18, used to measure the timming in logic device
	E_GOSUB("PCLK");

	E_LABEL("HSYNC");

	E_BCLR_IMM(R3, R3, 0);
	E_BCLR_IMM(R3, R3, 1);
	E_SUB_IMM(R3, R3, 192);
	E_LOAD_IMM(R5, 0);

	E_AND_IMM(R2, R2, 0x1FF);

	E_LDR(R4, R6, 3);//R4 point to the AI buffer in the RAM		

	E_XOR_IMMS(R0, R2, (14 * 1));
	E_COND_LOAD_IMM(ZE, R1, 1);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 2));
	E_COND_LOAD_IMM(ZE, R1, 2);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 3));
	E_COND_LOAD_IMM(ZE, R1, 3);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 4));
	E_COND_LOAD_IMM(ZE, R1, 4);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 5));
	E_COND_LOAD_IMM(ZE, R1, 5);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 6));
	E_COND_LOAD_IMM(ZE, R1, 6);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 7));
	E_COND_LOAD_IMM(ZE, R1, 7);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 8));
	E_COND_LOAD_IMM(ZE, R1, 8);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 9));
	E_COND_LOAD_IMM(ZE, R1, 9);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 10));
	E_COND_LOAD_IMM(ZE, R1, 10);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 11));
	E_COND_LOAD_IMM(ZE, R1, 11);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 12));
	E_COND_LOAD_IMM(ZE, R1, 12);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	


	E_XOR_IMMS(R0, R2, (14 * 13));
	E_COND_LOAD_IMM(ZE, R1, 13);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 14));
	E_COND_LOAD_IMM(ZE, R1, 14);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 15));
	E_COND_LOAD_IMM(ZE, R1, 15);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 16));
	E_COND_LOAD_IMM(ZE, R1, 16);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 17));
	E_COND_LOAD_IMM(ZE, R1, 17);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 18));
	E_COND_LOAD_IMM(ZE, R1, 18);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 19));
	E_COND_LOAD_IMM(ZE, R1, 19);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 20));
	E_COND_LOAD_IMM(ZE, R1, 20);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 21));
	E_COND_LOAD_IMM(ZE, R1, 21);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 22));
	E_COND_LOAD_IMM(ZE, R1, 22);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 23));
	E_COND_LOAD_IMM(ZE, R1, 23);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 24));
	E_COND_LOAD_IMM(ZE, R1, 24);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 25));
	E_COND_LOAD_IMM(ZE, R1, 25);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 26));
	E_COND_LOAD_IMM(ZE, R1, 26);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	


	E_XOR_IMMS(R0, R2, (14 * 27));
	E_COND_LOAD_IMM(ZE, R1, 27);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 28));
	E_COND_LOAD_IMM(ZE, R1, 28);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 29));
	E_COND_LOAD_IMM(ZE, R1, 29);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (14 * 30));
	E_COND_LOAD_IMM(ZE, R1, 30);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	


	E_XOR_IMMS(R0, R2, (14 * 31));
	E_COND_LOAD_IMM(ZE, R1, 31);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	

	E_BSET_IMM(CFM, CFM, 1); 			//clear the vector flag
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag			

	E_XOR_IMMS(R0, R2, (14 * 32));
	E_COND_LOAD_IMM(ZE, R1, 32);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);			 //R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0, EZH2ARM);   // interrupt and told ARM data is ready	
	E_COND_BCLR_IMM(ZE, CFM, CFM, 1); 	 //disable HSYNC interrupt
	E_COND_BCLR_IMM(ZE, CFM, CFM, 2); 	 //disable PCLK  interrupt	

	E_ADD_IMM(R2, R2, 1);
	E_BTOG_IMM(GPO, GPO, 18);			 //toggle the P0_18, used to measure the timming in logic device
	E_GOSUB("PCLK");
}

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


	BUNNY_BUILD_PRINTF(VT100_YELLOW"Testing bunny_build against the MCX/LPC55 camera interface generator....\r\n"VT100_DEFAULT);


	/*
		build camera generator example
	*/

	uint32_t ezh_target_memory_base_address = 0x20067000;

	
	ezbuild(&my_ezh_program[0],
		    sizeof(my_ezh_program), 
			ezh_target_memory_base_address,  //location of the camera interface code on the target
			ezh_camera_interface_builder
			);



	/*
		Check the output against a known reference
	*/

	if(memcmp(my_ezh_program, ezh_camera_keil_reference_code, ez_idx) != 0)
	{
		for (uint32_t i = 0; i < ez_idx; i++)
		{
			BUNNY_BUILD_PRINTF("0x%08x : 0x%08x , 0x%08x",ezh_target_memory_base_address + (4 * i),
											  my_ezh_program[i],
											  ezh_camera_keil_reference_code[i]
			       );

			if (my_ezh_program[i] != ezh_camera_keil_reference_code[i])
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
		BUNNY_BUILD_PRINTF(VT100_GREEN"bunny_build output matches the keil EZH reference code for the MCX/LPC55 Camera generator code \r\n"VT100_DEFAULT);
	}

	/*
		write the output files
	*/

	FILE* f = fopen("ezh_binary.c", "w+");

	fprintf(f, "#include \"ezh_binary.h\"\n\n");
	
	fprintf(f, "uint32_t ezh_bin[EZH_BIN_SIZE] =\n{\n    ");

	#define WORDS_PER_LINE 8

	for (uint32_t i = 0; i < ez_idx; i++)
	{
		fprintf(f, " 0x%08x " , my_ezh_program[i]);

		if (i < (ez_idx - 1))
		{
			if (i % WORDS_PER_LINE == (WORDS_PER_LINE - 1))
			{
				fprintf(f, ", \n    ");
			}
			else
			{
				fprintf(f, ",");
			}
		}
		else
		{
			fprintf(f, "\n");
		}
	}

	fprintf(f, "};");

	fclose(f);

	f = fopen("ezh_binary.h", "w+");


	fprintf(f, "#include \"stdint.h\"\n");

	fprintf(f, "\n");

	fprintf(f, "#ifndef __EZH_BIN_H_\n");
	fprintf(f, "#define __EZH_BIN_H_\n");

	fprintf(f, "\n");

	fprintf(f, "#define EZH_BIN_SIZE     %d\n\n",ez_idx);
	fprintf(f, "extern uint32_t ezh_bin[EZH_BIN_SIZE];");


	fprintf(f, "\n\n");

	fprintf(f, "#endif\n");

	fclose(f);
}