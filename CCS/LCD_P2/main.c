#include <main.h>
#include <lcd.c>
#define BUTTON1 PIN_E0
char chu[39] = {"                VI XU LY                "};
//  x=           0123456789012345678901234567890123456789    a[x]

/*void _DichPhai(void)   //Chi chay duoc 1 lan
{
    char i,j;
   
      FOR(i = 24; i >= 0; i--) 
      {
         for(j = 0; j < 16; j++)  //ko dc j = 1. Khi xet TH i = 0; j = 1; => chu[1], se khong chay dc TH chu[0]
         {
            lcd_gotoxy(j + 1, 1);
            printf(lcd_putc,"%c", chu[i + j]);
         }
         delay_ms(100);
      }
}*/
void _BUTTON()
{
   if(input(BUTTON1) == 0)
   {
      delay_ms(20);
      if(input(BUTTON1) == 0)
      {
         return;
         while(input(BUTTON1) == 0);
      }
   }
}
void _DichPhai()
{
      char i,j;
   while(1)
   {
      FOR(i = 0; i <= 24; i++) 
      {
         for(j = 0; j < 16; j++)  //ko dc j = 1. Khi xet TH i = 0; j = 1; => chu[1], se khong chay dc TH chu[0]
         {
            lcd_gotoxy(j + 1, 2);
            printf(lcd_putc,"%c", chu[24 - i + j]);
            _BUTTON();
         }
         delay_ms(100);
      }
   }
}
void _DichTrai()
{
   while(1)
   {
      char i,j;
      FOR(i = 0; i <= 24; i++) 
      {
         for(j = 0; j < 16; j++)  //ko dc j = 1. Khi xet TH i = 0; j = 1; => chu[1], se khong chay dc TH chu[0]
         {
            lcd_gotoxy(j + 1, 2);
            printf(lcd_putc,"%c", chu[i + j]);
            _BUTTON();
         }
         delay_ms(100);
      }
   }
}

void main()
{
   lcd_init () ;
   lcd_putc ('\f'); //clear screen

   WHILE (TRUE)
   {
      lcd_gotoxy(1,1);
      lcd_putc("TRUONG DUC THANG");
      _DichPhai();
      _DichTrai();
   }

   
}

