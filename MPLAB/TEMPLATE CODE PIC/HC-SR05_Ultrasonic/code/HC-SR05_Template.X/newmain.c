// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include "lcd.h"
#define _XTAL_FREQ  16000000
#define TRIGGER     PORTCbits.RC1
#define ECHO        PORTCbits.RC0
unsigned char buffer[20];
unsigned int temp1;
unsigned int temp;
unsigned int time;
unsigned int get_val()
{
    //Set timer1
    T1CONbits.T1CKPS1 = 0;
    T1CONbits.T1CKPS0 = 1;
    T1CONbits.TMR1CS = 0;
    
    //Kich 1 xung lon hon (>10ms) vao trigger
    TRIGGER = 1;
    __delay_ms(20);
    TRIGGER = 0; 
    
    //Lay thoi gian tu chan ECHO
    while(!ECHO);
    TMR1ON = 1;
    while(ECHO);
    TMR1ON = 0;
    
    time = TMR1H;
    time <<= 8;
    time += TMR1L;
    
    return time;
}
void config(void)
{
    TRISE = 0;
    TRISC0 = 1;
    TRISC1 = 0;
    LCD_Initialize();
}
void main(void) {
    config();
    while(1)
    {
        temp1 = get_val();
        temp = (get_val() * 1.0) / 232;      //4MHz _ chia cho 58 , 8MHz _ chia cho 116
        sprintf(buffer, "%u ",temp);
        LCDGoto(0,0);
        LCDPutStr(buffer);
        __delay_ms(500);
        TMR1L = 0;
        TMR1H = 0;
    }
    return;
}
