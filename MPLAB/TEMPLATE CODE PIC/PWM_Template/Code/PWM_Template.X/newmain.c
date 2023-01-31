// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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

//          KET HOP PWM VA UART
#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 20000000
#define IN1         PORTCbits.RC3
#define IN2         PORTCbits.RC4
#define Baud_rate 9600
#define SPBRGH_SPBRG    ((_XTAL_FREQ / 4) / Baud_rate) - 1
uint16_t dutyCycle = 0;
unsigned char rxdata;
unsigned char lenh[3];
unsigned char chuc, donvi;
float val;
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
void config()
{
    PWM_Init();
    RX_Init();
    TX_Init();
    //  Configure Interrupt
	RCIF=0;
	RCIE=1;
	PEIE=1;
	GIE=1;     
    
    TRISC6 = 0;
    TRISC7 = 1;
    TRISC3 = TRISC4 = 0;
    ANSEL = ANSELH = 0;
}
void main(void) {
    config();
    UART_send_string("Giao tiep UART da duoc khoi tao");
    PWM_Set_Duty(0);    
    while(1)
    {
    }
    return;
}

//  Nhan "P" -> stop, "S" -> start, "L","R" -> Dao chieu
//void __interrupt() ISR(void)
//{
//	if(RCIE && RCIF)
//	{
//        rxdata = RCREG;
//        if(rxdata == 'S') 
//		{
//            IN1 = 1; IN2 = 0;
//            PWM_Set_Duty(500);
//		}
//        else if(rxdata == 'P') 
//		{
//            IN1 = IN2 = 0;
//            PWM_Set_Duty(0);
//		}
//        else if(rxdata == 'R') 
//		{
//            IN1 = 1; IN2 = 0;
//            PWM_Set_Duty(500);
//		}
//        else if(rxdata == 'L') 
//		{
//            IN1 = 0; IN2 = 1;
//            PWM_Set_Duty(500);
//		}
//	}   
//	//// kiem tra loi
//	if( OERR==1)
//	{
//	  CREN=0;/// de xoa loi
//	  CREN=1;/// cho hoat dong lai		
//	}
//    RCIF=0;
//}
//void __interrupt() ISR(void)
//{
//    if(RCIE && RCIF)
//    {
//            if(lenh[] == 'L')
//            {
//                IN1 = 0; IN2 = 1;
//                chuc = lenh[1] - 48;
//                donvi = lenh[2] - 48;
//                val = ((lenh[1] - 48) * 10 + (lenh[0] - 48)) *1.0/ 100;
//                PWM_Set_Duty(val * 500);
//            }
//            if(lenh[0] == 'R')
//            {
//                IN1 = 1; IN2 = 0;
//                chuc = lenh[1] - 48;
//                donvi = lenh[2] - 48;
//                val = ((lenh[1] - 48) * 10 + (lenh[0] - 48)) *1.0/ 100;
//                PWM_Set_Duty(val * 500);
//            }
//        
//    }
//    RCIF=0;
//}