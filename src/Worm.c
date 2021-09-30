
#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Print.h"
#include "Keys.h"
 const UINT8 anim_squirm[] = {2,0,1};
 const UINT8 anim_squirm_side[] = {2,2,3};

const UINT8 anims[4][3]={
	{2,0,1},
	{2,2,3},
	{2,0,1},
	{2,2,3},
};

UINT8 frameskip = 0;
enum mirror mirrors[]={V_MIRROR,H_MIRROR,HV_MIRROR,HV_MIRROR};
INT8 shift=0;
const INT8 dirx[]={1,0,-1,0};
const INT8 diry[]={0,1,0,-1};
// 				//R,D,L,U

// const INT8 dirx[]={-1,0,1,0};
// const INT8 diry[]={0,-1,0,1};
BYTE clonestartile = 0;

void Start_Worm(){
	SetSpriteAnim(THIS, anim_squirm, 10u);
		TranslateSprite(THIS,0,4);
}


void CloneStartTile(){
	 clonestartile = 1;
	//     UINT8 i;
    // for(i=0;i<numloops;i++){
    //     wait_vbl_done();
    // }

	// set_bkg_tile_xy(THIS->x-1,THIS->y,get_bkg_tile_xy(THIS->x+1,THIS->y)); 
	//idk why this stopped working but frick me ig
	set_bkg_tile_xy(4,5,0x27);
}
void Move_Worm(){




if(TranslateSprite(THIS,dirx[(shift+1)%4],diry[(shift+1)%4])){
//if there is a floor under me, 

	//undo the test collision
//TranslateSprite(THIS,dirx[(shift+3)%3],diry[(shift+3)%3]);

	//try moving along it
	if(TranslateSprite(THIS,dirx[shift]<<delta_time,diry[shift]<<delta_time)){

		//if i hit a wall, change direction

			shift--;
	if(shift<0)shift=3;
		
		THIS->mirror = mirrors[shift];
		SetSpriteAnim(THIS,anims[shift],10u);
		
	}


}
else{
		//waitpad(J_A);
//if there is no floor, shift the other way
	shift++;
		if(shift>3)shift=0;
	TranslateSprite(THIS,dirx[shift]*3,diry[shift]*3); //force it to move so it gets the first collision instead of tumbling in air
		THIS->mirror = mirrors[shift];
		SetSpriteAnim(THIS,anims[shift],10u);
		//pDelay(1);

}

}
void Update_Worm(){
	if(clonestartile ==0){CloneStartTile();}
	
	frameskip++;
	if(frameskip>2){
		frameskip = 0;
			Move_Worm();
	}


}




void Destroy_Worm(){
}


