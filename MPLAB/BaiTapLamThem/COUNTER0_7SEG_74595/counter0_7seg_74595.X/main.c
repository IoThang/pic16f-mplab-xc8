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

unsigned char maLed[]={0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
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
        xuat = laybit7(xuatbyte & b);
        LATCbits.LATC0 = xuat;        
        LATCbits.LATC1 = 0; LATCbits.LATC1 = 1;
        b >>= 1;
    }
}
void hienthi(unsigned int n)
{
    xuat_1byte(maLed[n % 10]);
    xuat_1byte(maLed[n % 100 / 10]);
    xuat_1byte(maLed[n / 100 % 10]);
    xuat_1byte(maLed[n / 1000]);
    LATCbits.LATC2 = 0; LATCbits.LATC2 = 1;
    __delay_ms(10);
}
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    TMR0_Initialize();
    while (1)
    {
        if(TMR0_ReadTimer() * 50 > 1000)
            TMR0_Reload();
        hienthi(TMR0_ReadTimer() * 50);
    }
}
/**
 End of File
*/