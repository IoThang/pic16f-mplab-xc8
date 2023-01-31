#include <main.h>
#bit TMR1IF = 0x0c.0
#bit TMR0IF = 0x0b.2
#bit TMR2IF = 0x0c.1
int bdt = 0;
unsigned char b = 0;
void delay_210ms()  //T1 Den trong 1 chu ki 210ms
{
   set_timer1(43661);
   while(1)
   {
      if(TMR1IF == 1)
      {
         set_timer1(43661); bdt++; TMR1IF = 0;
         if(bdt == 3)
         {
            b =~ b;
            output_b(b);
            bdt = 0;
         }
      }
   }
}
void delay_200ms()  //T1 led sang tat dung ngat- dinh thoi voi chu ki delay 400ms (co nghia la sang 200ms, tat 200ms)
{
   set_timer1(3036);
   while(1)
   {
      if(TMR1IF == 1)
      {
         set_timer1(3036); bdt++; TMR1IF = 0;
         if(bdt == 2)
         {
            b =~ b;
            output_b(b);
            bdt = 0;
         }
      }
   }
}
void delay_1s()  //T1 Den sang trong 1s va tat trong 1s
{
   set_timer1(3036);
   while(1)
   {
      if(TMR1IF == 1)
      {
         set_timer1(3036); bdt++; TMR1IF = 0;
         if(bdt == 10)
         {
            b =~ b;
            output_b(b);
            bdt = 0;
         }
      }
   }
}
void delay_13ms()  //T0 Den  trong 1 chu ki 26 ms,sang trong 13ms va tat trong 13ms
{
   setup_timer_0(T0_INTERNAL|T0_DIV_256);
   set_timer0(0);
   while(1)
   {
      if(TMR0IF == 1)
      {
         set_timer0(0); TMR0IF = 0;
            b =~ b;
            output_b(b);
      }
   }
}
void delay_T0_1s()  //T0 Den sang trong 1s va tat trong 1s
{
   setup_timer_0(T0_INTERNAL|T0_DIV_256);
   set_timer0(15);   //Value: luon lay so nguyen va lam tron len
   while(1)
   {
      if(TMR0IF == 1)
      {
         set_timer0(15); bdt++; TMR0IF = 0;
         if(bdt == 81)
         {
            b =~ b;
            output_b(b);
            bdt = 0;
         }
      }
   }
}
void delay_T2_13ms()
{
   setup_timer_2(T2_DIV_BY_16, 254 , 16);
   set_timer2(0);   ko co set_timer2
   while(1)
   {
      if(TMR2IF == 1)
      {
         set_timer2(0); 
         TMR2IF = 0;
            b =~ b;
            output_b(b);
      }
   }
}
void delay_duty30()
{
   set_timer1(0)
   output_b(0xFF);
   if(get_timer1() > 300
}
void main()
{
   set_tris_b(0);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   output_b(b);
   while(TRUE)
   {
      //delay_210ms();
      //delay_200ms();
      //delay_1s();
      //delay_13ms();
      //delay_T0_1s();
      delay_T2_13ms();
   }

}
