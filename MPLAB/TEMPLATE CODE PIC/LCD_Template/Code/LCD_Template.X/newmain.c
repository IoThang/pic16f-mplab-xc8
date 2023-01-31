/*
 * File:   newmain.c
 * Author: tramt
 *
 * Created on Ngày 05 tháng 9 n?m 2022, 10:22
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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

#include <stdio.h>
#include <xc.h>
#include "lcd.h"

unsigned int cnt = 0, b2, b3;
unsigned char buffer[20];
void config(void)
{
    ANSEL = ANSELH = 0;
    TRISE = 0;
//    b2 = RB2; b3 = RB3;
//    GIE = 1;
//    RBIE = 1;
//    RBIF = 0;
//    IOCB2 = IOCB3 = 1;
//    TRISB = 0xFF;

    LCD_Initialize();
}

void main(void) {
    config();
    while(1)
    {
        LCDGoto(0,0);
//        sprintf(buffer,"COUNT: %02d", cnt);
        LCDPutStr("TRUONG DUC THANG");
    }
    return;
}
//void __interrupt() ISR(void)
//{
//    if(RBIF == 1)
//    {
//        if(b2 != RB2)
//            cnt++;
//        else if(b3 != RB3)
//            if(cnt != 0)
//                cnt--;
//    }
//    RBIF = 0;
//}