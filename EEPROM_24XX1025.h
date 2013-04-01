/*
  EEPROM_24X1025.h - Library for interfacing 24XX1025 EEPROM chips.
  Created by Valerio De Carolis, January, 2013.
  Licensed under MIT license, see LICENSE.md
 */

#ifndef EEPROM_24X1025_h
#define EEPROM_24X1025_h
#include "Arduino.h"

// TWI clock frequency (400 kHz)
#define TWI_FREQ_FAST 400000L

// default config (address & speed)
#define EEPROM_24X1025_ADDR B10100000
#define EEPROM_24X1025_FAST FALSE

class EEPROM_24X1025
{
  public:
    EEPROM_24X1025();
    EEPROM_24X1025(byte address, bool fast);
    int read(unsigned int eeprom_addr);
    int write(unsigned int eeprom_addr, byte data);
    int read_page();
    int write_page(); 
  private:
    byte _address;
};

#endif
