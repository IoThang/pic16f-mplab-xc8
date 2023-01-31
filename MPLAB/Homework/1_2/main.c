#include <main.h>

void main()
{
   set_tris_d(0);
   while(TRUE)
   {
      output_bit(PIN_D0,1);
      output_bit(PIN_D1,0);
      output_bit(PIN_D2,0);
      delay_ms(500);
      
      output_bit(PIN_D0,1);
      output_bit(PIN_D1,1);
      output_bit(PIN_D2,0);
      delay_ms(500);
      
      output_bit(PIN_D0,1);
      output_bit(PIN_D1,1);
      output_bit(PIN_D2,1);
      delay_ms(500);
      
      output_d(0);
      delay_ms(500);

   }

}
