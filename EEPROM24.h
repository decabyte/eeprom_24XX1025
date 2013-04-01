/*
  EEPROM_24X1025.h - Library for interfacing 24XX1025 EEPROM chips.
  Created by Valerio De Carolis, January, 2013.
  Licensed under MIT license, see LICENSE.md
 */

#ifndef EEPROM24_h
#define EEPROM24_h
#include "Arduino.h"

class EEPROM24
{
  public:
    EEPROM24();
    EEPROM24(byte address, bool fast);
    int read(unsigned int eeprom_addr);
    int write(unsigned int eeprom_addr, byte data);
    int read_page();
    int write_page();
  private:
    byte _address;
    bool _fast;
};

#endif

// see: http://arduino.cc/forum/index.php/topic,54345.0.html
