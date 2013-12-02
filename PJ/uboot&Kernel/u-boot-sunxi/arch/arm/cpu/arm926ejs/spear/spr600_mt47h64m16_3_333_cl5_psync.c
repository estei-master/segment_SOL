/*
 * (C) Copyright 2000-2009
 * Vipin Kumar, ST Microelectronics, vipin.kumar@st.com
 *
 * SPDX-License-Identifier:	GPL-2.0+ 
 */

#include <common.h>

#if (CONFIG_DDR_PLL2 || CONFIG_DDR_2HCLK)

const u32 mpmc_conf_vals[CONFIG_SPEAR_MPMCREGS] = {
#if (CONFIG_DDR_PLL2)
	0x00000001,
	0x00000000,
#elif (CONFIG_DDR_2HCLK)
	0x02020201,
	0x02020202,
#endif
	0x01000000,
	0x00000101,
	0x00000101,
	0x01000000,
	0x00010001,
	0x00000100,
	0x01010001,
	0x00000201,
	0x01000101,
	0x06000002,
	0x06060106,
	0x03050502,
	0x03040404,
	0x02020503,
#ifdef CONFIG_X600
	0x02030206,
#else
	0x02010106,
#endif
	0x03000405,
	0x03040202,
	0x04000305,
	0x0707073f,
	0x07070707,
	0x06060607,
	0x06060606,
	0x05050506,
	0x05050505,
	0x04040405,
	0x04040404,
	0x03030304,
	0x03030303,
	0x02020203,
	0x02020202,
	0x01010102,
	0x01010101,
	0x0a0a0a01,
	0x0000023f,
	0x00050a00,
	0x11000000,
	0x00001302,
	0x00000A0A,
#ifdef CONFIG_X600
	0x7f000000,
	0x005c0000,
#else
	0x72000000,
	0x00550000,
#endif
	0x2b050e86,
	0x00640064,
	0x00640064,
	0x00640064,
	0x00000064,
	0x00200020,
	0x00200020,
	0x00200020,
	0x00200020,
	0x00200020,
	0x00200020,
	0x00200020,
	0x00000a24,
	0x43C20000,
	0x5b1c00c8,
	0x00c8002e,
	0x00000000,
	0x0001046b,
	0x00000000,
	0x03030100,
	0x03030303,
	0x03030303,
	0x03030303,
	0x00210000,
	0x00010021,
	0x00200000,
	0x006c0090,
	0x003fffff,
	0x003fffff,
	0x00000000,
	0x00000000,
	0x003fffff,
	0x003fffff,
	0x00000000,
	0x00000000,
	0x003fffff,
	0x003fffff,
	0x00000000,
	0x00000000,
	0x003fffff,
	0x003fffff,
	0x00000000,
	0x00000000,
	0x003fffff,
	0x003fffff,
	0x00000000,
	0x00000000,
	0x003fffff,
	0x003fffff,
	0x00000000,
	0x00000000,
	0x003fffff,
	0x003fffff,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000
};
#endif
