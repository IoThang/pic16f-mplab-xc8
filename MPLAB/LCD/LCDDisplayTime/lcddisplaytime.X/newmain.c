/*
 * File:   newmain.c
 * Author: tramt
 *
 * Created on Ngày 30 tháng 3 n?m 2022, 16:28
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include "lcd.h"
unsigned char buffer[20];
void main(void) {
    TRISC = 1;
    TRISD = 0;
    ANSEL = 0;
    PORTC = 0;
    LCD_Initialize();
    LCDGoto(0,0);
    LCDPutStr("TRUONG DUC THANG");
    while(1)
    {
        for(unsigned char i = 0; i < 24; i++)
        {
            for(unsigned char j = 0; j < 60; j++)
            {
                for(unsigned char k = 0; k < 60; k++)
                {
                    sprintf(buffer, "%02u:%02u:%02u", i, j, k);
                    LCDGoto(3, 1);
                    LCDPutStr(buffer);
                    __delay_ms(50);
                }
            }
        }
    }
    return;
}
