#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTRC oscillator; port I/O function on both RA6/OSC2/CLKO pin and RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode disabled)
#include <xc.h>
#define _XTAL_FREQ 8000000
unsigned char maLed[]={0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
unsigned int potResistor;
float y, z; //Bien toan cuc
unsigned char *pt;
char laybit7(unsigned char x)
{
    if(x == 0)
        return 0;
    else
        return 1;
}
void xuat_1byte(unsigned char xuatbyte)
{
    unsigned char b = 0x80, xuat;
    for(unsigned char i = 0; i < 8; i++)
    {
        //PORTDbits.RD0 = byte_u.b7; sai cho nay
        xuat = laybit7(xuatbyte & b);
        PORTBbits.RB1 = xuat;        
        PORTBbits.RB0 = 0; PORTBbits.RB0 = 1;
        b >>= 1;
    }
}
void hienthi(unsigned char n, unsigned char m) //n: minute - m: second
{
    xuat_1byte(maLed[m % 10]);
    xuat_1byte(maLed[m % 100 / 10]);
    xuat_1byte(maLed[n % 10]);
    xuat_1byte(maLed[n % 100 / 10]);
    PORTBbits.RB2 = 0; PORTBbits.RB2 = 1;
    __delay_ms(10);
}

void ADCInit()
{
    ANSELbits.ANS0 = 1; //Set A0 as analog
    /*ADCON0bits.ADCS = 0x00; ////Fosc/2 ADC
    ADCON1bits.ADFM = 1; //Right justified
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;*/
    ADCON0 = 0x80;   // FOSC/64, AN0, GO_nDONE off, ADON off
    ADCON1 = 0xC0;  // Right justified, Vss, Vdd
    ADRESL = 0;
    ADRESH = 0;
}
unsigned int get_val()  //Ham tra ve so ADC (Ko phai so Voltage)
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
void Button_first(unsigned char x)
{
    if(PORTAbits.RA1 == 0)
    {
        __delay_ms(20);
        if(PORTAbits.RA1 == 0)
        {
            while(PORTAbits.RA1 == 0);
            while(1)
            {
                z = (get_val() * 5 * 1.0 / 1023) * 59  / 5;
                hienthi(z, x);
                if(PORTAbits.RA1 == 0)
                    break;
            }
        }
    }
}
void Button_second(unsigned char i)
{
    if(PORTAbits.RA1 == 0)
    {
        __delay_ms(20);
        if(PORTAbits.RA1 == 0)
        {
            while(PORTAbits.RA1 == 0);
            while(1)
            {
                y = (get_val() * 5 * 1.0 / 1023) * 59  / 5;
                hienthi(i, y);
                if(PORTAbits.RA1 == 0)
                    break;
            }
        }
    }
}

void Button_third(unsigned char m, unsigned char n)
{
    if(PORTAbits.RA1 == 0)
    {
        __delay_ms(20);
        if(PORTAbits.RA1 == 0)
        {
            while(PORTAbits.RA1 == 0);
            //for(unsigned i = m)
        }
    }
}

void main(void) {
    TRISB = 0;
    ANSEL = 0b00000001;
    ADCInit();
    while(1)
    {
//        x = (get_val() * 5 * 1.0 / 1023) * 59  / 5;
//        hienthi(x);
        for(unsigned char i = 0; i < 60; i++)
        {
            for(unsigned char j = 0; j < 60; j++)
            {
                hienthi(i, j);
                __delay_ms(10);
                Button_first(j);
                Button_second(z);
                //BUTTON 3 LA DONG DUOI
                if(PORTAbits.RA1 == 0)
                {
                    __delay_ms(20);
                    if(PORTAbits.RA1 == 0)
                    {
                        while(PORTAbits.RA1 == 0);
                        //for(unsigned i = m)
                        i = z; j = y;
                    }
                }
            }
        }
    }
    return;
}


//Note:
// Doc du lieu ve va chuyen sang Voltage
// 5 (V) --- 1023    (ADC)
// y (V) --- get_val (ADC)  
// Tu voltage chuyen sang so (0 -> 59)
// 5 (V) --- 59
// y (V) --- x
// => x = y * 59 / 5 = (get_val() * 5 * 1.0 / 1023) * 59 / 5        