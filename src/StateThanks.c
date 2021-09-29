#include "Banks/SetAutoBank.h"
#include "main.h"
#include "ZGBMain.h"
#include "Keys.h"
#include "Scroll.h"
#include "Print.h"
#include "Palette.h"
#include "Sound.h"
IMPORT_TILES(diawindowandfont);
IMPORT_MAP(sabinethx);
IMPORT_MAP(dialogue);

UINT8 delayShow = 106;
BYTE shown = 0;
void START() {
	OBP0_REG = PAL_DEF(2,0,1,3);
	BGP_REG = PAL_DEF(3,2,1,0);


   InitScroll(BANK(sabinethx), &sabinethx, 0, 0);

       
}
void Thank(){
    shown=1;
UINT8 x;
for(x=0;x<delayShow;x++)
{wait_vbl_done;}
   WX_REG = 7;
	   WY_REG = 144-25;
	InitWindow(0,0,BANK(dialogue),&dialogue);


	  INIT_FONT(diawindowandfont,PRINT_WIN);
   SHOW_WIN;
    	  PRINT_POS(1,1);
	   Printf("THANKS FOR PLAYING");

}



void UPDATE() {
  if(shown==0)Thank();

    if(KEY_PRESSED(ANY_KEY_PRESSED)){
        
      
        SetState(StatePressStart);
          HIDE_WIN;
    }
	


}
