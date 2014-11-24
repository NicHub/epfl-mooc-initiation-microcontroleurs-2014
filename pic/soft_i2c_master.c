#include <stdio.h>
#include <stdlib.h>
#include <p24FV32KA301.h>

#define SCL     TRISBbits.TRISB7 // I2C bus
#define SDA     TRISBbits.TRISB9 //
#define SCL_IN  PORTBbits.RB7    //
#define SDA_IN  PORTBbits.RB9    //
#define T_HALF 100
#define T_FULL 2*T_HALF

void i2c_dly(int wait)
{
    TMR1 = 0;      // Reset timer
    while(TMR1 < wait) {;}
}

void i2c_start(void)
{
  SDA = 1;             // i2c start bit sequence
  SCL = 1;
  i2c_dly(T_FULL);
  SDA = 0;
  i2c_dly(T_FULL);
  SCL = 0;
  i2c_dly(T_HALF);
}

void i2c_stop(void)
{
  SDA = 0;             // i2c stop bit sequence
  i2c_dly(T_HALF);
  SCL = 1;
  i2c_dly(T_FULL);
  SDA = 1;
  i2c_dly(T_FULL);
}



short i2c_tx(unsigned char d)
{
char x;
static char b;
  for(x=0; x<8; x++) {
    if(d&0x80) SDA = 1; // Select 7th bit for the test
    else SDA = 0;
    i2c_dly(T_HALF);
    SCL = 1;
    d <<= 1;    // Shift for the next bit to send;
    i2c_dly(T_FULL);
    SCL = 0;
    i2c_dly(T_HALF);
  }         // End of bit transmission
  SDA = 1;
  SCL = 1;
  i2c_dly(T_FULL);
  b = SDA_IN;          // possible ACK bit
  SCL = 0;
  SDA = 0;
  return b;
}


int main(int argc, char** argv) {
RCONbits.SWDTEN = 0; // Desactivate watchdog
T1CON = 0x8000;   // Activate timer
SDA = SCL = 1;    // Prepare for start
SCL_IN = SDA_IN = 0;
LATB = 0x0000;    // Set output to LOW
int i;
while(1) {
for( i=0; i<10; i++) {
    TMR1 = 0;
    while(TMR1 < 1000) {;}
    i2c_start();              // send start sequence
    i2c_tx(0b00010010);             // 0x09 I2C address with R/W bit clear
    i2c_tx(i);                 // Transmit loop counter
    i2c_stop();               // send stop sequence
    }
}
    return (EXIT_SUCCESS);
}
