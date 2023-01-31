/*
 * File:   main.c
 * Author: tramt
 *
 * Created on Ngày 01 tháng 4 n?m 2022, 19:13
 */

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
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
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 8000000
unsigned char maLed[]={0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};  
// Khai bao 1 mang chua cac so tu 0 -> 9 bang demical
unsigned char i = 0;
char laybit7(unsigned char x)  // Ham (tra ve) kiem tra bien x la so khac 0 hay khong?. Neu dung se tra ve 0 va sai se tra ve 1
{
    if(x == 0)
        return 0;
    else
        return 1;
}
void xuat_1byte(unsigned char xuatbyte) //Ham dua cac bit trong maLed vao IC74595
{
    unsigned char b = 0x80, xuat; //Khai bao bien b = 0x10000000
    for(unsigned char i = 0; i < 8; i++)
    {
        if(PORTCbits.RC6 == 0)
            return;
        if(PORTCbits.RC4 == 0)
            return;
        xuat = laybit7(xuatbyte & b); //Cho bien xuatbyte and voi b. Dua bieu thuc and vao ham laybit7 de lay lan luot cac bit trong 1byte
        LATCbits.LATC1 = xuat;  //Sau do dua bien xuat vao chan DATA (0 hoac 1)      
        LATCbits.LATC0 = 0; LATCbits.LATC0 = 1; //Kich 1 xung (rising edge) vao SH_CP de dua bit do vao IC74595
        b >>= 1; //Dich bien b sàn trai 1 lan. De lay bit thu 6 o lan lap tiep theo
    }
}
void hienthi(unsigned int n) //ham (dua vao bien n) co tac dung dua cac bit ra khoi IC 
{
    xuat_1byte(maLed[n % 10]); //Goi ham xuat_1byte de dua 1byte vao IC hien thi o hang don vi
    xuat_1byte(maLed[(n / 10) % 10]); //Goi ham xuat_1byte de dua 1byte vao IC hien thi o hang chuc
    xuat_1byte(maLed[n / 100]); //Goi ham xuat_1byte de dua 1byte vao IC hien thi o hang tram
    LATCbits.LATC2 = 0; LATCbits.LATC2 = 1; //Kich 1 xung (rising edge) vao ST_CP de dua bit do ra khoi IC74595
}

void main(void) {
    TRISC = 0b01110000;  // Cai dat chan C0,C1,C2,C3 la output; C4,C5,C6 la input
    LATCbits.LATC3 = 0; //Ban dau cho led tat
    hienthi(0);
    while(1) //Sap het gio roi thay nen em comment ko dc :((
    {
//        if(PORTCbits.RC5 == 0)
        if(PORTCbits.RC5 == 1)
        {
            LATCbits.LATC3 = 0;
            THANGDEPTRAI:
            hienthi(i);
            if(PORTCbits.RC4 == 0 && PORTCbits.RC6 == 0 )
            goto THANGDEPTRAI;
        }
        else if(PORTCbits.RC5 == 0) //Khi RC5 = 0 thi bat che do START
        {
            LATCbits.LATC3 = 1; //Hien thi led()
            if(PORTCbits.RC6 == 0)
            {
                __delay_ms(5);
                if(PORTCbits.RC6 == 0)
                {
                    while(PORTCbits.RC6 == 0);
                    i += 1;
                    hienthi(i);
                }
            }
            if(PORTCbits.RC4 == 0)
            {
                i = 0;
                hienthi(i);
            }
        }
        
    }
    return;
}
