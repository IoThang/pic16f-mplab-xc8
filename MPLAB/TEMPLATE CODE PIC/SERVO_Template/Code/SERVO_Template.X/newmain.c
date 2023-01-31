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
#define _XTAL_FREQ 16000000
unsigned char on_time = 0;
//  Do chu ki PWM qua lon (tan so PWM f = 50Hz qua nho). PWM khong dap ung duoc
//=> Dung timer0 de tao xung PWM
void TIMER0_Init(void)
{
    TMR0 = 131;
    PS2 = 1;
    PS1 = 0;
    PS0 = 1;
    T0CS = 0;
    PSA = 0;    
}
void config(void)
{
    TIMER0_Init();
    TRISD = 0;
    ANSEL = ANSELH = 0;
    
    //  Interrupt timer0
    PEIE = 1;
	GIE = 1; 
    T0IF = 0;
    T0IE = 1;
}
void main(void) {
    config();
    while(1)
    {
    }
    return;
}
void __interrupt() ISR(void)
{
    if(T0IE && T0IF)
    {
        
    }
    T0IF = 0;
}