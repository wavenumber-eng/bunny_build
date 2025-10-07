

#ifndef BUNNY_BUILD_PSUEDO_INSTR_H
#define BUNNY_BUILD_PSUEDO_INSTR_H


#ifdef __cplusplus
extern "C" {
#endif


void E_LABEL(const char* label);

//This one is probably no longer needed since we can resolve labels
//Leaving to throw an error to port old programs
void E_DCD(uint32_t loc) ;

void E_DCD_VAL(uint32_t val);

/*
 * E_END() is a common pattern to have the EZH hold forever
 *
 * This is useful if you have multiple EZH programs and you need it
 * to sit idle and not use up bandwidth on the AHB bus
 *
 */

void E_END();

/*
 * Loads a 32-bit immediate value into a reg.
 *
 * this psuedo instrucction is needed as ezh immediate loads are 11-bit
 */
void E_LOAD_32IMM(uint32_t rx, uint32_t imm);

#ifdef __cplusplus
}
#endif

#endif
