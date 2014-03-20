/*

2.4 kbps MELP Proposed Federal Standard speech coder

Fixed-point C code, version 1.0

Copyright (c) 1998, Texas Instruments, Inc.

Texas Instruments has intellectual property rights on the MELP
algorithm.	The Texas Instruments contact for licensing issues for
commercial and non-government use is William Gordon, Director,
Government Contracts, Texas Instruments Incorporated, Semiconductor
Group (phone 972 480 7442).

The fixed-point version of the voice codec Mixed Excitation Linear
Prediction (MELP) is based on specifications on the C-language software
simulation contained in GSM 06.06 which is protected by copyright and
is the property of the European Telecommunications Standards Institute
(ETSI). This standard is available from the ETSI publication office
tel. +33 (0)4 92 94 42 58. ETSI has granted a license to United States
Department of Defense to use the C-language software simulation contained
in GSM 06.06 for the purposes of the development of a fixed-point
version of the voice codec Mixed Excitation Linear Prediction (MELP).
Requests for authorization to make other use of the GSM 06.06 or
otherwise distribute or modify them need to be addressed to the ETSI
Secretariat fax: +33 493 65 47 16.

*/

#ifndef _MATHHALF_H_
#define _MATHHALF_H_

#ifdef __CC_ARM

#define ARM_MATH_CM4
#define __FPU_PRESENT 1

#include <arm_math.h>

#include <dspfns.h>
#endif

/* addition */
int16_t	add(int16_t var1, int16_t var2);                     /* 1 ops */

int16_t	sub(int16_t var1, int16_t var2);                     /* 1 ops */

int32_t	L_add(int32_t L_var1, int32_t L_var2);                 /* 2 ops */

int32_t	L_sub(int32_t L_var1, int32_t L_var2);                 /* 2 ops */

/* multiplication */

int16_t	mult(int16_t var1, int16_t var2);                    /* 1 ops */

int32_t	L_mult(int16_t var1, int16_t var2);                  /* 1 ops */

/* arithmetic shifts */

int16_t	shr(int16_t var1, int16_t var2);                     /* 1 ops */

int16_t	shl(int16_t var1, int16_t var2);                     /* 1 ops */

int32_t	L_shr(int32_t L_var1, int16_t var2);                  /* 2 ops */

int32_t	L_shl(int32_t L_var1, int16_t var2);                  /* 2 ops */

int16_t	shift_r(int16_t var, int16_t var2);                  /* 2 ops */

int32_t	L_shift_r(int32_t L_var, int16_t var2);               /* 3 ops */

/* absolute value  */

int16_t	abs_s(int16_t var1);                                   /* 1 ops */

int32_t	L_abs(int32_t var1);                                    /* 3 ops */

/* multiply accumulate	*/

int32_t	L_mac(int32_t L_var3, int16_t var1, int16_t var2);	  /* 1 op */

int32_t	L_msu(int32_t L_var3, int16_t var1, int16_t var2);   /* 1 op */

int16_t	msu_r(int32_t L_var3, int16_t var1, int16_t var2);   /* 2 op */

/* negation  */

int16_t	negate(int16_t var1);                                  /* 1 ops */

int32_t	L_negate(int32_t L_var1);                               /* 2 ops */

/* Accumulator manipulation */

int32_t	L_deposit_l(int16_t var1);                             /* 1 ops */

int32_t	L_deposit_h(int16_t var1);                             /* 1 ops */

int16_t	extract_l(int32_t L_var1);                              /* 1 ops */

int16_t	extract_h(int32_t L_var1);                              /* 1 ops */

/* Round */

int16_t	round(int32_t L_var1);                                  /* 1 ops */

/* Normalization */

int16_t	norm_l(int32_t L_var1);                                /* 30 ops */

int16_t	norm_s(int16_t var1);                                 /* 15 ops */

/* Division */
#ifdef __arm__
	#define divide_s div_s
#else
	int16_t	divide_s(int16_t var1, int16_t var2);               /* 18 ops */
#endif

/* -------------------------------------------------------------------------- */
/* 40-Bit Routines....added by Andre 11/23/99 */

/* new 40 bits basic operators */

Word40 L40_add(Word40 acc, int32_t L_var1);

Word40 L40_sub(Word40 acc, int32_t L_var1);

Word40 L40_mac(Word40 acc, int16_t var1, int16_t var2);

Word40 L40_msu(Word40 acc, int16_t var1, int16_t var2);

Word40 L40_shl(Word40 acc, int16_t var1);

Word40 L40_shr(Word40 acc, int16_t var1);

Word40 L40_negate(Word40 acc);

int16_t norm32(Word40 acc);

int32_t L_sat32(Word40 acc);



#endif

