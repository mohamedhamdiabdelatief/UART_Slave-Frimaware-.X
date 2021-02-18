/*
* File Name: UART Firmware For (Receiver / Slave)
* Author: Mohamed Hamdi
* please visit my youtube channel:https://www.youtube.com/channel/UCzt_0MFbJiT93KSR74pW6Jw
*
*/
#include <xc.h>
#include <stdint.h>
#include "config.h"
#define _XTAL_FREQ 4000000
#define Baud 9600
//--------------------------------
// Functions Declarations
void UART_RX_Init(void);
uint8_t UART_Read(void);
//--------------------------------
// Main Routine
void main(void)
{
  //--[ Peripherals & IO Configurations ]--
  UART_RX_Init(); // Initialize The UART in Master Mode @ 9600bps
  //---------------------------
  while(1)
  {
    // Do Whatever You Want !
    // ... 
  }
  return;
}
//--------------------------------
// Functions Definitions
void UART_RX_Init()
{
  uint16_t x;
  x = (_XTAL_FREQ - Baud*64)/(Baud*64); // Low Baud Rate
  if(x>255) 
  {
    x = (_XTAL_FREQ - Baud*16)/(Baud*16); // High Baud Rate
    BRGH = 1;
  }
  if (x<=255) 
  {
    SPBRG = x; //Writing SPBRG Register
  }
  // Enable The Ascynchronous Serial Port
  SYNC = 0;
  SPEN = 1;
  // Set The RX-TX Pins to be in UART mode (not io)
  TRISC6 = 1; // As stated in the datasheet
  TRISC7 = 1; // As stated in the datasheet
  //--[ Enable UART Receiving Interrupts ]--
  RCIE = 1; // UART Receving Interrupt Enable Bit
  PEIE = 1; // Peripherals Interrupt Enable Bit
  GIE = 1; // Global Interrupt Enable Bit
  //------------------
  CREN = 1; // Enable Data Continous Reception
}
uint8_t UART_Read()
{
  while(!RCIF); // Wait Untill a Data Frame is Received
  return RCREG;
}
// You Can Also Use The ISR If You Want To !
void __interrupt() ISR (void)
{
  if (RCIF == 1) 
  {
    // Read The RCREG Buffer Register...
    RCIF = 0; // Clear The Flag
  }
}