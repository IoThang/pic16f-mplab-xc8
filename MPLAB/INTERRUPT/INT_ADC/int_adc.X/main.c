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
#include "lcd.h"
#include <stdio.h>
//unsigned char maLed[]={0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
//unsigned char DLHT[2] = {0xFF,0xFF};
unsigned char temp = 0;
unsigned char buffer[10];
//void tachSo(unsigned char n)
//{
//    char i = 1;
//    while(n != 0)
//    {
//        DLHT[i--] = maLed[n % 10];
//        n /= 10;
//    }
//}
//void hienthi()
//{
//    unsigned char quet = 0b11110111;
//    for(unsigned char j = 0; j < 5; j++)
//    {
//        for(unsigned char i = 0; i < 2; i++)
//        {
//            LATB = quet;
//            LATC = DLHT[i];
//            __delay_ms(1);
//            LATC = 0xFF;
//            quet = (quet << 1) + 1;
//        }
//    }
//}
void My_ADC_ISR()
{
        temp = ADC_GetConversion(channel_AN0);
        temp = temp / 2;
}
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    LCD_Initialize();
    //ADC_Initialize();
    ADC_SelectChannel(channel_AN0);
    ADC_SetInterruptHandler(My_ADC_ISR);
    while (1)
    {
        ADC_StartConversion();
        LCDGoto(5, 0);
        sprintf(buffer, "%u", temp);
        LCDPutStr(buffer);
    }
}
/**
 End of File
*/