#include <ezh_app.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../../src/bunny_build.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define MCX_EZH_ARCH_B_CON_BASE 0x40033020
#define ARM2EZH      		(MCX_EZH_ARCH_B_CON_BASE   + 0x20)
#define EZH2ARM    			(MCX_EZH_ARCH_B_CON_BASE   + 0x24)

#define EZHBREAKADDR 		(MCX_EZH_ARCH_B_CON_BASE   + 0x10)
#define EZHBREAKVECT 		(MCX_EZH_ARCH_B_CON_BASE   + 0x14)
#define MCX_EZH_ARCH_B0     ((EZH_ARCH_B_CON_Type *)     MCX_EZH_ARCH_B_CON_BASE)  

#define EZH_CTR_b0      		 22         	/* GPIO22  us PIO2_2 on MCX */
#define EZH_CTR_b1      		 23         	/* GPIO23  us PIO2_3 on MCX */
#define EZH_CTR_b2      		 24         	/* GPIO24  us PIO2_4 on MCX */
#define EZH_CTR_b3      		 25         	/* GPIO25  us PIO2_5 on MCX */
#define EZH_FRQ_SEL              27             /* GPIO27  us PIO2_7 on MCX */

uint32_t __attribute__ ((section("for_ezh_ram"))) my_ezh_program[1024];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

// This application tests GOTOL, GOTOL and GOTO_REG instructions
// Counter up from 0 to 0xF
void ezh_4_bit_counter_up_app (void){
    E_NOP();
    E_PER_READ(R6, ARM2EZH); //Peripheral Read
    E_LSR(R6, R6, 2);        //remove bit 0:1
    E_LSL(R6, R6, 2);        //bit 0:1 now = 0
    E_LDR(SP, R6, 0);        //load stack pointer para.coprocessor_stack
	E_LDR(R7, R6, 1);        //R7 -> para.p_buffer

E_LABEL("INIT_CU");
	E_BSET_IMM(GPD, GPD, EZH_CTR_b0);   //counter pins direction
	E_BSET_IMM(GPD, GPD, EZH_CTR_b1);
    E_BSET_IMM(GPD, GPD, EZH_CTR_b2);
	E_BSET_IMM(GPD, GPD, EZH_CTR_b3);
    E_BCLR_IMM(GPD, GPD, EZH_FRQ_SEL);

    E_LOAD_IMM(R0, 0);  // R0 has the counter value

E_LABEL("LOOP_CU");
    E_GOTOL("COUNTER_INC_LOOP");
    E_GOTOL("UPDATE_OUTPUT");
    E_WAIT_FOR_BEAT();
    E_GOTO("LOOP_CU");


E_LABEL("COUNTER_INC_LOOP");
    E_ADD_IMM(R0, R0, 1);               // R0 = R0 + 1
    E_AND_IMM(R0, R0, 0XF);             // R0 = R0 % 0b1111
    E_GOTO_REG(RA);

E_LABEL("UPDATE_OUTPUT");
    E_LSL(GPO, R0, 22);                 // Set output bits of counter
    E_BTST_IMMS(R1, GPI, EZH_FRQ_SEL);  //if(FRQ_SEL == 1) ctr_freq = 8000, else ctr_freq = 4000
    E_COND_ADD(PO, PC, PC, 4);
    E_HEART_RYTHM_IMM(37500);           // ctr_freq = 8000
    E_HEART_RYTHM_IMM(18750);           // ctr_freq = 4000
    E_GOTO_REG(RA);
}


/*
 * EZH instruction code for QEI signal decoding, supporting two QEIs
 */
void ezh_cam_app (){
	E_NOP();
	E_NOP();
	E_PER_READ(R6, ARM2EZH);
 	//Align the value of R6 to word
	E_LSR(R6, R6, 2);
	E_LSL(R6, R6, 2);
	E_LDR(SP, R6, 0);//EZH stack initial
	E_LDR(R3, R6, 1);//R3 point to the store buffer in the RAM	
		
E_LABEL("init");
	E_LDR(CFS,PC,1); // Load CFS
	E_LDR(CFM,PC,1); // Load CFM
	E_ADD_IMM(PC,PC,1*4); //E_goto
	E_DCD_VAL (BS7(0)|BS6(0)|BS5(0)|BS4(0)|BS3(0)|BS2(2)|BS1(1)|BS0(0));   // Config source (C^D + C^D-)  where C^ is Clock rise, D- is Data inverted
	E_DCD_VAL (BS7(6)|BS6(6)|BS5(6)|BS4(6)|BS3(6)|BS2(BS_FALL)|BS1(BS_FALL)|BS0(BS_FALL)|(1<<0) ); // Config MUX    (C^D + C^D-)  where C^ is Clock rise, D- is Data inverted, enable OR 
	
	E_BCLR_IMM(GPD, GPD, 0); 
	E_BCLR_IMM(GPD, GPD, 1); 
	E_BCLR_IMM(GPD, GPD, 2); 
	E_BCLR_IMM(GPD, GPD, 3); 
	E_BCLR_IMM(GPD, GPD, 4); 
	E_BCLR_IMM(GPD, GPD, 5); 
	E_BCLR_IMM(GPD, GPD, 6); 
	E_BCLR_IMM(GPD, GPD, 7); 
	//E_BSET_IMM(GPD, GPD, 18); 
    E_BSET_IMM(GPD, GPD, EZH_CTR_b0);
    E_BSET_IMM(GPO, GPO, EZH_CTR_b0);
	
	E_LOAD_IMM(R2, 1);
	
E_LABEL("PCLK");
	E_ACC_VECTORED_HOLD(PC,(1<<2));     //EZH WILL STOP UNTIL THE OUTPUT OF LC IS 1
	E_AND_IMM(R0, GPI, 0xFF);
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
	E_GOSUB("VSYNC");//BS0
	E_GOSUB("HSYNC");//BS1
	E_STRB_POST(R3, R0, 1);  // data will be stored from GPI bottom byte to RAM
	E_STRB_POST(R5, R0, 1);  // data will be stored from GPI bottom byte to RAM	
	
	E_ACC_VECTORED_HOLD(PC,(1<<2));
	E_AND_IMM(R0, GPI, 0xFF);
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
	E_GOSUB("VSYNC");//BS0
	E_GOSUB("HSYNC");//BS1
	E_STRB_POST(R3, R0, 1);  // data will be stored from GPI bottom byte to RAM
	E_STRB_POST(R5, R0, 1);  // data will be stored from GPI bottom byte to RAM	
	
	E_ACC_VECTORED_HOLD(PC,(1<<2));
	E_AND_IMM(R0, GPI, 0xFF);
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
	E_GOSUB("VSYNC");//BS0
	E_GOSUB("HSYNC");//BS1
	E_STRB_POST(R3, R0, 1);  // data will be stored from GPI bottom byte to RAM
	//E_BTOG_IMM(GPO, GPO, 18);//BS2
    E_BTOG_IMM(GPO,GPO,EZH_CTR_b0);				//toggle the P0_18, used to measure the timming in logic device
	
	E_ACC_VECTORED_HOLD(PC,(1<<2));
	E_AND_IMM(R0, GPI, 0xFF);
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
	E_GOSUB("VSYNC");//BS0
	E_GOSUB("HSYNC");//BS1
	E_STRB_POST(R3, R0, 1);  // data will be stored from GPI bottom byte to RAM

	E_ACC_VECTORED_HOLD(PC,(1<<2));
	E_AND_IMM(R0, GPI, 0xFF);
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
	E_GOSUB("VSYNC");//BS0
	E_GOSUB("HSYNC");//BS1
	E_STRB_POST(R3, R0, 1);  // data will be stored from GPI bottom byte to RAM
	
	E_ACC_VECTORED_HOLD(PC,(1<<2));
	E_AND_IMM(R0, GPI, 0xFF);
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
	E_GOSUB("VSYNC");//BS0
	E_GOSUB("HSYNC");//BS1
	E_STRB_POST(R3, R0, 1);  // data will be stored from GPI bottom byte to RAM
	E_GOSUB("PCLK"); 
	
E_LABEL("VSYNC");
	E_BSET_IMM(CFM, CFM, 0); 			//clear the vector flag	
	E_LOAD_IMM(R2, 1);
	E_LOAD_IMM(R7, 0);
	
	E_BSET_IMM(CFM, CFM, 1); 			//enable HSYNC interrupt
	E_BSET_IMM(CFM, CFM, 2); 			//enable PCLK  interrupt	
	E_LDR(R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_LDR(R5, R6, 2);//R5 point to the AI buffer in the RAM	
	//E_BTOG_IMM(GPO,GPO,18);				//toggle the P0_18, used to measure the timming in logic device
    E_BTOG_IMM(GPO,GPO,EZH_CTR_b0);				//toggle the P0_18, used to measure the timming in logic device
	E_GOSUB("PCLK");
	
E_LABEL("HSYNC");

	E_BCLR_IMM(R3, R3, 0);
	E_BCLR_IMM(R3, R3, 1);
	E_SUB_IMM(R3, R3, 512);
	
	E_AND_IMM(R2, R2, 0x1FF);
	
	E_ADD_IMM(R7,R7, 1);
	E_XOR_IMMS(R0, R7, 1);
	E_COND_SUB_IMM(ZE, R5, R5, 172);
	E_XOR_IMMS(R0, R7, 2);
	E_COND_SUB_IMM(ZE, R5, R5, 428);
	E_XOR_IMMS(R0, R7, 3);
	E_COND_SUB_IMM(ZE, R5, R5, 428);
	E_COND_LOAD_IMM(ZE, R7, 0);
	
	E_LDR(R4, R6, 3);//R4 point to the AI buffer in the RAM		
	
	E_XOR_IMMS(R0, R2, (12*1));		
	E_COND_LOAD_IMM(ZE, R1, 1);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*2));		
	E_COND_LOAD_IMM(ZE, R1, 2);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*3));		
	E_COND_LOAD_IMM(ZE, R1, 3);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*4));		
	E_COND_LOAD_IMM(ZE, R1, 4);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*5));		
	E_COND_LOAD_IMM(ZE, R1, 5);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*6));		
	E_COND_LOAD_IMM(ZE, R1, 6);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*7));		
	E_COND_LOAD_IMM(ZE, R1, 7);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	
	E_XOR_IMMS(R0, R2, (12*8));		
	E_COND_LOAD_IMM(ZE, R1, 8);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*9));		
	E_COND_LOAD_IMM(ZE, R1, 9);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*10));		
	E_COND_LOAD_IMM(ZE, R1, 10);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*11));		
	E_COND_LOAD_IMM(ZE, R1, 11);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*12));		
	E_COND_LOAD_IMM(ZE, R1, 12);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*13));		
	E_COND_LOAD_IMM(ZE, R1, 13);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*14));		
	E_COND_LOAD_IMM(ZE, R1, 14);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*15));		
	E_COND_LOAD_IMM(ZE, R1, 15);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	
	E_XOR_IMMS(R0, R2, (12*16));		
	E_COND_LOAD_IMM(ZE, R1, 16);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*17));		
	E_COND_LOAD_IMM(ZE, R1, 17);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*18));		
	E_COND_LOAD_IMM(ZE, R1, 18);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*19));		
	E_COND_LOAD_IMM(ZE, R1, 19);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*20));		
	E_COND_LOAD_IMM(ZE, R1, 20);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*21));		
	E_COND_LOAD_IMM(ZE, R1, 21);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*22));		
	E_COND_LOAD_IMM(ZE, R1, 22);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*23));		
	E_COND_LOAD_IMM(ZE, R1, 23);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	
	E_XOR_IMMS(R0, R2, (12*24));		
	E_COND_LOAD_IMM(ZE, R1, 24);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*25));		
	E_COND_LOAD_IMM(ZE, R1, 25);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*26));		
	E_COND_LOAD_IMM(ZE, R1, 26);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*27));		
	E_COND_LOAD_IMM(ZE, R1, 27);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*28));		
	E_COND_LOAD_IMM(ZE, R1, 28);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*29));		
	E_COND_LOAD_IMM(ZE, R1, 29);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*30));		
	E_COND_LOAD_IMM(ZE, R1, 30);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (12*31));		
	E_COND_LOAD_IMM(ZE, R1, 31);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	
	E_BSET_IMM(CFM, CFM, 1); 			//clear the vector flag
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag			
	
	E_XOR_IMMS(R0, R2, (12*32));		
	E_COND_LOAD_IMM(ZE, R1, 32);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	E_COND_BCLR_IMM(ZE, CFM, CFM, 1); 			//disable HSYNC interrupt
	E_COND_BCLR_IMM(ZE, CFM, CFM, 2); 			//disable PCLK  interrupt	

	
	E_ADD_IMM(R2, R2, 1);
	//E_BTOG_IMM(GPO,GPO,18);				//toggle the P0_18, used to measure the timming in logic device
    E_BTOG_IMM(GPO,GPO,EZH_CTR_b0);				//toggle the P0_18, used to measure the timming in logic device
	E_GOSUB("PCLK");	
};

void EZH_cfgHandshake(bool _enable_handshake, bool _enable_event){
	int enable_handshake;
	int enable_event;
	enable_handshake = (_enable_handshake) ? 1 : 0;
	enable_event     = (_enable_event)     ? 1 : 0;
	MCX_EZH_ARCH_B0->EZHB_ARM2EZH |= (enable_handshake<<EZHB_HANDSHAKE_ENABLE) + (enable_event<<EZHB_HANDSHAKE_EVENT);
};

void EZH_Init(void *pPara){

    //bunny_build__relocate(&my_ezh_program[0],
    //            sizeof(my_ezh_program),
	//			(uint32_t)my_ezh_program, //start address of for_ezh_ram
    //            ezh_even_or_odd_app2
    //            );
	bunny_build(&my_ezh_program[0],
	                sizeof(my_ezh_program),
					ezh_cam_app
	                );

	MCX_EZH_ARCH_B0->EZHB_CTRL |= (0xC0DE0000 | (1<<EZHB_ENABLE_GPISYNCH));
    MCX_EZH_ARCH_B0->EZHB_ARM2EZH = (uint32_t)pPara;
	EZH_cfgHandshake(true,false);
}

void EZH_boot(void * pProgram) {
	MCX_EZH_ARCH_B0->EZHB_BOOT = (uint32_t) pProgram;
	MCX_EZH_ARCH_B0->EZHB_CTRL = 0xC0DE0011 | (0<<EZHB_MASK_RESP) |(0<<EZHB_ENABLE_AHBBUF) ; // BOOT
};

void EZH_Start(void){
	EZH_boot(my_ezh_program);
}


void EZH_SetExternalFlag(uint8_t flag)
{
    volatile uint32_t ezh_ctrl = (MCX_EZH_ARCH_B0->EZHB_CTRL & 0x0000FFFF);
    if (flag == 0) {
        ezh_ctrl &= ~(1 << EZHB_EXTERNAL_FLAG);
    } else {
        ezh_ctrl |= (1 << EZHB_EXTERNAL_FLAG);
    }
    MCX_EZH_ARCH_B0->EZHB_CTRL = (0xC0DE0000 | ezh_ctrl);
}
