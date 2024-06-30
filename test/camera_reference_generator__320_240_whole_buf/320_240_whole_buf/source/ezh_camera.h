#ifndef EZH_CAMERA_H
#define EZH_CAMERA_H

#define EZH_API_MEMORY_ADDRESS 0x04000000/*ramx*/

typedef void (*ezh_func_t)(void);

typedef struct _ezh_flexio_funcs_t
{
   ezh_func_t EZH_Camera_320240_Whole_Buf;
   ezh_func_t EZH_Camera_320240_Div16_Buf;
	 ezh_func_t EZH_Camera_480320_Whole_Buf;
	 ezh_func_t EZH_Camera_320240_GrayScale_Div4_Buf;
	 ezh_func_t EZH_Camera_320240_GrayScale_Div16_Buf;
	 ezh_func_t EZH_Camera_384_384_Div16_Buf;
	 ezh_func_t EZH_Camera_320480_Whole_Buf;
} ezh_flexio_funcs_t;

#endif