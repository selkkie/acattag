#include "Banks/SetAutoBank.h"
#include "main.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Print.h"


const UINT8 anim_spit_hurl[] = {2,0,1};

extern BYTE flipwhen;
typedef struct {
    UINT8 oritentation; //L U R D
    UINT8 fliptime; //L U R D
    INT8 vx;
    INT8 vy;
}CUSTOM_DATA;

void Start_Spit(){
SetSpriteAnim(THIS,anim_spit_hurl,10u);

}

// char* iota(int i, char b[]){
//     char const digit[] = "0123456789";
//     char* p = b;
//     if(i<0){
//         *p++ = '-';
//         i *= -1;
//     }
//     int shifter = i;
//     do{ //Move to where representation ends
//         ++p;
//         shifter = shifter/10;
//     }while(shifter);
//     *p = '\0';
//     do{ //Move back, inserting digits as u go
//         *--p = digit[i%10];
//         i = i/10;
//     }while(i);
//     return b;
// }


void Update_Spit(){

  CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

    // char snum[5];
    // iota(data->vx,snum);
    // SHOW_WIN;
    // PRINT_POS(0,1);
    
    // Printf(snum); Printf("        ");
    //   iota(data->vy,snum);
    // PRINT_POS(0,2);
     
    // Printf(snum); Printf("        ");

   // data->fliptime++;
   // UINT8 fliptime = data->fliptime;
   // if(fliptime>3){
    
    // if(THIS->vx == -1)
    // {
    
      if(TranslateSprite(THIS, data->vx, data->vy)) {

            SpriteManagerRemoveSprite(THIS);
        }
    


   // data->fliptime=0;
   // }

}
void Destroy_Spit(){

}

