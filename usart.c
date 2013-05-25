/*  USART Lib for Kaffi
 *
 *  ToDo:
 *       - Using interrupts!
 *
*/

#include "usart.h"

void usart_init(void) {
    // Set baud rate
    UBRR0H = (unsigned char)(UBRR >> 8);
    UBRR0L = (unsigned char)UBRR;

    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    
    // Set frame format: 8data and 2stop bit
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}


unsigned char usart_receive(void) {
// Wait for received data 
while ( !(UCSR0A & (1 << RXC0)) )
;

// Return the received data
return UDR0;
}


void usart_send(unsigned char data) {
    // Waiting for an empty transmit buffer
    while ( !( UCSR0A & (1 << UDRE0)) )
        ;

    // Sending data
    UDR0 = data;
}
