/* Name: main.c
 * Author: Severin Haas
 * Copyright: 2013
 * License: Coffee-Licence. Basically the same like Beerware licence ;-)
 *    As long as you retain this notice you can do whatever you want
 *    with this stuff. If we meet some day, and you think
 *    this stuff is worth it, you can buy me a coffee in return.
 *
 *
 * Kaffi is icelandic and means coffee. 
 *
 */

#include <avr/io.h>
#include "usart.h"
#include "config.h"
#include "cmd_line.h"

#include <util/delay.h>


int main(void) {

// Pin configuration:
// LED -> PORTD2
// 1wire -> PD7
// SolidState -> PB1
// RxD -> PD0
// TxD -> PD1

// Outputs
DDRD |= ( (1 << PORTD1) | (1 << LED) );
DDRB |= (1 << SOLIDSTATE);

// Inputs
DDRD ^= ~(1 << PORTD0) ;

    // USART initialisieren
     usart_init;
    

    //cmd_line();
    
    for( ; ; ){
        usart_send(1);
        _delay_ms(20);
    }

    
    return 0;
}
