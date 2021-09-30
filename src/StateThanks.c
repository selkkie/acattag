#include "Banks/SetAutoBank.h"
#include "main.h"
#include "ZGBMain.h"
#include "Keys.h"
#include "Scroll.h"
#include "Print.h"
#include "Palette.h"
#include "Music.h"
#include "Sound.h"

IMPORT_TILES(diawindowandfont);
IMPORT_MAP(sabinethx);
IMPORT_MAP(dialogue);
DECLARE_MUSIC(getscan);

UINT8 delayShow = 0;
BYTE shown = 0;
void START() {
	OBP0_REG = PAL_DEF(2,0,1,3);
	BGP_REG = PAL_DEF(3,2,1,0);


   InitScroll(BANK(sabinethx), &sabinethx, 0, 0);

       
}
void Thank(){
       PlayMusic(getscan,0);
 


   WX_REG = 7;
	   WY_REG = 144-25;
	InitWindow(0,0,BANK(dialogue),&dialogue);

	  INIT_FONT(diawindowandfont,PRINT_WIN);
   SHOW_WIN;
    	  PRINT_POS(1,1);
	   Printf("THANKS FOR PLAYING");


}



void UPDATE() {
   if(shown==0)
{   delayShow++;
  if(delayShow==60)Thank();
   if(delayShow>=195){StopMusic;shown = 1;}
   }
   //  if(KEY_PRESSED(ANY_KEY_PRESSED)){ disabling this because pertinent variables don't get reset on a new playthrough, gotta force the player to reset manually for now
   //      SetState(StatePressStart);
   //        HIDE_WIN; //also hiding this is ugly atm b/c it overwrote the background tiles
   //  }
	


}
