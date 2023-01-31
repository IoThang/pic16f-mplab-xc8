//https://youtu.be/VvQHP69yakA
#include <main.h>
#include <lcd.c>
//xem lai device adc = 16 thu xem
void main()
{
   lcd_init();
   set_tris_d(0);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_adc_ports(sAN0|VSS_VDD);  //Choose 1 port(ANxx) and Ref+, Ref- for ADC
   while(TRUE)
   {
      set_adc_channel(0);   //only 1 channel is selected at a time;
      delay_ms(10);
      lcd_gotoxy(5,1);
      lcd_putc("DO NHIET DO");
      int16 temp = read_adc() / 2.046;
      lcd_gotoxy(8,2);
      printf(lcd_putc,"%02lu  C", temp);   // int16 -> %lu
      lcd_gotoxy(11, 2);
      lcd_putc(0xDF);   //Add character '*' into row = 2; col = 11
   }

}
