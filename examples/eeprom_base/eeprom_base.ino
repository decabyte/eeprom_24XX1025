/*
  eeprom_base.ino - Example Arduino 24XX1025 EEPROM Library.
  Created by Valerio De Carolis, January, 2013.
  Licensed under MIT license, see LICENSE.md
 */

#include <Wire.h>     
#include <EEPROM24.h>

// init eeprom with default address
EEPROM24 eeprom;

// example: bytes to be read with a single loop
#define READ_BYTES 32

// example: using one chip max address is 2^17 => 1024K
#define ADDR_BOUNDARY 131072

// variables
int i = 0;
unsigned int curr_addr = 0;

void setup() {
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
  
  // init TWI pins
  pinMode(SDA, INPUT);
  pinMode(SCL, INPUT);

  // enable pull-ups on SDA & SCL pins
  digitalWrite(SDA, HIGH);
  digitalWrite(SCL, HIGH);
  
  // display welcome
  Serial.println("Arduino Uno Board");
}

void loop() {
  Serial.print("eeprom[");
  Serial.print(curr_addr, HEX);
  Serial.println("]:");
  
  // eeprom read loop
  for(i = 0; i < READ_BYTES; i++) {
    byte re = (byte) eeprom.read(curr_addr);
    
    Serial.print(re, HEX);
    Serial.print(' ');
  
    curr_addr += 1;

    if(curr_addr > ADDR_BOUNDARY)
    	curr_addr = 0;
  }
  
  Serial.println(' ');

  // wait before the next loop
  delay(2000);
}
