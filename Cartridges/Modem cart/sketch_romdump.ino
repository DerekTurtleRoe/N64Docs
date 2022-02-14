/*
  For Teensy 3.
  
  ROM Pin Name    connect to      Teensy pin
  1       AD0     teensy           5
  2       AD1     teensy           6
  3       AD2     teensy           7
  4       AD3     teensy           8
  5       VCC             
  6       ALEL    teensy           1
  7       /READ   teensy           0
  8       GND             
  9       ALEH    teensy           2
  10      GND             
  11      AD4     teensy           9
  12      AD5     teensy          10
  13      AD6     teensy          11
  14      AD7     teensy          12
  15      AD8     teensy          14
  16      AD9     teensy          15
  17      AD10    teensy          16
  18      AD11    teensy          17
  19      VCC             
  20      /READ   tie to ROM7     (0)
  21              n/c    
  22      VCC             
  23      GND             
  24      GND             
  25      AD12    teensy          18
  26      AD13    teensy          19
  27      AD14    teensy          20
  28      AD15    teensy          21
*/

const int pinLed = 13;

const int pinREAD = 0;
const int pinALEL = 1;
const int pinALEH = 2;

const int pinAD0 = 5;
const int pinAD1 = 6;
const int pinAD2 = 7;
const int pinAD3 = 8;
const int pinAD4 = 9;
const int pinAD5 = 10;
const int pinAD6 = 11;
const int pinAD7 = 12;
const int pinAD8 = 14;
const int pinAD9 = 15;
const int pinAD10 = 16;
const int pinAD11 = 17;
const int pinAD12 = 18;
const int pinAD13 = 19;
const int pinAD14 = 20;
const int pinAD15 = 21;

const int pinsAD[] = {
  pinAD0,
  pinAD1,
  pinAD2,
  pinAD3,
  pinAD4,
  pinAD5,
  pinAD6,
  pinAD7,
  pinAD8,
  pinAD9,
  pinAD10,
  pinAD11,
  pinAD12,
  pinAD13,
  pinAD14,
  pinAD15,
};

const int startAddress = 0x18000000;
const int endAddress = 0x18800000;
void setup()
{
  pinMode( pinLed,  OUTPUT );
  pinMode( pinREAD, OUTPUT );
  pinMode( pinALEL, OUTPUT );
  pinMode( pinALEH, OUTPUT );
  
  int i;
  for( i=0; i<16; ++i )
  {
    pinMode( pinsAD[i], INPUT );
  }
  
  Serial.begin( 115200 );
  delay( 2000 );
  Serial.println( "Hello, cruel world!\n" );
  
  // delay until an 'X' byte is received
  int goAhead = 0;
  while(goAhead == 0)
  {
    if( Serial.available() > 0 )
    {
      int incomingByte = Serial.read();
      if( incomingByte == 'X' )
        goAhead = 1;
    }
  }
  
  // scan the address space
//   unsigned int address;
//   for( address=0x1234; address<0xff000000; address+=0x00100000 )
//   {
//     unsigned int lowbits, highbits;
//     latchAddress( address );
//     digitalWriteFast( pinREAD, 0 );
//     delayMicroseconds( 1 );
//     highbits = readAD();       // high 16 bits
//     digitalWriteFast( pinREAD, 1 );
//     delayMicroseconds( 1 );
//     digitalWriteFast( pinREAD, 0 );
//     delayMicroseconds( 1 );
//     lowbits = readAD();       // low 16 bits
//     digitalWriteFast( pinREAD, 1 );
//     delayMicroseconds( 10 );
//     
//     Serial.print( "0x" );
//     Serial.print( address, HEX );
//     Serial.println( (highbits==0x1234 && lowbits==0x1234)?" no":" yes" );
//   }
  
  // dump the rom
  unsigned int address = startAddress;
  while( address < endAddress )
  {
    unsigned int temp;
    latchAddress( address );
    digitalWriteFast( pinREAD, 0 );
    delayMicroseconds( 1 );
    print16BitsAsHex( readAD() );
    digitalWriteFast( pinREAD, 1 );
    delayMicroseconds( 1 );
    digitalWriteFast( pinREAD, 0 );
    delayMicroseconds( 1 );
    print16BitsAsHex( readAD() );
    digitalWriteFast( pinREAD, 1 );
    delayMicroseconds( 10 );
    address += 4;
//     Serial.println();
  }
  digitalWriteFast( pinLed, 1 );
}

void loop()
{
}

unsigned int readAD()
{
  unsigned int varFromAD = 0;
  int i;
  for( i=0; i<16; ++i )
  {
    pinMode( pinsAD[i], INPUT );
  }
  for( i=0; i<16; ++i )
  {
    varFromAD |= digitalRead(pinsAD[i])?(1<<i):0;
  }
  return varFromAD;
}

void writeAD( unsigned int valToWrite )
{
  int i;
  for( i=0; i<16; ++i )
  {
    pinMode( pinsAD[i], OUTPUT );
  }
  for( i=0; i<16; ++i )
  {
    if( valToWrite & (1<<i) )
      digitalWrite( pinsAD[i], 1 );
    else
      digitalWrite( pinsAD[i], 0 );
  }
}

void latchAddress( unsigned int addressToLatch )
{
  digitalWrite( pinREAD, 1 );
  digitalWrite( pinALEL, 1 );
  digitalWrite( pinALEH, 1 );
  
  unsigned int addressHigh = (addressToLatch & 0xFFFF0000) >> 16;
//   Serial.print( addressHigh, HEX );
  unsigned int addressLow  =  addressToLatch & 0x0000FFFF;
//   Serial.print( addressLow, HEX );
  
  writeAD( addressHigh );
  delayMicroseconds( 1 );
  digitalWrite( pinALEH, 0 );
  delayMicroseconds( 1 );
  writeAD( addressLow );
  delayMicroseconds( 1 );
  digitalWrite( pinALEL, 0 );
  delayMicroseconds( 1 );
}

inline void print16BitsAsHex( unsigned int valToPrint )
{
  // ugh
  Serial.print( (valToPrint&0xF000)>>12, HEX );
  Serial.print( (valToPrint&0x0F00)>> 8, HEX );
  Serial.print( (valToPrint&0x00F0)>> 4, HEX );
  Serial.print( (valToPrint&0x000F)    , HEX );
}
