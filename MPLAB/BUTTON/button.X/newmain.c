/*
 * File:   newmain.c
 * Author: tramt
 *
 * Created on Ngày 23 tháng 3 n?m 2022, 21:35
 */
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
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
#include <xc.h>
#define _XTAL_FREQ 8000000
void flashing(unsigned char );
unsigned char i = 0, k, j = 0, z, state2 = 0;
unsigned int cnt = 0, cnt1 = 0;
void main(void) {
    TRISD = 0;
    ANSEL = 0;
    TRISA = 7; // 0x07 00000111
    PORTD = 0;         
    while(1)
    {
        if(PORTAbits.RA0 == 1)  //Press BT1
        {
            while(PORTAbits.RA0 == 1);
            k = 0x01 << i++;
            PORTD = k;
            if(i == 4) i = 0;
        }
        
        if(PORTAbits.RA1 == 1)  //Press BT2
        {
            while(PORTAbits.RA1 == 1);
            flashing(z++); 
            if(z == 4) z = 0;
        }
        if(PORTAbits.RA2 == 1) //Press BT3
        {
            while((PORTAbits.RA2 == 1))
            {
                if(cnt1 == 3000)
                {
                    cnt1 = 0;
                    PORTD = 0;
                    i = z = 0; break;
                }
                __delay_ms(1);
                cnt1++;
            }
        }
    }
    return;
}
void flashing(unsigned char i)
{
    while(PORTAbits.RA1 == 0)
    {
        PORTD = 0x01 << i; 
        __delay_ms(1); cnt++;
        if(PORTAbits.RA2 == 1) break;
        if(cnt == 1000) //Turn off
        {
            cnt = 0;
            while(1)
            {
                PORTD = 0;
                __delay_ms(1); cnt++;
                if(PORTAbits.RA1 == 1 || PORTAbits.RA2 == 1) break;
                if(cnt == 1000)
                {
                    cnt = 0; break;
                }
            }
        }
    }
}