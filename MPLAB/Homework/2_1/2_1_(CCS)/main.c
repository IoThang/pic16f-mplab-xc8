#include <main.h>
const UNSIGNED char so[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
void main()
{
   set_tris_c(0);
   set_tris_d(0);
   while(TRUE)
   {
       for(int32 k = 0; k < 10; k++)
       {
           output_c(so[k]);
           for(int32 f = 0; f < 10; f++)
           {
              output_d(so[f]);
              delay_ms(200);
           }
       }
   }

}
