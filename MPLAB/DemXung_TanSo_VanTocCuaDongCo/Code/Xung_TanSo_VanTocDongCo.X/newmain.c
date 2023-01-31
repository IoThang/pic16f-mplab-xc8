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

#include <xc.h>
#include <stdio.h>
#include "lcd.h"
#define _XTAL_FREQ 20000000
unsigned char buffer[10];
//unsigned int cnt = 0, pulse = 0;
//void TIMER0_Init(void)
//{
//    PSA = 1;    //  Prescaler is assigned to the WDT module
//    PS2 = 0;
//    PS1 = 0;    //  PS[2:0] prescaler (1 -> 256) (2^n)
//    PS0 = 0;
//    T0CS = 1;   //  Counter on T0CKI pin  
//    T0SE = 1;   //  Increment on high-to-low transition on T0CKI pin (Counting the falling edge)
//    TMR0 = 0;
//}
//
//void config(void)
//{
//    ANSEL = ANSELH = 0;
//    TRISA4 = 1; //  T0CKI set as input
//    
//    LCD_Initialize();
//    TIMER0_Init();
//    
//    //  Interrupt 
//    T0IE = 1;
//    T0IF = 0;
//    PEIE = 1;
//    GIE = 1;
//}
//void main(void) {
//    config();
//    while(1)
//    {
//        __delay_ms(1000);
//        pulse = cnt * 256 + TMR0;
//        TMR0 = 0;
//        cnt = 0;
//        LCDGoto(0,0);
//        sprintf(buffer," %u  ", pulse);
//        LCDPutStr(buffer);
//    }
//    return;
//}
//void __interrupt() ISR(void)
//{
//    if(T0IE && T0IF)
//    {
//        cnt++;
//    }
//    T0IF = 0;
//}


float Velocity = 0;
unsigned int Pulse = 0, PrePulse = 0, DeltaPulse = 0;
void TIMER1_Init(void)
{
    T1CKPS1 = 1;
    T1CKPS0 = 1;    //  Prescaler (1 -> 8)
    TMR1CS = 0;     //  Dinh Thoi
    TMR1ON = 1;     //  TIMER1 on
    TMR1 = 3036;    //  Dinh thoi 100ms
}
void config(void)
{
    ANSEL = ANSELH = 0;
    TRISC = 0;
    
    TIMER1_Init();
    LCD_Initialize();
    
    //  Interrupt TMR1
    TMR1IE = 1;
    TMR1IF = 0;
    //  Interrupt INT
    INTE = 1;
    INTF = 0;
    INTEDG = 1;     //  Interrupt on rising edge of INT pin
    
    PEIE = 1;
    GIE = 1;    
}
float get_val()
{
    float rpm;
    DeltaPulse = Pulse - PrePulse;
    PrePulse = Pulse;
    rpm = 6.0*(float)DeltaPulse;
    return rpm;
}
void main(void)
{
    config();
    while(1)
    {
        LCDGoto(0,0);
        sprintf(buffer," %0.3f   %u ", Velocity, DeltaPulse);
        LCDPutStr(buffer);        
    }
    return;
}
void __interrupt() ISR(void)
{
    if(INTF && INTE)
    {
        Pulse++;
        INTF = 0;
    }
    if(TMR1IF && TMR1IE)
    {
        Velocity = get_val();
        TMR1 = 3036;
        TMR1IF = 0;
    }
}


//unsigned int dem;
//unsigned int xungt1,xungt2,xung;
//float v;
//void main()
//{
//LCD_Initialize();
//ANSEL=ANSELH=0;
//
//
//TRISA4 = 1; // input
//dem = 0;
//xung = 0;
//
//T0CS = 1;   // counter
//T0SE = 1;
//
//PSA = 1;
//
////PS2 = 0;
////PS1 = 0;
////PS0 = 1;
//
//T0IE = 1;
//T0IF = 0;
//GIE = 1;
//
//TMR0 =0;
//
//while(1)
//{ 
//   
//    __delay_ms(1000);
//    xung = dem*256 + TMR0;
//    TMR0 = 0;
//    dem = 0;
//    v =  (xung/360.0)*60.0;
// LCDGoto(0,0);
// sprintf(buffer,"xung: %04d %03.2f",xung, v);
// LCDPutStr(buffer);
//
//    
//}
//}
//
//void __interrupt() ISR(void)
//{
// if(T0IF && T0IE)
// {
//  dem++;
// }
// T0IF = 0;
//
//}
