//https://youtu.be/ZEHO08qkz2E
#include <main.h>
#define ser pin_c0
#define sck pin_c1
#define rck pin_c2
unsigned int16 sp = 0;
unsigned int16 dem = 0;
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
void dich_byte(unsigned int16 sp)
{
   unsigned int x = maLed[sp % 10]; //Don vi
   unsigned int y = maLed[sp / 10 % 10]; //Chuc
   unsigned int z = maLed[sp / 100 % 10]; //Hang tram
   unsigned int k = maLed[sp / 1000 ];  //So hang nghin
   xuat_1byte(x);
   xuat_1byte(y);
   xuat_1byte(z);
   xuat_1byte(k);
   output_low(rck); output_high(rck); 
}
void main()
{
   set_tris_c(0);
   setup_timer_0(T0_EXT_L_TO_H|T0_DIV_1);
   set_timer0(0);
   while(TRUE)
   {
      dem = get_timer0();
      sp = dem * 50;
      dich_byte(sp);
      if(sp > 1000) set_timer0(0);
   }
}
