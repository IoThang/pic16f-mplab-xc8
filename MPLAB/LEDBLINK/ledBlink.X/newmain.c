/*
 * File:   newmain.c
 * Author: tramt
 *
 * Created on Ngày 06 tháng 3 n?m 2022, 10:59
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
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
#define _XTAL_FREQ 4000000
void blink(unsigned char time)
{
    for(unsigned char i = 0; i < time; i++)
    {
        PORTB = 0;
        __delay_ms(100);
        PORTB = 0XFF;
        __delay_ms(100);
    }
}
void blink1(unsigned char time)
{
    for(unsigned char i = 0; i < time; i++)
    {
        unsigned char temp = 0;
        while(temp <= 255) //255 = 11111111
        {
            PORTB = temp;
            __delay_ms(100);
            if(temp == 255)
                break;
            temp = (temp << 1) + 0x01;
        }
    }
}
void blink2(unsigned char time)
{
    for(unsigned char i = 0; i < time; i++)
    {
        unsigned char temp = 0b00000001;
        while(temp <= 128)  //128 = 10000000
        {
            PORTB = temp;
            __delay_ms(100);
            if(temp == 128)
                break;
            temp = (temp << 1);
        }
        PORTB = 0;
        __delay_ms(100);
    }
}
void blink3(unsigned char time)
{
    for(unsigned char i = 0; i < time; i++)
    {
        unsigned char run, stop, y;
        stop = 0;
        for(unsigned char j = 0; j <= 7; j++)
        {
            run = 0b00000001;
            for(unsigned char k = 0; k <= 7 - j; k++)
            {
                y = run | stop;
                PORTB = y;
                __delay_ms(100);
                run = run << 1;
            }
            stop = y;
        }
        PORTB = 0;
    }
}
void main(void) {
    TRISB = 0;
    while(1)
    {
        blink(2);
        blink1(2);
        blink2(2);
        blink3(2);

    }
    return;
}
