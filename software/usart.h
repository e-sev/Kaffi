/* header- File for usart.c
*/

#include <avr/io.h>
#include "config.h"

// Calculate baudrate
#define UBRR CLOCK/16/BAUD-1


void usart_init(void);
unsigned char usart_receive(void);
void usart_send(unsigned char);
