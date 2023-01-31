// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
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
#define _XTAL_FREQ 20000000
#define Baud_rate 9600
#define SPBRGH_SPBRG    ((_XTAL_FREQ / 4) / Baud_rate) - 1

unsigned char rxdata;

void TX_Init(void)
{
//  [SPBRGH:SPBRG] = ((_XTAL_FREQ / 4) / Baud_rate) - 1;
    
	SPBRGH = SPBRGH_SPBRG >> 8;
	SPBRG = SPBRGH_SPBRG;
	
	BRGH=1;
	BRG16= 1;	
	SYNC=0;
    
	SPEN=1;
	TX9=0;
    
	TXEN=1;    
}
void RX_Init(void)
{
	SPBRGH = SPBRGH_SPBRG >> 8;
	SPBRG = SPBRGH_SPBRG;
	BRGH = 1;
	BRG16 = 1;
	
	SYNC=0;
	SPEN=1;
	
	RX9=0;
	
	CREN=1;	    
}

void config()
{
//    SCS = 0;
    RX_Init();
    TX_Init();
    //  Configure Interrupt
	RCIF=0;
	RCIE=1;
	PEIE=1;
	GIE=1;     
    
    TRISC6 = 0;
    TRISC7 = 1;
    TRISA = TRISD = 0;
    RA3 = RA4 = RD0 = 1;
    ANSEL = ANSELH = 0;
}
void UART_send_char(char bt)
{
    while(!TXIF);
    TXREG = bt;
}
void UART_send_string(char* st_pt)
{
    while(*st_pt)
        UART_send_char(*st_pt++);
}
void main(void) {
    config();
    UART_send_string("Giao tiep UART da duoc khoi tao");
    while(1)
    {      
    }
    return;
}
void __interrupt() ISR(void)
{
	if(RCIE && RCIF)
	{
        rxdata = RCREG;
        if(rxdata == '1') 
		{
			RA3 = RA4 = RD0 = 0;
            UART_send_string("Number");  
		}

	}   
	//// kiem tra loi
	if( OERR==1)
	{
	  CREN=0;/// de xoa loi
	  CREN=1;/// cho hoat dong lai		
	}
    RCIF=0;
}