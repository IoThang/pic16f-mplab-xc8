/*
 * File:   newmain.c
 * Author: tramt
 *
 * Created on Ngày 20 tháng 3 n?m 2022, 08:14
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
unsigned char cnt = 0;
#include <xc.h>
//void TIMER0Init()  //High, low 13ms
//{
//    TMR0 = 4;//Clear the TMR0 register
//    OPTION_REGbits.PS2 = 1;
//    OPTION_REGbits.PS1 = 1;
//    OPTION_REGbits.PS0 = 1;
//    OPTION_REGbits.T0CS = 0;
//    OPTION_REGbits.PSA = 0;
//    // 20Mhz / 4 = 5Mhz, 5Mhz / 256 = 5/256 (Mhz) => T = 51.2 us
//    // TC : 1tick __ 51,2 us  
//    //      ??tick__ 0.5  s  => So tick = ....
//}
//void main(void) {
//    TRISDbits.TRISD0 = 0;
//    TRISDbits.TRISD1 = 0;
//    PORTDbits.RD0 = 0;  
//    TIMER0Init();
//    while(1)
//    {
//        if(INTCONbits.TMR0IF == 1)
//        {
//            INTCONbits.TMR0IF = 0;
//            cnt++; TMR0 = 4;
//            PORTDbits.RD0 =~ PORTDbits.RD0;
//        }
//    }
//    return;
//}

#include <xc.h>
void TIMER0Init()  //High, low 1s
{
    TMR0 = 12;//Clear the TMR0 register
    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1;
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    // 20Mhz / 4 = 5Mhz, 5Mhz / 256 = 5/256 (Mhz) => T = 51.2 us
    // TC : 1tick __ 51,2 us  
    //      ??tick__ 0.5  s  => So tick = ....
}
void main(void) {
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    PORTDbits.RD0 = 0;  
    TIMER0Init();
    while(1)
    {
        if(INTCONbits.TMR0IF == 1)
        {
            INTCONbits.TMR0IF = 0;
            cnt++; TMR0 = 12;
            if(cnt == 80)
            {
                PORTDbits.RD0 =~ PORTDbits.RD0;
                cnt = 0;
            }
        }
    }
    return;
}
