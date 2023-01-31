/*
 * File:   newmain.c
 * Author: tramt
 *
 * Created on Ng�y 20 th�ng 3 n?m 2022, 10:38
 */

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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
unsigned int cnt = 0;
void TIMER1Init() //200ms high, 200ms off
{
    T1CONbits.T1CKPS1 = 1;
    T1CONbits.T1CKPS0 = 1;
    T1CONbits.TMR1CS = 0;
    T1CONbits.TMR1ON = 1;
    TMR1 = 3036;
}
void main(void) {
    TRISDbits.TRISD0 = 0;
    PORTDbits.RD0 = 0;
    TIMER1Init();
    while(1)
    {
        if(PIR1bits.TMR1IF == 1)
        {
            PIR1bits.TMR1IF = 0;
            cnt++; TMR1 = 3036;
            if(cnt == 2)
            {
                PORTDbits.RD0 =~ PORTDbits.RD0;
                cnt = 0;
            }
        }
    }
    return;
}
