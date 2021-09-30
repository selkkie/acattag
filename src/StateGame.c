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

// void CreateBlob(UINT16 cbx,UINT16 cby,Sprite* cbParent, UINT8 cbOrientation);
// void CreateWorm(UINT16 cwx,UINT16 cwy,Sprite* cwParent, UINT8 cwOrientation);

typedef struct
{

	UINT8 orientation; //L U R D
	UINT8 fliptime;

} CUSTOM_DATA;

UINT8 creationRotation = 0;
UINT8 creationInitFrame;
UINT8 creationInitMirror;
MirroMode creation_mirrors[] = {NO_MIRROR, V_MIRROR, H_MIRROR, HV_MIRROR};

const UINT8 pieceanimations[8][3] = {
	{2, 0, 1}, {2, 2, 3}, {2, 4, 5}, {2, 6, 7}, {2, 8, 9}, {2, 10, 11}, {2, 12, 13}, {2, 14, 15}};

extern UINT8 creationPieces[];

UINT8 collision_tiles[] = {81, 82, 1, 2, 3, 8, 12, 55, 18, 48, 45, 51, 52, 56, 50, 18, 17, 69, 97, 70, 38, 49, 72, 73, 74, 124, 115, 120, 106, 107, 125, 100, 101, 102};

BYTE open[] = {0, 0, 0, 0, 0};
BYTE lastopen;

BYTE dosynthesis = 0;
BYTE frommachine = 0;

UINT8 gatespots[] = {
	10, 0, 0, 0, 10};

UINT8 level = 0;
UINT8 door = 1; //door of last entry for spawn location, 1 is left side
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
	97, 80,
	25, 97,
	25, 25,
	97, 25,
	80, 97};

Sprite *Creation;
Sprite *CreationArmL;
Sprite *CreationHead;
Sprite *CreationArmR;
Sprite *CreationLegs;
Sprite *ceye;

UINT8 creation_frameskip = 0;
INT8 creation_shift = 0;

INT8 creation_dir[4][2] = {
	{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
BYTE CreationDead = 0;
UINT8 creation_tile_collision;

UINT8 machinepoints[5][2] = {
	{0, 0}, {0, 0}, {16, 104}, {0, 0}, {64, 104}};

void pDelay(UINT8 numloops)
{
	UINT8 i;
	for (i = 0; i < numloops; i++)
	{
		wait_vbl_done();
	}
}

void ScreenShake(UINT8 duration, INT8 seismicscale)
{

	UINT8 d;

	for (d = 0; d < duration; d++)
	{

		scroll_offset_x = seismicscale;

		///scroll_offset_y=seismicscale;
		pDelay(2);
		scroll_offset_x = -seismicscale;

		//scroll_offset_y=-seismicscale;
		pDelay(2);
	}

	scroll_offset_x = 0;
	scroll_offset_y = 0;
}

// void //SetBodyData(Sprite* sprit,UINT8 inframe,UINT8 inmirror){
// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
// 		Creation = sprit;
// 		creationInitFrame = inframe;
// 		creationInitMirror=inmirror;
// }

void DoSynthesis()
{
	//not,1down,1left,2h,2v,elbow L/D, ULD T, LDR T, +
	// ARM L     HEAD    ARM R    FOOT
	//well this is a hot mess lmao. idk how to make it good tho and frankly i dont have time to care
	//Creation = SpriteManagerAdd(CreationHead,machinepoints[level][0],machinepoints[level][1]+8);

	if (creationPieces[0] == 0 && creationPieces[1] == 0 && creationPieces[2] == 0 && creationPieces[3] >= 1)
	{

		Creation = SpriteManagerAdd(CreationHead1, machinepoints[level][0], machinepoints[level][1] + 8);
		//SetBodyData(Creation,0,0);
		// CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 0;
		creationInitMirror = 0;
	}
	else if (creationPieces[0] == 0 && creationPieces[1] == 0 && creationPieces[2] >= 1 && creationPieces[3] == 0)
	{
		Creation = SpriteManagerAdd(CreationHead1, machinepoints[level][0], machinepoints[level][1] + 8);
		SetFrame(Creation, 1);
		//	Creation->mirror = HV_MIRROR;
		//SetBodyData(Creation,1,0);
		// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 1;
		creationInitMirror = 0;
	}
	else if (creationPieces[0] == 0 && creationPieces[1] == 0 && creationPieces[2] >= 1 && creationPieces[3] >= 1)
	{

		Creation = SpriteManagerAdd(CreationHead2e, machinepoints[level][0], machinepoints[level][1] + 8);
		Creation->mirror = V_MIRROR;
		//SetBodyData(Creation,0,1);
		// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 0;
		creationInitMirror = 1;
	}
	else if (creationPieces[0] == 0 && creationPieces[1] >= 1 && creationPieces[2] == 0 && creationPieces[3] == 0)
	{

		Creation = SpriteManagerAdd(CreationHead1, machinepoints[level][0], machinepoints[level][1] + 8);
		Creation->mirror = H_MIRROR;
		//SetBodyData(Creation,0,2);
		// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 0;
		creationInitMirror = 2;
	}
	else if (creationPieces[0] == 0 && creationPieces[1] >= 1 && creationPieces[2] == 0 && creationPieces[3] >= 1)
	{

		Creation = SpriteManagerAdd(CreationHead2, machinepoints[level][0], machinepoints[level][1] + 8);
		SetFrame(Creation, 1);
		//SetBodyData(Creation,1,0);
		// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 1;
		creationInitMirror = 0;
	}
	else if (creationPieces[0] == 0 && creationPieces[1] >= 1 && creationPieces[2] >= 1 && creationPieces[3] == 0)
	{

		Creation = SpriteManagerAdd(CreationHead2e, machinepoints[level][0], machinepoints[level][1] + 8);
		Creation->mirror = HV_MIRROR;
		//SetBodyData(Creation,0,3);
		// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 0;
		creationInitMirror = 3;
	}
	else if (creationPieces[0] == 0 && creationPieces[1] >= 1 && creationPieces[2] >= 1 && creationPieces[3] >= 1)
	{

		Creation = SpriteManagerAdd(CreationHead3, machinepoints[level][0], machinepoints[level][1] + 8);
		SetFrame(Creation, 1);
		Creation->mirror = V_MIRROR;
		//SetBodyData(Creation,1,1);
		// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 1;
		creationInitMirror = 1;
	}
	else if (creationPieces[0] >= 1 && creationPieces[1] == 0 && creationPieces[2] == 0 && creationPieces[3] == 0)
	{

		Creation = SpriteManagerAdd(CreationHead1, machinepoints[level][0], machinepoints[level][1] + 8);
		SetFrame(Creation, 1);
		//SetBodyData(Creation,1,0);
		// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 1;
		creationInitMirror = 0;
	}
	else if (creationPieces[0] >= 1 && creationPieces[1] == 0 && creationPieces[2] == 0 && creationPieces[3] >= 1)
	{

		Creation = SpriteManagerAdd(CreationHead2e, machinepoints[level][0], machinepoints[level][1] + 8);
		//SetBodyData(Creation,0,0);
		// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 0;
		creationInitMirror = 0;
	}
	else if (creationPieces[0] >= 1 && creationPieces[1] == 0 && creationPieces[2] >= 1 && creationPieces[3] == 0)
	{

		Creation = SpriteManagerAdd(CreationHead2, machinepoints[level][0], machinepoints[level][1] + 8);
		//SetBodyData(Creation,0,0);
		// 			CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 0;
		creationInitMirror = 0;
		//
	}
	else if (creationPieces[0] >= 1 && creationPieces[1] == 0 && creationPieces[2] >= 1 && creationPieces[3] >= 1)
	{

		Creation = SpriteManagerAdd(CreationHead3, machinepoints[level][0], machinepoints[level][1] + 8);
		//SetBodyData(Creation,0,0);
		// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 0;
		creationInitMirror = 0;
	}
	else if (creationPieces[0] >= 1 && creationPieces[1] >= 1 && creationPieces[2] == 0 && creationPieces[3] == 0)
	{

		Creation = SpriteManagerAdd(CreationHead2e, machinepoints[level][0], machinepoints[level][1] + 8);
		SetFrame(Creation, 1);
		//SetBodyData(Creation,1,0);
		// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 1;
		creationInitMirror = 0;
	}
	else if (creationPieces[0] >= 1 && creationPieces[1] >= 1 && creationPieces[2] == 0 && creationPieces[3] >= 1)
	{

		Creation = SpriteManagerAdd(CreationHead3, machinepoints[level][0], machinepoints[level][1] + 8);
		SetFrame(Creation, 1);
		//SetBodyData(Creation,1,0);
		// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 1;
		creationInitMirror = 0;
	}
	else if (creationPieces[0] >= 1 && creationPieces[1] >= 1 && creationPieces[2] >= 1 && creationPieces[3] == 0)
	{

		Creation = SpriteManagerAdd(CreationHead3, machinepoints[level][0], machinepoints[level][1] + 8);
		Creation->mirror = H_MIRROR;
		//SetBodyData(Creation,0,2);
		// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 0;
		creationInitMirror = 2;
	}
	else if (creationPieces[0] >= 1 && creationPieces[1] >= 1 && creationPieces[2] >= 1 && creationPieces[3] >= 1)
	{

		Creation = SpriteManagerAdd(CreationHead4, machinepoints[level][0], machinepoints[level][1] + 8);
		SetFrame(Creation, 8);
		//SetBodyData(Creation,0,0);
		// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 0;
		creationInitMirror = 0;
	}
	else
	{
		Creation = SpriteManagerAdd(CreationHead0, machinepoints[level][0] + 16, machinepoints[level][1] + 8);
		// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
		creationInitFrame = 0;
		creationInitMirror = 0;
	}
	// else if(creationPieces[0]>=1 && creationPieces[1]>=1 && creationPieces[2]>=1 && creationPieces[3]>=1){
	// 	Creation = SpriteManagerAdd(CreationHead,machinepoints[level][0],machinepoints[level][1]+8);
	// 		CUSTOM_DATA* cd = (CUSTOM_DATA*)Creation->custom_data;
	// 		creationInitFrame=;
	// 		creationInitMirror=;
	// }

	INT8 posits[4][2] = {
		{1, -1}, {2, -2}, {3, -1}, {2, 0}};

	UINT8 cc = 0;
	//yes i broke open a for loop just for the sprite definitions don't laugh at me

	switch (creationPieces[cc])
	{
	case 0:
		break;
	case 1:
		CreationArmL = SpriteManagerAdd(CreationWorm, machinepoints[level][0] + posits[cc][0] * 16, machinepoints[level][1] + posits[cc][1] * 16);
		//	CreationArmL = CreateWorm(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,0);
		break;
	case 2:
		CreationArmL = SpriteManagerAdd(CreationCrab, machinepoints[level][0] + posits[cc][0] * 16, machinepoints[level][1] + posits[cc][1] * 16);
		break;
	case 3:
		CreationArmL = SpriteManagerAdd(CreationBlob, machinepoints[level][0] + posits[cc][0] * 16, machinepoints[level][1] + posits[cc][1] * 16);
		//CreateBlob(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,0);

		break;
	}
	cc = 1;
	switch (creationPieces[cc])
	{
	case 0:
		break;
	case 1:
		CreationHead = SpriteManagerAdd(CreationWorm, machinepoints[level][0] + posits[cc][0] * 16, machinepoints[level][1] + posits[cc][1] * 16);
		//CreateWorm(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,1);
		break;
	case 2:
		CreationHead = SpriteManagerAdd(CreationCrab, machinepoints[level][0] + posits[cc][0] * 16, machinepoints[level][1] + posits[cc][1] * 16);
		break;
	case 3:
		CreationHead = SpriteManagerAdd(CreationBlob, machinepoints[level][0] + posits[cc][0] * 16, machinepoints[level][1] + posits[cc][1] * 16);
		//CreateBlob(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,1);
		break;
	}
	cc = 2;
	switch (creationPieces[cc])
	{
	case 0:
		break;
	case 1:
		CreationArmR = SpriteManagerAdd(CreationWorm, machinepoints[level][0] + posits[cc][0] * 16, machinepoints[level][1] + posits[cc][1] * 16);
		//	CreateWorm(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,2);

		break;
	case 2:
		CreationArmR = SpriteManagerAdd(CreationCrab, machinepoints[level][0] + posits[cc][0] * 16, machinepoints[level][1] + posits[cc][1] * 16);
		break;
	case 3:
		CreationArmR = SpriteManagerAdd(CreationBlob, machinepoints[level][0] + posits[cc][0] * 16, machinepoints[level][1] + posits[cc][1] * 16);
		//CreateBlob(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,2);
		break;
	}
	cc = 3;
	switch (creationPieces[cc])
	{
	case 0:
		break;
	case 1:
		CreationLegs = SpriteManagerAdd(CreationWorm, machinepoints[level][0] + posits[cc][0] * 16, machinepoints[level][1] + posits[cc][1] * 16);
		//CreateWorm(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,3);

		break;
	case 2:
		CreationLegs = SpriteManagerAdd(CreationCrab, machinepoints[level][0] + posits[cc][0] * 16, machinepoints[level][1] + posits[cc][1] * 16);
		break;
	case 3:
		CreationLegs = SpriteManagerAdd(CreationBlob, machinepoints[level][0] + posits[cc][0] * 16, machinepoints[level][1] + posits[cc][1] * 16);
		//CreateBlob(machinepoints[level][0]+posits[cc][0]*16,machinepoints[level][1]+posits[cc][1]*16,Creation,3);
		break;
	}
	CUSTOM_DATA *dataar = (CUSTOM_DATA *)CreationArmL->custom_data;

	dataar->orientation = 0;
	dataar->fliptime = 0;

	CUSTOM_DATA *datah = (CUSTOM_DATA *)CreationHead->custom_data;

	datah->orientation = 1;
	datah->fliptime = 0;

	CUSTOM_DATA *dataal = (CUSTOM_DATA *)CreationArmR->custom_data;

	dataal->orientation = 2;
	dataal->fliptime = 0;

	CUSTOM_DATA *datal = (CUSTOM_DATA *)CreationLegs->custom_data;

	datal->orientation = 3;
	datal->fliptime = 0;

	ceye = SpriteManagerAdd(CreationEye, machinepoints[level][0] + 16, machinepoints[level][1] + 8);
	//  CUSTOM_DATA* datai = (CUSTOM_DATA*)ceye->custom_data;
	//  datai->parent = Creation;

	// SetSpriteAnim(CreationArmL,pieceanimations[0],10u);
	// SetSpriteAnim(CreationHead,pieceanimations[2],10u);
	// SetSpriteAnim(CreationArmR,pieceanimations[4],10u);
	// SetSpriteAnim(CreationLegs,pieceanimations[6],10u);
	//SetFrame(CreationArmL,0);
	CreationDead = 0;
	dosynthesis = 0;
	creation_shift = 0;
}

void START()
{

	OBP0_REG = PAL_DEF(2, 0, 1, 3);
	//OBP1_REG = PAL_DEF(1, 0, 2, 3);
	BGP_REG = PAL_DEF(3, 2, 1, 0);
	//scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);

	WX_REG = 7;
	WY_REG = 144 - 40;
	// //scroll_h_border = 2 << 3;
	//InitWindow(0,0,BANK(dialogue),&dialogue);
	// InitScrollTiles()
	INIT_FONT(diawindowandfont, PRINT_WIN);

	SpriteManagerAdd(SpritePlayerHead, 80, 60);
	switch (level)
	{
	case 0:
		if (open[level] == 0)
			InitScroll(BANK(lvl0), &lvl0, collision_tiles, 0);

		else
		{
			InitScroll(BANK(lvl0Clear), &lvl0Clear, collision_tiles, 0);
			lastopen = 1;
		}
		SpriteManagerAdd(SpritePlayer, doorpointsx[0 + door], doorpointsy[0 + door]);
		SpriteManagerAdd(Button, 14 * 8, 8 * 8 - 1)->mirror = HV_MIRROR;
		break;
	case 1:
		InitScroll(BANK(lvl1), &lvl1, collision_tiles, 0);

		SpriteManagerAdd(SpritePlayer, doorpointsx[2 + door], doorpointsy[2 + door]);

		break;
	case 2:
		if (open[level] == 0)
			InitScroll(BANK(lvl2), &lvl2, collision_tiles, 0);
		else
		{
			InitScroll(BANK(lvl2Clear), &lvl2Clear, collision_tiles, 0);
			lastopen = 1;
		}
		if (frommachine)
			SpriteManagerAdd(SpritePlayer, machinepoints[2][0] + 16, machinepoints[2][1] - 7);
		else
			SpriteManagerAdd(SpritePlayer, doorpointsx[4 + door], doorpointsy[4 + door]);
		SpriteManagerAdd(Machine, 16, 96);
		SpriteManagerAdd(Button, 136, 88);

		//ScrollUpdateColumn() maybe try this with the gate removal
		break;

	case 3:
		InitScroll(BANK(lvl3), &lvl3, collision_tiles, 0);
		SpriteManagerAdd(SpritePlayer, doorpointsx[6 + door], doorpointsy[6 + door]);
		break;

	case 4:
		if (open[level] == 0)
			InitScroll(BANK(lvl4), &lvl4, collision_tiles, 0);
		else
		{
			InitScroll(BANK(lvl4Clear), &lvl4Clear, collision_tiles, 0);
			lastopen = 1;
		}

		if (frommachine)
			SpriteManagerAdd(SpritePlayer, machinepoints[4][0] - 16, machinepoints[4][1] - 7);
		else
			SpriteManagerAdd(SpritePlayer, doorpointsx[8 + door], doorpointsy[8 + door]);
		SpriteManagerAdd(Button, 8 * 8, 6 * 8 - 1)->mirror = HV_MIRROR;
		;
		SpriteManagerAdd(Machine, 64, 96);
		break;
	case 5:
		SetState(StateThanks);

	default:
		InitScroll(BANK(lvl0), &lvl0, collision_tiles, 0);

		SpriteManagerAdd(SpritePlayer, 20, 70);

		level = 0;
		break;
	}
	frommachine = 0;
	if (dosynthesis)
		DoSynthesis();

	lastopen = open[level];

	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume
	PlayMusic(aca, 1);

	//INIT_CONSOLE(diawindowandfont,3,2);
}

void OpenGate()
{
	//set_bkg_tiles(15,1,1,7,0); ...this doesn't work because the collision remains

	switch (level)
	{ //i hate this solution lmao
	case 0:
		ScrollSetMap(BANK(lvl0Clear), &lvl0Clear);
		break;
	case 2:
		ScrollSetMap(BANK(lvl2Clear), &lvl2Clear);
		break;
	case 4:
		ScrollSetMap(BANK(lvl4Clear), &lvl4Clear);
		break;
	default:
		break;
	}

	PlayFx(CHANNEL_1, 30);
	PlayFx(CHANNEL_2, 30);
	PlayFx(CHANNEL_3, 30);

	UINT8 ct = 1;
	for (ct; ct < 7; ct++)
	{

		ScrollUpdateRow(0, ct + gatespots[level]);
		pDelay(10);
		PlayFx(CHANNEL_4, 10, 0x3F, 0xF3, 0x4F, 0xC0);
		PlayFx(CHANNEL_1, 10);
		PlayFx(CHANNEL_2, 10);
		PlayFx(CHANNEL_3, 10);
		ScreenShake(1, 1);
	}
}

void CreationCheckCollisionTile(Sprite *sprite)
{
	if (creation_tile_collision == 100u || creation_tile_collision == 101u || creation_tile_collision == 102u)
	{
		SpriteManagerRemoveSprite(sprite);
		sprite = NULL;
		CreationDead=1;
	}
}
void Orient_Body()
{

	if (creationInitFrame != 8)
	{
		switch (creation_shift%4)
		{
		case 0:
			SetFrame(Creation, creationInitFrame);
			Creation->mirror = creation_mirrors[creationInitMirror];
			//if(creationInitFrame)
			break;
		case 1:
			SetFrame(Creation, (creationInitFrame + 1) % 2);
			Creation->mirror = creation_mirrors[(creationInitMirror + 3) % 4];
			break;
		case 2:
			SetFrame(Creation, (creationInitFrame + 0) % 2);
			Creation->mirror = creation_mirrors[(creationInitMirror + 3) % 4];
			break;
		case 3:
			SetFrame(Creation, (creationInitFrame + 1) % 2);
			Creation->mirror = creation_mirrors[(creationInitMirror + 0) % 4];
			break;
		}
	}
}
void Move_Body(BYTE goleft)
{

	if (goleft == 0)
	{
		creation_dir[0][0] = 1;
		creation_dir[2][0] = -1;
	}
	else
	{
		creation_dir[0][0] = -1;
		creation_dir[2][0] = 1;
	}
	if (TranslateSprite(Creation, creation_dir[(creation_shift + 1) % 4][0], creation_dir[(creation_shift + 1) % 4][1]))
	{
		//if there is a floor under me,

		//undo the test collision
		//TranslateSprite(Creation,creation_dir[(creation_shift+3)%3],creation_dir[(creation_shift+3)%3]);

		//try moving along it
		creation_tile_collision = TranslateSprite(Creation, creation_dir[creation_shift][0] << delta_time, creation_dir[creation_shift][1] << delta_time);
		if (creation_tile_collision)
		{
		creation_shift--;
		if (creation_shift < 0)
			creation_shift = 3;
			

		// 	//if i hit a wall, change direction
		// 	if (goleft == 0)
		// 	{
		// 		creation_shift--;
		// 		if (creation_shift < 0)
		// 			creation_shift = 3;
		// 	}
		// 	else
		// 	{
		// 		creation_shift++;
		// 		if (creation_shift > 3)
		// 			creation_shift = 0;
		// 	}
		}
	}
	else
	{
		//waitpad(J_A);
		//if there is no floor, creation_shift the other way
		creation_shift = (creation_shift + 1) % 4;

		// TranslateSprite(Creation, creation_dir[creation_shift][0] * 1, creation_dir[creation_shift][1] * 1); //force it to move so it gets the first collision instead of tumbling in air
		//pDelay(1);

		// This is incredibly dumb.
		INT8 creation_shift_attempt = creation_shift;
		for (int i = 0; i < 3; i++) {
			INT8 creation_shift_added = (creation_shift_attempt + 1) % 4;
			UINT8 trans_result = TranslateSprite(Creation, creation_dir[creation_shift_added][0] * 5, creation_dir[creation_shift_added][1] * 5);
			if (trans_result) {
				creation_shift = creation_shift_attempt;
				break;
			}
			TranslateSprite(Creation, (-1)*creation_dir[creation_shift_added][0] * 5, (-1)*creation_dir[creation_shift_added][1] * 5);
			creation_shift_attempt = creation_shift_added;
		}

	}
	Orient_Body();
}
void HandleCreation()
{
	if (Creation != NULL)
	{
		if (creationPieces[0] == 1 || creationPieces[2] == 1 || creationPieces[3] == 1)
		{
			creation_frameskip++;
			if (creation_frameskip > 2)
			{
				creation_frameskip = 0;
				if (creationPieces[2] == 1 && creationPieces[0] != 1)
					Move_Body(1);
				else if (creationPieces[0] == 1 && creationPieces[2] == 1)
					;
				else
					Move_Body(0);
			}
		}

		CreationCheckCollisionTile(Creation);
		CreationCheckCollisionTile(ceye);
		CreationCheckCollisionTile(CreationArmL);
		CreationCheckCollisionTile(CreationArmR);
		CreationCheckCollisionTile(CreationHead);
		CreationCheckCollisionTile(CreationLegs);
	}
}

void UPDATE()
{
	if (lastopen != open[level])
	{
		OpenGate();
		lastopen = 1;
	}

	// ceye->x = Creation->x;
	// ceye->y = Creation->y; //i swear to you i know this shouldn't all be in one file but everything keeps breaking when i try and keep it separated and i dont understand
	HandleCreation();
	// if(CreationArmL)
	// {SHOW_WIN;
	// PRINT_POS(0,0);
	// CUSTOM_DATA* data = (CUSTOM_DATA*)CreationArmL->custom_data;
	// char snum[5];
	// iota(data->orientation,snum);
	// Printf("%d.",snum);

	// }
}
