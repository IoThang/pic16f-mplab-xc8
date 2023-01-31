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
}
void dich_byte(unsigned int16 n)
{
   unsigned int8 x = maLed[n % 10]; //Don vi
   unsigned int8 y = maLed[n % 100 / 10]; //Chuc
   unsigned int8 z = maLed[n % 1000 / 100]; //Hang tram
   unsigned int8 k = maLed[n / 1000 ];  //So hang nghin
   xuat_1byte(x);
   xuat_1byte(y);
   xuat_1byte(z);
   xuat_1byte(k);
   output_low(rck); output_high(rck); 
}
void main()
{
   set_tris_c(0);
   while(TRUE)
   {
      for(unsigned int16 i = 0; i < 9999; i++)
      {
         dich_byte(i);
         delay_ms(50);
      }
   }

}
