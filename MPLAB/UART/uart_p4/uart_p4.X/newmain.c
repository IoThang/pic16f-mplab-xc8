#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 8000000
unsigned char buffer[100];
unsigned char buffer1[1];
unsigned char buffer2[1];
unsigned char savee = 0;
unsigned char savee1; 
unsigned char savee2;
unsigned char val;
void OSCILLATOR_Initialize(void)
{
    // SCS FOSC; IRCF 8MHz_HF; 
    OSCCON = 0x70;
    // SBOREN disabled; BORFS disabled; 
    BORCON = 0x00;
}

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    TRISA = 0x3F;
    TRISB = 0x70;
    TRISC = 0x00;
    ANSELC = 0x00;
    ANSELB = 0x10;
    ANSELA = 0x17;
}
void EUSART_Initialize(void)
{
    BAUDCON = 0x08;
    RCSTA = 0x90;
    TXSTA = 0x24;
    SPBRGL = 0xCF;
    SPBRGH = 0x00;
}
uint8_t EUSART_Read(void)
{
    while(!PIR1bits.RCIF)
    {
    }
    if(1 == RCSTAbits.OERR)
    {
        RCSTAbits.CREN = 0; 
        RCSTAbits.CREN = 1; 
    }
    return RCREG;
}
void EUSART_Write(uint8_t txData)
{
    while(0 == PIR1bits.TXIF)
    {
    }

    TXREG = txData;
}
void putch(char x)
{
    while(!TXIF);
    EUSART_Write(x);
}
void EUSART_Write_String(char* st_pt)
{
    while(*st_pt)
        EUSART_Write(*st_pt++);
}
void ON_OFF_BLINK(char* buffer, char* buffer1, unsigned char i)
{
    unsigned char bitt = 0b00000001;
    unsigned char bittt = 0b11111110;
    sprintf(buffer1, "%u", i);
    if((buffer[0] == 'O') && (buffer[1] == 'N') && (buffer[2] == '0') && ((buffer[3] - 48) == i) && (buffer[4] == '#'))
    {
        bitt = savee | (bitt << (i - 1));
        LATC = bitt;
        savee = bitt; savee1 = savee; savee2 = savee;
    }
    else if((buffer[0] == 'O') && (buffer[1] == 'N') && (buffer[2] == '*') && (buffer[3] == '#'))
    {
        LATC = 0xFF;
        savee = 0b11111111; savee1 = savee; savee2 = savee;
    }
    if((buffer[0] == 'O') && (buffer[1] == 'F') && (buffer[2] == 'F') && (buffer[3] == '0') && ((buffer[4] - 48) == i) && (buffer[5] == '#'))
    {
            
        unsigned char cnt = 1;
        while(cnt < i)
        {
            bittt <<= 1;
            bittt += 1;
            cnt++;
        }
        bittt &= savee;
        LATC = bittt;
        savee = bittt; savee1 = savee; savee2 = savee;
    }
    else if((buffer[0] == 'O') && (buffer[1] == 'F') && (buffer[2] == 'F') && (buffer[3] == '*') && (buffer[4] == '#'))
    {
        LATC = 0;
        savee = 0; savee1 = savee; savee2 = savee;
    }   
    unsigned char k = 0b00000001;
    unsigned char j = 0b11111110;
    unsigned char flag = 0;
    if((buffer[0] == 'B') && (buffer[1] == 'L') && (buffer[2] == 'I') && (buffer[3] == 'N') && (buffer[4] == 'K') && (buffer[5] == '0') && ((buffer[6] - 48) == i) && (buffer[7] == '#'))
    {
        k = savee1 | (k << (i - 1));
        LATC = k;
        savee1 = k;
        unsigned char cnt = 1;
        while(cnt < i)
        {
            j <<= 1;
            j += 1;
            cnt++;
        }
        j &= savee2; LATC = j;
        savee2 = j;
        while(1)
        {
            LATC = k;
            __delay_ms(500); if(RCIF) break;
            LATC = j;
            __delay_ms(500); if(RCIF) break;
        }
    }
    else if((buffer[0] == 'B') && (buffer[1] == 'L') && (buffer[2] == 'I') && (buffer[3] == 'N') && (buffer[4] == 'K') && (buffer[5] == '*') && (buffer[6] == '#'))
    {
        savee1 = 0; savee2 = 0xFF;
        while(1)
        {
            LATC = savee1;
            __delay_ms(500); if(RCIF) break;
            LATC = savee2;
            __delay_ms(500); if(RCIF) break;
        }
    }
}

void main ()
{
    OSCILLATOR_Initialize();
    PIN_MANAGER_Initialize();
    EUSART_Initialize();
    savee1 = savee; savee2 = savee;
    while(1)
    {
        for(unsigned char i = 0; i < 9; i++)
        {
            while(!RCIF);
            buffer[i] = EUSART_Read();
            if(buffer[i] == '#') i = 15;
            if(buffer[1] == 'L')
                val = buffer[6] - 48;
            else if(buffer[1] == 'N')
                val = buffer[3] - 48;
            else if(buffer[1] == 'F')
                val = buffer[4] - 48;
        }
        ON_OFF_BLINK(buffer, buffer1, val);
    }
}
