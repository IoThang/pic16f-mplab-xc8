#include <main.h>
#include <lcd.c>
#define _BUTTON1 PIN_E0
int mode = 0;
const unsigned char led[2] = {0b01000000, 0b01111001};
//xem lai device adc = 16 thu xem

void fun(int mode)
{
   if (mode == 0)
   {
      output_c(led[0]);
      set_adc_channel(0);   //only 1 channel is selected at a time;
      delay_ms(10);
      int16 temp = read_adc() / 2.046;
      lcd_gotoxy(8,2);
      printf(lcd_putc,"%02lu  C", temp);   // int16 -> %lu
   }
   else if(mode == 1)
   {
      output_c(led[1]);
      set_adc_channel(1);   //only 1 channel is selected at a time;
      delay_ms(10);
      int16 temp = read_adc() / 2.046;
      lcd_gotoxy(8,2);
      printf(lcd_putc,"%02lu  C", temp);   // int16 -> %lu
   }
}

void main()
{
   lcd_init();
   set_tris_a(1); //configures port A as input
   set_tris_c(0);
   set_tris_d(0);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_adc_ports(sAN0|sAN1|VSS_VDD);  //Choose 1 port(ANxx) and Ref+, Ref- for ADC
   while(TRUE)
   {
      delay_ms(10);
      lcd_gotoxy(5,1);
      lcd_putc("DO NHIET DO");
      set_adc_channel(0);   //only 1 channel is selected at a time;
      
      fun(mode);
      
      if(input(_BUTTON1) == 0)
      {
         delay_ms(20);
         if(input(_BUTTON1) == 0)
         {
            if(mode == 0)
            mode = 1;
            else
            mode = 0;
            while(input(_BUTTON1) == 0);
         }
      }
      
      lcd_gotoxy(11, 2);
      lcd_putc(0xDF);   //Add character '*' into row = 2; col = 11
   }

}
