#ifndef HD44780_H
#define HD44780_H

#include <stdint.h>

#define HD44780_CMD_CLEAR		0x01
#define HD44780_CMD_HOME		0x02
#define HD44780_CMD_ENTRY_MODE		0x04
#define	HD44780_CMD_DISPLAY_CTRL	0x08
#define HD44780_CMD_CURSOR_SHIFT	0x10
#define HD44780_CMD_FUNC_SET		0x20
#define HD44780_CMD_SET_CG_ADDRESS	0x40
#define HD44780_CMD_SET_ADDRESS		0x80

// Entry mode
#define HD44780_CURSOR_DEC		0x00
#define HD44780_CURSOR_INC		0x02
#define HD44780_CURSOR_SHIFT 		0x01

// Display control
#define HD44780_CURSOR_BLINK		0x01
#define HD44780_CURSOR_ON		0x02
#define HD44780_DISPLAY_ON		0x04

// Cursor/display shift
#define HD44780_CURSOR_MOVE		0x00
#define HD44780_DISPLAY_SHIFT		0x08
#define	HD44780_SHIFT_LEFT		0x00
#define HD44780_SHIFT_RIGHT		0x04

// Function set
#define HD44780_FONT_5x8		0x00
#define HD44780_FONT_5x10		0x04
#define HD44780_LINES_1			0x00
#define HD44780_LINES_2			0x08

// Data bus width
#define HD44780_DATA_MODE_4		0x00
#define HD44780_DATA_MODE_8		0x10

#define HD44780_FLAG_NONE		0x00
#define HD44780_FLAG_E			0x01
#define HD44780_FLAG_RS			0x02
#define HD44780_FLAG_WR			0x04

typedef void Hd44780WriteFunc(uint8_t data, uint8_t flags);

typedef struct {
	uint8_t lines;
	uint8_t columns;
	uint8_t data_mode;
	Hd44780WriteFunc *write_func;
} Hd44780Config;

typedef struct {
	const Hd44780Config *config;
	uint8_t display_control;
} Hd44780Device;

void Hd44780_Init(Hd44780Device *device);
void Hd44780_Clear(Hd44780Device *device);
void Hd44780_ClearLine(uint8_t line);
void Hd44780_SetCursorPos(Hd44780Device *device, const uint8_t line, const uint8_t column);
void Hd44780_PutChar(Hd44780Device *device, const char c);
void Hd44780_PutStringC(Hd44780Device *device, char *s, uint8_t count);
void Hd44780_PutString(Hd44780Device *device, char *s);

void Hd44780_DisplayOn(Hd44780Device *device);
void Hd44780_DisplayOff(Hd44780Device *device);

void Hd44780_CursorOn(Hd44780Device *device);
void Hd44780_CursorOff(Hd44780Device *device);

//void HD44780_set_font_char(char index, char *data);

#endif