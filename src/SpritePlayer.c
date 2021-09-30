#include "Banks/SetAutoBank.h"

#include "main.h"
#include "gb/gb.h"
#include "ZGBMain.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "Math.h"
#include "Scroll.h"
#include "Sprite.h"
#include "Palette.h"
#include "Print.h"
#include <string.h>
#include "Sound.h"
#include "Music.h"

IMPORT_MAP(dialogue);
Sprite *sprite_body;
extern Sprite *Creation;
const UINT8 anim_idle[] = {1, 0};
const UINT8 anim_walk[] = {2, 1, 0};
extern BYTE CreationDead;
typedef enum
{
	PLAYER_STATE_NORMAL,
	PLAYER_STATE_JUMPING,
	PLAYER_STATE_FALLING
} PLAYER_STATE;
PLAYER_STATE player_state;
INT16 player_accel_y;
extern UINT16 reset_x;
extern UINT16 reset_y;
extern UINT8 level;
extern BYTE open[];
extern BYTE door;
extern BYTE lastopen;
extern BYTE clonestartile;
DECLARE_MUSIC(getscan);
DECLARE_MUSIC(aca);
uint8_t *saved_tilemap;

extern BYTE scanventory[] = {1, 0, 1};

//worm,crab,blob
enum mirror whyy[] = {V_MIRROR, NO_MIRROR};
void START()
{
	//	THIS->coll_h = 32;
	//	THIS->coll_y = -16;

	sprite_body = THIS;
	player_accel_y = 0;
	player_state = PLAYER_STATE_NORMAL;

	THIS->mirror = whyy[door];
}

UINT8 tile_collision;
void CheckCollisionTile(Sprite *sprite, UINT8 idx)
{
	if (tile_collision == 48u || tile_collision == 124u)
	{
		PlayFx(CHANNEL_1, 20, 0x16, 0x87, 0x53, 0x66, 0x86);
		level--;
		lastopen = open[level];
		door = 0;
		SetState(StateGame);
		clonestartile = 0;
	}
	else if (tile_collision == 45u || tile_collision == 125u)
	{
		PlayFx(CHANNEL_1, 20, 0x16, 0x87, 0x53, 0x66, 0x86);
		level++;
		lastopen = open[level];
		door = 1;
		SetState(StateGame);
		clonestartile = 0;
	}

	//vheckCollisionTile(Sprite* sprite, UINT8 idx) {
	// if(tile_collision == 33u) {
	// 	Die(sprite, idx);
	// } else if(tile_collision == 53u) {
	// 	if(level == 1) {
	// 		SetState(StateWin);
	// 	} else {
	// 		level ++;
	// 		reset_x = 32;
	// 		reset_y = 112;
	// 		SetState(StateGame);
	// 	}
	// }
}

void MovePlayer(Sprite *sprite, UINT8 idx)
{
	if (KEY_PRESSED(J_RIGHT))
	{
		tile_collision = TranslateSprite(sprite, 1 << delta_time, 0);
		THIS->mirror = NO_MIRROR;
		CheckCollisionTile(sprite, idx);
	}
	else if (KEY_PRESSED(J_LEFT))
	{
		tile_collision = TranslateSprite(sprite, -1 << delta_time, 0);
		THIS->mirror = V_MIRROR;
		CheckCollisionTile(sprite, idx);
	}
}
void Capture(char *who)
{

	waitpadup();
	SHOW_WIN;
	StopMusic;
	PlayMusic(getscan, 1);
	WY_REG = 144 - 40;
	InitWindow(0, 0, BANK(dialogue), &dialogue);

	PRINT_POS(2, 2);
	Printf("DNA SCANNED:");
	PRINT_POS(2, 3);
	Printf(who);
	waitpad(J_A | J_B | J_START);
	HIDE_WIN;
	waitpadup();
	StopMusic;
	PlayMusic(aca, 1);
}

void NoThanks()
{
	waitpadup();
	PlayFx(CHANNEL_1, 5, 0x79, 0xCF, 0x63, 0x73, 0x86);
	SHOW_WIN;
	WY_REG = 144 - 40;
	InitWindow(0, 0, BANK(dialogue), &dialogue);
	PRINT_POS(2, 2);
	Printf("...I already");
	PRINT_POS(2, 3);
	Printf("scanned that.");
	waitpad(J_A | J_B | J_START);
	HIDE_WIN;
	waitpadup();
}
void UPDATE()
{

	UINT8 i;
	Sprite *spr;

	if (KEY_PRESSED(J_START))
	{

		// 	get_bkg_tiles(2,1,1,6,saved_tilemap);
		// set_bkg_tiles(15,1,1,6,saved_tilemap);
	}
	if (KEY_PRESSED(J_SELECT))
	{
		open[level] = 1;
	}
	if (KEY_TICKED(J_START))
	{
		StopMusic;

		PlayFx(CHANNEL_1, 4, 0x7C, 0x87, 0x53, 0x66, 0x86);
		WY_REG = 144 - 16;
		InitWindow(0, 0, BANK(dialogue), &dialogue);
		SHOW_WIN;
		PRINT_POS(6, 1);
		Printf("PAUSED");
		waitpadup();

		waitpad(J_A | J_B | J_START);
		PlayFx(CHANNEL_1, 4, 0x74, 0x87, 0x53, 0x66, 0x86);
		waitpadup();
		HIDE_WIN;

		PlayMusic(aca, 1);
	}
	switch (player_state)
	{
	case PLAYER_STATE_NORMAL:
		MovePlayer(THIS, THIS_IDX);

		//Choose idle anim or walk
		if (KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT))
		{
			SetSpriteAnim(THIS, anim_walk, 10u);
		}
		else
		{
			SetSpriteAnim(THIS, anim_idle, 3u);
		}

		//Check jumping
		if (KEY_TICKED(J_A))
		{

			player_accel_y = -50;
			player_state = PLAYER_STATE_JUMPING;
			PlayFx(CHANNEL_1, 20, 0x16, 0x87, 0x53, 0x66, 0x86);
		}

		//Check falling
		if ((player_accel_y >> 4) > 1)
		{
			player_state = PLAYER_STATE_FALLING;
		}
		break;

	case PLAYER_STATE_JUMPING:
		SetSpriteAnim(THIS, anim_idle, 33u);
		MovePlayer(THIS, THIS_IDX);
		break;
	case PLAYER_STATE_FALLING:
		SetSpriteAnim(THIS, anim_idle, 33u);
		MovePlayer(THIS, THIS_IDX);
		break;
	}
	if (player_accel_y < 40)
	{
		player_accel_y += 2;
	}
	tile_collision = TranslateSprite(THIS, 0, player_accel_y >> 4);
	if (!tile_collision && delta_time != 0 && player_accel_y < 40)
	{ //Do another iteration if there is no collision
		player_accel_y += 2;
		tile_collision = TranslateSprite(THIS, 0, player_accel_y >> 4);
	}
	if (tile_collision)
	{
		player_accel_y = 0;
		if (player_state == PLAYER_STATE_JUMPING)
		{
			player_state = PLAYER_STATE_FALLING;
		}
		else if (player_state == PLAYER_STATE_FALLING)
		{
			player_state = PLAYER_STATE_NORMAL;
		}

		CheckCollisionTile(THIS, THIS_IDX);
	}

	// This is a quick and dirty hack, since
	// the game doesn't have more than one button
	// ever shown on-screen.
	Sprite* buttonAppearance = NULL;
	SPRITEMANAGER_ITERATE(i, spr)
	{
		if (spr->type == Machine)
		{
			if (CheckCollision(THIS, spr))
			{
				if (KEY_PRESSED(J_B))
				{
					StopMusic;
					PlayFx(CHANNEL_1, 4, 0x74, 0x87, 0x53, 0x66, 0x86);
					SetState(StateSynthesizer);
				}
			}
		}
		else if (spr->type == Worm)
		{
			if (CheckCollision(THIS, spr))
			{
				if (KEY_PRESSED(J_B))
				{
					if (scanventory[0] != 1)
					{
						Capture("WORM");
						scanventory[0] = 1;
					}
					else
					{
						NoThanks();
					}
				}
			}
		}
		else if (spr->type == Blob)
		{
			if (CheckCollision(THIS, spr))
			{
				if (KEY_PRESSED(J_B))
				{
					if (scanventory[2] != 1)
					{
						Capture("BLOB");
						scanventory[2] = 1;
					}
					else
					{
						NoThanks();
					}
				}
			}
		}

		else if (spr->type == Button)
		{
			if (CheckCollision(THIS, spr) || CheckCollision(Creation, spr))
			{
				if (open[level] == 0 && CreationDead == 0)
				{
					PlayFx(CHANNEL_1, 5, 0x79, 0x8F, 0x64, 0x0B, 0x86);
					SetFrame(spr, 1);
					open[level] = 1;
				}
			}
			else {
				buttonAppearance = spr;
			}
		}
		else if (spr->type == Spit) 
		{
			if (buttonAppearance != NULL && CheckCollision(buttonAppearance, spr)) 
			{
				if (open[level] == 0 && CreationDead == 0)
				{
					PlayFx(CHANNEL_1, 5, 0x79, 0x8F, 0x64, 0x0B, 0x86);
					SetFrame(spr, 1);
					open[level] = 1;
				}
			}
		}
	}
}
void DESTROY()
{
}