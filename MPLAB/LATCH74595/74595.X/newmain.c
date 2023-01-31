/*
 * File:   newmain.c
 * Author: tramt
 *
 * Created on Ngày 18 tháng 3 n?m 2022, 19:48
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
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#define _XTAL_FREQ 8000000
unsigned char maLed[]={0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
//        Y tuong:  https://youtu.be/9-i-16EGIsQ
char laybit7(unsigned char x)
{
    if(x == 0)
        return 0;
    else
        return 1;
}
void xuat_1byte(unsigned char xuatbyte)
{
    unsigned char b = 0x80 , xuat; //0x80 = 10000000
    for(unsigned char i = 0; i < 8; i++)
    {
        //PORTDbits.RD0 = byte_u.b7; sai cho nay
        xuat = laybit7(xuatbyte & b);
        PORTDbits.RD0 = xuat;        
        PORTDbits.RD1 = 0; PORTDbits.RD1 = 1;
        b >>= 1;
    }
}
void hienthi(unsigned char n)
{
    xuat_1byte(maLed[n % 10]);
    xuat_1byte(maLed[n / 10]);
    PORTDbits.RD2 = 0; PORTDbits.RD2 = 1;
    __delay_ms(10);
}
void main(void) {
    TRISD = 0;
    while(1)
    {
        for(unsigned char i = 0; i <= 99; i++)
        {
            hienthi(i);
            __delay_ms(100);
        }
    }
    return;
}
