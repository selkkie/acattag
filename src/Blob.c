#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
 const UINT8 anim_blob_blink[] = {11,0,0,0,0,0,0,1,2,2,1,0};
 const UINT8 anim_blob_spit[] = {10,3,3,3,4,4,4,4,4,4,4};
BYTE blobtile = 0;
UINT16 spitting_frameskip = 0;

typedef struct {

    INT8 vx;
    INT8 vy;
}CUSTOM_DATA;
void CreateSpit(UINT16 x,UINT16 y,INT8 vx,INT8 vy);


void Start_Blob(){
SetSpriteAnim(THIS, anim_blob_blink, 6u);
}

void BlobCloneStartTile(){
	 blobtile = 1;

	set_bkg_tile_xy(10,2,0x53);
}

void BlobSpitAni(){
    SetSpriteAnim(THIS, anim_blob_spit, 25u);
	   Sprite* spt = SpriteManagerAdd(Spit,THIS->x,THIS->y);
  //  CreateSpit(THIS->x,THIS->y,,);
    CUSTOM_DATA* spitdata = (CUSTOM_DATA*)spt->custom_data;
    spitdata->vx = 0;
    spitdata->vy = 40;
}
void BlobSpit(){

}

void Update_Blob(){
	
	if(blobtile ==0){BlobCloneStartTile();}

    	spitting_frameskip++;
	if(spitting_frameskip==250){
		spitting_frameskip = 0;
		 BlobSpitAni();
	}else if (spitting_frameskip == 30){
        SetSpriteAnim(THIS, anim_blob_blink, 6u);
    }else if (spitting_frameskip == 10){
        BlobSpit();
    }

}
void Destroy_Blob(){

}

