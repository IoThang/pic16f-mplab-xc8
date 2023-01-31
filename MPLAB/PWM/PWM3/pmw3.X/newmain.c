/*
 * File:   newmain.c
 * Author: tramt
 *
 * Created on Ngày 20 tháng 5 n?m 2022, 12:56
 */
// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include "lcd.h"
#define _XTAL_FREQ  4000000
#define IN1         PORTCbits.RC3
#define IN2         PORTCbits.RC4
#define Sta_Sto     PORTBbits.RB0
#define CW_CCW_BT   PORTBbits.RB1
unsigned int temp;
unsigned int dutyCycle;
unsigned char flag1;
unsigned char flag2;
unsigned char buffer[20];
unsigned char buffer1[20];
void ADC_Init(void)
{
    ADCON0 = 0x80;   // FOSC/64, AN0, GO_nDONE off, ADON off
    ADCON1 = 0xC0;  // Right justified, Vss, Vdd
    ADRESL = 0;
    ADRESH = 0;
}
unsigned int get_val()
{
    ADCON0bits.ADON = 1;
//    __delay_ms(10);
    ADCON0bits.GO_nDONE = 1;
//    __delay_ms(10);
    while(ADCON0bits.GO_nDONE);
    return ((ADRESH<<8)+ADRESL); 
}
void PWM_Init(void)
{
      CCP1M3 = 1;
      CCP1M2 = 1;
      TRISC2 = 0;
      PR2 = 124;  // 500us
      T2CKPS0 = 1;
      T2CKPS1 = 0;
      TMR2ON = 1;
}
void PWM_Set_Duty(uint16_t DC)
{
    if(DC<1024)
    {
        CCP1Y = DC & 1;
        CCP1X = DC & 2;
        CCPR1L = DC >> 2;
    }
}
void Config(unsigned char *flag1)
{
    LCD_Initialize();
    PWM_Init();
    ADC_Init();
    TRISB = 0b00000011;
    TRISC = 0;
    TRISAbits.TRISA1 = 1;
    IN1 = 1; IN2 = 0;
    flag1 = 0;
}
void CW_CCW(unsigned char *flag1)
{
    unsigned char flag = 0;
    if(CW_CCW_BT == 1)
    {
        __delay_ms(20);
        if(CW_CCW_BT == 1)
        {
            while(CW_CCW_BT == 1);
            flag = 1;
        }
    }
    if(flag == 1)
    {
        if(*flag1 == 1)
        {
            IN1 = 1; IN2 = 0;
            *flag1 = 0;
        }
        else if(*flag1 == 0)
        {
            IN1 = 0; IN2 = 1;
            *flag1 = 1;
        }
    }
    flag = 0;
}
void Start_Stop(unsigned char *flag2)
{
    if(Sta_Sto == 1)
    {
        __delay_ms(10);
        if(Sta_Sto == 1)
        {
            while(Sta_Sto == 1);
            *flag2 = *flag2 + 1;
        }
    }

}
void main(void) {
    Config(&flag1);
    THANGDEPTRAI:
    LCDGoto(0,0);
    LCDPutStr("MOTOR: OFF");
    LCDGoto(0,1);
    LCDPutStr("              ");
    PWM_Set_Duty(0);
    while(1)
    {
        Start_Stop(&flag2);
        if(flag2 == 2)
        {
            flag2 = 0;
            goto THANGDEPTRAI;
        }
        if(flag2 == 1)
        {
            CW_CCW(&flag1);
            temp = ((((get_val() * 1.0 * 5) / 1023) * 80) / 5) + 20;
            dutyCycle = 500 * (temp * 1.0 / 100);
            //dutyCycle(max) = 500(us) / ( (1 / 4(Mhz)) * 4) = 500
            LCDGoto(0,0);
            sprintf(buffer1,"DC:%u/500", dutyCycle);
            LCDPutStr(buffer1);
            PWM_Set_Duty(dutyCycle);
            LCDGoto(0,1);
            sprintf(buffer, "SPEED= %u%%", temp);
            LCDPutStr(buffer);
        }
    }
    return;
}
