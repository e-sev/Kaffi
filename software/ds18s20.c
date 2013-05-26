/*  DS18S20 lib
 *
 * Author: Severin Haas
 * Copyright: 2013
 * License: Coffee-Licence. Basically the same like Beerware licence ;-)
 *    As long as you retain this notice you can do whatever you want
 *    with this stuff. If we meet some day, and you think
 *    this stuff is worth it, you can buy me a coffee in return.
 *
 * Kaffi is icelandic and means coffee.
 */

#include "ds18s20.h"

// Timer function, to wait x microseconds
inline __attribute__((gnu_inline)) void delay(unsigned int time_to_wait) {
    while(time_to_wait--) {
        asm volatile("nop");
    }
}


unsigned char one_wire_reset() {

    unsigned char incoming_data;
    
    // Pull the one wire pin down for 480us
    OW_LOW_LEVEL();
    OW_OUTPUT();
    delay(us_wait(480));
    
    // Now we wait for a response
    OW_INPUT();
    delay(us_wait(60));
    
    // Read the incoming data
    incoming_data = (OW_PIN & (1 << OW_DATA));
    // Wait the rest of the remaing 480us
    delay(us_wait(420));
    
    // Return the data. ("1" means something wrong, a "0" everything is ok)
    return incoming_data;    
}


void one_wire_send_bit(unsigned char send_bit) {
    // Start sequence: Pull pin to low and wait 1us
    OW_LOW_LEVEL();
    OW_OUTPUT();
    delay(us_wait(1));
    
    // To write a "1" we switch to input mode
    if(send_bit == 1) {
        OW_INPUT();
    }
    
    // Wait 60us, then switch to input mode
    delay(us_wait(60));
    OW_INPUT();
}


void one_wire_send_byte(unsigned char send_byte) {
    
    unsigned char counter = 8;
    
    while (counter--) {
        // Write actual bit to the bus
        one_wire_send_bit(send_byte & 1);
        // Shift right to get the next bit
        send_byte >>= 1;
    }
}


unsigned char one_wire_read_bit() {

    unsigned char received_bit = 0;
    
    // Start sequence: Pull pin to low and wait 1us
    OW_LOW_LEVEL();
    OW_OUTPUT();
    delay(us_wait(1));
    
    // Switch to input and wait 14us
    OW_INPUT();
    delay(us_wait(14));
    
    // Read pin level
    if(OW_PIN &(1 << OW_DATA) == 1 ) {
        received_bit = 1;
    } else {
        received_bit = 0;
    }
    
    // Wait and return the received bit
    delay(us_wait(45));
    return received_bit;
}


unsigned char one_wire_read_byte() {
    
    unsigned char counter = 8, received_byte = 0;
    
    while (counter--) {
        received_byte >>= 1;
        received_byte |= (one_wire_read_bit() << 7);
    }
    
    return received_byte;
}



void ds18s20_read_temperature(char *buffer) {
    
    //
    unsigned int temperature[2];
    int digit;
    long int decimal;
    
    // Reset the system
    one_wire_reset();
    // We skip the ROM and start directly with temperature conversion
    one_wire_send_byte(DS18S20_CMD_SKIPROM);
    one_wire_send_byte(DS18S20_CMD_CONVERTTEMP);
    
    // Wait for a signal from the sensor that conversion is done
    while (!(one_wire_read_bit)) {
        ;
    }
    
    // Reset the system
    one_wire_reset();
    // We skip the ROM and start directly with reading the scratchpad
    one_wire_send_byte(DS18S20_CMD_SKIPROM);
    one_wire_send_byte(DS18S20_CMD_RSCP);
    
    // Read the first 2 scratchpad bytes
    temperature[0] = one_wire_read_byte();
    temperature[1] = one_wire_read_byte();
    // Reset, because only the first 2 bytes are interesiting
    one_wire_reset();
    
    // Convert the received values
    digit  = temperature[0] >> 4;
    digit |= (temperature[1] & 0x7) << 4;
    decimal = temperature[0] & 0xf;
    
    //sprintf(buffer, "%+d.%04u C", digit, decimal);
    
}













