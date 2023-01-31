
#include <main.h>
#include <lcd.c>
#define BUTTON PIN_E0   //NUT BUTTON1 CO TAC DUNG NHAN GIU DE DUNG VIEC DEM
#define BUTTON1   PIN_E1
#define BUTTON2   PIN_E2
 const unsigned char chu[] = {"                VI XU LY                "};
//  x=         0123456789012345678901234567890123456789    a[x]
CHAR i, j;
void lcdRunning ()
{
   CHAR i, j;
   FOR(i = 23; i >= 0; i--) 
   {
      for(j = 1; j <= 16; j++)
      {
         lcd_gotoxy(j, 1);
         printf(lcd_putc,"%c", chu[i + j]);
      }
      delay_ms(100);
   }
   lcd_putc('\f');
}
VOID _BUTTON()  //NUT BUTTON1 CO TAC DUNG NHAN GIU DE DUNG VIEC DEM
{
   if(input(BUTTON) == 0)
   {
      delay_ms(20);
      if(input(BUTTON) == 0)
      {
          /*while(1)
          {
               if(input(BUTTON) == 0)
               {
                   DELAY_MS(10);
                   BREAK;
               }
          }*/
          //Cach 2
          int i = 0;
          i++;  //Lam 1 lenh bat ky tang den vo han
          while(input(BUTTON) == 0);
       }
   }
}
VOID _BUTTON1(INT i)
{
i = 0;
if(input(BUTTON1) == 0)
   {
      delay_ms(20);
      if(input(BUTTON1) == 0)
      {
          i++;
          if(i == 60){
          i = 0;}
          while(input(BUTTON1) == 0);
       }
   }
}
VOID _BUTTON2(INT i)
{
i = 0;
if(input(BUTTON2) == 0)
   {
      delay_ms(20);
      if(input(BUTTON2) == 0)
      {
          i--;
          if(i == 0){   //Xet TH neu i = 0, thi i-- se bang -1 nen khoi tao i = 59. Vi i co dau - nen dung signed
          i = 59;}
          while(input(BUTTON2) == 0);
       }
   }
}
void clock_second()
{
   lcd_gotoxy (1, 1) ;
   printf (lcd_putc, "TRUONG DUC THANG") ;
   for (UNSIGNED char i = 0; i < 60; i++)
      {
         lcd_gotoxy (2, 2) ;
         printf (lcd_putc, "DEM GIAY: %02u", i) ;
         delay_ms (1000) ;
      }
}
void clock_minute()
{
   lcd_gotoxy (1, 1) ;
   printf (lcd_putc, "TRUONG DUC THANG") ;
   for(unsigned char j = 0; j < 60; j++)
      {
         for(unsigned char k = 0; k < 60; k++)
         {
            _BUTTON();
            //_BUTTON1(k);
            //_BUTTON2(k);
            lcd_gotoxy (2, 2) ;
            printf(lcd_putc,"DEM PHUT: %02u:%02u", j,  k);
            delay_ms (1000) ;
         }
      }
}
void main()
{
   set_tris_d (0) ;
   lcd_init () ;
   lcd_putc ('\f'); //clear screen

   WHILE (TRUE)
   {

      //Cach 1
      //lcd_putc ("f") ;

      //Cach 2
      //printf (lcd_putc, "TRUONG DUC THANG") ;
      //printf (lcd_putc, " % d", 50);
      //printf (lcd_putc, " % f", 54.12);
      //printf (lcd_putc, "TRUONG DUC THANG") ;
      
      
      lcdRunning();
      //clock_minute();
      //clock_second();
      
   }

   
}

