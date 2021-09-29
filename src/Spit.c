#include "Banks/SetAutoBank.h"
#include "main.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"

const UINT8 anim_spit_hurl[] = {2,0,1};

UINT8 fliptime = 0;

typedef struct {
    INT8 vx;
    INT8 vy;
}CUSTOM_DATA;

 
 void CreateSpit(UINT16 x,UINT16 y,INT8 vx,INT8 vy){
  Sprite* spr;
  spr= SpriteManagerAdd(Spit,x,y);
  CUSTOM_DATA* data = (CUSTOM_DATA*)spr->custom_data;

    data->vx = vx;
    data->vy = vy;

 }

void Start_Spit(){
SetSpriteAnim(THIS,anim_spit_hurl,10u);

//	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
//	data->vy = 1;
}





void Update_Spit(){
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    fliptime++;
    if(fliptime>2){
	if(TranslateSprite(THIS, data->vx>>5, data->vy>>5)) {
		//data->vy = -data->vy;
      // SetSpriteAnim(THIS,anim_spit_plop,10u);
      
        SpriteManagerRemoveSprite(THIS);
	}
    fliptime=0;
    }

}
void Destroy_Spit(){

}

