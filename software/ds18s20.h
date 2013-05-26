/* Header File for ds18s20.c
 */

#include "config.h"
#include <avr/io.h>

// Constants for the timer
#define LOOP_CYCLES             8 // The loop takes 8 cycles
#define us_wait(loopNumber)     (loopNumber/(LOOP_CYCLES*(1/(CLOCK/1000000.0))))


// Some deffinitions to make our lifes easier
#define OW_PORT                 PORTD
#define OW_PIN                  PIND
#define OW_DDR                  DDRD
#define OW_DATA                 PD7


// Some macros to switch between input and output mode
#define OW_INPUT()              OW_DDR&=~(1<<OW_DATA)
#define OW_OUTPUT()             OW_DDR|=(1<<OW_DATA)
#define OW_LOW_LEVEL()          OW_PORT&=~(1<<OW_DATA)
#define OW_HIGH_LEVEL()         OW_PORT|=(1<<OW_DATA)


// ROM commands
#define DS18S20_CMD_SROM        0xF0
#define DS18S20_CMD_RROM        0x33
#define DS18S20_CMD_MROM        0x55
#define DS18S20_CMD_SKIPROM     0xCC
#define DS18S20_CMD_ALARM       0xEC

// DS18S20 commands
#define DS18S20_CMD_CONVERTTEMP 0x44
#define DS18S20_CMD_WSCP        0x4E
#define DS18S20_CMD_RSCP        0xBE
#define DS18S20_CMD_CSCP        0x48
#define DS18S20_CMD_RECEEPROM   0xB8
#define DS18S20_CMD_POWER       0xB4


// Functions
inline __attribute__((gnu_inline)) void delay(unsigned int);
unsigned char one_wire_reset(void);
void one_wire_send_bit(unsigned char);
void one_wire_send_byte(unsigned char);
unsigned char one_wire_read_bit(void);
unsigned char one_wire_read_byte(void);
