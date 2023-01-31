/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F1509
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    char ch_buffer[10]= {0};
    unsigned char  i = 0;
    unsigned char led_on = 0;
    unsigned char led_off = 0;
    unsigned char led_blink = 0;
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        i = 0;
        while(i<9)
        {
            while(!EUSART_is_rx_ready());
            ch_buffer[i] = EUSART_Read();
            if(ch_buffer[i] == '#') i= 10;
            else i++;
        }
        if((ch_buffer[0]=='O') && (ch_buffer[1]=='N') && (ch_buffer[2]=='0') && (ch_buffer[4]=='#'))
        {
            led_on = (ch_buffer[2] - 48)*10 + (ch_buffer[3] - 48);
            if(led_on == 1) LATCbits.LATC0= 1;
            else if(led_on == 2) LATCbits.LATC1= 1;
            else if(led_on == 3) LATCbits.LATC2= 1;
            else if(led_on == 4) LATCbits.LATC3= 1;
            else if(led_on == 5) LATCbits.LATC4= 1;
            else if(led_on == 6) LATCbits.LATC5= 1;
            else if(led_on == 7) LATCbits.LATC6= 1;
            else if(led_on == 8) LATCbits.LATC7= 1;
        }
        else if((ch_buffer[0]=='O') && (ch_buffer[1]=='N') && (ch_buffer[2]=='*') && (ch_buffer[3]=='#'))
        {
            LATC = 0b11111111;
        }
        if((ch_buffer[0]=='O') && (ch_buffer[1]=='F') && (ch_buffer[2]=='F') && (ch_buffer[3]=='0') && (ch_buffer[5]=='#'))
        {
            led_off = (ch_buffer[3] - 48)*10 + (ch_buffer[4] - 48);
            if(led_off == 1) LATCbits.LATC0= 0;
            else if(led_off == 2) LATCbits.LATC1= 0;
            else if(led_off == 3) LATCbits.LATC2= 0;
            else if(led_off == 4) LATCbits.LATC3= 0;
            else if(led_off == 5) LATCbits.LATC4= 0;
            else if(led_off == 6) LATCbits.LATC5= 0;
            else if(led_off == 7) LATCbits.LATC6= 0;
            else if(led_off == 8) LATCbits.LATC7= 0;
        }
        else if((ch_buffer[0]=='O') && (ch_buffer[1]=='F') && (ch_buffer[2]=='F') && (ch_buffer[3]=='*') && (ch_buffer[4]=='#'))
        {
            LATC = 0;
        }
        if((ch_buffer[0]=='B') && (ch_buffer[1]=='L') && (ch_buffer[2]=='I') && (ch_buffer[3]=='N') && (ch_buffer[4]=='K') && (ch_buffer[5]=='0') && (ch_buffer[7]=='#'))
        {
            led_blink = (ch_buffer[5] - 48)*10 + (ch_buffer[6] - 48);
            if(led_blink == 1) {while(1){LATCbits.LATC0= 1; __delay_ms(500); if(RCIF) break; LATCbits.LATC0 = 0; __delay_ms(500); if(RCIF) break;}}
            else if(led_blink == 2) {while(1){LATCbits.LATC1= 1; __delay_ms(500); if(RCIF) break; LATCbits.LATC1= 0; __delay_ms(500); if(RCIF) break;}}
            else if(led_blink == 3) {while(1){LATCbits.LATC2= 1; __delay_ms(500); if(RCIF) break; LATCbits.LATC2= 0; __delay_ms(500); if(RCIF) break;}}
            else if(led_blink == 4) {while(1){LATCbits.LATC3= 1; __delay_ms(500); if(RCIF) break; LATCbits.LATC3= 0; __delay_ms(500); if(RCIF) break;}}
            else if(led_blink == 5) {while(1){LATCbits.LATC4= 1; __delay_ms(500); if(RCIF) break; LATCbits.LATC4= 0; __delay_ms(500); if(RCIF) break;}}
            else if(led_blink == 6) {while(1){LATCbits.LATC5= 1; __delay_ms(500); if(RCIF) break; LATCbits.LATC5= 0; __delay_ms(500); if(RCIF) break;}}
            else if(led_blink == 7) {while(1){LATCbits.LATC6= 1; __delay_ms(500); if(RCIF) break; LATCbits.LATC6= 0; __delay_ms(500); if(RCIF) break;}}
            else if(led_blink == 8) {while(1){LATCbits.LATC7= 1; __delay_ms(500); if(RCIF) break; LATCbits.LATC7= 0; __delay_ms(500); if(RCIF) break;}}
        }
        else if((ch_buffer[0]=='B') && (ch_buffer[1]=='L') && (ch_buffer[2]=='I') && (ch_buffer[3]=='N') && (ch_buffer[4]=='K') && (ch_buffer[5]=='*') && (ch_buffer[6]=='#'))
        {
            while(1)
            {
                LATC = 0b11111111; __delay_ms(500); if(RCIF) break; LATC = 0; __delay_ms(500); if(RCIF) break;
            }
            
        }
    }
}
/**
 End of File
*/