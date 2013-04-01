/*
  EEPROM_24X1025.cpp - Library for interfacing 24XX1025 EEPROM chips.
  Created by Valerio De Carolis, January, 2013.
  Licensed under MIT license, see LICENSE.md
 */

#include "Arduino.h"
#include "Wire.h"
#include "EEPROM_24X1025.h"

/**
 * 
 */
EEPROM_24X1025::EEPROM_24X1025() 
{
  EEPROM_24X1025::EEPROM_24X1025(EEPROM_24X1025_ADDR, EEPROM_24X1025_FAST);
}

/**
 * 
 */
EEPROM_24X1025::EEPROM_24X1025(byte address, bool fast)
{
  _address = address;

  // init Wire library
  Wire.begin();

  // change TWI base clock
  if(fast)
    TWBR = ((CPU_FREQ / TWI_FREQ_FAST) - 16) / 2;
}

/**
 * [EEPROM_24X1025::read description]
 * @param  eeprom_addr [description]
 * @return             [description]
 */
int EEPROM_24X1025::read(unsigned int eeprom_addr)
{
  byte i2c_status = 0;
  byte i2c_addr = _address;
  int ee_out = 0;
  
  // swap chip (for daisy-chained eeproms)
  if( eeprom_addr > 65535 )
    i2c_addr = i2c_addr | B00001000;    
 
  // seven-bit address
  i2c_addr = i2c_addr >> 1;
  
  // i2c commands
  Wire.beginTransmission(i2c_addr);
  Wire.write( (byte) eeprom_addr >> 8 );
  Wire.write( (byte) (eeprom_addr && 0x00FF) );
  
  // check status
  i2c_status = Wire.endTransmission();
  
  if( i2c_status == 0 ) {  
    Wire.requestFrom(i2c_addr, 1);

    while( Wire.available() )
      ee_out = Wire.read();    

    return ee_out;
  } else {  
    return -1;
  } 
}

/**
 * [EEPROM_24X1025::write description]
 * @param  eeprom_addr [description]
 * @param  data        [description]
 * @return             [description]
 */
int EEPROM_24X1025::write(unsigned int eeprom_addr, byte data)
{
  byte i2c_addr = ctrl_24fc1025;
  
  if( eeprom_addr > 65535 )
    i2c_addr = i2c_addr | B00001000;    
 
  // seven-bit address
  i2c_addr = i2c_addr >> 1;
  
  // i2c commands
  Wire.beginTransmission(i2c_addr);
  Wire.write( (byte) eeprom_addr >> 8 );
  Wire.write( (byte) (eeprom_addr && 0x00FF) );
  Wire.write( data );
  
  return Wire.endTransmission();  
}
