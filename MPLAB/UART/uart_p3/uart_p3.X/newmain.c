/*
 * File:   newmain.c
 * Author: tramt
 *
 * Created on Ngày 05 tháng 4 n?m 2022, 23:39
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

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "lcd.h"
#include <stdio.h>
#define _XTAL_FREQ 8000000
#define Baud_rate 9600
void Initialize_UART(void)
{
    TRISC6 = 0;
    TRISC7 = 1;
    SPBRG = ((_XTAL_FREQ/16)/Baud_rate) - 1;
    BRGH  = 1;
    SYNC  = 0;
    SPEN  = 1;
    TXEN  = 1;
    CREN  = 1;
    TX9   = 0;
    RX9   = 0;
}
void UART_send_char(char bt)
{
    while(!TXIF);
    TXREG = bt;
}
char UART_get_char()
{
    if(OERR)
    {
        CREN = 0;
        CREN = 1;
    }
    while(!RCIF);
    return RCREG;
}
void UART_send_string(char* st_pt)
{
    while(*st_pt)
        UART_send_char(*st_pt++);
}
void putch(char x)  //Ham cho printf
{
    while(!TXIF);
    UART_send_char(x);
}
void ADCInit()
{
    ANSELbits.ANS0 = 1; //Set A0 as analog
    /*ADCON0bits.ADCS = 0x00; ////Fosc/2 ADC
    ADCON1bits.ADFM = 1; //Right justified
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;*/
    ADCON0 = 0x00;   // FOSC/2, AN0, GO_nDONE off, ADON off
    ADCON1 = 0x80;  // Right justified, Vss, Vdd
    ADRESL = 0;
    ADRESH = 0;
}
unsigned int get_val()
{
    ADCON0bits.ADON = 1; //ADC on (B?t ADC lên)
    __delay_ms(10);
    ADCON0bits.GO_nDONE = 1; //GO_nDONE on. Start to read ADC (B?t ch? ?? ??c ADC lên. ADC b?t ??u ??c)
    __delay_ms(10);
    while(ADCON0bits.GO_nDONE); //When ADC read completed(finish), GO_nDONE become '0' level and then get out of loop(while)
    //(Ch? cho ??n khi ADC ??c hoàn t?t. S? ??a GO_nDONE = 0 và thoát kh?i vòng l?p)
    return ((ADRESH<<8)+ADRESL); 
    //??c hàm get_val ? d??i cùng ?? hi?u rõ
}   
float temp;
unsigned char buffer[20];
void main(void) {
    LCD_Initialize();
    Initialize_UART();
    ADCInit();
    TRISD = 0;
    while(1)
    {
        temp = get_val() / 2.046;
        LCDGoto(0,1);
        sprintf(buffer, "Temperature:%.02f", temp);
        LCDPutStr(buffer);
        printf("T = %.02f ", temp);
    }        
    return;
}
