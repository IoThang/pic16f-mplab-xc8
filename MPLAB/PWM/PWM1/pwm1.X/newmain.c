/*
 * File:   newmain.c
 * Author: tramt
 *
 * Created on Ngày 08 tháng 5 n?m 2022, 16:55
 */


// CONFIG
#pragma config FOSC = EXTRC        // Oscillator Selection bits (HS oscillator)
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
#define _XTAL_FREQ 4000000 
uint16_t dutyCycle = 0;
void PWM_Init(void)
{
    //--[ Configure The CCP Module For PWM Mode ]--
      CCP1M3 = 1;
      CCP1M2 = 1;
      TRISC2 = 0; // The CCP1 Output Pin (PWM)
      // Set The PWM Frequency
      PR2 = 124;   // 500us
      // Set The PS For Timer2 (1:4 Ratio)
      T2CKPS0 = 1;
      T2CKPS1 = 0;
      // Start CCP1 PWM !
      TMR2ON = 1;
}
void PWM_Set_Duty(uint16_t DC)
{
    // Check The DC Value To Make Sure it's Within 10-Bit Range
    if(DC<1024)
    {
        CCP1Y = DC & 1;
        CCP1X = DC & 2;
        CCPR1L = DC >> 2;
    }
}
void main(void) {
    PWM_Init();
    while(1)
    {
        dutyCycle = 0; // Start With 0% DutyCycle

        // Gradually increase LED brightness
        while (dutyCycle<500)  // Use formula
        {
          PWM_Set_Duty(dutyCycle);
          dutyCycle++;
          __delay_ms(2);
        }
        __delay_ms(100);

        // Gradually decrease LED brightness
        while(dutyCycle>0)
        {
          PWM_Set_Duty(dutyCycle);
          dutyCycle--;
          __delay_ms(2);
        }

        __delay_ms(100);
    }
    return;
}
