/* Command Line interface

  Commands:
    t/T -> decrease/increase requested temperature
    p/P -> decrease/increase P- Value
    d/D -> decrease/increase D- Value
    w/W -> decrease/increase windup gard
    c   -> show current values
    m   -> print status in csv- format
    s   -> save data to EEPROM
    l   -> leave this menu
*/

#include <avr/io.h>
#include "config.h"
#include "usart.h"

void help(void){
// print help screen
}

void cmd_line(void) {
// Get data from usart
unsigned char usart_data = usart_receive();

// Checking which character was received
switch(usart_data) {
case 't':
 // Temp decrease function
 break;
case 'T':
 // Temp increase function
 break;

case 'p':
 // P decrease function
 break;
case 'P':
 // P increase function
 break;

case 'd':
 // D decrease function
 break;
case 'D':
 // D increase function
 break;

case 'w':
 // Windup guard decrease function
 break;
case 'W':
 // Windup guard increase function
 break;

case 'c': case 'C':
 // Show current values
 break;

case 'm': case 'M':
 // Toogle csv modus
 break;

case 's': case 'S':
 // Save values to eeprom
 break;

case 'l': case 'L':
 // Leave the menu
 break;

}
}
