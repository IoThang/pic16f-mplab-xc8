/*
 * File:   newmain.c
 * Author: tramt
 *
 * Created on Ngày 28 tháng 3 n?m 2022, 14:38
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
#define Baud_rate 9600
#define _XTAL_FREQ 8000000
char get_value;
//void uart_initialize()
//{
//    TRISCbits.TRISC6 = 0; //TX Pin set as output
//    TRISCbits.TRISC7 = 1; //RX Pin set as input
//    SPBRG = 12;
//    BRGH = 1; // baudrate toc do cao
//    SYNC = 0; // Asynchronous
//    SPEN = 1; // cho phep cong noi tiep
//    TXEN = 1; // cho phep truyen 
//    CREN = 1; // cho phep nhan
//    // chon che do truyen nhan 8 bits 
//    TX9 = 0;
//    RX9 = 0;
//}
//void uart_sendChar(char b)
//{
//    while(!TRMT); // Cho cho den khi thanh ghi dich trong
//    TXREG = b; // ghi gia tri truyen vao thanh ghi TXREG
//}
//char uart_getChar()
//{
//   while (!RCIF); // Cho cho den khi thanh ghi dich trong
//   RCIF=0;  
//   return RCREG;
//}
//void UART_sendString(char* str) 
//{
//   while (*str) 
//   {
//       uart_sendChar(*str++);
//   }
//}
//void main(void) 
//{
//   TRISB3 = 0; // chon B3 la output 
//   RB3 = 0;
//   uart_initialize();                  
//   UART_sendString("Giao tiep UART da duoc khoi tao");
//   while (1) 
//   {
//       get_value = uart_getChar(); //Do uart ham char nen co gia tri de hung
//       if (get_value == 49) 
//       {
//           RB3 = 1; 
//           UART_sendString("LED -> ON"); 
//           uart_sendChar(10); // gui ky tu xuong dong
//       }
//       if (get_value == 48) 
//       {
//           RB3 = 0; 
//           UART_sendString("LED-> OFF"); 
//           uart_sendChar(10); 
//       }
//   }
//   return;
//}

//***Initializing UART module for PIC16F877A***//
void Initialize_UART(void)
{
    //****Setting I/O pins for UART****//
    TRISC6 = 0; // TX Pin set as output
    TRISC7 = 1; // RX Pin set as input
    //________I/O pins set __________//
    
    /**Initialize SPBRG register for required 
    baud rate and set BRGH for fast baud_rate**/
    SPBRG = ((_XTAL_FREQ/16)/Baud_rate) - 1;
    BRGH  = 1;  // for high baud_rate
    //_________End of baud_rate setting_________//
    
    //****Enable Asynchronous serial port*******//
    SYNC  = 0;    // Asynchronous
    SPEN  = 1;    // Enable serial port pins
    //_____Asynchronous serial port enabled_______//

    //**Lets prepare for transmission & reception**//
    TXEN  = 1;    // enable transmission
    CREN  = 1;    // enable reception
    //__UART module up and ready for transmission and reception__//
    
    //**Select 8-bit mode**//  
    TX9   = 0;    // 8-bit reception selected
    RX9   = 0;    // 8-bit reception mode selected
    //__8-bit mode selected__//     
}
//________UART module Initialized__________//

//**Function to send one byte of date to UART**//
void UART_send_char(char bt)  //EUSART_Write
{
    while(!TXIF);  // hold the program till TX buffer is free
    TXREG = bt; //Load the transmitter buffer with the received value
}
//_____________End of function________________//

//**Function to get one byte of date from UART**//
char UART_get_char()   //EUSART_Read
{
    if(OERR) // check for Error 
    {
        CREN = 0; //If error -> Reset 
        CREN = 1; //If error -> Reset 
    }
    
    while(!RCIF);  // hold the program till RX buffer is free
    
    return RCREG; //receive the value and send it to main function
}
//_____________End of function________________//

//**Function to convert string to byte**//
void UART_send_string(char* st_pt)
{
    while(*st_pt) //if there is a char
        UART_send_char(*st_pt++); //process it as a byte data
}
//___________End of function______________//

// **********START of Main Function**************//
void main(void)
{
    int get_value;
    
    TRISB = 0x00; //Initialize PortB as output
    Initialize_UART();    //Initialize UART module                    
    
    UART_send_string("UART Module Initialized and active");    // Introductory Text
    
    while(1) //Infinite loop
    {
      get_value = UART_get_char(); 
        
        if (get_value == '1') //If the user sends "1"
        {
            RB3=1; //Turn on LED
            UART_send_string("RED LED -> ON"); //Send notification to the computer 
            UART_send_char(10);//ASCII value 10 is used for carriage return (to print in new line)
        }
        
        if (get_value == '0') //If the user sends "0"
        {
           RB3=0; //Turn off LED
           UART_send_string("RED -> OFF"); //Send notification to the computer      
           UART_send_char(10);//ASCII value 10 is used for carriage return (to print in new line)
        }
       
    }
}
// **********END of Main Function**************//