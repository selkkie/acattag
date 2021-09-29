#include "Banks/SetAutoBank.h"
#include "main.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
extern UINT8 creation_shift;
const INT8 wshotdirections[4][2]={
    {-1,0},{0,-1},{1,0},{0,1}
};
extern BYTE CreationDead;

typedef struct {
    UINT8 orientation; //L U R D
    Sprite* parent;
    int frameskip;
}CUSTOM_DATA;

void CreateWorm(UINT8 cwx,UINT8 cwy,Sprite* cwParent, UINT8 cwOrientation){
    //  spr;
  Sprite* spr= SpriteManagerAdd(CreationWorm,cwx,cwy);
 CUSTOM_DATA* data = (CUSTOM_DATA*)spr->custom_data;
 data->parent =cwParent;
  data->orientation=cwOrientation;
  data->frameskip = 0;
 //return spr;
}

void Start_CreationWorm(){
CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

}

void OrientWorm(){
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    switch(data->orientation){
        case 0:SetFrame(THIS,0);
        THIS->mirror=NO_MIRROR;
        break;
        case 1:SetFrame(THIS,2);
           THIS->mirror=NO_MIRROR;
        break;
        case 2:SetFrame(THIS,0);
         THIS->mirror=V_MIRROR;
        break;
        case 3:SetFrame(THIS,4);
           THIS->mirror=NO_MIRROR;
        break;
    }
}

void Update_CreationWorm(){

CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

// data->frameskip++;
// if(data->frameskip==100){
//     data->frameskip=0;
//     CreateSpit(THIS->x,THIS->y,shotdirections[data->orientation][0],shotdirections[data->orientation][1]);
// }

OrientWorm();//i dont want to call this on update but if we're doing turning shit it might be easiest

THIS->x= data->parent->x+wshotdirections[data->orientation+creation_shift][0]*16;
THIS->y= data->parent->y+wshotdirections[data->orientation+creation_shift][1]*16;

if(data->parent==NULL)SpriteManagerRemoveSprite(THIS);

}
void Destroy_CreationWorm(){

}

