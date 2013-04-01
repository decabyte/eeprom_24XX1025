/*
  EEPROM_24X1025.h - Library for interfacing 24XX1025 EEPROM chips.
  Created by Valerio De Carolis, January, 2013.
  Licensed under MIT license, see LICENSE.md
 */

#ifndef EEPROM_24X1025_h
#define EEPROM_24X1025_h

#include "Arduino.h"

class EEPROM_24X1025
{
  public:
    EEPROM_24X1025();
    void read();
    void write();
  private:
    int _address;
};

#endif
