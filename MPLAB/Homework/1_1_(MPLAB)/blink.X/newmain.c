/*
 * File:   newmain.c
 * Author: tramt
 *
 * Created on Ng?y 04 th?ng 3 n?m 2022, 08:09
 */


// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 1000000

void main(void) {
    TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;

    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;

    while (1) {
//        LATC0 = 1;
//        LATCbits.LATC1 = 0;
//        LATCbits.LATC2 = 0;
//        __delay_ms(100);
//        LATCbits.LATC0 = 0;
//        LATCbits.LATC1 = 1;
//        LATCbits.LATC2 = 0;
//        __delay_ms(100);
//        LATCbits.LATC0 = 0;
//        LATCbits.LATC1 = 0;
//        LATCbits.LATC2 = 1;
//        __delay_ms(100);
        
        PORTC = 0XFF;
        __delay_ms(100);
    }
    return;
}
