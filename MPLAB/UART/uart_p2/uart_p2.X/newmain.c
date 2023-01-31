/*
 * File:   newmain.c
 * Author: tramt
 *
 * Created on Ngày 05 tháng 4 n?m 2022, 15:36
 */
// CONFIG1
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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _XTAL_FREQ 8000000
#define Baud_rate 9600
char get_value;
char name[20];
char randomNum;
char GetRandom(char min,char max){
    return min + (char)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}
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
void putch(char data)  //Ham cho printf
{
    while(!TXIF);
    UART_send_char(data);
}
void main(void) {
    Initialize_UART();
    srand(time(NULL));
    //UART_send_string("Enter your name: ");
    randomNum = GetRandom(20, 60);
    while(1)
    {
        //get_value = UART_get_char();
        printf("%d ", randomNum);
    }
    return;
}
