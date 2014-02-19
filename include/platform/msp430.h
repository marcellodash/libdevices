/*
*
* Copyright (c) 2013, Michal Potrzebicz <michal@elevendroids.com>
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following 
* conditions are met:
*
*    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*      disclaimer.
*    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*      disclaimer in the documentation and/or other materials provided with the distribution.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
#ifndef _MSP430_H
#define _MSP430_H

#include <msp430.h>
#include <stdint.h>

#ifndef F_CPU
#define F_CPU 1000000UL
#warning "F_CPU is not defined!"
#endif

#if F_CPU == 16000000UL
	#define MSP430_CYCLES_PER_US 16
	#define MSP430_CYCLES_PER_MS 16000
#elif F_CPU == 1200000UL
	#define MSP430_CYCLES_PER_US 12
	#define MSP430_CYCLES_PER_MS 12000
#elif F_CPU == 8000000UL
	#define MSP430_CYCLES_PER_US 8
	#define MSP430_CYCLES_PER_MS 8000
#elif F_CPU == 1000000UL
	#define MSP430_CYCLES_PER_US 1
	#define MSP430_CYCLES_PER_MS 1000
#else
	#error "Unsupported F_CPU frequency"
#endif

#define MSP430_HAS_PORT1

#ifdef __MSP430_HAS_PORT2_R__
	// MSP430G2230 has P2 defined int its header though it doesn't have in the hardware
	#ifndef __MSP430G2230__
		#define MSP430_HAS_PORT2
	#endif
#endif

#ifdef __MSP430_HAS_PORT3_R__
	#define MSP430_HAS_PORT3
#endif

#ifdef MSP430_HAS_PORT2
	#define MSP430_PORT_INT_COUNT	16
#else
	#define MSP430_PORT_INT_COUNT	8
#endif

/*
 * MCU pin definitions 
 *
 */
#ifdef __MSP430G2553__
	#define UCA0RXD		1
	#define UCA0TXD		2
	
	#define UCA0SOMI	1
	#define UCA0SIMO	2
	#define UCA0STE		5
	#define UCA0CLK		4

	#define UCB0SCL		6
	#define UCB0SDA		7

	#define UCB0SOMI	6
	#define UCB0SIMO	7
	#define UCB0STE		4
	#define UCB0CLK		5
#endif

/// Primary peripherial mode selection
#define MSP430_PORT_MODE_SEL		0x40
#define MSP430_PIN_MODE_SEL			0x40
/// Secondary peripherial mode selection
#define MSP430_PORT_MODE_SEL2		0x80
#define MSP430_PIN_MODE_SEL2		0x80


void Msp430_InitClock();

uint16_t Msp430_GetSupplyVoltage(void);

#endif /* _MSP430_H */

