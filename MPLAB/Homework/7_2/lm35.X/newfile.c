// CONFIG1
#pragma config FOSC = HS// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
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
#include <conio.h>
#include <stdio.h>
#include "lcd_hd44780_pic16.h"
char get_value;
char text[10];
#define _XTAL_FREQ 8000000
unsigned int x, result;
float temp;  // adc 10bits => x have 10bits

void ADCInit()
{
    ANSELbits.ANS2 = 1; //Set A0 as analog
    /*ADCON0bits.ADCS = 0x00; ////Fosc/2 ADC
    ADCON1bits.ADFM = 1; //Right justified
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;*/
    ADCON0 = 0b10001000;   // FOSC/64, AN0, GO_nDONE off, ADON off
    ADCON1 = 0xC0;  // Right justified, Vss, Vdd
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
void fun()
{
    temp = get_val() / 2.046;
    __delay_ms(10);
    LCDGotoXY(0,1);
    sprintf(text, "Temp=%.01f", temp);
    LCDWriteString(text);
}
void main ()
{
    TRISAbits.TRISA2 = 1; //Set A0 as input
    TRISD = 0;
    LCDInit(LS_NONE);
    LCDGotoXY(0,0);
    LCDWriteString("THANG 20145196");
    ADCInit();
    while(1)
    {
        fun();
    }
    
}    
//                                HÀM GET_VAL ? ?ÂY NÈ
//}unsigned int get_val()
//{
//    x = ADRESL; // add 8 bits of x to ADRESL register => 2 bíts left
//    x = x << 8; //shift left 8bits
//    x += ADRESH; //add 2 bits left to ADRESH register => 10bits enough
//    //GO_nDONE = 1;                        //bat dau thuc hien doc ADC
//    //while(GO_nDONE);
//    return x;
////    GO_nDONE = 1;                        //bat dau thuc hien doc ADC
////   while(GO_nDONE);                     //Cho ADC thuc hien chuyen doi xong
////   return ((ADRESH<<8)| ADRESL);
//}

