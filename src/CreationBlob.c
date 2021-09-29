#include "Banks/SetAutoBank.h"
#include "main.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Print.h"
extern UINT8 creation_shift;
const INT8 bshotdirections[4][2]={
    {-1,0},{0,-1},{1,0},{0,1}
};

typedef struct {
    UINT8 orientation; //L U R D
    Sprite* parent;
    int frameskip;
    INT8 vx;
    INT8 vy;
}CUSTOM_DATA;

void CreateBlob(UINT8 cbx,UINT8 cby,Sprite* cbParent, UINT8 cbOrientation){
      Sprite* spr;
     spr= SpriteManagerAdd(CreationBlob,cbx,cby);
  CUSTOM_DATA* data = (CUSTOM_DATA*)spr->custom_data;
  data->parent = cbParent;
  data->orientation=cbOrientation;
 data->frameskip = 0;
//return spr;
}


void OrientBlob(){
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
        case 3:SetFrame(THIS,3);
          THIS->mirror=NO_MIRROR;
        break;
        
    }
}


void Start_CreationBlob(){
CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
}

void Update_CreationBlob(){
CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

data->frameskip++;
if(data->frameskip==100){

    data->frameskip=0;
   Sprite* spt = SpriteManagerAdd(Spit,THIS->x,THIS->y);
    CUSTOM_DATA* spitdata = (CUSTOM_DATA*)spt->custom_data;
     spitdata->vx = bshotdirections[data->orientation+creation_shift][0];
     spitdata->vy = bshotdirections[data->orientation+creation_shift][1];

}

OrientBlob();//i dont want to call this on update but if we're doing turning shit it might be easiest

THIS->x= data->parent->x+bshotdirections[(data->orientation+creation_shift)%4][0]*16;
THIS->y= data->parent->y+bshotdirections[(data->orientation+creation_shift)%4][1]*16;


}
void Destroy_CreationBlob(){

}

