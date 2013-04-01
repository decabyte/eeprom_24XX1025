// Arduino - MCP9700A
#include <Wire.h>

#define DEBUG

// constants
const byte apin = A0;
const byte tc = 10;        // mV/°C
const int t0 = 500;       // mV
const float res = 4.9;    // mV (5 V / 1024 units =~ 4.9 mV)

const byte ctrl_24fc1025 = B10100000;

// variables
int val = 0;
int vout = 0;
int i = 0;
float temp = 0;

// eeprom
unsigned int curr_addr = 0x0000;
byte ee_out = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  
  // enable pull-ups on SDA & SCL pins
  pinMode(SDA, INPUT);
  pinMode(SCL, INPUT);
  digitalWrite(SDA, HIGH);
  digitalWrite(SCL, HIGH);
  
  // init I2C
  Wire.begin();
  
  // display welcome
  Serial.println("Arduino Uno Board");
}

int read_eeprom(unsigned int eeprom_addr) {
  
  int i2c_addr = ctrl_24fc1025;
  
  if( eeprom_addr > 65535 )
    i2c_addr = i2c_addr | B00001000;    
 
  // seven-bit address
  i2c_addr = i2c_addr >> 1;
  
  Wire.beginTransmission(i2c_addr);
  Wire.write( (byte) eeprom_addr >> 8 );
  Wire.write( (byte) (eeprom_addr && 0x00FF) );
  
  byte i2c_status = Wire.endTransmission();
  
  if( i2c_status == 0 ) {
    
    Wire.requestFrom(i2c_addr, 1);
    
    while( Wire.available() ) {
      ee_out = Wire.read();    
    }
    
    return ee_out;
    
  } else {
    
    #ifdef DEBUG
    Serial.print("read_eeprom error: ");
    Serial.print(i2c_addr, BIN);
    Serial.print(" (address) + ");
    Serial.print(i2c_status, DEC);
    Serial.println(" (status)");
    #endif
    
    return -1;
  } 
}

int write_eeprom(unsigned int eeprom_addr, byte data) {
  int i2c_addr = ctrl_24fc1025;
  
  if( eeprom_addr > 65535 )
    i2c_addr = i2c_addr | B00001000;    
 
  // seven-bit address
  i2c_addr = i2c_addr >> 1;
  
  Wire.beginTransmission(i2c_addr);
  Wire.write( (byte) eeprom_addr >> 8 );
  Wire.write( (byte) (eeprom_addr && 0x00FF) );
  Wire.write( data );
  
  return Wire.endTransmission();  
}

void loop() {
  // read the analog in value:
  val = analogRead(apin);
  vout = map(val, 0, 1023, 0, 5000);

  // voltage-temperature conversion
  temp = (float) (vout - t0) / tc;    

  // print the results to the serial monitor:
  Serial.print("sensor = ");                       
  Serial.println(vout, DEC);
  
  // print the temperature
  Serial.print("temp = ");
  Serial.println(temp);
  
  // clear
  Serial.println(' ');
  
  
  Serial.print("eeprom[");
  Serial.print(curr_addr, HEX);
  Serial.println("]:");
  
  // eeprom loop
  for(i = 0; i < 26; i++) {
    byte re = (byte) read_eeprom(curr_addr);
    
    Serial.print(re, HEX);
    Serial.print(' ');
  
    curr_addr = (curr_addr + 1);   
  }
  
  Serial.println(' ');

  // wait 2000 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  delay(2000);                     
}
