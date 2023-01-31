/*
 * File:   newmain.c
 * Author: tramt
 *
 * Created on Ngày 27 tháng 3 n?m 2022, 09:14
 */
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable bit (Vcap functionality is disabled on RA6.)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = HI        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), high trip point selected.)
#pragma config LPBOR = OFF      // Low Power Brown-Out Reset Enable Bit (Low power brown-out is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
//      DE BAI: https://youtu.be/zHBJppgVY3I
#include <xc.h>
#define _XTAL_FREQ 1000000
unsigned char b = 0x00;
void INTInit()
{
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.TMR1IE = 1;
    PIR1bits.TMR1IF = 0;
}
void TIMER1Init()
{
    T1CONbits.TMR1CS = 0;
    T1CONbits.T1CKPS = 3; //00000011
    T1CONbits.TMR1ON = 1;
    TMR1 = 62255;
}
void __interrupt() ISP()
{
    if(PIR1bits.TMR1IF == 1)
    {
        LATD =~ LATD;
        PIR1bits.TMR1IF = 0;
        TMR1 = 62255;
    }
}
void main(void) {
    TIMER1Init();
    INTInit();
    TRISC = 0; TRISD = 0;
    ANSELD = 0;
    LATC = 0;  LATD = 0;
    while(1)
    {
        for(unsigned char i = 0; i <= 8; i++)
        {
            LATC = b;
            b = (b << 1) + 1;
            __delay_ms(50);
        }
        for(unsigned char i = 0; i < 8; i++)
        {
            b = b >> 1;
            LATC = b;
            __delay_ms(50);
        }
    }
    return;
}