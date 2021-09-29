#include "Banks/SetAutoBank.h"
#include "main.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "Palette.h"
#include "Keys.h"
#include "Sound.h"
#include "Print.h"
#include "Music.h"

IMPORT_TILES(diawindowandfont);

IMPORT_MAP(dialogue);
IMPORT_MAP(lvl0);
IMPORT_MAP(lvl0Clear);
IMPORT_MAP(lvl1);
IMPORT_MAP(lvl2);
IMPORT_MAP(lvl2Clear);
IMPORT_MAP(lvl3);
IMPORT_MAP(lvl4);
IMPORT_MAP(lvl4Clear);

IMPORT_MAP(lvl2Clear);
IMPORT_MAP(lvl4Clear);
DECLARE_MUSIC(aca);
UINT8 creationRotation = 0;
// void CreateBlob(UINT16 cbx,UINT16 cby,Sprite* cbParent, UINT8 cbOrientation);
// void CreateWorm(UINT16 cwx,UINT16 cwy,Sprite* cwParent, UINT8 cwOrientation);
typedef struct {
    UINT8 orientation; //L U R D
    Sprite* parent;
    int frameskip;
}CUSTOM_DATA;
const UINT8 pieceanimations[8][3]={
	{2,0,1},{2,2,3},
	{2,4,5},{2,6,7},
	{2,8,9},{2,10,11},
	{2,12,13},{2,14,15}
};

extern UINT8 creationPieces[];

UINT8 collision_tiles[] = {81,82,1,2,3,8,12,55,18,48,45,51,52,56,50,18,17,69,97,70,38,49,72,73,74,124,115,120,106,107,125,100,101,102};

BYTE open[] = {0,0,0,0,0};
BYTE lastopen;

BYTE dosynthesis = 0;

extern BYTE CreationDead;

UINT8 gatespots[]={
10,0,0,0,10
};

UINT8 level =0;
UINT8 door=1; //door of last entry for spawn location, 1 is left side
UINT8 doorpointsx[] = {
		125,
	25,
	125,
	25,
	130,
	16,
		120,
	25,
		125,
	25,
	};
UINT8 doorpointsy[] = {
	97,80,
	25,97,
	25,25,
	97,25,
	80,97
	};

Sprite* Creation;
Sprite* CreationArmL;
Sprite* CreationHead;
Sprite* CreationArmR;
Sprite* CreationLegs;



UINT8 machinepoints[5][2] = {
	{0,0},{0,0},{16,104},{0,0},{64,104}
};
void pDelay(UINT8 numloops){
    UINT8 i;
    for(i=0;i<numloops;i++){
        wait_vbl_done();
    }
}

void ScreenShake(UINT8 duration,INT8 seismicscale){
	
	UINT8 d;

for(d=0;d<duration;d++){

	scroll_offset_x=seismicscale;

	///scroll_offset_y=seismicscale;
		pDelay(2);
		scroll_offset_x=-seismicscale;

	//scroll_offset_y=-seismicscale;
		pDelay(2);
}

scroll_offset_x=0;
scroll_offset_y=0;
}



void DoSynthesis(){
	//not,1down,1left,2h,2v,elbow L/D, ULD T, LDR T, +
	// ARM L     HEAD    ARM R    FOOT
	//well this is a hot mess lmao. idk how to make it good tho and frankly i dont have time to care
	//Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);

	if(creationPieces[0]==0 && creationPieces[1]==0 && creationPieces[2]==0 && creationPieces[3]>=1){
		
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);
		SetFrame(Creation,1);
	}
	else if(creationPieces[0]==0 && creationPieces[1]==0 && creationPieces[2]>=1 && creationPieces[3]==0){
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);
		SetFrame(Creation,2);
		Creation->mirror = HV_MIRROR;
	}
	else if(creationPieces[0]==0 && creationPieces[1]==0 && creationPieces[2]>=1 && creationPieces[3]>=1){
		
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);
		SetFrame(Creation,5);
			Creation->mirror = V_MIRROR;
	}
	else if(creationPieces[0]==0 && creationPieces[1]>=1 && creationPieces[2]==0 && creationPieces[3]==0){
		
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);
		Creation->mirror = HV_MIRROR;
		SetFrame(Creation,1);
	}
	else if(creationPieces[0]==0 && creationPieces[1]>=1 && creationPieces[2]==0 && creationPieces[3]>=1){
		
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);
		SetFrame(Creation,4);
	}
	else if(creationPieces[0]==0 && creationPieces[1]>=1 && creationPieces[2]>=1 && creationPieces[3]==0){
		
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);
		SetFrame(Creation,5);
		Creation->mirror = HV_MIRROR;
	}
	else if(creationPieces[0]==0 && creationPieces[1]>=1 && creationPieces[2]>=1 && creationPieces[3]>=1){
		
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);
		SetFrame(Creation,6);
			Creation->mirror = V_MIRROR;
	}
	else if(creationPieces[0]>=1 && creationPieces[1]==0 && creationPieces[2]==0 && creationPieces[3]==0){
		
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);
		SetFrame(Creation,2);
	}
	else if(creationPieces[0]>=1 && creationPieces[1]==0 && creationPieces[2]==0 && creationPieces[3]>=1){
		
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);
		SetFrame(Creation,5);
	}
	else if(creationPieces[0]>=1 && creationPieces[1]==0 && creationPieces[2]>=1 && creationPieces[3]==0){
		
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);
		SetFrame(Creation,3);
	}
	else if(creationPieces[0]>=1 && creationPieces[1]==0 && creationPieces[2]>=1 && creationPieces[3]>=1){
		
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);
		SetFrame(Creation,7);
	}
	else if(creationPieces[0]>=1 && creationPieces[1]>=1 && creationPieces[2]==0 && creationPieces[3]==0){
		
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);
		SetFrame(Creation,5);
		Creation->mirror = H_MIRROR;
	}
	else if(creationPieces[0]>=1 && creationPieces[1]>=1 && creationPieces[2]==0 && creationPieces[3]>=1){
		
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);
		SetFrame(Creation,6);
	
	}	
	else if(creationPieces[0]>=1 && creationPieces[1]>=1 && creationPieces[2]>=1 && creationPieces[3]==0){
		
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);
		SetFrame(Creation,7);
		Creation->mirror = H_MIRROR;
	}
	else if(creationPieces[0]>=1 && creationPieces[1]>=1 && creationPieces[2]>1 && creationPieces[3]>=1){
		
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);
		SetFrame(Creation,8);
	}
	else if(creationPieces[0]>=1 && creationPieces[1]>=1 && creationPieces[2]>1 && creationPieces[3]>=1){
		Creation = SpriteManagerAdd(CreationBody,machinepoints[level][0],machinepoints[level][1]+8);

	}

	INT8 posits[4][2]={
		{1,-1},{2,-2},{3,-1},{2,0}
	};

	UINT8 cc = 0;
	//yes i broke open a for loop just for the sprite definitions don't laugh at me
	


	switch(creationPieces[cc]){
		case 0: break;
		case 1: CreationArmL = SpriteManagerAdd(CreationWorm,machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16);
			//	CreationArmL = CreateWorm(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,0);
		break;
		case 2: CreationArmL =SpriteManagerAdd(CreationCrab,machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16);
		break;
		case 3:  CreationArmL = SpriteManagerAdd(CreationBlob,machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16);
		//CreateBlob(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,0);

		break;

	}	
		 cc = 1;
	switch(creationPieces[cc]){
		case 0: break;
		case 1: CreationHead = SpriteManagerAdd(CreationWorm,machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16);
		//CreateWorm(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,1);
		break;
		case 2:CreationHead =  SpriteManagerAdd(CreationCrab,machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16);
		break;
		case 3: CreationHead =   SpriteManagerAdd(CreationBlob,machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16);
		//CreateBlob(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,1);
		break;

	}	
	 cc = 2;
	switch(creationPieces[cc]){
		case 0: break;
		case 1: CreationArmR = SpriteManagerAdd(CreationWorm,machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16);
		//	CreateWorm(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,2);

		break;
		case 2: CreationArmR =  SpriteManagerAdd(CreationCrab,machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16);
		break;
		case 3:  CreationArmR =  SpriteManagerAdd(CreationBlob,machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16);
		//CreateBlob(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,2);
		break;

	}
		 cc = 3;
	switch(creationPieces[cc]){
		case 0: break;
		case 1: CreationLegs = SpriteManagerAdd(CreationWorm,machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16);
			//CreateWorm(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,3);
	
		break;
		case 2: CreationLegs =SpriteManagerAdd(CreationCrab,machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16);
		break;
		case 3: CreationLegs =SpriteManagerAdd(CreationBlob,machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16);
		//CreateBlob(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,3);
		break;

	}
		CUSTOM_DATA* dataar = (CUSTOM_DATA*)CreationArmL->custom_data;
	dataar->parent = Creation;
	dataar->orientation = 0;
	dataar->frameskip = 0;
		CUSTOM_DATA* datah = (CUSTOM_DATA*)CreationHead->custom_data;
	datah->parent = Creation;
	datah->orientation = 1;
	datah->frameskip = 0;
		CUSTOM_DATA* dataal = (CUSTOM_DATA*)CreationArmR->custom_data;
	dataal->parent = Creation;
	dataal->orientation = 2;
	dataal->frameskip = 0;
		CUSTOM_DATA* datal = (CUSTOM_DATA*)CreationLegs->custom_data;
	datal->parent = Creation;
	datal->orientation = 3;
	datal->frameskip = 0;

	// SetSpriteAnim(CreationArmL,pieceanimations[0],10u);
	// SetSpriteAnim(CreationHead,pieceanimations[2],10u);
	// SetSpriteAnim(CreationArmR,pieceanimations[4],10u);
	// SetSpriteAnim(CreationLegs,pieceanimations[6],10u);
	//SetFrame(CreationArmL,0);

	dosynthesis = 0;
}

void START() {

	OBP0_REG = PAL_DEF(2,0,1,3);
	BGP_REG = PAL_DEF(3,2,1,0);
	//scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);

	   WX_REG = 7;
	   WY_REG = 144-40;
	// //scroll_h_border = 2 << 3;
	//InitWindow(0,0,BANK(dialogue),&dialogue);
	// InitScrollTiles()
	  INIT_FONT(diawindowandfont,PRINT_WIN);


		switch(level) {
			case 0:
			if(open[level]==0)InitScroll(BANK(lvl0), &lvl0, collision_tiles, 0);

			else {
				InitScroll(BANK(lvl0Clear), &lvl0Clear, collision_tiles, 0);
			lastopen = 1;
			}
			SpriteManagerAdd(SpritePlayer, doorpointsx[0+door], doorpointsy[0+door]);
			SpriteManagerAdd(Button,14*8,8*8-1)->mirror=HV_MIRROR;
			break;
		case 1:
			InitScroll(BANK(lvl1), &lvl1, collision_tiles, 0);
			
				SpriteManagerAdd(SpritePlayer, doorpointsx[2+door], doorpointsy[2+door]);
				
			break;
		case 2:
			if(open[level]==0)InitScroll(BANK(lvl2), &lvl2, collision_tiles, 0);
			else {InitScroll(BANK(lvl2Clear), &lvl2Clear, collision_tiles, 0);
			lastopen =1;
			}
			SpriteManagerAdd(SpritePlayer, doorpointsx[4+door], doorpointsy[4+door]);
			SpriteManagerAdd(Machine,16,96);
			SpriteManagerAdd(Button,136,88);

			
			//ScrollUpdateColumn() maybe try this with the gate removal
			break;

			case 3:
				InitScroll(BANK(lvl3), &lvl3, collision_tiles, 0);
				SpriteManagerAdd(SpritePlayer, doorpointsx[6+door], doorpointsy[6+door]);
			break;

			case 4:
			if(open[level]==0)InitScroll(BANK(lvl4), &lvl4, collision_tiles, 0);
			else {InitScroll(BANK(lvl4Clear), &lvl4Clear, collision_tiles, 0);
			lastopen=1;}
						SpriteManagerAdd(Machine,64,96);
						SpriteManagerAdd(SpritePlayer, doorpointsx[8+door], doorpointsy[8+door]);
						SpriteManagerAdd(Button,8*8,4*8-1)->mirror=HV_MIRROR;;
			break;
			case 5:
			SetState(StateThanks);

			default:
				InitScroll(BANK(lvl0), &lvl0, collision_tiles, 0);
							
				SpriteManagerAdd(SpritePlayer, 20, 70);

				level=0;
			break;

		}

if(dosynthesis)DoSynthesis();

 	
lastopen = open[level];
	SpriteManagerAdd(SpritePlayerHead,80,60);
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume
PlayMusic(aca,1);

//INIT_CONSOLE(terminalfont,3,2);
}	


void OpenGate(){
//set_bkg_tiles(15,1,1,7,0); ...this doesn't work because the collision remains

switch (level){ //i hate this solution lmao
	case 0:ScrollSetMap(BANK(lvl0Clear),&lvl0Clear);
	break;
	case 2:ScrollSetMap(BANK(lvl2Clear),&lvl2Clear);
	break;
	case 4:ScrollSetMap(BANK(lvl4Clear),&lvl4Clear);
	break;
	default:break;

}

	PlayFx(CHANNEL_1,30);
	PlayFx(CHANNEL_2,30);
	PlayFx(CHANNEL_3,30);

	UINT8 ct=1;
	for(ct;ct<7;ct++){

		
		ScrollUpdateRow(0,ct+gatespots[level]);
		pDelay(10);
		PlayFx(CHANNEL_4,10,0x3F,0xF3,0x4F,0xC0);
				PlayFx(CHANNEL_1,10);
	PlayFx(CHANNEL_2,10);
	PlayFx(CHANNEL_3,10);
		ScreenShake(1,1);	
	}

}


/*
void HandleCreation(){


	if(CreationArmL){
		if(CreationDead){
			SpriteManagerRemoveSprite(CreationArmL);
		}
	//	else{	

		//	CreationArmL->x = Creation->x-16;//add some multipliers for the direction to shift when he turns
	//		CreationArmL->y = Creation->y;	

			//}
	}
		if(CreationArmR){
					if(CreationDead){
			SpriteManagerRemoveSprite(CreationArmR);
		}
	//	else{	
//	CreationArmR->x = Creation->x+16;//add some multipliers for the direction to shift when he turns
//	CreationArmR->y = Creation->y;
	//SetFrame(CreationArmR,8);

	}
	//}
		if(CreationHead){
					if(CreationDead){
			SpriteManagerRemoveSprite(CreationHead);
		}
	//	else{	
//	CreationHead->x = Creation->x;//add some multipliers for the direction to shift when he turns
//	CreationHead->y = Creation->y-16;
			//	SetFrame(CreationHead,4);

	}
	//}
		if(CreationLegs){
					if(CreationDead){
			SpriteManagerRemoveSprite(CreationLegs);
		}
	//	else{	
//	CreationLegs->x = Creation->x;//add some multipliers for the direction to shift when he turns
//	CreationLegs->y = Creation->y+16;
	//	SetFrame(CreationLegs,12);
	}//}
	

}
*/


void UPDATE() {
	if(lastopen!=open[level]){
		OpenGate();
		lastopen = 1;
	}
	//HandleCreation();


}
