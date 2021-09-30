#include "Banks/SetAutoBank.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Sound.h"

extern Sprite* Creation; //WHY IN GODS NAME DOES CUSTOM DATA BREAK EVERYTHING. WHY DO I HAVE TO DO IT LIKE THIS. I FEEL DIRTY.
// const UINT8 wiggle[] = {2,0,1};
// UINT8 flipctEye = 0;
// BYTE flipEye = 0;
 const UINT8 blink[] = {20,0,0,0,0,0,1,2,2,1,0,0,0,0,0,0,0,0,0,0,0};
 extern UINT8 creation_shift;
extern BYTE CreationDead;
void Start_CreationEye(){

SetSpriteAnim(THIS,blink,10u);
}

void Update_CreationEye(){
   
THIS->x= Creation->x;
THIS->y= Creation->y;
if(Creation==NULL)SpriteManagerRemoveSprite(THIS);
}
void Destroy_CreationEye(){
if(CreationDead == 1)
{PlayFx(CHANNEL_1,20,0x7E,0xFF,0xF4,0x73,0x86);
PlayFx(CHANNEL_2,20,0xC7,0xEE,0x00,0xC0);
PlayFx(CHANNEL_3,20,0x80,0x00,0x20,0xB4,0xC3);
PlayFx(CHANNEL_4,20,0x3F,0xFA,0x33,0xC0);}
}

