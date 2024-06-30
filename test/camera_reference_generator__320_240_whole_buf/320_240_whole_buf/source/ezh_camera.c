/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
#include "fsl_ezh_armclang.h"
#include "ezh_camera.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ARM2EZH                0x33040
#define EZH2ARM                0x33044

#define EZH_CODE	__attribute__((section("EZH_CODE")))__attribute__ ((aligned (32))) 
#define EZH_DATA	__attribute__((section("EZH_DATA")))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void EZH_Camera_320240_Whole_Buf(void);
void EZH_Camera_320240_Div16_Buf(void);
void EZH_Camera_480320_Whole_Buf(void);
void EZH_Camera_320240_GrayScale_Div4_Buf(void);
void EZH_Camera_320240_GrayScale_Div16_Buf(void);
void EZH_Camera_384_384_Div16_Buf(void);
void EZH_Camera_320480_Whole_Buf(void);
/*!
 * @brief Parameter for camera
 */
typedef struct _smartdma_camera_param
{
	uint32_t *smartdma_stack;   /* user must allocate min 64bytes */
	uint32_t *p_buffer;         /* user must allocate size for pixel data */
	uint32_t *p_stripe_index;         /* user must allocate size for pixel data */
	uint32_t *p_buffer_ping_pong;         /* user must allocate size for pixel data */
} smartdma_camera_param_t;
/*******************************************************************************
 * Variables
 ******************************************************************************/
__attribute__((section(".ARM.__at_0x04000000"))) ezh_flexio_funcs_t g_ezh_api = {
    EZH_Camera_320240_Whole_Buf,
    EZH_Camera_320240_Div16_Buf,
		EZH_Camera_480320_Whole_Buf,
		EZH_Camera_320240_GrayScale_Div4_Buf,
		EZH_Camera_320240_GrayScale_Div16_Buf,
		EZH_Camera_384_384_Div16_Buf,
		EZH_Camera_320480_Whole_Buf,
};


	
/*******************************************************************************
 * Code
 ******************************************************************************/
/*
EZH_Camera_320_240_Whole_Buffer ,
the camera resolution must be 320*240, 
the camera must be set that the pclk is disapeared during HSYNC blocking.
the buffer is whole resolution size, 320*249*2=150K bytes

RGB565 format
R0:temporary variable
R1:temporary variable
R2:reserved
R3:camera buffer address
R4:reserved
R5:reserved
R6:para base address
R7:reserved
*/
void EZH_CODE EZH_Camera_320240_Whole_Buf(void)
{
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/

	
	E_PER_READ(R6, ARM2EZH);
 	//Align the value of R6 to word
	E_LSR(R6, R6, 2);
	E_LSL(R6, R6, 2);
	E_LDR(SP, R6, 0);//EZH stack initial
	E_LDR(R3, R6, 1);//R3 point to the store buffer in the RAM	
		
E_LABEL("init_0");
	E_LDR(CFS,PC,1); // Load CFS
	E_LDR(CFM,PC,1); // Load CFM
	E_ADD_IMM(PC,PC,1*4); //E_goto
	E_DCD_VAL (BS7(0)|BS6(0)|BS5(0)|BS4(0)|BS3(0)|BS2(1)|BS1(0)|BS0(2));   // Config source (C^D + C^D-)  where C^ is Clock rise, D- is Data inverted
	E_DCD_VAL (BS7(6)|BS6(6)|BS5(6)|BS4(6)|BS3(6)|BS2(BS_FALL)|BS1(BS_FALL)|BS0(BS_FALL)|(1<<2) ); // Config MUX    (C^D + C^D-)  where C^ is Clock rise, D- is Data inverted, enable OR 
	
	E_BCLR_IMM(GPD, GPD, 0); 
	E_BCLR_IMM(GPD, GPD, 1); 
	E_BCLR_IMM(GPD, GPD, 2); 
	E_BCLR_IMM(GPD, GPD, 3); 
	E_BCLR_IMM(GPD, GPD, 4); 
	E_BCLR_IMM(GPD, GPD, 5); 
	E_BCLR_IMM(GPD, GPD, 6); 
	E_BCLR_IMM(GPD, GPD, 7); 
	E_BSET_IMM(GPD, GPD, 13); 

	
	E_LOAD_IMM(R1, 0xFF);
E_LABEL("PCLK_0");
	E_ACC_VECTORED_HOLD_LV(PC,(1<<0));
	E_STRB_POST(R3, GPI, 1);  			// data will be stored from GPI bottom byte to RAM		
	E_BSET_IMM(CFM, CFM, 0); 			//clear the vector flag		
	
	E_SUB_IMMS(PC, PC, 4*5);//BS0
	E_BTOG_IMM(GPO,GPO,13);				//toggle the P0_18, used to measure the timming in logic device
	E_NOP;
	E_NOP;
	
	E_GOSUB(VSYNC_0);//BS1
	E_NOP;
	E_NOP;
	E_NOP;
	
	E_GOSUB(HSYNC_0);//BS2
	E_NOP;
	E_NOP;
	E_NOP;

	
//	E_LABEL("PCLK_0");
//	E_ACC_VECTORED_HOLD(PC,(1<<2));
//	E_LSR_AND(R0, R1, GPI, 0);
//	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
//	E_GOSUB(VSYNC_0);//BS0
//	E_GOSUB(HSYNC_0);//BS1
//	E_SUB_IMMS(PC, PC, 4*7);
//	E_STRB_POST(R3, R0, 1);  			// data will be stored from GPI bottom byte to RAM	
//	E_BTOG_IMM(GPO,GPO,13);				//toggle the P0_18, used to measure the timming in logic device
//	E_GOSUB(PCLK_0); 
	
E_LABEL("VSYNC_0");
	E_BSET_IMM(CFM, CFM, 0); 			//clear the VSYNC vector flag	
	E_BSET_IMM(CFM, CFM, 1); 			//enable HSYNC interrupt
	E_BSET_IMM(CFM, CFM, 2); 			//enable PCLK  interrupt	
	E_LDR(R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_BTOG_IMM(GPO,GPO,13);				//toggle the P0_18, used to measure the timming in logic device
	E_INT_TRIGGER(0x11); // interrupt and told ARM data is ready	
	E_GOSUB(PCLK_0);
	
E_LABEL("HSYNC_0");
	E_BCLR_IMM(R3, R3, 0);
	E_BCLR_IMM(R3, R3, 1);
	E_BSET_IMM(CFM, CFM, 0); 			//clear the vector flag
	E_BSET_IMM(CFM, CFM, 1); 			//clear the vector flag			
	E_BTOG_IMM(GPO,GPO,13);				//toggle the P0_18, used to measure the timming in logic device
	E_GOSUB(PCLK_0);	
}

void EZH_CODE EZH_Camera_320240_Div16_Buf(void)
{
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	E_PER_READ(R6, ARM2EZH);
 	//Align the value of R6 to word
	E_LSR(R6, R6, 2);
	E_LSL(R6, R6, 2);
	E_LDR(SP, R6, 0);//EZH stack initial
	E_LDR(R3, R6, 3);//R3 point to the store ping buffer in the RAM	
		
E_LABEL("init_1");
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
	E_BSET_IMM(GPD, GPD, 18); 
	
//	E_LABEL("teset");
//		E_BTOG_IMM(GPO, GPO, 18); 
//	E_GOSUB(teset); 


	E_LOAD_IMM(R2, 1);
	E_LOAD_IMM(R5, 0);

E_LABEL("PCLK_1");
	E_ACC_VECTORED_HOLD(PC,(1<<2));
	E_AND_IMM(R0, GPI, 0xff);
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
	E_GOSUB(VSYNC_1);//BS0
	E_GOSUB(HSYNC_1);//BS1
	E_SUB_IMMS(PC, PC, 4*7);
	E_STRB_POST(R3, R0, 1);  // data will be stored from GPI bottom byte to RAM
	E_BTOG_IMM(GPO,GPO,18);				//toggle the P0_18, used to measure the timming in logic device
	//	E_GOSUB(PCLK_1); 
	
E_LABEL("VSYNC_1");
	E_BSET_IMM(CFM, CFM, 0); 			//clear the vector flag	
	E_LOAD_IMM(R2, 1);
	E_LOAD_IMM(R5, 0);
	
	E_BSET_IMM(CFM, CFM, 1); 			//enable HSYNC interrupt
	E_BSET_IMM(CFM, CFM, 2); 			//enable PCLK  interrupt	
	E_LDR(R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_BTOG_IMM(GPO,GPO,18);				//toggle the P0_18, used to measure the timming in logic device
	E_GOSUB(PCLK_1);
	
E_LABEL("HSYNC_1");

	E_BCLR_IMM(R3, R3, 0);
	E_BCLR_IMM(R3, R3, 1);
	E_LOAD_IMM(R5, 0);
	
	E_AND_IMM(R2, R2, 0x1FF);

	E_LDR(R4, R6, 2);//R4 point to the AI buffer in the RAM		
	
	E_XOR_IMMS(R0, R2, (15*1));		
	E_COND_LOAD_IMM(ZE, R1, 0);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*2));		
	E_COND_LOAD_IMM(ZE, R1, 1);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*3));		
	E_COND_LOAD_IMM(ZE, R1, 2);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*4));		
	E_COND_LOAD_IMM(ZE, R1, 3);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*5));		
	E_COND_LOAD_IMM(ZE, R1, 4);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*6));		
	E_COND_LOAD_IMM(ZE, R1, 5);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*7));		
	E_COND_LOAD_IMM(ZE, R1, 6);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	
	E_XOR_IMMS(R0, R2, (15*8));		
	E_COND_LOAD_IMM(ZE, R1, 7);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*9));		
	E_COND_LOAD_IMM(ZE, R1, 8);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*10));		
	E_COND_LOAD_IMM(ZE, R1, 9);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	

	E_XOR_IMMS(R0, R2, (15*11));		
	E_COND_LOAD_IMM(ZE, R1, 10);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	
	E_XOR_IMMS(R0, R2, (15*12));		
	E_COND_LOAD_IMM(ZE, R1, 11);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*13));		
	E_COND_LOAD_IMM(ZE, R1, 12);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*14));		
	E_COND_LOAD_IMM(ZE, R1, 13);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready		
	

	E_XOR_IMMS(R0, R2, (15*15));		
	E_COND_LOAD_IMM(ZE, R1, 14);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_BSET_IMM(CFM, CFM, 1); 			//clear the vector flag
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag			
	
	E_XOR_IMMS(R0, R2, (15*16));		
	E_COND_LOAD_IMM(ZE, R1, 15);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	E_COND_BCLR_IMM(ZE, CFM, CFM, 1); 			//disable HSYNC interrupt
	E_COND_BCLR_IMM(ZE, CFM, CFM, 2); 			//disable PCLK  interrupt	
		
	
	E_ADD_IMM(R2, R2, 1);
	E_BTOG_IMM(GPO,GPO,18);				//toggle the P0_18, used to measure the timming in logic device
	E_GOSUB(PCLK_1);		

}
void EZH_CODE EZH_Camera_480320_Whole_Buf(void)
{
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	
	E_PER_READ(R6, ARM2EZH);
 	//Align the value of R6 to word
	E_LSR(R6, R6, 2);
	E_LSL(R6, R6, 2);
	E_LDR(SP, R6, 0);//EZH stack initial
	E_LDR(R3, R6, 1);//R3 point to the store buffer in the RAM	
		
E_LABEL("init_480320");
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
	E_BSET_IMM(GPD, GPD, 18); 
	
	E_LOAD_IMM(R1, 0xFF);
E_LABEL("PCLK_480320");
	E_ACC_VECTORED_HOLD(PC,(1<<2));
	E_LSR_AND(R0, R1, GPI, 0);
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
	E_GOSUB(VSYNC_480320);//BS0
	E_GOSUB(HSYNC_480320);//BS1
	E_SUB_IMMS(RA, R2, 960);
	E_COND_STRB_POST(NE, R3, R0, 1);  			// data will be stored from GPI bottom byte to RAM	
	E_SUB_IMMS(PC, PC, 9*4);
	E_COND_BTOG_IMM(NE, GPO, GPO, 18);				//toggle the P0_18, used to measure the timming in logic device
	E_ADD_IMM(R2, R2, 1);
//	E_GOSUB(PCLK_480320); 
	
E_LABEL("VSYNC_480320");
	E_BSET_IMM(CFM, CFM, 0); 			//clear the VSYNC vector flag	
	E_BSET_IMM(CFM, CFM, 1); 			//enable HSYNC interrupt
	E_LDR(R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_LOAD_IMM(R2, 0);
	E_LOAD_IMM(R4, 0);
	E_BTOG_IMM(GPO,GPO,18);				//toggle the P0_18, used to measure the timming in logic device
	E_PER_WRITE(R0,EZH2ARM);   	  // interrupt and told ARM data is ready	
	E_GOSUB(PCLK_480320);
	
E_LABEL("HSYNC_480320");
//	E_BCLR_IMM(R3, R3, 0);
//	E_BCLR_IMM(R3, R3, 1);
	E_BSET_IMM(CFM, CFM, 1); 			//clear the vector flag
	E_ADD_IMM(R4, R4, 1);
	E_SUB_IMMS(RA, R4, 80);
	E_COND_BSET_IMM(AZ, CFM, CFM, 2); 			//clear the vector flag	
	
	E_SUB_IMMS(RA, R4, 400);
	E_COND_BCLR_IMM(AZ, CFM, CFM, 2); 			//clear the vector flag		
	
	E_LOAD_IMM(R2, 0);
	E_GOSUB(PCLK_480320);	
}
/*******************************************************************************
 * Code
 ******************************************************************************/
///*!
// * @brief Parameter for camera
// */
//typedef struct _smartdma_camera_param
//{
//	uint32_t *smartdma_stack;   /* user must allocate min 64bytes */
//	uint32_t *p_buffer;         /* user must allocate size for pixel data */
//	uint32_t *p_stripe_index;         /* user must allocate size for pixel data */
//	uint32_t *p_buffer_ping_pong;         /* user must allocate size for pixel data */
//} smartdma_camera_param_t;


/*
EZH_Camera_320240_GrayScale_Div4_Buf ,
the camera resolution must be 320*240, 
the camera must be set that the pclk is disapeared during HSYNC blocking.
the buffer is 1/4  resolution size, both of ping-pong buffer size are 320*60*2=75K bytes

the output of camera format is RGB565, SmartDMA just store Part Y of YUV
R0:temporary variable
R1:temporary variable
R2:reserved
R3:camera buffer address
R4:reserved
R5:reserved
R6:para base address
R7:reserved
*/
void EZH_CODE EZH_Camera_320240_GrayScale_Div4_Buf(void)
{
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	
	E_PER_READ(R6, ARM2EZH);
 	//Align the value of R6 to word
	E_LSR(R6, R6, 2);
	E_LSL(R6, R6, 2);
	E_LDR(SP, R6, 0);//EZH stack initial
	E_LDR(R3, R6, 3);//R3 point to the store buffer in the RAM	
		
E_LABEL("init_Div4");
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
	E_BSET_IMM(GPD, GPD, 18); 
	
	E_LOAD_IMM(R5, 0xFF);
E_LABEL("PCLK_Div4");
	E_ACC_VECTORED_HOLD(PC,(1<<2));
	E_LSR_AND(R0, R5, GPI, 0);
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
	E_GOSUB(VSYNC_Div4);//BS0
	E_GOSUB(HSYNC_Div4);//BS1
	
	E_ACC_VECTORED_HOLD(PC,(1<<2));
	E_LSR_AND(R0, R5, GPI, 0);
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
	E_GOSUB(VSYNC_Div4);//BS0
	E_GOSUB(HSYNC_Div4);//BS1
	E_STRB_POST(R3, R0, 1);  			// data will be stored from GPI bottom byte to RAM	
	E_GOSUB(PCLK_Div4); 

E_LABEL("VSYNC_Div4");
	E_BSET_IMM(CFM, CFM, 0); 			//clear the VSYNC vector flag	
	E_LOAD_IMM(R2, 1);
	
	E_BSET_IMM(CFM, CFM, 1); 			//enable HSYNC interrupt
	E_BSET_IMM(CFM, CFM, 2); 			//enable PCLK  interrupt	
	E_LDR(R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_BTOG_IMM(GPO,GPO,18);				//toggle the P0_18, used to measure the timming in logic device
	E_GOSUB(PCLK_Div4);
	
E_LABEL("HSYNC_Div4");

	E_BCLR_IMM(R3, R3, 0);
	E_BCLR_IMM(R3, R3, 1);	
	E_AND_IMM(R2, R2, 0x1FF);
	E_LDR(R4, R6, 2);//R4 point to the index buffer in the RAM
	
	E_XOR_IMMS(R0, R2, (60*1));		
	E_COND_LOAD_IMM(ZE, R1, 0);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (60*2));		
	E_COND_LOAD_IMM(ZE, R1, 1);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (60*3));		
	E_COND_LOAD_IMM(ZE, R1, 2);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_BSET_IMM(CFM, CFM, 1); 			//clear the vector flag
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag			
	
	E_XOR_IMMS(R0, R2, (60*4));		
	E_COND_LOAD_IMM(ZE, R1, 3);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	E_COND_BCLR_IMM(ZE, CFM, CFM, 1); 			//disable HSYNC interrupt
	E_COND_BCLR_IMM(ZE, CFM, CFM, 2); 			//disable PCLK  interrupt	
	
	E_ADD_IMM(R2, R2, 1);
	E_BTOG_IMM(GPO,GPO,18);				//toggle the P0_18, used to measure the timming in logic device
	E_GOSUB(PCLK_Div4);			
}
/*
EZH_Camera_320240_GrayScale_Div16_Buf ,
the camera resolution must be 320*240, 
the camera must be set that the pclk is disapeared during HSYNC blocking.
the buffer is 1/16  resolution size, both of ping-pong buffer size are 320*15*2=9.3K bytes

the output of camera format is RGB565, SmartDMA just store Part Y of YUV
R0:temporary variable
R1:temporary variable
R2:reserved
R3:camera buffer address
R4:reserved
R5:reserved
R6:para base address
R7:reserved
*/
void EZH_CODE EZH_Camera_320240_GrayScale_Div16_Buf(void)
{
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	
	E_PER_READ(R6, ARM2EZH);
 	//Align the value of R6 to word
	E_LSR(R6, R6, 2);
	E_LSL(R6, R6, 2);
	E_LDR(SP, R6, 0);//EZH stack initial
	E_LDR(R3, R6, 3);//R3 point to the store ping buffer in the RAM	
		
E_LABEL("init_gs_16");
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
	E_BSET_IMM(GPD, GPD, 18); 
	
//	E_LABEL("teset");
//		E_BTOG_IMM(GPO, GPO, 18); 
//	E_GOSUB(teset); 


	E_LOAD_IMM(R5, 0xFF);

E_LABEL("PCLK_gs_16");
	E_ACC_VECTORED_HOLD(PC,(1<<2));
	E_LSR_AND(R0, R5, GPI, 0);
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
	E_GOSUB(VSYNC_gs_16);//BS0
	E_GOSUB(HSYNC_gs_16);//BS1
		
	E_ACC_VECTORED_HOLD(PC,(1<<2));
	E_LSR_AND(R0, R5, GPI, 0);
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
	E_GOSUB(VSYNC_gs_16);//BS0
	E_GOSUB(HSYNC_gs_16);//BS1	
	E_STRB_POST(R3, R0, 1);  // data will be stored from GPI bottom byte to RAM
	E_GOSUB(PCLK_gs_16); 
	

E_LABEL("VSYNC_gs_16");
	E_BSET_IMM(CFM, CFM, 0); 			//clear the vector flag	
	E_LOAD_IMM(R2, 1);
	
	E_BSET_IMM(CFM, CFM, 1); 			//enable HSYNC interrupt
	E_BSET_IMM(CFM, CFM, 2); 			//enable PCLK  interrupt	
	E_LDR(R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_BTOG_IMM(GPO,GPO,18);				//toggle the P0_18, used to measure the timming in logic device
	E_GOSUB(PCLK_gs_16);
	
E_LABEL("HSYNC_gs_16");

	E_BCLR_IMM(R3, R3, 0);
	E_BCLR_IMM(R3, R3, 1);
	E_AND_IMM(R2, R2, 0x1FF);
	E_LDR(R4, R6, 2);//R4 point to the AI buffer in the RAM		
	
	E_XOR_IMMS(R0, R2, (15*1));		
	E_COND_LOAD_IMM(ZE, R1, 0);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*2));		
	E_COND_LOAD_IMM(ZE, R1, 1);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*3));		
	E_COND_LOAD_IMM(ZE, R1, 2);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*4));		
	E_COND_LOAD_IMM(ZE, R1, 3);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*5));		
	E_COND_LOAD_IMM(ZE, R1, 4);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*6));		
	E_COND_LOAD_IMM(ZE, R1, 5);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*7));		
	E_COND_LOAD_IMM(ZE, R1, 6);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	
	E_XOR_IMMS(R0, R2, (15*8));		
	E_COND_LOAD_IMM(ZE, R1, 7);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*9));		
	E_COND_LOAD_IMM(ZE, R1, 8);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*10));		
	E_COND_LOAD_IMM(ZE, R1, 9);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	

	E_XOR_IMMS(R0, R2, (15*11));		
	E_COND_LOAD_IMM(ZE, R1, 10);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	
	E_XOR_IMMS(R0, R2, (15*12));		
	E_COND_LOAD_IMM(ZE, R1, 11);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*13));		
	E_COND_LOAD_IMM(ZE, R1, 12);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (15*14));		
	E_COND_LOAD_IMM(ZE, R1, 13);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready		
	

	E_XOR_IMMS(R0, R2, (15*15));		
	E_COND_LOAD_IMM(ZE, R1, 14);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_BSET_IMM(CFM, CFM, 1); 			//clear the vector flag
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag			
	
	E_XOR_IMMS(R0, R2, (15*16));		
	E_COND_LOAD_IMM(ZE, R1, 15);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	E_COND_BCLR_IMM(ZE, CFM, CFM, 1); 			//disable HSYNC interrupt
	E_COND_BCLR_IMM(ZE, CFM, CFM, 2); 			//disable PCLK  interrupt	
		
	
	E_ADD_IMM(R2, R2, 1);
	E_BTOG_IMM(GPO,GPO,18);				//toggle the P0_18, used to measure the timming in logic device
	E_GOSUB(PCLK_gs_16);		

}
/***********************************************************************************************
640 = 128 + 384 + 128 = 512 + 128,
480 = 48  + 384 + 48  = 432 + 48,

EZH_Camera_320240_GrayScale_Div16_Buf ,
the camera resolution must be 320*240, 
the camera must be set that the pclk is disapeared during HSYNC blocking.
the buffer is 1/16  resolution size, both of ping-pong buffer size are 320*15*2=9.3K bytes

the output of camera format is RGB565, SmartDMA just store Part Y of YUV
R0:temporary variable
R1:temporary variable
R2:reserved
R3:camera buffer address
R4:reserved
R5:reserved
R6:para base address
R7:reserved
*/
#define WIDTH 24
void EZH_CODE EZH_Camera_384_384_Div16_Buf(void)
{
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	
	E_PER_READ(R6, ARM2EZH);
 	//Align the value of R6 to word
	E_LSR(R6, R6, 2);
	E_LSL(R6, R6, 2);
	E_LDR(SP, R6, 0);//EZH stack initial
	E_LDR(R3, R6, 3);//R3 point to the store ping buffer in the RAM	
		
E_LABEL("init_384_384_div16");
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
	E_BSET_IMM(GPD, GPD, 18); 
	
//	E_LABEL("teset");
//		E_BTOG_IMM(GPO, GPO, 18); 
//	E_GOSUB(teset); 


	E_LOAD_IMM(R5, 0xFF);

E_LABEL("PCLK_384_384_div16");
	E_ACC_VECTORED_HOLD(PC,(1<<2));
	E_LSR_AND(R0, R5, GPI, 0);
//	E_LOAD_IMM(R0, 0xff);
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
	E_GOSUB(VSYNC_384_384_div16);//BS0
	E_GOSUB(HSYNC_384_384_div16);//BS1
	E_SUB_IMMS(RA, R7, 384*2);
	E_COND_STRB_POST(ZB, R3, R0, 1);  // data will be stored from GPI bottom byte to RAM
	E_SUB_IMMS(PC, PC, 9*4);
	E_ADD_IMM(R7, R7, 1);
	E_BTOG_IMM(GPO,GPO,18);				//toggle the P0_18, used to measure the timming in logic device


E_LABEL("VSYNC_384_384_div16");
	E_BSET_IMM(CFM, CFM, 0); 			//clear the vector flag	
	E_LOAD_IMM(R2, 1);
	E_LOAD_IMM(R7, 0);
	
	E_BSET_IMM(CFM, CFM, 1); 			//enable HSYNC interrupt
	E_BSET_IMM(CFM, CFM, 2); 			//enable PCLK  interrupt	
	E_LDR(R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_BTOG_IMM(GPO,GPO,18);				//toggle the P0_18, used to measure the timming in logic device
	E_GOSUB(PCLK_384_384_div16);
	
E_LABEL("HSYNC_384_384_div16");

	E_LOAD_IMM(R7, 0);
	E_BCLR_IMM(R3, R3, 0);
	E_BCLR_IMM(R3, R3, 1);
	E_AND_IMM(R2, R2, 0x1FF);
	E_LDR(R4, R6, 2);									 //R4 point to the g_stripe_index in the RAM		
	
	E_XOR_IMMS(R0, R2, (WIDTH*1));		
	E_COND_LOAD_IMM(ZE, R1, 0);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (WIDTH*2));		
	E_COND_LOAD_IMM(ZE, R1, 1);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (WIDTH*3));		
	E_COND_LOAD_IMM(ZE, R1, 2);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (WIDTH*4));		
	E_COND_LOAD_IMM(ZE, R1, 3);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (WIDTH*5));		
	E_COND_LOAD_IMM(ZE, R1, 4);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (WIDTH*6));		
	E_COND_LOAD_IMM(ZE, R1, 5);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (WIDTH*7));		
	E_COND_LOAD_IMM(ZE, R1, 6);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	
	E_XOR_IMMS(R0, R2, (WIDTH*8));		
	E_COND_LOAD_IMM(ZE, R1, 7);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (WIDTH*9));		
	E_COND_LOAD_IMM(ZE, R1, 8);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (WIDTH*10));		
	E_COND_LOAD_IMM(ZE, R1, 9);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	

	E_XOR_IMMS(R0, R2, (WIDTH*11));		
	E_COND_LOAD_IMM(ZE, R1, 10);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	
	E_XOR_IMMS(R0, R2, (WIDTH*12));		
	E_COND_LOAD_IMM(ZE, R1, 11);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (WIDTH*13));		
	E_COND_LOAD_IMM(ZE, R1, 12);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_XOR_IMMS(R0, R2, (WIDTH*14));		
	E_COND_LOAD_IMM(ZE, R1, 13);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready		
	

	E_XOR_IMMS(R0, R2, (WIDTH*15));		
	E_COND_LOAD_IMM(ZE, R1, 14);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	

	E_BSET_IMM(CFM, CFM, 1); 			//clear the vector flag
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag			
	
	E_XOR_IMMS(R0, R2, (WIDTH*16));		
	E_COND_LOAD_IMM(ZE, R1, 15);
	E_COND_STR(ZE, R4, R1, 0);
	E_COND_LDR(ZE, R3, R6, 3);							//R3 point to the store buffer in the RAM	
	E_COND_PER_WRITE(ZE, R0,EZH2ARM);   // interrupt and told ARM data is ready	
	E_COND_BCLR_IMM(ZE, CFM, CFM, 1); 			//disable HSYNC interrupt
	E_COND_BCLR_IMM(ZE, CFM, CFM, 2); 			//disable PCLK  interrupt	
	
	E_ADD_IMM(R2, R2, 1);
	E_BTOG_IMM(GPO,GPO,18);				//toggle the P0_18, used to measure the timming in logic device
	E_GOSUB(PCLK_384_384_div16);		

}


void EZH_CODE EZH_Camera_320480_Whole_Buf(void)
{
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	E_NOP;/*pattern*/
	
	E_PER_READ(R6, ARM2EZH);
 	//Align the value of R6 to word
	E_LSR(R6, R6, 2);
	E_LSL(R6, R6, 2);
	E_LDR(SP, R6, 0);//EZH stack initial
	E_LDR(R3, R6, 1);//R3 point to the store buffer in the RAM	
		
E_LABEL("init_320480");
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
	E_BSET_IMM(GPD, GPD, 18); 
	
	E_LOAD_IMM(R1, 0xFF);
E_LABEL("PCLK_320480");
	E_ACC_VECTORED_HOLD(PC,(1<<2));
	E_LSR_AND(R0, R1, GPI, 0);
	E_BSET_IMM(CFM, CFM, 2); 			//clear the vector flag	
	E_GOSUB(VSYNC_320480);//BS0
	E_GOSUB(HSYNC_320480);//BS1
	E_SUB_IMMS(RA, R2, 640);
	E_COND_STRB_POST(NE, R3, R0, 1);  			// data will be stored from GPI bottom byte to RAM	
	E_SUB_IMMS(PC, PC, 9*4);
	E_COND_BTOG_IMM(NE, GPO, GPO, 18);				//toggle the P0_18, used to measure the timming in logic device
	E_ADD_IMM(R2, R2, 1);
//	E_GOSUB(PCLK_320480); 
	
E_LABEL("VSYNC_320480");
	E_BSET_IMM(CFM, CFM, 0); 			//clear the VSYNC vector flag	
	E_BSET_IMM(CFM, CFM, 1); 			//enable HSYNC interrupt
	E_LDR(R3, R6, 1);							//R3 point to the store buffer in the RAM	
	E_LOAD_IMM(R2, 0);
	E_LOAD_IMM(R4, 0);
	E_BTOG_IMM(GPO,GPO,18);				//toggle the P0_18, used to measure the timming in logic device
	E_PER_WRITE(R0,EZH2ARM);   	  // interrupt and told ARM data is ready	
	E_GOSUB(PCLK_320480);
	
E_LABEL("HSYNC_320480");
//	E_BCLR_IMM(R3, R3, 0);
//	E_BCLR_IMM(R3, R3, 1);
	E_BSET_IMM(CFM, CFM, 1); 			//clear the vector flag
	E_ADD_IMM(R4, R4, 1);
	E_SUB_IMMS(RA, R4, 80);
	E_COND_BSET_IMM(AZ, CFM, CFM, 2); 			//clear the vector flag	
	
	E_SUB_IMMS(RA, R4, 560);
	E_COND_BCLR_IMM(AZ, CFM, CFM, 2); 			//clear the vector flag		
	
	E_LOAD_IMM(R2, 0);
	E_GOSUB(PCLK_320480);	
}
int main(void)
{
    while (1)
    {

    }
}