#ifndef EZH_ARCH_H
#define EZH_ARCH_H

#ifdef __cplusplus
extern "C" {
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

#ifdef __cplusplus
}
#endif


#endif
