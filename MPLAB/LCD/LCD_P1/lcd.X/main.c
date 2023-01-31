#include <xc.h>
#include <stdio.h>
#include "lcd_hd44780_pic16.h"
#define _XTAL_FREQ 4000000 
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
char p[20];
const char *chu[39] = {"                VI XU LY                "};
//                    0123456789012345678901234567890123456789012345
void leftToRight(void)  // Ko chay dc
{
    char i,j;
    for(i = 0; i <= 24; i++) 
      {
         for(j = 0; j < 16; j++) 
         {
            LCDGotoXY(j, 1);
//            LCDWriteString(cdt[45 - i - j]);  
            sprintf(p, "%c", chu[24 - i + j]);
            LCDWriteString(p);
        }
        __delay_ms(1000);
    }
}
void main (void)
{
//    LCDGotoXY(1,1);
//    sprintf(p, "%c", cdt[20]);
//    LCDWriteString(p);
  LCDInit(LS_NONE);
  while(1)
  {
    for(unsigned char i = 0; i < 10; i++)
    {
        LCDGotoXY(0,0);
        LCDWriteString("TRUONG DUC THANG");
        LCDGotoXY(i, 1);
        sprintf(p, "%u", i);
        LCDWriteString(p);
        __delay_ms(200);
        LCDClear();
    }
    //leftToRight();
  }

}
