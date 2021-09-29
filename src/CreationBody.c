
#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "SpriteManager.h"

UINT8 creation_frameskip = 0;
INT8 creation_shift=0;
 INT8 creation_dirx[4]={1,0,-1,0};
INT8 creation_diry[4]={0,1,0,-1};

UINT8 creation_tile_collision;

BYTE CreationDead = 0;
				//R,D,L,U
void Start_CreationBody(){
CreationDead = 0;
}
void CreationCheckCollisionTile(Sprite* sprite, UINT8 idx) {
	if(creation_tile_collision == 100u||creation_tile_collision==101u||creation_tile_collision==102u){
		SpriteManagerRemoveSprite(THIS);
	}


}


void Move_Body(BYTE goleft){
	if(goleft==0)
{ 
	creation_dirx[0]=1;
	creation_dirx[2]=-1;
	

 }
else{
creation_dirx[0]=-1;
	creation_dirx[2]=1;

}
if(TranslateSprite(THIS,creation_dirx[(creation_shift+1)%4],creation_diry[(creation_shift+1)%4])){
//if there is a floor under me, 

	//undo the test collision
//TranslateSprite(THIS,creation_dirx[(creation_shift+3)%3],creation_diry[(creation_shift+3)%3]);

	//try moving along it
creation_tile_collision =	TranslateSprite(THIS,creation_dirx[creation_shift]<<delta_time,creation_diry[creation_shift]<<delta_time);
	if(creation_tile_collision){

		//if i hit a wall, change direction
if(goleft==0)
{			creation_shift--;
	if(creation_shift<0)creation_shift=3;}
	else{
		creation_shift++;
		if(creation_shift>3)creation_shift=0;
	}

	}

}
else{
		//waitpad(J_A);
//if there is no floor, creation_shift the other way
if(goleft==0)
{		creation_shift++;
		if(creation_shift>3)creation_shift=0;
	TranslateSprite(THIS,creation_dirx[creation_shift]*3,creation_diry[creation_shift]*3); //force it to move so it gets the first collision instead of tumbling in air
}
else{
	creation_shift--;
	if(creation_shift<0)creation_shift=3;
	TranslateSprite(THIS,creation_dirx[creation_shift]*3,creation_diry[creation_shift]*3); //force it to move so it gets the first collision instead of tumbling in air

}
		//pDelay(1);

}}
void Update_CreationBody(){
	extern UINT8 creationPieces[];
	if(creationPieces[0]==1||creationPieces[2]==1||creationPieces[3]==1)
	{	
		creation_frameskip++;
		if(creation_frameskip>2){
			creation_frameskip = 0;
			if(creationPieces[2]==1)Move_Body(1);
				else Move_Body(0);
		}
	}

	CreationCheckCollisionTile(THIS, THIS_IDX);



	

}
void Destroy_CreationBody(){

}

