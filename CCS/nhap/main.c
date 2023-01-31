

#include <main.h>

UNSIGNED INT8 DEM, I,a,m ;
#DEFINE UP PIN_E0
#DEFINE DOWN PIN_E1
#DEFINE START PIN_E2
const UNSIGNED char MA7DOAN[]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0b11111000, 0x80, 0x90};
VOID HIENTHI_DELAY(INT8 DEM)
{
   FOR (I = 0; I < 200; I++)
   {
      OUTPUT_B (MA7DOAN[DEM % 10]); OUTPUT_LOW (PIN_D0);
      DELAY_MS (1); OUTPUT_HIGH (PIN_D0);
      OUTPUT_B (MA7DOAN[DEM / 10]); OUTPUT_LOW (PIN_D1);
      DELAY_MS (1); OUTPUT_HIGH (PIN_D1);
   }
}
VOID MAIN()
 {
   SET_TRIS_B (0x00); SET_TRIS_E (0xFF); SET_TRIS_D (0x00);
   OUTPUT_D (0XFF) ;
   DEM = 5;
   WHILE (TRUE)
   {
      HIENTHI_DELAY (DEM) ;
      WHILE (input (UP) == 0)
      {
         IF (DEM == 15) break;
         ELSE
         {
            DEM = DEM + 1;
            HIENTHI_DELAY (DEM) ;
         }
      }

      WHILE (input (DOWN) == 0)
      {
         IF (DEM <= 6) break;
         ELSE
         {
            DEM = DEM - 2;
            HIENTHI_DELAY (DEM) ;
         }
      }

      WHILE (input (START) == 0)
      {
         FOR (m = 0; m <= DEM; m++)
         {
            HIENTHI_DELAY (m) ;
         }
      }}}


