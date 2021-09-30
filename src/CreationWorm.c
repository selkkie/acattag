#include "Banks/SetAutoBank.h"
#include "main.h"
#include "ZGBMain.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Print.h"

extern Sprite* Creation;

extern UINT8 creation_shift;
const INT8 wshotdirections[4][2]={
    {-1,0},{0,-1},{1,0},{0,1}
};
extern BYTE CreationDead;
typedef struct{
    UINT8 orientation;
    UINT8 fliptime;
}CUSTOM_DATA;

BYTE flipwhen = 0;


UINT8 worm_fixedOrientation;
// void CreateWorm(UINT8 cwx,UINT8 cwy,Sprite* cwParent, UINT8 cwOrientation){
//     //  spr;
//   Sprite* spr= SpriteManagerAdd(CreationWorm,cwx,cwy);
//  CUSTOM_DATA* data = (CUSTOM_DATA*)spr->custom_data;
//  data->parent =cwParent;
//   data->orientation=cwOrientation;
//   data->frameskip = 0;
//  //return spr;
// }

void Start_CreationWorm(){


}

void OrientWorm(){

   CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
   if(worm_fixedOrientation!= data->orientation+creation_shift)
 {  flipwhen = 1;
     worm_fixedOrientation = data->orientation+creation_shift;

  
    switch(worm_fixedOrientation){
        case 0:
        if(data->orientation != 3){SetFrame(THIS,0);
        THIS->mirror=NO_MIRROR;}
        else{
            SetFrame(THIS,5);
            THIS->mirror=V_MIRROR;
        }

        break;
        case 1:
         if(data->orientation != 3){SetFrame(THIS,2);
           THIS->mirror=NO_MIRROR;}
           else{
               SetFrame(THIS,4);
               THIS->mirror=H_MIRROR;
           }
        break;
        case 2:
         if(data->orientation != 3){SetFrame(THIS,0);
         THIS->mirror=V_MIRROR;}
         else{
             SetFrame(THIS,5);
         }
        break;
        case 3:
         if(data->orientation != 3){SetFrame(THIS,2);
           THIS->mirror=H_MIRROR;}
        else{
            SetFrame(THIS,0);
        THIS->mirror=NO_MIRROR;
        }
        break;
        default: THIS->mirror=NO_MIRROR;break;

    }}
}

void Update_CreationWorm(){

   CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

// data->frameskip++;
// if(data->frameskip==100){
//     data->frameskip=0;
//     CreateSpit(THIS->x,THIS->y,shotdirections[data->orientation][0],shotdirections[data->orientation][1]);
// }

OrientWorm();//i dont want to call this on update but if we're doing turning stuff it might be easiest

THIS->x= Creation->x+wshotdirections[data->orientation+creation_shift][0]*16;
THIS->y= Creation->y+wshotdirections[data->orientation+creation_shift][1]*16;

if(Creation==NULL)SpriteManagerRemoveSprite(THIS);

}
void Destroy_CreationWorm(){

}

