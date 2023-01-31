///*
// * File:   newmain.c
// * Author: tramt
// *
// * Created on Ngày 18 tháng 5 n?m 2022, 11:41
// */
//// CONFIG
//#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
//#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
//#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
//#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
//#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
//#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
//#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
//#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
//
//// #pragma config statements should precede project file includes.
//// Use project enums instead of #define for ON and OFF.
//
//#include <xc.h>
//#define _XTAL_FREQ  4000000
//#define IN1         PORTCbits.RC3
//#define IN2         PORTCbits.RC4
//#define Sta_Sto     PORTBbits.RB0
//#define pwm_level   PORTBbits.RB1
//unsigned char maLed[]={0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10}; 
//uint16_t    dutyCycle;
//uint8_t     flag1 = 0;
//uint8_t     flag2 = 0;
//
//void PWM_Init(void)
//{
//    //--[ Configure The CCP Module For PWM Mode ]--
//      CCP1M3 = 1;
//      CCP1M2 = 1;
//      TRISC2 = 0; // The CCP1 Output Pin (PWM)
//      // Set The PWM Frequency
//      PR2 = 124;  // 500us
//      // Set The PS For Timer2 (1:4 Ratio)
//      T2CKPS0 = 1;
//      T2CKPS1 = 0;
//      // Start CCP1 PWM !
//      TMR2ON = 1;
//}
//void PWM_Set_Duty(uint16_t DC)
//{
//    // Check The DC Value To Make Sure it's Within 10-Bit Range
//    if(DC<1024)
//    {
//        CCP1Y = DC & 1;
//        CCP1X = DC & 2;
//        CCPR1L = DC >> 2;
//    }
//}
//void levelpwm(unsigned char flag2)
//{
//    if(flag2 == 1)
//    {
//        PWM_Set_Duty(100);
//        PORTD = maLed[1];
//    }
//    else if(flag2 == 2)
//    {
//        PWM_Set_Duty(200);
//        PORTD = maLed[2];
//    }
//    else if(flag2 == 3)
//    {
//        PWM_Set_Duty(300);
//        PORTD = maLed[3];
//    }
//    else if(flag2 == 4)
//    {
//        PWM_Set_Duty(400);
//        PORTD = maLed[4];
//    }
//        
//    else if(flag2 == 5)
//    {
//        PWM_Set_Duty(500);
//        PORTD = maLed[5];
//    }
//        
//}
//void main(void) {
//    TRISB = 1;
//    TRISC = 0;
//    TRISD = 0;
//    PWM_Init();
//    THANGDEPTRAI:
//    PWM_Set_Duty(0);
//    PORTD = maLed[0];
//    IN1 = 1; IN2 = 0;
//    while(1)
//    {
//        if(Sta_Sto == 1)
//        {
//            __delay_ms(20);
//            if(Sta_Sto == 1)
//            {
//                while(Sta_Sto == 1);
//                flag1++;
//                if(flag1 == 2)
//                {
//                    flag1 = 0; flag2 = 0;
//                    goto THANGDEPTRAI;
//                }
//            }
//        }
//        if((pwm_level == 1) && (flag1 == 1))
//        {
//            __delay_ms(20);
//            if(pwm_level == 1)
//            {
//                while(pwm_level == 1);
//                flag2++;
//                if(flag2 > 5)
//                {
//                    flag2 = 0;
//                    goto THANGDEPTRAI;
//                }
//            }
//        }
//        if((flag1 == 1) && (flag2 != 0))
//            levelpwm(flag2);
//    }
//    return;
//}
/*
 * File:   newmain.c
 * Author: tramt
 *
 * Created on Ngày 18 tháng 5 n?m 2022, 11:41
 */
// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
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
#define _XTAL_FREQ  4000000
#define IN1         PORTCbits.RC3
#define IN2         PORTCbits.RC4
#define Sta_Sto     PORTBbits.RB0
#define pwm_level   PORTBbits.RB1
unsigned char maLed[]={0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10}; 
uint16_t    dutyCycle;
uint8_t     flag1;
uint8_t     flag2;

void PWM_Init(void)
{
    //--[ Configure The CCP Module For PWM Mode ]--
      CCP1M3 = 1;
      CCP1M2 = 1;
      TRISC2 = 0; // The CCP1 Output Pin (PWM)
      // Set The PWM Frequency
      PR2 = 124;  // 500us
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
void levelpwm(unsigned char flag2)
{
    if(flag2 == 1)
    {
        PWM_Set_Duty(100);
        PORTD = maLed[1];
    }
    else if(flag2 == 2)
    {
        PWM_Set_Duty(200);
        PORTD = maLed[2];
    }
    else if(flag2 == 3)
    {
        PWM_Set_Duty(300);
        PORTD = maLed[3];
    }
    else if(flag2 == 4)
    {
        PWM_Set_Duty(400);
        PORTD = maLed[4];
    }    
    else if(flag2 == 5)
    {
        PWM_Set_Duty(499);
        PORTD = maLed[5];
    }   
}
void Start_Stop(unsigned char *flag1, unsigned char *flag2)
{
        if(Sta_Sto == 1)
        {
            __delay_ms(10);
            if(Sta_Sto == 1)
            {
                while(Sta_Sto == 1);
                *flag1 = *flag1 + 1;
            }
        }
}
void level_pwm(unsigned char *flag1, unsigned char *flag2)
{
        if((pwm_level == 1) && (*flag1 == 1))
        {
            __delay_ms(10);
            if(pwm_level == 1)
            {
                while(pwm_level == 1);
                *flag2 = *flag2 + 1;
                if(*flag2 == 6)
                    *flag2 = 1;
            }
        }
}
void main(void) {
    TRISB = 1;
    TRISC = 0;
    TRISD = 0;
    PWM_Init();
    THANGDEPTRAI:
    flag1 = 0; flag2 = 0;
    PWM_Set_Duty(0);
    PORTD = maLed[0];
    IN1 = 1; IN2 = 0;
    while(1)
    {
        Start_Stop(&flag1, &flag2);
        if(flag1 == 2)
            goto THANGDEPTRAI;
        level_pwm(&flag1, &flag2);
        if((flag1 == 1) && (flag2 > 0))
            levelpwm(flag2);
    }
    return;
}
