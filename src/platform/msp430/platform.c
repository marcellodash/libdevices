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

#include <msp430.h>
#include <stdint.h>
#include "delay.h"
#include "timer.h"
#include "platform/msp430.h"

uint8_t	Msp430_currentClock = 0;

void Msp430_SetClock(int clock)
{
	uint8_t bcs1, dco;

	__disable_interrupt();
	switch (clock) {
		#ifdef CALDCO_8MHZ
		case MSP430_CLOCK_8MHZ	:
			bcs1 = CALBC1_8MHZ;
			dco = CALDCO_8MHZ;
			break;
		#endif
		#ifdef CALDCO_12MHZ
		case MSP430_CLOCK_12MHZ	:
			bcs1 = CALBC1_12MHZ;
			dco = CALDCO_12MHZ;
			break;
		#endif
		#ifdef CALDCO_16MHZ
		case MSP430_CLOCK_16MHZ	: 
 			bcs1 = CALBC1_16MHZ;
			dco = CALDCO_16MHZ;
			break;
		#endif
		default:
			bcs1 = CALBC1_1MHZ;
			dco = CALDCO_1MHZ;
			break;
	}
	Msp430_currentClock = clock;

	// configure base clock, divide ACLK by 8
	BCSCTL1 = bcs1 | DIVA_3;
	// configure DCO
	DCOCTL = dco;
	Delay_Init();
	__enable_interrupt();
}

uint16_t Msp430_GetSupplyVoltage(void)
{
	uint16_t raw_value;
	// first attempt - measure Vcc/2 with 1.5V reference (Vcc < 3V )
	ADC10CTL0 = SREF_1 | REFON | ADC10SHT_2 | ADC10SR | ADC10ON;
	ADC10CTL1 = INCH_11 | SHS_0 | ADC10DIV_0 | ADC10SSEL_0;
	// start conversion and wait for it
	ADC10CTL0 |= ENC | ADC10SC;
	while (ADC10CTL1 & ADC10BUSY) ;
	// stop conversion and turn off ADC
	ADC10CTL0 &= ~ENC;
	ADC10CTL0 &= ~(ADC10IFG | ADC10ON | REFON);
	raw_value = ADC10MEM;
	// check for overflow
	if (raw_value == 0x3ff) {
		// switch range - use 2.5V reference (Vcc >= 3V)
		ADC10CTL0 = SREF_1 | REF2_5V | REFON | ADC10SHT_2 | ADC10SR | ADC10ON;
		// start conversion and wait for it
		ADC10CTL0 |= ENC | ADC10SC;
		while (ADC10CTL1 & ADC10BUSY) ;
		raw_value = ADC10MEM;
		// end conversion and turn off ADC
		ADC10CTL0 &= ~ENC;
		ADC10CTL0 &= ~(ADC10IFG | ADC10ON | REFON);
		// convert value to mV
		return ((uint32_t)raw_value * 5000) / 1024;
	} else
		return ((uint32_t)raw_value * 3000) / 1024;
}

