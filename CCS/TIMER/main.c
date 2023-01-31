//https://youtu.be/cK6N2QQdhiM
#include <main.h>
#bit TMR1IF = 0x0c.0
//High, low 0.5s
void delay_5ms()   //Use timer0 to internal
{
   set_timer0(0);
   while(get_timer0() < 208)
   {}
}
//High 0.1s, low 0.2s
void delay_1ms(int *flag)  //Use timer1
{
   if(*flag == 1)
   {
      set_timer1(0);
      output_high(pin_d1);
      while(get_timer1() < 5000);
      *flag = 0;
   }
   if(*flag == 0)
   {
      set_timer1(0);
      output_low(pin_d1);
      while(get_timer1() < 10000);
      *flag = 1;
   }
   
}
/*void main()
{
   int *flag = 1;
   output_drive(pin_d0);
   output_high(pin_d0);
   output_drive(pin_d1);   
   setup_timer_0(T0_INTERNAL|T0_DIV_128);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   while(TRUE)
   {
      output_toggle(pin_d0);
      delay_5ms();
      delay_1ms(&flag);
   }

}*/

//Ham main chay 2 xung cung 1 thoi diem
void main ()
{
   int flag = 1;
   output_drive(pin_d0);
   output_drive(pin_d1);
   
   output_high(pin_d0);
   
   setup_timer_0(T0_INTERNAL|T0_DIV_128);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   
   set_timer0(0);
   set_timer1(0);
   
   while(1)
   {
      if(get_timer0() > 207)
      { 
         set_timer0(0);
         output_toggle(pin_d0);
      }
      if(get_timer1() > 5000 && flag == 1)
      {  
         set_timer1(0);
         output_low(pin_d1);
         flag = 0;
      }
      else if(get_timer1() > 10000)
      {
         set_timer1(0);
         output_high(pin_d1);
         flag = 1;
      }
      
   }
}
