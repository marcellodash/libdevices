/*
*
* Copyright (c) 2014, Michal Potrzebicz <michal@elevendroids.com>
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

#include <stdarg.h>
#include "platform/msp430.h"
#include "board/mspnode.h"
#include "digital_io.h"

void Board_Init(void)
{
	// disable watchdog
	WDTCTL = WDTPW + WDTHOLD;
	Msp430_InitClock();
	// initialize LED outputs
	Pin_SetMode(LED_ERROR, PIN_MODE_OUTPUT);
	Pin_SetMode(LED_STATUS_1, PIN_MODE_OUTPUT);
	Pin_SetMode(LED_STATUS_2, PIN_MODE_OUTPUT);
}

/**
Board-specific control

*/
void Board_Control(int request, ...)
{
	va_list arguments;

	va_start(arguments, request);
	// TODO: Handle control requests
//	switch(request) {
//		case BOARD_POWERSAVE_ON		: P2OUT |= BIT7; break;
//		case BOARD_POWERSAVE_OFF	: P2OUT &= ~BIT7; break;
//	}

	va_end(arguments);
}

