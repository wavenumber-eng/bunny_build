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


#include "ezh_arch.h"



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


#ifdef __cplusplus
}
#endif

#endif

#include "bunny_build__instr.h"
#include "bunny_build__psuedo_instr.h"




