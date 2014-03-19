#ifndef _GPIO_PIN_H
#define _GPIO_PIN_H

typedef enum {
	P1_0 = 0x0001,
	P1_1 = 0x0002,
	P1_2 = 0x0004,
	P1_3 = 0x0008,
	P1_4 = 0x0010,
	P1_5 = 0x0020,
	P1_6 = 0x0040,
	P1_7 = 0x0080,

	P2_0 = 0x0101,
	P2_1 = 0x0102,
	P2_2 = 0x0104,
	P2_3 = 0x0108,
	P2_4 = 0x0110,
	P2_5 = 0x0120,
	P2_6 = 0x0140,
	P2_7 = 0x0180,

	P3_0 = 0x0201,
	P3_1 = 0x0202,
	P3_2 = 0x0204,
	P3_3 = 0x0208,
	P3_4 = 0x0210,
	P3_5 = 0x0220,
	P3_6 = 0x0240,
	P3_7 = 0x0280
} GpioPin;

#endif
