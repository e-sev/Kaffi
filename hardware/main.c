/* Name: main.c
 * Author: Severin Haas
 * Copyright: 2013
 * License: Coffee-Licence. Basically the same like Beerware licence ;-)
 *
 * Kaffi is icelandic and means coffee. 
 *
 */

#include <avr/io.h>
#include "usart.h"
#include "config.h"
#include "cmd_line.h"

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
DDRD ^= ~( (1 << PORTD0) | (1 << ONEWIRE) );

    // USART initialisieren
     usart_init;
    
    usart_send(1);

    //cmd_line();
    
    for(int i = 0; i <= 100; i++){

    }

    
    return 0;
}
