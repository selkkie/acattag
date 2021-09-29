#include "Banks/SetAutoBank.h"
#include "main.h"
#include "ZGBMain.h"
#include "Keys.h"
#include "Scroll.h"
#include "Palette.h"
#include "Sound.h"
IMPORT_MAP(pressstart);

void START() {
    	BGP_REG = PAL_DEF(3,2,1,0);
    InitScroll(BANK(pressstart), &pressstart, 0, 0);

}




void UPDATE() {

if(KEY_TICKED(J_START)){
   PlayFx(CHANNEL_1, 10, 0x74, 0x87, 0x53, 0x66,0x86);
   wait_vbl_done();
    SetState(StateGame);
    
}
}
