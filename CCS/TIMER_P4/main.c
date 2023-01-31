//Chua lam xong 
//Hinh dau tien trong video https://youtu.be/xwMwh0_m9Yw
#include <main.h>
#include <lcd.c>
unsigned char sp;
unsigned char flag = 0;
void fun()
{
   sp = get_timer0();
   if(input(pin_b0) == 0)
   {
      delay_ms(20);
      if(input(pin_b0) == 0)
      {
         if(flag == 0)
         {
            set_timer0(0);
            flag = 1;
         }
         lcd_gotoxy(3,1);
         printf(lcd_putc,"DEM SAN PHAM");
         while(input(pin_b0) == 0);
      }
   }
   if(flag == 1)
   {
      lcd_gotoxy(3, 2);
      printf(lcd_putc,"SO LUONG: %2u", sp);
   }
   if(input(pin_b1) == 0)
   {
      delay_ms(20);
      if(input(pin_b1) == 0)
      {
         
         while(input(pin_b1) == 0);
      }
   }
}
void main()
{
   lcd_init();
   setup_timer_0(T0_EXT_H_TO_L|T0_DIV_1);
   set_timer0(0);
   
   lcd_gotoxy(4, 1);
   printf(lcd_putc,"NHAN START");
   lcd_gotoxy(3, 2);
   printf(lcd_putc,"DE KHOI DONG");
   while(TRUE)
   {
      fun();
   }

}
