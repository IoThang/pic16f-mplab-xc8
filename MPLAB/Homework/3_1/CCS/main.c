#include <main.h>
#define ser pin_c0
#define sck pin_c1
#define rck pin_c2
const UNSIGNED char maLed[]={0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
void xuat_1byte(unsigned int8 xuatbyte) 
{
   #bit bser = xuatbyte.7
   for(unsigned int8 i = 0; i < 8; i++)
   {
      output_bit(ser, bser);
      output_low(sck); output_high(sck);
      xuatbyte <<= 1;
   }
   output_low(rck); output_high(rck);
}
void dich_byte(unsigned int8 n)
{
   unsigned int8 y = maLed[n % 10];
   unsigned int8 x = maLed[n / 10];
   xuat_1byte(y);
   xuat_1byte(x);
   output_low(rck); output_high(rck); 
}
void main()
{
   set_tris_c(0);
   while(TRUE)
   {
      for(unsigned char i = 0; i < 99; i++)
      {
         dich_byte(i);
         delay_ms(200);
      }
   }
}
