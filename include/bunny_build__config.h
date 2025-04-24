/*

Sample bunny build configs for zephyr, the host pc test sample and some of the mcx/lpc55 sampless

*/


#include "bunny_build__targets.h"

#ifndef _BUNNY_BUILD_CONF_H
#define _BUNNY_BUILD_CONF_H

#ifdef  __ZEPHYR__

#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>

#if CONFIG_SOC_SERIES_LPC55XXX == 1
	#define LPC_EZH_ARCH_B_CON_BASE 			LPC_EZH_ARCH_B_CON_BASE__LPC556x
#else
	#warning "Need to check for other zephyr SOC options"
	#define LPC_EZH_ARCH_B_CON_BASE 			LPC_EZH_ARCH_B_CON_BASE__MCX
#endif


	#define BUNNY_BUILD_PRINTF					 printk
	#define BUNNY_BUILD_MAX_LABELS				 64


	/*
		Output formatting for printf messages
	*/

	#define VT100_RED     "\033[31;40m"
	#define VT100_GREEN   "\033[32;40m"
	#define VT100_YELLOW  "\033[33;40m"
	#define VT100_BLUE    "\033[34;40m"
	#define VT100_MAGENTA "\033[35;40m"
	#define VT100_CYAN    "\033[36;40m"
	#define VT100_WHITE   "\033[37;40m"
	#define VT100_DEFAULT  VT100_WHITE


	//#define BUNNY_BUILD_ERROR_FLAG		VT100_RED "[ERROR] " VT100_DEFAULT
	//#define BUNNY_BUILD_WARNING_FLAG		VT100_YELLOW "[WARNING] " VT100_DEFAULT
	//#define BUNNY_BUILD_INFO_FLAG			VT100_GREEN "[INFO] " VT100_DEFAULT

	#define BUNNY_BUILD_ERROR_FLAG		
	#define BUNNY_BUILD_WARNING_FLAG	
	#define BUNNY_BUILD_INFO_FLAG		

#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__APPLE__) || defined(__MACH__) || defined(__linux__)

	#include <assert.h>
	#include <stdbool.h>
	#include <stdint.h>
	#include <string.h>
	#include <stdlib.h>
	#include <stdio.h>


	#define LPC_EZH_ARCH_B_CON_BASE 			 LPC_EZH_ARCH_B_CON_BASE__MCX

	#define BUNNY_BUILD_PRINTF					 printf
	#define BUNNY_BUILD_MAX_LABELS				 64

	/*
		Output formatting for printf messages
	*/

	#define VT100_RED     "\033[31;40m"
	#define VT100_GREEN   "\033[32;40m"
	#define VT100_YELLOW  "\033[33;40m"
	#define VT100_BLUE    "\033[34;40m"
	#define VT100_MAGENTA "\033[35;40m"
	#define VT100_CYAN    "\033[36;40m"
	#define VT100_WHITE   "\033[37;40m"
	#define VT100_DEFAULT  VT100_WHITE


	#define BUNNY_BUILD_ERROR_FLAG		VT100_RED "[ERROR] " VT100_DEFAULT
	#define BUNNY_BUILD_WARNING_FLAG	VT100_YELLOW "[WARNING] " VT100_DEFAULT
	#define BUNNY_BUILD_INFO_FLAG		VT100_GREEN "[INFO] " VT100_DEFAULT

#endif


#ifdef __MCUXPRESSO


	#include "board.h"
	#include "fsl_common.h"
	#include "fsl_debug_console.h"

	#ifdef CPU_MCXN947VDF

		#define LPC_EZH_ARCH_B_CON_BASE 			 LPC_EZH_ARCH_B_CON_BASE__MCX

	#endif


	#ifdef CPU_LPC55S69JBD100
			#define LPC_EZH_ARCH_B_CON_BASE 			 LPC_EZH_ARCH_B_CON_BASE__LPC556x
	#endif


		#define VT100_RED     "\033[31;40m"
		#define VT100_GREEN   "\033[32;40m"
		#define VT100_YELLOW  "\033[33;40m"
		#define VT100_BLUE    "\033[34;40m"
		#define VT100_MAGENTA "\033[35;40m"
		#define VT100_CYAN    "\033[36;40m"
		#define VT100_WHITE   "\033[37;40m"
		#define VT100_DEFAULT  VT100_WHITE


		#define BUNNY_BUILD_ERROR_FLAG				VT100_RED "[ERROR] " VT100_DEFAULT
		#define BUNNY_BUILD_WARNING_FLAG			VT100_YELLOW "[WARNING] " VT100_DEFAULT
		#define BUNNY_BUILD_INFO_FLAG				VT100_GREEN "[INFO] " VT100_DEFAULT

		#define BUNNY_BUILD_PRINTF 					 PRINTF
		#define BUNNY_BUILD_MAX_LABELS				 64



#endif


#endif 
