#include "bunny_build__targets.h"
#include "bunny_build__config.h"

#include "stdint.h"
#include "string.h"
#include "stdbool.h"

#ifndef _BUNNY_BUILD_H_
#define _BUNNY_BUILD_H_


#ifdef __cplusplus
extern "C" {
#endif

#ifndef VT100_ESC
#define VT100_ESC                  "\x1b"
#endif

#ifndef VT100_CSI
#define VT100_CSI                  "\x1b["
#endif

#ifndef VT100_RED
#define VT100_RED                  VT100_CSI"31;40m"
#endif

#ifndef VT100_GREEN
#define VT100_GREEN                VT100_CSI"32;40m"
#endif

#ifndef VT100_YELLOW
#define VT100_YELLOW               VT100_CSI"33;40m"
#endif

#ifndef VT100_BLUE
#define VT100_BLUE                 VT100_CSI"34;40m"
#endif

#ifndef VT100_MAGENTA
#define VT100_MAGENTA              VT100_CSI"35;40m"
#endif

#ifndef VT100_CYAN
#define VT100_CYAN                 VT100_CSI"36;40m"
#endif

#ifndef VT100_WHITE
#define VT100_WHITE                VT100_CSI"37;40m"
#endif

#ifndef VT100_DEFAULT
#define VT100_DEFAULT              VT100_WHITE
#endif


#ifndef BUNNY_BUILD_PRINTF
	#error "Please set BUNNY_BUILD_PRINTF to something in bunny_build__config.h..."
#endif


#ifndef BUNNY_BUILD_MAX_LABELS				 
	#error "Please set BUNNY_BUILD_MAX_LABELS to something in bunny_build__config.h..."
#endif


#ifndef LPC_EZH_ARCH_B_CON_BASE
	#error "Please set LPC_EZH_ARCH_B_CON_BASE to an option in bunny_build__targets.h  in the bunny_build__config.h"
		//	#define LPC_EZH_ARCH_B_CON_BASE		LPC_EZH_ARCH_B_CON_BASE__MCX
#endif

#ifndef ARM2EZH
#define ARM2EZH						(LPC_EZH_ARCH_B_CON_BASE   + 0x20)
#endif

#ifndef EZH2ARM
#define EZH2ARM						(LPC_EZH_ARCH_B_CON_BASE   + 0x24)
#endif

#ifndef EZHBREAKADDR
#define EZHBREAKADDR				(LPC_EZH_ARCH_B_CON_BASE   + 0x10)
#endif

#ifndef EZHBREAKVECT
#define EZHBREAKVECT				(LPC_EZH_ARCH_B_CON_BASE   + 0x14)
#endif

#ifndef LPC_EZH_ARCH_B0
#define LPC_EZH_ARCH_B0             ((EZH_ARCH_B_CON_Type *)     LPC_EZH_ARCH_B_CON_BASE)
#endif



#ifdef __cplusplus
#define   __I     volatile             /*!< Defines 'read only' permissions */
#else
#define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define   __O     volatile             /*!< Defines 'write only' permissions */
#define   __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define   __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define   __OM     volatile            /*! Defines 'write only' structure member permissions */
#define   __IOM    volatile            /*! Defines 'read / write' structure member permissions */



#define EZH_INPUT_SOURCE_0				0
#define EZH_INPUT_SOURCE_1				1
#define EZH_INPUT_SOURCE_2				2
#define EZH_INPUT_SOURCE_3				3
#define EZH_INPUT_SOURCE_4				4
#define EZH_INPUT_SOURCE_5				5
#define EZH_INPUT_SOURCE_6				6
#define EZH_INPUT_SOURCE_7				7


#define EZHB_DISABLE_EMERGENCY_BIT		8

#define EZHB_HANDSHAKE_EVENT			0
#define EZHB_HANDSHAKE_ENABLE			1
#define EZHB_EXTERNAL_FLAG				1

#define EZHB_MASK_RESP					2
#define EZHB_ENABLE_AHBBUF				3
#define EZHB_ENABLE_GPISYNCH			4

typedef struct {
		__IO uint32_t     EZHB_BOOT;
		__IO uint32_t     EZHB_CTRL;
		__I  uint32_t     EZHB_PC;
		__I  uint32_t     EZHB_SP;
		__IO uint32_t     EZHB_BREAK_ADDR;
		__IO uint32_t     EZHB_BREAK_VECT;
		__IO uint32_t     EZHB_EMER_VECT;
		__IO uint32_t     EZHB_EMER_SEL;
		__IO uint32_t     EZHB_ARM2EZH;
		__IO uint32_t     EZHB_EZH2ARM;
		__IO uint32_t     EZHB_PENDTRAP;  ///< Note : only available on versions 1.2 of EZH_dual_subsys or version 1.0.8 of EZH_arch_B_integration.v                        
	} EZH_ARCH_B_CON_Type;


#define R0              0x00
#define R1              0x01
#define R2              0x02
#define R3              0x03
#define R4              0x04
#define R5              0x05
#define R6              0x06
#define R7              0x07
#define GPO				0x08
#define GPD      		0x09
#define CFS			    0x0a
#define CFM	            0x0b
#define SP              0x0c
#define PC              0x0d
#define GPI             0x0e
#define RA              0x0f

	// Conditional Flags
#define  EU				0x0
#define  ZE				0x1
#define  NZ				0x2
#define  PO				0x3
#define  NE				0x4
#define  AZ				0x5
#define  ZB				0x6
#define  CA				0x7
#define  NC				0x8
#define  CZ				0x9
#define  SPO			0xa
#define  SNE			0xb
#define  NBS			0xc
#define  NEX			0xd
#define  BS				0xe
#define  EX				0xf
#define  UNS			0xa
#define  NZS			0xb
#define  VECT0			0x1
#define  VECT1			0x2
#define  VECT2			0x4
#define  VECT3			0x8
#define  VECT4			0x10
#define  VECT5			0x20
#define  VECT6			0x40
#define  VECT7			0x80

// Bit Slice Mux cfg
#define BS_1			0
#define BS_RISE			1
#define BS_FALL			2
#define BS_CHANGE		3
#define BS_SIG			4
#define BS_SIGN			5
#define BS_0			6
#define BS_EVENT		7

#define BS0(c)			(c<<8)
#define BS1(c)			(c<<11)
#define BS2(c)			(c<<14)
#define BS3(c)			(c<<17)
#define BS4(c)			(c<<20)
#define BS5(c)			(c<<23)
#define BS6(c)			(c<<26)
#define BS7(c)			(c<<29)


// Size verification mask

#define A21_MASK	0xFFE00000


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      EZH ARCH B
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	typedef struct
	{

		const char* label;
		uint32_t address;

	} bunny_build__label_t;

	typedef enum
	{

		bunny_build_label__ok,
		bunny_build_label__out_of_mem,
		bunny_build_label__exists

	}bunny_build_label__result_t;


	extern uint32_t* bunny_build__out;
	extern uint32_t   bunny_build__idx;
	extern bunny_build__label_t bunny_build__labels[BUNNY_BUILD_MAX_LABELS];
	extern uint32_t   bunny_build__base_address;
	extern uint32_t   bunny_build__pass_num;


	/*
		Adds a label to the bunny_build storage.  Also checks if already exists

		Pass in a pointer to get the resolved address.

	*/
	bunny_build_label__result_t bunny_build__add_label(const char* label, uint32_t* resolved_address);


	/*
		Returns true if label exists and stuffs it in the address pointer location
		returns false if we haven't seen this label.
	*/

	bool bunny_build__label_get_address(const char* label, uint32_t* Address);


	/*

		This function is intended to be used on a host environment relocate the base address of the program

		Pass a pointer of where to store ezh program
		Pass a base address of where the program will live.
			If running on the target, this should be the same address of the target memory.
			This was provided so we could run on a PC where the prog_mem_array will be somewhere else
		Pass the length of the program memory array.
		Pass a pointer to the builder function

		returns to the total number of words assembled
		*/

	extern uint32_t bunny_build__relocate(uint32_t* ezh_prog_mem_array,
		uint32_t ezh_prog_mem_length,
		uint32_t ezh_prog_mem_base_address,
		void(*ezh_program)(void));

	/*
		This function is intended to be used on the target where it is
		assumed that the address of ezh_prog_mem_array is exactly where you want the binary
	*/

	extern uint32_t bunny_build(uint32_t* ezh_prog_mem_array,
		uint32_t ezh_prog_mem_length,
		void(*ezh_program)(void));


	/*
		This handles storing the encoded value
	*/
	extern void bunny_build__add_instruction(uint32_t instruction_encoding);

	static inline void E_LABEL(const char* label)
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

	static inline void E_DCD(uint32_t loc) { bunny_build__add_instruction(0); if (bunny_build__pass_num) { BUNNY_BUILD_PRINTF(BUNNY_BUILD_ERROR_FLAG"E_DCD NOT YET IMPLEMENTED\r\n"); } }    // __asm(".word "#loc) 

	static inline void E_DCD_VAL(uint32_t val) { bunny_build__add_instruction(val); }


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                      Unconditional OpCodes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//#define E_GOSUB(a30)                    __asm(".word %c0" : : "i" (0x03 + a30))
	static inline void  E_GOSUB(const char* a30)
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

#define E_NOP			bunny_build__add_instruction(0x12);

	//static inline void  E_NOP() { ; }

	static inline void  E_INT_TRIGGER(uint32_t x24) { bunny_build__add_instruction(0x14 + (x24 << 8)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_GOTO
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//#define E_GOTO(a21)			__asm(".word 0x15 + (1<<9) + " #a21 "<<9")
	static inline void  E_GOTO(const char* a21)
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
	static inline void  E_GOTO_REG(uint32_t raddr)
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
	static inline void  E_GOTOL(const char* a21)
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
	static inline void  E_GOTO_REGL(uint32_t raddr)
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
	static inline void  E_COND_GOTO(uint32_t cond, const char* a21)
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
	static inline void  E_COND_GOTO_REG(uint32_t cond, uint32_t raddr)
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
	static inline void  E_COND_GOTOL(uint32_t cond, const char* a21)
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
	static inline void  E_COND_GOTO_REGL(uint32_t cond, uint32_t raddr)
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

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_MOV
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static inline void  E_MOV(uint32_t dest, uint32_t source) { bunny_build__add_instruction(0x0 + (source << 14) + (dest << 10) + (EU << 5)); }
	static inline void  E_MOVS(uint32_t dest, uint32_t source) { bunny_build__add_instruction(0x0 + (source << 14) + (dest << 10) + (1 << 9) + (EU << 5)); }
	static inline void  E_COND_MOV(uint32_t cond, uint32_t dest, uint32_t source) { bunny_build__add_instruction(0x0 + (source << 14) + (dest << 10) + (cond << 5)); }
	static inline void  E_COND_MOVS(uint32_t cond, uint32_t dest, uint32_t source) { bunny_build__add_instruction(0x0 + (source << 14) + (dest << 10) + (1 << 9) + (cond << 5)); }

	// Invert
	static inline void  E_MVN(uint32_t dest, uint32_t source) { bunny_build__add_instruction(0x0 + (source << 14) + (dest << 10) + (EU << 5) + (1 << 31)); }
	static inline void  E_MVNS(uint32_t dest, uint32_t source) { bunny_build__add_instruction(0x0 + (source << 14) + (dest << 10) + (1 << 9) + (EU << 5) + (1 << 31)); }
	static inline void  E_COND_MVN(uint32_t cond, uint32_t dest, uint32_t source) { bunny_build__add_instruction(0x0 + (source << 14) + (dest << 10) + (cond << 5) + (1 << 31)); }
	static inline void  E_COND_MVNS(uint32_t cond, uint32_t dest, uint32_t source) { bunny_build__add_instruction(0x0 + (source << 14) + (dest << 10) + (1 << 9) + (cond << 5) + (1 << 31)); }

	// Load  Immediate
	static inline void  E_LOAD_IMM(uint32_t dest, uint32_t imm11s) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (EU << 5)); }
	static inline void  E_LOAD_IMMS(uint32_t dest, uint32_t imm11s) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (EU << 5)); }
	static inline void  E_COND_LOAD_IMM(uint32_t cond, uint32_t dest, uint32_t imm11s) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (cond << 5)); }
	static inline void  E_COND_LOAD_IMMS(uint32_t cond, uint32_t dest, uint32_t imm11s) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (cond << 5)); }

	// Load Shifted Immediate
	static inline void  E_LOAD_SIMM(uint32_t dest, uint32_t imm11s, uint32_t sam) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (EU << 5) + ((sam & 0xf) << 14) + (((sam & 0x10) >> 4) << 19)); }
	static inline void  E_LOAD_SIMMS(uint32_t dest, uint32_t imm11s, uint32_t sam) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (EU << 5) + ((sam & 0xf) << 14) + (((sam & 0x10) >> 4) << 19)); }
	static inline void  E_COND_LOAD_SIMM(uint32_t cond, uint32_t dest, uint32_t imm11s, uint32_t sam) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (cond << 5) + ((sam & 0xf) << 14) + (((sam & 0x10) >> 4) << 19)); }
	static inline void  E_COND_LOAD_SIMMS(uint32_t cond, uint32_t dest, uint32_t imm11s, uint32_t sam) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (cond << 5) + ((sam & 0xf) << 14) + (((sam & 0x10) >> 4) << 19)); }

	// Load  Inverted Immediate
	static inline void  E_LOAD_IMMN(uint32_t dest, uint32_t imm11s) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (EU << 5) + (1 << 31)); }
	static inline void  E_LOAD_IMMNS(uint32_t dest, uint32_t imm11s) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (EU << 5) + (1 << 31)); }
	static inline void  E_COND_LOAD_IMMN(uint32_t cond, uint32_t dest, uint32_t imm11s) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (cond << 5) + (1 << 31)); }
	static inline void  E_COND_LOAD_IMMNS(uint32_t cond, uint32_t dest, uint32_t imm11s) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (cond << 5) + (1 << 31)); }

	// Load Shifted then inverted Immediate
	static inline void  E_LOAD_SIMMN(uint32_t dest, uint32_t imm11s, uint32_t sam) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (EU << 5) + ((sam & 0xf) << 14) + (((sam & 0x10) >> 4) << 19) + (1 << 31)); }
	static inline void  E_LOAD_SIMMNS(uint32_t dest, uint32_t imm11s, uint32_t sam) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (EU << 5) + ((sam & 0xf) << 14) + (((sam & 0x10) >> 4) << 19) + (1 << 31)); }
	static inline void  E_COND_LOAD_SIMMN(uint32_t cond, uint32_t dest, uint32_t imm11s, uint32_t sam) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (cond << 5) + ((sam & 0xf) << 14) + (((sam & 0x10) >> 4) << 19) + (1 << 31)); }
	static inline void  E_COND_LOAD_SIMMNS(uint32_t cond, uint32_t dest, uint32_t imm11s, uint32_t sam) { bunny_build__add_instruction(0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (cond << 5) + ((sam & 0xf) << 14) + (((sam & 0x10) >> 4) << 19) + (1 << 31)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_AHB_READ Codes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                        opcode    Ptr PostIncrement (0 means pre-inc)   Rdata Dest       Pointer       WData Source        Offset          UpdatePointer    SizeWord    Signed Access  Cond                       
	// LDR (Load, Load Byte, LoadByteSigned)
	static inline void  E_LDR(uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (0 << 20) + (1 << 18) + (0 << 21) + (EU << 5)); }
	static inline void  E_LDRB(uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (0 << 20) + (0 << 18) + (0 << 21) + (EU << 5)); }
	static inline void  E_LDRBS(uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (0 << 20) + (0 << 18) + (1 << 21) + (EU << 5)); }

	// Conditional LDR (Load, Load Byte, LoadByteSigned)
	static inline void  E_COND_LDR(uint32_t cond, uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (0 << 20) + (1 << 18) + (0 << 21) + (cond << 5)); }
	static inline void  E_COND_LDRB(uint32_t cond, uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (0 << 20) + (0 << 18) + (0 << 21) + (cond << 5)); }
	static inline void  E_COND_LDRBS(uint32_t cond, uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (0 << 20) + (0 << 18) + (1 << 21) + (cond << 5)); }

	// With Update Pointer
	static inline void  E_LDR_PRE(uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (1 << 18) + (0 << 21) + (EU << 5)); }
	static inline void  E_LDRB_PRE(uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (0 << 21) + (EU << 5)); }
	static inline void  E_LDRBS_PRE(uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (1 << 21) + (EU << 5)); }
	static inline void  E_COND_LDR_PRE(uint32_t cond, uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (1 << 18) + (0 << 21) + (cond << 5)); }
	static inline void  E_COND_LDRB_PRE(uint32_t cond, uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (0 << 21) + (cond << 5)); }
	static inline void  E_COND_LDRBS_PRE(uint32_t cond, uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (1 << 21) + (cond << 5)); }

	// With Update Pointer (Post Increment pointer)
	static inline void  E_LDR_POST(uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (1 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (1 << 18) + (0 << 21) + (EU << 5)); }
	static inline void  E_LDRB_POST(uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (1 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (0 << 21) + (EU << 5)); }
	static inline void  E_LDRBS_POST(uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (1 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (1 << 21) + (EU << 5)); }
	static inline void  E_COND_LDR_POST(uint32_t cond, uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (1 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (1 << 18) + (0 << 21) + (cond << 5)); }
	static inline void  E_COND_LDRB_POST(uint32_t cond, uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (1 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (0 << 21) + (cond << 5)); }
	static inline void  E_COND_LDRBS_POST(uint32_t cond, uint32_t dest, uint32_t source, uint32_t offset8s) { bunny_build__add_instruction(0x1 + (1 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (1 << 21) + (cond << 5)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_AHB_WRITE Codes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                       opcode    Ptr PostIncrement (0 means pre-inc)   Rdata Dest       Pointer       WData Source        offset8s          UpdatePointer    SizeWord    Signed Access  Cond                               
	// STR (Load, Load Byte, LoadByteSigned)
	static inline void  E_STR(uint32_t raddr, uint32_t  rdata, uint32_t  offset8s) { bunny_build__add_instruction(0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (0 << 10) + (1 << 18) + (0 << 11) + (EU << 5)); }
	static inline void  E_STRB(uint32_t raddr, uint32_t  rdata, uint32_t  offset8s) { bunny_build__add_instruction(0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (0 << 10) + (0 << 18) + (0 << 11) + (EU << 5)); }

	// Conditional STR (Load, Load Byte, LoadByteSigned)
	static inline void  E_COND_STR(uint32_t cond, uint32_t raddr, uint32_t  rdata, uint32_t  offset8s) { bunny_build__add_instruction(0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (0 << 10) + (1 << 18) + (0 << 11) + (cond << 5)); }
	static inline void  E_COND_STRB(uint32_t cond, uint32_t raddr, uint32_t  rdata, uint32_t  offset8s) { bunny_build__add_instruction(0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (0 << 10) + (0 << 18) + (0 << 11) + (cond << 5)); }

	// With Update Pointer
	static inline void  E_STR_PRE(uint32_t raddr, uint32_t  rdata, uint32_t  offset8s) { bunny_build__add_instruction(0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (1 << 18) + (0 << 11) + (EU << 5)); }
	static inline void  E_STRB_PRE(uint32_t raddr, uint32_t  rdata, uint32_t  offset8s) { bunny_build__add_instruction(0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (0 << 18) + (0 << 11) + (EU << 5)); }
	static inline void  E_COND_STR_PRE(uint32_t cond, uint32_t raddr, uint32_t  rdata, uint32_t  offset8s) { bunny_build__add_instruction(0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (1 << 18) + (0 << 11) + (cond << 5)); }
	static inline void  E_COND_STRB_PRE(uint32_t cond, uint32_t raddr, uint32_t  rdata, uint32_t  offset8s) { bunny_build__add_instruction(0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (0 << 18) + (0 << 11) + (cond << 5)); }

	// With Update Pointer (Post Increment pointer)
	static inline void  E_STR_POST(uint32_t raddr, uint32_t  rdata, uint32_t  offset8s) { bunny_build__add_instruction(0x2 + (1 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (1 << 18) + (0 << 11) + (EU << 5)); }
	static inline void  E_STRB_POST(uint32_t raddr, uint32_t  rdata, uint32_t  offset8s) { bunny_build__add_instruction(0x2 + (1 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (0 << 18) + (0 << 11) + (EU << 5)); }
	static inline void  E_COND_STR_POST(uint32_t cond, uint32_t raddr, uint32_t  rdata, uint32_t  offset8s) { bunny_build__add_instruction(0x2 + (1 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (1 << 18) + (0 << 11) + (cond << 5)); }
	static inline void  E_COND_STRB_POST(uint32_t cond, uint32_t raddr, uint32_t  rdata, uint32_t  offset8s) { bunny_build__add_instruction(0x2 + (1 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (0 << 18) + (0 << 11) + (cond << 5)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                      Stack Operations (built up from E_LDR and E_STR codes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                       opcode    Ptr PostIncrement (0 means pre-inc)   Rdata Dest       Pointer       WData Source        Offset          UpdatePointer    SizeWord    Signed Access  Cond                               
	static inline void  E_PUSH(uint32_t source) { bunny_build__add_instruction(0x2 + (1 << 19) + (SP << 14) + (source << 20) + (1 << 24) + (1 << 10) + (1 << 18) + (0 << 11) + (EU << 5)); }
	static inline void  E_POP(uint32_t dest) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (SP << 14) + ((-1) << 24) + (1 << 20) + (1 << 18) + (0 << 21) + (EU << 5)); }
	static inline void  E_PUSHB(uint32_t source) { bunny_build__add_instruction(0x2 + (1 << 19) + (SP << 14) + (source << 20) + (1 << 24) + (1 << 10) + (0 << 18) + (0 << 11) + (EU << 5)); }
	static inline void  E_POPB(uint32_t dest) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (SP << 14) + ((-1) << 24) + (1 << 20) + (0 << 18) + (0 << 21) + (EU << 5)); }
	static inline void  E_POPBS(uint32_t dest) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (SP << 14) + ((-1) << 24) + (1 << 20) + (0 << 18) + (1 << 21) + (EU << 5)); }
	static inline void  E_COND_PUSH(uint32_t cond, uint32_t source) { bunny_build__add_instruction(0x2 + (1 << 19) + (SP << 14) + (source << 20) + (1 << 24) + (1 << 10) + (1 << 18) + (0 << 11) + (cond << 5)); }
	static inline void  E_COND_POP(uint32_t cond, uint32_t dest) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (SP << 14) + ((-1) << 24) + (1 << 20) + (1 << 18) + (0 << 21) + (cond << 5)); }
	static inline void  E_COND_PUSHB(uint32_t cond, uint32_t source) { bunny_build__add_instruction(0x2 + (1 << 19) + (SP << 14) + (source << 20) + (1 << 24) + (1 << 10) + (0 << 18) + (0 << 11) + (cond << 5)); }
	static inline void  E_COND_POPB(uint32_t cond, uint32_t dest) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (SP << 14) + ((-1) << 24) + (1 << 20) + (0 << 18) + (0 << 21) + (cond << 5)); }
	static inline void  E_COND_POPBS(uint32_t cond, uint32_t dest) { bunny_build__add_instruction(0x1 + (0 << 19) + (dest << 10) + (SP << 14) + ((-1) << 24) + (1 << 20) + (0 << 18) + (1 << 21) + (cond << 5)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_PER_READ Codes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest       Address                        Cond                               
	static inline void  E_PER_READ(uint32_t dest, uint32_t addr20) { bunny_build__add_instruction(0x4 + (dest << 10) + ((addr20 & 0x000ffffc) << 12) + (EU << 5)); }
	static inline void  E_COND_PER_READ(uint32_t cond, uint32_t dest, uint32_t addr20) { bunny_build__add_instruction(0x4 + (dest << 10) + ((addr20 & 0x000ffffc) << 12) + (cond << 5)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_PER_WRITE Codes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest       Address                        Cond                               
	static inline void  E_PER_WRITE(uint32_t source, uint32_t addr20) { bunny_build__add_instruction(0x5 + (source << 20) + ((addr20 & 0x000ff000) << 12) + ((addr20 & 0x00000ffc) << 8) + (EU << 5)); }
	static inline void  E_COND_PER_WRITE(uint32_t cond, uint32_t source, uint32_t addr20) { bunny_build__add_instruction(0x5 + (source << 20) + ((addr20 & 0x000ff000) << 12) + ((addr20 & 0x00000ffc) << 8) + (cond << 5)); }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_ADD Codes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              src2        SFlag              Cond         Imm            Use_Imm      Invert Result       Shift Amount           Shift/Rotate    Left/Right   Flip
	// Add reg to reg  
	static inline void  E_ADD(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5)); }
	static inline void  E_ADDS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5)); }
	static inline void  E_COND_ADD(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5)); }
	static inline void  E_COND_ADDS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5)); }

	// Add reg to reg and invert result 
	static inline void  E_ADDN(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19)); }
	static inline void  E_ADDNS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19)); }
	static inline void  E_COND_ADDN(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19)); }
	static inline void  E_COND_ADDNS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19)); }

	// Add imm12s to reg  
	static inline void  E_ADD_IMM(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_ADD_IMMS(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_COND_ADD_IMM(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_COND_ADD_IMMS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18)); }

	// Add imm12s to reg and invert result 
	static inline void  E_ADDN_IMM(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_ADDN_IMMS(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_COND_ADDN_IMM(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_COND_ADDN_IMMS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }

	// Add reg to reg with Post Shift Left
	static inline void  E_ADD_LSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_ADD_LSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADD_LSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADD_LSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }

	// Add reg to reg and invert result with Post Shift Left
	static inline void  E_ADDN_LSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_ADDN_LSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADDN_LSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADDN_LSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }

	// Add reg to reg with Post Shift Right
	static inline void  E_ADD_LSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_ADD_LSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADD_LSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADD_LSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }

	// Add reg to reg and invert result with Post Shift Right
	static inline void  E_ADDN_LSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_ADDN_LSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADDN_LSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADDN_LSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }

	// Add reg to reg with Post Arith Shift Right
	static inline void  E_ADD_ASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_ADD_ASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADD_ASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADD_ASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }

	// Add reg to reg and invert result with Post Arith Shift Right
	static inline void  E_ADDN_ASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_ADDN_ASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADDN_ASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADDN_ASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }

	// Add reg to reg with Post ROR
	static inline void  E_ADD_ROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_ADD_RORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADD_ROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADD_RORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }

	// Add reg to reg and invert result with ROR
	static inline void  E_ADDN_ROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_ADDN_RORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADDN_ROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADDN_RORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }

	// Add reg to reg with Flip
	static inline void  E_ADD_F(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ADD_FS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADD_F(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADD_FS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// Add reg to reg and invert result with Flip
	static inline void  E_ADDN_F(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ADDN_FS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADDN_F(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADDN_FS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// Add reg to reg with Post Shift Left
	static inline void  E_ADD_FLSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ADD_FLSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADD_FLSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADD_FLSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// Add reg to reg and invert result with Post Shift Left
	static inline void  E_ADDN_FLSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ADDN_FLSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADDN_FLSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADDN_FLSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// Add reg to reg with Post Shift Right
	static inline void  E_ADD_FLSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_ADD_FLSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADD_FLSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADD_FLSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }

	// Add reg to reg and invert result with Post Shift Right
	static inline void  E_ADDN_FLSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_ADDN_FLSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADDN_FLSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADDN_FLSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }

	// Add reg to reg with Post Arith Shift Right
	static inline void  E_ADD_FASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ADD_FASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADD_FASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADD_FASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }

	// Add reg to reg and invert result with Post Arith Shift Right
	static inline void  E_ADDN_FASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ADDN_FASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADDN_FASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADDN_FASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }

	// Add reg to reg with Post ROR
	static inline void  E_ADD_FROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_ADD_FRORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADD_FROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADD_FRORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }

	// Add reg to reg and invert result with ROR
	static inline void  E_ADDN_FROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_ADDN_FRORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADDN_FROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADDN_FRORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_SUB Codes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              src2        SFlag              Cond         Imm            Use_Imm      Invert Result    Shift Result       
	// sub reg from reg  
	static inline void  E_SUB(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5)); }
	static inline void  E_SUBS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5)); }
	static inline void  E_COND_SUB(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5)); }
	static inline void  E_COND_SUBS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5)); }

	// sub reg from reg and invert result 
	static inline void  E_SUBN(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19)); }
	static inline void  E_SUBNS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19)); }
	static inline void  E_COND_SUBN(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19)); }
	static inline void  E_COND_SUBNS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19)); }

	// sub imm12s from reg  
	static inline void  E_SUB_IMM(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_SUB_IMMS(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_COND_SUB_IMM(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_COND_SUB_IMMS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18)); }

	// sub imm12s from reg and invert result 
	static inline void  E_SUBN_IMM(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_SUBN_IMMS(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_COND_SUBN_IMM(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_COND_SUBN_IMMS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }

	// SUB reg to reg with Post Shift Left
	static inline void  E_SUB_LSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_SUB_LSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SUB_LSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SUB_LSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }

	// SUB reg to reg and invert result with Post Shift Left
	static inline void  E_SUBN_LSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_SUBN_LSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SUBN_LSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SUBN_LSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }

	// SUB reg to reg with Post Shift Right
	static inline void  E_SUB_LSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_SUB_LSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SUB_LSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SUB_LSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }

	// SUB reg to reg and invert result with Post Shift Right
	static inline void  E_SUBN_LSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_SUBN_LSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SUBN_LSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SUBN_LSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }

	// SUB reg to reg with Post Arith Shift Right
	static inline void  E_SUB_ASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_SUB_ASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SUB_ASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SUB_ASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }

	// SUB reg to reg and invert result with Post Arith Shift Right
	static inline void  E_SUBN_ASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_SUBN_ASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SUBN_ASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SUBN_ASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }

	// SUB reg to reg with Post ROR
	static inline void  E_SUB_ROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_SUB_RORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SUB_ROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SUB_RORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }

	// SUB reg to reg and invert result with ROR
	static inline void  E_SUBN_ROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_SUBN_RORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SUBN_ROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SUBN_RORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }

	// Flip Endianness and then shift5/Rotate
	// Sub reg to reg with Flip
	static inline void  E_SUB_F(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_SUB_FS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SUB_F(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SUB_FS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// Sub reg to reg and invert result with Flip
	static inline void  E_SUBN_F(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_SUBN_FS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SUBN_F(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SUBN_FS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// SUB reg to reg with Post Shift Left
	static inline void  E_SUB_FLSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_SUB_FLSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SUB_FLSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SUB_FLSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// SUB reg to reg and invert result with Post Shift Left
	static inline void  E_SUBN_FLSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_SUBN_FLSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SUBN_FLSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SUBN_FLSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// SUB reg to reg with Post Shift Right
	static inline void  E_SUB_FLSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_SUB_FLSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SUB_FLSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SUB_FLSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }

	// SUB reg to reg and invert result with Post Shift Right
	static inline void  E_SUBN_FLSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_SUBN_FLSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SUBN_FLSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SUBN_FLSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }

	// SUB reg to reg with Post Arith Shift Right
	static inline void  E_SUB_FASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_SUB_FASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SUB_FASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SUB_FASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }

	// SUB reg to reg and invert result with Post Arith Shift Right
	static inline void  E_SUBN_FASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_SUBN_FASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SUBN_FASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SUBN_FASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }

	// SUB reg to reg with Post ROR
	static inline void  E_SUB_FROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_SUB_FRORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SUB_FROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SUB_FRORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }

	// SUB reg to reg and invert result with ROR
	static inline void  E_SUBN_FROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_SUBN_FRORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SUBN_FROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SUBN_FRORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_ADC Codes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              src2        SFlag              Cond         Imm            Use_Imm      Invert Result    Shift Result       
	// carry add reg from reg  
	static inline void  E_ADC(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5)); }
	static inline void  E_ADCS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5)); }
	static inline void  E_COND_ADC(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5)); }
	static inline void  E_COND_ADCS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5)); }

	// carry add reg from reg and invert result 
	static inline void  E_ADCN(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19)); }
	static inline void  E_ADCNS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19)); }
	static inline void  E_COND_ADCN(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19)); }
	static inline void  E_COND_ADCNS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19)); }

	// carry add imm12s from reg  
	static inline void  E_ADC_IMM(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_ADC_IMMS(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_COND_ADC_IMM(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_COND_ADC_IMMS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18)); }

	// carry add imm12s from reg and invert result 
	static inline void  E_ADCN_IMM(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_ADCN_IMMS(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_COND_ADCN_IMM(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_COND_ADCN_IMMS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }

	// ADC reg to reg with Post Shift Left
	static inline void  E_ADC_LSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_ADC_LSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADC_LSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADC_LSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }

	// ADC reg to reg and invert result with Post Shift Left
	static inline void  E_ADCN_LSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_ADCN_LSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADCN_LSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADCN_LSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }

	// ADC reg to reg with Post Shift Right
	static inline void  E_ADC_LSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_ADC_LSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADC_LSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADC_LSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }

	// ADC reg to reg and invert result with Post Shift Right
	static inline void  E_ADCN_LSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_ADCN_LSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADCN_LSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADCN_LSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }

	// ADC reg to reg with Post Arith Shift Right
	static inline void  E_ADC_ASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_ADC_ASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADC_ASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADC_ASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }

	// ADC reg to reg and invert result with Post Arith Shift Right
	static inline void  E_ADCN_ASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_ADCN_ASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADCN_ASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ADCN_ASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }

	// ADC reg to reg with Post ROR
	static inline void  E_ADC_ROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_ADC_RORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADC_ROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADC_RORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }

	// ADC reg to reg and invert result with ROR
	static inline void  E_ADCN_ROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_ADCN_RORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADCN_ROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ADCN_RORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }

	// Flip Endianness and then shift5/Rotate
	// adc reg to reg with Flip
	static inline void  E_ADC_F(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ADC_FS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADC_F(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADC_FS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// ADC reg to reg and invert result with Flip
	static inline void  E_ADCN_F(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ADCN_FS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADCN_F(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADCN_FS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// ADC reg to reg with Post Shift Left
	static inline void  E_ADC_FLSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ADC_FLSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADC_FLSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADC_FLSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// ADC reg to reg and invert result with Post Shift Left
	static inline void  E_ADCN_FLSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ADCN_FLSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADCN_FLSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADCN_FLSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// ADC reg to reg with Post Shift Right
	static inline void  E_ADC_FLSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_ADC_FLSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADC_FLSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADC_FLSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }

	// ADC reg to reg and invert result with Post Shift Right
	static inline void  E_ADCN_FLSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_ADCN_FLSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADCN_FLSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADCN_FLSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }

	// ADC reg to reg with Post Arith Shift Right
	static inline void  E_ADC_FASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ADC_FASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADC_FASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADC_FASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }

	// ADC reg to reg and invert result with Post Arith Shift Right
	static inline void  E_ADCN_FASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ADCN_FASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADCN_FASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ADCN_FASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }

	// ADC reg to reg with Post ROR
	static inline void  E_ADC_FROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_ADC_FRORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADC_FROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADC_FRORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }

	// ADC reg to reg and invert result with ROR
	static inline void  E_ADCN_FROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_ADCN_FRORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADCN_FROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ADCN_FRORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_SBC Codes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              src2        SFlag              Cond         Imm            Use_Imm      Invert Result    Shift Result       
	// carry sub reg from reg  
	static inline void  E_SBC(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5)); }
	static inline void  E_SBCS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5)); }
	static inline void  E_COND_SBC(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5)); }
	static inline void  E_COND_SBCS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5)); }

	// carry sub reg from reg and invert result 
	static inline void  E_SBCN(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19)); }
	static inline void  E_SBCNS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19)); }
	static inline void  E_COND_SBCN(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19)); }
	static inline void  E_COND_SBCNS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19)); }

	// carry sub imm12s from reg  
	static inline void  E_SBC_IMM(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_SBC_IMMS(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_COND_SBC_IMM(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_COND_SBC_IMMS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18)); }

	// carry sub imm12s from reg and invert result 
	static inline void  E_SBCN_IMM(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_SBCN_IMMS(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_COND_SBCN_IMM(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_COND_SBCN_IMMS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }

	// SBC reg to reg with Post Shift Left
	static inline void  E_SBC_LSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_SBC_LSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SBC_LSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SBC_LSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }

	// SBC reg to reg and invert result with Post Shift Left
	static inline void  E_SBCN_LSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_SBCN_LSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SBCN_LSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SBCN_LSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }

	// SBC reg to reg with Post Shift Right
	static inline void  E_SBC_LSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_SBC_LSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SBC_LSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SBC_LSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }

	// SBC reg to reg and invert result with Post Shift Right
	static inline void  E_SBCN_LSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_SBCN_LSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SBCN_LSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SBCN_LSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }

	// SBC reg to reg with Post Arith Shift Right
	static inline void  E_SBC_ASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_SBC_ASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SBC_ASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SBC_ASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }

	// SBC reg to reg and invert result with Post Arith Shift Right
	static inline void  E_SBCN_ASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_SBCN_ASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SBCN_ASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_SBCN_ASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }

	// SBC reg to reg with Post ROR
	static inline void  E_SBC_ROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_SBC_RORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SBC_ROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SBC_RORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }

	// SBC reg to reg and invert result with ROR
	static inline void  E_SBCN_ROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_SBCN_RORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SBCN_ROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_SBCN_RORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }

	// Flip Endianness and then shift5/Rotate
	// SBC reg to reg with Flip
	static inline void  E_SBC_F(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_SBC_FS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SBC_F(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SBC_FS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// SBC reg to reg and invert result with Flip
	static inline void  E_SBCN_F(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_SBCN_FS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SBCN_F(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SBCN_FS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// SBC reg to reg with Post Shift Left
	static inline void  E_SBC_FLSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_SBC_FLSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SBC_FLSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SBC_FLSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// SBC reg to reg and invert result with Post Shift Left
	static inline void  E_SBCN_FLSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_SBCN_FLSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SBCN_FLSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SBCN_FLSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// SBC reg to reg with Post Shift Right
	static inline void  E_SBC_FLSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_SBC_FLSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SBC_FLSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SBC_FLSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }

	// SBC reg to reg and invert result with Post Shift Right
	static inline void  E_SBCN_FLSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_SBCN_FLSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SBCN_FLSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SBCN_FLSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }

	// SBC reg to reg with Post Arith Shift Right
	static inline void  E_SBC_FASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_SBC_FASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SBC_FASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SBC_FASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }

	// SBC reg to reg and invert result with Post Arith Shift Right
	static inline void  E_SBCN_FASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_SBCN_FASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SBCN_FASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_SBCN_FASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }

	// SBC reg to reg with Post ROR
	static inline void  E_SBC_FROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_SBC_FRORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SBC_FROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SBC_FRORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }

	// SBC reg to reg and invert result with ROR
	static inline void  E_SBCN_FROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_SBCN_FRORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SBCN_FROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_SBCN_FRORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_OR Codes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              src2        SFlag              Cond         Imm            Use_Imm      Invert Result    Shift Result       
	// or reg with reg  
	static inline void  E_OR(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5)); }
	static inline void  E_ORS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5)); }
	static inline void  E_COND_OR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5)); }
	static inline void  E_COND_ORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5)); }

	// or reg with reg and invert result 
	static inline void  E_ORN(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19)); }
	static inline void  E_ORNS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19)); }
	static inline void  E_COND_ORN(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19)); }
	static inline void  E_COND_ORNS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19)); }

	// or imm12s with reg  
	static inline void  E_OR_IMM(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_OR_IMMS(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_COND_OR_IMM(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_COND_OR_IMMS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18)); }

	// or imm12s with reg and invert result 
	static inline void  E_ORN_IMM(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_ORN_IMMS(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_COND_ORN_IMM(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_COND_ORN_IMMS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }

	// OR reg to reg with Post Shift Left
	static inline void  E_OR_LSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_OR_LSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_OR_LSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_OR_LSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }

	// OR reg to reg and invert result with Post Shift Left
	static inline void  E_ORN_LSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_ORN_LSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ORN_LSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ORN_LSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }

	// OR reg to reg with Post Shift Right
	static inline void  E_OR_LSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_OR_LSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_OR_LSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_OR_LSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }

	// OR reg to reg and invert result with Post Shift Right
	static inline void  E_ORN_LSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_ORN_LSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ORN_LSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ORN_LSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }

	// OR reg to reg with Post Arith Shift Right
	static inline void  E_OR_ASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_OR_ASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_OR_ASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_OR_ASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }

	// OR reg to reg and invert result with Post Arith Shift Right
	static inline void  E_ORN_ASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_ORN_ASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ORN_ASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ORN_ASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }

	// OR reg to reg with Post ROR
	static inline void  E_OR_ROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_OR_RORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_OR_ROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_OR_RORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }

	// OR reg to reg and invert result with ROR
	static inline void  E_ORN_ROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_ORN_RORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ORN_ROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ORN_RORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }

	// Flip Endianness and then shift5/Rotate
	// OR reg to reg with Flip
	static inline void  E_OR_F(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_OR_FS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_OR_F(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_OR_FS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// OR reg to reg and invert result with Flip
	static inline void  E_ORN_F(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ORN_FS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ORN_F(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ORN_FS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// OR reg to reg with Post Shift Left
	static inline void  E_OR_FLSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_OR_FLSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_OR_FLSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_OR_FLSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// OR reg to reg and invert result with Post Shift Left
	static inline void  E_ORN_FLSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ORN_FLSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ORN_FLSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ORN_FLSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// OR reg to reg with Post Shift Right
	static inline void  E_OR_FLSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_OR_FLSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_OR_FLSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_OR_FLSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }

	// OR reg to reg and invert result with Post Shift Right
	static inline void  E_ORN_FLSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_ORN_FLSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ORN_FLSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ORN_FLSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }

	// OR reg to reg with Post Arith Shift Right
	static inline void  E_OR_FASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_OR_FASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_OR_FASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_OR_FASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }

	// OR reg to reg and invert result with Post Arith Shift Right
	static inline void  E_ORN_FASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ORN_FASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ORN_FASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ORN_FASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }

	// OR reg to reg with Post ROR
	static inline void  E_OR_FROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_OR_FRORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_OR_FROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_OR_FRORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }

	// OR reg to reg and invert result with ROR
	static inline void  E_ORN_FROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_ORN_FRORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ORN_FROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ORN_FRORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_AND Codes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              src2        SFlag              Cond         Imm            Use_Imm      Invert Result    Shift Result       
	// AND reg with reg  
	static inline void  E_AND(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5)); }
	static inline void  E_ANDS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5)); }
	static inline void  E_COND_AND(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5)); }
	static inline void  E_COND_ANDS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5)); }

	// AND reg with reg and invert result 
	static inline void  E_ANDN(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19)); }
	static inline void  E_ANDNS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19)); }
	static inline void  E_COND_ANDN(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19)); }
	static inline void  E_COND_ANDNS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19)); }

	// AND imm12s with reg  
	static inline void  E_AND_IMM(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_AND_IMMS(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_COND_AND_IMM(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_COND_AND_IMMS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18)); }

	// AND imm12s with reg and invert result 
	static inline void  E_ANDN_IMM(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_ANDN_IMMS(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_COND_ANDN_IMM(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_COND_ANDN_IMMS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }

	// AND reg to reg with Post Shift Left
	static inline void  E_AND_LSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_AND_LSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_AND_LSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_AND_LSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }

	// AND reg to reg and invert result with Post Shift Left
	static inline void  E_ANDN_LSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_ANDN_LSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ANDN_LSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ANDN_LSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }

	// AND reg to reg with Post Shift Right
	static inline void  E_AND_LSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_AND_LSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_AND_LSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_AND_LSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }

	// AND reg to reg and invert result with Post Shift Right
	static inline void  E_ANDN_LSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_ANDN_LSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ANDN_LSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ANDN_LSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }

	// AND reg to reg with Post Arith Shift Right
	static inline void  E_AND_ASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_AND_ASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_AND_ASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_AND_ASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }

	// AND reg to reg and invert result with Post Arith Shift Right
	static inline void  E_ANDN_ASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_ANDN_ASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ANDN_ASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_ANDN_ASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }

	// AND reg to reg with Post ROR
	static inline void  E_AND_ROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_AND_RORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_AND_ROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_AND_RORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }

	// AND reg to reg and invert result with ROR
	static inline void  E_ANDN_ROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_ANDN_RORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ANDN_ROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_ANDN_RORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }

	// Flip Endianness and then shift5/Rotate
	// AND reg to reg with Flip
	static inline void  E_AND_F(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_AND_FS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_AND_F(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_AND_FS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// AND reg to reg and invert result with Flip
	static inline void  E_ANDN_F(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ANDN_FS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ANDN_F(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ANDN_FS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// AND reg to reg with Post Shift Left
	static inline void  E_AND_FLSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_AND_FLSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_AND_FLSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_AND_FLSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// AND reg to reg and invert result with Post Shift Left
	static inline void  E_ANDN_FLSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ANDN_FLSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ANDN_FLSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ANDN_FLSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// AND reg to reg with Post Shift Right
	static inline void  E_AND_FLSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_AND_FLSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_AND_FLSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_AND_FLSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }

	// AND reg to reg and invert result with Post Shift Right
	static inline void  E_ANDN_FLSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_ANDN_FLSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ANDN_FLSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ANDN_FLSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }

	// AND reg to reg with Post Arith Shift Right
	static inline void  E_AND_FASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_AND_FASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_AND_FASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_AND_FASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }

	// AND reg to reg and invert result with Post Arith Shift Right
	static inline void  E_ANDN_FASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_ANDN_FASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ANDN_FASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_ANDN_FASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }

	// AND reg to reg with Post ROR
	static inline void  E_AND_FROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_AND_FRORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_AND_FROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_AND_FRORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }

	// AND reg to reg and invert result with ROR
	static inline void  E_ANDN_FROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_ANDN_FRORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ANDN_FROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_ANDN_FRORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_XOR Codes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              src2        SFlag              Cond         Imm            Use_Imm      Invert Result    Shift Result       
	// XOR reg with reg  
	static inline void  E_XOR(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5)); }
	static inline void  E_XORS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5)); }
	static inline void  E_COND_XOR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5)); }
	static inline void  E_COND_XORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5)); }

	// XOR reg with reg XOR invert result 
	static inline void  E_XORN(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19)); }
	static inline void  E_XORNS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19)); }
	static inline void  E_COND_XORN(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19)); }
	static inline void  E_COND_XORNS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19)); }

	// XOR imm12s with reg  
	static inline void  E_XOR_IMM(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_XOR_IMMS(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_COND_XOR_IMM(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18)); }
	static inline void  E_COND_XOR_IMMS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18)); }

	// XOR imm12s with reg XOR invert result 
	static inline void  E_XORN_IMM(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_XORN_IMMS(uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_COND_XORN_IMM(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }
	static inline void  E_COND_XORN_IMMS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t imm12s) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)); }

	// XOR reg to reg with Post Shift Left
	static inline void  E_XOR_LSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_XOR_LSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_XOR_LSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_XOR_LSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }

	// XOR reg to reg XOR invert result with Post Shift Left
	static inline void  E_XORN_LSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_XORN_LSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_XORN_LSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_XORN_LSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)); }

	// XOR reg to reg with Post Shift Right
	static inline void  E_XOR_LSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_XOR_LSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_XOR_LSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_XOR_LSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }

	// XOR reg to reg XOR invert result with Post Shift Right
	static inline void  E_XORN_LSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_XORN_LSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_XORN_LSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_XORN_LSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)); }

	// XOR reg to reg with Post Arith Shift Right
	static inline void  E_XOR_ASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_XOR_ASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_XOR_ASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_XOR_ASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }

	// XOR reg to reg XOR invert result with Post Arith Shift Right
	static inline void  E_XORN_ASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_XORN_ASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_XORN_ASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }
	static inline void  E_COND_XORN_ASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)); }

	// XOR reg to reg with Post ROR
	static inline void  E_XOR_ROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_XOR_RORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_XOR_ROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_XOR_RORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }

	// XOR reg to reg XOR invert result with ROR
	static inline void  E_XORN_ROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_XORN_RORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_XORN_ROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }
	static inline void  E_COND_XORN_RORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)); }

	// Flip Endianness and then shift5/Rotate
	// XOR reg to reg with Flip
	static inline void  E_XOR_F(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_XOR_FS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_XOR_F(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_XOR_FS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// XOR reg to reg and invert result with Flip
	static inline void  E_XORN_F(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_XORN_FS(uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_XORN_F(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_XORN_FS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// XOR reg to reg with Post Shift Left
	static inline void  E_XOR_FLSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_XOR_FLSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_XOR_FLSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_XOR_FLSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// XOR reg to reg XOR invert result with Post Shift Left
	static inline void  E_XORN_FLSL(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_XORN_FLSLS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_XORN_FLSL(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_XORN_FLSLS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)); }

	// XOR reg to reg with Post Shift Right
	static inline void  E_XOR_FLSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_XOR_FLSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_XOR_FLSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_XOR_FLSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }

	// XOR reg to reg XOR invert result with Post Shift Right
	static inline void  E_XORN_FLSR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_XORN_FLSRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_XORN_FLSR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_XORN_FLSRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)); }

	// XOR reg to reg with Post Arith Shift Right
	static inline void  E_XOR_FASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_XOR_FASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_XOR_FASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_XOR_FASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }

	// XOR reg to reg XOR invert result with Post Arith Shift Right
	static inline void  E_XORN_FASR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_XORN_FASRS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_XORN_FASR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }
	static inline void  E_COND_XORN_FASRS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)); }

	// XOR reg to reg with Post ROR
	static inline void  E_XOR_FROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_XOR_FRORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_XOR_FROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_XOR_FRORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }

	// XOR reg to reg XOR invert result with ROR
	static inline void  E_XORN_FROR(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_XORN_FRORS(uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_XORN_FROR(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }
	static inline void  E_COND_XORN_FRORS(uint32_t cond, uint32_t dest, uint32_t src1, uint32_t src2, uint32_t shift5) { bunny_build__add_instruction(0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_Shift Codes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              r2shift        SFlag              Cond         Imm                    Extra Operation    Left/Right   Shift/Rotate
	// Logical Shift  
	static inline void  E_LSL(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSR(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag
	static inline void  E_LSLS(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSRS(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then AND
	static inline void  E_LSL_AND(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSR_AND(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then AND
	static inline void  E_LSL_ANDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSR_ANDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then OR
	static inline void  E_LSL_OR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSR_OR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then OR
	static inline void  E_LSL_ORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSR_ORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then XOR
	static inline void  E_LSL_XOR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSR_XOR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then XOR
	static inline void  E_LSL_XORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSR_XORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then ADD
	static inline void  E_LSL_ADD(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSR_ADD(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then ADD
	static inline void  E_LSL_ADDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSR_ADDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then SUB
	static inline void  E_LSL_SUB(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSR_SUB(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then SUB
	static inline void  E_LSL_SUBS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSR_SUBS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then ADC          
	static inline void  E_LSL_ADC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSR_ADC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then ADC
	static inline void  E_LSL_ADCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSR_ADCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then SBC
	static inline void  E_LSL_SBC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSR_SBC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then SBC
	static inline void  E_LSL_SBCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_LSR_SBCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift  
	static inline void  E_COND_LSL(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSR(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag
	static inline void  E_COND_LSLS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSRS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then AND
	static inline void  E_COND_LSL_AND(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSR_AND(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then AND
	static inline void  E_COND_LSL_ANDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSR_ANDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then OR
	static inline void  E_COND_LSL_OR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSR_OR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then OR
	static inline void  E_COND_LSL_ORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSR_ORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then XOR
	static inline void  E_COND_LSL_XOR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSR_XOR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then XOR
	static inline void  E_COND_LSL_XORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSR_XORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then ADD
	static inline void  E_COND_LSL_ADD(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSR_ADD(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then ADD
	static inline void  E_COND_LSL_ADDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSR_ADDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then SUB
	static inline void  E_COND_LSL_SUB(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSR_SUB(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then SUB
	static inline void  E_COND_LSL_SUBS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSR_SUBS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then ADC          
	static inline void  E_COND_LSL_ADC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSR_ADC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then ADC
	static inline void  E_COND_LSL_ADCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSR_ADCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then SBC
	static inline void  E_COND_LSL_SBC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSR_SBC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then SBC
	static inline void  E_COND_LSL_SBCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_LSR_SBCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18)); }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_ROTATE Codes
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              r2shift        SFlag              Cond         Imm                   Extra Operation    Left/Right   Shift/Rotate
	// Rotate  
	static inline void  E_ROR(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag
	static inline void  E_RORS(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then AND
	static inline void  E_ROR_AND(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then AND
	static inline void  E_ROR_ANDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then OR
	static inline void  E_ROR_OR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then OR
	static inline void  E_ROR_ORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then XOR
	static inline void  E_ROR_XOR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then XOR
	static inline void  E_ROR_XORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then ADD
	static inline void  E_ROR_ADD(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then ADD
	static inline void  E_ROR_ADDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then SUB
	static inline void  E_ROR_SUB(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then SUB
	static inline void  E_ROR_SUBS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then ADC          
	static inline void  E_ROR_ADC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then ADC
	static inline void  E_ROR_ADCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then SBC
	static inline void  E_ROR_SBC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then SBC
	static inline void  E_ROR_SBCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate  
	static inline void  E_COND_ROR(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag
	static inline void  E_COND_RORS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then AND
	static inline void  E_COND_ROR_AND(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then AND
	static inline void  E_COND_ROR_ANDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then OR
	static inline void  E_COND_ROR_OR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then OR
	static inline void  E_COND_ROR_ORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then XOR
	static inline void  E_COND_ROR_XOR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then XOR
	static inline void  E_COND_ROR_XORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then ADD
	static inline void  E_COND_ROR_ADD(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then ADD
	static inline void  E_COND_ROR_ADDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then SUB
	static inline void  E_COND_ROR_SUB(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then SUB
	static inline void  E_COND_ROR_SUBS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then ADC          
	static inline void  E_COND_ROR_ADC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then ADC
	static inline void  E_COND_ROR_ADCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then SBC
	static inline void  E_COND_ROR_SBC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then SBC
	static inline void  E_COND_ROR_SBCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18)); }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       Arithmetical Shift Codes
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              r2shift        SFlag              Cond         Imm                   Extra Operation    Left/Right   Shift/Rotate  Arith/Shift
	// Arith Shift Right  
	static inline void  E_ASR(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag
	static inline void  E_ASRS(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and then AND
	static inline void  E_ASR_AND(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag then AND
	static inline void  E_ASR_ANDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and then OR
	static inline void  E_ASR_OR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag then OR
	static inline void  E_ASR_ORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and then XOR
	static inline void  E_ASR_XOR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag then XOR
	static inline void  E_ASR_XORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and then ADD
	static inline void  E_ASR_ADD(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag then ADD
	static inline void  E_ASR_ADDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and then SUB
	static inline void  E_ASR_SUB(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag then SUB
	static inline void  E_ASR_SUBS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and then ADC          
	static inline void  E_ASR_ADC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag then ADC
	static inline void  E_ASR_ADCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and then SBC
	static inline void  E_ASR_SBC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag then SBC
	static inline void  E_ASR_SBCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift  
	static inline void  E_COND_ASR(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag
	static inline void  E_COND_ASRS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and then AND
	static inline void  E_COND_ASR_AND(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag then AND
	static inline void  E_COND_ASR_ANDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and then OR
	static inline void  E_COND_ASR_OR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag then OR
	static inline void  E_COND_ASR_ORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and then XOR
	static inline void  E_COND_ASR_XOR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag then XOR
	static inline void  E_COND_ASR_XORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and then ADD
	static inline void  E_COND_ASR_ADD(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag then ADD
	static inline void  E_COND_ASR_ADDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and then SUB
	static inline void  E_COND_ASR_SUB(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag then SUB
	static inline void  E_COND_ASR_SUBS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and then ADC          
	static inline void  E_COND_ASR_ADC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag then ADC
	static inline void  E_COND_ASR_ADCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and then SBC
	static inline void  E_COND_ASR_SBC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag then SBC
	static inline void  E_COND_ASR_SBCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18)); }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       Flip Opcodes
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              r2shift        SFlag              Cond         Imm                   Extra Operation     Endian/bit   ARITH  Arith/Shift
	// Flip Endian , ASR Right  
	static inline void  E_FEND_ASR(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 18) + (1 << 19)); }

	// Flip Endian , ASR Right ,Set Flag
	static inline void  E_FEND_ASRS(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 18) + (1 << 19)); }

	// Flip Endian , ASR Right , AND
	static inline void  E_FEND_ASR_AND(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (1 << 19)); }

	// Flip Endian , ASR Right ,Set Flag then AND
	static inline void  E_FEND_ASR_ANDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (1 << 19)); }

	// Flip Endian , ASR Right , OR
	static inline void  E_FEND_ASR_OR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + (1 << 19)); }

	// Flip Endian , ASR Right ,Set Flag then OR
	static inline void  E_FEND_ASR_ORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + (1 << 19)); }

	// Flip Endian , ASR Right , XOR
	static inline void  E_FEND_ASR_XOR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + (1 << 19)); }

	// Flip Endian , ASR Right ,Set Flag then XOR
	static inline void  E_FEND_ASR_XORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + (1 << 19)); }

	// Flip Endian , ASR Right , ADD
	static inline void  E_FEND_ASR_ADD(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 18) + (1 << 19)); }

	// Flip Endian , ASR Right ,Set Flag then ADD
	static inline void  E_FEND_ASR_ADDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 18) + (1 << 19)); }

	// Flip Endian , ASR Right , SUB
	static inline void  E_FEND_ASR_SUB(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 18) + (1 << 19)); }

	// Flip Endian , ASR Right ,Set Flag then SUB
	static inline void  E_FEND_ASR_SUBS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 18) + (1 << 19)); }

	// Flip Endian , ASR Right , ADC          
	static inline void  E_FEND_ASR_ADC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 18) + (1 << 19)); }

	// Flip Endian , ASR Right ,Set Flag then ADC
	static inline void  E_FEND_ASR_ADCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 18) + (1 << 19)); }

	// Flip Endian , ASR Right , SBC
	static inline void  E_FEND_ASR_SBC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 18) + (1 << 19)); }

	// Flip Endian , ASR Right ,Set Flag then SBC
	static inline void  E_FEND_ASR_SBCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR  
	static inline void  E_COND_FEND_ASR(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR ,Set Flag
	static inline void  E_COND_FEND_ASRS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR , AND
	static inline void  E_COND_FEND_ASR_AND(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR ,Set Flag then AND
	static inline void  E_COND_FEND_ASR_ANDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR , OR
	static inline void  E_COND_FEND_ASR_OR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR ,Set Flag then OR
	static inline void  E_COND_FEND_ASR_ORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR , XOR
	static inline void  E_COND_FEND_ASR_XOR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR ,Set Flag then XOR
	static inline void  E_COND_FEND_ASR_XORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR , ADD
	static inline void  E_COND_FEND_ASR_ADD(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR ,Set Flag then ADD
	static inline void  E_COND_FEND_ASR_ADDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR , SUB
	static inline void  E_COND_FEND_ASR_SUB(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR ,Set Flag then SUB
	static inline void  E_COND_FEND_ASR_SUBS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR , ADC          
	static inline void  E_COND_FEND_ASR_ADC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR ,Set Flag then ADC
	static inline void  E_COND_FEND_ASR_ADCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR , SBC
	static inline void  E_COND_FEND_ASR_SBC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 18) + (1 << 19)); }

	// Conditional Flip Endian , ASR ,Set Flag then SBC
	static inline void  E_COND_FEND_ASR_SBCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 18) + (1 << 19)); }

	// Bitwise Flip ASR
	// Flip Bitwise , ASR Right  
	static inline void  E_FBIT_ASR(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Bitwise , ASR Right ,Set Flag
	static inline void  E_FBIT_ASRS(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Bitwise , ASR Right , AND
	static inline void  E_FBIT_ASR_AND(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Bitwise , ASR Right ,Set Flag then AND
	static inline void  E_FBIT_ASR_ANDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Bitwise , ASR Right , OR
	static inline void  E_FBIT_ASR_OR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Bitwise , ASR Right ,Set Flag then OR
	static inline void  E_FBIT_ASR_ORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Bitwise , ASR Right , XOR
	static inline void  E_FBIT_ASR_XOR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Bitwise , ASR Right ,Set Flag then XOR
	static inline void  E_FBIT_ASR_XORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Bitwise , ASR Right , ADD
	static inline void  E_FBIT_ASR_ADD(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Bitwise , ASR Right ,Set Flag then ADD
	static inline void  E_FBIT_ASR_ADDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Bitwise , ASR Right , SUB
	static inline void  E_FBIT_ASR_SUB(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Bitwise , ASR Right ,Set Flag then SUB
	static inline void  E_FBIT_ASR_SUBS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Bitwise , ASR Right , ADC          
	static inline void  E_FBIT_ASR_ADC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Bitwise , ASR Right ,Set Flag then ADC
	static inline void  E_FBIT_ASR_ADCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Bitwise , ASR Right , SBC
	static inline void  E_FBIT_ASR_SBC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Bitwise , ASR Right ,Set Flag then SBC
	static inline void  E_FBIT_ASR_SBCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR  
	static inline void  E_COND_FBIT_ASR(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR ,Set Flag
	static inline void  E_COND_FBIT_ASRS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR , AND
	static inline void  E_COND_FBIT_ASR_AND(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR ,Set Flag then AND
	static inline void  E_COND_FBIT_ASR_ANDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR , OR
	static inline void  E_COND_FBIT_ASR_OR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR ,Set Flag then OR
	static inline void  E_COND_FBIT_ASR_ORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR , XOR
	static inline void  E_COND_FBIT_ASR_XOR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR ,Set Flag then XOR
	static inline void  E_COND_FBIT_ASR_XORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR , ADD
	static inline void  E_COND_FBIT_ASR_ADD(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR ,Set Flag then ADD
	static inline void  E_COND_FBIT_ASR_ADDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR , SUB
	static inline void  E_COND_FBIT_ASR_SUB(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR ,Set Flag then SUB
	static inline void  E_COND_FBIT_ASR_SUBS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR , ADC          
	static inline void  E_COND_FBIT_ASR_ADC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR ,Set Flag then ADC
	static inline void  E_COND_FBIT_ASR_ADCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR , SBC
	static inline void  E_COND_FBIT_ASR_SBC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 18) + (1 << 19)); }

	// Conditional Flip Bitwise , ASR ,Set Flag then SBC
	static inline void  E_COND_FBIT_ASR_SBCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 18) + (1 << 19)); }

	// Flip Endian , LSR Right  
	static inline void  E_FEND_LSR(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 18) + (0 << 19)); }

	// Flip Endian , LSR Right ,Set Flag
	static inline void  E_FEND_LSRS(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 18) + (0 << 19)); }

	// Flip Endian , LSR Right , AND
	static inline void  E_FEND_LSR_AND(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (0 << 19)); }

	// Flip Endian , LSR Right ,Set Flag then AND
	static inline void  E_FEND_LSR_ANDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (0 << 19)); }

	// Flip Endian , LSR Right , OR
	static inline void  E_FEND_LSR_OR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + (0 << 19)); }

	// Flip Endian , LSR Right ,Set Flag then OR
	static inline void  E_FEND_LSR_ORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + (0 << 19)); }

	// Flip Endian , LSR Right , XOR
	static inline void  E_FEND_LSR_XOR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + (0 << 19)); }

	// Flip Endian , LSR Right ,Set Flag then XOR
	static inline void  E_FEND_LSR_XORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + (0 << 19)); }

	// Flip Endian , LSR Right , ADD
	static inline void  E_FEND_LSR_ADD(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 18) + (0 << 19)); }

	// Flip Endian , LSR Right ,Set Flag then ADD
	static inline void  E_FEND_LSR_ADDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 18) + (0 << 19)); }

	// Flip Endian , LSR Right , SUB
	static inline void  E_FEND_LSR_SUB(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 18) + (0 << 19)); }

	// Flip Endian , LSR Right ,Set Flag then SUB
	static inline void  E_FEND_LSR_SUBS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 18) + (0 << 19)); }

	// Flip Endian , LSR Right , ADC          
	static inline void  E_FEND_LSR_ADC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 18) + (0 << 19)); }

	// Flip Endian , LSR Right ,Set Flag then ADC
	static inline void  E_FEND_LSR_ADCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 18) + (0 << 19)); }

	// Flip Endian , LSR Right , SBC
	static inline void  E_FEND_LSR_SBC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 18) + (0 << 19)); }

	// Flip Endian , LSR Right ,Set Flag then SBC
	static inline void  E_FEND_LSR_SBCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR  
	static inline void  E_COND_FEND_LSR(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR ,Set Flag
	static inline void  E_COND_FEND_LSRS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR , AND
	static inline void  E_COND_FEND_LSR_AND(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR ,Set Flag then AND
	static inline void  E_COND_FEND_LSR_ANDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR , OR
	static inline void  E_COND_FEND_LSR_OR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR ,Set Flag then OR
	static inline void  E_COND_FEND_LSR_ORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR , XOR
	static inline void  E_COND_FEND_LSR_XOR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR ,Set Flag then XOR
	static inline void  E_COND_FEND_LSR_XORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR , ADD
	static inline void  E_COND_FEND_LSR_ADD(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR ,Set Flag then ADD
	static inline void  E_COND_FEND_LSR_ADDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR , SUB
	static inline void  E_COND_FEND_LSR_SUB(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR ,Set Flag then SUB
	static inline void  E_COND_FEND_LSR_SUBS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR , ADC          
	static inline void  E_COND_FEND_LSR_ADC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR ,Set Flag then ADC
	static inline void  E_COND_FEND_LSR_ADCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR , SBC
	static inline void  E_COND_FEND_LSR_SBC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 18) + (0 << 19)); }

	// Conditional Flip Endian , LSR ,Set Flag then SBC
	static inline void  E_COND_FEND_LSR_SBCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (0 << 18) + (0 << 19)); }

	// Bitwise Flip LSR
	// Flip Bitwise , LSR Right  
	static inline void  E_FBIT_LSR(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 18) + (0 << 19)); }

	// Flip Bitwise , LSR Right ,Set Flag
	static inline void  E_FBIT_LSRS(uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 18) + (0 << 19)); }

	// Flip Bitwise , LSR Right , AND
	static inline void  E_FBIT_LSR_AND(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 18) + (0 << 19)); }

	// Flip Bitwise , LSR Right ,Set Flag then AND
	static inline void  E_FBIT_LSR_ANDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 18) + (0 << 19)); }

	// Flip Bitwise , LSR Right , OR
	static inline void  E_FBIT_LSR_OR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 18) + (0 << 19)); }

	// Flip Bitwise , LSR Right ,Set Flag then OR
	static inline void  E_FBIT_LSR_ORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 18) + (0 << 19)); }

	// Flip Bitwise , LSR Right , XOR
	static inline void  E_FBIT_LSR_XOR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 18) + (0 << 19)); }

	// Flip Bitwise , LSR Right ,Set Flag then XOR
	static inline void  E_FBIT_LSR_XORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 18) + (0 << 19)); }

	// Flip Bitwise , LSR Right , ADD
	static inline void  E_FBIT_LSR_ADD(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 18) + (0 << 19)); }

	// Flip Bitwise , LSR Right ,Set Flag then ADD
	static inline void  E_FBIT_LSR_ADDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 18) + (0 << 19)); }

	// Flip Bitwise , LSR Right , SUB
	static inline void  E_FBIT_LSR_SUB(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 18) + (0 << 19)); }

	// Flip Bitwise , LSR Right ,Set Flag then SUB
	static inline void  E_FBIT_LSR_SUBS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 18) + (0 << 19)); }

	// Flip Bitwise , LSR Right , ADC          
	static inline void  E_FBIT_LSR_ADC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 18) + (0 << 19)); }

	// Flip Bitwise , LSR Right ,Set Flag then ADC
	static inline void  E_FBIT_LSR_ADCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 18) + (0 << 19)); }

	// Flip Bitwise , LSR Right , SBC
	static inline void  E_FBIT_LSR_SBC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 18) + (0 << 19)); }

	// Flip Bitwise , LSR Right ,Set Flag then SBC
	static inline void  E_FBIT_LSR_SBCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR  
	static inline void  E_COND_FBIT_LSR(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR ,Set Flag
	static inline void  E_COND_FBIT_LSRS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR , AND
	static inline void  E_COND_FBIT_LSR_AND(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR ,Set Flag then AND
	static inline void  E_COND_FBIT_LSR_ANDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR , OR
	static inline void  E_COND_FBIT_LSR_OR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR ,Set Flag then OR
	static inline void  E_COND_FBIT_LSR_ORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (2 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR , XOR
	static inline void  E_COND_FBIT_LSR_XOR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR ,Set Flag then XOR
	static inline void  E_COND_FBIT_LSR_XORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (3 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR , ADD
	static inline void  E_COND_FBIT_LSR_ADD(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR ,Set Flag then ADD
	static inline void  E_COND_FBIT_LSR_ADDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (4 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR , SUB
	static inline void  E_COND_FBIT_LSR_SUB(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR ,Set Flag then SUB
	static inline void  E_COND_FBIT_LSR_SUBS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (5 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR , ADC          
	static inline void  E_COND_FBIT_LSR_ADC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR ,Set Flag then ADC
	static inline void  E_COND_FBIT_LSR_ADCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (6 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR , SBC
	static inline void  E_COND_FBIT_LSR_SBC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 18) + (0 << 19)); }

	// Conditional Flip Bitwise , LSR ,Set Flag then SBC
	static inline void  E_COND_FBIT_LSR_SBCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t shift5) { bunny_build__add_instruction(0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (7 << 29) + (1 << 18) + (0 << 19)); }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_ANDOR
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1               src2           SFlag              Cond         SRC3                    
	// ANDOR
	static inline void  E_ANDOR(uint32_t dest, uint32_t rsrc, uint32_t rand, uint32_t ror) { if (bunny_build__pass_num) { BUNNY_BUILD_PRINTF(BUNNY_BUILD_WARNING_FLAG"DOUBLE CHECK E_ANDOR ENCODING\n"); } bunny_build__add_instruction(0x16 + (dest << 10) + (rsrc << 14) + (rand << 20) + (0 << 9) + (EU << 5) + (ror << 24)); }
	static inline void  E_ANDORS(uint32_t dest, uint32_t rsrc, uint32_t rand, uint32_t ror) { if (bunny_build__pass_num) { BUNNY_BUILD_PRINTF(BUNNY_BUILD_WARNING_FLAG"WARNING DOUBLE CHECK E_ANDORS ENCODING\n"); } bunny_build__add_instruction(0x16 + (dest << 10) + (rsrc << 14) + (rand << 20) + (1 << 9) + (EU << 5) + (ror << 24)); }
	static inline void  E_COND_ANDOR(uint32_t cond, uint32_t dest, uint32_t rsrc, uint32_t rand, uint32_t ror) { if (bunny_build__pass_num) { BUNNY_BUILD_PRINTF(BUNNY_BUILD_WARNING_FLAG"WARNING DOUBLE CHHCK E_COND_ANDOR ENCODING\n"); } bunny_build__add_instruction(0x16 + (dest << 10) + (rsrc << 14) + (rand << 20) + (0 << 9) + (cond << 5) + (ror << 24)); }
	static inline void  E_COND_ANDORS(uint32_t cond, uint32_t dest, uint32_t rsrc, uint32_t rand, uint32_t ror) { if (bunny_build__pass_num) { BUNNY_BUILD_PRINTF(BUNNY_BUILD_WARNING_FLAG"WARNING DOUBLE CGECK E_COND_ANDORS ENCODING\n"); } bunny_build__add_instruction(0x16 + (dest << 10) + (rsrc << 14) + (rand << 20) + (1 << 9) + (cond << 5) + (ror << 24)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_Shift byte reg Codes
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              src2        SFlag              Cond         Imm                    Extra Operation    Left/Right   Shift/Rotate    Invert
	// Logical Shift  
	static inline void  E_RLSL(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSR(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag
	static inline void  E_RLSLS(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSRS(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then AND
	static inline void  E_RLSL_AND(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSR_AND(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then AND
	static inline void  E_RLSL_ANDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSR_ANDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then OR
	static inline void  E_RLSL_OR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSR_OR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then OR
	static inline void  E_RLSL_ORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSR_ORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then XOR
	static inline void  E_RLSL_XOR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSR_XOR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then XOR
	static inline void  E_RLSL_XORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSR_XORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then ADD
	static inline void  E_RLSL_ADD(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSR_ADD(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then ADD
	static inline void  E_RLSL_ADDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSR_ADDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then SUB
	static inline void  E_RLSL_SUB(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSR_SUB(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then SUB
	static inline void  E_RLSL_SUBS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSR_SUBS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then ADC          
	static inline void  E_RLSL_ADC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSR_ADC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then ADC
	static inline void  E_RLSL_ADCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSR_ADCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then SBC
	static inline void  E_RLSL_SBC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSR_SBC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then SBC
	static inline void  E_RLSL_SBCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_RLSR_SBCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift  
	static inline void  E_COND_RLSL(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSR(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag
	static inline void  E_COND_RLSLS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSRS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then AND
	static inline void  E_COND_RLSL_AND(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSR_AND(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then AND
	static inline void  E_COND_RLSL_ANDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSR_ANDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then OR
	static inline void  E_COND_RLSL_OR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSR_OR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then OR
	static inline void  E_COND_RLSL_ORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSR_ORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then XOR
	static inline void  E_COND_RLSL_XOR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSR_XOR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then XOR
	static inline void  E_COND_RLSL_XORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSR_XORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then ADD
	static inline void  E_COND_RLSL_ADD(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSR_ADD(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then ADD
	static inline void  E_COND_RLSL_ADDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSR_ADDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then SUB
	static inline void  E_COND_RLSL_SUB(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSR_SUB(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then SUB
	static inline void  E_COND_RLSL_SUBS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSR_SUBS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then ADC          
	static inline void  E_COND_RLSL_ADC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSR_ADC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then ADC
	static inline void  E_COND_RLSL_ADCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSR_ADCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and then SBC
	static inline void  E_COND_RLSL_SBC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSR_SBC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18)); }

	// Logical Shift and Set Flag then SBC
	static inline void  E_COND_RLSL_SBCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18)); }
	static inline void  E_COND_RLSR_SBCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18)); }

	//                                                         opcode      Dest            Src1              r2shift        SFlag              Cond         Imm                    Extra Operation    Left/Right   Shift/Rotate  POSTshift
	// Logical Shift and then AND
	static inline void  E_AND_RLSL(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_AND_RLSR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and Set Flag then AND
	static inline void  E_AND_RLSLS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_AND_RLSRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and then OR
	static inline void  E_OR_RLSL(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_OR_RLSR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and Set Flag then OR
	static inline void  E_OR_RLSLS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_OR_RLSRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and then XOR
	static inline void  E_XOR_RLSL(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_XOR_RLSR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and Set Flag then XOR
	static inline void  E_XOR_RLSLS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_XOR_RLSRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and then ADD
	static inline void  E_ADD_RLSL(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_ADD_RLSR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and Set Flag then ADD
	static inline void  E_ADD_RLSLS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_ADD_RLSRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and then SUB
	static inline void  E_SUB_RLSL(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_SUB_RLSR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and Set Flag then SUB
	static inline void  E_SUB_RLSLS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_SUB_RLSRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and then ADC          
	static inline void  E_ADC_RLSL(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_ADC_RLSR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and Set Flag then ADC
	static inline void  E_ADC_RLSLS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_ADC_RLSRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and then SBC
	static inline void  E_SBC_RLSL(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_SBC_RLSR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and Set Flag then SBC
	static inline void  E_SBC_RLSLS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_SBC_RLSRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and then AND
	static inline void  E_COND_AND_RLSL(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_COND_AND_RLSR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and Set Flag then AND
	static inline void  E_COND_AND_RLSLS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_COND_AND_RLSRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and then OR
	static inline void  E_COND_OR_RLSL(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_COND_OR_RLSR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and Set Flag then OR
	static inline void  E_COND_OR_RLSLS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_COND_OR_RLSRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and then XOR
	static inline void  E_COND_XOR_RLSL(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_COND_XOR_RLSR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and Set Flag then XOR
	static inline void  E_COND_XOR_RLSLS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_COND_XOR_RLSRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and then ADD
	static inline void  E_COND_ADD_RLSL(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_COND_ADD_RLSR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and Set Flag then ADD
	static inline void  E_COND_ADD_RLSLS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_COND_ADD_RLSRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and then SUB
	static inline void  E_COND_SUB_RLSL(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_COND_SUB_RLSR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and Set Flag then SUB
	static inline void  E_COND_SUB_RLSLS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_COND_SUB_RLSRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and then ADC          
	static inline void  E_COND_ADC_RLSL(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_COND_ADC_RLSR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and Set Flag then ADC
	static inline void  E_COND_ADC_RLSLS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_COND_ADC_RLSRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and then SBC
	static inline void  E_COND_SBC_RLSL(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_COND_SBC_RLSR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	// Logical Shift and Set Flag then SBC
	static inline void  E_COND_SBC_RLSLS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18) + (1 << 28)); }
	static inline void  E_COND_SBC_RLSRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18) + (1 << 28)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_Shift byte reg with inversion
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Logical Shift  
	static inline void  E_RLSLN(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSRN(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag
	static inline void  E_RLSLNS(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSRNS(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and then AND
	static inline void  E_RLSL_ANDN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSR_ANDN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag then AND
	static inline void  E_RLSL_ANDNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSR_ANDNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and then OR
	static inline void  E_RLSL_ORN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSR_ORN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag then OR
	static inline void  E_RLSL_ORNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSR_ORNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and then XOR
	static inline void  E_RLSL_XORN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSR_XORN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag then XOR
	static inline void  E_RLSL_XORNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSR_XORNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and then ADD
	static inline void  E_RLSL_ADDN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSR_ADDN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag then ADD
	static inline void  E_RLSL_ADDNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSR_ADDNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and then SUB
	static inline void  E_RLSL_SUBN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSR_SUBN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag then SUB
	static inline void  E_RLSL_SUBNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSR_SUBNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and then ADC          
	static inline void  E_RLSL_ADCN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSR_ADCN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag then ADC
	static inline void  E_RLSL_ADCNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSR_ADCNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and then SBC
	static inline void  E_RLSL_SBCN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSR_SBCN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag then SBC
	static inline void  E_RLSL_SBCNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_RLSR_SBCNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift  
	static inline void  E_COND_RLSLN(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSRN(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag
	static inline void  E_COND_RLSLNS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSRNS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and then AND
	static inline void  E_COND_RLSL_ANDN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSR_ANDN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag then AND
	static inline void  E_COND_RLSL_ANDNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSR_ANDNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and then OR
	static inline void  E_COND_RLSL_ORN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSR_ORN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag then OR
	static inline void  E_COND_RLSL_ORNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSR_ORNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and then XOR
	static inline void  E_COND_RLSL_XORN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSR_XORN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag then XOR
	static inline void  E_COND_RLSL_XORNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSR_XORNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and then ADD
	static inline void  E_COND_RLSL_ADDN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSR_ADDN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag then ADD
	static inline void  E_COND_RLSL_ADDNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSR_ADDNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and then SUB
	static inline void  E_COND_RLSL_SUBN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSR_SUBN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag then SUB
	static inline void  E_COND_RLSL_SUBNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSR_SUBNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and then ADC          
	static inline void  E_COND_RLSL_ADCN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSR_ADCN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag then ADC
	static inline void  E_COND_RLSL_ADCNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSR_ADCNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and then SBC
	static inline void  E_COND_RLSL_SBCN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSR_SBCN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	// Logical Shift and Set Flag then SBC
	static inline void  E_COND_RLSL_SBCNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27)); }
	static inline void  E_COND_RLSR_SBCNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27)); }

	//                                                         opcode      Dest            Src1              r2shift        SFlag              Cond         Imm                    Extra Operation    Left/Right   Shift/Rotate   Inv  POSTshift
	// Logical Shift and then AND
	static inline void  E_ANDN_RLSL(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_ANDN_RLSR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and Set Flag then AND
	static inline void  E_ANDN_RLSLS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_ANDN_RLSRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and then OR
	static inline void  E_ORN_RLSL(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_ORN_RLSR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and Set Flag then OR
	static inline void  E_ORN_RLSLS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_ORN_RLSRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and then XOR
	static inline void  E_XORN_RLSL(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_XORN_RLSR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and Set Flag then XOR
	static inline void  E_XORN_RLSLS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_XORN_RLSRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and then ADD
	static inline void  E_ADDN_RLSL(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_ADDN_RLSR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and Set Flag then ADD
	static inline void  E_ADDN_RLSLS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_ADDN_RLSRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and then SUB
	static inline void  E_SUBN_RLSL(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_SUBN_RLSR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and Set Flag then SUB
	static inline void  E_SUBN_RLSLS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_SUBN_RLSRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and then ADC          
	static inline void  E_ADCN_RLSL(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_ADCN_RLSR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and Set Flag then ADC
	static inline void  E_ADCN_RLSLS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_ADCN_RLSRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and then SBC
	static inline void  E_SBCN_RLSL(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_SBCN_RLSR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and Set Flag then SBC
	static inline void  E_SBCN_RLSLS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_SBCN_RLSRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and then AND
	static inline void  E_COND_ANDN_RLSL(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_COND_ANDN_RLSR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and Set Flag then AND
	static inline void  E_COND_ANDN_RLSLS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_COND_ANDN_RLSRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and then OR
	static inline void  E_COND_ORN_RLSL(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_COND_ORN_RLSR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and Set Flag then OR
	static inline void  E_COND_ORN_RLSLS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_COND_ORN_RLSRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and then XOR
	static inline void  E_COND_XORN_RLSL(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_COND_XORN_RLSR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and Set Flag then XOR
	static inline void  E_COND_XORN_RLSLS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_COND_XORN_RLSRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and then ADD
	static inline void  E_COND_ADDN_RLSL(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_COND_ADDN_RLSR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and Set Flag then ADD
	static inline void  E_COND_ADDN_RLSLS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_COND_ADDN_RLSRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and then SUB
	static inline void  E_COND_SUBN_RLSL(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_COND_SUBN_RLSR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and Set Flag then SUB
	static inline void  E_COND_SUBN_RLSLS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_COND_SUBN_RLSRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and then ADC          
	static inline void  E_COND_ADCN_RLSL(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_COND_ADCN_RLSR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and Set Flag then ADC
	static inline void  E_COND_ADCN_RLSLS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_COND_ADCN_RLSRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and then SBC
	static inline void  E_COND_SBCN_RLSL(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_COND_SBCN_RLSR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	// Logical Shift and Set Flag then SBC
	static inline void  E_COND_SBCN_RLSLS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }
	static inline void  E_COND_SBCN_RLSRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)); }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_ROTATE by Reg Codes
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              r2shift        SFlag              Cond         Imm                   Extra Operation    Left/Right   Shift/Rotate
	// Rotate  
	static inline void  E_RROR(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag
	static inline void  E_RRORS(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then AND
	static inline void  E_RROR_AND(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then AND
	static inline void  E_RROR_ANDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then OR
	static inline void  E_RROR_OR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then OR
	static inline void  E_RROR_ORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then XOR
	static inline void  E_RROR_XOR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then XOR
	static inline void  E_RROR_XORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then ADD
	static inline void  E_RROR_ADD(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then ADD
	static inline void  E_RROR_ADDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then SUB
	static inline void  E_RROR_SUB(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then SUB
	static inline void  E_RROR_SUBS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then ADC          
	static inline void  E_RROR_ADC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then ADC
	static inline void  E_RROR_ADCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then SBC
	static inline void  E_RROR_SBC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then SBC
	static inline void  E_RROR_SBCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate  
	static inline void  E_COND_RROR(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag
	static inline void  E_COND_RRORS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then AND
	static inline void  E_COND_RROR_AND(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then AND
	static inline void  E_COND_RROR_ANDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then OR
	static inline void  E_COND_RROR_OR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then OR
	static inline void  E_COND_RROR_ORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then XOR
	static inline void  E_COND_RROR_XOR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then XOR
	static inline void  E_COND_RROR_XORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then ADD
	static inline void  E_COND_RROR_ADD(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then ADD
	static inline void  E_COND_RROR_ADDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then SUB
	static inline void  E_COND_RROR_SUB(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then SUB
	static inline void  E_COND_RROR_SUBS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then ADC          
	static inline void  E_COND_RROR_ADC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then ADC
	static inline void  E_COND_RROR_ADCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then SBC
	static inline void  E_COND_RROR_SBC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and Set Flag then SBC
	static inline void  E_COND_RROR_SBCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18)); }

	// Rotate and then AND
	static inline void  E_AND_RROR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and Set Flag then AND
	static inline void  E_AND_RRORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and then OR
	static inline void  E_OR_RROR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and Set Flag then OR
	static inline void  E_OR_RRORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and then XOR
	static inline void  E_XOR_RROR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and Set Flag then XOR
	static inline void  E_XOR_RRORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and then ADD
	static inline void  E_ADD_RROR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and Set Flag then ADD
	static inline void  E_ADD_RRORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and then SUB
	static inline void  E_SUB_RROR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and Set Flag then SUB
	static inline void  E_SUB_RRORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and then ADC          
	static inline void  E_ADC_RROR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and Set Flag then ADC
	static inline void  E_ADC_RRORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and then SBC
	static inline void  E_SBC_RROR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and Set Flag then SBC
	static inline void  E_SBC_RRORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and then AND
	static inline void  E_COND_AND_RROR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and Set Flag then AND
	static inline void  E_COND_AND_RRORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and then OR
	static inline void  E_COND_OR_RROR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and Set Flag then OR
	static inline void  E_COND_OR_RRORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and then XOR
	static inline void  E_COND_XOR_RROR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and Set Flag then XOR
	static inline void  E_COND_XOR_RRORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and then ADD
	static inline void  E_COND_ADD_RROR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and Set Flag then ADD
	static inline void  E_COND_ADD_RRORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and then SUB
	static inline void  E_COND_SUB_RROR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and Set Flag then SUB
	static inline void  E_COND_SUB_RRORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and then ADC          
	static inline void  E_COND_ADC_RROR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and Set Flag then ADC
	static inline void  E_COND_ADC_RRORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and then SBC
	static inline void  E_COND_SBC_RROR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	// Rotate and Set Flag then SBC
	static inline void  E_COND_SBC_RRORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18) + (1 << 28)); }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       E_ROTATE by Reg Codes and invert ALU result
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              r2shift        SFlag              Cond         Imm                   Extra Operation    Left/Right   Shift/Rotate
	// Rotate  
	static inline void  E_RRORN(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag
	static inline void  E_RRORNS(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and then AND
	static inline void  E_RROR_ANDN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag then AND
	static inline void  E_RROR_ANDNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and then OR
	static inline void  E_RROR_ORN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag then OR
	static inline void  E_RROR_ORNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and then XOR
	static inline void  E_RROR_XORN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag then XOR
	static inline void  E_RROR_XORNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and then ADD
	static inline void  E_RROR_ADDN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag then ADD
	static inline void  E_RROR_ADDNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and then SUB
	static inline void  E_RROR_SUBN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag then SUB
	static inline void  E_RROR_SUBNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and then ADC          
	static inline void  E_RROR_ADCN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag then ADC
	static inline void  E_RROR_ADCNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and then SBC
	static inline void  E_RROR_SBCN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag then SBC
	static inline void  E_RROR_SBCNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate  
	static inline void  E_COND_RRORN(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag
	static inline void  E_COND_RRORNS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and then AND
	static inline void  E_COND_RROR_ANDN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag then AND
	static inline void  E_COND_RROR_ANDNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and then OR
	static inline void  E_COND_RROR_ORN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag then OR
	static inline void  E_COND_RROR_ORNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and then XOR
	static inline void  E_COND_RROR_XORN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag then XOR
	static inline void  E_COND_RROR_XORNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and then ADD
	static inline void  E_COND_RROR_ADDN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag then ADD
	static inline void  E_COND_RROR_ADDNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and then SUB
	static inline void  E_COND_RROR_SUBN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag then SUB
	static inline void  E_COND_RROR_SUBNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and then ADC          
	static inline void  E_COND_RROR_ADCN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag then ADC
	static inline void  E_COND_RROR_ADCNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and then SBC
	static inline void  E_COND_RROR_SBCN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and Set Flag then SBC
	static inline void  E_COND_RROR_SBCNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27)); }

	// Rotate and then AND
	static inline void  E_ANDN_RROR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and Set Flag then AND
	static inline void  E_ANDN_RRORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and then OR
	static inline void  E_ORN_RROR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and Set Flag then OR
	static inline void  E_ORN_RRORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and then XOR
	static inline void  E_XORN_RROR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and Set Flag then XOR
	static inline void  E_XORN_RRORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and then ADD
	static inline void  E_ADDN_RROR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and Set Flag then ADD
	static inline void  E_ADDN_RRORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and then SUB
	static inline void  E_SUBN_RROR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and Set Flag then SUB
	static inline void  E_SUBN_RRORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and then ADC          
	static inline void  E_ADCN_RROR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and Set Flag then ADC
	static inline void  E_ADCN_RRORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and then SBC
	static inline void  E_SBCN_RROR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and Set Flag then SBC
	static inline void  E_SBCN_RRORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and then AND
	static inline void  E_COND_ANDN_RROR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and Set Flag then AND
	static inline void  E_COND_ANDN_RRORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and then OR
	static inline void  E_COND_ORN_RROR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and Set Flag then OR
	static inline void  E_COND_ORN_RRORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and then XOR
	static inline void  E_COND_XORN_RROR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and Set Flag then XOR
	static inline void  E_COND_XORN_RRORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and then ADD
	static inline void  E_COND_ADDN_RROR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and Set Flag then ADD
	static inline void  E_COND_ADDN_RRORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and then SUB
	static inline void  E_COND_SUBN_RROR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and Set Flag then SUB
	static inline void  E_COND_SUBN_RRORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and then ADC          
	static inline void  E_COND_ADCN_RROR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and Set Flag then ADC
	static inline void  E_COND_ADCN_RRORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and then SBC
	static inline void  E_COND_SBCN_RROR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Rotate and Set Flag then SBC
	static inline void  E_COND_SBCN_RRORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       Arithmetical Shift Codes
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              r2shift        SFlag              Cond         Imm                   Extra Operation    Left/Right   Shift/Rotate  Arith/Shift
	// Arith Shift Right  
	static inline void  E_RASR(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag
	static inline void  E_RASRS(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and then AND
	static inline void  E_RASR_AND(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag then AND
	static inline void  E_RASR_ANDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and then OR
	static inline void  E_RASR_OR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag then OR
	static inline void  E_RASR_ORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and then XOR
	static inline void  E_RASR_XOR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag then XOR
	static inline void  E_RASR_XORS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and then ADD
	static inline void  E_RASR_ADD(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag then ADD
	static inline void  E_RASR_ADDS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and then SUB
	static inline void  E_RASR_SUB(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag then SUB
	static inline void  E_RASR_SUBS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and then ADC          
	static inline void  E_RASR_ADC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag then ADC
	static inline void  E_RASR_ADCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and then SBC
	static inline void  E_RASR_SBC(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and Set Flag then SBC
	static inline void  E_RASR_SBCS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift  
	static inline void  E_COND_RASR(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag
	static inline void  E_COND_RASRS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and then AND
	static inline void  E_COND_RASR_AND(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag then AND
	static inline void  E_COND_RASR_ANDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and then OR
	static inline void  E_COND_RASR_OR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag then OR
	static inline void  E_COND_RASR_ORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and then XOR
	static inline void  E_COND_RASR_XOR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag then XOR
	static inline void  E_COND_RASR_XORS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and then ADD
	static inline void  E_COND_RASR_ADD(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag then ADD
	static inline void  E_COND_RASR_ADDS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and then SUB
	static inline void  E_COND_RASR_SUB(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag then SUB
	static inline void  E_COND_RASR_SUBS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and then ADC          
	static inline void  E_COND_RASR_ADC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag then ADC
	static inline void  E_COND_RASR_ADCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and then SBC
	static inline void  E_COND_RASR_SBC(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18)); }

	// Conditional Arith Shift and Set Flag then SBC
	static inline void  E_COND_RASR_SBCS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18)); }

	// Arith Shift Right and then AND
	static inline void  E_AND_RASR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Arith Shift Right and Set Flag then AND
	static inline void  E_AND_RASRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Arith Shift Right and then OR
	static inline void  E_OR_RASR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Arith Shift Right and Set Flag then OR
	static inline void  E_OR_RASRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Arith Shift Right and then XOR
	static inline void  E_XOR_RASR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Arith Shift Right and Set Flag then XOR
	static inline void  E_XOR_RASRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Arith Shift Right and then ADD
	static inline void  E_ADD_RASR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Arith Shift Right and Set Flag then ADD
	static inline void  E_ADD_RASRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Arith Shift Right and then SUB
	static inline void  E_SUB_RASR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Arith Shift Right and Set Flag then SUB
	static inline void  E_SUB_RASRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Arith Shift Right and then ADC          
	static inline void  E_ADC_RASR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Arith Shift Right and Set Flag then ADC
	static inline void  E_ADC_RASRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Arith Shift Right and then SBC
	static inline void  E_SBC_RASR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Arith Shift Right and Set Flag then SBC
	static inline void  E_SBC_RASRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Conditional Arith Shift and then AND
	static inline void  E_COND_AND_RASR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Conditional Arith Shift and Set Flag then AND
	static inline void  E_COND_AND_RASRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Conditional Arith Shift and then OR
	static inline void  E_COND_OR_RASR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Conditional Arith Shift and Set Flag then OR
	static inline void  E_COND_OR_RASRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Conditional Arith Shift and then XOR
	static inline void  E_COND_XOR_RASR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Conditional Arith Shift and Set Flag then XOR
	static inline void  E_COND_XOR_RASRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Conditional Arith Shift and then ADD
	static inline void  E_COND_ADD_RASR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Conditional Arith Shift and Set Flag then ADD
	static inline void  E_COND_ADD_RASRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Conditional Arith Shift and then SUB
	static inline void  E_COND_SUB_RASR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Conditional Arith Shift and Set Flag then SUB
	static inline void  E_COND_SUB_RASRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Conditional Arith Shift and then ADC          
	static inline void  E_COND_ADC_RASR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Conditional Arith Shift and Set Flag then ADC
	static inline void  E_COND_ADC_RASRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Conditional Arith Shift and then SBC
	static inline void  E_COND_SBC_RASR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	// Conditional Arith Shift and Set Flag then SBC
	static inline void  E_COND_SBC_RASRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18) + (1 << 28)); }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       Arithmetical Shift Codes with invert ALU
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1              r2shift        SFlag              Cond         Imm                   Extra Operation    Left/Right   Shift/Rotate  pOSTShift
	// Arith Shift Right  
	static inline void  E_RASRN(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and Set Flag 
	static inline void  E_RASRNS(uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and then AND
	static inline void  E_RASR_ANDN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and Set Flag then AND
	static inline void  E_RASR_ANDNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and then OR
	static inline void  E_RASR_ORN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and Set Flag then OR
	static inline void  E_RASR_ORNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and then XOR
	static inline void  E_RASR_XORN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and Set Flag then XOR
	static inline void  E_RASR_XORNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and then ADD
	static inline void  E_RASR_ADDN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and Set Flag then ADD
	static inline void  E_RASR_ADDNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and then SUB
	static inline void  E_RASR_SUBN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and Set Flag then SUB
	static inline void  E_RASR_SUBNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and then ADC          
	static inline void  E_RASR_ADCN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and Set Flag then ADC
	static inline void  E_RASR_ADCNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and then SBC
	static inline void  E_RASR_SBCN(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and Set Flag then SBC
	static inline void  E_RASR_SBCNS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift  
	static inline void  E_COND_RASRN(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift and Set Flag
	static inline void  E_COND_RASRNS(uint32_t cond, uint32_t dest, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift and then AND
	static inline void  E_COND_RASR_ANDN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift and Set Flag then AND
	static inline void  E_COND_RASR_ANDNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift and then OR
	static inline void  E_COND_RASR_ORN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift and Set Flag then OR
	static inline void  E_COND_RASR_ORNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift and then XOR
	static inline void  E_COND_RASR_XORN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift and Set Flag then XOR
	static inline void  E_COND_RASR_XORNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift and then ADD
	static inline void  E_COND_RASR_ADDN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift and Set Flag then ADD
	static inline void  E_COND_RASR_ADDNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift and then SUB
	static inline void  E_COND_RASR_SUBN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift and Set Flag then SUB
	static inline void  E_COND_RASR_SUBNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift and then ADC          
	static inline void  E_COND_RASR_ADCN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift and Set Flag then ADC
	static inline void  E_COND_RASR_ADCNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift and then SBC
	static inline void  E_COND_RASR_SBCN(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Conditional Arith Shift and Set Flag then SBC
	static inline void  E_COND_RASR_SBCNS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27)); }

	// Arith Shift Right and then AND
	static inline void  E_ANDN_RASR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Arith Shift Right and Set Flag then AND
	static inline void  E_ANDN_RASRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Arith Shift Right and then OR
	static inline void  E_ORN_RASR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Arith Shift Right and Set Flag then OR
	static inline void  E_ORN_RASRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Arith Shift Right and then XOR
	static inline void  E_XORN_RASR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Arith Shift Right and Set Flag then XOR
	static inline void  E_XORN_RASRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Arith Shift Right and then ADD
	static inline void  E_ADDN_RASR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Arith Shift Right and Set Flag then ADD
	static inline void  E_ADDN_RASRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Arith Shift Right and then SUB
	static inline void  E_SUBN_RASR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Arith Shift Right and Set Flag then SUB
	static inline void  E_SUBN_RASRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Arith Shift Right and then ADC          
	static inline void  E_ADCN_RASR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Arith Shift Right and Set Flag then ADC
	static inline void  E_ADCN_RASRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Arith Shift Right and then SBC
	static inline void  E_SBCN_RASR(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Arith Shift Right and Set Flag then SBC
	static inline void  E_SBCN_RASRS(uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Conditional Arith Shift and then AND
	static inline void  E_COND_ANDN_RASR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Conditional Arith Shift and Set Flag then AND
	static inline void  E_COND_ANDN_RASRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Conditional Arith Shift and then OR
	static inline void  E_COND_ORN_RASR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Conditional Arith Shift and Set Flag then OR
	static inline void  E_COND_ORN_RASRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Conditional Arith Shift and then XOR
	static inline void  E_COND_XORN_RASR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Conditional Arith Shift and Set Flag then XOR
	static inline void  E_COND_XORN_RASRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Conditional Arith Shift and then ADD
	static inline void  E_COND_ADDN_RASR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Conditional Arith Shift and Set Flag then ADD
	static inline void  E_COND_ADDN_RASRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Conditional Arith Shift and then SUB
	static inline void  E_COND_SUBN_RASR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Conditional Arith Shift and Set Flag then SUB
	static inline void  E_COND_SUBN_RASRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Conditional Arith Shift and then ADC          
	static inline void  E_COND_ADCN_RASR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Conditional Arith Shift and Set Flag then ADC
	static inline void  E_COND_ADCN_RASRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Conditional Arith Shift and then SBC
	static inline void  E_COND_SBCN_RASR(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	// Conditional Arith Shift and Set Flag then SBC
	static inline void  E_COND_SBCN_RASRS(uint32_t cond, uint32_t dest, uint32_t roperand, uint32_t r2shift, uint32_t rshift) { bunny_build__add_instruction(0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)); }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       Bit Manipulate
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                         opcode      Dest            Src1               src2           SFlag              Cond         Imm                  Extra Operation     ShiftByByte    Neg/Pos Mask 
	// Bit test by byte 
	static inline void  E_BTST(uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (EU << 5) + (0 << 24) + (1 << 29) + (1 << 18) + (1 << 31)); }
	static inline void  E_BCLR(uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (EU << 5) + (0 << 24) + (1 << 29) + (1 << 18) + (0 << 31)); }
	static inline void  E_BSET(uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (EU << 5) + (0 << 24) + (2 << 29) + (1 << 18) + (1 << 31)); }
	static inline void  E_BTOG(uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (EU << 5) + (0 << 24) + (3 << 29) + (1 << 18) + (1 << 31)); }

	// Bit test by byte with set flags
	static inline void  E_BTSTS(uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (EU << 5) + (0 << 24) + (1 << 29) + (1 << 18) + (1 << 31)); }
	static inline void  E_BCLRS(uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (EU << 5) + (0 << 24) + (1 << 29) + (1 << 18) + (0 << 31)); }
	static inline void  E_BSETS(uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (EU << 5) + (0 << 24) + (2 << 29) + (1 << 18) + (1 << 31)); }
	static inline void  E_BTOGS(uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (EU << 5) + (0 << 24) + (3 << 29) + (1 << 18) + (1 << 31)); }

	// Conditional Bit test by byte 
	static inline void  E_COND_BTST(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (cond << 5) + (0 << 24) + (1 << 29) + (1 << 18) + (1 << 31)); }
	static inline void  E_COND_BCLR(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (cond << 5) + (0 << 24) + (1 << 29) + (1 << 18) + (0 << 31)); }
	static inline void  E_COND_BSET(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (cond << 5) + (0 << 24) + (2 << 29) + (1 << 18) + (1 << 31)); }
	static inline void  E_COND_BTOG(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (cond << 5) + (0 << 24) + (3 << 29) + (1 << 18) + (1 << 31)); }

	// Conditional Bit test by byte with set flags
	static inline void  E_COND_BTSTS(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (cond << 5) + (0 << 24) + (1 << 29) + (1 << 18) + (1 << 31)); }
	static inline void  E_COND_BCLRS(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (cond << 5) + (0 << 24) + (1 << 29) + (1 << 18) + (0 << 31)); }
	static inline void  E_COND_BSETS(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (cond << 5) + (0 << 24) + (2 << 29) + (1 << 18) + (1 << 31)); }
	static inline void  E_COND_BTOGS(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t rbit) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (cond << 5) + (0 << 24) + (3 << 29) + (1 << 18) + (1 << 31)); }

	// Bit test by imm 
	static inline void  E_BTST_IMM(uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (1 << 31)); }
	static inline void  E_BCLR_IMM(uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (0 << 31)); }
	static inline void  E_BSET_IMM(uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + (1 << 31)); }
	static inline void  E_BTOG_IMM(uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + (1 << 31)); }

	// Bit test by imm with set flags
	static inline void  E_BTST_IMMS(uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (1 << 31)); }
	static inline void  E_BCLR_IMMS(uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (0 << 31)); }
	static inline void  E_BSET_IMMS(uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + (1 << 31)); }
	static inline void  E_BTOG_IMMS(uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + (1 << 31)); }

	// Conditional Bit test by imm 
	static inline void  E_COND_BTST_IMM(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (1 << 31)); }
	static inline void  E_COND_BCLR_IMM(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (0 << 31)); }
	static inline void  E_COND_BSET_IMM(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + (1 << 31)); }
	static inline void  E_COND_BTOG_IMM(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + (1 << 31)); }

	// Conditional Bit test by imm with set flags
	static inline void  E_COND_BTST_IMMS(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (1 << 31)); }
	static inline void  E_COND_BCLR_IMMS(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + (0 << 31)); }
	static inline void  E_COND_BSET_IMMS(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + (1 << 31)); }
	static inline void  E_COND_BTOG_IMMS(uint32_t cond, uint32_t dest, uint32_t rdata, uint32_t bit5) { bunny_build__add_instruction(0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + (1 << 31)); }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                      Tight Loop
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static inline void  E_TIGHT_LOOP(uint32_t rend, uint32_t rcount) { bunny_build__add_instruction(0x1A + (rend << 14) + (rcount << 20)); }
	static inline void  E_COND_TIGHT_LOOP(uint32_t cond, uint32_t rend, uint32_t rcount) { bunny_build__add_instruction(0x1A + (rend << 14) + (rcount << 20) + (cond << 5)); }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                    Boolean Detect
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                                Opcode     Dest           Vector/Single       NoUpdateRA       LargeVectors    Cond              Table
	static inline void  E_HOLD() { bunny_build__add_instruction(0x1C + (PC << 10) + (1 << 15) + (0 << 18) + (0 << 19) + (EU << 5)); }
	static inline void  E_COND_HOLD(uint32_t cond) { bunny_build__add_instruction(0x1C + (PC << 10) + (1 << 15) + (0 << 18) + (0 << 19) + (cond << 5)); }

	// Small Vector Versions
	static inline void  E_VECTORED_HOLD(uint32_t table) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (0 << 18) + (0 << 19) + (EU << 5) + (table << 20)); }
	static inline void  E_COND_VECTORED_HOLD(uint32_t cond, uint32_t table) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (0 << 18) + (0 << 19) + (cond << 5) + (table << 20)); }
	static inline void  E_VECTORED_HOLD_NRA(uint32_t table) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (1 << 18) + (0 << 19) + (EU << 5) + (table << 20)); }
	static inline void  E_COND_VECTORED_HOLD_NRA(uint32_t cond, uint32_t table) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (1 << 18) + (0 << 19) + (cond << 5) + (table << 20)); }

	// Large Vector Versions
	static inline void  E_VECTORED_HOLD_LV(uint32_t table) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (0 << 18) + (1 << 19) + (EU << 5) + (table << 20)); }
	static inline void  E_COND_VECTORED_HOLD_LV(uint32_t cond, uint32_t table) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (0 << 18) + (1 << 19) + (cond << 5) + (table << 20)); }
	static inline void  E_VECTORED_HOLD_LV_NRA(uint32_t table) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (1 << 18) + (1 << 19) + (EU << 5) + (table << 20)); }
	static inline void  E_COND_VECTORED_HOLD_LV_NRA(uint32_t cond, uint32_t table) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (1 << 18) + (1 << 19) + (cond << 5) + (table << 20)); }

	/// Accelarated Vectored_hold
	// Small Vector Versions
	static inline void  E_ACC_VECTORED_HOLD(uint32_t table, uint32_t vectors) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (0 << 18) + (0 << 19) + (EU << 5) + (table << 20) + (1 << 9) + (vectors << 24)); }
	static inline void  E_COND_ACC_VECTORED_HOLD(uint32_t cond, uint32_t table, uint32_t vectors) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (0 << 18) + (0 << 19) + (cond << 5) + (table << 20) + (1 << 9) + (vectors << 24)); }
	static inline void  E_ACC_VECTORED_HOLD_NRA(uint32_t table, uint32_t vectors) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (1 << 18) + (0 << 19) + (EU << 5) + (table << 20) + (1 << 9) + (vectors << 24)); }
	static inline void  E_COND_ACC_VECTORED_HOLD_NRA(uint32_t cond, uint32_t table, uint32_t vectors) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (1 << 18) + (0 << 19) + (cond << 5) + (table << 20) + (1 << 9) + (vectors << 24)); }

	// Large Vector Versions
	static inline void  E_ACC_VECTORED_HOLD_LV(uint32_t table, uint32_t vectors) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (0 << 18) + (1 << 19) + (EU << 5) + (table << 20) + (1 << 9) + (vectors << 24)); }
	static inline void  E_COND_ACC_VECTORED_HOLD_LV(uint32_t cond, uint32_t table, uint32_t vectors) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (0 << 18) + (1 << 19) + (cond << 5) + (table << 20) + (1 << 9) + (vectors << 24)); }
	static inline void  E_ACC_VECTORED_HOLD_LV_NRA(uint32_t table, uint32_t vectors) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (1 << 18) + (1 << 19) + (EU << 5) + (table << 20) + (1 << 9) + (vectors << 24)); }
	static inline void  E_COND_ACC_VECTORED_HOLD_LV_NRA(uint32_t cond, uint32_t table, uint32_t vectors) { bunny_build__add_instruction(0x1C + (table << 10) + (0 << 15) + (1 << 18) + (1 << 19) + (cond << 5) + (table << 20) + (1 << 9) + (vectors << 24)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       Reg offset Read
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                        opcode      Rdata Dest       Pointer         WData Source        Offset             SizeWord    Signed Access  Cond        Write              
	// LDR (Load, Load Byte, LoadByteSigned)
	static inline void  E_LDR_REG(uint32_t dest, uint32_t source, uint32_t offset) { bunny_build__add_instruction(0x1D + (dest << 10) + (source << 14) + (offset << 24) + (1 << 18) + (0 << 21) + (EU << 5)); }
	static inline void  E_LDR_REGB(uint32_t dest, uint32_t source, uint32_t offset) { bunny_build__add_instruction(0x1D + (dest << 10) + (source << 14) + (offset << 24) + (0 << 18) + (0 << 21) + (EU << 5)); }
	static inline void  E_LDR_REGBS(uint32_t dest, uint32_t source, uint32_t offset) { bunny_build__add_instruction(0x1D + (dest << 10) + (source << 14) + (offset << 24) + (0 << 18) + (1 << 21) + (EU << 5)); }

	// Conditional LDR (Load, Load Byte, LoadByteSigned)
	static inline void  E_COND_LDR_REG(uint32_t cond, uint32_t dest, uint32_t source, uint32_t offset) { bunny_build__add_instruction(0x1D + (dest << 10) + (source << 14) + (offset << 24) + (1 << 18) + (0 << 21) + (cond << 5)); }
	static inline void  E_COND_LDR_REGB(uint32_t cond, uint32_t dest, uint32_t source, uint32_t offset) { bunny_build__add_instruction(0x1D + (dest << 10) + (source << 14) + (offset << 24) + (0 << 18) + (0 << 21) + (cond << 5)); }
	static inline void  E_COND_LDR_REGBS(uint32_t cond, uint32_t dest, uint32_t source, uint32_t offset) { bunny_build__add_instruction(0x1D + (dest << 10) + (source << 14) + (offset << 24) + (0 << 18) + (1 << 21) + (cond << 5)); }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                       Reg offset Write
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                       opcode      Rdata Dest         Pointer       WData Source        Offset             SizeWord    Signed Access  Cond         Write                              
	// STR (Load, Load Byte, LoadByteSigned)
	static inline void  E_STR_REG(uint32_t raddr, uint32_t rdata, uint32_t roffset) { bunny_build__add_instruction(0x1D + (raddr << 14) + (rdata << 20) + (roffset << 24) + (1 << 18) + (0 << 11) + (EU << 5) + (1 << 30)); }
	static inline void  E_STR_REGB(uint32_t raddr, uint32_t rdata, uint32_t roffset) { bunny_build__add_instruction(0x1D + (raddr << 14) + (rdata << 20) + (roffset << 24) + (0 << 18) + (0 << 11) + (EU << 5) + (1 << 30)); }

	// Conditional STR (Load, Load Byte, LoadByteSigned)
	static inline void  E_COND_STR_REG(uint32_t cond, uint32_t raddr, uint32_t rdata, uint32_t roffset) { bunny_build__add_instruction(0x1D + (raddr << 14) + (rdata << 20) + (roffset << 24) + (1 << 18) + (0 << 11) + (cond << 5) + (1 << 30)); }
	static inline void  E_COND_STR_REGB(uint32_t cond, uint32_t raddr, uint32_t rdata, uint32_t roffset) { bunny_build__add_instruction(0x1D + (raddr << 14) + (rdata << 20) + (roffset << 24) + (0 << 18) + (0 << 11) + (cond << 5) + (1 << 30)); }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                     GPO modify Byte
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static inline void  E_MODIFY_GPO_BYTE(uint32_t andmask, uint32_t ormask, uint32_t xormask) { if (bunny_build__pass_num) { BUNNY_BUILD_PRINTF(BUNNY_BUILD_WARNING_FLAG"DOUBLE CHECK ENCODING OF E_MODIFY_GPO_BYTE \n"); } bunny_build__add_instruction(0x1E + (andmask << 8) + (ormask << 16) + (xormask << 24)); }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                    HeartBeat opcodes
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static inline void  E_HEART_RYTHM_IMM(uint32_t val16imm) { bunny_build__add_instruction(0x32 + (val16imm << 16)); }
	static inline void  E_HEART_RYTHM(uint32_t r16bit) { bunny_build__add_instruction(0x32 + (r16bit << 14) + (1 << 9)); }
	static inline void  E_SYNCH_ALL_TO_BEAT(uint32_t on1imm) { bunny_build__add_instruction(0x52 + (on1imm << 31)); }
	static inline void  E_WAIT_FOR_BEAT() { bunny_build__add_instruction(0x72); }


#ifdef __cplusplus
}
#endif

#endif
