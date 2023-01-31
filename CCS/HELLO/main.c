//cocacola: https://youtu.be/Jds6iRi88Lw
//hello: https://youtu.be/fCqUL3hBUeg
#include <main.h>
const UNSIGNED char hello[21]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, 0xFF,
                              0x89, 0x86, 0xC7, 0xC7, 0xC0,
                              0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, 0xFF};
const UNSIGNED char cocacola[16] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, 0xFF,
                                 0xC6, 0xC0, 0xC6, 0x88,0xC6, 0xC0,0xC7, 0x88};
UNSIGNED char DLHT[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, 0xFF};
void quetLed()
{
   for(unsigned char j = 0; j < 10; j++)
      {
         unsigned char quet = 0b11111110;
         for(unsigned char i = 0; i < 8; i++)
         {
            output_d(quet);
            output_c(DLHT[i]);
            delay_ms(4);
            output_c(0xFF);
            quet = (quet << 1) + 1;
         }
      }
}

void main()
{
   //output_c (0x00); //tat het port c chong nhieu
   set_tris_c (0); //configues
   set_tris_d (0);
   WHILE (TRUE)
   {
      /*for(unsigned int8 i = 0; i < 14; i++)
      {
         for(unsigned int8 j = 0; j < 8; j++)
         {
            DLHT[j] = hello[j + i];
         }
         quetLed();
      }*/
      for(unsigned int8 k = 0; k < 9; k++)
      {
         for(unsigned int8 h = 0; h < 8; h++)
         {
            DLHT[h] = cocacola[h + k];
         }
         quetLed();
      }
      for(unsigned int8 n = 0; n < 5; n++) //lam cho led chop tat (blink)
      {
         for(k = 0; k < 9; k++)
         {
            DLHT[k] = 0xFF;
         }
         quetLed();
         for(k = 0; k < 9; k++)
         {
            DLHT[k] = cocacola[k + 8];
         }
         quetLed();
      } 
   }
}
