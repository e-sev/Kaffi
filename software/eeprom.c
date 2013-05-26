/*  EEPROM lib
 *
 *  This file based on the examble code in the ATmega328p datasheet
 *
 * Author: Severin Haas
 * Copyright: 2013
 * License: Coffee-Licence. Basically the same like Beerware licence ;-)
 *    As long as you retain this notice you can do whatever you want
 *    with this stuff. If we meet some day, and you think
 *    this stuff is worth it, you can buy me a coffee in return.
 *
 */


void EEPROM_write(unsigned int uiAddress, unsigned char ucData) {
    // Wait until we can write data
    while(EECR & (1 << EEPE)) {
        ;
    }

    // Set up address and data degisters
    EEAR = uiAddress;
    EEDR = ucData;

    // Write logical one to EEMPE
    EECR |= (1 << EEMPE);

    // Start eeprom write by setting EEPE
    EECR |= (1 << EEPE);
}


unsigned char EEPROM_read(unsigned int uiAddress) {
    // Wait until we can read data
    while(EECR & (1 << EEPE)) {
        ;
    }

    // Set up address register
    EEAR = uiAddress;

    // Start eeprom read by writing EERE
    EECR |= (1 << EERE);

    // Return data from adressed data register
    return EEDR;
}
